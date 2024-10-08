Route103_MapScripts:: @ 81EC38E
	map_script MAP_SCRIPT_ON_TRANSITION, Route103_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Route103_OnLoad
	.byte 0

Route103_OnTransition: @ 81EC399
	call Common_EventScript_SetupRivalGfxId
	call ProfBirch_EventScript_UpdateLocation
	end

Route103_OnLoad: @ 81EC3A4
	call_if_set FLAG_SYS_GAME_CLEAR, Route103_EventScript_OpenAlteringCave_ShowRival
	end

Route103_EventScript_OpenAlteringCave_ShowRival:: @ 81EC3AE
	setmetatile 45, 5, METATILE_General_CaveEntrance_Top, 1
	setmetatile 45, 6, METATILE_General_CaveEntrance_Bottom, 0
	clearflag FLAG_HIDE_ROUTE_103_RIVAL
	return

Route103_EventScript_Rival:: @ 81EC3C1
	lockall
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq Route103_EventScript_RivalMay
	compare VAR_RESULT, FEMALE
	goto_if_eq Route103_EventScript_RivalBrendan
	end

Route103_EventScript_RivalMay:: @ 81EC3DA
	goto_if_set FLAG_SYS_GAME_CLEAR, Route103_EventScript_RivalMayPostGame
	msgbox Route103_Text_MayRoute103Pokemon, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_GIRL_SUP, 1
	applymovement 2, Common_Movement_FacePlayer
	waitmovement 0
	applymovement 2, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 2, Common_Movement_Delay48
	waitmovement 0
	msgbox Route103_Text_MayLetsBattle, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, Route103_EventScript_StartMayBattleTreecko
	case 1, Route103_EventScript_StartMayBattleTorchic
	case 2, Route103_EventScript_StartMayBattleMudkip
	end

Route103_EventScript_RivalBrendan:: @ 81EC434
	goto_if_set FLAG_SYS_GAME_CLEAR, Route103_EventScript_RivalBrendanPostGame
	msgbox Route103_Text_BrendanRoute103Pokemon, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_BOY_SUP, 1
	applymovement 2, Common_Movement_FacePlayer
	waitmovement 0
	applymovement 2, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 2, Common_Movement_Delay48
	waitmovement 0
	msgbox Route103_Text_BrendanLetsBattle, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, Route103_EventScript_StartBrendanBattleTreecko
	case 1, Route103_EventScript_StartBrendanBattleTorchic
	case 2, Route103_EventScript_StartBrendanBattleMudkip
	end

Route103_EventScript_RivalMayPostGame::
	goto_if_set FLAG_DAILY_RIVAL_BATTLE, Route103_EventScript_RivalMayPostGameAfterBattle
	faceplayer
	goto_if_set FLAG_TEMP_1, Route103_EventScript_RivalMayPostGameReconsider
	msgbox Route103_Text_MayRoute103PostGame, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route103_EventScript_RivalMayPostGameBattle
	setflag FLAG_TEMP_1
	msgbox Route103_Text_MayRoute103PostGameNoBattle, MSGBOX_NPC
	releaseall
	end

Route103_EventScript_RivalMayPostGameReconsider::
	msgbox Route103_Text_MayRoute103PostGameReconsider, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route103_EventScript_RivalMayPostGameBattle
	msgbox Route103_Text_MayRoute103PostGameNoBattle, MSGBOX_NPC
	releaseall
	end

Route103_EventScript_RivalMayPostGameBattle::
	setflag FLAG_DAILY_RIVAL_BATTLE
	msgbox Route103_Text_MayRoute103PostGameBattle, MSGBOX_NPC
	switch VAR_STARTER_MON
	case 0, Route103_EventScript_StartMayBattleTreeckoPostGame
	case 1, Route103_EventScript_StartMayBattleTorchicPostGame
	case 2, Route103_EventScript_StartMayBattleMudkipPostGame
	end

Route103_EventScript_StartMayBattleTreeckoPostGame::
	trainerbattle_no_intro TRAINER_MAY_POSTGAME_TREECKO, Route103_Text_MayRoute103PostGameDefeated
	goto Route103_EventScript_RivalMayPostGameAfterBattle
	end

Route103_EventScript_StartMayBattleTorchicPostGame::
	trainerbattle_no_intro TRAINER_MAY_POSTGAME_TORCHIC, Route103_Text_MayRoute103PostGameDefeated
	goto Route103_EventScript_RivalMayPostGameAfterBattle
	end

Route103_EventScript_StartMayBattleMudkipPostGame::
	trainerbattle_no_intro TRAINER_MAY_POSTGAME_MUDKIP, Route103_Text_MayRoute103PostGameDefeated
	goto Route103_EventScript_RivalMayPostGameAfterBattle
	end

Route103_EventScript_RivalMayPostGameAfterBattle::
	msgbox Route103_Text_MayRoute103PostGameAfterBattle, MSGBOX_NPC
	releaseall
	end

Route103_EventScript_RivalBrendanPostGame::
	goto_if_set FLAG_DAILY_RIVAL_BATTLE, Route103_EventScript_RivalBrendanPostGameAfterBattle
	faceplayer
	goto_if_set FLAG_TEMP_1, Route103_EventScript_RivalBrendanPostGameReconsider
	msgbox Route103_Text_BrendanRoute103PostGame, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route103_EventScript_RivalBrendanPostGameBattle
	setflag FLAG_TEMP_1
	msgbox Route103_Text_BrendanRoute103PostGameNoBattle, MSGBOX_NPC
	releaseall
	end

Route103_EventScript_RivalBrendanPostGameReconsider::
	msgbox Route103_Text_BrendanRoute103PostGameReconsider, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route103_EventScript_RivalBrendanPostGameBattle
	msgbox Route103_Text_BrendanRoute103PostGameNoBattle, MSGBOX_NPC
	releaseall
	end

Route103_EventScript_RivalBrendanPostGameBattle::
	setflag FLAG_DAILY_RIVAL_BATTLE
	msgbox Route103_Text_BrendanRoute103PostGameBattle, MSGBOX_NPC
	switch VAR_STARTER_MON
	case 0, Route103_EventScript_StartBrendanBattleTreeckoPostGame
	case 1, Route103_EventScript_StartBrendanBattleTorchicPostGame
	case 2, Route103_EventScript_StartBrendanBattleMudkipPostGame
	end

Route103_EventScript_StartBrendanBattleTreeckoPostGame::
	trainerbattle_no_intro TRAINER_BRENDAN_POSTGAME_TREECKO, Route103_Text_BrendanRoute103PostGameDefeated
	goto Route103_EventScript_RivalBrendanPostGameAfterBattle
	end

Route103_EventScript_StartBrendanBattleTorchicPostGame::
	trainerbattle_no_intro TRAINER_BRENDAN_POSTGAME_TORCHIC, Route103_Text_BrendanRoute103PostGameDefeated
	goto Route103_EventScript_RivalBrendanPostGameAfterBattle
	end

Route103_EventScript_StartBrendanBattleMudkipPostGame::
	trainerbattle_no_intro TRAINER_BRENDAN_POSTGAME_MUDKIP, Route103_Text_BrendanRoute103PostGameDefeated
	goto Route103_EventScript_RivalBrendanPostGameAfterBattle
	end

Route103_EventScript_RivalBrendanPostGameAfterBattle::
	msgbox Route103_Text_BrendanRoute103PostGameAfterBattle, MSGBOX_NPC
	releaseall
	end

Route103_EventScript_StartMayBattleTreecko:: @ 81EC48E
	trainerbattle_no_intro TRAINER_MAY_ROUTE_103_TREECKO, Route103_Text_MayDefeated
	goto Route103_EventScript_AfterMayBattle
	end

Route103_EventScript_StartMayBattleTorchic:: @ 81EC49E
	trainerbattle_no_intro TRAINER_MAY_ROUTE_103_TORCHIC, Route103_Text_MayDefeated
	goto Route103_EventScript_AfterMayBattle
	end

Route103_EventScript_StartMayBattleMudkip:: @ 81EC4AE
	trainerbattle_no_intro TRAINER_MAY_ROUTE_103_MUDKIP, Route103_Text_MayDefeated
	goto Route103_EventScript_AfterMayBattle
	end

Route103_EventScript_StartBrendanBattleTreecko:: @ 81EC4BE
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_103_TREECKO, Route103_Text_BrendanDefeated
	goto Route103_EventScript_AfterBrendanBattle
	end

Route103_EventScript_StartBrendanBattleTorchic:: @ 81EC4CE
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_103_TORCHIC, Route103_Text_BrendanDefeated
	goto Route103_EventScript_AfterBrendanBattle
	end

Route103_EventScript_StartBrendanBattleMudkip:: @ 81EC4DE
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_103_MUDKIP, Route103_Text_BrendanDefeated
	goto Route103_EventScript_AfterBrendanBattle
	end

Route103_EventScript_AfterMayBattle:: @ 81EC4EE
	msgbox Route103_Text_MayTimeToHeadBack, MSGBOX_DEFAULT
	goto Route103_EventScript_RivalExit
	end

Route103_EventScript_AfterBrendanBattle:: @ 81EC4FC
	msgbox Route103_Text_BrendanTimeToHeadBack, MSGBOX_DEFAULT
	goto Route103_EventScript_RivalExit
	end

Route103_EventScript_RivalExit:: @ 81EC50A
	closemessage
	switch VAR_FACING
	case DIR_SOUTH, Route103_EventScript_RivalExitFacingSouth
	case DIR_NORTH, Route103_EventScript_RivalExitFacingNorth
	case DIR_WEST, Route103_EventScript_RivalExitFacingEastOrWest
	case DIR_EAST, Route103_EventScript_RivalExitFacingEastOrWest
	end

Route103_EventScript_RivalExitFacingNorth:: @ 81EC53D
	applymovement EVENT_OBJ_ID_PLAYER, Route103_Movement_WatchRivalExitFacingNorth
	applymovement 2, Route103_Movement_RivalExitFacingNorth1
	waitmovement 0
	playse SE_DANSA
	applymovement 2, Route103_EventScript_RivalExitFacingNorth2
	waitmovement 0
	goto Route103_EventScript_RivalEnd
	end

Route103_EventScript_RivalExitFacingEastOrWest:: @ 81EC561
	applymovement EVENT_OBJ_ID_PLAYER, Route103_Movement_WatchRivalExitFacingEastOrWest
	applymovement 2, Route103_Movement_RivalExit1
	waitmovement 0
	playse SE_DANSA
	applymovement 2, Route103_Movement_RivalExit2
	waitmovement 0
	goto Route103_EventScript_RivalEnd
	end

Route103_EventScript_RivalExitFacingSouth:: @ 81EC585
	applymovement 2, Route103_Movement_RivalExit1
	waitmovement 0
	playse SE_DANSA
	applymovement 2, Route103_Movement_RivalExit2
	waitmovement 0
	goto Route103_EventScript_RivalEnd
	end

Route103_EventScript_RivalEnd:: @ 81EC5A2
	removeobject 2
	setvar VAR_BIRCH_LAB_STATE, 4
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_RIVAL
	setflag FLAG_DEFEATED_RIVAL_ROUTE103
	setvar VAR_OLDALE_RIVAL_STATE, 1
	clearflag FLAG_HIDE_OLDALE_TOWN_RIVAL
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

Route103_Movement_RivalExitFacingNorth1: @ 81EC5BE
	walk_left
	walk_down
	step_end

Route103_EventScript_RivalExitFacingNorth2: @ 81EC5C1
	jump_2_down
	delay_16
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Route103_Movement_WatchRivalExitFacingNorth: @ 81EC5C8
	delay_16
	delay_4
	walk_in_place_fastest_left
	delay_16
	walk_in_place_fastest_down
	step_end

Route103_Movement_RivalExit1: @ 81EC5CE
	walk_down
	step_end

Route103_Movement_RivalExit2: @ 81EC5D0
	jump_2_down
	delay_16
	walk_down
	walk_down
	walk_down
	step_end

Route103_Movement_WatchRivalExitFacingEastOrWest: @ 81EC5D6
	delay_16
	walk_in_place_fastest_down
	step_end

Route103_EventScript_Boy:: @ 81EC5D9
	msgbox Route103_Text_ShouldHaveBroughtPotion, MSGBOX_NPC
	end

Route103_EventScript_Man:: @ 81EC5E2
	msgbox Route103_Text_ShortcutToOldale, MSGBOX_NPC
	end

Route103_EventScript_RouteSign:: @ 81EC5EB
	msgbox Route103_Text_RouteSign, MSGBOX_SIGN
	end

Route103_EventScript_Daisy:: @ 81EC5F4
	trainerbattle_single TRAINER_DAISY, Route103_Text_DaisyIntro, Route103_Text_DaisyDefeated
	msgbox Route103_Text_DaisyPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Amy:: @ 81EC60B
	trainerbattle_double TRAINER_AMY_AND_LIV_1, Route103_Text_AmyIntro, Route103_Text_AmyDefeated, Route103_Text_AmyNotEnoughPokemon, Route102_EventScript_AmyRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route102_EventScript_AmyRematch
	msgbox Route103_Text_AmyPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_EventScript_AmyRegisterMatchCallAfterBattle:: @ 81EC63A
	msgbox Route103_Text_AmyLivRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_AMY_AND_LIV_1
	release
	end

Route102_EventScript_AmyRematch:: @ 81EC653
	trainerbattle_rematch_double TRAINER_AMY_AND_LIV_1, Route103_Text_AmyRematchIntro, Route103_Text_AmyRematchDefeated, Route103_Text_AmyRematchNotEnoughPokemon
	msgbox Route103_Text_AmyRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Liv:: @ 81EC66E
	trainerbattle_double TRAINER_AMY_AND_LIV_1, Route103_Text_LivIntro, Route103_Text_LivDefeated, Route103_Text_LivNotEnoughPokemon, Route102_EventScript_LivRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route102_EventScript_LivRematch
	msgbox Route103_Text_LivPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_EventScript_LivRegisterMatchCallAfterBattle:: @ 81EC69D
	msgbox Route103_Text_AmyLivRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_AMY_AND_LIV_1
	release
	end

Route102_EventScript_LivRematch:: @ 81EC6B6
	trainerbattle_rematch_double TRAINER_AMY_AND_LIV_1, Route103_Text_LivRematchIntro, Route103_Text_LivRematchDefeated, Route103_Text_LivRematchNotEnoughPokemon
	msgbox Route103_Text_LivRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Andrew:: @ 81EC6D1
	trainerbattle_single TRAINER_ANDREW, Route103_Text_AndrewIntro, Route103_Text_AndrewDefeated
	msgbox Route103_Text_AndrewPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Miguel:: @ 81EC6E8
	trainerbattle_single TRAINER_MIGUEL_1, Route103_Text_MiguelIntro, Route103_Text_MiguelDefeated, Route102_EventScript_MiguelRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route103_EventScript_MiguelRematch
	msgbox Route103_Text_MiguelPostBattle, MSGBOX_DEFAULT
	release
	end

Route102_EventScript_MiguelRegisterMatchCallAfterBattle:: @ 81EC714
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route103_Text_MiguelRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_MIGUEL_1
	release
	end

Route103_EventScript_MiguelRematch:: @ 81EC733
	trainerbattle_rematch TRAINER_MIGUEL_1, Route103_Text_MiguelRematchIntro, Route103_Text_MiguelRematchDefeated
	msgbox Route103_Text_MiguelRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Marcos:: @ 81EC74A
	trainerbattle_single TRAINER_MARCOS, Route103_Text_MarcosIntro, Route103_Text_MarcosDefeated
	msgbox Route103_Text_MarcosPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Rhett:: @ 81EC761
	trainerbattle_single TRAINER_RHETT, Route103_Text_RhettIntro, Route103_Text_RhettDefeated
	msgbox Route103_Text_RhettPostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Pete:: @ 81EC778
	trainerbattle_single TRAINER_PETE, Route103_Text_PeteIntro, Route103_Text_PeteDefeated
	msgbox Route103_Text_PetePostBattle, MSGBOX_AUTOCLOSE
	end

Route103_EventScript_Isabelle:: @ 81EC78F
	trainerbattle_single TRAINER_ISABELLE, Route103_Text_IsabelleIntro, Route103_Text_IsabelleDefeated
	msgbox Route103_Text_IsabellePostBattle, MSGBOX_AUTOCLOSE
	end

Route103_Text_MayRoute103Pokemon: @ 81EC7A6
	.string "MAY: Let's see… The POKéMON found\n"
	.string "on ROUTE 103 include…$"

Route103_Text_MayLetsBattle: @ 81EC7DE
	.string "Oh, hi, {PLAYER}{KUN}!\p"
	.string "…Oh, I see, my dad gave you\n"
	.string "a POKéMON as a gift.\p"
	.string "Since we're here, let's have a quick\n"
	.string "battle!\p"
	.string "I'll give you a taste of what being\n"
	.string "a TRAINER is like.$"

Route103_Text_MayDefeated: @ 81EC881
	.string "Wow! That's great!\n"
	.string "{PLAYER}{KUN}, you're pretty good!$"

Route103_Text_MayTimeToHeadBack: @ 81EC8AE
	.string "MAY: I think I know why my dad has\n"
	.string "an eye out for you now.\p"
	.string "I mean, you just got that POKéMON,\n"
	.string "but it already likes you.\p"
	.string "You might be able to befriend any\n"
	.string "kind of POKéMON easily.\p"
	.string "Well, it's time to head back to\n"
	.string "the LAB.$"

Route103_Text_BrendanRoute103Pokemon: @ 81EC989
	.string "BRENDAN: Okay, so it's this one and\n"
	.string "that one that live on ROUTE 103…$"

Route103_Text_BrendanLetsBattle: @ 81EC9CE
	.string "Hey, it's {PLAYER}!\p"
	.string "…Oh, yeah, Dad gave you a POKéMON.\p"
	.string "Since we're here, how about a little\n"
	.string "battle?\p"
	.string "I'll teach you what being a TRAINER's\n"
	.string "about!$"

Route103_Text_BrendanDefeated: @ 81ECA59
	.string "Huh, {PLAYER}, you're not too shabby.$"

Route103_Text_BrendanTimeToHeadBack: @ 81ECA79
	.string "BRENDAN: I think I get it.\n"
	.string "I think I know why my dad has his eye\l"
	.string "out for you now.\p"
	.string "Look, your POKéMON already likes you,\n"
	.string "even though you just got it.\p"
	.string "{PLAYER}, I get the feeling that you\n"
	.string "could befriend any POKéMON with ease.\p"
	.string "We should head back to the LAB.$"

Route103_Text_ShouldHaveBroughtPotion: @ 81ECB73
	.string "My POKéMON is staggeringly tired…\n"
	.string "I should have brought a POTION…$"

Route103_Text_ShortcutToOldale: @ 81ECBB5
	.string "If you cross the sea from here,\n"
	.string "it'll be a shortcut to OLDALE TOWN.\p"
	.string "Fufufu, that's useful, isn't it?$"

Route103_Text_RouteSign: @ 81ECC1A
	.string "ROUTE 103\n"
	.string "{DOWN_ARROW} OLDALE TOWN$"

Route103_Text_BrendanRoute103PostGame:
	.string "BRENDAN: Oh hey {PLAYER}!\p"
	.string "Funny meeting you here again!\p"
	.string "A lot of things have happened\n"
	.string "since we first met…\p"
	.string "Say…\p"
	.string "Since you're here,\n"
	.string "do you want to have a POKéMON battle?$"

Route103_Text_BrendanRoute103PostGameReconsider:
	.string "BRENDAN: Changed your mind?\p"
	.string "Do you want to have a POKéMON battle?$"

Route103_Text_BrendanRoute103PostGameBattle:
	.string "That's what I like to hear!\p"
	.string "Give it your best!$"

Route103_Text_BrendanRoute103PostGameNoBattle:
	.string "No?\p"
	.string "You didn't lose your spirit did you?$"

Route103_Text_BrendanRoute103PostGameDefeated:
	.string "I see you're still going strong!$"

Route103_Text_BrendanRoute103PostGameAfterBattle:
	.string "That was fun!\p"
	.string "I forgot how strong you are!\p"
	.string "Let's do this again sometime!$"

Route103_Text_MayRoute103PostGame:
	.string "MAY: Oh hey {PLAYER}!\p"
	.string "This is the place where we had\n"
	.string "our first battle, remember?\p"
	.string "Eheheh…\p"
	.string "It's silly but…\p"
	.string "It makes me kind of nostalgic…\p"
	.string "Uhm, I was wondering…\p"
	.string "Would you have another\n"
	.string "POKéMON battle with me?$"

Route103_Text_MayRoute103PostGameReconsider:
	.string "MAY: Ah…\p"
	.string "Did you change your mind?\p"
	.string "Do you want to have a POKéMON battle?$"

Route103_Text_MayRoute103PostGameBattle:
	.string "Thanks, I'll give it my best!$"

Route103_Text_MayRoute103PostGameNoBattle:
	.string "Oh…\p"
	.string "That's fine…$"

Route103_Text_MayRoute103PostGameDefeated:
	.string "You're as strong as ever {PLAYER}!$"

Route103_Text_MayRoute103PostGameAfterBattle:
	.string "That was great!\p"
	.string "You just keep getting stronger!\p"
	.string "Let's do this again sometime!$"
