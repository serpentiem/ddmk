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
	PhysicsMetadata ** physicsMetadata
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













































// @Todo: Add Shadow.

export void ResetModel(ModelData & modelData)
{
	//func_897B0(modelData);
	//func_89450(modelData);
	//memset(modelData, 0, sizeof(ModelData));
	//func_89270(modelData);
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
		actorData.newModelData[modelIndex],
		modelFile,
		textureFile
	);

	RegisterShadow
	(
		actorData.newModelData[modelIndex],
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
		&actorData.submodelPhysicsMetadataPool[0]
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
			actorData.newSubmodelShadowData[submodelIndex],
			shadowFile
		);
	}

	actorData.var_9AC0[submodelIndex] = true;

	RegisterPhysics
	(
		physicsFile,
		&actorData.submodelPhysicsData,
		&actorData.submodelPhysicsMetadataPool[0]
	);

	func_2CA2F0
	(
		actorData.submodelPhysicsData,
		actorData.newModelPhysicsMetadataPool[modelIndex],
		(appBaseAddr + 0x58B380),
		actorData.modelMetadata,
		(coat) ? 6 : 1
	);

	if (coat)
	{
		auto g_vertices = reinterpret_cast<vec4 *>(appBaseAddr + 0x35D580);
		auto & submodelPhysicsMetadata = *actorData.submodelPhysicsMetadataPool[0];

		submodelPhysicsMetadata.vertices[0] = g_vertices[0];
		submodelPhysicsMetadata.vertices[1] = g_vertices[1];
		submodelPhysicsMetadata.vertices[2] = g_vertices[2];
		submodelPhysicsMetadata.vertices[3] = g_vertices[3];
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


/*

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
		&actorData.newSubmodelPhysicsMetadata[0]
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
			actorData.newSubmodelShadowData[submodelIndex],
			shadowFile
		);
	}

	actorData.var_9AC0[submodelIndex] = true;

	RegisterPhysics
	(
		physicsFile,
		&actorData.newSubmodelPhysicsData[0],
		&actorData.newSubmodelPhysicsMetadata[0]
	);

	func_2CA2F0
	(
		actorData.newSubmodelPhysicsData[0],
		actorData.modelPhysicsMetadataPool[modelIndex],
		(appBaseAddr + 0x58B380),
		actorData.modelMetadata,
		(coat) ? 6 : 1
	);

	if (coat)
	{
		auto g_vertices = reinterpret_cast<vec4 *>(appBaseAddr + 0x35D580);

		actorData.newSubmodelPhysicsMetadata[0].vertices[0] = g_vertices[0];
		actorData.newSubmodelPhysicsMetadata[0].vertices[1] = g_vertices[1];
		actorData.newSubmodelPhysicsMetadata[0].vertices[2] = g_vertices[2];
		actorData.newSubmodelPhysicsMetadata[0].vertices[3] = g_vertices[3];
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

*/






export void UpdateModelDante(byte8 * baseAddr)
{
	LogFunction(baseAddr);

	auto & actorData = *reinterpret_cast<ActorDataDante *>(baseAddr);

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

























template <typename T>
void NewFunc
(
	T & actorData,
	uint32 modelIndex
)
{
	func_8A000
	(
		actorData.newModelData[modelIndex],
		actorData.motionArchives[0],
		actorData.newModelPhysicsMetadataPool[modelIndex]
	);

	actorData.newModelData[modelIndex].Motion.init = false;

	// Not sure if required, but legit.
	{
		auto dest = reinterpret_cast<byte8 *>(actorData.newModelPhysicsMetadataPool[0][(1 + modelIndex)]);
		*reinterpret_cast<RecoveryData **>(dest + 0x100) = &actorData.newRecoveryData[modelIndex];
	}

	auto & recoveryData = actorData.newRecoveryData[modelIndex];
	recoveryData.init = false;
	memset(recoveryData.data, 0, 32);

	auto file = File_staticFiles[pl000][5];

	func_594B0
	(
		actorData.newBodyPartData[modelIndex][UPPER_BODY],
		file,
		UPPER_BODY,
		0,
		actorData.motionArchives,
		&actorData.newModelData[modelIndex].functions,
		actorData.newModelPhysicsMetadataPool[modelIndex],
		&actorData.motionSpeed,
		&actorData.var_7250
	);

	func_594B0
	(
		actorData.newBodyPartData[modelIndex][LOWER_BODY],
		file,
		LOWER_BODY,
		0,
		actorData.motionArchives,
		&actorData.newModelData[modelIndex].functions,
		actorData.newModelPhysicsMetadataPool[modelIndex],
		&actorData.motionSpeed,
		0
	);

	auto dest = func_8A520(actorData.newModelData[modelIndex]);
	func_30E630(dest, 0);
}










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

	byte8 * modelFile = 0;
	byte8 * textureFile = 0;
	byte8 * shadowFile = 0;
	byte8 * physicsFile = 0;

	//uint8 modelIndex = (devilModelIndex == 0) ? 1 : 2;
	//uint8 submodelIndex = (devilModelIndex == 0) ? 1 : 3;
	//uint8 devilSubmodelIndex = (devilModelIndex == 0) ? 0 : 2;

	auto & devilModelMetadata = actorData.devilModelMetadata[devil];




	
	uint8 modelIndex = (1 + devilModelIndex);
	uint8 submodelIndex = (1 + (devilModelIndex * 2));
	uint8 devilSubmodelIndex = (devilModelIndex * 2);




	uint8 modelPhysicsMetadataIndex = 0;
	uint8 devilModelPhysicsMetadataIndex = 0;
























	auto LinkModelPhysicsData = [&]
	(
		uint8 _devilSubmodelPhysicsLinkDataIndex,
		uint8 _modelPhysicsMetadataIndex,
		uint8 _devilModelPhysicsMetadataIndex
	)
	{
		auto & devilSubmodelPhysicsLinkData = actorData.newDevilSubmodelPhysicsLinkData[devilSubmodelIndex][_devilSubmodelPhysicsLinkDataIndex];

		auto modelPhysicsMetadataAddr = actorData.newModelPhysicsMetadataPool[modelIndex][(modelPhysicsMetadataIndex + _modelPhysicsMetadataIndex)];
		if (!modelPhysicsMetadataAddr)
		{
			Log("LinkModelPhysicsData failed.");
			Log("modelPhysicsMetadataAddr");
			return;
		}
		auto & modelPhysicsMetadata = *modelPhysicsMetadataAddr;

		auto devilModelPhysicsMetadataAddr = actorData.newDevilModelPhysicsMetadataPool[devilModelIndex][(devilModelPhysicsMetadataIndex + _devilModelPhysicsMetadataIndex)];
		if (!devilModelPhysicsMetadataAddr)
		{
			Log("LinkModelPhysicsData failed.");
			Log("devilModelPhysicsMetadataAddr");
			return;
		}
		auto & devilPhysicsMetadata = *devilModelPhysicsMetadataAddr;

		devilSubmodelPhysicsLinkData.enable = 1;
		devilSubmodelPhysicsLinkData.physicsData = modelPhysicsMetadata.physicsData;
		memcpy(devilSubmodelPhysicsLinkData.data, (appBaseAddr + 0x35D580), 64);

		devilPhysicsMetadata.physicsLinkData = &devilSubmodelPhysicsLinkData;
	};

	actorData.newDevilModels[modelIndex] = devil;

	// Main

	modelFile = file[1];
	textureFile = file[0];

	if (devil == DEVIL_DANTE_AGNI_RUDRA)
	{
		shadowFile = file[2];
	}
	else if
	(
		(devil == DEVIL_DANTE_CERBERUS) ||
		(devil == DEVIL_DANTE_BEOWULF ) ||
		(devil == DEVIL_DANTE_SPARDA  )
	)
	{
		shadowFile = file[4];
	}
	else if
	(
		(devil == DEVIL_DANTE_REBELLION) ||
		(devil == DEVIL_DANTE_NEVAN    )
	)
	{
		shadowFile = file[6];
	}

	RegisterModel
	(
		actorData.newModelData[modelIndex],
		modelFile,
		textureFile
	);

	//func_1EF040
	//(
	//	actorData,
	//	modelIndex
	//);

	NewFunc
	(
		actorData,
		modelIndex
	);



	RegisterShadow
	(
		actorData.newModelData[modelIndex],
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
		&actorData.newDevilModelPhysicsMetadataPool[devilModelIndex][devilModelPhysicsMetadataIndex]
	);

	RegisterShadow
	(
		actorData.newSubmodelData[submodelIndex],
		actorData.newSubmodelShadowData[submodelIndex],
		shadowFile
	);

	actorData.var_9AC0[submodelIndex] = true;

	RegisterPhysics
	(
		physicsFile,
		&actorData.newDevilSubmodelPhysicsData[devilSubmodelIndex],
		&actorData.newDevilModelPhysicsMetadataPool[devilModelIndex][devilModelPhysicsMetadataIndex]
	);

	if
	(
		(devil == DEVIL_DANTE_REBELLION) ||
		(devil == DEVIL_DANTE_NEVAN    )
	)
	{
		LinkModelPhysicsData(0, 3, 1 );
		LinkModelPhysicsData(1, 2, 12);
	}
	else if
	(
		(devil == DEVIL_DANTE_CERBERUS) ||
		(devil == DEVIL_DANTE_BEOWULF )
	)
	{
		LinkModelPhysicsData(0, 3 , 1);
		LinkModelPhysicsData(1, 6 , 2);
		LinkModelPhysicsData(2, 10, 8);
	}

	devilModelMetadata.devilSubmodelMetadata[0].submodelIndex = submodelIndex;
	devilModelMetadata.devilSubmodelMetadata[0].devilModelPhysicsMetadataIndex = ((devilModelIndex * 36) + devilModelPhysicsMetadataIndex);
	devilModelMetadata.devilSubmodelMetadata[0].devilSubmodelIndex = devilSubmodelIndex;

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
		&actorData.newDevilModelPhysicsMetadataPool[devilModelIndex][devilModelPhysicsMetadataIndex]
	);

	RegisterShadow
	(
		actorData.newSubmodelData[submodelIndex],
		actorData.newSubmodelShadowData[submodelIndex],
		shadowFile
	);

	actorData.var_9AC0[submodelIndex] = true;

	RegisterPhysics
	(
		physicsFile,
		&actorData.newDevilSubmodelPhysicsData[devilSubmodelIndex],
		&actorData.newDevilModelPhysicsMetadataPool[devilModelIndex][devilModelPhysicsMetadataIndex]
	);

	func_2CA2F0
	(
		actorData.newDevilSubmodelPhysicsData[devilSubmodelIndex],
		actorData.newModelPhysicsMetadataPool[modelIndex],
		(appBaseAddr + 0x58B380),
		actorData.modelMetadata,
		6
	);

	LinkModelPhysicsData(0, 2 , 1);
	LinkModelPhysicsData(1, 14, 2);

	devilModelMetadata.devilSubmodelMetadata[1].submodelIndex = submodelIndex;
	devilModelMetadata.devilSubmodelMetadata[1].devilModelPhysicsMetadataIndex = ((devilModelIndex * 36) + devilModelPhysicsMetadataIndex);
	devilModelMetadata.devilSubmodelMetadata[1].devilSubmodelIndex = devilSubmodelIndex;
}




















void UpdateDevilModelDante(ActorDataDante & actorData)
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
	//auto & actorData = *reinterpret_cast<ActorData *>(actorBaseAddr);
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

	auto & actorData = *reinterpret_cast<ActorData *>(baseAddr);




	//func_1F94D0(actorData, 1);











}

void LeaveDevilForm(byte8 * baseAddr)
{
	LogFunction(baseAddr);

	if (!baseAddr)
	{
		return;
	}
	auto & actorData = *reinterpret_cast<ActorData *>(baseAddr);
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






/*
dmc3.exe+212D6A - 33 D2                 - xor edx,edx { first leak
}
dmc3.exe+212D6C - 48 8B CE              - mov rcx,rsi
dmc3.exe+212D6F - E8 CCC2FDFF           - call dmc3.exe+1EF040

*/














/*
template <typename T>
void NewFunc
(
T & actorData,
uint32 modelIndex
)
{
func_8A000
(
actorData.modelData[modelIndex],
actorData.motionArchives[0],
actorData.modelPhysicsMetadataPool[modelIndex]
);

actorData.modelData[modelIndex].Motion.init = false;

// Not sure if required, but legit.
{
auto dest = reinterpret_cast<byte8 *>(actorData.modelPhysicsMetadataPool[0][(1 + modelIndex)]);
*reinterpret_cast<RecoveryData **>(dest + 0x100) = &actorData.recoveryData[modelIndex];
}

auto & recoveryData = actorData.recoveryData[modelIndex];
recoveryData.init = false;
memset(recoveryData.data, 0, 32);

auto file = File_staticFiles[pl000][5];

func_594B0
(
actorData.bodyPartData[modelIndex][UPPER_BODY],
file,
UPPER_BODY,
0,
actorData.motionArchives,
&actorData.modelData[modelIndex].functions,
actorData.modelPhysicsMetadataPool[modelIndex],
&actorData.motionSpeed,
&actorData.var_7250
);

func_594B0
(
actorData.bodyPartData[modelIndex][LOWER_BODY],
file,
LOWER_BODY,
0,
actorData.motionArchives,
&actorData.modelData[modelIndex].functions,
actorData.modelPhysicsMetadataPool[modelIndex],
&actorData.motionSpeed,
0
);

auto dest = func_8A520(actorData.modelData[modelIndex]);
func_30E630(dest, 0);
}
*/














void ToggleRelocations(bool enable)
{
	LogFunction(enable);







	// 0x200
	{
		constexpr auto off = offsetof(ActorData, modelData[0]);
		constexpr auto newOff = offsetof(ActorData, newModelData[0]);
		static_assert(off == 0x200);
		// Write<uint32>((appBaseAddr + 0x23470 + 3), (enable) ? newOff : off); // dmc3.exe+23470 - 48 89 8B 00020000 - MOV [RBX+00000200],RCX
		// LikelyWeapon<uint32>((appBaseAddr + 0x5082D + 3), (enable) ? newOff : off); // dmc3.exe+5082D - 48 89 81 00020000 - MOV [RCX+00000200],RAX
		// Write<uint32>((appBaseAddr + 0xBADBA + 3), (enable) ? newOff : off); // dmc3.exe+BADBA - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0xC9F2B + 3), (enable) ? newOff : off); // dmc3.exe+C9F2B - 49 8D 8F 00020000 - LEA RCX,[R15+00000200]
		// Write<uint32>((appBaseAddr + 0xDB2A9 + 3), (enable) ? newOff : off); // dmc3.exe+DB2A9 - 48 8B 89 00020000 - MOV RCX,[RCX+00000200]
		// Write<uint32>((appBaseAddr + 0xDC2AB + 3), (enable) ? newOff : off); // dmc3.exe+DC2AB - 48 8B 8B 00020000 - MOV RCX,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0xFCBF7 + 3), (enable) ? newOff : off); // dmc3.exe+FCBF7 - 4C 89 BC 24 00020000 - MOV [RSP+00000200],R15
		// Write<uint32>((appBaseAddr + 0xFDB3A + 3), (enable) ? newOff : off); // dmc3.exe+FDB3A - 4C 8B BC 24 00020000 - MOV R15,[RSP+00000200]
		// Write<uint32>((appBaseAddr + 0x101747 + 3), (enable) ? newOff : off); // dmc3.exe+101747 - 4C 8D 83 00020000 - LEA R8,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x1017B5 + 3), (enable) ? newOff : off); // dmc3.exe+1017B5 - 48 8D B3 00020000 - LEA RSI,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x101905 + 3), (enable) ? newOff : off); // dmc3.exe+101905 - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x101DA6 + 3), (enable) ? newOff : off); // dmc3.exe+101DA6 - 4C 8D 83 00020000 - LEA R8,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x101E97 + 3), (enable) ? newOff : off); // dmc3.exe+101E97 - 4C 8D 8B 00020000 - LEA R9,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x101EBD + 3), (enable) ? newOff : off); // dmc3.exe+101EBD - 4C 8D 8B 00020000 - LEA R9,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x1021E7 + 3), (enable) ? newOff : off); // dmc3.exe+1021E7 - 4C 8D 83 00020000 - LEA R8,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x102544 + 3), (enable) ? newOff : off); // dmc3.exe+102544 - 48 8D B1 00020000 - LEA RSI,[RCX+00000200]
		// Write<uint32>((appBaseAddr + 0x102E9F + 3), (enable) ? newOff : off); // dmc3.exe+102E9F - 4C 8D 83 00020000 - LEA R8,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x102EE2 + 3), (enable) ? newOff : off); // dmc3.exe+102EE2 - 48 8D 91 00020000 - LEA RDX,[RCX+00000200]
		// Write<uint32>((appBaseAddr + 0x104A5F + 3), (enable) ? newOff : off); // dmc3.exe+104A5F - 4C 8D 8B 00020000 - LEA R9,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x104A99 + 3), (enable) ? newOff : off); // dmc3.exe+104A99 - 4C 8D 8B 00020000 - LEA R9,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x104AFF + 3), (enable) ? newOff : off); // dmc3.exe+104AFF - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x104C6F + 3), (enable) ? newOff : off); // dmc3.exe+104C6F - 48 8D B7 00020000 - LEA RSI,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x105025 + 3), (enable) ? newOff : off); // dmc3.exe+105025 - 48 8D B7 00020000 - LEA RSI,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x105518 + 3), (enable) ? newOff : off); // dmc3.exe+105518 - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x105A02 + 3), (enable) ? newOff : off); // dmc3.exe+105A02 - 4C 8D 8F 00020000 - LEA R9,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x105B4B + 3), (enable) ? newOff : off); // dmc3.exe+105B4B - 4C 8D 87 00020000 - LEA R8,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x10630A + 3), (enable) ? newOff : off); // dmc3.exe+10630A - 48 8D B7 00020000 - LEA RSI,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x10B6EF + 3), (enable) ? newOff : off); // dmc3.exe+10B6EF - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x11602F + 3), (enable) ? newOff : off); // dmc3.exe+11602F - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x11614E + 3), (enable) ? newOff : off); // dmc3.exe+11614E - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x116EF0 + 3), (enable) ? newOff : off); // dmc3.exe+116EF0 - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x151EA7 + 3), (enable) ? newOff : off); // dmc3.exe+151EA7 - 48 05 00020000 - ADD RAX,00000200
		// Write<uint32>((appBaseAddr + 0x15204C + 3), (enable) ? newOff : off); // dmc3.exe+15204C - 48 05 00020000 - ADD RAX,00000200
		// Write<uint32>((appBaseAddr + 0x17412C + 3), (enable) ? newOff : off); // dmc3.exe+17412C - 48 05 00020000 - ADD RAX,00000200
		// Write<uint32>((appBaseAddr + 0x174A8C + 3), (enable) ? newOff : off); // dmc3.exe+174A8C - 48 05 00020000 - ADD RAX,00000200
		// Write<uint32>((appBaseAddr + 0x174AF1 + 3), (enable) ? newOff : off); // dmc3.exe+174AF1 - 48 05 00020000 - ADD RAX,00000200
		// Write<uint32>((appBaseAddr + 0x174C27 + 3), (enable) ? newOff : off); // dmc3.exe+174C27 - 48 81 C6 00020000 - ADD RSI,00000200
		// Write<uint32>((appBaseAddr + 0x19E23F + 3), (enable) ? newOff : off); // dmc3.exe+19E23F - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x1A1B46 + 3), (enable) ? newOff : off); // dmc3.exe+1A1B46 - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x1A1EAF + 3), (enable) ? newOff : off); // dmc3.exe+1A1EAF - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x1A1ED9 + 3), (enable) ? newOff : off); // dmc3.exe+1A1ED9 - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x1A2110 + 3), (enable) ? newOff : off); // dmc3.exe+1A2110 - 4C 8D 81 00020000 - LEA R8,[RCX+00000200]
		// Write<uint32>((appBaseAddr + 0x1CE56D + 3), (enable) ? newOff : off); // dmc3.exe+1CE56D - 48 8D B7 00020000 - LEA RSI,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x1CEA98 + 3), (enable) ? newOff : off); // dmc3.exe+1CEA98 - 4C 8D 8E 00020000 - LEA R9,[RSI+00000200]
		// Write<uint32>((appBaseAddr + 0x1CEAB5 + 3), (enable) ? newOff : off); // dmc3.exe+1CEAB5 - 4C 8D 8E 00020000 - LEA R9,[RSI+00000200]
		// Write<uint32>((appBaseAddr + 0x1CEDCB + 3), (enable) ? newOff : off); // dmc3.exe+1CEDCB - 48 8D 8E 00020000 - LEA RCX,[RSI+00000200]
		// Write<uint32>((appBaseAddr + 0x1CF144 + 3), (enable) ? newOff : off); // dmc3.exe+1CF144 - 48 8D 83 00020000 - LEA RAX,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x1D0ADF + 3), (enable) ? newOff : off); // dmc3.exe+1D0ADF - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x1D0B6E + 3), (enable) ? newOff : off); // dmc3.exe+1D0B6E - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x1D0DE0 + 3), (enable) ? newOff : off); // dmc3.exe+1D0DE0 - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x1D10B7 + 3), (enable) ? newOff : off); // dmc3.exe+1D10B7 - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x1D12C3 + 3), (enable) ? newOff : off); // dmc3.exe+1D12C3 - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x1D830F + 3), (enable) ? newOff : off); // dmc3.exe+1D830F - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x1D83BA + 3), (enable) ? newOff : off); // dmc3.exe+1D83BA - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x1D868B + 3), (enable) ? newOff : off); // dmc3.exe+1D868B - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x1D869F + 3), (enable) ? newOff : off); // dmc3.exe+1D869F - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x1D86AB + 3), (enable) ? newOff : off); // dmc3.exe+1D86AB - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x1D86C4 + 3), (enable) ? newOff : off); // dmc3.exe+1D86C4 - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x1D883B + 3), (enable) ? newOff : off); // dmc3.exe+1D883B - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x1D8F04 + 3), (enable) ? newOff : off); // dmc3.exe+1D8F04 - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x1D92B5 + 3), (enable) ? newOff : off); // dmc3.exe+1D92B5 - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x1D92C9 + 3), (enable) ? newOff : off); // dmc3.exe+1D92C9 - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x1D92D5 + 3), (enable) ? newOff : off); // dmc3.exe+1D92D5 - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x1D92EE + 3), (enable) ? newOff : off); // dmc3.exe+1D92EE - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x1D93A0 + 3), (enable) ? newOff : off); // dmc3.exe+1D93A0 - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x1DDB4B + 3), (enable) ? newOff : off); // dmc3.exe+1DDB4B - 48 8D 8E 00020000 - LEA RCX,[RSI+00000200]
		Write<uint32>((appBaseAddr + 0x1DE41A + 3), (enable) ? newOff : off); // dmc3.exe+1DE41A - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x1DE764 + 3), (enable) ? newOff : off); // dmc3.exe+1DE764 - 48 8D 99 00020000 - LEA RBX,[RCX+00000200]
		Write<uint32>((appBaseAddr + 0x1DFD29 + 3), (enable) ? newOff : off); // dmc3.exe+1DFD29 - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x1EEF16 + 3), (enable) ? newOff : off); // dmc3.exe+1EEF16 - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x1EEF4D + 3), (enable) ? newOff : off); // dmc3.exe+1EEF4D - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x1EF09A + 3), (enable) ? newOff : off); // dmc3.exe+1EF09A - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x1EF3E0 + 3), (enable) ? newOff : off); // dmc3.exe+1EF3E0 - 4D 8D BD 00020000 - LEA R15,[R13+00000200]
		Write<uint32>((appBaseAddr + 0x1EF566 + 3), (enable) ? newOff : off); // dmc3.exe+1EF566 - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x1EF5CC + 3), (enable) ? newOff : off); // dmc3.exe+1EF5CC - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x1EF6DC + 3), (enable) ? newOff : off); // dmc3.exe+1EF6DC - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x1EF762 + 3), (enable) ? newOff : off); // dmc3.exe+1EF762 - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x1EF7B3 + 3), (enable) ? newOff : off); // dmc3.exe+1EF7B3 - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x1EF7F3 + 3), (enable) ? newOff : off); // dmc3.exe+1EF7F3 - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x1EF82E + 3), (enable) ? newOff : off); // dmc3.exe+1EF82E - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x1EF867 + 3), (enable) ? newOff : off); // dmc3.exe+1EF867 - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x1EF8B3 + 3), (enable) ? newOff : off); // dmc3.exe+1EF8B3 - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x1FB570 + 3), (enable) ? newOff : off); // dmc3.exe+1FB570 - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x1FB70B + 3), (enable) ? newOff : off); // dmc3.exe+1FB70B - 48 8D B3 00020000 - LEA RSI,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x1FB7C3 + 3), (enable) ? newOff : off); // dmc3.exe+1FB7C3 - 48 8D B3 00020000 - LEA RSI,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x1FB88C + 3), (enable) ? newOff : off); // dmc3.exe+1FB88C - 48 8D B3 00020000 - LEA RSI,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x1FB946 + 3), (enable) ? newOff : off); // dmc3.exe+1FB946 - 48 8D B3 00020000 - LEA RSI,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x1FB9D1 + 3), (enable) ? newOff : off); // dmc3.exe+1FB9D1 - 48 81 C3 00020000 - ADD RBX,00000200
		Write<uint32>((appBaseAddr + 0x1FC3CB + 3), (enable) ? newOff : off); // dmc3.exe+1FC3CB - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x1FC525 + 3), (enable) ? newOff : off); // dmc3.exe+1FC525 - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x1FCA34 + 3), (enable) ? newOff : off); // dmc3.exe+1FCA34 - 48 8D B1 00020000 - LEA RSI,[RCX+00000200]
		// Write<uint32>((appBaseAddr + 0x1FCB5B + 3), (enable) ? newOff : off); // dmc3.exe+1FCB5B - 4C 8D B7 00020000 - LEA R14,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x1FCBC7 + 3), (enable) ? newOff : off); // dmc3.exe+1FCBC7 - 4C 8D B7 00020000 - LEA R14,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x1FCC2D + 3), (enable) ? newOff : off); // dmc3.exe+1FCC2D - 4C 8D B7 00020000 - LEA R14,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x1FCC97 + 3), (enable) ? newOff : off); // dmc3.exe+1FCC97 - 4C 8D B7 00020000 - LEA R14,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x1FCCFC + 3), (enable) ? newOff : off); // dmc3.exe+1FCCFC - 4C 8D B7 00020000 - LEA R14,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x1FCD6A + 3), (enable) ? newOff : off); // dmc3.exe+1FCD6A - 4C 8D B7 00020000 - LEA R14,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x1FCDEC + 3), (enable) ? newOff : off); // dmc3.exe+1FCDEC - 4C 8D B7 00020000 - LEA R14,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x1FCE63 + 3), (enable) ? newOff : off); // dmc3.exe+1FCE63 - 4C 8D B7 00020000 - LEA R14,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x2005C0 + 3), (enable) ? newOff : off); // dmc3.exe+2005C0 - 48 8D 83 00020000 - LEA RAX,[RBX+00000200]
		Write<uint32>((appBaseAddr + 0x2131D9 + 3), (enable) ? newOff : off); // dmc3.exe+2131D9 - 49 81 C4 00020000 - ADD R12,00000200
		Write<uint32>((appBaseAddr + 0x2135D4 + 3), (enable) ? newOff : off); // dmc3.exe+2135D4 - 49 81 C4 00020000 - ADD R12,00000200
		Write<uint32>((appBaseAddr + 0x2139E1 + 3), (enable) ? newOff : off); // dmc3.exe+2139E1 - 49 81 C4 00020000 - ADD R12,00000200
		Write<uint32>((appBaseAddr + 0x214037 + 3), (enable) ? newOff : off); // dmc3.exe+214037 - 49 81 C4 00020000 - ADD R12,00000200
		Write<uint32>((appBaseAddr + 0x214165 + 3), (enable) ? newOff : off); // dmc3.exe+214165 - 49 81 C4 00020000 - ADD R12,00000200
		Write<uint32>((appBaseAddr + 0x214558 + 3), (enable) ? newOff : off); // dmc3.exe+214558 - 49 81 C4 00020000 - ADD R12,00000200
		Write<uint32>((appBaseAddr + 0x214BE7 + 3), (enable) ? newOff : off); // dmc3.exe+214BE7 - 48 8D 8E 00020000 - LEA RCX,[RSI+00000200]
		Write<uint32>((appBaseAddr + 0x214C00 + 3), (enable) ? newOff : off); // dmc3.exe+214C00 - 48 8D 8E 00020000 - LEA RCX,[RSI+00000200]
		Write<uint32>((appBaseAddr + 0x214C19 + 3), (enable) ? newOff : off); // dmc3.exe+214C19 - 48 8D 8E 00020000 - LEA RCX,[RSI+00000200]
		Write<uint32>((appBaseAddr + 0x214C32 + 3), (enable) ? newOff : off); // dmc3.exe+214C32 - 48 8D 8E 00020000 - LEA RCX,[RSI+00000200]
		Write<uint32>((appBaseAddr + 0x214CC2 + 3), (enable) ? newOff : off); // dmc3.exe+214CC2 - 48 8D 8E 00020000 - LEA RCX,[RSI+00000200]
		Write<uint32>((appBaseAddr + 0x214CDB + 3), (enable) ? newOff : off); // dmc3.exe+214CDB - 48 8D 8E 00020000 - LEA RCX,[RSI+00000200]
		Write<uint32>((appBaseAddr + 0x214CF4 + 3), (enable) ? newOff : off); // dmc3.exe+214CF4 - 48 8D 8E 00020000 - LEA RCX,[RSI+00000200]
		Write<uint32>((appBaseAddr + 0x214D0D + 3), (enable) ? newOff : off); // dmc3.exe+214D0D - 48 8D 8E 00020000 - LEA RCX,[RSI+00000200]
		Write<uint32>((appBaseAddr + 0x214D95 + 3), (enable) ? newOff : off); // dmc3.exe+214D95 - 49 8D B6 00020000 - LEA RSI,[R14+00000200]
		// LikelyValid<uint32>((appBaseAddr + 0x216A1E + 3), (enable) ? newOff : off); // dmc3.exe+216A1E - 48 8D 99 00020000 - LEA RBX,[RCX+00000200]
		// LikelyValid<uint32>((appBaseAddr + 0x216A55 + 3), (enable) ? newOff : off); // dmc3.exe+216A55 - 48 8D 99 00020000 - LEA RBX,[RCX+00000200]
		Write<uint32>((appBaseAddr + 0x218A2F + 3), (enable) ? newOff : off); // dmc3.exe+218A2F - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x219318 + 3), (enable) ? newOff : off); // dmc3.exe+219318 - 4C 8D A5 00020000 - LEA R12,[RBP+00000200]
		// Write<uint32>((appBaseAddr + 0x219AA1 + 3), (enable) ? newOff : off); // dmc3.exe+219AA1 - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x220E21 + 3), (enable) ? newOff : off); // dmc3.exe+220E21 - 49 81 C6 00020000 - ADD R14,00000200
		// Write<uint32>((appBaseAddr + 0x2211EB + 3), (enable) ? newOff : off); // dmc3.exe+2211EB - 49 81 C6 00020000 - ADD R14,00000200
		// Write<uint32>((appBaseAddr + 0x2215F0 + 3), (enable) ? newOff : off); // dmc3.exe+2215F0 - 49 81 C6 00020000 - ADD R14,00000200
		// Write<uint32>((appBaseAddr + 0x22202B + 3), (enable) ? newOff : off); // dmc3.exe+22202B - 4C 8D B5 00020000 - LEA R14,[RBP+00000200]
		// Write<uint32>((appBaseAddr + 0x223455 + 3), (enable) ? newOff : off); // dmc3.exe+223455 - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x22347F + 3), (enable) ? newOff : off); // dmc3.exe+22347F - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x2234A7 + 3), (enable) ? newOff : off); // dmc3.exe+2234A7 - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x2234D1 + 3), (enable) ? newOff : off); // dmc3.exe+2234D1 - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x22350F + 3), (enable) ? newOff : off); // dmc3.exe+22350F - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x223528 + 3), (enable) ? newOff : off); // dmc3.exe+223528 - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x223543 + 3), (enable) ? newOff : off); // dmc3.exe+223543 - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x22355C + 3), (enable) ? newOff : off); // dmc3.exe+22355C - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x223590 + 3), (enable) ? newOff : off); // dmc3.exe+223590 - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x2235BA + 3), (enable) ? newOff : off); // dmc3.exe+2235BA - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x2235DF + 3), (enable) ? newOff : off); // dmc3.exe+2235DF - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x2235F8 + 3), (enable) ? newOff : off); // dmc3.exe+2235F8 - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x223611 + 3), (enable) ? newOff : off); // dmc3.exe+223611 - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x22362A + 3), (enable) ? newOff : off); // dmc3.exe+22362A - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x22364D + 3), (enable) ? newOff : off); // dmc3.exe+22364D - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x223666 + 3), (enable) ? newOff : off); // dmc3.exe+223666 - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x22367F + 3), (enable) ? newOff : off); // dmc3.exe+22367F - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x223698 + 3), (enable) ? newOff : off); // dmc3.exe+223698 - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x225E61 + 3), (enable) ? newOff : off); // dmc3.exe+225E61 - 49 8D B6 00020000 - LEA RSI,[R14+00000200]
		// Write<uint32>((appBaseAddr + 0x226414 + 3), (enable) ? newOff : off); // dmc3.exe+226414 - 4C 8B 83 00020000 - MOV R8,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x22641B + 3), (enable) ? newOff : off); // dmc3.exe+22641B - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x226426 + 3), (enable) ? newOff : off); // dmc3.exe+226426 - 4C 8B 8B 00020000 - MOV R9,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x22642D + 3), (enable) ? newOff : off); // dmc3.exe+22642D - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x226988 + 3), (enable) ? newOff : off); // dmc3.exe+226988 - 4C 8B 83 00020000 - MOV R8,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x22698F + 3), (enable) ? newOff : off); // dmc3.exe+22698F - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x22699A + 3), (enable) ? newOff : off); // dmc3.exe+22699A - 4C 8B 8B 00020000 - MOV R9,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x2269A1 + 3), (enable) ? newOff : off); // dmc3.exe+2269A1 - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x226C65 + 3), (enable) ? newOff : off); // dmc3.exe+226C65 - 49 8D 8E 00020000 - LEA RCX,[R14+00000200]
		// Write<uint32>((appBaseAddr + 0x226C7D + 3), (enable) ? newOff : off); // dmc3.exe+226C7D - 49 8D 8E 00020000 - LEA RCX,[R14+00000200]
		// Write<uint32>((appBaseAddr + 0x2297A8 + 3), (enable) ? newOff : off); // dmc3.exe+2297A8 - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x229822 + 3), (enable) ? newOff : off); // dmc3.exe+229822 - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x229B05 + 3), (enable) ? newOff : off); // dmc3.exe+229B05 - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x229B1C + 3), (enable) ? newOff : off); // dmc3.exe+229B1C - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x229B3C + 3), (enable) ? newOff : off); // dmc3.exe+229B3C - 49 8D 80 00020000 - LEA RAX,[R8+00000200]
		// Write<uint32>((appBaseAddr + 0x229BAC + 3), (enable) ? newOff : off); // dmc3.exe+229BAC - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x229BED + 3), (enable) ? newOff : off); // dmc3.exe+229BED - 48 81 C1 00020000 - ADD RCX,00000200
		// LikelyWeapon<uint32>((appBaseAddr + 0x229C4D + 3), (enable) ? newOff : off); // dmc3.exe+229C4D - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x22B908 + 3), (enable) ? newOff : off); // dmc3.exe+22B908 - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x22B972 + 3), (enable) ? newOff : off); // dmc3.exe+22B972 - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x22BC70 + 3), (enable) ? newOff : off); // dmc3.exe+22BC70 - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x22BC87 + 3), (enable) ? newOff : off); // dmc3.exe+22BC87 - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x22BCA7 + 3), (enable) ? newOff : off); // dmc3.exe+22BCA7 - 48 8D 81 00020000 - LEA RAX,[RCX+00000200]
		// Write<uint32>((appBaseAddr + 0x22BCC4 + 3), (enable) ? newOff : off); // dmc3.exe+22BCC4 - 48 8D 8A 00020000 - LEA RCX,[RDX+00000200]
		// Write<uint32>((appBaseAddr + 0x22BD45 + 3), (enable) ? newOff : off); // dmc3.exe+22BD45 - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x22BD89 + 3), (enable) ? newOff : off); // dmc3.exe+22BD89 - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x22BE4D + 3), (enable) ? newOff : off); // dmc3.exe+22BE4D - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x22BEEB + 3), (enable) ? newOff : off); // dmc3.exe+22BEEB - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x22C001 + 3), (enable) ? newOff : off); // dmc3.exe+22C001 - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x22C05A + 3), (enable) ? newOff : off); // dmc3.exe+22C05A - 48 8B 87 00020000 - MOV RAX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x22C06F + 3), (enable) ? newOff : off); // dmc3.exe+22C06F - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x22C081 + 3), (enable) ? newOff : off); // dmc3.exe+22C081 - 48 8B 87 00020000 - MOV RAX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x22C088 + 3), (enable) ? newOff : off); // dmc3.exe+22C088 - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x22C0CA + 3), (enable) ? newOff : off); // dmc3.exe+22C0CA - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x22C160 + 3), (enable) ? newOff : off); // dmc3.exe+22C160 - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x22C2C2 + 3), (enable) ? newOff : off); // dmc3.exe+22C2C2 - 48 81 C1 00020000 - ADD RCX,00000200
		// LikelyWeapon<uint32>((appBaseAddr + 0x22FDFE + 2), (enable) ? newOff : off); // dmc3.exe+22FDFE - 48 05 00020000 - ADD RAX,00000200
		// LikelyWeapon<uint32>((appBaseAddr + 0x230588 + 3), (enable) ? newOff : off); // dmc3.exe+230588 - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2305F2 + 3), (enable) ? newOff : off); // dmc3.exe+2305F2 - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2308DF + 3), (enable) ? newOff : off); // dmc3.exe+2308DF - 48 81 C1 00020000 - ADD RCX,00000200
		// LikelyWeapon<uint32>((appBaseAddr + 0x2308F6 + 3), (enable) ? newOff : off); // dmc3.exe+2308F6 - 48 81 C1 00020000 - ADD RCX,00000200
		// LikelyWeapon<uint32>((appBaseAddr + 0x230916 + 3), (enable) ? newOff : off); // dmc3.exe+230916 - 48 8D 81 00020000 - LEA RAX,[RCX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x230933 + 3), (enable) ? newOff : off); // dmc3.exe+230933 - 48 8D 8A 00020000 - LEA RCX,[RDX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2309B8 + 3), (enable) ? newOff : off); // dmc3.exe+2309B8 - 48 81 C1 00020000 - ADD RCX,00000200
		// LikeleyWeapon<uint32>((appBaseAddr + 0x2309EA + 3), (enable) ? newOff : off); // dmc3.exe+2309EA - 48 81 C1 00020000 - ADD RCX,00000200
		// LikelyWeapon<uint32>((appBaseAddr + 0x230A4D + 3), (enable) ? newOff : off); // dmc3.exe+230A4D - 48 81 C1 00020000 - ADD RCX,00000200
		// LikelyWeapon<uint32>((appBaseAddr + 0x230B43 + 3), (enable) ? newOff : off); // dmc3.exe+230B43 - 48 8D 8E 00020000 - LEA RCX,[RSI+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x230C9D + 3), (enable) ? newOff : off); // dmc3.exe+230C9D - 48 8B 83 00020000 - MOV RAX,[RBX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x230CA4 + 3), (enable) ? newOff : off); // dmc3.exe+230CA4 - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x230D1C + 3), (enable) ? newOff : off); // dmc3.exe+230D1C - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x230D99 + 3), (enable) ? newOff : off); // dmc3.exe+230D99 - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x230DF0 + 3), (enable) ? newOff : off); // dmc3.exe+230DF0 - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x230ED2 + 3), (enable) ? newOff : off); // dmc3.exe+230ED2 - 48 81 C1 00020000 - ADD RCX,00000200
		// LikelyWeapon<uint32>((appBaseAddr + 0x230F78 + 3), (enable) ? newOff : off); // dmc3.exe+230F78 - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x230FF2 + 3), (enable) ? newOff : off); // dmc3.exe+230FF2 - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2312F0 + 3), (enable) ? newOff : off); // dmc3.exe+2312F0 - 48 81 C1 00020000 - ADD RCX,00000200
		// LikelyWeapon<uint32>((appBaseAddr + 0x231307 + 3), (enable) ? newOff : off); // dmc3.exe+231307 - 48 81 C1 00020000 - ADD RCX,00000200
		// LikelyWeapon<uint32>((appBaseAddr + 0x231327 + 3), (enable) ? newOff : off); // dmc3.exe+231327 - 48 8D 81 00020000 - LEA RAX,[RCX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x231344 + 3), (enable) ? newOff : off); // dmc3.exe+231344 - 48 8D 8A 00020000 - LEA RCX,[RDX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2313C0 + 3), (enable) ? newOff : off); // dmc3.exe+2313C0 - 48 81 C1 00020000 - ADD RCX,00000200
		// LikelyWeapon<uint32>((appBaseAddr + 0x231401 + 3), (enable) ? newOff : off); // dmc3.exe+231401 - 48 81 C1 00020000 - ADD RCX,00000200
		// LikelyWeapon<uint32>((appBaseAddr + 0x231525 + 3), (enable) ? newOff : off); // dmc3.exe+231525 - 48 8D 8E 00020000 - LEA RCX,[RSI+00000200]
		// Write<uint32>((appBaseAddr + 0x2316FF + 3), (enable) ? newOff : off); // dmc3.exe+2316FF - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x231739 + 3), (enable) ? newOff : off); // dmc3.exe+231739 - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		//LikelyWeapon<uint32>((appBaseAddr + 0x23178E + 3), (enable) ? newOff : off); // dmc3.exe+23178E - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x27507B + 3), (enable) ? newOff : off); // dmc3.exe+27507B - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x275092 + 3), (enable) ? newOff : off); // dmc3.exe+275092 - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x275BC9 + 3), (enable) ? newOff : off); // dmc3.exe+275BC9 - 48 81 C1 00020000 - ADD RCX,00000200
		// LikelyWeapon<uint32>((appBaseAddr + 0x27D724 + 3), (enable) ? newOff : off); // dmc3.exe+27D724 - 48 89 9F 00020000 - MOV [RDI+00000200],RBX
		// LikelyWeapon<uint32>((appBaseAddr + 0x27DDA5 + 3), (enable) ? newOff : off); // dmc3.exe+27DDA5 - 4C 8D 87 00020000 - LEA R8,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x2C8270 + 3), (enable) ? newOff : off); // dmc3.exe+2C8270 - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2CB8B3 + 3), (enable) ? newOff : off); // dmc3.exe+2CB8B3 - 48 8D 8D 00020000 - LEA RCX,[RBP+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2CBA97 + 3), (enable) ? newOff : off); // dmc3.exe+2CBA97 - 4C 8D 85 00020000 - LEA R8,[RBP+00000200]
		// Write<uint32>((appBaseAddr + 0x2DC32D + 3), (enable) ? newOff : off); // dmc3.exe+2DC32D - 48 05 00020000 - ADD RAX,00000200
		// Write<uint32>((appBaseAddr + 0x2DE765 + 3), (enable) ? newOff : off); // dmc3.exe+2DE765 - 48 05 00020000 - ADD RAX,00000200
		// Write<uint32>((appBaseAddr + 0x2DE827 + 3), (enable) ? newOff : off); // dmc3.exe+2DE827 - 48 05 00020000 - ADD RAX,00000200
		// Write<uint32>((appBaseAddr + 0x2DEB27 + 3), (enable) ? newOff : off); // dmc3.exe+2DEB27 - 48 05 00020000 - ADD RAX,00000200
		// Write<uint32>((appBaseAddr + 0x2F3F15 + 3), (enable) ? newOff : off); // dmc3.exe+2F3F15 - 48 8D 8C 0A 00020000 - LEA RCX,[RDX+RCX+00000200]
		// Write<uint32>((appBaseAddr + 0x2F415F + 3), (enable) ? newOff : off); // dmc3.exe+2F415F - 49 8D 94 10 00020000 - LEA RDX,[R8+RDX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2F85AC + 3), (enable) ? newOff : off); // dmc3.exe+2F85AC - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FABB3 + 3), (enable) ? newOff : off); // dmc3.exe+2FABB3 - 48 8D 8C 0A 00020000 - LEA RCX,[RDX+RCX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FAC0F + 3), (enable) ? newOff : off); // dmc3.exe+2FAC0F - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FAC42 + 3), (enable) ? newOff : off); // dmc3.exe+2FAC42 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FAC75 + 3), (enable) ? newOff : off); // dmc3.exe+2FAC75 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FACA8 + 3), (enable) ? newOff : off); // dmc3.exe+2FACA8 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FACE0 + 3), (enable) ? newOff : off); // dmc3.exe+2FACE0 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FAD13 + 3), (enable) ? newOff : off); // dmc3.exe+2FAD13 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FAD46 + 3), (enable) ? newOff : off); // dmc3.exe+2FAD46 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FAD79 + 3), (enable) ? newOff : off); // dmc3.exe+2FAD79 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FADB1 + 3), (enable) ? newOff : off); // dmc3.exe+2FADB1 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FADE4 + 3), (enable) ? newOff : off); // dmc3.exe+2FADE4 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FAE17 + 3), (enable) ? newOff : off); // dmc3.exe+2FAE17 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FAE4A + 3), (enable) ? newOff : off); // dmc3.exe+2FAE4A - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FAE82 + 3), (enable) ? newOff : off); // dmc3.exe+2FAE82 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FAEBE + 3), (enable) ? newOff : off); // dmc3.exe+2FAEBE - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FAEFA + 3), (enable) ? newOff : off); // dmc3.exe+2FAEFA - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FAF36 + 3), (enable) ? newOff : off); // dmc3.exe+2FAF36 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FAF6E + 3), (enable) ? newOff : off); // dmc3.exe+2FAF6E - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FAFA3 + 3), (enable) ? newOff : off); // dmc3.exe+2FAFA3 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FAFD8 + 3), (enable) ? newOff : off); // dmc3.exe+2FAFD8 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FB00D + 3), (enable) ? newOff : off); // dmc3.exe+2FB00D - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FB042 + 3), (enable) ? newOff : off); // dmc3.exe+2FB042 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FB077 + 3), (enable) ? newOff : off); // dmc3.exe+2FB077 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FB0AC + 3), (enable) ? newOff : off); // dmc3.exe+2FB0AC - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FB0E1 + 3), (enable) ? newOff : off); // dmc3.exe+2FB0E1 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FB116 + 3), (enable) ? newOff : off); // dmc3.exe+2FB116 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FB14B + 3), (enable) ? newOff : off); // dmc3.exe+2FB14B - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FB180 + 3), (enable) ? newOff : off); // dmc3.exe+2FB180 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FB1B5 + 3), (enable) ? newOff : off); // dmc3.exe+2FB1B5 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FB1EA + 3), (enable) ? newOff : off); // dmc3.exe+2FB1EA - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FB21F + 3), (enable) ? newOff : off); // dmc3.exe+2FB21F - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FB254 + 3), (enable) ? newOff : off); // dmc3.exe+2FB254 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FB289 + 3), (enable) ? newOff : off); // dmc3.exe+2FB289 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB2DB + 3), (enable) ? newOff : off); // dmc3.exe+2FB2DB - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB30E + 3), (enable) ? newOff : off); // dmc3.exe+2FB30E - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB341 + 3), (enable) ? newOff : off); // dmc3.exe+2FB341 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB374 + 3), (enable) ? newOff : off); // dmc3.exe+2FB374 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB3AC + 3), (enable) ? newOff : off); // dmc3.exe+2FB3AC - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB3DF + 3), (enable) ? newOff : off); // dmc3.exe+2FB3DF - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB412 + 3), (enable) ? newOff : off); // dmc3.exe+2FB412 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB445 + 3), (enable) ? newOff : off); // dmc3.exe+2FB445 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB47D + 3), (enable) ? newOff : off); // dmc3.exe+2FB47D - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB4B0 + 3), (enable) ? newOff : off); // dmc3.exe+2FB4B0 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB4E3 + 3), (enable) ? newOff : off); // dmc3.exe+2FB4E3 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB516 + 3), (enable) ? newOff : off); // dmc3.exe+2FB516 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB54E + 3), (enable) ? newOff : off); // dmc3.exe+2FB54E - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB583 + 3), (enable) ? newOff : off); // dmc3.exe+2FB583 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB5B8 + 3), (enable) ? newOff : off); // dmc3.exe+2FB5B8 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB5ED + 3), (enable) ? newOff : off); // dmc3.exe+2FB5ED - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB622 + 3), (enable) ? newOff : off); // dmc3.exe+2FB622 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB657 + 3), (enable) ? newOff : off); // dmc3.exe+2FB657 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB68C + 3), (enable) ? newOff : off); // dmc3.exe+2FB68C - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB6C1 + 3), (enable) ? newOff : off); // dmc3.exe+2FB6C1 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB6F6 + 3), (enable) ? newOff : off); // dmc3.exe+2FB6F6 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB72B + 3), (enable) ? newOff : off); // dmc3.exe+2FB72B - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB760 + 3), (enable) ? newOff : off); // dmc3.exe+2FB760 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB795 + 3), (enable) ? newOff : off); // dmc3.exe+2FB795 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB7CA + 3), (enable) ? newOff : off); // dmc3.exe+2FB7CA - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB7FF + 3), (enable) ? newOff : off); // dmc3.exe+2FB7FF - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB834 + 3), (enable) ? newOff : off); // dmc3.exe+2FB834 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB869 + 3), (enable) ? newOff : off); // dmc3.exe+2FB869 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB8CD + 3), (enable) ? newOff : off); // dmc3.exe+2FB8CD - 49 8D 94 10 00020000 - LEA RDX,[R8+RDX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB8F0 + 3), (enable) ? newOff : off); // dmc3.exe+2FB8F0 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB923 + 3), (enable) ? newOff : off); // dmc3.exe+2FB923 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB956 + 3), (enable) ? newOff : off); // dmc3.exe+2FB956 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB989 + 3), (enable) ? newOff : off); // dmc3.exe+2FB989 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB9C1 + 3), (enable) ? newOff : off); // dmc3.exe+2FB9C1 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB9F4 + 3), (enable) ? newOff : off); // dmc3.exe+2FB9F4 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FBA27 + 3), (enable) ? newOff : off); // dmc3.exe+2FBA27 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FBA5A + 3), (enable) ? newOff : off); // dmc3.exe+2FBA5A - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FBA92 + 3), (enable) ? newOff : off); // dmc3.exe+2FBA92 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FBAC5 + 3), (enable) ? newOff : off); // dmc3.exe+2FBAC5 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FBAF8 + 3), (enable) ? newOff : off); // dmc3.exe+2FBAF8 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FBB2B + 3), (enable) ? newOff : off); // dmc3.exe+2FBB2B - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FBB8F + 3), (enable) ? newOff : off); // dmc3.exe+2FBB8F - 48 8D 8C 0A 00020000 - LEA RCX,[RDX+RCX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x2FEEDC + 3), (enable) ? newOff : off); // dmc3.exe+2FEEDC - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// LikelyWeapon<uint32>((appBaseAddr + 0x310BBC + 3), (enable) ? newOff : off); // dmc3.exe+310BBC - 48 8D 8D 00020000 - LEA RCX,[RBP+00000200]
		// Menu<uint32>((appBaseAddr + 0x310F0C + 3), (enable) ? newOff : off); // dmc3.exe+310F0C - 49 8D 8E 00020000 - LEA RCX,[R14+00000200]
		// Write<uint32>((appBaseAddr + 0x3210AF + 3), (enable) ? newOff : off); // dmc3.exe+3210AF - 48 8D 86 00020000 - LEA RAX,[RSI+00000200]
		// Write<uint32>((appBaseAddr + 0x348DC3 + 3), (enable) ? newOff : off); // dmc3.exe+348DC3 - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x34B2B3 + 3), (enable) ? newOff : off); // dmc3.exe+34B2B3 - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x34B2D3 + 3), (enable) ? newOff : off); // dmc3.exe+34B2D3 - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x34B81C + 3), (enable) ? newOff : off); // dmc3.exe+34B81C - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x34C064 + 3), (enable) ? newOff : off); // dmc3.exe+34C064 - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x34C0B4 + 3), (enable) ? newOff : off); // dmc3.exe+34C0B4 - 48 81 C1 00020000 - ADD RCX,00000200
	}
	// 0x208
	{
		constexpr auto off = (offsetof(ActorData, modelData[0]) + 8);
		constexpr auto newOff = (offsetof(ActorData, newModelData[0]) + 8);
		static_assert(off == 0x208);
		Write<uint32>((appBaseAddr + 0x1EF412 + 3), (enable) ? newOff : off); // dmc3.exe+1EF412 - 49 8D AD 08020000 - lea rbp,[r13+00000208]
	}
	// 0x980
	{
		constexpr auto off = offsetof(ActorData, modelData[1]);
		constexpr auto newOff = offsetof(ActorData, newModelData[1]);
		static_assert(off == 0x980);
		// Write<uint32>((appBaseAddr + 0xD6A18 + 3), (enable) ? newOff : off); // dmc3.exe+D6A18 - 4C 89 A8 80090000 - MOV [RAX+00000980],R13
		// Write<uint32>((appBaseAddr + 0xD70D3 + 3), (enable) ? newOff : off); // dmc3.exe+D70D3 - 4D 8B 87 80090000 - MOV R8,[R15+00000980]
		// Write<uint32>((appBaseAddr + 0xD7161 + 3), (enable) ? newOff : off); // dmc3.exe+D7161 - 49 8B 8F 80090000 - MOV RCX,[R15+00000980]
		// Write<uint32>((appBaseAddr + 0xD7206 + 3), (enable) ? newOff : off); // dmc3.exe+D7206 - 49 8B B7 80090000 - MOV RSI,[R15+00000980]
		// Write<uint32>((appBaseAddr + 0xD725B + 3), (enable) ? newOff : off); // dmc3.exe+D725B - 49 8B 9F 80090000 - MOV RBX,[R15+00000980]
		// Write<uint32>((appBaseAddr + 0xD729B + 3), (enable) ? newOff : off); // dmc3.exe+D729B - 49 8B 8F 80090000 - MOV RCX,[R15+00000980]
		// Write<uint32>((appBaseAddr + 0xD72D7 + 3), (enable) ? newOff : off); // dmc3.exe+D72D7 - 49 8B 8F 80090000 - MOV RCX,[R15+00000980]
		// Write<uint32>((appBaseAddr + 0xD7313 + 3), (enable) ? newOff : off); // dmc3.exe+D7313 - 49 8B 8F 80090000 - MOV RCX,[R15+00000980]
		// Write<uint32>((appBaseAddr + 0xD7383 + 3), (enable) ? newOff : off); // dmc3.exe+D7383 - 49 8B BF 80090000 - MOV RDI,[R15+00000980]
		// Write<uint32>((appBaseAddr + 0xD7438 + 3), (enable) ? newOff : off); // dmc3.exe+D7438 - 4D 8B 87 80090000 - MOV R8,[R15+00000980]
		// Write<uint32>((appBaseAddr + 0xD7487 + 3), (enable) ? newOff : off); // dmc3.exe+D7487 - 49 8B 8F 80090000 - MOV RCX,[R15+00000980]
		// Write<uint32>((appBaseAddr + 0xD760D + 3), (enable) ? newOff : off); // dmc3.exe+D760D - 49 8B 97 80090000 - MOV RDX,[R15+00000980]
		// Write<uint32>((appBaseAddr + 0xD7678 + 3), (enable) ? newOff : off); // dmc3.exe+D7678 - 49 8B 97 80090000 - MOV RDX,[R15+00000980]
		// Write<uint32>((appBaseAddr + 0x15F8C7 + 3), (enable) ? newOff : off); // dmc3.exe+15F8C7 - 48 89 B0 80090000 - MOV [RAX+00000980],RSI
		// Write<uint32>((appBaseAddr + 0x162066 + 3), (enable) ? newOff : off); // dmc3.exe+162066 - 48 8B 91 80090000 - MOV RDX,[RCX+00000980]
		// Write<uint32>((appBaseAddr + 0x1628DA + 3), (enable) ? newOff : off); // dmc3.exe+1628DA - 4C 8B 8F 80090000 - MOV R9,[RDI+00000980]
		// Trash<uint32>((appBaseAddr + 0x18C8E0 + 3), (enable) ? newOff : off); // dmc3.exe+18C8E0 - 0F29 80 80090000 - MOVAPS [RAX+00000980],XMM0
		// Write<uint32>((appBaseAddr + 0x1D0AEC + 3), (enable) ? newOff : off); // dmc3.exe+1D0AEC - 48 8D 8B 80090000 - LEA RCX,[RBX+00000980]
		// Write<uint32>((appBaseAddr + 0x1D0B62 + 3), (enable) ? newOff : off); // dmc3.exe+1D0B62 - 48 81 C1 80090000 - ADD RCX,00000980
		// Write<uint32>((appBaseAddr + 0x1D0EF2 + 3), (enable) ? newOff : off); // dmc3.exe+1D0EF2 - 48 8D 8F 80090000 - LEA RCX,[RDI+00000980]
		// Write<uint32>((appBaseAddr + 0x1D0EFE + 3), (enable) ? newOff : off); // dmc3.exe+1D0EFE - 48 8D 8F 80090000 - LEA RCX,[RDI+00000980]
		// Write<uint32>((appBaseAddr + 0x1D0F15 + 3), (enable) ? newOff : off); // dmc3.exe+1D0F15 - 48 8D 8F 80090000 - LEA RCX,[RDI+00000980]
		// Write<uint32>((appBaseAddr + 0x1D0FA9 + 3), (enable) ? newOff : off); // dmc3.exe+1D0FA9 - 48 8D 8F 80090000 - LEA RCX,[RDI+00000980]
		// Write<uint32>((appBaseAddr + 0x1D0FBA + 3), (enable) ? newOff : off); // dmc3.exe+1D0FBA - 48 8D 8F 80090000 - LEA RCX,[RDI+00000980]
		// Write<uint32>((appBaseAddr + 0x1D1095 + 3), (enable) ? newOff : off); // dmc3.exe+1D1095 - 48 8D 8F 80090000 - LEA RCX,[RDI+00000980]
		// Write<uint32>((appBaseAddr + 0x1D10F7 + 3), (enable) ? newOff : off); // dmc3.exe+1D10F7 - 48 8D 9F 80090000 - LEA RBX,[RDI+00000980]
		Write<uint32>((appBaseAddr + 0x1EF2B4 + 3), (enable) ? newOff : off); // dmc3.exe+1EF2B4 - 49 8B 85 80090000 - MOV RAX,[R13+00000980]
		Write<uint32>((appBaseAddr + 0x1EF2C8 + 3), (enable) ? newOff : off); // dmc3.exe+1EF2C8 - 49 8D 8D 80090000 - LEA RCX,[R13+00000980]
		Write<uint32>((appBaseAddr + 0x1EF2D5 + 3), (enable) ? newOff : off); // dmc3.exe+1EF2D5 - 49 8D 8D 80090000 - LEA RCX,[R13+00000980]
		Write<uint32>((appBaseAddr + 0x1EF2EB + 3), (enable) ? newOff : off); // dmc3.exe+1EF2EB - 4D 8D B5 80090000 - LEA R14,[R13+00000980]
		// Wrong<uint32>((appBaseAddr + 0x2297B5 + 3), (enable) ? newOff : off); // dmc3.exe+2297B5 - 48 8D 8B 80090000 - LEA RCX,[RBX+00000980]
		// Wrong<uint32>((appBaseAddr + 0x229815 + 3), (enable) ? newOff : off); // dmc3.exe+229815 - 48 81 C1 80090000 - ADD RCX,00000980
		// Wrong<uint32>((appBaseAddr + 0x229BA5 + 3), (enable) ? newOff : off); // dmc3.exe+229BA5 - 48 8B 99 80090000 - MOV RBX,[RCX+00000980]
		// Wrong<uint32>((appBaseAddr + 0x229BC0 + 3), (enable) ? newOff : off); // dmc3.exe+229BC0 - 48 81 C1 80090000 - ADD RCX,00000980
		// Wrong<uint32>((appBaseAddr + 0x229C66 + 3), (enable) ? newOff : off); // dmc3.exe+229C66 - 48 8D 8F 80090000 - LEA RCX,[RDI+00000980]
		// Wrong<uint32>((appBaseAddr + 0x22B915 + 3), (enable) ? newOff : off); // dmc3.exe+22B915 - 48 8D 8B 80090000 - LEA RCX,[RBX+00000980]
		// Wrong<uint32>((appBaseAddr + 0x22B965 + 3), (enable) ? newOff : off); // dmc3.exe+22B965 - 48 81 C1 80090000 - ADD RCX,00000980
		// Wrong<uint32>((appBaseAddr + 0x22BD3E + 3), (enable) ? newOff : off); // dmc3.exe+22BD3E - 48 8B 99 80090000 - MOV RBX,[RCX+00000980]
		// Wrong<uint32>((appBaseAddr + 0x22BD59 + 3), (enable) ? newOff : off); // dmc3.exe+22BD59 - 48 81 C1 80090000 - ADD RCX,00000980
		// Wrong<uint32>((appBaseAddr + 0x22BE66 + 3), (enable) ? newOff : off); // dmc3.exe+22BE66 - 48 8D 8F 80090000 - LEA RCX,[RDI+00000980]
		// Wrong<uint32>((appBaseAddr + 0x22C2E5 + 3), (enable) ? newOff : off); // dmc3.exe+22C2E5 - 48 8D 8B 80090000 - LEA RCX,[RBX+00000980]
		// Wrong<uint32>((appBaseAddr + 0x230595 + 3), (enable) ? newOff : off); // dmc3.exe+230595 - 48 8D 8B 80090000 - LEA RCX,[RBX+00000980]
		// Wrong<uint32>((appBaseAddr + 0x2305E5 + 3), (enable) ? newOff : off); // dmc3.exe+2305E5 - 48 81 C1 80090000 - ADD RCX,00000980
		// Wrong<uint32>((appBaseAddr + 0x2309B1 + 3), (enable) ? newOff : off); // dmc3.exe+2309B1 - 48 8B 99 80090000 - MOV RBX,[RCX+00000980]
		// Wrong<uint32>((appBaseAddr + 0x2309CC + 3), (enable) ? newOff : off); // dmc3.exe+2309CC - 48 81 C1 80090000 - ADD RCX,00000980
		// Wrong<uint32>((appBaseAddr + 0x230A66 + 3), (enable) ? newOff : off); // dmc3.exe+230A66 - 48 8D 8F 80090000 - LEA RCX,[RDI+00000980]
		// Wrong<uint32>((appBaseAddr + 0x230EF5 + 3), (enable) ? newOff : off); // dmc3.exe+230EF5 - 48 8D 8B 80090000 - LEA RCX,[RBX+00000980]
		// Wrong<uint32>((appBaseAddr + 0x230F85 + 3), (enable) ? newOff : off); // dmc3.exe+230F85 - 48 8D 8B 80090000 - LEA RCX,[RBX+00000980]
		// Wrong<uint32>((appBaseAddr + 0x230FE5 + 3), (enable) ? newOff : off); // dmc3.exe+230FE5 - 48 81 C1 80090000 - ADD RCX,00000980
		// Wrong<uint32>((appBaseAddr + 0x2313B9 + 3), (enable) ? newOff : off); // dmc3.exe+2313B9 - 48 8B 99 80090000 - MOV RBX,[RCX+00000980]
		// Wrong<uint32>((appBaseAddr + 0x2313D4 + 3), (enable) ? newOff : off); // dmc3.exe+2313D4 - 48 81 C1 80090000 - ADD RCX,00000980
		// Write<uint32>((appBaseAddr + 0x24F0EF + 3), (enable) ? newOff : off); // dmc3.exe+24F0EF - 48 8D 8B 80090000 - LEA RCX,[RBX+00000980]
		// Write<uint32>((appBaseAddr + 0x24F243 + 3), (enable) ? newOff : off); // dmc3.exe+24F243 - 48 81 C1 80090000 - ADD RCX,00000980
		// Write<uint32>((appBaseAddr + 0x2506D5 + 3), (enable) ? newOff : off); // dmc3.exe+2506D5 - 48 81 C1 80090000 - ADD RCX,00000980
		// Write<uint32>((appBaseAddr + 0x2506F5 + 3), (enable) ? newOff : off); // dmc3.exe+2506F5 - 48 8D 8E 80090000 - LEA RCX,[RSI+00000980]
		// Write<uint32>((appBaseAddr + 0x250701 + 3), (enable) ? newOff : off); // dmc3.exe+250701 - 48 8D 8E 80090000 - LEA RCX,[RSI+00000980]
		// Write<uint32>((appBaseAddr + 0x250725 + 3), (enable) ? newOff : off); // dmc3.exe+250725 - 48 8D 8E 80090000 - LEA RCX,[RSI+00000980]
		// Write<uint32>((appBaseAddr + 0x25077F + 3), (enable) ? newOff : off); // dmc3.exe+25077F - 48 8D 8E 80090000 - LEA RCX,[RSI+00000980]
		// Write<uint32>((appBaseAddr + 0x250898 + 3), (enable) ? newOff : off); // dmc3.exe+250898 - 48 8D 8F 80090000 - LEA RCX,[RDI+00000980]
		// Write<uint32>((appBaseAddr + 0x25150A + 3), (enable) ? newOff : off); // dmc3.exe+25150A - 48 81 C1 80090000 - ADD RCX,00000980
		// Write<uint32>((appBaseAddr + 0x25151B + 3), (enable) ? newOff : off); // dmc3.exe+25151B - 48 8D 8F 80090000 - LEA RCX,[RDI+00000980]
		// Write<uint32>((appBaseAddr + 0x26B327 + 3), (enable) ? newOff : off); // dmc3.exe+26B327 - 48 81 C1 80090000 - ADD RCX,00000980
		// Write<uint32>((appBaseAddr + 0x26B33B + 3), (enable) ? newOff : off); // dmc3.exe+26B33B - 4C 8D 80 80090000 - LEA R8,[RAX+00000980]
		// Write<uint32>((appBaseAddr + 0x26B9E9 + 3), (enable) ? newOff : off); // dmc3.exe+26B9E9 - 48 89 B1 80090000 - MOV [RCX+00000980],RSI
		// Write<uint32>((appBaseAddr + 0x26D4DD + 3), (enable) ? newOff : off); // dmc3.exe+26D4DD - 48 8D 8B 80090000 - LEA RCX,[RBX+00000980]
		// Write<uint32>((appBaseAddr + 0x26D5AD + 3), (enable) ? newOff : off); // dmc3.exe+26D5AD - 48 8D 8B 80090000 - LEA RCX,[RBX+00000980]
		// Write<uint32>((appBaseAddr + 0x26D81A + 3), (enable) ? newOff : off); // dmc3.exe+26D81A - 48 81 C1 80090000 - ADD RCX,00000980
		// Write<uint32>((appBaseAddr + 0x26D843 + 3), (enable) ? newOff : off); // dmc3.exe+26D843 - 49 8D 88 80090000 - LEA RCX,[R8+00000980]
		// Write<uint32>((appBaseAddr + 0x26D861 + 3), (enable) ? newOff : off); // dmc3.exe+26D861 - 48 81 C1 80090000 - ADD RCX,00000980
		// Write<uint32>((appBaseAddr + 0x26D87D + 3), (enable) ? newOff : off); // dmc3.exe+26D87D - 48 81 C1 80090000 - ADD RCX,00000980
		// Write<uint32>((appBaseAddr + 0x26DA02 + 3), (enable) ? newOff : off); // dmc3.exe+26DA02 - 48 8D 8F 80090000 - LEA RCX,[RDI+00000980]
		// Write<uint32>((appBaseAddr + 0x26DE5B + 3), (enable) ? newOff : off); // dmc3.exe+26DE5B - 48 8D 8E 80090000 - LEA RCX,[RSI+00000980]
		// Write<uint32>((appBaseAddr + 0x26DEA6 + 3), (enable) ? newOff : off); // dmc3.exe+26DEA6 - 48 8D 8E 80090000 - LEA RCX,[RSI+00000980]
		// Write<uint32>((appBaseAddr + 0x26DF6F + 3), (enable) ? newOff : off); // dmc3.exe+26DF6F - 48 8D 8E 80090000 - LEA RCX,[RSI+00000980]
		// Write<uint32>((appBaseAddr + 0x26DF9D + 3), (enable) ? newOff : off); // dmc3.exe+26DF9D - 48 8D 8E 80090000 - LEA RCX,[RSI+00000980]
		// Write<uint32>((appBaseAddr + 0x26DFAB + 3), (enable) ? newOff : off); // dmc3.exe+26DFAB - 48 8D 8E 80090000 - LEA RCX,[RSI+00000980]
		// Write<uint32>((appBaseAddr + 0x26DFC0 + 3), (enable) ? newOff : off); // dmc3.exe+26DFC0 - 4C 8B 96 80090000 - MOV R10,[RSI+00000980]
		// Write<uint32>((appBaseAddr + 0x26E04C + 3), (enable) ? newOff : off); // dmc3.exe+26E04C - 48 81 C1 80090000 - ADD RCX,00000980
		// Write<uint32>((appBaseAddr + 0x26E37F + 3), (enable) ? newOff : off); // dmc3.exe+26E37F - 48 81 C1 80090000 - ADD RCX,00000980
		// Write<uint32>((appBaseAddr + 0x26E46E + 3), (enable) ? newOff : off); // dmc3.exe+26E46E - 48 8D 8B 80090000 - LEA RCX,[RBX+00000980]
		// Write<uint32>((appBaseAddr + 0x26E54F + 3), (enable) ? newOff : off); // dmc3.exe+26E54F - 48 8B 83 80090000 - MOV RAX,[RBX+00000980]
		// Write<uint32>((appBaseAddr + 0x26E55D + 3), (enable) ? newOff : off); // dmc3.exe+26E55D - 48 8D 8B 80090000 - LEA RCX,[RBX+00000980]
		// Write<uint32>((appBaseAddr + 0x26E56F + 3), (enable) ? newOff : off); // dmc3.exe+26E56F - 48 8B 83 80090000 - MOV RAX,[RBX+00000980]
		// Write<uint32>((appBaseAddr + 0x26E57D + 3), (enable) ? newOff : off); // dmc3.exe+26E57D - 48 8D 8B 80090000 - LEA RCX,[RBX+00000980]
		// Trash<uint32>((appBaseAddr + 0x2952E3 + 3), (enable) ? newOff : off); // dmc3.exe+2952E3 - BA 80090000 - MOV EDX,00000980
		// Trash<uint32>((appBaseAddr + 0x29538F + 3), (enable) ? newOff : off); // dmc3.exe+29538F - BA 80090000 - MOV EDX,00000980
		// Trash<uint32>((appBaseAddr + 0x2E36ED + 3), (enable) ? newOff : off); // dmc3.exe+2E36ED - BA 80090000 - MOV EDX,00000980
		// Wrong<uint32>((appBaseAddr + 0x2E3C93 + 3), (enable) ? newOff : off); // dmc3.exe+2E3C93 - 41 B8 80090000 - MOV R8D,00000980
		// Write<uint32>((appBaseAddr + 0x34CEDA + 3), (enable) ? newOff : off); // dmc3.exe+34CEDA - 48 81 C1 80090000 - ADD RCX,00000980
	}
	// 0x988
	{
		constexpr auto off = (offsetof(ActorData, modelData[1]) + 8);
		constexpr auto newOff = (offsetof(ActorData, newModelData[1]) + 8);
		static_assert(off == 0x988);
		Write<uint32>((appBaseAddr + 0x1EF2F2 + 3), (enable) ? newOff : off); // dmc3.exe+1EF2F2 - 49 8D AD 88090000 - lea rbp,[r13+00000988]
	}
	// 0x1100
	{
		constexpr auto off = offsetof(ActorData, modelData[2]);
		constexpr auto newOff = offsetof(ActorData, newModelData[2]);
		static_assert(off == 0x1100);
		// Trash<uint32>((appBaseAddr + 0xDF897 + 3), (enable) ? newOff : off); // dmc3.exe+DF897 - 48 B8 1100000011000000 - MOV RAX,0000001100000011
		// Write<uint32>((appBaseAddr + 0x13A3CB + 3), (enable) ? newOff : off); // dmc3.exe+13A3CB - 4C 89 A8 00110000 - MOV [RAX+00001100],R13
		// Write<uint32>((appBaseAddr + 0x13BA1A + 3), (enable) ? newOff : off); // dmc3.exe+13BA1A - 48 8B 89 00110000 - MOV RCX,[RCX+00001100]
		// Write<uint32>((appBaseAddr + 0x13BC9B + 3), (enable) ? newOff : off); // dmc3.exe+13BC9B - 48 8B 8E 00110000 - MOV RCX,[RSI+00001100]
		// Write<uint32>((appBaseAddr + 0x13BCD6 + 3), (enable) ? newOff : off); // dmc3.exe+13BCD6 - 48 8B 8E 00110000 - MOV RCX,[RSI+00001100]
		// Write<uint32>((appBaseAddr + 0x13BD15 + 3), (enable) ? newOff : off); // dmc3.exe+13BD15 - 48 8B 8E 00110000 - MOV RCX,[RSI+00001100]
		// Write<uint32>((appBaseAddr + 0x13BD50 + 3), (enable) ? newOff : off); // dmc3.exe+13BD50 - 48 8B 8E 00110000 - MOV RCX,[RSI+00001100]
		// Write<uint32>((appBaseAddr + 0x13BD8B + 3), (enable) ? newOff : off); // dmc3.exe+13BD8B - 48 8B 8E 00110000 - MOV RCX,[RSI+00001100]
		// Write<uint32>((appBaseAddr + 0x13BDC6 + 3), (enable) ? newOff : off); // dmc3.exe+13BDC6 - 48 8B 8E 00110000 - MOV RCX,[RSI+00001100]
		// Write<uint32>((appBaseAddr + 0x13BE01 + 3), (enable) ? newOff : off); // dmc3.exe+13BE01 - 48 8B 8E 00110000 - MOV RCX,[RSI+00001100]
		// Write<uint32>((appBaseAddr + 0x13BE3C + 3), (enable) ? newOff : off); // dmc3.exe+13BE3C - 48 8B 8E 00110000 - MOV RCX,[RSI+00001100]
		// Write<uint32>((appBaseAddr + 0x13BE77 + 3), (enable) ? newOff : off); // dmc3.exe+13BE77 - 48 8B 8E 00110000 - MOV RCX,[RSI+00001100]
		// Write<uint32>((appBaseAddr + 0x13BEB2 + 3), (enable) ? newOff : off); // dmc3.exe+13BEB2 - 48 8B 8E 00110000 - MOV RCX,[RSI+00001100]
		// Write<uint32>((appBaseAddr + 0x13BEED + 3), (enable) ? newOff : off); // dmc3.exe+13BEED - 48 8B 8E 00110000 - MOV RCX,[RSI+00001100]
		// Write<uint32>((appBaseAddr + 0x13BF28 + 3), (enable) ? newOff : off); // dmc3.exe+13BF28 - 48 8B 8E 00110000 - MOV RCX,[RSI+00001100]
		// Write<uint32>((appBaseAddr + 0x13CC1F + 3), (enable) ? newOff : off); // dmc3.exe+13CC1F - 48 8B 96 00110000 - MOV RDX,[RSI+00001100]
		// Write<uint32>((appBaseAddr + 0x13D957 + 3), (enable) ? newOff : off); // dmc3.exe+13D957 - 4C 89 A8 00110000 - MOV [RAX+00001100],R13
		// Write<uint32>((appBaseAddr + 0x13DEA2 + 3), (enable) ? newOff : off); // dmc3.exe+13DEA2 - 48 8B 89 00110000 - MOV RCX,[RCX+00001100]
		// Write<uint32>((appBaseAddr + 0x13E241 + 3), (enable) ? newOff : off); // dmc3.exe+13E241 - 48 8B 8E 00110000 - MOV RCX,[RSI+00001100]
		// Write<uint32>((appBaseAddr + 0x13F3D4 + 3), (enable) ? newOff : off); // dmc3.exe+13F3D4 - 48 8B 97 00110000 - MOV RDX,[RDI+00001100]
		// Write<uint32>((appBaseAddr + 0x13F4A9 + 3), (enable) ? newOff : off); // dmc3.exe+13F4A9 - 48 8B 97 00110000 - MOV RDX,[RDI+00001100]
		// Write<uint32>((appBaseAddr + 0x13F68B + 3), (enable) ? newOff : off); // dmc3.exe+13F68B - 48 8B 97 00110000 - MOV RDX,[RDI+00001100]
		// Write<uint32>((appBaseAddr + 0x13F840 + 3), (enable) ? newOff : off); // dmc3.exe+13F840 - 48 8B 97 00110000 - MOV RDX,[RDI+00001100]
		// Write<uint32>((appBaseAddr + 0x13F904 + 3), (enable) ? newOff : off); // dmc3.exe+13F904 - 48 8B 97 00110000 - MOV RDX,[RDI+00001100]
		// Write<uint32>((appBaseAddr + 0x13F9D3 + 3), (enable) ? newOff : off); // dmc3.exe+13F9D3 - 48 8B 97 00110000 - MOV RDX,[RDI+00001100]
		// Write<uint32>((appBaseAddr + 0x13FAA3 + 3), (enable) ? newOff : off); // dmc3.exe+13FAA3 - 48 8B 97 00110000 - MOV RDX,[RDI+00001100]
		// Write<uint32>((appBaseAddr + 0x13FB54 + 3), (enable) ? newOff : off); // dmc3.exe+13FB54 - 48 8B 97 00110000 - MOV RDX,[RDI+00001100]
		// Write<uint32>((appBaseAddr + 0x13FD56 + 3), (enable) ? newOff : off); // dmc3.exe+13FD56 - 48 8B 97 00110000 - MOV RDX,[RDI+00001100]
		// Write<uint32>((appBaseAddr + 0x1400C4 + 3), (enable) ? newOff : off); // dmc3.exe+1400C4 - 48 8B 96 00110000 - MOV RDX,[RSI+00001100]
		// Write<uint32>((appBaseAddr + 0x14051A + 3), (enable) ? newOff : off); // dmc3.exe+14051A - 48 8B 93 00110000 - MOV RDX,[RBX+00001100]
		// Write<uint32>((appBaseAddr + 0x1405E5 + 3), (enable) ? newOff : off); // dmc3.exe+1405E5 - 48 8B 93 00110000 - MOV RDX,[RBX+00001100]
		// Write<uint32>((appBaseAddr + 0x140F3A + 3), (enable) ? newOff : off); // dmc3.exe+140F3A - 48 8B 93 00110000 - MOV RDX,[RBX+00001100]
		// Write<uint32>((appBaseAddr + 0x14104F + 3), (enable) ? newOff : off); // dmc3.exe+14104F - 48 8B 93 00110000 - MOV RDX,[RBX+00001100]
		// Write<uint32>((appBaseAddr + 0x1413EC + 3), (enable) ? newOff : off); // dmc3.exe+1413EC - 48 8B 93 00110000 - MOV RDX,[RBX+00001100]
		// Write<uint32>((appBaseAddr + 0x1415D3 + 3), (enable) ? newOff : off); // dmc3.exe+1415D3 - 48 8B 93 00110000 - MOV RDX,[RBX+00001100]
		// Write<uint32>((appBaseAddr + 0x141733 + 3), (enable) ? newOff : off); // dmc3.exe+141733 - 48 8B 93 00110000 - MOV RDX,[RBX+00001100]
		// Write<uint32>((appBaseAddr + 0x141A1C + 3), (enable) ? newOff : off); // dmc3.exe+141A1C - 48 8B 93 00110000 - MOV RDX,[RBX+00001100]
		// Write<uint32>((appBaseAddr + 0x141E29 + 3), (enable) ? newOff : off); // dmc3.exe+141E29 - 48 8B 93 00110000 - MOV RDX,[RBX+00001100]
		// Write<uint32>((appBaseAddr + 0x141F50 + 3), (enable) ? newOff : off); // dmc3.exe+141F50 - 48 8B 93 00110000 - MOV RDX,[RBX+00001100]
		// Write<uint32>((appBaseAddr + 0x142B7B + 3), (enable) ? newOff : off); // dmc3.exe+142B7B - 48 8B 93 00110000 - MOV RDX,[RBX+00001100]
		// Write<uint32>((appBaseAddr + 0x142C11 + 3), (enable) ? newOff : off); // dmc3.exe+142C11 - 48 8B 93 00110000 - MOV RDX,[RBX+00001100]
		// Write<uint32>((appBaseAddr + 0x165F5A + 3), (enable) ? newOff : off); // dmc3.exe+165F5A - 48 8B 81 00110000 - MOV RAX,[RCX+00001100]
		// Write<uint32>((appBaseAddr + 0x165F7A + 3), (enable) ? newOff : off); // dmc3.exe+165F7A - 48 89 B9 00110000 - MOV [RCX+00001100],RDI
		// Write<uint32>((appBaseAddr + 0x165F81 + 3), (enable) ? newOff : off); // dmc3.exe+165F81 - 48 8B 89 00110000 - MOV RCX,[RCX+00001100]
		// Write<uint32>((appBaseAddr + 0x165F92 + 3), (enable) ? newOff : off); // dmc3.exe+165F92 - 48 89 BB 00110000 - MOV [RBX+00001100],RDI
		// Write<uint32>((appBaseAddr + 0x16601A + 3), (enable) ? newOff : off); // dmc3.exe+16601A - 48 8B 81 00110000 - MOV RAX,[RCX+00001100]
		// Write<uint32>((appBaseAddr + 0x16603A + 3), (enable) ? newOff : off); // dmc3.exe+16603A - 48 89 B9 00110000 - MOV [RCX+00001100],RDI
		// Write<uint32>((appBaseAddr + 0x166041 + 3), (enable) ? newOff : off); // dmc3.exe+166041 - 48 39 B9 00110000 - CMP [RCX+00001100],RDI
		// Write<uint32>((appBaseAddr + 0x166061 + 3), (enable) ? newOff : off); // dmc3.exe+166061 - 48 89 83 00110000 - MOV [RBX+00001100],RAX
		// Write<uint32>((appBaseAddr + 0x16608C + 3), (enable) ? newOff : off); // dmc3.exe+16608C - 48 8B 83 00110000 - MOV RAX,[RBX+00001100]
		// Trash<uint32>((appBaseAddr + 0x197B31 + 3), (enable) ? newOff : off); // dmc3.exe+197B31 - C7 85 00110000 00001643 - MOV [RBP+00001100],43160000
		// Trash<uint32>((appBaseAddr + 0x1A0655 + 3), (enable) ? newOff : off); // dmc3.exe+1A0655 - 0F29 87 00110000 - MOVAPS [RDI+00001100],XMM0
		// Write<uint32>((appBaseAddr + 0x1A068A + 3), (enable) ? newOff : off); // dmc3.exe+1A068A - 4C 8D 8F 00110000 - LEA R9,[RDI+00001100]
		// Write<uint32>((appBaseAddr + 0x1A9C9C + 3), (enable) ? newOff : off); // dmc3.exe+1A9C9C - 48 8D 94 24 00110000 - LEA RDX,[RSP+00001100]
		// Trash<uint32>((appBaseAddr + 0x1A9CF5 + 3), (enable) ? newOff : off); // dmc3.exe+1A9CF5 - 44 39 84 84 00110000 - CMP [RSP+RAX*4+00001100],R8D
		// Trash<uint32>((appBaseAddr + 0x1A9D0D + 3), (enable) ? newOff : off); // dmc3.exe+1A9D0D - 44 89 84 94 00110000 - MOV [RSP+RDX*4+00001100],R8D
		// Trash<uint32>((appBaseAddr + 0x1A9D50 + 3), (enable) ? newOff : off); // dmc3.exe+1A9D50 - 8B 94 AC 00110000 - MOV EDX,[RSP+RBP*4+00001100]
		Write<uint32>((appBaseAddr + 0x1EF188 + 3), (enable) ? newOff : off); // dmc3.exe+1EF188 - 49 8B 85 00110000 - MOV RAX,[R13+00001100]
		Write<uint32>((appBaseAddr + 0x1EF19C + 3), (enable) ? newOff : off); // dmc3.exe+1EF19C - 49 8D 8D 00110000 - LEA RCX,[R13+00001100]
		Write<uint32>((appBaseAddr + 0x1EF1A9 + 3), (enable) ? newOff : off); // dmc3.exe+1EF1A9 - 49 8D 8D 00110000 - LEA RCX,[R13+00001100]
		Write<uint32>((appBaseAddr + 0x1EF1BF + 3), (enable) ? newOff : off); // dmc3.exe+1EF1BF - 4D 8D B5 00110000 - LEA R14,[R13+00001100]
		// Write<uint32>((appBaseAddr + 0x26D4EA + 3), (enable) ? newOff : off); // dmc3.exe+26D4EA - 48 8D 8B 00110000 - LEA RCX,[RBX+00001100]
		// Write<uint32>((appBaseAddr + 0x26D5A0 + 3), (enable) ? newOff : off); // dmc3.exe+26D5A0 - 48 8D 8B 00110000 - LEA RCX,[RBX+00001100]
		// Write<uint32>((appBaseAddr + 0x26D9AD + 3), (enable) ? newOff : off); // dmc3.exe+26D9AD - 48 81 C1 00110000 - ADD RCX,00001100
		// Write<uint32>((appBaseAddr + 0x26DA41 + 3), (enable) ? newOff : off); // dmc3.exe+26DA41 - 48 8D 8F 00110000 - LEA RCX,[RDI+00001100]
		// Write<uint32>((appBaseAddr + 0x26DE54 + 3), (enable) ? newOff : off); // dmc3.exe+26DE54 - 48 8B BE 00110000 - MOV RDI,[RSI+00001100]
		// Write<uint32>((appBaseAddr + 0x26DE70 + 3), (enable) ? newOff : off); // dmc3.exe+26DE70 - 48 8D 8E 00110000 - LEA RCX,[RSI+00001100]
		// Write<uint32>((appBaseAddr + 0x26DF35 + 3), (enable) ? newOff : off); // dmc3.exe+26DF35 - 48 8D 8E 00110000 - LEA RCX,[RSI+00001100]
		// Wrong<uint32>((appBaseAddr + 0x296F6D + 3), (enable) ? newOff : off); // dmc3.exe+296F6D - 49 8B 85 00110000 - MOV RAX,[R13+00001100]
		// Wrong<uint32>((appBaseAddr + 0x296FC8 + 3), (enable) ? newOff : off); // dmc3.exe+296FC8 - 4D 89 85 00110000 - MOV [R13+00001100],R8
		// Trash<uint32>((appBaseAddr + 0x316075 + 3), (enable) ? newOff : off); // dmc3.exe+316075 - 49 B8 0000001001000000 - MOV R8,0000000110000000
		// Trash<uint32>((appBaseAddr + 0x316223 + 3), (enable) ? newOff : off); // dmc3.exe+316223 - 49 B9 0000001001000000 - MOV R9,0000000110000000
		// Write<uint32>((appBaseAddr + 0x34CEED + 3), (enable) ? newOff : off); // dmc3.exe+34CEED - 48 81 C1 00110000 - ADD RCX,00001100
		// Trash<uint32>((appBaseAddr + 0x3D74D3 + 3), (enable) ? newOff : off); // dmc3.exe+3D74D3 - 80 94 00 00001100 00 - ADC BYTE PTR [RAX+RAX+00110000],00
		// Trash<uint32>((appBaseAddr + 0x3DB76F + 3), (enable) ? newOff : off); // dmc3.exe+3DB76F - 80 94 00 00001100 00 - ADC BYTE PTR [RAX+RAX+00110000],00
		// Trash<uint32>((appBaseAddr + 0x52DA94 + 3), (enable) ? newOff : off); // dmc3.exe+52DA94 - 28 8C 34 00110000 - SUB [RSP+RSI+00001100],CL
		// Trash<uint32>((appBaseAddr + 0x52DBA1 + 3), (enable) ? newOff : off); // dmc3.exe+52DBA1 - 69 10 00110000 - IMUL EDX,[RAX]00001100
	}
	// 0x1108
	{
		constexpr auto off = (offsetof(ActorData, modelData[2]) + 8);
		constexpr auto newOff = (offsetof(ActorData, newModelData[2]) + 8);
		static_assert(off == 0x1108);
		Write<uint32>((appBaseAddr + 0x1EF1C6 + 3), (enable) ? newOff : off); // dmc3.exe+1EF1C6 - 49 8D AD 08110000 - lea rbp,[r13+00001108]
	}
	// 0x1880
	{
		constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][0]);
		constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][0]);
		static_assert(off == 0x1880);
		// Trash<uint32>((appBaseAddr + 0x3EDAE + 3), (enable) ? newOff : off); // dmc3.exe+3EDAE - B9 80180000 - MOV ECX,00001880
		// Trash<uint32>((appBaseAddr + 0x3EEBC + 3), (enable) ? newOff : off); // dmc3.exe+3EEBC - B9 80180000 - MOV ECX,00001880
		// Trash<uint32>((appBaseAddr + 0x4445E + 3), (enable) ? newOff : off); // dmc3.exe+4445E - 81 F9 80180000 - CMP ECX,00001880
		// Trash<uint32>((appBaseAddr + 0x44E92 + 3), (enable) ? newOff : off); // dmc3.exe+44E92 - 81 3D 18C45100 80180000 - CMP [005606B4],00001880
		Write<uint32>((appBaseAddr + 0x8C3B9 + 4), (enable) ? newOff : off); // dmc3.exe+8C3B9 - 49 8B 94 C4 80180000 - MOV RDX,[R12+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x8CB96 + 3), (enable) ? newOff : off); // dmc3.exe+8CB96 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x8CBB3 + 3), (enable) ? newOff : off); // dmc3.exe+8CBB3 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x8FA6B + 4), (enable) ? newOff : off); // dmc3.exe+8FA6B - 49 8B 94 C6 80180000 - MOV RDX,[R14+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x8FC47 + 4), (enable) ? newOff : off); // dmc3.exe+8FC47 - 49 8B 94 C6 80180000 - MOV RDX,[R14+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x9176B + 4), (enable) ? newOff : off); // dmc3.exe+9176B - 49 8B 94 C6 80180000 - MOV RDX,[R14+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x91D6F + 3), (enable) ? newOff : off); // dmc3.exe+91D6F - 49 8B 94 C6 80180000 - MOV RDX,[R14+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x91E9D + 4), (enable) ? newOff : off); // dmc3.exe+91E9D - 49 8B 94 C6 80180000 - MOV RDX,[R14+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x92289 + 4), (enable) ? newOff : off); // dmc3.exe+92289 - 49 8B 94 C6 80180000 - MOV RDX,[R14+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0xB9F5A + 3), (enable) ? newOff : off); // dmc3.exe+B9F5A - 48 8B 87 80180000 - MOV RAX,[RDI+00001880]
		// Write<uint32>((appBaseAddr + 0xD1CF1 + 3), (enable) ? newOff : off); // dmc3.exe+D1CF1 - 48 8D 8B 80180000 - LEA RCX,[RBX+00001880]
		Write<uint32>((appBaseAddr + 0xDA8A9 + 4), (enable) ? newOff : off); // dmc3.exe+DA8A9 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0xDA8C5 + 4), (enable) ? newOff : off); // dmc3.exe+DA8C5 - 48 8B 8C C7 80180000 - MOV RCX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0xDA8E7 + 4), (enable) ? newOff : off); // dmc3.exe+DA8E7 - 48 8B 8C C7 80180000 - MOV RCX,[RDI+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0xF7FB2 + 3), (enable) ? newOff : off); // dmc3.exe+F7FB2 - 48 8D 8E 80180000 - LEA RCX,[RSI+00001880]
		// Write<uint32>((appBaseAddr + 0xF8209 + 3), (enable) ? newOff : off); // dmc3.exe+F8209 - 48 81 C1 80180000 - ADD RCX,00001880
		// Write<uint32>((appBaseAddr + 0xFEA30 + 3), (enable) ? newOff : off); // dmc3.exe+FEA30 - 48 8D 8F 80180000 - LEA RCX,[RDI+00001880]
		// Write<uint32>((appBaseAddr + 0x150370 + 3), (enable) ? newOff : off); // dmc3.exe+150370 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x150395 + 3), (enable) ? newOff : off); // dmc3.exe+150395 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		// Trash<uint32>((appBaseAddr + 0x150C2D + 3), (enable) ? newOff : off); // dmc3.exe+150C2D - F3 0F10 87 80180000 - MOVSS XMM0,[RDI+00001880]
		// Trash<uint32>((appBaseAddr + 0x150C3E + 3), (enable) ? newOff : off); // dmc3.exe+150C3E - F3 0F11 87 80180000 - MOVSS [RDI+00001880],XMM0
		// Trash<uint32>((appBaseAddr + 0x150C4C + 3), (enable) ? newOff : off); // dmc3.exe+150C4C - 89 9F 80180000 - MOV [RDI+00001880],EBX
		// Trash<uint32>((appBaseAddr + 0x150C52 + 3), (enable) ? newOff : off); // dmc3.exe+150C52 - F3 48 0F2C B7 80180000 - CVTTSS2SI RSI,[RDI+00001880]
		// Trash<uint32>((appBaseAddr + 0x150CA9 + 3), (enable) ? newOff : off); // dmc3.exe+150CA9 - F3 48 0F2C B7 80180000 - CVTTSS2SI RSI,[RDI+00001880]
		// Trash<uint32>((appBaseAddr + 0x150D7B + 3), (enable) ? newOff : off); // dmc3.exe+150D7B - C7 87 80180000 00000043 - MOV [RDI+00001880],43000000
		// Trash<uint32>((appBaseAddr + 0x150DA5 + 3), (enable) ? newOff : off); // dmc3.exe+150DA5 - F3 48 0F2C 9F 80180000 - CVTTSS2SI RBX,[RDI+00001880]
		// Write<uint32>((appBaseAddr + 0x16FC58 + 3), (enable) ? newOff : off); // dmc3.exe+16FC58 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x173072 + 3), (enable) ? newOff : off); // dmc3.exe+173072 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x173D52 + 3), (enable) ? newOff : off); // dmc3.exe+173D52 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x17C39B + 3), (enable) ? newOff : off); // dmc3.exe+17C39B - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x17C784 + 3), (enable) ? newOff : off); // dmc3.exe+17C784 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x17D694 + 3), (enable) ? newOff : off); // dmc3.exe+17D694 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x17DA05 + 3), (enable) ? newOff : off); // dmc3.exe+17DA05 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x188FB0 + 3), (enable) ? newOff : off); // dmc3.exe+188FB0 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x1892AF + 3), (enable) ? newOff : off); // dmc3.exe+1892AF - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1A35EB + 4), (enable) ? newOff : off); // dmc3.exe+1A35EB - 48 8B 8C C7 80180000 - MOV RCX,[RDI+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x1A36FF + 3), (enable) ? newOff : off); // dmc3.exe+1A36FF - 48 8B 8C C7 80180000 - MOV RCX,[RDI+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x1B2266 + 3), (enable) ? newOff : off); // dmc3.exe+1B2266 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1DE92E + 3), (enable) ? newOff : off); // dmc3.exe+1DE92E - 48 8D 90 80180000 - LEA RDX,[RAX+00001880]
		Write<uint32>((appBaseAddr + 0x1DEA47 + 3), (enable) ? newOff : off); // dmc3.exe+1DEA47 - 48 8D 90 80180000 - LEA RDX,[RAX+00001880]
		Write<uint32>((appBaseAddr + 0x1DEB43 + 3), (enable) ? newOff : off); // dmc3.exe+1DEB43 - 48 8D 90 80180000 - LEA RDX,[RAX+00001880]
		Write<uint32>((appBaseAddr + 0x1DEC5C + 3), (enable) ? newOff : off); // dmc3.exe+1DEC5C - 48 8D 90 80180000 - LEA RDX,[RAX+00001880]
		Write<uint32>((appBaseAddr + 0x1E946F + 4), (enable) ? newOff : off); // dmc3.exe+1E946F - 48 8B 8C C7 80180000 - MOV RCX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1EAE89 + 4), (enable) ? newOff : off); // dmc3.exe+1EAE89 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1EAEE9 + 4), (enable) ? newOff : off); // dmc3.exe+1EAEE9 - 4C 8D 0C C5 80180000 - LEA R9,[RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1EAF20 + 4), (enable) ? newOff : off); // dmc3.exe+1EAF20 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1EAF79 + 4), (enable) ? newOff : off); // dmc3.exe+1EAF79 - 48 8D 0C C5 80180000 - LEA RCX,[RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x1ED840 + 3), (enable) ? newOff : off); // dmc3.exe+1ED840 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x1ED8E2 + 3), (enable) ? newOff : off); // dmc3.exe+1ED8E2 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x1ED920 + 3), (enable) ? newOff : off); // dmc3.exe+1ED920 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1ED9AA + 4), (enable) ? newOff : off); // dmc3.exe+1ED9AA - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x1EDACF + 3), (enable) ? newOff : off); // dmc3.exe+1EDACF - 48 8B 94 CF 80180000 - MOV RDX,[RDI+RCX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1EDB5B + 4), (enable) ? newOff : off); // dmc3.exe+1EDB5B - 48 8B 8C C7 80180000 - MOV RCX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1EDCB4 + 4), (enable) ? newOff : off); // dmc3.exe+1EDCB4 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x1EE62E + 3), (enable) ? newOff : off); // dmc3.exe+1EE62E - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x1EE690 + 3), (enable) ? newOff : off); // dmc3.exe+1EE690 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x1EE6ED + 3), (enable) ? newOff : off); // dmc3.exe+1EE6ED - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1EF3ED + 3), (enable) ? newOff : off); // dmc3.exe+1EF3ED - 4D 8D B5 80180000 - LEA R14,[R13+00001880]
		// Write<uint32>((appBaseAddr + 0x1F0764 + 3), (enable) ? newOff : off); // dmc3.exe+1F0764 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F08D5 + 4), (enable) ? newOff : off); // dmc3.exe+1F08D5 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F0D12 + 4), (enable) ? newOff : off); // dmc3.exe+1F0D12 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F0D94 + 4), (enable) ? newOff : off); // dmc3.exe+1F0D94 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x1F0DC6 + 3), (enable) ? newOff : off); // dmc3.exe+1F0DC6 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x1F0FE6 + 3), (enable) ? newOff : off); // dmc3.exe+1F0FE6 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F15D5 + 4), (enable) ? newOff : off); // dmc3.exe+1F15D5 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F1B2B + 4), (enable) ? newOff : off); // dmc3.exe+1F1B2B - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F1EC0 + 4), (enable) ? newOff : off); // dmc3.exe+1F1EC0 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F22E4 + 4), (enable) ? newOff : off); // dmc3.exe+1F22E4 - 4C 8B 84 C7 80180000 - MOV R8,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F2ECB + 4), (enable) ? newOff : off); // dmc3.exe+1F2ECB - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F2FEC + 4), (enable) ? newOff : off); // dmc3.exe+1F2FEC - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F353C + 4), (enable) ? newOff : off); // dmc3.exe+1F353C - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F359E + 4), (enable) ? newOff : off); // dmc3.exe+1F359E - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F35EB + 4), (enable) ? newOff : off); // dmc3.exe+1F35EB - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F3669 + 4), (enable) ? newOff : off); // dmc3.exe+1F3669 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F3721 + 4), (enable) ? newOff : off); // dmc3.exe+1F3721 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F39F4 + 4), (enable) ? newOff : off); // dmc3.exe+1F39F4 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x1F4118 + 4), (enable) ? newOff : off); // dmc3.exe+1F4118 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x1F4218 + 4), (enable) ? newOff : off); // dmc3.exe+1F4218 - 4C 8B 84 D3 80180000 - MOV R8,[RBX+RDX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x1F425D + 4), (enable) ? newOff : off); // dmc3.exe+1F425D - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F5721 + 4), (enable) ? newOff : off); // dmc3.exe+1F5721 - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x1F61AF + 4), (enable) ? newOff : off); // dmc3.exe+1F61AF - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F62DD + 4), (enable) ? newOff : off); // dmc3.exe+1F62DD - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F6306 + 4), (enable) ? newOff : off); // dmc3.exe+1F6306 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F6350 + 4), (enable) ? newOff : off); // dmc3.exe+1F6350 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F65BE + 4), (enable) ? newOff : off); // dmc3.exe+1F65BE - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F7846 + 4), (enable) ? newOff : off); // dmc3.exe+1F7846 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x1F7CEE + 4), (enable) ? newOff : off); // dmc3.exe+1F7CEE - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F81DE + 4), (enable) ? newOff : off); // dmc3.exe+1F81DE - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F9791 + 4), (enable) ? newOff : off); // dmc3.exe+1F9791 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x1FA61A + 4), (enable) ? newOff : off); // dmc3.exe+1FA61A - 48 8B 94 CB 80180000 - MOV RDX,[RBX+RCX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x1FAA81 + 4), (enable) ? newOff : off); // dmc3.exe+1FAA81 - 48 8B 84 C1 80180000 - MOV RAX,[RCX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1FAAA5 + 4), (enable) ? newOff : off); // dmc3.exe+1FAAA5 - 4A 8B 84 C1 80180000 - MOV RAX,[RCX+R8*8+00001880]
		Write<uint32>((appBaseAddr + 0x1FB059 + 4), (enable) ? newOff : off); // dmc3.exe+1FB059 - 4E 8B 8C CB 80180000 - MOV R9,[RBX+R9*8+00001880]
		Write<uint32>((appBaseAddr + 0x1FB065 + 4), (enable) ? newOff : off); // dmc3.exe+1FB065 - 4E 8B 84 C3 80180000 - MOV R8,[RBX+R8*8+00001880]
		Write<uint32>((appBaseAddr + 0x1FB070 + 4), (enable) ? newOff : off); // dmc3.exe+1FB070 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1FB09B + 4), (enable) ? newOff : off); // dmc3.exe+1FB09B - 4E 8B 8C CB 80180000 - MOV R9,[RBX+R9*8+00001880]
		Write<uint32>((appBaseAddr + 0x1FB0A7 + 4), (enable) ? newOff : off); // dmc3.exe+1FB0A7 - 4E 8B 84 C3 80180000 - MOV R8,[RBX+R8*8+00001880]
		Write<uint32>((appBaseAddr + 0x1FB0B2 + 4), (enable) ? newOff : off); // dmc3.exe+1FB0B2 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1FBAE5 + 4), (enable) ? newOff : off); // dmc3.exe+1FBAE5 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1FBBE3 + 4), (enable) ? newOff : off); // dmc3.exe+1FBBE3 - 48 8B 8C CB 80180000 - MOV RCX,[RBX+RCX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1FEE63 + 4), (enable) ? newOff : off); // dmc3.exe+1FEE63 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1FEF97 + 4), (enable) ? newOff : off); // dmc3.exe+1FEF97 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1FFB74 + 4), (enable) ? newOff : off); // dmc3.exe+1FFB74 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1FFD5B + 4), (enable) ? newOff : off); // dmc3.exe+1FFD5B - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1FFFCC + 4), (enable) ? newOff : off); // dmc3.exe+1FFFCC - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x200604 + 4), (enable) ? newOff : off); // dmc3.exe+200604 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20121A + 4), (enable) ? newOff : off); // dmc3.exe+20121A - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20136A + 4), (enable) ? newOff : off); // dmc3.exe+20136A - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x201471 + 4), (enable) ? newOff : off); // dmc3.exe+201471 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x201659 + 4), (enable) ? newOff : off); // dmc3.exe+201659 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x201696 + 4), (enable) ? newOff : off); // dmc3.exe+201696 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x201B74 + 4), (enable) ? newOff : off); // dmc3.exe+201B74 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x201D2E + 4), (enable) ? newOff : off); // dmc3.exe+201D2E - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x202155 + 4), (enable) ? newOff : off); // dmc3.exe+202155 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2021F9 + 4), (enable) ? newOff : off); // dmc3.exe+2021F9 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2026ED + 4), (enable) ? newOff : off); // dmc3.exe+2026ED - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x202974 + 4), (enable) ? newOff : off); // dmc3.exe+202974 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x202A64 + 4), (enable) ? newOff : off); // dmc3.exe+202A64 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x203160 + 4), (enable) ? newOff : off); // dmc3.exe+203160 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2032F2 + 4), (enable) ? newOff : off); // dmc3.exe+2032F2 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20381D + 4), (enable) ? newOff : off); // dmc3.exe+20381D - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x203A34 + 4), (enable) ? newOff : off); // dmc3.exe+203A34 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x203AE7 + 4), (enable) ? newOff : off); // dmc3.exe+203AE7 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x204159 + 4), (enable) ? newOff : off); // dmc3.exe+204159 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2041CE + 4), (enable) ? newOff : off); // dmc3.exe+2041CE - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20445E + 4), (enable) ? newOff : off); // dmc3.exe+20445E - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20454F + 4), (enable) ? newOff : off); // dmc3.exe+20454F - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2049FF + 4), (enable) ? newOff : off); // dmc3.exe+2049FF - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x205A15 + 4), (enable) ? newOff : off); // dmc3.exe+205A15 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x205BF3 + 4), (enable) ? newOff : off); // dmc3.exe+205BF3 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x205D66 + 4), (enable) ? newOff : off); // dmc3.exe+205D66 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x207241 + 4), (enable) ? newOff : off); // dmc3.exe+207241 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x209391 + 4), (enable) ? newOff : off); // dmc3.exe+209391 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x209AD0 + 4), (enable) ? newOff : off); // dmc3.exe+209AD0 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x209E14 + 4), (enable) ? newOff : off); // dmc3.exe+209E14 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x209E67 + 4), (enable) ? newOff : off); // dmc3.exe+209E67 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x209FBA + 4), (enable) ? newOff : off); // dmc3.exe+209FBA - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20A0A0 + 4), (enable) ? newOff : off); // dmc3.exe+20A0A0 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20A127 + 4), (enable) ? newOff : off); // dmc3.exe+20A127 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20A230 + 4), (enable) ? newOff : off); // dmc3.exe+20A230 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20A301 + 4), (enable) ? newOff : off); // dmc3.exe+20A301 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20A7F4 + 4), (enable) ? newOff : off); // dmc3.exe+20A7F4 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20AA63 + 4), (enable) ? newOff : off); // dmc3.exe+20AA63 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x20ABFC + 4), (enable) ? newOff : off); // dmc3.exe+20ABFC - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20AF79 + 4), (enable) ? newOff : off); // dmc3.exe+20AF79 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20B02B + 4), (enable) ? newOff : off); // dmc3.exe+20B02B - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20B230 + 4), (enable) ? newOff : off); // dmc3.exe+20B230 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20B283 + 4), (enable) ? newOff : off); // dmc3.exe+20B283 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20B7A4 + 4), (enable) ? newOff : off); // dmc3.exe+20B7A4 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20B7CA + 4), (enable) ? newOff : off); // dmc3.exe+20B7CA - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20BD9F + 4), (enable) ? newOff : off); // dmc3.exe+20BD9F - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20BDC5 + 4), (enable) ? newOff : off); // dmc3.exe+20BDC5 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20C322 + 4), (enable) ? newOff : off); // dmc3.exe+20C322 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20C359 + 4), (enable) ? newOff : off); // dmc3.exe+20C359 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20C411 + 4), (enable) ? newOff : off); // dmc3.exe+20C411 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20C51B + 4), (enable) ? newOff : off); // dmc3.exe+20C51B - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20C72B + 4), (enable) ? newOff : off); // dmc3.exe+20C72B - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20CAA2 + 4), (enable) ? newOff : off); // dmc3.exe+20CAA2 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20D75E + 4), (enable) ? newOff : off); // dmc3.exe+20D75E - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20DBFE + 4), (enable) ? newOff : off); // dmc3.exe+20DBFE - 48 8B 94 CB 80180000 - MOV RDX,[RBX+RCX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20DD00 + 4), (enable) ? newOff : off); // dmc3.exe+20DD00 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20DFED + 4), (enable) ? newOff : off); // dmc3.exe+20DFED - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20E1AB + 4), (enable) ? newOff : off); // dmc3.exe+20E1AB - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20E6C6 + 4), (enable) ? newOff : off); // dmc3.exe+20E6C6 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20EC4F + 4), (enable) ? newOff : off); // dmc3.exe+20EC4F - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20EE46 + 4), (enable) ? newOff : off); // dmc3.exe+20EE46 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20F166 + 4), (enable) ? newOff : off); // dmc3.exe+20F166 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20F3B2 + 4), (enable) ? newOff : off); // dmc3.exe+20F3B2 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x20FCAA + 4), (enable) ? newOff : off); // dmc3.exe+20FCAA - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20FDFA + 4), (enable) ? newOff : off); // dmc3.exe+20FDFA - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20FF43 + 4), (enable) ? newOff : off); // dmc3.exe+20FF43 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2101E2 + 4), (enable) ? newOff : off); // dmc3.exe+2101E2 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2106FE + 4), (enable) ? newOff : off); // dmc3.exe+2106FE - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x210829 + 4), (enable) ? newOff : off); // dmc3.exe+210829 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x210CA2 + 4), (enable) ? newOff : off); // dmc3.exe+210CA2 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2114AC + 4), (enable) ? newOff : off); // dmc3.exe+2114AC - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2119E6 + 4), (enable) ? newOff : off); // dmc3.exe+2119E6 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x211BAC + 4), (enable) ? newOff : off); // dmc3.exe+211BAC - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x212190 + 4), (enable) ? newOff : off); // dmc3.exe+212190 - 4C 8B 84 C6 80180000 - MOV R8,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2121F3 + 4), (enable) ? newOff : off); // dmc3.exe+2121F3 - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x212272 + 4), (enable) ? newOff : off); // dmc3.exe+212272 - 4C 8B 84 C6 80180000 - MOV R8,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2122D5 + 4), (enable) ? newOff : off); // dmc3.exe+2122D5 - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x212340 + 4), (enable) ? newOff : off); // dmc3.exe+212340 - 4C 8B 84 C1 80180000 - MOV R8,[RCX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2123A3 + 4), (enable) ? newOff : off); // dmc3.exe+2123A3 - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x212422 + 4), (enable) ? newOff : off); // dmc3.exe+212422 - 4C 8B 84 C6 80180000 - MOV R8,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x212485 + 4), (enable) ? newOff : off); // dmc3.exe+212485 - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x212504 + 4), (enable) ? newOff : off); // dmc3.exe+212504 - 4C 8B 84 C6 80180000 - MOV R8,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x212567 + 4), (enable) ? newOff : off); // dmc3.exe+212567 - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2125CF + 4), (enable) ? newOff : off); // dmc3.exe+2125CF - 4C 8B 84 C1 80180000 - MOV R8,[RCX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x212632 + 4), (enable) ? newOff : off); // dmc3.exe+212632 - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21266C + 4), (enable) ? newOff : off); // dmc3.exe+21266C - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2126D7 + 4), (enable) ? newOff : off); // dmc3.exe+2126D7 - 4C 8B 84 C6 80180000 - MOV R8,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21273A + 4), (enable) ? newOff : off); // dmc3.exe+21273A - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2129AA + 4), (enable) ? newOff : off); // dmc3.exe+2129AA - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x213814 + 4), (enable) ? newOff : off); // dmc3.exe+213814 - 48 8B 8C C6 80180000 - MOV RCX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x213873 + 4), (enable) ? newOff : off); // dmc3.exe+213873 - 48 8B 8C C6 80180000 - MOV RCX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2138D2 + 4), (enable) ? newOff : off); // dmc3.exe+2138D2 - 48 8B 8C C6 80180000 - MOV RCX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x213C18 + 4), (enable) ? newOff : off); // dmc3.exe+213C18 - 48 8B 8C C6 80180000 - MOV RCX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x213C79 + 4), (enable) ? newOff : off); // dmc3.exe+213C79 - 48 8B 8C C6 80180000 - MOV RCX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x213ECF + 4), (enable) ? newOff : off); // dmc3.exe+213ECF - 48 8B 8C C6 80180000 - MOV RCX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x213F30 + 4), (enable) ? newOff : off); // dmc3.exe+213F30 - 48 8B 8C C6 80180000 - MOV RCX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21440F + 4), (enable) ? newOff : off); // dmc3.exe+21440F - 48 8B 8C C6 80180000 - MOV RCX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21446B + 4), (enable) ? newOff : off); // dmc3.exe+21446B - 48 8B 8C C6 80180000 - MOV RCX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2144C7 + 4), (enable) ? newOff : off); // dmc3.exe+2144C7 - 48 8B 8C C6 80180000 - MOV RCX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2147EC + 4), (enable) ? newOff : off); // dmc3.exe+2147EC - 48 8B 8C C6 80180000 - MOV RCX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21484D + 4), (enable) ? newOff : off); // dmc3.exe+21484D - 48 8B 8C C6 80180000 - MOV RCX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x214A9A + 4), (enable) ? newOff : off); // dmc3.exe+214A9A - 48 8B 8C C6 80180000 - MOV RCX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x214AF8 + 4), (enable) ? newOff : off); // dmc3.exe+214AF8 - 48 8B 8C C6 80180000 - MOV RCX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2151C3 + 3), (enable) ? newOff : off); // dmc3.exe+2151C3 - 49 8D 96 80180000 - LEA RDX,[R14+00001880]
		Write<uint32>((appBaseAddr + 0x215373 + 3), (enable) ? newOff : off); // dmc3.exe+215373 - 49 8D 96 80180000 - LEA RDX,[R14+00001880]
		Write<uint32>((appBaseAddr + 0x21544F + 4), (enable) ? newOff : off); // dmc3.exe+21544F - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2160EF + 4), (enable) ? newOff : off); // dmc3.exe+2160EF - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x216129 + 4), (enable) ? newOff : off); // dmc3.exe+216129 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x216157 + 4), (enable) ? newOff : off); // dmc3.exe+216157 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x216289 + 4), (enable) ? newOff : off); // dmc3.exe+216289 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x2162C3 + 4), (enable) ? newOff : off); // dmc3.exe+2162C3 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2162F1 + 4), (enable) ? newOff : off); // dmc3.exe+2162F1 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21636C + 4), (enable) ? newOff : off); // dmc3.exe+21636C - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x216493 + 4), (enable) ? newOff : off); // dmc3.exe+216493 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2166C0 + 4), (enable) ? newOff : off); // dmc3.exe+2166C0 - 4C 8B 84 C7 80180000 - MOV R8,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21670F + 4), (enable) ? newOff : off); // dmc3.exe+21670F - 4C 8B 84 C7 80180000 - MOV R8,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21677F + 4), (enable) ? newOff : off); // dmc3.exe+21677F - 4C 8B 84 C7 80180000 - MOV R8,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2167EF + 4), (enable) ? newOff : off); // dmc3.exe+2167EF - 4C 8B 84 C7 80180000 - MOV R8,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21685F + 4), (enable) ? newOff : off); // dmc3.exe+21685F - 4C 8B 84 C7 80180000 - MOV R8,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2168CF + 4), (enable) ? newOff : off); // dmc3.exe+2168CF - 4C 8B 84 C7 80180000 - MOV R8,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21693F + 4), (enable) ? newOff : off); // dmc3.exe+21693F - 4C 8B 84 C7 80180000 - MOV R8,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2169AF + 4), (enable) ? newOff : off); // dmc3.exe+2169AF - 4C 8B 84 C7 80180000 - MOV R8,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x216BB5 + 4), (enable) ? newOff : off); // dmc3.exe+216BB5 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x216D3B + 4), (enable) ? newOff : off); // dmc3.exe+216D3B - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x216D8A + 4), (enable) ? newOff : off); // dmc3.exe+216D8A - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x216EF2 + 4), (enable) ? newOff : off); // dmc3.exe+216EF2 - 48 8B 8C C7 80180000 - MOV RCX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21709C + 4), (enable) ? newOff : off); // dmc3.exe+21709C - 48 8B 8C C7 80180000 - MOV RCX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21723B + 4), (enable) ? newOff : off); // dmc3.exe+21723B - 48 8B 8C C7 80180000 - MOV RCX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x217387 + 4), (enable) ? newOff : off); // dmc3.exe+217387 - 48 8B 8C C7 80180000 - MOV RCX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x218087 + 4), (enable) ? newOff : off); // dmc3.exe+218087 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x218278 + 4), (enable) ? newOff : off); // dmc3.exe+218278 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x218358 + 4), (enable) ? newOff : off); // dmc3.exe+218358 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x218A97 + 4), (enable) ? newOff : off); // dmc3.exe+218A97 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x218B2D + 4), (enable) ? newOff : off); // dmc3.exe+218B2D - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x218BE0 + 4), (enable) ? newOff : off); // dmc3.exe+218BE0 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x218C76 + 4), (enable) ? newOff : off); // dmc3.exe+218C76 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x218D0C + 4), (enable) ? newOff : off); // dmc3.exe+218D0C - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x218DBC + 4), (enable) ? newOff : off); // dmc3.exe+218DBC - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x218E52 + 4), (enable) ? newOff : off); // dmc3.exe+218E52 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2194B2 + 3), (enable) ? newOff : off); // dmc3.exe+2194B2 - 48 8D 95 80180000 - LEA RDX,[RBP+00001880]
		// Write<uint32>((appBaseAddr + 0x21A3CA + 4), (enable) ? newOff : off); // dmc3.exe+21A3CA - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x21B1EE + 4), (enable) ? newOff : off); // dmc3.exe+21B1EE - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21B9DD + 4), (enable) ? newOff : off); // dmc3.exe+21B9DD - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21BD4F + 4), (enable) ? newOff : off); // dmc3.exe+21BD4F - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21C0F6 + 4), (enable) ? newOff : off); // dmc3.exe+21C0F6 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21C4ED + 4), (enable) ? newOff : off); // dmc3.exe+21C4ED - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21C801 + 4), (enable) ? newOff : off); // dmc3.exe+21C801 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21C9A4 + 4), (enable) ? newOff : off); // dmc3.exe+21C9A4 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21CBC0 + 4), (enable) ? newOff : off); // dmc3.exe+21CBC0 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21CCF1 + 4), (enable) ? newOff : off); // dmc3.exe+21CCF1 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21CDE5 + 4), (enable) ? newOff : off); // dmc3.exe+21CDE5 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21CE48 + 4), (enable) ? newOff : off); // dmc3.exe+21CE48 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21D214 + 4), (enable) ? newOff : off); // dmc3.exe+21D214 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21D314 + 4), (enable) ? newOff : off); // dmc3.exe+21D314 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21DA7A + 4), (enable) ? newOff : off); // dmc3.exe+21DA7A - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21DAED + 4), (enable) ? newOff : off); // dmc3.exe+21DAED - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21DD32 + 4), (enable) ? newOff : off); // dmc3.exe+21DD32 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21DDF0 + 4), (enable) ? newOff : off); // dmc3.exe+21DDF0 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21DF4B + 4), (enable) ? newOff : off); // dmc3.exe+21DF4B - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21E0D3 + 4), (enable) ? newOff : off); // dmc3.exe+21E0D3 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21E3A2 + 4), (enable) ? newOff : off); // dmc3.exe+21E3A2 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21EB05 + 4), (enable) ? newOff : off); // dmc3.exe+21EB05 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21ED0A + 4), (enable) ? newOff : off); // dmc3.exe+21ED0A - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21EECA + 4), (enable) ? newOff : off); // dmc3.exe+21EECA - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21F014 + 4), (enable) ? newOff : off); // dmc3.exe+21F014 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21F6EC + 4), (enable) ? newOff : off); // dmc3.exe+21F6EC - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x21F8FE + 4), (enable) ? newOff : off); // dmc3.exe+21F8FE - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x21F9EF + 4), (enable) ? newOff : off); // dmc3.exe+21F9EF - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x21FADF + 4), (enable) ? newOff : off); // dmc3.exe+21FADF - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x21FC5B + 4), (enable) ? newOff : off); // dmc3.exe+21FC5B - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x21FCD1 + 4), (enable) ? newOff : off); // dmc3.exe+21FCD1 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x21FF27 + 4), (enable) ? newOff : off); // dmc3.exe+21FF27 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x220032 + 4), (enable) ? newOff : off); // dmc3.exe+220032 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x220059 + 4), (enable) ? newOff : off); // dmc3.exe+220059 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x22019D + 4), (enable) ? newOff : off); // dmc3.exe+22019D - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x2201D0 + 4), (enable) ? newOff : off); // dmc3.exe+2201D0 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x2202A5 + 4), (enable) ? newOff : off); // dmc3.exe+2202A5 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x220595 + 4), (enable) ? newOff : off); // dmc3.exe+220595 - 4C 8B 84 C6 80180000 - MOV R8,[RSI+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x2205EA + 4), (enable) ? newOff : off); // dmc3.exe+2205EA - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x22060A + 4), (enable) ? newOff : off); // dmc3.exe+22060A - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x220644 + 4), (enable) ? newOff : off); // dmc3.exe+220644 - 4C 8B 84 C6 80180000 - MOV R8,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22069D + 4), (enable) ? newOff : off); // dmc3.exe+22069D - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2206BD + 4), (enable) ? newOff : off); // dmc3.exe+2206BD - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22071E + 4), (enable) ? newOff : off); // dmc3.exe+22071E - 4C 8B 84 C6 80180000 - MOV R8,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x220777 + 4), (enable) ? newOff : off); // dmc3.exe+220777 - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x220797 + 4), (enable) ? newOff : off); // dmc3.exe+220797 - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2207C3 + 4), (enable) ? newOff : off); // dmc3.exe+2207C3 - 4C 8B 84 C6 80180000 - MOV R8,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22081C + 4), (enable) ? newOff : off); // dmc3.exe+22081C - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22083C + 4), (enable) ? newOff : off); // dmc3.exe+22083C - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x220894 + 4), (enable) ? newOff : off); // dmc3.exe+220894 - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x22112F + 4), (enable) ? newOff : off); // dmc3.exe+22112F - 49 8B 8C C4 80180000 - MOV RCX,[R12+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22148C + 4), (enable) ? newOff : off); // dmc3.exe+22148C - 49 8B 8C C4 80180000 - MOV RCX,[R12+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2214E5 + 4), (enable) ? newOff : off); // dmc3.exe+2214E5 - 49 8B 8C C4 80180000 - MOV RCX,[R12+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x221551 + 4), (enable) ? newOff : off); // dmc3.exe+221551 - 49 8B 8C C4 80180000 - MOV RCX,[R12+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22188B + 4), (enable) ? newOff : off); // dmc3.exe+22188B - 49 8B 8C C4 80180000 - MOV RCX,[R12+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2218F9 + 4), (enable) ? newOff : off); // dmc3.exe+2218F9 - 49 8B 8C C4 80180000 - MOV RCX,[R12+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x221B09 + 4), (enable) ? newOff : off); // dmc3.exe+221B09 - 49 8B 8C C4 80180000 - MOV RCX,[R12+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x221B71 + 4), (enable) ? newOff : off); // dmc3.exe+221B71 - 49 8B 8C C4 80180000 - MOV RCX,[R12+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x222653 + 3), (enable) ? newOff : off); // dmc3.exe+222653 - 48 8D 95 80180000 - LEA RDX,[RBP+00001880]
		// Write<uint32>((appBaseAddr + 0x2227D3 + 4), (enable) ? newOff : off); // dmc3.exe+2227D3 - 48 8D 95 80180000 - LEA RDX,[RBP+00001880]
		// Write<uint32>((appBaseAddr + 0x222C61 + 4), (enable) ? newOff : off); // dmc3.exe+222C61 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22316A + 4), (enable) ? newOff : off); // dmc3.exe+22316A - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2231DB + 4), (enable) ? newOff : off); // dmc3.exe+2231DB - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x223223 + 4), (enable) ? newOff : off); // dmc3.exe+223223 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x223295 + 4), (enable) ? newOff : off); // dmc3.exe+223295 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2232D9 + 4), (enable) ? newOff : off); // dmc3.exe+2232D9 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x223335 + 4), (enable) ? newOff : off); // dmc3.exe+223335 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x2233A8 + 4), (enable) ? newOff : off); // dmc3.exe+2233A8 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x2233EF + 4), (enable) ? newOff : off); // dmc3.exe+2233EF - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22464B + 4), (enable) ? newOff : off); // dmc3.exe+22464B - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2246DD + 4), (enable) ? newOff : off); // dmc3.exe+2246DD - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x224D88 + 4), (enable) ? newOff : off); // dmc3.exe+224D88 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x224ED8 + 4), (enable) ? newOff : off); // dmc3.exe+224ED8 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x225028 + 4), (enable) ? newOff : off); // dmc3.exe+225028 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2251F2 + 4), (enable) ? newOff : off); // dmc3.exe+2251F2 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22531D + 4), (enable) ? newOff : off); // dmc3.exe+22531D - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22553B + 4), (enable) ? newOff : off); // dmc3.exe+22553B - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x225602 + 4), (enable) ? newOff : off); // dmc3.exe+225602 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x225846 + 4), (enable) ? newOff : off); // dmc3.exe+225846 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2258AE + 4), (enable) ? newOff : off); // dmc3.exe+2258AE - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x225A40 + 3), (enable) ? newOff : off); // dmc3.exe+225A40 - 4C 8B 83 80180000 - MOV R8,[RBX+00001880]
		Write<uint32>((appBaseAddr + 0x225A93 + 3), (enable) ? newOff : off); // dmc3.exe+225A93 - 48 8B 93 80180000 - MOV RDX,[RBX+00001880]
		// Write<uint32>((appBaseAddr + 0x225B03 + 4), (enable) ? newOff : off); // dmc3.exe+225B03 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x225B5C + 4), (enable) ? newOff : off); // dmc3.exe+225B5C - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x225B83 + 4), (enable) ? newOff : off); // dmc3.exe+225B83 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x225BDD + 4), (enable) ? newOff : off); // dmc3.exe+225BDD - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x225C36 + 4), (enable) ? newOff : off); // dmc3.exe+225C36 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x225C56 + 4), (enable) ? newOff : off); // dmc3.exe+225C56 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x225C82 + 4), (enable) ? newOff : off); // dmc3.exe+225C82 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x225CDB + 4), (enable) ? newOff : off); // dmc3.exe+225CDB - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x225CFB + 4), (enable) ? newOff : off); // dmc3.exe+225CFB - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x225D47 + 4), (enable) ? newOff : off); // dmc3.exe+225D47 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2261BE + 3), (enable) ? newOff : off); // dmc3.exe+2261BE - 49 8D 96 80180000 - LEA RDX,[R14+00001880]
		Write<uint32>((appBaseAddr + 0x2265C7 + 4), (enable) ? newOff : off); // dmc3.exe+2265C7 - 49 8B 8C C6 80180000 - MOV RCX,[R14+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x226638 + 4), (enable) ? newOff : off); // dmc3.exe+226638 - 49 8B 8C C6 80180000 - MOV RCX,[R14+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2267CD + 4), (enable) ? newOff : off); // dmc3.exe+2267CD - 49 8B 8C C6 80180000 - MOV RCX,[R14+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22683E + 4), (enable) ? newOff : off); // dmc3.exe+22683E - 49 8B 8C C6 80180000 - MOV RCX,[R14+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x226B37 + 4), (enable) ? newOff : off); // dmc3.exe+226B37 - 49 8B 8C C6 80180000 - MOV RCX,[R14+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x226BA0 + 4), (enable) ? newOff : off); // dmc3.exe+226BA0 - 49 8B 8C C6 80180000 - MOV RCX,[R14+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x226BFD + 4), (enable) ? newOff : off); // dmc3.exe+226BFD - 49 8B 8C C6 80180000 - MOV RCX,[R14+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x226E08 + 4), (enable) ? newOff : off); // dmc3.exe+226E08 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x226E75 + 4), (enable) ? newOff : off); // dmc3.exe+226E75 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x226EE2 + 4), (enable) ? newOff : off); // dmc3.exe+226EE2 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22737C + 4), (enable) ? newOff : off); // dmc3.exe+22737C - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Trash<uint32>((appBaseAddr + 0x2588D9 + 4), (enable) ? newOff : off); // dmc3.exe+2588D9 - C7 83 80180000 00000000 - MOV [RBX+00001880],00000000
		// Trash<uint32>((appBaseAddr + 0x2596CE + 4), (enable) ? newOff : off); // dmc3.exe+2596CE - C7 82 80180000 00000100 - MOV [RDX+00001880],00010000
		// Write<uint32>((appBaseAddr + 0x25A9C7 + 4), (enable) ? newOff : off); // dmc3.exe+25A9C7 - 48 8D 97 80180000 - LEA RDX,[RDI+00001880]
		// Trash<uint32>((appBaseAddr + 0x25B0AE + 4), (enable) ? newOff : off); // dmc3.exe+25B0AE - C7 83 80180000 00000000 - MOV [RBX+00001880],00000000
		// Trash<uint32>((appBaseAddr + 0x25C019 + 4), (enable) ? newOff : off); // dmc3.exe+25C019 - C7 82 80180000 00000100 - MOV [RDX+00001880],00010000
		// Write<uint32>((appBaseAddr + 0x25D2B3 + 4), (enable) ? newOff : off); // dmc3.exe+25D2B3 - 48 8D 97 80180000 - LEA RDX,[RDI+00001880]
		Write<uint32>((appBaseAddr + 0x27A7E8 + 4), (enable) ? newOff : off); // dmc3.exe+27A7E8 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Trash<uint32>((appBaseAddr + 0x3313D7 + 4), (enable) ? newOff : off); // dmc3.exe+3313D7 - B8 80180000 - MOV EAX,00001880
		// Trash<uint32>((appBaseAddr + 0x598949 + 4), (enable) ? newOff : off); // dmc3.exe+598949 - 15 00001880 - ADC EAX,80180000
		// Trash<uint32>((appBaseAddr + 0x598959 + 4), (enable) ? newOff : off); // dmc3.exe+598959 - 15 00001880 - ADC EAX,80180000
		// Trash<uint32>((appBaseAddr + 0x598969 + 4), (enable) ? newOff : off); // dmc3.exe+598969 - 15 00001880 - ADC EAX,80180000
		// Trash<uint32>((appBaseAddr + 0x598979 + 4), (enable) ? newOff : off); // dmc3.exe+598979 - 15 00001880 - ADC EAX,80180000
		// Trash<uint32>((appBaseAddr + 0x5989C9 + 4), (enable) ? newOff : off); // dmc3.exe+5989C9 - 15 00001880 - ADC EAX,80180000
		// 0x310
		{
			constexpr auto off = (offsetof(ActorData, modelPhysicsMetadataPool[0][0]) / 8);
			constexpr auto newOff = (offsetof(ActorData, newModelPhysicsMetadataPool[0][0]) / 8);
			static_assert(off == 0x310);
			// Trash<uint32>((appBaseAddr + 0x8F750 + 3), (enable) ? newOff : off); // dmc3.exe+8F750 - 48 81 EC 10030000 - SUB RSP,00000310
			// Write<uint32>((appBaseAddr + 0x123DF9 + 3), (enable) ? newOff : off); // dmc3.exe+123DF9 - BA 10030000 - MOV EDX,00000310
			Write<uint32>((appBaseAddr + 0x1DF131 + 3), (enable) ? newOff : off); // dmc3.exe+1DF131 - 48 81 C3 10030000 - ADD RBX,00000310
			Write<uint32>((appBaseAddr + 0x213E42 + 2), (enable) ? newOff : off); // dmc3.exe+213E42 - 48 05 10030000 - ADD RAX,00000310
			Write<uint32>((appBaseAddr + 0x214A06 + 2), (enable) ? newOff : off); // dmc3.exe+214A06 - 48 05 10030000 - ADD RAX,00000310
			// Write<uint32>((appBaseAddr + 0x221077 + 3), (enable) ? newOff : off); // dmc3.exe+221077 - 48 05 10030000 - ADD RAX,00000310
			// Write<uint32>((appBaseAddr + 0x271850 + 3), (enable) ? newOff : off); // dmc3.exe+271850 - 48 81 C1 10030000 - ADD RCX,00000310
		}
	}
	// 0x1888
	{
		constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][1]);
		constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][1]);
		static_assert(off == 0x1888);
		// Write<uint32>((appBaseAddr + 0xBA9DE + 3), (enable) ? newOff : off); // dmc3.exe+BA9DE - 48 8B 96 88180000 - MOV RDX,[RSI+00001888]
		// Write<uint32>((appBaseAddr + 0xBAAE5 + 3), (enable) ? newOff : off); // dmc3.exe+BAAE5 - 48 8B 96 88180000 - MOV RDX,[RSI+00001888]
		// Trash<uint32>((appBaseAddr + 0x15096D + 3), (enable) ? newOff : off); // dmc3.exe+15096D - 0FBF 86 88180000 - MOVSX EAX,WORD PTR [RSI+00001888]
		// Trash<uint32>((appBaseAddr + 0x150997 + 3), (enable) ? newOff : off); // dmc3.exe+150997 - 66 89 86 88180000 - MOV [RSI+00001888],AX
		Write<uint32>((appBaseAddr + 0x1EF434 + 3), (enable) ? newOff : off); // dmc3.exe+1EF434 - 49 8B 85 88180000 - MOV RAX,[R13+00001888]
		Write<uint32>((appBaseAddr + 0x212096 + 3), (enable) ? newOff : off); // dmc3.exe+212096 - 4C 8B 86 88180000 - MOV R8,[RSI+00001888]
		Write<uint32>((appBaseAddr + 0x2120E6 + 3), (enable) ? newOff : off); // dmc3.exe+2120E6 - 48 8B 96 88180000 - MOV RDX,[RSI+00001888]
		Write<uint32>((appBaseAddr + 0x2191DF + 3), (enable) ? newOff : off); // dmc3.exe+2191DF - 4C 8B 81 88180000 - MOV R8,[RCX+00001888]
		Write<uint32>((appBaseAddr + 0x21922C + 3), (enable) ? newOff : off); // dmc3.exe+21922C - 48 8B 97 88180000 - MOV RDX,[RDI+00001888]
		Write<uint32>((appBaseAddr + 0x2204D4 + 3), (enable) ? newOff : off); // dmc3.exe+2204D4 - 4C 8B 81 88180000 - MOV R8,[RCX+00001888]
		Write<uint32>((appBaseAddr + 0x220528 + 3), (enable) ? newOff : off); // dmc3.exe+220528 - 48 8B 96 88180000 - MOV RDX,[RSI+00001888]
		// Write<uint32>((appBaseAddr + 0x2588E5 + 3), (enable) ? newOff : off); // dmc3.exe+2588E5 - 48 89 83 88180000 - MOV [RBX+00001888],RAX
		// Write<uint32>((appBaseAddr + 0x2596DF + 3), (enable) ? newOff : off); // dmc3.exe+2596DF - 48 89 92 88180000 - MOV [RDX+00001888],RDX
		// Write<uint32>((appBaseAddr + 0x25B0BA + 3), (enable) ? newOff : off); // dmc3.exe+25B0BA - 48 89 BB 88180000 - MOV [RBX+00001888],RDI
		// Write<uint32>((appBaseAddr + 0x25C02A + 3), (enable) ? newOff : off); // dmc3.exe+25C02A - 48 89 92 88180000 - MOV [RDX+00001888],RDX
	}
	// 0x1890
	{
		constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][2]);
		constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][2]);
		static_assert(off == 0x1890);
		// Write<uint32>((appBaseAddr + 0x1510CA + 3), (enable) ? newOff : off); // dmc3.exe+1510CA - 48 89 88 90180000 - MOV [RAX+00001890],RCX
		Write<uint32>((appBaseAddr + 0x1EF30A + 3), (enable) ? newOff : off); // dmc3.exe+1EF30A - 49 8B 85 90180000 - MOV RAX,[R13+00001890]
		// Write<uint32>((appBaseAddr + 0x2588EC + 3), (enable) ? newOff : off); // dmc3.exe+2588EC - 48 89 83 90180000 - MOV [RBX+00001890],RAX
		// Write<uint32>((appBaseAddr + 0x2596E6 + 3), (enable) ? newOff : off); // dmc3.exe+2596E6 - 48 89 82 90180000 - MOV [RDX+00001890],RAX
		// Write<uint32>((appBaseAddr + 0x25B0C1 + 3), (enable) ? newOff : off); // dmc3.exe+25B0C1 - 48 89 BB 90180000 - MOV [RBX+00001890],RDI
		// Write<uint32>((appBaseAddr + 0x25C031 + 3), (enable) ? newOff : off); // dmc3.exe+25C031 - 48 89 82 90180000 - MOV [RDX+00001890],RAX
	}
	// 0x1898
	{
		constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][3]);
		constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][3]);
		static_assert(off == 0x1898);
		// Write<uint32>((appBaseAddr + 0xB9DF1 + 3), (enable) ? newOff : off); // dmc3.exe+B9DF1 - 48 8B 87 98180000 - MOV RAX,[RDI+00001898]
		// Write<uint32>((appBaseAddr + 0xBA06E + 3), (enable) ? newOff : off); // dmc3.exe+BA06E - 48 8B 8F 98180000 - MOV RCX,[RDI+00001898]
		// Write<uint32>((appBaseAddr + 0xBA9F4 + 3), (enable) ? newOff : off); // dmc3.exe+BA9F4 - 48 8B 96 98180000 - MOV RDX,[RSI+00001898]
		// Write<uint32>((appBaseAddr + 0xBAAFB + 3), (enable) ? newOff : off); // dmc3.exe+BAAFB - 48 8B 96 98180000 - MOV RDX,[RSI+00001898]
		// Write<uint32>((appBaseAddr + 0xC75A7 + 3), (enable) ? newOff : off); // dmc3.exe+C75A7 - 48 8B 96 98180000 - MOV RDX,[RSI+00001898]
		// Write<uint32>((appBaseAddr + 0xC7A1D + 3), (enable) ? newOff : off); // dmc3.exe+C7A1D - 48 8B 97 98180000 - MOV RDX,[RDI+00001898]
		// Write<uint32>((appBaseAddr + 0xC823B + 3), (enable) ? newOff : off); // dmc3.exe+C823B - 48 8B 85 98180000 - MOV RAX,[RBP+00001898]
		// Write<uint32>((appBaseAddr + 0xCB18E + 3), (enable) ? newOff : off); // dmc3.exe+CB18E - 48 8B 8E 98180000 - MOV RCX,[RSI+00001898]
		// Trash<uint32>((appBaseAddr + 0xE8872 + 3), (enable) ? newOff : off); // dmc3.exe+E8872 - C7 83 98180000 00000000 - MOV [RBX+00001898],00000000
		Write<uint32>((appBaseAddr + 0x1EF1DE + 3), (enable) ? newOff : off); // dmc3.exe+1EF1DE - 49 8B 85 98180000 - MOV RAX,[R13+00001898]
		Write<uint32>((appBaseAddr + 0x2120C4 + 3), (enable) ? newOff : off); // dmc3.exe+2120C4 - 48 8B 96 98180000 - MOV RDX,[RSI+00001898]
		Write<uint32>((appBaseAddr + 0x218EFD + 3), (enable) ? newOff : off); // dmc3.exe+218EFD - 48 8B 97 98180000 - MOV RDX,[RDI+00001898]
		Write<uint32>((appBaseAddr + 0x218F67 + 3), (enable) ? newOff : off); // dmc3.exe+218F67 - 48 8B 97 98180000 - MOV RDX,[RDI+00001898]
		Write<uint32>((appBaseAddr + 0x220506 + 3), (enable) ? newOff : off); // dmc3.exe+220506 - 48 8B 96 98180000 - MOV RDX,[RSI+00001898]
		Write<uint32>((appBaseAddr + 0x223068 + 3), (enable) ? newOff : off); // dmc3.exe+223068 - 4C 8B 81 98180000 - MOV R8,[RCX+00001898]
		Write<uint32>((appBaseAddr + 0x2230AA + 3), (enable) ? newOff : off); // dmc3.exe+2230AA - 4C 8B 83 98180000 - MOV R8,[RBX+00001898]
		Write<uint32>((appBaseAddr + 0x2230E0 + 3), (enable) ? newOff : off); // dmc3.exe+2230E0 - 48 8B 93 98180000 - MOV RDX,[RBX+00001898]
		Write<uint32>((appBaseAddr + 0x2243FB + 3), (enable) ? newOff : off); // dmc3.exe+2243FB - 48 8B 93 98180000 - MOV RDX,[RBX+00001898]
		// Write<uint32>((appBaseAddr + 0x22445B + 3), (enable) ? newOff : off); // dmc3.exe+22445B - 48 8B 93 98180000 - MOV RDX,[RBX+00001898]
		Write<uint32>((appBaseAddr + 0x225A71 + 3), (enable) ? newOff : off); // dmc3.exe+225A71 - 48 8B 93 98180000 - MOV RDX,[RBX+00001898]
		Write<uint32>((appBaseAddr + 0x226D86 + 3), (enable) ? newOff : off); // dmc3.exe+226D86 - 4C 8B 81 98180000 - MOV R8,[RCX+00001898]
		Write<uint32>((appBaseAddr + 0x2272D1 + 3), (enable) ? newOff : off); // dmc3.exe+2272D1 - 48 8B 93 98180000 - MOV RDX,[RBX+00001898]
		// Write<uint32>((appBaseAddr + 0x2588F3 + 3), (enable) ? newOff : off); // dmc3.exe+2588F3 - 48 89 83 98180000 - MOV [RBX+00001898],RAX
		// Write<uint32>((appBaseAddr + 0x2596ED + 3), (enable) ? newOff : off); // dmc3.exe+2596ED - 48 89 8A 98180000 - MOV [RDX+00001898],RCX
		// Write<uint32>((appBaseAddr + 0x25B0C8 + 3), (enable) ? newOff : off); // dmc3.exe+25B0C8 - 48 89 BB 98180000 - MOV [RBX+00001898],RDI
		// Write<uint32>((appBaseAddr + 0x25C038 + 3), (enable) ? newOff : off); // dmc3.exe+25C038 - 48 89 8A 98180000 - MOV [RDX+00001898],RCX
		// Write<uint32>((appBaseAddr + 0x29D970 + 3), (enable) ? newOff : off); // dmc3.exe+29D970 - 49 8B 83 98180000 - MOV RAX,[R11+00001898]
		// Write<uint32>((appBaseAddr + 0x29DB70 + 3), (enable) ? newOff : off); // dmc3.exe+29DB70 - 49 8B 83 98180000 - MOV RAX,[R11+00001898]
		// Write<uint32>((appBaseAddr + 0x29DD10 + 3), (enable) ? newOff : off); // dmc3.exe+29DD10 - 48 8B 83 98180000 - MOV RAX,[RBX+00001898]
	}
	// 0x18A8
	{
		constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][5]);
		constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][5]);
		static_assert(off == 0x18A8);
		Write<uint32>((appBaseAddr + 0x986CE + 3), (enable) ? newOff : off); // dmc3.exe+986CE - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		// Write<uint32>((appBaseAddr + 0x9DB24 + 3), (enable) ? newOff : off); // dmc3.exe+9DB24 - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0xA2A55 + 3), (enable) ? newOff : off); // dmc3.exe+A2A55 - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		// Mission3<uint32>((appBaseAddr + 0xA78C7 + 3), (enable) ? newOff : off); // dmc3.exe+A78C7 - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0xA8F8D + 3), (enable) ? newOff : off); // dmc3.exe+A8F8D - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		// Write<uint32>((appBaseAddr + 0xAB6DA + 3), (enable) ? newOff : off); // dmc3.exe+AB6DA - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		// Mission19<uint32>((appBaseAddr + 0xB04AF + 3), (enable) ? newOff : off); // dmc3.exe+B04AF - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		// Write<uint32>((appBaseAddr + 0xB2B09 + 3), (enable) ? newOff : off); // dmc3.exe+B2B09 - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0xB685E + 3), (enable) ? newOff : off); // dmc3.exe+B685E - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		// Write<uint32>((appBaseAddr + 0xD1C4B + 3), (enable) ? newOff : off); // dmc3.exe+D1C4B - 48 8D 8B A8180000 - LEA RCX,[RBX+000018A8]
		// Write<uint32>((appBaseAddr + 0xD1D28 + 3), (enable) ? newOff : off); // dmc3.exe+D1D28 - 48 8D 8B A8180000 - LEA RCX,[RBX+000018A8]
		// Trash<uint32>((appBaseAddr + 0xD3410 + 3), (enable) ? newOff : off); // dmc3.exe+D3410 - 8B 81 A8180000 - MOV EAX,[RCX+000018A8]
		// Trash<uint32>((appBaseAddr + 0xFDE6E + 3), (enable) ? newOff : off); // dmc3.exe+FDE6E - 0F11 87 A8180000 - MOVUPS [RDI+000018A8],XMM0
		Write<uint32>((appBaseAddr + 0x1FAF4F + 3), (enable) ? newOff : off); // dmc3.exe+1FAF4F - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0x1FAF93 + 3), (enable) ? newOff : off); // dmc3.exe+1FAF93 - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0x1FAFA4 + 3), (enable) ? newOff : off); // dmc3.exe+1FAFA4 - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0x1FC8F3 + 3), (enable) ? newOff : off); // dmc3.exe+1FC8F3 - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0x21920A + 3), (enable) ? newOff : off); // dmc3.exe+21920A - 48 8B 97 A8180000 - MOV RDX,[RDI+000018A8]
		Write<uint32>((appBaseAddr + 0x219ACB + 3), (enable) ? newOff : off); // dmc3.exe+219ACB - 48 8B 97 A8180000 - MOV RDX,[RDI+000018A8]
		// Trash<uint32>((appBaseAddr + 0x258901 + 3), (enable) ? newOff : off); // dmc3.exe+258901 - 89 83 A8180000 - MOV [RBX+000018A8],EAX
		// Trash<uint32>((appBaseAddr + 0x259660 + 3), (enable) ? newOff : off); // dmc3.exe+259660 - 89 9A A8180000 - MOV [RDX+000018A8],EBX
		// Trash<uint32>((appBaseAddr + 0x259709 + 3), (enable) ? newOff : off); // dmc3.exe+259709 - 89 82 A8180000 - MOV [RDX+000018A8],EAX
		// Trash<uint32>((appBaseAddr + 0x25B0D6 + 3), (enable) ? newOff : off); // dmc3.exe+25B0D6 - 89 BB A8180000 - MOV [RBX+000018A8],EDI
		// Trash<uint32>((appBaseAddr + 0x25BFAB + 3), (enable) ? newOff : off); // dmc3.exe+25BFAB - 89 9A A8180000 - MOV [RDX+000018A8],EBX
		// Trash<uint32>((appBaseAddr + 0x25C054 + 3), (enable) ? newOff : off); // dmc3.exe+25C054 - 89 82 A8180000 - MOV [RDX+000018A8],EAX
	}
	// 0x1940
	{
		constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[1][0]);
		constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[1][0]);
		static_assert(off == 0x1940);
		Write<uint32>((appBaseAddr + 0x1EF2BB + 3), (enable) ? newOff : off); // dmc3.exe+1EF2BB - 4D 8D BD 40190000 - LEA R15,[R13+00001940]
	}
	// 0x1A00
	{
		constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[2][0]);
		constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[2][0]);
		static_assert(off == 0x1A00);
		Write<uint32>((appBaseAddr + 0x1EF18F + 3), (enable) ? newOff : off); // dmc3.exe+1EF18F - 4D 8D BD 001A0000 - LEA R15,[R13+00001A00]
	}
	// 0x1AC0
	{
		constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[3][0]);
		constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[3][0]); // -> [6]
		static_assert(off == 0x1AC0);
		Write<uint32>((appBaseAddr + 0x1EF0A9 + 3), (enable) ? newOff : off); // dmc3.exe+1EF0A9 - 49 8D AD C01A0000 - LEA RBP,[R13+00001AC0]
	}
	// 0x1B88
	{
		constexpr auto off = offsetof(ActorData, modelAllocationData[0]);
		constexpr auto newOff = offsetof(ActorData, newModelAllocationData[0]);
		static_assert(off == 0x1B88);
		Write<uint32>((appBaseAddr + 0x1DD1AA + 3), (enable) ? newOff : off); // dmc3.exe+1DD1AA - 49 8D 8E 881B0000 - LEA RCX,[R14+00001B88]
		Write<uint32>((appBaseAddr + 0x1DD27A + 3), (enable) ? newOff : off); // dmc3.exe+1DD27A - 49 8D 8E 881B0000 - LEA RCX,[R14+00001B88]
		Write<uint32>((appBaseAddr + 0x1DD34A + 3), (enable) ? newOff : off); // dmc3.exe+1DD34A - 49 8D 8E 881B0000 - LEA RCX,[R14+00001B88]
		Write<uint32>((appBaseAddr + 0x1DD41A + 3), (enable) ? newOff : off); // dmc3.exe+1DD41A - 49 8D 8E 881B0000 - LEA RCX,[R14+00001B88]
		Write<uint32>((appBaseAddr + 0x1DDB76 + 3), (enable) ? newOff : off); // dmc3.exe+1DDB76 - 48 8D 8E 881B0000 - LEA RCX,[RSI+00001B88]
		Write<uint32>((appBaseAddr + 0x1DE3FB + 3), (enable) ? newOff : off); // dmc3.exe+1DE3FB - 48 8D 8F 881B0000 - LEA RCX,[RDI+00001B88]
		Write<uint32>((appBaseAddr + 0x1DE7B3 + 3), (enable) ? newOff : off); // dmc3.exe+1DE7B3 - 48 8D 8F 881B0000 - LEA RCX,[RDI+00001B88]
		// Write<uint32>((appBaseAddr + 0x1DFAEE + 3), (enable) ? newOff : off); // dmc3.exe+1DFAEE - 48 81 C1 881B0000 - ADD RCX,00001B88
		// Write<uint32>((appBaseAddr + 0x34B84D + 3), (enable) ? newOff : off); // dmc3.exe+34B84D - 48 81 C1 881B0000 - ADD RCX,00001B88
	}
	// 0x1B98
	{
		constexpr auto off = (offsetof(ActorData, modelAllocationData[0]) + 0x10);
		constexpr auto newOff = (offsetof(ActorData, newModelAllocationData[0]) + 0x10);
		static_assert(off == 0x1B98);
		Write<uint32>((appBaseAddr + 0x1DD1BB + 3), (enable) ? newOff : off); // dmc3.exe+1DD1BB - 49 8B 8E 981B0000 - MOV RCX,[R14+00001B98]
		Write<uint32>((appBaseAddr + 0x1DD28B + 3), (enable) ? newOff : off); // dmc3.exe+1DD28B - 49 8B 8E 981B0000 - MOV RCX,[R14+00001B98]
		Write<uint32>((appBaseAddr + 0x1DD35B + 3), (enable) ? newOff : off); // dmc3.exe+1DD35B - 49 8B 8E 981B0000 - MOV RCX,[R14+00001B98]
		Write<uint32>((appBaseAddr + 0x1DD42B + 3), (enable) ? newOff : off); // dmc3.exe+1DD42B - 49 8B 8E 981B0000 - MOV RCX,[R14+00001B98]
	}
	// 0x3B00
	{
		constexpr auto off = offsetof(ActorData, recoveryData[0]);
		constexpr auto newOff = offsetof(ActorData, newRecoveryData[0]);
		static_assert(off == 0x3B00);
		// Trash<uint32>((appBaseAddr + 0xA9357 + 3), (enable) ? newOff : off); // dmc3.exe+A9357 - BA 003B0000 - MOV EDX,00003B00
		// Trash<uint32>((appBaseAddr + 0xA9542 + 3), (enable) ? newOff : off); // dmc3.exe+A9542 - BA 003B0000 - MOV EDX,00003B00
		// Write<uint32>((appBaseAddr + 0xDB494 + 3), (enable) ? newOff : off); // dmc3.exe+DB494 - 48 89 AE 003B0000 - MOV [RSI+00003B00],RBP
		Write<uint32>((appBaseAddr + 0x1DDC09 + 3), (enable) ? newOff : off); // dmc3.exe+1DDC09 - 48 8D 8E 003B0000 - LEA RCX,[RSI+00003B00]
		Write<uint32>((appBaseAddr + 0x1DE3AD + 3), (enable) ? newOff : off); // dmc3.exe+1DE3AD - 48 8D 8F 003B0000 - LEA RCX,[RDI+00003B00]
		Write<uint32>((appBaseAddr + 0x1EF408 + 3), (enable) ? newOff : off); // dmc3.exe+1EF408 - 49 8D 8D 003B0000 - LEA RCX,[R13+00003B00]
		// Write<uint32>((appBaseAddr + 0x34B8E1 + 3), (enable) ? newOff : off); // dmc3.exe+34B8E1 - 48 81 C1 003B0000 - ADD RCX,00003B00
		// Trash<uint32>((appBaseAddr + 0x4A20EB + 3), (enable) ? newOff : off); // dmc3.exe+4A20EB - 80 9C 03 00003B00 00 - SBB BYTE PTR [RBX+RAX+003B0000],00
		// Trash<uint32>((appBaseAddr + 0x4B7C59 + 3), (enable) ? newOff : off); // dmc3.exe+4B7C59 - 05 00003B00 - ADD EAX,003B0000
		// Trash<uint32>((appBaseAddr + 0x4B7C67 + 3), (enable) ? newOff : off); // dmc3.exe+4B7C67 - 00 14 05 00003B00 - ADD [RAX+003B0000],DL
		// Trash<uint32>((appBaseAddr + 0x4B7C77 + 3), (enable) ? newOff : off); // dmc3.exe+4B7C77 - 00 34 05 00003B00 - ADD [RAX+003B0000],DH
		// Trash<uint32>((appBaseAddr + 0x4B7CA9 + 3), (enable) ? newOff : off); // dmc3.exe+4B7CA9 - 05 00003B00 - ADD EAX,003B0000
		// Trash<uint32>((appBaseAddr + 0x4B7CC7 + 3), (enable) ? newOff : off); // dmc3.exe+4B7CC7 - 00 B4 05 00003B00 - ADD [RBP+RAX+003B0000],DH
		// Trash<uint32>((appBaseAddr + 0x4B7CD9 + 3), (enable) ? newOff : off); // dmc3.exe+4B7CD9 - 05 00003B00 - ADD EAX,003B0000
		// Trash<uint32>((appBaseAddr + 0x4B7CE9 + 3), (enable) ? newOff : off); // dmc3.exe+4B7CE9 - 05 00003B00 - ADD EAX,003B0000
		// Trash<uint32>((appBaseAddr + 0x4BEA8D + 3), (enable) ? newOff : off); // dmc3.exe+4BEA8D - 05 00003B00 - ADD EAX,003B0000
		// Trash<uint32>((appBaseAddr + 0x4BEABB + 3), (enable) ? newOff : off); // dmc3.exe+4BEABB - 00 84 05 00003B00 - ADD [RBP+RAX+003B0000],AL
	}
	// 0x3B70
	{
		constexpr auto off = offsetof(ActorData, recoveryData[1]);
		constexpr auto newOff = offsetof(ActorData, newRecoveryData[1]);
		static_assert(off == 0x3B70);
		// Write<uint32>((appBaseAddr + 0xD8A7A + 3), (enable) ? newOff : off); // dmc3.exe+D8A7A - 4C 89 BE 703B0000 - MOV [RSI+00003B70],R15
		// Write<uint32>((appBaseAddr + 0xE16B1 + 3), (enable) ? newOff : off); // dmc3.exe+E16B1 - 48 89 83 703B0000 - MOV [RBX+00003B70],RAX
		// Write<uint32>((appBaseAddr + 0x118D65 + 3), (enable) ? newOff : off); // dmc3.exe+118D65 - 4C 89 B6 703B0000 - MOV [RSI+00003B70],R14
		// Write<uint32>((appBaseAddr + 0x125199 + 3), (enable) ? newOff : off); // dmc3.exe+125199 - 48 8B 89 703B0000 - MOV RCX,[RCX+00003B70]
		Write<uint32>((appBaseAddr + 0x1EF2E1 + 3), (enable) ? newOff : off); // dmc3.exe+1EF2E1 - 49 8D 8D 703B0000 - LEA RCX,[R13+00003B70]
	}
	// 0x3BE0
	{
		constexpr auto off = offsetof(ActorData, recoveryData[2]);
		constexpr auto newOff = offsetof(ActorData, newRecoveryData[2]);
		static_assert(off == 0x3BE0);
		// Write<uint32>((appBaseAddr + 0x121E32 + 3), (enable) ? newOff : off); // dmc3.exe+121E32 - 48 8D 93 E03B0000 - LEA RDX,[RBX+00003BE0]
		// Write<uint32>((appBaseAddr + 0x126454 + 3), (enable) ? newOff : off); // dmc3.exe+126454 - 48 8D BE E03B0000 - LEA RDI,[RSI+00003BE0]
		// Write<uint32>((appBaseAddr + 0x126E64 + 3), (enable) ? newOff : off); // dmc3.exe+126E64 - 48 8D 93 E03B0000 - LEA RDX,[RBX+00003BE0]
		Write<uint32>((appBaseAddr + 0x1EF1B5 + 3), (enable) ? newOff : off); // dmc3.exe+1EF1B5 - 49 8D 8D E03B0000 - LEA RCX,[R13+00003BE0]
	}
	// 0x3E74
	{
		constexpr auto off = offsetof(ActorData, devilModels[0]);
		constexpr auto newOff = offsetof(ActorData, newDevilModels[0]);
		static_assert(off == 0x3E74);
		// Trash<uint32>((appBaseAddr + 0x4B215 + 3), (enable) ? newOff : off); // dmc3.exe+4B215 - 0F10 87 743E0000 - MOVUPS XMM0,[RDI+00003E74]
		// Trash<uint32>((appBaseAddr + 0x4B262 + 3), (enable) ? newOff : off); // dmc3.exe+4B262 - 0F10 87 743E0000 - MOVUPS XMM0,[RDI+00003E74]
		// Write<uint32>((appBaseAddr + 0x4B950 + 3), (enable) ? newOff : off); // dmc3.exe+4B950 - C7 83 743E0000 01000000 - MOV [RBX+00003E74],00000001
		Write<uint32>((appBaseAddr + 0x90B67 + 4), (enable) ? newOff : off); // dmc3.exe+90B67 - 41 8B 8C 86 743E0000 - MOV ECX,[R14+RAX*4+00003E74]
		Write<uint32>((appBaseAddr + 0x1F7E5A + 2), (enable) ? newOff : off); // dmc3.exe+1F7E5A - C7 83 743E0000 FFFFFFFF - MOV [RBX+00003E74],FFFFFFFF
		Write<uint32>((appBaseAddr + 0x1FAB17 + 3), (enable) ? newOff : off); // dmc3.exe+1FAB17 - 8B 84 81 743E0000 - MOV EAX,[RCX+RAX*4+00003E74]
		Write<uint32>((appBaseAddr + 0x1FAB34 + 4), (enable) ? newOff : off); // dmc3.exe+1FAB34 - 48 63 94 81 743E0000 - MOVSXD RDX,DWORD PTR [RCX+RAX*4+00003E74]
		Write<uint32>((appBaseAddr + 0x212110 + 3), (enable) ? newOff : off); // dmc3.exe+212110 - 8B 94 81 743E0000 - MOV EDX,[RCX+RAX*4+00003E74]
		Write<uint32>((appBaseAddr + 0x213181 + 3), (enable) ? newOff : off); // dmc3.exe+213181 - C7 84 BE 743E0000 05000000 - MOV [RSI+RDI*4+00003E74],00000005
		Write<uint32>((appBaseAddr + 0x213580 + 3), (enable) ? newOff : off); // dmc3.exe+213580 - C7 84 BE 743E0000 04000000 - MOV [RSI+RDI*4+00003E74],00000004
		Write<uint32>((appBaseAddr + 0x213989 + 3), (enable) ? newOff : off); // dmc3.exe+213989 - C7 84 BE 743E0000 03000000 - MOV [RSI+RDI*4+00003E74],00000003
		Write<uint32>((appBaseAddr + 0x213FE0 + 4), (enable) ? newOff : off); // dmc3.exe+213FE0 - 42 C7 84 AE 743E0000 02000000 - MOV [RSI+R13*4+00003E74],00000002
		Write<uint32>((appBaseAddr + 0x21410F + 3), (enable) ? newOff : off); // dmc3.exe+21410F - C7 84 BE 743E0000 01000000 - MOV [RSI+RDI*4+00003E74],00000001
		Write<uint32>((appBaseAddr + 0x21450A + 3), (enable) ? newOff : off); // dmc3.exe+21450A - C7 84 BE 743E0000 00000000 - MOV [RSI+RDI*4+00003E74],00000000
		Write<uint32>((appBaseAddr + 0x2189B0 + 3), (enable) ? newOff : off); // dmc3.exe+2189B0 - 8B 94 8F 743E0000 - MOV EDX,[RDI+RCX*4+00003E74]
		// Write<uint32>((appBaseAddr + 0x220552 + 3), (enable) ? newOff : off); // dmc3.exe+220552 - 8B 8C 81 743E0000 - MOV ECX,[RCX+RAX*4+00003E74]
		// Write<uint32>((appBaseAddr + 0x220D9E + 3), (enable) ? newOff : off); // dmc3.exe+220D9E - 41 C7 84 BC 743E0000 06000000 - MOV [R12+RDI*4+00003E74],00000006
		// Write<uint32>((appBaseAddr + 0x221198 + 3), (enable) ? newOff : off); // dmc3.exe+221198 - 41 C7 84 BC 743E0000 04000000 - MOV [R12+RDI*4+00003E74],00000004
		// Write<uint32>((appBaseAddr + 0x2215A0 + 3), (enable) ? newOff : off); // dmc3.exe+2215A0 - 45 89 B4 BC 743E0000 - MOV [R12+RDI*4+00003E74],R14D
		// Write<uint32>((appBaseAddr + 0x2244A8 + 3), (enable) ? newOff : off); // dmc3.exe+2244A8 - 8B 8C 83 743E0000 - MOV ECX,[RBX+RAX*4+00003E74]
		// Write<uint32>((appBaseAddr + 0x2263C0 + 3), (enable) ? newOff : off); // dmc3.exe+2263C0 - 41 C7 84 9E 743E0000 00000000 - MOV [R14+RBX*4+00003E74],00000000
		// Write<uint32>((appBaseAddr + 0x22692E + 3), (enable) ? newOff : off); // dmc3.exe+22692E - 41 C7 84 9E 743E0000 04000000 - MOV [R14+RBX*4+00003E74],00000004
		Write<uint32>((appBaseAddr + 0x2296B3 + 3), (enable) ? newOff : off); // dmc3.exe+2296B3 - 83 BC 81 743E0000 04 - CMP DWORD PTR [RCX+RAX*4+00003E74],04
	}
	// 0x6950
	{
		constexpr auto off = offsetof(ActorData, bodyPartData[0][0]);
		constexpr auto newOff = offsetof(ActorData, newBodyPartData[0][0]);
		static_assert(off == 0x6950);
		// Write<uint32>((appBaseAddr + 0x1313BE + 3), (enable) ? newOff : off); // dmc3.exe+1313BE - 49 89 86 50690000 - MOV [R14+00006950],RAX
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
		// Write<uint32>((appBaseAddr + 0x1F0446 + 3), (enable) ? newOff : off); // dmc3.exe+1F0446 - 48 81 C1 50690000 - ADD RCX,00006950
		Write<uint32>((appBaseAddr + 0x1F906A + 3), (enable) ? newOff : off); // dmc3.exe+1F906A - 48 81 C1 50690000 - ADD RCX,00006950
		Write<uint32>((appBaseAddr + 0x1F9080 + 3), (enable) ? newOff : off); // dmc3.exe+1F9080 - 48 8D 97 50690000 - LEA RDX,[RDI+00006950]
		// Trash<uint32>((appBaseAddr + 0x27B424 + 3), (enable) ? newOff : off); // dmc3.exe+27B424 - 88 83 50690000 - MOV [RBX+00006950],AL
		// Trash<uint32>((appBaseAddr + 0x27BF20 + 3), (enable) ? newOff : off); // dmc3.exe+27BF20 - 66 C7 81 50690000 0000 - MOV WORD PTR [RCX+00006950],0000
		// Trash<uint32>((appBaseAddr + 0x27C044 + 3), (enable) ? newOff : off); // dmc3.exe+27C044 - 66 C7 81 50690000 0101 - MOV WORD PTR [RCX+00006950],0101
		// Trash<uint32>((appBaseAddr + 0x27F355 + 3), (enable) ? newOff : off); // dmc3.exe+27F355 - 80 BB 50690000 00 - CMP BYTE PTR [RBX+00006950],00
		// Write<uint32>((appBaseAddr + 0x34B9F4 + 3), (enable) ? newOff : off); // dmc3.exe+34B9F4 - 48 81 C1 50690000 - ADD RCX,00006950
	}
	// 0x6A70
	{
		constexpr auto off = offsetof(ActorData, bodyPartData[0][1]);
		constexpr auto newOff = offsetof(ActorData, newBodyPartData[0][1]);
		static_assert(off == 0x6A70);
		// Write<uint32>((appBaseAddr + 0xB9C7C + 3), (enable) ? newOff : off); // dmc3.exe+B9C7C - 4C 8D B7 706A0000 - LEA R14,[RDI+00006A70]
		// Write<uint32>((appBaseAddr + 0xCA512 + 3), (enable) ? newOff : off); // dmc3.exe+CA512 - 48 8D 8E 706A0000 - LEA RCX,[RSI+00006A70]
		// Write<uint32>((appBaseAddr + 0xCA62B + 3), (enable) ? newOff : off); // dmc3.exe+CA62B - 48 8D 8E 706A0000 - LEA RCX,[RSI+00006A70]
		// Write<uint32>((appBaseAddr + 0xCA97E + 3), (enable) ? newOff : off); // dmc3.exe+CA97E - 48 8D 8D 706A0000 - LEA RCX,[RBP+00006A70]
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
		constexpr auto off = offsetof(ActorData, bodyPartData[1][0]);
		constexpr auto newOff = offsetof(ActorData, newBodyPartData[1][0]);
		static_assert(off == 0x6B90);
		Write<uint32>((appBaseAddr + 0x1EF3AE + 3), (enable) ? newOff : off); // dmc3.exe+1EF3AE - 49 8D 8D 906B0000 - LEA RCX,[R13+00006B90]
	}
	// 0x6CB0
	{
		constexpr auto off = offsetof(ActorData, bodyPartData[1][1]);
		constexpr auto newOff = offsetof(ActorData, newBodyPartData[1][1]);
		static_assert(off == 0x6CB0);
		Write<uint32>((appBaseAddr + 0x1EF357 + 3), (enable) ? newOff : off); // dmc3.exe+1EF357 - 49 8D 8D B06C0000 - LEA RCX,[R13+00006CB0]
	}
	// 0x6DD0
	{
		constexpr auto off = offsetof(ActorData, bodyPartData[2][0]);
		constexpr auto newOff = offsetof(ActorData, newBodyPartData[2][0]);
		static_assert(off == 0x6DD0);
		Write<uint32>((appBaseAddr + 0x1EF282 + 3), (enable) ? newOff : off); // dmc3.exe+1EF282 - 49 8D 8D D06D0000 - LEA RCX,[R13+00006DD0]
	}
	// 0x6EF0
	{
		constexpr auto off = offsetof(ActorData, bodyPartData[2][1]);
		constexpr auto newOff = offsetof(ActorData, newBodyPartData[2][1]);
		static_assert(off == 0x6EF0);
		Write<uint32>((appBaseAddr + 0x1EF22B + 3), (enable) ? newOff : off); // dmc3.exe+1EF22B - 49 8D 8D F06E0000 - LEA RCX,[R13+00006EF0]
	}
	// // 0x7010
	// {
	// 	constexpr auto off = offsetof(ActorData, bodyPartData[3][0]);
	// 	constexpr auto newOff = offsetof(ActorData, newBodyPartData[6][0]);
	// 	static_assert(off == 0x7010);
	// 	Write<uint32>((appBaseAddr + 0x1DDD8C + 3), (enable) ? newOff : off); // dmc3.exe+1DDD8C - 48 8D 8E 10700000 - LEA RCX,[RSI+00007010]
	// 	Write<uint32>((appBaseAddr + 0x1DE2D5 + 3), (enable) ? newOff : off); // dmc3.exe+1DE2D5 - 48 8D 8F 10700000 - LEA RCX,[RDI+00007010]
	// 	Write<uint32>((appBaseAddr + 0x1EF13D + 3), (enable) ? newOff : off); // dmc3.exe+1EF13D - 49 8D 8D 10700000 - LEA RCX,[R13+00007010]
	// 	Write<uint32>((appBaseAddr + 0x1EF177 + 3), (enable) ? newOff : off); // dmc3.exe+1EF177 - 49 8D 8D 10700000 - LEA RCX,[R13+00007010]
	// 	Write<uint32>((appBaseAddr + 0x1EF9BE + 3), (enable) ? newOff : off); // dmc3.exe+1EF9BE - 48 8D 8F 10700000 - LEA RCX,[RDI+00007010]
	// 	Write<uint32>((appBaseAddr + 0x1EFA0E + 3), (enable) ? newOff : off); // dmc3.exe+1EFA0E - 48 8D 8F 10700000 - LEA RCX,[RDI+00007010]
	// 	Write<uint32>((appBaseAddr + 0x1EFA1F + 3), (enable) ? newOff : off); // dmc3.exe+1EFA1F - 48 8D 8F 10700000 - LEA RCX,[RDI+00007010]
	// 	Write<uint32>((appBaseAddr + 0x1EFE44 + 3), (enable) ? newOff : off); // dmc3.exe+1EFE44 - 49 8D 8E 10700000 - LEA RCX,[R14+00007010]
	// 	Write<uint32>((appBaseAddr + 0x1EFED0 + 3), (enable) ? newOff : off); // dmc3.exe+1EFED0 - 48 8D 8B 10700000 - LEA RCX,[RBX+00007010]
	// 	// Write<uint32>((appBaseAddr + 0x34BA25 + 3), (enable) ? newOff : off); // dmc3.exe+34BA25 - 48 81 C1 10700000 - ADD RCX,00007010
	// }
	// // 0x7130
	// {
	// 	constexpr auto off = offsetof(ActorData, bodyPartData[3][1]);
	// 	constexpr auto newOff = offsetof(ActorData, newBodyPartData[6][1]);
	// 	static_assert(off == 0x7130);
	// 	Write<uint32>((appBaseAddr + 0x1EF0FE + 3), (enable) ? newOff : off); // dmc3.exe+1EF0FE - 49 8D 8D 30710000 - LEA RCX,[R13+00007130]
	// 	Write<uint32>((appBaseAddr + 0x1EF169 + 3), (enable) ? newOff : off); // dmc3.exe+1EF169 - 49 8D 8D 30710000 - LEA RCX,[R13+00007130]
	// 	Write<uint32>((appBaseAddr + 0x1EF9AD + 3), (enable) ? newOff : off); // dmc3.exe+1EF9AD - 48 8D 8F 30710000 - LEA RCX,[RDI+00007130]
	// 	Write<uint32>((appBaseAddr + 0x1EF9CA + 3), (enable) ? newOff : off); // dmc3.exe+1EF9CA - 48 8D 8F 30710000 - LEA RCX,[RDI+00007130]
	// 	Write<uint32>((appBaseAddr + 0x1EFA6E + 3), (enable) ? newOff : off); // dmc3.exe+1EFA6E - 48 8D 8F 30710000 - LEA RCX,[RDI+00007130]
	// 	Write<uint32>((appBaseAddr + 0x1EFA7F + 3), (enable) ? newOff : off); // dmc3.exe+1EFA7F - 48 8D 8F 30710000 - LEA RCX,[RDI+00007130]
	// 	Write<uint32>((appBaseAddr + 0x1EFDE0 + 3), (enable) ? newOff : off); // dmc3.exe+1EFDE0 - 49 8D 8E 30710000 - LEA RCX,[R14+00007130]
	// 	Write<uint32>((appBaseAddr + 0x1EFF60 + 3), (enable) ? newOff : off); // dmc3.exe+1EFF60 - 48 8D 8B 30710000 - LEA RCX,[RBX+00007130]
	// }
	// 0x7540
	{
		constexpr auto off = offsetof(ActorData, submodelData[0]);
		constexpr auto newOff = offsetof(ActorData, newSubmodelData[0]);
		static_assert(off == 0x7540);
		// Write<uint32>((appBaseAddr + 0x17644B + 3), (enable) ? newOff : off); // dmc3.exe+17644B - 48 8D 8E 40750000 - LEA RCX,[RSI+00007540]
		// Write<uint32>((appBaseAddr + 0x176BF2 + 3), (enable) ? newOff : off); // dmc3.exe+176BF2 - 48 8D 8E 40750000 - LEA RCX,[RSI+00007540]
		// Write<uint32>((appBaseAddr + 0x180756 + 3), (enable) ? newOff : off); // dmc3.exe+180756 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		// Write<uint32>((appBaseAddr + 0x180ABD + 3), (enable) ? newOff : off); // dmc3.exe+180ABD - 48 8D 8F 40750000 - LEA RCX,[RDI+00007540]
		// Write<uint32>((appBaseAddr + 0x1832F7 + 3), (enable) ? newOff : off); // dmc3.exe+1832F7 - 4C 8D B6 40750000 - LEA R14,[RSI+00007540]
		// Write<uint32>((appBaseAddr + 0x185127 + 3), (enable) ? newOff : off); // dmc3.exe+185127 - 48 81 C1 40750000 - ADD RCX,00007540
		// Write<uint32>((appBaseAddr + 0x18566D + 3), (enable) ? newOff : off); // dmc3.exe+18566D - 48 8D 8F 40750000 - LEA RCX,[RDI+00007540]
		// Write<uint32>((appBaseAddr + 0x1869EE + 3), (enable) ? newOff : off); // dmc3.exe+1869EE - 4C 8D BF 40750000 - LEA R15,[RDI+00007540]
		// Write<uint32>((appBaseAddr + 0x186A63 + 3), (enable) ? newOff : off); // dmc3.exe+186A63 - 4C 8D BF 40750000 - LEA R15,[RDI+00007540]
		// Write<uint32>((appBaseAddr + 0x186DC8 + 3), (enable) ? newOff : off); // dmc3.exe+186DC8 - 48 8D AF 40750000 - LEA RBP,[RDI+00007540]
		// Write<uint32>((appBaseAddr + 0x186E43 + 3), (enable) ? newOff : off); // dmc3.exe+186E43 - 48 8D AF 40750000 - LEA RBP,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x1DD4D2 + 3), (enable) ? newOff : off); // dmc3.exe+1DD4D2 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x1DD642 + 3), (enable) ? newOff : off); // dmc3.exe+1DD642 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x1DD7F2 + 3), (enable) ? newOff : off); // dmc3.exe+1DD7F2 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x1DD9A2 + 3), (enable) ? newOff : off); // dmc3.exe+1DD9A2 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x1DDF1E + 3), (enable) ? newOff : off); // dmc3.exe+1DDF1E - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x1DDFF0 + 3), (enable) ? newOff : off); // dmc3.exe+1DDFF0 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x1DE126 + 3), (enable) ? newOff : off); // dmc3.exe+1DE126 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x1DE24C + 3), (enable) ? newOff : off); // dmc3.exe+1DE24C - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		// Write<uint32>((appBaseAddr + 0x1DE6F9 + 3), (enable) ? newOff : off); // dmc3.exe+1DE6F9 - BA 40750000 - MOV EDX,00007540
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
		// Write<uint32>((appBaseAddr + 0x220580 + 3), (enable) ? newOff : off); // dmc3.exe+220580 - 48 8D 96 40750000 - LEA RDX,[RSI+00007540]
		// Write<uint32>((appBaseAddr + 0x2205E0 + 3), (enable) ? newOff : off); // dmc3.exe+2205E0 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x22062F + 3), (enable) ? newOff : off); // dmc3.exe+22062F - 48 8D 96 40750000 - LEA RDX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x220691 + 3), (enable) ? newOff : off); // dmc3.exe+220691 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x2206F9 + 3), (enable) ? newOff : off); // dmc3.exe+2206F9 - 48 8D 96 40750000 - LEA RDX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x22076B + 3), (enable) ? newOff : off); // dmc3.exe+22076B - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x220810 + 3), (enable) ? newOff : off); // dmc3.exe+220810 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x220888 + 3), (enable) ? newOff : off); // dmc3.exe+220888 - 48 81 C1 40750000 - ADD RCX,00007540
		// Write<uint32>((appBaseAddr + 0x220F35 + 3), (enable) ? newOff : off); // dmc3.exe+220F35 - 49 81 C6 40750000 - ADD R14,00007540
		Write<uint32>((appBaseAddr + 0x2212C8 + 3), (enable) ? newOff : off); // dmc3.exe+2212C8 - 49 81 C6 40750000 - ADD R14,00007540
		Write<uint32>((appBaseAddr + 0x2216C3 + 3), (enable) ? newOff : off); // dmc3.exe+2216C3 - 49 81 C6 40750000 - ADD R14,00007540
		Write<uint32>((appBaseAddr + 0x22195B + 3), (enable) ? newOff : off); // dmc3.exe+22195B - 49 81 C6 40750000 - ADD R14,00007540
		Write<uint32>((appBaseAddr + 0x221BC4 + 4), (enable) ? newOff : off); // dmc3.exe+221BC4 - 4D 8D B4 24 40750000 - LEA R14,[R12+00007540]
		// Write<uint32>((appBaseAddr + 0x22221B + 3), (enable) ? newOff : off); // dmc3.exe+22221B - 4C 8D AD 40750000 - LEA R13,[RBP+00007540]
		Write<uint32>((appBaseAddr + 0x222449 + 3), (enable) ? newOff : off); // dmc3.exe+222449 - 4C 8D AD 40750000 - LEA R13,[RBP+00007540]
		// Write<uint32>((appBaseAddr + 0x222702 + 3), (enable) ? newOff : off); // dmc3.exe+222702 - 48 8D B5 40750000 - LEA RSI,[RBP+00007540]
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
		// Write<uint32>((appBaseAddr + 0x22338D + 3), (enable) ? newOff : off); // dmc3.exe+22338D - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		// Write<uint32>((appBaseAddr + 0x2233E5 + 3), (enable) ? newOff : off); // dmc3.exe+2233E5 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x223780 + 3), (enable) ? newOff : off); // dmc3.exe+223780 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x2237DF + 3), (enable) ? newOff : off); // dmc3.exe+2237DF - 48 8D B1 40750000 - LEA RSI,[RCX+00007540]
		// Write<uint32>((appBaseAddr + 0x2238C3 + 3), (enable) ? newOff : off); // dmc3.exe+2238C3 - 48 8D B5 40750000 - LEA RSI,[RBP+00007540]
		// Write<uint32>((appBaseAddr + 0x223919 + 3), (enable) ? newOff : off); // dmc3.exe+223919 - 48 8D B5 40750000 - LEA RSI,[RBP+00007540]
		// Write<uint32>((appBaseAddr + 0x22397A + 3), (enable) ? newOff : off); // dmc3.exe+22397A - 48 8D B5 40750000 - LEA RSI,[RBP+00007540]
		// Write<uint32>((appBaseAddr + 0x2239DF + 3), (enable) ? newOff : off); // dmc3.exe+2239DF - 48 8D B5 40750000 - LEA RSI,[RBP+00007540]
		Write<uint32>((appBaseAddr + 0x223A46 + 3), (enable) ? newOff : off); // dmc3.exe+223A46 - 48 8D B5 40750000 - LEA RSI,[RBP+00007540]
		Write<uint32>((appBaseAddr + 0x2243CA + 3), (enable) ? newOff : off); // dmc3.exe+2243CA - 48 8D BB 40750000 - LEA RDI,[RBX+00007540]
		// Write<uint32>((appBaseAddr + 0x2244D7 + 3), (enable) ? newOff : off); // dmc3.exe+2244D7 - 48 81 C1 40750000 - ADD RCX,00007540
		// Write<uint32>((appBaseAddr + 0x22451B + 3), (enable) ? newOff : off); // dmc3.exe+22451B - 48 81 C1 40750000 - ADD RCX,00007540
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
		// Write<uint32>((appBaseAddr + 0x225AEE + 3), (enable) ? newOff : off); // dmc3.exe+225AEE - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		// Write<uint32>((appBaseAddr + 0x225B50 + 3), (enable) ? newOff : off); // dmc3.exe+225B50 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x225BB8 + 3), (enable) ? newOff : off); // dmc3.exe+225BB8 - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x225C2A + 3), (enable) ? newOff : off); // dmc3.exe+225C2A - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x225CCF + 3), (enable) ? newOff : off); // dmc3.exe+225CCF - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x225D3B + 3), (enable) ? newOff : off); // dmc3.exe+225D3B - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x2260CA + 3), (enable) ? newOff : off); // dmc3.exe+2260CA - 49 8D B6 40750000 - LEA RSI,[R14+00007540]
		Write<uint32>((appBaseAddr + 0x22648D + 3), (enable) ? newOff : off); // dmc3.exe+22648D - 48 81 C7 40750000 - ADD RDI,00007540
		Write<uint32>((appBaseAddr + 0x22669C + 3), (enable) ? newOff : off); // dmc3.exe+22669C - 48 81 C7 40750000 - ADD RDI,00007540
		Write<uint32>((appBaseAddr + 0x2268A2 + 3), (enable) ? newOff : off); // dmc3.exe+2268A2 - 48 81 C7 40750000 - ADD RDI,00007540
		// Write<uint32>((appBaseAddr + 0x226A03 + 3), (enable) ? newOff : off); // dmc3.exe+226A03 - 48 81 C7 40750000 - ADD RDI,00007540
		Write<uint32>((appBaseAddr + 0x226C92 + 3), (enable) ? newOff : off); // dmc3.exe+226C92 - 49 8D 8E 40750000 - LEA RCX,[R14+00007540]
		Write<uint32>((appBaseAddr + 0x226D9F + 3), (enable) ? newOff : off); // dmc3.exe+226D9F - 48 8D 91 40750000 - LEA RDX,[RCX+00007540]
		Write<uint32>((appBaseAddr + 0x226DE9 + 3), (enable) ? newOff : off); // dmc3.exe+226DE9 - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x226E56 + 3), (enable) ? newOff : off); // dmc3.exe+226E56 - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		// Write<uint32>((appBaseAddr + 0x226EC3 + 3), (enable) ? newOff : off); // dmc3.exe+226EC3 - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x2272D8 + 3), (enable) ? newOff : off); // dmc3.exe+2272D8 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x227370 + 3), (enable) ? newOff : off); // dmc3.exe+227370 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x2273A8 + 3), (enable) ? newOff : off); // dmc3.exe+2273A8 - 48 81 C1 40750000 - ADD RCX,00007540
		// Write<uint32>((appBaseAddr + 0x34A49B + 3), (enable) ? newOff : off); // dmc3.exe+34A49B - 48 81 C1 40750000 - ADD RCX,00007540
		// Write<uint32>((appBaseAddr + 0x34B399 + 3), (enable) ? newOff : off); // dmc3.exe+34B399 - 48 81 C1 40750000 - ADD RCX,00007540
		// Write<uint32>((appBaseAddr + 0x34B4A9 + 3), (enable) ? newOff : off); // dmc3.exe+34B4A9 - 48 81 C1 40750000 - ADD RCX,00007540
		// Write<uint32>((appBaseAddr + 0x34B549 + 3), (enable) ? newOff : off); // dmc3.exe+34B549 - 48 81 C1 40750000 - ADD RCX,00007540
		// Write<uint32>((appBaseAddr + 0x34B6B9 + 3), (enable) ? newOff : off); // dmc3.exe+34B6B9 - 48 81 C1 40750000 - ADD RCX,00007540
		// Trash<uint32>((appBaseAddr + 0x598B58 + 3), (enable) ? newOff : off); // dmc3.exe+598B58 - D1 15 00007540 - RCL [40CE7F5E],1
	}
	// 0x9AD0
	{
		constexpr auto off = offsetof(ActorData, modelShadowData[0]);
		constexpr auto newOff = offsetof(ActorData, newModelShadowData[0]);
		static_assert(off == 0x9AD0);
		// Write<uint32>((appBaseAddr + 0x18278E + 3), (enable) ? newOff : off); // dmc3.exe+18278E - 0F29 85 D09A0000 - MOVAPS [RBP+00009AD0],XMM0
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
		// Write<uint32>((appBaseAddr + 0x220CCF + 3), (enable) ? newOff : off); // dmc3.exe+220CCF - 4D 89 B4 24 D09A0000 - MOV [R12+00009AD0],R14
		// Write<uint32>((appBaseAddr + 0x22631F + 3), (enable) ? newOff : off); // dmc3.exe+22631F - 49 89 B6 D09A0000 - MOV [R14+00009AD0],RSI
		// Write<uint32>((appBaseAddr + 0x34B3CA + 3), (enable) ? newOff : off); // dmc3.exe+34B3CA - 48 81 C1 D09A0000 - ADD RCX,00009AD0
	}
	// 0x9D10
	{
		constexpr auto off = offsetof(ActorData, submodelShadowData[0]);
		constexpr auto newOff = offsetof(ActorData, newSubmodelShadowData[0]);
		static_assert(off == 0x9D10);
		Write<uint32>((appBaseAddr + 0x1DD528 + 3), (enable) ? newOff : off); // dmc3.exe+1DD528 - 48 8D 8B 109D0000 - LEA RCX,[RBX+00009D10]
		Write<uint32>((appBaseAddr + 0x1DDEE0 + 3), (enable) ? newOff : off); // dmc3.exe+1DDEE0 - 48 8D 8B 109D0000 - LEA RCX,[RBX+00009D10]
		Write<uint32>((appBaseAddr + 0x211F46 + 3), (enable) ? newOff : off); // dmc3.exe+211F46 - 4C 8D B1 109D0000 - LEA R14,[RCX+00009D10]
		Write<uint32>((appBaseAddr + 0x211F9D + 3), (enable) ? newOff : off); // dmc3.exe+211F9D - 48 8D 8B 109D0000 - LEA RCX,[RBX+00009D10]
		Write<uint32>((appBaseAddr + 0x21335B + 4), (enable) ? newOff : off); // dmc3.exe+21335B - 48 8B BC 33 109D0000 - MOV RDI,[RBX+RSI+00009D10]
		Write<uint32>((appBaseAddr + 0x21336B + 3), (enable) ? newOff : off); // dmc3.exe+21336B - 48 8D 8E 109D0000 - LEA RCX,[RSI+00009D10]
		Write<uint32>((appBaseAddr + 0x213931 + 4), (enable) ? newOff : off); // dmc3.exe+213931 - 48 8B BC 33 109D0000 - MOV RDI,[RBX+RSI+00009D10]
		Write<uint32>((appBaseAddr + 0x21393C + 3), (enable) ? newOff : off); // dmc3.exe+21393C - 48 8D 8E 109D0000 - LEA RCX,[RSI+00009D10]
		Write<uint32>((appBaseAddr + 0x213CD8 + 4), (enable) ? newOff : off); // dmc3.exe+213CD8 - 48 8B BC 33 109D0000 - MOV RDI,[RBX+RSI+00009D10]
		Write<uint32>((appBaseAddr + 0x213CE3 + 3), (enable) ? newOff : off); // dmc3.exe+213CE3 - 48 8D 8E 109D0000 - LEA RCX,[RSI+00009D10]
		Write<uint32>((appBaseAddr + 0x213F8F + 4), (enable) ? newOff : off); // dmc3.exe+213F8F - 48 8B BC 33 109D0000 - MOV RDI,[RBX+RSI+00009D10]
		Write<uint32>((appBaseAddr + 0x213F9A + 3), (enable) ? newOff : off); // dmc3.exe+213F9A - 48 8D 8E 109D0000 - LEA RCX,[RSI+00009D10]
		Write<uint32>((appBaseAddr + 0x2142E5 + 4), (enable) ? newOff : off); // dmc3.exe+2142E5 - 48 8B BC 33 109D0000 - MOV RDI,[RBX+RSI+00009D10]
		Write<uint32>((appBaseAddr + 0x2142F5 + 3), (enable) ? newOff : off); // dmc3.exe+2142F5 - 48 8D 8E 109D0000 - LEA RCX,[RSI+00009D10]
		Write<uint32>((appBaseAddr + 0x2146CC + 4), (enable) ? newOff : off); // dmc3.exe+2146CC - 48 8B BC 33 109D0000 - MOV RDI,[RBX+RSI+00009D10]
		Write<uint32>((appBaseAddr + 0x2146DC + 3), (enable) ? newOff : off); // dmc3.exe+2146DC - 48 8D 8E 109D0000 - LEA RCX,[RSI+00009D10]
		Write<uint32>((appBaseAddr + 0x214948 + 4), (enable) ? newOff : off); // dmc3.exe+214948 - 48 8B BC 33 109D0000 - MOV RDI,[RBX+RSI+00009D10]
		Write<uint32>((appBaseAddr + 0x214958 + 3), (enable) ? newOff : off); // dmc3.exe+214958 - 48 8D 8E 109D0000 - LEA RCX,[RSI+00009D10]
		Write<uint32>((appBaseAddr + 0x21522A + 3), (enable) ? newOff : off); // dmc3.exe+21522A - 49 8B BE 109D0000 - MOV RDI,[R14+00009D10]
		Write<uint32>((appBaseAddr + 0x215237 + 3), (enable) ? newOff : off); // dmc3.exe+215237 - 49 8D 8E 109D0000 - LEA RCX,[R14+00009D10]
		Write<uint32>((appBaseAddr + 0x218E88 + 3), (enable) ? newOff : off); // dmc3.exe+218E88 - 48 81 C1 109D0000 - ADD RCX,00009D10
		Write<uint32>((appBaseAddr + 0x218F20 + 3), (enable) ? newOff : off); // dmc3.exe+218F20 - 48 8D 8F 109D0000 - LEA RCX,[RDI+00009D10]
		// Write<uint32>((appBaseAddr + 0x34B3FB + 3), (enable) ? newOff : off); // dmc3.exe+34B3FB - 48 81 C1 109D0000 - ADD RCX,00009D10
	}
	// 0xA300
	{
		constexpr auto off = offsetof(ActorData, devilModelPhysicsMetadataPool[0][0]);
		constexpr auto newOff = offsetof(ActorData, newDevilModelPhysicsMetadataPool[0][0]);
		static_assert(off == 0xA300);
		Write<uint32>((appBaseAddr + 0x1DEC79 + 3), (enable) ? newOff : off); // dmc3.exe+1DEC79 - 48 81 C2 00A30000 - ADD RDX,0000A300
		Write<uint32>((appBaseAddr + 0x2136FC + 3), (enable) ? newOff : off); // dmc3.exe+2136FC - 4D 8D 85 00A30000 - LEA R8,[R13+0000A300]
		Write<uint32>((appBaseAddr + 0x213773 + 3), (enable) ? newOff : off); // dmc3.exe+213773 - 49 8D 95 00A30000 - LEA RDX,[R13+0000A300]
		Write<uint32>((appBaseAddr + 0x2137DA + 4), (enable) ? newOff : off); // dmc3.exe+2137DA - 48 8B 84 C6 00A30000 - MOV RAX,[RSI+RAX*8+0000A300]
		Write<uint32>((appBaseAddr + 0x21383C + 4), (enable) ? newOff : off); // dmc3.exe+21383C - 48 8B 84 C6 00A30000 - MOV RAX,[RSI+RAX*8+0000A300]
		Write<uint32>((appBaseAddr + 0x21389B + 4), (enable) ? newOff : off); // dmc3.exe+21389B - 48 8B 84 C6 00A30000 - MOV RAX,[RSI+RAX*8+0000A300]
		Write<uint32>((appBaseAddr + 0x213B0A + 3), (enable) ? newOff : off); // dmc3.exe+213B0A - 4D 8D 85 00A30000 - LEA R8,[R13+0000A300]
		Write<uint32>((appBaseAddr + 0x213B73 + 3), (enable) ? newOff : off); // dmc3.exe+213B73 - 49 8D 95 00A30000 - LEA RDX,[R13+0000A300]
		Write<uint32>((appBaseAddr + 0x213BDC + 4), (enable) ? newOff : off); // dmc3.exe+213BDC - 48 8B 84 C6 00A30000 - MOV RAX,[RSI+RAX*8+0000A300]
		Write<uint32>((appBaseAddr + 0x213C40 + 4), (enable) ? newOff : off); // dmc3.exe+213C40 - 48 8B 84 C6 00A30000 - MOV RAX,[RSI+RAX*8+0000A300]
		Write<uint32>((appBaseAddr + 0x213D8C + 3), (enable) ? newOff : off); // dmc3.exe+213D8C - 4D 8D 85 00A30000 - LEA R8,[R13+0000A300]
		Write<uint32>((appBaseAddr + 0x213E03 + 3), (enable) ? newOff : off); // dmc3.exe+213E03 - 49 8D 95 00A30000 - LEA RDX,[R13+0000A300]
		Write<uint32>((appBaseAddr + 0x213E93 + 4), (enable) ? newOff : off); // dmc3.exe+213E93 - 48 8B 84 C6 00A30000 - MOV RAX,[RSI+RAX*8+0000A300]
		Write<uint32>((appBaseAddr + 0x213EF7 + 4), (enable) ? newOff : off); // dmc3.exe+213EF7 - 48 8B 84 C6 00A30000 - MOV RAX,[RSI+RAX*8+0000A300]
		Write<uint32>((appBaseAddr + 0x2143D5 + 4), (enable) ? newOff : off); // dmc3.exe+2143D5 - 48 8B 84 C6 00A30000 - MOV RAX,[RSI+RAX*8+0000A300]
		Write<uint32>((appBaseAddr + 0x214434 + 4), (enable) ? newOff : off); // dmc3.exe+214434 - 48 8B 84 C6 00A30000 - MOV RAX,[RSI+RAX*8+0000A300]
		Write<uint32>((appBaseAddr + 0x214490 + 4), (enable) ? newOff : off); // dmc3.exe+214490 - 48 8B 84 C6 00A30000 - MOV RAX,[RSI+RAX*8+0000A300]
		Write<uint32>((appBaseAddr + 0x2147B0 + 4), (enable) ? newOff : off); // dmc3.exe+2147B0 - 48 8B 84 C6 00A30000 - MOV RAX,[RSI+RAX*8+0000A300]
		Write<uint32>((appBaseAddr + 0x214814 + 4), (enable) ? newOff : off); // dmc3.exe+214814 - 48 8B 84 C6 00A30000 - MOV RAX,[RSI+RAX*8+0000A300]
		Write<uint32>((appBaseAddr + 0x214A57 + 4), (enable) ? newOff : off); // dmc3.exe+214A57 - 48 8B 84 C6 00A30000 - MOV RAX,[RSI+RAX*8+0000A300]
		Write<uint32>((appBaseAddr + 0x214ABF + 4), (enable) ? newOff : off); // dmc3.exe+214ABF - 48 8B 84 C6 00A30000 - MOV RAX,[RSI+RAX*8+0000A300]
		// Trash<uint32>((appBaseAddr + 0x5FD05D + 3), (enable) ? newOff : off); // dmc3.exe+5FD05D - A2 0002A40000A30000 - MOV [A30000A40200],AL
		// 0x1460
		{
			constexpr auto off = (offsetof(ActorData, devilModelPhysicsMetadataPool[0][0]) / 8);
			constexpr auto newOff = (offsetof(ActorData, newDevilModelPhysicsMetadataPool[0][0]) / 8);
			static_assert(off == 0x1460);
			// Trash<uint32>((appBaseAddr + 0xE1F36 + 3), (enable) ? newOff : off); // dmc3.exe+E1F36 - 48 C7 86 60140000 0050C347 - MOV QWORD PTR [RSI+00001460],47C35000
			// Trash<uint32>((appBaseAddr + 0xE3D69 + 3), (enable) ? newOff : off); // dmc3.exe+E3D69 - 48 C7 86 60140000 0050C347 - MOV QWORD PTR [RSI+00001460],47C35000
			// Trash<uint32>((appBaseAddr + 0xFB64B + 3), (enable) ? newOff : off); // dmc3.exe+FB64B - C6 86 60140000 00 - MOV BYTE PTR [RSI+00001460],00
			// Trash<uint32>((appBaseAddr + 0xFEE49 + 3), (enable) ? newOff : off); // dmc3.exe+FEE49 - C6 87 60140000 01 - MOV BYTE PTR [RDI+00001460],01
			// Trash<uint32>((appBaseAddr + 0xFEF35 + 3), (enable) ? newOff : off); // dmc3.exe+FEF35 - C6 87 60140000 00 - MOV BYTE PTR [RDI+00001460],00
			// Write<uint32>((appBaseAddr + 0x14DB1B + 3), (enable) ? newOff : off); // dmc3.exe+14DB1B - 4C 8D A6 60140000 - LEA R12,[RSI+00001460]
			// Write<uint32>((appBaseAddr + 0x198489 + 3), (enable) ? newOff : off); // dmc3.exe+198489 - 48 8B 87 60140000 - MOV RAX,[RDI+00001460]
			// Write<uint32>((appBaseAddr + 0x198490 + 3), (enable) ? newOff : off); // dmc3.exe+198490 - 48 8D 8F 60140000 - LEA RCX,[RDI+00001460]
			// Write<uint32>((appBaseAddr + 0x1984A4 + 3), (enable) ? newOff : off); // dmc3.exe+1984A4 - 48 8B 87 60140000 - MOV RAX,[RDI+00001460]
			// Write<uint32>((appBaseAddr + 0x1984AB + 3), (enable) ? newOff : off); // dmc3.exe+1984AB - 48 8D 8F 60140000 - LEA RCX,[RDI+00001460]
			// Write<uint32>((appBaseAddr + 0x19854D + 3), (enable) ? newOff : off); // dmc3.exe+19854D - 48 8D 8F 60140000 - LEA RCX,[RDI+00001460]
			Write<uint32>((appBaseAddr + 0x2132F2 + 2), (enable) ? newOff : off); // dmc3.exe+2132F2 - 48 05 60140000 - ADD RAX,00001460
			Write<uint32>((appBaseAddr + 0x21427C + 2), (enable) ? newOff : off); // dmc3.exe+21427C - 48 05 60140000 - ADD RAX,00001460
			Write<uint32>((appBaseAddr + 0x214667 + 2), (enable) ? newOff : off); // dmc3.exe+214667 - 48 05 60140000 - ADD RAX,00001460
			Write<uint32>((appBaseAddr + 0x2148E3 + 2), (enable) ? newOff : off); // dmc3.exe+2148E3 - 48 05 60140000 - ADD RAX,00001460
			// Write<uint32>((appBaseAddr + 0x258B38 + 3), (enable) ? newOff : off); // dmc3.exe+258B38 - 48 8D 99 60140000 - LEA RBX,[RCX+00001460]
			// Trash<uint32>((appBaseAddr + 0x259778 + 3), (enable) ? newOff : off); // dmc3.exe+259778 - 89 98 60140000 - MOV [RAX+00001460],EBX
			// Trash<uint32>((appBaseAddr + 0x259EA8 + 3), (enable) ? newOff : off); // dmc3.exe+259EA8 - F3 0F58 81 60140000 - ADDSS XMM0,DWORD PTR [RCX+00001460]
			// Trash<uint32>((appBaseAddr + 0x259EB0 + 3), (enable) ? newOff : off); // dmc3.exe+259EB0 - F3 0F11 81 60140000 - MOVSS [RCX+00001460],XMM0
			// Write<uint32>((appBaseAddr + 0x25A3B7 + 3), (enable) ? newOff : off); // dmc3.exe+25A3B7 - 48 8D 97 60140000 - LEA RDX,[RDI+00001460]
			// Trash<uint32>((appBaseAddr + 0x25A3FD + 3), (enable) ? newOff : off); // dmc3.exe+25A3FD - F3 0F10 8F 60140000 - MOVSS XMM1,[RDI+00001460]
			// Trash<uint32>((appBaseAddr + 0x25A434 + 3), (enable) ? newOff : off); // dmc3.exe+25A434 - F3 0F11 8F 60140000 - MOVSS [RDI+00001460],XMM1
			// Trash<uint32>((appBaseAddr + 0x25ADB0 + 3), (enable) ? newOff : off); // dmc3.exe+25ADB0 - F3 0F10 81 60140000 - MOVSS XMM0,[RCX+00001460]
			// Trash<uint32>((appBaseAddr + 0x25ADD3 + 3), (enable) ? newOff : off); // dmc3.exe+25ADD3 - F3 0F11 81 60140000 - MOVSS [RCX+00001460],XMM0
			// Write<uint32>((appBaseAddr + 0x25AECB + 3), (enable) ? newOff : off); // dmc3.exe+25AECB - 49 89 80 60140000 - MOV [R8+00001460],RAX
			// Write<uint32>((appBaseAddr + 0x25B3F1 + 3), (enable) ? newOff : off); // dmc3.exe+25B3F1 - 48 8D 9F 60140000 - LEA RBX,[RDI+00001460]
			// Trash<uint32>((appBaseAddr + 0x25C0F9 + 3), (enable) ? newOff : off); // dmc3.exe+25C0F9 - 89 98 60140000 - MOV [RAX+00001460],EBX
			// Trash<uint32>((appBaseAddr + 0x25C748 + 3), (enable) ? newOff : off); // dmc3.exe+25C748 - F3 0F58 81 60140000 - ADDSS XMM0,DWORD PTR [RCX+00001460]
			// Trash<uint32>((appBaseAddr + 0x25C750 + 3), (enable) ? newOff : off); // dmc3.exe+25C750 - F3 0F11 81 60140000 - MOVSS [RCX+00001460],XMM0
			// Write<uint32>((appBaseAddr + 0x25C80A + 3), (enable) ? newOff : off); // dmc3.exe+25C80A - 48 89 81 60140000 - MOV [RCX+00001460],RAX
			// Write<uint32>((appBaseAddr + 0x25CCAC + 3), (enable) ? newOff : off); // dmc3.exe+25CCAC - 48 8D 97 60140000 - LEA RDX,[RDI+00001460]
			// Trash<uint32>((appBaseAddr + 0x25CCE2 + 3), (enable) ? newOff : off); // dmc3.exe+25CCE2 - F3 0F10 8F 60140000 - MOVSS XMM1,[RDI+00001460]
			// Trash<uint32>((appBaseAddr + 0x25CD19 + 3), (enable) ? newOff : off); // dmc3.exe+25CD19 - F3 0F11 8F 60140000 - MOVSS [RDI+00001460],XMM1
			// Trash<uint32>((appBaseAddr + 0x25D606 + 3), (enable) ? newOff : off); // dmc3.exe+25D606 - F3 0F10 81 60140000 - MOVSS XMM0,[RCX+00001460]
			// Trash<uint32>((appBaseAddr + 0x25D629 + 3), (enable) ? newOff : off); // dmc3.exe+25D629 - F3 0F11 81 60140000 - MOVSS [RCX+00001460],XMM0
		}
	}
	// 0xA540
	{
		constexpr auto off = offsetof(ActorData, devilSubmodelPhysicsData[0]);
		constexpr auto newOff = offsetof(ActorData, newDevilSubmodelPhysicsData[0]);
		static_assert(off == 0xA540);
		Write<uint32>((appBaseAddr + 0x1DD577 + 3), (enable) ? newOff : off); // dmc3.exe+1DD577 - 48 8D 8B 40A50000 - LEA RCX,[RBX+0000A540]
		Write<uint32>((appBaseAddr + 0x1DDEA2 + 3), (enable) ? newOff : off); // dmc3.exe+1DDEA2 - 48 8D 8B 40A50000 - LEA RCX,[RBX+0000A540]
		Write<uint32>((appBaseAddr + 0x2121BC + 3), (enable) ? newOff : off); // dmc3.exe+2121BC - 48 8D 8E 40A50000 - LEA RCX,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x21229E + 3), (enable) ? newOff : off); // dmc3.exe+21229E - 48 8D 8E 40A50000 - LEA RCX,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x21236C + 3), (enable) ? newOff : off); // dmc3.exe+21236C - 48 8D 8E 40A50000 - LEA RCX,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x21244E + 3), (enable) ? newOff : off); // dmc3.exe+21244E - 48 8D 8E 40A50000 - LEA RCX,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x212530 + 3), (enable) ? newOff : off); // dmc3.exe+212530 - 48 8D 8E 40A50000 - LEA RCX,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x2125FB + 3), (enable) ? newOff : off); // dmc3.exe+2125FB - 48 8D 8E 40A50000 - LEA RCX,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x212703 + 3), (enable) ? newOff : off); // dmc3.exe+212703 - 48 8D 8E 40A50000 - LEA RCX,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x2133CA + 3), (enable) ? newOff : off); // dmc3.exe+2133CA - 48 8D BE 40A50000 - LEA RDI,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x213746 + 3), (enable) ? newOff : off); // dmc3.exe+213746 - 48 8D BE 40A50000 - LEA RDI,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x213B53 + 3), (enable) ? newOff : off); // dmc3.exe+213B53 - 48 8D BE 40A50000 - LEA RDI,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x213DDD + 3), (enable) ? newOff : off); // dmc3.exe+213DDD - 48 8D BE 40A50000 - LEA RDI,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x213E60 + 3), (enable) ? newOff : off); // dmc3.exe+213E60 - 48 81 C1 40A50000 - ADD RCX,0000A540
		Write<uint32>((appBaseAddr + 0x214353 + 3), (enable) ? newOff : off); // dmc3.exe+214353 - 48 8D BE 40A50000 - LEA RDI,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x214736 + 3), (enable) ? newOff : off); // dmc3.exe+214736 - 48 8D BE 40A50000 - LEA RDI,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x2149B3 + 3), (enable) ? newOff : off); // dmc3.exe+2149B3 - 48 8D BE 40A50000 - LEA RDI,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x214A24 + 3), (enable) ? newOff : off); // dmc3.exe+214A24 - 48 81 C1 40A50000 - ADD RCX,0000A540
		Write<uint32>((appBaseAddr + 0x216737 + 3), (enable) ? newOff : off); // dmc3.exe+216737 - 48 8D 8F 40A50000 - LEA RCX,[RDI+0000A540]
		Write<uint32>((appBaseAddr + 0x2167A7 + 3), (enable) ? newOff : off); // dmc3.exe+2167A7 - 48 8D 8F 40A50000 - LEA RCX,[RDI+0000A540]
		Write<uint32>((appBaseAddr + 0x216817 + 3), (enable) ? newOff : off); // dmc3.exe+216817 - 48 8D 8F 40A50000 - LEA RCX,[RDI+0000A540]
		Write<uint32>((appBaseAddr + 0x216887 + 3), (enable) ? newOff : off); // dmc3.exe+216887 - 48 8D 8F 40A50000 - LEA RCX,[RDI+0000A540]
		Write<uint32>((appBaseAddr + 0x2168F7 + 3), (enable) ? newOff : off); // dmc3.exe+2168F7 - 48 8D 8F 40A50000 - LEA RCX,[RDI+0000A540]
		Write<uint32>((appBaseAddr + 0x216967 + 3), (enable) ? newOff : off); // dmc3.exe+216967 - 48 8D 8F 40A50000 - LEA RCX,[RDI+0000A540]
		Write<uint32>((appBaseAddr + 0x2169D7 + 3), (enable) ? newOff : off); // dmc3.exe+2169D7 - 48 8D 8F 40A50000 - LEA RCX,[RDI+0000A540]
		// Write<uint32>((appBaseAddr + 0x34B45D + 3), (enable) ? newOff : off); // dmc3.exe+34B45D - 48 81 C1 40A50000 - ADD RCX,0000A540
	}
	// 0xAA00
	{
		constexpr auto off = offsetof(ActorData, devilSubmodelPhysicsLinkData[0][0]);
		constexpr auto newOff = offsetof(ActorData, newDevilSubmodelPhysicsLinkData[0][0]);
		static_assert(off == 0xAA00);
		Write<uint32>((appBaseAddr + 0x1DD59B + 3), (enable) ? newOff : off); // dmc3.exe+1DD59B - 48 8D 8B 00AA0000 - LEA RCX,[RBX+0000AA00]
		Write<uint32>((appBaseAddr + 0x1DDE83 + 3), (enable) ? newOff : off); // dmc3.exe+1DDE83 - 48 81 C1 00AA0000 - ADD RCX,0000AA00
		Write<uint32>((appBaseAddr + 0x2137AA + 3), (enable) ? newOff : off); // dmc3.exe+2137AA - 48 8D 96 00AA0000 - LEA RDX,[RSI+0000AA00]
		Write<uint32>((appBaseAddr + 0x213BAA + 3), (enable) ? newOff : off); // dmc3.exe+213BAA - 48 8D 96 00AA0000 - LEA RDX,[RSI+0000AA00]
		Write<uint32>((appBaseAddr + 0x213E8C + 3), (enable) ? newOff : off); // dmc3.exe+213E8C - 48 8D 96 00AA0000 - LEA RDX,[RSI+0000AA00]
		Write<uint32>((appBaseAddr + 0x21439E + 3), (enable) ? newOff : off); // dmc3.exe+21439E - 48 8D 96 00AA0000 - LEA RDX,[RSI+0000AA00]
		Write<uint32>((appBaseAddr + 0x21477E + 3), (enable) ? newOff : off); // dmc3.exe+21477E - 48 8D 96 00AA0000 - LEA RDX,[RSI+0000AA00]
		Write<uint32>((appBaseAddr + 0x214A50 + 3), (enable) ? newOff : off); // dmc3.exe+214A50 - 48 8D 96 00AA0000 - LEA RDX,[RSI+0000AA00]
		// Trash<uint32>((appBaseAddr + 0x50C997 + 3), (enable) ? newOff : off); // dmc3.exe+50C997 - 00 80 0000AA00 - ADD [RAX+00AA0000],AL
		// Trash<uint32>((appBaseAddr + 0x50C9A7 + 3), (enable) ? newOff : off); // dmc3.exe+50C9A7 - 00 80 0000AA00 - ADD [RAX+00AA0000],AL
		// Trash<uint32>((appBaseAddr + 0x50C9E7 + 3), (enable) ? newOff : off); // dmc3.exe+50C9E7 - 00 80 0000AA00 - ADD [RAX+00AA0000],AL
		// Trash<uint32>((appBaseAddr + 0x50C9F7 + 3), (enable) ? newOff : off); // dmc3.exe+50C9F7 - 00 80 0000AA00 - ADD [RAX+00AA0000],AL
		// Trash<uint32>((appBaseAddr + 0x50CA07 + 3), (enable) ? newOff : off); // dmc3.exe+50CA07 - 00 80 0000AA00 - ADD [RAX+00AA0000],AL
		// Trash<uint32>((appBaseAddr + 0x50CA27 + 3), (enable) ? newOff : off); // dmc3.exe+50CA27 - 00 80 0000AA00 - ADD [RAX+00AA0000],AL
	}
	// 0xAAC0
	{
		constexpr auto off = (offsetof(ActorData, devilSubmodelPhysicsLinkData[0][0]) + 0xC0);
		constexpr auto newOff = (offsetof(ActorData, newDevilSubmodelPhysicsLinkData[0][0]) + 0xC0);
		static_assert(off == 0xAAC0);
		Write<uint32>((appBaseAddr + 0x213832 + 3), (enable) ? newOff : off); // dmc3.exe+213832 - 48 8D 96 C0AA0000 - LEA RDX,[RSI+0000AAC0]
		Write<uint32>((appBaseAddr + 0x213C36 + 3), (enable) ? newOff : off); // dmc3.exe+213C36 - 48 8D 96 C0AA0000 - LEA RDX,[RSI+0000AAC0]
		Write<uint32>((appBaseAddr + 0x213EED + 3), (enable) ? newOff : off); // dmc3.exe+213EED - 48 8D 96 C0AA0000 - LEA RDX,[RSI+0000AAC0]
		Write<uint32>((appBaseAddr + 0x21442A + 3), (enable) ? newOff : off); // dmc3.exe+21442A - 48 8D 96 C0AA0000 - LEA RDX,[RSI+0000AAC0]
		Write<uint32>((appBaseAddr + 0x21480A + 3), (enable) ? newOff : off); // dmc3.exe+21480A - 48 8D 96 C0AA0000 - LEA RDX,[RSI+0000AAC0]
		Write<uint32>((appBaseAddr + 0x214AB5 + 3), (enable) ? newOff : off); // dmc3.exe+214AB5 - 48 8D 96 C0AA0000 - LEA RDX,[RSI+0000AAC0]
	}











































}















































void ToggleCountAdjustments(bool enable)
{
	LogFunction(enable);

	// Model Data
	{
		constexpr uint32 count = 3;
		constexpr uint32 newCount = 6;
		// Create
		Write<uint32>((appBaseAddr + 0x1DDB6A + 2), (enable) ? newCount : count); // dmc3.exe+1DDB6A - 41 B8 03000000 - mov r8d,00000003
		// Free
		Write<uint32>((appBaseAddr + 0x1DE42D + 2), (enable) ? newCount : count); // dmc3.exe+1DE42D - 41 B8 03000000 - mov r8d,00000003
	}

	// Model Physics Metadata Pool
	{
		constexpr uint32 count = (4 * 24);
		constexpr uint32 newCount = (7 * 24);
		// Create
		// Write<uint32>((appBaseAddr + 0x1DE935 + 2), (enable) ? newCount : count); // dmc3.exe+1DE935 - 41 B9 60000000 - MOV R9D,00000060
		// Write<uint32>((appBaseAddr + 0x1DEA4E + 2), (enable) ? newCount : count); // dmc3.exe+1DEA4E - 41 B9 60000000 - MOV R9D,00000060
		// Write<uint32>((appBaseAddr + 0x1DEB4A + 2), (enable) ? newCount : count); // dmc3.exe+1DEB4A - 41 B9 60000000 - MOV R9D,00000060
		Write<uint32>((appBaseAddr + 0x1DEC63 + 2), (enable) ? newCount : count); // dmc3.exe+1DEC63 - 41 B9 60000000 - mov r9d,00000060
		// Free
		// Handled together with Model Allocation Data.
	}

	// Model Allocation Data
	{
		constexpr uint32 count = 209;
		constexpr uint32 newCount = 512;
		// Create
		Write<uint32>((appBaseAddr + 0x1DDB95 + 2), (enable) ? newCount : count); // dmc3.exe+1DDB95 - 41 B8 D1000000 - mov r8d,000000D1
		Write<uint32>((appBaseAddr + 0x1DD172 + 1), (enable) ? newCount : count); // dmc3.exe+1DD172 - B8 D1000000 - mov eax,000000D1
		// Free
		Write<uint32>((appBaseAddr + 0x1DE40E + 2), (enable) ? newCount : count); // dmc3.exe+1DE40E - 41 B8 D1000000 - mov r8d,000000D1
		// Unknown
		// Write<uint32>((appBaseAddr + 0x13C9F1 + 1), (enable) ? newCount : count); // dmc3.exe+13C9F1 - BA D1000000 - MOV EDX,000000D1
		// Write<uint32>((appBaseAddr + 0x13CA38 + 1), (enable) ? newCount : count); // dmc3.exe+13CA38 - BA D1000000 - MOV EDX,000000D1
		// Write<uint32>((appBaseAddr + 0x1DD242 + 1), (enable) ? newCount : count); // dmc3.exe+1DD242 - B8 D1000000 - MOV EAX,000000D1
		// Write<uint32>((appBaseAddr + 0x1DD312 + 1), (enable) ? newCount : count); // dmc3.exe+1DD312 - B8 D1000000 - MOV EAX,000000D1
		// Write<uint32>((appBaseAddr + 0x1DD3E2 + 1), (enable) ? newCount : count); // dmc3.exe+1DD3E2 - B8 D1000000 - MOV EAX,000000D1
		// Write<uint32>((appBaseAddr + 0x34B85B + 2), (enable) ? newCount : count); // dmc3.exe+34B85B - 41 B8 D1000000 - MOV R8D,000000D1
	}

	// Recovery Data
	{
		constexpr int8 count = -(static_cast<int8>(sizeof(RecoveryData) - 3));
		constexpr int8 newCount = -(static_cast<int8>(sizeof(RecoveryData) - 6));
		// Create
		Write<int8>((appBaseAddr + 0x1DDC28 + 3), (enable) ? newCount : count); // dmc3.exe+1DDC28 - 44 8D 42 93 - lea r8d,[rdx-6D]
		// Free
		Write<int8>((appBaseAddr + 0x1DE3C0 + 3), (enable) ? newCount : count); // dmc3.exe+1DE3C0 - 44 8D 42 93 - lea r8d,[rdx-6D]
	}

	// Body Part Data
	{
		constexpr uint32 count = (3 * 2);
		constexpr uint32 newCount = (6 * 2);
		// Create
		Write<uint8>((appBaseAddr + 0x1DDD82 + 3), (enable) ? static_cast<uint8>(newCount) : static_cast<uint8>(count)); // dmc3.exe+1DDD82 - 45 8D 47 06 - lea r8d,[r15+06]
		// Free
		Write<uint32>((appBaseAddr + 0x1DE307 + 2), (enable) ? newCount : count); // dmc3.exe+1DE307 - 41 B8 06000000 - mov r8d,00000006
	}

	// Submodel Data
	{
		constexpr uint32 count = (1 + (2 * 2));
		constexpr uint32 newCount = (1 + (5 * 2));
		// Create
		Write<uint32>((appBaseAddr + 0x1DD4F1 + 2), (enable) ? newCount : count); // dmc3.exe+1DD4F1 - 41 B8 05000000 - mov r8d,00000005
		// Free
		Write<uint32>((appBaseAddr + 0x1DDF31 + 2), (enable) ? newCount : count); // dmc3.exe+1DDF31 - 41 B8 05000000 - mov r8d,00000005
	}

	// Model Shadow Data
	{
		constexpr uint32 count = 3;
		constexpr uint32 newCount = 6;
		// Create
		Write<uint32>((appBaseAddr + 0x1DD51C + 2), (enable) ? newCount : count); // dmc3.exe+1DD51C - 41 B8 03000000 - mov r8d,00000003
		// Free
		Write<uint32>((appBaseAddr + 0x1DDF12 + 2), (enable) ? newCount : count); // dmc3.exe+1DDF12 - 41 B8 03000000 - mov r8d,00000003
	}

	// Submodel Shadow Data
	{
		constexpr uint32 count = (1 + (2 * 2));
		constexpr uint32 newCount = (1 + (5 * 2));
		// Create
		Write<uint32>((appBaseAddr + 0x1DD540 + 2), (enable) ? newCount : count); // dmc3.exe+1DD540 - 41 B8 05000000 - mov r8d,00000005
		// Free
		Write<uint32>((appBaseAddr + 0x1DDEF3 + 2), (enable) ? newCount : count); // dmc3.exe+1DDEF3 - 41 B8 05000000 - mov r8d,00000005
	}

	// Submodel Physics Metadata Pool
	{
		constexpr uint32 count = 39;
		constexpr uint32 newCount = 39;
		// Create
		Write<uint32>((appBaseAddr + 0x1DEC9D + 2), (enable) ? newCount : count); // dmc3.exe+1DEC9D - 41 B9 27000000 - mov r9d,00000027
		// Free
		// Handled together with Model Allocation Data.
	}

	// Submodel Physics Data
	{
		constexpr uint32 count = 1;
		constexpr uint32 newCount = 1;
		// Create
		Write<uint32>((appBaseAddr + 0x1DD56B + 2), (enable) ? newCount : count); // dmc3.exe+1DD56B - 41 B8 01000000 - mov r8d,00000001
		// Free
		Write<uint32>((appBaseAddr + 0x1DDED4 + 2), (enable) ? newCount : count); // dmc3.exe+1DDED4 - 41 B8 01000000 - mov r8d,00000001
	}

	// Devil Model Physics Metadata Pool
	{
		constexpr uint32 count = (2 * 36);
		constexpr uint32 newCount = (5 * 36);
		// Create
		Write<uint32>((appBaseAddr + 0x1DEC80 + 2), (enable) ? newCount : count); // dmc3.exe+1DEC80 - 41 B9 48000000 - mov r9d,00000048
		// Free
		// Handled together with Model Allocation Data.
	}

	// Devil Submodel Physics Data
	{
		constexpr uint32 count = (2 * 2);
		constexpr uint32 newCount = (5 * 2);
		// Create
		Write<uint32>((appBaseAddr + 0x1DD58F + 2), (enable) ? newCount : count); // dmc3.exe+1DD58F - 41 B8 04000000 - mov r8d,00000004
		// Free
		Write<uint32>((appBaseAddr + 0x1DDEB5 + 2), (enable) ? newCount : count); // dmc3.exe+1DDEB5 - 41 B8 04000000 - mov r8d,00000004
	}

	// Devil Submodel Physics Link Data
	{
		constexpr uint32 count = (2 * 2 * 4);
		constexpr uint32 newCount = (5 * 2 * 4);
		// Create
		Write<uint32>((appBaseAddr + 0x1DD5BA + 2), (enable) ? newCount : count); // dmc3.exe+1DD5BA - 41 B8 10000000 - mov r8d,00000010
		// Free
		Write<uint32>((appBaseAddr + 0x1DDE96 + 2), (enable) ? newCount : count); // dmc3.exe+1DDE96 - 41 B8 10000000 - mov r8d,00000010
	}
}

export void Model_Init()
{
	LogFunction();


	//auto modelPhysicsMetadataOffs = HighAlloc(64);


	//return;


	{
		auto off = HighAlloc(64);
		if (!off)
		{
			Log("HighAlloc failed.");
			return;
		}
		for_all(uint32, index, 7)
		{
			(reinterpret_cast<uint32 *>(off))[index] = (index * 24);
		}
		WriteAddress((appBaseAddr + 0x1FA60B), off, 7);
		WriteAddress((appBaseAddr + 0x1FAA57), off, 7);
		WriteAddress((appBaseAddr + 0x1FAA77), off, 7);
		WriteAddress((appBaseAddr + 0x1FAA97), off, 7);
		WriteAddress((appBaseAddr + 0x1FB031), off, 7);
		WriteAddress((appBaseAddr + 0x1FBAC4), off, 7);
		/*
		dmc3.exe+ - 48 8D 0D 165D2E00 - lea rcx,[dmc3.exe+4E0328]
		dmc3.exe+ - 48 8D 0D CA582E00 - lea rcx,[dmc3.exe+4E0328]
		dmc3.exe+ - 48 8D 15 AA582E00 - lea rdx,[dmc3.exe+4E0328]
		dmc3.exe+ - 4C 8D 05 8A582E00 - lea r8,[dmc3.exe+4E0328]
		dmc3.exe+ - 48 8D 3D F0522E00 - lea rdi,[dmc3.exe+4E0328]
		dmc3.exe+ - 48 8D 3D 5D482E00 - lea rdi,[dmc3.exe+4E0328]
		*/
	}



	// Devil Coat Update Ignore Range Check
	{
		WriteAddress((appBaseAddr + 0x218982), (appBaseAddr + 0x218988), 6);
		/*
		dmc3.exe+21897C - 8D 41 FF          - lea eax,[rcx-01]
		dmc3.exe+21897F - 83 F8 01          - cmp eax,01
		dmc3.exe+218982 - 0F87 F9050000     - ja dmc3.exe+218F81
		dmc3.exe+218988 - 83 BF 183A0000 01 - cmp dword ptr [rdi+00003A18],01
		*/
	}



	





	// // Fix Model Physics Metadata Pool Offset
	// {
	// 	constexpr byte8 sect0[] =
	// 	{
	// 		0x8B, 0x81, 0x6C, 0x3E, 0x00, 0x00, // mov eax,[rcx+00003E6C]
	// 		0x6B, 0xC0, 0x18,                   // imul eax,eax,18
	// 		0xC3,                               // ret
	// 	};
	// 	auto func = CreateFunction(0, 0, false, false, sizeof(sect0));
	// 	memcpy(func.sect0, sect0, sizeof(sect0));
	// 	WriteJump((appBaseAddr + 0x1FAA50), func.addr, 2);
	// 	/*
	// 	dmc3.exe+1FAA50 - 48 63 81 6C3E0000 - movsxd rax,dword ptr [rcx+00003E6C]
	// 	*/
	// }












	// {
	// 	auto func = CreateFunction(NewFunc<ActorDataDante>);
	// 	WriteCall((appBaseAddr + 0x212D6F), func.addr); // dante
	// 	WriteCall((appBaseAddr + 0x21459A), func.addr); // rebellion
	// }




	// {
	// 	constexpr byte8 sect1[] =
	// 	{
	// 		mov_rcx_rsi,
	// 	};
	// 	auto func = CreateFunction(UpdateDevilModelDante, (appBaseAddr + 0x21344F), true, true, 0, sizeof(sect1));
	// 	memcpy(func.sect1, sect1, sizeof(sect1));
	// 	WriteJump((appBaseAddr + 0x213167), func.addr, 2);
	// }





	ToggleRelocations(true);
	ToggleCountAdjustments(true);



	//return;



	//if (!devilAuras.Init(512))
	//{
	//	Log("devilAuras.Init failed.");
	//	return;
	//}



	// ToggleBodyPartDataRelocation(true);
	// ToggleSubmodelDataRelocation(true);
	// ToggleModelShadowDataRelocation(true);
	// ToggleSubmodelShadowDataRelocation(true);
	// ToggleSubmodelPhysicsMetadataRelocation(true);
	// ToggleSubmodelPhysicsDataRelocation(true);
	// ToggleDevilSubmodelPhysicsDataRelocation(true);
	// ToggleDevilSubmodelPhysicsLinkDataRelocation(true);
	// ToggleDevilModelPhysicsLinkMetadataPoolRelocation(true);

	
	//ToggleModelPhysicsMetadataPoolRelocation(true);




	//ToggleExpansion(true);
	//ToggleSubmodelRelocation(true);




	// Force Only Rebellion
	//WriteJump((appBaseAddr + 0x214B29), (appBaseAddr + 0x21344F));


	//return;





	{
		auto func = CreateFunction(UpdateModelDante);
		//WriteCall((appBaseAddr + 0x212CB3), func.addr);
		/*
		dmc3.exe+212CB3 - E8 98200000       - call dmc3.exe+214D50
		dmc3.exe+212CB8 - 48 8D 86 A0380000 - lea rax,[rsi+000038A0]
		*/
	}


	//return;



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
		*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ActorData, newForceFiles);
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
		*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ActorData, newForceFiles);
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
		*reinterpret_cast<uint32 *>(func.sect0 + 9) = offsetof(ActorData, newForceFiles);
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
			0x48, 0x8B, 0x96, 0x00, 0x00, 0x00, 0x00, // mov rdx,[rsi+000018A8]
			0xEB, 0x07,                               // jmp short
			0x48, 0x8B, 0x96, 0x00, 0x00, 0x00, 0x00, // mov rdx,[rsi+00001898]
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x2120CB), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ActorData, newForceFiles);
		*reinterpret_cast<uint32 *>(func.sect0 + 0xB) = offsetof(ActorData, newForceFilesCharacter);
		*reinterpret_cast<uint8 *>(func.sect0 + 0xF) = CHAR_LADY;
		*reinterpret_cast<uint32 *>(func.sect0 + 0x15) = offsetof(ActorData, newModelPhysicsMetadataPool[0][5]);
		*reinterpret_cast<uint32 *>(func.sect0 + 0x1E) = offsetof(ActorData, newModelPhysicsMetadataPool[0][3]);
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
	//	*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ActorData, newForceFiles);
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
	//	*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ActorData, devil);
	//	*reinterpret_cast<uint32 *>(func.sect0 + 0xB) = offsetof(ActorData, newForceFiles);
	//	*reinterpret_cast<uint32 *>(func.sect0 + 0x14) = offsetof(ActorData, newForceFilesCharacter);
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
	//	*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ActorData, newForceFiles);
	//	*reinterpret_cast<uint32 *>(func.sect0 + 0xB) = offsetof(ActorData, newForceFilesCharacter);
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
	//	*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ActorData, newForceLadyFiles);
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
		*reinterpret_cast<uint32 *>(func.sect0 + 0xF) = offsetof(ActorData, newEffectIndices);
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
		*reinterpret_cast<uint32 *>(func.sect0 + 0xF) = offsetof(ActorData, newEffectIndices);
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
		*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ActorData, newEffectIndices[1]);
		*reinterpret_cast<uint32 *>(func.sect0 + 8) = offsetof(ActorData, newEffectIndices[2]);
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
		*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ActorData, newEffectIndices[1]);
		*reinterpret_cast<uint32 *>(func.sect0 + 8) = offsetof(ActorData, newEffectIndices[2]);
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
		*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(ActorData, newEffectIndices);
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

#ifdef __GARBAGE__
	// // 0x18A0
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][4]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][4]);
		//static_assert(off == 0x18A0);
	// 	// Write<uint32>((appBaseAddr + 0xCEAA0 + 3), (enable) ? newOff : off); // dmc3.exe+CEAA0 - 48 63 83 A0180000 - MOVSXD RAX,DWORD PTR [RBX+000018A0]
	// 	// Trash<uint32>((appBaseAddr + 0xCECB2 + 3), (enable) ? newOff : off); // dmc3.exe+CECB2 - 8B 83 A0180000 - MOV EAX,[RBX+000018A0]
	// 	// Trash<uint32>((appBaseAddr + 0xCF9A9 + 3), (enable) ? newOff : off); // dmc3.exe+CF9A9 - 89 91 A0180000 - MOV [RCX+000018A0],EDX
	// 	// Write<uint32>((appBaseAddr + 0xCFA20 + 3), (enable) ? newOff : off); // dmc3.exe+CFA20 - 49 63 80 A0180000 - MOVSXD RAX,DWORD PTR [R8+000018A0]
	// 	// Trash<uint32>((appBaseAddr + 0xD33F0 + 3), (enable) ? newOff : off); // dmc3.exe+D33F0 - 8B 81 A0180000 - MOV EAX,[RCX+000018A0]
	// 	// Trash<uint32>((appBaseAddr + 0x1508D9 + 3), (enable) ? newOff : off); // dmc3.exe+1508D9 - BA A0180000 - MOV EDX,000018A0
	// 	// Trash<uint32>((appBaseAddr + 0x150F66 + 3), (enable) ? newOff : off); // dmc3.exe+150F66 - BA A0180000 - MOV EDX,000018A0
	// 	// Write<uint32>((appBaseAddr + 0x2588FA + 3), (enable) ? newOff : off); // dmc3.exe+2588FA - 48 89 83 A0180000 - MOV [RBX+000018A0],RAX
	// 	// Write<uint32>((appBaseAddr + 0x259659 + 3), (enable) ? newOff : off); // dmc3.exe+259659 - 48 89 9A A0180000 - MOV [RDX+000018A0],RBX
	// 	// Write<uint32>((appBaseAddr + 0x2596F7 + 3), (enable) ? newOff : off); // dmc3.exe+2596F7 - 89 82 A0180000 - MOV [RDX+000018A0],EAX
	// 	// Write<uint32>((appBaseAddr + 0x25B0CF + 3), (enable) ? newOff : off); // dmc3.exe+25B0CF - 48 89 BB A0180000 - MOV [RBX+000018A0],RDI
	// 	// Write<uint32>((appBaseAddr + 0x25BFA0 + 3), (enable) ? newOff : off); // dmc3.exe+25BFA0 - 48 C7 82 A0180000 00000000 - MOV QWORD PTR [RDX+000018A0],00000000
	// 	// Trash<uint32>((appBaseAddr + 0x25C042 + 3), (enable) ? newOff : off); // dmc3.exe+25C042 - 89 82 A0180000 - MOV [RDX+000018A0],EAX
	// }

	// // 0x18B0
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][6]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][6]);
		//static_assert(off == 0x18B0);
	// 	// Trash<uint32>((appBaseAddr + 0xCFA01 + 3), (enable) ? newOff : off); // dmc3.exe+CFA01 - 41 C7 80 B0180000 02000000 - MOV [R8+000018B0],00000002
	// 	// Write<uint32>((appBaseAddr + 0xCFA19 + 3), (enable) ? newOff : off); // dmc3.exe+CFA19 - 49 89 90 B0180000 - MOV [R8+000018B0],RDX
	// 	// Trash<uint32>((appBaseAddr + 0xD3420 + 3), (enable) ? newOff : off); // dmc3.exe+D3420 - 8B 81 B0180000 - MOV EAX,[RCX+000018B0]
	// 	// Trash<uint32>((appBaseAddr + 0xF92B0 + 3), (enable) ? newOff : off); // dmc3.exe+F92B0 - 89 8B B0180000 - MOV [RBX+000018B0],ECX
	// 	// Write<uint32>((appBaseAddr + 0x258911 + 3), (enable) ? newOff : off); // dmc3.exe+258911 - 48 C7 83 B0180000 0050C347 - MOV QWORD PTR [RBX+000018B0],47C35000
	// 	// Write<uint32>((appBaseAddr + 0x259670 + 3), (enable) ? newOff : off); // dmc3.exe+259670 - 48 C7 82 B0180000 0050C347 - MOV QWORD PTR [RDX+000018B0],47C35000
	// 	// Write<uint32>((appBaseAddr + 0x25B0E6 + 3), (enable) ? newOff : off); // dmc3.exe+25B0E6 - 48 C7 83 B0180000 0050C347 - MOV QWORD PTR [RBX+000018B0],47C35000
	// 	// Write<uint32>((appBaseAddr + 0x25BFBB + 3), (enable) ? newOff : off); // dmc3.exe+25BFBB - 48 C7 82 B0180000 0050C347 - MOV QWORD PTR [RDX+000018B0],47C35000
	// 	// Write<uint32>((appBaseAddr + 0x2932B8 + 3), (enable) ? newOff : off); // dmc3.exe+2932B8 - 48 8D 93 B0180000 - LEA RDX,[RBX+000018B0]
	// }
	// // 0x18B8
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][7]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][7]);
		//static_assert(off == 0x18B8);
	// 	// Trash<uint32>((appBaseAddr + 0xCFB55 + 3), (enable) ? newOff : off); // dmc3.exe+CFB55 - 41 83 B8 B8180000 0E - CMP DWORD PTR [R8+000018B8],0E
	// 	// Trash<uint32>((appBaseAddr + 0xFDE7C + 3), (enable) ? newOff : off); // dmc3.exe+FDE7C - 0F11 8F B8180000 - MOVUPS [RDI+000018B8],XMM1
	// 	// Trash<uint32>((appBaseAddr + 0x25891C + 3), (enable) ? newOff : off); // dmc3.exe+25891C - 89 83 B8180000 - MOV [RBX+000018B8],EAX
	// 	// Trash<uint32>((appBaseAddr + 0x25967B + 3), (enable) ? newOff : off); // dmc3.exe+25967B - 89 9A B8180000 - MOV [RDX+000018B8],EBX
	// 	// Trash<uint32>((appBaseAddr + 0x25B0F1 + 3), (enable) ? newOff : off); // dmc3.exe+25B0F1 - 89 BB B8180000 - MOV [RBX+000018B8],EDI
	// 	// Trash<uint32>((appBaseAddr + 0x25BFC6 + 3), (enable) ? newOff : off); // dmc3.exe+25BFC6 - 89 9A B8180000 - MOV [RDX+000018B8],EBX
	// }
	// // 0x18C0
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][8]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][8]);
		//static_assert(off == 0x18C0);
	// 	// Trash<uint32>((appBaseAddr + 0x258930 + 3), (enable) ? newOff : off); // dmc3.exe+258930 - 66 89 BB C0180000 - MOV [RBX+000018C0],DI
	// 	// Trash<uint32>((appBaseAddr + 0x25968F + 3), (enable) ? newOff : off); // dmc3.exe+25968F - 66 89 BA C0180000 - MOV [RDX+000018C0],DI
	// 	// Trash<uint32>((appBaseAddr + 0x25B105 + 3), (enable) ? newOff : off); // dmc3.exe+25B105 - 66 89 B3 C0180000 - MOV [RBX+000018C0],SI
	// 	// Trash<uint32>((appBaseAddr + 0x25BFDA + 3), (enable) ? newOff : off); // dmc3.exe+25BFDA - 66 89 BA C0180000 - MOV [RDX+000018C0],DI
	// }
	// // 0x18C8
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][9]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][9]);
		//static_assert(off == 0x18C8);
	// 	// Trash<uint32>((appBaseAddr + 0xFDE8A + 3), (enable) ? newOff : off); // dmc3.exe+FDE8A - 0F11 87 C8180000 - MOVUPS [RDI+000018C8],XMM0
	// 	// Trash<uint32>((appBaseAddr + 0x25894C + 3), (enable) ? newOff : off); // dmc3.exe+25894C - 66 89 BB C8180000 - MOV [RBX+000018C8],DI
	// 	// Trash<uint32>((appBaseAddr + 0x2596AB + 3), (enable) ? newOff : off); // dmc3.exe+2596AB - 66 89 BA C8180000 - MOV [RDX+000018C8],DI
	// 	// Trash<uint32>((appBaseAddr + 0x25B121 + 3), (enable) ? newOff : off); // dmc3.exe+25B121 - 66 89 B3 C8180000 - MOV [RBX+000018C8],SI
	// 	// Trash<uint32>((appBaseAddr + 0x25BFF6 + 3), (enable) ? newOff : off); // dmc3.exe+25BFF6 - 66 89 BA C8180000 - MOV [RDX+000018C8],DI
	// }
	// // 0x18D0
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][10]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][10]);
		//static_assert(off == 0x18D0);
	// 	// Trash<uint32>((appBaseAddr + 0x258968 + 3), (enable) ? newOff : off); // dmc3.exe+258968 - 66 89 BB D0180000 - MOV [RBX+000018D0],DI
	// 	// Trash<uint32>((appBaseAddr + 0x2596C7 + 3), (enable) ? newOff : off); // dmc3.exe+2596C7 - 66 89 BA D0180000 - MOV [RDX+000018D0],DI
	// 	// Trash<uint32>((appBaseAddr + 0x25B13D + 3), (enable) ? newOff : off); // dmc3.exe+25B13D - 66 89 B3 D0180000 - MOV [RBX+000018D0],SI
	// 	// Trash<uint32>((appBaseAddr + 0x25C012 + 3), (enable) ? newOff : off); // dmc3.exe+25C012 - 66 89 BA D0180000 - MOV [RDX+000018D0],DI
	// }
	// // 0x18D8
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][11]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][11]);
		//static_assert(off == 0x18D8);
	// 	// Trash<uint32>((appBaseAddr + 0xFDE98 + 3), (enable) ? newOff : off); // dmc3.exe+FDE98 - 0F11 8F D8180000 - MOVUPS [RDI+000018D8],XMM1
	// 	// Trash<uint32>((appBaseAddr + 0xFE957 + 3), (enable) ? newOff : off); // dmc3.exe+FE957 - F3 0F11 87 D8180000 - MOVSS [RDI+000018D8],XMM0
	// }
	// // 0x18E0
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][12]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][12]);
		//static_assert(off == 0x18E0);
	// 	// Write<uint32>((appBaseAddr + 0xCBE97 + 3), (enable) ? newOff : off); // dmc3.exe+CBE97 - 48 8D 8E E0180000 - LEA RCX,[RSI+000018E0]
	// 	// Write<uint32>((appBaseAddr + 0xCBFB4 + 3), (enable) ? newOff : off); // dmc3.exe+CBFB4 - 48 8D 8E E0180000 - LEA RCX,[RSI+000018E0]
	// 	// Write<uint32>((appBaseAddr + 0xD21DB + 3), (enable) ? newOff : off); // dmc3.exe+D21DB - 4D 8D 8D E0180000 - LEA R9,[R13+000018E0]
	// 	// Write<uint32>((appBaseAddr + 0xD224F + 3), (enable) ? newOff : off); // dmc3.exe+D224F - 49 8B 85 E0180000 - MOV RAX,[R13+000018E0]
	// 	// Write<uint32>((appBaseAddr + 0xD226B + 3), (enable) ? newOff : off); // dmc3.exe+D226B - 49 8D 8D E0180000 - LEA RCX,[R13+000018E0]
	// 	// Write<uint32>((appBaseAddr + 0xD2DEB + 3), (enable) ? newOff : off); // dmc3.exe+D2DEB - 48 8D 8F E0180000 - LEA RCX,[RDI+000018E0]
	// 	// Write<uint32>((appBaseAddr + 0x259652 + 3), (enable) ? newOff : off); // dmc3.exe+259652 - 48 8D 82 E0180000 - LEA RAX,[RDX+000018E0]
	// 	// Write<uint32>((appBaseAddr + 0x25BF99 + 3), (enable) ? newOff : off); // dmc3.exe+25BF99 - 48 8D 82 E0180000 - LEA RAX,[RDX+000018E0]
	// 	// Write<uint32>((appBaseAddr + 0x348016 + 3), (enable) ? newOff : off); // dmc3.exe+348016 - 48 81 C1 E0180000 - ADD RCX,000018E0
	// }
	// // 0x18E8
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][13]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][13]);
		//static_assert(off == 0x18E8);
	// 	// Trash<uint32>((appBaseAddr + 0xFDEA6 + 3), (enable) ? newOff : off); // dmc3.exe+FDEA6 - 0F11 87 E8180000 - MOVUPS [RDI+000018E8],XMM0
	// }
	// // 0x18F0
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][14]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][14]);
		//static_assert(off == 0x18F0);
	// 	// Trash<uint32>((appBaseAddr + 0x25A5EA + 3), (enable) ? newOff : off); // dmc3.exe+25A5EA - 0F29 87 F0180000 - MOVAPS [RDI+000018F0],XMM0
	// 	// Write<uint32>((appBaseAddr + 0x25CE6A + 3), (enable) ? newOff : off); // dmc3.exe+25CE6A - 48 8D 8F F0180000 - LEA RCX,[RDI+000018F0]
	// 	// Write<uint32>((appBaseAddr + 0x25CE87 + 3), (enable) ? newOff : off); // dmc3.exe+25CE87 - 48 8D 8F F0180000 - LEA RCX,[RDI+000018F0]
	// 	// Write<uint32>((appBaseAddr + 0x25CE93 + 3), (enable) ? newOff : off); // dmc3.exe+25CE93 - 48 8D 8F F0180000 - LEA RCX,[RDI+000018F0]
	// 	// Write<uint32>((appBaseAddr + 0x25CEA6 + 3), (enable) ? newOff : off); // dmc3.exe+25CEA6 - 48 8D 8F F0180000 - LEA RCX,[RDI+000018F0]
	// 	// Write<uint32>((appBaseAddr + 0x2919D8 + 3), (enable) ? newOff : off); // dmc3.exe+2919D8 - 48 89 83 F0180000 - MOV [RBX+000018F0],RAX
	// 	// Write<uint32>((appBaseAddr + 0x29213E + 3), (enable) ? newOff : off); // dmc3.exe+29213E - 48 89 BB F0180000 - MOV [RBX+000018F0],RDI
	// 	// Write<uint32>((appBaseAddr + 0x292250 + 3), (enable) ? newOff : off); // dmc3.exe+292250 - 48 89 83 F0180000 - MOV [RBX+000018F0],RAX
	// 	// Write<uint32>((appBaseAddr + 0x292281 + 3), (enable) ? newOff : off); // dmc3.exe+292281 - 48 8B 8B F0180000 - MOV RCX,[RBX+000018F0]
	// 	// Write<uint32>((appBaseAddr + 0x293030 + 3), (enable) ? newOff : off); // dmc3.exe+293030 - 48 8B 89 F0180000 - MOV RCX,[RCX+000018F0]
	// }
	// // 0x18F8
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][15]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][15]);
		//static_assert(off == 0x18F8);
	// 	// Write<uint32>((appBaseAddr + 0xBAA0B + 3), (enable) ? newOff : off); // dmc3.exe+BAA0B - 48 8B 96 F8180000 - MOV RDX,[RSI+000018F8]
	// 	// Write<uint32>((appBaseAddr + 0xBAB12 + 3), (enable) ? newOff : off); // dmc3.exe+BAB12 - 48 8B 96 F8180000 - MOV RDX,[RSI+000018F8]
	// 	// Trash<uint32>((appBaseAddr + 0xFDEB3 + 3), (enable) ? newOff : off); // dmc3.exe+FDEB3 - 89 87 F8180000 - MOV [RDI+000018F8],EAX
	// 	// Write<uint32>((appBaseAddr + 0x259870 + 3), (enable) ? newOff : off); // dmc3.exe+259870 - 48 89 98 F8180000 - MOV [RAX+000018F8],RBX
	// 	// Write<uint32>((appBaseAddr + 0x259D36 + 3), (enable) ? newOff : off); // dmc3.exe+259D36 - 48 8D BE F8180000 - LEA RDI,[RSI+000018F8]
	// 	// Write<uint32>((appBaseAddr + 0x25A7E8 + 3), (enable) ? newOff : off); // dmc3.exe+25A7E8 - 48 89 84 CF F8180000 - MOV [RDI+RCX*8+000018F8],RAX
	// 	// Write<uint32>((appBaseAddr + 0x25A7F7 + 3), (enable) ? newOff : off); // dmc3.exe+25A7F7 - 48 8B 8C C7 F8180000 - MOV RCX,[RDI+RAX*8+000018F8]
	// 	// Write<uint32>((appBaseAddr + 0x25A820 + 3), (enable) ? newOff : off); // dmc3.exe+25A820 - 48 8B 8C C7 F8180000 - MOV RCX,[RDI+RAX*8+000018F8]
	// 	// Write<uint32>((appBaseAddr + 0x25AAC4 + 3), (enable) ? newOff : off); // dmc3.exe+25AAC4 - 48 8D 8F F8180000 - LEA RCX,[RDI+000018F8]
	// 	// Write<uint32>((appBaseAddr + 0x25AD52 + 3), (enable) ? newOff : off); // dmc3.exe+25AD52 - 48 8D B3 F8180000 - LEA RSI,[RBX+000018F8]
	// 	// Write<uint32>((appBaseAddr + 0x25C5EC + 3), (enable) ? newOff : off); // dmc3.exe+25C5EC - 48 8D B7 F8180000 - LEA RSI,[RDI+000018F8]
	// 	// Write<uint32>((appBaseAddr + 0x25D0C2 + 3), (enable) ? newOff : off); // dmc3.exe+25D0C2 - 48 89 84 CF F8180000 - MOV [RDI+RCX*8+000018F8],RAX
	// 	// Write<uint32>((appBaseAddr + 0x25D0D1 + 3), (enable) ? newOff : off); // dmc3.exe+25D0D1 - 48 8B 8C C7 F8180000 - MOV RCX,[RDI+RAX*8+000018F8]
	// 	// Write<uint32>((appBaseAddr + 0x25D0FA + 3), (enable) ? newOff : off); // dmc3.exe+25D0FA - 48 8B 8C C7 F8180000 - MOV RCX,[RDI+RAX*8+000018F8]
	// 	// Write<uint32>((appBaseAddr + 0x25D2E2 + 3), (enable) ? newOff : off); // dmc3.exe+25D2E2 - 48 8D 8F F8180000 - LEA RCX,[RDI+000018F8]
	// 	// Write<uint32>((appBaseAddr + 0x25D55C + 3), (enable) ? newOff : off); // dmc3.exe+25D55C - 48 8D BB F8180000 - LEA RDI,[RBX+000018F8]
	// 	// Write<uint32>((appBaseAddr + 0x25D5A3 + 3), (enable) ? newOff : off); // dmc3.exe+25D5A3 - 48 8D BB F8180000 - LEA RDI,[RBX+000018F8]
	// 	// Trash<uint32>((appBaseAddr + 0x2919DF + 3), (enable) ? newOff : off); // dmc3.exe+2919DF - 89 83 F8180000 - MOV [RBX+000018F8],EAX
	// 	// Trash<uint32>((appBaseAddr + 0x291D56 + 3), (enable) ? newOff : off); // dmc3.exe+291D56 - 8B 81 F8180000 - MOV EAX,[RCX+000018F8]
	// 	// Trash<uint32>((appBaseAddr + 0x29207E + 3), (enable) ? newOff : off); // dmc3.exe+29207E - 83 BB F8180000 01 - CMP DWORD PTR [RBX+000018F8],01
	// 	// Trash<uint32>((appBaseAddr + 0x2920B4 + 3), (enable) ? newOff : off); // dmc3.exe+2920B4 - 83 BB F8180000 02 - CMP DWORD PTR [RBX+000018F8],02
	// 	// Trash<uint32>((appBaseAddr + 0x2921E2 + 3), (enable) ? newOff : off); // dmc3.exe+2921E2 - 89 BB F8180000 - MOV [RBX+000018F8],EDI
	// 	// Trash<uint32>((appBaseAddr + 0x2926C0 + 3), (enable) ? newOff : off); // dmc3.exe+2926C0 - C7 83 F8180000 01000000 - MOV [RBX+000018F8],00000001
	// 	// Trash<uint32>((appBaseAddr + 0x292858 + 3), (enable) ? newOff : off); // dmc3.exe+292858 - C7 83 F8180000 04000000 - MOV [RBX+000018F8],00000004
	// 	// Trash<uint32>((appBaseAddr + 0x292864 + 3), (enable) ? newOff : off); // dmc3.exe+292864 - C7 83 F8180000 03000000 - MOV [RBX+000018F8],00000003
	// 	// Trash<uint32>((appBaseAddr + 0x292870 + 3), (enable) ? newOff : off); // dmc3.exe+292870 - C7 83 F8180000 02000000 - MOV [RBX+000018F8],00000002
	// 	// Trash<uint32>((appBaseAddr + 0x292D91 + 3), (enable) ? newOff : off); // dmc3.exe+292D91 - C7 83 F8180000 04000000 - MOV [RBX+000018F8],00000004
	// 	// Trash<uint32>((appBaseAddr + 0x292DB8 + 3), (enable) ? newOff : off); // dmc3.exe+292DB8 - C7 83 F8180000 03000000 - MOV [RBX+000018F8],00000003
	// 	// Trash<uint32>((appBaseAddr + 0x292E00 + 3), (enable) ? newOff : off); // dmc3.exe+292E00 - C7 83 F8180000 02000000 - MOV [RBX+000018F8],00000002
	// 	// Trash<uint32>((appBaseAddr + 0x292F97 + 3), (enable) ? newOff : off); // dmc3.exe+292F97 - C7 83 F8180000 04000000 - MOV [RBX+000018F8],00000004
	// 	// Trash<uint32>((appBaseAddr + 0x292FA3 + 3), (enable) ? newOff : off); // dmc3.exe+292FA3 - C7 83 F8180000 03000000 - MOV [RBX+000018F8],00000003
	// }
	// // 0x1900
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][16]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][16]);
		//static_assert(off == 0x1900);
	// 	// Trash<uint32>((appBaseAddr + 0x86274 + 3), (enable) ? newOff : off); // dmc3.exe+86274 - BA 00190000 - MOV EDX,00001900
	// 	// Write<uint32>((appBaseAddr + 0xBAA25 + 3), (enable) ? newOff : off); // dmc3.exe+BAA25 - 48 8B 96 00190000 - MOV RDX,[RSI+00001900]
	// 	// Write<uint32>((appBaseAddr + 0xBAB2C + 3), (enable) ? newOff : off); // dmc3.exe+BAB2C - 48 8B 96 00190000 - MOV RDX,[RSI+00001900]
	// 	// Trash<uint32>((appBaseAddr + 0xD2848 + 3), (enable) ? newOff : off); // dmc3.exe+D2848 - C6 81 00190000 01 - MOV BYTE PTR [RCX+00001900],01
	// 	// Trash<uint32>((appBaseAddr + 0xE0153 + 3), (enable) ? newOff : off); // dmc3.exe+E0153 - 48 B8 1900000019000000 - MOV RAX,0000001900000019
	// 	// Trash<uint32>((appBaseAddr + 0x1F62A7 + 3), (enable) ? newOff : off); // dmc3.exe+1F62A7 - B8 00190000 - MOV EAX,00001900
	// 	// Write<uint32>((appBaseAddr + 0x25987B + 3), (enable) ? newOff : off); // dmc3.exe+25987B - 48 89 98 00190000 - MOV [RAX+00001900],RBX
	// 	// Trash<uint32>((appBaseAddr + 0x25A5F8 + 3), (enable) ? newOff : off); // dmc3.exe+25A5F8 - 0F29 8F 00190000 - MOVAPS [RDI+00001900],XMM1
	// 	// Write<uint32>((appBaseAddr + 0x28581B + 3), (enable) ? newOff : off); // dmc3.exe+28581B - 48 8D 8B 00190000 - LEA RCX,[RBX+00001900]
	// 	// Trash<uint32>((appBaseAddr + 0x292075 + 3), (enable) ? newOff : off); // dmc3.exe+292075 - 83 BB 00190000 05 - CMP DWORD PTR [RBX+00001900],05
	// 	// Trash<uint32>((appBaseAddr + 0x2920AB + 3), (enable) ? newOff : off); // dmc3.exe+2920AB - 83 BB 00190000 06 - CMP DWORD PTR [RBX+00001900],06
	// 	// Trash<uint32>((appBaseAddr + 0x2920EB + 3), (enable) ? newOff : off); // dmc3.exe+2920EB - 8B 8B 00190000 - MOV ECX,[RBX+00001900]
	// 	// Trash<uint32>((appBaseAddr + 0x292162 + 3), (enable) ? newOff : off); // dmc3.exe+292162 - C7 83 00190000 05000000 - MOV [RBX+00001900],00000005
	// 	// Trash<uint32>((appBaseAddr + 0x292170 + 3), (enable) ? newOff : off); // dmc3.exe+292170 - C7 83 00190000 05000000 - MOV [RBX+00001900],00000005
	// 	// Trash<uint32>((appBaseAddr + 0x292189 + 3), (enable) ? newOff : off); // dmc3.exe+292189 - C7 83 00190000 06000000 - MOV [RBX+00001900],00000006
	// 	// Trash<uint32>((appBaseAddr + 0x293342 + 3), (enable) ? newOff : off); // dmc3.exe+293342 - 83 BB 00190000 05 - CMP DWORD PTR [RBX+00001900],05
	// 	// Write<uint32>((appBaseAddr + 0x2A7BEB + 3), (enable) ? newOff : off); // dmc3.exe+2A7BEB - 48 8D 8B 00190000 - LEA RCX,[RBX+00001900]
	// 	// Write<uint32>((appBaseAddr + 0x2ADB29 + 3), (enable) ? newOff : off); // dmc3.exe+2ADB29 - 48 8D 8B 00190000 - LEA RCX,[RBX+00001900]
	// 	// Trash<uint32>((appBaseAddr + 0x2C333B + 3), (enable) ? newOff : off); // dmc3.exe+2C333B - 81 FB 00190000 - CMP EBX,00001900
	// 	// Trash<uint32>((appBaseAddr + 0x333292 + 3), (enable) ? newOff : off); // dmc3.exe+333292 - B9 00190000 - MOV ECX,00001900
	// 	// Trash<uint32>((appBaseAddr + 0x387553 + 3), (enable) ? newOff : off); // dmc3.exe+387553 - 80 A4 00 00001900 00 - AND BYTE PTR [RAX+RAX+00190000],00
	// 	// Trash<uint32>((appBaseAddr + 0x3CEE33 + 3), (enable) ? newOff : off); // dmc3.exe+3CEE33 - 80 94 01 00001900 00 - ADC BYTE PTR [RCX+RAX+00190000],00
	// 	// Trash<uint32>((appBaseAddr + 0x3DF3AF + 3), (enable) ? newOff : off); // dmc3.exe+3DF3AF - 80 AC 01 00001900 00 - SUB BYTE PTR [RCX+RAX+00190000],00
	// 	// Trash<uint32>((appBaseAddr + 0x3EBD77 + 3), (enable) ? newOff : off); // dmc3.exe+3EBD77 - 80 A4 00 00001900 00 - AND BYTE PTR [RAX+RAX+00190000],00
	// 	// Trash<uint32>((appBaseAddr + 0x441C37 + 3), (enable) ? newOff : off); // dmc3.exe+441C37 - 80 BC 00 00001900 00 - CMP BYTE PTR [RAX+RAX+00190000],00
	// 	// Trash<uint32>((appBaseAddr + 0x441CF7 + 3), (enable) ? newOff : off); // dmc3.exe+441CF7 - 80 94 01 00001900 00 - ADC BYTE PTR [RCX+RAX+00190000],00
	// 	// Trash<uint32>((appBaseAddr + 0x441D17 + 3), (enable) ? newOff : off); // dmc3.exe+441D17 - 80 AC 01 00001900 00 - SUB BYTE PTR [RCX+RAX+00190000],00
	// 	// Trash<uint32>((appBaseAddr + 0x441E17 + 3), (enable) ? newOff : off); // dmc3.exe+441E17 - 80 9C 02 00001900 00 - SBB BYTE PTR [RDX+RAX+00190000],00
	// 	// Trash<uint32>((appBaseAddr + 0x441F37 + 3), (enable) ? newOff : off); // dmc3.exe+441F37 - 80 A4 03 00001900 00 - AND BYTE PTR [RBX+RAX+00190000],00
	// 	// Trash<uint32>((appBaseAddr + 0x441F57 + 3), (enable) ? newOff : off); // dmc3.exe+441F57 - 80 BC 03 00001900 00 - CMP BYTE PTR [RBX+RAX+00190000],00
	// 	// Trash<uint32>((appBaseAddr + 0x442077 + 3), (enable) ? newOff : off); // dmc3.exe+442077 - 80 84 04 00001900 00 - ADD BYTE PTR [RSP+RAX+00190000],00
	// 	// Trash<uint32>((appBaseAddr + 0x442097 + 3), (enable) ? newOff : off); // dmc3.exe+442097 - 80 8C 04 00001900 00 - OR BYTE PTR [RSP+RAX+00190000],00
	// 	// Trash<uint32>((appBaseAddr + 0x447B58 + 3), (enable) ? newOff : off); // dmc3.exe+447B58 - A0 01000019000080A0 - MOV AL,[A080000019000001]
	// 	// Trash<uint32>((appBaseAddr + 0x447B67 + 3), (enable) ? newOff : off); // dmc3.exe+447B67 - 00 AC 01 00001900 - ADD [RCX+RAX+00190000],CH
	// 	// Trash<uint32>((appBaseAddr + 0x447D8F + 3), (enable) ? newOff : off); // dmc3.exe+447D8F - 80 94 03 00001900 00 - ADC BYTE PTR [RBX+RAX+00190000],00
	// 	// Trash<uint32>((appBaseAddr + 0x447DAF + 3), (enable) ? newOff : off); // dmc3.exe+447DAF - 80 BC 03 00001900 00 - CMP BYTE PTR [RBX+RAX+00190000],00
	// 	// Trash<uint32>((appBaseAddr + 0x447E8F + 3), (enable) ? newOff : off); // dmc3.exe+447E8F - 80 94 04 00001900 00 - ADC BYTE PTR [RSP+RAX+00190000],00
	// 	// Trash<uint32>((appBaseAddr + 0x447EAF + 3), (enable) ? newOff : off); // dmc3.exe+447EAF - 80 9C 04 00001900 00 - SBB BYTE PTR [RSP+RAX+00190000],00
	// 	// Trash<uint32>((appBaseAddr + 0x447EEF + 3), (enable) ? newOff : off); // dmc3.exe+447EEF - 80 BC 04 00001900 00 - CMP BYTE PTR [RSP+RAX+00190000],00
	// 	// Trash<uint32>((appBaseAddr + 0x533AA9 + 3), (enable) ? newOff : off); // dmc3.exe+533AA9 - A1 340019000000F5A1 - MOV EAX,[A1F5000000190034]
	// 	// Trash<uint32>((appBaseAddr + 0x58337C + 3), (enable) ? newOff : off); // dmc3.exe+58337C - 03 05 00001900 - ADD EAX,[00712782]
	// }
	// // 0x1908
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][17]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][17]);
		//static_assert(off == 0x1908);
	// 	// Write<uint32>((appBaseAddr + 0xCBEA4 + 3), (enable) ? newOff : off); // dmc3.exe+CBEA4 - 48 8D 8E 08190000 - LEA RCX,[RSI+00001908]
	// 	// Write<uint32>((appBaseAddr + 0xCBFA7 + 3), (enable) ? newOff : off); // dmc3.exe+CBFA7 - 48 81 C1 08190000 - ADD RCX,00001908
	// 	// Write<uint32>((appBaseAddr + 0xD2185 + 3), (enable) ? newOff : off); // dmc3.exe+D2185 - 49 8B 85 08190000 - MOV RAX,[R13+00001908]
	// 	// Write<uint32>((appBaseAddr + 0xD21AD + 3), (enable) ? newOff : off); // dmc3.exe+D21AD - 49 8D 8D 08190000 - LEA RCX,[R13+00001908]
	// 	// Write<uint32>((appBaseAddr + 0xD2243 + 3), (enable) ? newOff : off); // dmc3.exe+D2243 - 4D 8D 85 08190000 - LEA R8,[R13+00001908]
	// 	// Write<uint32>((appBaseAddr + 0xD2DFF + 3), (enable) ? newOff : off); // dmc3.exe+D2DFF - 48 8D 8F 08190000 - LEA RCX,[RDI+00001908]
	// 	// Write<uint32>((appBaseAddr + 0x259886 + 3), (enable) ? newOff : off); // dmc3.exe+259886 - 48 89 98 08190000 - MOV [RAX+00001908],RBX
	// 	// Trash<uint32>((appBaseAddr + 0x293150 + 3), (enable) ? newOff : off); // dmc3.exe+293150 - 80 BB 08190000 01 - CMP BYTE PTR [RBX+00001908],01
	// 	// Trash<uint32>((appBaseAddr + 0x29318E + 3), (enable) ? newOff : off); // dmc3.exe+29318E - 80 BB 08190000 01 - CMP BYTE PTR [RBX+00001908],01
	// 	// Trash<uint32>((appBaseAddr + 0x293222 + 3), (enable) ? newOff : off); // dmc3.exe+293222 - 80 BB 08190000 01 - CMP BYTE PTR [RBX+00001908],01
	// 	// Trash<uint32>((appBaseAddr + 0x293323 + 3), (enable) ? newOff : off); // dmc3.exe+293323 - 80 BB 08190000 00 - CMP BYTE PTR [RBX+00001908],00
	// 	// Write<uint32>((appBaseAddr + 0x348029 + 3), (enable) ? newOff : off); // dmc3.exe+348029 - 48 81 C1 08190000 - ADD RCX,00001908
	// }
	// // 0x1910
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][18]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][18]);
		//static_assert(off == 0x1910);
	// 	// Write<uint32>((appBaseAddr + 0x259891 + 3), (enable) ? newOff : off); // dmc3.exe+259891 - 48 89 98 10190000 - MOV [RAX+00001910],RBX
	// 	// Trash<uint32>((appBaseAddr + 0x25A606 + 3), (enable) ? newOff : off); // dmc3.exe+25A606 - 0F29 87 10190000 - MOVAPS [RDI+00001910],XMM0
	// 	// Trash<uint32>((appBaseAddr + 0x29196B + 3), (enable) ? newOff : off); // dmc3.exe+29196B - C7 83 10190000 FFFFFFFF - MOV [RBX+00001910],FFFFFFFF
	// 	// Write<uint32>((appBaseAddr + 0x2934C3 + 3), (enable) ? newOff : off); // dmc3.exe+2934C3 - 48 8D 81 10190000 - LEA RAX,[RCX+00001910]
	// 	// Write<uint32>((appBaseAddr + 0x293513 + 3), (enable) ? newOff : off); // dmc3.exe+293513 - 48 8D 81 10190000 - LEA RAX,[RCX+00001910]
	// 	// Write<uint32>((appBaseAddr + 0x29357D + 3), (enable) ? newOff : off); // dmc3.exe+29357D - 48 8D 99 10190000 - LEA RBX,[RCX+00001910]
	// 	// Write<uint32>((appBaseAddr + 0x293663 + 3), (enable) ? newOff : off); // dmc3.exe+293663 - 48 8D 81 10190000 - LEA RAX,[RCX+00001910]
	// 	// Write<uint32>((appBaseAddr + 0x293703 + 3), (enable) ? newOff : off); // dmc3.exe+293703 - 48 8D 81 10190000 - LEA RAX,[RCX+00001910]
	// }
	// // 0x1918
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][19]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][19]);
		//static_assert(off == 0x1918);
	// 	// Write<uint32>((appBaseAddr + 0xBAA3F + 3), (enable) ? newOff : off); // dmc3.exe+BAA3F - 48 8B 96 18190000 - MOV RDX,[RSI+00001918]
	// 	// Write<uint32>((appBaseAddr + 0xBAB46 + 3), (enable) ? newOff : off); // dmc3.exe+BAB46 - 48 8B 96 18190000 - MOV RDX,[RSI+00001918]
	// 	// Write<uint32>((appBaseAddr + 0x25989C + 3), (enable) ? newOff : off); // dmc3.exe+25989C - 48 89 98 18190000 - MOV [RAX+00001918],RBX
	// }
	// // 0x1920
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][20]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][20]);
		//static_assert(off == 0x1920);
	// 	// Write<uint32>((appBaseAddr + 0xBAA59 + 3), (enable) ? newOff : off); // dmc3.exe+BAA59 - 48 8B 96 20190000 - MOV RDX,[RSI+00001920]
	// 	// Write<uint32>((appBaseAddr + 0xBAB60 + 3), (enable) ? newOff : off); // dmc3.exe+BAB60 - 48 8B 96 20190000 - MOV RDX,[RSI+00001920]
	// 	// Trash<uint32>((appBaseAddr + 0xD1155 + 3), (enable) ? newOff : off); // dmc3.exe+D1155 - 83 BB 20190000 00 - CMP DWORD PTR [RBX+00001920],00
	// 	// Trash<uint32>((appBaseAddr + 0xD180E + 3), (enable) ? newOff : off); // dmc3.exe+D180E - C7 83 20190000 02000000 - MOV [RBX+00001920],00000002
	// 	// Write<uint32>((appBaseAddr + 0x2598A7 + 3), (enable) ? newOff : off); // dmc3.exe+2598A7 - 48 89 98 20190000 - MOV [RAX+00001920],RBX
	// 	// Trash<uint32>((appBaseAddr + 0x25A60D + 3), (enable) ? newOff : off); // dmc3.exe+25A60D - 0F29 8F 20190000 - MOVAPS [RDI+00001920],XMM1
	// 	// Trash<uint32>((appBaseAddr + 0x291975 + 3), (enable) ? newOff : off); // dmc3.exe+291975 - 66 89 83 20190000 - MOV [RBX+00001920],AX
	// 	// Trash<uint32>((appBaseAddr + 0x542660 + 3), (enable) ? newOff : off); // dmc3.exe+542660 - A0 0000001920080012 - MOV AL,[1200082019000000]
	// 	// Trash<uint32>((appBaseAddr + 0x54CC20 + 3), (enable) ? newOff : off); // dmc3.exe+54CC20 - A0 0000001920042512 - MOV AL,[1225042019000000]
	// }
	// // 0x1928
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][21]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][21]);
		//static_assert(off == 0x1928);
	// 	// Write<uint32>((appBaseAddr + 0x2598B2 + 3), (enable) ? newOff : off); // dmc3.exe+2598B2 - 48 89 98 28190000 - MOV [RAX+00001928],RBX
	// 	// Trash<uint32>((appBaseAddr + 0x52E334 + 3), (enable) ? newOff : off); // dmc3.exe+52E334 - A0 010000192808001A - MOV AL,[1A00082819000001]
	// }
	// // 0x1930
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][22]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][22]);
		//static_assert(off == 0x1930);
	// 	// Trash<uint32>((appBaseAddr + 0xD281F + 3), (enable) ? newOff : off); // dmc3.exe+D281F - C7 81 30190000 0000A040 - MOV [RCX+00001930],40A00000
	// 	// Trash<uint32>((appBaseAddr + 0xF8A89 + 3), (enable) ? newOff : off); // dmc3.exe+F8A89 - C6 83 30190000 01 - MOV BYTE PTR [RBX+00001930],01
	// 	// Trash<uint32>((appBaseAddr + 0xFE270 + 3), (enable) ? newOff : off); // dmc3.exe+FE270 - C6 86 30190000 00 - MOV BYTE PTR [RSI+00001930],00
	// 	// Trash<uint32>((appBaseAddr + 0xFE2C0 + 3), (enable) ? newOff : off); // dmc3.exe+FE2C0 - C6 81 30190000 01 - MOV BYTE PTR [RCX+00001930],01
	// 	// Trash<uint32>((appBaseAddr + 0xFE3C0 + 3), (enable) ? newOff : off); // dmc3.exe+FE3C0 - C6 81 30190000 01 - MOV BYTE PTR [RCX+00001930],01
	// 	// Write<uint32>((appBaseAddr + 0x2598BD + 3), (enable) ? newOff : off); // dmc3.exe+2598BD - 48 89 98 30190000 - MOV [RAX+00001930],RBX
	// 	// Write<uint32>((appBaseAddr + 0x25A58A + 3), (enable) ? newOff : off); // dmc3.exe+25A58A - 48 8D 8F 30190000 - LEA RCX,[RDI+00001930]
	// 	// Write<uint32>((appBaseAddr + 0x25A5A7 + 3), (enable) ? newOff : off); // dmc3.exe+25A5A7 - 48 8D 8F 30190000 - LEA RCX,[RDI+00001930]
	// 	// Write<uint32>((appBaseAddr + 0x25A5B3 + 3), (enable) ? newOff : off); // dmc3.exe+25A5B3 - 48 8D 8F 30190000 - LEA RCX,[RDI+00001930]
	// 	// Write<uint32>((appBaseAddr + 0x25A5C6 + 3), (enable) ? newOff : off); // dmc3.exe+25A5C6 - 48 8D 8F 30190000 - LEA RCX,[RDI+00001930]
	// }
	// // 0x1938
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][23]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][23]);
		//static_assert(off == 0x1938);
	// 	// Write<uint32>((appBaseAddr + 0xD2833 + 3), (enable) ? newOff : off); // dmc3.exe+D2833 - 48 C7 81 38190000 0000A040 - MOV QWORD PTR [RCX+00001938],40A00000
	// 	// Trash<uint32>((appBaseAddr + 0xF8A9A + 3), (enable) ? newOff : off); // dmc3.exe+F8A9A - C7 83 38190000 0000A042 - MOV [RBX+00001938],42A00000
	// 	// Trash<uint32>((appBaseAddr + 0xFE2D1 + 3), (enable) ? newOff : off); // dmc3.exe+FE2D1 - C7 81 38190000 0000A041 - MOV [RCX+00001938],41A00000
	// 	// Trash<uint32>((appBaseAddr + 0xFE3D1 + 3), (enable) ? newOff : off); // dmc3.exe+FE3D1 - C7 81 38190000 00002042 - MOV [RCX+00001938],42200000
	// 	// Write<uint32>((appBaseAddr + 0x2598C8 + 3), (enable) ? newOff : off); // dmc3.exe+2598C8 - 48 89 98 38190000 - MOV [RAX+00001938],RBX
	// 	// Trash<uint32>((appBaseAddr + 0x29198D + 3), (enable) ? newOff : off); // dmc3.exe+29198D - C7 83 38190000 FFFFFFFF - MOV [RBX+00001938],FFFFFFFF
	// }


	// // 0x1948
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[1][1]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[1][1]);
		//static_assert(off == 0x1948);
	// 	// Trash<uint32>((appBaseAddr + 0xD182C + 3), (enable) ? newOff : off); // dmc3.exe+D182C - C7 83 48190000 00009644 - MOV [RBX+00001948],44960000
	// 	// Trash<uint32>((appBaseAddr + 0xD1843 + 3), (enable) ? newOff : off); // dmc3.exe+D1843 - 89 83 48190000 - MOV [RBX+00001948],EAX
	// 	// Trash<uint32>((appBaseAddr + 0x259811 + 3), (enable) ? newOff : off); // dmc3.exe+259811 - 89 98 48190000 - MOV [RAX+00001948],EBX
	// 	// Trash<uint32>((appBaseAddr + 0x259D26 + 3), (enable) ? newOff : off); // dmc3.exe+259D26 - 39 9E 48190000 - CMP [RSI+00001948],EBX
	// 	// Trash<uint32>((appBaseAddr + 0x259D53 + 3), (enable) ? newOff : off); // dmc3.exe+259D53 - 3B 9E 48190000 - CMP EBX,[RSI+00001948]
	// 	// Trash<uint32>((appBaseAddr + 0x25A7E1 + 3), (enable) ? newOff : off); // dmc3.exe+25A7E1 - 48 63 8F 48190000 - MOVSXD RCX,DWORD PTR [RDI+00001948]
	// 	// Trash<uint32>((appBaseAddr + 0x25A7F0 + 3), (enable) ? newOff : off); // dmc3.exe+25A7F0 - 48 63 87 48190000 - MOVSXD RAX,DWORD PTR [RDI+00001948]
	// 	// Trash<uint32>((appBaseAddr + 0x25A819 + 3), (enable) ? newOff : off); // dmc3.exe+25A819 - 48 63 87 48190000 - MOVSXD RAX,DWORD PTR [RDI+00001948]
	// 	// Trash<uint32>((appBaseAddr + 0x25A82C + 3), (enable) ? newOff : off); // dmc3.exe+25A82C - FF 87 48190000 - INC [RDI+00001948]
	// 	// Trash<uint32>((appBaseAddr + 0x25AABC + 3), (enable) ? newOff : off); // dmc3.exe+25AABC - 39 97 48190000 - CMP [RDI+00001948],EDX
	// 	// Trash<uint32>((appBaseAddr + 0x25AAF0 + 3), (enable) ? newOff : off); // dmc3.exe+25AAF0 - 3B 97 48190000 - CMP EDX,[RDI+00001948]
	// 	// Trash<uint32>((appBaseAddr + 0x25AD45 + 3), (enable) ? newOff : off); // dmc3.exe+25AD45 - 39 BB 48190000 - CMP [RBX+00001948],EDI
	// 	// Trash<uint32>((appBaseAddr + 0x25AD73 + 3), (enable) ? newOff : off); // dmc3.exe+25AD73 - 3B BB 48190000 - CMP EDI,[RBX+00001948]
	// 	// Trash<uint32>((appBaseAddr + 0x25AD85 + 3), (enable) ? newOff : off); // dmc3.exe+25AD85 - C7 83 48190000 00000000 - MOV [RBX+00001948],00000000
	// 	// Trash<uint32>((appBaseAddr + 0x25C192 + 3), (enable) ? newOff : off); // dmc3.exe+25C192 - 89 98 48190000 - MOV [RAX+00001948],EBX
	// 	// Trash<uint32>((appBaseAddr + 0x25C5DC + 3), (enable) ? newOff : off); // dmc3.exe+25C5DC - 39 9F 48190000 - CMP [RDI+00001948],EBX
	// 	// Trash<uint32>((appBaseAddr + 0x25C606 + 3), (enable) ? newOff : off); // dmc3.exe+25C606 - 3B 9F 48190000 - CMP EBX,[RDI+00001948]
	// 	// Trash<uint32>((appBaseAddr + 0x25D0BB + 3), (enable) ? newOff : off); // dmc3.exe+25D0BB - 48 63 8F 48190000 - MOVSXD RCX,DWORD PTR [RDI+00001948]
	// 	// Trash<uint32>((appBaseAddr + 0x25D0CA + 3), (enable) ? newOff : off); // dmc3.exe+25D0CA - 48 63 87 48190000 - MOVSXD RAX,DWORD PTR [RDI+00001948]
	// 	// Trash<uint32>((appBaseAddr + 0x25D0F3 + 3), (enable) ? newOff : off); // dmc3.exe+25D0F3 - 48 63 87 48190000 - MOVSXD RAX,DWORD PTR [RDI+00001948]
	// 	// Trash<uint32>((appBaseAddr + 0x25D106 + 3), (enable) ? newOff : off); // dmc3.exe+25D106 - FF 87 48190000 - INC [RDI+00001948]
	// 	// Trash<uint32>((appBaseAddr + 0x25D2DA + 3), (enable) ? newOff : off); // dmc3.exe+25D2DA - 39 97 48190000 - CMP [RDI+00001948],EDX
	// 	// Trash<uint32>((appBaseAddr + 0x25D310 + 3), (enable) ? newOff : off); // dmc3.exe+25D310 - 3B 97 48190000 - CMP EDX,[RDI+00001948]
	// 	// Trash<uint32>((appBaseAddr + 0x25D554 + 3), (enable) ? newOff : off); // dmc3.exe+25D554 - 39 B3 48190000 - CMP [RBX+00001948],ESI
	// 	// Trash<uint32>((appBaseAddr + 0x25D576 + 3), (enable) ? newOff : off); // dmc3.exe+25D576 - 3B B3 48190000 - CMP ESI,[RBX+00001948]
	// 	// Trash<uint32>((appBaseAddr + 0x25D59B + 3), (enable) ? newOff : off); // dmc3.exe+25D59B - 39 B3 48190000 - CMP [RBX+00001948],ESI
	// 	// Trash<uint32>((appBaseAddr + 0x25D5C3 + 3), (enable) ? newOff : off); // dmc3.exe+25D5C3 - 3B B3 48190000 - CMP ESI,[RBX+00001948]
	// 	// Trash<uint32>((appBaseAddr + 0x25D5CB + 3), (enable) ? newOff : off); // dmc3.exe+25D5CB - C7 83 48190000 00000000 - MOV [RBX+00001948],00000000
	// 	// Trash<uint32>((appBaseAddr + 0x291997 + 3), (enable) ? newOff : off); // dmc3.exe+291997 - 66 89 83 48190000 - MOV [RBX+00001948],AX
	// }
	// // 0x1950
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[1][2]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[1][2]);
		//static_assert(off == 0x1950);
	// 	// Trash<uint32>((appBaseAddr + 0xD1849 + 3), (enable) ? newOff : off); // dmc3.exe+D1849 - 89 83 50190000 - MOV [RBX+00001950],EAX
	// 	// Write<uint32>((appBaseAddr + 0x25A80B + 3), (enable) ? newOff : off); // dmc3.exe+25A80B - 48 8D 87 50190000 - LEA RAX,[RDI+00001950]
	// 	// Write<uint32>((appBaseAddr + 0x25AAFF + 3), (enable) ? newOff : off); // dmc3.exe+25AAFF - 48 8D 8F 50190000 - LEA RCX,[RDI+00001950]
	// 	// Write<uint32>((appBaseAddr + 0x25AB58 + 3), (enable) ? newOff : off); // dmc3.exe+25AB58 - 48 8D 97 50190000 - LEA RDX,[RDI+00001950]
	// 	// Write<uint32>((appBaseAddr + 0x25AB64 + 3), (enable) ? newOff : off); // dmc3.exe+25AB64 - 48 8D 8F 50190000 - LEA RCX,[RDI+00001950]
	// 	// Write<uint32>((appBaseAddr + 0x25B144 + 3), (enable) ? newOff : off); // dmc3.exe+25B144 - 48 8D 8B 50190000 - LEA RCX,[RBX+00001950]
	// }
	// // 0x1958
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[1][3]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[1][3]);
		//static_assert(off == 0x1958);
	// 	// Trash<uint32>((appBaseAddr + 0xD2FE7 + 3), (enable) ? newOff : off); // dmc3.exe+D2FE7 - F3 0F10 91 58190000 - MOVSS XMM2,[RCX+00001958]
	// 	// Trash<uint32>((appBaseAddr + 0xD300E + 3), (enable) ? newOff : off); // dmc3.exe+D300E - F3 0F11 91 58190000 - MOVSS [RCX+00001958],XMM2
	// 	// Trash<uint32>((appBaseAddr + 0xD3023 + 3), (enable) ? newOff : off); // dmc3.exe+D3023 - 89 81 58190000 - MOV [RCX+00001958],EAX
	// }
	// // 0x1960
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[1][4]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[1][4]);
		//static_assert(off == 0x1960);
	// 	// Trash<uint32>((appBaseAddr + 0xD115E + 3), (enable) ? newOff : off); // dmc3.exe+D115E - 8B 8B 60190000 - MOV ECX,[RBX+00001960]
	// 	// Trash<uint32>((appBaseAddr + 0xD1823 + 3), (enable) ? newOff : off); // dmc3.exe+D1823 - 83 BB 60190000 00 - CMP DWORD PTR [RBX+00001960],00
	// 	// Trash<uint32>((appBaseAddr + 0xD1838 + 3), (enable) ? newOff : off); // dmc3.exe+D1838 - 83 BB 60190000 01 - CMP DWORD PTR [RBX+00001960],01
	// 	// Trash<uint32>((appBaseAddr + 0xD2F98 + 3), (enable) ? newOff : off); // dmc3.exe+D2F98 - F3 0F58 89 60190000 - ADDSS XMM1,DWORD PTR [RCX+00001960]
	// 	// Trash<uint32>((appBaseAddr + 0xD2FAB + 3), (enable) ? newOff : off); // dmc3.exe+D2FAB - F3 0F11 89 60190000 - MOVSS [RCX+00001960],XMM1
	// 	// Trash<uint32>((appBaseAddr + 0xE9A46 + 3), (enable) ? newOff : off); // dmc3.exe+E9A46 - 0F28 81 60190000 - MOVAPS XMM0,[RCX+00001960]
	// 	// Write<uint32>((appBaseAddr + 0x157B94 + 3), (enable) ? newOff : off); // dmc3.exe+157B94 - 49 8B 86 60190000 - MOV RAX,[R14+00001960]
	// 	// Write<uint32>((appBaseAddr + 0x157B9B + 3), (enable) ? newOff : off); // dmc3.exe+157B9B - 49 8D 8E 60190000 - LEA RCX,[R14+00001960]
	// 	// Write<uint32>((appBaseAddr + 0x157BAF + 3), (enable) ? newOff : off); // dmc3.exe+157BAF - 49 8B 86 60190000 - MOV RAX,[R14+00001960]
	// 	// Write<uint32>((appBaseAddr + 0x157BBF + 3), (enable) ? newOff : off); // dmc3.exe+157BBF - 49 8D 8E 60190000 - LEA RCX,[R14+00001960]
	// 	// Trash<uint32>((appBaseAddr + 0x2919AF + 3), (enable) ? newOff : off); // dmc3.exe+2919AF - C7 83 60190000 FFFFFFFF - MOV [RBX+00001960],FFFFFFFF
	// 	// Trash<uint32>((appBaseAddr + 0x5369CF + 3), (enable) ? newOff : off); // dmc3.exe+5369CF - FF B7 60190000 - PUSH [RDI+00001960]
	// }
	// // 0x1968
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[1][5]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[1][5]);
		// static_assert(off == 0x1968);
	// 	// Write<uint32>((appBaseAddr + 0xF9294 + 3), (enable) ? newOff : off); // dmc3.exe+F9294 - 48 89 83 68190000 - MOV [RBX+00001968],RAX
	// }
	// // 0x1970
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[1][6]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[1][6]);
		// static_assert(off == 0x1970);
	// 	// Trash<uint32>((appBaseAddr + 0x2919B9 + 3), (enable) ? newOff : off); // dmc3.exe+2919B9 - 66 89 83 70190000 - MOV [RBX+00001970],AX
	// }
	// // 0x1978
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[1][7]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[1][7]);
		// static_assert(off == 0x1978);
	// 	// Write<uint32>((appBaseAddr + 0xF92CA + 3), (enable) ? newOff : off); // dmc3.exe+F92CA - 48 C7 83 78190000 01000000 - MOV QWORD PTR [RBX+00001978],00000001
	// 	// Trash<uint32>((appBaseAddr + 0x5CE2DE + 3), (enable) ? newOff : off); // dmc3.exe+5CE2DE - 0D 00001978 - OR EAX,78190000
	// }
	// // 0x1980
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[1][8]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[1][8]);
		// static_assert(off == 0x1980);
	// 	// Write<uint32>((appBaseAddr + 0xF92B6 + 3), (enable) ? newOff : off); // dmc3.exe+F92B6 - 48 89 8B 80190000 - MOV [RBX+00001980],RCX
	// 	// Save<uint32>((appBaseAddr + 0x298014 + 3), (enable) ? newOff : off); // dmc3.exe+298014 - 48 8D 8D 80190000 - LEA RCX,[RBP+00001980]
	// 	// Save<uint32>((appBaseAddr + 0x298028 + 3), (enable) ? newOff : off); // dmc3.exe+298028 - 48 8D 8D 80190000 - LEA RCX,[RBP+00001980]
	// 	// Save<uint32>((appBaseAddr + 0x29827E + 3), (enable) ? newOff : off); // dmc3.exe+29827E - 48 8D 8D 80190000 - LEA RCX,[RBP+00001980]
	// 	// Save<uint32>((appBaseAddr + 0x298292 + 3), (enable) ? newOff : off); // dmc3.exe+298292 - 48 8D 8D 80190000 - LEA RCX,[RBP+00001980]
	// 	// Write<uint32>((appBaseAddr + 0x298D20 + 3), (enable) ? newOff : off); // dmc3.exe+298D20 - 48 8D 8F 80190000 - LEA RCX,[RDI+00001980]
	// 	// Save<uint32>((appBaseAddr + 0x298E80 + 3), (enable) ? newOff : off); // dmc3.exe+298E80 - 48 8D 8F 80190000 - LEA RCX,[RDI+00001980]
	// 	// Save<uint32>((appBaseAddr + 0x299490 + 3), (enable) ? newOff : off); // dmc3.exe+299490 - 48 8D 8B 80190000 - LEA RCX,[RBX+00001980]
	// 	// Save<uint32>((appBaseAddr + 0x299550 + 3), (enable) ? newOff : off); // dmc3.exe+299550 - 48 8D 8B 80190000 - LEA RCX,[RBX+00001980]
	// }
	// // 0x1988
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[1][9]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[1][9]);
		// static_assert(off == 0x1988);
	// 	// Trash<uint32>((appBaseAddr + 0xD0D62 + 3), (enable) ? newOff : off); // dmc3.exe+D0D62 - 48 63 83 88190000 - MOVSXD RAX,DWORD PTR [RBX+00001988]
	// 	// Trash<uint32>((appBaseAddr + 0xD1930 + 3), (enable) ? newOff : off); // dmc3.exe+D1930 - 89 91 88190000 - MOV [RCX+00001988],EDX
	// 	// Trash<uint32>((appBaseAddr + 0xF92BD + 3), (enable) ? newOff : off); // dmc3.exe+F92BD - 89 8B 88190000 - MOV [RBX+00001988],ECX
	// 	// Trash<uint32>((appBaseAddr + 0xFE802 + 3), (enable) ? newOff : off); // dmc3.exe+FE802 - 89 87 88190000 - MOV [RDI+00001988],EAX
	// 	// Trash<uint32>((appBaseAddr + 0x292329 + 3), (enable) ? newOff : off); // dmc3.exe+292329 - 44 0FBF 8B 88190000 - MOVSX R9D,WORD PTR [RBX+00001988]
	// 	// Trash<uint32>((appBaseAddr + 0x2923D4 + 3), (enable) ? newOff : off); // dmc3.exe+2923D4 - 44 0FBF 8B 88190000 - MOVSX R9D,WORD PTR [RBX+00001988]
	// 	// Trash<uint32>((appBaseAddr + 0x292432 + 3), (enable) ? newOff : off); // dmc3.exe+292432 - 66 83 83 88190000 FE - ADD WORD PTR [RBX+00001988],-02
	// 	// Trash<uint32>((appBaseAddr + 0x2924B4 + 3), (enable) ? newOff : off); // dmc3.exe+2924B4 - 66 89 83 88190000 - MOV [RBX+00001988],AX
	// 	// Trash<uint32>((appBaseAddr + 0x2929AE + 3), (enable) ? newOff : off); // dmc3.exe+2929AE - 44 0FBF 8B 88190000 - MOVSX R9D,WORD PTR [RBX+00001988]
	// 	// Trash<uint32>((appBaseAddr + 0x292A58 + 3), (enable) ? newOff : off); // dmc3.exe+292A58 - 44 0FBF 8B 88190000 - MOVSX R9D,WORD PTR [RBX+00001988]
	// 	// Trash<uint32>((appBaseAddr + 0x292AB7 + 3), (enable) ? newOff : off); // dmc3.exe+292AB7 - 66 83 83 88190000 FE - ADD WORD PTR [RBX+00001988],-02
	// 	// Trash<uint32>((appBaseAddr + 0x292B3F + 3), (enable) ? newOff : off); // dmc3.exe+292B3F - 66 89 83 88190000 - MOV [RBX+00001988],AX
	// }
	// // 0x1990
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[1][10]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[1][10]);
		// static_assert(off == 0x1990);
	// 	// Trash<uint32>((appBaseAddr + 0xFEF4A + 3), (enable) ? newOff : off); // dmc3.exe+FEF4A - 80 BF 90190000 00 - CMP BYTE PTR [RDI+00001990],00
	// 	// Trash<uint32>((appBaseAddr + 0xFF1A8 + 3), (enable) ? newOff : off); // dmc3.exe+FF1A8 - C6 87 90190000 00 - MOV BYTE PTR [RDI+00001990],00
	// 	// Write<uint32>((appBaseAddr + 0x25896F + 3), (enable) ? newOff : off); // dmc3.exe+25896F - 48 8D 8B 90190000 - LEA RCX,[RBX+00001990]
	// 	// Write<uint32>((appBaseAddr + 0x25A9DA + 3), (enable) ? newOff : off); // dmc3.exe+25A9DA - 48 8D 9F 90190000 - LEA RBX,[RDI+00001990]
	// }
	// // 0x1998
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[1][11]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[1][11]);
		// static_assert(off == 0x1998);
	// 	// Trash<uint32>((appBaseAddr + 0xFEFBD + 3), (enable) ? newOff : off); // dmc3.exe+FEFBD - F3 0F59 87 98190000 - MULSS XMM0,[RDI+00001998]
	// 	// Trash<uint32>((appBaseAddr + 0xFEFF7 + 3), (enable) ? newOff : off); // dmc3.exe+FEFF7 - F3 0F59 87 98190000 - MULSS XMM0,[RDI+00001998]
	// 	// Trash<uint32>((appBaseAddr + 0xFF031 + 3), (enable) ? newOff : off); // dmc3.exe+FF031 - F3 0F59 87 98190000 - MULSS XMM0,[RDI+00001998]
	// 	// Trash<uint32>((appBaseAddr + 0xFF06B + 3), (enable) ? newOff : off); // dmc3.exe+FF06B - F3 0F59 87 98190000 - MULSS XMM0,[RDI+00001998]
	// 	// Trash<uint32>((appBaseAddr + 0xFF0A1 + 3), (enable) ? newOff : off); // dmc3.exe+FF0A1 - F3 0F59 87 98190000 - MULSS XMM0,[RDI+00001998]
	// 	// Trash<uint32>((appBaseAddr + 0xFF0D7 + 3), (enable) ? newOff : off); // dmc3.exe+FF0D7 - F3 0F59 87 98190000 - MULSS XMM0,[RDI+00001998]
	// 	// Trash<uint32>((appBaseAddr + 0xFF10D + 3), (enable) ? newOff : off); // dmc3.exe+FF10D - F3 0F59 87 98190000 - MULSS XMM0,[RDI+00001998]
	// 	// Trash<uint32>((appBaseAddr + 0xFF147 + 3), (enable) ? newOff : off); // dmc3.exe+FF147 - F3 0F59 87 98190000 - MULSS XMM0,[RDI+00001998]
	// 	// Trash<uint32>((appBaseAddr + 0xFF182 + 3), (enable) ? newOff : off); // dmc3.exe+FF182 - F3 0F59 87 98190000 - MULSS XMM0,[RDI+00001998]
	// }
	// // 0x19A0
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[1][12]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[1][12]);
		// static_assert(off == 0x19A0);
	// 	// Trash<uint32>((appBaseAddr + 0xC8DCF + 3), (enable) ? newOff : off); // dmc3.exe+C8DCF - F3 0F11 84 9E A0190000 - MOVSS [RSI+RBX*4+000019A0],XMM0
	// 	// Trash<uint32>((appBaseAddr + 0xC8F65 + 3), (enable) ? newOff : off); // dmc3.exe+C8F65 - F3 0F11 84 9E A0190000 - MOVSS [RSI+RBX*4+000019A0],XMM0
	// 	// Trash<uint32>((appBaseAddr + 0xC8FD4 + 3), (enable) ? newOff : off); // dmc3.exe+C8FD4 - F3 0F11 84 9E A0190000 - MOVSS [RSI+RBX*4+000019A0],XMM0
	// 	// Trash<uint32>((appBaseAddr + 0xC8FFC + 3), (enable) ? newOff : off); // dmc3.exe+C8FFC - F3 0F11 84 9E A0190000 - MOVSS [RSI+RBX*4+000019A0],XMM0
	// 	// Trash<uint32>((appBaseAddr + 0xE9ABF + 3), (enable) ? newOff : off); // dmc3.exe+E9ABF - 0F28 83 A0190000 - MOVAPS XMM0,[RBX+000019A0]
	// 	// Trash<uint32>((appBaseAddr + 0xFB956 + 3), (enable) ? newOff : off); // dmc3.exe+FB956 - F3 0F10 86 A0190000 - MOVSS XMM0,[RSI+000019A0]
	// 	// Trash<uint32>((appBaseAddr + 0xFB97B + 3), (enable) ? newOff : off); // dmc3.exe+FB97B - F3 0F11 86 A0190000 - MOVSS [RSI+000019A0],XMM0
	// 	// Trash<uint32>((appBaseAddr + 0xFB992 + 3), (enable) ? newOff : off); // dmc3.exe+FB992 - 89 86 A0190000 - MOV [RSI+000019A0],EAX
	// }
	// // 0x19A8
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[1][13]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[1][13]);
		// static_assert(off == 0x19A8);
	// 	// Empty
	// }
	// // 0x19B0
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[1][14]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[1][14]);
		// static_assert(off == 0x19B0);
	// 	// Trash<uint32>((appBaseAddr + 0xD0C85 + 3), (enable) ? newOff : off); // dmc3.exe+D0C85 - 89 AF B0190000 - MOV [RDI+000019B0],EBP
	// 	// Trash<uint32>((appBaseAddr + 0xD2D6E + 3), (enable) ? newOff : off); // dmc3.exe+D2D6E - F3 0F10 87 B0190000 - MOVSS XMM0,[RDI+000019B0]
	// 	// Trash<uint32>((appBaseAddr + 0xE84FB + 3), (enable) ? newOff : off); // dmc3.exe+E84FB - 89 BE B0190000 - MOV [RSI+000019B0],EDI
	// 	// Write<uint32>((appBaseAddr + 0xE9787 + 3), (enable) ? newOff : off); // dmc3.exe+E9787 - 48 8D 97 B0190000 - LEA RDX,[RDI+000019B0]
	// 	// Write<uint32>((appBaseAddr + 0xE9DC0 + 3), (enable) ? newOff : off); // dmc3.exe+E9DC0 - 48 8D 91 B0190000 - LEA RDX,[RCX+000019B0]
	// 	// Trash<uint32>((appBaseAddr + 0xEA49E + 3), (enable) ? newOff : off); // dmc3.exe+EA49E - 44 89 AE B0190000 - MOV [RSI+000019B0],R13D
	// 	// Trash<uint32>((appBaseAddr + 0x25AA0A + 3), (enable) ? newOff : off); // dmc3.exe+25AA0A - F3 0F11 87 B0190000 - MOVSS [RDI+000019B0],XMM0
	// 	// Trash<uint32>((appBaseAddr + 0x25AA6D + 3), (enable) ? newOff : off); // dmc3.exe+25AA6D - F3 0F11 B7 B0190000 - MOVSS [RDI+000019B0],XMM6
	// }
	// // 0x19B8
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[1][15]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[1][15]);
		// static_assert(off == 0x19B8);
	// 	// Trash<uint32>((appBaseAddr + 0xD0D1D + 3), (enable) ? newOff : off); // dmc3.exe+D0D1D - F3 0F11 87 B8190000 - MOVSS [RDI+000019B8],XMM0
	// 	// Trash<uint32>((appBaseAddr + 0xD2DC6 + 3), (enable) ? newOff : off); // dmc3.exe+D2DC6 - F3 0F58 8F B8190000 - ADDSS XMM1,DWORD PTR [RDI+000019B8]
	// 	// Trash<uint32>((appBaseAddr + 0xD2DD9 + 3), (enable) ? newOff : off); // dmc3.exe+D2DD9 - F3 0F11 8F B8190000 - MOVSS [RDI+000019B8],XMM1
	// 	// Trash<uint32>((appBaseAddr + 0xD2DE3 + 3), (enable) ? newOff : off); // dmc3.exe+D2DE3 - F3 0F11 87 B8190000 - MOVSS [RDI+000019B8],XMM0
	// 	// Write<uint32>((appBaseAddr + 0xE8501 + 3), (enable) ? newOff : off); // dmc3.exe+E8501 - 48 89 BE B8190000 - MOV [RSI+000019B8],RDI
	// 	// Trash<uint32>((appBaseAddr + 0xE8AC6 + 3), (enable) ? newOff : off); // dmc3.exe+E8AC6 - 0F2F B1 B8190000 - COMISS XMM6,[RCX+000019B8]
	// 	// Trash<uint32>((appBaseAddr + 0xE8BE1 + 3), (enable) ? newOff : off); // dmc3.exe+E8BE1 - 0F2F B3 B8190000 - COMISS XMM6,[RBX+000019B8]
	// 	// Trash<uint32>((appBaseAddr + 0xE8BF8 + 3), (enable) ? newOff : off); // dmc3.exe+E8BF8 - 0F2F B3 B8190000 - COMISS XMM6,[RBX+000019B8]
	// 	// Trash<uint32>((appBaseAddr + 0xE9B20 + 3), (enable) ? newOff : off); // dmc3.exe+E9B20 - 8B 81 B8190000 - MOV EAX,[RCX+000019B8]
	// 	// Write<uint32>((appBaseAddr + 0xEA4AD + 3), (enable) ? newOff : off); // dmc3.exe+EA4AD - 48 89 B6 B8190000 - MOV [RSI+000019B8],RSI
	// }
	// // 0x19C0
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[1][16]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[1][16]);
		// static_assert(off == 0x19C0);
	// 	// Trash<uint32>((appBaseAddr + 0xD2DF2 + 3), (enable) ? newOff : off); // dmc3.exe+D2DF2 - 44 89 A7 C0190000 - MOV [RDI+000019C0],R12D
	// 	// Write<uint32>((appBaseAddr + 0xE8508 + 3), (enable) ? newOff : off); // dmc3.exe+E8508 - 48 89 BE C0190000 - MOV [RSI+000019C0],RDI
	// 	// Write<uint32>((appBaseAddr + 0xEA4B4 + 3), (enable) ? newOff : off); // dmc3.exe+EA4B4 - 48 89 BE C0190000 - MOV [RSI+000019C0],RDI
	// 	// Trash<uint32>((appBaseAddr + 0xF8479 + 3), (enable) ? newOff : off); // dmc3.exe+F8479 - BA C0190000 - MOV EDX,000019C0
	// 	// Trash<uint32>((appBaseAddr + 0xF99ED + 3), (enable) ? newOff : off); // dmc3.exe+F99ED - BA C0190000 - MOV EDX,000019C0
	// 	// Write<uint32>((appBaseAddr + 0x152D2F + 3), (enable) ? newOff : off); // dmc3.exe+152D2F - 48 8D 8E C0190000 - LEA RCX,[RSI+000019C0]
	// 	// Write<uint32>((appBaseAddr + 0x152EF4 + 3), (enable) ? newOff : off); // dmc3.exe+152EF4 - 48 8D 8E C0190000 - LEA RCX,[RSI+000019C0]
	// 	// Write<uint32>((appBaseAddr + 0x153928 + 3), (enable) ? newOff : off); // dmc3.exe+153928 - 48 8D 8B C0190000 - LEA RCX,[RBX+000019C0]
	// 	// Write<uint32>((appBaseAddr + 0x154BDE + 3), (enable) ? newOff : off); // dmc3.exe+154BDE - 48 8D 8B C0190000 - LEA RCX,[RBX+000019C0]
	// 	// Write<uint32>((appBaseAddr + 0x155387 + 3), (enable) ? newOff : off); // dmc3.exe+155387 - 48 8D 8B C0190000 - LEA RCX,[RBX+000019C0]
	// 	// Write<uint32>((appBaseAddr + 0x15745D + 3), (enable) ? newOff : off); // dmc3.exe+15745D - 48 8D 8E C0190000 - LEA RCX,[RSI+000019C0]
	// 	// Write<uint32>((appBaseAddr + 0x157834 + 3), (enable) ? newOff : off); // dmc3.exe+157834 - 48 8D 8B C0190000 - LEA RCX,[RBX+000019C0]
	// 	// Write<uint32>((appBaseAddr + 0x15816B + 3), (enable) ? newOff : off); // dmc3.exe+15816B - 49 8D 8F C0190000 - LEA RCX,[R15+000019C0]
	// 	// Write<uint32>((appBaseAddr + 0x1595B9 + 3), (enable) ? newOff : off); // dmc3.exe+1595B9 - 48 8D 8F C0190000 - LEA RCX,[RDI+000019C0]
	// 	// Write<uint32>((appBaseAddr + 0x15A1AB + 3), (enable) ? newOff : off); // dmc3.exe+15A1AB - 48 8D 8F C0190000 - LEA RCX,[RDI+000019C0]
	// 	// MissionEnd<uint32>((appBaseAddr + 0x243A9D + 3), (enable) ? newOff : off); // dmc3.exe+243A9D - 48 8D 8F C0190000 - LEA RCX,[RDI+000019C0]
	// 	// MissionEnd<uint32>((appBaseAddr + 0x243E3E + 3), (enable) ? newOff : off); // dmc3.exe+243E3E - 4C 8D B6 C0190000 - LEA R14,[RSI+000019C0]
	// 	// MissionEnd<uint32>((appBaseAddr + 0x2441AC + 3), (enable) ? newOff : off); // dmc3.exe+2441AC - 48 8D 8E C0190000 - LEA RCX,[RSI+000019C0]
	// 	// MissionEnd<uint32>((appBaseAddr + 0x24431F + 3), (enable) ? newOff : off); // dmc3.exe+24431F - 48 8D 8E C0190000 - LEA RCX,[RSI+000019C0]
	// 	// MissionEnd<uint32>((appBaseAddr + 0x24463B + 3), (enable) ? newOff : off); // dmc3.exe+24463B - 48 8D 8E C0190000 - LEA RCX,[RSI+000019C0]
	// 	// MissionEnd<uint32>((appBaseAddr + 0x244679 + 3), (enable) ? newOff : off); // dmc3.exe+244679 - 48 81 C1 C0190000 - ADD RCX,000019C0
	// 	// Write<uint32>((appBaseAddr + 0x28B1AF + 3), (enable) ? newOff : off); // dmc3.exe+28B1AF - 48 8D 9F C0190000 - LEA RBX,[RDI+000019C0]
	// 	// Write<uint32>((appBaseAddr + 0x28B3DF + 3), (enable) ? newOff : off); // dmc3.exe+28B3DF - 48 8D 8F C0190000 - LEA RCX,[RDI+000019C0]
	// 	// Write<uint32>((appBaseAddr + 0x28BACB + 3), (enable) ? newOff : off); // dmc3.exe+28BACB - 48 8D 8E C0190000 - LEA RCX,[RSI+000019C0]
	// 	// Write<uint32>((appBaseAddr + 0x28BAF9 + 3), (enable) ? newOff : off); // dmc3.exe+28BAF9 - 48 8D 8E C0190000 - LEA RCX,[RSI+000019C0]
	// 	// Write<uint32>((appBaseAddr + 0x28BC3E + 3), (enable) ? newOff : off); // dmc3.exe+28BC3E - 48 8D 8E C0190000 - LEA RCX,[RSI+000019C0]
	// 	// Write<uint32>((appBaseAddr + 0x28BC60 + 3), (enable) ? newOff : off); // dmc3.exe+28BC60 - 48 8B 86 C0190000 - MOV RAX,[RSI+000019C0]
	// 	// Write<uint32>((appBaseAddr + 0x28BC67 + 3), (enable) ? newOff : off); // dmc3.exe+28BC67 - 48 8D 8E C0190000 - LEA RCX,[RSI+000019C0]
	// 	// Write<uint32>((appBaseAddr + 0x28BCD1 + 3), (enable) ? newOff : off); // dmc3.exe+28BCD1 - 48 81 C1 C0190000 - ADD RCX,000019C0
	// 	// Write<uint32>((appBaseAddr + 0x28BCFD + 3), (enable) ? newOff : off); // dmc3.exe+28BCFD - 48 8B 86 C0190000 - MOV RAX,[RSI+000019C0]
	// 	// Write<uint32>((appBaseAddr + 0x28BD04 + 3), (enable) ? newOff : off); // dmc3.exe+28BD04 - 48 8D 8E C0190000 - LEA RCX,[RSI+000019C0]
	// 	// Write<uint32>((appBaseAddr + 0x28BE80 + 3), (enable) ? newOff : off); // dmc3.exe+28BE80 - 48 8D 8E C0190000 - LEA RCX,[RSI+000019C0]
	// 	// Write<uint32>((appBaseAddr + 0x28BFA6 + 3), (enable) ? newOff : off); // dmc3.exe+28BFA6 - 48 8D 8F C0190000 - LEA RCX,[RDI+000019C0]
	// 	// Write<uint32>((appBaseAddr + 0x28C03F + 3), (enable) ? newOff : off); // dmc3.exe+28C03F - 48 8D 8F C0190000 - LEA RCX,[RDI+000019C0]
	// 	// Write<uint32>((appBaseAddr + 0x28C0CA + 3), (enable) ? newOff : off); // dmc3.exe+28C0CA - 48 8D 8F C0190000 - LEA RCX,[RDI+000019C0]
	// 	// Trash<uint32>((appBaseAddr + 0x291A79 + 3), (enable) ? newOff : off); // dmc3.exe+291A79 - BA C0190000 - MOV EDX,000019C0
	// 	// Trash<uint32>((appBaseAddr + 0x291B41 + 3), (enable) ? newOff : off); // dmc3.exe+291B41 - BA C0190000 - MOV EDX,000019C0
	// 	// Write<uint32>((appBaseAddr + 0x349C08 + 3), (enable) ? newOff : off); // dmc3.exe+349C08 - 48 81 C1 C0190000 - ADD RCX,000019C0
	// }
	// // 0x19C8
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[1][17]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[1][17]);
		// static_assert(off == 0x19C8);
	// 	// Trash<uint32>((appBaseAddr + 0xCC606 + 3), (enable) ? newOff : off); // dmc3.exe+CC606 - C7 83 C8190000 02000000 - MOV [RBX+000019C8],00000002
	// 	// Trash<uint32>((appBaseAddr + 0xCC78A + 3), (enable) ? newOff : off); // dmc3.exe+CC78A - C7 83 C8190000 02000000 - MOV [RBX+000019C8],00000002
	// 	// Trash<uint32>((appBaseAddr + 0xCD551 + 3), (enable) ? newOff : off); // dmc3.exe+CD551 - C7 83 C8190000 03000000 - MOV [RBX+000019C8],00000003
	// 	// Trash<uint32>((appBaseAddr + 0xCD7BE + 3), (enable) ? newOff : off); // dmc3.exe+CD7BE - C7 83 C8190000 03000000 - MOV [RBX+000019C8],00000003
	// 	// Trash<uint32>((appBaseAddr + 0xCD9D4 + 3), (enable) ? newOff : off); // dmc3.exe+CD9D4 - C7 87 C8190000 03000000 - MOV [RDI+000019C8],00000003
	// 	// Trash<uint32>((appBaseAddr + 0xCF295 + 3), (enable) ? newOff : off); // dmc3.exe+CF295 - C7 83 C8190000 00000000 - MOV [RBX+000019C8],00000000
	// 	// Trash<uint32>((appBaseAddr + 0xCF46A + 3), (enable) ? newOff : off); // dmc3.exe+CF46A - 89 B3 C8190000 - MOV [RBX+000019C8],ESI
	// 	// Trash<uint32>((appBaseAddr + 0xCF76F + 3), (enable) ? newOff : off); // dmc3.exe+CF76F - 89 93 C8190000 - MOV [RBX+000019C8],EDX
	// 	// Write<uint32>((appBaseAddr + 0xE850F + 3), (enable) ? newOff : off); // dmc3.exe+E850F - 48 89 BE C8190000 - MOV [RSI+000019C8],RDI
	// 	// Write<uint32>((appBaseAddr + 0xEA497 + 3), (enable) ? newOff : off); // dmc3.exe+EA497 - 48 89 8E C8190000 - MOV [RSI+000019C8],RCX
	// }
	// // 0x19D0
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[1][18]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[1][18]);
		// static_assert(off == 0x19D0);
	// 	// Write<uint32>((appBaseAddr + 0x58DDB + 3), (enable) ? newOff : off); // dmc3.exe+58DDB - 48 8D 8F D0190000 - LEA RCX,[RDI+000019D0]
	// 	// Write<uint32>((appBaseAddr + 0xCBEFB + 3), (enable) ? newOff : off); // dmc3.exe+CBEFB - 48 89 9E D0190000 - MOV [RSI+000019D0],RBX
	// 	// Write<uint32>((appBaseAddr + 0xCCC13 + 3), (enable) ? newOff : off); // dmc3.exe+CCC13 - 48 8B 8B D0190000 - MOV RCX,[RBX+000019D0]
	// 	// Write<uint32>((appBaseAddr + 0xCCDA3 + 3), (enable) ? newOff : off); // dmc3.exe+CCDA3 - 48 8B 8B D0190000 - MOV RCX,[RBX+000019D0]
	// 	// Write<uint32>((appBaseAddr + 0xCCF74 + 3), (enable) ? newOff : off); // dmc3.exe+CCF74 - 48 8B 8B D0190000 - MOV RCX,[RBX+000019D0]
	// 	// Write<uint32>((appBaseAddr + 0xCD078 + 3), (enable) ? newOff : off); // dmc3.exe+CD078 - 48 8B 8B D0190000 - MOV RCX,[RBX+000019D0]
	// 	// Write<uint32>((appBaseAddr + 0xCD233 + 3), (enable) ? newOff : off); // dmc3.exe+CD233 - 48 8B 8B D0190000 - MOV RCX,[RBX+000019D0]
	// 	// Write<uint32>((appBaseAddr + 0xCD404 + 3), (enable) ? newOff : off); // dmc3.exe+CD404 - 48 8B 8B D0190000 - MOV RCX,[RBX+000019D0]
	// 	// Write<uint32>((appBaseAddr + 0xCD8E3 + 3), (enable) ? newOff : off); // dmc3.exe+CD8E3 - 48 8B 8F D0190000 - MOV RCX,[RDI+000019D0]
	// 	// Write<uint32>((appBaseAddr + 0xD2401 + 3), (enable) ? newOff : off); // dmc3.exe+D2401 - 48 89 83 D0190000 - MOV [RBX+000019D0],RAX
	// 	// Write<uint32>((appBaseAddr + 0xD2EFE + 3), (enable) ? newOff : off); // dmc3.exe+D2EFE - 48 8B 87 D0190000 - MOV RAX,[RDI+000019D0]
	// 	// Write<uint32>((appBaseAddr + 0xD2F19 + 3), (enable) ? newOff : off); // dmc3.exe+D2F19 - 4C 89 A7 D0190000 - MOV [RDI+000019D0],R12
	// 	// Write<uint32>((appBaseAddr + 0xD30BA + 3), (enable) ? newOff : off); // dmc3.exe+D30BA - 48 8B 8E D0190000 - MOV RCX,[RSI+000019D0]
	// 	// Write<uint32>((appBaseAddr + 0xD30CB + 3), (enable) ? newOff : off); // dmc3.exe+D30CB - 48 89 AE D0190000 - MOV [RSI+000019D0],RBP
	// 	// Write<uint32>((appBaseAddr + 0xD33C6 + 3), (enable) ? newOff : off); // dmc3.exe+D33C6 - 48 8B 81 D0190000 - MOV RAX,[RCX+000019D0]
	// 	// Write<uint32>((appBaseAddr + 0xD33E1 + 3), (enable) ? newOff : off); // dmc3.exe+D33E1 - 4C 89 89 D0190000 - MOV [RCX+000019D0],R9
	// 	// Write<uint32>((appBaseAddr + 0xE8516 + 3), (enable) ? newOff : off); // dmc3.exe+E8516 - 48 89 BE D0190000 - MOV [RSI+000019D0],RDI
	// 	// Write<uint32>((appBaseAddr + 0xEA41F + 3), (enable) ? newOff : off); // dmc3.exe+EA41F - 4C 89 AE D0190000 - MOV [RSI+000019D0],R13
	// 	// Trash<uint32>((appBaseAddr + 0xEA4BE + 3), (enable) ? newOff : off); // dmc3.exe+EA4BE - 89 86 D0190000 - MOV [RSI+000019D0],EAX
	// 	// Trash<uint32>((appBaseAddr + 0x25AEF0 + 3), (enable) ? newOff : off); // dmc3.exe+25AEF0 - 66 83 B9 D0190000 FF - CMP WORD PTR [RCX+000019D0],-01
	// 	// Trash<uint32>((appBaseAddr + 0x25AEFA + 3), (enable) ? newOff : off); // dmc3.exe+25AEFA - 66 89 91 D0190000 - MOV [RCX+000019D0],DX
	// }
	// // 0x19D8
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[1][19]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[1][19]);
		// static_assert(off == 0x19D8);
	// 	// Write<uint32>((appBaseAddr + 0xCBEE3 + 3), (enable) ? newOff : off); // dmc3.exe+CBEE3 - 48 8D BE D8190000 - LEA RDI,[RSI+000019D8]
	// 	// Write<uint32>((appBaseAddr + 0xD22FD + 3), (enable) ? newOff : off); // dmc3.exe+D22FD - 48 89 83 D8190000 - MOV [RBX+000019D8],RAX
	// 	// Write<uint32>((appBaseAddr + 0xD2328 + 3), (enable) ? newOff : off); // dmc3.exe+D2328 - 48 8B 83 D8190000 - MOV RAX,[RBX+000019D8]
	// 	// Write<uint32>((appBaseAddr + 0xD2E2B + 3), (enable) ? newOff : off); // dmc3.exe+D2E2B - 48 8D 9F D8190000 - LEA RBX,[RDI+000019D8]
	// 	// Write<uint32>((appBaseAddr + 0xD308F + 3), (enable) ? newOff : off); // dmc3.exe+D308F - 48 8D 9E D8190000 - LEA RBX,[RSI+000019D8]
	// 	// Write<uint32>((appBaseAddr + 0xD3370 + 3), (enable) ? newOff : off); // dmc3.exe+D3370 - 48 8D 91 D8190000 - LEA RDX,[RCX+000019D8]
	// 	// Trash<uint32>((appBaseAddr + 0xE851D + 3), (enable) ? newOff : off); // dmc3.exe+E851D - 89 BE D8190000 - MOV [RSI+000019D8],EDI
	// 	// Trash<uint32>((appBaseAddr + 0xEA426 + 3), (enable) ? newOff : off); // dmc3.exe+EA426 - 44 89 AE D8190000 - MOV [RSI+000019D8],R13D
	// 	// Trash<uint32>((appBaseAddr + 0xEA4D7 + 3), (enable) ? newOff : off); // dmc3.exe+EA4D7 - 89 86 D8190000 - MOV [RSI+000019D8],EAX
	// }
	// // 0x19E0
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[1][20]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[1][20]);
		// static_assert(off == 0x19E0);
	// 	// Write<uint32>((appBaseAddr + 0xCDC8E + 3), (enable) ? newOff : off); // dmc3.exe+CDC8E - 48 8B 8B E0190000 - MOV RCX,[RBX+000019E0]
	// 	// Write<uint32>((appBaseAddr + 0xCDC9F + 3), (enable) ? newOff : off); // dmc3.exe+CDC9F - 48 89 BB E0190000 - MOV [RBX+000019E0],RDI
	// 	// Write<uint32>((appBaseAddr + 0xD234A + 3), (enable) ? newOff : off); // dmc3.exe+D234A - 48 89 83 E0190000 - MOV [RBX+000019E0],RAX
	// 	// Write<uint32>((appBaseAddr + 0xD2375 + 3), (enable) ? newOff : off); // dmc3.exe+D2375 - 48 8B 83 E0190000 - MOV RAX,[RBX+000019E0]
	// 	// Write<uint32>((appBaseAddr + 0xD2C23 + 3), (enable) ? newOff : off); // dmc3.exe+D2C23 - 48 8B 87 E0190000 - MOV RAX,[RDI+000019E0]
	// 	// Write<uint32>((appBaseAddr + 0xD2C35 + 3), (enable) ? newOff : off); // dmc3.exe+D2C35 - 48 8B 87 E0190000 - MOV RAX,[RDI+000019E0]
	// 	// Write<uint32>((appBaseAddr + 0xE852D + 3), (enable) ? newOff : off); // dmc3.exe+E852D - 48 C7 86 E0190000 0050C347 - MOV QWORD PTR [RSI+000019E0],47C35000
	// 	// Write<uint32>((appBaseAddr + 0xEA437 + 3), (enable) ? newOff : off); // dmc3.exe+EA437 - 48 C7 86 E0190000 0050C347 - MOV QWORD PTR [RSI+000019E0],47C35000
	// 	// Write<uint32>((appBaseAddr + 0x122CDD + 3), (enable) ? newOff : off); // dmc3.exe+122CDD - 48 8D 8E E0190000 - LEA RCX,[RSI+000019E0]
	// 	// Write<uint32>((appBaseAddr + 0x122D01 + 3), (enable) ? newOff : off); // dmc3.exe+122D01 - 48 8D 8E E0190000 - LEA RCX,[RSI+000019E0]
	// 	// Mission19<uint32>((appBaseAddr + 0x1609FC + 3), (enable) ? newOff : off); // dmc3.exe+1609FC - 49 8B 86 E0190000 - MOV RAX,[R14+000019E0]
	// 	// Mission19<uint32>((appBaseAddr + 0x160A03 + 3), (enable) ? newOff : off); // dmc3.exe+160A03 - 49 8D 8E E0190000 - LEA RCX,[R14+000019E0]
	// 	// Mission19<uint32>((appBaseAddr + 0x160A0D + 3), (enable) ? newOff : off); // dmc3.exe+160A0D - 49 8B 9E E0190000 - MOV RBX,[R14+000019E0]
	// 	// Mission19<uint32>((appBaseAddr + 0x160A23 + 3), (enable) ? newOff : off); // dmc3.exe+160A23 - 49 8D 8E E0190000 - LEA RCX,[R14+000019E0]
	// }
	// // 0x19E8
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[1][21]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[1][21]);
		// static_assert(off == 0x19E8);
	// 	// Write<uint32>((appBaseAddr + 0xD2397 + 3), (enable) ? newOff : off); // dmc3.exe+D2397 - 48 89 83 E8190000 - MOV [RBX+000019E8],RAX
	// 	// Write<uint32>((appBaseAddr + 0xD23C2 + 3), (enable) ? newOff : off); // dmc3.exe+D23C2 - 48 8B 83 E8190000 - MOV RAX,[RBX+000019E8]
	// 	// Trash<uint32>((appBaseAddr + 0xE8538 + 3), (enable) ? newOff : off); // dmc3.exe+E8538 - 89 BE E8190000 - MOV [RSI+000019E8],EDI
	// 	// Trash<uint32>((appBaseAddr + 0xEA442 + 3), (enable) ? newOff : off); // dmc3.exe+EA442 - 44 89 AE E8190000 - MOV [RSI+000019E8],R13D
	// }
	// // 0x19F0
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[1][22]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[1][22]);
		// static_assert(off == 0x19F0);
	// 	// Trash<uint32>((appBaseAddr + 0xE854F + 3), (enable) ? newOff : off); // dmc3.exe+E854F - 66 89 86 F0190000 - MOV [RSI+000019F0],AX
	// 	// Trash<uint32>((appBaseAddr + 0xEA458 + 3), (enable) ? newOff : off); // dmc3.exe+EA458 - 66 89 86 F0190000 - MOV [RSI+000019F0],AX
	// }
	// // 0x19F8
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[1][23]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[1][23]);
		// static_assert(off == 0x19F8);
	// 	// Trash<uint32>((appBaseAddr + 0xE856B + 3), (enable) ? newOff : off); // dmc3.exe+E856B - 66 89 86 F8190000 - MOV [RSI+000019F8],AX
	// 	// Trash<uint32>((appBaseAddr + 0xEA474 + 3), (enable) ? newOff : off); // dmc3.exe+EA474 - 66 89 86 F8190000 - MOV [RSI+000019F8],AX
	// 	// Write<uint32>((appBaseAddr + 0x17892D + 3), (enable) ? newOff : off); // dmc3.exe+17892D - 4C 8D 87 F8190000 - LEA R8,[RDI+000019F8]
	// 	// Write<uint32>((appBaseAddr + 0x17893C + 3), (enable) ? newOff : off); // dmc3.exe+17893C - 48 8D 97 F8190000 - LEA RDX,[RDI+000019F8]
	// }

	// // 0x1A08
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[2][1]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[2][1]);
		// static_assert(off == 0x1A08);
	// 	// Write<uint32>((appBaseAddr + 0x1788B2 + 3), (enable) ? newOff : off); // dmc3.exe+1788B2 - 4C 8B 87 081A0000 - MOV R8,[RDI+00001A08]
	// }
	// // 0x1A10
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[2][2]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[2][2]);
		// static_assert(off == 0x1A10);
	// 	// Write<uint32>((appBaseAddr + 0xCE7BF + 3), (enable) ? newOff : off); // dmc3.exe+CE7BF - 48 89 83 101A0000 - MOV [RBX+00001A10],RAX
	// 	// Write<uint32>((appBaseAddr + 0xEA3AC + 3), (enable) ? newOff : off); // dmc3.exe+EA3AC - 48 8D BE 101A0000 - LEA RDI,[RSI+00001A10]
	// }
	// // 0x1A18
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[2][3]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[2][3]);
		// static_assert(off == 0x1A18);
	// 	// Write<uint32>((appBaseAddr + 0xCF36D + 3), (enable) ? newOff : off); // dmc3.exe+CF36D - 48 89 83 181A0000 - MOV [RBX+00001A18],RAX
	// 	// Trash<uint32>((appBaseAddr + 0xE881B + 3), (enable) ? newOff : off); // dmc3.exe+E881B - 0F2F 81 181A0000 - COMISS XMM0,[RCX+00001A18]
	// 	// Trash<uint32>((appBaseAddr + 0xE9298 + 3), (enable) ? newOff : off); // dmc3.exe+E9298 - 44 0F2F 87 181A0000 - COMISS XMM8,[RDI+00001A18]
	// 	// Trash<uint32>((appBaseAddr + 0xE92BF + 3), (enable) ? newOff : off); // dmc3.exe+E92BF - 44 0F2F 87 181A0000 - COMISS XMM8,[RDI+00001A18]
	// 	// Trash<uint32>((appBaseAddr + 0xE946B + 3), (enable) ? newOff : off); // dmc3.exe+E946B - 8B 87 181A0000 - MOV EAX,[RDI+00001A18]
	// 	// Trash<uint32>((appBaseAddr + 0xEA534 + 3), (enable) ? newOff : off); // dmc3.exe+EA534 - F3 0F10 86 181A0000 - MOVSS XMM0,[RSI+00001A18]
	// 	// Trash<uint32>((appBaseAddr + 0xEA6E2 + 3), (enable) ? newOff : off); // dmc3.exe+EA6E2 - 0F2F B6 181A0000 - COMISS XMM6,[RSI+00001A18]
	// 	// Trash<uint32>((appBaseAddr + 0xEA71F + 3), (enable) ? newOff : off); // dmc3.exe+EA71F - 0F2F B6 181A0000 - COMISS XMM6,[RSI+00001A18]
	// 	// Trash<uint32>((appBaseAddr + 0xEA758 + 3), (enable) ? newOff : off); // dmc3.exe+EA758 - 0F2F B6 181A0000 - COMISS XMM6,[RSI+00001A18]
	// 	// Trash<uint32>((appBaseAddr + 0xEB1A1 + 3), (enable) ? newOff : off); // dmc3.exe+EB1A1 - 0F2F B7 181A0000 - COMISS XMM6,[RDI+00001A18]
	// 	// Trash<uint32>((appBaseAddr + 0xEB2C3 + 3), (enable) ? newOff : off); // dmc3.exe+EB2C3 - 0F2F 81 181A0000 - COMISS XMM0,[RCX+00001A18]
	// 	// Trash<uint32>((appBaseAddr + 0xEB397 + 3), (enable) ? newOff : off); // dmc3.exe+EB397 - 0F2F 87 181A0000 - COMISS XMM0,[RDI+00001A18]
	// 	// Trash<uint32>((appBaseAddr + 0xEB3B3 + 3), (enable) ? newOff : off); // dmc3.exe+EB3B3 - 0F2F 87 181A0000 - COMISS XMM0,[RDI+00001A18]
	// 	// Trash<uint32>((appBaseAddr + 0xEB4CC + 3), (enable) ? newOff : off); // dmc3.exe+EB4CC - 44 0F2F 8F 181A0000 - COMISS XMM9,[RDI+00001A18]
	// 	// Mission19<uint32>((appBaseAddr + 0x160A5E + 3), (enable) ? newOff : off); // dmc3.exe+160A5E - 49 8B 86 181A0000 - MOV RAX,[R14+00001A18]
	// 	// Mission19<uint32>((appBaseAddr + 0x160A65 + 3), (enable) ? newOff : off); // dmc3.exe+160A65 - 49 8D 8E 181A0000 - LEA RCX,[R14+00001A18]
	// 	// Mission19<uint32>((appBaseAddr + 0x160A6F + 3), (enable) ? newOff : off); // dmc3.exe+160A6F - 49 8B 9E 181A0000 - MOV RBX,[R14+00001A18]
	// 	// Mission19<uint32>((appBaseAddr + 0x160A85 + 3), (enable) ? newOff : off); // dmc3.exe+160A85 - 49 8D 8E 181A0000 - LEA RCX,[R14+00001A18]
	// 	// Trash<uint32>((appBaseAddr + 0x162D80 + 3), (enable) ? newOff : off); // dmc3.exe+162D80 - 8B 91 181A0000 - MOV EDX,[RCX+00001A18]
	// }
	// // 0x1A20
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[2][4]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[2][4]);
		// static_assert(off == 0x1A20);
	// 	// Write<uint32>((appBaseAddr + 0xCC715 + 3), (enable) ? newOff : off); // dmc3.exe+CC715 - 48 89 83 201A0000 - MOV [RBX+00001A20],RAX
	// 	// Write<uint32>((appBaseAddr + 0xCC99E + 3), (enable) ? newOff : off); // dmc3.exe+CC99E - 48 89 83 201A0000 - MOV [RBX+00001A20],RAX
	// 	// Write<uint32>((appBaseAddr + 0x19004E + 3), (enable) ? newOff : off); // dmc3.exe+19004E - 49 8B 87 201A0000 - MOV RAX,[R15+00001A20]
	// 	// Write<uint32>((appBaseAddr + 0x190055 + 3), (enable) ? newOff : off); // dmc3.exe+190055 - 49 8D 8F 201A0000 - LEA RCX,[R15+00001A20]
	// 	// Write<uint32>((appBaseAddr + 0x1900FC + 3), (enable) ? newOff : off); // dmc3.exe+1900FC - 49 8B 87 201A0000 - MOV RAX,[R15+00001A20]
	// 	// Write<uint32>((appBaseAddr + 0x190103 + 3), (enable) ? newOff : off); // dmc3.exe+190103 - 49 8D 8F 201A0000 - LEA RCX,[R15+00001A20]
	// 	// Write<uint32>((appBaseAddr + 0x190B0B + 3), (enable) ? newOff : off); // dmc3.exe+190B0B - 49 8B 87 201A0000 - MOV RAX,[R15+00001A20]
	// 	// Write<uint32>((appBaseAddr + 0x190B12 + 3), (enable) ? newOff : off); // dmc3.exe+190B12 - 49 8D 8F 201A0000 - LEA RCX,[R15+00001A20]
	// 	// Write<uint32>((appBaseAddr + 0x190B25 + 3), (enable) ? newOff : off); // dmc3.exe+190B25 - 49 8B 87 201A0000 - MOV RAX,[R15+00001A20]
	// 	// Write<uint32>((appBaseAddr + 0x190B2C + 3), (enable) ? newOff : off); // dmc3.exe+190B2C - 49 8D 8F 201A0000 - LEA RCX,[R15+00001A20]
	// }
	// // 0x1A28
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[2][5]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[2][5]);
		// static_assert(off == 0x1A28);
	// 	// Write<uint32>((appBaseAddr + 0xCD7F2 + 3), (enable) ? newOff : off); // dmc3.exe+CD7F2 - 48 89 83 281A0000 - MOV [RBX+00001A28],RAX
	// 	// Write<uint32>((appBaseAddr + 0xE858E + 3), (enable) ? newOff : off); // dmc3.exe+E858E - 48 8D 8E 281A0000 - LEA RCX,[RSI+00001A28]
	// 	// Write<uint32>((appBaseAddr + 0xE86C1 + 3), (enable) ? newOff : off); // dmc3.exe+E86C1 - 48 8D 8E 281A0000 - LEA RCX,[RSI+00001A28]
	// 	// Write<uint32>((appBaseAddr + 0xE8B43 + 3), (enable) ? newOff : off); // dmc3.exe+E8B43 - 48 8D 8B 281A0000 - LEA RCX,[RBX+00001A28]
	// 	// Write<uint32>((appBaseAddr + 0xE8C18 + 3), (enable) ? newOff : off); // dmc3.exe+E8C18 - 48 8D 8B 281A0000 - LEA RCX,[RBX+00001A28]
	// 	// Write<uint32>((appBaseAddr + 0xEA3A5 + 3), (enable) ? newOff : off); // dmc3.exe+EA3A5 - 48 8D 8E 281A0000 - LEA RCX,[RSI+00001A28]
	// 	// Write<uint32>((appBaseAddr + 0x25B20A + 3), (enable) ? newOff : off); // dmc3.exe+25B20A - 48 89 81 281A0000 - MOV [RCX+00001A28],RAX
	// 	// Write<uint32>((appBaseAddr + 0x348557 + 3), (enable) ? newOff : off); // dmc3.exe+348557 - 48 81 C1 281A0000 - ADD RCX,00001A28
	// }
	// // 0x1A30
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[2][6]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[2][6]);
		// static_assert(off == 0x1A30);
	// 	// Write<uint32>((appBaseAddr + 0xCDC58 + 3), (enable) ? newOff : off); // dmc3.exe+CDC58 - 48 89 83 301A0000 - MOV [RBX+00001A30],RAX
	// 	// Write<uint32>((appBaseAddr + 0xCDC83 + 3), (enable) ? newOff : off); // dmc3.exe+CDC83 - 48 8B 83 301A0000 - MOV RAX,[RBX+00001A30]
	// 	// Mission19<uint32>((appBaseAddr + 0x25735C + 3), (enable) ? newOff : off); // dmc3.exe+25735C - 48 8D 91 301A0000 - LEA RDX,[RCX+00001A30]
	// 	// Write<uint32>((appBaseAddr + 0x25A5A0 + 3), (enable) ? newOff : off); // dmc3.exe+25A5A0 - 48 8D 97 301A0000 - LEA RDX,[RDI+00001A30]
	// }
	// // 0x1A38
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[2][7]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[2][7]);
		// static_assert(off == 0x1A38);
	// 	// Empty
	// }
	// // 0x1A40
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[2][8]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[2][8]);
		// static_assert(off == 0x1A40);
	// 	// Trash<uint32>((appBaseAddr + 0xD1C68 + 3), (enable) ? newOff : off); // dmc3.exe+D1C68 - 83 BB 401A0000 02 - CMP DWORD PTR [RBX+00001A40],02
	// 	// Write<uint32>((appBaseAddr + 0x118C79 + 3), (enable) ? newOff : off); // dmc3.exe+118C79 - 48 8D 8E 401A0000 - LEA RCX,[RSI+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x118E9A + 3), (enable) ? newOff : off); // dmc3.exe+118E9A - 48 8D 8E 401A0000 - LEA RCX,[RSI+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x11B36D + 3), (enable) ? newOff : off); // dmc3.exe+11B36D - 48 8D 8B 401A0000 - LEA RCX,[RBX+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x11B3F6 + 3), (enable) ? newOff : off); // dmc3.exe+11B3F6 - 48 8D 8B 401A0000 - LEA RCX,[RBX+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x11BEC0 + 3), (enable) ? newOff : off); // dmc3.exe+11BEC0 - 48 8D 8B 401A0000 - LEA RCX,[RBX+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x11C070 + 3), (enable) ? newOff : off); // dmc3.exe+11C070 - 48 8D 8B 401A0000 - LEA RCX,[RBX+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x11C328 + 3), (enable) ? newOff : off); // dmc3.exe+11C328 - 48 8D 8B 401A0000 - LEA RCX,[RBX+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x11D6A8 + 3), (enable) ? newOff : off); // dmc3.exe+11D6A8 - 48 8D 8B 401A0000 - LEA RCX,[RBX+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x11E954 + 3), (enable) ? newOff : off); // dmc3.exe+11E954 - 48 8D 8B 401A0000 - LEA RCX,[RBX+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x11FD1E + 3), (enable) ? newOff : off); // dmc3.exe+11FD1E - 48 8D 8B 401A0000 - LEA RCX,[RBX+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x11FDC1 + 3), (enable) ? newOff : off); // dmc3.exe+11FDC1 - 48 8D 8B 401A0000 - LEA RCX,[RBX+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x120345 + 3), (enable) ? newOff : off); // dmc3.exe+120345 - 48 8D 8F 401A0000 - LEA RCX,[RDI+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x1203FC + 3), (enable) ? newOff : off); // dmc3.exe+1203FC - 48 8D 8F 401A0000 - LEA RCX,[RDI+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x120498 + 3), (enable) ? newOff : off); // dmc3.exe+120498 - 48 8D 8F 401A0000 - LEA RCX,[RDI+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x120573 + 3), (enable) ? newOff : off); // dmc3.exe+120573 - 48 8D 8F 401A0000 - LEA RCX,[RDI+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x12061C + 3), (enable) ? newOff : off); // dmc3.exe+12061C - 48 8D 8F 401A0000 - LEA RCX,[RDI+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x120630 + 3), (enable) ? newOff : off); // dmc3.exe+120630 - 48 8D 8F 401A0000 - LEA RCX,[RDI+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x120822 + 3), (enable) ? newOff : off); // dmc3.exe+120822 - 48 8D 8F 401A0000 - LEA RCX,[RDI+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x121475 + 3), (enable) ? newOff : off); // dmc3.exe+121475 - 48 8D 8B 401A0000 - LEA RCX,[RBX+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x121595 + 3), (enable) ? newOff : off); // dmc3.exe+121595 - 48 81 C1 401A0000 - ADD RCX,00001A40
	// 	// Write<uint32>((appBaseAddr + 0x1215DD + 3), (enable) ? newOff : off); // dmc3.exe+1215DD - 48 8D 8F 401A0000 - LEA RCX,[RDI+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x121C78 + 3), (enable) ? newOff : off); // dmc3.exe+121C78 - 48 8D 8F 401A0000 - LEA RCX,[RDI+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x121E52 + 3), (enable) ? newOff : off); // dmc3.exe+121E52 - 48 8D 8B 401A0000 - LEA RCX,[RBX+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x1231B5 + 3), (enable) ? newOff : off); // dmc3.exe+1231B5 - 49 8D 8F 401A0000 - LEA RCX,[R15+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x12324E + 3), (enable) ? newOff : off); // dmc3.exe+12324E - 49 8D 8F 401A0000 - LEA RCX,[R15+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x1232A8 + 3), (enable) ? newOff : off); // dmc3.exe+1232A8 - 49 8B 87 401A0000 - MOV RAX,[R15+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x1232BD + 3), (enable) ? newOff : off); // dmc3.exe+1232BD - 49 8D 8F 401A0000 - LEA RCX,[R15+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x1233C4 + 3), (enable) ? newOff : off); // dmc3.exe+1233C4 - 49 8D 8F 401A0000 - LEA RCX,[R15+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x1238B9 + 3), (enable) ? newOff : off); // dmc3.exe+1238B9 - 49 8D 9F 401A0000 - LEA RBX,[R15+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x123A3B + 3), (enable) ? newOff : off); // dmc3.exe+123A3B - 49 8D 9F 401A0000 - LEA RBX,[R15+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x1260DB + 3), (enable) ? newOff : off); // dmc3.exe+1260DB - 48 8D 8B 401A0000 - LEA RCX,[RBX+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x126145 + 3), (enable) ? newOff : off); // dmc3.exe+126145 - 48 8D 8B 401A0000 - LEA RCX,[RBX+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x1261C5 + 3), (enable) ? newOff : off); // dmc3.exe+1261C5 - 48 8D 8F 401A0000 - LEA RCX,[RDI+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x1261D9 + 3), (enable) ? newOff : off); // dmc3.exe+1261D9 - 48 8D 8F 401A0000 - LEA RCX,[RDI+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x1261E2 + 3), (enable) ? newOff : off); // dmc3.exe+1261E2 - 48 81 C1 401A0000 - ADD RCX,00001A40
	// 	// Write<uint32>((appBaseAddr + 0x1261F6 + 3), (enable) ? newOff : off); // dmc3.exe+1261F6 - 48 8D 8F 401A0000 - LEA RCX,[RDI+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x126289 + 3), (enable) ? newOff : off); // dmc3.exe+126289 - 48 8D 8F 401A0000 - LEA RCX,[RDI+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x12629D + 3), (enable) ? newOff : off); // dmc3.exe+12629D - 48 8D 8F 401A0000 - LEA RCX,[RDI+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x1262BB + 3), (enable) ? newOff : off); // dmc3.exe+1262BB - 48 81 C1 401A0000 - ADD RCX,00001A40
	// 	// Write<uint32>((appBaseAddr + 0x1262CF + 3), (enable) ? newOff : off); // dmc3.exe+1262CF - 48 8D 8F 401A0000 - LEA RCX,[RDI+00001A40]
	// 	// Trash<uint32>((appBaseAddr + 0x126334 + 3), (enable) ? newOff : off); // dmc3.exe+126334 - B9 401A0000 - MOV ECX,00001A40
	// 	// Trash<uint32>((appBaseAddr + 0x126548 + 3), (enable) ? newOff : off); // dmc3.exe+126548 - B9 401A0000 - MOV ECX,00001A40
	// 	// Write<uint32>((appBaseAddr + 0x1266C4 + 3), (enable) ? newOff : off); // dmc3.exe+1266C4 - 48 8D 8E 401A0000 - LEA RCX,[RSI+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x1266CD + 3), (enable) ? newOff : off); // dmc3.exe+1266CD - 48 8D 8E 401A0000 - LEA RCX,[RSI+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x1267D6 + 3), (enable) ? newOff : off); // dmc3.exe+1267D6 - 48 8D 8E 401A0000 - LEA RCX,[RSI+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x126A44 + 3), (enable) ? newOff : off); // dmc3.exe+126A44 - 48 8D 8E 401A0000 - LEA RCX,[RSI+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x126A91 + 3), (enable) ? newOff : off); // dmc3.exe+126A91 - 48 8D 8E 401A0000 - LEA RCX,[RSI+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x126E87 + 3), (enable) ? newOff : off); // dmc3.exe+126E87 - 48 8D 8B 401A0000 - LEA RCX,[RBX+00001A40]
	// 	// Mission19<uint32>((appBaseAddr + 0x15C7E0 + 3), (enable) ? newOff : off); // dmc3.exe+15C7E0 - 48 8D 8E 401A0000 - LEA RCX,[RSI+00001A40]
	// 	// Mission19<uint32>((appBaseAddr + 0x15CACB + 3), (enable) ? newOff : off); // dmc3.exe+15CACB - 48 8D 8E 401A0000 - LEA RCX,[RSI+00001A40]
	// 	// Mission19<uint32>((appBaseAddr + 0x15FD2D + 3), (enable) ? newOff : off); // dmc3.exe+15FD2D - 48 8D 8F 401A0000 - LEA RCX,[RDI+00001A40]
	// 	// Mission19<uint32>((appBaseAddr + 0x161EBB + 3), (enable) ? newOff : off); // dmc3.exe+161EBB - 48 8D 9F 401A0000 - LEA RBX,[RDI+00001A40]
	// 	// Mission19<uint32>((appBaseAddr + 0x161ED3 + 3), (enable) ? newOff : off); // dmc3.exe+161ED3 - 48 8D 8F 401A0000 - LEA RCX,[RDI+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x286FF0 + 3), (enable) ? newOff : off); // dmc3.exe+286FF0 - 48 8D 8F 401A0000 - LEA RCX,[RDI+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x287571 + 3), (enable) ? newOff : off); // dmc3.exe+287571 - 4D 8D BD 401A0000 - LEA R15,[R13+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x2AEE1D + 3), (enable) ? newOff : off); // dmc3.exe+2AEE1D - 48 8D 8B 401A0000 - LEA RCX,[RBX+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x2AF7D0 + 3), (enable) ? newOff : off); // dmc3.exe+2AF7D0 - 4C 8D A1 401A0000 - LEA R12,[RCX+00001A40]
	// 	// Write<uint32>((appBaseAddr + 0x348EB8 + 3), (enable) ? newOff : off); // dmc3.exe+348EB8 - 48 81 C1 401A0000 - ADD RCX,00001A40
	// 	// Write<uint32>((appBaseAddr + 0x349D66 + 3), (enable) ? newOff : off); // dmc3.exe+349D66 - 48 81 C1 401A0000 - ADD RCX,00001A40
	// }
	// // 0x1A48
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[2][9]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[2][9]);
		// static_assert(off == 0x1A48);
	// 	// Empty
	// }
	// // 0x1A50
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[2][10]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[2][10]);
		// static_assert(off == 0x1A50);
	// 	// Write<uint32>((appBaseAddr + 0xE8AEF + 3), (enable) ? newOff : off); // dmc3.exe+E8AEF - 48 81 C1 501A0000 - ADD RCX,00001A50
	// 	// Mission19<uint32>((appBaseAddr + 0x160B64 + 3), (enable) ? newOff : off); // dmc3.exe+160B64 - 49 8D BE 501A0000 - LEA RDI,[R14+00001A50]
	// 	// Mission19<uint32>((appBaseAddr + 0x257351 + 3), (enable) ? newOff : off); // dmc3.exe+257351 - 4C 8D 81 501A0000 - LEA R8,[RCX+00001A50]
	// 	// Trash<uint32>((appBaseAddr + 0x25B172 + 3), (enable) ? newOff : off); // dmc3.exe+25B172 - 66 89 B3 501A0000 - MOV [RBX+00001A50],SI
	// 	// Trash<uint32>((appBaseAddr + 0x25D580 + 3), (enable) ? newOff : off); // dmc3.exe+25D580 - 0FB7 93 501A0000 - MOVZX EDX,WORD PTR [RBX+00001A50]
	// 	// Trash<uint32>((appBaseAddr + 0x25D6C0 + 3), (enable) ? newOff : off); // dmc3.exe+25D6C0 - 0FB7 93 501A0000 - MOVZX EDX,WORD PTR [RBX+00001A50]
	// }
	// // 0x1A58
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[2][11]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[2][11]);
		// static_assert(off == 0x1A58);
	// 	// Trash<uint32>((appBaseAddr + 0x25B18E + 3), (enable) ? newOff : off); // dmc3.exe+25B18E - 89 BB 581A0000 - MOV [RBX+00001A58],EDI
	// 	// Trash<uint32>((appBaseAddr + 0x25B378 + 3), (enable) ? newOff : off); // dmc3.exe+25B378 - 44 39 B7 581A0000 - CMP [RDI+00001A58],R14D
	// 	// Trash<uint32>((appBaseAddr + 0x25BB18 + 3), (enable) ? newOff : off); // dmc3.exe+25BB18 - 44 89 B0 581A0000 - MOV [RAX+00001A58],R14D
	// 	// Trash<uint32>((appBaseAddr + 0x25BB7D + 3), (enable) ? newOff : off); // dmc3.exe+25BB7D - 8B 91 581A0000 - MOV EDX,[RCX+00001A58]
	// 	// Trash<uint32>((appBaseAddr + 0x25C616 + 3), (enable) ? newOff : off); // dmc3.exe+25C616 - 83 BF 581A0000 00 - CMP DWORD PTR [RDI+00001A58],00
	// 	// Trash<uint32>((appBaseAddr + 0x25CEF6 + 3), (enable) ? newOff : off); // dmc3.exe+25CEF6 - 8B 89 581A0000 - MOV ECX,[RCX+00001A58]
	// 	// Trash<uint32>((appBaseAddr + 0x25D511 + 3), (enable) ? newOff : off); // dmc3.exe+25D511 - 8B 89 581A0000 - MOV ECX,[RCX+00001A58]
	// 	// Trash<uint32>((appBaseAddr + 0x25D6A1 + 3), (enable) ? newOff : off); // dmc3.exe+25D6A1 - 8B 89 581A0000 - MOV ECX,[RCX+00001A58]
	// }
	// // 0x1A60
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[2][12]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[2][12]);
		// static_assert(off == 0x1A60);
	// 	// Trash<uint32>((appBaseAddr + 0x160B8A + 3), (enable) ? newOff : off); // dmc3.exe+160B8A - 41 0F29 86 601A0000 - MOVAPS [R14+00001A60],XMM0
	// 	// Mission19<uint32>((appBaseAddr + 0x2573AA + 3), (enable) ? newOff : off); // dmc3.exe+2573AA - 48 8D 9D 601A0000 - LEA RBX,[RBP+00001A60]
	// 	// Write<uint32>((appBaseAddr + 0x25B194 + 3), (enable) ? newOff : off); // dmc3.exe+25B194 - 48 89 BB 601A0000 - MOV [RBX+00001A60],RDI
	// 	// Write<uint32>((appBaseAddr + 0x25CAB3 + 3), (enable) ? newOff : off); // dmc3.exe+25CAB3 - 48 89 98 601A0000 - MOV [RAX+00001A60],RBX
	// 	// Write<uint32>((appBaseAddr + 0x25CF16 + 3), (enable) ? newOff : off); // dmc3.exe+25CF16 - 48 8B 87 601A0000 - MOV RAX,[RDI+00001A60]
	// 	// Write<uint32>((appBaseAddr + 0x25D52E + 3), (enable) ? newOff : off); // dmc3.exe+25D52E - 48 8B 83 601A0000 - MOV RAX,[RBX+00001A60]
	// 	// Write<uint32>((appBaseAddr + 0x25D6B0 + 3), (enable) ? newOff : off); // dmc3.exe+25D6B0 - 48 8B 83 601A0000 - MOV RAX,[RBX+00001A60]
	// }
	// // 0x1A68
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[2][13]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[2][13]);
		// static_assert(off == 0x1A68);
	// 	// Trash<uint32>((appBaseAddr + 0xCC2A7 + 3), (enable) ? newOff : off); // dmc3.exe+CC2A7 - F3 0F58 83 681A0000 - ADDSS XMM0,DWORD PTR [RBX+00001A68]
	// 	// Trash<uint32>((appBaseAddr + 0xCC2AF + 3), (enable) ? newOff : off); // dmc3.exe+CC2AF - F3 0F11 83 681A0000 - MOVSS [RBX+00001A68],XMM0
	// 	// Write<uint32>((appBaseAddr + 0x258A0A + 3), (enable) ? newOff : off); // dmc3.exe+258A0A - 48 89 81 681A0000 - MOV [RCX+00001A68],RAX
	// 	// Write<uint32>((appBaseAddr + 0x25B19B + 3), (enable) ? newOff : off); // dmc3.exe+25B19B - 48 89 BB 681A0000 - MOV [RBX+00001A68],RDI
	// 	// Write<uint32>((appBaseAddr + 0x25B387 + 3), (enable) ? newOff : off); // dmc3.exe+25B387 - 48 8B 87 681A0000 - MOV RAX,[RDI+00001A68]
	// 	// Write<uint32>((appBaseAddr + 0x25B3B9 + 3), (enable) ? newOff : off); // dmc3.exe+25B3B9 - 48 8B 8F 681A0000 - MOV RCX,[RDI+00001A68]
	// 	// Write<uint32>((appBaseAddr + 0x25CA9D + 3), (enable) ? newOff : off); // dmc3.exe+25CA9D - 48 89 83 681A0000 - MOV [RBX+00001A68],RAX
	// 	// Write<uint32>((appBaseAddr + 0x25CB19 + 3), (enable) ? newOff : off); // dmc3.exe+25CB19 - 48 8B 83 681A0000 - MOV RAX,[RBX+00001A68]
	// 	// Write<uint32>((appBaseAddr + 0x25CB3B + 3), (enable) ? newOff : off); // dmc3.exe+25CB3B - 48 8B 83 681A0000 - MOV RAX,[RBX+00001A68]
	// 	// Write<uint32>((appBaseAddr + 0x25CB4A + 3), (enable) ? newOff : off); // dmc3.exe+25CB4A - 48 8B 83 681A0000 - MOV RAX,[RBX+00001A68]
	// 	// Write<uint32>((appBaseAddr + 0x25CB59 + 3), (enable) ? newOff : off); // dmc3.exe+25CB59 - 48 8B 83 681A0000 - MOV RAX,[RBX+00001A68]
	// 	// Write<uint32>((appBaseAddr + 0x25D3F0 + 3), (enable) ? newOff : off); // dmc3.exe+25D3F0 - 48 8B 89 681A0000 - MOV RCX,[RCX+00001A68]
	// }
	// // 0x1A70
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[2][14]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[2][14]);
		// static_assert(off == 0x1A70);
	// 	// Trash<uint32>((appBaseAddr + 0x160B96 + 3), (enable) ? newOff : off); // dmc3.exe+160B96 - 41 0F29 8E 701A0000 - MOVAPS [R14+00001A70],XMM1
	// }
	// // 0x1A78
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[2][15]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[2][15]);
		// static_assert(off == 0x1A78);
	// 	// Mission19<uint32>((appBaseAddr + 0x15FD3A + 3), (enable) ? newOff : off); // dmc3.exe+15FD3A - 48 8D 8F 781A0000 - LEA RCX,[RDI+00001A78]
	// }
	// // 0x1A80
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[2][16]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[2][16]);
		// static_assert(off == 0x1A80);
	// 	// Trash<uint32>((appBaseAddr + 0xCC24E + 3), (enable) ? newOff : off); // dmc3.exe+CC24E - 83 BB 801A0000 00 - CMP DWORD PTR [RBX+00001A80],00
	// 	// Trash<uint32>((appBaseAddr + 0xCCB11 + 3), (enable) ? newOff : off); // dmc3.exe+CCB11 - 0F29 86 801A0000 - MOVAPS [RSI+00001A80],XMM0
	// 	// Trash<uint32>((appBaseAddr + 0xCCB1D + 3), (enable) ? newOff : off); // dmc3.exe+CCB1D - F3 0F10 86 801A0000 - MOVSS XMM0,[RSI+00001A80]
	// 	// Write<uint32>((appBaseAddr + 0xCCB25 + 3), (enable) ? newOff : off); // dmc3.exe+CCB25 - 48 8D 96 801A0000 - LEA RDX,[RSI+00001A80]
	// 	// Trash<uint32>((appBaseAddr + 0xCE89A + 3), (enable) ? newOff : off); // dmc3.exe+CE89A - 0F29 83 801A0000 - MOVAPS [RBX+00001A80],XMM0
	// 	// Trash<uint32>((appBaseAddr + 0xCEFAA + 3), (enable) ? newOff : off); // dmc3.exe+CEFAA - 0F29 83 801A0000 - MOVAPS [RBX+00001A80],XMM0
	// 	// Write<uint32>((appBaseAddr + 0xCEFED + 3), (enable) ? newOff : off); // dmc3.exe+CEFED - 48 8D 93 801A0000 - LEA RDX,[RBX+00001A80]
	// 	// Trash<uint32>((appBaseAddr + 0xCF11A + 3), (enable) ? newOff : off); // dmc3.exe+CF11A - 0F29 83 801A0000 - MOVAPS [RBX+00001A80],XMM0
	// 	// Write<uint32>((appBaseAddr + 0xCF15D + 3), (enable) ? newOff : off); // dmc3.exe+CF15D - 48 8D 93 801A0000 - LEA RDX,[RBX+00001A80]
	// 	// Trash<uint32>((appBaseAddr + 0xCF561 + 3), (enable) ? newOff : off); // dmc3.exe+CF561 - F3 0F11 83 801A0000 - MOVSS [RBX+00001A80],XMM0
	// 	// Trash<uint32>((appBaseAddr + 0xCF5A9 + 3), (enable) ? newOff : off); // dmc3.exe+CF5A9 - F3 0F10 83 801A0000 - MOVSS XMM0,[RBX+00001A80]
	// 	// Trash<uint32>((appBaseAddr + 0xCF866 + 3), (enable) ? newOff : off); // dmc3.exe+CF866 - F3 0F11 83 801A0000 - MOVSS [RBX+00001A80],XMM0
	// 	// Trash<uint32>((appBaseAddr + 0xCF8A6 + 3), (enable) ? newOff : off); // dmc3.exe+CF8A6 - F3 0F10 83 801A0000 - MOVSS XMM0,[RBX+00001A80]
	// 	// Trash<uint32>((appBaseAddr + 0xCFFBE + 3), (enable) ? newOff : off); // dmc3.exe+CFFBE - F3 0F10 9F 801A0000 - MOVSS XMM3,[RDI+00001A80]
	// 	// Write<uint32>((appBaseAddr + 0xD0055 + 3), (enable) ? newOff : off); // dmc3.exe+D0055 - 48 8D 97 801A0000 - LEA RDX,[RDI+00001A80]
	// 	// Trash<uint32>((appBaseAddr + 0xD0128 + 3), (enable) ? newOff : off); // dmc3.exe+D0128 - F3 0F11 87 801A0000 - MOVSS [RDI+00001A80],XMM0
	// 	// Trash<uint32>((appBaseAddr + 0xD0338 + 3), (enable) ? newOff : off); // dmc3.exe+D0338 - F3 0F10 96 801A0000 - MOVSS XMM2,[RSI+00001A80]
	// 	// Write<uint32>((appBaseAddr + 0xD03BA + 3), (enable) ? newOff : off); // dmc3.exe+D03BA - 48 8D 96 801A0000 - LEA RDX,[RSI+00001A80]
	// 	// Trash<uint32>((appBaseAddr + 0xD044B + 3), (enable) ? newOff : off); // dmc3.exe+D044B - 0F29 86 801A0000 - MOVAPS [RSI+00001A80],XMM0
	// 	// Trash<uint32>((appBaseAddr + 0xD0469 + 3), (enable) ? newOff : off); // dmc3.exe+D0469 - F3 0F58 86 801A0000 - ADDSS XMM0,DWORD PTR [RSI+00001A80]
	// 	// Trash<uint32>((appBaseAddr + 0xD0471 + 3), (enable) ? newOff : off); // dmc3.exe+D0471 - F3 0F11 86 801A0000 - MOVSS [RSI+00001A80],XMM0
	// 	// Trash<uint32>((appBaseAddr + 0xD0664 + 3), (enable) ? newOff : off); // dmc3.exe+D0664 - F3 0F10 9F 801A0000 - MOVSS XMM3,[RDI+00001A80]
	// 	// Write<uint32>((appBaseAddr + 0xD06F2 + 3), (enable) ? newOff : off); // dmc3.exe+D06F2 - 48 8D 97 801A0000 - LEA RDX,[RDI+00001A80]
	// 	// Trash<uint32>((appBaseAddr + 0xD07C4 + 3), (enable) ? newOff : off); // dmc3.exe+D07C4 - F3 0F11 87 801A0000 - MOVSS [RDI+00001A80],XMM0
	// 	// Trash<uint32>((appBaseAddr + 0xD0968 + 3), (enable) ? newOff : off); // dmc3.exe+D0968 - 0F29 87 801A0000 - MOVAPS [RDI+00001A80],XMM0
	// 	// Trash<uint32>((appBaseAddr + 0xD0983 + 3), (enable) ? newOff : off); // dmc3.exe+D0983 - F3 0F58 87 801A0000 - ADDSS XMM0,DWORD PTR [RDI+00001A80]
	// 	// Trash<uint32>((appBaseAddr + 0xD098B + 3), (enable) ? newOff : off); // dmc3.exe+D098B - F3 0F11 87 801A0000 - MOVSS [RDI+00001A80],XMM0
	// 	// Write<uint32>((appBaseAddr + 0xD09F8 + 3), (enable) ? newOff : off); // dmc3.exe+D09F8 - 48 8D 97 801A0000 - LEA RDX,[RDI+00001A80]
	// 	// Trash<uint32>((appBaseAddr + 0xD0B1A + 3), (enable) ? newOff : off); // dmc3.exe+D0B1A - 0F29 83 801A0000 - MOVAPS [RBX+00001A80],XMM0
	// 	// Write<uint32>((appBaseAddr + 0xD0B62 + 3), (enable) ? newOff : off); // dmc3.exe+D0B62 - 48 8D 93 801A0000 - LEA RDX,[RBX+00001A80]
	// 	// Write<uint32>((appBaseAddr + 0x18A823 + 3), (enable) ? newOff : off); // dmc3.exe+18A823 - 48 8D 8E 801A0000 - LEA RCX,[RSI+00001A80]
	// 	// Write<uint32>((appBaseAddr + 0x18AC49 + 3), (enable) ? newOff : off); // dmc3.exe+18AC49 - 48 8D 8E 801A0000 - LEA RCX,[RSI+00001A80]
	// 	// Write<uint32>((appBaseAddr + 0x18E8BD + 3), (enable) ? newOff : off); // dmc3.exe+18E8BD - 48 8D 8F 801A0000 - LEA RCX,[RDI+00001A80]
	// 	// Write<uint32>((appBaseAddr + 0x18F9CF + 3), (enable) ? newOff : off); // dmc3.exe+18F9CF - 48 8B 83 801A0000 - MOV RAX,[RBX+00001A80]
	// 	// Write<uint32>((appBaseAddr + 0x18F9D6 + 3), (enable) ? newOff : off); // dmc3.exe+18F9D6 - 48 8D 8B 801A0000 - LEA RCX,[RBX+00001A80]
	// 	// Write<uint32>((appBaseAddr + 0x18F9ED + 3), (enable) ? newOff : off); // dmc3.exe+18F9ED - 48 8B 83 801A0000 - MOV RAX,[RBX+00001A80]
	// 	// Write<uint32>((appBaseAddr + 0x18F9F4 + 3), (enable) ? newOff : off); // dmc3.exe+18F9F4 - 48 8D 8B 801A0000 - LEA RCX,[RBX+00001A80]
	// 	// Write<uint32>((appBaseAddr + 0x1921A3 + 3), (enable) ? newOff : off); // dmc3.exe+1921A3 - 48 8D 8F 801A0000 - LEA RCX,[RDI+00001A80]
	// 	// Write<uint32>((appBaseAddr + 0x1921CD + 3), (enable) ? newOff : off); // dmc3.exe+1921CD - 48 8D 8F 801A0000 - LEA RCX,[RDI+00001A80]
	// 	// Write<uint32>((appBaseAddr + 0x1955B6 + 3), (enable) ? newOff : off); // dmc3.exe+1955B6 - 48 8D 8B 801A0000 - LEA RCX,[RBX+00001A80]
	// 	// Trash<uint32>((appBaseAddr + 0x253D63 + 3), (enable) ? newOff : off); // dmc3.exe+253D63 - 44 0F29 88 801A0000 - MOVAPS [RAX+00001A80],XMM9
	// 	// Write<uint32>((appBaseAddr + 0x253D85 + 3), (enable) ? newOff : off); // dmc3.exe+253D85 - 49 8D 88 801A0000 - LEA RCX,[R8+00001A80]
	// 	// Write<uint32>((appBaseAddr + 0x254470 + 3), (enable) ? newOff : off); // dmc3.exe+254470 - 4C 8D 8D 801A0000 - LEA R9,[RBP+00001A80]
	// 	// Write<uint32>((appBaseAddr + 0x2545DC + 3), (enable) ? newOff : off); // dmc3.exe+2545DC - 48 8D 95 801A0000 - LEA RDX,[RBP+00001A80]
	// 	// Write<uint32>((appBaseAddr + 0x2545F7 + 3), (enable) ? newOff : off); // dmc3.exe+2545F7 - 48 8D 95 801A0000 - LEA RDX,[RBP+00001A80]
	// 	// Write<uint32>((appBaseAddr + 0x2549C7 + 3), (enable) ? newOff : off); // dmc3.exe+2549C7 - 48 8D 97 801A0000 - LEA RDX,[RDI+00001A80]
	// 	// Write<uint32>((appBaseAddr + 0x2549DE + 3), (enable) ? newOff : off); // dmc3.exe+2549DE - 48 8D 97 801A0000 - LEA RDX,[RDI+00001A80]
	// 	// Trash<uint32>((appBaseAddr + 0x25B2B9 + 3), (enable) ? newOff : off); // dmc3.exe+25B2B9 - BA 801A0000 - MOV EDX,00001A80
	// 	// Trash<uint32>((appBaseAddr + 0x25BA74 + 3), (enable) ? newOff : off); // dmc3.exe+25BA74 - BA 801A0000 - MOV EDX,00001A80
	// 	// Write<uint32>((appBaseAddr + 0x34AA90 + 3), (enable) ? newOff : off); // dmc3.exe+34AA90 - 48 81 C1 801A0000 - ADD RCX,00001A80
	// 	// Trash<uint32>((appBaseAddr + 0x598A29 + 3), (enable) ? newOff : off); // dmc3.exe+598A29 - 15 00001A80 - ADC EAX,801A0000
	// 	// Trash<uint32>((appBaseAddr + 0x598A58 + 3), (enable) ? newOff : off); // dmc3.exe+598A58 - C1 15 00001A80 00 - RCL [FFFFFFFF80737E5F],00
	// 	// Trash<uint32>((appBaseAddr + 0x598A77 + 3), (enable) ? newOff : off); // dmc3.exe+598A77 - 00 BC 15 00001A80 - ADD [RBP+RDX-7FE60000],BH
	// }
	// // 0x1A88
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[2][17]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[2][17]);
		// static_assert(off == 0x1A88);
	// 	// Trash<uint32>((appBaseAddr + 0xCCB7D + 3), (enable) ? newOff : off); // dmc3.exe+CCB7D - F3 0F10 8E 881A0000 - MOVSS XMM1,[RSI+00001A88]
	// 	// Trash<uint32>((appBaseAddr + 0xCF036 + 3), (enable) ? newOff : off); // dmc3.exe+CF036 - F3 0F10 8B 881A0000 - MOVSS XMM1,[RBX+00001A88]
	// 	// Trash<uint32>((appBaseAddr + 0xCF1A6 + 3), (enable) ? newOff : off); // dmc3.exe+CF1A6 - F3 0F10 8B 881A0000 - MOVSS XMM1,[RBX+00001A88]
	// 	// Trash<uint32>((appBaseAddr + 0xCF5A1 + 3), (enable) ? newOff : off); // dmc3.exe+CF5A1 - F3 0F11 83 881A0000 - MOVSS [RBX+00001A88],XMM0
	// 	// Trash<uint32>((appBaseAddr + 0xCF5C9 + 3), (enable) ? newOff : off); // dmc3.exe+CF5C9 - F3 0F10 9B 881A0000 - MOVSS XMM3,[RBX+00001A88]
	// 	// Trash<uint32>((appBaseAddr + 0xCF89E + 3), (enable) ? newOff : off); // dmc3.exe+CF89E - F3 0F11 83 881A0000 - MOVSS [RBX+00001A88],XMM0
	// 	// Trash<uint32>((appBaseAddr + 0xCF8B6 + 3), (enable) ? newOff : off); // dmc3.exe+CF8B6 - F3 0F10 8B 881A0000 - MOVSS XMM1,[RBX+00001A88]
	// 	// Trash<uint32>((appBaseAddr + 0xCFFC6 + 3), (enable) ? newOff : off); // dmc3.exe+CFFC6 - F3 0F10 A7 881A0000 - MOVSS XMM4,[RDI+00001A88]
	// 	// Trash<uint32>((appBaseAddr + 0xD015B + 3), (enable) ? newOff : off); // dmc3.exe+D015B - F3 0F11 87 881A0000 - MOVSS [RDI+00001A88],XMM0
	// 	// Trash<uint32>((appBaseAddr + 0xD0351 + 3), (enable) ? newOff : off); // dmc3.exe+D0351 - F3 0F10 A6 881A0000 - MOVSS XMM4,[RSI+00001A88]
	// 	// Trash<uint32>((appBaseAddr + 0xD0490 + 3), (enable) ? newOff : off); // dmc3.exe+D0490 - F3 0F58 86 881A0000 - ADDSS XMM0,DWORD PTR [RSI+00001A88]
	// 	// Trash<uint32>((appBaseAddr + 0xD0498 + 3), (enable) ? newOff : off); // dmc3.exe+D0498 - F3 0F11 86 881A0000 - MOVSS [RSI+00001A88],XMM0
	// 	// Trash<uint32>((appBaseAddr + 0xD066C + 3), (enable) ? newOff : off); // dmc3.exe+D066C - F3 0F10 A7 881A0000 - MOVSS XMM4,[RDI+00001A88]
	// 	// Trash<uint32>((appBaseAddr + 0xD07F7 + 3), (enable) ? newOff : off); // dmc3.exe+D07F7 - F3 0F11 87 881A0000 - MOVSS [RDI+00001A88],XMM0
	// 	// Trash<uint32>((appBaseAddr + 0xD09C4 + 3), (enable) ? newOff : off); // dmc3.exe+D09C4 - F3 0F58 87 881A0000 - ADDSS XMM0,DWORD PTR [RDI+00001A88]
	// 	// Trash<uint32>((appBaseAddr + 0xD09CC + 3), (enable) ? newOff : off); // dmc3.exe+D09CC - F3 0F11 87 881A0000 - MOVSS [RDI+00001A88],XMM0
	// 	// Trash<uint32>((appBaseAddr + 0xD0A41 + 3), (enable) ? newOff : off); // dmc3.exe+D0A41 - F3 0F10 8F 881A0000 - MOVSS XMM1,[RDI+00001A88]
	// 	// Trash<uint32>((appBaseAddr + 0xD0BAB + 3), (enable) ? newOff : off); // dmc3.exe+D0BAB - F3 0F10 8B 881A0000 - MOVSS XMM1,[RBX+00001A88]
	// 	// Write<uint32>((appBaseAddr + 0xE859B + 3), (enable) ? newOff : off); // dmc3.exe+E859B - 48 8D 8E 881A0000 - LEA RCX,[RSI+00001A88]
	// 	// Write<uint32>((appBaseAddr + 0xE86B4 + 3), (enable) ? newOff : off); // dmc3.exe+E86B4 - 48 8D 8E 881A0000 - LEA RCX,[RSI+00001A88]
	// 	// Write<uint32>((appBaseAddr + 0xEA3CB + 3), (enable) ? newOff : off); // dmc3.exe+EA3CB - 4C 8D 8E 881A0000 - LEA R9,[RSI+00001A88]
	// 	// Write<uint32>((appBaseAddr + 0xEA3D7 + 3), (enable) ? newOff : off); // dmc3.exe+EA3D7 - 48 8B 86 881A0000 - MOV RAX,[RSI+00001A88]
	// 	// Write<uint32>((appBaseAddr + 0xEA3DE + 3), (enable) ? newOff : off); // dmc3.exe+EA3DE - 48 8D 8E 881A0000 - LEA RCX,[RSI+00001A88]
	// 	// Write<uint32>((appBaseAddr + 0x34856A + 3), (enable) ? newOff : off); // dmc3.exe+34856A - 48 81 C1 881A0000 - ADD RCX,00001A88
	// }
	// // 0x1A90
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[2][18]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[2][18]);
		// static_assert(off == 0x1A90);
	// 	// Trash<uint32>((appBaseAddr + 0xCF450 + 3), (enable) ? newOff : off); // dmc3.exe+CF450 - 89 B3 901A0000 - MOV [RBX+00001A90],ESI
	// 	// Trash<uint32>((appBaseAddr + 0xCF755 + 3), (enable) ? newOff : off); // dmc3.exe+CF755 - 89 93 901A0000 - MOV [RBX+00001A90],EDX
	// 	// Write<uint32>((appBaseAddr + 0xCFF3F + 3), (enable) ? newOff : off); // dmc3.exe+CFF3F - 48 89 AF 901A0000 - MOV [RDI+00001A90],RBP
	// 	// Trash<uint32>((appBaseAddr + 0xD02EE + 3), (enable) ? newOff : off); // dmc3.exe+D02EE - 89 96 901A0000 - MOV [RSI+00001A90],EDX
	// 	// Write<uint32>((appBaseAddr + 0xD05E0 + 3), (enable) ? newOff : off); // dmc3.exe+D05E0 - 48 89 97 901A0000 - MOV [RDI+00001A90],RDX
	// 	// Trash<uint32>((appBaseAddr + 0xD2AF6 + 3), (enable) ? newOff : off); // dmc3.exe+D2AF6 - 89 BB 901A0000 - MOV [RBX+00001A90],EDI
	// 	// Trash<uint32>((appBaseAddr + 0x253D6B + 3), (enable) ? newOff : off); // dmc3.exe+253D6B - 44 0F29 80 901A0000 - MOVAPS [RAX+00001A90],XMM8
	// 	// Trash<uint32>((appBaseAddr + 0x259822 + 3), (enable) ? newOff : off); // dmc3.exe+259822 - 0F11 80 901A0000 - MOVUPS [RAX+00001A90],XMM0
	// 	// Write<uint32>((appBaseAddr + 0x25AA39 + 3), (enable) ? newOff : off); // dmc3.exe+25AA39 - 48 8D 97 901A0000 - LEA RDX,[RDI+00001A90]
	// }
	// // 0x1A98
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[2][19]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[2][19]);
		// static_assert(off == 0x1A98);
	// 	// Trash<uint32>((appBaseAddr + 0xC88E2 + 3), (enable) ? newOff : off); // dmc3.exe+C88E2 - F3 0F10 84 9E 981A0000 - MOVSS XMM0,[RSI+RBX*4+00001A98]
	// 	// Trash<uint32>((appBaseAddr + 0xC890D + 3), (enable) ? newOff : off); // dmc3.exe+C890D - F3 0F11 84 9E 981A0000 - MOVSS [RSI+RBX*4+00001A98],XMM0
	// 	// Write<uint32>((appBaseAddr + 0xC89D2 + 3), (enable) ? newOff : off); // dmc3.exe+C89D2 - 48 8D A9 981A0000 - LEA RBP,[RCX+00001A98]
	// 	// Trash<uint32>((appBaseAddr + 0xC8F09 + 3), (enable) ? newOff : off); // dmc3.exe+C8F09 - C7 84 9E 981A0000 0000803F - MOV [RSI+RBX*4+00001A98],3F800000
	// 	// Trash<uint32>((appBaseAddr + 0xC9088 + 3), (enable) ? newOff : off); // dmc3.exe+C9088 - C7 86 981A0000 000020C1 - MOV [RSI+00001A98],C1200000
	// 	// Trash<uint32>((appBaseAddr + 0xD01F8 + 3), (enable) ? newOff : off); // dmc3.exe+D01F8 - 0FBF 87 981A0000 - MOVSX EAX,WORD PTR [RDI+00001A98]
	// 	// Trash<uint32>((appBaseAddr + 0xD021E + 3), (enable) ? newOff : off); // dmc3.exe+D021E - 66 89 87 981A0000 - MOV [RDI+00001A98],AX
	// 	// Trash<uint32>((appBaseAddr + 0xD04F8 + 3), (enable) ? newOff : off); // dmc3.exe+D04F8 - 0FBF 86 981A0000 - MOVSX EAX,WORD PTR [RSI+00001A98]
	// 	// Trash<uint32>((appBaseAddr + 0xD051E + 3), (enable) ? newOff : off); // dmc3.exe+D051E - 66 89 86 981A0000 - MOV [RSI+00001A98],AX
	// 	// Trash<uint32>((appBaseAddr + 0xD0857 + 3), (enable) ? newOff : off); // dmc3.exe+D0857 - 0FBF 87 981A0000 - MOVSX EAX,WORD PTR [RDI+00001A98]
	// 	// Trash<uint32>((appBaseAddr + 0xD087D + 3), (enable) ? newOff : off); // dmc3.exe+D087D - 66 89 87 981A0000 - MOV [RDI+00001A98],AX
	// 	// Trash<uint32>((appBaseAddr + 0xD2AEF + 3), (enable) ? newOff : off); // dmc3.exe+D2AEF - 66 89 BB 981A0000 - MOV [RBX+00001A98],DI
	// }
	// // 0x1AA0
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[2][20]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[2][20]);
		// static_assert(off == 0x1AA0);
	// 	// Trash<uint32>((appBaseAddr + 0xCC371 + 3), (enable) ? newOff : off); // dmc3.exe+CC371 - 8B 8B A01A0000 - MOV ECX,[RBX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xCC510 + 3), (enable) ? newOff : off); // dmc3.exe+CC510 - 8B 89 A01A0000 - MOV ECX,[RCX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xCC7CA + 3), (enable) ? newOff : off); // dmc3.exe+CC7CA - 8B 89 A01A0000 - MOV ECX,[RCX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xCC850 + 3), (enable) ? newOff : off); // dmc3.exe+CC850 - 8B 89 A01A0000 - MOV ECX,[RCX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xCCA0F + 3), (enable) ? newOff : off); // dmc3.exe+CCA0F - 8B 89 A01A0000 - MOV ECX,[RCX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xCCC3A + 3), (enable) ? newOff : off); // dmc3.exe+CCC3A - 8B 8B A01A0000 - MOV ECX,[RBX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xCCE62 + 3), (enable) ? newOff : off); // dmc3.exe+CCE62 - 8B 8B A01A0000 - MOV ECX,[RBX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xCCFA9 + 3), (enable) ? newOff : off); // dmc3.exe+CCFA9 - 8B 8B A01A0000 - MOV ECX,[RBX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xCD139 + 3), (enable) ? newOff : off); // dmc3.exe+CD139 - 8B 8B A01A0000 - MOV ECX,[RBX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xCD298 + 3), (enable) ? newOff : off); // dmc3.exe+CD298 - 8B 8B A01A0000 - MOV ECX,[RBX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xCD434 + 3), (enable) ? newOff : off); // dmc3.exe+CD434 - 8B 8B A01A0000 - MOV ECX,[RBX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xCDB1D + 3), (enable) ? newOff : off); // dmc3.exe+CDB1D - 8B 8F A01A0000 - MOV ECX,[RDI+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xCDBD4 + 3), (enable) ? newOff : off); // dmc3.exe+CDBD4 - 8B 89 A01A0000 - MOV ECX,[RCX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xCDE3F + 3), (enable) ? newOff : off); // dmc3.exe+CDE3F - 8B 89 A01A0000 - MOV ECX,[RCX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xCDFC0 + 3), (enable) ? newOff : off); // dmc3.exe+CDFC0 - 8B 89 A01A0000 - MOV ECX,[RCX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xCE0BF + 3), (enable) ? newOff : off); // dmc3.exe+CE0BF - 8B 89 A01A0000 - MOV ECX,[RCX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xCE25F + 3), (enable) ? newOff : off); // dmc3.exe+CE25F - 8B 89 A01A0000 - MOV ECX,[RCX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xCE3EF + 3), (enable) ? newOff : off); // dmc3.exe+CE3EF - 8B 89 A01A0000 - MOV ECX,[RCX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xCE56F + 3), (enable) ? newOff : off); // dmc3.exe+CE56F - 8B 89 A01A0000 - MOV ECX,[RCX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xCE6E0 + 3), (enable) ? newOff : off); // dmc3.exe+CE6E0 - 8B 89 A01A0000 - MOV ECX,[RCX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xCE78D + 3), (enable) ? newOff : off); // dmc3.exe+CE78D - C7 83 A01A0000 01000000 - MOV [RBX+00001AA0],00000001
	// 	// Trash<uint32>((appBaseAddr + 0xCE820 + 3), (enable) ? newOff : off); // dmc3.exe+CE820 - 8B 89 A01A0000 - MOV ECX,[RCX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xCE930 + 3), (enable) ? newOff : off); // dmc3.exe+CE930 - 8B 89 A01A0000 - MOV ECX,[RCX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xCEDDF + 3), (enable) ? newOff : off); // dmc3.exe+CEDDF - 8B 89 A01A0000 - MOV ECX,[RCX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xCEF40 + 3), (enable) ? newOff : off); // dmc3.exe+CEF40 - 8B 89 A01A0000 - MOV ECX,[RCX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xCF0A0 + 3), (enable) ? newOff : off); // dmc3.exe+CF0A0 - 8B 89 A01A0000 - MOV ECX,[RCX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xCF277 + 3), (enable) ? newOff : off); // dmc3.exe+CF277 - C7 83 A01A0000 00000000 - MOV [RBX+00001AA0],00000000
	// 	// Trash<uint32>((appBaseAddr + 0xCF2DC + 3), (enable) ? newOff : off); // dmc3.exe+CF2DC - 8B 8B A01A0000 - MOV ECX,[RBX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xCF3D9 + 3), (enable) ? newOff : off); // dmc3.exe+CF3D9 - 8B 89 A01A0000 - MOV ECX,[RCX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xCF6E4 + 3), (enable) ? newOff : off); // dmc3.exe+CF6E4 - 8B 89 A01A0000 - MOV ECX,[RCX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xCFED3 + 3), (enable) ? newOff : off); // dmc3.exe+CFED3 - 8B 89 A01A0000 - MOV ECX,[RCX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xD027F + 3), (enable) ? newOff : off); // dmc3.exe+D027F - 8B 89 A01A0000 - MOV ECX,[RCX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xD057F + 3), (enable) ? newOff : off); // dmc3.exe+D057F - 8B 89 A01A0000 - MOV ECX,[RCX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xD08D0 + 3), (enable) ? newOff : off); // dmc3.exe+D08D0 - 8B 89 A01A0000 - MOV ECX,[RCX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xD0AA0 + 3), (enable) ? newOff : off); // dmc3.exe+D0AA0 - 8B 89 A01A0000 - MOV ECX,[RCX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xD19CC + 3), (enable) ? newOff : off); // dmc3.exe+D19CC - 83 BB A01A0000 01 - CMP DWORD PTR [RBX+00001AA0],01
	// 	// Trash<uint32>((appBaseAddr + 0xD2B0A + 3), (enable) ? newOff : off); // dmc3.exe+D2B0A - 89 BB A01A0000 - MOV [RBX+00001AA0],EDI
	// 	// Trash<uint32>((appBaseAddr + 0xD2B60 + 3), (enable) ? newOff : off); // dmc3.exe+D2B60 - 8B 87 A01A0000 - MOV EAX,[RDI+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xD3256 + 3), (enable) ? newOff : off); // dmc3.exe+D3256 - 8B 91 A01A0000 - MOV EDX,[RCX+00001AA0]
	// 	// Trash<uint32>((appBaseAddr + 0xE8B7D + 3), (enable) ? newOff : off); // dmc3.exe+E8B7D - C6 83 A01A0000 01 - MOV BYTE PTR [RBX+00001AA0],01
	// 	// Trash<uint32>((appBaseAddr + 0xE9A2A + 3), (enable) ? newOff : off); // dmc3.exe+E9A2A - C6 81 A01A0000 01 - MOV BYTE PTR [RCX+00001AA0],01
	// 	// Trash<uint32>((appBaseAddr + 0x253D73 + 3), (enable) ? newOff : off); // dmc3.exe+253D73 - 0F29 B8 A01A0000 - MOVAPS [RAX+00001AA0],XMM7
	// 	// Trash<uint32>((appBaseAddr + 0x2541FD + 3), (enable) ? newOff : off); // dmc3.exe+2541FD - C6 81 A01A0000 00 - MOV BYTE PTR [RCX+00001AA0],00
	// 	// Trash<uint32>((appBaseAddr + 0x254373 + 3), (enable) ? newOff : off); // dmc3.exe+254373 - C6 86 A01A0000 01 - MOV BYTE PTR [RSI+00001AA0],01
	// 	// Trash<uint32>((appBaseAddr + 0x259830 + 3), (enable) ? newOff : off); // dmc3.exe+259830 - 0F11 88 A01A0000 - MOVUPS [RAX+00001AA0],XMM1
	// }
	// // 0x1AA8
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[2][21]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[2][21]);
		// static_assert(off == 0x1AA8);
	// 	// Trash<uint32>((appBaseAddr + 0xCC67C + 3), (enable) ? newOff : off); // dmc3.exe+CC67C - F3 0F58 83 A81A0000 - ADDSS XMM0,DWORD PTR [RBX+00001AA8]
	// 	// Trash<uint32>((appBaseAddr + 0xCC68B + 3), (enable) ? newOff : off); // dmc3.exe+CC68B - F3 0F11 83 A81A0000 - MOVSS [RBX+00001AA8],XMM0
	// 	// Trash<uint32>((appBaseAddr + 0xCC695 + 3), (enable) ? newOff : off); // dmc3.exe+CC695 - C7 83 A81A0000 0000803F - MOV [RBX+00001AA8],3F800000
	// 	// Trash<uint32>((appBaseAddr + 0xCC6BF + 3), (enable) ? newOff : off); // dmc3.exe+CC6BF - C7 83 A81A0000 0000803F - MOV [RBX+00001AA8],3F800000
	// 	// Trash<uint32>((appBaseAddr + 0xCC8FA + 3), (enable) ? newOff : off); // dmc3.exe+CC8FA - F3 0F58 83 A81A0000 - ADDSS XMM0,DWORD PTR [RBX+00001AA8]
	// 	// Trash<uint32>((appBaseAddr + 0xCC909 + 3), (enable) ? newOff : off); // dmc3.exe+CC909 - F3 0F11 83 A81A0000 - MOVSS [RBX+00001AA8],XMM0
	// 	// Trash<uint32>((appBaseAddr + 0xCC913 + 3), (enable) ? newOff : off); // dmc3.exe+CC913 - C7 83 A81A0000 0000803F - MOV [RBX+00001AA8],3F800000
	// 	// Trash<uint32>((appBaseAddr + 0xCC940 + 3), (enable) ? newOff : off); // dmc3.exe+CC940 - C7 83 A81A0000 0000803F - MOV [RBX+00001AA8],3F800000
	// 	// Trash<uint32>((appBaseAddr + 0xCDD37 + 3), (enable) ? newOff : off); // dmc3.exe+CDD37 - F3 0F10 8B A81A0000 - MOVSS XMM1,[RBX+00001AA8]
	// 	// Trash<uint32>((appBaseAddr + 0xCDD59 + 3), (enable) ? newOff : off); // dmc3.exe+CDD59 - F3 0F11 8B A81A0000 - MOVSS [RBX+00001AA8],XMM1
	// 	// Trash<uint32>((appBaseAddr + 0xCDD63 + 3), (enable) ? newOff : off); // dmc3.exe+CDD63 - 89 BB A81A0000 - MOV [RBX+00001AA8],EDI
	// 	// Trash<uint32>((appBaseAddr + 0xCDD8C + 3), (enable) ? newOff : off); // dmc3.exe+CDD8C - 89 BB A81A0000 - MOV [RBX+00001AA8],EDI
	// 	// Trash<uint32>((appBaseAddr + 0xD0CFE + 3), (enable) ? newOff : off); // dmc3.exe+D0CFE - 89 AF A81A0000 - MOV [RDI+00001AA8],EBP
	// 	// Trash<uint32>((appBaseAddr + 0xD32FF + 3), (enable) ? newOff : off); // dmc3.exe+D32FF - F3 0F59 87 A81A0000 - MULSS XMM0,[RDI+00001AA8]
	// 	// Trash<uint32>((appBaseAddr + 0x25420E + 3), (enable) ? newOff : off); // dmc3.exe+25420E - 44 8B 81 A81A0000 - MOV R8D,[RCX+00001AA8]
	// }
	// // 0x1AB0
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[2][22]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[2][22]);
		// static_assert(off == 0x1AB0);
	// 	// Trash<uint32>((appBaseAddr + 0xCCC9E + 3), (enable) ? newOff : off); // dmc3.exe+CCC9E - C7 83 B01A0000 EC51383E - MOV [RBX+00001AB0],3E3851EC
	// 	// Trash<uint32>((appBaseAddr + 0xCCCE3 + 3), (enable) ? newOff : off); // dmc3.exe+CCCE3 - F3 0F10 93 B01A0000 - MOVSS XMM2,[RBX+00001AB0]
	// 	// Trash<uint32>((appBaseAddr + 0xCCDE2 + 3), (enable) ? newOff : off); // dmc3.exe+CCDE2 - F3 0F10 93 B01A0000 - MOVSS XMM2,[RBX+00001AB0]
	// 	// Trash<uint32>((appBaseAddr + 0xCCEF0 + 3), (enable) ? newOff : off); // dmc3.exe+CCEF0 - C7 83 B01A0000 0000003E - MOV [RBX+00001AB0],3E000000
	// 	// Trash<uint32>((appBaseAddr + 0xCD0B9 + 3), (enable) ? newOff : off); // dmc3.exe+CD0B9 - F3 0F10 93 B01A0000 - MOVSS XMM2,[RBX+00001AB0]
	// 	// Trash<uint32>((appBaseAddr + 0xCD1BC + 3), (enable) ? newOff : off); // dmc3.exe+CD1BC - C7 83 B01A0000 EC51383E - MOV [RBX+00001AB0],3E3851EC
	// 	// Trash<uint32>((appBaseAddr + 0xCD2F2 + 3), (enable) ? newOff : off); // dmc3.exe+CD2F2 - C7 83 B01A0000 0000803F - MOV [RBX+00001AB0],3F800000
	// 	// Trash<uint32>((appBaseAddr + 0xCD36D + 3), (enable) ? newOff : off); // dmc3.exe+CD36D - F3 0F10 93 B01A0000 - MOVSS XMM2,[RBX+00001AB0]
	// 	// Trash<uint32>((appBaseAddr + 0xCD91B + 3), (enable) ? newOff : off); // dmc3.exe+CD91B - F3 0F10 97 B01A0000 - MOVSS XMM2,[RDI+00001AB0]
	// 	// Trash<uint32>((appBaseAddr + 0xCDB0C + 3), (enable) ? newOff : off); // dmc3.exe+CDB0C - C7 87 B01A0000 00000040 - MOV [RDI+00001AB0],40000000
	// 	// Trash<uint32>((appBaseAddr + 0xCDED9 + 3), (enable) ? newOff : off); // dmc3.exe+CDED9 - F3 0F11 8B B01A0000 - MOVSS [RBX+00001AB0],XMM1
	// 	// Trash<uint32>((appBaseAddr + 0xCDF24 + 3), (enable) ? newOff : off); // dmc3.exe+CDF24 - F3 0F10 93 B01A0000 - MOVSS XMM2,[RBX+00001AB0]
	// 	// Trash<uint32>((appBaseAddr + 0xCE145 + 3), (enable) ? newOff : off); // dmc3.exe+CE145 - C7 83 B01A0000 00000040 - MOV [RBX+00001AB0],40000000
	// 	// Trash<uint32>((appBaseAddr + 0xCE1CA + 3), (enable) ? newOff : off); // dmc3.exe+CE1CA - F3 0F10 93 B01A0000 - MOVSS XMM2,[RBX+00001AB0]
	// 	// Trash<uint32>((appBaseAddr + 0xCE2F9 + 3), (enable) ? newOff : off); // dmc3.exe+CE2F9 - F3 0F11 8B B01A0000 - MOVSS [RBX+00001AB0],XMM1
	// 	// Trash<uint32>((appBaseAddr + 0xCE344 + 3), (enable) ? newOff : off); // dmc3.exe+CE344 - F3 0F10 93 B01A0000 - MOVSS XMM2,[RBX+00001AB0]
	// 	// Trash<uint32>((appBaseAddr + 0xCE489 + 3), (enable) ? newOff : off); // dmc3.exe+CE489 - F3 0F11 8B B01A0000 - MOVSS [RBX+00001AB0],XMM1
	// 	// Trash<uint32>((appBaseAddr + 0xCE4D4 + 3), (enable) ? newOff : off); // dmc3.exe+CE4D4 - F3 0F10 93 B01A0000 - MOVSS XMM2,[RBX+00001AB0]
	// 	// Trash<uint32>((appBaseAddr + 0xCE609 + 3), (enable) ? newOff : off); // dmc3.exe+CE609 - F3 0F11 8B B01A0000 - MOVSS [RBX+00001AB0],XMM1
	// 	// Trash<uint32>((appBaseAddr + 0xCE654 + 3), (enable) ? newOff : off); // dmc3.exe+CE654 - F3 0F10 93 B01A0000 - MOVSS XMM2,[RBX+00001AB0]
	// 	// Trash<uint32>((appBaseAddr + 0xCEE62 + 3), (enable) ? newOff : off); // dmc3.exe+CEE62 - C7 83 B01A0000 0000803F - MOV [RBX+00001AB0],3F800000
	// 	// Trash<uint32>((appBaseAddr + 0xCEEA7 + 3), (enable) ? newOff : off); // dmc3.exe+CEEA7 - F3 0F10 93 B01A0000 - MOVSS XMM2,[RBX+00001AB0]
	// 	// Write<uint32>((appBaseAddr + 0xE85A8 + 3), (enable) ? newOff : off); // dmc3.exe+E85A8 - 48 8D 8E B01A0000 - LEA RCX,[RSI+00001AB0]
	// 	// Write<uint32>((appBaseAddr + 0xE86A7 + 3), (enable) ? newOff : off); // dmc3.exe+E86A7 - 48 81 C1 B01A0000 - ADD RCX,00001AB0
	// 	// Write<uint32>((appBaseAddr + 0xEA622 + 3), (enable) ? newOff : off); // dmc3.exe+EA622 - 48 8D 8E B01A0000 - LEA RCX,[RSI+00001AB0]
	// 	// Trash<uint32>((appBaseAddr + 0x15C80B + 3), (enable) ? newOff : off); // dmc3.exe+15C80B - 89 BE B01A0000 - MOV [RSI+00001AB0],EDI
	// 	// Trash<uint32>((appBaseAddr + 0x253D7A + 3), (enable) ? newOff : off); // dmc3.exe+253D7A - 0F29 B0 B01A0000 - MOVAPS [RAX+00001AB0],XMM6
	// 	// Trash<uint32>((appBaseAddr + 0x25983E + 3), (enable) ? newOff : off); // dmc3.exe+25983E - 0F11 80 B01A0000 - MOVUPS [RAX+00001AB0],XMM0
	// 	// Write<uint32>((appBaseAddr + 0x34857D + 3), (enable) ? newOff : off); // dmc3.exe+34857D - 48 81 C1 B01A0000 - ADD RCX,00001AB0
	// }
	// // 0x1AB8
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[2][23]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[2][23]);
		// static_assert(off == 0x1AB8);
	// 	// Trash<uint32>((appBaseAddr + 0x254252 + 3), (enable) ? newOff : off); // dmc3.exe+254252 - 44 8B 86 B81A0000 - MOV R8D,[RSI+00001AB8]
	// 	// Trash<uint32>((appBaseAddr + 0x25A206 + 3), (enable) ? newOff : off); // dmc3.exe+25A206 - 66 44 89 A8 B81A0000 - MOV [RAX+00001AB8],R13W
	// }








	
	




	// // 0x1AC8
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[3][1]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[3][1]);
	// 	static_assert(off == 0x1AC8);
	// 	// Trash<uint32>((appBaseAddr + 0xD0D04 + 3), (enable) ? newOff : off); // dmc3.exe+D0D04 - 89 AF C81A0000 - MOV [RDI+00001AC8],EBP
	// }
	// // 0x1AD0
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[3][2]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[3][2]);
	// 	static_assert(off == 0x1AD0);
	// 	// Mission19<uint32>((appBaseAddr + 0x15FF1D + 3), (enable) ? newOff : off); // dmc3.exe+15FF1D - 4C 8D 81 D01A0000 - LEA R8,[RCX+00001AD0]
	// 	// Mission19<uint32>((appBaseAddr + 0x1607DE + 3), (enable) ? newOff : off); // dmc3.exe+1607DE - 49 89 86 D01A0000 - MOV [R14+00001AD0],RAX
	// 	// Mission19<uint32>((appBaseAddr + 0x1609CC + 3), (enable) ? newOff : off); // dmc3.exe+1609CC - 4D 8B 86 D01A0000 - MOV R8,[R14+00001AD0]
	// 	// Mission19<uint32>((appBaseAddr + 0x160A36 + 3), (enable) ? newOff : off); // dmc3.exe+160A36 - 4D 8B 86 D01A0000 - MOV R8,[R14+00001AD0]
	// 	// Mission19<uint32>((appBaseAddr + 0x161DB8 + 3), (enable) ? newOff : off); // dmc3.exe+161DB8 - 4C 8D 87 D01A0000 - LEA R8,[RDI+00001AD0]
	// 	// Trash<uint32>((appBaseAddr + 0x161DF2 + 3), (enable) ? newOff : off); // dmc3.exe+161DF2 - 0F29 87 D01A0000 - MOVAPS [RDI+00001AD0],XMM0
	// 	// Trash<uint32>((appBaseAddr + 0x253DA4 + 3), (enable) ? newOff : off); // dmc3.exe+253DA4 - 44 0F29 80 D01A0000 - MOVAPS [RAX+00001AD0],XMM8
	// 	// Trash<uint32>((appBaseAddr + 0x25985A + 3), (enable) ? newOff : off); // dmc3.exe+25985A - 0F11 80 D01A0000 - MOVUPS [RAX+00001AD0],XMM0
	// }
	// // 0x1AD8
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[3][3]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[3][3]);
	// 	static_assert(off == 0x1AD8);
	// 	// Mission19<uint32>((appBaseAddr + 0x160813 + 3), (enable) ? newOff : off); // dmc3.exe+160813 - 49 89 86 D81A0000 - MOV [R14+00001AD8],RAX
	// 	// Mission19<uint32>((appBaseAddr + 0x1609D3 + 3), (enable) ? newOff : off); // dmc3.exe+1609D3 - 49 8B 96 D81A0000 - MOV RDX,[R14+00001AD8]
	// }
	// // 0x1AE0
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[3][4]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[3][4]);
	// 	static_assert(off == 0x1AE0);
	// 	// Trash<uint32>((appBaseAddr + 0xD0D0A + 3), (enable) ? newOff : off); // dmc3.exe+D0D0A - 89 AF E01A0000 - MOV [RDI+00001AE0],EBP
	// 	// Write<uint32>((appBaseAddr + 0xE85B5 + 3), (enable) ? newOff : off); // dmc3.exe+E85B5 - 48 8D 9E E01A0000 - LEA RBX,[RSI+00001AE0]
	// 	// Write<uint32>((appBaseAddr + 0xE86A0 + 3), (enable) ? newOff : off); // dmc3.exe+E86A0 - 48 89 81 E01A0000 - MOV [RCX+00001AE0],RAX
	// 	// Trash<uint32>((appBaseAddr + 0xE8B73 + 3), (enable) ? newOff : off); // dmc3.exe+E8B73 - C7 83 E01A0000 00007041 - MOV [RBX+00001AE0],41700000
	// 	// Trash<uint32>((appBaseAddr + 0xE9A20 + 3), (enable) ? newOff : off); // dmc3.exe+E9A20 - C7 81 E01A0000 00002041 - MOV [RCX+00001AE0],41200000
	// 	// Write<uint32>((appBaseAddr + 0xEA4E9 + 3), (enable) ? newOff : off); // dmc3.exe+EA4E9 - 48 8D 8E E01A0000 - LEA RCX,[RSI+00001AE0]
	// 	// Write<uint32>((appBaseAddr + 0x15FD8A + 3), (enable) ? newOff : off); // dmc3.exe+15FD8A - 48 8B 81 E01A0000 - MOV RAX,[RCX+00001AE0]
	// 	// Write<uint32>((appBaseAddr + 0x15FDAA + 3), (enable) ? newOff : off); // dmc3.exe+15FDAA - 48 89 B9 E01A0000 - MOV [RCX+00001AE0],RDI
	// 	// Write<uint32>((appBaseAddr + 0x15FDB1 + 3), (enable) ? newOff : off); // dmc3.exe+15FDB1 - 48 8B 89 E01A0000 - MOV RCX,[RCX+00001AE0]
	// 	// Write<uint32>((appBaseAddr + 0x15FDC2 + 3), (enable) ? newOff : off); // dmc3.exe+15FDC2 - 48 89 BB E01A0000 - MOV [RBX+00001AE0],RDI
	// 	// Write<uint32>((appBaseAddr + 0x15FE4A + 3), (enable) ? newOff : off); // dmc3.exe+15FE4A - 48 8B 81 E01A0000 - MOV RAX,[RCX+00001AE0]
	// 	// Write<uint32>((appBaseAddr + 0x15FE6A + 3), (enable) ? newOff : off); // dmc3.exe+15FE6A - 48 89 B9 E01A0000 - MOV [RCX+00001AE0],RDI
	// 	// Write<uint32>((appBaseAddr + 0x15FE71 + 3), (enable) ? newOff : off); // dmc3.exe+15FE71 - 48 39 B9 E01A0000 - CMP [RCX+00001AE0],RDI
	// 	// Write<uint32>((appBaseAddr + 0x15FE91 + 3), (enable) ? newOff : off); // dmc3.exe+15FE91 - 48 89 83 E01A0000 - MOV [RBX+00001AE0],RAX
	// 	// Write<uint32>((appBaseAddr + 0x15FEBC + 3), (enable) ? newOff : off); // dmc3.exe+15FEBC - 48 8B 83 E01A0000 - MOV RAX,[RBX+00001AE0]
	// 	// Mission19<uint32>((appBaseAddr + 0x15FFBE + 3), (enable) ? newOff : off); // dmc3.exe+15FFBE - 4C 8D 87 E01A0000 - LEA R8,[RDI+00001AE0]
	// 	// Mission19<uint32>((appBaseAddr + 0x160848 + 3), (enable) ? newOff : off); // dmc3.exe+160848 - 49 89 86 E01A0000 - MOV [R14+00001AE0],RAX
	// 	// Mission19<uint32>((appBaseAddr + 0x160A3D + 3), (enable) ? newOff : off); // dmc3.exe+160A3D - 49 8B 96 E01A0000 - MOV RDX,[R14+00001AE0]
	// 	// Mission19<uint32>((appBaseAddr + 0x161E28 + 3), (enable) ? newOff : off); // dmc3.exe+161E28 - 4C 8D 87 E01A0000 - LEA R8,[RDI+00001AE0]
	// 	// Trash<uint32>((appBaseAddr + 0x253DAC + 3), (enable) ? newOff : off); // dmc3.exe+253DAC - 0F29 B8 E01A0000 - MOVAPS [RAX+00001AE0],XMM7
	// 	// Trash<uint32>((appBaseAddr + 0x25899D + 3), (enable) ? newOff : off); // dmc3.exe+25899D - 66 89 BB E01A0000 - MOV [RBX+00001AE0],DI
	// 	// Trash<uint32>((appBaseAddr + 0x25ACCD + 3), (enable) ? newOff : off); // dmc3.exe+25ACCD - 0FB7 81 E01A0000 - MOVZX EAX,WORD PTR [RCX+00001AE0]
	// 	// Trash<uint32>((appBaseAddr + 0x25AE4B + 3), (enable) ? newOff : off); // dmc3.exe+25AE4B - 0FB7 81 E01A0000 - MOVZX EAX,WORD PTR [RCX+00001AE0]
	// }
	// // 0x1AE8
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[3][5]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[3][5]);
	// 	static_assert(off == 0x1AE8);
	// 	// Trash<uint32>((appBaseAddr + 0x15F480 + 3), (enable) ? newOff : off); // dmc3.exe+15F480 - 8B 89 E81A0000 - MOV ECX,[RCX+00001AE8]
	// 	// Mission19<uint32>((appBaseAddr + 0x16087D + 3), (enable) ? newOff : off); // dmc3.exe+16087D - 49 8D B6 E81A0000 - LEA RSI,[R14+00001AE8]
	// }
	// // 0x1AF0
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[3][6]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[3][6]);
	// 	static_assert(off == 0x1AF0);
	// 	// Write<uint32>((appBaseAddr + 0x15D97B + 3), (enable) ? newOff : off); // dmc3.exe+15D97B - 4C 8D 86 F01A0000 - LEA R8,[RSI+00001AF0]
	// 	// Mission19<uint32>((appBaseAddr + 0x15FF4A + 3), (enable) ? newOff : off); // dmc3.exe+15FF4A - 48 8D 99 F01A0000 - LEA RBX,[RCX+00001AF0]
	// 	// Mission19<uint32>((appBaseAddr + 0x1608BC + 3), (enable) ? newOff : off); // dmc3.exe+1608BC - 4D 8D A6 F01A0000 - LEA R12,[R14+00001AF0]
	// 	// Mission19<uint32>((appBaseAddr + 0x161DB1 + 3), (enable) ? newOff : off); // dmc3.exe+161DB1 - 48 8D 9F F01A0000 - LEA RBX,[RDI+00001AF0]
	// 	// Mission19<uint32>((appBaseAddr + 0x161E44 + 3), (enable) ? newOff : off); // dmc3.exe+161E44 - 48 8D 97 F01A0000 - LEA RDX,[RDI+00001AF0]
	// 	// Mission19<uint32>((appBaseAddr + 0x161E5E + 3), (enable) ? newOff : off); // dmc3.exe+161E5E - 48 8D 97 F01A0000 - LEA RDX,[RDI+00001AF0]
	// 	// Mission19<uint32>((appBaseAddr + 0x162B28 + 3), (enable) ? newOff : off); // dmc3.exe+162B28 - 48 8D 91 F01A0000 - LEA RDX,[RCX+00001AF0]
	// 	// Trash<uint32>((appBaseAddr + 0x253DB3 + 3), (enable) ? newOff : off); // dmc3.exe+253DB3 - 0F29 B0 F01A0000 - MOVAPS [RAX+00001AF0],XMM6
	// }
	// // 0x1AF8
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[3][7]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[3][7]);
	// 	static_assert(off == 0x1AF8);
	// 	// Trash<uint32>((appBaseAddr + 0xC8587 + 3), (enable) ? newOff : off); // dmc3.exe+C8587 - F3 0F10 84 B7 F81A0000 - MOVSS XMM0,[RDI+RSI*4+00001AF8]
	// 	// Trash<uint32>((appBaseAddr + 0xC859F + 3), (enable) ? newOff : off); // dmc3.exe+C859F - F3 0F11 84 B7 F81A0000 - MOVSS [RDI+RSI*4+00001AF8],XMM0
	// 	// Write<uint32>((appBaseAddr + 0xC9584 + 3), (enable) ? newOff : off); // dmc3.exe+C9584 - 48 8D B7 F81A0000 - LEA RSI,[RDI+00001AF8]
	// 	// Trash<uint32>((appBaseAddr + 0xC9AC3 + 3), (enable) ? newOff : off); // dmc3.exe+C9AC3 - F3 42 0F10 84 AE F81A0000 - MOVSS XMM0,[RSI+R13*4+00001AF8]
	// 	// Trash<uint32>((appBaseAddr + 0xC9AE2 + 3), (enable) ? newOff : off); // dmc3.exe+C9AE2 - F3 42 0F11 84 AE F81A0000 - MOVSS [RSI+R13*4+00001AF8],XMM0
	// 	// Mission19<uint32>((appBaseAddr + 0x1608FC + 3), (enable) ? newOff : off); // dmc3.exe+1608FC - 49 89 86 F81A0000 - MOV [R14+00001AF8],RAX
	// }
	// // 0x1B00
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[3][8]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[3][8]);
	// 	static_assert(off == 0x1B00);
	// 	// Trash<uint32>((appBaseAddr + 0xCC3A3 + 3), (enable) ? newOff : off); // dmc3.exe+CC3A3 - C7 83 001B0000 02000000 - MOV [RBX+00001B00],00000002
	// 	// Write<uint32>((appBaseAddr + 0xCC3BA + 3), (enable) ? newOff : off); // dmc3.exe+CC3BA - 48 89 83 001B0000 - MOV [RBX+00001B00],RAX
	// 	// Trash<uint32>((appBaseAddr + 0xCC538 + 3), (enable) ? newOff : off); // dmc3.exe+CC538 - C7 83 001B0000 02000000 - MOV [RBX+00001B00],00000002
	// 	// Write<uint32>((appBaseAddr + 0xCC54E + 3), (enable) ? newOff : off); // dmc3.exe+CC54E - 48 C7 83 001B0000 00000000 - MOV QWORD PTR [RBX+00001B00],00000000
	// 	// Trash<uint32>((appBaseAddr + 0xCC7F2 + 3), (enable) ? newOff : off); // dmc3.exe+CC7F2 - C7 82 001B0000 02000000 - MOV [RDX+00001B00],00000002
	// 	// Write<uint32>((appBaseAddr + 0xCC80A + 3), (enable) ? newOff : off); // dmc3.exe+CC80A - 48 89 82 001B0000 - MOV [RDX+00001B00],RAX
	// 	// Trash<uint32>((appBaseAddr + 0xCC878 + 3), (enable) ? newOff : off); // dmc3.exe+CC878 - C7 83 001B0000 02000000 - MOV [RBX+00001B00],00000002
	// 	// Write<uint32>((appBaseAddr + 0xCC88E + 3), (enable) ? newOff : off); // dmc3.exe+CC88E - 48 C7 83 001B0000 00000000 - MOV QWORD PTR [RBX+00001B00],00000000
	// 	// Trash<uint32>((appBaseAddr + 0xCCA37 + 3), (enable) ? newOff : off); // dmc3.exe+CCA37 - C7 86 001B0000 02000000 - MOV [RSI+00001B00],00000002
	// 	// Write<uint32>((appBaseAddr + 0xCCA4F + 3), (enable) ? newOff : off); // dmc3.exe+CCA4F - 48 89 86 001B0000 - MOV [RSI+00001B00],RAX
	// 	// Trash<uint32>((appBaseAddr + 0xCCC69 + 3), (enable) ? newOff : off); // dmc3.exe+CCC69 - C7 83 001B0000 02000000 - MOV [RBX+00001B00],00000002
	// 	// Write<uint32>((appBaseAddr + 0xCCC7F + 3), (enable) ? newOff : off); // dmc3.exe+CCC7F - 48 C7 83 001B0000 00000000 - MOV QWORD PTR [RBX+00001B00],00000000
	// 	// Trash<uint32>((appBaseAddr + 0xCCE91 + 3), (enable) ? newOff : off); // dmc3.exe+CCE91 - C7 83 001B0000 02000000 - MOV [RBX+00001B00],00000002
	// 	// Write<uint32>((appBaseAddr + 0xCCEA7 + 3), (enable) ? newOff : off); // dmc3.exe+CCEA7 - 48 C7 83 001B0000 00000000 - MOV QWORD PTR [RBX+00001B00],00000000
	// 	// Trash<uint32>((appBaseAddr + 0xCCFD8 + 3), (enable) ? newOff : off); // dmc3.exe+CCFD8 - C7 83 001B0000 02000000 - MOV [RBX+00001B00],00000002
	// 	// Write<uint32>((appBaseAddr + 0xCCFF0 + 3), (enable) ? newOff : off); // dmc3.exe+CCFF0 - 48 89 83 001B0000 - MOV [RBX+00001B00],RAX
	// 	// Trash<uint32>((appBaseAddr + 0xCD168 + 3), (enable) ? newOff : off); // dmc3.exe+CD168 - C7 83 001B0000 02000000 - MOV [RBX+00001B00],00000002
	// 	// Write<uint32>((appBaseAddr + 0xCD17E + 3), (enable) ? newOff : off); // dmc3.exe+CD17E - 48 89 B3 001B0000 - MOV [RBX+00001B00],RSI
	// 	// Trash<uint32>((appBaseAddr + 0xCD2C7 + 3), (enable) ? newOff : off); // dmc3.exe+CD2C7 - C7 83 001B0000 02000000 - MOV [RBX+00001B00],00000002
	// 	// Write<uint32>((appBaseAddr + 0xCD2DD + 3), (enable) ? newOff : off); // dmc3.exe+CD2DD - 48 C7 83 001B0000 00000000 - MOV QWORD PTR [RBX+00001B00],00000000
	// 	// Trash<uint32>((appBaseAddr + 0xCD463 + 3), (enable) ? newOff : off); // dmc3.exe+CD463 - C7 83 001B0000 02000000 - MOV [RBX+00001B00],00000002
	// 	// Write<uint32>((appBaseAddr + 0xCD47B + 3), (enable) ? newOff : off); // dmc3.exe+CD47B - 48 89 83 001B0000 - MOV [RBX+00001B00],RAX
	// 	// Trash<uint32>((appBaseAddr + 0xCDB4C + 3), (enable) ? newOff : off); // dmc3.exe+CDB4C - C7 87 001B0000 02000000 - MOV [RDI+00001B00],00000002
	// 	// Write<uint32>((appBaseAddr + 0xCDB62 + 3), (enable) ? newOff : off); // dmc3.exe+CDB62 - 48 C7 87 001B0000 00000000 - MOV QWORD PTR [RDI+00001B00],00000000
	// 	// Trash<uint32>((appBaseAddr + 0xCDBFE + 3), (enable) ? newOff : off); // dmc3.exe+CDBFE - C7 83 001B0000 02000000 - MOV [RBX+00001B00],00000002
	// 	// Write<uint32>((appBaseAddr + 0xCDC14 + 3), (enable) ? newOff : off); // dmc3.exe+CDC14 - 48 89 BB 001B0000 - MOV [RBX+00001B00],RDI
	// 	// Trash<uint32>((appBaseAddr + 0xCDE67 + 3), (enable) ? newOff : off); // dmc3.exe+CDE67 - C7 83 001B0000 02000000 - MOV [RBX+00001B00],00000002
	// 	// Write<uint32>((appBaseAddr + 0xCDE7D + 3), (enable) ? newOff : off); // dmc3.exe+CDE7D - 48 C7 83 001B0000 00000000 - MOV QWORD PTR [RBX+00001B00],00000000
	// 	// Trash<uint32>((appBaseAddr + 0xCDFE8 + 3), (enable) ? newOff : off); // dmc3.exe+CDFE8 - C7 83 001B0000 02000000 - MOV [RBX+00001B00],00000002
	// 	// Write<uint32>((appBaseAddr + 0xCDFFE + 3), (enable) ? newOff : off); // dmc3.exe+CDFFE - 48 C7 83 001B0000 00000000 - MOV QWORD PTR [RBX+00001B00],00000000
	// 	// Trash<uint32>((appBaseAddr + 0xCE0E7 + 3), (enable) ? newOff : off); // dmc3.exe+CE0E7 - C7 83 001B0000 02000000 - MOV [RBX+00001B00],00000002
	// 	// Write<uint32>((appBaseAddr + 0xCE0FD + 3), (enable) ? newOff : off); // dmc3.exe+CE0FD - 48 C7 83 001B0000 00000000 - MOV QWORD PTR [RBX+00001B00],00000000
	// 	// Trash<uint32>((appBaseAddr + 0xCE287 + 3), (enable) ? newOff : off); // dmc3.exe+CE287 - C7 83 001B0000 02000000 - MOV [RBX+00001B00],00000002
	// 	// Write<uint32>((appBaseAddr + 0xCE29D + 3), (enable) ? newOff : off); // dmc3.exe+CE29D - 48 C7 83 001B0000 00000000 - MOV QWORD PTR [RBX+00001B00],00000000
	// 	// Trash<uint32>((appBaseAddr + 0xCE417 + 3), (enable) ? newOff : off); // dmc3.exe+CE417 - C7 83 001B0000 02000000 - MOV [RBX+00001B00],00000002
	// 	// Write<uint32>((appBaseAddr + 0xCE42D + 3), (enable) ? newOff : off); // dmc3.exe+CE42D - 48 C7 83 001B0000 00000000 - MOV QWORD PTR [RBX+00001B00],00000000
	// 	// Trash<uint32>((appBaseAddr + 0xCE597 + 3), (enable) ? newOff : off); // dmc3.exe+CE597 - C7 83 001B0000 02000000 - MOV [RBX+00001B00],00000002
	// 	// Write<uint32>((appBaseAddr + 0xCE5AD + 3), (enable) ? newOff : off); // dmc3.exe+CE5AD - 48 C7 83 001B0000 00000000 - MOV QWORD PTR [RBX+00001B00],00000000
	// 	// Trash<uint32>((appBaseAddr + 0xCE708 + 3), (enable) ? newOff : off); // dmc3.exe+CE708 - C7 83 001B0000 02000000 - MOV [RBX+00001B00],00000002
	// 	// Write<uint32>((appBaseAddr + 0xCE71E + 3), (enable) ? newOff : off); // dmc3.exe+CE71E - 48 C7 83 001B0000 00000000 - MOV QWORD PTR [RBX+00001B00],00000000
	// 	// Trash<uint32>((appBaseAddr + 0xCE848 + 3), (enable) ? newOff : off); // dmc3.exe+CE848 - C7 83 001B0000 02000000 - MOV [RBX+00001B00],00000002
	// 	// Write<uint32>((appBaseAddr + 0xCE860 + 3), (enable) ? newOff : off); // dmc3.exe+CE860 - 48 89 83 001B0000 - MOV [RBX+00001B00],RAX
	// 	// Trash<uint32>((appBaseAddr + 0xCE958 + 3), (enable) ? newOff : off); // dmc3.exe+CE958 - C7 87 001B0000 02000000 - MOV [RDI+00001B00],00000002
	// 	// Write<uint32>((appBaseAddr + 0xCE970 + 3), (enable) ? newOff : off); // dmc3.exe+CE970 - 48 89 87 001B0000 - MOV [RDI+00001B00],RAX
	// 	// Trash<uint32>((appBaseAddr + 0xCEE07 + 3), (enable) ? newOff : off); // dmc3.exe+CEE07 - C7 83 001B0000 02000000 - MOV [RBX+00001B00],00000002
	// 	// Write<uint32>((appBaseAddr + 0xCEE1D + 3), (enable) ? newOff : off); // dmc3.exe+CEE1D - 48 C7 83 001B0000 00000000 - MOV QWORD PTR [RBX+00001B00],00000000
	// 	// Trash<uint32>((appBaseAddr + 0xCEF68 + 3), (enable) ? newOff : off); // dmc3.exe+CEF68 - C7 83 001B0000 02000000 - MOV [RBX+00001B00],00000002
	// 	// Write<uint32>((appBaseAddr + 0xCEF80 + 3), (enable) ? newOff : off); // dmc3.exe+CEF80 - 48 89 83 001B0000 - MOV [RBX+00001B00],RAX
	// 	// Trash<uint32>((appBaseAddr + 0xCF0C8 + 3), (enable) ? newOff : off); // dmc3.exe+CF0C8 - C7 83 001B0000 02000000 - MOV [RBX+00001B00],00000002
	// 	// Write<uint32>((appBaseAddr + 0xCF0E0 + 3), (enable) ? newOff : off); // dmc3.exe+CF0E0 - 48 89 83 001B0000 - MOV [RBX+00001B00],RAX
	// 	// Trash<uint32>((appBaseAddr + 0xCF30B + 3), (enable) ? newOff : off); // dmc3.exe+CF30B - C7 83 001B0000 02000000 - MOV [RBX+00001B00],00000002
	// 	// Write<uint32>((appBaseAddr + 0xCF321 + 3), (enable) ? newOff : off); // dmc3.exe+CF321 - 48 C7 83 001B0000 00000000 - MOV QWORD PTR [RBX+00001B00],00000000
	// 	// Trash<uint32>((appBaseAddr + 0xCF406 + 3), (enable) ? newOff : off); // dmc3.exe+CF406 - 89 BB 001B0000 - MOV [RBX+00001B00],EDI
	// 	// Write<uint32>((appBaseAddr + 0xCF414 + 3), (enable) ? newOff : off); // dmc3.exe+CF414 - 48 89 B3 001B0000 - MOV [RBX+00001B00],RSI
	// 	// Trash<uint32>((appBaseAddr + 0xCF710 + 3), (enable) ? newOff : off); // dmc3.exe+CF710 - 89 BB 001B0000 - MOV [RBX+00001B00],EDI
	// 	// Write<uint32>((appBaseAddr + 0xCF71E + 3), (enable) ? newOff : off); // dmc3.exe+CF71E - 48 89 93 001B0000 - MOV [RBX+00001B00],RDX
	// 	// Trash<uint32>((appBaseAddr + 0xCFF03 + 3), (enable) ? newOff : off); // dmc3.exe+CFF03 - C7 87 001B0000 02000000 - MOV [RDI+00001B00],00000002
	// 	// Write<uint32>((appBaseAddr + 0xCFF19 + 3), (enable) ? newOff : off); // dmc3.exe+CFF19 - 48 89 AF 001B0000 - MOV [RDI+00001B00],RBP
	// 	// Trash<uint32>((appBaseAddr + 0xD02A8 + 3), (enable) ? newOff : off); // dmc3.exe+D02A8 - C7 86 001B0000 02000000 - MOV [RSI+00001B00],00000002
	// 	// Write<uint32>((appBaseAddr + 0xD02BE + 3), (enable) ? newOff : off); // dmc3.exe+D02BE - 48 89 96 001B0000 - MOV [RSI+00001B00],RDX
	// 	// Trash<uint32>((appBaseAddr + 0xD05A8 + 3), (enable) ? newOff : off); // dmc3.exe+D05A8 - C7 87 001B0000 02000000 - MOV [RDI+00001B00],00000002
	// 	// Write<uint32>((appBaseAddr + 0xD05BE + 3), (enable) ? newOff : off); // dmc3.exe+D05BE - 48 89 97 001B0000 - MOV [RDI+00001B00],RDX
	// 	// Trash<uint32>((appBaseAddr + 0xD08F8 + 3), (enable) ? newOff : off); // dmc3.exe+D08F8 - C7 87 001B0000 02000000 - MOV [RDI+00001B00],00000002
	// 	// Write<uint32>((appBaseAddr + 0xD0910 + 3), (enable) ? newOff : off); // dmc3.exe+D0910 - 48 89 87 001B0000 - MOV [RDI+00001B00],RAX
	// 	// Trash<uint32>((appBaseAddr + 0xD0AC8 + 3), (enable) ? newOff : off); // dmc3.exe+D0AC8 - C7 83 001B0000 02000000 - MOV [RBX+00001B00],00000002
	// 	// Write<uint32>((appBaseAddr + 0xD0AE0 + 3), (enable) ? newOff : off); // dmc3.exe+D0AE0 - 48 89 83 001B0000 - MOV [RBX+00001B00],RAX
	// 	// Trash<uint32>((appBaseAddr + 0xD327E + 3), (enable) ? newOff : off); // dmc3.exe+D327E - C7 81 001B0000 02000000 - MOV [RCX+00001B00],00000002
	// 	// Write<uint32>((appBaseAddr + 0xD3295 + 3), (enable) ? newOff : off); // dmc3.exe+D3295 - 48 89 81 001B0000 - MOV [RCX+00001B00],RAX
	// 	// Trash<uint32>((appBaseAddr + 0xE0575 + 3), (enable) ? newOff : off); // dmc3.exe+E0575 - 48 B8 1B0000001B000000 - MOV RAX,0000001B0000001B
	// 	// Mission19<uint32>((appBaseAddr + 0x160A99 + 3), (enable) ? newOff : off); // dmc3.exe+160A99 - 49 8D 96 001B0000 - LEA RDX,[R14+00001B00]
	// 	// Trash<uint32>((appBaseAddr + 0x2544CB + 3), (enable) ? newOff : off); // dmc3.exe+2544CB - 0FB6 8D 001B0000 - MOVZX ECX,BYTE PTR [RBP+00001B00]
	// 	// Trash<uint32>((appBaseAddr + 0x254AE0 + 3), (enable) ? newOff : off); // dmc3.exe+254AE0 - C6 87 001B0000 01 - MOV BYTE PTR [RDI+00001B00],01
	// 	// Trash<uint32>((appBaseAddr + 0x258AB9 + 3), (enable) ? newOff : off); // dmc3.exe+258AB9 - BA 001B0000 - MOV EDX,00001B00
	// 	// Trash<uint32>((appBaseAddr + 0x2591C4 + 3), (enable) ? newOff : off); // dmc3.exe+2591C4 - BA 001B0000 - MOV EDX,00001B00
	// 	// Trash<uint32>((appBaseAddr + 0x3836E3 + 3), (enable) ? newOff : off); // dmc3.exe+3836E3 - 80 AC 01 00001B00 00 - SUB BYTE PTR [RCX+RAX+001B0000],00
	// 	// Trash<uint32>((appBaseAddr + 0x38EE3B + 3), (enable) ? newOff : off); // dmc3.exe+38EE3B - 80 9C 00 00001B00 00 - SBB BYTE PTR [RAX+RAX+001B0000],00
	// 	// Trash<uint32>((appBaseAddr + 0x38EE43 + 3), (enable) ? newOff : off); // dmc3.exe+38EE43 - 00 BC 00 00001B00 - ADD [RAX+RAX+001B0000],BH
	// 	// Trash<uint32>((appBaseAddr + 0x39DFA7 + 3), (enable) ? newOff : off); // dmc3.exe+39DFA7 - 80 9C 00 00001B00 00 - SBB BYTE PTR [RAX+RAX+001B0000],00
	// 	// Trash<uint32>((appBaseAddr + 0x39DFAF + 3), (enable) ? newOff : off); // dmc3.exe+39DFAF - 00 BC 00 00001B00 - ADD [RAX+RAX+001B0000],BH
	// 	// Trash<uint32>((appBaseAddr + 0x3A1C67 + 3), (enable) ? newOff : off); // dmc3.exe+3A1C67 - 80 9C 00 00001B00 00 - SBB BYTE PTR [RAX+RAX+001B0000],00
	// 	// Trash<uint32>((appBaseAddr + 0x3A1C6F + 3), (enable) ? newOff : off); // dmc3.exe+3A1C6F - 00 BC 00 00001B00 - ADD [RAX+RAX+001B0000],BH
	// 	// Trash<uint32>((appBaseAddr + 0x3ADBEF + 3), (enable) ? newOff : off); // dmc3.exe+3ADBEF - 80 A4 00 00001B00 00 - AND BYTE PTR [RAX+RAX+001B0000],00
	// 	// Trash<uint32>((appBaseAddr + 0x3ADCCF + 3), (enable) ? newOff : off); // dmc3.exe+3ADCCF - 80 94 01 00001B00 00 - ADC BYTE PTR [RCX+RAX+001B0000],00
	// 	// Trash<uint32>((appBaseAddr + 0x3ADCEF + 3), (enable) ? newOff : off); // dmc3.exe+3ADCEF - 80 AC 01 00001B00 00 - SUB BYTE PTR [RCX+RAX+001B0000],00
	// 	// Trash<uint32>((appBaseAddr + 0x3ADDEF + 3), (enable) ? newOff : off); // dmc3.exe+3ADDEF - 80 9C 02 00001B00 00 - SBB BYTE PTR [RDX+RAX+001B0000],00
	// 	// Trash<uint32>((appBaseAddr + 0x3ADEF8 + 3), (enable) ? newOff : off); // dmc3.exe+3ADEF8 - A0 0300001B000080A0 - MOV AL,[A08000001B000003]
	// 	// Trash<uint32>((appBaseAddr + 0x3ADF07 + 3), (enable) ? newOff : off); // dmc3.exe+3ADF07 - 00 A4 03 00001B00 - ADD [RBX+RAX+001B0000],AH
	// 	// Trash<uint32>((appBaseAddr + 0x3ADF2F + 3), (enable) ? newOff : off); // dmc3.exe+3ADF2F - 80 BC 03 00001B00 00 - CMP BYTE PTR [RBX+RAX+001B0000],00
	// 	// Trash<uint32>((appBaseAddr + 0x3C3C9B + 3), (enable) ? newOff : off); // dmc3.exe+3C3C9B - 80 94 01 00001B00 00 - ADC BYTE PTR [RCX+RAX+001B0000],00
	// 	// Trash<uint32>((appBaseAddr + 0x3D7603 + 3), (enable) ? newOff : off); // dmc3.exe+3D7603 - 80 94 02 00001B00 00 - ADC BYTE PTR [RDX+RAX+001B0000],00
	// 	// Trash<uint32>((appBaseAddr + 0x3F0123 + 3), (enable) ? newOff : off); // dmc3.exe+3F0123 - 80 AC 01 00001B00 00 - SUB BYTE PTR [RCX+RAX+001B0000],00
	// 	// Trash<uint32>((appBaseAddr + 0x40B2C7 + 3), (enable) ? newOff : off); // dmc3.exe+40B2C7 - 80 9C 00 00001B00 00 - SBB BYTE PTR [RAX+RAX+001B0000],00
	// 	// Trash<uint32>((appBaseAddr + 0x41D10F + 3), (enable) ? newOff : off); // dmc3.exe+41D10F - 00 8C 01 00001B00 - ADD [RCX+RAX+001B0000],CL
	// 	// Trash<uint32>((appBaseAddr + 0x447F78 + 3), (enable) ? newOff : off); // dmc3.exe+447F78 - 38 05 00001B00 - CMP [005F737E],AL
	// 	// Trash<uint32>((appBaseAddr + 0x4B2623 + 3), (enable) ? newOff : off); // dmc3.exe+4B2623 - 80 AC 00 00001B00 00 - SUB BYTE PTR [RAX+RAX+001B0000],00
	// 	// Trash<uint32>((appBaseAddr + 0x527C6C + 3), (enable) ? newOff : off); // dmc3.exe+527C6C - 81 79 34 001B0000 - CMP [RCX+34],00001B00
	// }
	// // 0x1B08
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[3][9]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[3][9]);
	// 	static_assert(off == 0x1B08);
	// 	// Trash<uint32>((appBaseAddr + 0xCF64A + 3), (enable) ? newOff : off); // dmc3.exe+CF64A - 83 BB 081B0000 1F - CMP DWORD PTR [RBX+00001B08],1F
	// 	// Trash<uint32>((appBaseAddr + 0xD01D4 + 3), (enable) ? newOff : off); // dmc3.exe+D01D4 - 83 BF 081B0000 1F - CMP DWORD PTR [RDI+00001B08],1F
	// 	// Trash<uint32>((appBaseAddr + 0x253DCE + 3), (enable) ? newOff : off); // dmc3.exe+253DCE - 89 88 081B0000 - MOV [RAX+00001B08],ECX
	// 	// Trash<uint32>((appBaseAddr + 0x254555 + 3), (enable) ? newOff : off); // dmc3.exe+254555 - 44 8B 85 081B0000 - MOV R8D,[RBP+00001B08]
	// }
	// // 0x1B10
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[3][10]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[3][10]);
	// 	static_assert(off == 0x1B10);
	// 	// Trash<uint32>((appBaseAddr + 0x253DE8 + 3), (enable) ? newOff : off); // dmc3.exe+253DE8 - 89 88 101B0000 - MOV [RAX+00001B10],ECX
	// 	// Trash<uint32>((appBaseAddr + 0x25453E + 3), (enable) ? newOff : off); // dmc3.exe+25453E - 66 0F6E 85 101B0000 - MOVD XMM0,[RBP+00001B10]
	// }
	// // 0x1B18
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[3][11]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[3][11]);
	// 	static_assert(off == 0x1B18);
	// 	// Trash<uint32>((appBaseAddr + 0x253E02 + 3), (enable) ? newOff : off); // dmc3.exe+253E02 - 89 88 181B0000 - MOV [RAX+00001B18],ECX
	// 	// Trash<uint32>((appBaseAddr + 0x2545A4 + 3), (enable) ? newOff : off); // dmc3.exe+2545A4 - 44 8B 85 181B0000 - MOV R8D,[RBP+00001B18]
	// }
	// // 0x1B20
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[3][12]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[3][12]);
	// 	static_assert(off == 0x1B20);
	// 	// Trash<uint32>((appBaseAddr + 0x253E1C + 3), (enable) ? newOff : off); // dmc3.exe+253E1C - 89 88 201B0000 - MOV [RAX+00001B20],ECX
	// 	// Trash<uint32>((appBaseAddr + 0x254586 + 3), (enable) ? newOff : off); // dmc3.exe+254586 - 66 0F6E 85 201B0000 - MOVD XMM0,[RBP+00001B20]
	// }
	// // 0x1B28
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[3][13]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[3][13]);
	// 	static_assert(off == 0x1B28);
	// 	// Trash<uint32>((appBaseAddr + 0x2538CD + 3), (enable) ? newOff : off); // dmc3.exe+2538CD - 89 83 281B0000 - MOV [RBX+00001B28],EAX
	// 	// Trash<uint32>((appBaseAddr + 0x253A4D + 3), (enable) ? newOff : off); // dmc3.exe+253A4D - 44 01 81 281B0000 - ADD [RCX+00001B28],R8D
	// 	// Trash<uint32>((appBaseAddr + 0x254655 + 3), (enable) ? newOff : off); // dmc3.exe+254655 - C7 85 281B0000 00000000 - MOV [RBP+00001B28],00000000
	// 	// Trash<uint32>((appBaseAddr + 0x254A30 + 3), (enable) ? newOff : off); // dmc3.exe+254A30 - 8B 81 281B0000 - MOV EAX,[RCX+00001B28]
	// }
	// // 0x1B30
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[3][14]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[3][14]);
	// 	static_assert(off == 0x1B30);
	// 	// Empty
	// }
	// // 0x1B38
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[3][15]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[3][15]);
	// 	static_assert(off == 0x1B38);
	// 	// Empty
	// }
	// // 0x1B40
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[3][16]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[3][16]);
	// 	static_assert(off == 0x1B40);
	// 	// Trash<uint32>((appBaseAddr + 0xCC0E9 + 3), (enable) ? newOff : off); // dmc3.exe+CC0E9 - BA 401B0000 - MOV EDX,00001B40
	// 	// Trash<uint32>((appBaseAddr + 0xD1A8B + 3), (enable) ? newOff : off); // dmc3.exe+D1A8B - BA 401B0000 - MOV EDX,00001B40
	// 	// Mission3<uint32>((appBaseAddr + 0x1A3BAB + 3), (enable) ? newOff : off); // dmc3.exe+1A3BAB - 48 8D 99 401B0000 - LEA RBX,[RCX+00001B40]
	// 	// Mission3<uint32>((appBaseAddr + 0x1A3F60 + 3), (enable) ? newOff : off); // dmc3.exe+1A3F60 - 48 8D 95 401B0000 - LEA RDX,[RBP+00001B40]
	// }
	// // 0x1B48
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[3][17]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[3][17]);
	// 	static_assert(off == 0x1B48);
	// 	// Write<uint32>((appBaseAddr + 0x15D8E7 + 3), (enable) ? newOff : off); // dmc3.exe+15D8E7 - 48 8B 86 481B0000 - MOV RAX,[RSI+00001B48]
	// }
	// // 0x1B50
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[3][18]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[3][18]);
	// 	static_assert(off == 0x1B50);
	// 	// Write<uint32>((appBaseAddr + 0xEA209 + 3), (enable) ? newOff : off); // dmc3.exe+EA209 - 48 89 86 501B0000 - MOV [RSI+00001B50],RAX
	// 	// Write<uint32>((appBaseAddr + 0xEA31B + 3), (enable) ? newOff : off); // dmc3.exe+EA31B - 48 8B 86 501B0000 - MOV RAX,[RSI+00001B50]
	// 	// Write<uint32>((appBaseAddr + 0x15D907 + 3), (enable) ? newOff : off); // dmc3.exe+15D907 - 48 8B 86 501B0000 - MOV RAX,[RSI+00001B50]
	// }
	// // 0x1B58
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[3][19]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[3][19]);
	// 	static_assert(off == 0x1B58);
	// 	// Write<uint32>((appBaseAddr + 0xE85E7 + 3), (enable) ? newOff : off); // dmc3.exe+E85E7 - 48 89 BE 581B0000 - MOV [RSI+00001B58],RDI
	// 	// Write<uint32>((appBaseAddr + 0xE91EF + 3), (enable) ? newOff : off); // dmc3.exe+E91EF - 48 8B 81 581B0000 - MOV RAX,[RCX+00001B58]
	// 	// Write<uint32>((appBaseAddr + 0xE920A + 3), (enable) ? newOff : off); // dmc3.exe+E920A - 48 89 A9 581B0000 - MOV [RCX+00001B58],RBP
	// 	// Write<uint32>((appBaseAddr + 0xE9CA0 + 3), (enable) ? newOff : off); // dmc3.exe+E9CA0 - 48 8B 81 581B0000 - MOV RAX,[RCX+00001B58]
	// 	// Write<uint32>((appBaseAddr + 0xE9CBD + 3), (enable) ? newOff : off); // dmc3.exe+E9CBD - 48 89 91 581B0000 - MOV [RCX+00001B58],RDX
	// 	// Write<uint32>((appBaseAddr + 0xEA56C + 3), (enable) ? newOff : off); // dmc3.exe+EA56C - 48 89 86 581B0000 - MOV [RSI+00001B58],RAX
	// 	// Write<uint32>((appBaseAddr + 0xEA87F + 3), (enable) ? newOff : off); // dmc3.exe+EA87F - 48 89 83 581B0000 - MOV [RBX+00001B58],RAX
	// 	// Write<uint32>((appBaseAddr + 0xEBD28 + 3), (enable) ? newOff : off); // dmc3.exe+EBD28 - 48 8B 83 581B0000 - MOV RAX,[RBX+00001B58]
	// 	// Write<uint32>((appBaseAddr + 0xEBD88 + 3), (enable) ? newOff : off); // dmc3.exe+EBD88 - 48 8B 83 581B0000 - MOV RAX,[RBX+00001B58]
	// 	// Write<uint32>((appBaseAddr + 0xEC91E + 3), (enable) ? newOff : off); // dmc3.exe+EC91E - 48 8B 83 581B0000 - MOV RAX,[RBX+00001B58]
	// 	// Write<uint32>((appBaseAddr + 0xEC9C3 + 3), (enable) ? newOff : off); // dmc3.exe+EC9C3 - 48 8B 83 581B0000 - MOV RAX,[RBX+00001B58]
	// 	// Write<uint32>((appBaseAddr + 0x15D13C + 3), (enable) ? newOff : off); // dmc3.exe+15D13C - 4C 8B 87 581B0000 - MOV R8,[RDI+00001B58]
	// 	// Trash<uint32>((appBaseAddr + 0x59B9D8 + 3), (enable) ? newOff : off); // dmc3.exe+59B9D8 - A0 0F0000581B000010 - MOV AL,[1000001B5800000F]
	// 	// Trash<uint32>((appBaseAddr + 0x59E98C + 3), (enable) ? newOff : off); // dmc3.exe+59E98C - A0 0F0000581B000010 - MOV AL,[1000001B5800000F]
	// 	// Trash<uint32>((appBaseAddr + 0x59EDB4 + 3), (enable) ? newOff : off); // dmc3.exe+59EDB4 - A0 0F0000581B000010 - MOV AL,[1000001B5800000F]
	// 	// Trash<uint32>((appBaseAddr + 0x59F2E8 + 3), (enable) ? newOff : off); // dmc3.exe+59F2E8 - A0 0F0000581B000010 - MOV AL,[1000001B5800000F]
	// 	// Trash<uint32>((appBaseAddr + 0x5A0C50 + 3), (enable) ? newOff : off); // dmc3.exe+5A0C50 - A0 0F0000581B000010 - MOV AL,[1000001B5800000F]
	// 	// Trash<uint32>((appBaseAddr + 0x5A1418 + 3), (enable) ? newOff : off); // dmc3.exe+5A1418 - A0 0F0000581B000010 - MOV AL,[1000001B5800000F]
	// 	// Trash<uint32>((appBaseAddr + 0x5A16B0 + 3), (enable) ? newOff : off); // dmc3.exe+5A16B0 - A0 0F0000581B000010 - MOV AL,[1000001B5800000F]
	// }
	// // 0x1B60
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[3][20]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[3][20]);
	// 	static_assert(off == 0x1B60);
	// 	// Mission19<uint32>((appBaseAddr + 0x15C811 + 3), (enable) ? newOff : off); // dmc3.exe+15C811 - 48 8D 9E 601B0000 - LEA RBX,[RSI+00001B60]
	// 	// Mission19<uint32>((appBaseAddr + 0x15CAC4 + 3), (enable) ? newOff : off); // dmc3.exe+15CAC4 - 48 89 86 601B0000 - MOV [RSI+00001B60],RAX
	// 	// Trash<uint32>((appBaseAddr + 0x1BD9F9 + 3), (enable) ? newOff : off); // dmc3.exe+1BD9F9 - BA 601B0000 - MOV EDX,00001B60
	// 	// Write<uint32>((appBaseAddr + 0x349D9D + 3), (enable) ? newOff : off); // dmc3.exe+349D9D - 48 81 C1 601B0000 - ADD RCX,00001B60
	// }
	// // 0x1B68
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[3][21]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[3][21]);
	// 	static_assert(off == 0x1B68);
	// 	// Trash<uint32>((appBaseAddr + 0x254A52 + 3), (enable) ? newOff : off); // dmc3.exe+254A52 - F3 0F58 81 681B0000 - ADDSS XMM0,DWORD PTR [RCX+00001B68]
	// 	// Trash<uint32>((appBaseAddr + 0x254A62 + 3), (enable) ? newOff : off); // dmc3.exe+254A62 - F3 0F11 81 681B0000 - MOVSS [RCX+00001B68],XMM0
	// 	// Trash<uint32>((appBaseAddr + 0x254A7D + 3), (enable) ? newOff : off); // dmc3.exe+254A7D - F3 0F11 91 681B0000 - MOVSS [RCX+00001B68],XMM2
	// 	// Trash<uint32>((appBaseAddr + 0x254B39 + 3), (enable) ? newOff : off); // dmc3.exe+254B39 - 89 81 681B0000 - MOV [RCX+00001B68],EAX
	// }
	// // 0x1B70
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[3][22]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[3][22]);
	// 	static_assert(off == 0x1B70);
	// 	// Write<uint32>((appBaseAddr + 0x2538A8 + 3), (enable) ? newOff : off); // dmc3.exe+2538A8 - 48 8D 8B 701B0000 - LEA RCX,[RBX+00001B70]
	// 	// Write<uint32>((appBaseAddr + 0x253963 + 3), (enable) ? newOff : off); // dmc3.exe+253963 - 48 81 C1 701B0000 - ADD RCX,00001B70
	// 	// Write<uint32>((appBaseAddr + 0x254405 + 3), (enable) ? newOff : off); // dmc3.exe+254405 - 48 81 C1 701B0000 - ADD RCX,00001B70
	// 	// Write<uint32>((appBaseAddr + 0x254423 + 3), (enable) ? newOff : off); // dmc3.exe+254423 - 48 8D 8D 701B0000 - LEA RCX,[RBP+00001B70]
	// 	// Write<uint32>((appBaseAddr + 0x254464 + 3), (enable) ? newOff : off); // dmc3.exe+254464 - 48 8D 8D 701B0000 - LEA RCX,[RBP+00001B70]
	// 	// Write<uint32>((appBaseAddr + 0x25447D + 3), (enable) ? newOff : off); // dmc3.exe+25447D - 48 8D 8D 701B0000 - LEA RCX,[RBP+00001B70]
	// 	// Write<uint32>((appBaseAddr + 0x2544F7 + 3), (enable) ? newOff : off); // dmc3.exe+2544F7 - 48 8D 8D 701B0000 - LEA RCX,[RBP+00001B70]
	// }
	// // 0x1B78
	// {
	// 	constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[3][23]);
	// 	constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[3][23]);
	// 	static_assert(off == 0x1B78);
	// 	// Trash<uint32>((appBaseAddr + 0x254419 + 3), (enable) ? newOff : off); // dmc3.exe+254419 - C7 85 781B0000 0D000000 - MOV [RBP+00001B78],0000000D
	// }























	// 0x7CC0
	{
		constexpr auto off = offsetof(ActorData, submodelData[1]);
		constexpr auto newOff = offsetof(ActorData, newSubmodelData[1]);
		static_assert(off == 0x7CC0);
		// Write<uint32>((appBaseAddr + 0x176458 + 3), (enable) ? newOff : off); // dmc3.exe+176458 - 48 8D 8E C07C0000 - LEA RCX,[RSI+00007CC0]
		// Write<uint32>((appBaseAddr + 0x176BE5 + 3), (enable) ? newOff : off); // dmc3.exe+176BE5 - 48 8D 8E C07C0000 - LEA RCX,[RSI+00007CC0]
		// Trash<uint32>((appBaseAddr + 0x21913F + 3), (enable) ? newOff : off); // dmc3.exe+21913F - 80 B9 C07C0000 00 - CMP BYTE PTR [RCX+00007CC0],00
		// Trash<uint32>((appBaseAddr + 0x21915B + 3), (enable) ? newOff : off); // dmc3.exe+21915B - C6 87 C07C0000 00 - MOV BYTE PTR [RDI+00007CC0],00
		// Trash<uint32>((appBaseAddr + 0x21927C + 3), (enable) ? newOff : off); // dmc3.exe+21927C - C6 81 C07C0000 00 - MOV BYTE PTR [RCX+00007CC0],00
		// Trash<uint32>((appBaseAddr + 0x2193F7 + 3), (enable) ? newOff : off); // dmc3.exe+2193F7 - C6 85 C07C0000 01 - MOV BYTE PTR [RBP+00007CC0],01
		// Write<uint32>((appBaseAddr + 0x34A4AE + 3), (enable) ? newOff : off); // dmc3.exe+34A4AE - 48 81 C1 C07C0000 - ADD RCX,00007CC0
	}
	// 0x8440
	{
		constexpr auto off = offsetof(ActorData, submodelData[2]);
		constexpr auto newOff = offsetof(ActorData, newSubmodelData[2]);
		static_assert(off == 0x8440);
		// Write<uint32>((appBaseAddr + 0xB5F18 + 3), (enable) ? newOff : off); // dmc3.exe+B5F18 - 49 8D 94 24 40840000 - LEA RDX,[R12+00008440]
		// Write<uint32>((appBaseAddr + 0x176465 + 3), (enable) ? newOff : off); // dmc3.exe+176465 - 48 8D 8E 40840000 - LEA RCX,[RSI+00008440]
		// Write<uint32>((appBaseAddr + 0x176BD8 + 3), (enable) ? newOff : off); // dmc3.exe+176BD8 - 48 8D 8E 40840000 - LEA RCX,[RSI+00008440]
		// Write<uint32>((appBaseAddr + 0x180773 + 3), (enable) ? newOff : off); // dmc3.exe+180773 - 48 8D 8B 40840000 - LEA RCX,[RBX+00008440]
		// Write<uint32>((appBaseAddr + 0x18392C + 3), (enable) ? newOff : off); // dmc3.exe+18392C - 48 8B BE 40840000 - MOV RDI,[RSI+00008440]
		// Write<uint32>((appBaseAddr + 0x183939 + 3), (enable) ? newOff : off); // dmc3.exe+183939 - 48 8D 8E 40840000 - LEA RCX,[RSI+00008440]
		// Write<uint32>((appBaseAddr + 0x184529 + 3), (enable) ? newOff : off); // dmc3.exe+184529 - 48 8B BE 40840000 - MOV RDI,[RSI+00008440]
		// Write<uint32>((appBaseAddr + 0x184536 + 3), (enable) ? newOff : off); // dmc3.exe+184536 - 48 8D 8E 40840000 - LEA RCX,[RSI+00008440]
		// Write<uint32>((appBaseAddr + 0x186EC7 + 3), (enable) ? newOff : off); // dmc3.exe+186EC7 - 48 8D 8F 40840000 - LEA RCX,[RDI+00008440]
		// Write<uint32>((appBaseAddr + 0x1870B7 + 3), (enable) ? newOff : off); // dmc3.exe+1870B7 - 48 8D 8F 40840000 - LEA RCX,[RDI+00008440]
		// Write<uint32>((appBaseAddr + 0x34A4C1 + 3), (enable) ? newOff : off); // dmc3.exe+34A4C1 - 48 81 C1 40840000 - ADD RCX,00008440
		// Trash<uint32>((appBaseAddr + 0x589CFE + 3), (enable) ? newOff : off); // dmc3.exe+589CFE - 8C BF 00008440 - MOV [RDI+40840000],IS
		// Trash<uint32>((appBaseAddr + 0x589D22 + 3), (enable) ? newOff : off); // dmc3.exe+589D22 - C0 BF 00008440 00 - SAR BYTE PTR [RDI+40840000],00
		// Trash<uint32>((appBaseAddr + 0x589D46 + 3), (enable) ? newOff : off); // dmc3.exe+589D46 - C0 BF 00008440 00 - SAR BYTE PTR [RDI+40840000],00
		// Trash<uint32>((appBaseAddr + 0x589D6A + 3), (enable) ? newOff : off); // dmc3.exe+589D6A - C0 BF 00008440 00 - SAR BYTE PTR [RDI+40840000],00
		// Trash<uint32>((appBaseAddr + 0x58F6DE + 3), (enable) ? newOff : off); // dmc3.exe+58F6DE - 8C BF 00008440 - MOV [RDI+40840000],IS
		// Trash<uint32>((appBaseAddr + 0x58F702 + 3), (enable) ? newOff : off); // dmc3.exe+58F702 - C0 BF 00008440 00 - SAR BYTE PTR [RDI+40840000],00
		// Trash<uint32>((appBaseAddr + 0x58F726 + 3), (enable) ? newOff : off); // dmc3.exe+58F726 - C0 BF 00008440 00 - SAR BYTE PTR [RDI+40840000],00
		// Trash<uint32>((appBaseAddr + 0x58F74A + 3), (enable) ? newOff : off); // dmc3.exe+58F74A - C0 BF 00008440 00 - SAR BYTE PTR [RDI+40840000],00
		// Trash<uint32>((appBaseAddr + 0x591AEE + 3), (enable) ? newOff : off); // dmc3.exe+591AEE - 8C BF 00008440 - MOV [RDI+40840000],IS
		// Trash<uint32>((appBaseAddr + 0x591B12 + 3), (enable) ? newOff : off); // dmc3.exe+591B12 - C0 BF 00008440 00 - SAR BYTE PTR [RDI+40840000],00
		// Trash<uint32>((appBaseAddr + 0x591B36 + 3), (enable) ? newOff : off); // dmc3.exe+591B36 - C0 BF 00008440 00 - SAR BYTE PTR [RDI+40840000],00
		// Trash<uint32>((appBaseAddr + 0x591B5A + 3), (enable) ? newOff : off); // dmc3.exe+591B5A - C0 BF 00008440 00 - SAR BYTE PTR [RDI+40840000],00
	}
	// 0x8BC0
	{
		constexpr auto off = offsetof(ActorData, submodelData[3]);
		constexpr auto newOff = offsetof(ActorData, newSubmodelData[3]);
		static_assert(off == 0x8BC0);
		// Write<uint32>((appBaseAddr + 0x1764E7 + 3), (enable) ? newOff : off); // dmc3.exe+1764E7 - 48 8D 9E C08B0000 - LEA RBX,[RSI+00008BC0]
		// Write<uint32>((appBaseAddr + 0x176B5C + 3), (enable) ? newOff : off); // dmc3.exe+176B5C - 48 89 AE C08B0000 - MOV [RSI+00008BC0],RBP
		// Write<uint32>((appBaseAddr + 0x184F89 + 3), (enable) ? newOff : off); // dmc3.exe+184F89 - C7 83 C08B0000 00002041 - MOV [RBX+00008BC0],41200000
		// Write<uint32>((appBaseAddr + 0x34A58B + 3), (enable) ? newOff : off); // dmc3.exe+34A58B - 48 81 C1 C08B0000 - ADD RCX,00008BC0
	}



#endif
