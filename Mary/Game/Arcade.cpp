#include "Arcade.h"

void Game_Arcade_Toggle(bool enable)
{
	Log("%s %u", FUNC_NAME, enable);
	if (enable)
	{
		//Write<BYTE>((appBaseAddr + 0x2433FB), 0xEB);                         // Force New Game
		//Write<BYTE>((appBaseAddr + 0x243299), 0xEB);                         // Ignore Mission Select Menu
		//Write<BYTE>((appBaseAddr + 0x2411F5), 0xEB);                         // Force Start Mission





		//WriteAddress((appBaseAddr + 0x217991), (appBaseAddr + 0x217993), 2); // Force Costume
		//WriteAddress((appBaseAddr + 0x21799A), (appBaseAddr + 0x21799C), 2); // ..
		Write<BYTE>((appBaseAddr + 0x1AA791), 0xEB);                         // Skip Orb Notifications
	}
	else
	{
		Write<BYTE>((appBaseAddr + 0x2433FB), 0x74);
		Write<BYTE>((appBaseAddr + 0x243299), 0x74);
		Write<BYTE>((appBaseAddr + 0x2411F5), 0x74);
		WriteAddress((appBaseAddr + 0x217991), (appBaseAddr + 0x2179A2), 2);
		WriteAddress((appBaseAddr + 0x21799A), (appBaseAddr + 0x2179A2), 2);
		Write<BYTE>((appBaseAddr + 0x1AA791), 0x75);
	}
}
