MauvilleCity_Mart_MapScripts:: @ 82110E5
	.byte 0

MauvilleCity_Mart_EventScript_Clerk:: @ 82110E6
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart MauvilleCity_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
MauvilleCity_Mart_Pokemart: @ 8211100
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_GUARD_SPEC
	.2byte ITEM_DIRE_HIT
	.2byte ITEM_X_ACCURACY
	.2byte ITEM_NONE
	release
	end

MauvilleCity_Mart_EventScript_Clerk2::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart MauvilleCity_Mart_Pokemart2
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
MauvilleCity_Mart_Pokemart2:
	.2byte ITEM_TM09 @ Venoshock
	.2byte ITEM_TM40 @ Aerial Ace
	.2byte ITEM_TM42 @ Facade
	.2byte ITEM_TM47 @ Low Sweep
	.2byte ITEM_TM57 @ Charge Beam
	.2byte ITEM_TM78 @ Bulldoze
	.2byte ITEM_TM82 @ Dragon Tail
	.2byte ITEM_TM98 @ Power-Up Punch
	.2byte ITEM_NONE
	release
	end

MauvilleCity_Mart_EventScript_ExpertM:: @ 821111C
	msgbox MauvilleCity_Mart_Text_ItemsToTemporarilyElevateStats, MSGBOX_NPC
	end

MauvilleCity_Mart_EventScript_Man:: @ 8211125
	msgbox MauvilleCity_Mart_Text_DecisionsDetermineBattle, MSGBOX_NPC
	end

MauvilleCity_Mart_EventScript_ToughGuy::
	lock
	faceplayer
	checkitem ITEM_TM58, 1
	compare VAR_RESULT, TRUE
	goto_if_eq MauvilleCity_Mart_EventScript_ToughGuyExplainSkyDrop
	msgbox MauvilleCity_Mart_Text_LikeRollercoasters, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq MauvilleCity_Mart_EventScript_ToughGuyNoLike
	msgbox MauvilleCity_Mart_Text_ThenYoullLikeThis
	giveitem_std ITEM_TM58
	goto MauvilleCity_Mart_EventScript_ToughGuyExplainSkyDrop
	end

MauvilleCity_Mart_EventScript_ToughGuyNoLike::
	msgbox MauvilleCity_Mart_Text_AreYouAfraid
	release
	end

MauvilleCity_Mart_EventScript_ToughGuyExplainSkyDrop::
	msgbox MauvilleCity_Mart_Text_SkyDropExplanation
	release
	end

MauvilleCity_Mart_Text_LikeRollercoasters:
	.string "I love roller coasters!\p"
	.string "Especially fast ones with\n"
	.string "loops and everything!\p"
	.string "What about you?\n"
	.string "Do you like roller coasters?$"

MauvilleCity_Mart_Text_AreYouAfraid:
	.string "Ha, what's the matter?\p"
	.string "Are you afraid of heights?$"

MauvilleCity_Mart_Text_ThenYoullLikeThis::
	.string "Then you will love this!$"

MauvilleCity_Mart_Text_SkyDropExplanation::
	.string "TM58 contains SKY DROP!\p"
	.string "It takes the opposing POKéMON\n"
	.string "high up in the air in the first turn\l"
	.string "and then drops it down in the second.\p"
	.string "It sounds super scary…\p"
	.string "I'm not afraid or anything!$"

MauvilleCity_Mart_Text_ItemsToTemporarilyElevateStats: @ 821112E
	.string "There are items that temporarily\n"
	.string "elevate the stats of POKéMON.\p"
	.string "The ones I know you use in battle\n"
	.string "are X ATTACK and X DEFEND…\p"
	.string "I do believe that there are others\n"
	.string "like them.$"

MauvilleCity_Mart_Text_DecisionsDetermineBattle: @ 82111D8
	.string "Use a certain move, or use an item\n"
	.string "instead…\p"
	.string "The TRAINER's decisions determine how\n"
	.string "battles turn out, I think.$"
