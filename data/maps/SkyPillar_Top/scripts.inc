SkyPillar_Top_MapScripts:: @ 82396B8
	map_script MAP_SCRIPT_ON_RESUME, SkyPillar_Top_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, SkyPillar_Top_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, SkyPillar_Top_OnWarp
	.byte 0

SkyPillar_Top_OnResume: @ 82396C8
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, SkyPillar_Top_EventScript_TryRemoveRayquaza
	end

SkyPillar_Top_EventScript_TryRemoveRayquaza:: @ 82396D2
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_ne Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

SkyPillar_Top_OnTransition: @ 82396E6
	compare VAR_SKY_PILLAR_STATE, 2
	call_if_lt SkyPillar_Top_EventScript_SetCleanLayout
	compare VAR_SKY_PILLAR_STATE, 2
	call_if_ge SkyPillar_Top_EventScript_TryShowRayquaza
	end

SkyPillar_Top_EventScript_SetCleanLayout:: @ 82396FD
	setmaplayoutindex LAYOUT_SKY_PILLAR_TOP_CLEAN
	setobjectmovementtype 1, MOVEMENT_TYPE_FACE_DOWN
	return

SkyPillar_Top_EventScript_TryShowRayquaza:: @ 8239705
	call_if_unset FLAG_DEFEATED_RAYQUAZA, SkyPillar_Top_EventScript_ShowRayquaza
	return

SkyPillar_Top_EventScript_ShowRayquaza:: @ 823970F
	clearflag FLAG_HIDE_RAYQUAZA_SKY_TOWER_SUMMIT
	clearflag FLAG_HIDE_ZINNIA_SKY_TOWER_SUMMIT
	return

SkyPillar_Top_OnWarp: @ 8239713
	map_script_2 VAR_SKY_PILLAR_STATE, 0, SkyPillar_Top_EventScript_RayquazaFaceDown
	.2byte 0

SkyPillar_Top_EventScript_RayquazaFaceDown:: @ 823971D
	turnobject 1, DIR_SOUTH
	end

SkyPillar_Top_EventScript_Rayquaza:: @ 8239722
	lockall
	waitse
	playmoncry SPECIES_RAYQUAZA, 2
	delay 40
	waitmoncry
	setvar VAR_NUM_MAXED_IVS, 4
	setwildbattle SPECIES_RAYQUAZA, 70, ITEM_NONE
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq SkyPillar_Top_EventScript_DefeatedRayquaza
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq SkyPillar_Top_EventScript_CaughtRayquaza
	compare VAR_RESULT, B_OUTCOME_RAN
	goto_if_eq SkyPillar_Top_EventScript_RanFromRayquaza
	compare VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED
	goto_if_eq SkyPillar_Top_EventScript_RanFromRayquaza
	setflag FLAG_DEFEATED_RAYQUAZA
	releaseall
	end

SkyPillar_Top_EventScript_DefeatedRayquaza:: @ 8239768
	setflag FLAG_DEFEATED_RAYQUAZA
	goto SkyPillar_Top_EventScript_DefeatedRayquaza2
	end

SkyPillar_Top_EventScript_CaughtRayquaza::
	setflag FLAG_DEFEATED_RAYQUAZA
	setflag FLAG_CAUGHT_RAYQUAZA
	goto SkyPillar_Top_EventScript_DefeatedRayquaza2
	end

SkyPillar_Top_EventScript_RanFromRayquaza:: @ 8239771
	setvar VAR_0x8004, SPECIES_RAYQUAZA
	goto SkyPillar_Top_EventScript_RanFromRayquaza2
	end

SkyPillar_Top_EventScript_DefeatedRayquaza2:: @ 823977C
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	releaseall
	end

SkyPillar_Top_EventScript_RanFromRayquaza2:: @ 8239785
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	bufferspeciesname 0, VAR_0x8004
	msgbox gText_LegendaryFlewAway, MSGBOX_DEFAULT
	releaseall
	end

SkyPillar_Top_EventScript_AwakenRayquaza:: @ 823979A
	lockall
	fadeoutbgm 1
	applymovement EVENT_OBJ_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	special SpawnCameraObject
	applymovement EVENT_OBJ_ID_CAMERA, SkyPillar_Top_Movement_CameraPanUp
	waitmovement 0
	special RemoveCameraObject
	applymovement 1, SkyPillar_Top_Movement_RayquazaStir
	waitmovement 0
	waitse
	playmoncry SPECIES_RAYQUAZA, 2
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 3  @ shake delay
	special ShakeCamera
	waitstate
	waitse
	playmoncry SPECIES_RAYQUAZA, 2
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 2  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	waitmoncry
	applymovement 1, SkyPillar_Top_Movement_RayquazaFlyOff
	waitmovement 0
	removeobject 1
	msgbox SkyPillar_Top_Text_RayquazaFlewOff, MSGBOX_DEFAULT
	closemessage
	delay 20
	fadeinbgm 1
	special SpawnCameraObject
	applymovement EVENT_OBJ_ID_CAMERA, SkyPillar_Top_Movement_CameraPanDown
	waitmovement 0
	special RemoveCameraObject
	setvar VAR_SOOTOPOLIS_CITY_STATE, 5
	setvar VAR_SKY_PILLAR_STATE, 1
	setvar VAR_SKY_PILLAR_RAQUAZA_CRY_DONE, 1
	releaseall
	end

SkyPillar_Top_EventScript_Zinnia::
	goto_if_set FLAG_CAUGHT_RAYQUAZA, SkyPillar_Top_EventScript_ZinniaRayquazaCaught
	goto_if_set FLAG_DEFEATED_RAYQUAZA, SkyPillar_Top_EventScript_ZinniaRayquazaDefeated
	lockall
	faceplayer
	msgbox SkyPillar_Top_Text_ZinniaNotImportant, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

SkyPillar_Top_EventScript_ZinniaRayquazaDefeated::
	lockall
	faceplayer
	msgbox SkyPillar_Top_Text_ZinniaRayquazaDefeated, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

SkyPillar_Top_EventScript_ZinniaRayquazaCaught::
	lockall
	faceplayer
	msgbox SkyPillar_Top_Text_ZinniaRayquazaCaught, MSGBOX_DEFAULT
	checkpartymon SPECIES_RAYQUAZA
	compare VAR_RESULT, PARTY_SIZE
	call_if_ne SkyPillar_Top_EventScript_ZinniaAskTeachRayquaza
	msgbox SkyPillar_Top_Text_ZinniaTakeCare, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

SkyPillar_Top_EventScript_ZinniaAskTeachRayquaza::
	msgbox SkyPillar_Top_Text_ZinniaAskTeachRayquaza, MSGBOX_YESNO
	compare VAR_RESULT, YES
	call_if_eq SkyPillar_Top_EventScript_ZinniaTeachRayquaza
	call_if_ne SkyPillar_Top_EventScript_ZinniaTeachRayquazaDecline
	return

SkyPillar_Top_EventScript_ZinniaTeachRayquaza::
	setvar VAR_0x8005, TUTOR_MOVE_DRAGON_ASCEND
	call MoveTutor_EventScript_OpenPartyMenu
	return

SkyPillar_Top_EventScript_ZinniaTeachRayquazaDecline::
	msgbox SkyPillar_Top_Text_ZinniaTeachRayquazaDecline, MSGBOX_DEFAULT
	return

SkyPillar_Top_Text_ZinniaNotImportant:
	.string "Me?\p"
	.string "Who I am is not important…\p"
	.string "I'm just here to pay my respects\n"
	.string "to RAYQUAZA.\p"
	.string "It saved HOENN after all…$"

SkyPillar_Top_Text_ZinniaRayquazaDefeated:
	.string "You…\p"
	.string "You actually defeated RAYQUAZA…\p"
	.string "I… I have no words…$"

SkyPillar_Top_Text_ZinniaRayquazaCaught:
	.string "You…\p"
	.string "You actually caught RAYQUAZA…\p"
	.string "It… It must have chosen you…\p"
	.string "I hope you know what an incredible\n"
	.string "honor this is…$"

SkyPillar_Top_Text_ZinniaAskTeachRayquaza:
	.string "If you want, I can teach it a\n"
	.string "special move, one only it can learn…$"

SkyPillar_Top_Text_ZinniaTeachRayquazaDecline:
	.string "Oh… I see…$"

SkyPillar_Top_Text_ZinniaTakeCare:
	.string "Please…\n"
	.string "Take care…$"

SkyPillar_Top_Movement_RayquazaStir: @ 823983A
	delay_16
	walk_in_place_fast_left
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_left
	delay_16
	walk_in_place_right
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	step_end

SkyPillar_Top_Movement_RayquazaFlyOff: @ 823984B
	delay_16
	walk_in_place_down
	delay_8
	walk_in_place_right
	delay_8
	walk_fastest_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	step_end

SkyPillar_Top_Movement_CameraPanUp: @ 8239858
	walk_slow_up
	walk_slow_up
	walk_slow_up
	step_end

SkyPillar_Top_Movement_CameraPanDown: @ 823985C
	walk_slow_down
	walk_slow_down
	walk_slow_down
	step_end

SkyPillar_Top_Text_RayquazaFlewOff: @ 8239860
	.string "The awakened RAYQUAZA flew off…$"
