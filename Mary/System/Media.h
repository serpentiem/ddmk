#pragma once
#include "../../Core/Core.h"

typedef void(* PlayTrack_t)(const char *);
extern PlayTrack_t PlayTrack;

enum MEDIA_
{
	MEDIA_NO_ERROR,
	MEDIA_SKIP_TRACK,
};

extern byte32 mediaError;
extern bool  mediaSkipTrack;

void System_Media_Init();
