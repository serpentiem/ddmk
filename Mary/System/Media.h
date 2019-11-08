#pragma once
#include "../../Core/Core.h"

typedef void(* PlayTrack_t)(const char *);
extern PlayTrack_t PlayTrack;

enum MEDIA_
{
	MEDIA_NO_ERROR,
	MEDIA_SKIP_TRACK,
};

extern dword mediaError;
extern bool  mediaSkipTrack;

void System_Media_Init();
void System_Media_ToggleSkipIntro(bool enable);
void System_Media_ToggleSkipCutscenes(bool enable);
