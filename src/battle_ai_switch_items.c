#include "global.h"
#include "battle.h"
#include "battle_ai_script_commands.h"
#include "battle_anim.h"
#include "battle_controllers.h"
#include "battle_setup.h"
#include "pokemon.h"
#include "random.h"
#include "util.h"
#include "constants/abilities.h"
#include "constants/battle_ai.h"
#include "constants/battle_move_effects.h"
#include "constants/item_effects.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/species.h"

#define BATTLE_HISTORY (gBattleResources->battleHistory)
#define BATTLE_HISTORY_USED_MOVES(battler) (gBattleResources->battleHistory->usedMoves[GET_BATTLER_SIDE2(battler)][gBattlerPartyIndexes[battler]])

#define IS_VALID_MOVE(move) (move != 0 && move != 0xFFFF)

// this file's functions
static bool8 HasSuperEffectiveMoveAgainstOpponents(bool8 noRng);
static bool8 FindMonWithFlagsAndSuperEffective(u8 battlerIn1, u8 battlerIn2, s32 firstId, s32 lastId, struct Pokemon *party, u8 invalidMons, u16 flags, u8 moduloPercent);
static bool8 ShouldUseItem(void);
static u32 GetBestMonDefensive(struct Pokemon *party, int firstId, int lastId, u8 invalidMons, u32 opposingBattler, u32 allowedDmgPercentage);
static u32 GetBestMonOffensive(struct Pokemon *party, int firstId, int lastId, u8 invalidMons, u32 opposingBattler);

void GetAIPartyIndexes(u32 battlerId, s32 *firstId, s32 *lastId)
{
    if (BATTLE_TWO_VS_ONE_OPPONENT && (battlerId & BIT_SIDE) == B_SIDE_OPPONENT)
    {
        *firstId = 0, *lastId = 6;
    }
    else if (gBattleTypeFlags & (BATTLE_TYPE_TWO_OPPONENTS | BATTLE_TYPE_INGAME_PARTNER | BATTLE_TYPE_x800000))
    {
        if ((battlerId & BIT_FLANK) == B_FLANK_LEFT)
            *firstId = 0, *lastId = 3;
        else
            *firstId = 3, *lastId = 6;
    }
    else
    {
        *firstId = 0, *lastId = 6;
    }
}

static void SaveBattleMons(struct BattlePokemon *battleMons)
{
    u8 i;
    for (i = 0; i < MAX_BATTLERS_COUNT; i++)
        battleMons[i] = gBattleMons[i];
}

static void LoadBattleMons(struct BattlePokemon *battleMons)
{
    u8 i;
    for (i = 0; i < MAX_BATTLERS_COUNT; i++)
        gBattleMons[i] = battleMons[i];
}

static u8 GetOpponent(u8 battler)
{
    u8 opponent;
    if (gLastHitBy[battler] != 0xFF && !(gAbsentBattlerFlags & gBitTable[gLastHitBy[battler]]))
        opponent = gLastHitBy[battler];
    else if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
    {
        opponent = BATTLE_OPPOSITE(battler);
        if (gAbsentBattlerFlags & gBitTable[opponent])
            opponent ^= BIT_FLANK;
    }
    else
    {
        opponent = GetBattlerAtPosition(GET_BATTLER_POSITION(battler) ^ BIT_SIDE);
    }
    return opponent;
}

static void PredictOpponentMove(u8 opponent, u16 *predictedMove, s32 *predictedDamage)
{
    u8 i;
    s32 weights[MAX_MON_MOVES];
    s32 damage[MAX_MON_MOVES];
    s32 totalWeight = 0;
    s32 randomRoll;
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        u16 move = BATTLE_HISTORY_USED_MOVES(opponent).moves[i];
        if (IS_VALID_MOVE(move))
        {
            damage[i] = 0;
            weights[i] = 100;
            if (gBattleMoves[move].power > 0)
            {
                damage[i] = AI_CalcDamage(move, opponent, gActiveBattler);
                weights[i] += damage[i];
            }
            totalWeight += weights[i];
        }
    }
    *predictedMove = MOVE_NONE;
    *predictedDamage = 0;
    randomRoll = Random32() % totalWeight;
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        randomRoll -= weights[i];
        if (randomRoll < 0)
        {
            *predictedMove = BATTLE_HISTORY_USED_MOVES(opponent).moves[i];
            *predictedDamage = damage[i];
            break;
        }
    }
}

static bool8 ShouldSwitchIfAllBadMoves(void)
{
    if (gBattleResources->ai->switchMon)
    {
        gBattleResources->ai->switchMon = 0;
        *(gBattleStruct->AI_monToSwitchIntoId + gActiveBattler) = PARTY_SIZE;
        BtlController_EmitTwoReturnValues(1, B_ACTION_SWITCH, 0);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

static bool8 ShouldSwitchIfPerishSong(void)
{
    if (gStatuses3[gActiveBattler] & STATUS3_PERISH_SONG
        && gDisableStructs[gActiveBattler].perishSongTimer == 0)
    {
        *(gBattleStruct->AI_monToSwitchIntoId + gActiveBattler) = PARTY_SIZE;
        BtlController_EmitTwoReturnValues(1, B_ACTION_SWITCH, 0);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

static bool8 ShouldSwitchIfWonderGuard(u8 battlerIn1, u8 battlerIn2, s32 firstId, s32 lastId, struct Pokemon *party, u8 invalidMons)
{
    u8 opposingBattler;
    s32 i, j;
    u16 move;

    if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
        return FALSE;

    opposingBattler = GetOpponent(gActiveBattler);

    if (gBattleMons[opposingBattler].ability != ABILITY_WONDER_GUARD)
        return FALSE;

    // Check if Pokemon has a super effective move.
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        move = gBattleMons[gActiveBattler].moves[i];
        if (move != MOVE_NONE)
        {
            if (AI_GetTypeEffectiveness(move, gActiveBattler, opposingBattler) >= UQ_4_12(2.0))
                return FALSE;
        }
    }

    // Find a Pokemon in the party that has a super effective move.
    for (i = firstId; i < lastId; i++)
    {
        if (invalidMons & gBitTable[i])
            continue;

        for (j = 0; j < MAX_MON_MOVES; j++)
        {
            move = GetMonData(&party[i], MON_DATA_MOVE1 + j);
            if (move != MOVE_NONE)
            {
                if (AI_GetTypeEffectiveness(move, gActiveBattler, opposingBattler) >= UQ_4_12(2.0) && Random() % 3 < 2)
                {
                    // We found a mon.
                    *(gBattleStruct->AI_monToSwitchIntoId + gActiveBattler) = i;
                    BtlController_EmitTwoReturnValues(1, B_ACTION_SWITCH, 0);
                    return TRUE;
                }
            }
        }
    }

    return FALSE; // There is not a single Pokemon in the party that has a super effective move against a mon with Wonder Guard.
}

static bool8 FindResistingOrImmuneMon(u8 battlerIn1, u8 battlerIn2, s32 firstId, s32 lastId, struct Pokemon *party, u8 invalidMons)
{
    struct BattlePokemon battleMons[MAX_BATTLERS_COUNT];
    u8 absorbingTypeAbility;
    u16 predictedMove;
    s32 predictedDamage;
    s32 bestDamage;
    s32 i;
    u8 bestMon = PARTY_SIZE;
    u8 attacker = GetOpponent(gActiveBattler);

    if (gChosenActionByBattler[attacker] == B_ACTION_SWITCH
    || gChosenActionByBattler[gActiveBattler] == B_ACTION_SWITCH)
        return FALSE;

    PredictOpponentMove(attacker, &predictedMove, &predictedDamage);

    if (gBattleMons[gActiveBattler].hp * 4 < gBattleMons[gActiveBattler].maxHP) // If HP are low, switching doesn't really make sense
        return FALSE;
    if (predictedDamage * 3 < gBattleMons[gActiveBattler].maxHP) // if damage is low, don't try to switch
        return FALSE;

    if (gBattleMoves[predictedMove].type == TYPE_FIRE)
        absorbingTypeAbility = ABILITY_FLASH_FIRE;
    else if (gBattleMoves[predictedMove].type == TYPE_WATER)
        absorbingTypeAbility = ABILITY_WATER_ABSORB;
    else if (gBattleMoves[predictedMove].type == TYPE_ELECTRIC)
        absorbingTypeAbility = ABILITY_VOLT_ABSORB;
    else if (gBattleMoves[predictedMove].type == TYPE_GROUND)
        absorbingTypeAbility = ABILITY_LEVITATE;

    if (absorbingTypeAbility && gBattleMons[gActiveBattler].ability == absorbingTypeAbility)
        return FALSE;

    bestDamage = predictedDamage;
    SaveBattleMons(battleMons);
    for (i = firstId; i < lastId; i++)
    {
        s32 dmg;
        if (invalidMons & gBitTable[i])
            continue;

        if (absorbingTypeAbility && absorbingTypeAbility == gBaseStats[GetMonData(&party[i], MON_DATA_SPECIES_EGG)].abilities[GetMonData(&party[i], MON_DATA_ABILITY_NUM)])
        {
            dmg = 0;
        }
        else
        {
            PokemonToBattleMon(&party[i], &gBattleMons[gActiveBattler]);
            dmg = AI_CalcDamage(predictedMove, attacker, gActiveBattler);
        }
        if (dmg <= 0)
        {
            bestDamage = 0;
            bestMon = i;
            break;
        }
        else if (dmg * 3 < gBattleMons[gActiveBattler].hp && dmg < bestDamage)
        {
            bestMon = i;
            bestDamage = dmg;
        }
    }
    LoadBattleMons(battleMons);
    if (bestMon != PARTY_SIZE && bestDamage < Random32() % predictedDamage)
    {
        // we found a mon.
        *(gBattleStruct->AI_monToSwitchIntoId + gActiveBattler) = bestMon;
        BtlController_EmitTwoReturnValues(1, B_ACTION_SWITCH, 0);
        return TRUE;
    }
    return FALSE;
}

static bool8 FindMonThatResistsTwoTurnMove(u8 battlerIn1, u8 battlerIn2, s32 firstId, s32 lastId, struct Pokemon *party, u8 invalidMons)
{
    struct BattlePokemon battleMons[MAX_BATTLERS_COUNT];
    s32 i;
    u8 switchToMon = PARTY_SIZE;
    s32 bestDamage;
    u8 attacker = GetOpponent(gActiveBattler);

    if (!IS_VALID_MOVE(gLastMoves[attacker]))
        return FALSE;
    if (gBattleMons[gActiveBattler].hp * 4 < gBattleMons[gActiveBattler].maxHP) // If HP are low, switching doesn't really make sense
        return FALSE;
    if (gBattleMoves[gLastMoves[attacker]].effect != EFFECT_SOLARBEAM
    && gBattleMoves[gLastMoves[attacker]].effect != EFFECT_SKULL_BASH
    && gBattleMoves[gLastMoves[attacker]].effect != EFFECT_TWO_TURNS_ATTACK
    && gBattleMoves[gLastMoves[attacker]].effect != EFFECT_SEMI_INVULNERABLE)
        return FALSE;
    bestDamage = AI_CalcDamage(gLastMoves[attacker], attacker, gActiveBattler);
    if (bestDamage * 3 < gBattleMons[gActiveBattler].maxHP) // if damage is low, don't try to switch
        return FALSE;

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        u16 move = gBattleMons[gActiveBattler].moves[i];
        // If we have a protect move, don't switch
        if (move != MOVE_NONE && gBattleMoves[move].effect == EFFECT_PROTECT)
            return FALSE;
    }

    SaveBattleMons(battleMons);
    for (i = firstId; i < lastId; i++)
    {
        s32 damage;
        if (invalidMons & gBitTable[i])
            continue;

        PokemonToBattleMon(&party[i], &gBattleMons[gActiveBattler]);
        damage = AI_CalcDamage(gLastMoves[attacker], attacker, gActiveBattler);
        if (damage < bestDamage && damage * 4 < gBattleMons[gActiveBattler].hp) // We gotta take at least less damage than a quarter of our hp to switch in
        {
            bestDamage = damage;
            switchToMon = i;
        }
    }
    LoadBattleMons(battleMons);
    if (switchToMon != PARTY_SIZE)
    {
        // we found a mon.
        *(gBattleStruct->AI_monToSwitchIntoId + gActiveBattler) = switchToMon;
        BtlController_EmitTwoReturnValues(1, B_ACTION_SWITCH, 0);
        return TRUE;
    }
    return FALSE;
}

static bool8 ShouldSwitchIfRegenerativeAbility(u8 battlerIn1, u8 battlerIn2, s32 firstId, s32 lastId, struct Pokemon *party, u8 invalidMons)
{
    u8 bestMon;
    u8 ability = gBattleMons[gActiveBattler].ability;

    if (ability != ABILITY_NATURAL_CURE && ability != ABILITY_REGENERATOR)
        return FALSE;

    // Checks for natural cure
    if (ability == ABILITY_NATURAL_CURE && !(gBattleMons[gActiveBattler].status1 & STATUS1_ANY))
        return FALSE;
    if (ability == ABILITY_NATURAL_CURE && gBattleMons[gActiveBattler].hp * 2 < gBattleMons[gActiveBattler].maxHP)
        return FALSE;

    // Checks for regenerator
    if (ability == ABILITY_REGENERATOR && gBattleMons[gActiveBattler].hp * 3 > gBattleMons[gActiveBattler].maxHP * 2)
        return FALSE;

    bestMon = GetBestMonDefensive(party, firstId, lastId, invalidMons, GetOpponent(gActiveBattler), 35);

    if (bestMon != PARTY_SIZE && (Random() & 1))
    {
        *(gBattleStruct->AI_monToSwitchIntoId + gActiveBattler) = bestMon;
        BtlController_EmitTwoReturnValues(1, B_ACTION_SWITCH, 0);
        return TRUE;
    }

    return FALSE;
}

static bool8 HasSuperEffectiveMoveAgainstOpponents(bool8 noRng)
{
    u8 opposingPosition;
    u8 opposingBattler;
    s32 i;
    u16 move;

    opposingPosition = BATTLE_OPPOSITE(GET_BATTLER_POSITION(gActiveBattler));
    opposingBattler = GetBattlerAtPosition(opposingPosition);

    if (!(gAbsentBattlerFlags & gBitTable[opposingBattler]))
    {
        for (i = 0; i < MAX_MON_MOVES; i++)
        {
            move = gBattleMons[gActiveBattler].moves[i];
            if (move == MOVE_NONE)
                continue;

            if (AI_GetTypeEffectiveness(move, gActiveBattler, opposingBattler) >= UQ_4_12(2.0))
            {
                if (noRng)
                    return TRUE;
                if (Random() % 10 != 0)
                    return TRUE;
            }
        }
    }
    if (!(gBattleTypeFlags & BATTLE_TYPE_DOUBLE))
        return FALSE;

    opposingBattler = GetBattlerAtPosition(BATTLE_PARTNER(opposingPosition));

    if (!(gAbsentBattlerFlags & gBitTable[opposingBattler]))
    {
        for (i = 0; i < MAX_MON_MOVES; i++)
        {
            move = gBattleMons[gActiveBattler].moves[i];
            if (move == MOVE_NONE)
                continue;

            if (AI_GetTypeEffectiveness(move, gActiveBattler, opposingBattler) >= UQ_4_12(2.0))
            {
                if (noRng)
                    return TRUE;
                if (Random() % 10 != 0)
                    return TRUE;
            }
        }
    }

    return FALSE;
}

static bool8 AreStatsRaised(void)
{
    u8 buffedStatsValue = 0;
    s32 i;

    for (i = 0; i < NUM_BATTLE_STATS; i++)
    {
        if (gBattleMons[gActiveBattler].statStages[i] > 6)
            buffedStatsValue += gBattleMons[gActiveBattler].statStages[i] - 6;
    }

    return (buffedStatsValue > 3);
}

static bool8 FindMonWithFlagsAndSuperEffective(u8 battlerIn1, u8 battlerIn2, s32 firstId, s32 lastId, struct Pokemon *party, u8 invalidMons, u16 flags, u8 moduloPercent)
{
    s32 i, j;
    u16 move;

    if (!IS_VALID_MOVE(gLastLandedMoves[gActiveBattler]) || gBattleMoves[gLastLandedMoves[gActiveBattler]].power == 0)
        return FALSE;
    if (gLastHitBy[gActiveBattler] == 0xFF)
        return FALSE;

    for (i = firstId; i < lastId; i++)
    {
        u16 species;
        u8 monAbility;
        if (invalidMons & gBitTable[i])
            continue;

        species = GetMonData(&party[i], MON_DATA_SPECIES);
        monAbility = gBaseStats[species].abilities[GetMonData(&party[i], MON_DATA_ABILITY_NUM)];

        CalcPartyMonTypeEffectivenessMultiplier(gLastLandedMoves[gActiveBattler], species, monAbility);
        if (gMoveResultFlags & flags)
        {
            battlerIn1 = gLastHitBy[gActiveBattler];

            for (j = 0; j < MAX_MON_MOVES; j++)
            {
                move = GetMonData(&party[i], MON_DATA_MOVE1 + j);
                if (move == 0)
                    continue;

                if (AI_GetTypeEffectiveness(move, gActiveBattler, battlerIn1) >= UQ_4_12(2.0) && Random() % moduloPercent == 0)
                {
                    *(gBattleStruct->AI_monToSwitchIntoId + gActiveBattler) = i;
                    BtlController_EmitTwoReturnValues(1, B_ACTION_SWITCH, 0);
                    return TRUE;
                }
            }
        }
    }

    return FALSE;
}

static bool8 ShouldSwitch(void)
{
    u8 battlerIn1, battlerIn2;
    s32 firstId, lastId;
    struct Pokemon *party;
    s32 i;
    u8 invalidMons = 0;
    s32 availableToSwitch = 0;

    // If AI isn't smart, don't do advanced mon switches
    if (!(gBattleResources->ai->aiFlags & (AI_SCRIPT_CHECK_VIABILITY)))
        return FALSE;

    if (gBattleMons[gActiveBattler].status2 & (STATUS2_WRAPPED | STATUS2_ESCAPE_PREVENTION))
        return FALSE;
    if (gStatuses3[gActiveBattler] & STATUS3_ROOTED)
        return FALSE;
    if (IsAbilityOnOpposingSide(gActiveBattler, ABILITY_SHADOW_TAG))
        return FALSE;
    if (IsAbilityOnOpposingSide(gActiveBattler, ABILITY_ARENA_TRAP))
    {
        if (gBattleMons[gActiveBattler].type1 != TYPE_FLYING
        && gBattleMons[gActiveBattler].type2 != TYPE_FLYING
        && gBattleMons[gActiveBattler].ability != ABILITY_LEVITATE)
            return FALSE;
    }
    if (IsAbilityOnField(ABILITY_MAGNET_PULL))
    {
        if (gBattleMons[gActiveBattler].type1 == TYPE_STEEL)
            return FALSE;
        if (gBattleMons[gActiveBattler].type2 == TYPE_STEEL)
            return FALSE;
    }
    if (gBattleTypeFlags & BATTLE_TYPE_ARENA)
        return FALSE;

    if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
    {
        battlerIn1 = gActiveBattler;
        if (gAbsentBattlerFlags & gBitTable[GetBattlerAtPosition(BATTLE_PARTNER(GET_BATTLER_POSITION(gActiveBattler)))])
            battlerIn2 = gActiveBattler;
        else
            battlerIn2 = GetBattlerAtPosition(BATTLE_PARTNER(GET_BATTLER_POSITION(gActiveBattler)));
    }
    else
    {
        battlerIn1 = gActiveBattler;
        battlerIn2 = gActiveBattler;
    }

    GetAIPartyIndexes(gActiveBattler, &firstId, &lastId);

    if (GET_BATTLER_SIDE2(gActiveBattler) == B_SIDE_PLAYER)
        party = gPlayerParty;
    else
        party = gEnemyParty;

    for (i = firstId; i < lastId; i++)
    {
        if (GetMonData(&party[i], MON_DATA_HP) == 0
        || GetMonData(&party[i], MON_DATA_SPECIES_EGG) == SPECIES_NONE
        || GetMonData(&party[i], MON_DATA_SPECIES_EGG) == SPECIES_EGG
        || i == gBattlerPartyIndexes[battlerIn1]
        || i == gBattlerPartyIndexes[battlerIn2]
        || i == *(gBattleStruct->monToSwitchIntoId + battlerIn1)
        || i == *(gBattleStruct->monToSwitchIntoId + battlerIn2))
        {
            invalidMons |= gBitTable[i];
            continue;
        }
        availableToSwitch++;
    }

    if (availableToSwitch == 0)
        return FALSE;

    if (ShouldSwitchIfAllBadMoves())
        return TRUE;
    if (ShouldSwitchIfPerishSong())
        return TRUE;
    if (ShouldSwitchIfWonderGuard(battlerIn1, battlerIn2, firstId, lastId, party, invalidMons))
        return TRUE;
    if (FindMonThatResistsTwoTurnMove(battlerIn1, battlerIn2, firstId, lastId, party, invalidMons))
        return TRUE;
    if (FindResistingOrImmuneMon(battlerIn1, battlerIn2, firstId, lastId, party, invalidMons))
        return TRUE;
    if (ShouldSwitchIfRegenerativeAbility(battlerIn1, battlerIn2, firstId, lastId, party, invalidMons))
        return TRUE;
    if (HasSuperEffectiveMoveAgainstOpponents(FALSE))
        return FALSE;
    if (AreStatsRaised())
        return FALSE;
    if (FindMonWithFlagsAndSuperEffective(battlerIn1, battlerIn2, firstId, lastId, party, invalidMons, MOVE_RESULT_DOESNT_AFFECT_FOE, 2)
        || FindMonWithFlagsAndSuperEffective(battlerIn1, battlerIn2, firstId, lastId, party, invalidMons, MOVE_RESULT_NOT_VERY_EFFECTIVE, 3))
        return TRUE;

    return FALSE;
}

void AI_TrySwitchOrUseItem(void)
{
    struct Pokemon *party;
    u8 battlerIn1, battlerIn2;
    s32 firstId;
    s32 lastId; // + 1
    u8 battlerIdentity = GET_BATTLER_POSITION(gActiveBattler);

    if (GET_BATTLER_SIDE2(gActiveBattler) == B_SIDE_PLAYER)
        party = gPlayerParty;
    else
        party = gEnemyParty;

    if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
    {
        if (ShouldSwitch())
        {
            if (*(gBattleStruct->AI_monToSwitchIntoId + gActiveBattler) == PARTY_SIZE)
            {
                s32 monToSwitchId = GetMostSuitableMonToSwitchInto();
                if (monToSwitchId == PARTY_SIZE)
                {
                    if (!(gBattleTypeFlags & BATTLE_TYPE_DOUBLE))
                    {
                        battlerIn1 = GetBattlerAtPosition(battlerIdentity);
                        battlerIn2 = battlerIn1;
                    }
                    else
                    {
                        battlerIn1 = GetBattlerAtPosition(battlerIdentity);
                        battlerIn2 = GetBattlerAtPosition(battlerIdentity ^ BIT_FLANK);
                    }

                    GetAIPartyIndexes(gActiveBattler, &firstId, &lastId);

                    for (monToSwitchId = firstId; monToSwitchId < lastId; monToSwitchId++)
                    {
                        if (GetMonData(&party[monToSwitchId], MON_DATA_HP) == 0)
                            continue;
                        if (monToSwitchId == gBattlerPartyIndexes[battlerIn1])
                            continue;
                        if (monToSwitchId == gBattlerPartyIndexes[battlerIn2])
                            continue;
                        if (monToSwitchId == *(gBattleStruct->monToSwitchIntoId + battlerIn1))
                            continue;
                        if (monToSwitchId == *(gBattleStruct->monToSwitchIntoId + battlerIn2))
                            continue;

                        break;
                    }
                }

                *(gBattleStruct->AI_monToSwitchIntoId + gActiveBattler) = monToSwitchId;
            }

            *(gBattleStruct->monToSwitchIntoId + gActiveBattler) = *(gBattleStruct->AI_monToSwitchIntoId + gActiveBattler);
            return;
        }
        else if (ShouldUseItem())
        {
            return;
        }
    }

    BtlController_EmitTwoReturnValues(1, B_ACTION_USE_MOVE, (gActiveBattler ^ BIT_SIDE) << 8);
}

// If there are two(or more) mons to choose from, always choose one that has baton pass
// as most often it can't do much on its own.
static u32 GetBestMonBatonPass(struct Pokemon *party, int firstId, int lastId, u8 invalidMons, int aliveCount)
{
    int i, j, bits = 0;

    for (i = firstId; i < lastId; i++)
    {
        if (invalidMons & gBitTable[i])
            continue;

        for (j = 0; j < MAX_MON_MOVES; j++)
        {
            if (GetMonData(&party[i], MON_DATA_MOVE1 + j, NULL) == MOVE_BATON_PASS)
            {
                bits |= gBitTable[i];
                break;
            }
        }
    }

    if ((aliveCount == 2 || (aliveCount > 2 && Random() % 3 == 0)) && bits)
    {
        do
        {
            i = (Random() % (lastId - firstId)) + firstId;
        } while (!(bits & gBitTable[i]));
        return i;
    }

    return PARTY_SIZE;
}

static void MulModifier(u16 *modifier, u16 val)
{
    *modifier = UQ_4_12_TO_INT((*modifier * val) + UQ_4_12_ROUND);
}

static u32 GetBestMonOffensive(struct Pokemon *party, int firstId, int lastId, u8 invalidMons, u32 opposingBattler)
{
    int i, j;
    u32 bestDmg = 0;
    u32 bestMonId = PARTY_SIZE;
    struct BattlePokemon battleMons[MAX_BATTLERS_COUNT];
    SaveBattleMons(battleMons);
    // Find the mon that deals the most amount of damage
    for (i = firstId; i < lastId; i++)
    {
        if (!(gBitTable[i] & invalidMons))
        {
            PokemonToBattleMon(&party[i], &gBattleMons[gActiveBattler]);
            // Check the power of our moves
            for (j = 0; j < MAX_MON_MOVES; j++)
            {
                u16 move = GetMonData(&party[i], MON_DATA_MOVE1 + j);
                if (move != MOVE_NONE && gBattleMoves[move].power > 0)
                {
                    u32 dmg = AI_CalcDamage(move, gActiveBattler, opposingBattler);
                    if (dmg > bestDmg)
                    {
                        bestDmg = dmg;
                        bestMonId = i;
                    }
                }
            }
        }
    }
    LoadBattleMons(battleMons);
    return bestMonId;
}

static u32 GetBestMonDefensive(struct Pokemon *party, int firstId, int lastId, u8 invalidMons, u32 opposingBattler, u32 allowedDmgPercentage)
{
    int i, j;
    u32 bestDmg = 0xFFFFFFFF;
    u32 bestMonId = PARTY_SIZE;
    struct BattlePokemon battleMons[MAX_BATTLERS_COUNT];
    SaveBattleMons(battleMons);
    // Find the mon that takes the least amount of damage
    for (i = firstId; i < lastId; i++)
    {
        if (!(gBitTable[i] & invalidMons))
        {
            u32 maxDmg = 0;
            PokemonToBattleMon(&party[i], &gBattleMons[gActiveBattler]);
            // Consider the opponent's known/guessed moves
            for (j = 0; j < MAX_MON_MOVES; j++)
            {
                u16 move = BATTLE_HISTORY_USED_MOVES(opposingBattler).moves[j];
                if (move != MOVE_NONE && gBattleMoves[move].power > 0)
                {
                    u32 dmg = AI_CalcDamage(move, opposingBattler, gActiveBattler);
                    if (dmg > maxDmg)
                        maxDmg = dmg;
                }
            }
            if (maxDmg < bestDmg && maxDmg < (gBattleMons[gActiveBattler].hp * allowedDmgPercentage) / 100)
            {
                bestDmg = maxDmg;
                bestMonId = i;
            }
        }
    }
    LoadBattleMons(battleMons);
    return bestMonId;
}

u8 GetMostSuitableMonToSwitchInto(void)
{
    u32 opposingBattler = 0;
    u32 bestDmg = 0;
    u32 bestMonId = 0;
    u8 battlerIn1 = 0, battlerIn2 = 0;
    s32 firstId = 0;
    s32 lastId = 0; // + 1
    struct Pokemon *party;
    s32 i, j, aliveCount = 0;
    u8 invalidMons = 0;

    if (*(gBattleStruct->monToSwitchIntoId + gActiveBattler) != PARTY_SIZE)
        return *(gBattleStruct->monToSwitchIntoId + gActiveBattler);
    if (gBattleTypeFlags & BATTLE_TYPE_ARENA)
        return gBattlerPartyIndexes[gActiveBattler] + 1;

    if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
    {
        battlerIn1 = gActiveBattler;
        if (gAbsentBattlerFlags & gBitTable[GetBattlerAtPosition(GET_BATTLER_POSITION(gActiveBattler) ^ BIT_FLANK)])
            battlerIn2 = gActiveBattler;
        else
            battlerIn2 = GetBattlerAtPosition(GET_BATTLER_POSITION(gActiveBattler) ^ BIT_FLANK);
    }
    else
    {
        battlerIn1 = gActiveBattler;
        battlerIn2 = gActiveBattler;
    }
    opposingBattler = GetOpponent(gActiveBattler);

    GetAIPartyIndexes(gActiveBattler, &firstId, &lastId);

    if (GET_BATTLER_SIDE2(gActiveBattler) == B_SIDE_PLAYER)
        party = gPlayerParty;
    else
        party = gEnemyParty;

    // Get invalid slots ids.
    for (i = firstId; i < lastId; i++)
    {
        if (GetMonData(&party[i], MON_DATA_SPECIES) == SPECIES_NONE
            || GetMonData(&party[i], MON_DATA_HP) == 0
            || gBattlerPartyIndexes[battlerIn1] == i
            || gBattlerPartyIndexes[battlerIn2] == i
            || i == *(gBattleStruct->monToSwitchIntoId + battlerIn1)
            || i == *(gBattleStruct->monToSwitchIntoId + battlerIn2)
            || (GetMonAbility(&party[i]) == ABILITY_TRUANT && IsTruantMonVulnerable(gActiveBattler, opposingBattler))) // While not really invalid per say, not really wise to switch into this mon.
            invalidMons |= gBitTable[i];
        else
            aliveCount++;
    }

    bestMonId = GetBestMonBatonPass(party, firstId, lastId, invalidMons, aliveCount);

    // Try choosing a mon that resists the opponent first
    if (bestMonId == PARTY_SIZE)
        bestMonId = GetBestMonDefensive(party, firstId, lastId, invalidMons, opposingBattler, 50);

    // If there's no good defensive option, take the one that deals the most damage
    if (bestMonId == PARTY_SIZE)
        bestMonId = GetBestMonOffensive(party, firstId, lastId, invalidMons, opposingBattler);

    return bestMonId;
}

static u8 GetAI_ItemType(u16 itemId, const u8 *itemEffect)
{
    if (itemId == ITEM_FULL_RESTORE)
        return AI_ITEM_FULL_RESTORE;
    else if (itemEffect[4] & ITEM4_HEAL_HP)
        return AI_ITEM_HEAL_HP;
    else if (itemEffect[3] & ITEM3_STATUS_ALL)
        return AI_ITEM_CURE_CONDITION;
    else if (itemEffect[0] & (ITEM0_DIRE_HIT | ITEM0_X_ATTACK) || itemEffect[1] != 0 || itemEffect[2] != 0)
        return AI_ITEM_X_STAT;
    else if (itemEffect[3] & ITEM3_GUARD_SPEC)
        return AI_ITEM_GUARD_SPECS;
    else
        return AI_ITEM_NOT_RECOGNIZABLE;
}

static bool8 ShouldUseItem(void)
{
    struct Pokemon *party;
    s32 i;
    u8 validMons = 0;
    bool8 shouldUse = FALSE;

    if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER && GET_BATTLER_POSITION(gActiveBattler) == B_POSITION_PLAYER_RIGHT)
        return FALSE;

    if (GET_BATTLER_SIDE2(gActiveBattler) == B_SIDE_PLAYER)
        party = gPlayerParty;
    else
        party = gEnemyParty;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&party[i], MON_DATA_HP) != 0
            && GetMonData(&party[i], MON_DATA_SPECIES_EGG) != SPECIES_NONE
            && GetMonData(&party[i], MON_DATA_SPECIES_EGG) != SPECIES_EGG)
        {
            validMons++;
        }
    }

    for (i = 0; i < MAX_TRAINER_ITEMS; i++)
    {
        u16 item;
        const u8 *itemEffects;
        u8 paramOffset;
        u8 battlerSide;

        if (i != 0 && validMons > (BATTLE_HISTORY->itemsNo - i) + 1)
            continue;
        item = BATTLE_HISTORY->trainerItems[i];
        if (item == ITEM_NONE)
            continue;
        if (gItemEffectTable[item - FIRST_MEDICINE_INDEX] == NULL)
            continue;

        itemEffects = gItemEffectTable[item - FIRST_MEDICINE_INDEX];

        *(gBattleStruct->AI_itemType + gActiveBattler / 2) = GetAI_ItemType(item, itemEffects);

        switch (*(gBattleStruct->AI_itemType + gActiveBattler / 2))
        {
        case AI_ITEM_FULL_RESTORE:
            if (gBattleMons[gActiveBattler].hp >= gBattleMons[gActiveBattler].maxHP / 4)
                break;
            if (gBattleMons[gActiveBattler].hp == 0)
                break;
            shouldUse = TRUE;
            break;
        case AI_ITEM_HEAL_HP:
            paramOffset = GetItemEffectParamOffset(item, 4, 4);
            if (paramOffset == 0)
                break;
            if (gBattleMons[gActiveBattler].hp == 0)
                break;
            if (gBattleMons[gActiveBattler].hp < gBattleMons[gActiveBattler].maxHP / 4 || gBattleMons[gActiveBattler].maxHP - gBattleMons[gActiveBattler].hp > itemEffects[paramOffset])
                shouldUse = TRUE;
            break;
        case AI_ITEM_CURE_CONDITION:
            *(gBattleStruct->AI_itemFlags + gActiveBattler / 2) = 0;
            if (itemEffects[3] & ITEM3_SLEEP && gBattleMons[gActiveBattler].status1 & STATUS1_SLEEP)
            {
                *(gBattleStruct->AI_itemFlags + gActiveBattler / 2) |= 0x20;
                shouldUse = TRUE;
            }
            if (itemEffects[3] & ITEM3_POISON && (gBattleMons[gActiveBattler].status1 & STATUS1_POISON || gBattleMons[gActiveBattler].status1 & STATUS1_TOXIC_POISON))
            {
                *(gBattleStruct->AI_itemFlags + gActiveBattler / 2) |= 0x10;
                shouldUse = TRUE;
            }
            if (itemEffects[3] & ITEM3_BURN && gBattleMons[gActiveBattler].status1 & STATUS1_BURN)
            {
                *(gBattleStruct->AI_itemFlags + gActiveBattler / 2) |= 0x8;
                shouldUse = TRUE;
            }
            if (itemEffects[3] & ITEM3_FREEZE && gBattleMons[gActiveBattler].status1 & STATUS1_FREEZE)
            {
                *(gBattleStruct->AI_itemFlags + gActiveBattler / 2) |= 0x4;
                shouldUse = TRUE;
            }
            if (itemEffects[3] & ITEM3_PARALYSIS && gBattleMons[gActiveBattler].status1 & STATUS1_PARALYSIS)
            {
                *(gBattleStruct->AI_itemFlags + gActiveBattler / 2) |= 0x2;
                shouldUse = TRUE;
            }
            if (itemEffects[3] & ITEM3_CONFUSION && gBattleMons[gActiveBattler].status2 & STATUS2_CONFUSION)
            {
                *(gBattleStruct->AI_itemFlags + gActiveBattler / 2) |= 0x1;
                shouldUse = TRUE;
            }
            break;
        case AI_ITEM_X_STAT:
            *(gBattleStruct->AI_itemFlags + gActiveBattler / 2) = 0;
            if (gDisableStructs[gActiveBattler].isFirstTurn == 0)
                break;
            if (itemEffects[0] & ITEM0_X_ATTACK)
                *(gBattleStruct->AI_itemFlags + gActiveBattler / 2) |= 0x1;
            if (itemEffects[1] & ITEM1_X_DEFEND)
                *(gBattleStruct->AI_itemFlags + gActiveBattler / 2) |= 0x2;
            if (itemEffects[1] & ITEM1_X_SPEED)
                *(gBattleStruct->AI_itemFlags + gActiveBattler / 2) |= 0x4;
            if (itemEffects[2] & ITEM2_X_SPATK)
                *(gBattleStruct->AI_itemFlags + gActiveBattler / 2) |= 0x8;
            if (itemEffects[2] & ITEM2_X_ACCURACY)
                *(gBattleStruct->AI_itemFlags + gActiveBattler / 2) |= 0x20;
            if (itemEffects[0] & ITEM0_DIRE_HIT)
                *(gBattleStruct->AI_itemFlags + gActiveBattler / 2) |= 0x80;
            shouldUse = TRUE;
            break;
        case AI_ITEM_GUARD_SPECS:
            battlerSide = GET_BATTLER_SIDE2(gActiveBattler);
            if (gDisableStructs[gActiveBattler].isFirstTurn != 0 && gSideTimers[battlerSide].mistTimer == 0)
                shouldUse = TRUE;
            break;
        case AI_ITEM_NOT_RECOGNIZABLE:
            return FALSE;
        }

        if (shouldUse)
        {
            BtlController_EmitTwoReturnValues(1, B_ACTION_USE_ITEM, 0);
            *(gBattleStruct->chosenItem + (gActiveBattler / 2) * 2) = item;
            BATTLE_HISTORY->trainerItems[i] = 0;
            return shouldUse;
        }
    }

    return FALSE;
}
