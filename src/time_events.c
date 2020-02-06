#include "global.h"
#include "time_events.h"
#include "event_data.h"
#include "field_weather.h"
#include "pokemon.h"
#include "random.h"
#include "region_map.h"
#include "overworld.h"
#include "rtc.h"
#include "script.h"
#include "string_util.h"
#include "task.h"
#include "constants/maps.h"
#include "constants/mirage_locations.h"

static const u16 sMirageLocationMappings[][4] = {
    {MIRAGE_LOCATION_ROUTE_106,     MAP_GROUP(ROUTE106),      MAP_NUM(ROUTE106), TRUE},
    {MIRAGE_LOCATION_ROUTE_114,     MAP_GROUP(ROUTE114),      MAP_NUM(ROUTE114), FALSE},
    {MIRAGE_LOCATION_LILYCOVE_CITY, MAP_GROUP(LILYCOVE_CITY), MAP_NUM(LILYCOVE_CITY), FALSE},
    {MIRAGE_LOCATION_ROUTE_125,     MAP_GROUP(ROUTE125),      MAP_NUM(ROUTE125), TRUE},
    {MIRAGE_LOCATION_ROUTE_130,     MAP_GROUP(ROUTE130),      MAP_NUM(ROUTE130), TRUE},
};

static u32 GetMirageRnd(void)
{
    u32 hi = VarGet(VAR_MIRAGE_RND_H);
    u32 lo = VarGet(VAR_MIRAGE_RND_L);
    return (hi << 16) | lo;
}

static void SetMirageRnd(u32 rnd)
{
    VarSet(VAR_MIRAGE_RND_H, rnd >> 16);
    VarSet(VAR_MIRAGE_RND_L, rnd);
}

void UpdateMirageRnd(u16 days)
{
    s32 rnd = GetMirageRnd();
    while (days)
    {
        rnd = 1103515245 * rnd + 12345;
        days--;
    }
    SetMirageRnd(rnd);
}

u8 GetCurrentMirageLocation(void)
{
    if (FlagGet(FLAG_VISITED_PACIFIDLOG_TOWN))
    {
        return (GetMirageRnd() % NUM_MIRAGE_LOCATIONS) + 1;
    }
    return MIRAGE_LOCATION_NONE;
}

void BufferCurrentMirageLocationName(void)
{
    u8 i;
    u8 location = GetCurrentMirageLocation();
    for (i = 0; i < ARRAY_COUNT(sMirageLocationMappings); i++)
    {
        if (sMirageLocationMappings[i][0] == location)
        {
            u8 mapSecId = Overworld_GetMapHeaderByGroupAndId(sMirageLocationMappings[i][1], sMirageLocationMappings[i][2])->regionMapSectionId;
            StringCopy(gStringVar1, gRegionMapEntries[mapSecId].name);
            return;
        }
    }
}

bool8 MirageLocationOnlyDoWaterMonCries()
{
    u8 i;
    u8 location = GetCurrentMirageLocation();
    for (i = 0; i < ARRAY_COUNT(sMirageLocationMappings); i++)
    {
        if (gSaveBlock1Ptr->location.mapGroup == sMirageLocationMappings[i][1]
        && gSaveBlock1Ptr->location.mapNum == sMirageLocationMappings[i][2])
        {
            if (location == sMirageLocationMappings[i][0])
                return FALSE;
            else
                return sMirageLocationMappings[i][3];
        }
    }
    return FALSE;
}

void UpdateShoalTideFlag(void)
{
    static const u8 tide[] =
    {
        1, // 00
        1, // 01
        1, // 02
        0, // 03
        0, // 04
        0, // 05
        0, // 06
        0, // 07
        0, // 08
        1, // 09
        1, // 10
        1, // 11
        1, // 12
        1, // 13
        1, // 14
        0, // 15
        0, // 16
        0, // 17
        0, // 18
        0, // 19
        0, // 20
        1, // 21
        1, // 22
        1, // 23
    };

    if (IsMapTypeOutdoors(GetLastUsedWarpMapType()))
    {
        RtcCalcLocalTime();
        if (tide[gLocalTime.hours])
            FlagSet(FLAG_SYS_SHOAL_TIDE);
        else
            FlagClear(FLAG_SYS_SHOAL_TIDE);
    }
}

static void Task_WaitWeather(u8 taskId)
{
    if (IsWeatherChangeComplete())
    {
        EnableBothScriptContexts();
        DestroyTask(taskId);
    }
}

void WaitWeather(void)
{
    CreateTask(Task_WaitWeather, 80);
}

void InitBirchState(void)
{
    *GetVarPointer(VAR_BIRCH_STATE) = 0;
}

void UpdateBirchState(u16 days)
{
    u16 *state = GetVarPointer(VAR_BIRCH_STATE);
    *state += days;
    *state %= 7;
}

void UpdateAlteringCaveRnd(u16 days)
{
    s32 rnd = VarGet(VAR_ALTERING_CAVE_RND);
    while (days)
    {
        rnd = 1103515245 * rnd + 12345;
        days--;
    }
    VarSet(VAR_ALTERING_CAVE_RND, rnd);
}
