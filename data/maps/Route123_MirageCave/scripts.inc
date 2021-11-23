Route123_MirageCave_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, Route123_MirageCave_OnLoad
	.byte 0

Route123_MirageCave_OnLoad::
	setflag FLAG_ENTERED_MIRAGE_LOCATION
	end
