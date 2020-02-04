RustboroCity_Mart_MapScripts:: @ 8214F05
	.byte 0

RustboroCity_Mart_EventScript_Clerk:: @ 8214F06
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart RustboroCity_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

RustboroCity_Mart_Pokemart: @ 8214F30
	.2byte ITEM_POKE_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_NONE
	release
	end

RustboroCity_Mart_EventScript_Clerk2::
	goto_if_unset FLAG_MET_DEVON_EMPLOYEE, RustboroCity_Mart_EventScript_Clerk2OutOfStock
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart RustboroCity_Mart_Pokemart2
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

RustboroCity_Mart_EventScript_Clerk2OutOfStock::
	msgbox RustboroCity_Mart_Text_SorryOutOfStock, MSGBOX_NPC
	end

	.align 2
RustboroCity_Mart_Pokemart2: @ 8214F58
	.2byte ITEM_NET_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_LUXURY_BALL
	.2byte ITEM_DIVE_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_QUICK_BALL
	.2byte ITEM_HEAL_BALL
	.2byte ITEM_NONE
	release
	end

RustboroCity_Mart_EventScript_PokefanF:: @ 8214F74
	msgbox RustboroCity_Mart_Text_BuyingHealsInCaseOfShroomish, MSGBOX_NPC
	end

RustboroCity_Mart_EventScript_Boy:: @ 8214F7D
	msgbox RustboroCity_Mart_Text_ShouldBuySuperPotionsInstead, MSGBOX_NPC
	end

RustboroCity_Mart_EventScript_BugCatcher:: @ 8214F86
	msgbox RustboroCity_Mart_Text_GettingEscapeRopeJustInCase, MSGBOX_NPC
	end

RustboroCity_Mart_EventScript_FalseSwipeMan::
	lock
	faceplayer
	checkitem ITEM_TM54, 1
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_Mart_EventScript_ReceivedFalseSwipe
	msgbox RustboroCity_Mart_Text_LoweringHpIsEssential, MSGBOX_DEFAULT
	giveitem_std ITEM_TM54
	release
	end

RustboroCity_Mart_EventScript_ReceivedFalseSwipe::
	msgbox RustboroCity_Mart_Text_ExplainFalseSwipe, MSGBOX_NPC
	end

RustboroCity_Mart_Text_SorryOutOfStock:
	.string "Sorry, our special POKé BALLS\n"
	.string "haven't been delivered yet…\p"
	.string "Please come back later!$"

RustboroCity_Mart_Text_BuyingHealsInCaseOfShroomish: @ 8214F8F
	.string "I'm buying some PARLYZ HEALS and\n"
	.string "ANTIDOTES.\p"
	.string "Just in case I run into SHROOMISH\n"
	.string "in PETALBURG WOODS.$"

RustboroCity_Mart_Text_ShouldBuySuperPotionsInstead: @ 8214FF1
	.string "My POKéMON evolved.\n"
	.string "It has a lot of HP now.\p"
	.string "I should buy SUPER POTIONS for it\n"
	.string "instead of ordinary POTIONS.$"

RustboroCity_Mart_Text_GettingEscapeRopeJustInCase: @ 821505C
	.string "I'm getting an ESCAPE ROPE just in\n"
	.string "case I get lost in a cave.\p"
	.string "I just need to use it to get back to\n"
	.string "the entrance.$"

RustboroCity_Mart_Text_LoweringHpIsEssential:
	.string "Lowering the HP of a wild POKéMON\n"
	.string "increases your chance of catching it.\p"
	.string "You can't catch a fainted POKéMON\n"
	.string "though, so this TM comes in handy!$"

RustboroCity_Mart_Text_ExplainFalseSwipe:
	.string "TM54 contains FALSE SWIPE.\p"
	.string "It leaves the target with at\n"
	.string "least one HP.\p"
	.string "It's perfect for catching POKéMON!$"
