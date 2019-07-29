#include "Path.h"

//#pragma warning(disable: 4102) // Unreferenced label.

static void SetPath()
{
	LogFunction();
	uint32 bufferSize = 4096;
	char * buffer = (char *)VirtualAllocEx(appProcess, 0, bufferSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	DWORD error = GetLastError();
	if (!buffer && error)
	{
		Log("VirtualAllocEx failed. %X", error);
		return;
	}
	uint32 pos = 0;
	char * & exePath = *(char **)(appBaseAddr + 0xF66F18);
	char drive[8];
	char userName[64];
	char savePath[512];
	{
		char buffer[128];
		GetSystemDirectoryA(buffer, sizeof(buffer));
		drive[0] = buffer[0];
		drive[1] = 0;
	}
	{
		uint32 userNameSize = sizeof(userName);
		GetUserNameA(userName, &userNameSize);
	}
	{
		snprintf(savePath, sizeof(savePath), "%s:\\Users\\%s\\Documents\\CAPCOM\\DEVILMAYCRY4SPECIALEDITION\\SavedGame00.DevilMayCry4SpecialEdition", drive, userName);
	}
	snprintf(buffer, bufferSize, "%s", exePath);
	pos += (strlen(buffer) - pos);
	SkipIntroStart:
	{
		if (!Config.System.Media.skipIntro)
		{
			goto SkipIntroEnd;
		}
		snprintf((buffer + pos), (bufferSize - pos), "\"%s\"", savePath);
		pos += (strlen(buffer) - pos);
	}
	SkipIntroEnd:
	exePath = buffer;
	Log("%s", buffer);
	Log("pos %u", pos);
}

void System_Path_Init()
{
	LogFunction();
	{
		BYTE sect0[] =
		{
			0xA3, 0x00, 0x00, 0x00, 0x00, //mov [dmc4.exe+F66F18],eax
		};
		FUNC func = CreateFunction(SetPath, (appBaseAddr + 0xACF40E), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*(BYTE **)(func.sect0 + 1) = (appBaseAddr + 0xF66F18);
		WriteJump((appBaseAddr + 0xACF409), func.addr);
	}
}
