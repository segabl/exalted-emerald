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

#define B_CRIT_CHANCE               GEN_7 // Chances of a critical hit landing. See atk04_critcalc.
#define B_FELL_STINGER_STAT_RAISE   GEN_7 // Gen6 Atk+2, Gen7 Atk+3.
#define B_ABILITY_WEATHER           GEN_7 // Up to gen5 - weather induced by abilities such as Drought or Drizzle lasted till the battle's end or weather change by a move. From Gen6 onwards, weather caused by abilities lasts the same amount of turns as induced from a move.
#define B_GALE_WINGS                GEN_7 // Gen7 requires full hp.
#define B_SOUND_SUBSTITUTE          GEN_7 // Starting from gen6 sound moves bypass Substitute.
#define B_EXP_CATCH                 GEN_7 // Starting from gen6, pokemon get experience from catching.
#define B_ABILITY_POP_UP            GEN_7 // Starting from gen5, the pokemon abilities are displayed in a pop-up, when they activate in battle.
#define B_STANCE_CHANGE_FAIL        GEN_7 // In Gen7, Aegislash's form change does not happen, if the pokemon cannot use a move, because of confusion, paralysis, etc. In gen6, the form change occurs despite not being able to move.

#define B_FAST_INTRO                TRUE // If set to TRUE, battle intro texts print at the same time as animation of a pokemon, as opposing to waiting for the animation to end.

#endif // GUARD_CONSTANTS_BATTLE_CONFIG_H
