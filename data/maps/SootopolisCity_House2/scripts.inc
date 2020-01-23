SootopolisCity_House2_MapScripts:: @ 8226A76
	.byte 0

SootopolisCity_House2_EventScript_ExpertF:: @ 8226A77
	lock
	faceplayer
	msgbox SootopolisCity_House2_Text_DidYouKnowAboutMtPyreOrbs, MSGBOX_YESNO
	compare VAR_RESULT, YES
	call_if_eq SootopolisCity_House2_EventScript_KnowAboutOrbs
	compare VAR_RESULT, NO
	call_if_eq SootopolisCity_House2_EventScript_DontKnowAboutOrbs
	release
	end

SootopolisCity_House2_EventScript_KnowAboutOrbs:: @ 8226A99
	msgbox SootopolisCity_House2_Text_YesTwoOrbsSideBySide, MSGBOX_DEFAULT
	return

SootopolisCity_House2_EventScript_DontKnowAboutOrbs:: @ 8226AA2
	msgbox SootopolisCity_House2_Text_OughtToVisitAndSee, MSGBOX_DEFAULT
	return

SootopolisCity_House2_EventScript_BallCollector::
	lock
	faceplayer
	dotimebasedevents
	goto_if_set FLAG_DAILY_BALL_COLLECTOR_RECEIVED_BALL, SootopolisCity_House2_EventScript_ReceivedBallToday
	msgbox SootopolisCity_House2_Text_ShareBallsWithYou, MSGBOX_DEFAULT
	random NUM_BALL_COLLECTOR_BALLS
	addvar VAR_RESULT, FIRST_BALL_COLLECTOR_BALL
	giveitem_std VAR_RESULT
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_DAILY_BALL_COLLECTOR_RECEIVED_BALL
	goto SootopolisCity_House2_EventScript_ReceivedBallToday
	end

SootopolisCity_House2_EventScript_ReceivedBallToday::
	msgbox SootopolisCity_House2_Text_ThisOneWasPopular, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House2_Text_DidYouKnowAboutMtPyreOrbs: @ 8226AAB
	.string "MT. PYRE…\p"
	.string "At its peak are two orbs placed side\n"
	.string "by side. Did you know?$"

SootopolisCity_House2_Text_YesTwoOrbsSideBySide: @ 8226AF1
	.string "Yes, two orbs side by side…\p"
	.string "The sight of them together…\n"
	.string "It is somehow soothing…$"

SootopolisCity_House2_Text_OughtToVisitAndSee: @ 8226B41
	.string "Is that so?\n"
	.string "Perhaps you ought to visit and see…$"

SootopolisCity_House2_Text_ShareBallsWithYou:
	.string "When I was younger I used to\n"
	.string "collect rare POKé BALLS on my\l"
	.string "trips all over the world…\p"
	.string "Here, let me give you one.$"

SootopolisCity_House2_Text_ThisOneWasPopular:
	.string "This BALL was made in the\n"
	.string "JOHTO region from a regional\l"
	.string "fruit known as APRICORN.\p"
	.string "It's quite popular there!$"
