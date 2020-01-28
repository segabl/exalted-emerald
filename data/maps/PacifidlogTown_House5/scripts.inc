PacifidlogTown_House5_MapScripts:: @ 8204110
	.byte 0

PacifidlogTown_House5_EventScript_MirageIslandWatcher:: @ 8204111
	lock
	faceplayer
	specialvar VAR_RESULT, IsMirageLocationPresent
	compare VAR_RESULT, MIRAGE_LOCATION_ROUTE_130
	goto_if_eq PacifidlogTown_House5_EventScript_MirageIslandPresent
	msgbox PacifidlogTown_House5_Text_CantSeeMirageIslandToday, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House5_EventScript_MirageIslandPresent:: @ 820412D
	msgbox PacifidlogTown_House5_Text_CanSeeMirageIslandToday, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House5_EventScript_Gentleman:: @ 8204137
	msgbox PacifidlogTown_House5_Text_MirageIslandAppearDependingOnWeather, MSGBOX_NPC
	end

PacifidlogTown_House5_EventScript_Psychic::
	lock
	faceplayer
	checkitem ITEM_TM03, 1
	compare VAR_RESULT, TRUE
	goto_if_eq PacifidlogTown_House5_EventScript_PsychicExplainPsyshock
	msgbox PacifidlogTown_House5_Text_PsychicPokemonAreShocking
	giveitem_std ITEM_TM03
	release
	end

PacifidlogTown_House5_EventScript_PsychicExplainPsyshock::
	msgbox PacifidlogTown_House5_Text_PsyshockExplanation
	release
	end

PacifidlogTown_House5_Text_CantSeeMirageIslandToday: @ 8204140
	.string "I can't see MIRAGE ISLAND today…\p"
	.string "Maybe it appeared somewhere else?$"

PacifidlogTown_House5_Text_CanSeeMirageIslandToday: @ 8204161
	.string "Oh! Oh my!\n"
	.string "I can see MIRAGE ISLAND today!$"

PacifidlogTown_House5_Text_MirageIslandAppearDependingOnWeather: @ 820418B
	.string "MIRAGE ISLAND…\p"
	.string "It must become visible and invisible\n"
	.string "depending on the weather conditions.\p"
	.string "I heard there are other locations\n"
	.string "that appear and disappear\l"
	.string "in a similar way…\p"
	.string "I wonder where they might be…$"

PacifidlogTown_House5_Text_PsychicPokemonAreShocking:
	.string "PSYCHIC type POKéMON can be quite\n"
	.string "shocking, don't you think?\p"
	.string "Like this SPECIAL move that deals\n"
	.string "PHYSICAL damage to an opponent.$"

PacifidlogTown_House5_Text_PsyshockExplanation:
	.string "TM03 contains PSYSHOCK.\p"
	.string "It's a SPECIAL attack that deals\n"
	.string "PHYSICAL damage.\p"
	.string "Isn't that shocking?$"
