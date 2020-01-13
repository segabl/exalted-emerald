MauvilleCity_House3_2F_MapScripts::
	.byte 0

MauvilleCity_House3_2F_EventScript_Girl::
	lock
	faceplayer
	checkitem ITEM_TM89, 1
	compare VAR_RESULT, TRUE
	goto_if_eq MauvilleCity_House3_2F_EventScript_GirlExplainUTurn
	msgbox MauvilleCity_House3_2F_Text_ILikeDoingUTurns
	giveitem_std ITEM_TM89
	release
	end

MauvilleCity_House3_2F_EventScript_GirlExplainUTurn::
	msgbox MauvilleCity_House3_2F_Text_UTurnExplanation
	release
	end

MauvilleCity_House3_2F_EventScript_OldMan::
	msgbox MauvilleCity_House3_2F_Text_IEnvyTheChild, MSGBOX_NPC
	end

MauvilleCity_House3_2F_Text_ILikeDoingUTurns:
	.string "I like doing U-TURNS!\p"
	.string "Do you want to join me?\p"
	.string "You will need this!$"

MauvilleCity_House3_2F_Text_UTurnExplanation:
	.string "TM89 contains U-TURN!\p"
	.string "A POKéMON using it will attack\n"
	.string "and then immediately switch\l"
	.string "places with an ally.\p"
	.string "I don't have any POKéMON yet,\n"
	.string "so I'm doing the U-TURNS myself!$"

MauvilleCity_House3_2F_Text_IEnvyTheChild:
	.string "I envy my granddaughter…\p"
	.string "She has energy for two!$"
