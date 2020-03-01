
// @Todo: Change clothFile to file.
// @Todo: Add descriptions.

#pragma once
#include "../Core/Core.h"

// Reset Model Data

typedef void(__fastcall * func_897B0_t)(byte8 * dest);
typedef void(__fastcall * func_89450_t)(byte8 * dest);
typedef void(__fastcall * func_89270_t)(byte8 * dest);

// Set Model State

typedef void (__fastcall * func_8B470_t)
(
	byte8  * dest,
	uint32   flag
);

// Register Model

typedef void (__fastcall * func_89960_t)
(
	byte8 * dest,
	byte8 * modelFile,
	byte8 * textureFile
);

typedef byte8 * (__fastcall * func_89DE0_t)
(
	byte8 * dest
);

typedef void (__fastcall * func_8BC60_t)
(
	byte8 * dest,
	byte8 * addr,
	byte8 * shadowFile
);

typedef void (__fastcall * func_305D80_t)
(
	byte8 * dest
);

typedef void (__fastcall * func_8A000_t)
(
	byte8 * dest,
	byte8 * motionArchive,
	byte8 * addr
);

typedef uint32 (__fastcall * func_2C9F40_t)
(
	byte8 * clothFile
);

typedef void (__fastcall * func_2CA1D0_t)
(
	byte8  * dest,
	byte8  * addr,
	byte8  * clothFile,
	uint32   index
);

typedef void (__fastcall * func_2CA2F0_t)
(
	byte8  * dest,
	byte8  * addr,
	byte8  * unknown,
	byte8  * modelData,
	uint32   count
);

typedef void(__fastcall * func_1EF040_t)
(
	byte8  * baseAddr,
	uint32   index
);

// Actor Spawn Functions

typedef byte8 *(__fastcall * func_1DE820_t)
(
	uint8 characterId,
	uint8 actorId,
	bool  isDoppelganger
);

typedef void (__fastcall * func_1DF240_t)
(
	byte8 * baseAddr,
	byte8 * sessionData
);

typedef void(__fastcall * func_1F92C0_t)
(
	byte8  * dest,
	byte32   flag
);

typedef void(__fastcall * func_1F97F0_t)
(
	byte8  * dest,
	byte32   flag
);

extern func_897B0_t  func_897B0;
extern func_89450_t  func_89450;
extern func_89270_t  func_89270;
extern func_8B470_t  func_8B470;
extern func_89960_t  func_89960;
extern func_89DE0_t  func_89DE0;
extern func_8BC60_t  func_8BC60;
extern func_305D80_t func_305D80;
extern func_8A000_t  func_8A000;
extern func_2C9F40_t func_2C9F40;
extern func_2CA1D0_t func_2CA1D0;
extern func_2CA2F0_t func_2CA2F0;
extern func_1EF040_t func_1EF040;
extern func_1DE820_t func_1DE820;
extern func_1DF240_t func_1DF240;
extern func_1F92C0_t func_1F92C0;
extern func_1F97F0_t func_1F97F0;

void Internal_Init();
