#include "global.h"
#include "text.h"
#include "text_window.h"
#include "window.h"
#include "palette.h"
#include "bg.h"
#include "graphics.h"

// const rom data
const u8 gTextWindowFrame1_Gfx[] = INCBIN_U8("graphics/text_window/1.4bpp");
static const u8 sTextWindowFrame2_Gfx[] = INCBIN_U8("graphics/text_window/2.4bpp");
static const u8 sTextWindowFrame3_Gfx[] = INCBIN_U8("graphics/text_window/3.4bpp");
static const u8 sTextWindowFrame4_Gfx[] = INCBIN_U8("graphics/text_window/4.4bpp");
static const u8 sTextWindowFrame5_Gfx[] = INCBIN_U8("graphics/text_window/5.4bpp");
static const u8 sTextWindowFrame6_Gfx[] = INCBIN_U8("graphics/text_window/6.4bpp");
static const u8 sTextWindowFrame7_Gfx[] = INCBIN_U8("graphics/text_window/7.4bpp");
static const u8 sTextWindowFrame8_Gfx[] = INCBIN_U8("graphics/text_window/8.4bpp");
static const u8 sTextWindowFrame9_Gfx[] = INCBIN_U8("graphics/text_window/9.4bpp");
static const u8 sTextWindowFrame10_Gfx[] = INCBIN_U8("graphics/text_window/10.4bpp");
static const u8 sTextWindowFrame11_Gfx[] = INCBIN_U8("graphics/text_window/11.4bpp");
static const u8 sTextWindowFrame12_Gfx[] = INCBIN_U8("graphics/text_window/12.4bpp");
static const u8 sTextWindowFrame13_Gfx[] = INCBIN_U8("graphics/text_window/13.4bpp");
static const u8 sTextWindowFrame14_Gfx[] = INCBIN_U8("graphics/text_window/14.4bpp");
static const u8 sTextWindowFrame15_Gfx[] = INCBIN_U8("graphics/text_window/15.4bpp");
static const u8 sTextWindowFrame16_Gfx[] = INCBIN_U8("graphics/text_window/16.4bpp");
static const u8 sTextWindowFrame17_Gfx[] = INCBIN_U8("graphics/text_window/17.4bpp");
static const u8 sTextWindowFrame18_Gfx[] = INCBIN_U8("graphics/text_window/18.4bpp");
static const u8 sTextWindowFrame19_Gfx[] = INCBIN_U8("graphics/text_window/19.4bpp");
static const u8 sTextWindowFrame20_Gfx[] = INCBIN_U8("graphics/text_window/20.4bpp");
static const u8 sTextWindowFrame21_Gfx[] = INCBIN_U8("graphics/text_window/21.4bpp");
static const u8 sTextWindowFrame22_Gfx[] = INCBIN_U8("graphics/text_window/22.4bpp");
static const u8 sTextWindowFrame23_Gfx[] = INCBIN_U8("graphics/text_window/23.4bpp");
static const u8 sTextWindowFrame24_Gfx[] = INCBIN_U8("graphics/text_window/24.4bpp");
static const u8 sTextWindowFrame25_Gfx[] = INCBIN_U8("graphics/text_window/25.4bpp");
static const u8 sTextWindowFrame26_Gfx[] = INCBIN_U8("graphics/text_window/26.4bpp");
static const u8 sTextWindowFrame27_Gfx[] = INCBIN_U8("graphics/text_window/27.4bpp");
static const u8 sTextWindowFrame28_Gfx[] = INCBIN_U8("graphics/text_window/28.4bpp");
static const u8 sTextWindowFrame29_Gfx[] = INCBIN_U8("graphics/text_window/29.4bpp");
static const u8 sTextWindowFrame30_Gfx[] = INCBIN_U8("graphics/text_window/30.4bpp");
static const u8 sTextWindowFrame31_Gfx[] = INCBIN_U8("graphics/text_window/31.4bpp");
static const u8 sTextWindowFrame32_Gfx[] = INCBIN_U8("graphics/text_window/32.4bpp");

const u16 gTextWindowFrame1_Pal[] = INCBIN_U16("graphics/text_window/1.gbapal");
static const u16 sTextWindowFrame2_Pal[] = INCBIN_U16("graphics/text_window/2.gbapal");
static const u16 sTextWindowFrame3_Pal[] = INCBIN_U16("graphics/text_window/3.gbapal");
static const u16 sTextWindowFrame4_Pal[] = INCBIN_U16("graphics/text_window/4.gbapal");
static const u16 sTextWindowFrame5_Pal[] = INCBIN_U16("graphics/text_window/5.gbapal");
static const u16 sTextWindowFrame6_Pal[] = INCBIN_U16("graphics/text_window/6.gbapal");
static const u16 sTextWindowFrame7_Pal[] = INCBIN_U16("graphics/text_window/7.gbapal");
static const u16 sTextWindowFrame8_Pal[] = INCBIN_U16("graphics/text_window/8.gbapal");
static const u16 sTextWindowFrame9_Pal[] = INCBIN_U16("graphics/text_window/9.gbapal");
static const u16 sTextWindowFrame10_Pal[] = INCBIN_U16("graphics/text_window/10.gbapal");
static const u16 sTextWindowFrame11_Pal[] = INCBIN_U16("graphics/text_window/11.gbapal");
static const u16 sTextWindowFrame12_Pal[] = INCBIN_U16("graphics/text_window/12.gbapal");
static const u16 sTextWindowFrame13_Pal[] = INCBIN_U16("graphics/text_window/13.gbapal");
static const u16 sTextWindowFrame14_Pal[] = INCBIN_U16("graphics/text_window/14.gbapal");
static const u16 sTextWindowFrame15_Pal[] = INCBIN_U16("graphics/text_window/15.gbapal");
static const u16 sTextWindowFrame16_Pal[] = INCBIN_U16("graphics/text_window/16.gbapal");
static const u16 sTextWindowFrame17_Pal[] = INCBIN_U16("graphics/text_window/17.gbapal");
static const u16 sTextWindowFrame18_Pal[] = INCBIN_U16("graphics/text_window/18.gbapal");
static const u16 sTextWindowFrame19_Pal[] = INCBIN_U16("graphics/text_window/19.gbapal");
static const u16 sTextWindowFrame20_Pal[] = INCBIN_U16("graphics/text_window/20.gbapal");
static const u16 sTextWindowFrame21_Pal[] = INCBIN_U16("graphics/text_window/21.gbapal");
static const u16 sTextWindowFrame22_Pal[] = INCBIN_U16("graphics/text_window/22.gbapal");
static const u16 sTextWindowFrame23_Pal[] = INCBIN_U16("graphics/text_window/23.gbapal");
static const u16 sTextWindowFrame24_Pal[] = INCBIN_U16("graphics/text_window/24.gbapal");
static const u16 sTextWindowFrame25_Pal[] = INCBIN_U16("graphics/text_window/25.gbapal");
static const u16 sTextWindowFrame26_Pal[] = INCBIN_U16("graphics/text_window/26.gbapal");
static const u16 sTextWindowFrame27_Pal[] = INCBIN_U16("graphics/text_window/27.gbapal");
static const u16 sTextWindowFrame28_Pal[] = INCBIN_U16("graphics/text_window/28.gbapal");
static const u16 sTextWindowFrame29_Pal[] = INCBIN_U16("graphics/text_window/29.gbapal");
static const u16 sTextWindowFrame30_Pal[] = INCBIN_U16("graphics/text_window/30.gbapal");
static const u16 sTextWindowFrame31_Pal[] = INCBIN_U16("graphics/text_window/31.gbapal");
static const u16 sTextWindowFrame32_Pal[] = INCBIN_U16("graphics/text_window/32.gbapal");

static const u16 sUnknown_0851017C[][16] =
{
    INCBIN_U16("graphics/text_window/message_box.gbapal"),
    INCBIN_U16("graphics/text_window/text_pal1.gbapal"),
    INCBIN_U16("graphics/text_window/text_pal2.gbapal"),
    INCBIN_U16("graphics/text_window/text_pal3.gbapal"),
    INCBIN_U16("graphics/text_window/text_pal4.gbapal")
};

static const struct TilesPal sWindowFrames[WINDOW_FRAMES_COUNT] =
{
    {gTextWindowFrame1_Gfx, gTextWindowFrame1_Pal},
    {sTextWindowFrame2_Gfx, sTextWindowFrame2_Pal},
    {sTextWindowFrame3_Gfx, sTextWindowFrame3_Pal},
    {sTextWindowFrame4_Gfx, sTextWindowFrame4_Pal},
    {sTextWindowFrame5_Gfx, sTextWindowFrame5_Pal},
    {sTextWindowFrame6_Gfx, sTextWindowFrame6_Pal},
    {sTextWindowFrame7_Gfx, sTextWindowFrame7_Pal},
    {sTextWindowFrame8_Gfx, sTextWindowFrame8_Pal},
    {sTextWindowFrame9_Gfx, sTextWindowFrame9_Pal},
    {sTextWindowFrame10_Gfx, sTextWindowFrame10_Pal},
    {sTextWindowFrame11_Gfx, sTextWindowFrame11_Pal},
    {sTextWindowFrame12_Gfx, sTextWindowFrame12_Pal},
    {sTextWindowFrame13_Gfx, sTextWindowFrame13_Pal},
    {sTextWindowFrame14_Gfx, sTextWindowFrame14_Pal},
    {sTextWindowFrame15_Gfx, sTextWindowFrame15_Pal},
    {sTextWindowFrame16_Gfx, sTextWindowFrame16_Pal},
    {sTextWindowFrame17_Gfx, sTextWindowFrame17_Pal},
    {sTextWindowFrame18_Gfx, sTextWindowFrame18_Pal},
    {sTextWindowFrame19_Gfx, sTextWindowFrame19_Pal},
    {sTextWindowFrame20_Gfx, sTextWindowFrame20_Pal},
    {sTextWindowFrame21_Gfx, sTextWindowFrame21_Pal},
    {sTextWindowFrame22_Gfx, sTextWindowFrame22_Pal},
    {sTextWindowFrame23_Gfx, sTextWindowFrame23_Pal},
    {sTextWindowFrame24_Gfx, sTextWindowFrame24_Pal},
    {sTextWindowFrame25_Gfx, sTextWindowFrame25_Pal},
    {sTextWindowFrame26_Gfx, sTextWindowFrame26_Pal},
    {sTextWindowFrame27_Gfx, sTextWindowFrame27_Pal},
    {sTextWindowFrame28_Gfx, sTextWindowFrame28_Pal},
    {sTextWindowFrame29_Gfx, sTextWindowFrame29_Pal},
    {sTextWindowFrame30_Gfx, sTextWindowFrame30_Pal},
    {sTextWindowFrame31_Gfx, sTextWindowFrame31_Pal},
    {sTextWindowFrame32_Gfx, sTextWindowFrame32_Pal},
};

// code
const struct TilesPal *GetWindowFrameTilesPal(u8 id)
{
    if (id >= WINDOW_FRAMES_COUNT)
        return &sWindowFrames[0];
    else
        return &sWindowFrames[id];
}

void LoadMessageBoxGfx(u8 windowId, u16 destOffset, u8 palOffset)
{
    LoadBgTiles(GetWindowAttribute(windowId, WINDOW_BG), gMessageBox_Gfx, 0x1C0, destOffset);
    LoadPalette(GetOverworldTextboxPalettePtr(), palOffset, 0x20);
}

void LoadUserWindowBorderGfx_(u8 windowId, u16 destOffset, u8 palOffset)
{
    LoadUserWindowBorderGfx(windowId, destOffset, palOffset);
}

void LoadWindowGfx(u8 windowId, u8 frameId, u16 destOffset, u8 palOffset)
{
    LoadBgTiles(GetWindowAttribute(windowId, WINDOW_BG), sWindowFrames[frameId].tiles, 0x120, destOffset);
    LoadPalette(sWindowFrames[frameId].pal, palOffset, 0x20);
}

void LoadUserWindowBorderGfx(u8 windowId, u16 destOffset, u8 palOffset)
{
    LoadWindowGfx(windowId, gSaveBlock2Ptr->optionsWindowFrameType, destOffset, palOffset);
}

void DrawTextBorderOuter(u8 windowId, u16 tileNum, u8 palNum)
{
    u8 bgLayer = GetWindowAttribute(windowId, WINDOW_BG);
    u16 tilemapLeft = GetWindowAttribute(windowId, WINDOW_TILEMAP_LEFT);
    u16 tilemapTop = GetWindowAttribute(windowId, WINDOW_TILEMAP_TOP);
    u16 width = GetWindowAttribute(windowId, WINDOW_WIDTH);
    u16 height = GetWindowAttribute(windowId, WINDOW_HEIGHT);

    FillBgTilemapBufferRect(bgLayer, tileNum + 0, tilemapLeft - 1,      tilemapTop - 1,         1,      1,      palNum);
    FillBgTilemapBufferRect(bgLayer, tileNum + 1, tilemapLeft,          tilemapTop - 1,         width,  1,      palNum);
    FillBgTilemapBufferRect(bgLayer, tileNum + 2, tilemapLeft + width,  tilemapTop - 1,         1,      1,      palNum);
    FillBgTilemapBufferRect(bgLayer, tileNum + 3, tilemapLeft - 1,      tilemapTop,             1,      height, palNum);
    FillBgTilemapBufferRect(bgLayer, tileNum + 5, tilemapLeft + width,  tilemapTop,             1,      height, palNum);
    FillBgTilemapBufferRect(bgLayer, tileNum + 6, tilemapLeft - 1,      tilemapTop + height,    1,      1,      palNum);
    FillBgTilemapBufferRect(bgLayer, tileNum + 7, tilemapLeft,          tilemapTop + height,    width,  1,      palNum);
    FillBgTilemapBufferRect(bgLayer, tileNum + 8, tilemapLeft + width,  tilemapTop + height,    1,      1,      palNum);
}

void DrawTextBorderInner(u8 windowId, u16 tileNum, u8 palNum)
{
    u8 bgLayer = GetWindowAttribute(windowId, WINDOW_BG);
    u16 tilemapLeft = GetWindowAttribute(windowId, WINDOW_TILEMAP_LEFT);
    u16 tilemapTop = GetWindowAttribute(windowId, WINDOW_TILEMAP_TOP);
    u16 width = GetWindowAttribute(windowId, WINDOW_WIDTH);
    u16 height = GetWindowAttribute(windowId, WINDOW_HEIGHT);

    FillBgTilemapBufferRect(bgLayer, tileNum + 0, tilemapLeft,              tilemapTop,                 1,          1,          palNum);
    FillBgTilemapBufferRect(bgLayer, tileNum + 1, tilemapLeft + 1,          tilemapTop,                 width - 2,  1,          palNum);
    FillBgTilemapBufferRect(bgLayer, tileNum + 2, tilemapLeft + width - 1,  tilemapTop,                 1,          1,          palNum);
    FillBgTilemapBufferRect(bgLayer, tileNum + 3, tilemapLeft,              tilemapTop + 1,             1,          height - 2, palNum);
    FillBgTilemapBufferRect(bgLayer, tileNum + 5, tilemapLeft + width - 1,  tilemapTop + 1,             1,          height - 2, palNum);
    FillBgTilemapBufferRect(bgLayer, tileNum + 6, tilemapLeft,              tilemapTop + height - 1,    1,          1,          palNum);
    FillBgTilemapBufferRect(bgLayer, tileNum + 7, tilemapLeft + 1,          tilemapTop + height - 1,    width -     2,  1,      palNum);
    FillBgTilemapBufferRect(bgLayer, tileNum + 8, tilemapLeft + width - 1,  tilemapTop + height - 1,    1,          1,          palNum);
}

void rbox_fill_rectangle(u8 windowId)
{
    u8 bgLayer = GetWindowAttribute(windowId, WINDOW_BG);
    u16 tilemapLeft = GetWindowAttribute(windowId, WINDOW_TILEMAP_LEFT);
    u16 tilemapTop = GetWindowAttribute(windowId, WINDOW_TILEMAP_TOP);
    u16 width = GetWindowAttribute(windowId, WINDOW_WIDTH);
    u16 height = GetWindowAttribute(windowId, WINDOW_HEIGHT);

    FillBgTilemapBufferRect(bgLayer, 0, tilemapLeft - 1, tilemapTop - 1, width + 2, height + 2, 0x11);
}

const u16 *stdpal_get(u8 id)
{
    switch (id)
    {
    case 0:
        id = 0;
        break;
    case 1:
        id = 0x10;
        break;
    case 2:
        id = 0x20;
        break;
    case 3:
        id = 0x30;
        break;
    case 4:
    default:
        id = 0x40;
        break;
    }

    return (const u16 *)(sUnknown_0851017C) + id;
}

const u16 *GetOverworldTextboxPalettePtr(void)
{
    return gMessageBox_Pal;
}

void sub_8098C6C(u8 bg, u16 destOffset, u8 palOffset)
{
    LoadBgTiles(bg, sWindowFrames[gSaveBlock2Ptr->optionsWindowFrameType].tiles, 0x120, destOffset);
    LoadPalette(GetWindowFrameTilesPal(gSaveBlock2Ptr->optionsWindowFrameType)->pal, palOffset, 0x20);
}
