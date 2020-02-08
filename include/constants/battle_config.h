#ifndef GUARD_CONSTANTS_BATTLE_CONFIG_H
#define GUARD_CONSTANTS_BATTLE_CONFIG_H

// Species with peculiar battle effects. Remove them if they're properly placed in constant/species.h
#define SPECIES_DIALGA 0
#define SPECIES_PALKIA 0
#define SPECIES_GIRATINA 0
#define SPECIES_CHERRIM 0
#define SPECIES_ARCEUS 0
#define SPECIES_SILVALLY 0
#define SPECIES_GENESECT 0
#define SPECIES_AEGISLASH 0
#define SPECIES_AEGISLASH_BLADE 10000

#define GEN_3 0
#define GEN_4 1
#define GEN_5 2
#define GEN_6 3
#define GEN_7 4

// Calculation settings
#define B_CRIT_CHANCE               GEN_7 // Chances of a critical hit landing. See atk04_critcalc.
#define B_CRIT_MULTIPLIER           GEN_7 // Starting from gen6, critical hits multiply damage by 1.5 instead of 2.
#define B_EXP_CATCH                 GEN_7 // Starting from gen6, pokemon get experience from catching.
#define B_TRAINER_EXP_MULTIPLIER    GEN_6 // Gen7 no longer gives a 1.5 multiplier to exp gain in trainer battles.
#define B_BURN_DAMAGE               GEN_7 // In Gen7, burn damage is 1/16th of max HP instead of 1/8th.
#define B_PARALYSIS_SPEED           GEN_7 // In Gen7, speed is decreased by 50% instead of 75%.

// Move settings
#define B_FELL_STINGER_STAT_RAISE   GEN_7 // Gen6 Atk+2, Gen7 Atk+3.
#define B_SOUND_SUBSTITUTE          GEN_7 // Starting from gen6 sound moves bypass Substitute.

// Ability settings
#define B_ABILITY_POP_UP            GEN_7 // Starting from gen5, the pokemon abilities are displayed in a pop-up, when they activate in battle.
#define B_ABILITY_WEATHER           GEN_7 // Up to gen5 - weather induced by abilities such as Drought or Drizzle lasted till the battle's end or weather change by a move. From Gen6 onwards, weather caused by abilities lasts the same amount of turns as induced from a move.
#define B_GALE_WINGS                GEN_7 // Gen7 requires full hp.
#define B_STANCE_CHANGE_FAIL        GEN_7 // In Gen7, Aegislash's form change does not happen, if the pokemon cannot use a move, because of confusion, paralysis, etc. In gen6, the form change occurs despite not being able to move.
#define B_GHOSTS_ESCAPE             GEN_6 // From Gen6 onwards, ghosts can escape even when blocked by abilities such as Shadow Tag.

// Other
#define B_FAST_INTRO                TRUE // If set to TRUE, battle intro texts print at the same time as animation of a pokemon, as opposing to waiting for the animation to end.

#endif // GUARD_CONSTANTS_BATTLE_CONFIG_H
