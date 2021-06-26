module;
#include <xmmintrin.h>
export module Internal;

import Core;

#include "../Core/Macros.h"

import Vars;

// $DataStart

export typedef void(__fastcall * func_897B0_t)(ModelData & modelData);
export typedef void(__fastcall * func_89450_t)(ModelData & modelData);
export typedef void(__fastcall * func_89270_t)(ModelData & modelData);
export typedef void(__fastcall * func_8B470_t)(ModelData & modelData, bool32 enable);
export typedef void(__fastcall * func_89960_t)(ModelData & modelData, byte8 * modelFile, byte8 * textureFile);
export typedef void(__fastcall * func_1EF040_t)(byte8 * actorData, uint32 index);
export typedef byte8 *(__fastcall * func_89DE0_t)(ModelData & modelData);
export typedef void(__fastcall * func_8BC60_t)(ShadowData & shadowData, byte8 * dest, byte8 * file);
export typedef void(__fastcall * func_305D80_t)(byte8 * dest);
export typedef void(__fastcall * func_8A000_t)(ModelData & modelData, byte8 * motionFile, PhysicsMetadata ** modelPhysicsMetadataPool);
export typedef uint32(__fastcall * func_2C9F40_t)(byte8 * physicsFile);
export typedef void(__fastcall * func_2CA1D0_t)(PhysicsData & physicsData, PhysicsMetadata ** physicsMetadata, byte8 * physicsFile, uint32 index);
export typedef void(__fastcall * func_2CA2F0_t)(PhysicsData & physicsData, void * dest, byte8 * addr, ModelMetadata * modelMetadata, uint32 count);
export typedef void *(__fastcall * func_2C6150_t)(void * dest, uint32 size, int32 mode); // Alloc
export typedef bool(__fastcall * func_1FD3E0_t)(WeaponData & weaponData, uint8); // IsWeaponReady
export typedef void(__fastcall * func_1FDE10_t)(WeaponData & weaponData); // Show Weapon
export typedef void(__fastcall * func_8BF30_t)(uint32 index, void * dest, byte8 * baseAddr);
export typedef void(__fastcall * func_2EDFC0_t)(byte8 *);
export typedef void(__fastcall * func_337710_t)(byte8 *);
export typedef bool(__fastcall * func_27AA90_t)(void *, uint32, void *, float);
export typedef byte8 *(__fastcall * func_1A4680_t)(byte8 *, const CreateEnemyActorData &); // Create Enemy Actor
export typedef void(__fastcall * func_3391C0_t)(void *, int32, int32, int32, int32); // Play Sound
export typedef void(__fastcall * func_2EE3D0_t)(byte8 * dest);
export typedef void(__fastcall * func_1FAF40_t)(byte8 * baseAddr);
export typedef void(__fastcall * func_1EEF80_t)(byte8 * baseAddr);
export typedef bool(__fastcall * func_2EE060_t)(byte8 * dest, uint32 size);
export typedef byte8 *(__fastcall * func_1DE820_t)(uint32 character, uint32 id, bool isClone); // Create Actor
export typedef void(__fastcall * func_217B90_t)(byte8 * actorData, ActiveMissionActorData & activeMissionActorData); // Init Actor Dante
export typedef void(__fastcall * func_226F10_t)(byte8 * actorData, ActiveMissionActorData & activeMissionActorData); // Init Actor Bob
export typedef void(__fastcall * func_219660_t)(byte8 * actorData, ActiveMissionActorData & activeMissionActorData); // Init Actor Lady
export typedef void(__fastcall * func_223CB0_t)(byte8 * actorData, ActiveMissionActorData & activeMissionActorData); // Init Actor Vergil
export typedef void(__fastcall * func_212BE0_t)(byte8 * actorData); // Update Actor Dante
export typedef void(__fastcall * func_225D70_t)(byte8 * actorData); // Update Actor Bob
export typedef void(__fastcall * func_219260_t)(byte8 * actorData); // Update Actor Lady
export typedef void(__fastcall * func_220970_t)(byte8 * actorData); // Update Actor Vergil
export typedef void(__fastcall * func_1DFC20_t)(byte8 * actorData);
export typedef WeaponData *(__fastcall * func_2310B0_t)(byte8 * actorData, uint32 id); // Dante Rebellion
export typedef WeaponData *(__fastcall * func_22EC90_t)(byte8 * actorData, uint32 id); // Dante Cerberus
export typedef WeaponData *(__fastcall * func_227870_t)(byte8 * actorData, uint32 id); // Dante Agni & Rudra
export typedef WeaponData *(__fastcall * func_22A1E0_t)(byte8 * actorData, uint32 id); // Dante Nevan
export typedef WeaponData *(__fastcall * func_228CF0_t)(byte8 * actorData, uint32 id); // Dante Vergil Beowulf
export typedef WeaponData *(__fastcall * func_22B0C0_t)(byte8 * actorData, uint32 id); // Dante Ebony & Ivory
export typedef WeaponData *(__fastcall * func_2306B0_t)(byte8 * actorData, uint32 id); // Dante Shotgun
export typedef WeaponData *(__fastcall * func_22C4A0_t)(byte8 * actorData, uint32 id); // Dante Artemis
export typedef WeaponData *(__fastcall * func_2300A0_t)(byte8 * actorData, uint32 id); // Dante Spiral
export typedef WeaponData *(__fastcall * func_22BA30_t)(byte8 * actorData, uint32 id); // Dante Lady Kalina Ann
export typedef WeaponData *(__fastcall * func_231A30_t)(byte8 * actorData, uint32 id); // Bob Yamato
export typedef WeaponData *(__fastcall * func_22D960_t)(byte8 * actorData, uint32 id); // Vergil Yamato
export typedef WeaponData *(__fastcall * func_2298E0_t)(byte8 * actorData, uint32 id); // Vergil Force Edge
export typedef WeaponData *(__fastcall * func_22CF00_t)(byte8 * actorData, uint32 id); // Vergil Nero Angelo Sword
export typedef void(__fastcall * func_280120_t)(byte8 * dest, uint32 side, uint32 index); // Weapon Switch Animation Dante
export typedef void(__fastcall * func_280160_t)(byte8 * dest, uint32 group, uint32 index, uint32 motion); // Weapon Switch Animation Vergil
export typedef void(__fastcall * func_1EB0E0_t)(byte8 * actorData, uint32 index); // Call after Weapon Switch Animation.
export typedef void(__fastcall * func_1F92C0_t)(byte8 * actorData, uint32 phase); // Queue devil model update.
export typedef void(__fastcall * func_1F97F0_t)(byte8 * actorData, bool noMotion); // Update devil model and play motion.
export typedef void(__fastcall * func_1F94D0_t)(byte8 * actorData, uint8 index); // Devil Flux
export typedef void(__fastcall * func_1EAE60_t)(byte8 * actorData, uint8 index); // Play Doppelganger Effect
export typedef void(__fastcall * func_1FCA20_t)(byte8 * actorBaseAddr, uint32 visibility); // Update Color Matrices
export typedef float32(__fastcall * func_32E5F0_t)(vec4 & position);
export typedef void(__fastcall * func_89E30_t)(ModelData & modelData, uint32 index); // Call after icon update.
export typedef void(__fastcall * func_1B9FA0_t)(byte8 * addr); // Adjust file pointers.
export typedef void(__fastcall * func_223AC0_t)(byte8 * actorData); // Create Spiral Swords.
export typedef void(__fastcall * func_223F50_t)(byte8 * actorData, uint32 index); // Specific Summoned Swords.
export typedef void(__fastcall * func_223BE0_t)(byte8 * actorData, uint32 index); // Shoot Summoned Sword. Use index 52.
export typedef void(__fastcall * func_594B0_t)(BodyPartData & bodyPartData, byte8 * file, uint32 bodyPart, uint32, byte8 ** motionArchives, byte8 *** modelDataFunctions, PhysicsMetadata ** modelPhysicsMetadataPool, float32 * motionSpeed, void *);
export typedef void(__fastcall * func_5A290_t)(byte8 * body, uint32 group, uint32 index, uint16, uint8, uint8); // Play Motion
export typedef void(__fastcall * func_8AC80_t)(ModelData & modelData, uint32 bodyPart, byte8 * motionFile, uint32, bool); // Play Motion
export typedef void(__fastcall * func_1EFB90_t)(byte8 * actorData, uint32 group, uint32 index, float32, int8, uint8, uint8); // Play motion and update state.
export typedef void(__fastcall * func_1DFDA0_t)(byte8 *, uint32, uint8, float32, float32, uint8); // Drop1
export typedef void(__fastcall * func_1FB300_t)(byte8 * actorData, uint32 direction, float32 value); // Adjust Position
export typedef void(__fastcall * func_1E09D0_t)(byte8 * actorBaseAddr, uint32 event);
export typedef byte8 *(__fastcall * func_175210_t)(vec4 *, vec4 *, __m128); // Boss Lady Grenade
export typedef void(__fastcall * func_1E0800_t)(byte8 * actorData, uint32 index, uint32, uint32); // Trigger Attack
export typedef void(__fastcall * func_211100_t)(byte8 * actorData); // Rebellion Combo 1 Part 3
export typedef void(__fastcall * func_1F01F0_t)(byte8 * actorData, uint32 index); // Reset State
export typedef void(__fastcall * func_2F74E0_t)(byte8 * dest, uint32 index); // Show Model Partition
export typedef void(__fastcall * func_2F7350_t)(byte8 * dest, uint32 index); // Hide Model Partition
export typedef void(__fastcall * func_32BE20_t)(byte8 * dest); // Init Track
export typedef void(__fastcall * func_32BA90_t)(byte8 * dest, const char * filename, uint32, uint32); // Set Track
export typedef byte8 *(__fastcall * func_8A520_t)(ModelData & modelData);
export typedef void(__fastcall * func_30E630_t)(byte8 * dest, uint32 index);

export func_897B0_t func_897B0 = 0; // (ModelData & modelData)
export func_89450_t func_89450 = 0; // (ModelData & modelData)
export func_89270_t func_89270 = 0; // (ModelData & modelData)
export func_8B470_t func_8B470 = 0; // (ModelData & modelData, bool32 enable)
export func_89960_t func_89960 = 0; // (ModelData & modelData, byte8 * modelFile, byte8 * textureFile)
export func_1EF040_t func_1EF040 = 0; // (byte8 * actorData, uint32 index)
export func_89DE0_t func_89DE0 = 0; // (ModelData & modelData)
export func_8BC60_t func_8BC60 = 0; // (ShadowData & shadowData, byte8 * dest, byte8 * file)
export func_305D80_t func_305D80 = 0; // (byte8 * dest)
export func_8A000_t func_8A000 = 0; // (ModelData & modelData, byte8 * motionFile, PhysicsMetadata ** modelPhysicsMetadataPool)
export func_2C9F40_t func_2C9F40 = 0; // (byte8 * physicsFile)
export func_2CA1D0_t func_2CA1D0 = 0; // (PhysicsData & physicsData, PhysicsMetadata ** physicsMetadata, byte8 * physicsFile, uint32 index)
export func_2CA2F0_t func_2CA2F0 = 0; // (PhysicsData & physicsData, void * dest, byte8 * addr, ModelMetadata * modelMetadata, uint32 count)
export func_2C6150_t func_2C6150 = 0; // (void * dest, uint32 size, int32 mode)
export func_1FD3E0_t func_1FD3E0 = 0; // (WeaponData & weaponData, uint8)
export func_1FDE10_t func_1FDE10 = 0; // (WeaponData & weaponData)
export func_8BF30_t func_8BF30 = 0; // (uint32 index, void * dest, byte8 * baseAddr)
export func_2EDFC0_t func_2EDFC0 = 0; // (byte8 *)
export func_337710_t func_337710 = 0; // (byte8 *)
export func_27AA90_t func_27AA90 = 0; // (void *, uint32, void *, float)
export func_1A4680_t func_1A4680 = 0; // (byte8 *, const CreateEnemyActorData &)
export func_3391C0_t func_3391C0 = 0; // (void *, int32, int32, int32, int32)
export func_2EE3D0_t func_2EE3D0 = 0; // (byte8 * dest)
export func_1FAF40_t func_1FAF40 = 0; // (byte8 * baseAddr)
export func_1EEF80_t func_1EEF80 = 0; // (byte8 * baseAddr)
export func_2EE060_t func_2EE060 = 0; // (byte8 * dest, uint32 size)
export func_1DE820_t func_1DE820 = 0; // (uint32 character, uint32 id, bool isClone)
export func_217B90_t func_217B90 = 0; // (byte8 * actorData, ActiveMissionActorData & activeMissionActorData)
export func_226F10_t func_226F10 = 0; // (byte8 * actorData, ActiveMissionActorData & activeMissionActorData)
export func_219660_t func_219660 = 0; // (byte8 * actorData, ActiveMissionActorData & activeMissionActorData)
export func_223CB0_t func_223CB0 = 0; // (byte8 * actorData, ActiveMissionActorData & activeMissionActorData)
export func_212BE0_t func_212BE0 = 0; // (byte8 * actorData)
export func_225D70_t func_225D70 = 0; // (byte8 * actorData)
export func_219260_t func_219260 = 0; // (byte8 * actorData)
export func_220970_t func_220970 = 0; // (byte8 * actorData)
export func_1DFC20_t func_1DFC20 = 0; // (byte8 * actorData)
export func_2310B0_t func_2310B0 = 0; // (byte8 * actorData, uint32 id)
export func_22EC90_t func_22EC90 = 0; // (byte8 * actorData, uint32 id)
export func_227870_t func_227870 = 0; // (byte8 * actorData, uint32 id)
export func_22A1E0_t func_22A1E0 = 0; // (byte8 * actorData, uint32 id)
export func_228CF0_t func_228CF0 = 0; // (byte8 * actorData, uint32 id)
export func_22B0C0_t func_22B0C0 = 0; // (byte8 * actorData, uint32 id)
export func_2306B0_t func_2306B0 = 0; // (byte8 * actorData, uint32 id)
export func_22C4A0_t func_22C4A0 = 0; // (byte8 * actorData, uint32 id)
export func_2300A0_t func_2300A0 = 0; // (byte8 * actorData, uint32 id)
export func_22BA30_t func_22BA30 = 0; // (byte8 * actorData, uint32 id)
export func_231A30_t func_231A30 = 0; // (byte8 * actorData, uint32 id)
export func_22D960_t func_22D960 = 0; // (byte8 * actorData, uint32 id)
export func_2298E0_t func_2298E0 = 0; // (byte8 * actorData, uint32 id)
export func_22CF00_t func_22CF00 = 0; // (byte8 * actorData, uint32 id)
export func_280120_t func_280120 = 0; // (byte8 * dest, uint32 side, uint32 index)
export func_280160_t func_280160 = 0; // (byte8 * dest, uint32 group, uint32 index, uint32 motion)
export func_1EB0E0_t func_1EB0E0 = 0; // (byte8 * actorData, uint32 index)
export func_1F92C0_t func_1F92C0 = 0; // (byte8 * actorData, uint32 phase)
export func_1F97F0_t func_1F97F0 = 0; // (byte8 * actorData, bool noMotion)
export func_1F94D0_t func_1F94D0 = 0; // (byte8 * actorData, uint8 index)
export func_1EAE60_t func_1EAE60 = 0; // (byte8 * actorData, uint8 index)
export func_1FCA20_t func_1FCA20 = 0; // (byte8 * actorBaseAddr, uint32 visibility)
export func_32E5F0_t func_32E5F0 = 0; // (vec4 & position)
export func_89E30_t func_89E30 = 0; // (ModelData & modelData, uint32 index)
export func_1B9FA0_t func_1B9FA0 = 0; // (byte8 * addr)
export func_223AC0_t func_223AC0 = 0; // (byte8 * actorData)
export func_223F50_t func_223F50 = 0; // (byte8 * actorData, uint32 index)
export func_223BE0_t func_223BE0 = 0; // (byte8 * actorData, uint32 index)
export func_594B0_t func_594B0 = 0; // (BodyPartData & bodyPartData, byte8 * file, uint32 bodyPart, uint32, byte8 ** motionArchives, byte8 *** modelDataFunctions, PhysicsMetadata ** modelPhysicsMetadataPool, float32 * motionSpeed, void *)
export func_5A290_t func_5A290 = 0; // (byte8 * body, uint32 group, uint32 index, uint16, uint8, uint8)
export func_8AC80_t func_8AC80 = 0; // (ModelData & modelData, uint32 bodyPart, byte8 * motionFile, uint32, bool)
export func_1EFB90_t func_1EFB90 = 0; // (byte8 * actorData, uint32 group, uint32 index, float32, int8, uint8, uint8)
export func_1DFDA0_t func_1DFDA0 = 0; // (byte8 *, uint32, uint8, float32, float32, uint8)
export func_1FB300_t func_1FB300 = 0; // (byte8 * actorData, uint32 direction, float32 value)
export func_1E09D0_t func_1E09D0 = 0; // (byte8 * actorBaseAddr, uint32 event)
export func_175210_t func_175210 = 0; // (vec4 *, vec4 *, __m128)
export func_1E0800_t func_1E0800 = 0; // (byte8 * actorData, uint32 index, uint32, uint32)
export func_211100_t func_211100 = 0; // (byte8 * actorData)
export func_1F01F0_t func_1F01F0 = 0; // (byte8 * actorData, uint32 index)
export func_2F74E0_t func_2F74E0 = 0; // (byte8 * dest, uint32 index)
export func_2F7350_t func_2F7350 = 0; // (byte8 * dest, uint32 index)
export func_32BE20_t func_32BE20 = 0; // (byte8 * dest)
export func_32BA90_t func_32BA90 = 0; // (byte8 * dest, const char * filename, uint32, uint32)
export func_8A520_t func_8A520 = 0; // (ModelData & modelData)
export func_30E630_t func_30E630 = 0; // (byte8 * dest, uint32 index)

export void Internal_Init()
{
	LogFunction();
	{
		auto func = CreateFunction((appBaseAddr + 0x897B0));
		func_897B0 = (func_897B0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x89450));
		func_89450 = (func_89450_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x89270));
		func_89270 = (func_89270_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x8B470));
		func_8B470 = (func_8B470_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x89960));
		func_89960 = (func_89960_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1EF040));
		func_1EF040 = (func_1EF040_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x89DE0), 0, true, false);
		func_89DE0 = (func_89DE0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x8BC60));
		func_8BC60 = (func_8BC60_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x305D80));
		func_305D80 = (func_305D80_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x8A000));
		func_8A000 = (func_8A000_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x2C9F40), 0, true, false);
		func_2C9F40 = (func_2C9F40_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x2CA1D0));
		func_2CA1D0 = (func_2CA1D0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x2CA2F0), 0, true, true, 0, 0, 0, 0, 1);
		func_2CA2F0 = (func_2CA2F0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x2C6150));
		func_2C6150 = (func_2C6150_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1FD3E0));
		func_1FD3E0 = (func_1FD3E0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1FDE10));
		func_1FDE10 = (func_1FDE10_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x8BF30));
		func_8BF30 = (func_8BF30_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x2EDFC0));
		func_2EDFC0 = (func_2EDFC0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x337710));
		func_337710 = (func_337710_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x27AA90));
		func_27AA90 = (func_27AA90_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1A4680), 0, true, false);
		func_1A4680 = (func_1A4680_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x3391C0), 0, true, true, 0, 0, 0, 0, 1);
		func_3391C0 = (func_3391C0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x2EE3D0));
		func_2EE3D0 = (func_2EE3D0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1FAF40));
		func_1FAF40 = (func_1FAF40_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1EEF80));
		func_1EEF80 = (func_1EEF80_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x2EE060));
		func_2EE060 = (func_2EE060_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1DE820), 0, true, false);
		func_1DE820 = (func_1DE820_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x217B90));
		func_217B90 = (func_217B90_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x226F10));
		func_226F10 = (func_226F10_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x219660));
		func_219660 = (func_219660_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x223CB0));
		func_223CB0 = (func_223CB0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x212BE0));
		func_212BE0 = (func_212BE0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x225D70));
		func_225D70 = (func_225D70_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x219260));
		func_219260 = (func_219260_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x220970));
		func_220970 = (func_220970_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1DFC20));
		func_1DFC20 = (func_1DFC20_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x2310B0), 0, true, false);
		func_2310B0 = (func_2310B0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x22EC90), 0, true, false);
		func_22EC90 = (func_22EC90_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x227870), 0, true, false);
		func_227870 = (func_227870_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x22A1E0), 0, true, false);
		func_22A1E0 = (func_22A1E0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x228CF0), 0, true, false);
		func_228CF0 = (func_228CF0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x22B0C0), 0, true, false);
		func_22B0C0 = (func_22B0C0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x2306B0), 0, true, false);
		func_2306B0 = (func_2306B0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x22C4A0), 0, true, false);
		func_22C4A0 = (func_22C4A0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x2300A0), 0, true, false);
		func_2300A0 = (func_2300A0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x22BA30), 0, true, false);
		func_22BA30 = (func_22BA30_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x231A30), 0, true, false);
		func_231A30 = (func_231A30_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x22D960), 0, true, false);
		func_22D960 = (func_22D960_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x2298E0), 0, true, false);
		func_2298E0 = (func_2298E0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x22CF00), 0, true, false);
		func_22CF00 = (func_22CF00_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x280120));
		func_280120 = (func_280120_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x280160));
		func_280160 = (func_280160_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1EB0E0));
		func_1EB0E0 = (func_1EB0E0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1F92C0));
		func_1F92C0 = (func_1F92C0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1F97F0));
		func_1F97F0 = (func_1F97F0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1F94D0));
		func_1F94D0 = (func_1F94D0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1EAE60));
		func_1EAE60 = (func_1EAE60_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1FCA20));
		func_1FCA20 = (func_1FCA20_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x32E5F0), 0, true, false);
		func_32E5F0 = (func_32E5F0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x89E30));
		func_89E30 = (func_89E30_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1B9FA0));
		func_1B9FA0 = (func_1B9FA0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x223AC0));
		func_223AC0 = (func_223AC0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x223F50));
		func_223F50 = (func_223F50_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x223BE0));
		func_223BE0 = (func_223BE0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x594B0), 0, true, true, 0, 0, 0, 0, 5);
		func_594B0 = (func_594B0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x5A290), 0, true, true, 0, 0, 0, 0, 2);
		func_5A290 = (func_5A290_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x8AC80), 0, true, true, 0, 0, 0, 0, 1);
		func_8AC80 = (func_8AC80_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1EFB90), 0, true, true, 0, 0, 0, 0, 3);
		func_1EFB90 = (func_1EFB90_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1DFDA0), 0, true, true, 0, 0, 0, 0, 2);
		func_1DFDA0 = (func_1DFDA0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1FB300));
		func_1FB300 = (func_1FB300_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1E09D0));
		func_1E09D0 = (func_1E09D0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x175210), 0, true, false, 0, 0, 0, 0, 0, false, true);
		func_175210 = (func_175210_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1E0800));
		func_1E0800 = (func_1E0800_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x211100));
		func_211100 = (func_211100_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1F01F0));
		func_1F01F0 = (func_1F01F0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x2F74E0));
		func_2F74E0 = (func_2F74E0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x2F7350));
		func_2F7350 = (func_2F7350_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x32BE20));
		func_32BE20 = (func_32BE20_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x32BA90));
		func_32BA90 = (func_32BA90_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x8A520), 0, true, false);
		func_8A520 = (func_8A520_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x30E630));
		func_30E630 = (func_30E630_t)func.addr;
	}
}

// $DataEnd
