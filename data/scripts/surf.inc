EventScript_UseSurf:: @ 8271EA0
	checkitem ITEM_HM03, 1
	compare VAR_RESULT, FALSE
	goto_if_eq EventScript_EndUseSurf
	checkpartytmhm ITEM_HM03
	compare VAR_RESULT, PARTY_SIZE
	goto_if_eq EventScript_EndUseSurf
	bufferpartymonnick 0, VAR_RESULT
	setfieldeffectargument 0, VAR_RESULT
	lockall
	msgbox gText_WantToUseSurf, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq EventScript_ReleaseUseSurf
	msgbox gText_PlayerUsedSurf, MSGBOX_DEFAULT
	dofieldeffect FLDEFF_USE_SURF
EventScript_ReleaseUseSurf:: @ 8271ED5
	releaseall
EventScript_EndUseSurf:: @ 8271ED6
	end
