MauvilleCity_House4_MapScripts::
	.byte 0

MauvilleCity_House4_EventScript_Ace::
	msgbox MauvilleCity_House4_Text_DoYouGetToEverGrande, MSGBOX_NPC
	end

MauvilleCity_House4_EventScript_Girl::
	lock
	faceplayer
	checkitem ITEM_TM48, 1
	compare VAR_RESULT, TRUE
	goto_if_eq MauvilleCity_House4_EventScript_ReceivedRound
	msgbox MauvilleCity_House4_Text_DontMindMyBrother
	giveitem_std ITEM_TM48
	call MauvilleCity_House4_EventScript_ReceivedRound
	end

MauvilleCity_House4_EventScript_ReceivedRound::
	msgbox MauvilleCity_House4_Text_ExplainRound
	release
	end

MauvilleCity_House4_Text_DoYouGetToEverGrande:
	.string "Do you get to EVER GRANDE CITY\n"
	.string "very often?\p"
	.string "Oh, what am I saying?\n"
	.string "Of course you don't.$"

MauvilleCity_House4_Text_DontMindMyBrother:
	.string "Please don't mind my brother…\p"
	.string "He's just repeating silly phrases\n"
	.string "that he has heard online…\p"
	.string "Here, you can have this!$"

MauvilleCity_House4_Text_ExplainRound:
	.string "TM48 contains ROUND…\p"
	.string "A POKéMON using it will immediately\n"
	.string "go after any POKéMON that used\l"
	.string "the same attack.\p"
	.string "The power doubles when that happens!$"
