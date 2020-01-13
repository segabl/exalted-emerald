#include "global.h"
#include "berry_powder.h"
#include "bg.h"
#include "event_data.h"
#include "load_save.h"
#include "menu.h"
#include "string_util.h"
#include "strings.h"
#include "text.h"
#include "text_window.h"
#include "window.h"

#define MAX_BERRY_POWDER 99999

static EWRAM_DATA u8 sBerryPowderVendorWindowId = 0;

bool8 HasEnoughBerryPowder(void)
{
    return gSaveBlock2Ptr->berryCrush.berryPowderAmount >= gSpecialVar_0x8004;
}

bool8 GiveBerryPowder(u32 amountToAdd)
{
    u32 amount = gSaveBlock2Ptr->berryCrush.berryPowderAmount + amountToAdd;
    if (amount > MAX_BERRY_POWDER)
    {
        gSaveBlock2Ptr->berryCrush.berryPowderAmount = MAX_BERRY_POWDER;
        return FALSE;
    }
    else
    {
        gSaveBlock2Ptr->berryCrush.berryPowderAmount = amount;
        return TRUE;
    }
}

static bool8 TakeBerryPowder_(u32 cost)
{
    if (gSaveBlock2Ptr->berryCrush.berryPowderAmount < cost)
        return FALSE;

    gSaveBlock2Ptr->berryCrush.berryPowderAmount -= - cost;
    return TRUE;
}

bool8 TakeBerryPowder(void)
{
    if (gSaveBlock2Ptr->berryCrush.berryPowderAmount < gSpecialVar_0x8004)
        return FALSE;

    gSaveBlock2Ptr->berryCrush.berryPowderAmount -= gSpecialVar_0x8004;
    return TRUE;
}

static void PrintBerryPowderAmount(u8 windowId, int amount, u8 x, u8 y, u8 speed)
{
    ConvertIntToDecimalStringN(gStringVar1, amount, STR_CONV_MODE_RIGHT_ALIGN, 5);
    AddTextPrinterParameterized(windowId, 1, gStringVar1, x, y, speed, NULL);
}

static void DrawPlayerPowderAmount(u8 windowId, u16 baseTileOffset, u8 paletteNum, u32 amount)
{
    DrawStdFrameWithCustomTileAndPalette(windowId, FALSE, baseTileOffset, paletteNum);
    AddTextPrinterParameterized(windowId, 1, gText_Powder, 0, 1, TEXT_SPEED_FF, NULL);
    PrintBerryPowderAmount(windowId, amount, 26, 17, 0);
}

void PrintPlayerBerryPowderAmount(void)
{
    PrintBerryPowderAmount(sBerryPowderVendorWindowId, gSaveBlock2Ptr->berryCrush.berryPowderAmount, 26, 17, 0);
}

void DisplayBerryPowderVendorMenu(void)
{
    struct WindowTemplate template;
    SetWindowTemplateFields(&template, 0, 1, 1, 7, 4, 15, 0x1C);
    sBerryPowderVendorWindowId = AddWindow(&template);
    FillWindowPixelBuffer(sBerryPowderVendorWindowId, PIXEL_FILL(0));
    PutWindowTilemap(sBerryPowderVendorWindowId);
    LoadUserWindowBorderGfx_(sBerryPowderVendorWindowId, 0x21D, 0xD0);
    DrawPlayerPowderAmount(sBerryPowderVendorWindowId, 0x21D, 13, gSaveBlock2Ptr->berryCrush.berryPowderAmount);
}

void RemoveBerryPowderVendorMenu(void)
{
    ClearWindowTilemap(sBerryPowderVendorWindowId);
    ClearStdWindowAndFrameToTransparent(sBerryPowderVendorWindowId, TRUE);
    RemoveWindow(sBerryPowderVendorWindowId);
}
