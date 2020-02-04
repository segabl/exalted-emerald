BattleFrontier_Lounge9_MapScripts:: @ 82678F8
	.byte 0

BattleFrontier_Lounge9_EventScript_SwaggerGirl::
	lock
	faceplayer
	checkitem ITEM_TM87, 1
	compare VAR_RESULT, TRUE
	goto_if_eq BattleFrontier_Lounge9_EventScript_ReceivedSwagger
	msgbox BattleFrontier_Lounge9_Text_ILikeyourStyle, MSGBOX_DEFAULT
	giveitem_std ITEM_TM87
	release
	end

BattleFrontier_Lounge9_EventScript_ReceivedSwagger::
	msgbox BattleFrontier_Lounge9_Text_SwaggerExplanantion, MSGBOX_NPC
	end

BattleFrontier_Lounge9_Text_ILikeyourStyle:
	.string "I like your style!\p"
	.string "You're just bursting of confidence!\p"
	.string "Please have this!$"

BattleFrontier_Lounge9_Text_SwaggerExplanantion:
	.string "TM87 contains SWAGGER.\p"
	.string "It sharply raises the target's\n"
	.string "ATTACK but also confuses it.\p"
	.string "You have to be really confident to\n"
	.string "keep attacking when you're hit by it!$"
