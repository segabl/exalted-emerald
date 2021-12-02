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
    gSaveBlock2Ptr = (void*)&gSaveblock2;
    gSaveBlock1Ptr = (void*)&gSaveblock1;
    gPokemonStoragePtr = (void*)&gPokemonStorage;

    SetBagItemsPointers();
    SetDecorationInventoriesPointers();
}

void MoveSaveBlocks_ResetHeap(void)
{
    void *vblankCB, *hblankCB;

    // save interrupt functions and turn them off
    vblankCB = gMain.vblankCallback;
    hblankCB = gMain.hblankCallback;
    gMain.vblankCallback = NULL;
    gMain.hblankCallback = NULL;
    gTrainerHillVBlankCounter = NULL;

    SetSaveBlocksPointers(0);

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
    memset(gSaveBlock1Ptr->ownedPokeBalls, 0, sizeof(gSaveBlock1Ptr->ownedPokeBalls));
    for (i = 0; i < BAG_POKEBALLS_COUNT; i++)
    {
        if (gBagPocketPokeBalls[i].itemId == ITEM_NONE)
            break;
        else
        {
            u16 ballId = gBagPocketPokeBalls[i].itemId - FIRST_BALL_INDEX;
            u16 quantity = gBagPocketPokeBalls[i].quantity;
            gSaveBlock1Ptr->ownedPokeBalls[i] = ballId | (quantity << 6); // quantity can be 999 at max, only needs 10 bit
        }
    }
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
    memset(gSaveBlock1Ptr->ownedKeyItems, 0, sizeof(gSaveBlock1Ptr->ownedKeyItems));
    for (i = 0; i < BAG_KEYITEMS_COUNT; i++)
    {
        if (gBagPocketKeyItems[i].itemId == ITEM_NONE)
            break;
        gSaveBlock1Ptr->ownedKeyItems[i] = gBagPocketKeyItems[i].itemId - FIRST_KEY_ITEM_INDEX + 1; // + 1 to distinguish between no item and first item
    }
}

void LoadSerializedItems(void)
{
    int i, j;
    for (i = 0; i < BAG_POKEBALLS_COUNT; i++)
    {
        u16 pokeBallValue = gSaveBlock1Ptr->ownedPokeBalls[i];
        if (!pokeBallValue)
            break;
        gBagPocketPokeBalls[i].itemId = FIRST_BALL_INDEX + (pokeBallValue & 0x3F); // 0x3F = (1 << 6) - 1 (6 bits for ball id)
        gBagPocketPokeBalls[i].quantity = pokeBallValue >> 6;
    }
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
        if (!keyItemNum)
            break;
        gBagPocketKeyItems[i].itemId = FIRST_KEY_ITEM_INDEX + keyItemNum - 1;
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
        gLoadedSaveData.pokeBalls[i] = gBagPocketPokeBalls[i];

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
        gBagPocketPokeBalls[i] = gLoadedSaveData.pokeBalls[i];

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
