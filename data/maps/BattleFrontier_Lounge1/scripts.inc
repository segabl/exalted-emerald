BattleFrontier_Lounge1_MapScripts:: @ 825E774
	.byte 0

@ NPC that rates pokemon based on their IVs
BattleFrontier_Lounge1_EventScript_Breeder:: @ 825E775
	lock
	faceplayer
	call_if_unset FLAG_MET_BATTLE_FRONTIER_BREEDER, BattleFrontier_Lounge1_EventScript_BreederIntro
	call_if_set FLAG_MET_BATTLE_FRONTIER_BREEDER, BattleFrontier_Lounge1_EventScript_AlreadyMetBreeder
	setflag FLAG_MET_BATTLE_FRONTIER_BREEDER
	goto BattleFrontier_Lounge1_EventScript_ChooseMonToShowBreeder
	end

BattleFrontier_Lounge1_EventScript_ChooseMonToShowBreeder:: @ 825E792
	special ChoosePartyMon
	waitstate
	compare VAR_0x8004, 255
	goto_if_ne BattleFrontier_Lounge1_EventScript_ShowMonToBreeder
	compare VAR_0x8004, 255
	goto_if_eq BattleFrontier_Lounge1_EventScript_CancelMonSelect
	end

BattleFrontier_Lounge1_EventScript_BreederIntro:: @ 825E7AD
	msgbox BattleFrontier_Lounge1_Text_PokemonBreederIntro, MSGBOX_DEFAULT
	return

BattleFrontier_Lounge1_EventScript_AlreadyMetBreeder:: @ 825E7B6
	msgbox BattleFrontier_Lounge1_Text_LetsLookAtYourPokemon, MSGBOX_DEFAULT
	return

@ BufferVarsForIVRater buffers the following values
@ VAR_0x8004: Sum of the mons IVs
@ VAR_0x8005: IV of the highest IV stat
@ VAR_0x8006, VAR_0x8007, VAR_0x8008, VAR_0x8009, VAR_0x800A, VAR_0x800B: IVs
BattleFrontier_Lounge1_EventScript_ShowMonToBreeder:: @ 825E7BF
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	compare VAR_RESULT, SPECIES_EGG
	goto_if_eq BattleFrontier_Lounge1_EventScript_ShowEggToBreeder
	special BufferVarsForIVRater
	compare VAR_0x8004, 90   @ Average of 15
	goto_if_le BattleFrontier_Lounge1_EventScript_AverageTotalIVs
	compare VAR_0x8004, 120  @ Average of 20
	goto_if_le BattleFrontier_Lounge1_EventScript_AboveAverageTotalIVs
	compare VAR_0x8004, 150  @ Average of 25
	goto_if_le BattleFrontier_Lounge1_EventScript_HighTotalIVs
	compare VAR_0x8004, 151  @ Average of > 25
	goto_if_ge BattleFrontier_Lounge1_EventScript_VeryHighTotalIVs
	end

BattleFrontier_Lounge1_EventScript_ShowEggToBreeder:: @ 825E7FF
	msgbox BattleFrontier_Lounge1_Text_EvenICantTell, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_ChooseMonToShowBreeder
	end

@ Comment on the highest IV stat
BattleFrontier_Lounge1_EventScript_HighestIVStat:: @ 825E80D
	setvar VAR_0x8003, 0
	bufferstring 0, BattleFrontier_Lounge1_Text_BestAspectHP
	compare_var_to_var VAR_0x8005, VAR_0x8006
	call_if_eq BattleFrontier_Lounge1_EventScript_HighestIV
	bufferstring 0, BattleFrontier_Lounge1_Text_BestAspectAtk
	compare_var_to_var VAR_0x8005, VAR_0x8007
	call_if_eq BattleFrontier_Lounge1_EventScript_HighestIV
	bufferstring 0, BattleFrontier_Lounge1_Text_BestAspectDef
	compare_var_to_var VAR_0x8005, VAR_0x8008
	call_if_eq BattleFrontier_Lounge1_EventScript_HighestIV
	bufferstring 0, BattleFrontier_Lounge1_Text_BestAspectSpeed
	compare_var_to_var VAR_0x8005, VAR_0x8009
	call_if_eq BattleFrontier_Lounge1_EventScript_HighestIV
	bufferstring 0, BattleFrontier_Lounge1_Text_BestAspectSpAtk
	compare_var_to_var VAR_0x8005, VAR_0x800A
	call_if_eq BattleFrontier_Lounge1_EventScript_HighestIV
	bufferstring 0, BattleFrontier_Lounge1_Text_BestAspectSpDef
	compare_var_to_var VAR_0x8005, VAR_0x800B
	call_if_eq BattleFrontier_Lounge1_EventScript_HighestIV
	setvar VAR_0x8001, 0
	bufferstring 0, BattleFrontier_Lounge1_Text_BestAspectHP
	compare VAR_0x8006, 0
	call_if_eq BattleFrontier_Lounge1_EventScript_WorstIV
	bufferstring 0, BattleFrontier_Lounge1_Text_BestAspectAtk
	compare VAR_0x8007, 0
	call_if_eq BattleFrontier_Lounge1_EventScript_WorstIV
	bufferstring 0, BattleFrontier_Lounge1_Text_BestAspectDef
	compare VAR_0x8008, 0
	call_if_eq BattleFrontier_Lounge1_EventScript_WorstIV
	bufferstring 0, BattleFrontier_Lounge1_Text_BestAspectSpeed
	compare VAR_0x8009, 0
	call_if_eq BattleFrontier_Lounge1_EventScript_WorstIV
	bufferstring 0, BattleFrontier_Lounge1_Text_BestAspectSpAtk
	compare VAR_0x800A, 0
	call_if_eq BattleFrontier_Lounge1_EventScript_WorstIV
	bufferstring 0, BattleFrontier_Lounge1_Text_BestAspectSpDef
	compare VAR_0x800B, 0
	call_if_eq BattleFrontier_Lounge1_EventScript_WorstIV
	release
	end

@ Comment on the highest IV value
BattleFrontier_Lounge1_EventScript_HighestIVValue::
	copyvar VAR_0x8002, VAR_0x8005
	compare VAR_0x8002, 15
	call_if_le BattleFrontier_Lounge1_EventScript_HighestIVLow
	compare VAR_0x8002, 25
	call_if_le BattleFrontier_Lounge1_EventScript_HighestIVMid
	compare VAR_0x8002, 30
	call_if_le BattleFrontier_Lounge1_EventScript_HighestIVHigh
	compare VAR_0x8002, 31
	call_if_eq BattleFrontier_Lounge1_EventScript_HighestIVMax
	return

BattleFrontier_Lounge1_EventScript_AverageTotalIVs:: @ 825E87F
	msgbox BattleFrontier_Lounge1_Text_AverageAbility, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVStat
	end

BattleFrontier_Lounge1_EventScript_AboveAverageTotalIVs:: @ 825E88D
	msgbox BattleFrontier_Lounge1_Text_BetterThanAverageAbility, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVStat
	end

BattleFrontier_Lounge1_EventScript_HighTotalIVs:: @ 825E89B
	msgbox BattleFrontier_Lounge1_Text_ImpressiveAbility, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVStat
	end

BattleFrontier_Lounge1_EventScript_VeryHighTotalIVs:: @ 825E8A9
	msgbox BattleFrontier_Lounge1_Text_OutstandingAbility, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVStat
	end

BattleFrontier_Lounge1_EventScript_HighestIV:: @ 825E8B7
	compare VAR_0x8003, 1
	call_if_eq BattleFrontier_Lounge1_EventScript_HighestIVAlso
	compare VAR_0x8003, 0
	call_if_eq BattleFrontier_Lounge1_EventScript_HighestIVFirst
	return

BattleFrontier_Lounge1_EventScript_HighestIVFirst:: @ 825E8B7
	msgbox BattleFrontier_Lounge1_Text_BestAspect, MSGBOX_DEFAULT
	setvar VAR_0x8003, 1
	call BattleFrontier_Lounge1_EventScript_HighestIVValue
	return

BattleFrontier_Lounge1_EventScript_HighestIVAlso:: @ 825E8B7
	msgbox BattleFrontier_Lounge1_Text_BestAspectAlso, MSGBOX_DEFAULT
	return

BattleFrontier_Lounge1_EventScript_WorstIV:: @ 825E8B7
	compare VAR_0x8001, 1
	call_if_eq BattleFrontier_Lounge1_EventScript_WorstIVAlso
	compare VAR_0x8001, 0
	call_if_eq BattleFrontier_Lounge1_EventScript_WorstIVFirst
	return

BattleFrontier_Lounge1_EventScript_WorstIVFirst:: @ 825E8B7
	msgbox BattleFrontier_Lounge1_Text_WorstAspect, MSGBOX_DEFAULT
	setvar VAR_0x8001, 1
	return

BattleFrontier_Lounge1_EventScript_WorstIVAlso:: @ 825E8B7
	msgbox BattleFrontier_Lounge1_Text_WorstAspectAlso, MSGBOX_DEFAULT
	return

BattleFrontier_Lounge1_EventScript_HighestIVLow:: @ 825E90B
	msgbox BattleFrontier_Lounge1_Text_StatRelativelyGood, MSGBOX_DEFAULT
	setvar VAR_0x8002, 0xFF
	return

BattleFrontier_Lounge1_EventScript_HighestIVMid:: @ 825E919
	msgbox BattleFrontier_Lounge1_Text_StatImpressive, MSGBOX_DEFAULT
	setvar VAR_0x8002, 0xFF
	return

BattleFrontier_Lounge1_EventScript_HighestIVHigh:: @ 825E927
	msgbox BattleFrontier_Lounge1_Text_StatOutstanding, MSGBOX_DEFAULT
	setvar VAR_0x8002, 0xFF
	return

BattleFrontier_Lounge1_EventScript_HighestIVMax:: @ 825E935
	msgbox BattleFrontier_Lounge1_Text_StatFlawless, MSGBOX_DEFAULT
	setvar VAR_0x8002, 0xFF
	return

BattleFrontier_Lounge1_EventScript_CancelMonSelect:: @ 825E943
	msgbox BattleFrontier_Lounge1_Text_NoTimeForMyAdvice, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge1_EventScript_Boy1:: @ 825E94D
	msgbox BattleFrontier_Lounge1_Text_SaidMyMonIsOutstanding, MSGBOX_NPC
	end

BattleFrontier_Lounge1_EventScript_Boy2:: @ 825E956
	msgbox BattleFrontier_Lounge1_Text_DidntDoAnythingSpecialRaisingIt, MSGBOX_NPC
	end

BattleFrontier_Lounge1_Text_PokemonBreederIntro: @ 825E95F
	.string "For 70 years I have raised POKéMON!\n"
	.string "I am the man they revere as\l"
	.string "the legendary top POKéMON BREEDER!\p"
	.string "If you ever become as seasoned as me,\n"
	.string "you'll see the abilities of POKéMON\l"
	.string "at a glance.\p"
	.string "You're a TRAINER. Doesn't it interest\n"
	.string "you to know your own POKéMON's\l"
	.string "abilities?\p"
	.string "Here!\n"
	.string "Let's have a look at your POKéMON!$"

BattleFrontier_Lounge1_Text_AverageAbility: @ 825EA92
	.string "…Hmm…\p"
	.string "This one, overall, I would describe\n"
	.string "as being of average ability.$"

BattleFrontier_Lounge1_Text_BetterThanAverageAbility: @ 825EAD9
	.string "…Hmm…\p"
	.string "This one, overall, I would describe as\n"
	.string "having better-than-average ability.$"

BattleFrontier_Lounge1_Text_ImpressiveAbility: @ 825EB2A
	.string "…Hmm…\p"
	.string "This one, overall, I would say is\n"
	.string "quite impressive in ability!$"

BattleFrontier_Lounge1_Text_OutstandingAbility: @ 825EB6F
	.string "…Hmm…\p"
	.string "This one, overall, I would say is\n"
	.string "wonderfully outstanding in ability!$"

BattleFrontier_Lounge1_Text_BestAspect:
	.string "Incidentally, the best aspect of it,\n"
	.string "I would say, is its {STR_VAR_1}…$"

BattleFrontier_Lounge1_Text_BestAspectAlso:
	.string "And its {STR_VAR_1} is equally good.$"

BattleFrontier_Lounge1_Text_WorstAspect:
	.string "However, its {STR_VAR_1} is\n"
	.string "absolutely terrible.$"

BattleFrontier_Lounge1_Text_WorstAspectAlso:
	.string "And its {STR_VAR_1} is bad aswell.$"

BattleFrontier_Lounge1_Text_BestAspectHP:
	.string "HP$"

BattleFrontier_Lounge1_Text_BestAspectAtk:
	.string "ATTACK$"

BattleFrontier_Lounge1_Text_BestAspectDef:
	.string "DEFENSE$"

BattleFrontier_Lounge1_Text_BestAspectSpAtk:
	.string "SPECIAL ATTACK$"

BattleFrontier_Lounge1_Text_BestAspectSpDef:
	.string "SPECIAL DEFENSE$"

BattleFrontier_Lounge1_Text_BestAspectSpeed:
	.string "SPEED$"

BattleFrontier_Lounge1_Text_StatRelativelyGood: @ 825ED4E
	.string "That stat is relatively good.\n"
	.string "…Hm… That's how I call it.$"

BattleFrontier_Lounge1_Text_StatImpressive: @ 825ED87
	.string "That stat is quite impressive.\n"
	.string "…Hm… That's how I call it.$"

BattleFrontier_Lounge1_Text_StatOutstanding: @ 825EDC1
	.string "That stat is outstanding!\n"
	.string "…Hm… That's how I call it.$"

BattleFrontier_Lounge1_Text_StatFlawless: @ 825EDF6
	.string "It's flawless! A thing of perfection!\n"
	.string "…Hm… That's how I call it.$"

BattleFrontier_Lounge1_Text_NoTimeForMyAdvice: @ 825EE37
	.string "What?\n"
	.string "You have no time for my advice?\p"
	.string "You should always be eager to learn\n"
	.string "from the experiences of your elders!$"

@ Unused
BattleFrontier_Lounge1_Text_HaveBusinessNeedsTending: @ 825EEA6
	.string "Yes, what is it now?\p"
	.string "I have business that needs tending!\n"
	.string "Save it for next time!$"

BattleFrontier_Lounge1_Text_LetsLookAtYourPokemon: @ 825EEF6
	.string "Ah, youngster! Do your POKéMON's\n"
	.string "abilities intrigue you?\p"
	.string "Here, here!\n"
	.string "Let's have a look at your POKéMON!$"

BattleFrontier_Lounge1_Text_EvenICantTell: @ 825EF5E
	.string "An expert I am, but even I can't tell\n"
	.string "anything about an unhatched POKéMON!\p"
	.string "Show me a POKéMON!\n"
	.string "A POKéMON is what I need to see!$"

BattleFrontier_Lounge1_Text_SaidMyMonIsOutstanding: @ 825EFDD
	.string "He said my POKéMON is outstanding!\n"
	.string "I'm glad I raised it carefully!$"

BattleFrontier_Lounge1_Text_DidntDoAnythingSpecialRaisingIt: @ 825F020
	.string "He said my POKéMON is outstanding!\n"
	.string "But I didn't do anything special\l"
	.string "raising it…$"

