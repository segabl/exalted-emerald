SlateportCity_NameRatersHouse_MapScripts:: @ 8209AA4
	.byte 0

SlateportCity_NameRatersHouse_EventScript_NameRater:: @ 8209AA5
	lock
	faceplayer
	msgbox SlateportCity_NameRatersHouse_Text_PleasedToRateMonNickname, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SlateportCity_NameRatersHouse_EventScript_ChooseMonToRate
	compare VAR_RESULT, NO
	goto_if_eq SlateportCity_NameRatersHouse_EventScript_DeclineNameRate
	end

SlateportCity_NameRatersHouse_EventScript_ChooseMonToRate:: @ 8209AC6
	msgbox SlateportCity_NameRatersHouse_Text_CritiqueWhichMonNickname, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	compare VAR_0x8004, 255
	goto_if_ne SlateportCity_NameRatersHouse_EventScript_RateMonNickname
	compare VAR_0x8004, 255
	goto_if_eq SlateportCity_NameRatersHouse_EventScript_DeclineNameRate
	end

SlateportCity_NameRatersHouse_EventScript_DeclineNameRate:: @ 8209AE9
	msgbox SlateportCity_NameRatersHouse_Text_DoVisitAgain, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_EventScript_RateMonNickname:: @ 8209AF3
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	compare VAR_RESULT, SPECIES_EGG
	goto_if_eq SlateportCity_NameRatersHouse_EventScript_CantRateEgg
	special BufferMonNickname
	special IsMonOTIDNotPlayers
	compare VAR_RESULT, TRUE
	goto_if_eq SlateportCity_NameRatersHouse_EventScript_PlayerNotMonsOT
	specialvar VAR_RESULT, MonOTNameNotPlayer
	special BufferMonNickname
	compare VAR_RESULT, TRUE
	goto_if_eq SlateportCity_NameRatersHouse_EventScript_PlayerNotMonsOT
	call SlateportCity_NameRatersHouse_EventScript_RateName
	msgbox SlateportCity_NameRatersHouse_Text_FineNameSuggestBetterOne, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq SlateportCity_NameRatersHouse_EventScript_ChangeNickname
	compare VAR_RESULT, NO
	goto_if_eq SlateportCity_NameRatersHouse_EventScript_DeclineNameRate
	end

SlateportCity_NameRatersHouse_EventScript_CantRateEgg:: @ 8209B46
	msgbox SlateportCity_NameRatersHouse_Text_ThatIsMerelyAnEgg, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_EventScript_PlayerNotMonsOT:: @ 8209B50
	msgbox SlateportCity_NameRatersHouse_Text_MagnificentName, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_EventScript_ChangeNickname:: @ 8209B5A
	msgbox SlateportCity_NameRatersHouse_Text_WhatShallNewNameBe, MSGBOX_DEFAULT
	call Common_EventScript_NameReceivedPartyMon
	specialvar VAR_0x8005, TryPutNameRaterShowOnTheAir
	special BufferMonNickname
	compare VAR_0x8005, TRUE
	call_if_eq SlateportCity_NameRatersHouse_EventScript_RateName
	compare VAR_0x8005, FALSE
	call_if_eq SlateportCity_NameRatersHouse_EventScript_NameNoDifferent
	release
	end

SlateportCity_NameRatersHouse_EventScript_NameNoDifferent::
	msgbox SlateportCity_NameRatersHouse_Text_NameNoDifferent, MSGBOX_DEFAULT
	return

SlateportCity_NameRatersHouse_EventScript_RateName:: @ 8209B84
	specialvar VAR_RESULT, GetMonNameScore
	compare VAR_RESULT, 0
	call_if_eq SlateportCity_NameRatersHouse_EventScript_RateName0
	compare VAR_RESULT, 1
	call_if_eq SlateportCity_NameRatersHouse_EventScript_RateName1
	compare VAR_RESULT, 2
	call_if_eq SlateportCity_NameRatersHouse_EventScript_RateName2
	compare VAR_RESULT, 3
	call_if_eq SlateportCity_NameRatersHouse_EventScript_RateName3
	compare VAR_RESULT, 4
	call_if_eq SlateportCity_NameRatersHouse_EventScript_RateName4
	compare VAR_RESULT, 5
	call_if_eq SlateportCity_NameRatersHouse_EventScript_RateName5
	return

SlateportCity_NameRatersHouse_EventScript_RateName0::
	msgbox SlateportCity_NameRatersHouse_Text_RatedName0, MSGBOX_DEFAULT
	return

SlateportCity_NameRatersHouse_EventScript_RateName1::
	msgbox SlateportCity_NameRatersHouse_Text_RatedName1, MSGBOX_DEFAULT
	return

SlateportCity_NameRatersHouse_EventScript_RateName2::
	msgbox SlateportCity_NameRatersHouse_Text_RatedName2, MSGBOX_DEFAULT
	return

SlateportCity_NameRatersHouse_EventScript_RateName3::
	msgbox SlateportCity_NameRatersHouse_Text_RatedName3, MSGBOX_DEFAULT
	return

SlateportCity_NameRatersHouse_EventScript_RateName4::
	msgbox SlateportCity_NameRatersHouse_Text_RatedName4, MSGBOX_DEFAULT
	return

SlateportCity_NameRatersHouse_EventScript_RateName5::
	msgbox SlateportCity_NameRatersHouse_Text_RatedName5, MSGBOX_DEFAULT
	return

SlateportCity_NameRatersHouse_Text_PleasedToRateMonNickname: @ 8209B8E
	.string "Hi, hi! I'm the NAME RATER!\n"
	.string "I'm the fortune-teller of names!\p"
	.string "I shall be pleased to rate your\n"
	.string "POKéMON's nickname.$"

SlateportCity_NameRatersHouse_Text_CritiqueWhichMonNickname: @ 8209BFF
	.string "Which POKéMON's nickname should\n"
	.string "I critique?$"

SlateportCity_NameRatersHouse_Text_FineNameSuggestBetterOne: @ 8209C2B
	.string "What say you, if I were to suggest\n"
	.string "a slightly different name?$"

SlateportCity_NameRatersHouse_Text_WhatShallNewNameBe: @ 8209CA4
	.string "Ah, good. Then, what shall the new\n"
	.string "nickname be?$"

SlateportCity_NameRatersHouse_Text_RatedName0:
	.string "It's a {STR_VAR_1}, I see…\p"
	.string "Well in a way, no nickname is also a\n"
	.string "way to express yourself…$"

SlateportCity_NameRatersHouse_Text_RatedName1:
	.string "Hmmm, {STR_VAR_1}? I don't know…\p"
	.string "It's not the worst, but you could\n"
	.string "do a lot better than that!$"

SlateportCity_NameRatersHouse_Text_RatedName2:
	.string "{STR_VAR_1}… … …\n"
	.string "{STR_VAR_1}… … …\p"
	.string "I'd say this is a pretty solid name,\n"
	.string "nothing special but not bad either!$"

SlateportCity_NameRatersHouse_Text_RatedName3:
	.string "Hey, {STR_VAR_1} is pretty good!\p"
	.string "It has a certain ring to it!\n"
	.string "It's a nickname that just works!$"

SlateportCity_NameRatersHouse_Text_RatedName4:
	.string "{STR_VAR_1}? That's brilliant!\p"
	.string "It's an excellent name choice,\n"
	.string "I like it a lot!$"

SlateportCity_NameRatersHouse_Text_RatedName5:
	.string "Oh wow!\p"
	.string "{STR_VAR_1} is amazing!\p"
	.string "It's rare that I get to hear\n"
	.string "such a wonderful nickname!$"

SlateportCity_NameRatersHouse_Text_DoVisitAgain: @ 8209D42
	.string "I see.\n"
	.string "Do come visit again.$"

SlateportCity_NameRatersHouse_Text_NameNoDifferent: @ 8209D5E
	.string "{STR_VAR_1}?\p"
	.string "It's no different than before…$"

SlateportCity_NameRatersHouse_Text_MagnificentName: @ 8209DF0
	.string "Hmmm… {STR_VAR_1} it is!\p"
	.string "This is a magnificent nickname!\n"
	.string "It is impeccably beyond reproach!\p"
	.string "You'll do well to cherish your\n"
	.string "{STR_VAR_1} now and beyond.$"

SlateportCity_NameRatersHouse_Text_ThatIsMerelyAnEgg: @ 8209E74
	.string "Now, now.\n"
	.string "That is merely an EGG!$"

