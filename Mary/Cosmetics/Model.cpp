#include "Model.h"

void SetModel(byte8 * baseAddr)
{
	auto & model   = *(byte8 **)(baseAddr + 0x108);
	auto & texture = *(byte8 **)(baseAddr + 0x110);



	byte8 * rebellionModel = 0;
	byte8 * rebellionTexture = 0;


	byte8 * forceEdgeModel = 0;
	byte8 * forceEdgeTexture = 0;


	
	byte8 * neroAngeloSwordModel = 0;
	byte8 * neroAngeloSwordTexture = 0;



	{
		auto archive = cacheFile[plwp_sword];
		auto off = (uint32 *)(archive + 8);
		rebellionTexture = (archive + off[0]);
		rebellionModel = (archive + off[1]);
	}


	{
		auto archive = cacheFile[plwp_forceedge];
		auto off = (uint32 *)(archive + 8);
		forceEdgeTexture = (archive + off[0]);
		forceEdgeModel = (archive + off[1]);
	}

	{
		auto archive = cacheFile[plwp_nerosword];
		auto off = (uint32 *)(archive + 8);

		neroAngeloSwordModel = (archive + off[1]);
		neroAngeloSwordTexture = (archive + off[0]);



	}



	
	if (model == forceEdgeModel)
	{
		Log("model match");

		//model = rebellionModel;
		model = neroAngeloSwordModel;
	}

	if (texture == forceEdgeTexture)
	{
		Log("texture match");

		//texture = rebellionTexture;

		texture = neroAngeloSwordTexture;

	}







}

void Cosmetics_Model_Init()
{
	LogFunction();
	{
		byte8 sect0[] =
		{
			0x48, 0x89, 0x88, 0x10, 0x01, 0x00, 0x00, //mov [rax+00000110],rcx
		};
		byte8 sect1[] =
		{
			0x48, 0x8B, 0xC8, //mov rcx,rax
		};
		FUNC func = CreateFunction(SetModel, (appBaseAddr + 0x304B1B), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteJump((appBaseAddr + 0x304B14), func.addr, 2);
		// dmc3.exe+304B14 - 48 89 88 10010000 - mov [rax+00000110],rcx
		// dmc3.exe+304B1B - 48 8B 45 50       - mov rax,[rbp+50]
	}
}
