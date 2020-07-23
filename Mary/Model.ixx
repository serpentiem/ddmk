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

//void old_RegisterModel
//(
//	byte8 * dest,
//	byte8 * modelFile,
//	byte8 * textureFile
//)
//{
//	func_8B470(dest, 1);
//	func_89960(dest, modelFile, textureFile);
//}
//
//void old_RegisterShadow
//(
//	byte8 * dest,
//	byte8 * buffer,
//	byte8 * file
//)
//{
//	byte8 * addr = 0;
//
//	addr = func_89DE0(dest);
//	func_8BC60(buffer, addr, file);
//	addr = func_89DE0(dest);
//	func_305D80(addr);
//}
//
//void old_RegisterPhysics
//(
//	byte8 * dest,
//	byte8 * buffer,
//	byte8 * file
//)
//{
//	uint32 count = 0;
//
//	count = func_2C9F40(file);
//
//	for_all(uint32, index, count)
//	{
//		func_2CA1D0(dest, buffer, file, index);
//		dest += 0xF0; // @Todo: Change to Size_240.
//	}
//}
//










inline void RegisterModel
(
	ModelData & modelData,
	byte8 * modelFile,
	byte8 * textureFile
)
{
	func_8B470
	(
		modelData,
		1
	);
	func_89960
	(
		modelData,
		modelFile,
		textureFile
	);
}

inline void RegisterShadow
(
	ModelData & modelData,
	ShadowData & shadowData,
	byte8 * shadowFile
)
{
	auto dest = func_89DE0(modelData);
	func_8BC60
	(
		shadowData,
		dest,
		shadowFile
	);
	//dest = func_89DE0(modelData);
	func_305D80(dest);
}

inline void RegisterPhysics
(
	byte8 * physicsFile,
	PhysicsData * physicsData,
	void * physicsMetadata
)
{
	auto count = func_2C9F40(physicsFile);
	if (count == 0)
	{
		return;
	}
	for_all(uint32, index, count)
	{
		func_2CA1D0
		(
			physicsData[index],
			physicsMetadata,
			physicsFile,
			index
		);
	}
}

//template <typename T>
//void LinkModelPhysicsData
//(
//	T & actorData,
//	DevilModelMetadata & devilModelMetadata,
//	DevilSubmodelMetadata & devilSubmodelMetadata,
//	uint8 devilSubmodelPhysicsLinkDataIndex,
//	uint8 modelPhysicsMetadataIndex,
//	uint8 devilModelPhysicsMetadataIndex
//)
//{
//	uint8 devilModelIndex = (devilModelMetadata.modelIndex == 1) ? 0 : 1;
//
//	auto & devilSubmodelPhysicsLinkData = actorData.devilSubmodelPhysicsLinkData[devilSubmodelMetadata.devilSubmodelIndex][devilSubmodelPhysicsLinkDataIndex];
//
//	auto modelPhysicsMetadataAddr = actorData.modelPhysicsMetadata[devilModelMetadata.modelIndex][(devilModelMetadata.modelPhysicsMetadataIndex + modelPhysicsMetadataIndex)];
//	if (!modelPhysicsMetadataAddr)
//	{
//		return;
//	}
//	auto & modelPhysicsMetadata = *modelPhysicsMetadataAddr;
//
//	auto devilModelPhysicsMetadataAddr = actorData.devilModelPhysicsMetadata[devilModelIndex][(devilSubmodelMetadata.devilModelPhysicsMetadataIndex + devilModelPhysicsMetadataIndex)];
//	if (!devilModelPhysicsMetadataAddr)
//	{
//		return;
//	}
//	auto & devilPhysicsMetadata = *devilModelPhysicsMetadataAddr;
//
//	devilSubmodelPhysicsLinkData.enable = 1;
//	devilSubmodelPhysicsLinkData.physicsData = modelPhysicsMetadata.physicsData;
//	memcpy(devilSubmodelPhysicsLinkData.data, (appBaseAddr + 0x35D580), 64);
//
//	devilPhysicsMetadata.devilPhysicsData = &devilSubmodelPhysicsLinkData;
//}





















/*
human

func_2CA1D0
(
actorData.var_A210,
actorData.var_A0D0,
physicsFile,
index
);

devil

func_2CA1D0
(
actorData.var_A540[devilSubmodelIndex],
&actorData.devilPhysicsMetadata[devilModelIndex][devilPhysicsMetadataIndex],
physicsFile,
index
);
*/










































// @Todo: Add Shadow.

export void ResetModel(ModelData & modelData)
{
	func_897B0(modelData);
	func_89450(modelData);
	memset(modelData, 0, sizeof(ModelData));
	func_89270(modelData);
}



















//void CopyBaseVertices(MODEL_METADATA * modelMetadata)
//{
//	auto g_vertices = reinterpret_cast<vec4 *>(appBaseAddr + 0x58B260);
//
//	for_all(uint8, index, 6)
//	{
//		uint8 off = (index * 3);
//		modelMetadata[index].count = 4;
//		modelMetadata[index].vertices[0] = g_vertices[(off + 0)];
//		modelMetadata[index].vertices[1] = g_vertices[(off + 1)];
//		modelMetadata[index].vertices[2] = g_vertices[(off + 2)];
//	}
//}
//
//void CopyAmuletVertices(MODEL_METADATA * modelMetadata)
//{
//	auto g_vertices = reinterpret_cast<vec4 *>(appBaseAddr + 0x58B260);
//
//	modelMetadata[0].count = 4;
//	modelMetadata[0].vertices[0] = g_vertices[23];
//	modelMetadata[0].vertices[1] = g_vertices[24];
//	modelMetadata[0].vertices[2] = g_vertices[25];
//}
//
//void CopyCoatVertices(byte8 * dest)
//{
//	auto g_vertices = reinterpret_cast<vec4 *>(appBaseAddr + 0x35D580);
//	auto addr = *reinterpret_cast<byte8 **>(dest);
//	auto vertices = *reinterpret_cast<vec4 **>(addr + 0x108);
//
//	vertices[0] = g_vertices[0];
//	vertices[1] = g_vertices[1];
//	vertices[2] = g_vertices[2];
//	vertices[3] = g_vertices[3];
//}











template <typename T>
void UpdateModelFunctionDante(T & actorData)
{
	auto costume = actorData.costume;
	if (costume >= MAX_COSTUME_DANTE)
	{
		costume = 0;
	}
	auto costumeFileId = costumeFileIdsDante[costume];
	auto coat =
	(
		(costume == COSTUME_DANTE_DEFAULT                           ) ||
		(costume == COSTUME_DANTE_DEFAULT_TORN                      ) ||
		(costume == COSTUME_DANTE_DMC1                              ) ||
		(costume == COSTUME_DANTE_SPARDA                            ) ||
		(costume == COSTUME_DANTE_DEFAULT_TORN_INFINITE_MAGIC_POINTS) ||
		(costume == COSTUME_DANTE_SPARDA_INFINITE_MAGIC_POINTS      )
	)
	? true : false;

	if (actorData.newForceFiles)
	{
		switch (actorData.newForceFilesCharacter)
		{
		case CHAR_BOB:
		{
			if (costume >= MAX_COSTUME_BOB)
			{
				costume = 0;
			}
			costumeFileId = costumeFileIdsBob[costume];
			coat = false;
			break;
		}
		case CHAR_LADY:
		{
			if (costume >= MAX_COSTUME_LADY)
			{
				costume = 0;
			}
			costumeFileId = costumeFileIdsLady[costume];
			coat = false;
			break;
		}
		case CHAR_VERGIL:
		{
			if (costume >= MAX_COSTUME_VERGIL)
			{
				costume = 0;
			}
			costumeFileId = costumeFileIdsVergil[costume];
			coat =
			(
				(costume == COSTUME_VERGIL_DEFAULT                      ) ||
				(costume == COSTUME_VERGIL_DEFAULT_INFINITE_MAGIC_POINTS) ||
				(costume == COSTUME_VERGIL_SPARDA                       ) ||
				(costume == COSTUME_VERGIL_SPARDA_INFINITE_MAGIC_POINTS )
			)
			? true : false;
			break;
		}
		}
	}

	auto & file = File_staticFiles[costumeFileId];

	byte8 * modelFile   = 0;
	byte8 * textureFile = 0;
	byte8 * shadowFile  = 0;
	byte8 * physicsFile = 0;

	uint8 modelIndex    = 0;
	uint8 submodelIndex = 0;

	// Main

	modelFile   = file[1];
	textureFile = file[0];
	shadowFile  = file[8];

	if (actorData.newForceFiles && (actorData.newForceFilesCharacter == CHAR_LADY) && (costume == COSTUME_LADY_LEATHER_JUMPSUIT))
	{
		modelFile   = file[32];
		textureFile = file[31];
		shadowFile  = file[16];
	}

	RegisterModel
	(
		actorData.modelData[modelIndex],
		modelFile,
		textureFile
	);

	RegisterShadow
	(
		actorData.modelData[modelIndex],
		actorData.newModelShadowData[modelIndex],
		shadowFile
	);

	{
		auto g_vertices = reinterpret_cast<vec4 *>(appBaseAddr + 0x58B260);

		for_all(uint8, index, 6)
		{
			uint8 off = (index * 3);
			actorData.modelMetadata[index].count = 4;
			actorData.modelMetadata[index].vertices[0] = g_vertices[(off + 0)];
			actorData.modelMetadata[index].vertices[1] = g_vertices[(off + 1)];
			actorData.modelMetadata[index].vertices[2] = g_vertices[(off + 2)];
		}
	}

	// Coat

	modelFile   = file[12];
	textureFile = file[0 ];
	shadowFile  = file[14];
	physicsFile = file[13];

	if (actorData.newForceFiles && (actorData.newForceFilesCharacter == CHAR_LADY) && (costume == COSTUME_LADY_LEATHER_JUMPSUIT))
	{
		modelFile   = file[17];
		textureFile = file[31];
		physicsFile = file[18];
	}

	RegisterModel
	(
		actorData.newSubmodelData[submodelIndex],
		modelFile,
		textureFile
	);

	func_8A000
	(
		actorData.newSubmodelData[submodelIndex],
		0,
		&actorData.submodelPhysicsMetadata
	);

	if (actorData.newForceFiles && (actorData.newForceFilesCharacter == CHAR_LADY))
	{
		return;
	}

	if (coat)
	{
		RegisterShadow
		(
			actorData.newSubmodelData[submodelIndex],
			actorData.submodelShadowData[submodelIndex],
			shadowFile
		);
	}

	actorData.var_9AC0[submodelIndex] = true;

	RegisterPhysics
	(
		physicsFile,
		&actorData.submodelPhysicsData,
		&actorData.submodelPhysicsMetadata
	);

	func_2CA2F0
	(
		actorData.submodelPhysicsData,
		actorData.modelPhysicsMetadataPool[modelIndex],
		(appBaseAddr + 0x58B380),
		actorData.modelMetadata,
		(coat) ? 6 : 1
	);

	if (coat)
	{
		auto g_vertices = reinterpret_cast<vec4 *>(appBaseAddr + 0x35D580);

		actorData.submodelPhysicsMetadata.vertices[0] = g_vertices[0];
		actorData.submodelPhysicsMetadata.vertices[1] = g_vertices[1];
		actorData.submodelPhysicsMetadata.vertices[2] = g_vertices[2];
		actorData.submodelPhysicsMetadata.vertices[3] = g_vertices[3];
	}
	else
	{
		auto g_vertices = reinterpret_cast<vec4 *>(appBaseAddr + 0x58B260);

		actorData.modelMetadata[0].count = 4;
		actorData.modelMetadata[0].vertices[0] = g_vertices[23];
		actorData.modelMetadata[0].vertices[1] = g_vertices[24];
		actorData.modelMetadata[0].vertices[2] = g_vertices[25];
	}
}









export void UpdateModelDante(byte8 * baseAddr)
{
	LogFunction(baseAddr);

	auto & actorData = *reinterpret_cast<ACTOR_DATA_DANTE *>(baseAddr);

	UpdateModelFunctionDante(actorData);
}










//template <typename T>
//void LinkPhysics
//(
//	T & actorData,
//	DevilPhysicsData & devilPhysicsData,
//	uint8 physicsIndex,
//	uint8 devilPhysicsIndex
//)
//{
//	uint8 modelIndex = 1;
//	uint8 devilModelIndex = 0;
//
//	auto & devilPhysicsMetadata = *actorData.devilPhysicsMetadata[devilModelIndex][devilPhysicsIndex];
//	devilPhysicsMetadata.devilPhysicsData = &devilPhysicsData;
//
//	devilPhysicsData.enable = 1;
//
//	auto & physicsMetadata = *actorData.physicsMetadata[modelIndex][physicsIndex];
//	devilPhysicsData.physicsData = physicsMetadata.physicsData;
//
//	memcpy(devilPhysicsData.data, (appBaseAddr + 0x35D580), 64);
//}
































export template <typename T>
void UpdateDevilModelFunctionDante
(
	T & actorData,
	uint8 devil,
	uint8 devilModelIndex
)
{
	auto devilFileId = devilFileIdsDante[devil];

	auto & file = File_staticFiles[devilFileId];

	byte8 * modelFile   = 0;
	byte8 * textureFile = 0;
	byte8 * shadowFile  = 0;
	byte8 * physicsFile = 0;

	auto & devilModelMetadata = actorData.devilModelMetadata[devil];

	uint8 modelIndex                = (devilModelIndex == 0) ? 1  : 2;
	uint8 modelPhysicsMetadataIndex = 0;

	uint8 submodelIndex                  = (devilModelIndex == 0) ? 1 : 3;
	uint8 devilModelPhysicsMetadataIndex = 0;
	uint8 devilSubmodelIndex             = (devilModelIndex == 0) ? 0 : 2;

	auto LinkModelPhysicsData = [&]
	(
		uint8 _devilSubmodelPhysicsLinkDataIndex,
		uint8 _modelPhysicsMetadataIndex,
		uint8 _devilModelPhysicsMetadataIndex
	)
	{
		auto & devilSubmodelPhysicsLinkData = actorData.devilSubmodelPhysicsLinkData[devilSubmodelIndex][_devilSubmodelPhysicsLinkDataIndex];

		auto modelPhysicsMetadataAddr = actorData.modelPhysicsMetadataPool[modelIndex][(modelPhysicsMetadataIndex + _modelPhysicsMetadataIndex)];
		if (!modelPhysicsMetadataAddr)
		{
			return;
		}
		auto & modelPhysicsMetadata = *modelPhysicsMetadataAddr;

		auto devilModelPhysicsMetadataAddr = actorData.devilModelPhysicsLinkMetadataPool[devilModelIndex][(devilModelPhysicsMetadataIndex + _devilModelPhysicsMetadataIndex)];
		if (!devilModelPhysicsMetadataAddr)
		{
			return;
		}
		auto & devilPhysicsMetadata = *devilModelPhysicsMetadataAddr;

		devilSubmodelPhysicsLinkData.enable = 1;
		devilSubmodelPhysicsLinkData.physicsData = modelPhysicsMetadata.physicsData;
		memcpy(devilSubmodelPhysicsLinkData.data, (appBaseAddr + 0x35D580), 64);

		devilPhysicsMetadata.devilPhysicsData = &devilSubmodelPhysicsLinkData;
	};

	actorData.devilModels[modelIndex] = devil;

	// Main

	modelFile   = file[1];
	textureFile = file[0];

	if (devil == DEVIL_DANTE_AGNI_RUDRA)
	{
		shadowFile  = file[2];
	}
	else if
	(
		(devil == DEVIL_DANTE_CERBERUS) ||
		(devil == DEVIL_DANTE_BEOWULF ) ||
		(devil == DEVIL_DANTE_SPARDA  )
	)
	{
		shadowFile  = file[4];
	}
	else if
	(
		(devil == DEVIL_DANTE_REBELLION) ||
		(devil == DEVIL_DANTE_NEVAN    )
	)
	{
		shadowFile  = file[6];
	}

	RegisterModel
	(
		actorData.modelData[modelIndex],
		modelFile,
		textureFile
	);

	func_1EF040
	(
		actorData,
		modelIndex
	);

	RegisterShadow
	(
		actorData.modelData[modelIndex],
		actorData.newModelShadowData[modelIndex],
		shadowFile
	);

	devilModelMetadata.modelIndex = modelIndex;
	devilModelMetadata.modelPhysicsMetadataIndex = ((modelIndex * 24) + modelPhysicsMetadataIndex);

	if (devil == DEVIL_DANTE_AGNI_RUDRA)
	{
		return;
	}

	// Wings

	modelFile   = file[2];
	textureFile = file[0];
	physicsFile = file[3];

	if
	(
		(devil == DEVIL_DANTE_REBELLION) ||
		(devil == DEVIL_DANTE_NEVAN    )
	)
	{
		shadowFile = file[7];
	}
	else if
	(
		(devil == DEVIL_DANTE_CERBERUS) ||
		(devil == DEVIL_DANTE_BEOWULF ) ||
		(devil == DEVIL_DANTE_SPARDA  )
	)
	{
		shadowFile = file[5];
	}

	RegisterModel
	(
		actorData.newSubmodelData[submodelIndex],
		modelFile,
		textureFile
	);

	func_8A000
	(
		actorData.newSubmodelData[submodelIndex],
		0,
		&actorData.devilModelPhysicsLinkMetadataPool[devilModelIndex][devilModelPhysicsMetadataIndex]
	);

	RegisterShadow
	(
		actorData.newSubmodelData[submodelIndex],
		actorData.submodelShadowData[submodelIndex],
		shadowFile
	);

	actorData.var_9AC0[submodelIndex] = true;

	RegisterPhysics
	(
		physicsFile,
		&actorData.devilSubmodelPhysicsData[devilSubmodelIndex],
		&actorData.devilModelPhysicsLinkMetadataPool[devilModelIndex][devilModelPhysicsMetadataIndex]
	);

	if
	(
		(devil == DEVIL_DANTE_REBELLION) ||
		(devil == DEVIL_DANTE_NEVAN    )
	)
	{
		LinkModelPhysicsData(0, 3, 1);
		LinkModelPhysicsData(1, 2, 12);
	}
	else if
	(
		(devil == DEVIL_DANTE_CERBERUS) ||
		(devil == DEVIL_DANTE_BEOWULF )
	)
	{
		LinkModelPhysicsData(0, 3, 1);
		LinkModelPhysicsData(1, 6 , 2);
		LinkModelPhysicsData(2, 10, 8);
	}

	devilModelMetadata.devilSubmodelMetadata[0].submodelIndex                  = submodelIndex;
	devilModelMetadata.devilSubmodelMetadata[0].devilModelPhysicsMetadataIndex = ((devilModelIndex * 36) + devilModelPhysicsMetadataIndex);
	devilModelMetadata.devilSubmodelMetadata[0].devilSubmodelIndex             = devilSubmodelIndex;

	submodelIndex++;
	devilModelPhysicsMetadataIndex += 9;
	devilSubmodelIndex++;

	// Coat

	if
	(
		!(
			(devil == DEVIL_DANTE_REBELLION) ||
			(devil == DEVIL_DANTE_NEVAN    )
		)
	)
	{
		return;
	}

	modelFile   = file[4];
	textureFile = file[0];
	shadowFile  = file[8];
	physicsFile = file[5];

	RegisterModel
	(
		actorData.newSubmodelData[submodelIndex],
		modelFile,
		textureFile
	);

	func_8A000
	(
		actorData.newSubmodelData[submodelIndex],
		0,
		&actorData.devilModelPhysicsLinkMetadataPool[devilModelIndex][devilModelPhysicsMetadataIndex]
	);

	RegisterShadow
	(
		actorData.newSubmodelData[submodelIndex],
		actorData.submodelShadowData[submodelIndex],
		shadowFile
	);

	actorData.var_9AC0[submodelIndex] = true;

	RegisterPhysics
	(
		physicsFile,
		&actorData.devilSubmodelPhysicsData[devilSubmodelIndex],
		&actorData.devilModelPhysicsLinkMetadataPool[devilModelIndex][devilModelPhysicsMetadataIndex]
	);

	func_2CA2F0
	(
		actorData.devilSubmodelPhysicsData[devilSubmodelIndex],
		actorData.modelPhysicsMetadataPool[modelIndex],
		(appBaseAddr + 0x58B380),
		actorData.modelMetadata,
		6
	);

	LinkModelPhysicsData(0, 2 , 1);
	LinkModelPhysicsData(1, 14, 2);

	devilModelMetadata.devilSubmodelMetadata[1].submodelIndex                   = submodelIndex;
	devilModelMetadata.devilSubmodelMetadata[1].devilModelPhysicsMetadataIndex  = ((devilModelIndex * 36) + devilModelPhysicsMetadataIndex);
	devilModelMetadata.devilSubmodelMetadata[1].devilSubmodelIndex              = devilSubmodelIndex;
}

















void UpdateDevilModelDante(ACTOR_DATA_DANTE & actorData)
{
	LogFunction(actorData.operator byte8 *());
	UpdateDevilModelFunctionDante(actorData, 0, 0);
}



























//Vector devilAuras<byte8 *>;

export Vector<byte8 *> devilAuras;















void CreateDevilAura(byte8 * baseAddr)
{
	LogFunction(baseAddr);

	if (!baseAddr)
	{
		return;
	}

	devilAuras.Push(baseAddr);






	//auto actorBaseAddr = *reinterpret_cast<byte8 **>(baseAddr + 0xC0);
	//if (!actorBaseAddr)
	//{
	//	return;
	//}
	//auto & actorData = *reinterpret_cast<ACTOR_DATA *>(actorBaseAddr);
	//actorData.newDevilAura = baseAddr;
}




void EnterDevilForm(byte8 * baseAddr)
{
	LogFunction(baseAddr);


	if (!baseAddr)
	{
		return;
	}

	//auto & actorData = *reinterpret_cast<byte8 **>(baseAddr);

	auto & actorData = *reinterpret_cast<ACTOR_DATA *>(baseAddr);




	//func_1F94D0(actorData, 1);











}

void LeaveDevilForm(byte8 * baseAddr)
{
	LogFunction(baseAddr);

	if (!baseAddr)
	{
		return;
	}
	auto & actorData = *reinterpret_cast<ACTOR_DATA *>(baseAddr);
	//if (!actorData.newDevilAura)
	//{
	//	return;
	//}


	if (!devilAuras[0])
	{
		return;
	}

	
	
	auto & actorBaseAddr = *reinterpret_cast<byte8 **>(devilAuras[0] + 0xC0);

	Log("actorBaseAddr %llX", actorBaseAddr);

	//actorBaseAddr = actorData;





	Log("PopFirst");

	devilAuras.PopFirst();










	//auto & actorBaseAddr = *reinterpret_cast<byte8 **>(actorData.newDevilAura + 0xC0);









	//actorData.newDevilAura = 0;

















	//func_1F94D0(actorData, 2);
}
































void ToggleBodyPartDataRelocation(bool enable)
{
	LogFunction(enable);
	// 0x6950
	{
		static_assert(offsetof(ACTOR_DATA, bodyPartData[0][LOWER_BODY]) == 0x6950);
		constexpr auto off = offsetof(ACTOR_DATA, bodyPartData[0][LOWER_BODY]);
		constexpr auto newOff = offsetof(ACTOR_DATA, newBodyPartData[0][LOWER_BODY]);
		Write<uint32>((appBaseAddr + 0x1313BE + 3), (enable) ? newOff : off); // dmc3.exe+1313BE - 49 89 86 50690000 - MOV [R14+00006950],RAX
		Write<uint32>((appBaseAddr + 0x1DDD63 + 3), (enable) ? newOff : off); // dmc3.exe+1DDD63 - 48 8D 8E 50690000 - LEA RCX,[RSI+00006950]
		Write<uint32>((appBaseAddr + 0x1DE2F4 + 3), (enable) ? newOff : off); // dmc3.exe+1DE2F4 - 48 8D 8F 50690000 - LEA RCX,[RDI+00006950]
		Write<uint32>((appBaseAddr + 0x1EF4CE + 3), (enable) ? newOff : off); // dmc3.exe+1EF4CE - 49 8D 8D 50690000 - LEA RCX,[R13+00006950]
		Write<uint32>((appBaseAddr + 0x1EF90E + 3), (enable) ? newOff : off); // dmc3.exe+1EF90E - 48 8D 8B 50690000 - LEA RCX,[RBX+00006950]
		Write<uint32>((appBaseAddr + 0x1EF947 + 3), (enable) ? newOff : off); // dmc3.exe+1EF947 - 48 81 C1 50690000 - ADD RCX,00006950
		Write<uint32>((appBaseAddr + 0x1EFAC0 + 3), (enable) ? newOff : off); // dmc3.exe+1EFAC0 - 48 81 C1 50690000 - ADD RCX,00006950
		Write<uint32>((appBaseAddr + 0x1EFADE + 3), (enable) ? newOff : off); // dmc3.exe+1EFADE - 48 8D 8B 50690000 - LEA RCX,[RBX+00006950]
		Write<uint32>((appBaseAddr + 0x1EFB0E + 3), (enable) ? newOff : off); // dmc3.exe+1EFB0E - 48 81 C3 50690000 - ADD RBX,00006950
		Write<uint32>((appBaseAddr + 0x1EFC62 + 3), (enable) ? newOff : off); // dmc3.exe+1EFC62 - 48 81 C1 50690000 - ADD RCX,00006950
		Write<uint32>((appBaseAddr + 0x1EFD36 + 3), (enable) ? newOff : off); // dmc3.exe+1EFD36 - 48 81 C1 50690000 - ADD RCX,00006950
		Write<uint32>((appBaseAddr + 0x1EFFFE + 3), (enable) ? newOff : off); // dmc3.exe+1EFFFE - 48 81 C1 50690000 - ADD RCX,00006950
		Write<uint32>((appBaseAddr + 0x1F0052 + 3), (enable) ? newOff : off); // dmc3.exe+1F0052 - 48 81 C1 50690000 - ADD RCX,00006950
		Write<uint32>((appBaseAddr + 0x1F0446 + 3), (enable) ? newOff : off); // dmc3.exe+1F0446 - 48 81 C1 50690000 - ADD RCX,00006950
		Write<uint32>((appBaseAddr + 0x1F906A + 3), (enable) ? newOff : off); // dmc3.exe+1F906A - 48 81 C1 50690000 - ADD RCX,00006950
		Write<uint32>((appBaseAddr + 0x1F9080 + 3), (enable) ? newOff : off); // dmc3.exe+1F9080 - 48 8D 97 50690000 - LEA RDX,[RDI+00006950]
		Write<uint32>((appBaseAddr + 0x27B424 + 2), (enable) ? newOff : off); // dmc3.exe+27B424 - 88 83 50690000 - MOV [RBX+00006950],AL
		Write<uint32>((appBaseAddr + 0x27BF20 + 3), (enable) ? newOff : off); // dmc3.exe+27BF20 - 66 C7 81 50690000 0000 - MOV WORD PTR [RCX+00006950],0000
		Write<uint32>((appBaseAddr + 0x27C044 + 3), (enable) ? newOff : off); // dmc3.exe+27C044 - 66 C7 81 50690000 0101 - MOV WORD PTR [RCX+00006950],0101
		Write<uint32>((appBaseAddr + 0x27F355 + 2), (enable) ? newOff : off); // dmc3.exe+27F355 - 80 BB 50690000 00 - CMP BYTE PTR [RBX+00006950],00
		Write<uint32>((appBaseAddr + 0x34B9F4 + 3), (enable) ? newOff : off); // dmc3.exe+34B9F4 - 48 81 C1 50690000 - ADD RCX,00006950
	}
	// 0x6A70
	{
		static_assert(offsetof(ACTOR_DATA, bodyPartData[0][UPPER_BODY]) == 0x6A70);
		constexpr auto off = offsetof(ACTOR_DATA, bodyPartData[0][UPPER_BODY]);
		constexpr auto newOff = offsetof(ACTOR_DATA, newBodyPartData[0][UPPER_BODY]);
		Write<uint32>((appBaseAddr + 0xB9C7C + 3), (enable) ? newOff : off); // dmc3.exe+B9C7C - 4C 8D B7 706A0000 - LEA R14,[RDI+00006A70]
		Write<uint32>((appBaseAddr + 0xCA512 + 3), (enable) ? newOff : off); // dmc3.exe+CA512 - 48 8D 8E 706A0000 - LEA RCX,[RSI+00006A70]
		Write<uint32>((appBaseAddr + 0xCA62B + 3), (enable) ? newOff : off); // dmc3.exe+CA62B - 48 8D 8E 706A0000 - LEA RCX,[RSI+00006A70]
		Write<uint32>((appBaseAddr + 0xCA97E + 3), (enable) ? newOff : off); // dmc3.exe+CA97E - 48 8D 8D 706A0000 - LEA RCX,[RBP+00006A70]
		Write<uint32>((appBaseAddr + 0x1EF477 + 3), (enable) ? newOff : off); // dmc3.exe+1EF477 - 49 8D 8D 706A0000 - LEA RCX,[R13+00006A70]
		Write<uint32>((appBaseAddr + 0x1EF8F0 + 3), (enable) ? newOff : off); // dmc3.exe+1EF8F0 - 48 81 C1 706A0000 - ADD RCX,00006A70
		Write<uint32>((appBaseAddr + 0x1EF969 + 3), (enable) ? newOff : off); // dmc3.exe+1EF969 - 48 81 C3 706A0000 - ADD RBX,00006A70
		Write<uint32>((appBaseAddr + 0x1EFB40 + 3), (enable) ? newOff : off); // dmc3.exe+1EFB40 - 48 81 C1 706A0000 - ADD RCX,00006A70
		Write<uint32>((appBaseAddr + 0x1EFB6B + 3), (enable) ? newOff : off); // dmc3.exe+1EFB6B - 48 8D 8B 706A0000 - LEA RCX,[RBX+00006A70]
		Write<uint32>((appBaseAddr + 0x1EFC24 + 3), (enable) ? newOff : off); // dmc3.exe+1EFC24 - 48 81 C1 706A0000 - ADD RCX,00006A70
		Write<uint32>((appBaseAddr + 0x1F0102 + 3), (enable) ? newOff : off); // dmc3.exe+1F0102 - 48 81 C1 706A0000 - ADD RCX,00006A70
		Write<uint32>((appBaseAddr + 0x1F0211 + 3), (enable) ? newOff : off); // dmc3.exe+1F0211 - 48 81 C1 706A0000 - ADD RCX,00006A70
		Write<uint32>((appBaseAddr + 0x1F025C + 3), (enable) ? newOff : off); // dmc3.exe+1F025C - 48 81 C1 706A0000 - ADD RCX,00006A70
		Write<uint32>((appBaseAddr + 0x1F02A5 + 3), (enable) ? newOff : off); // dmc3.exe+1F02A5 - 48 81 C1 706A0000 - ADD RCX,00006A70
		Write<uint32>((appBaseAddr + 0x1F030D + 3), (enable) ? newOff : off); // dmc3.exe+1F030D - 48 81 C1 706A0000 - ADD RCX,00006A70
		Write<uint32>((appBaseAddr + 0x1F0331 + 3), (enable) ? newOff : off); // dmc3.exe+1F0331 - 48 81 C1 706A0000 - ADD RCX,00006A70
		Write<uint32>((appBaseAddr + 0x1F035B + 3), (enable) ? newOff : off); // dmc3.exe+1F035B - 48 81 C1 706A0000 - ADD RCX,00006A70
		Write<uint32>((appBaseAddr + 0x1F0385 + 3), (enable) ? newOff : off); // dmc3.exe+1F0385 - 48 81 C1 706A0000 - ADD RCX,00006A70
		Write<uint32>((appBaseAddr + 0x1F03B7 + 3), (enable) ? newOff : off); // dmc3.exe+1F03B7 - 48 81 C1 706A0000 - ADD RCX,00006A70
		Write<uint32>((appBaseAddr + 0x1F903D + 3), (enable) ? newOff : off); // dmc3.exe+1F903D - 48 81 C1 706A0000 - ADD RCX,00006A70
	}
	// 0x6B90
	{
		static_assert(offsetof(ACTOR_DATA, bodyPartData[1][LOWER_BODY]) == 0x6B90);
		constexpr auto off = offsetof(ACTOR_DATA, bodyPartData[1][LOWER_BODY]);
		constexpr auto newOff = offsetof(ACTOR_DATA, newBodyPartData[1][LOWER_BODY]);
		Write<uint32>((appBaseAddr + 0x1EF3AE + 3), (enable) ? newOff : off); // dmc3.exe+1EF3AE - 49 8D 8D 906B0000 - LEA RCX,[R13+00006B90]
	}
	// 0x6CB0
	{
		static_assert(offsetof(ACTOR_DATA, bodyPartData[1][UPPER_BODY]) == 0x6CB0);
		constexpr auto off = offsetof(ACTOR_DATA, bodyPartData[1][UPPER_BODY]);
		constexpr auto newOff = offsetof(ACTOR_DATA, newBodyPartData[1][UPPER_BODY]);
		Write<uint32>((appBaseAddr + 0x1EF357 + 3), (enable) ? newOff : off); // dmc3.exe+1EF357 - 49 8D 8D B06C0000 - LEA RCX,[R13+00006CB0]
	}
	// 0x6DD0
	{
		static_assert(offsetof(ACTOR_DATA, bodyPartData[2][LOWER_BODY]) == 0x6DD0);
		constexpr auto off = offsetof(ACTOR_DATA, bodyPartData[2][LOWER_BODY]);
		constexpr auto newOff = offsetof(ACTOR_DATA, newBodyPartData[2][LOWER_BODY]);
		Write<uint32>((appBaseAddr + 0x1EF282 + 3), (enable) ? newOff : off); // dmc3.exe+1EF282 - 49 8D 8D D06D0000 - LEA RCX,[R13+00006DD0]
	}
	// 0x6EF0
	{
		static_assert(offsetof(ACTOR_DATA, bodyPartData[2][UPPER_BODY]) == 0x6EF0);
		constexpr auto off = offsetof(ACTOR_DATA, bodyPartData[2][UPPER_BODY]);
		constexpr auto newOff = offsetof(ACTOR_DATA, newBodyPartData[2][UPPER_BODY]);
		Write<uint32>((appBaseAddr + 0x1EF22B + 3), (enable) ? newOff : off); // dmc3.exe+1EF22B - 49 8D 8D F06E0000 - LEA RCX,[R13+00006EF0]
	}
	// 0x7010
	{
		static_assert(offsetof(ACTOR_DATA, bodyPartData[3][LOWER_BODY]) == 0x7010);
		constexpr auto off = offsetof(ACTOR_DATA, bodyPartData[3][LOWER_BODY]);
		constexpr auto newOff = offsetof(ACTOR_DATA, newBodyPartData[6][LOWER_BODY]);
		Write<uint32>((appBaseAddr + 0x1DDD8C + 3), (enable) ? newOff : off); // dmc3.exe+1DDD8C - 48 8D 8E 10700000 - LEA RCX,[RSI+00007010]
		Write<uint32>((appBaseAddr + 0x1DE2D5 + 3), (enable) ? newOff : off); // dmc3.exe+1DE2D5 - 48 8D 8F 10700000 - LEA RCX,[RDI+00007010]
		Write<uint32>((appBaseAddr + 0x1EF13D + 3), (enable) ? newOff : off); // dmc3.exe+1EF13D - 49 8D 8D 10700000 - LEA RCX,[R13+00007010]
		Write<uint32>((appBaseAddr + 0x1EF177 + 3), (enable) ? newOff : off); // dmc3.exe+1EF177 - 49 8D 8D 10700000 - LEA RCX,[R13+00007010]
		Write<uint32>((appBaseAddr + 0x1EF9BE + 3), (enable) ? newOff : off); // dmc3.exe+1EF9BE - 48 8D 8F 10700000 - LEA RCX,[RDI+00007010]
		Write<uint32>((appBaseAddr + 0x1EFA0E + 3), (enable) ? newOff : off); // dmc3.exe+1EFA0E - 48 8D 8F 10700000 - LEA RCX,[RDI+00007010]
		Write<uint32>((appBaseAddr + 0x1EFA1F + 3), (enable) ? newOff : off); // dmc3.exe+1EFA1F - 48 8D 8F 10700000 - LEA RCX,[RDI+00007010]
		Write<uint32>((appBaseAddr + 0x1EFE44 + 3), (enable) ? newOff : off); // dmc3.exe+1EFE44 - 49 8D 8E 10700000 - LEA RCX,[R14+00007010]
		Write<uint32>((appBaseAddr + 0x1EFED0 + 3), (enable) ? newOff : off); // dmc3.exe+1EFED0 - 48 8D 8B 10700000 - LEA RCX,[RBX+00007010]
		Write<uint32>((appBaseAddr + 0x34BA25 + 3), (enable) ? newOff : off); // dmc3.exe+34BA25 - 48 81 C1 10700000 - ADD RCX,00007010
	}
	// 0x7130
	{
		static_assert(offsetof(ACTOR_DATA, bodyPartData[3][UPPER_BODY]) == 0x7130);
		constexpr auto off = offsetof(ACTOR_DATA, bodyPartData[3][UPPER_BODY]);
		constexpr auto newOff = offsetof(ACTOR_DATA, newBodyPartData[6][UPPER_BODY]);
		Write<uint32>((appBaseAddr + 0x1EF0FE + 3), (enable) ? newOff : off); // dmc3.exe+1EF0FE - 49 8D 8D 30710000 - LEA RCX,[R13+00007130]
		Write<uint32>((appBaseAddr + 0x1EF169 + 3), (enable) ? newOff : off); // dmc3.exe+1EF169 - 49 8D 8D 30710000 - LEA RCX,[R13+00007130]
		Write<uint32>((appBaseAddr + 0x1EF9AD + 3), (enable) ? newOff : off); // dmc3.exe+1EF9AD - 48 8D 8F 30710000 - LEA RCX,[RDI+00007130]
		Write<uint32>((appBaseAddr + 0x1EF9CA + 3), (enable) ? newOff : off); // dmc3.exe+1EF9CA - 48 8D 8F 30710000 - LEA RCX,[RDI+00007130]
		Write<uint32>((appBaseAddr + 0x1EFA6E + 3), (enable) ? newOff : off); // dmc3.exe+1EFA6E - 48 8D 8F 30710000 - LEA RCX,[RDI+00007130]
		Write<uint32>((appBaseAddr + 0x1EFA7F + 3), (enable) ? newOff : off); // dmc3.exe+1EFA7F - 48 8D 8F 30710000 - LEA RCX,[RDI+00007130]
		Write<uint32>((appBaseAddr + 0x1EFDE0 + 3), (enable) ? newOff : off); // dmc3.exe+1EFDE0 - 49 8D 8E 30710000 - LEA RCX,[R14+00007130]
		Write<uint32>((appBaseAddr + 0x1EFF60 + 3), (enable) ? newOff : off); // dmc3.exe+1EFF60 - 48 8D 8B 30710000 - LEA RCX,[RBX+00007130]
	}
}

void ToggleSubmodelDataRelocation(bool enable)
{
	LogFunction(enable);
	// 0x7540
	{
		static_assert(offsetof(ACTOR_DATA, submodelData[0]) == 0x7540);
		constexpr auto off = offsetof(ACTOR_DATA, submodelData[0]);
		constexpr auto newOff = offsetof(ACTOR_DATA, newSubmodelData[0]);
		Write<uint32>((appBaseAddr + 0x17644B + 3), (enable) ? newOff : off); // dmc3.exe+17644B - 48 8D 8E 40750000 - LEA RCX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x176BF2 + 3), (enable) ? newOff : off); // dmc3.exe+176BF2 - 48 8D 8E 40750000 - LEA RCX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x180756 + 3), (enable) ? newOff : off); // dmc3.exe+180756 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x180ABD + 3), (enable) ? newOff : off); // dmc3.exe+180ABD - 48 8D 8F 40750000 - LEA RCX,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x1832F7 + 3), (enable) ? newOff : off); // dmc3.exe+1832F7 - 4C 8D B6 40750000 - LEA R14,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x185127 + 3), (enable) ? newOff : off); // dmc3.exe+185127 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x18566D + 3), (enable) ? newOff : off); // dmc3.exe+18566D - 48 8D 8F 40750000 - LEA RCX,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x1869EE + 3), (enable) ? newOff : off); // dmc3.exe+1869EE - 4C 8D BF 40750000 - LEA R15,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x186A63 + 3), (enable) ? newOff : off); // dmc3.exe+186A63 - 4C 8D BF 40750000 - LEA R15,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x186DC8 + 3), (enable) ? newOff : off); // dmc3.exe+186DC8 - 48 8D AF 40750000 - LEA RBP,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x186E43 + 3), (enable) ? newOff : off); // dmc3.exe+186E43 - 48 8D AF 40750000 - LEA RBP,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x1DD4D2 + 3), (enable) ? newOff : off); // dmc3.exe+1DD4D2 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x1DD642 + 3), (enable) ? newOff : off); // dmc3.exe+1DD642 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x1DD7F2 + 3), (enable) ? newOff : off); // dmc3.exe+1DD7F2 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x1DD9A2 + 3), (enable) ? newOff : off); // dmc3.exe+1DD9A2 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x1DDF1E + 3), (enable) ? newOff : off); // dmc3.exe+1DDF1E - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x1DDFF0 + 3), (enable) ? newOff : off); // dmc3.exe+1DDFF0 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x1DE126 + 3), (enable) ? newOff : off); // dmc3.exe+1DE126 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x1DE24C + 3), (enable) ? newOff : off); // dmc3.exe+1DE24C - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x1DE6F9 + 1), (enable) ? newOff : off); // dmc3.exe+1DE6F9 - BA 40750000 - MOV EDX,00007540
		Write<uint32>((appBaseAddr + 0x211F4D + 3), (enable) ? newOff : off); // dmc3.exe+211F4D - 4C 8D B9 40750000 - LEA R15,[RCX+00007540]
		Write<uint32>((appBaseAddr + 0x211F68 + 3), (enable) ? newOff : off); // dmc3.exe+211F68 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x21209D + 3), (enable) ? newOff : off); // dmc3.exe+21209D - 48 8D 96 40750000 - LEA RDX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x2120CB + 3), (enable) ? newOff : off); // dmc3.exe+2120CB - 48 8D 8E 40750000 - LEA RCX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x2120D2 + 3), (enable) ? newOff : off); // dmc3.exe+2120D2 - 48 8B 86 40750000 - MOV RAX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x212176 + 3), (enable) ? newOff : off); // dmc3.exe+212176 - 48 8D 96 40750000 - LEA RDX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x2121E7 + 3), (enable) ? newOff : off); // dmc3.exe+2121E7 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x212258 + 3), (enable) ? newOff : off); // dmc3.exe+212258 - 48 8D 96 40750000 - LEA RDX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x2122C9 + 3), (enable) ? newOff : off); // dmc3.exe+2122C9 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x212326 + 3), (enable) ? newOff : off); // dmc3.exe+212326 - 48 8D 96 40750000 - LEA RDX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x212397 + 3), (enable) ? newOff : off); // dmc3.exe+212397 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x212408 + 3), (enable) ? newOff : off); // dmc3.exe+212408 - 48 8D 96 40750000 - LEA RDX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x212479 + 3), (enable) ? newOff : off); // dmc3.exe+212479 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x2124EA + 3), (enable) ? newOff : off); // dmc3.exe+2124EA - 48 8D 96 40750000 - LEA RDX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x21255B + 3), (enable) ? newOff : off); // dmc3.exe+21255B - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x2125B5 + 3), (enable) ? newOff : off); // dmc3.exe+2125B5 - 48 8D 96 40750000 - LEA RDX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x212626 + 3), (enable) ? newOff : off); // dmc3.exe+212626 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x2126BD + 3), (enable) ? newOff : off); // dmc3.exe+2126BD - 48 8D 96 40750000 - LEA RDX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x21272E + 3), (enable) ? newOff : off); // dmc3.exe+21272E - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x2132C5 + 3), (enable) ? newOff : off); // dmc3.exe+2132C5 - 49 81 C4 40750000 - ADD R12,00007540
		Write<uint32>((appBaseAddr + 0x2136BF + 3), (enable) ? newOff : off); // dmc3.exe+2136BF - 49 81 C4 40750000 - ADD R12,00007540
		Write<uint32>((appBaseAddr + 0x213ACD + 3), (enable) ? newOff : off); // dmc3.exe+213ACD - 49 81 C4 40750000 - ADD R12,00007540
		Write<uint32>((appBaseAddr + 0x213D57 + 3), (enable) ? newOff : off); // dmc3.exe+213D57 - 49 81 C4 40750000 - ADD R12,00007540
		Write<uint32>((appBaseAddr + 0x21424F + 3), (enable) ? newOff : off); // dmc3.exe+21424F - 49 81 C4 40750000 - ADD R12,00007540
		Write<uint32>((appBaseAddr + 0x21463A + 3), (enable) ? newOff : off); // dmc3.exe+21463A - 49 81 C4 40750000 - ADD R12,00007540
		Write<uint32>((appBaseAddr + 0x2148B6 + 3), (enable) ? newOff : off); // dmc3.exe+2148B6 - 49 81 C4 40750000 - ADD R12,00007540
		Write<uint32>((appBaseAddr + 0x214FAB + 3), (enable) ? newOff : off); // dmc3.exe+214FAB - 4D 8D AE 40750000 - LEA R13,[R14+00007540]
		Write<uint32>((appBaseAddr + 0x2152A1 + 3), (enable) ? newOff : off); // dmc3.exe+2152A1 - 49 8D B6 40750000 - LEA RSI,[R14+00007540]
		Write<uint32>((appBaseAddr + 0x21557C + 3), (enable) ? newOff : off); // dmc3.exe+21557C - 48 81 C7 40750000 - ADD RDI,00007540
		Write<uint32>((appBaseAddr + 0x2166B2 + 3), (enable) ? newOff : off); // dmc3.exe+2166B2 - 48 8D 97 40750000 - LEA RDX,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x2166EC + 3), (enable) ? newOff : off); // dmc3.exe+2166EC - 48 8D 97 40750000 - LEA RDX,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x21675C + 3), (enable) ? newOff : off); // dmc3.exe+21675C - 48 8D 97 40750000 - LEA RDX,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x2167CC + 3), (enable) ? newOff : off); // dmc3.exe+2167CC - 48 8D 97 40750000 - LEA RDX,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x21683C + 3), (enable) ? newOff : off); // dmc3.exe+21683C - 48 8D 97 40750000 - LEA RDX,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x2168AC + 3), (enable) ? newOff : off); // dmc3.exe+2168AC - 48 8D 97 40750000 - LEA RDX,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x21691C + 3), (enable) ? newOff : off); // dmc3.exe+21691C - 48 8D 97 40750000 - LEA RDX,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x21698C + 3), (enable) ? newOff : off); // dmc3.exe+21698C - 48 8D 97 40750000 - LEA RDX,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x2189F2 + 3), (enable) ? newOff : off); // dmc3.exe+2189F2 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x218A55 + 3), (enable) ? newOff : off); // dmc3.exe+218A55 - 48 8D 8F 40750000 - LEA RCX,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x218A8B + 3), (enable) ? newOff : off); // dmc3.exe+218A8B - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x218AD9 + 3), (enable) ? newOff : off); // dmc3.exe+218AD9 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x218B21 + 3), (enable) ? newOff : off); // dmc3.exe+218B21 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x218B8C + 3), (enable) ? newOff : off); // dmc3.exe+218B8C - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x218BD4 + 3), (enable) ? newOff : off); // dmc3.exe+218BD4 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x218C22 + 3), (enable) ? newOff : off); // dmc3.exe+218C22 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x218C6A + 3), (enable) ? newOff : off); // dmc3.exe+218C6A - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x218CB8 + 3), (enable) ? newOff : off); // dmc3.exe+218CB8 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x218D00 + 3), (enable) ? newOff : off); // dmc3.exe+218D00 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x218D68 + 3), (enable) ? newOff : off); // dmc3.exe+218D68 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x218DB0 + 3), (enable) ? newOff : off); // dmc3.exe+218DB0 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x218DFE + 3), (enable) ? newOff : off); // dmc3.exe+218DFE - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x218E46 + 3), (enable) ? newOff : off); // dmc3.exe+218E46 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x218ED5 + 3), (enable) ? newOff : off); // dmc3.exe+218ED5 - 48 8D 9F 40750000 - LEA RBX,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x218F3F + 3), (enable) ? newOff : off); // dmc3.exe+218F3F - 48 8D 9F 40750000 - LEA RBX,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x21914B + 3), (enable) ? newOff : off); // dmc3.exe+21914B - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x2191FE + 3), (enable) ? newOff : off); // dmc3.exe+2191FE - 48 8D 97 40750000 - LEA RDX,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x219211 + 3), (enable) ? newOff : off); // dmc3.exe+219211 - 48 8D 8F 40750000 - LEA RCX,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x219218 + 3), (enable) ? newOff : off); // dmc3.exe+219218 - 48 8B 87 40750000 - MOV RAX,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x2193C2 + 3), (enable) ? newOff : off); // dmc3.exe+2193C2 - 48 8D B5 40750000 - LEA RSI,[RBP+00007540]
		Write<uint32>((appBaseAddr + 0x219A76 + 3), (enable) ? newOff : off); // dmc3.exe+219A76 - 48 8D B1 40750000 - LEA RSI,[RCX+00007540]
		Write<uint32>((appBaseAddr + 0x219BFC + 3), (enable) ? newOff : off); // dmc3.exe+219BFC - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x2203D7 + 3), (enable) ? newOff : off); // dmc3.exe+2203D7 - 4C 8D B9 40750000 - LEA R15,[RCX+00007540]
		Write<uint32>((appBaseAddr + 0x2203F0 + 3), (enable) ? newOff : off); // dmc3.exe+2203F0 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x2204E2 + 3), (enable) ? newOff : off); // dmc3.exe+2204E2 - 48 8D 91 40750000 - LEA RDX,[RCX+00007540]
		Write<uint32>((appBaseAddr + 0x22050D + 3), (enable) ? newOff : off); // dmc3.exe+22050D - 48 8D 8E 40750000 - LEA RCX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x220514 + 3), (enable) ? newOff : off); // dmc3.exe+220514 - 48 8B 86 40750000 - MOV RAX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x220580 + 3), (enable) ? newOff : off); // dmc3.exe+220580 - 48 8D 96 40750000 - LEA RDX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x2205E0 + 3), (enable) ? newOff : off); // dmc3.exe+2205E0 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x22062F + 3), (enable) ? newOff : off); // dmc3.exe+22062F - 48 8D 96 40750000 - LEA RDX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x220691 + 3), (enable) ? newOff : off); // dmc3.exe+220691 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x2206F9 + 3), (enable) ? newOff : off); // dmc3.exe+2206F9 - 48 8D 96 40750000 - LEA RDX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x22076B + 3), (enable) ? newOff : off); // dmc3.exe+22076B - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x220810 + 3), (enable) ? newOff : off); // dmc3.exe+220810 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x220888 + 3), (enable) ? newOff : off); // dmc3.exe+220888 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x220F35 + 3), (enable) ? newOff : off); // dmc3.exe+220F35 - 49 81 C6 40750000 - ADD R14,00007540
		Write<uint32>((appBaseAddr + 0x2212C8 + 3), (enable) ? newOff : off); // dmc3.exe+2212C8 - 49 81 C6 40750000 - ADD R14,00007540
		Write<uint32>((appBaseAddr + 0x2216C3 + 3), (enable) ? newOff : off); // dmc3.exe+2216C3 - 49 81 C6 40750000 - ADD R14,00007540
		Write<uint32>((appBaseAddr + 0x22195B + 3), (enable) ? newOff : off); // dmc3.exe+22195B - 49 81 C6 40750000 - ADD R14,00007540
		Write<uint32>((appBaseAddr + 0x221BC4 + 4), (enable) ? newOff : off); // dmc3.exe+221BC4 - 4D 8D B4 24 40750000 - LEA R14,[R12+00007540]
		Write<uint32>((appBaseAddr + 0x22221B + 3), (enable) ? newOff : off); // dmc3.exe+22221B - 4C 8D AD 40750000 - LEA R13,[RBP+00007540]
		Write<uint32>((appBaseAddr + 0x222449 + 3), (enable) ? newOff : off); // dmc3.exe+222449 - 4C 8D AD 40750000 - LEA R13,[RBP+00007540]
		Write<uint32>((appBaseAddr + 0x222702 + 3), (enable) ? newOff : off); // dmc3.exe+222702 - 48 8D B5 40750000 - LEA RSI,[RBP+00007540]
		Write<uint32>((appBaseAddr + 0x222861 + 3), (enable) ? newOff : off); // dmc3.exe+222861 - 48 8D B7 40750000 - LEA RSI,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x22306F + 3), (enable) ? newOff : off); // dmc3.exe+22306F - 48 8D 91 40750000 - LEA RDX,[RCX+00007540]
		Write<uint32>((appBaseAddr + 0x2230B8 + 3), (enable) ? newOff : off); // dmc3.exe+2230B8 - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x2230E7 + 3), (enable) ? newOff : off); // dmc3.exe+2230E7 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x2230EE + 3), (enable) ? newOff : off); // dmc3.exe+2230EE - 48 8B 83 40750000 - MOV RAX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x22314B + 3), (enable) ? newOff : off); // dmc3.exe+22314B - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x2231BC + 3), (enable) ? newOff : off); // dmc3.exe+2231BC - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x223217 + 3), (enable) ? newOff : off); // dmc3.exe+223217 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x223276 + 3), (enable) ? newOff : off); // dmc3.exe+223276 - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x2232C4 + 3), (enable) ? newOff : off); // dmc3.exe+2232C4 - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x223329 + 3), (enable) ? newOff : off); // dmc3.exe+223329 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x22338D + 3), (enable) ? newOff : off); // dmc3.exe+22338D - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x2233E5 + 3), (enable) ? newOff : off); // dmc3.exe+2233E5 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x223780 + 3), (enable) ? newOff : off); // dmc3.exe+223780 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x2237DF + 3), (enable) ? newOff : off); // dmc3.exe+2237DF - 48 8D B1 40750000 - LEA RSI,[RCX+00007540]
		Write<uint32>((appBaseAddr + 0x2238C3 + 3), (enable) ? newOff : off); // dmc3.exe+2238C3 - 48 8D B5 40750000 - LEA RSI,[RBP+00007540]
		Write<uint32>((appBaseAddr + 0x223919 + 3), (enable) ? newOff : off); // dmc3.exe+223919 - 48 8D B5 40750000 - LEA RSI,[RBP+00007540]
		Write<uint32>((appBaseAddr + 0x22397A + 3), (enable) ? newOff : off); // dmc3.exe+22397A - 48 8D B5 40750000 - LEA RSI,[RBP+00007540]
		Write<uint32>((appBaseAddr + 0x2239DF + 3), (enable) ? newOff : off); // dmc3.exe+2239DF - 48 8D B5 40750000 - LEA RSI,[RBP+00007540]
		Write<uint32>((appBaseAddr + 0x223A46 + 3), (enable) ? newOff : off); // dmc3.exe+223A46 - 48 8D B5 40750000 - LEA RSI,[RBP+00007540]
		Write<uint32>((appBaseAddr + 0x2243CA + 3), (enable) ? newOff : off); // dmc3.exe+2243CA - 48 8D BB 40750000 - LEA RDI,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x2244D7 + 3), (enable) ? newOff : off); // dmc3.exe+2244D7 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x22451B + 3), (enable) ? newOff : off); // dmc3.exe+22451B - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x22456E + 3), (enable) ? newOff : off); // dmc3.exe+22456E - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x2245B2 + 3), (enable) ? newOff : off); // dmc3.exe+2245B2 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x2245F9 + 3), (enable) ? newOff : off); // dmc3.exe+2245F9 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x22463F + 3), (enable) ? newOff : off); // dmc3.exe+22463F - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x22468B + 3), (enable) ? newOff : off); // dmc3.exe+22468B - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x2246D1 + 3), (enable) ? newOff : off); // dmc3.exe+2246D1 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x22472C + 3), (enable) ? newOff : off); // dmc3.exe+22472C - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x224770 + 3), (enable) ? newOff : off); // dmc3.exe+224770 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x2259A0 + 3), (enable) ? newOff : off); // dmc3.exe+2259A0 - 48 8D B1 40750000 - LEA RSI,[RCX+00007540]
		Write<uint32>((appBaseAddr + 0x2259AF + 3), (enable) ? newOff : off); // dmc3.exe+2259AF - 48 8D 8D 40750000 - LEA RCX,[RBP+00007540]
		Write<uint32>((appBaseAddr + 0x225A4E + 3), (enable) ? newOff : off); // dmc3.exe+225A4E - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x225A78 + 3), (enable) ? newOff : off); // dmc3.exe+225A78 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x225A7F + 3), (enable) ? newOff : off); // dmc3.exe+225A7F - 48 8B 83 40750000 - MOV RAX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x225AEE + 3), (enable) ? newOff : off); // dmc3.exe+225AEE - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x225B50 + 3), (enable) ? newOff : off); // dmc3.exe+225B50 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x225BB8 + 3), (enable) ? newOff : off); // dmc3.exe+225BB8 - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x225C2A + 3), (enable) ? newOff : off); // dmc3.exe+225C2A - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x225CCF + 3), (enable) ? newOff : off); // dmc3.exe+225CCF - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x225D3B + 3), (enable) ? newOff : off); // dmc3.exe+225D3B - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x2260CA + 3), (enable) ? newOff : off); // dmc3.exe+2260CA - 49 8D B6 40750000 - LEA RSI,[R14+00007540]
		Write<uint32>((appBaseAddr + 0x22648D + 3), (enable) ? newOff : off); // dmc3.exe+22648D - 48 81 C7 40750000 - ADD RDI,00007540
		Write<uint32>((appBaseAddr + 0x22669C + 3), (enable) ? newOff : off); // dmc3.exe+22669C - 48 81 C7 40750000 - ADD RDI,00007540
		Write<uint32>((appBaseAddr + 0x2268A2 + 3), (enable) ? newOff : off); // dmc3.exe+2268A2 - 48 81 C7 40750000 - ADD RDI,00007540
		Write<uint32>((appBaseAddr + 0x226A03 + 3), (enable) ? newOff : off); // dmc3.exe+226A03 - 48 81 C7 40750000 - ADD RDI,00007540
		Write<uint32>((appBaseAddr + 0x226C92 + 3), (enable) ? newOff : off); // dmc3.exe+226C92 - 49 8D 8E 40750000 - LEA RCX,[R14+00007540]
		Write<uint32>((appBaseAddr + 0x226D9F + 3), (enable) ? newOff : off); // dmc3.exe+226D9F - 48 8D 91 40750000 - LEA RDX,[RCX+00007540]
		Write<uint32>((appBaseAddr + 0x226DE9 + 3), (enable) ? newOff : off); // dmc3.exe+226DE9 - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x226E56 + 3), (enable) ? newOff : off); // dmc3.exe+226E56 - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x226EC3 + 3), (enable) ? newOff : off); // dmc3.exe+226EC3 - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x2272D8 + 3), (enable) ? newOff : off); // dmc3.exe+2272D8 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x227370 + 3), (enable) ? newOff : off); // dmc3.exe+227370 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x2273A8 + 3), (enable) ? newOff : off); // dmc3.exe+2273A8 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x34A49B + 3), (enable) ? newOff : off); // dmc3.exe+34A49B - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x34B399 + 3), (enable) ? newOff : off); // dmc3.exe+34B399 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x34B4A9 + 3), (enable) ? newOff : off); // dmc3.exe+34B4A9 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x34B549 + 3), (enable) ? newOff : off); // dmc3.exe+34B549 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x34B6B9 + 3), (enable) ? newOff : off); // dmc3.exe+34B6B9 - 48 81 C1 40750000 - ADD RCX,00007540
		//Write<uint32>((appBaseAddr + 0x598B58 + 3), (enable) ? newOff : off); // dmc3.exe+598B58 - D1 15 00007540 - RCL [40CE7F5E],1
	}
	// 0x7CC0
	{
		static_assert(offsetof(ACTOR_DATA, submodelData[1]) == 0x7CC0);
		constexpr auto off = offsetof(ACTOR_DATA, submodelData[1]);
		constexpr auto newOff = offsetof(ACTOR_DATA, newSubmodelData[1]);
		Write<uint32>((appBaseAddr + 0x176458 + 3), (enable) ? newOff : off); // dmc3.exe+176458 - 48 8D 8E C07C0000 - LEA RCX,[RSI+00007CC0]
		Write<uint32>((appBaseAddr + 0x176BE5 + 3), (enable) ? newOff : off); // dmc3.exe+176BE5 - 48 8D 8E C07C0000 - LEA RCX,[RSI+00007CC0]
		Write<uint32>((appBaseAddr + 0x21913F + 2), (enable) ? newOff : off); // dmc3.exe+21913F - 80 B9 C07C0000 00 - CMP BYTE PTR [RCX+00007CC0],00
		Write<uint32>((appBaseAddr + 0x21915B + 2), (enable) ? newOff : off); // dmc3.exe+21915B - C6 87 C07C0000 00 - MOV BYTE PTR [RDI+00007CC0],00
		Write<uint32>((appBaseAddr + 0x21927C + 2), (enable) ? newOff : off); // dmc3.exe+21927C - C6 81 C07C0000 00 - MOV BYTE PTR [RCX+00007CC0],00
		Write<uint32>((appBaseAddr + 0x2193F7 + 2), (enable) ? newOff : off); // dmc3.exe+2193F7 - C6 85 C07C0000 01 - MOV BYTE PTR [RBP+00007CC0],01
		Write<uint32>((appBaseAddr + 0x34A4AE + 3), (enable) ? newOff : off); // dmc3.exe+34A4AE - 48 81 C1 C07C0000 - ADD RCX,00007CC0
	}
	// 0x8440
	{
		static_assert(offsetof(ACTOR_DATA, submodelData[2]) == 0x8440);
		constexpr auto off = offsetof(ACTOR_DATA, submodelData[2]);
		constexpr auto newOff = offsetof(ACTOR_DATA, newSubmodelData[2]);
		Write<uint32>((appBaseAddr + 0xB5F18 + 4), (enable) ? newOff : off); // dmc3.exe+B5F18 - 49 8D 94 24 40840000 - LEA RDX,[R12+00008440]
		Write<uint32>((appBaseAddr + 0x176465 + 3), (enable) ? newOff : off); // dmc3.exe+176465 - 48 8D 8E 40840000 - LEA RCX,[RSI+00008440]
		Write<uint32>((appBaseAddr + 0x176BD8 + 3), (enable) ? newOff : off); // dmc3.exe+176BD8 - 48 8D 8E 40840000 - LEA RCX,[RSI+00008440]
		Write<uint32>((appBaseAddr + 0x180773 + 3), (enable) ? newOff : off); // dmc3.exe+180773 - 48 8D 8B 40840000 - LEA RCX,[RBX+00008440]
		Write<uint32>((appBaseAddr + 0x18392C + 3), (enable) ? newOff : off); // dmc3.exe+18392C - 48 8B BE 40840000 - MOV RDI,[RSI+00008440]
		Write<uint32>((appBaseAddr + 0x183939 + 3), (enable) ? newOff : off); // dmc3.exe+183939 - 48 8D 8E 40840000 - LEA RCX,[RSI+00008440]
		Write<uint32>((appBaseAddr + 0x184529 + 3), (enable) ? newOff : off); // dmc3.exe+184529 - 48 8B BE 40840000 - MOV RDI,[RSI+00008440]
		Write<uint32>((appBaseAddr + 0x184536 + 3), (enable) ? newOff : off); // dmc3.exe+184536 - 48 8D 8E 40840000 - LEA RCX,[RSI+00008440]
		Write<uint32>((appBaseAddr + 0x186EC7 + 3), (enable) ? newOff : off); // dmc3.exe+186EC7 - 48 8D 8F 40840000 - LEA RCX,[RDI+00008440]
		Write<uint32>((appBaseAddr + 0x1870B7 + 3), (enable) ? newOff : off); // dmc3.exe+1870B7 - 48 8D 8F 40840000 - LEA RCX,[RDI+00008440]
		Write<uint32>((appBaseAddr + 0x34A4C1 + 3), (enable) ? newOff : off); // dmc3.exe+34A4C1 - 48 81 C1 40840000 - ADD RCX,00008440
		// Write<uint32>((appBaseAddr + 0x589CFE + 3), (enable) ? newOff : off); // dmc3.exe+589CFE - 8C BF 00008440 - MOV [RDI+40840000],IS
		// Write<uint32>((appBaseAddr + 0x589D22 + 3), (enable) ? newOff : off); // dmc3.exe+589D22 - C0 BF 00008440 00 - SAR BYTE PTR [RDI+40840000],00
		// Write<uint32>((appBaseAddr + 0x589D46 + 3), (enable) ? newOff : off); // dmc3.exe+589D46 - C0 BF 00008440 00 - SAR BYTE PTR [RDI+40840000],00
		// Write<uint32>((appBaseAddr + 0x589D6A + 3), (enable) ? newOff : off); // dmc3.exe+589D6A - C0 BF 00008440 00 - SAR BYTE PTR [RDI+40840000],00
		// Write<uint32>((appBaseAddr + 0x58F6DE + 3), (enable) ? newOff : off); // dmc3.exe+58F6DE - 8C BF 00008440 - MOV [RDI+40840000],IS
		// Write<uint32>((appBaseAddr + 0x58F702 + 3), (enable) ? newOff : off); // dmc3.exe+58F702 - C0 BF 00008440 00 - SAR BYTE PTR [RDI+40840000],00
		// Write<uint32>((appBaseAddr + 0x58F726 + 3), (enable) ? newOff : off); // dmc3.exe+58F726 - C0 BF 00008440 00 - SAR BYTE PTR [RDI+40840000],00
		// Write<uint32>((appBaseAddr + 0x58F74A + 3), (enable) ? newOff : off); // dmc3.exe+58F74A - C0 BF 00008440 00 - SAR BYTE PTR [RDI+40840000],00
		// Write<uint32>((appBaseAddr + 0x591AEE + 3), (enable) ? newOff : off); // dmc3.exe+591AEE - 8C BF 00008440 - MOV [RDI+40840000],IS
		// Write<uint32>((appBaseAddr + 0x591B12 + 3), (enable) ? newOff : off); // dmc3.exe+591B12 - C0 BF 00008440 00 - SAR BYTE PTR [RDI+40840000],00
		// Write<uint32>((appBaseAddr + 0x591B36 + 3), (enable) ? newOff : off); // dmc3.exe+591B36 - C0 BF 00008440 00 - SAR BYTE PTR [RDI+40840000],00
		// Write<uint32>((appBaseAddr + 0x591B5A + 3), (enable) ? newOff : off); // dmc3.exe+591B5A - C0 BF 00008440 00 - SAR BYTE PTR [RDI+40840000],00
	}
	// 0x8BC0
	{
		static_assert(offsetof(ACTOR_DATA, submodelData[3]) == 0x8BC0);
		constexpr auto off = offsetof(ACTOR_DATA, submodelData[3]);
		constexpr auto newOff = offsetof(ACTOR_DATA, newSubmodelData[3]);
		Write<uint32>((appBaseAddr + 0x1764E7 + 3), (enable) ? newOff : off); // dmc3.exe+1764E7 - 48 8D 9E C08B0000 - LEA RBX,[RSI+00008BC0]
		Write<uint32>((appBaseAddr + 0x176B5C + 3), (enable) ? newOff : off); // dmc3.exe+176B5C - 48 89 AE C08B0000 - MOV [RSI+00008BC0],RBP
		Write<uint32>((appBaseAddr + 0x184F89 + 2), (enable) ? newOff : off); // dmc3.exe+184F89 - C7 83 C08B0000 00002041 - MOV [RBX+00008BC0],41200000
		Write<uint32>((appBaseAddr + 0x34A58B + 3), (enable) ? newOff : off); // dmc3.exe+34A58B - 48 81 C1 C08B0000 - ADD RCX,00008BC0
	}
}





void ToggleModelShadowDataRelocation(bool enable)
{
	LogFunction(enable);
	// 0x9AD0
	{
		static_assert(offsetof(ACTOR_DATA, modelShadowData[0]) == 0x9AD0);
		constexpr auto off = offsetof(ACTOR_DATA, modelShadowData[0]);
		constexpr auto newOff = offsetof(ACTOR_DATA, newModelShadowData[0]);
		Write<uint32>((appBaseAddr + 0x18278E + 3), (enable) ? newOff : off); // dmc3.exe+18278E - 0F29 85 D09A0000 - MOVAPS [RBP+00009AD0],XMM0
		Write<uint32>((appBaseAddr + 0x1DD4FD + 3), (enable) ? newOff : off); // dmc3.exe+1DD4FD - 48 8D 8B D09A0000 - LEA RCX,[RBX+00009AD0]
		Write<uint32>((appBaseAddr + 0x1DDEFF + 3), (enable) ? newOff : off); // dmc3.exe+1DDEFF - 48 8D 8B D09A0000 - LEA RCX,[RBX+00009AD0]
		Write<uint32>((appBaseAddr + 0x211FC7 + 3), (enable) ? newOff : off); // dmc3.exe+211FC7 - 48 8D B3 D09A0000 - LEA RSI,[RBX+00009AD0]
		Write<uint32>((appBaseAddr + 0x211FF8 + 3), (enable) ? newOff : off); // dmc3.exe+211FF8 - 48 81 C1 D09A0000 - ADD RCX,00009AD0
		Write<uint32>((appBaseAddr + 0x213262 + 4), (enable) ? newOff : off); // dmc3.exe+213262 - 48 8B BC 33 D09A0000 - MOV RDI,[RBX+RSI+00009AD0]
		Write<uint32>((appBaseAddr + 0x21326D + 3), (enable) ? newOff : off); // dmc3.exe+21326D - 48 8D 8E D09A0000 - LEA RCX,[RSI+00009AD0]
		Write<uint32>((appBaseAddr + 0x21365C + 4), (enable) ? newOff : off); // dmc3.exe+21365C - 48 8B BC 33 D09A0000 - MOV RDI,[RBX+RSI+00009AD0]
		Write<uint32>((appBaseAddr + 0x213667 + 3), (enable) ? newOff : off); // dmc3.exe+213667 - 48 8D 8E D09A0000 - LEA RCX,[RSI+00009AD0]
		Write<uint32>((appBaseAddr + 0x213A6A + 4), (enable) ? newOff : off); // dmc3.exe+213A6A - 48 8B BC 33 D09A0000 - MOV RDI,[RBX+RSI+00009AD0]
		Write<uint32>((appBaseAddr + 0x213A75 + 3), (enable) ? newOff : off); // dmc3.exe+213A75 - 48 8D 8E D09A0000 - LEA RCX,[RSI+00009AD0]
		Write<uint32>((appBaseAddr + 0x2140CD + 4), (enable) ? newOff : off); // dmc3.exe+2140CD - 48 8B BC 33 D09A0000 - MOV RDI,[RBX+RSI+00009AD0]
		Write<uint32>((appBaseAddr + 0x2140DD + 3), (enable) ? newOff : off); // dmc3.exe+2140DD - 48 8D 8E D09A0000 - LEA RCX,[RSI+00009AD0]
		Write<uint32>((appBaseAddr + 0x2141ED + 4), (enable) ? newOff : off); // dmc3.exe+2141ED - 48 8B BC 33 D09A0000 - MOV RDI,[RBX+RSI+00009AD0]
		Write<uint32>((appBaseAddr + 0x2141F8 + 3), (enable) ? newOff : off); // dmc3.exe+2141F8 - 48 8D 8E D09A0000 - LEA RCX,[RSI+00009AD0]
		Write<uint32>((appBaseAddr + 0x2145DC + 4), (enable) ? newOff : off); // dmc3.exe+2145DC - 48 8B BC 33 D09A0000 - MOV RDI,[RBX+RSI+00009AD0]
		Write<uint32>((appBaseAddr + 0x2145E7 + 3), (enable) ? newOff : off); // dmc3.exe+2145E7 - 48 8D 8E D09A0000 - LEA RCX,[RSI+00009AD0]
		Write<uint32>((appBaseAddr + 0x214DED + 3), (enable) ? newOff : off); // dmc3.exe+214DED - 49 8B BE D09A0000 - MOV RDI,[R14+00009AD0]
		Write<uint32>((appBaseAddr + 0x214DFA + 3), (enable) ? newOff : off); // dmc3.exe+214DFA - 49 8D 8E D09A0000 - LEA RCX,[R14+00009AD0]
		Write<uint32>((appBaseAddr + 0x218999 + 3), (enable) ? newOff : off); // dmc3.exe+218999 - 48 81 C1 D09A0000 - ADD RCX,00009AD0
		Write<uint32>((appBaseAddr + 0x218EAC + 3), (enable) ? newOff : off); // dmc3.exe+218EAC - 48 8D 8F D09A0000 - LEA RCX,[RDI+00009AD0]
		Write<uint32>((appBaseAddr + 0x220CCF + 4), (enable) ? newOff : off); // dmc3.exe+220CCF - 4D 89 B4 24 D09A0000 - MOV [R12+00009AD0],R14
		Write<uint32>((appBaseAddr + 0x22631F + 3), (enable) ? newOff : off); // dmc3.exe+22631F - 49 89 B6 D09A0000 - MOV [R14+00009AD0],RSI
		Write<uint32>((appBaseAddr + 0x34B3CA + 3), (enable) ? newOff : off); // dmc3.exe+34B3CA - 48 81 C1 D09A0000 - ADD RCX,00009AD0
	}
	// 0x9B90
	{
		static_assert(offsetof(ACTOR_DATA, modelShadowData[1]) == 0x9B90);
		constexpr auto off = offsetof(ACTOR_DATA, modelShadowData[1]);
		constexpr auto newOff = offsetof(ACTOR_DATA, newModelShadowData[1]);
		Write<uint32>((appBaseAddr + 0xFD855 + 3), (enable) ? newOff : off); // dmc3.exe+FD855 - 4C 8D 9E 909B0000 - LEA R11,[RSI+00009B90]
		Write<uint32>((appBaseAddr + 0xFFF7C + 3), (enable) ? newOff : off); // dmc3.exe+FFF7C - 0F29 81 909B0000 - MOVAPS [RCX+00009B90],XMM0
	}
	// 0x9C50
	{
		static_assert(offsetof(ACTOR_DATA, modelShadowData[2]) == 0x9C50);
		constexpr auto off = offsetof(ACTOR_DATA, modelShadowData[2]);
		constexpr auto newOff = offsetof(ACTOR_DATA, newModelShadowData[2]);
		Write<uint32>((appBaseAddr + 0xF8521 + 2), (enable) ? newOff : off); // dmc3.exe+F8521 - C7 81 509C0000 00000000 - MOV [RCX+00009C50],00000000
		Write<uint32>((appBaseAddr + 0xFC18D + 2), (enable) ? newOff : off); // dmc3.exe+FC18D - 89 AB 509C0000 - MOV [RBX+00009C50],EBP
		Write<uint32>((appBaseAddr + 0xFCF75 + 3), (enable) ? newOff : off); // dmc3.exe+FCF75 - 45 89 BE 509C0000 - MOV [R14+00009C50],R15D
		Write<uint32>((appBaseAddr + 0xFFE95 + 2), (enable) ? newOff : off); // dmc3.exe+FFE95 - C7 87 509C0000 00000000 - MOV [RDI+00009C50],00000000
		Write<uint32>((appBaseAddr + 0x100652 + 3), (enable) ? newOff : off); // dmc3.exe+100652 - 44 38 B7 509C0000 - CMP [RDI+00009C50],R14L
		Write<uint32>((appBaseAddr + 0x100665 + 2), (enable) ? newOff : off); // dmc3.exe+100665 - C6 87 509C0000 01 - MOV BYTE PTR [RDI+00009C50],01
		Write<uint32>((appBaseAddr + 0x1007C2 + 3), (enable) ? newOff : off); // dmc3.exe+1007C2 - 44 89 B7 509C0000 - MOV [RDI+00009C50],R14D
	}
}
















export void Model_Init()
{
	LogFunction();



	//if (!devilAuras.Init(512))
	//{
	//	Log("devilAuras.Init failed.");
	//	return;
	//}



	ToggleBodyPartDataRelocation(true);
	ToggleSubmodelDataRelocation(true);
	ToggleModelShadowDataRelocation(true);

	//ToggleExpansion(true);
	//ToggleSubmodelRelocation(true);


	//{
	//	constexpr byte8 sect1[] =
	//	{
	//		mov_rcx_rsi,
	//	};
	//	auto func = CreateFunction(UpdateDevilModelDante, (appBaseAddr + 0x21344F), true, true, 0, sizeof(sect1));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	//WriteJump((appBaseAddr + 0x213167), func.addr, 2);
	//}

	// Force Only Rebellion
	//WriteJump((appBaseAddr + 0x214B29), (appBaseAddr + 0x21344F));


	//return;





	{
		auto func = CreateFunction(UpdateModelDante);
		WriteCall((appBaseAddr + 0x212CB3), func.addr);
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
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x21557C), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ACTOR_DATA, newForceFiles);
		WriteCall((func.sect0 + 9), (appBaseAddr + 0x2169F0));
		WriteJump((appBaseAddr + 0x215577), func.addr);
		/*
		dmc3.exe+215577 - E8 74140000       - call dmc3.exe+2169F0
		dmc3.exe+21557C - 48 81 C7 40750000 - add rdi,00007540
		*/
	}


	// Vergil Model Parition Updates
	{
		constexpr byte8 sect0[] =
		{
			0x80, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x01, // cmp byte ptr [rcx+0000B8C0],01
			0x74, 0x05,                               // je short
			0xE8, 0x00, 0x00, 0x00, 0x00,             // call dmc3.exe+223420
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x222861), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ACTOR_DATA, newForceFiles);
		WriteCall((func.sect0 + 9), (appBaseAddr + 0x223420));
		WriteJump((appBaseAddr + 0x22285C), func.addr);
		/*
		dmc3.exe+22285C - E8 BF0B0000       - call dmc3.exe+223420
		dmc3.exe+222861 - 48 8D B7 40750000 - lea rsi,[rdi+00007540]
		*/
	}

	// Ebony Ivory Position Update
	{
		constexpr byte8 sect0[] =
		{
			0x0F, 0xB6, 0x90, 0x9E, 0x3E, 0x00, 0x00, // movzx edx,byte ptr [rax+00003E9E]
			0x80, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x01, // cmp byte ptr [rax+0000B8C0],01
			0x0F, 0x84, 0x00, 0x00, 0x00, 0x00,       // je dmc3.exe+22B7E2
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x22B616), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint32 *>(func.sect0 + 9) = offsetof(ACTOR_DATA, newForceFiles);
		WriteAddress((func.sect0 + 0xE), (appBaseAddr + 0x22B7E2), 6);
		WriteJump((appBaseAddr + 0x22B60F), func.addr, 2);
		/*
		dmc3.exe+22B60F - 0FB6 90 9E3E0000 - movzx edx,byte ptr [rax+00003E9E]
		dmc3.exe+22B616 - 8D 42 FD         - lea eax,[rdx-03]
		*/
	}


	// Dante Coat Update
	{
		constexpr byte8 sect0[] =
		{
			0x80, 0xBE, 0x00, 0x00, 0x00, 0x00, 0x01, // cmp byte ptr [rsi+0000B8C0],01
			0x75, 0x12,                               // jne short
			0x80, 0xBE, 0x00, 0x00, 0x00, 0x00, 0x00, // cmp byte ptr [rsi+0000B8C0],02
			0x75, 0x09,                               // jne short
			0x48, 0x8B, 0x96, 0xA8, 0x18, 0x00, 0x00, // mov rdx,[rsi+000018A8]
			0xEB, 0x07,                               // jmp short
			0x48, 0x8B, 0x96, 0x98, 0x18, 0x00, 0x00, // mov rdx,[rsi+00001898]
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x2120CB), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ACTOR_DATA, newForceFiles);
		*reinterpret_cast<uint32 *>(func.sect0 + 0xB) = offsetof(ACTOR_DATA, newForceFilesCharacter);
		*reinterpret_cast<uint8 *>(func.sect0 + 0xF) = CHAR_LADY;
		WriteJump((appBaseAddr + 0x2120C4), func.addr, 2);
		/*
		dmc3.exe+2120C4 - 48 8B 96 98180000 - mov rdx,[rsi+00001898]
		dmc3.exe+2120CB - 48 8D 8E 40750000 - lea rcx,[rsi+00007540]
		*/
	}























	//// Devil Coat Update
	//{
	//	constexpr byte8 sect0[] =
	//	{
	//		0x80, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x01, // cmp byte ptr [rcx+0000B8C0],01
	//		0x75, 0x01,                               // jne short
	//		0xC3,                                     // ret
	//		0x40, 0x57,                               // push rdi
	//		0x48, 0x83, 0xEC, 0x30,                   // sub rsp,30
	//	};
	//	auto func = CreateFunction(0, (appBaseAddr + 0x216686), false, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ACTOR_DATA, newForceFiles);
	//	//WriteJump((appBaseAddr + 0x216680), func.addr, 1);
	//	/*
	//	dmc3.exe+216680 - 40 57       - push rdi
	//	dmc3.exe+216682 - 48 83 EC 30 - sub rsp,30
	//	dmc3.exe+216686 - 48 8B F9    - mov rdi,rcx
	//	*/
	//}





	//// Dante Coat Position Update
	//{
	//	constexpr byte8 sect0[] =
	//	{
	//		0x80, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x01, // cmp byte ptr [rcx+0000B8C0],01
	//		0x74, 0x16,                               // je short
	//		0x80, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x01, // cmp byte ptr [rcx+0000B8C0],01
	//		0x75, 0x0D,                               // jne short
	//		0x80, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, // cmp byte ptr [rcx+0000B8C0],02
	//		0x0F, 0x84, 0x00, 0x00, 0x00, 0x00,       // je dmc3.exe+2191D0
	//		0x40, 0x56,                               // push rsi
	//		0x48, 0x83, 0xEC, 0x20,                   // sub rsp,20
	//	};
	//	auto func = CreateFunction(0, (appBaseAddr + 0x212076), false, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ACTOR_DATA, devil);
	//	*reinterpret_cast<uint32 *>(func.sect0 + 0xB) = offsetof(ACTOR_DATA, newForceFiles);
	//	*reinterpret_cast<uint32 *>(func.sect0 + 0x14) = offsetof(ACTOR_DATA, newForceFilesCharacter);
	//	*reinterpret_cast<uint8 *>(func.sect0 + 0x18) = CHAR_LADY;
	//	WriteAddress((func.sect0 + 0x19), (appBaseAddr + 0x2191D0), 6);
	//	//WriteJump((appBaseAddr + 0x212070), func.addr, 1);
	//	/*
	//	dmc3.exe+212070 - 40 56             - push rsi
	//	dmc3.exe+212072 - 48 83 EC 20       - sub rsp,20
	//	dmc3.exe+212076 - 48 63 81 6C3E0000 - movsxd  rax,dword ptr [rcx+00003E6C]
	//	*/
	//}
























	
	//// Dante Coat Position Update
	//{
	//	constexpr byte8 sect0[] =
	//	{
	//		0x80, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x01, // cmp byte ptr [rcx+0000B8C0],01
	//		0x75, 0x0E,                               // jne short
	//		0x80, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, // cmp byte ptr [rcx+0000B8C0],02
	//		0x75, 0x05,                               // jne short
	//		0xE9, 0x00, 0x00, 0x00, 0x00,             // jmp dmc3.exe+2191D0
	//		0x40, 0x56,                               // push rsi
	//		0x48, 0x83, 0xEC, 0x20,                   // sub rsp,20
	//	};
	//	auto func = CreateFunction(0, (appBaseAddr + 0x212076), false, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ACTOR_DATA, newForceFiles);
	//	*reinterpret_cast<uint32 *>(func.sect0 + 0xB) = offsetof(ACTOR_DATA, newForceFilesCharacter);
	//	*reinterpret_cast<uint8 *>(func.sect0 + 0xF) = CHAR_LADY;
	//	WriteJump((func.sect0 + 0x12), (appBaseAddr + 0x2191D0));



	//	//WriteJump((appBaseAddr + 0x212070), func.addr, 1);




	//	/*
	//	dmc3.exe+212070 - 40 56             - push rsi
	//	dmc3.exe+212072 - 48 83 EC 20       - sub rsp,20
	//	dmc3.exe+212076 - 48 63 81 6C3E0000 - movsxd  rax,dword ptr [rcx+00003E6C]
	//	*/
	//}






	//// Dante 7540 Position Update
	//{
	//	constexpr byte8 sect0[] =
	//	{
	//		0x80, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x01, // cmp byte ptr [rcx+0000B8C0],01
	//		0x0F, 0x84, 0x00, 0x00, 0x00, 0x00,       // je dmc3.exe+2191D0
	//		0x40, 0x56,                               // push rsi
	//		0x48, 0x83, 0xEC, 0x20,                   // sub rsp,20
	//	};
	//	auto func = CreateFunction(0, (appBaseAddr + 0x212076), false, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ACTOR_DATA, newForceLadyFiles);
	//	WriteAddress((func.sect0 + 7), (appBaseAddr + 0x2191D0), 6);
	//	WriteJump((appBaseAddr + 0x212070), func.addr, 1);
	//	/*
	//	dmc3.exe+212070 - 40 56             - push rsi
	//	dmc3.exe+212072 - 48 83 EC 20       - sub rsp,20
	//	dmc3.exe+212076 - 48 63 81 6C3E0000 - movsxd  rax,dword ptr [rcx+00003E6C]
	//	*/
	//}




	// Create Devil Aura
	//{
	//	constexpr byte8 sect0[] =
	//	{
	//		0x48, 0x8B, 0x83, 0xC0, 0x00, 0x00, 0x00, // mov rax,[rbx+000000C0]
	//		0x48, 0x85, 0xC0,                         // test rax,rax
	//		0x74, 0x03,                               // je short
	//		0x48, 0x8B, 0xC8,                         // mov rcx,rax
	//		0xE8, 0x00, 0x00, 0x00, 0x00,             // call dmc3.exe+1FAA90
	//	};
	//	constexpr byte8 sect1[] =
	//	{
	//		mov_rcx_rbx,
	//	};
	//	auto func = CreateFunction(CreateDevilAura, (appBaseAddr + 0x8E45C), true, true, sizeof(sect0), sizeof(sect1));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	WriteCall((func.sect0 + 0xF), (appBaseAddr + 0x1FAA90));
	//	WriteJump((appBaseAddr + 0x8E457), func.addr);
	//	/*
	//	dmc3.exe+8E457 - E8 34C61600 - call dmc3.exe+1FAA90
	//	dmc3.exe+8E45C - 48 8B D0    - mov rdx,rax
	//	*/
	//}





	// Enter Devil Form
	//{
	//	constexpr byte8 sect0[] =
	//	{
	//		0xC6, 0x87, 0x9B, 0x3E, 0x00, 0x00, 0x01, // mov byte ptr [rdi+00003E9B],01
	//	};
	//	constexpr byte8 sect1[] =
	//	{
	//		mov_rcx_rdi,
	//	};
	//	auto func = CreateFunction(EnterDevilForm, (appBaseAddr + 0x1E7810), true, true, sizeof(sect0), sizeof(sect1));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	WriteJump((appBaseAddr + 0x1E7809), func.addr, 2);
	//	/*
	//	dmc3.exe+1E7809 - C6 87 9B3E0000 01 - mov byte ptr [rdi+00003E9B],01
	//	dmc3.exe+1E7810 - 89 74 24 30       - mov [rsp+30],esi
	//	*/
	//}


	// Leave Devil Form
	//{
	//	constexpr byte8 sect0[] =
	//	{
	//		0x40, 0x88, 0xB7, 0x9B, 0x3E, 0x00, 0x00, // mov [rdi+00003E9B],sil
	//	};
	//	constexpr byte8 sect1[] =
	//	{
	//		mov_rcx_rdi,
	//	};
	//	auto func = CreateFunction(LeaveDevilForm, (appBaseAddr + 0x1E78C6), true, true, sizeof(sect0), sizeof(sect1));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	WriteJump((appBaseAddr + 0x1E78BF), func.addr, 2);
	//	/*
	//	dmc3.exe+1E78BF - 40 88 B7 9B3E0000 - mov [rdi+00003E9B],sil
	//	dmc3.exe+1E78C6 - 48 8B CF          - mov rcx,rdi
	//	*/
	//}








	// On
	{
		constexpr byte8 sect0[] =
		{
			0x48, 0x8B, 0x83, 0xC0, 0x00, 0x00, 0x00, // mov rax,[rbx+000000C0]
			0x48, 0x85, 0xC0,                         // test rax,rax
			0x74, 0x09,                               // je short
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
			0xEB, 0x07,                               // jmp short
			0x8B, 0x84, 0x96, 0xC0, 0x2D, 0xC9, 0x00, // mov eax,[rsi+rdx*4+00C92DC0]
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x8DC23), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint32 *>(func.sect0 + 0xF) = offsetof(ACTOR_DATA, newEffectIndices);
		WriteJump((appBaseAddr + 0x8DC1C), func.addr, 2);
		/*
		dmc3.exe+8DC1C - 8B 84 96 C02DC900 - mov eax,[rsi+rdx*4+00C92DC0]
		dmc3.exe+8DC23 - 0FA3 C8           - bt eax,ecx
		*/
	}



	// Update
	{
		constexpr byte8 sect0[] =
		{
			0x48, 0x8B, 0x87, 0xC0, 0x00, 0x00, 0x00,       // mov rax,[rdi+000000C0]
			0x48, 0x85, 0xC0,                               // test rax,rax
			0x74, 0x09,                                     // je short
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00,       // mov eax,[rax+rdx*4+0000B8C0]
			0xEB, 0x08,                                     // jmp short
			0x41, 0x8B, 0x84, 0x91, 0xC0, 0x2D, 0xC9, 0x00, // mov eax,[r9+rdx*4+00C92DC0]
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x90D29), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint32 *>(func.sect0 + 0xF) = offsetof(ACTOR_DATA, newEffectIndices);
		WriteJump((appBaseAddr + 0x90D21), func.addr, 3);
		/*
		dmc3.exe+90D21 - 41 8B 84 91 C02DC900 - mov eax,[r9+rdx*4+00C92DC0]
		dmc3.exe+90D29 - 0FA3 C8              - bt eax,ecx
		*/
	}





	// Off
	{
		constexpr byte8 sect0[] =
		{
			0x8B, 0x83, 0x00, 0x00, 0x00, 0x00, // mov eax,[rbx+0000B8C0]
			0x8B, 0x8B, 0x00, 0x00, 0x00, 0x00, // mov ecx,[rbx+0000B8C0]
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x1F954E), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ACTOR_DATA, newEffectIndices[1]);
		*reinterpret_cast<uint32 *>(func.sect0 + 8) = offsetof(ACTOR_DATA, newEffectIndices[2]);
		WriteJump((appBaseAddr + 0x1F9542), func.addr, 1);
		/*
		dmc3.exe+1F9542 - 8B 05 7C98A900 - mov eax,[dmc3.exe+C92DC4]
		dmc3.exe+1F9548 - 8B 0D 7A98A900 - mov ecx,[dmc3.exe+C92DC8]
		dmc3.exe+1F954E - 83 C8 01       - or eax,01
		*/
	}





	{
		constexpr byte8 sect0[] =
		{
			0x89, 0x83, 0x00, 0x00, 0x00, 0x00, // mov [rbx+0000B8C0],eax
			0x89, 0x8B, 0x00, 0x00, 0x00, 0x00, // mov [rbx+0000B8C0],ecx
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x1F9578), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ACTOR_DATA, newEffectIndices[1]);
		*reinterpret_cast<uint32 *>(func.sect0 + 8) = offsetof(ACTOR_DATA, newEffectIndices[2]);
		WriteJump((appBaseAddr + 0x1F956C), func.addr, 1);
		/*
		dmc3.exe+1F956C - 89 05 5298A900 - mov [dmc3.exe+C92DC4],eax
		dmc3.exe+1F9572 - 89 0D 5098A900 - mov [dmc3.exe+C92DC8],ecx
		dmc3.exe+1F9578 - 48 83 C4 20    - add rsp,20
		*/
	}




	{
		constexpr byte8 sect0[] =
		{
			0xD3, 0xE0,                                     // shl eax,cl
			0x48, 0x8B, 0x8F, 0xC0, 0x00, 0x00, 0x00,       // mov rcx,[rdi+000000C0]
			0x48, 0x85, 0xC9,                               // test rcx,rcx
			0x74, 0x09,                                     // je short
			0x31, 0x84, 0x91, 0x00, 0x00, 0x00, 0x00,       // xor [rcx+rdx*4+0000B8C0],eax
			0xEB, 0x08,                                     // jmp short
			0x41, 0x31, 0x84, 0x91, 0xC0, 0x2D, 0xC9, 0x00, // xor [r9+rdx*4+00C92DC0],eax
			0x48, 0x8B, 0xCF,                               // mov rcx,rdi
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x90D57), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(ACTOR_DATA, newEffectIndices);
		WriteJump((appBaseAddr + 0x90D4A), func.addr);
		/*
		dmc3.exe+90D4A - D3 E0                - shl eax,cl
		dmc3.exe+90D4C - 48 8B CF             - mov rcx,rdi
		dmc3.exe+90D4F - 41 31 84 91 C02DC900 - xor [r9+rdx*4+00C92DC0],eax
		dmc3.exe+90D57 - 33 D2                - xor edx,edx
		*/
	}





	// Update Effect Position

	{
		constexpr byte8 sect0[] =
		{
			0x48, 0x8B, 0x87, 0xC0, 0x00, 0x00, 0x00, // mov rax,[rdi+000000C0]
			0x48, 0x85, 0xC0,                         // test rax,rax
			0x74, 0x03,                               // je short
			0x48, 0x8B, 0xC8,                         // mov rcx,rax
			0xE8, 0x00, 0x00, 0x00, 0x00,             // call dmc3.exe+1FAA90
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x90B2D), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteJump((appBaseAddr + 0x90B28), func.addr);
		WriteCall((func.sect0 + 0xF), (appBaseAddr + 0x1FAA90));
		/*
		dmc3.exe+90B28 - E8 639F1600 - call dmc3.exe+1FAA90
		dmc3.exe+90B2D - 48 8B D0    - mov rdx,rax
		*/
	}



















}






#endif
