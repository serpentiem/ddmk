#include "Model.h"

PrivateStart;

#pragma region Functions

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

#pragma endregion

MODEL_FILE_HELPER Dante_modelFileHelper[MAX_COSTUME_DANTE][MODEL_MAX_PART] =
{
	// Default
	{
		// Base
		{
			{ pl000, 1 },
			{ pl000, 0 },
			{ pl000, 8 },
			{ 0    , 0 },
		},
		// Amulet
		{
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
		},
		// Coat
		{
			{ pl000, 12 },
			{ pl000, 0  },
			{ pl000, 14 },
			{ pl000, 13 },
		},
	},
	// Default No Coat
	{
		// Base
		{
			{ pl011, 1 },
			{ pl011, 0 },
			{ pl011, 8 },
			{ 0    , 0 },
		},
		// Amulet
		{
			{ pl011, 12 },
			{ pl011, 0  },
			{ 0    , 0  },
			{ pl011, 13 },
		},
		// Coat
		{
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
		},
	},
	// Default Torn
	{
		// Base
		{
			{ pl013, 1 },
			{ pl013, 0 },
			{ pl013, 8 },
			{ 0    , 0 },
		},
		// Amulet
		{
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
		},
		// Coat
		{
			{ pl013, 12 },
			{ pl013, 0  },
			{ pl013, 14 },
			{ pl013, 13 },
		},
	},
	// DMC1
	{
		// Base
		{
			{ pl015, 1 },
			{ pl015, 0 },
			{ pl015, 8 },
			{ 0    , 0 },
		},
		// Amulet
		{
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
		},
		// Coat
		{
			{ pl015, 12 },
			{ pl015, 0  },
			{ pl015, 14 },
			{ pl015, 13 },
		},
	},
	// DMC1 No Coat
	{
		// Base
		{
			{ pl016, 1 },
			{ pl016, 0 },
			{ pl016, 8 },
			{ 0    , 0 },
		},
		// Amulet
		{
			{ pl016, 12 },
			{ pl016, 0  },
			{ 0    , 0  },
			{ pl016, 13 },
		},
		// Coat
		{
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
		},
	},
	// Sparda
	{
		// Base
		{
			{ pl018, 1 },
			{ pl018, 0 },
			{ pl018, 8 },
			{ 0    , 0 },
		},
		// Coat
		{
			{ pl018, 12 },
			{ pl018, 0  },
			{ pl018, 14 },
			{ pl018, 13 },
		},
		// Amulet
		{
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
		},
	},
};

DEVIL_MODEL_FILE_HELPER Dante_devilModelFileHelper[MAX_DEVIL_DANTE][DEVIL_MODEL_MAX_PART] =
{
	// Rebellion
	{
		// Base
		{
			{ pl005, 1 },
			{ pl005, 0 },
			{ pl005, 6 },
			{ 0    , 0 },
		},
		// Wings
		{
			{ pl005, 2 },
			{ pl005, 0 },
			{ pl005, 7 },
			{ pl005, 3 },
		},
		// Coat
		{
			{ pl005, 4 },
			{ pl005, 0 },
			{ pl005, 8 },
			{ pl005, 5 },
		},
	},
	// Cerberus
	{
		// Base
		{
			{ pl006, 1 },
			{ pl006, 0 },
			{ pl006, 4 },
			{ 0    , 0 },
		},
		// Wings
		{
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
		},
		// Coat
		{
			{ pl006, 2 },
			{ pl006, 0 },
			{ pl006, 5 },
			{ pl006, 3 },
		},
	},
	// Agni Rudra
	{
		// Base
		{
			{ pl007, 1 },
			{ pl007, 0 },
			{ pl007, 2 },
			{ 0    , 0 },
		},
		// Wings
		{
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
		},
		// Coat
		{
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
		},
	},
	// Nevan
	{
		// Base
		{
			{ pl008, 1 },
			{ pl008, 0 },
			{ pl008, 6 },
			{ 0    , 0 },
		},
		// Wings
		{
			{ pl008, 2 },
			{ pl008, 0 },
			{ pl008, 7 },
			{ pl008, 3 },
		},
		// Coat
		{
			{ pl008, 4 },
			{ pl008, 0 },
			{ pl008, 8 },
			{ pl008, 5 },
		},
	},
	// Beowulf
	{
		// Base
		{
			{ pl009, 1 },
			{ pl009, 0 },
			{ pl009, 4 },
			{ 0    , 0 },
		},
		// Wings
		{
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
		},
		// Coat
		{
			{ pl009, 2 },
			{ pl009, 0 },
			{ pl009, 5 },
			{ pl009, 3 },
		},
	},
	// Sparda
	{
		// Base
		{
			{ pl017, 1 },
			{ pl017, 0 },
			{ pl017, 4 },
			{ 0    , 0 },
		},
		// Wings
		{
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
		},
		// Coat
		{
			{ pl017, 2 },
			{ pl017, 0 },
			{ pl017, 5 },
			{ pl017, 3 },
		},
	},
};

MODEL_FILE_HELPER Vergil_modelFileHelper[MAX_COSTUME_VERGIL][MODEL_MAX_PART] =
{
	// Default
	{
		// Base
		{
			{ pl021, 1 },
			{ pl021, 0 },
			{ pl021, 8 },
			{ 0    , 0 },
		},
		// Amulet
		{
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
		},
		// Coat
		{
			{ pl021, 12 },
			{ pl021, 0  },
			{ pl021, 14 },
			{ pl021, 13 },
		},
	},
	// Default No Coat
	{
		// Base
		{
			{ pl023, 1 },
			{ pl023, 0 },
			{ pl023, 8 },
			{ 0    , 0 },
		},
		// Amulet
		{
			{ pl023, 12 },
			{ pl023, 0  },
			{ 0    , 0  },
			{ pl023, 13 },
		},
		// Coat
		{
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
		},
	},
	// Sparda
	{
		// Base
		{
			{ pl026, 1 },
			{ pl026, 0 },
			{ pl026, 8 },
			{ 0    , 0 },
		},
		// Amulet
		{
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
		},
		// Coat
		{
			{ pl026, 12 },
			{ pl026, 0  },
			{ pl026, 14 },
			{ pl026, 13 },
		},
	},
};

DEVIL_MODEL_FILE_HELPER Vergil_devilModelFileHelper[MAX_DEVIL_VERGIL][DEVIL_MODEL_MAX_PART] =
{
	// Yamato
	{
		// Base
		{
			{ pl010, 1 },
			{ pl010, 0 },
			{ pl010, 7 },
			{ 0    , 0 },
		},
		// Wings
		{
			{ pl010, 2 },
			{ pl010, 0 },
			{ pl010, 8 },
			{ pl010, 3 },
		},
		// Coat
		{
			{ pl010, 5  },
			{ pl010, 0  },
			{ pl010, 10 },
			{ pl010, 6  },
		},
	},
	// Beowulf
	{
		// Base
		{
			{ pl014, 1 },
			{ pl014, 0 },
			{ pl014, 4 },
			{ 0    , 0 },
		},
		// Wings
		{
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
			{ 0, 0 },
		},
		// Coat
		{
			{ pl014, 2 },
			{ pl014, 0 },
			{ pl014, 5 },
			{ pl014, 3 },
		},
	},
};








//enum SUBMODEL_
//{
//	SUBMODEL_COAT_DANTE,
//	SUBMODEL_COAT_VERGIL,
//	SUBMODEL_AMULET_DANTE,
//	SUBMODEL_AMULET_VERGIL,
//	SUBMODEL_NONE = 0xFF,
//};
//
//enum DEVIL_SUBMODEL_
//{
//	DEVIL_SUBMODEL_COAT_DANTE_REBELLION,
//	DEVIL_SUBMODEL_COAT_DANTE_NEVAN,
//	DEVIL_SUBMODEL_COAT_VERGIL_YAMATO,
//	DEVIL_SUBMODEL_WINGS_DANTE_REBELLION,
//	DEVIL_SUBMODEL_WINGS_DANTE_CERBERUS,
//	DEVIL_SUBMODEL_WINGS_DANTE_NEVAN,
//	DEVIL_SUBMODEL_WINGS_DANTE_BEOWULF,
//	DEVIL_SUBMODEL_WINGS_DANTE_SPARDA,
//	DEVIL_SUBMODEL_WINGS_VERGIL_BEOWULF,
//	DEVIL_SUBMODEL_NONE = 0xFF,
//};



// UpdateModelTemplate<CHAR_DANTE, LOGIC_COSTUME_DANTE_DEFAULT, Config.Cosmetics.Vergil.modelFileHelper[LOGIC_COSTUME_VERGIL_DEFAULT]>

// UpdateDevilModelTemplate<CHAR_DANTE, DEVIL_DANTE_REBELLION, Config.Cosmetics.Vergil.devilModelFileHelper[DEVIL_VERGIL_YAMATO]>




template
<
	uint8 character,
	uint8 costume,
	uint8 fileHelperCharacter,
	uint8 fileHelperCostume
>
void UpdateModelTemplate(byte8 * baseAddr)
{
	uint8 modelIndex = 0;
	uint8 modelOff   = 0;

	uint8 submodelIndex = 0;

	MODEL_FILE_HELPER * modelFileHelper = 0;

	MODEL_DATA * modelData = 0;

	byte8 * dest  = 0;
	byte8 * dest2 = 0;

	if constexpr (fileHelperCharacter == CHAR_DANTE)
	{
		//modelFileHelper = Config.Cosmetics.Dante.modelFileHelper[fileHelperCostume];
		modelFileHelper = Dante_modelFileHelper[fileHelperCostume];
	}
	else if constexpr (fileHelperCharacter == CHAR_VERGIL)
	{
		//modelFileHelper = Config.Cosmetics.Vergil.modelFileHelper[fileHelperCostume];
		modelFileHelper = Vergil_modelFileHelper[fileHelperCostume];
	}

	modelData = (MODEL_DATA *)(baseAddr + 0xB630);

	// Base

	{
		auto & fileHelper = modelFileHelper[MODEL_PART_BASE];

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

	// Amulet

	if constexpr
	(
		(costume == COSTUME_DANTE_DEFAULT_NO_COAT) ||
		(costume == COSTUME_DANTE_DMC1_NO_COAT   )
	)
	{
		auto & fileHelper = modelFileHelper[MODEL_PART_AMULET];

		dest = (baseAddr + 0x7540 + (submodelIndex * 0x780));
		dest2 = (baseAddr + 0xA0D0);

		RegisterModel
		(
			dest,
			System_File_cacheFile[fileHelper.model.cacheFileId][fileHelper.model.fileIndex],
			System_File_cacheFile[fileHelper.texture.cacheFileId][fileHelper.texture.fileIndex]
		);

		func_8A000(dest, 0, dest2);

		((uint8 *)(baseAddr + 0x9AC0))[submodelIndex] = 1;

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

	// Coat

	if constexpr
	(
		(costume == COSTUME_DANTE_DEFAULT     ) ||
		(costume == COSTUME_DANTE_DEFAULT_TORN) ||
		(costume == COSTUME_DANTE_DMC1        ) ||
		(costume == COSTUME_DANTE_SPARDA      )
	)
	{
		auto & fileHelper = modelFileHelper[MODEL_PART_COAT];

		dest = (baseAddr + 0x7540 + (submodelIndex * 0x780));
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
			(baseAddr + 0x9D10 + (submodelIndex * 0xC0)),
			System_File_cacheFile[fileHelper.shadow.cacheFileId][fileHelper.shadow.fileIndex]
		);

		((uint8 *)(baseAddr + 0x9AC0))[submodelIndex] = 1;

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

constexpr uint32 devilModelDataOffVergil[MAX_DEVIL_VERGIL] =
{
	0xB640,
	0xB640,
};

template <
	uint8 character          ,
	uint8 devil              ,
	uint8 fileHelperCharacter,
	uint8 fileHelperDevil
>
void UpdateDevilModelTemplate
(
	byte8 * baseAddr,
	uint8   slot
)
{
	uint8 modelIndex = 0;
	uint8 modelOff   = 0;

	uint8 submodelIndex = 0;

	MODEL_DATA * modelData = 0;

	uint8 devilModelOff = 0;
	
	uint8 devilSubmodelIndex = 0;

	DEVIL_MODEL_FILE_HELPER * devilModelFileHelper = 0;

	DEVIL_MODEL_DATA * devilModelData = 0;

	byte8 * dest  = 0;
	byte8 * dest2 = 0;

	auto CopyVertices = [&]
	(
		byte8 * baseAddr,
		uint8   index0,
		uint8   index1,
		uint8   index2
	)
	{
		auto g_vertices = (vec4 *)(appBaseAddr + 0x35D580);
	
		byte8 * dest = 0;
		byte8 * addr = 0;
	
		vec4 * vertices = 0;
	
		dest = (baseAddr + 0xAA00 + (index0 * 0xC0) + (devilSubmodelIndex * 0x300));
	
		addr = *(byte8 **)(baseAddr + 0xA300 + ((devilModelOff + index1) * 8));
		*(byte8 **)(addr + 0x100) = dest;
	
		vertices = (vec4 *)(dest + 0x80);
		vertices[0] = g_vertices[0];
		vertices[1] = g_vertices[1];
		vertices[2] = g_vertices[2];
		vertices[3] = g_vertices[3];

		*(uint32 *)(dest + 0x28) = 1;
		addr = *(byte8 **)(baseAddr + 0x1880 + ((modelOff + index2) * 8));
		addr = *(byte8 **)(addr + 0x110);
		*(byte8 **)(dest + 0x30) = addr;
	};

	modelIndex = (slot == 1) ? 1 : 2;
	modelOff   = (slot == 1) ? 0x18 : 0x30;

	submodelIndex = (slot == 1) ? 1 : 3;

	modelData = (MODEL_DATA *)(baseAddr + 0xB630);

	devilModelOff = (slot == 1) ? 0 : 0x24;

	devilSubmodelIndex = (slot == 1) ? 0 : 2;

	if constexpr (fileHelperCharacter == CHAR_DANTE)
	{
		//devilModelFileHelper = Config.Cosmetics.Dante.devilModelFileHelper[fileHelperDevil];
		devilModelFileHelper = Dante_devilModelFileHelper[fileHelperDevil];
	}
	else if constexpr (fileHelperCharacter == CHAR_VERGIL)
	{
		//devilModelFileHelper = Config.Cosmetics.Vergil.devilModelFileHelper[fileHelperDevil];
		devilModelFileHelper = Vergil_devilModelFileHelper[fileHelperDevil];
	}

	if constexpr (character == CHAR_DANTE)
	{
		devilModelData = (DEVIL_MODEL_DATA *)(baseAddr + devilModelDataOffDante[devil]);
	}
	else if constexpr (character == CHAR_VERGIL)
	{
		devilModelData = (DEVIL_MODEL_DATA *)(baseAddr + devilModelDataOffVergil[devil]);
	}

	((uint32 *)(baseAddr + 0x3E74))[slot] = devil;

	devilModelData->modelIndex = modelIndex;
	devilModelData->modelOff   = modelOff;

	// Base

	{
		auto & fileHelper = devilModelFileHelper[DEVIL_MODEL_PART_BASE];

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

	if constexpr (devil == DEVIL_DANTE_AGNI_RUDRA)
	{
		return;
	}

	// Wings

	if constexpr
	(
		(devil == DEVIL_DANTE_REBELLION) ||
		(devil == DEVIL_DANTE_NEVAN    )
	)
	{
		auto & fileHelper = devilModelFileHelper[DEVIL_MODEL_PART_WINGS];

		dest = (baseAddr + 0x7540 + (submodelIndex * 0x780));
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
			(baseAddr + 0x9D10 + (submodelIndex * 0xC0)),
			System_File_cacheFile[fileHelper.shadow.cacheFileId][fileHelper.shadow.fileIndex]
		);

		((uint8 *)(baseAddr + 0x9AC0))[submodelIndex] = 1;

		dest = (baseAddr + 0xA540 + (devilSubmodelIndex * 0xF0));

		RegisterPhysics
		(
			dest,
			dest2,
			System_File_cacheFile[fileHelper.physics.cacheFileId][fileHelper.physics.fileIndex]
		);

		CopyVertices(baseAddr, 0, 1 , 3);
		CopyVertices(baseAddr, 1, 12, 2);

		devilModelData->submodelData[0].submodelIndex      = submodelIndex;
		devilModelData->submodelData[0].devilModelOff      = devilModelOff;
		devilModelData->submodelData[0].devilSubmodelIndex = devilSubmodelIndex;

		submodelIndex++;
		devilModelOff += 9;
		devilSubmodelIndex++;
	}


	//devilModelData->submodelData[1].submodelIndex      = 0;
	//devilModelData->submodelData[1].devilModelOff      = 0;
	//devilModelData->submodelData[1].devilSubmodelIndex = 0;


	//return;

	// Coat

	{
		auto & fileHelper = devilModelFileHelper[DEVIL_MODEL_PART_COAT];

		dest = (baseAddr + 0x7540 + (submodelIndex * 0x780));

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
			(baseAddr + 0x9D10 + (submodelIndex * 0xC0)),
			System_File_cacheFile[fileHelper.shadow.cacheFileId][fileHelper.shadow.fileIndex]
		);

		((uint8 *)(baseAddr + 0x9AC0))[submodelIndex] = 1;

		dest = (baseAddr + 0xA540 + (devilSubmodelIndex * 0xF0));

		RegisterPhysics
		(
			dest,
			dest2,
			System_File_cacheFile[fileHelper.physics.cacheFileId][fileHelper.physics.fileIndex]
		);

		if constexpr
		(
			(devil == DEVIL_DANTE_REBELLION) ||
			(devil == DEVIL_DANTE_NEVAN    )
		)
		{
			dest = (baseAddr + 0xA540 + (devilSubmodelIndex * 0xF0));

			func_2CA2F0
			(
				dest,
				(baseAddr + ((modelOff + 0x310) * 8)),
				(appBaseAddr + 0x58B380),
				modelData,
				6
			);

			CopyVertices(baseAddr, 0, 1, 2 );
			CopyVertices(baseAddr, 1, 2, 14);
		}
		else if constexpr
		(
			(devil == DEVIL_DANTE_CERBERUS) ||
			(devil == DEVIL_DANTE_BEOWULF )
		)
		{
			CopyVertices(baseAddr, 0, 1, 3 );
			CopyVertices(baseAddr, 1, 2, 6 );
			CopyVertices(baseAddr, 2, 8, 10);
		}

		if constexpr
		(
			(devil == DEVIL_DANTE_REBELLION) ||
			(devil == DEVIL_DANTE_NEVAN)
		)
		{
			devilModelData->submodelData[1].submodelIndex      = submodelIndex;
			devilModelData->submodelData[1].devilModelOff      = devilModelOff;
			devilModelData->submodelData[1].devilSubmodelIndex = devilSubmodelIndex;
		}
		else
		{
			devilModelData->submodelData[0].submodelIndex      = submodelIndex;
			devilModelData->submodelData[0].devilModelOff      = devilModelOff;
			devilModelData->submodelData[0].devilSubmodelIndex = devilSubmodelIndex;
		}
	}
}

PrivateEnd;

Cosmetics_Model_UpdateModel_t Cosmetics_Model_UpdateModelDante[MAX_COSTUME_DANTE] =
{
	UpdateModelTemplate<CHAR_DANTE, COSTUME_DANTE_DEFAULT        , CHAR_DANTE, COSTUME_DANTE_DEFAULT        >,
	UpdateModelTemplate<CHAR_DANTE, COSTUME_DANTE_DEFAULT_NO_COAT, CHAR_DANTE, COSTUME_DANTE_DEFAULT_NO_COAT>,
	UpdateModelTemplate<CHAR_DANTE, COSTUME_DANTE_DEFAULT_TORN   , CHAR_DANTE, COSTUME_DANTE_DEFAULT_TORN   >,
	UpdateModelTemplate<CHAR_DANTE, COSTUME_DANTE_DMC1           , CHAR_DANTE, COSTUME_DANTE_DMC1           >,
	UpdateModelTemplate<CHAR_DANTE, COSTUME_DANTE_DMC1_NO_COAT   , CHAR_DANTE, COSTUME_DANTE_DMC1_NO_COAT   >,
	UpdateModelTemplate<CHAR_DANTE, COSTUME_DANTE_SPARDA         , CHAR_DANTE, COSTUME_DANTE_SPARDA         >,
};

Cosmetics_Model_UpdateModel_t Cosmetics_Model_UpdateModelDanteVergil[MAX_COSTUME_VERGIL] =
{
	UpdateModelTemplate<CHAR_DANTE, COSTUME_DANTE_DEFAULT        , CHAR_VERGIL, COSTUME_VERGIL_DEFAULT        >,
	UpdateModelTemplate<CHAR_DANTE, COSTUME_DANTE_DEFAULT_NO_COAT, CHAR_VERGIL, COSTUME_VERGIL_DEFAULT_NO_COAT>,
	UpdateModelTemplate<CHAR_DANTE, COSTUME_DANTE_SPARDA         , CHAR_VERGIL, COSTUME_VERGIL_SPARDA         >,
};

Cosmetics_Model_UpdateDevilModel_t Cosmetics_Model_UpdateDevilModelDante[MAX_DEVIL_DANTE] =
{
	UpdateDevilModelTemplate<CHAR_DANTE, DEVIL_DANTE_REBELLION , CHAR_DANTE, DEVIL_DANTE_REBELLION >,
	UpdateDevilModelTemplate<CHAR_DANTE, DEVIL_DANTE_CERBERUS  , CHAR_DANTE, DEVIL_DANTE_CERBERUS  >,
	UpdateDevilModelTemplate<CHAR_DANTE, DEVIL_DANTE_AGNI_RUDRA, CHAR_DANTE, DEVIL_DANTE_AGNI_RUDRA>,
	UpdateDevilModelTemplate<CHAR_DANTE, DEVIL_DANTE_NEVAN     , CHAR_DANTE, DEVIL_DANTE_NEVAN     >,
	UpdateDevilModelTemplate<CHAR_DANTE, DEVIL_DANTE_BEOWULF   , CHAR_DANTE, DEVIL_DANTE_BEOWULF   >,
	UpdateDevilModelTemplate<CHAR_DANTE, DEVIL_DANTE_SPARDA    , CHAR_DANTE, DEVIL_DANTE_SPARDA    >,
};

Cosmetics_Model_UpdateDevilModel_t Cosmetics_Model_UpdateDevilModelDanteVergil[MAX_DEVIL_VERGIL] =
{
	UpdateDevilModelTemplate<CHAR_DANTE, DEVIL_DANTE_REBELLION, CHAR_VERGIL, DEVIL_VERGIL_YAMATO >,
	UpdateDevilModelTemplate<CHAR_DANTE, DEVIL_DANTE_BEOWULF  , CHAR_VERGIL, DEVIL_VERGIL_BEOWULF>,
};

void Cosmetics_Model_Init()
{
	LogFunction();

	for (uint8 index = 0; index < countof(Cosmetics_Model_UpdateModelDante); index++)
	{
		auto func = CreateFunction(Cosmetics_Model_UpdateModelDante[index]);
		Log("Cosmetics_Model_UpdateModelDante[%u] %llX", index, func.addr);
	}

	for (uint8 index = 0; index < countof(Cosmetics_Model_UpdateModelDanteVergil); index++)
	{
		auto func = CreateFunction(Cosmetics_Model_UpdateModelDanteVergil[index]);
		Log("Cosmetics_Model_UpdateModelDanteVergil[%u] %llX", index, func.addr);
	}

	for (uint8 index = 0; index < countof(Cosmetics_Model_UpdateDevilModelDante); index++)
	{
		Log("Cosmetics_Model_UpdateDevilModelDante[%u] %llX", index, Cosmetics_Model_UpdateDevilModelDante[index]);
	}
}
