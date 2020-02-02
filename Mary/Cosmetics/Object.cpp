
// @Todo: Add actor only flag.

#include "Object.h"

uint8 g_cacheFileIndex[Object_Count] =
{
	pl000,
	pl002,
	plwp_sword,
	plwp_sword2,
	plwp_sword3,
	plwp_newvergilsword,
	plwp_forceedge,
	plwp_nerosword,
};

byte8 * g_model  [Object_Count] = {};
byte8 * g_texture[Object_Count] = {};

void SetObject(byte8 * baseAddr)
{
	auto & model   = *(byte8 **)(baseAddr + 0x108);
	auto & texture = *(byte8 **)(baseAddr + 0x110);

	for (uint8 object = 0; object < Object_Count; object++)
	{
		auto & objectIndex = Config.Cosmetics.Object.index[object];

		if (model == g_model[object])
		{
			model   = g_model  [objectIndex];
			texture = g_texture[objectIndex];
			break;
		}
	}
}

void Cosmetics_Object_Init()
{
	LogFunction();
	for (uint8 object = 0; object < Object_Count; object++)
	{
		auto & cacheFileIndex = g_cacheFileIndex[object];
		//auto archive = System_Cache_file[cacheFileIndex];

		auto archive = System_File_cacheFile[cacheFileIndex]; // @Todo: Change to id.

		auto fileOff = (uint32 *)(archive + 8);
		g_model  [object] = (archive + fileOff[1]);
		g_texture[object] = (archive + fileOff[0]);
	}
	{
		byte8 sect0[] =
		{
			0x48, 0x89, 0x88, 0x10, 0x01, 0x00, 0x00, //mov [rax+00000110],rcx
		};
		byte8 sect1[] =
		{
			0x48, 0x8B, 0xC8, //mov rcx,rax
		};
		FUNC func = CreateFunction(SetObject, (appBaseAddr + 0x304B1B), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteJump((appBaseAddr + 0x304B14), func.addr, 2);
		// dmc3.exe+304B14 - 48 89 88 10010000 - mov [rax+00000110],rcx
		// dmc3.exe+304B1B - 48 8B 45 50       - mov rax,[rbp+50]
	}
}

void Cosmetics_Object_ToggleDisableObjectPartitionUpdates(bool enable)
{
	LogFunction(enable);


	// Disable Motion



}










