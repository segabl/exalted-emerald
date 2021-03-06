PacifidlogTown_MapScripts:: @ 81EBAB1
	map_script MAP_SCRIPT_ON_TRANSITION, PacifidlogTown_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, PacifidlogTown_OnResume
	.byte 0

PacifidlogTown_OnTransition: @ 81EBABC
	setflag FLAG_VISITED_PACIFIDLOG_TOWN
	end

PacifidlogTown_OnResume: @ 81EBAC0
	setstepcallback STEP_CB_PACIFIDLOG_BRIDGE
	end

PacifidlogTown_EventScript_NinjaBoy:: @ 81EBAC3
	msgbox PacifidlogTown_Text_NeatHousesOnWater, MSGBOX_NPC
	end

PacifidlogTown_EventScript_Girl:: @ 81EBACC
	msgbox PacifidlogTown_Text_FastRunningCurrent, MSGBOX_NPC
	end

PacifidlogTown_EventScript_Fisherman:: @ 81EBAD5
	msgbox PacifidlogTown_Text_SkyPillarTooScary, MSGBOX_NPC
	end

PacifidlogTown_EventScript_FlingKid::
	lock
	faceplayer
	checkitem ITEM_TM56, 1
	compare VAR_RESULT, TRUE
	goto_if_eq PacifidlogTown_EventScript_FlingKidExplainFling
	msgbox PacifidlogTown_Text_SoAngry
	giveitem_std ITEM_TM56
	release
	end

PacifidlogTown_EventScript_FlingKidExplainFling::
	msgbox PacifidlogTown_Text_FlingExplanation
	release
	end


PacifidlogTown_EventScript_TownSign:: @ 81EBADE
	msgbox PacifidlogTown_Text_TownSign, MSGBOX_SIGN
	end

PacifidlogTown_Text_FastRunningCurrent: @ 81EBAE7
	.string "The sea between PACIFIDLOG and\n"
	.string "SLATEPORT has a fast-running tide.\p"
	.string "If you decide to SURF, you could end\n"
	.string "up swept away somewhere else.$"

PacifidlogTown_Text_NeatHousesOnWater: @ 81EBB6C
	.string "See, isn't it neat?\n"
	.string "These houses are on water!\p"
	.string "I was born here!$"

PacifidlogTown_Text_SkyPillarTooScary: @ 81EBBAC
	.string "The SKY PILLAR?\p"
	.string "…Oh, you must mean that tall, tall\n"
	.string "tower a little further out.\p"
	.string "If you asked me, I wouldn't climb it.\n"
	.string "It's too scary to get up that high.\p"
	.string "Life at sea level in PACIFIDLOG,\n"
	.string "that suits me fine.$"

PacifidlogTown_Text_TownSign: @ 81EBC7A
	.string "PACIFIDLOG TOWN\p"
	.string "“Where the morning sun smiles upon\n"
	.string "the waters.”$"

PacifidlogTown_Text_SoAngry:
	.string "Aaargh, I'm so angry, I could\n"
	.string "FLING this TM into the sea!\p"
	.string "None of my POKéMON can learn it,\n"
	.string "so take it before I throw it away!$"

PacifidlogTown_Text_FlingExplanation:
	.string "TM56 contains FLING!\p"
	.string "A POKéMON using this move will\n"
	.string "throw its ITEM at the opponent.\p"
	.string "How effective it is depends on\n"
	.string "the ITEM it is holding.$"
