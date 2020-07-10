#ifndef __MODULE_MODEL__
#define __MODULE_MODEL__

module;
#include "../Core/Core.h"

#include "Vars.h"
export module ModuleName(Model);

import ModuleName(Config);
import ModuleName(File);
import ModuleName(Internal);

#ifdef __INTELLISENSE__
#include "Config.ixx"
#include "File.ixx"
#include "Internal.ixx"
#endif

void RegisterModel
(
	byte8 * dest,
	byte8 * modelFile,
	byte8 * textureFile
)
{
	func_8B470(dest, 1);
	func_89960(dest, modelFile, textureFile);
}

void RegisterShadow
(
	byte8 * dest,
	byte8 * buffer,
	byte8 * file
)
{
	byte8 * addr = 0;

	addr = func_89DE0(dest);
	func_8BC60(buffer, addr, file);
	addr = func_89DE0(dest);
	func_305D80(addr);
}

void RegisterPhysics
(
	byte8 * dest,
	byte8 * buffer,
	byte8 * file
)
{
	uint32 count = 0;

	count = func_2C9F40(file);

	for_all(uint32, index, count)
	{
		func_2CA1D0(dest, buffer, file, index);
		dest += 0xF0;
	}
}

// replace with modeldata.

export void ResetModel(byte8 * dest)
{
	func_897B0(dest);
	func_89450(dest);
	memset(dest, 0, 0x780);
	func_89270(dest);
}

void CopyBaseVertices(MODEL_METADATA * modelMetadata)
{
	auto g_vertices = reinterpret_cast<vec4 *>(appBaseAddr + 0x58B260);

	for_all(uint8, index, 6)
	{
		uint8 off = (index * 3);
		modelMetadata[index].count = 4;
		modelMetadata[index].vertices[0] = g_vertices[(off + 0)];
		modelMetadata[index].vertices[1] = g_vertices[(off + 1)];
		modelMetadata[index].vertices[2] = g_vertices[(off + 2)];
	}
}

void CopyAmuletVertices(MODEL_METADATA * modelMetadata)
{
	auto g_vertices = reinterpret_cast<vec4 *>(appBaseAddr + 0x58B260);

	modelMetadata[0].count = 4;
	modelMetadata[0].vertices[0] = g_vertices[23];
	modelMetadata[0].vertices[1] = g_vertices[24];
	modelMetadata[0].vertices[2] = g_vertices[25];
}

void CopyCoatVertices(byte8 * dest)
{
	auto g_vertices = reinterpret_cast<vec4 *>(appBaseAddr + 0x35D580);
	auto addr = *reinterpret_cast<byte8 **>(dest);
	auto vertices = *reinterpret_cast<vec4 **>(addr + 0x108);

	vertices[0] = g_vertices[0];
	vertices[1] = g_vertices[1];
	vertices[2] = g_vertices[2];
	vertices[3] = g_vertices[3];
}









// costumeCacheFileId


template <typename T>
void UpdateModelFunction(T & actorData)
{
	uint8 modelIndex = 0;
	uint8 modelOff = 0;

	uint8 submodelIndex = 0;



	auto baseAddr = reinterpret_cast<byte8 *>(&actorData);

	auto & modelData = actorData.modelData[0];






	auto costume = actorData.costume;
	if (costume >= MAX_COSTUME_DANTE)
	{
		costume = 0;
	}


	auto costumeFileId = costumeFileIdsDante[costume];

	//auto file = File_staticFiles[costumeFileId];

	byte8 * modelFile   = 0;
	byte8 * textureFile = 0;
	byte8 * shadowFile  = 0;
	byte8 * physicsFile = 0;










	// noAmuletNoCoat



	//bool coat =
	//(actorData.costume == COSTUME_DANTE_DEFAULT_NO_COAT) ? false :
	//(actorData.costume == COSTUME_DANTE_DMC1_NO_COAT   ) ? false :
	//true;



	{
		{
			auto & file = File_staticFiles[costumeFileId];
			modelFile   = file[1];
			textureFile = file[0];
			shadowFile  = file[8];
		}
		if (actorData.newForceLadyFiles)
		{
			//if (costume == COSTUME_LADY_DEFAULT)
			//{
			//	auto & file = File_staticFiles[pl002];
			//	modelFile   = file[1];
			//	textureFile = file[0];
			//	shadowFile  = file[8];
			//}
			//else
			//{
				auto & file = File_staticFiles[em034];
				modelFile   = file[32];
				textureFile = file[31];
				shadowFile  = file[16];
			/*}*/
		}
	}





	// Main

	RegisterModel
	(
		modelData,
		modelFile,
		textureFile
	);

	RegisterShadow
	(
		modelData,
		actorData.var_9AD0[modelIndex],
		shadowFile
	);

	CopyBaseVertices(actorData.modelMetadata);















	// Coat

	{
		auto & file = File_staticFiles[costumeFileId];
		modelFile   = file[12];
		textureFile = file[0];
		shadowFile  = file[14];
		physicsFile = file[13];
	}






	RegisterModel
	(
		actorData.var_7540[submodelIndex],
		modelFile,
		textureFile
	);

	func_8A000
	(
		actorData.var_7540[submodelIndex],
		0,
		actorData.var_A0D0
	);

	RegisterShadow
	(
		actorData.var_7540[submodelIndex],
		actorData.var_9D10[submodelIndex],
		shadowFile
	);

	actorData.var_9AC0[submodelIndex] = 1;

	RegisterPhysics
	(
		actorData.var_A210,
		actorData.var_A0D0,
		physicsFile
	);

	func_2CA2F0
	(
		actorData.var_A210,
		(baseAddr + ((modelOff + 0x310) * 8)), // @Research: May no longer be needed.
		(appBaseAddr + 0x58B380),
		actorData.modelMetadata,
		6
	);

	CopyCoatVertices(actorData.var_A0D0);
}



export void UpdateModelDante(byte8 * baseAddr)
{
	LogFunction(baseAddr);

	auto & actorData = *reinterpret_cast<ACTOR_DATA_DANTE *>(baseAddr);

	UpdateModelFunction(actorData);
}














export void Model_Init()
{
	LogFunction();

	{
		auto func = CreateFunction(UpdateModelDante);
		//WriteCall((appBaseAddr + 0x212CB3), func.addr);
		/*
		dmc3.exe+212CB3 - E8 98200000       - call dmc3.exe+214D50
		dmc3.exe+212CB8 - 48 8D 86 A0380000 - lea rax,[rsi+000038A0]
		*/
	}



	// Dante Model Partition Updates
	{
		constexpr byte8 sect0[] =
		{
			0x80, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x01, // cmp byte ptr [rcx+0000B8C0],01
			0x74, 0x05,                               // je short
			0xE8, 0x00, 0x00, 0x00, 0x00,             // call dmc3.exe+2169F0
		};		auto func = CreateFunction(0, (appBaseAddr + 0x21557C), false, true, sizeof(sect0));		memcpy(func.sect0, sect0, sizeof(sect0));		*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ACTOR_DATA, newForceLadyFiles);		WriteCall((func.sect0 + 9), (appBaseAddr + 0x2169F0));		WriteJump((appBaseAddr + 0x215577), func.addr);		/*		dmc3.exe+215577 - E8 74140000       - call dmc3.exe+2169F0
		dmc3.exe+21557C - 48 81 C7 40750000 - add rdi,00007540		*/
	}








}






#endif
