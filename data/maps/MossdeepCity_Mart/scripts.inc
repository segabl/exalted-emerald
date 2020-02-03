MossdeepCity_Mart_MapScripts:: @ 82223C7
	.byte 0

MossdeepCity_Mart_EventScript_Clerk:: @ 82223C8
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart MossdeepCity_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
MossdeepCity_Mart_Pokemart: @ 82223E0
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_NONE
	release
	end

MossdeepCity_Mart_EventScript_Boy:: @ 82223FF
	msgbox MossdeepCity_Mart_Text_MaxRepelLastsLongest, MSGBOX_NPC
	end

MossdeepCity_Mart_EventScript_Sailor:: @ 8222408
	msgbox MossdeepCity_Mart_Text_NetAndDiveBallsRare, MSGBOX_NPC
	end

MossdeepCity_Mart_EventScript_Woman::
	lock
	faceplayer
	checkitem ITEM_TM60, 1
	compare VAR_RESULT, TRUE
	goto_if_eq MossdeepCity_Mart_EventScript_WomanExplainQuash
	msgbox MossdeepCity_Mart_Text_WaitingInLine
	giveitem_std ITEM_TM60
	release
	end

MossdeepCity_Mart_EventScript_WomanExplainQuash::
	msgbox MossdeepCity_Mart_Text_QuashExplanation
	release
	end

MossdeepCity_Mart_Text_WaitingInLine:
	.string "I've been waiting in line forever!\p"
	.string "Maybe it's because of this?\p"
	.string "Here, you have it!$"

MossdeepCity_Mart_Text_QuashExplanation:
	.string "TM60 contains QUASH!\p"
	.string "It makes the targeted POKéMON\n"
	.string "move last if it hasn't moved yet.\p"
	.string "Maybe I should start making a move…$"

MossdeepCity_Mart_Text_MaxRepelLastsLongest: @ 82224A0
	.string "MAX REPEL keeps all weak POKéMON away.\p"
	.string "Out of all the REPEL sprays, it lasts\n"
	.string "the longest.$"

MossdeepCity_Mart_Text_NetAndDiveBallsRare: @ 82224FA
	.string "The NET and DIVE BALL production\n"
	.string "was recently moved to RUSTBORO CITY…\p"
	.string "Now that the DEVON CORPORATION took\n"
	.string "over production they are harder\l"
	.string "to come by here in MOSSDEEP CITY…$"
