#ifndef __MODULE_MODEL__
#define __MODULE_MODEL__

module;
#include "../Core/Core.h"

#include "Vars.h"
export module ModuleName(Model);

import ModuleName(Internal);

#ifdef __INTELLISENSE__
#include "Internal.ixx"
#endif

export void RegisterModel
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

export void RegisterShadow
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
	func_305D80(dest);
}

export void RegisterPhysics
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

export void ResetModel(ModelData & modelData)
{
	func_897B0(modelData);
	func_89450(modelData);
	memset(&modelData, 0, sizeof(ModelData));
	func_89270(modelData);
}

#endif

#ifdef __GARBAGE__
#endif
