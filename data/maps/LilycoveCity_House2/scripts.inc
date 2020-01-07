LilycoveCity_House2_MapScripts:: @ 821ED74
	.byte 0

LilycoveCity_House2_EventScript_FatMan:: @ 821ED75
	lock
	faceplayer
	checkitem ITEM_TM44, 1
	compare VAR_RESULT, TRUE
	goto_if_eq LilycoveCity_House2_EventScript_ReceivedRest
	msgbox LilycoveCity_House2_Text_NotAwakeYetHaveThis, MSGBOX_DEFAULT
	giveitem_std ITEM_TM44
	msgbox LilycoveCity_House2_Text_SleepIsEssential, MSGBOX_DEFAULT
	giveitem_std ITEM_TM88
	release
	end

LilycoveCity_House2_EventScript_ReceivedRest:: @ 821EDAC
	msgbox LilycoveCity_House2_Text_SleepIsEssential, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House2_Text_NotAwakeYetHaveThis: @ 821EDB6
	.string "Huh? What? What's that?\p"
	.string "I'm not near awake yet…\n"
	.string "You can have this…$"

LilycoveCity_House2_Text_SleepIsEssential: @ 821EDF9
	.string "Yawn…\p"
	.string "Sleep is essential for good health…\n"
	.string "Sleep and regain health…$"
