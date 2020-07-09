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







template <typename T>
void UpdateModelFunction(T & actorData)
{
	uint8 modelIndex = 0;
	uint8 modelOff = 0;

	uint8 submodelIndex = 0;



	auto baseAddr = reinterpret_cast<byte8 *>(&actorData);

	//auto & modelData = actorData.modelData[actorData.activeModelIndex];

	auto & modelData = actorData.newModelData[0];





	// Main

	RegisterModel
	(
		modelData,
		File_staticFiles[pl011][1],
		File_staticFiles[pl011][0]
	);

	RegisterShadow
	(
		modelData,
		(baseAddr + 0x9AD0 + (modelIndex * 0xC0)),
		File_staticFiles[pl011][8]
	);

	CopyBaseVertices(actorData.modelMetadata);



	//func_8A000(modelData, File_staticFiles[pl000_00_0], (baseAddr + 0x1880));



	/*
	dmc3.exe+1EF3E0 - 4D 8D BD 00020000     - lea r15,[r13+00000200] { __SLOT_0_START__
	}
	dmc3.exe+1EF3E7 - 48 8B D1              - mov rdx,rcx { MOT_BASE
	}
	dmc3.exe+1EF3EA - 49 8B 07              - mov rax,[r15]
	dmc3.exe+1EF3ED - 4D 8D B5 80180000     - lea r14,[r13+00001880] { baseAddr + 1880
	}
	dmc3.exe+1EF3F4 - 4D 8B C6              - mov r8,r14
	dmc3.exe+1EF3F7 - 49 8B CF              - mov rcx,r15 { modelData
	}
	dmc3.exe+1EF3FA - FF 90 50010000        - call qword ptr [rax+00000150] { dmc3.exe+8A000
	}

	*/














	//// Coat

	//auto dest = (baseAddr + 0x7540 + (submodelIndex * 0x780));
	//auto dest2 = (baseAddr + 0xA0D0);


	//RegisterModel
	//(
	//	dest,
	//	File_staticFiles[pl000][12],
	//	File_staticFiles[pl000][0]
	//);

	//func_8A000(dest, 0, dest2);

	//RegisterShadow
	//(
	//	dest,
	//	(baseAddr + 0x9D10 + (submodelIndex * 0xC0)),
	//	File_staticFiles[pl000][14]
	//);

	//(reinterpret_cast<uint8 *>(baseAddr + 0x9AC0))[submodelIndex] = 1;

	//dest = (baseAddr + 0xA210);

	//RegisterPhysics
	//(
	//	dest,
	//	dest2,
	//	File_staticFiles[pl000][13]
	//);

	//func_2CA2F0
	//(
	//	dest,
	//	(baseAddr + ((modelOff + 0x310) * 8)),
	//	(appBaseAddr + 0x58B380),
	//	actorData.modelMetadata,
	//	6
	//);

	//CopyCoatVertices(dest2);
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







}






#endif
