RustboroCity_DevonCorp_2F_MapScripts:: @ 8211857
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_DevonCorp_2F_OnTransition
	.byte 0

RustboroCity_DevonCorp_2F_OnTransition: @ 821185D
	compare VAR_FOSSIL_RESURRECTION_STATE, 1
	call_if_eq RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	end

RustboroCity_DevonCorp_2F_EventScript_SetFossilReady:: @ 8211869
	setvar VAR_FOSSIL_RESURRECTION_STATE, 2
	return

RustboroCity_DevonCorp_2F_EventScript_TalkToPokemonScientist:: @ 821186F
	lock
	faceplayer
	compare VAR_FOSSIL_RESURRECTION_STATE, 1
	call_if_eq RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	msgbox RustboroCity_DevonCorp_2F_Text_DeviceForTalkingToPokemon, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_BallScientist:: @ 8211886
	lock
	faceplayer
	compare VAR_FOSSIL_RESURRECTION_STATE, 1
	call_if_eq RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	goto_if_set FLAG_MET_DEVON_EMPLOYEE, RustboroCity_DevonCorp_2F_EventScript_DevelopedBalls
	msgbox RustboroCity_DevonCorp_2F_Text_DevelopingNewBalls, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_DevelopedBalls:: @ 82118A6
	msgbox RustboroCity_DevonCorp_2F_Text_WeFinallyMadeNewBalls, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_PokenavScientist:: @ 82118B0
	lock
	faceplayer
	compare VAR_FOSSIL_RESURRECTION_STATE, 1
	call_if_eq RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	goto_if_set FLAG_RECEIVED_POKENAV, RustboroCity_DevonCorp_2F_EventScript_HasPokenav
	msgbox RustboroCity_DevonCorp_2F_Text_IMadePokenav, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_HasPokenav:: @ 82118D0
	msgbox RustboroCity_DevonCorp_2F_Text_WowThatsAPokenav, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_PokemonDreamsScientist:: @ 82118DA
	lock
	faceplayer
	compare VAR_FOSSIL_RESURRECTION_STATE, 1
	call_if_eq RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	msgbox RustboroCity_DevonCorp_2F_Text_DeviceToVisualizePokemonDreams, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_TradeScientist::
	lock
	faceplayer
	compare VAR_FOSSIL_RESURRECTION_STATE, 1
	call_if_eq RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	msgbox RustboroCity_DevonCorp_2F_Text_DeviceToSimulateTrades, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_TradeScientistDoTrade
	goto RustboroCity_DevonCorp_2F_EventScript_TradeScientistDeclineTrade
	end

RustboroCity_DevonCorp_2F_EventScript_TradeScientistDeclineTrade::
	msgbox RustboroCity_DevonCorp_2F_Text_SimulateTradeDecline
	release
	end

RustboroCity_DevonCorp_2F_EventScript_TradeScientistDoTrade::
	msgbox RustboroCity_DevonCorp_2F_Text_WhichMonToTrade
	special ChoosePartyMon
	waitstate
	compare VAR_0x8004, 0xFF
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_TradeScientistDeclineTrade
	special CanEvolveThroughTrade
	compare VAR_RESULT, SPECIES_NONE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_TradeScientistNoTrade
	msgbox RustboroCity_DevonCorp_2F_Text_AlrightLetsSee
	copyvar VAR_0x8005, VAR_0x8004
	setvar VAR_0x8004, 0xFFFF
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	msgbox RustboroCity_DevonCorp_2F_Text_SimulateTradeDone
	release
	end

RustboroCity_DevonCorp_2F_EventScript_TradeScientistNoTrade::
	msgbox RustboroCity_DevonCorp_2F_Text_ThisIsNoTradeEvolution
	release
	end

RustboroCity_DevonCorp_2F_EventScript_FossilScientist:: @ 82118F1
	lock
	faceplayer
	compare VAR_FOSSIL_RESURRECTION_STATE, 2
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FossilMonReady
	compare VAR_FOSSIL_RESURRECTION_STATE, 1
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_StillRegenerating
	msgbox RustboroCity_DevonCorp_2F_Text_DevelopDeviceToResurrectFossils, MSGBOX_DEFAULT
	checkitem ITEM_ROOT_FOSSIL, 1
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_NoticeFossil
	checkitem ITEM_CLAW_FOSSIL, 1
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_NoticeFossil
	checkitem ITEM_HELIX_FOSSIL, 1
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_NoticeFossil
	checkitem ITEM_DOME_FOSSIL, 1
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_NoticeFossil
	checkitem ITEM_OLD_AMBER, 1
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_NoticeFossil
	release
	end

RustboroCity_DevonCorp_2F_EventScript_NoticeFossil:: @ 8211933
	closemessage
	playse SE_PIN
	applymovement 5, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement 5, Common_Movement_Delay48
	waitmovement 0
	msgbox RustboroCity_DevonCorp_2F_Text_WantToBringFossilBackToLife, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_DeclineGiveFossil
	checkitem ITEM_ROOT_FOSSIL, 1
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_GiveRootFossil
	checkitem ITEM_CLAW_FOSSIL, 1
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_GiveClawFossil
	checkitem ITEM_HELIX_FOSSIL, 1
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_GiveHelixFossil
	checkitem ITEM_DOME_FOSSIL, 1
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_GiveDomeFossil
	checkitem ITEM_OLD_AMBER, 1
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_GiveOldAmber
	end

RustboroCity_DevonCorp_2F_EventScript_GiveRootFossil::
	bufferitemname 0, ITEM_ROOT_FOSSIL
	msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	takeitem ITEM_ROOT_FOSSIL, 1
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	setvar VAR_WHICH_FOSSIL_REVIVED, 1
	release
	end

RustboroCity_DevonCorp_2F_EventScript_GiveClawFossil::
	bufferitemname 0, ITEM_CLAW_FOSSIL
	msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	takeitem ITEM_CLAW_FOSSIL, 1
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	setvar VAR_WHICH_FOSSIL_REVIVED, 2
	release
	end

RustboroCity_DevonCorp_2F_EventScript_GiveHelixFossil::
	bufferitemname 0, ITEM_HELIX_FOSSIL
	msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	takeitem ITEM_HELIX_FOSSIL, 1
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	setvar VAR_WHICH_FOSSIL_REVIVED, 3
	release
	end

RustboroCity_DevonCorp_2F_EventScript_GiveDomeFossil::
	bufferitemname 0, ITEM_DOME_FOSSIL
	msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	takeitem ITEM_DOME_FOSSIL, 1
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	setvar VAR_WHICH_FOSSIL_REVIVED, 4
	release
	end

RustboroCity_DevonCorp_2F_EventScript_GiveOldAmber::
	bufferitemname 0, ITEM_OLD_AMBER
	msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	takeitem ITEM_OLD_AMBER, 1
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	setvar VAR_WHICH_FOSSIL_REVIVED, 5
	release
	end

RustboroCity_DevonCorp_2F_EventScript_DeclineGiveFossil:: @ 82119EF
	msgbox RustboroCity_DevonCorp_2F_Text_OhIsThatSo, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_StillRegenerating:: @ 82119F9
	msgbox RustboroCity_DevonCorp_2F_Text_FossilRegeneratorTakesTime, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_FossilMonReady:: @ 8211A03
	compare VAR_WHICH_FOSSIL_REVIVED, 1
	call_if_eq RustboroCity_DevonCorp_2F_EventScript_LileepReady
	compare VAR_WHICH_FOSSIL_REVIVED, 2
	call_if_eq RustboroCity_DevonCorp_2F_EventScript_AnorithReady
	compare VAR_WHICH_FOSSIL_REVIVED, 3
	call_if_eq RustboroCity_DevonCorp_2F_EventScript_OmanyteReady
	compare VAR_WHICH_FOSSIL_REVIVED, 4
	call_if_eq RustboroCity_DevonCorp_2F_EventScript_KabutoReady
	compare VAR_WHICH_FOSSIL_REVIVED, 5
	call_if_eq RustboroCity_DevonCorp_2F_EventScript_AerodactylReady
	bufferspeciesname 1, VAR_TEMP_1
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
	givemon VAR_TEMP_1, 20
	compare VAR_RESULT, 0
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_ReceiveParty
	compare VAR_RESULT, 1
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_ReceivePC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

RustboroCity_DevonCorp_2F_EventScript_LileepReady::
	setvar VAR_TEMP_1, SPECIES_LILEEP
	return

RustboroCity_DevonCorp_2F_EventScript_AnorithReady::
	setvar VAR_TEMP_1, SPECIES_ANORITH
	return

RustboroCity_DevonCorp_2F_EventScript_OmanyteReady::
	setvar VAR_TEMP_1, SPECIES_OMANYTE
	return

RustboroCity_DevonCorp_2F_EventScript_KabutoReady::
	setvar VAR_TEMP_1, SPECIES_KABUTO
	return

RustboroCity_DevonCorp_2F_EventScript_AerodactylReady::
	setvar VAR_TEMP_1, SPECIES_AERODACTYL
	return

RustboroCity_DevonCorp_2F_EventScript_ReceiveParty:: @ 8211A6E
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_FinishReceiving
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceiving
	end

RustboroCity_DevonCorp_2F_EventScript_ReceivePC:: @ 8211A96
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq RustboroCity_DevonCorp_2F_EventScript_TransferToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RustboroCity_DevonCorp_2F_EventScript_TransferToPC
	end

RustboroCity_DevonCorp_2F_EventScript_TransferToPC:: @ 8211AB9
	call Common_EventScript_TransferredToPC
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceiving
	end

RustboroCity_DevonCorp_2F_EventScript_ReceivedFanfare:: @ 8211AC4
	bufferspeciesname 1, VAR_TEMP_1
	playfanfare MUS_FANFA4
	message RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	bufferspeciesname 0, VAR_TEMP_1
	return

RustboroCity_DevonCorp_2F_EventScript_FinishReceiving:: @ 8211AD7
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
	release
	end

RustboroCity_DevonCorp_2F_EventScript_MatchCallScientist:: @ 8211BCF
	lock
	faceplayer
	compare VAR_FOSSIL_RESURRECTION_STATE, 1
	call_if_eq RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	compare VAR_RUSTBORO_CITY_STATE, 6
	goto_if_ge RustboroCity_DevonCorp_2F_EventScript_WorkOnNext
	msgbox RustboroCity_DevonCorp_2F_Text_DevelopNewPokenavFeature, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_WorkOnNext:: @ 8211BF1
	msgbox RustboroCity_DevonCorp_2F_Text_WhatToWorkOnNext, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_Text_DeviceForTalkingToPokemon: @ 8211BFB
	.string "We're developing a device for talking\n"
	.string "with POKéMON.\p"
	.string "But we haven't had much success…$"

RustboroCity_DevonCorp_2F_Text_DeviceToSimulateTrades:
	.string "I'm working on a device that can\n"
	.string "simulate POKéMON trades.\p"
	.string "As you might know, normally, certain\n"
	.string "POKéMON only evolve when they are\l"
	.string "traded with another person.\p"
	.string "This device creates a setting\n"
	.string "similar to the trading environment…\p"
	.string "I think it is working but it still\n"
	.string "needs some more testing…\p"
	.string "Say………\p"
	.string "Do you want to simulate a trade?$"

RustboroCity_DevonCorp_2F_Text_WhichMonToTrade:
	.string "Excellent!\p"
	.string "Which POKéMON do you want to use\n"
	.string "for the trade simulation?$"

RustboroCity_DevonCorp_2F_Text_AlrightLetsSee:
	.string "Alright, hold on…$"

RustboroCity_DevonCorp_2F_Text_ThisIsNoTradeEvolution:
	.string "My device only works on POKéMON\n"
	.string "that evolve through trading…\p"
	.string "In theory…$"

RustboroCity_DevonCorp_2F_Text_SimulateTradeDecline:
	.string "Oh…\n"
	.string "I understand…\p"
	.string "On second thought, it does\n"
	.string "seem kind of risky, doesn't it?$"

RustboroCity_DevonCorp_2F_Text_SimulateTradeDone:
	.string "Now, let's see…\p"
	.string "This parameter looks good…\p"
	.string "I'm seeing predictable phase arrays…\p"
	.string "Uh… It's probably not a problem…\p"
	.string "Probably…\p"
	.string "Wait, it's done already?\p"
	.string "Did it work?\p"
	.string "I was so busy monitoring the device\n"
	.string "that I missed the action…$"

RustboroCity_DevonCorp_2F_Text_DevelopingNewBalls: @ 8211C50
	.string "I'm developing new kinds of\n"
	.string "POKé BALLS…\p"
	.string "But I haven't made much headway…$"

RustboroCity_DevonCorp_2F_Text_WeFinallyMadeNewBalls: @ 8211C99
	.string "We finally made new kinds of\n"
	.string "POKé BALLS!\p"
	.string "The REPEAT BALL makes it easier to\n"
	.string "catch POKéMON you've caught before.\p"
	.string "The TIMER BALL gets better at catching\n"
	.string "POKéMON the longer a battle runs.\p"
	.string "Both are proudly developed by\n"
	.string "the DEVON CORPORATION.\p"
	.string "Please give them a try!$"

RustboroCity_DevonCorp_2F_Text_IMadePokenav: @ 8211D9F
	.string "I made the POKéNAV!\p"
	.string "As an engineer, I feel blessed to have\n"
	.string "made something so great!$"

RustboroCity_DevonCorp_2F_Text_WowThatsAPokenav: @ 8211DF3
	.string "Oh, wow!\n"
	.string "That's a POKéNAV!\p"
	.string "It came about as a result of our\n"
	.string "PRESIDENT's desire to learn about\l"
	.string "the feelings of POKéMON.\p"
	.string "Would you like me to describe its\n"
	.string "features in detail?\p"
	.string "No, no. I think you'll find out just by\n"
	.string "trying the POKéNAV out.$"

RustboroCity_DevonCorp_2F_Text_DeviceToVisualizePokemonDreams: @ 8211EE0
	.string "I'm trying to develop a device that\n"
	.string "visually reproduces the dreams of\l"
	.string "POKéMON…\p"
	.string "But it's not going well.$"

RustboroCity_DevonCorp_2F_Text_DevelopDeviceToResurrectFossils: @ 8211F48
	.string "I've been trying to develop a device\n"
	.string "that resurrects POKéMON from fossils…\p"
	.string "And, it's working!$"

RustboroCity_DevonCorp_2F_Text_WantToBringFossilBackToLife: @ 8211FA6
	.string "Wait! That thing you have there…\n"
	.string "Is that a POKéMON fossil?\p"
	.string "Would you like to bring that POKéMON\n"
	.string "back to life?\p"
	.string "I can do that with my newly developed\n"
	.string "FOSSIL REGENERATOR.$"

RustboroCity_DevonCorp_2F_Text_OhIsThatSo: @ 8212046
	.string "Oh, is that so?\p"
	.string "DEVON's technological expertise\n"
	.string "is outstanding, I tell you.$"

RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher: @ 8212153
	.string "Excellent!\n"
	.string "Let's do this right away.\p"
	.string "{PLAYER} handed the {STR_VAR_1} to\n"
	.string "the DEVON RESEARCHER.$"

RustboroCity_DevonCorp_2F_Text_FossilRegeneratorTakesTime: @ 82121A2
	.string "The FOSSIL REGENERATOR, which I made,\n"
	.string "is incredible.\p"
	.string "But it has one drawback--it takes\n"
	.string "a long time to work.\p"
	.string "So, uh… How about you go for a stroll\n"
	.string "and look around for a while?$"

RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife: @ 8212251
	.string "Thanks for waiting!\p"
	.string "Your fossilized POKéMON has been\n"
	.string "brought back to life!\p"
	.string "The fossil was an ancient POKéMON.\n"
	.string "{STR_VAR_2}, it was!$"

RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher: @ 82122CB
	.string "{PLAYER} received {STR_VAR_2} from\n"
	.string "the DEVON RESEARCHER.$"

RustboroCity_DevonCorp_2F_Text_DevelopNewPokenavFeature: @ 8212338
	.string "I'm trying to develop a new feature\n"
	.string "for the POKéNAV…\p"
	.string "But it's not going well.$"

RustboroCity_DevonCorp_2F_Text_WhatToWorkOnNext: @ 8212386
	.string "Well, now what shall I work on\n"
	.string "developing next?\p"
	.string "Our company allows us to make our\n"
	.string "inspirations into reality.\p"
	.string "One couldn't ask for a better\n"
	.string "environment as an engineer.$"

