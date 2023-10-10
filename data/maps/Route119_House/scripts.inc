Route119_House_MapScripts:: @ 8270965
	.byte 0

Route119_House_EventScript_Woman:: @ 822A920
	goto_if_set FLAG_TEMP_1, Route119_House_EventScript_RumorAboutCaveOfOrigin
	msgbox Route119_House_Text_RestUpHere, MSGBOX_NPC
	call Common_EventScript_OutOfCenterPartyHeal
	setflag FLAG_TEMP_1
	msgbox Route119_House_Text_AfterRest, MSGBOX_NPC
	end

Route119_House_EventScript_RumorAboutCaveOfOrigin::
	msgbox Route119_House_Text_RumorAboutCaveOfOrigin, MSGBOX_NPC
	end

Route119_House_EventScript_Wingull:: @ 827096F
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WINGULL, 0
	msgbox Route119_House_Text_Wingull, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route119_House_Text_RestUpHere:
	.string "Are you travelling up ROUTE 119?\p"
	.string "It has a lot of tall grass\n"
	.string "and strong TRAINERS, so you\l"
	.string "should come prepared.\p"
	.string "Let me quickly take care of\n"
	.string "your POKéMON for you, okay?$"

Route119_House_Text_AfterRest:
	.string "There, that's better.\p"
	.string "Don't be afraid to come back\n"
	.string "whenever you need a rest.$"

Route119_House_Text_RumorAboutCaveOfOrigin: @ 8270982
	.string "I heard about a cave called the CAVE\n"
	.string "OF ORIGIN.\p"
	.string "People rumor that the spirits of\n"
	.string "POKéMON are revived there. Could\l"
	.string "something like that really happen?$"

Route119_House_Text_Wingull: @ 8270A17
	.string "WINGULL: Pihyoh!$"

