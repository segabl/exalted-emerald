Route133_MapScripts:: @ 81F75A2
	.byte 0

Route133_EventScript_Franklin:: @ 81F75A3
	trainerbattle_single TRAINER_FRANKLIN, Route133_Text_FranklinIntro, Route133_Text_FranklinDefeat
	msgbox Route133_Text_FranklinPostBattle, MSGBOX_AUTOCLOSE
	end

Route133_EventScript_Debra:: @ 81F75BA
	trainerbattle_single TRAINER_DEBRA, Route133_Text_DebraIntro, Route133_Text_DebraDefeat
	msgbox Route133_Text_DebraPostBattle, MSGBOX_AUTOCLOSE
	end

Route133_EventScript_Linda:: @ 81F75D1
	trainerbattle_single TRAINER_LINDA, Route133_Text_LindaIntro, Route133_Text_LindaDefeat
	msgbox Route133_Text_LindaPostBattle, MSGBOX_AUTOCLOSE
	end

Route133_EventScript_Warren:: @ 81F75E8
	trainerbattle_single TRAINER_WARREN, Route133_Text_WarrenIntro, Route133_Text_WarrenDefeat
	msgbox Route133_Text_WarrenPostBattle, MSGBOX_AUTOCLOSE
	end

Route133_EventScript_Beck:: @ 81F75FF
	trainerbattle_single TRAINER_BECK, Route133_Text_BeckIntro, Route133_Text_BeckDefeat
	msgbox Route133_Text_BeckPostBattle, MSGBOX_AUTOCLOSE
	end

Route133_EventScript_Mollie:: @ 81F7616
	trainerbattle_single TRAINER_MOLLIE, Route133_Text_MollieIntro, Route133_Text_MollieDefeat
	msgbox Route133_Text_MolliePostBattle, MSGBOX_AUTOCLOSE
	end

Route133_EventScript_Conor:: @ 81F762D
	trainerbattle_single TRAINER_CONOR, Route133_Text_ConorIntro, Route133_Text_ConorDefeat
	msgbox Route133_Text_ConorPostBattle, MSGBOX_AUTOCLOSE
	end

Route133_EventScript_Psychic::
	lock
	faceplayer
	checkitem ITEM_TM77, 1
	compare VAR_RESULT, TRUE
	goto_if_eq Route133_EventScript_PsychicExplainPsychUp
	msgbox Route133_Text_GotCarriedHere
	giveitem_std ITEM_TM77
	release
	end

Route133_EventScript_PsychicExplainPsychUp::
	msgbox Route133_Text_PsychUpExplanation
	release
	end

Route133_Text_GotCarriedHere:
	.string "Wow!\p"
	.string "I got carried here by the currents\n"
	.string "all the way from PACIFIDLOG TOWN!\p"
	.string "I'm pretty psyched up!\p"
	.string "Here, take this.$"

Route133_Text_PsychUpExplanation:
	.string "The TM77 contains PSYCH UP!\p"
	.string "It boosts the senses to copy\n"
	.string "the stat changes of the target.\p"
	.string "My senses are already boosted\n"
	.string "enough though!$"
