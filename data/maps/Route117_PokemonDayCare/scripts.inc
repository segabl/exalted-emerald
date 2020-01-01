Route117_PokemonDayCare_MapScripts:: @ 822BBB1
	map_script MAP_SCRIPT_ON_TRANSITION, Route117_PokemonDayCare_OnTransition
	.byte 0

Route117_PokemonDayCare_OnTransition: @ 822BBB7
	setflag FLAG_LANDMARK_POKEMON_DAYCARE
	end

Route117_PokemonDayCare_EventScript_Girl::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_DESTINY_KNOT, Route117_PokemonDayCare_EventScript_ExplainDestinyKnot
	msgbox Route117_PokemonDayCare_Text_ItMustBeDestiny, MSGBOX_DEFAULT
	giveitem_std ITEM_DESTINY_KNOT
	compare VAR_RESULT, 0
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_DESTINY_KNOT
	release
	end

Route117_PokemonDayCare_EventScript_ExplainDestinyKnot::
	msgbox Route117_PokemonDayCare_Text_ExplainDestinyKnot, MSGBOX_DEFAULT
	release
	end

Route117_PokemonDayCare_Text_ItMustBeDestiny:
	.string "That we meet here...\p"
	.string "It must be destiny...\p"
	.string "Here, take this...$"

Route117_PokemonDayCare_Text_ExplainDestinyKnot:
	.string "When your POKéMON becomes infatuated\n"
	.string "while holding the DESTINY KNOT,\l"
	.string "it will also infatuate the\l"
	.string "POKéMON that caused it.\p"
	.string "I wonder if it would work on humans...$"
