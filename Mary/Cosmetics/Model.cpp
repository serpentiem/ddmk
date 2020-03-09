#include "Model.h"

PrivateStart;

inline void RegisterModel
(
	byte8 * dest,
	byte8 * modelFile,
	byte8 * textureFile
)
{
	func_8B470(dest, 1);
	func_89960(dest, modelFile, textureFile);
}

inline void RegisterShadow
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

inline void RegisterPhysics
(
	byte8 * dest,
	byte8 * buffer,
	byte8 * file
)
{
	uint32 count = 0;

	count = func_2C9F40(file);
	for (uint32 index = 0; index < count; index++)
	{
		func_2CA1D0(dest, buffer, file, index);
		dest += 0xF0;
	}
}

inline void ResetModel(byte8 * dest)
{
	func_897B0(dest);
	func_89450(dest);
	memset(dest, 0, 0x780);
	func_89270(dest);
}

inline void CopyBaseVertices(MODEL_DATA * modelData)
{
	auto g_vertices = (vec4 *)(appBaseAddr + 0x58B260);

	for (uint8 index = 0; index < 6; index++)
	{
		uint8 off = (index * 3);
		modelData[index].count = 4;
		modelData[index].vertices[0] = g_vertices[(off + 0)];
		modelData[index].vertices[1] = g_vertices[(off + 1)];
		modelData[index].vertices[2] = g_vertices[(off + 2)];
	}
}

inline void CopyAmuletVertices(MODEL_DATA * modelData)
{
	auto g_vertices = (vec4 *)(appBaseAddr + 0x58B260);

	modelData[0].count = 4;
	modelData[0].vertices[0] = g_vertices[23];
	modelData[0].vertices[1] = g_vertices[24];
	modelData[0].vertices[2] = g_vertices[25];
}

inline void CopyCoatVertices(byte8 * dest)
{
	auto g_vertices = (vec4 *)(appBaseAddr + 0x35D580);

	byte8 * addr     = 0;
	vec4  * vertices = 0;

	addr = *(byte8 **)dest;
	vertices = *(vec4 **)(addr + 0x108);

	vertices[0] = g_vertices[0];
	vertices[1] = g_vertices[1];
	vertices[2] = g_vertices[2];
	vertices[3] = g_vertices[3];
}

template <uint8 id>
void UpdateModelTemplateDante(byte8 * baseAddr)
{
	uint8 modelIndex = 0;
	uint8 modelOff   = 0;

	uint8 subModelIndex = 0;

	MODEL_DATA * modelData = 0;

	byte8 * dest  = 0;
	byte8 * dest2 = 0;

	modelData = (MODEL_DATA *)(baseAddr + 0xB630);

	// Base

	{
		auto & fileHelper = Config.Cosmetics.Dante.modelFileHelper[id][MODEL_PART_BASE];

		dest = (baseAddr + 0x200 + (modelIndex * 0x780));

		RegisterModel
		(
			dest,
			System_File_cacheFile[fileHelper.model.cacheFileId][fileHelper.model.fileIndex],
			System_File_cacheFile[fileHelper.texture.cacheFileId][fileHelper.texture.fileIndex]
		);

		RegisterShadow
		(
			dest,
			(baseAddr + 0x9AD0 + (modelIndex * 0xC0)),
			System_File_cacheFile[fileHelper.shadow.cacheFileId][fileHelper.shadow.fileIndex]
		);

		CopyBaseVertices(modelData);
	}

	// Coat

	if constexpr
	(
		(id == COSTUME_DANTE_DEFAULT     ) ||
		(id == COSTUME_DANTE_DEFAULT_TORN) ||
		(id == COSTUME_DANTE_DMC1        ) ||
		(id == COSTUME_DANTE_SPARDA      )
	)
	{
		auto & fileHelper = Config.Cosmetics.Dante.modelFileHelper[id][MODEL_PART_COAT];

		dest = (baseAddr + 0x7540 + (subModelIndex * 0x780));
		dest2 = (baseAddr + 0xA0D0);

		RegisterModel
		(
			dest,
			System_File_cacheFile[fileHelper.model.cacheFileId][fileHelper.model.fileIndex],
			System_File_cacheFile[fileHelper.texture.cacheFileId][fileHelper.texture.fileIndex]
		);

		func_8A000(dest, 0, dest2);

		RegisterShadow
		(
			dest,
			(baseAddr + 0x9D10 + (subModelIndex * 0xC0)),
			System_File_cacheFile[fileHelper.shadow.cacheFileId][fileHelper.shadow.fileIndex]
		);

		dest = (baseAddr + 0xA210);

		RegisterPhysics
		(
			dest,
			dest2,
			System_File_cacheFile[fileHelper.physics.cacheFileId][fileHelper.physics.fileIndex]
		);

		func_2CA2F0
		(
			dest,
			(baseAddr + ((modelOff + 0x310) * 8)),
			(appBaseAddr + 0x58B380),
			modelData,
			6
		);

		CopyCoatVertices(dest2);
	}

	// Amulet

	if constexpr
	(
		(id == COSTUME_DANTE_DEFAULT_NO_COAT) ||
		(id == COSTUME_DANTE_DMC1_NO_COAT   )
	)
	{
		auto & fileHelper = Config.Cosmetics.Dante.modelFileHelper[id][MODEL_PART_COAT];

		dest = (baseAddr + 0x7540 + (subModelIndex * 0x780));
		dest2 = (baseAddr + 0xA0D0);

		RegisterModel
		(
			dest,
			System_File_cacheFile[fileHelper.model.cacheFileId][fileHelper.model.fileIndex],
			System_File_cacheFile[fileHelper.texture.cacheFileId][fileHelper.texture.fileIndex]
		);

		func_8A000(dest, 0, dest2);

		dest = (baseAddr + 0xA210);

		RegisterPhysics
		(
			dest,
			dest2,
			System_File_cacheFile[fileHelper.physics.cacheFileId][fileHelper.physics.fileIndex]
		);

		func_2CA2F0
		(
			dest,
			(baseAddr + ((modelOff + 0x310) * 8)),
			(appBaseAddr + 0x58B380),
			modelData,
			1
		);

		CopyAmuletVertices(modelData);
	}
}

constexpr uint32 devilModelDataOffDante[MAX_DEVIL_DANTE] =
{
	0xB600,
	0xB608,
	0xB60D,
	0xB60F,
	0xB617,
	0xB61C,
};

template <uint8 id>
void UpdateDevilModelTemplateDante
(
	byte8 * baseAddr,
	uint8   slot
)
{
	uint8 modelIndex = 0;
	uint8 modelOff   = 0;

	uint8 subModelIndex = 0;

	MODEL_DATA * modelData = 0;

	uint8 devilModelOff = 0;
	
	uint8 devilSubModelIndex = 0;

	DEVIL_MODEL_DATA * devilModelData = 0;

	byte8 * dest  = 0;
	byte8 * dest2 = 0;

	auto CopyVertices = [&]
	(
		byte8 * baseAddr,
		uint8   baseIndex,
		uint8   devilIndex,
		uint8   index
	)
	{
		auto g_vertices = (vec4 *)(appBaseAddr + 0x35D580);
	
		byte8 * dest = 0;
		byte8 * addr = 0;
	
		vec4 * vertices = 0;
	
		dest = (baseAddr + 0xAA00 + (baseIndex * 0xC0) + (devilSubModelIndex * 0x300));
	
		addr = *(byte8 **)(baseAddr + 0xA300 + ((devilModelOff + devilIndex) * 8));
		*(byte8 **)(addr + 0x100) = dest;
	
		vertices = (vec4 *)(dest + 0x80);
		vertices[0] = g_vertices[0];
		vertices[1] = g_vertices[1];
		vertices[2] = g_vertices[2];
		vertices[3] = g_vertices[3];
	
		*(uint32 *)(dest + 0x28) = 1;
		// @Research: Replace 0x1880 with ((modelOff + 0x310) * 8).
		addr = *(byte8 **)(baseAddr + 0x1880 + ((modelOff + index) * 8));
		addr = *(byte8 **)(addr + 0x110);
		*(byte8 **)(dest + 0x30) = addr;
	};

	modelIndex = (slot == 1) ? 1 : 2;
	modelOff   = (slot == 1) ? 0x18 : 0x30;

	subModelIndex = (slot == 1) ? 1 : 3;

	modelData = (MODEL_DATA *)(baseAddr + 0xB630);

	devilModelOff = (slot == 1) ? 0 : 0x24;

	devilSubModelIndex = (slot == 1) ? 0 : 2;

	devilModelData = (DEVIL_MODEL_DATA *)(baseAddr + devilModelDataOffDante[id]);

	((uint32 *)(baseAddr + 0x3E74))[slot] = id;

	devilModelData->modelIndex = modelIndex;
	devilModelData->modelOff   = modelOff;

	// Base

	{
		auto & fileHelper = Config.Cosmetics.Dante.devilModelFileHelper[id][DEVIL_MODEL_PART_BASE];

		dest = (baseAddr + 0x200 + (slot * 0x780));

		RegisterModel
		(
			dest,
			System_File_cacheFile[fileHelper.model.cacheFileId][fileHelper.model.fileIndex],
			System_File_cacheFile[fileHelper.texture.cacheFileId][fileHelper.texture.fileIndex]
		);

		func_1EF040(baseAddr, slot);

		RegisterShadow
		(
			dest,
			(baseAddr + 0x9AD0 + (slot * 0xC0)),
			System_File_cacheFile[fileHelper.shadow.cacheFileId][fileHelper.shadow.fileIndex]
		);
	}

	// Coat

	if constexpr ((id == DEVIL_DANTE_REBELLION) || (id == DEVIL_DANTE_NEVAN))
	{
		auto & fileHelper = Config.Cosmetics.Dante.devilModelFileHelper[id][DEVIL_MODEL_PART_COAT];

		dest = (baseAddr + 0x7540 + (subModelIndex * 0x780));
		dest2 = (baseAddr + ((0x1460 + devilModelOff) * 8));

		RegisterModel
		(
			dest,
			System_File_cacheFile[fileHelper.model.cacheFileId][fileHelper.model.fileIndex],
			System_File_cacheFile[fileHelper.texture.cacheFileId][fileHelper.texture.fileIndex]
		);

		func_8A000(dest, 0, dest2);

		RegisterShadow
		(
			dest,
			(baseAddr + 0x9D10 + (subModelIndex * 0xC0)),
			System_File_cacheFile[fileHelper.shadow.cacheFileId][fileHelper.shadow.fileIndex]
		);

		dest = (baseAddr + 0xA540 + (devilSubModelIndex * 0xF0));

		RegisterPhysics
		(
			dest,
			dest2,
			System_File_cacheFile[fileHelper.physics.cacheFileId][fileHelper.physics.fileIndex]
		);

		CopyVertices(baseAddr, 0, 1 , 3);
		CopyVertices(baseAddr, 1, 12, 2);

		devilModelData->subModelData[0].subModelIndex      = subModelIndex;
		devilModelData->subModelData[0].devilModelOff      = devilModelOff;
		devilModelData->subModelData[0].devilSubModelIndex = devilSubModelIndex;

		subModelIndex++;
		devilSubModelIndex++;
	}

	// Wings

	{
		auto & fileHelper = Config.Cosmetics.Dante.devilModelFileHelper[id][DEVIL_MODEL_PART_WINGS];

		dest = (baseAddr + 0x7540 + (subModelIndex * 0x780));

		if constexpr ((id == DEVIL_DANTE_REBELLION) || (id == DEVIL_DANTE_NEVAN))
		{
			dest2 = (baseAddr + ((0x1460 + devilModelOff + 9) * 8));
		}
		else if constexpr ((id == DEVIL_DANTE_CERBERUS) || (id == DEVIL_DANTE_SPARDA))
		{
			dest2 = (baseAddr + ((0x1460 + devilModelOff) * 8));
		}
		else
		{
			dest2 = (baseAddr + ((0xA300 + devilModelOff) * 8));
		}

		RegisterModel
		(
			dest,
			System_File_cacheFile[fileHelper.model.cacheFileId][fileHelper.model.fileIndex],
			System_File_cacheFile[fileHelper.texture.cacheFileId][fileHelper.texture.fileIndex]
		);

		func_8A000(dest, 0, dest2);

		RegisterShadow
		(
			dest,
			(baseAddr + 0x9D10 + (subModelIndex * 0xC0)),
			System_File_cacheFile[fileHelper.shadow.cacheFileId][fileHelper.shadow.fileIndex]
		);

		dest = (baseAddr + 0xA540 + (devilSubModelIndex * 0xF0));

		RegisterPhysics
		(
			dest,
			dest2,
			System_File_cacheFile[fileHelper.physics.cacheFileId][fileHelper.physics.fileIndex]
		);

		if constexpr ((id == DEVIL_DANTE_REBELLION) || (id == DEVIL_DANTE_NEVAN))
		{
			func_2CA2F0
			(
				dest,
				(baseAddr + ((modelOff + 0x310) * 8)),
				(appBaseAddr + 0x58B380),
				modelData,
				6
			);

			CopyVertices(baseAddr, 0, (9 + 1), 2 );
			CopyVertices(baseAddr, 1, (9 + 2), 14);
		}
		else if constexpr ((id == DEVIL_DANTE_CERBERUS) || (id == DEVIL_DANTE_BEOWULF))
		{
			CopyVertices(baseAddr, 0, 1, 3 );
			CopyVertices(baseAddr, 1, 2, 6 );
			CopyVertices(baseAddr, 2, 8, 10);
		}

		if constexpr ((id == DEVIL_DANTE_REBELLION) || (id == DEVIL_DANTE_NEVAN))
		{
			devilModelData->subModelData[1].subModelIndex      = subModelIndex;
			devilModelData->subModelData[1].devilModelOff      = devilModelOff;
			devilModelData->subModelData[1].devilSubModelIndex = devilSubModelIndex;
		}
		else
		{
			devilModelData->subModelData[0].subModelIndex      = subModelIndex;
			devilModelData->subModelData[0].devilModelOff      = devilModelOff;
			devilModelData->subModelData[0].devilSubModelIndex = devilSubModelIndex;
		}
	}
}

PrivateEnd;

Cosmetics_Model_UpdateModel_t Cosmetics_Model_UpdateModelDante[MAX_COSTUME_DANTE] =
{
	UpdateModelTemplateDante<COSTUME_DANTE_DEFAULT>,
	UpdateModelTemplateDante<COSTUME_DANTE_DEFAULT_NO_COAT>,
	UpdateModelTemplateDante<COSTUME_DANTE_DEFAULT_TORN>,
	UpdateModelTemplateDante<COSTUME_DANTE_DMC1>,
	UpdateModelTemplateDante<COSTUME_DANTE_DMC1_NO_COAT>,
	UpdateModelTemplateDante<COSTUME_DANTE_SPARDA>,
	UpdateModelTemplateDante<COSTUME_DANTE_DEFAULT_TORN>,
	UpdateModelTemplateDante<COSTUME_DANTE_SPARDA>,
};

Cosmetics_Model_UpdateDevilModel_t Cosmetics_Model_UpdateDevilModelDante[MAX_DEVIL_DANTE] =
{
	UpdateDevilModelTemplateDante<DEVIL_DANTE_REBELLION>,
	UpdateDevilModelTemplateDante<DEVIL_DANTE_CERBERUS>,
	UpdateDevilModelTemplateDante<DEVIL_DANTE_AGNI_RUDRA>,
	UpdateDevilModelTemplateDante<DEVIL_DANTE_NEVAN>,
	UpdateDevilModelTemplateDante<DEVIL_DANTE_BEOWULF>,
	UpdateDevilModelTemplateDante<DEVIL_DANTE_SPARDA>,
};

void Cosmetics_Model_Init()
{
	LogFunction();

	for (uint8 index = 0; index < countof(Cosmetics_Model_UpdateModelDante); index++)
	{
		Log("Cosmetics_Model_UpdateModelDante[%u] %llX", index, Cosmetics_Model_UpdateModelDante[index]);
	}

	for (uint8 index = 0; index < countof(Cosmetics_Model_UpdateDevilModelDante); index++)
	{
		Log("Cosmetics_Model_UpdateDevilModelDante[%u] %llX", index, Cosmetics_Model_UpdateDevilModelDante[index]);
	}
}
