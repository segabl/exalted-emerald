#include "global.h"
#include "malloc.h"
#include "berry_powder.h"
#include "item.h"
#include "load_save.h"
#include "main.h"
#include "overworld.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "random.h"
#include "save_location.h"
#include "trainer_hill.h"
#include "gba/flash_internal.h"
#include "decoration_inventory.h"
#include "agb_flash.h"
#include "constants/items.h"

#define SAVEBLOCK_MOVE_RANGE    128

struct LoadedSaveData
{
 /*0x0000*/ struct ItemSlot items[BAG_ITEMS_COUNT];
 /*0x0078*/ struct ItemSlot keyItems[BAG_KEYITEMS_COUNT];
 /*0x00F0*/ struct ItemSlot pokeBalls[BAG_POKEBALLS_COUNT];
 /*0x0130*/ struct ItemSlot TMsHMs[BAG_TMHM_COUNT];
 /*0x0230*/ struct ItemSlot berries[BAG_BERRIES_COUNT];
 /*0x02E8*/ struct MailStruct mail[MAIL_COUNT];
};

// EWRAM DATA
EWRAM_DATA struct SaveBlock2 gSaveblock2 = {0};
EWRAM_DATA u8 gSaveblock2_DMA[SAVEBLOCK_MOVE_RANGE] = {0};

EWRAM_DATA struct SaveBlock1 gSaveblock1 = {0};
EWRAM_DATA u8 gSaveblock1_DMA[SAVEBLOCK_MOVE_RANGE] = {0};

EWRAM_DATA struct PokemonStorage gPokemonStorage = {0};
EWRAM_DATA u8 gSaveblock3_DMA[SAVEBLOCK_MOVE_RANGE] = {0};

EWRAM_DATA struct LoadedSaveData gLoadedSaveData = {0};

// IWRAM common
bool32 gFlashMemoryPresent;
struct SaveBlock1 *gSaveBlock1Ptr;
struct SaveBlock2 *gSaveBlock2Ptr;
struct PokemonStorage *gPokemonStoragePtr;

// code
void CheckForFlashMemory(void)
{
    if (!IdentifyFlash())
    {
        gFlashMemoryPresent = TRUE;
        InitFlashTimer();
    }
    else
    {
        gFlashMemoryPresent = FALSE;
    }
}

void ClearSav2(void)
{
    CpuFill16(0, &gSaveblock2, sizeof(struct SaveBlock2) + sizeof(gSaveblock2_DMA));
}

void ClearSav1(void)
{
    CpuFill16(0, &gSaveblock1, sizeof(struct SaveBlock1) + sizeof(gSaveblock1_DMA));
}

void SetSaveBlocksPointers(u16 offset)
{
    struct SaveBlock1** sav1_LocalVar = &gSaveBlock1Ptr;

    offset = (offset + Random()) & (SAVEBLOCK_MOVE_RANGE - 4);

    gSaveBlock2Ptr = (void*)(&gSaveblock2) + offset;
    *sav1_LocalVar = (void*)(&gSaveblock1) + offset;
    gPokemonStoragePtr = (void*)(&gPokemonStorage) + offset;

    SetBagItemsPointers();
    SetDecorationInventoriesPointers();
}

void MoveSaveBlocks_ResetHeap(void)
{
    void *vblankCB, *hblankCB;
    struct SaveBlock2 *saveBlock2Copy;
    struct SaveBlock1 *saveBlock1Copy;
    struct PokemonStorage *pokemonStorageCopy;

    // save interrupt functions and turn them off
    vblankCB = gMain.vblankCallback;
    hblankCB = gMain.hblankCallback;
    gMain.vblankCallback = NULL;
    gMain.hblankCallback = NULL;
    gTrainerHillVBlankCounter = NULL;

    saveBlock2Copy = (struct SaveBlock2 *)(gHeap);
    saveBlock1Copy = (struct SaveBlock1 *)(gHeap + sizeof(struct SaveBlock2));
    pokemonStorageCopy = (struct PokemonStorage *)(gHeap + sizeof(struct SaveBlock2) + sizeof(struct SaveBlock1));

    // backup the saves.
    *saveBlock2Copy = *gSaveBlock2Ptr;
    *saveBlock1Copy = *gSaveBlock1Ptr;
    *pokemonStorageCopy = *gPokemonStoragePtr;

    // change saveblocks' pointers
    // argument is a sum of the individual trainerId bytes
    SetSaveBlocksPointers(
      saveBlock2Copy->playerTrainerId[0] +
      saveBlock2Copy->playerTrainerId[1] +
      saveBlock2Copy->playerTrainerId[2] +
      saveBlock2Copy->playerTrainerId[3]);

    // restore saveblock data since the pointers changed
    *gSaveBlock2Ptr = *saveBlock2Copy;
    *gSaveBlock1Ptr = *saveBlock1Copy;
    *gPokemonStoragePtr = *pokemonStorageCopy;

    // heap was destroyed in the copying process, so reset it
    InitHeap(gHeap, HEAP_SIZE);

    // restore interrupt functions
    gMain.hblankCallback = hblankCB;
    gMain.vblankCallback = vblankCB;
}

u32 UseContinueGameWarp(void)
{
    return gSaveBlock2Ptr->specialSaveWarpFlags & CONTINUE_GAME_WARP;
}

void ClearContinueGameWarpStatus(void)
{
    gSaveBlock2Ptr->specialSaveWarpFlags &= ~CONTINUE_GAME_WARP;
}

void SetContinueGameWarpStatus(void)
{
    gSaveBlock2Ptr->specialSaveWarpFlags |= CONTINUE_GAME_WARP;
}

void SetContinueGameWarpStatusToDynamicWarp(void)
{
    SetContinueGameWarpToDynamicWarp(0);
    gSaveBlock2Ptr->specialSaveWarpFlags |= CONTINUE_GAME_WARP;
}

void ClearContinueGameWarpStatus2(void)
{
    gSaveBlock2Ptr->specialSaveWarpFlags &= ~CONTINUE_GAME_WARP;
}

void SavePlayerParty(void)
{
    int i;

    gSaveBlock1Ptr->playerPartyCount = gPlayerPartyCount;

    for (i = 0; i < PARTY_SIZE; i++)
        gSaveBlock1Ptr->playerParty[i] = gPlayerParty[i];
}

void LoadPlayerParty(void)
{
    int i;

    gPlayerPartyCount = gSaveBlock1Ptr->playerPartyCount;

    for (i = 0; i < PARTY_SIZE; i++)
        gPlayerParty[i] = gSaveBlock1Ptr->playerParty[i];
}

void SaveEventObjects(void)
{
    int i;

    for (i = 0; i < EVENT_OBJECTS_COUNT; i++)
        gSaveBlock1Ptr->eventObjects[i] = gEventObjects[i];
}

void LoadEventObjects(void)
{
    int i;

    for (i = 0; i < EVENT_OBJECTS_COUNT; i++)
        gEventObjects[i] = gSaveBlock1Ptr->eventObjects[i];
}

void SaveSerializedItems(void)
{
    int i;
    memset(gSaveBlock1Ptr->ownedTMsHMs, 0, sizeof(gSaveBlock1Ptr->ownedTMsHMs));
    for (i = 0; i < BAG_TMHM_COUNT; i++)
    {
        if (gBagPocketTMHM[i].itemId == ITEM_NONE)
            break;
        else
        {
            u16 tmNum = gBagPocketTMHM[i].itemId - FIRST_TM_INDEX;
            gSaveBlock1Ptr->ownedTMsHMs[tmNum / 8] |= 1 << (tmNum % 8);
        }
    }
    memset(gSaveBlock1Ptr->ownedBerries, 0, sizeof(gSaveBlock1Ptr->ownedBerries));
    for (i = 0; i < BAG_BERRIES_COUNT; i++)
    {
        if (gBagPocketBerries[i].itemId == ITEM_NONE)
            break;
        else
        {
            u16 berryNum = gBagPocketBerries[i].itemId - FIRST_BERRY_INDEX;
            gSaveBlock1Ptr->ownedBerries[berryNum] = gBagPocketBerries[i].quantity;
        }
    }
    memset(gSaveBlock1Ptr->ownedKeyItems, 0xFF, sizeof(gSaveBlock1Ptr->ownedKeyItems));
    for (i = 0; i < BAG_KEYITEMS_COUNT; i++)
    {
        if (gBagPocketKeyItems[i].itemId == ITEM_NONE)
            break;
        gSaveBlock1Ptr->ownedKeyItems[i] = gBagPocketKeyItems[i].itemId - FIRST_KEY_ITEM_INDEX;
    }
}

void LoadSerializedItems(void)
{
    int i, j;
    for (i = 0, j = 0; i < BAG_TMHM_COUNT; i++)
    {
        if ((gSaveBlock1Ptr->ownedTMsHMs[i / 8] >> (i % 8)) & 1)
        {
            gBagPocketTMHM[j].itemId = FIRST_TM_INDEX + i;
            gBagPocketTMHM[j].quantity = 1;
            j++;
        }
    }
    for (i = 0, j = 0; i < BAG_BERRIES_COUNT; i++)
    {
        u16 quantity = gSaveBlock1Ptr->ownedBerries[i];
        if (quantity > 0)
        {
            gBagPocketBerries[j].itemId = FIRST_BERRY_INDEX + i;
            gBagPocketBerries[j].quantity = quantity;
            j++;
        }
    }
    for (i = 0; i < BAG_KEYITEMS_COUNT; i++)
    {
        u8 keyItemNum = gSaveBlock1Ptr->ownedKeyItems[i];
        if (keyItemNum == 0xFF)
            break;
        gBagPocketKeyItems[i].itemId = FIRST_KEY_ITEM_INDEX + keyItemNum;
        gBagPocketKeyItems[i].quantity = 1;
    }
}

void SaveSerializedGame(void)
{
    SavePlayerParty();
    SaveEventObjects();
    SaveSerializedItems();
}

void LoadSerializedGame(void)
{
    LoadPlayerParty();
    LoadEventObjects();
    LoadSerializedItems();
}

void LoadPlayerBag(void)
{
    int i, j;
    struct ItemSlot *itemSlot;

    // load player items.
    for (i = 0; i < BAG_ITEMS_COUNT; i++)
        gLoadedSaveData.items[i] = gSaveBlock1Ptr->bagPocket_Items[i];

    // load player key items.
    for (i = 0; i < BAG_KEYITEMS_COUNT; i++)
        gLoadedSaveData.keyItems[i] = gBagPocketKeyItems[i];

    // load player pokeballs.
    for (i = 0; i < BAG_POKEBALLS_COUNT; i++)
        gLoadedSaveData.pokeBalls[i] = gSaveBlock1Ptr->bagPocket_PokeBalls[i];

    // load player TMs and HMs.
    for (i = 0; i < BAG_TMHM_COUNT; i++)
        gLoadedSaveData.TMsHMs[i] = gBagPocketTMHM[i];

    // load player berries.
    for (i = 0; i < BAG_BERRIES_COUNT; i++)
        gLoadedSaveData.berries[i] = gBagPocketBerries[i];

    // load mail.
    for (i = 0; i < MAIL_COUNT; i++)
        gLoadedSaveData.mail[i] = gSaveBlock1Ptr->mail[i];
}

void SavePlayerBag(void)
{
    int i;
    struct ItemSlot *itemSlot;

    // save player items.
    for (i = 0; i < BAG_ITEMS_COUNT; i++)
        gSaveBlock1Ptr->bagPocket_Items[i] = gLoadedSaveData.items[i];

    // save player key items.
    for (i = 0; i < BAG_KEYITEMS_COUNT; i++)
        gBagPocketKeyItems[i] = gLoadedSaveData.keyItems[i];

    // save player pokeballs.
    for (i = 0; i < BAG_POKEBALLS_COUNT; i++)
        gSaveBlock1Ptr->bagPocket_PokeBalls[i] = gLoadedSaveData.pokeBalls[i];

    // save player TMs and HMs.
    for (i = 0; i < BAG_TMHM_COUNT; i++)
        gBagPocketTMHM[i] = gLoadedSaveData.TMsHMs[i];

    // save player berries.
    for (i = 0; i < BAG_BERRIES_COUNT; i++)
        gBagPocketBerries[i] = gLoadedSaveData.berries[i];

    // save mail.
    for (i = 0; i < MAIL_COUNT; i++)
        gSaveBlock1Ptr->mail[i] = gLoadedSaveData.mail[i];
}
