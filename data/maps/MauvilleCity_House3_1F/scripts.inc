MauvilleCity_House3_1F_MapScripts::
	.byte 0

MauvilleCity_House3_1F_EventScript_Hoppip::
	lock
	faceplayer
	goto_if_set FLAG_DAILY_TRAINER_HOPPIP_BATTLE, MauvilleCity_House3_1F_EventScript_HoppipBattleDone
	goto_if_set FLAG_TEMP_1, MauvilleCity_House3_1F_EventScript_HoppipFirstBattleReconsidered
	goto_if_set FLAG_BATTLED_TRAINER_HOPPIP, MauvilleCity_House3_1F_EventScript_HoppipRematchBattle
	msgbox MauvilleCity_House3_1F_Text_CameHereLookingForStrongTrainers, MSGBOX_DEFAULT
	goto_if_set FLAG_IS_CHAMPION, MauvilleCity_House3_1F_EventScript_HoppipFirstBattle
	release
	end

MauvilleCity_House3_1F_EventScript_HoppipFirstBattle::
	setflag FLAG_TEMP_1
	msgbox MauvilleCity_House3_1F_Text_YouLookStrong, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq MauvilleCity_House3_1F_EventScript_HoppipBattle
MauvilleCity_House3_1F_EventScript_HoppipDeclineBattle::
	msgbox MauvilleCity_House3_1F_Text_ComeBackWhenYouReconsider, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House3_1F_EventScript_HoppipRematchBattle::
	setflag FLAG_TEMP_1
	msgbox MauvilleCity_House3_1F_Text_WantARematch, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq MauvilleCity_House3_1F_EventScript_HoppipBattle
	goto MauvilleCity_House3_1F_EventScript_HoppipDeclineBattle
	end

MauvilleCity_House3_1F_EventScript_HoppipFirstBattleReconsidered::
	msgbox MauvilleCity_House3_1F_Text_HaveYouReconsidered, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq MauvilleCity_House3_1F_EventScript_HoppipBattle
	goto MauvilleCity_House3_1F_EventScript_HoppipDeclineBattle
	end

MauvilleCity_House3_1F_EventScript_HoppipBattle::
	special HasEnoughMonsForDoubleBattle
	compare VAR_RESULT, PLAYER_HAS_TWO_USABLE_MONS
	goto_if_ne MauvilleCity_House3_1F_EventScript_NotEnoughMonsForDoubleBattle
	msgbox MauvilleCity_House3_1F_Text_LetsBattle, MSGBOX_DEFAULT
	clearflag FLAG_TEMP_1
	setflag FLAG_BATTLED_TRAINER_HOPPIP
	setflag FLAG_DAILY_TRAINER_HOPPIP_BATTLE
	trainerbattle_no_intro TRAINER_HOPPIP, MauvilleCity_House3_1F_Text_HoppipDefeat
MauvilleCity_House3_1F_EventScript_HoppipBattleDone::
	msgbox MauvilleCity_House3_1F_Text_GoodBattle, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House3_1F_EventScript_NotEnoughMonsForDoubleBattle::
	msgbox MauvilleCity_House3_1F_Text_NeedTwoMons, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House3_1F_Text_CameHereLookingForStrongTrainers:
	.string "I moved to HOENN hoping to find some\n"
	.string "strong TRAINERS for DOUBLE BATTLES.\p"
	.string "I haven't had much success so far…$"

MauvilleCity_House3_1F_Text_YouLookStrong:
	.string "Hmm, you look like a capable TRAINER…\p"
	.string "What's your name?\p"
	.string "{PLAYER}, huh?\p"
	.string "Do you want to have a DOUBLE BATTLE?$"

MauvilleCity_House3_1F_Text_WantARematch:
	.string "Oh hi {PLAYER}!\n"
	.string "Are your POKéMON ready for a rematch?$"

MauvilleCity_House3_1F_Text_LetsBattle:
	.string "Great!\p"
	.string "Let's get right to it then!$"

MauvilleCity_House3_1F_Text_ComeBackWhenYouReconsider:
	.string "Oh, what a shame…\p"
	.string "I'll be here in case you reconsider!$"

MauvilleCity_House3_1F_Text_HaveYouReconsidered:
	.string "Have you reconsidered?\n"
	.string "Do you want to have a DOUBLE BATTLE?$"

MauvilleCity_House3_1F_Text_HoppipDefeat:
	.string "Wow, {PLAYER}, you are really strong!$"

MauvilleCity_House3_1F_Text_GoodBattle:
	.string "That was a really good battle!\p"
	.string "I knew coming here wasn't a mistake.\p"
	.string "Let's have another battle sometime!$"

MauvilleCity_House3_1F_Text_NeedTwoMons:
	.string "I didn't think I would\n"
	.string "have to explain this…\p"
	.string "You need two POKéMON\n"
	.string "for a DOUBLE BATTLE…$"
