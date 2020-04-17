#pragma once
#include "../Core/Core.h"

#include "Vars.h"

typedef void(__fastcall * func_897B0_t)(byte8 * dest);
typedef void(__fastcall * func_89450_t)(byte8 * dest);
typedef void(__fastcall * func_89270_t)(byte8 * dest);
typedef void(__fastcall * func_8B470_t)(byte8 * dest, uint32 flag);
typedef void(__fastcall * func_89960_t)(byte8 * dest, byte8 * modelFile, byte8 * textureFile);
typedef byte8 *(__fastcall * func_89DE0_t)(byte8 * dest);
typedef void(__fastcall * func_8BC60_t)(byte8 * dest, byte8 * addr, byte8 * shadowFile);
typedef void(__fastcall * func_305D80_t)(byte8 * dest);
typedef void(__fastcall * func_8A000_t)(byte8 * dest, byte8 * motionFile, byte8 * addr);
typedef uint32(__fastcall * func_2C9F40_t)(byte8 * physicsFile);
typedef void(__fastcall * func_2CA1D0_t)(byte8 * dest, byte8 * addr, byte8 * physicsFile, uint32 index);
typedef void(__fastcall * func_2CA2F0_t)(byte8 * dest, byte8 * addr, byte8 *, MODEL_METADATA * modelData, uint32 count);
typedef void(__fastcall * func_1EF040_t)(byte8 * baseAddr, uint32 index);
typedef void(__fastcall * func_2EE3D0_t)(byte8 * dest);
typedef void(__fastcall * func_1FAF40_t)(byte8 * baseAddr);
typedef void(__fastcall * func_1EEF80_t)(byte8 * baseAddr);
typedef bool(__fastcall * func_2EE060_t)(byte8 * dest, uint32 size);
typedef byte8 *(__fastcall * func_1DE820_t)(uint32 character, uint32 id, bool isClone); // Create Actor
typedef void(__fastcall * func_1BB390_t)(byte8 ** pool, uint32 actor);
typedef void(__fastcall * func_217B90_t)(byte8 * baseAddr, byte8 * sessionData);
typedef void(__fastcall * func_223CB0_t)(byte8 * baseAddr, byte8 * sessionData);
typedef void(__fastcall * func_1DFC20_t)(byte8 * baseAddr);
typedef byte8 *(__fastcall * func_2310B0_t)(byte8 * baseAddr, uint32 id); // Dante Rebellion
typedef byte8 *(__fastcall * func_22EC90_t)(byte8 * baseAddr, uint32 id); // Dante Cerberus
typedef byte8 *(__fastcall * func_227870_t)(byte8 * baseAddr, uint32 id); // Dante Agni & Rudra
typedef byte8 *(__fastcall * func_22A1E0_t)(byte8 * baseAddr, uint32 id); // Dante Nevan
typedef byte8 *(__fastcall * func_228CF0_t)(byte8 * baseAddr, uint32 id); // Dante Vergil Beowulf
typedef byte8 *(__fastcall * func_22B0C0_t)(byte8 * baseAddr, uint32 id); // Dante Ebony & Ivory
typedef byte8 *(__fastcall * func_2306B0_t)(byte8 * baseAddr, uint32 id); // Dante Shotgun
typedef byte8 *(__fastcall * func_22C4A0_t)(byte8 * baseAddr, uint32 id); // Dante Artemis
typedef byte8 *(__fastcall * func_2300A0_t)(byte8 * baseAddr, uint32 id); // Dante Spiral
typedef byte8 *(__fastcall * func_22BA30_t)(byte8 * baseAddr, uint32 id); // Dante Lady Kalina Ann
typedef byte8 *(__fastcall * func_231A30_t)(byte8 * baseAddr, uint32 id); // Bob Yamato
typedef byte8 *(__fastcall * func_22D960_t)(byte8 * baseAddr, uint32 id); // Vergil Yamato
typedef byte8 *(__fastcall * func_2298E0_t)(byte8 * baseAddr, uint32 id); // Vergil Force Edge
typedef byte8 *(__fastcall * func_22CF00_t)(byte8 * baseAddr, uint32 id); // Vergil Nero Angelo Sword
typedef void(__fastcall * func_23E560_t)(byte8 * eventData, uint32 position);
typedef void(__fastcall * func_280120_t)(byte8 * baseAddr, uint32 side, uint32 index); // Weapon Switch Animation Dante
typedef void(__fastcall * func_280160_t)(byte8 * baseAddr, uint32 group, uint32 index, uint32 motion); // Weapon Switch Animation Vergil
typedef void(__fastcall * func_1EB0E0_t)(ACTOR_DATA & actorData, uint32 index); // Call after Weapon Switch Animation.
typedef void(__fastcall * func_1F92C0_t)(ACTOR_DATA & actorData, uint32 phase); // Queue devil model update.
typedef void(__fastcall * func_1F97F0_t)(ACTOR_DATA & actorData, bool playMotion); // Update devil model and play motion.
typedef void(__fastcall * func_8AC80_t)(MODEL_DATA & modelData, uint32 bodyPart, byte8 * motionFile, uint32, bool); // Play Motion
typedef void(__fastcall * func_89E30_t)(byte8 * baseAddr, uint32 index); // Call after icon update.

extern func_897B0_t func_897B0;
extern func_89450_t func_89450;
extern func_89270_t func_89270;
extern func_8B470_t func_8B470;
extern func_89960_t func_89960;
extern func_89DE0_t func_89DE0;
extern func_8BC60_t func_8BC60;
extern func_305D80_t func_305D80;
extern func_8A000_t func_8A000;
extern func_2C9F40_t func_2C9F40;
extern func_2CA1D0_t func_2CA1D0;
extern func_2CA2F0_t func_2CA2F0;
extern func_1EF040_t func_1EF040;
extern func_2EE3D0_t func_2EE3D0;
extern func_1FAF40_t func_1FAF40;
extern func_1EEF80_t func_1EEF80;
extern func_2EE060_t func_2EE060;
extern func_1DE820_t func_1DE820;
extern func_1BB390_t func_1BB390;
extern func_217B90_t func_217B90;
extern func_223CB0_t func_223CB0;
extern func_1DFC20_t func_1DFC20;
extern func_2310B0_t func_2310B0;
extern func_22EC90_t func_22EC90;
extern func_227870_t func_227870;
extern func_22A1E0_t func_22A1E0;
extern func_228CF0_t func_228CF0;
extern func_22B0C0_t func_22B0C0;
extern func_2306B0_t func_2306B0;
extern func_22C4A0_t func_22C4A0;
extern func_2300A0_t func_2300A0;
extern func_22BA30_t func_22BA30;
extern func_231A30_t func_231A30;
extern func_22D960_t func_22D960;
extern func_2298E0_t func_2298E0;
extern func_22CF00_t func_22CF00;
extern func_23E560_t func_23E560;
extern func_280120_t func_280120;
extern func_280160_t func_280160;
extern func_1EB0E0_t func_1EB0E0;
extern func_1F92C0_t func_1F92C0;
extern func_1F97F0_t func_1F97F0;
extern func_8AC80_t func_8AC80;
extern func_89E30_t func_89E30;

void Internal_Init();
