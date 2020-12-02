// @Todo: Vergil Doppelganger crashes game when entering elevator.
// @Todo: Other crash.
// @Todo: Cleanup.
// @Todo: Capture grabbed state.
// @Todo: Get resurrect variable.
// @Todo: Quick Drive.
// @Todo: Color Toggle.
// @Todo: Air Stinger, Air Lunar Phase and Nevan instant Vortex.

module;
#include "../Core/Core.h"

#include "Vars.h"
export module Actor;

import Config;
import File;
import Global;
import HUD;
import Internal;
import Input;
import Memory;
import Model;

#define debug true

#pragma region Main

export Vector<byte8 *> Actor_actorBaseAddr;

byte8 * GetActorBaseAddr[MAX_REGISTER] = {};

void InitGetActorBaseAddr()
{
	{
		constexpr byte8 sect0[] =
		{
			0x48, 0x8B, 0x80, 0xC0, 0x00, 0x00, 0x00, // mov rax,[rax+000000C0]
			0x48, 0x85, 0xC0,                         // test rax,rax
			0x75, 0x0B,                               // jne short
			0x48, 0x8B, 0x05, 0x00, 0x00, 0x00, 0x00, // mov rax,[dmc3.exe+C90E28]
			0x48, 0x8B, 0x40, 0x18,                   // mov rax,[rax+18]
			0xC3,                                     // ret
		};
		for_all(uint8, index, MAX_REGISTER)
		{
			auto func = CreateFunction(0, 0, false, true, sizeof(sect0), 0, 0, 0, 0, true);
			memcpy(func.sect0, sect0, sizeof(sect0));
			WriteAddress((func.sect0 + 0xC), (appBaseAddr + 0xC90E28), 7);
			GetActorBaseAddr[index] = func.addr;

			if (index < R8)
			{
				*reinterpret_cast<byte8 *>(func.sect0) = 0x48;
				*reinterpret_cast<byte8 *>(func.sect0 + 2) = (0x80 + index);
			}
			else
			{
				*reinterpret_cast<byte8 *>(func.sect0) = 0x49;
				*reinterpret_cast<byte8 *>(func.sect0 + 2) = (0x80 + (index - R8));
			}
		}
	}
}







export template <typename T>
void SetMainActor(T & actorData)
{
	auto actorBaseAddr = reinterpret_cast<byte8 *>(&actorData);

	LogFunction(actorBaseAddr);

	// Main
	[&]()
	{
		auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
		if (!pool)
		{
			return;
		}
		pool[3] = actorBaseAddr;
	}();

	// Life
	[&]()
	{
		auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E10);
		if (!pool)
		{
			return;
		}
		if (!pool[5])
		{
			return;
		}
		*reinterpret_cast<byte8 **>(pool[5] + 0x2CB8) = actorBaseAddr;
	}();

	// Style Data
	[&]()
	{
		auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
		if (!pool)
		{
			return;
		}
		if (!pool[12])
		{
			return;
		}
		auto dest = *reinterpret_cast<byte8 **>(pool[12]);
		if (!dest)
		{
			return;
		}
		*reinterpret_cast<StyleData **>(dest + 0x3D10) = &actorData.styleData;
	}();
}

export void SetMainActor(uint32 index)
{
	IntroduceActorData(actorBaseAddr, actorData, Actor_actorBaseAddr[index], return);

	SetMainActor(actorData);
}















template
<
	typename T1,
	typename T2
>
void CopyState
(
	T1 & activeActorData,
	T2 & idleActorData,
	byte32 flags = 0
)
{
	idleActorData.position       = activeActorData.position;
	idleActorData.pull           = activeActorData.pull;
	idleActorData.pullMultiplier = activeActorData.pullMultiplier;
	idleActorData.rotation       = activeActorData.rotation;

	if (flags & CopyStateFlags_EventData)
	{
		memcpy
		(
			idleActorData.eventData,
			activeActorData.eventData,
			sizeof(idleActorData.eventData)
		);

		memcpy
		(
			idleActorData.var_3E10,
			activeActorData.var_3E10,
			sizeof(idleActorData.var_3E10)
		);
	}
	else if (flags & CopyStateFlags_Mode)
	{
		idleActorData.mode = activeActorData.mode;
	}

	idleActorData.kickJumpCount = activeActorData.kickJumpCount;
	idleActorData.wallHikeCount = activeActorData.wallHikeCount;
	idleActorData.airTrickCount = activeActorData.airTrickCount;

	idleActorData.hitPoints      = activeActorData.hitPoints;
	idleActorData.maxHitPoints   = activeActorData.maxHitPoints;
	idleActorData.magicPoints    = activeActorData.magicPoints;
	idleActorData.maxMagicPoints = activeActorData.maxMagicPoints;

	// idleActorData.styleRank  = activeActorData.styleRank;
	// idleActorData.styleMeter = activeActorData.styleMeter;

	idleActorData.styleData.rank     = activeActorData.styleData.rank;
	idleActorData.styleData.meter    = activeActorData.styleData.meter;
	idleActorData.styleData.quotient = activeActorData.styleData.quotient;
	idleActorData.styleData.dividend = activeActorData.styleData.dividend;
	idleActorData.styleData.divisor  = activeActorData.styleData.divisor;








	memcpy
	(
		idleActorData.nextActionRequestPolicy,
		activeActorData.nextActionRequestPolicy,
		sizeof(activeActorData.nextActionRequestPolicy)
	);

	idleActorData.idleTimer = 600.0f;

	idleActorData.permissions = activeActorData.permissions;
	idleActorData.state       = activeActorData.state;
	idleActorData.lastState   = activeActorData.lastState;

	[&]()
	{
		IntroduceActorData(actorBaseAddr, actorData, Actor_actorBaseAddr[2], return);

		idleActorData.speedMode = actorData.speedMode;
		idleActorData.quicksilver = actorData.quicksilver;
	}();
}

template<typename T>
void UpdatePermissions(T & actorData)
{
	if (actorData.state & STATE_ON_FLOOR)
	{
		if (actorData.permissions == 0x1C19)
		{
			actorData.permissions = 0x1C1B;
		}
	}
}

template <typename T>
void EndMotion(T & actorData)
{
	actorData.eventData[0].event = 2;
}

template <typename T>
void ToggleInput
(
	T & actorData,
	bool enable
)
{
	actorData.newButtonMask = (enable) ? 0xFFFF : 0;
	actorData.newEnableRightStick = enable;
	actorData.newEnableLeftStick = enable;
}

export template <typename T>
void ToggleActor
(
	T & actorData,
	bool enable
)
{
	actorData.newEnableCollision = enable;

	actorData.newEnableVisibility = enable;

	if (enable)
	{
		actorData.visibility = (g_quicksilver) ? 2 : 1;
	}
	else
	{
		actorData.visibility = 0;
	}

	if
	(
		enable &&
		!actorData.doppelganger
	)
	{
		actorData.shadow = 1;
	}
	else
	{
		actorData.shadow = 0;
	}

	actorData.lastShadow = 0;

	ToggleInput(actorData, enable);
}

export void ToggleActor
(
	uint32 index,
	bool enable
)
{
	IntroduceActorData(actorBaseAddr, actorData, Actor_actorBaseAddr[index], return);

	ToggleActor(actorData, enable);
}

template <typename T>
void CommissionActor
(
	T & actorData
	// bool copyState = false
)
{
	LogFunction(actorData.operator byte8 *());

	auto & playerData = GetPlayerData(actorData);

	if
	(
		//!InCutscene() &&
		(actorData.newCharacterIndex == playerData.activeCharacterIndex) &&
		(actorData.newEntityIndex == ENTITY_MAIN)
	)
	{
		ToggleActor(actorData, true);

		if (actorData.newPlayerIndex == 0)
		{
			SetMainActor(actorData);
		}
	}
	else
	{
		ToggleActor(actorData, false);
	}

	//if (copyState)
	{
		IntroduceActorData(actorBaseAddr2, actorData2, Actor_actorBaseAddr[0], return);

		CopyState
		(
			actorData2,
			actorData,
			CopyStateFlags_EventData | CopyStateFlags_Mode
		);
	}

	if (actorData.mode == ACTOR_MODE_MISSION_19)
	{
		actorData.mode = ACTOR_MODE_DEFAULT;
	}
}


































export template <typename T>
struct GetCharacterId
{
	enum
	{
		value =
		(TypeMatch<T, ActorDataDante >::value) ? CHAR_DANTE  :
		(TypeMatch<T, ActorDataBob   >::value) ? CHAR_BOB    :
		(TypeMatch<T, ActorDataLady  >::value) ? CHAR_LADY   :
		(TypeMatch<T, ActorDataVergil>::value) ? CHAR_VERGIL :
		0
	};
};



// @Todo: Use CharacterData.
// @Todo: 2 or CharacterModelData.
struct CharacterModelData
{
	uint8 character;
	uint8 costume;
	uint16 costumeFileId;
	bool coat;

	template <typename T>
	void Update(T & actorData);
};

template <typename T>
void CharacterModelData::Update(T & actorData)
{
	character = (actorData.newForceFiles) ? actorData.newForceFilesCharacter : static_cast<uint8>(actorData.character);
	if (character >= MAX_CHAR)
	{
		character = 0;
	}
	costume = actorData.costume;
	costumeFileId = 0;
	coat = false;

	switch (character)
	{
	case CHAR_DANTE:
	{
		if (costume >= MAX_COSTUME_DANTE)
		{
			costume = 0;
		}
		costumeFileId = costumeFileIdsDante[costume];
		coat =
		(
			(costume == COSTUME_DANTE_DEFAULT                           ) ||
			(costume == COSTUME_DANTE_DEFAULT_TORN                      ) ||
			(costume == COSTUME_DANTE_DMC1                              ) ||
			(costume == COSTUME_DANTE_SPARDA                            ) ||
			(costume == COSTUME_DANTE_DEFAULT_TORN_INFINITE_MAGIC_POINTS) ||
			(costume == COSTUME_DANTE_SPARDA_INFINITE_MAGIC_POINTS      )
		)
		? true : false;
		break;
	}
	case CHAR_BOB:
	{
		if (costume >= MAX_COSTUME_BOB)
		{
			costume = 0;
		}
		costumeFileId = costumeFileIdsBob[costume];
		coat = false; // @Research: Compare coat vars.
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
			(costume == COSTUME_VERGIL_NERO_ANGELO                       ) ||
			(costume == COSTUME_VERGIL_NERO_ANGELO_INFINITE_MAGIC_POINTS )
		)
		? true : false;
		break;
	}
	}
}



typedef WeaponData *(__fastcall * RegisterWeapon_t)
(
	byte8 * actorData,
	uint32 weapon
);

RegisterWeapon_t RegisterWeapon[MAX_WEAPON] = {};

void InitRegisterWeapon()
{
	RegisterWeapon[WEAPON_REBELLION        ] = func_2310B0;
	RegisterWeapon[WEAPON_CERBERUS         ] = func_22EC90;
	RegisterWeapon[WEAPON_AGNI_RUDRA       ] = func_227870;
	RegisterWeapon[WEAPON_NEVAN            ] = func_22A1E0;
	RegisterWeapon[WEAPON_BEOWULF_DANTE    ] = func_228CF0;
	RegisterWeapon[WEAPON_EBONY_IVORY      ] = func_22B0C0;
	RegisterWeapon[WEAPON_SHOTGUN          ] = func_2306B0;
	RegisterWeapon[WEAPON_ARTEMIS          ] = func_22C4A0;
	RegisterWeapon[WEAPON_SPIRAL           ] = func_2300A0;
	RegisterWeapon[WEAPON_KALINA_ANN       ] = func_22BA30;
	RegisterWeapon[WEAPON_YAMATO_VERGIL    ] = func_22D960;
	RegisterWeapon[WEAPON_BEOWULF_VERGIL   ] = func_228CF0;
	RegisterWeapon[WEAPON_YAMATO_FORCE_EDGE] = func_2298E0;
	RegisterWeapon[WEAPON_YAMATO_BOB       ] = func_231A30;
}





















bool IsDanteMeleeWeapon(uint8 weapon)
{
	if
	(
		(weapon >= WEAPON_REBELLION    ) &&
		(weapon <= WEAPON_BEOWULF_DANTE)
	)
	{
		return true;
	}

	return false;
}

bool IsVergilMeleeWeapon(uint8 weapon)
{
	if
	(
		(weapon >= WEAPON_YAMATO_VERGIL) &&
		(weapon <= WEAPON_YAMATO_FORCE_EDGE   )
	)
	{
		return true;
	}

	return false;
}

bool IsDanteRangedWeapon(uint8 weapon)
{
	if
	(
		(weapon >= WEAPON_EBONY_IVORY) &&
		(weapon <= WEAPON_KALINA_ANN )
	)
	{
		return true;
	}

	return false;
}

bool IsDanteWeapon(uint8 weapon)
{
	if (IsDanteMeleeWeapon(weapon))
	{
		return true;
	}
	else if (IsDanteRangedWeapon(weapon))
	{
		return true;
	}

	return false;
}

bool IsVergilWeapon(uint8 weapon)
{
	if (IsVergilMeleeWeapon(weapon))
	{
		return true;
	}

	return false;
}









template <typename T>
bool IsWeaponActive
(
	T & actorData,
	uint8 weapon
)
{
	auto & motionData = actorData.motionData[UPPER_BODY];

	if (motionData.index == 0)
	{
		return false;
	}

	switch (actorData.character)
	{
		case CHAR_DANTE:
		{

			if (!IsDanteWeapon(weapon))
			{
				return false;
			}

			if (motionData.group == (MOTION_GROUP_DANTE_REBELLION + weapon))
			{
				return true;
			}
			else if (motionData.group == (MOTION_GROUP_DANTE_SWORDMASTER_REBELLION + weapon))
			{
				return true;
			}

			break;
		}
		case CHAR_VERGIL:
		{
			if (!IsVergilWeapon(weapon))
			{
				return false;
			}

			if (motionData.group == (MOTION_GROUP_VERGIL_YAMATO + (weapon - WEAPON_YAMATO_VERGIL)))
			{
				return true;
			}

			break;
		}
	}

	return false;
}

template <typename T>
bool IsWeaponActive(T & actorData)
{
	auto & motionData = actorData.motionData[UPPER_BODY];

	switch (actorData.character)
	{
		case CHAR_DANTE:
		{
			if
			(
				(motionData.group >= MOTION_GROUP_DANTE_REBELLION ) &&
				(motionData.group <= MOTION_GROUP_DANTE_KALINA_ANN) &&
				(motionData.index > 0)
			)
			{
				return true;
			}
			else if
			(
				(motionData.group >= MOTION_GROUP_DANTE_SWORDMASTER_REBELLION) &&
				(motionData.group <= MOTION_GROUP_DANTE_GUNSLINGER_KALINA_ANN)
			)
			{
				return true;
			}

			break;
		}
		case CHAR_BOB:
		{
			if
			(
				(motionData.group == MOTION_GROUP_BOB_YAMATO ) &&
				(motionData.index > 0)
			)
			{
				return true;
			}

			break;
		}
		case CHAR_VERGIL:
		{
			if
			(
				(motionData.group >= MOTION_GROUP_VERGIL_YAMATO    ) &&
				(motionData.group <= MOTION_GROUP_VERGIL_FORCE_EDGE) &&
				(motionData.index > 0)
			)
			{
				return true;
			}
			else if
			(
				(motionData.group >= MOTION_GROUP_VERGIL_NERO_ANGELO_YAMATO ) &&
				(motionData.group <= MOTION_GROUP_VERGIL_NERO_ANGELO_BEOWULF) &&
				(motionData.index > 0)
			)
			{
				return true;
			}

			break;
		}
	}

	return false;
}

template <typename T>
bool IsActive(T & actorData)
{
	auto & motionData = actorData.motionData[UPPER_BODY];

	switch (actorData.character)
	{
		case CHAR_DANTE:
		{
			if (motionData.group == MOTION_GROUP_DANTE_BASE)
			{
				switch (motionData.index)
				{
					case 0:
					case 3:
					{
						return false;
					}
				}

				return true;
			}
			else if
			(
				(motionData.group >= MOTION_GROUP_DANTE_DAMAGE) &&
				(motionData.group <= MOTION_GROUP_DANTE_TAUNTS)
			)
			{
				return true;
			}
			else if (IsWeaponActive(actorData))
			{
				return true;
			}
			else if
			(
				(motionData.group >= MOTION_GROUP_DANTE_TRICKSTER   ) &&
				(motionData.group <= MOTION_GROUP_DANTE_DOPPELGANGER)
			)
			{
				return true;
			}

			break;
		}
		case CHAR_BOB:
		{
			if (motionData.group == MOTION_GROUP_BOB_BASE)
			{
				switch (motionData.index)
				{
					case 0:
					case 3:
					{
						return false;
					}
				}

				return true;
			}
			else if
			(
				(motionData.group >= MOTION_GROUP_BOB_DAMAGE) &&
				(motionData.group <= MOTION_GROUP_BOB_TAUNTS)
			)
			{
				return true;
			}
			else if (IsWeaponActive(actorData))
			{
				return true;
			}

			break;
		}
		case CHAR_LADY:
		{
			if (motionData.group == MOTION_GROUP_LADY_BASE)
			{
				switch (motionData.index)
				{
					case 0:
					case 3:
					{
						return false;
					}
				}

				return true;
			}
			else if
			(
				(motionData.group >= MOTION_GROUP_LADY_DAMAGE) &&
				(motionData.group <= MOTION_GROUP_LADY_TAUNTS)
			)
			{
				return true;
			}

			break;
		}
		case CHAR_VERGIL:
		{
			if (motionData.group == MOTION_GROUP_VERGIL_BASE)
			{
				switch (motionData.index)
				{
					case 0:
					case 3:
					{
						return false;
					}
				}

				return true;
			}
			else if
			(
				(motionData.group >= MOTION_GROUP_VERGIL_DAMAGE) &&
				(motionData.group <= MOTION_GROUP_VERGIL_TAUNTS)
			)
			{
				return true;
			}
			else if (IsWeaponActive(actorData))
			{
				return true;
			}
			else if (motionData.group == MOTION_GROUP_VERGIL_DARK_SLAYER)
			{
				return true;
			}

			break;
		}
	}

	return false;
}

#pragma region IsWeaponReady

bool IsMeleeWeaponReady
(
	ActorData & actorData,
	uint8 weapon
)
{
	if (weapon >= MAX_WEAPON)
	{
		return true;
	}

	switch (actorData.character)
	{
		case CHAR_DANTE:
		{
			if (actorData.devil)
			{
				if (actorData.sparda)
				{
					if (weapon == WEAPON_BEOWULF_DANTE)
					{
						return false;
					}
				}
				else
				{
					if (actorData.activeDevil == weaponDevilIds[weapon])
					{
						return true;
					}
				}
			}
			else
			{
				if ((weapon == WEAPON_BEOWULF_DANTE) && activeConfig.BeowulfDante.hide)
				{
					return false;
				}
			}

			if (IsWeaponActive(actorData, weapon))
			{
				return true;
			}

			for_all(uint8, index, MELEE_WEAPON_COUNT_DANTE)
			{
				uint8 weapon2 = (WEAPON_REBELLION + index);

				if (weapon2 == weapon)
				{
					continue;
				}

				if (IsWeaponActive(actorData, weapon2))
				{
					return false;
				}
			}

			if (actorData.devil && actorData.sparda)
			{
				return false;
			}

			if (actorData.meleeWeaponIndex == weapon)
			{
				return true;
			}

			break;
		}
		case CHAR_VERGIL:
		{
			if (actorData.devil)
			{
				if (actorData.neroAngelo)
				{
					return false;
				}
				else
				{
					if (actorData.activeDevil == weaponDevilIds[weapon])
					{
						return true;
					}
				}
			}
			else
			{
				if ((weapon == WEAPON_BEOWULF_VERGIL) && activeConfig.BeowulfVergil.hide)
				{
					return false;
				}
			}

			if (IsWeaponActive(actorData, weapon))
			{
				return true;
			}

			for_all(uint8, index, MELEE_WEAPON_COUNT_VERGIL)
			{
				uint8 weapon2 = (WEAPON_YAMATO_VERGIL + index);

				if (weapon2 == weapon)
				{
					continue;
				}

				if (IsWeaponActive(actorData, weapon2))
				{
					return false;
				}
			}

			if (actorData.activeMeleeWeaponIndex == (weapon - WEAPON_YAMATO_VERGIL))
			{
				return true;
			}

			break;
		}
	}

	return false;
}

bool IsMeleeWeaponReadyProxy(WeaponData & weaponData)
{
	auto actorBaseAddr = weaponData.actorBaseAddr;
	if (!actorBaseAddr)
	{
		return true;
	}
	auto & actorData = *reinterpret_cast<ActorData *>(actorBaseAddr);

	return IsMeleeWeaponReady(actorData, weaponData.weapon);
}

bool IsRangedWeaponReady
(
	ActorDataDante & actorData,
	uint8 weapon
)
{
	if (IsWeaponActive(actorData, weapon))
	{
		return true;
	}

	for_all(uint8, index, RANGED_WEAPON_COUNT_DANTE)
	{
		uint8 weapon2 = (WEAPON_EBONY_IVORY + index);

		if (weapon2 == weapon)
		{
			continue;
		}

		if (IsWeaponActive(actorData, weapon2))
		{
			return false;
		}
	}

	if (actorData.rangedWeaponIndex == weapon)
	{
		return true;
	}

	return false;
}

bool IsRangedWeaponReadyProxy(WeaponData & weaponData)
{
	if (!weaponData.actorBaseAddr)
	{
		return true;
	}
	auto & actorData = *reinterpret_cast<ActorDataDante *>(weaponData.actorBaseAddr);

	return IsRangedWeaponReady(actorData, weaponData.weapon);
}

void IsMeleeWeaponReadyVergilFix(ActorData & actorData)
{
	if (actorData.activeMeleeWeaponIndex != actorData.queuedMeleeWeaponIndex)
	{
		uint8 weapon = (WEAPON_YAMATO_VERGIL + static_cast<uint8>(actorData.activeMeleeWeaponIndex));

		if (!IsWeaponActive(actorData, weapon))
		{
			actorData.activeMeleeWeaponIndex = actorData.queuedMeleeWeaponIndex;
		}
	}
}

byte8 * IsMeleeWeaponReadyProxyAddr      = 0;
byte8 * IsMeleeWeaponReadyProxyShowAddr  = 0;
byte8 * IsRangedWeaponReadyProxyAddr     = 0;
byte8 * IsRangedWeaponReadyProxyShowAddr = 0;

void InitIsWeaponReady()
{
	LogFunction();

	// Melee
	{
		auto func = CreateFunction(IsMeleeWeaponReadyProxy, 0, true, false);
		IsMeleeWeaponReadyProxyAddr = func.addr;
	}
	{
		constexpr byte8 sect2[] =
		{
			0x84, 0xC0,                   // test al,al
			0x74, 0x05,                   // je short
			0xE9, 0x00, 0x00, 0x00, 0x00, // jmp dmc3.exe+1FDE10
		};
		auto func = CreateFunction(IsMeleeWeaponReadyProxy, 0, true, false, 0, 0, sizeof(sect2));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteJump((func.sect2 + 4), (appBaseAddr + 0x1FDE10));
		IsMeleeWeaponReadyProxyShowAddr = func.addr;
	}

	// Ranged
	{
		auto func = CreateFunction(IsRangedWeaponReadyProxy, 0, true, false);
		IsRangedWeaponReadyProxyAddr = func.addr;
	}
	{
		constexpr byte8 sect2[] =
		{
			0x84, 0xC0,                   // test al,al
			0x74, 0x05,                   // je short
			0xE9, 0x00, 0x00, 0x00, 0x00, // jmp dmc3.exe+1FDE10
		};
		auto func = CreateFunction(IsRangedWeaponReadyProxy, 0, true, false, 0, 0, sizeof(sect2));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteJump((func.sect2 + 4), (appBaseAddr + 0x1FDE10));
		IsRangedWeaponReadyProxyAddr = func.addr;
	}
}

void ToggleIsWeaponReady(bool enable)
{
	LogFunction(enable);

	// Rebellion
	WriteCall((appBaseAddr + 0x23162E), (enable) ? IsMeleeWeaponReadyProxyAddr : (appBaseAddr + 0x1FD3E0));
	/*
	dmc3.exe+23162E - E8 ADBDFCFF - call dmc3.exe+1FD3E0
	*/

	// Cerberus
	WriteCall((appBaseAddr + 0x22FAD4), (enable) ? IsMeleeWeaponReadyProxyAddr : (appBaseAddr + 0x1FD3E0));
	/*
	dmc3.exe+22FAD4 - E8 07D9FCFF - call dmc3.exe+1FD3E0
	*/

	// Agni & Rudra
	WriteCall((appBaseAddr + 0x2288A4), (enable) ? IsMeleeWeaponReadyProxyAddr : (appBaseAddr + 0x1FD3E0));
	/*
	dmc3.exe+2288A4 - E8 374BFDFF - call dmc3.exe+1FD3E0
	*/

	// Nevan
	WriteCall((appBaseAddr + 0x22AD2D), (enable) ? IsMeleeWeaponReadyProxyAddr : (appBaseAddr + 0x1FD3E0));
	/*
	dmc3.exe+22AD2D - E8 AE26FDFF - call dmc3.exe+1FD3E0
	*/

	// Beowulf
	WriteCall((appBaseAddr + 0x2295B7), (enable) ? IsMeleeWeaponReadyProxyShowAddr : (appBaseAddr + 0x1FDE10));
	/*
	dmc3.exe+2295B7 - E8 5448FDFF - call dmc3.exe+1FDE10
	*/

	// Artemis
	WriteCall((appBaseAddr + 0x22CBC8), (enable) ? IsRangedWeaponReadyProxyAddr : (appBaseAddr + 0x1FDE10));
	/*
	dmc3.exe+22CBC8 - E8 4312FDFF - call dmc3.exe+1FDE10
	*/
}

#pragma endregion







































template <typename T>
bool SystemButtonCheck(T & actorData)
{
	// switch (activeConfig.Actor.system)
	// {
	// 	case ACTOR_SYSTEM_DOPPELGANGER:
	// 	{
	// 		if (actorData.newIndex == ENTITY_MAIN)
	// 		{
	// 			if (actorData.buttons[0] & GetBinding(BINDING_DEFAULT_CAMERA))
	// 			{
	// 				return false;
	// 			}
	// 		}
	// 		else
	// 		{
	// 			if (!(actorData.buttons[0] & GetBinding(BINDING_DEFAULT_CAMERA)))
	// 			{
	// 				return false;
	// 			}
	// 		}

	// 		break;
	// 	}
	// 	case ACTOR_SYSTEM_CHARACTER_SWITCHER:
	// 	{
	// 		if (actorData.buttons[0] & GetBinding(BINDING_DEFAULT_CAMERA))
	// 		{
	// 			return false;
	// 		}

	// 		break;
	// 	}
	// }

	return true;
}




template <typename T>
bool IsNeroAngelo(T & actorData)
{
	return
	(
		(actorData.character == CHAR_VERGIL) &&
		actorData.neroAngelo &&
		actorData.devil
	);
}













#pragma endregion

#pragma region File

struct FileDataHelper
{
	uint16 fileDataId;
	uint16 fileId;
};

constexpr FileDataHelper fileDataHelperDante[] =
{
	{ 0  , pl000         },
	{ 200, pl005         },
	{ 201, pl006         },
	{ 202, pl007         },
	{ 203, pl008         },
	{ 204, pl009         },
	{ 205, pl017         },
	{ 140, plwp_sword    },
	{ 141, plwp_nunchaku },
	{ 142, plwp_2sword   },
	{ 143, plwp_guitar   },
	{ 144, plwp_fight    },
	{ 145, plwp_gun      },
	{ 146, plwp_shotgun  },
	{ 147, plwp_laser    },
	{ 148, plwp_rifle    },
	{ 149, plwp_ladygun  },
};

constexpr FileDataHelper fileDataHelperBob[] =
{
	{ 1  , pl001            },
	{ 207, pl010            },
	{ 169, plwp_vergilsword },
};

constexpr FileDataHelper fileDataHelperLady[] =
{
	{ 2, pl002 },
};

constexpr FileDataHelper fileDataHelperVergil[] =
{
	{ 3  , pl021               },
	{ 221, pl010               },
	{ 222, pl014               },
	{ 223, pl025               },
	{ 196, plwp_newvergilsword },
	{ 189, plwp_newvergilfight },
	{ 198, plwp_forceedge      },
	{ 187, plwp_nerosword      },
};

template<uint8 itemCount>
void UpdateFileDataFunction(const FileDataHelper(&items)[itemCount])
{
	for_all(uint8, itemIndex, itemCount)
	{
		File_UpdateFileData
		(
			items[itemIndex].fileDataId,
			items[itemIndex].fileId
		);
	}
}

template <typename T>
void UpdateFileData(T & actorData)
{
	if constexpr (TypeMatch<T, ActorDataDante>::value)
	{
		UpdateFileDataFunction(fileDataHelperDante);
	}
	else if constexpr (TypeMatch<T, ActorDataBob>::value)
	{
		UpdateFileDataFunction(fileDataHelperBob);
	}
	else if constexpr (TypeMatch<T, ActorDataLady>::value)
	{
		UpdateFileDataFunction(fileDataHelperLady);
	}
	else if constexpr (TypeMatch<T, ActorDataVergil>::value)
	{
		UpdateFileDataFunction(fileDataHelperVergil);
	}
}

template <typename T>
void UpdateCostumeFileData(T & actorData)
{
	IntroduceSessionData();

	CharacterModelData characterData;

	characterData.Update(actorData);

	auto & character     = characterData.character;
	auto & costume       = characterData.costume;
	auto & costumeFileId = characterData.costumeFileId;
	auto & coat          = characterData.coat;

	File_UpdateFileData(static_cast<uint16>(character), costumeFileId);

	if constexpr (TypeMatch<T, ActorDataDante>::value)
	{
		uint16 swordFileId = plwp_sword;

		if (sessionData.unlockDevilTrigger)
		{
			swordFileId = plwp_sword2;
		}

		if (actorData.sparda)
		{
			swordFileId = plwp_sword3;
		}

		File_UpdateFileData(140, swordFileId);
	}
}

#pragma endregion

#pragma region Actor Management

template <typename T>
void InitActor
(
	T & actorData,
	ActiveMissionActorData & activeMissionActorData
)
{
	if constexpr      (TypeMatch<T, ActorDataDante >::value) { func_217B90(actorData, activeMissionActorData); }
	else if constexpr (TypeMatch<T, ActorDataBob   >::value) { func_226F10(actorData, activeMissionActorData); }
	else if constexpr (TypeMatch<T, ActorDataLady  >::value) { func_219660(actorData, activeMissionActorData); }
	else if constexpr (TypeMatch<T, ActorDataVergil>::value) { func_223CB0(actorData, activeMissionActorData); }
}

template <typename T>
void UpdateActor(T & actorData)
{
	if constexpr      (TypeMatch<T, ActorDataDante >::value) { func_212BE0(actorData); }
	else if constexpr (TypeMatch<T, ActorDataBob   >::value) { func_225D70(actorData); }
	else if constexpr (TypeMatch<T, ActorDataLady  >::value) { func_219260(actorData); }
	else if constexpr (TypeMatch<T, ActorDataVergil>::value) { func_220970(actorData); }
}

template <typename T>
void InitModel
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

	auto file = File_staticFiles[pl000][5]; // @Todo: Update.

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
		&actorData.collisionData
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

template <typename T>
void UpdateModel(T & actorData)
{
	CharacterModelData characterModelData;

	characterModelData.Update(actorData);

	auto & character     = characterModelData.character;
	auto & costume       = characterModelData.costume;
	auto & costumeFileId = characterModelData.costumeFileId;
	auto & coat          = characterModelData.coat;

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

	if ((character == CHAR_LADY) && (costume == COSTUME_LADY_LEATHER_JUMPSUIT))
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

	if ((character == CHAR_LADY) && (costume == COSTUME_LADY_LEATHER_JUMPSUIT))
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

	if ((character == CHAR_LADY))
	{
		return;
	}

	if (coat && shadowFile)
	{
		RegisterShadow
		(
			actorData.newSubmodelData[submodelIndex],
			actorData.newSubmodelShadowData[submodelIndex],
			shadowFile
		);
	}

	actorData.newSubmodelInit[submodelIndex] = true;

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
		(appBaseAddr + ((coat) ? 0x58B380 : 0x58B054)),
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

template <typename T>
void UpdateDevilModel
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

	// @Todo: Update.
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

	if (devil == DEVIL_AGNI_RUDRA)
	{
		shadowFile = file[2];
	}
	else if
	(
		(devil == DEVIL_CERBERUS) ||
		(devil == DEVIL_BEOWULF ) ||
		(devil == DEVIL_SPARDA  )
	)
	{
		shadowFile = file[4];
	}
	else if
	(
		(devil == DEVIL_REBELLION) ||
		(devil == DEVIL_NEVAN    )
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

	InitModel
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

	if (devil == DEVIL_AGNI_RUDRA)
	{
		return;
	}

	// Wings

	modelFile   = file[2];
	textureFile = file[0];
	physicsFile = file[3];

	if
	(
		(devil == DEVIL_REBELLION) ||
		(devil == DEVIL_NEVAN    )
	)
	{
		shadowFile = file[7];
	}
	else if
	(
		(devil == DEVIL_CERBERUS) ||
		(devil == DEVIL_BEOWULF ) ||
		(devil == DEVIL_SPARDA  )
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

	actorData.newSubmodelInit[submodelIndex] = true;

	RegisterPhysics
	(
		physicsFile,
		&actorData.newDevilSubmodelPhysicsData[devilSubmodelIndex],
		&actorData.newDevilModelPhysicsMetadataPool[devilModelIndex][devilModelPhysicsMetadataIndex]
	);

	if
	(
		(devil == DEVIL_REBELLION) ||
		(devil == DEVIL_NEVAN    )
	)
	{
		LinkModelPhysicsData(0, 3, 1 );
		LinkModelPhysicsData(1, 2, 12);
	}
	else if
	(
		(devil == DEVIL_CERBERUS) ||
		(devil == DEVIL_BEOWULF )
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
		(devil == DEVIL_REBELLION) ||
		(devil == DEVIL_NEVAN    )
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

	actorData.newSubmodelInit[submodelIndex] = true;

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

void UpdateModelPartitions(ActorData & actorData)
{
	IntroduceSessionData();

	CharacterModelData characterModelData;

	characterModelData.Update(actorData);

	auto & character     = characterModelData.character;
	auto & costume       = characterModelData.costume;
	auto & costumeFileId = characterModelData.costumeFileId;
	auto & coat          = characterModelData.coat;

	auto modelPartitionData = actorData.newModelData[0].modelPartitionData;
	if (!modelPartitionData)
	{
		return;
	}

	bool beowulf = false;

	switch (actorData.character)
	{
		case CHAR_DANTE:
		{
			beowulf = IsMeleeWeaponReady(actorData, WEAPON_BEOWULF_DANTE);

			break;
		}
		case CHAR_VERGIL:
		{
			beowulf = IsMeleeWeaponReady(actorData, WEAPON_BEOWULF_VERGIL);

			break;
		}
	}

	switch (character)
	{
		case CHAR_DANTE:
		{
			switch (costume)
			{
				case COSTUME_DANTE_DEFAULT:
				{
					modelPartitionData[0 ].value = (beowulf) ? 2 : 3; // Hands
					modelPartitionData[1 ].value = (beowulf) ? 3 : 2; // Fists
					modelPartitionData[2 ].value = 3; // Shoulders
					modelPartitionData[3 ].value = (beowulf) ? 2 : 3; // Lower Arms
					modelPartitionData[4 ].value = (beowulf) ? 3 : 2; // Lower Arms Half
					modelPartitionData[5 ].value = (beowulf) ? 3 : 2; // Lower Legs Half
					modelPartitionData[6 ].value = (beowulf) ? 2 : 3; // Lower Legs and Feet
					modelPartitionData[7 ].value = 3; // Upper Legs
					modelPartitionData[8 ].value = 3; // Accessories
					modelPartitionData[9 ].value = 3; // Upper Body
					modelPartitionData[10].value = 3; // Face
					modelPartitionData[11].value = 3; // Hair Base
					modelPartitionData[12].value = 3; // Hair Back Layer 1
					modelPartitionData[13].value = 3; // Hair Back Layer 2
					modelPartitionData[14].value = 3; // Hair Sides
					modelPartitionData[15].value = 3; // Hair Back Layer 3
					modelPartitionData[16].value = 3; // Hair Main

					break;
				}
				case COSTUME_DANTE_DEFAULT_NO_COAT:
				{
					modelPartitionData[0 ].value = (beowulf) ? 2 : 3; // Hands
					modelPartitionData[1 ].value = (beowulf) ? 3 : 2; // Fists
					modelPartitionData[2 ].value = 3; // Upper Body
					modelPartitionData[3 ].value = 2; // Filler
					modelPartitionData[4 ].value = 2; // Filler
					modelPartitionData[5 ].value = (beowulf) ? 3 : 2; // Lower Legs Half
					modelPartitionData[6 ].value = (beowulf) ? 2 : 3; // Lower Legs and Feet
					modelPartitionData[7 ].value = 3; // Upper Legs
					modelPartitionData[8 ].value = 3; // Accessories
					modelPartitionData[9 ].value = 3; // Face
					modelPartitionData[10].value = 3; // Hair Base
					modelPartitionData[11].value = 3; // Hair Back Layer 1
					modelPartitionData[12].value = 3; // Hair Back Layer 2
					modelPartitionData[13].value = 3; // Hair Sides
					modelPartitionData[14].value = 3; // Hair Back Layer 3
					modelPartitionData[15].value = 3; // Hair Main

					break;
				}
				case COSTUME_DANTE_DEFAULT_TORN:
				case COSTUME_DANTE_DEFAULT_TORN_INFINITE_MAGIC_POINTS:
				{
					modelPartitionData[0 ].value = (beowulf) ? 2 : 3; // Hands
					modelPartitionData[1 ].value = (beowulf) ? 3 : 2; // Fists
					modelPartitionData[2 ].value = 3; // Shoulders
					modelPartitionData[3 ].value = (beowulf) ? 2 : 3; // Lower Arms
					modelPartitionData[4 ].value = (beowulf) ? 3 : 2; // Lower Arms Half
					modelPartitionData[5 ].value = (beowulf) ? 3 : 2; // Lower Legs Half
					modelPartitionData[6 ].value = (beowulf) ? 2 : 3; // Lower Legs and Feet
					modelPartitionData[7 ].value = 3; // Upper Legs
					modelPartitionData[8 ].value = 3; // Accessories
					modelPartitionData[9 ].value = 3; // Upper Body
					modelPartitionData[10].value = 3; // Lower Right Arm
					modelPartitionData[11].value = 3; // Face
					modelPartitionData[12].value = 3; // Hair Base
					modelPartitionData[13].value = 3; // Hair Back Layer 1
					modelPartitionData[14].value = 3; // Hair Back Layer 2
					modelPartitionData[15].value = 3; // Hair Sides
					modelPartitionData[16].value = 3; // Hair Back Layer 3
					modelPartitionData[17].value = 3; // Hair Main

					break;
				}
				case COSTUME_DANTE_DMC1:
				{
					modelPartitionData[0 ].value = (beowulf) ? 2 : 3; // Hands
					modelPartitionData[1 ].value = (beowulf) ? 3 : 2; // Fists
					modelPartitionData[2 ].value = 3; // Shoulders and Arms
					modelPartitionData[3 ].value = 2; // Filler
					modelPartitionData[4 ].value = 2; // Filler
					modelPartitionData[5 ].value = (beowulf) ? 3 : 2; // Lower Legs Half
					modelPartitionData[6 ].value = (beowulf) ? 2 : 3; // Lower Legs and Feet
					modelPartitionData[7 ].value = 3; // Upper Legs
					modelPartitionData[8 ].value = 3; // Vest
					modelPartitionData[9 ].value = 3; // Upper Body
					modelPartitionData[10].value = 3; // Face
					modelPartitionData[11].value = 3; // Hair Base
					modelPartitionData[12].value = 3; // Hair Back Layer 1
					modelPartitionData[13].value = 3; // Hair Back Layer 2
					modelPartitionData[14].value = 3; // Hair Back Layer 3
					modelPartitionData[15].value = 3; // Hair Main

					break;
				}
				case COSTUME_DANTE_DMC1_NO_COAT:
				{
					modelPartitionData[0 ].value = (beowulf) ? 2 : 3; // Hands
					modelPartitionData[1 ].value = (beowulf) ? 3 : 2; // Fists
					modelPartitionData[2 ].value = 3; // Upper Body
					modelPartitionData[3 ].value = 2; // Filler
					modelPartitionData[4 ].value = 2; // Filler
					modelPartitionData[5 ].value = (beowulf) ? 3 : 2; // Lower Legs Half
					modelPartitionData[6 ].value = (beowulf) ? 2 : 3; // Lower Legs and Feet
					modelPartitionData[7 ].value = 3; // Upper Legs
					modelPartitionData[8 ].value = 3; // Collar
					modelPartitionData[9 ].value = 3; // Face
					modelPartitionData[10].value = 3; // Hair Base
					modelPartitionData[11].value = 3; // Hair Back Layer 1
					modelPartitionData[12].value = 3; // Hair Back Layer 2
					modelPartitionData[13].value = 3; // Hair Back Layer 3
					modelPartitionData[14].value = 3; // Hair Main

					break;
				}
				case COSTUME_DANTE_SPARDA:
				case COSTUME_DANTE_SPARDA_INFINITE_MAGIC_POINTS:
				{
					modelPartitionData[0 ].value = (beowulf) ? 2 : 3; // Hands
					modelPartitionData[1 ].value = (beowulf) ? 3 : 2; // Fists
					modelPartitionData[2 ].value = 3; // Shoulders
					modelPartitionData[3 ].value = (beowulf) ? 2 : 3; // Lower Arms
					modelPartitionData[4 ].value = (beowulf) ? 3 : 2; // Lower Arms Half
					modelPartitionData[5 ].value = (beowulf) ? 3 : 2; // Lower Legs Half
					modelPartitionData[6 ].value = (beowulf) ? 2 : 3; // Lower Legs and Feet
					modelPartitionData[7 ].value = 3; // Upper Legs
					modelPartitionData[8 ].value = 3; // Upper Body
					modelPartitionData[9 ].value = 3; // Monocle
					modelPartitionData[10].value = 3; // Collar
					modelPartitionData[11].value = 3; // Neck
					modelPartitionData[12].value = 3; // Face
					modelPartitionData[13].value = 3; // Hair
					
					break;
				}
			}

			break;
		}
		case CHAR_LADY:
		{
			switch (costume)
			{
				case COSTUME_LADY_DEFAULT:
				{
					modelPartitionData[0].value = 3; // Body
					modelPartitionData[1].value = 3; // Face
					modelPartitionData[2].value = 3; // Hands
					modelPartitionData[3].value = 3; // Accessories
					modelPartitionData[4].value = (sessionData.mission >= 14) ? 3 : 2; // Bandage

					break;
				}
				case COSTUME_LADY_LEATHER_JUMPSUIT:
				{
					modelPartitionData[0].value = 3; // Body
					modelPartitionData[1].value = 3; // Face
					modelPartitionData[2].value = 3; // Hands
					modelPartitionData[3].value = 3; // Accessories
					modelPartitionData[4].value = 2; // Millenium Puzzle
					modelPartitionData[5].value = 3; // Feet
					modelPartitionData[6].value = 3; // Belt
					modelPartitionData[7].value = 3; // Zippers

					break;
				}
			}

			break;
		}
		case CHAR_VERGIL:
		{
			switch (costume)
			{
				case COSTUME_VERGIL_DEFAULT:
				case COSTUME_VERGIL_DEFAULT_INFINITE_MAGIC_POINTS:
				{
					modelPartitionData[0 ].value = 3; // Body
					modelPartitionData[1 ].value = 3; // Shoulders
					modelPartitionData[2 ].value = (beowulf) ? 2 : 3; // Hands
					modelPartitionData[3 ].value = 3; // Face
					modelPartitionData[4 ].value = (beowulf) ? 3 : 2; // Fists
					modelPartitionData[5 ].value = 3; // Hair Base
					modelPartitionData[6 ].value = 3; // Hair Main
					modelPartitionData[7 ].value = (beowulf) ? 3 : 2; // Lower Legs Half
					modelPartitionData[8 ].value = (beowulf) ? 2 : 3; // Lower Legs and Feet
					modelPartitionData[9 ].value = (beowulf) ? 3 : 2; // Lower Arms Half
					modelPartitionData[10].value = (beowulf) ? 2 : 3; // Lower Arms

					break;
				}
				case COSTUME_VERGIL_DEFAULT_NO_COAT:
				{
					modelPartitionData[0 ].value = 3; // Body
					modelPartitionData[1 ].value = 3; // Arms
					modelPartitionData[2 ].value = (beowulf) ? 2 : 3; // Hands
					modelPartitionData[3 ].value = 3; // Face
					modelPartitionData[4 ].value = (beowulf) ? 3 : 2; // Fists
					modelPartitionData[5 ].value = 3; // Hair Base
					modelPartitionData[6 ].value = 3; // Hair Main
					modelPartitionData[7 ].value = (beowulf) ? 3 : 2; // Lower Legs Half
					modelPartitionData[8 ].value = (beowulf) ? 2 : 3; // Lower Legs and Feet
					modelPartitionData[9 ].value = 2; // Filler
					modelPartitionData[10].value = 2; // Filler

					break;
				}
				case COSTUME_VERGIL_NERO_ANGELO:
				case COSTUME_VERGIL_NERO_ANGELO_INFINITE_MAGIC_POINTS:
				{
					modelPartitionData[0 ].value = 3; // Neck
					modelPartitionData[1 ].value = 3; // Face
					modelPartitionData[2 ].value = (beowulf) ? 2 : 3; // Hands
					modelPartitionData[3 ].value = 3; // Eyes
					modelPartitionData[4 ].value = (beowulf) ? 3 : 2; // Fists
					modelPartitionData[5 ].value = 3; // Hair Base
					modelPartitionData[6 ].value = 3; // Hair Main
					modelPartitionData[7 ].value = (beowulf) ? 3 : 2; // Lower Legs Half
					modelPartitionData[8 ].value = (beowulf) ? 2 : 3; // Lower Legs and Feet
					modelPartitionData[9 ].value = (beowulf) ? 3 : 2; // Lower Arms Half
					modelPartitionData[10].value = (beowulf) ? 2 : 3; // Lower Arms
					modelPartitionData[11].value = 3; // Collar
					modelPartitionData[12].value = 3; // Lower Legs
					modelPartitionData[13].value = 3; // Shoulders
					modelPartitionData[14].value = 3; // Body

					break;
				}
			}

			break;
		}
	}
}

















void UpdateActorDante(ActorDataDante & actorData)
{
	LogFunction(actorData.operator byte8 *());

	actorData.devilModelMetadata.Rebellion.devilSubmodelMetadata[0].submodelIndex = 255;
	actorData.devilModelMetadata.Rebellion.devilSubmodelMetadata[1].submodelIndex = 255;
	actorData.devilModelMetadata.Cerberus.devilSubmodelMetadata.submodelIndex = 255;
	actorData.devilModelMetadata.Nevan.devilSubmodelMetadata[0].submodelIndex = 255;
	actorData.devilModelMetadata.Nevan.devilSubmodelMetadata[1].submodelIndex = 255;
	actorData.devilModelMetadata.Beowulf.devilSubmodelMetadata.submodelIndex = 255;
	actorData.devilModelMetadata.Sparda.devilSubmodelMetadata.submodelIndex = 255;
	/*
	dmc3.exe+212C20 - C6 81 02B60000 FF - mov byte ptr [rcx+0000B602],-01
	dmc3.exe+212C2B - C6 81 05B60000 FF - mov byte ptr [rcx+0000B605],-01
	dmc3.exe+212C32 - C6 81 0AB60000 FF - mov byte ptr [rcx+0000B60A],-01
	dmc3.exe+212C39 - C6 81 11B60000 FF - mov byte ptr [rcx+0000B611],-01
	dmc3.exe+212C40 - C6 81 14B60000 FF - mov byte ptr [rcx+0000B614],-01
	dmc3.exe+212C47 - C6 81 19B60000 FF - mov byte ptr [rcx+0000B619],-01
	dmc3.exe+212C4E - C6 81 1EB60000 FF - mov byte ptr [rcx+0000B61E],-01
	*/

	UpdateModel(actorData);

	func_1EF040(actorData, 0);
	func_1EEF80(actorData);
	func_1EF040(actorData, 3);

	if (actorData.sparda)
	{
		UpdateDevilModel(actorData, DEVIL_SPARDA, 0);
	}
	else
	{
		for_all(uint8, index, 5)
		{
			UpdateDevilModel(actorData, (DEVIL_REBELLION + index), index);
		}
	}

	// func_2EE060(actorData.var_6410, 60);
	// /*
	// dmc3.exe+2134C6 - 48 8D 8E 10640000 - lea rcx,[rsi+00006410]
	// dmc3.exe+2134CD - BA 3C000000       - mov edx,0000003C
	// dmc3.exe+2134D2 - E8 89AB0D00       - call dmc3.exe+2EE060
	// */

	// func_2C6150(actorData.var_6458, 0x49000, -2);
	// /*
	// dmc3.exe+214B37 - 48 8D 8E 58640000 - lea rcx,[rsi+00006458]
	// dmc3.exe+214B3E - BA 00900400       - mov edx,00049000
	// dmc3.exe+214B43 - 41 B8 FEFFFFFF    - mov r8d,FFFFFFFE
	// dmc3.exe+214B49 - E8 02160B00       - call dmc3.exe+2C6150
	// */

	actorData.actionData[0] = *reinterpret_cast<byte8 **>(appBaseAddr + 0x590598);
	actorData.actionData[1] = *reinterpret_cast<byte8 **>(appBaseAddr + 0x58A2A0);
	actorData.actionData[2] = (appBaseAddr + 0x5905B0);
	actorData.actionData[3] = File_staticFiles[pl000][9];
	actorData.actionData[4] = File_staticFiles[pl000][10];
	actorData.actionData[5] = File_staticFiles[pl000][11];
	/*
	dmc3.exe+214B50 - 48 8B 05 41BA3700 - mov rax,[dmc3.exe+590598]
	dmc3.exe+214B5E - 48 89 86 D03D0000 - mov [rsi+00003DD0],rax

	dmc3.exe+214B65 - 48 8B 05 34573700 - mov rax,[dmc3.exe+58A2A0]
	dmc3.exe+214B6C - 48 89 86 D83D0000 - mov [rsi+00003DD8],rax

	dmc3.exe+214B73 - 48 8D 05 36BA3700 - lea rax,[dmc3.exe+5905B0]
	dmc3.exe+214B7A - 48 89 86 E03D0000 - mov [rsi+00003DE0],rax

	dmc3.exe+212C27 - 45 8D 4F 09       - lea r9d,[r15+09]
	dmc3.exe+212C5C - E8 5F56FAFF       - call __GET_FILE__
	dmc3.exe+212C6C - 48 89 86 E83D0000 - mov [rsi+00003DE8],rax

	dmc3.exe+212C66 - 45 8D 4F 0A       - lea r9d,[r15+0A]
	dmc3.exe+212C7A - E8 4156FAFF       - call __GET_FILE__
	dmc3.exe+212C8A - 48 89 86 F03D0000 - mov [rsi+00003DF0],rax

	dmc3.exe+212C84 - 45 8D 4F 0B       - lea r9d,[r15+0B]
	dmc3.exe+212C98 - E8 2356FAFF       - call __GET_FILE__
	dmc3.exe+212CA0 - 48 89 86 F83D0000 - mov [rsi+00003DF8],rax
	*/

	func_2EE3D0(actorData.var_3C50);
	/*
	dmc3.exe+214B57 - 48 8D 8E 503C0000 - lea rcx,[rsi+00003C50]
	dmc3.exe+214B81 - E8 4A980D00       - call dmc3.exe+2EE3D0
	*/

	func_1FAF40(actorData);
}

// @Todo: Update.
template <typename T>
void UpdateForm
(
	T & actorData
)
{
	actorData.queuedModelIndex       = 0;
	actorData.activeModelIndexMirror = 0;
	actorData.airRaid                = 0;

	if (actorData.devil)
	{
		if constexpr (TypeMatch<T, ActorDataDante>::value)
		{
			if (actorData.sparda)
			{
				actorData.queuedModelIndex       = 1;
				actorData.activeModelIndexMirror = 1;
				actorData.activeDevil            = DEVIL_SPARDA;
				actorData.airRaid                = 0;
			}
			else
			{
				auto weapon = (WEAPON_REBELLION + actorData.meleeWeaponIndex);
				if (weapon > WEAPON_BEOWULF_DANTE)
				{
					weapon = WEAPON_REBELLION;
				}

				actorData.queuedModelIndex       = (1 + weapon);
				actorData.activeModelIndexMirror = (1 + weapon);
				actorData.activeDevil            = static_cast<uint32>(weaponDevilIds[weapon]);
				actorData.airRaid                = 0;

				func_1F97F0(actorData, true);
			}
		}
		else if constexpr (TypeMatch<T, ActorDataVergil>::value)
		{
			if (actorData.neroAngelo)
			{
				actorData.queuedModelIndex       = 1;
				actorData.activeModelIndexMirror = 1;
				actorData.activeDevil            = DEVIL_NERO_ANGELO;
				actorData.airRaid                = 0;
			}
			else
			{
				auto weapon = (WEAPON_YAMATO_VERGIL + actorData.queuedMeleeWeaponIndex);
				if
				(
					(weapon < WEAPON_YAMATO_VERGIL    ) ||
					(weapon > WEAPON_YAMATO_FORCE_EDGE)
				)
				{
					weapon = WEAPON_YAMATO_VERGIL;
				}

				actorData.queuedModelIndex       = (weapon == WEAPON_BEOWULF_VERGIL) ? 2 : 1;
				actorData.activeModelIndexMirror = (weapon == WEAPON_BEOWULF_VERGIL) ? 2 : 1;
				actorData.activeDevil            = static_cast<uint32>(weaponDevilIds[weapon]);
				actorData.airRaid                = 0;

				func_1F97F0(actorData, true);
			}
		}
	}
}

template <typename T>
void UpdateMotionArchives(T & actorData)
{
	constexpr uint8 count =
	(TypeMatch<T, ActorDataDante >::value) ? static_cast<uint8>(countof(motionArchiveHelperDante )) :
	(TypeMatch<T, ActorDataBob   >::value) ? static_cast<uint8>(countof(motionArchiveHelperBob   )) :
	(TypeMatch<T, ActorDataLady  >::value) ? static_cast<uint8>(countof(motionArchiveHelperLady  )) :
	(TypeMatch<T, ActorDataVergil>::value) ? static_cast<uint8>(countof(motionArchiveHelperVergil)) :
	0;

	const MotionArchiveHelper * motionArchiveHelper =
	(TypeMatch<T, ActorDataDante >::value) ? motionArchiveHelperDante  :
	(TypeMatch<T, ActorDataBob   >::value) ? motionArchiveHelperBob    :
	(TypeMatch<T, ActorDataLady  >::value) ? motionArchiveHelperLady   :
	(TypeMatch<T, ActorDataVergil>::value) ? motionArchiveHelperVergil :
	0;

	for_all(uint8, index, count)
	{
		auto & group = motionArchiveHelper[index].group;
		auto & cacheFileId = motionArchiveHelper[index].cacheFileId;

		auto & metadata = File_staticFiles[cacheFileId];

		actorData.motionArchives[group] = File_dynamicFiles.Push(metadata.addr, metadata.size);
	}
}

// template <typename T>
// void InitStyle(T & actorData)
// {
// 	if constexpr (TypeMatch<T, ActorDataDante>::value)
// 	{
// 		actorData.style = STYLE_TRICKSTER;
// 	}
// 	else if constexpr (TypeMatch<T, ActorDataBob>::value)
// 	{
// 		actorData.style = STYLE_DARK_SLAYER;
// 	}
// 	else if constexpr (TypeMatch<T, ActorDataVergil>::value)
// 	{
// 		actorData.style = STYLE_DARK_SLAYER;
// 	}
// }

// @Todo: Update.
template <typename T>
void InitWeapons(T & actorData)
{
	memset
	(
		(reinterpret_cast<byte8 *>(&actorData) + offsetof(ActorDataVergil, activeMeleeWeaponIndex)),
		0,
		(offsetof(ActorDataVergil, styleData) - offsetof(ActorDataVergil, activeMeleeWeaponIndex))
	);
	memset(actorData.newWeapons, WEAPON_VOID, sizeof(actorData.newWeapons));
	memset(actorData.newWeaponStatus, WEAPON_STATUS_DISABLED, sizeof(actorData.newWeaponStatus));

	constexpr uint8 count =
	(TypeMatch<T, ActorDataDante >::value) ? WEAPON_COUNT_DANTE  :
	(TypeMatch<T, ActorDataBob >::value) ? WEAPON_COUNT_BOB  :
	(TypeMatch<T, ActorDataVergil>::value) ? WEAPON_COUNT_VERGIL :
	0;

	for_all(uint8, index, count)
	{
		uint8 weapon =
		(TypeMatch<T, ActorDataDante >::value) ? (WEAPON_REBELLION     + index) :
		(TypeMatch<T, ActorDataBob >::value) ? (WEAPON_YAMATO_BOB     + index) :
		(TypeMatch<T, ActorDataVergil>::value) ? (WEAPON_YAMATO_VERGIL + index) :
		0;

		actorData.newWeapons[index] = weapon;
		actorData.newWeaponDataAddr[index] = RegisterWeapon[weapon](actorData, weapon);
		actorData.newWeaponStatus[index] = WEAPON_STATUS_READY;
	}

	if constexpr (TypeMatch<T, ActorDataDante>::value)
	{
		actorData.meleeWeaponIndex = 0;
		actorData.rangedWeaponIndex = 5;
	}
	else if constexpr (TypeMatch<T, ActorDataBob>::value)
	{
		actorData.meleeWeaponIndex = 0;
	}
	else if constexpr (TypeMatch<T, ActorDataVergil>::value)
	{
		actorData.activeMeleeWeaponIndex = 0;
		actorData.queuedMeleeWeaponIndex = 0;

		if (actorData.neroAngelo)
		{
			actorData.newWeaponDataAddr[3] = func_22CF00(actorData, 0);
		}
	}
}







auto GetStyle(CharacterData & characterData)
{
	auto & styleIndex = characterData.styleIndices[characterData.styleButtonIndex];

	return characterData.styles[characterData.styleButtonIndex][styleIndex];
}

template <typename T>
auto GetStyle(T & actorData)
{
	auto & characterData = GetCharacterData(actorData);

	return GetStyle(characterData);
}

template <typename T>
auto GetMeleeWeapon(T & actorData)
{
	auto & characterData = GetCharacterData(actorData);

	return characterData.meleeWeapons[characterData.meleeWeaponIndex];
}

template <typename T>
auto GetRangedWeapon(T & actorData)
{
	auto & characterData = GetCharacterData(actorData);

	return characterData.rangedWeapons[characterData.rangedWeaponIndex];
}












template <typename T>
void UpdateStyle(T & actorData)
{
	LogFunction(actorData.operator byte8 *());
	// auto & characterData = GetCharacterData(actorData);

	// auto & styleIndex = characterData.styleIndices[characterData.styleButtonIndex];
	// auto & style = characterData.styles[characterData.styleButtonIndex][styleIndex];

	actorData.style = GetStyle(actorData);
}

template <typename T>
void UpdateMeleeWeapon(T & actorData)
{
	LogFunction(actorData.operator byte8 *());
	auto & characterData = GetCharacterData(actorData);

	if (characterData.meleeWeaponIndex >= characterData.meleeWeaponCount)
	{
		characterData.meleeWeaponIndex = 0;
	}

	//auto weapon = characterData.meleeWeapons[characterData.meleeWeaponIndex];

	auto weapon = GetMeleeWeapon(actorData);




	// weapon = 3;

	// Log("weapon %u", weapon);

	// Log("meleeWeapon %u", characterData.meleeWeapons[characterData.meleeWeaponIndex]);

	if constexpr (TypeMatch<T, ActorDataDante>::value)
	{
		if (IsDanteMeleeWeapon(weapon))
		{
			actorData.meleeWeaponIndex = weapon;
		}
	}
	else if constexpr (TypeMatch<T, ActorDataVergil>::value)
	{
		if (IsVergilMeleeWeapon(weapon))
		{
			actorData.queuedMeleeWeaponIndex = (weapon - WEAPON_YAMATO_VERGIL);
		}
	}
}

template <typename T>
void UpdateRangedWeapon(T & actorData)
{
	LogFunction(actorData.operator byte8 *());
	auto & characterData = GetCharacterData(actorData);

	if (characterData.rangedWeaponIndex >= characterData.rangedWeaponCount)
	{
		characterData.rangedWeaponIndex = 0;
	}

	//auto weapon = characterData.rangedWeapons[characterData.rangedWeaponIndex];

	auto weapon = GetRangedWeapon(actorData);

	if constexpr (TypeMatch<T, ActorDataDante>::value)
	{
		if (IsDanteRangedWeapon(weapon))
		{
			actorData.rangedWeaponIndex = weapon;
		}
	}
}

template <typename T>
void UpdateWeapons(T & actorData)
{
	LogFunction(actorData.operator byte8 *());
	UpdateMeleeWeapon (actorData);
	UpdateRangedWeapon(actorData);
}












template <typename T>
byte8 * CreateActor
(
	uint8 playerIndex,
	uint8 characterIndex,
	uint8 entityIndex
)
{
	// LogFunction
	// (
	// 	playerIndex,
	// 	characterIndex,
	// 	entityIndex
	// );

	auto & playerData = GetPlayerData(playerIndex);
	auto & characterData = GetCharacterData
	(
		playerIndex,
		characterIndex,
		entityIndex
	);

	IntroduceMissionActorData(return 0);

	auto actorBaseAddr = func_1DE820(characterData.character, 0, false);
	if (!actorBaseAddr)
	{
		return 0;
	}
	auto & actorData = *reinterpret_cast<T *>(actorBaseAddr);

	UpdateFileData(actorData);

	InitActor(actorData, activeMissionActorData);

	actorData.shadow = 1;
	actorData.costume = characterData.costume;

	{
		bool value = false;

		if constexpr (TypeMatch<T, ActorDataDante>::value)
		{
			switch (actorData.costume)
			{
				case COSTUME_DANTE_DMC1:
				case COSTUME_DANTE_DMC1_NO_COAT:
				case COSTUME_DANTE_SPARDA:
				case COSTUME_DANTE_SPARDA_INFINITE_MAGIC_POINTS:
				{
					value = true;

					break;
				}
			}

			actorData.sparda = value;
		}
		else if constexpr (TypeMatch<T, ActorDataVergil>::value)
		{
			switch (actorData.costume)
			{
				case COSTUME_VERGIL_NERO_ANGELO:
				case COSTUME_VERGIL_NERO_ANGELO_INFINITE_MAGIC_POINTS:
				{
					value = true;

					break;
				}
			}

			actorData.neroAngelo = value;
		}
	}

	UpdateCostumeFileData(actorData);

	actorData.newPlayerIndex         = playerIndex;
	actorData.newCharacterIndex      = characterIndex;
	actorData.newEntityIndex         = entityIndex;
	actorData.newForceFiles          = characterData.forceFiles;
	actorData.newForceFilesCharacter = characterData.forceFilesCharacter;
	actorData.newGamepad             = playerIndex;

	if constexpr (TypeMatch<T, ActorDataDante>::value)
	{
		UpdateActorDante(actorData);
	}
	else
	{
		UpdateActor(actorData);
	}

	if (entityIndex == ENTITY_MAIN)
	{
		func_2EE060(actorData.var_6410, 60);
		/*
		dmc3.exe+2134C6 - 48 8D 8E 10640000 - lea rcx,[rsi+00006410]
		dmc3.exe+2134CD - BA 3C000000       - mov edx,0000003C
		dmc3.exe+2134D2 - E8 89AB0D00       - call dmc3.exe+2EE060
		*/

		func_2C6150(actorData.var_6458, 0x49000, -2);
		/*
		dmc3.exe+214B37 - 48 8D 8E 58640000 - lea rcx,[rsi+00006458]
		dmc3.exe+214B3E - BA 00900400       - mov edx,00049000
		dmc3.exe+214B43 - 41 B8 FEFFFFFF    - mov r8d,FFFFFFFE
		dmc3.exe+214B49 - E8 02160B00       - call dmc3.exe+2C6150
		*/
	}

	UpdateMotionArchives(actorData);

	UpdateStyle(actorData);

	if
	(
		(playerIndex == 0) &&
		(characterIndex == playerData.activeCharacterIndex) &&
		(entityIndex == ENTITY_MAIN)
	)
	{
		HUD_UpdateStyleIcon
		(
			GetStyle(actorData),
			characterData.character
		);
	}

	InitWeapons(actorData);

	UpdateWeapons(actorData);

	memset
	(
		actorData.expertise,
		0xFF,
		sizeof(actorData.expertise)
	);

	actorData.styleLevel = 2;

	if constexpr (TypeMatch<T, ActorDataDante>::value)
	{
		for_each(uint8, weaponIndex, WEAPON_EBONY_IVORY, WEAPON_COUNT_DANTE)
		{
			actorData.newWeaponLevels[weaponIndex] = 2;
		}
	}

	if (entityIndex == ENTITY_CLONE)
	{
		actorData.newIsClone = true;
	}

	func_1DFC20(actorData);

	CommissionActor(actorData);

	Actor_actorBaseAddr.Push(actorBaseAddr);

	return actorBaseAddr;
}





byte8 * SpawnActor
(
	uint8 playerIndex,
	uint8 characterIndex,
	uint8 entityIndex
)
{
	byte8 * actorBaseAddr = 0;

	auto & characterData = GetCharacterData
	(
		playerIndex,
		characterIndex,
		entityIndex
	);

	switch (characterData.character)
	{
		case CHAR_DANTE:
		{
			actorBaseAddr = CreateActor<ActorDataDante>
			(
				playerIndex,
				characterIndex,
				entityIndex
			);

			break;
		}
		case CHAR_BOB:
		{
			actorBaseAddr = CreateActor<ActorDataBob>
			(
				playerIndex,
				characterIndex,
				entityIndex
			);

			break;
		}
		case CHAR_LADY:
		{
			actorBaseAddr = CreateActor<ActorDataLady>
			(
				playerIndex,
				characterIndex,
				entityIndex
			);

			break;
		}
		case CHAR_VERGIL:
		{
			actorBaseAddr = CreateActor<ActorDataVergil>
			(
				playerIndex,
				characterIndex,
				entityIndex
			);

			break;
		}
	}

	return actorBaseAddr;
}






export void SpawnActors()
{
	LogFunction();

	// auto mainActorBaseAddr = Actor_actorBaseAddr[0];
	// if (!mainActorBaseAddr)
	// {
	// 	return;
	// }
	// auto & mainActorData = *reinterpret_cast<ActorData *>(mainActorBaseAddr);



	for_all(uint8, playerIndex, activeConfig.Actor.playerCount)
	{
		auto & playerData = GetPlayerData(playerIndex);

		if (playerData.characterIndex >= playerData.characterCount)
		{
			playerData.characterIndex = 0;
		}

		playerData.activeCharacterIndex = playerData.lastCharacterIndex = playerData.characterIndex;



		for_all(uint8, characterIndex, playerData.characterCount)
		{
			auto actorBaseAddr = SpawnActor
			(
				playerIndex,
				characterIndex,
				ENTITY_MAIN
			);
			if (!actorBaseAddr)
			{
				continue;
			}
			auto & actorData = *reinterpret_cast<ActorData *>(actorBaseAddr);

			actorData.cloneActorBaseAddr = SpawnActor
			(
				playerIndex,
				characterIndex,
				ENTITY_CLONE
			);
			if (!actorData.cloneActorBaseAddr)
			{
				continue;
			}
			//auto & cloneActorData = *reinterpret_cast<ActorData *>(cloneActorBaseAddr);

			// actorData.position = mainActorData.position;
			// actorData.rotation = mainActorData.rotation;
			//actorData.cloneActorBaseAddr = cloneActorBaseAddr;

			// cloneActorData.position = mainActorData.position;
			// cloneActorData.rotation = mainActorData.rotation;
		}
	}
}

#pragma endregion







#pragma region Controllers





// void RemoveBusyFlagController(byte8 * baseAddr)
// {
// 	if (!activeConfig.RemoveBusyFlag.enable)
// 	{
// 		return;
// 	}

// 	if (!baseAddr)
// 	{
// 		return;
// 	}
// 	if (baseAddr == Actor_actorBaseAddr[0])
// 	{
// 		return;
// 	}
// 	if (baseAddr == Actor_actorBaseAddr[1])
// 	{
// 		return;
// 	}
// 	auto & actorData = *reinterpret_cast<ActorData *>(baseAddr);

// 	if (actorData.buttons[2] & activeConfig.RemoveBusyFlag.button)
// 	{
// 		actorData.state &= ~STATE_BUSY;
// 	}
// }

void ResetPermissionsController(byte8 * baseAddr)
{
	if (!activeConfig.ResetPermissions.enable)
	{
		return;
	}

	if (!baseAddr)
	{
		return;
	}
	if (baseAddr == Actor_actorBaseAddr[0])
	{
		return;
	}
	if (baseAddr == Actor_actorBaseAddr[1])
	{
		return;
	}
	auto & actorData = *reinterpret_cast<ActorData *>(baseAddr);

	if (actorData.buttons[2] & activeConfig.ResetPermissions.button)
	{
		actorData.permissions = 0x1C1B;
	}
}




























template <typename T>
void StyleSwitchController(T & actorData)
{
	auto & playerData = GetPlayerData(actorData);
	auto & characterData = GetCharacterData(actorData);

	bool update = false;

	{
		bool condition = (actorData.buttons[0] & playerData.button);

		if (actorData.newEntityIndex == ENTITY_MAIN)
		{
			if (condition)
			{
				return;
			}
		}
		else
		{
			if (!condition)
			{
				return;
			}
		}
	}

	for_all(uint8, styleButtonIndex, STYLE_COUNT)
	{
		auto & styleButton = characterData.styleButtons[styleButtonIndex];
		auto & styleIndex = characterData.styleIndices[styleButtonIndex];

		auto lastStyleIndex = styleIndex;

		if (actorData.buttons[2] & styleButton)
		{
			if (characterData.styleButtonIndex == styleButtonIndex)
			{
				styleIndex++;

				if (styleIndex >= 2)
				{
					styleIndex = 0;
				}
			}
			else
			{
				styleIndex = 0;
			}

			auto style = characterData.styles[styleButtonIndex][styleIndex];

			switch (style)
			{
				case STYLE_QUICKSILVER:
				{
					if
					(
						(actorData.newPlayerIndex != 0) ||
						(actorData.newCharacterIndex != 0) ||
						(actorData.newEntityIndex != ENTITY_MAIN)
					)
					{
						styleIndex = lastStyleIndex;

						goto LoopContinue;
					}

					break;
				}
				case STYLE_DOPPELGANGER:
				{
					if (actorData.newEntityIndex != ENTITY_MAIN)
					{
						styleIndex = lastStyleIndex;

						goto LoopContinue;
					}

					break;
				}
			}

			characterData.styleButtonIndex = styleButtonIndex;

			update = true;

			break;
		}

		LoopContinue:;
	}

	if (!update)
	{
		return;
	}

	UpdateStyle(actorData);

	if (activeConfig.removeBusyFlag)
	{
		actorData.state &= ~STATE_BUSY;

		Log("%llX Remove Busy Flag", actorData.operator byte8 *());
	}

	if (actorData.newPlayerIndex != 0)
	{
		return;
	}
	else if (actorData.newEntityIndex != ENTITY_MAIN)
	{
		return;
	}

	HUD_UpdateStyleIcon
	(
		GetStyle(actorData),
		characterData.character
	);
}

template <typename T>
void MeleeWeaponSwitchController(T & actorData)
{
	auto & playerData = GetPlayerData(actorData);
	auto & characterData = GetCharacterData(actorData);

	bool update = false;

	bool forward = false;
	bool back = false;

	{
		bool condition = (actorData.buttons[0] & playerData.button);

		if (actorData.newEntityIndex == ENTITY_MAIN)
		{
			if (condition)
			{
				return;
			}
		}
		else
		{
			if (!condition)
			{
				return;
			}
		}
	}

	if (0 < actorData.meleeWeaponSwitchTimeout)
	{
		return;
	}
	else if (characterData.meleeWeaponCount < 2)
	{
		return;
	}

	auto Forward = [&]()
	{
		if (characterData.meleeWeaponIndex == (characterData.meleeWeaponCount - 1))
		{
			characterData.meleeWeaponIndex = 0;
		}
		else
		{
			characterData.meleeWeaponIndex++;
		}
		update = true;

		forward = true;
	};

	auto Back = [&]()
	{
		if (characterData.meleeWeaponIndex == 0)
		{
			characterData.meleeWeaponIndex = (characterData.meleeWeaponCount - 1);
		}
		else
		{
			characterData.meleeWeaponIndex--;
		}
		update = true;

		back = true;
	};

	if (actorData.buttons[2] & GetBinding(BINDING_CHANGE_DEVIL_ARMS))
	{
		if (actorData.buttons[0] & GetBinding(BINDING_TAUNT))
		{
			Back();
		}
		else
		{
			Forward();
		}
	}
	else if (actorData.buttons[2] & GetBinding(BINDING_CHANGE_GUN))
	{
		if constexpr (TypeMatch<T, ActorDataVergil>::value)
		{
			Back();
		}
	}

	if (!update)
	{
		return;
	}

	actorData.meleeWeaponSwitchTimeout = activeConfig.weaponSwitchTimeout;

	// Nero Angelo Fix
	{
		auto weapon = GetMeleeWeapon(actorData);

		if
		(
			IsNeroAngelo(actorData) &&
			(weapon == WEAPON_YAMATO_FORCE_EDGE)
		)
		{
			if (forward)
			{
				Forward();
			}
			else if (back)
			{
				Back();
			}
		}
	}

	UpdateMeleeWeapon(actorData);

	UpdateForm(actorData);

	if (actorData.newPlayerIndex != 0)
	{
		return;
	}
	else if (actorData.newEntityIndex != ENTITY_MAIN)
	{
		return;
	}

	IntroduceHUDPointers(return);

	HUD_UpdateWeaponIcon
	(
		HUD_BOTTOM_MELEE_WEAPON_1,
		GetMeleeWeapon(actorData)
	);

	func_280120(hudBottom, 1, 0); // @Todo: Enums.

	func_1EB0E0(actorData, 4);
}

template <typename T>
void RangedWeaponSwitchController(T & actorData)
{
	auto & playerData = GetPlayerData(actorData);
	auto & characterData = GetCharacterData(actorData);

	bool update = false;

	{
		bool condition = (actorData.buttons[0] & playerData.button);

		if (actorData.newEntityIndex == ENTITY_MAIN)
		{
			if (condition)
			{
				return;
			}
		}
		else
		{
			if (!condition)
			{
				return;
			}
		}
	}

	if (0 < actorData.rangedWeaponSwitchTimeout)
	{
		return;
	}
	else if (characterData.rangedWeaponCount < 2)
	{
		return;
	}

	auto Forward = [&]()
	{
		if (characterData.rangedWeaponIndex == (characterData.rangedWeaponCount - 1))
		{
			characterData.rangedWeaponIndex = 0;
		}
		else
		{
			characterData.rangedWeaponIndex++;
		}
		update = true;
	};

	auto Back = [&]()
	{
		if (characterData.rangedWeaponIndex == 0)
		{
			characterData.rangedWeaponIndex = (characterData.rangedWeaponCount - 1);
		}
		else
		{
			characterData.rangedWeaponIndex--;
		}
		update = true;
	};

	if (actorData.buttons[2] & GetBinding(BINDING_CHANGE_GUN))
	{
		if (actorData.buttons[0] & GetBinding(BINDING_TAUNT))
		{
			Back();
		}
		else
		{
			Forward();
		}
	}

	if (!update)
	{
		return;
	}

	actorData.rangedWeaponSwitchTimeout = activeConfig.weaponSwitchTimeout;

	UpdateRangedWeapon(actorData);

	if (actorData.newPlayerIndex != 0)
	{
		return;
	}
	else if (actorData.newEntityIndex != ENTITY_MAIN)
	{
		return;
	}

	IntroduceHUDPointers(return);

	HUD_UpdateWeaponIcon
	(
		HUD_BOTTOM_RANGED_WEAPON_1,
		GetRangedWeapon(actorData)
	);

	func_280120(hudBottom, 0, 0); // @Todo: Enums.

	func_1EB0E0(actorData, 4);
}

template <typename T>
bool WeaponSwitchController(byte8 * actorBaseAddr)
{
	if
	(
		!actorBaseAddr ||
		(actorBaseAddr == Actor_actorBaseAddr[0]) ||
		(actorBaseAddr == Actor_actorBaseAddr[1])
	)
	{
		return true;
	}
	auto & actorData = *reinterpret_cast<T *>(actorBaseAddr);

	if (actorData.mode == ACTOR_MODE_MISSION_18)
	{
		return true;
	}
	else if (actorData.var_3F19)
	{
		return false;
	}

	StyleSwitchController(actorData);

	MeleeWeaponSwitchController(actorData);

	if constexpr (TypeMatch<T, ActorDataDante>::value)
	{
		RangedWeaponSwitchController(actorData);
	}

	ResetPermissionsController(actorData);

	return true;
}















export bool g_executeButton[PLAYER_COUNT] = {};
export bool g_executeFunction[PLAYER_COUNT] = {};

export void CharacterSwitchController()
{
	if (!activeConfig.Actor.enable)
	{
		return;
	}

	for_all(uint8, playerIndex, activeConfig.Actor.playerCount)
	{
		auto & playerData = GetPlayerData(playerIndex);

		auto & gamepad = GetGamepad(playerIndex);

		auto & executeButton   = g_executeButton  [playerIndex];
		auto & executeFunction = g_executeFunction[playerIndex];

		byte8 * activeActorBaseAddr = 0;
		byte8 * idleActorBaseAddr   = 0;

		for_each(uint32, index, 2, Actor_actorBaseAddr.count)
		{
			IntroduceActorData(actorBaseAddr, actorData, Actor_actorBaseAddr[index], continue);

			if
			(
				InCutscene() ||
				(actorData.mode == ACTOR_MODE_MISSION_18) ||
				actorData.var_3F19
			)
			{
				continue;
			}
			else if
			(
				(actorData.newPlayerIndex == playerIndex) &&
				(actorData.newEntityIndex == ENTITY_MAIN) &&
				(actorData.newCharacterIndex == playerData.activeCharacterIndex)
			)
			{
				activeActorBaseAddr = actorBaseAddr;

				break;
			}
		}

		if (!activeActorBaseAddr)
		{
			continue;
		}
		auto & activeActorData = *reinterpret_cast<ActorData *>(activeActorBaseAddr);



		[&]()
		{
			if (playerData.characterCount < 2)
			{
				return;
			}
			else if (activeActorData.doppelganger)
			{
				return;
			}

			if (gamepad.buttons[0] & playerData.button)
			{
				if (executeButton)
				{
					executeButton = false;

					playerData.characterIndex++;

					if (playerData.characterIndex >= playerData.characterCount)
					{
						playerData.characterIndex = 0;
					}
				}
			}
			else
			{
				executeButton = true;
			}

			for_each(uint32, index, 2, Actor_actorBaseAddr.count)
			{
				IntroduceActorData(actorBaseAddr, actorData, Actor_actorBaseAddr[index], continue);
				//IntroduceActorData(actorBaseAddr, actorData, index, continue);
				// auto actorBaseAddr = Actor_actorBaseAddr[index];
				// if (!actorBaseAddr)
				// {
				// 	continue;
				// }
				// auto & actorData = *reinterpret_cast<ActorData *>(actorBaseAddr);

				if (actorData.newPlayerIndex != playerIndex)
				{
					continue;
				}
				else if (actorData.newEntityIndex != ENTITY_MAIN)
				{
					continue;
				}
				else if (actorData.newCharacterIndex == playerData.characterIndex)
				{
					idleActorBaseAddr = actorBaseAddr;

					break;
				}
			}

			if (!idleActorBaseAddr)
			{
				return;
			}
			auto & idleActorData = *reinterpret_cast<ActorData *>(idleActorBaseAddr);

			if (playerData.lastCharacterIndex != playerData.characterIndex)
			{
				playerData.lastCharacterIndex = playerData.characterIndex;

				ToggleInput(activeActorData, false);
				ToggleInput(idleActorData  , true );

				executeFunction = true;
			}

			if (!executeFunction)
			{
				return;
			}

			// @Todo: Create function.
			if (IsActive(activeActorData))
			{
				if (IsActive(idleActorData))
				{
					executeFunction = false;

					playerData.activeCharacterIndex = playerData.characterIndex;

					ToggleActor(activeActorData, false);
					ToggleActor(idleActorData  , true );

					EndMotion(activeActorData);

					UpdatePermissions(idleActorData);

					if (playerIndex == 0)
					{
						auto & characterData = GetCharacterData(idleActorData);

						HUD_UpdateStyleIcon
						(
							GetStyle(characterData),
							characterData.character
						);

						SetMainActor(idleActorData);
					}
				}
			}
			else
			{
				executeFunction = false;

				playerData.activeCharacterIndex = playerData.characterIndex;

				ToggleActor(activeActorData, false);
				ToggleActor(idleActorData  , true );

				EndMotion(activeActorData);

				UpdatePermissions(idleActorData);

				if (playerIndex == 0)
				{
					auto & characterData = GetCharacterData(idleActorData);

					HUD_UpdateStyleIcon
					(
						GetStyle(characterData),
						characterData.character
					);

					SetMainActor(idleActorData);
				}
			}
		}();



		for_each(uint32, index, 2, Actor_actorBaseAddr.count)
		{
			//IntroduceActorData(actorBaseAddr, actorData, index, continue);
			IntroduceActorData(actorBaseAddr, actorData, Actor_actorBaseAddr[index], continue);
			// auto actorBaseAddr = Actor_actorBaseAddr[index];
			// if (!actorBaseAddr)
			// {
			// 	continue;
			// }
			// auto & actorData = *reinterpret_cast<ActorData *>(actorBaseAddr);

			if (InCutscene())
			{
				continue;
			}
			else if (actorData.newPlayerIndex != playerIndex)
			{
				continue;
			}
			else if
			(
				(actorData.newCharacterIndex == playerData.activeCharacterIndex) &&
				(actorData.newEntityIndex == ENTITY_MAIN)
			)
			{
				continue;
			}
			else if
			(
				(actorData.newCharacterIndex == playerData.activeCharacterIndex) &&
				(actorData.newEntityIndex == ENTITY_CLONE) &&
				actorData.doppelganger
			)
			{
				continue;
			}

			CopyState(activeActorData, actorData);
		}
	}
}

#pragma endregion

#pragma region Relocations

export void ToggleRelocations(bool enable)
{
	LogFunction(enable);
	// 0x200
	{
		constexpr auto off = offsetof(ActorData, modelData[0]);
		constexpr auto newOff = offsetof(ActorData, newModelData[0]);
		static_assert(off == 0x200);
		// Update Actor Dante
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
		// Update Actor Bob
		Write<uint32>((appBaseAddr + 0x225E61 + 3), (enable) ? newOff : off); // dmc3.exe+225E61 - 49 8D B6 00020000 - LEA RSI,[R14+00000200]
		Write<uint32>((appBaseAddr + 0x226414 + 3), (enable) ? newOff : off); // dmc3.exe+226414 - 4C 8B 83 00020000 - MOV R8,[RBX+00000200]
		Write<uint32>((appBaseAddr + 0x22641B + 3), (enable) ? newOff : off); // dmc3.exe+22641B - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		Write<uint32>((appBaseAddr + 0x226426 + 3), (enable) ? newOff : off); // dmc3.exe+226426 - 4C 8B 8B 00020000 - MOV R9,[RBX+00000200]
		Write<uint32>((appBaseAddr + 0x22642D + 3), (enable) ? newOff : off); // dmc3.exe+22642D - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x226988 + 3), (enable) ? newOff : off); // dmc3.exe+226988 - 4C 8B 83 00020000 - MOV R8,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x22698F + 3), (enable) ? newOff : off); // dmc3.exe+22698F - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x22699A + 3), (enable) ? newOff : off); // dmc3.exe+22699A - 4C 8B 8B 00020000 - MOV R9,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x2269A1 + 3), (enable) ? newOff : off); // dmc3.exe+2269A1 - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		Write<uint32>((appBaseAddr + 0x226C65 + 3), (enable) ? newOff : off); // dmc3.exe+226C65 - 49 8D 8E 00020000 - LEA RCX,[R14+00000200]
		Write<uint32>((appBaseAddr + 0x226C7D + 3), (enable) ? newOff : off); // dmc3.exe+226C7D - 49 8D 8E 00020000 - LEA RCX,[R14+00000200]
		// Update Actor Lady
		Write<uint32>((appBaseAddr + 0x219318 + 3), (enable) ? newOff : off); // dmc3.exe+219318 - 4C 8D A5 00020000 - LEA R12,[RBP+00000200]
		// Update Actor Vergil
		Write<uint32>((appBaseAddr + 0x220E21 + 3), (enable) ? newOff : off); // dmc3.exe+220E21 - 49 81 C6 00020000 - ADD R14,00000200
		Write<uint32>((appBaseAddr + 0x2211EB + 3), (enable) ? newOff : off); // dmc3.exe+2211EB - 49 81 C6 00020000 - ADD R14,00000200
		Write<uint32>((appBaseAddr + 0x2215F0 + 3), (enable) ? newOff : off); // dmc3.exe+2215F0 - 49 81 C6 00020000 - ADD R14,00000200
		// Update Model Dante
		Write<uint32>((appBaseAddr + 0x214D95 + 3), (enable) ? newOff : off); // dmc3.exe+214D95 - 49 8D B6 00020000 - LEA RSI,[R14+00000200]
		// Update Model Vergil
		Write<uint32>((appBaseAddr + 0x22202B + 3), (enable) ? newOff : off); // dmc3.exe+22202B - 4C 8D B5 00020000 - LEA R14,[RBP+00000200]
		// func_1DDAF0
		Write<uint32>((appBaseAddr + 0x1DDB4B + 3), (enable) ? newOff : off); // dmc3.exe+1DDB4B - 48 8D 8E 00020000 - LEA RCX,[RSI+00000200]
		// func_1DE280
		Write<uint32>((appBaseAddr + 0x1DE41A + 3), (enable) ? newOff : off); // dmc3.exe+1DE41A - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// func_1DE750
		Write<uint32>((appBaseAddr + 0x1DE764 + 3), (enable) ? newOff : off); // dmc3.exe+1DE764 - 48 8D 99 00020000 - LEA RBX,[RCX+00000200]
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF09A + 3), (enable) ? newOff : off); // dmc3.exe+1EF09A - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x1EF3E0 + 3), (enable) ? newOff : off); // dmc3.exe+1EF3E0 - 4D 8D BD 00020000 - LEA R15,[R13+00000200]
		// Other
		Write<uint32>((appBaseAddr + 0xC9F2B + 3), (enable) ? newOff : off); // dmc3.exe+C9F2B - 49 8D 8F 00020000 - LEA RCX,[R15+00000200]
		Write<uint32>((appBaseAddr + 0x1DFD29 + 3), (enable) ? newOff : off); // dmc3.exe+1DFD29 - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x1EEF16 + 3), (enable) ? newOff : off); // dmc3.exe+1EEF16 - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x1EEF4D + 3), (enable) ? newOff : off); // dmc3.exe+1EEF4D - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x1EF566 + 3), (enable) ? newOff : off); // dmc3.exe+1EF566 - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x1EF5CC + 3), (enable) ? newOff : off); // dmc3.exe+1EF5CC - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x1EF6DC + 3), (enable) ? newOff : off); // dmc3.exe+1EF6DC - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x1EF8B3 + 3), (enable) ? newOff : off); // dmc3.exe+1EF8B3 - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x1FB570 + 3), (enable) ? newOff : off); // dmc3.exe+1FB570 - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x1FB7C3 + 3), (enable) ? newOff : off); // dmc3.exe+1FB7C3 - 48 8D B3 00020000 - LEA RSI,[RBX+00000200]
		Write<uint32>((appBaseAddr + 0x1FB946 + 3), (enable) ? newOff : off); // dmc3.exe+1FB946 - 48 8D B3 00020000 - LEA RSI,[RBX+00000200]
		Write<uint32>((appBaseAddr + 0x1FB9D1 + 3), (enable) ? newOff : off); // dmc3.exe+1FB9D1 - 48 81 C3 00020000 - ADD RBX,00000200
		Write<uint32>((appBaseAddr + 0x1FC3CB + 3), (enable) ? newOff : off); // dmc3.exe+1FC3CB - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x1FC525 + 3), (enable) ? newOff : off); // dmc3.exe+1FC525 - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x1FCA34 + 3), (enable) ? newOff : off); // dmc3.exe+1FCA34 - 48 8D B1 00020000 - LEA RSI,[RCX+00000200]
		Write<uint32>((appBaseAddr + 0x1FCB5B + 3), (enable) ? newOff : off); // dmc3.exe+1FCB5B - 4C 8D B7 00020000 - LEA R14,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x1FCC97 + 3), (enable) ? newOff : off); // dmc3.exe+1FCC97 - 4C 8D B7 00020000 - LEA R14,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x1FCCFC + 3), (enable) ? newOff : off); // dmc3.exe+1FCCFC - 4C 8D B7 00020000 - LEA R14,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x1FCD6A + 3), (enable) ? newOff : off); // dmc3.exe+1FCD6A - 4C 8D B7 00020000 - LEA R14,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x1FCDEC + 3), (enable) ? newOff : off); // dmc3.exe+1FCDEC - 4C 8D B7 00020000 - LEA R14,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x1FCE63 + 3), (enable) ? newOff : off); // dmc3.exe+1FCE63 - 4C 8D B7 00020000 - LEA R14,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x2005C0 + 3), (enable) ? newOff : off); // dmc3.exe+2005C0 - 48 8D 83 00020000 - LEA RAX,[RBX+00000200]
		Write<uint32>((appBaseAddr + 0x216A1E + 3), (enable) ? newOff : off); // dmc3.exe+216A1E - 48 8D 99 00020000 - LEA RBX,[RCX+00000200]
		Write<uint32>((appBaseAddr + 0x216A55 + 3), (enable) ? newOff : off); // dmc3.exe+216A55 - 48 8D 99 00020000 - LEA RBX,[RCX+00000200]
		Write<uint32>((appBaseAddr + 0x218A2F + 3), (enable) ? newOff : off); // dmc3.exe+218A2F - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x219AA1 + 3), (enable) ? newOff : off); // dmc3.exe+219AA1 - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x223455 + 3), (enable) ? newOff : off); // dmc3.exe+223455 - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x22347F + 3), (enable) ? newOff : off); // dmc3.exe+22347F - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x2234A7 + 3), (enable) ? newOff : off); // dmc3.exe+2234A7 - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x2234D1 + 3), (enable) ? newOff : off); // dmc3.exe+2234D1 - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x22350F + 3), (enable) ? newOff : off); // dmc3.exe+22350F - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x223528 + 3), (enable) ? newOff : off); // dmc3.exe+223528 - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x223543 + 3), (enable) ? newOff : off); // dmc3.exe+223543 - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x22355C + 3), (enable) ? newOff : off); // dmc3.exe+22355C - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x223590 + 3), (enable) ? newOff : off); // dmc3.exe+223590 - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x2235BA + 3), (enable) ? newOff : off); // dmc3.exe+2235BA - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x2235DF + 3), (enable) ? newOff : off); // dmc3.exe+2235DF - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x2235F8 + 3), (enable) ? newOff : off); // dmc3.exe+2235F8 - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x223611 + 3), (enable) ? newOff : off); // dmc3.exe+223611 - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x22362A + 3), (enable) ? newOff : off); // dmc3.exe+22362A - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x22364D + 3), (enable) ? newOff : off); // dmc3.exe+22364D - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x223666 + 3), (enable) ? newOff : off); // dmc3.exe+223666 - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x22367F + 3), (enable) ? newOff : off); // dmc3.exe+22367F - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x223698 + 3), (enable) ? newOff : off); // dmc3.exe+223698 - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Unknown
		// Write<uint32>((appBaseAddr + 0x23470 + 3), (enable) ? newOff : off); // dmc3.exe+23470 - 48 89 8B 00020000 - MOV [RBX+00000200],RCX
		// Write<uint32>((appBaseAddr + 0xDB2A9 + 3), (enable) ? newOff : off); // dmc3.exe+DB2A9 - 48 8B 89 00020000 - MOV RCX,[RCX+00000200]
		// Write<uint32>((appBaseAddr + 0x101747 + 3), (enable) ? newOff : off); // dmc3.exe+101747 - 4C 8D 83 00020000 - LEA R8,[RBX+00000200]
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
		// Write<uint32>((appBaseAddr + 0x1EF762 + 3), (enable) ? newOff : off); // dmc3.exe+1EF762 - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x1EF7B3 + 3), (enable) ? newOff : off); // dmc3.exe+1EF7B3 - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x1EF7F3 + 3), (enable) ? newOff : off); // dmc3.exe+1EF7F3 - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x1EF82E + 3), (enable) ? newOff : off); // dmc3.exe+1EF82E - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x1EF867 + 3), (enable) ? newOff : off); // dmc3.exe+1EF867 - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x1FB70B + 3), (enable) ? newOff : off); // dmc3.exe+1FB70B - 48 8D B3 00020000 - LEA RSI,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x1FB88C + 3), (enable) ? newOff : off); // dmc3.exe+1FB88C - 48 8D B3 00020000 - LEA RSI,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x1FCBC7 + 3), (enable) ? newOff : off); // dmc3.exe+1FCBC7 - 4C 8D B7 00020000 - LEA R14,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x1FCC2D + 3), (enable) ? newOff : off); // dmc3.exe+1FCC2D - 4C 8D B7 00020000 - LEA R14,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x2DC32D + 2), (enable) ? newOff : off); // dmc3.exe+2DC32D - 48 05 00020000 - ADD RAX,00000200
		// Write<uint32>((appBaseAddr + 0x2DE765 + 2), (enable) ? newOff : off); // dmc3.exe+2DE765 - 48 05 00020000 - ADD RAX,00000200
		// Write<uint32>((appBaseAddr + 0x2DE827 + 2), (enable) ? newOff : off); // dmc3.exe+2DE827 - 48 05 00020000 - ADD RAX,00000200
		// Write<uint32>((appBaseAddr + 0x2DEB27 + 2), (enable) ? newOff : off); // dmc3.exe+2DEB27 - 48 05 00020000 - ADD RAX,00000200
		// Write<uint32>((appBaseAddr + 0x2FB2DB + 4), (enable) ? newOff : off); // dmc3.exe+2FB2DB - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB30E + 4), (enable) ? newOff : off); // dmc3.exe+2FB30E - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB341 + 4), (enable) ? newOff : off); // dmc3.exe+2FB341 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB374 + 4), (enable) ? newOff : off); // dmc3.exe+2FB374 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB3AC + 4), (enable) ? newOff : off); // dmc3.exe+2FB3AC - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB3DF + 4), (enable) ? newOff : off); // dmc3.exe+2FB3DF - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB412 + 4), (enable) ? newOff : off); // dmc3.exe+2FB412 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB445 + 4), (enable) ? newOff : off); // dmc3.exe+2FB445 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB47D + 4), (enable) ? newOff : off); // dmc3.exe+2FB47D - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB4B0 + 4), (enable) ? newOff : off); // dmc3.exe+2FB4B0 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB4E3 + 4), (enable) ? newOff : off); // dmc3.exe+2FB4E3 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB516 + 4), (enable) ? newOff : off); // dmc3.exe+2FB516 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB54E + 4), (enable) ? newOff : off); // dmc3.exe+2FB54E - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB583 + 4), (enable) ? newOff : off); // dmc3.exe+2FB583 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB5B8 + 4), (enable) ? newOff : off); // dmc3.exe+2FB5B8 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB5ED + 4), (enable) ? newOff : off); // dmc3.exe+2FB5ED - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB622 + 4), (enable) ? newOff : off); // dmc3.exe+2FB622 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB657 + 4), (enable) ? newOff : off); // dmc3.exe+2FB657 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB68C + 4), (enable) ? newOff : off); // dmc3.exe+2FB68C - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB6C1 + 4), (enable) ? newOff : off); // dmc3.exe+2FB6C1 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB6F6 + 4), (enable) ? newOff : off); // dmc3.exe+2FB6F6 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB72B + 4), (enable) ? newOff : off); // dmc3.exe+2FB72B - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB760 + 4), (enable) ? newOff : off); // dmc3.exe+2FB760 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB795 + 4), (enable) ? newOff : off); // dmc3.exe+2FB795 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB7CA + 4), (enable) ? newOff : off); // dmc3.exe+2FB7CA - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB7FF + 4), (enable) ? newOff : off); // dmc3.exe+2FB7FF - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB834 + 4), (enable) ? newOff : off); // dmc3.exe+2FB834 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB869 + 4), (enable) ? newOff : off); // dmc3.exe+2FB869 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
	}
	// 0x208
	{
		constexpr auto off = (offsetof(ActorData, modelData[0]) + 8);
		constexpr auto newOff = (offsetof(ActorData, newModelData[0]) + 8);
		static_assert(off == 0x208);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF412 + 3), (enable) ? newOff : off); // dmc3.exe+1EF412 - 49 8D AD 08020000 - LEA RBP,[R13+00000208]
		// Other
		Write<uint32>((appBaseAddr + 0x2005B9 + 3), (enable) ? newOff : off); // dmc3.exe+2005B9 - 48 8D 8B 08020000 - LEA RCX,[RBX+00000208]
		// Unknown
		// Write<uint32>((appBaseAddr + 0x2A108 + 3), (enable) ? newOff : off); // dmc3.exe+2A108 - 48 81 C2 08020000 - ADD RDX,00000208
		// Write<uint32>((appBaseAddr + 0x2A83B + 3), (enable) ? newOff : off); // dmc3.exe+2A83B - 48 81 C3 08020000 - ADD RBX,00000208
		// Write<uint32>((appBaseAddr + 0x2DE34 + 3), (enable) ? newOff : off); // dmc3.exe+2DE34 - 41 B8 08020000 - MOV R8D,00000208
		// Write<uint32>((appBaseAddr + 0x10135F + 3), (enable) ? newOff : off); // dmc3.exe+10135F - 48 89 B9 08020000 - MOV [RCX+00000208],RDI
		// Write<uint32>((appBaseAddr + 0x10461F + 3), (enable) ? newOff : off); // dmc3.exe+10461F - 48 8B 81 08020000 - MOV RAX,[RCX+00000208]
		// Write<uint32>((appBaseAddr + 0x10463F + 3), (enable) ? newOff : off); // dmc3.exe+10463F - 48 89 B1 08020000 - MOV [RCX+00000208],RSI
		// Write<uint32>((appBaseAddr + 0x104646 + 3), (enable) ? newOff : off); // dmc3.exe+104646 - 48 39 B1 08020000 - CMP [RCX+00000208],RSI
		// Write<uint32>((appBaseAddr + 0x1046D3 + 3), (enable) ? newOff : off); // dmc3.exe+1046D3 - 48 8B 87 08020000 - MOV RAX,[RDI+00000208]
		// Write<uint32>((appBaseAddr + 0x104701 + 3), (enable) ? newOff : off); // dmc3.exe+104701 - 48 8B 87 08020000 - MOV RAX,[RDI+00000208]
		// Write<uint32>((appBaseAddr + 0x1050AB + 3), (enable) ? newOff : off); // dmc3.exe+1050AB - F3 0F59 97 08020000 - MULSS XMM2,[RDI+00000208]
		// Write<uint32>((appBaseAddr + 0x105EBF + 3), (enable) ? newOff : off); // dmc3.exe+105EBF - 48 8B 81 08020000 - MOV RAX,[RCX+00000208]
		// Write<uint32>((appBaseAddr + 0x105EDF + 3), (enable) ? newOff : off); // dmc3.exe+105EDF - 48 89 B1 08020000 - MOV [RCX+00000208],RSI
		// Write<uint32>((appBaseAddr + 0x105EE6 + 3), (enable) ? newOff : off); // dmc3.exe+105EE6 - 48 39 B1 08020000 - CMP [RCX+00000208],RSI
		// Write<uint32>((appBaseAddr + 0x105F4E + 3), (enable) ? newOff : off); // dmc3.exe+105F4E - 48 8B 83 08020000 - MOV RAX,[RBX+00000208]
		// Write<uint32>((appBaseAddr + 0x22EE29 + 3), (enable) ? newOff : off); // dmc3.exe+22EE29 - 48 8D 81 08020000 - LEA RAX,[RCX+00000208]
		// Write<uint32>((appBaseAddr + 0x22EF4F + 3), (enable) ? newOff : off); // dmc3.exe+22EF4F - 48 05 08020000 - ADD RAX,00000208
		// Write<uint32>((appBaseAddr + 0x24297E + 3), (enable) ? newOff : off); // dmc3.exe+24297E - 48 8D 8F 08020000 - LEA RCX,[RDI+00000208]
		// Write<uint32>((appBaseAddr + 0x2429A4 + 3), (enable) ? newOff : off); // dmc3.exe+2429A4 - 48 8D 8F 08020000 - LEA RCX,[RDI+00000208]
		// Write<uint32>((appBaseAddr + 0x2429B5 + 3), (enable) ? newOff : off); // dmc3.exe+2429B5 - 48 8D 8F 08020000 - LEA RCX,[RDI+00000208]
		// Write<uint32>((appBaseAddr + 0x242AC0 + 3), (enable) ? newOff : off); // dmc3.exe+242AC0 - 48 8D 8F 08020000 - LEA RCX,[RDI+00000208]
		// Write<uint32>((appBaseAddr + 0x242ADA + 3), (enable) ? newOff : off); // dmc3.exe+242ADA - 48 8D 8F 08020000 - LEA RCX,[RDI+00000208]
		// Write<uint32>((appBaseAddr + 0x242AEB + 3), (enable) ? newOff : off); // dmc3.exe+242AEB - 48 8D 8F 08020000 - LEA RCX,[RDI+00000208]
	}
	// 0x980
	{
		constexpr auto off = offsetof(ActorData, modelData[1]);
		constexpr auto newOff = offsetof(ActorData, newModelData[1]);
		static_assert(off == 0x980);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF2B4 + 3), (enable) ? newOff : off); // dmc3.exe+1EF2B4 - 49 8B 85 80090000 - MOV RAX,[R13+00000980]
		Write<uint32>((appBaseAddr + 0x1EF2C8 + 3), (enable) ? newOff : off); // dmc3.exe+1EF2C8 - 49 8D 8D 80090000 - LEA RCX,[R13+00000980]
		Write<uint32>((appBaseAddr + 0x1EF2D5 + 3), (enable) ? newOff : off); // dmc3.exe+1EF2D5 - 49 8D 8D 80090000 - LEA RCX,[R13+00000980]
		Write<uint32>((appBaseAddr + 0x1EF2EB + 3), (enable) ? newOff : off); // dmc3.exe+1EF2EB - 4D 8D B5 80090000 - LEA R14,[R13+00000980]
	}
	// 0x988
	{
		constexpr auto off = (offsetof(ActorData, modelData[1]) + 8);
		constexpr auto newOff = (offsetof(ActorData, newModelData[1]) + 8);
		static_assert(off == 0x988);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF2F2 + 3), (enable) ? newOff : off); // dmc3.exe+1EF2F2 - 49 8D AD 88090000 - lea rbp,[r13+00000988]
	}
	// 0x1100
	{
		constexpr auto off = offsetof(ActorData, modelData[2]);
		constexpr auto newOff = offsetof(ActorData, newModelData[2]);
		static_assert(off == 0x1100);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF188 + 3), (enable) ? newOff : off); // dmc3.exe+1EF188 - 49 8B 85 00110000 - MOV RAX,[R13+00001100]
		Write<uint32>((appBaseAddr + 0x1EF19C + 3), (enable) ? newOff : off); // dmc3.exe+1EF19C - 49 8D 8D 00110000 - LEA RCX,[R13+00001100]
		Write<uint32>((appBaseAddr + 0x1EF1A9 + 3), (enable) ? newOff : off); // dmc3.exe+1EF1A9 - 49 8D 8D 00110000 - LEA RCX,[R13+00001100]
		Write<uint32>((appBaseAddr + 0x1EF1BF + 3), (enable) ? newOff : off); // dmc3.exe+1EF1BF - 4D 8D B5 00110000 - LEA R14,[R13+00001100]
		// Unknown
		// Write<uint32>((appBaseAddr + 0x1400C4 + 3), (enable) ? newOff : off); // dmc3.exe+1400C4 - 48 8B 96 00110000 - MOV RDX,[RSI+00001100]
		// Write<uint32>((appBaseAddr + 0x14051A + 3), (enable) ? newOff : off); // dmc3.exe+14051A - 48 8B 93 00110000 - MOV RDX,[RBX+00001100]
		// Write<uint32>((appBaseAddr + 0x1405E5 + 3), (enable) ? newOff : off); // dmc3.exe+1405E5 - 48 8B 93 00110000 - MOV RDX,[RBX+00001100]
		// Write<uint32>((appBaseAddr + 0x141E29 + 3), (enable) ? newOff : off); // dmc3.exe+141E29 - 48 8B 93 00110000 - MOV RDX,[RBX+00001100]
		// Write<uint32>((appBaseAddr + 0x165F5A + 3), (enable) ? newOff : off); // dmc3.exe+165F5A - 48 8B 81 00110000 - MOV RAX,[RCX+00001100]
		// Write<uint32>((appBaseAddr + 0x165F7A + 3), (enable) ? newOff : off); // dmc3.exe+165F7A - 48 89 B9 00110000 - MOV [RCX+00001100],RDI
		// Write<uint32>((appBaseAddr + 0x165F81 + 3), (enable) ? newOff : off); // dmc3.exe+165F81 - 48 8B 89 00110000 - MOV RCX,[RCX+00001100]
		// Write<uint32>((appBaseAddr + 0x165F92 + 3), (enable) ? newOff : off); // dmc3.exe+165F92 - 48 89 BB 00110000 - MOV [RBX+00001100],RDI
		// Write<uint32>((appBaseAddr + 0x16601A + 3), (enable) ? newOff : off); // dmc3.exe+16601A - 48 8B 81 00110000 - MOV RAX,[RCX+00001100]
		// Write<uint32>((appBaseAddr + 0x16603A + 3), (enable) ? newOff : off); // dmc3.exe+16603A - 48 89 B9 00110000 - MOV [RCX+00001100],RDI
		// Write<uint32>((appBaseAddr + 0x166041 + 3), (enable) ? newOff : off); // dmc3.exe+166041 - 48 39 B9 00110000 - CMP [RCX+00001100],RDI
		// Write<uint32>((appBaseAddr + 0x166061 + 3), (enable) ? newOff : off); // dmc3.exe+166061 - 48 89 83 00110000 - MOV [RBX+00001100],RAX
		// Write<uint32>((appBaseAddr + 0x16608C + 3), (enable) ? newOff : off); // dmc3.exe+16608C - 48 8B 83 00110000 - MOV RAX,[RBX+00001100]
	}
	// 0x1108
	{
		constexpr auto off = (offsetof(ActorData, modelData[2]) + 8);
		constexpr auto newOff = (offsetof(ActorData, newModelData[2]) + 8);
		static_assert(off == 0x1108);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF1C6 + 3), (enable) ? newOff : off); // dmc3.exe+1EF1C6 - 49 8D AD 08110000 - lea rbp,[r13+00001108]
	}
	// 0x1880
	{
		constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][0]);
		constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][0]);
		static_assert(off == 0x1880);
		// Create Actor Dante
		Write<uint32>((appBaseAddr + 0x1DEC5C + 3), (enable) ? newOff : off); // dmc3.exe+1DEC5C - 48 8D 90 80180000 - LEA RDX,[RAX+00001880]
		// Create Actor Bob
		Write<uint32>((appBaseAddr + 0x1DEB43 + 3), (enable) ? newOff : off); // dmc3.exe+1DEB43 - 48 8D 90 80180000 - LEA RDX,[RAX+00001880]
		// Create Actor Lady
		Write<uint32>((appBaseAddr + 0x1DEA47 + 3), (enable) ? newOff : off); // dmc3.exe+1DEA47 - 48 8D 90 80180000 - LEA RDX,[RAX+00001880]
		// Create Actor Vergil
		Write<uint32>((appBaseAddr + 0x1DE92E + 3), (enable) ? newOff : off); // dmc3.exe+1DE92E - 48 8D 90 80180000 - LEA RDX,[RAX+00001880]
		// Update Actor Dante
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
		// Update Actor Bob
		Write<uint32>((appBaseAddr + 0x2261BE + 3), (enable) ? newOff : off); // dmc3.exe+2261BE - 49 8D 96 80180000 - LEA RDX,[R14+00001880]
		Write<uint32>((appBaseAddr + 0x2265C7 + 4), (enable) ? newOff : off); // dmc3.exe+2265C7 - 49 8B 8C C6 80180000 - MOV RCX,[R14+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x226638 + 4), (enable) ? newOff : off); // dmc3.exe+226638 - 49 8B 8C C6 80180000 - MOV RCX,[R14+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2267CD + 4), (enable) ? newOff : off); // dmc3.exe+2267CD - 49 8B 8C C6 80180000 - MOV RCX,[R14+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22683E + 4), (enable) ? newOff : off); // dmc3.exe+22683E - 49 8B 8C C6 80180000 - MOV RCX,[R14+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x226B37 + 4), (enable) ? newOff : off); // dmc3.exe+226B37 - 49 8B 8C C6 80180000 - MOV RCX,[R14+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x226BA0 + 4), (enable) ? newOff : off); // dmc3.exe+226BA0 - 49 8B 8C C6 80180000 - MOV RCX,[R14+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x226BFD + 4), (enable) ? newOff : off); // dmc3.exe+226BFD - 49 8B 8C C6 80180000 - MOV RCX,[R14+RAX*8+00001880]
		// Update Actor Lady
		Write<uint32>((appBaseAddr + 0x2194B2 + 3), (enable) ? newOff : off); // dmc3.exe+2194B2 - 48 8D 95 80180000 - LEA RDX,[RBP+00001880]
		// Update Actor Vergil
		Write<uint32>((appBaseAddr + 0x22112F + 4), (enable) ? newOff : off); // dmc3.exe+22112F - 49 8B 8C C4 80180000 - MOV RCX,[R12+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22148C + 4), (enable) ? newOff : off); // dmc3.exe+22148C - 49 8B 8C C4 80180000 - MOV RCX,[R12+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2214E5 + 4), (enable) ? newOff : off); // dmc3.exe+2214E5 - 49 8B 8C C4 80180000 - MOV RCX,[R12+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x221551 + 4), (enable) ? newOff : off); // dmc3.exe+221551 - 49 8B 8C C4 80180000 - MOV RCX,[R12+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22188B + 4), (enable) ? newOff : off); // dmc3.exe+22188B - 49 8B 8C C4 80180000 - MOV RCX,[R12+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2218F9 + 4), (enable) ? newOff : off); // dmc3.exe+2218F9 - 49 8B 8C C4 80180000 - MOV RCX,[R12+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x221B09 + 4), (enable) ? newOff : off); // dmc3.exe+221B09 - 49 8B 8C C4 80180000 - MOV RCX,[R12+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x221B71 + 4), (enable) ? newOff : off); // dmc3.exe+221B71 - 49 8B 8C C4 80180000 - MOV RCX,[R12+RAX*8+00001880]
		// Update Model Dante
		Write<uint32>((appBaseAddr + 0x2151C3 + 3), (enable) ? newOff : off); // dmc3.exe+2151C3 - 49 8D 96 80180000 - LEA RDX,[R14+00001880]
		Write<uint32>((appBaseAddr + 0x215373 + 3), (enable) ? newOff : off); // dmc3.exe+215373 - 49 8D 96 80180000 - LEA RDX,[R14+00001880]
		// Update Model Vergil
		Write<uint32>((appBaseAddr + 0x222653 + 3), (enable) ? newOff : off); // dmc3.exe+222653 - 48 8D 95 80180000 - LEA RDX,[RBP+00001880]
		Write<uint32>((appBaseAddr + 0x2227D3 + 3), (enable) ? newOff : off); // dmc3.exe+2227D3 - 48 8D 95 80180000 - LEA RDX,[RBP+00001880]
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF3ED + 3), (enable) ? newOff : off); // dmc3.exe+1EF3ED - 4D 8D B5 80180000 - LEA R14,[R13+00001880]
		// func_1F7BE0
		Write<uint32>((appBaseAddr + 0x1F7CEE + 4), (enable) ? newOff : off); // dmc3.exe+1F7CEE - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F81DE + 4), (enable) ? newOff : off); // dmc3.exe+1F81DE - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		// Other
		Write<uint32>((appBaseAddr + 0x8C3B9 + 4), (enable) ? newOff : off); // dmc3.exe+8C3B9 - 49 8B 94 C4 80180000 - MOV RDX,[R12+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x8CB96 + 4), (enable) ? newOff : off); // dmc3.exe+8CB96 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x8FA6B + 4), (enable) ? newOff : off); // dmc3.exe+8FA6B - 49 8B 94 C6 80180000 - MOV RDX,[R14+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x8FC47 + 4), (enable) ? newOff : off); // dmc3.exe+8FC47 - 49 8B 94 C6 80180000 - MOV RDX,[R14+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x9176B + 4), (enable) ? newOff : off); // dmc3.exe+9176B - 49 8B 94 C6 80180000 - MOV RDX,[R14+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x91D6F + 4), (enable) ? newOff : off); // dmc3.exe+91D6F - 49 8B 94 C6 80180000 - MOV RDX,[R14+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x91E9D + 4), (enable) ? newOff : off); // dmc3.exe+91E9D - 49 8B 94 C6 80180000 - MOV RDX,[R14+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x92289 + 4), (enable) ? newOff : off); // dmc3.exe+92289 - 49 8B 94 C6 80180000 - MOV RDX,[R14+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0xB9F5A + 3), (enable) ? newOff : off); // dmc3.exe+B9F5A - 48 8B 87 80180000 - MOV RAX,[RDI+00001880]
		Write<uint32>((appBaseAddr + 0xDA8A9 + 4), (enable) ? newOff : off); // dmc3.exe+DA8A9 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0xDA8C5 + 4), (enable) ? newOff : off); // dmc3.exe+DA8C5 - 48 8B 8C C7 80180000 - MOV RCX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0xDA8E7 + 4), (enable) ? newOff : off); // dmc3.exe+DA8E7 - 48 8B 8C C7 80180000 - MOV RCX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x150370 + 4), (enable) ? newOff : off); // dmc3.exe+150370 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x150395 + 4), (enable) ? newOff : off); // dmc3.exe+150395 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x16FC58 + 4), (enable) ? newOff : off); // dmc3.exe+16FC58 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x173072 + 4), (enable) ? newOff : off); // dmc3.exe+173072 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x173D52 + 4), (enable) ? newOff : off); // dmc3.exe+173D52 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x17C39B + 4), (enable) ? newOff : off); // dmc3.exe+17C39B - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x17C784 + 4), (enable) ? newOff : off); // dmc3.exe+17C784 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x17D694 + 4), (enable) ? newOff : off); // dmc3.exe+17D694 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x17DA05 + 4), (enable) ? newOff : off); // dmc3.exe+17DA05 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x188FB0 + 4), (enable) ? newOff : off); // dmc3.exe+188FB0 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1892AF + 4), (enable) ? newOff : off); // dmc3.exe+1892AF - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1A35EB + 4), (enable) ? newOff : off); // dmc3.exe+1A35EB - 48 8B 8C C7 80180000 - MOV RCX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1A36FF + 4), (enable) ? newOff : off); // dmc3.exe+1A36FF - 48 8B 8C C7 80180000 - MOV RCX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1B2266 + 4), (enable) ? newOff : off); // dmc3.exe+1B2266 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1E946F + 4), (enable) ? newOff : off); // dmc3.exe+1E946F - 48 8B 8C C7 80180000 - MOV RCX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1EAE89 + 4), (enable) ? newOff : off); // dmc3.exe+1EAE89 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1EAEE9 + 4), (enable) ? newOff : off); // dmc3.exe+1EAEE9 - 4C 8D 0C C5 80180000 - LEA R9,[RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1EAF20 + 4), (enable) ? newOff : off); // dmc3.exe+1EAF20 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1EAF79 + 4), (enable) ? newOff : off); // dmc3.exe+1EAF79 - 48 8D 0C C5 80180000 - LEA RCX,[RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1ED840 + 4), (enable) ? newOff : off); // dmc3.exe+1ED840 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1ED8E2 + 4), (enable) ? newOff : off); // dmc3.exe+1ED8E2 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1ED920 + 4), (enable) ? newOff : off); // dmc3.exe+1ED920 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1ED9AA + 4), (enable) ? newOff : off); // dmc3.exe+1ED9AA - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1EDACF + 4), (enable) ? newOff : off); // dmc3.exe+1EDACF - 48 8B 94 CF 80180000 - MOV RDX,[RDI+RCX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1EDB5B + 4), (enable) ? newOff : off); // dmc3.exe+1EDB5B - 48 8B 8C C7 80180000 - MOV RCX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1EDCB4 + 4), (enable) ? newOff : off); // dmc3.exe+1EDCB4 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1EE62E + 4), (enable) ? newOff : off); // dmc3.exe+1EE62E - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1EE690 + 4), (enable) ? newOff : off); // dmc3.exe+1EE690 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1EE6ED + 4), (enable) ? newOff : off); // dmc3.exe+1EE6ED - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F0764 + 4), (enable) ? newOff : off); // dmc3.exe+1F0764 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F08D5 + 4), (enable) ? newOff : off); // dmc3.exe+1F08D5 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F0D12 + 4), (enable) ? newOff : off); // dmc3.exe+1F0D12 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F0D94 + 4), (enable) ? newOff : off); // dmc3.exe+1F0D94 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F0DC6 + 4), (enable) ? newOff : off); // dmc3.exe+1F0DC6 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F0FE6 + 4), (enable) ? newOff : off); // dmc3.exe+1F0FE6 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
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
		Write<uint32>((appBaseAddr + 0x1F4118 + 4), (enable) ? newOff : off); // dmc3.exe+1F4118 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F4218 + 4), (enable) ? newOff : off); // dmc3.exe+1F4218 - 4C 8B 84 D3 80180000 - MOV R8,[RBX+RDX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F425D + 4), (enable) ? newOff : off); // dmc3.exe+1F425D - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F5721 + 4), (enable) ? newOff : off); // dmc3.exe+1F5721 - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F62DD + 4), (enable) ? newOff : off); // dmc3.exe+1F62DD - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F6306 + 4), (enable) ? newOff : off); // dmc3.exe+1F6306 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F6350 + 4), (enable) ? newOff : off); // dmc3.exe+1F6350 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F65BE + 4), (enable) ? newOff : off); // dmc3.exe+1F65BE - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F7846 + 4), (enable) ? newOff : off); // dmc3.exe+1F7846 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F9791 + 4), (enable) ? newOff : off); // dmc3.exe+1F9791 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1FA61A + 4), (enable) ? newOff : off); // dmc3.exe+1FA61A - 48 8B 94 CB 80180000 - MOV RDX,[RBX+RCX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1FAA81 + 4), (enable) ? newOff : off); // dmc3.exe+1FAA81 - 48 8B 84 C1 80180000 - MOV RAX,[RCX+RAX*8+00001880]
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
		Write<uint32>((appBaseAddr + 0x20ABFC + 4), (enable) ? newOff : off); // dmc3.exe+20ABFC - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
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
		Write<uint32>((appBaseAddr + 0x20FCAA + 4), (enable) ? newOff : off); // dmc3.exe+20FCAA - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
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
		Write<uint32>((appBaseAddr + 0x21544F + 4), (enable) ? newOff : off); // dmc3.exe+21544F - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2160EF + 4), (enable) ? newOff : off); // dmc3.exe+2160EF - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x216157 + 4), (enable) ? newOff : off); // dmc3.exe+216157 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x216289 + 4), (enable) ? newOff : off); // dmc3.exe+216289 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
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
		Write<uint32>((appBaseAddr + 0x21A3CA + 4), (enable) ? newOff : off); // dmc3.exe+21A3CA - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21B1EE + 4), (enable) ? newOff : off); // dmc3.exe+21B1EE - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
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
		Write<uint32>((appBaseAddr + 0x21F8FE + 4), (enable) ? newOff : off); // dmc3.exe+21F8FE - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21F9EF + 4), (enable) ? newOff : off); // dmc3.exe+21F9EF - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21FADF + 4), (enable) ? newOff : off); // dmc3.exe+21FADF - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21FC5B + 4), (enable) ? newOff : off); // dmc3.exe+21FC5B - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21FCD1 + 4), (enable) ? newOff : off); // dmc3.exe+21FCD1 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21FF27 + 4), (enable) ? newOff : off); // dmc3.exe+21FF27 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x220032 + 4), (enable) ? newOff : off); // dmc3.exe+220032 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x220059 + 4), (enable) ? newOff : off); // dmc3.exe+220059 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22019D + 4), (enable) ? newOff : off); // dmc3.exe+22019D - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2201D0 + 4), (enable) ? newOff : off); // dmc3.exe+2201D0 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2202A5 + 4), (enable) ? newOff : off); // dmc3.exe+2202A5 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x220595 + 4), (enable) ? newOff : off); // dmc3.exe+220595 - 4C 8B 84 C6 80180000 - MOV R8,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2205EA + 4), (enable) ? newOff : off); // dmc3.exe+2205EA - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22060A + 4), (enable) ? newOff : off); // dmc3.exe+22060A - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
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
		Write<uint32>((appBaseAddr + 0x222C61 + 4), (enable) ? newOff : off); // dmc3.exe+222C61 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22316A + 4), (enable) ? newOff : off); // dmc3.exe+22316A - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2231DB + 4), (enable) ? newOff : off); // dmc3.exe+2231DB - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x223223 + 4), (enable) ? newOff : off); // dmc3.exe+223223 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x223295 + 4), (enable) ? newOff : off); // dmc3.exe+223295 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2232D9 + 4), (enable) ? newOff : off); // dmc3.exe+2232D9 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x223335 + 4), (enable) ? newOff : off); // dmc3.exe+223335 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2233A8 + 4), (enable) ? newOff : off); // dmc3.exe+2233A8 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2233EF + 4), (enable) ? newOff : off); // dmc3.exe+2233EF - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22464B + 4), (enable) ? newOff : off); // dmc3.exe+22464B - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2246DD + 4), (enable) ? newOff : off); // dmc3.exe+2246DD - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x224D88 + 4), (enable) ? newOff : off); // dmc3.exe+224D88 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2251F2 + 4), (enable) ? newOff : off); // dmc3.exe+2251F2 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22531D + 4), (enable) ? newOff : off); // dmc3.exe+22531D - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22553B + 4), (enable) ? newOff : off); // dmc3.exe+22553B - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x225602 + 4), (enable) ? newOff : off); // dmc3.exe+225602 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x225846 + 4), (enable) ? newOff : off); // dmc3.exe+225846 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2258AE + 4), (enable) ? newOff : off); // dmc3.exe+2258AE - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x225A40 + 3), (enable) ? newOff : off); // dmc3.exe+225A40 - 4C 8B 83 80180000 - MOV R8,[RBX+00001880]
		Write<uint32>((appBaseAddr + 0x225A93 + 3), (enable) ? newOff : off); // dmc3.exe+225A93 - 48 8B 93 80180000 - MOV RDX,[RBX+00001880]
		Write<uint32>((appBaseAddr + 0x225BDD + 4), (enable) ? newOff : off); // dmc3.exe+225BDD - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x225C36 + 4), (enable) ? newOff : off); // dmc3.exe+225C36 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x225C56 + 4), (enable) ? newOff : off); // dmc3.exe+225C56 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x225C82 + 4), (enable) ? newOff : off); // dmc3.exe+225C82 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x225CDB + 4), (enable) ? newOff : off); // dmc3.exe+225CDB - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x225CFB + 4), (enable) ? newOff : off); // dmc3.exe+225CFB - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x225D47 + 4), (enable) ? newOff : off); // dmc3.exe+225D47 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x226E08 + 4), (enable) ? newOff : off); // dmc3.exe+226E08 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x226E75 + 4), (enable) ? newOff : off); // dmc3.exe+226E75 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22737C + 4), (enable) ? newOff : off); // dmc3.exe+22737C - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x27A7E8 + 4), (enable) ? newOff : off); // dmc3.exe+27A7E8 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Unknown
		// Write<uint32>((appBaseAddr + 0x8CBB3 + 4), (enable) ? newOff : off); // dmc3.exe+8CBB3 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x1F61AF + 4), (enable) ? newOff : off); // dmc3.exe+1F61AF - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x216129 + 4), (enable) ? newOff : off); // dmc3.exe+216129 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x2162C3 + 4), (enable) ? newOff : off); // dmc3.exe+2162C3 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x224ED8 + 4), (enable) ? newOff : off); // dmc3.exe+224ED8 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x225028 + 4), (enable) ? newOff : off); // dmc3.exe+225028 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x225B03 + 4), (enable) ? newOff : off); // dmc3.exe+225B03 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x225B5C + 4), (enable) ? newOff : off); // dmc3.exe+225B5C - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x225B83 + 4), (enable) ? newOff : off); // dmc3.exe+225B83 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x226EE2 + 4), (enable) ? newOff : off); // dmc3.exe+226EE2 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		// 0x310
		{
			constexpr auto off = (offsetof(ActorData, modelPhysicsMetadataPool[0][0]) / 8);
			constexpr auto newOff = (offsetof(ActorData, newModelPhysicsMetadataPool[0][0]) / 8);
			static_assert(off == 0x310);
			// Update Actor Dante
			Write<uint32>((appBaseAddr + 0x213E42 + 2), (enable) ? newOff : off); // dmc3.exe+213E42 - 48 05 10030000 - ADD RAX,00000310
			Write<uint32>((appBaseAddr + 0x214A06 + 2), (enable) ? newOff : off); // dmc3.exe+214A06 - 48 05 10030000 - ADD RAX,00000310
			// Update Actor Vergil
			Write<uint32>((appBaseAddr + 0x221077 + 2), (enable) ? newOff : off); // dmc3.exe+221077 - 48 05 10030000 - ADD RAX,00000310
			// Other
			Write<uint32>((appBaseAddr + 0x1DF131 + 3), (enable) ? newOff : off); // dmc3.exe+1DF131 - 48 81 C3 10030000 - ADD RBX,00000310
			// Unknown
			// Write<uint32>((appBaseAddr + 0x271850 + 3), (enable) ? newOff : off); // dmc3.exe+271850 - 48 81 C1 10030000 - ADD RCX,00000310
		}
		// 0x1820
		{
			constexpr auto off = (offsetof(ActorData, modelPhysicsMetadataPool[0][0]) - 0x60);
			constexpr auto newOff = (offsetof(ActorData, newModelPhysicsMetadataPool[0][0]) - 0x60);
			static_assert(off == 0x1820);
			// Other
			Write<uint32>((appBaseAddr + 0x1ED65A + 4), (enable) ? newOff : off); // dmc3.exe+1ED65A - 48 8B 94 C3 20180000 - MOV RDX,[RBX+RAX*8+00001820]
			// Unknown
			// Write<uint32>((appBaseAddr + 0xFA7F2 + 3), (enable) ? newOff : off); // dmc3.exe+FA7F2 - 48 8D 8E 20180000 - LEA RCX,[RSI+00001820]
			// Write<uint32>((appBaseAddr + 0xFA8B2 + 3), (enable) ? newOff : off); // dmc3.exe+FA8B2 - 48 8D 8E 20180000 - LEA RCX,[RSI+00001820]
		}
	}
	// 0x1888
	{
		constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][1]);
		constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][1]);
		static_assert(off == 0x1888);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF434 + 3), (enable) ? newOff : off); // dmc3.exe+1EF434 - 49 8B 85 88180000 - MOV RAX,[R13+00001888]
		// Other
		Write<uint32>((appBaseAddr + 0xBA9DE + 3), (enable) ? newOff : off); // dmc3.exe+BA9DE - 48 8B 96 88180000 - MOV RDX,[RSI+00001888]
		Write<uint32>((appBaseAddr + 0xBAAE5 + 3), (enable) ? newOff : off); // dmc3.exe+BAAE5 - 48 8B 96 88180000 - MOV RDX,[RSI+00001888]
		Write<uint32>((appBaseAddr + 0x212096 + 3), (enable) ? newOff : off); // dmc3.exe+212096 - 4C 8B 86 88180000 - MOV R8,[RSI+00001888]
		Write<uint32>((appBaseAddr + 0x2120E6 + 3), (enable) ? newOff : off); // dmc3.exe+2120E6 - 48 8B 96 88180000 - MOV RDX,[RSI+00001888]
		Write<uint32>((appBaseAddr + 0x2191DF + 3), (enable) ? newOff : off); // dmc3.exe+2191DF - 4C 8B 81 88180000 - MOV R8,[RCX+00001888]
		Write<uint32>((appBaseAddr + 0x21922C + 3), (enable) ? newOff : off); // dmc3.exe+21922C - 48 8B 97 88180000 - MOV RDX,[RDI+00001888]
		Write<uint32>((appBaseAddr + 0x2204D4 + 3), (enable) ? newOff : off); // dmc3.exe+2204D4 - 4C 8B 81 88180000 - MOV R8,[RCX+00001888]
		Write<uint32>((appBaseAddr + 0x220528 + 3), (enable) ? newOff : off); // dmc3.exe+220528 - 48 8B 96 88180000 - MOV RDX,[RSI+00001888]
	}
	// 0x1890
	{
		constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][2]);
		constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][2]);
		static_assert(off == 0x1890);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF30A + 3), (enable) ? newOff : off); // dmc3.exe+1EF30A - 49 8B 85 90180000 - MOV RAX,[R13+00001890]
	}
	// 0x1898
	{
		constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][3]);
		constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][3]);
		static_assert(off == 0x1898);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF1DE + 3), (enable) ? newOff : off); // dmc3.exe+1EF1DE - 49 8B 85 98180000 - MOV RAX,[R13+00001898]
		// Other
		Write<uint32>((appBaseAddr + 0xB9DF1 + 3), (enable) ? newOff : off); // dmc3.exe+B9DF1 - 48 8B 87 98180000 - MOV RAX,[RDI+00001898]
		Write<uint32>((appBaseAddr + 0xBA06E + 3), (enable) ? newOff : off); // dmc3.exe+BA06E - 48 8B 8F 98180000 - MOV RCX,[RDI+00001898]
		Write<uint32>((appBaseAddr + 0xBA9F4 + 3), (enable) ? newOff : off); // dmc3.exe+BA9F4 - 48 8B 96 98180000 - MOV RDX,[RSI+00001898]
		Write<uint32>((appBaseAddr + 0xBAAFB + 3), (enable) ? newOff : off); // dmc3.exe+BAAFB - 48 8B 96 98180000 - MOV RDX,[RSI+00001898]
		Write<uint32>((appBaseAddr + 0xC75A7 + 3), (enable) ? newOff : off); // dmc3.exe+C75A7 - 48 8B 96 98180000 - MOV RDX,[RSI+00001898]
		Write<uint32>((appBaseAddr + 0xC7A1D + 3), (enable) ? newOff : off); // dmc3.exe+C7A1D - 48 8B 97 98180000 - MOV RDX,[RDI+00001898]
		Write<uint32>((appBaseAddr + 0xCB18E + 3), (enable) ? newOff : off); // dmc3.exe+CB18E - 48 8B 8E 98180000 - MOV RCX,[RSI+00001898]
		Write<uint32>((appBaseAddr + 0x2120C4 + 3), (enable) ? newOff : off); // dmc3.exe+2120C4 - 48 8B 96 98180000 - MOV RDX,[RSI+00001898]
		Write<uint32>((appBaseAddr + 0x218EFD + 3), (enable) ? newOff : off); // dmc3.exe+218EFD - 48 8B 97 98180000 - MOV RDX,[RDI+00001898]
		Write<uint32>((appBaseAddr + 0x218F67 + 3), (enable) ? newOff : off); // dmc3.exe+218F67 - 48 8B 97 98180000 - MOV RDX,[RDI+00001898]
		Write<uint32>((appBaseAddr + 0x220506 + 3), (enable) ? newOff : off); // dmc3.exe+220506 - 48 8B 96 98180000 - MOV RDX,[RSI+00001898]
		Write<uint32>((appBaseAddr + 0x223068 + 3), (enable) ? newOff : off); // dmc3.exe+223068 - 4C 8B 81 98180000 - MOV R8,[RCX+00001898]
		Write<uint32>((appBaseAddr + 0x2230AA + 3), (enable) ? newOff : off); // dmc3.exe+2230AA - 4C 8B 83 98180000 - MOV R8,[RBX+00001898]
		Write<uint32>((appBaseAddr + 0x2230E0 + 3), (enable) ? newOff : off); // dmc3.exe+2230E0 - 48 8B 93 98180000 - MOV RDX,[RBX+00001898]
		Write<uint32>((appBaseAddr + 0x2243FB + 3), (enable) ? newOff : off); // dmc3.exe+2243FB - 48 8B 93 98180000 - MOV RDX,[RBX+00001898]
		Write<uint32>((appBaseAddr + 0x22445B + 3), (enable) ? newOff : off); // dmc3.exe+22445B - 48 8B 93 98180000 - MOV RDX,[RBX+00001898]
		Write<uint32>((appBaseAddr + 0x225A71 + 3), (enable) ? newOff : off); // dmc3.exe+225A71 - 48 8B 93 98180000 - MOV RDX,[RBX+00001898]
		Write<uint32>((appBaseAddr + 0x226D86 + 3), (enable) ? newOff : off); // dmc3.exe+226D86 - 4C 8B 81 98180000 - MOV R8,[RCX+00001898]
		Write<uint32>((appBaseAddr + 0x2272D1 + 3), (enable) ? newOff : off); // dmc3.exe+2272D1 - 48 8B 93 98180000 - MOV RDX,[RBX+00001898]
		// Unknown
		// Write<uint32>((appBaseAddr + 0xC823B + 3), (enable) ? newOff : off); // dmc3.exe+C823B - 48 8B 85 98180000 - MOV RAX,[RBP+00001898]
	}
	// 0x18A8
	{
		constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][5]);
		constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][5]);
		static_assert(off == 0x18A8);
		// Other
		Write<uint32>((appBaseAddr + 0x986CE + 3), (enable) ? newOff : off); // dmc3.exe+986CE - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0x9DB24 + 3), (enable) ? newOff : off); // dmc3.exe+9DB24 - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0xA2A55 + 3), (enable) ? newOff : off); // dmc3.exe+A2A55 - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0xA78C7 + 3), (enable) ? newOff : off); // dmc3.exe+A78C7 - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0xA8F8D + 3), (enable) ? newOff : off); // dmc3.exe+A8F8D - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0xAB6DA + 3), (enable) ? newOff : off); // dmc3.exe+AB6DA - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0xB04AF + 3), (enable) ? newOff : off); // dmc3.exe+B04AF - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0xB2B09 + 3), (enable) ? newOff : off); // dmc3.exe+B2B09 - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0xB685E + 3), (enable) ? newOff : off); // dmc3.exe+B685E - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0x1FAF4F + 3), (enable) ? newOff : off); // dmc3.exe+1FAF4F - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0x1FAF93 + 3), (enable) ? newOff : off); // dmc3.exe+1FAF93 - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0x1FAFA4 + 3), (enable) ? newOff : off); // dmc3.exe+1FAFA4 - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0x1FC8F3 + 3), (enable) ? newOff : off); // dmc3.exe+1FC8F3 - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0x21920A + 3), (enable) ? newOff : off); // dmc3.exe+21920A - 48 8B 97 A8180000 - MOV RDX,[RDI+000018A8]
		Write<uint32>((appBaseAddr + 0x219ACB + 3), (enable) ? newOff : off); // dmc3.exe+219ACB - 48 8B 97 A8180000 - MOV RDX,[RDI+000018A8]
	}
	// 0x18F8
	{
		constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][15]);
		constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][15]);
		static_assert(off == 0x18F8);
		// Other
		Write<uint32>((appBaseAddr + 0xBAA0B + 3), (enable) ? newOff : off); // dmc3.exe+BAA0B - 48 8B 96 F8180000 - MOV RDX,[RSI+000018F8]
		Write<uint32>((appBaseAddr + 0xBAB12 + 3), (enable) ? newOff : off); // dmc3.exe+BAB12 - 48 8B 96 F8180000 - MOV RDX,[RSI+000018F8]
		// Unknown
		// Write<uint32>((appBaseAddr + 0x25AD52 + 3), (enable) ? newOff : off); // dmc3.exe+25AD52 - 48 8D B3 F8180000 - LEA RSI,[RBX+000018F8]
		// Write<uint32>((appBaseAddr + 0x25C5EC + 3), (enable) ? newOff : off); // dmc3.exe+25C5EC - 48 8D B7 F8180000 - LEA RSI,[RDI+000018F8]
		// Write<uint32>((appBaseAddr + 0x25D0C2 + 4), (enable) ? newOff : off); // dmc3.exe+25D0C2 - 48 89 84 CF F8180000 - MOV [RDI+RCX*8+000018F8],RAX
		// Write<uint32>((appBaseAddr + 0x25D0D1 + 4), (enable) ? newOff : off); // dmc3.exe+25D0D1 - 48 8B 8C C7 F8180000 - MOV RCX,[RDI+RAX*8+000018F8]
		// Write<uint32>((appBaseAddr + 0x25D0FA + 4), (enable) ? newOff : off); // dmc3.exe+25D0FA - 48 8B 8C C7 F8180000 - MOV RCX,[RDI+RAX*8+000018F8]
		// Write<uint32>((appBaseAddr + 0x25D2E2 + 3), (enable) ? newOff : off); // dmc3.exe+25D2E2 - 48 8D 8F F8180000 - LEA RCX,[RDI+000018F8]
		// Write<uint32>((appBaseAddr + 0x25D55C + 3), (enable) ? newOff : off); // dmc3.exe+25D55C - 48 8D BB F8180000 - LEA RDI,[RBX+000018F8]
		// Write<uint32>((appBaseAddr + 0x25D5A3 + 3), (enable) ? newOff : off); // dmc3.exe+25D5A3 - 48 8D BB F8180000 - LEA RDI,[RBX+000018F8]
		// Write<uint32>((appBaseAddr + 0x2920B4 + 2), (enable) ? newOff : off); // dmc3.exe+2920B4 - 83 BB F8180000 02 - CMP DWORD PTR [RBX+000018F8],02
		// Write<uint32>((appBaseAddr + 0x292858 + 2), (enable) ? newOff : off); // dmc3.exe+292858 - C7 83 F8180000 04000000 - MOV [RBX+000018F8],00000004
		// Write<uint32>((appBaseAddr + 0x292864 + 2), (enable) ? newOff : off); // dmc3.exe+292864 - C7 83 F8180000 03000000 - MOV [RBX+000018F8],00000003
		// Write<uint32>((appBaseAddr + 0x292D91 + 2), (enable) ? newOff : off); // dmc3.exe+292D91 - C7 83 F8180000 04000000 - MOV [RBX+000018F8],00000004
		// Write<uint32>((appBaseAddr + 0x292DB8 + 2), (enable) ? newOff : off); // dmc3.exe+292DB8 - C7 83 F8180000 03000000 - MOV [RBX+000018F8],00000003
		// Write<uint32>((appBaseAddr + 0x292E00 + 2), (enable) ? newOff : off); // dmc3.exe+292E00 - C7 83 F8180000 02000000 - MOV [RBX+000018F8],00000002
		// Write<uint32>((appBaseAddr + 0x292F97 + 2), (enable) ? newOff : off); // dmc3.exe+292F97 - C7 83 F8180000 04000000 - MOV [RBX+000018F8],00000004
		// Write<uint32>((appBaseAddr + 0x292FA3 + 2), (enable) ? newOff : off); // dmc3.exe+292FA3 - C7 83 F8180000 03000000 - MOV [RBX+000018F8],00000003
	}
	// 0x1900
	{
		constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][16]);
		constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][16]);
		static_assert(off == 0x1900);
		// Other
		Write<uint32>((appBaseAddr + 0xBAA25 + 3), (enable) ? newOff : off); // dmc3.exe+BAA25 - 48 8B 96 00190000 - MOV RDX,[RSI+00001900]
		Write<uint32>((appBaseAddr + 0xBAB2C + 3), (enable) ? newOff : off); // dmc3.exe+BAB2C - 48 8B 96 00190000 - MOV RDX,[RSI+00001900]
		// Unknown
		// Write<uint32>((appBaseAddr + 0x292170 + 2), (enable) ? newOff : off); // dmc3.exe+292170 - C7 83 00190000 05000000 - MOV [RBX+00001900],00000005
		// Write<uint32>((appBaseAddr + 0x292189 + 2), (enable) ? newOff : off); // dmc3.exe+292189 - C7 83 00190000 06000000 - MOV [RBX+00001900],00000006
	}
	// 0x1918
	{
		constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][19]);
		constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][19]);
		static_assert(off == 0x1918);
		// Other
		Write<uint32>((appBaseAddr + 0xBAA3F + 3), (enable) ? newOff : off); // dmc3.exe+BAA3F - 48 8B 96 18190000 - MOV RDX,[RSI+00001918]
		Write<uint32>((appBaseAddr + 0xBAB46 + 3), (enable) ? newOff : off); // dmc3.exe+BAB46 - 48 8B 96 18190000 - MOV RDX,[RSI+00001918]
	}
	// 0x1920
	{
		constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[0][20]);
		constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[0][20]);
		static_assert(off == 0x1920);
		// Other
		Write<uint32>((appBaseAddr + 0xBAA59 + 3), (enable) ? newOff : off); // dmc3.exe+BAA59 - 48 8B 96 20190000 - MOV RDX,[RSI+00001920]
		Write<uint32>((appBaseAddr + 0xBAB60 + 3), (enable) ? newOff : off); // dmc3.exe+BAB60 - 48 8B 96 20190000 - MOV RDX,[RSI+00001920]
	}
	// 0x1940
	{
		constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[1][0]);
		constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[1][0]);
		static_assert(off == 0x1940);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF2BB + 3), (enable) ? newOff : off); // dmc3.exe+1EF2BB - 4D 8D BD 40190000 - LEA R15,[R13+00001940]
	}
	// 0x1A00
	{
		constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[2][0]);
		constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[2][0]);
		static_assert(off == 0x1A00);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF18F + 3), (enable) ? newOff : off); // dmc3.exe+1EF18F - 4D 8D BD 001A0000 - LEA R15,[R13+00001A00]
	}
	// 0x1AC0
	{
		constexpr auto off = offsetof(ActorData, modelPhysicsMetadataPool[3][0]);
		constexpr auto newOff = offsetof(ActorData, newModelPhysicsMetadataPool[6][0]); // [3] -> [6]
		static_assert(off == 0x1AC0);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF0A9 + 3), (enable) ? newOff : off); // dmc3.exe+1EF0A9 - 49 8D AD C01A0000 - LEA RBP,[R13+00001AC0]
	}
	// 0x1B88
	{
		constexpr auto off = offsetof(ActorData, modelAllocationData[0]);
		constexpr auto newOff = offsetof(ActorData, newModelAllocationData[0]);
		static_assert(off == 0x1B88);
		// func_1DD140
		Write<uint32>((appBaseAddr + 0x1DD1AA + 3), (enable) ? newOff : off); // dmc3.exe+1DD1AA - 49 8D 8E 881B0000 - LEA RCX,[R14+00001B88]
		// func_1DD210
		Write<uint32>((appBaseAddr + 0x1DD27A + 3), (enable) ? newOff : off); // dmc3.exe+1DD27A - 49 8D 8E 881B0000 - LEA RCX,[R14+00001B88]
		// func_1DD2E0
		Write<uint32>((appBaseAddr + 0x1DD34A + 3), (enable) ? newOff : off); // dmc3.exe+1DD34A - 49 8D 8E 881B0000 - LEA RCX,[R14+00001B88]
		// func_1DD3B0
		Write<uint32>((appBaseAddr + 0x1DD41A + 3), (enable) ? newOff : off); // dmc3.exe+1DD41A - 49 8D 8E 881B0000 - LEA RCX,[R14+00001B88]
		// func_1DDAF0
		Write<uint32>((appBaseAddr + 0x1DDB76 + 3), (enable) ? newOff : off); // dmc3.exe+1DDB76 - 48 8D 8E 881B0000 - LEA RCX,[RSI+00001B88]
		// func_1DE280
		Write<uint32>((appBaseAddr + 0x1DE3FB + 3), (enable) ? newOff : off); // dmc3.exe+1DE3FB - 48 8D 8F 881B0000 - LEA RCX,[RDI+00001B88]
		// func_1DE750
		Write<uint32>((appBaseAddr + 0x1DE7B3 + 3), (enable) ? newOff : off); // dmc3.exe+1DE7B3 - 48 8D 8F 881B0000 - LEA RCX,[RDI+00001B88]
		// Other
		Write<uint32>((appBaseAddr + 0x1DFAEE + 3), (enable) ? newOff : off); // dmc3.exe+1DFAEE - 48 81 C1 881B0000 - ADD RCX,00001B88
	}
	// 0x1B98
	{
		constexpr auto off = (offsetof(ActorData, modelAllocationData[0]) + 0x10);
		constexpr auto newOff = (offsetof(ActorData, newModelAllocationData[0]) + 0x10);
		static_assert(off == 0x1B98);
		// func_1DD140
		Write<uint32>((appBaseAddr + 0x1DD1BB + 3), (enable) ? newOff : off); // dmc3.exe+1DD1BB - 49 8B 8E 981B0000 - MOV RCX,[R14+00001B98]
		// func_1DD210
		Write<uint32>((appBaseAddr + 0x1DD28B + 3), (enable) ? newOff : off); // dmc3.exe+1DD28B - 49 8B 8E 981B0000 - MOV RCX,[R14+00001B98]
		// func_1DD2E0
		Write<uint32>((appBaseAddr + 0x1DD35B + 3), (enable) ? newOff : off); // dmc3.exe+1DD35B - 49 8B 8E 981B0000 - MOV RCX,[R14+00001B98]
		// func_1DD3B0
		Write<uint32>((appBaseAddr + 0x1DD42B + 3), (enable) ? newOff : off); // dmc3.exe+1DD42B - 49 8B 8E 981B0000 - MOV RCX,[R14+00001B98]
	}
	// 0x3B00
	{
		constexpr auto off = offsetof(ActorData, recoveryData[0]);
		constexpr auto newOff = offsetof(ActorData, newRecoveryData[0]);
		static_assert(off == 0x3B00);
		// func_1DDAF0
		Write<uint32>((appBaseAddr + 0x1DDC09 + 3), (enable) ? newOff : off); // dmc3.exe+1DDC09 - 48 8D 8E 003B0000 - LEA RCX,[RSI+00003B00]
		// func_1DE280
		Write<uint32>((appBaseAddr + 0x1DE3AD + 3), (enable) ? newOff : off); // dmc3.exe+1DE3AD - 48 8D 8F 003B0000 - LEA RCX,[RDI+00003B00]
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF408 + 3), (enable) ? newOff : off); // dmc3.exe+1EF408 - 49 8D 8D 003B0000 - LEA RCX,[R13+00003B00]
	}
	// 0x3B70
	{
		constexpr auto off = offsetof(ActorData, recoveryData[1]);
		constexpr auto newOff = offsetof(ActorData, newRecoveryData[1]);
		static_assert(off == 0x3B70);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF2E1 + 3), (enable) ? newOff : off); // dmc3.exe+1EF2E1 - 49 8D 8D 703B0000 - LEA RCX,[R13+00003B70]
	}
	// 0x3BE0
	{
		constexpr auto off = offsetof(ActorData, recoveryData[2]);
		constexpr auto newOff = offsetof(ActorData, newRecoveryData[2]);
		static_assert(off == 0x3BE0);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF1B5 + 3), (enable) ? newOff : off); // dmc3.exe+1EF1B5 - 49 8D 8D E03B0000 - LEA RCX,[R13+00003BE0]
	}
	// 0x3E74
	{
		constexpr auto off = offsetof(ActorData, devilModels[0]);
		constexpr auto newOff = offsetof(ActorData, newDevilModels[0]);
		static_assert(off == 0x3E74);
		// Update Actor Dante
		Write<uint32>((appBaseAddr + 0x213181 + 3), (enable) ? newOff : off); // dmc3.exe+213181 - C7 84 BE 743E0000 05000000 - MOV [RSI+RDI*4+00003E74],00000005
		Write<uint32>((appBaseAddr + 0x213580 + 3), (enable) ? newOff : off); // dmc3.exe+213580 - C7 84 BE 743E0000 04000000 - MOV [RSI+RDI*4+00003E74],00000004
		Write<uint32>((appBaseAddr + 0x213989 + 3), (enable) ? newOff : off); // dmc3.exe+213989 - C7 84 BE 743E0000 03000000 - MOV [RSI+RDI*4+00003E74],00000003
		Write<uint32>((appBaseAddr + 0x213FE0 + 4), (enable) ? newOff : off); // dmc3.exe+213FE0 - 42 C7 84 AE 743E0000 02000000 - MOV [RSI+R13*4+00003E74],00000002
		Write<uint32>((appBaseAddr + 0x21410F + 3), (enable) ? newOff : off); // dmc3.exe+21410F - C7 84 BE 743E0000 01000000 - MOV [RSI+RDI*4+00003E74],00000001
		Write<uint32>((appBaseAddr + 0x21450A + 3), (enable) ? newOff : off); // dmc3.exe+21450A - C7 84 BE 743E0000 00000000 - MOV [RSI+RDI*4+00003E74],00000000
		// Update Actor Bob
		Write<uint32>((appBaseAddr + 0x2263C0 + 4), (enable) ? newOff : off); // dmc3.exe+2263C0 - 41 C7 84 9E 743E0000 00000000 - MOV [R14+RBX*4+00003E74],00000000
		// Write<uint32>((appBaseAddr + 0x22692E + 4), (enable) ? newOff : off); // dmc3.exe+22692E - 41 C7 84 9E 743E0000 04000000 - MOV [R14+RBX*4+00003E74],00000004
		// Update Actor Vergil
		Write<uint32>((appBaseAddr + 0x220D9E + 4), (enable) ? newOff : off); // dmc3.exe+220D9E - 41 C7 84 BC 743E0000 06000000 - MOV [R12+RDI*4+00003E74],00000006
		Write<uint32>((appBaseAddr + 0x221198 + 4), (enable) ? newOff : off); // dmc3.exe+221198 - 41 C7 84 BC 743E0000 04000000 - MOV [R12+RDI*4+00003E74],00000004
		Write<uint32>((appBaseAddr + 0x2215A0 + 4), (enable) ? newOff : off); // dmc3.exe+2215A0 - 45 89 B4 BC 743E0000 - MOV [R12+RDI*4+00003E74],R14D
		// func_1F7BE0
		Write<uint32>((appBaseAddr + 0x1F7E5A + 2), (enable) ? newOff : off); // dmc3.exe+1F7E5A - C7 83 743E0000 FFFFFFFF - MOV [RBX+00003E74],FFFFFFFF
		// Other
		Write<uint32>((appBaseAddr + 0x90B67 + 4), (enable) ? newOff : off); // dmc3.exe+90B67 - 41 8B 8C 86 743E0000 - MOV ECX,[R14+RAX*4+00003E74]
		Write<uint32>((appBaseAddr + 0x1FAB17 + 3), (enable) ? newOff : off); // dmc3.exe+1FAB17 - 8B 84 81 743E0000 - MOV EAX,[RCX+RAX*4+00003E74]
		Write<uint32>((appBaseAddr + 0x1FAB34 + 4), (enable) ? newOff : off); // dmc3.exe+1FAB34 - 48 63 94 81 743E0000 - MOVSXD RDX,DWORD PTR [RCX+RAX*4+00003E74]
		Write<uint32>((appBaseAddr + 0x212110 + 3), (enable) ? newOff : off); // dmc3.exe+212110 - 8B 94 81 743E0000 - MOV EDX,[RCX+RAX*4+00003E74]
		Write<uint32>((appBaseAddr + 0x2189B0 + 3), (enable) ? newOff : off); // dmc3.exe+2189B0 - 8B 94 8F 743E0000 - MOV EDX,[RDI+RCX*4+00003E74]
		Write<uint32>((appBaseAddr + 0x220552 + 3), (enable) ? newOff : off); // dmc3.exe+220552 - 8B 8C 81 743E0000 - MOV ECX,[RCX+RAX*4+00003E74]
		Write<uint32>((appBaseAddr + 0x2244A8 + 3), (enable) ? newOff : off); // dmc3.exe+2244A8 - 8B 8C 83 743E0000 - MOV ECX,[RBX+RAX*4+00003E74]
		Write<uint32>((appBaseAddr + 0x2296B3 + 3), (enable) ? newOff : off); // dmc3.exe+2296B3 - 83 BC 81 743E0000 04 - CMP DWORD PTR [RCX+RAX*4+00003E74],04
		// Unknown
		// Write<uint32>((appBaseAddr + 0x4B950 + 2), (enable) ? newOff : off); // dmc3.exe+4B950 - C7 83 743E0000 01000000 - MOV [RBX+00003E74],00000001
	}
	// 0x6498
	{
		constexpr auto off = offsetof(ActorData, weapons[0]);
		constexpr auto newOff = offsetof(ActorData, newWeapons[0]);
		static_assert(off == 0x6498);
		// Init Actor Dante
		Write<uint32>((appBaseAddr + 0x217BF4 + 2), (enable) ? newOff : off); // dmc3.exe+217BF4 - 88 81 98640000 - MOV [RCX+00006498],AL
		// Init Actor Bob
		Write<uint32>((appBaseAddr + 0x226F53 + 2), (enable) ? newOff : off); // dmc3.exe+226F53 - C7 81 98640000 0EFFFFFF - MOV [RCX+00006498],FFFFFF0E
		// Init Actor Lady
		Write<uint32>((appBaseAddr + 0x2196AA + 2), (enable) ? newOff : off); // dmc3.exe+2196AA - C7 81 98640000 FFFF090A - MOV [RCX+00006498],0A09FFFF
		// Init Actor Vergil
		Write<uint32>((appBaseAddr + 0x223D11 + 2), (enable) ? newOff : off); // dmc3.exe+223D11 - C7 81 98640000 0B0C0DFF - MOV [RCX+00006498],FF0D0C0B
		// Update Actor Dante
		Write<uint32>((appBaseAddr + 0x212D9A + 3), (enable) ? newOff : off); // dmc3.exe+212D9A - 4C 8D A6 98640000 - LEA R12,[RSI+00006498]
		Write<uint32>((appBaseAddr + 0x213423 + 3), (enable) ? newOff : off); // dmc3.exe+213423 - 4C 8D A6 98640000 - LEA R12,[RSI+00006498]
		Write<uint32>((appBaseAddr + 0x2143AC + 3), (enable) ? newOff : off); // dmc3.exe+2143AC - 4C 8D A6 98640000 - LEA R12,[RSI+00006498]
		Write<uint32>((appBaseAddr + 0x214A5F + 3), (enable) ? newOff : off); // dmc3.exe+214A5F - 4C 8D A6 98640000 - LEA R12,[RSI+00006498]
		Write<uint32>((appBaseAddr + 0x214BD2 + 3), (enable) ? newOff : off); // dmc3.exe+214BD2 - 80 BC 30 98640000 04 - CMP BYTE PTR [RAX+RSI+00006498],04
		// Update Actor Bob
		Write<uint32>((appBaseAddr + 0x22629D + 3), (enable) ? newOff : off); // dmc3.exe+22629D - 49 8D 86 98640000 - LEA RAX,[R14+00006498]
		Write<uint32>((appBaseAddr + 0x22639B + 5), (enable) ? newOff : off); // dmc3.exe+22639B - 42 0FB6 84 31 98640000 - MOVZX EAX,BYTE PTR [RCX+R14+00006498]
		// Update Actor Lady
		Write<uint32>((appBaseAddr + 0x21959D + 3), (enable) ? newOff : off); // dmc3.exe+21959D - 48 8D 9D 98640000 - LEA RBX,[RBP+00006498]
		// Register Weapons
		Write<uint32>((appBaseAddr + 0x1DED41 + 3), (enable) ? newOff : off); // dmc3.exe+1DED41 - 48 8D A9 98640000 - LEA RBP,[RCX+00006498]
		// Weapon Switch Controller Dante
		Write<uint32>((appBaseAddr + 0x1EA987 + 5), (enable) ? newOff : off); // dmc3.exe+1EA987 - 44 0FB6 84 3B 98640000 - MOVZX R8D,BYTE PTR [RBX+RDI+00006498]
		Write<uint32>((appBaseAddr + 0x1EA99D + 3), (enable) ? newOff : off); // dmc3.exe+1EA99D - 80 BC 38 98640000 FF - CMP BYTE PTR [RAX+RDI+00006498],-01
		Write<uint32>((appBaseAddr + 0x1EA9AF + 4), (enable) ? newOff : off); // dmc3.exe+1EA9AF - 44 3A 84 38 98640000 - CMP R8L,[RAX+RDI+00006498]
		Write<uint32>((appBaseAddr + 0x1EAA74 + 4), (enable) ? newOff : off); // dmc3.exe+1EAA74 - 0FB6 8C 3B 98640000 - MOVZX ECX,BYTE PTR [RBX+RDI+00006498]
		Write<uint32>((appBaseAddr + 0x1EAA8A + 3), (enable) ? newOff : off); // dmc3.exe+1EAA8A - 80 BC 3B 98640000 FF - CMP BYTE PTR [RBX+RDI+00006498],-01
		Write<uint32>((appBaseAddr + 0x1EAA9F + 3), (enable) ? newOff : off); // dmc3.exe+1EAA9F - 3A 8C 3B 98640000 - CMP CL,[RBX+RDI+00006498]
		// func_1F7BE0
		Write<uint32>((appBaseAddr + 0x1F80B1 + 4), (enable) ? newOff : off); // dmc3.exe+1F80B1 - 0FB6 84 19 98640000 - MOVZX EAX,BYTE PTR [RCX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1F80BF + 4), (enable) ? newOff : off); // dmc3.exe+1F80BF - 0FB6 84 19 98640000 - MOVZX EAX,BYTE PTR [RCX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1F80D4 + 4), (enable) ? newOff : off); // dmc3.exe+1F80D4 - 0FB6 8C 18 98640000 - MOVZX ECX,BYTE PTR [RAX+RBX+00006498]
		// func_2198D0
		Write<uint32>((appBaseAddr + 0x2198D0 + 3), (enable) ? newOff : off); // dmc3.exe+2198D0 - 0FB6 81 98640000 - MOVZX EAX,BYTE PTR [RCX+00006498]
		// func_2241F0
		Write<uint32>((appBaseAddr + 0x2241F0 + 3), (enable) ? newOff : off); // dmc3.exe+2241F0 - 0FB6 81 98640000 - MOVZX EAX,BYTE PTR [RCX+00006498]
		// Other
		Write<uint32>((appBaseAddr + 0x1D91E0 + 3), (enable) ? newOff : off); // dmc3.exe+1D91E0 - 80 BC 11 98640000 0D - CMP BYTE PTR [RCX+RDX+00006498],0D
		Write<uint32>((appBaseAddr + 0x1E02A2 + 4), (enable) ? newOff : off); // dmc3.exe+1E02A2 - 40 38 B4 18 98640000 - CMP [RAX+RBX+00006498],SIL
		Write<uint32>((appBaseAddr + 0x1E088D + 3), (enable) ? newOff : off); // dmc3.exe+1E088D - 80 BC 18 98640000 05 - CMP BYTE PTR [RAX+RBX+00006498],05
		Write<uint32>((appBaseAddr + 0x1E090C + 4), (enable) ? newOff : off); // dmc3.exe+1E090C - 0FB6 8C 18 98640000 - MOVZX ECX,BYTE PTR [RAX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1E0923 + 4), (enable) ? newOff : off); // dmc3.exe+1E0923 - 0FB6 8C 18 98640000 - MOVZX ECX,BYTE PTR [RAX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1E28E6 + 4), (enable) ? newOff : off); // dmc3.exe+1E28E6 - 0FB6 B4 08 98640000 - MOVZX ESI,BYTE PTR [RAX+RCX+00006498]
		Write<uint32>((appBaseAddr + 0x1E64DB + 4), (enable) ? newOff : off); // dmc3.exe+1E64DB - 0FB6 8C 18 98640000 - MOVZX ECX,BYTE PTR [RAX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1E64FB + 4), (enable) ? newOff : off); // dmc3.exe+1E64FB - 0FB6 8C 18 98640000 - MOVZX ECX,BYTE PTR [RAX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1E657D + 3), (enable) ? newOff : off); // dmc3.exe+1E657D - 80 BC 18 98640000 07 - CMP BYTE PTR [RAX+RBX+00006498],07
		Write<uint32>((appBaseAddr + 0x1E6BB8 + 4), (enable) ? newOff : off); // dmc3.exe+1E6BB8 - 0FB6 8C 1A 98640000 - MOVZX ECX,BYTE PTR [RDX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1E6C03 + 4), (enable) ? newOff : off); // dmc3.exe+1E6C03 - 0FB6 8C 18 98640000 - MOVZX ECX,BYTE PTR [RAX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1E6C35 + 4), (enable) ? newOff : off); // dmc3.exe+1E6C35 - 0FB6 84 1A 98640000 - MOVZX EAX,BYTE PTR [RDX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1E6D9B + 4), (enable) ? newOff : off); // dmc3.exe+1E6D9B - 0FB6 8C 18 98640000 - MOVZX ECX,BYTE PTR [RAX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1E70DD + 4), (enable) ? newOff : off); // dmc3.exe+1E70DD - 40 3A BC 18 98640000 - CMP DIL,[RAX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1E70EE + 4), (enable) ? newOff : off); // dmc3.exe+1E70EE - 40 3A BC 18 98640000 - CMP DIL,[RAX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1E711C + 4), (enable) ? newOff : off); // dmc3.exe+1E711C - 40 3A BC 18 98640000 - CMP DIL,[RAX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1E714A + 4), (enable) ? newOff : off); // dmc3.exe+1E714A - 40 3A BC 18 98640000 - CMP DIL,[RAX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1E7174 + 4), (enable) ? newOff : off); // dmc3.exe+1E7174 - 40 3A BC 18 98640000 - CMP DIL,[RAX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1E7185 + 4), (enable) ? newOff : off); // dmc3.exe+1E7185 - 40 3A BC 18 98640000 - CMP DIL,[RAX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1E7E93 + 3), (enable) ? newOff : off); // dmc3.exe+1E7E93 - 80 BC 18 98640000 03 - CMP BYTE PTR [RAX+RBX+00006498],03
		Write<uint32>((appBaseAddr + 0x1E927F + 5), (enable) ? newOff : off); // dmc3.exe+1E927F - 42 0FB6 8C 00 98640000 - MOVZX ECX,BYTE PTR [RAX+R8+00006498]
		Write<uint32>((appBaseAddr + 0x1E9B04 + 4), (enable) ? newOff : off); // dmc3.exe+1E9B04 - 0FB6 8C 18 98640000 - MOVZX ECX,BYTE PTR [RAX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1EADEA + 4), (enable) ? newOff : off); // dmc3.exe+1EADEA - 0FBE 8C 08 98640000 - MOVSX ECX,BYTE PTR [RAX+RCX+00006498]
		Write<uint32>((appBaseAddr + 0x1EAE10 + 3), (enable) ? newOff : off); // dmc3.exe+1EAE10 - 80 BC 11 98640000 05 - CMP BYTE PTR [RCX+RDX+00006498],05
		Write<uint32>((appBaseAddr + 0x1EB1E5 + 3), (enable) ? newOff : off); // dmc3.exe+1EB1E5 - 80 BC 18 98640000 07 - CMP BYTE PTR [RAX+RBX+00006498],07
		Write<uint32>((appBaseAddr + 0x1F59B1 + 3), (enable) ? newOff : off); // dmc3.exe+1F59B1 - 80 BC 31 98640000 05 - CMP BYTE PTR [RCX+RSI+00006498],05
		Write<uint32>((appBaseAddr + 0x1F59D7 + 3), (enable) ? newOff : off); // dmc3.exe+1F59D7 - 80 BC 30 98640000 05 - CMP BYTE PTR [RAX+RSI+00006498],05
		Write<uint32>((appBaseAddr + 0x1F6674 + 4), (enable) ? newOff : off); // dmc3.exe+1F6674 - 40 38 BC 18 98640000 - CMP [RAX+RBX+00006498],DIL
		Write<uint32>((appBaseAddr + 0x1F66A9 + 4), (enable) ? newOff : off); // dmc3.exe+1F66A9 - 40 38 BC 18 98640000 - CMP [RAX+RBX+00006498],DIL
		Write<uint32>((appBaseAddr + 0x1F7607 + 3), (enable) ? newOff : off); // dmc3.exe+1F7607 - 80 BC 18 98640000 07 - CMP BYTE PTR [RAX+RBX+00006498],07
		Write<uint32>((appBaseAddr + 0x1F762A + 3), (enable) ? newOff : off); // dmc3.exe+1F762A - 80 BC 18 98640000 07 - CMP BYTE PTR [RAX+RBX+00006498],07
		Write<uint32>((appBaseAddr + 0x1F9445 + 4), (enable) ? newOff : off); // dmc3.exe+1F9445 - 0FBE 94 08 98640000 - MOVSX EDX,BYTE PTR [RAX+RCX+00006498]
		Write<uint32>((appBaseAddr + 0x1FACA0 + 3), (enable) ? newOff : off); // dmc3.exe+1FACA0 - 38 94 08 98640000 - CMP [RAX+RCX+00006498],DL
		Write<uint32>((appBaseAddr + 0x1FAD00 + 3), (enable) ? newOff : off); // dmc3.exe+1FAD00 - 38 94 08 98640000 - CMP [RAX+RCX+00006498],DL
		Write<uint32>((appBaseAddr + 0x1FAD40 + 3), (enable) ? newOff : off); // dmc3.exe+1FAD40 - 38 94 08 98640000 - CMP [RAX+RCX+00006498],DL
		Write<uint32>((appBaseAddr + 0x1FB13F + 3), (enable) ? newOff : off); // dmc3.exe+1FB13F - 80 BC 08 98640000 00 - CMP BYTE PTR [RAX+RCX+00006498],00
		Write<uint32>((appBaseAddr + 0x1FD143 + 3), (enable) ? newOff : off); // dmc3.exe+1FD143 - 38 94 08 98640000 - CMP [RAX+RCX+00006498],DL
		Write<uint32>((appBaseAddr + 0x1FD173 + 4), (enable) ? newOff : off); // dmc3.exe+1FD173 - 41 38 94 09 98640000 - CMP [R9+RCX+00006498],DL
		Write<uint32>((appBaseAddr + 0x1FD1A6 + 4), (enable) ? newOff : off); // dmc3.exe+1FD1A6 - 0FB6 8C 08 98640000 - MOVZX ECX,BYTE PTR [RAX+RCX+00006498]
		Write<uint32>((appBaseAddr + 0x1FD1D0 + 3), (enable) ? newOff : off); // dmc3.exe+1FD1D0 - 38 94 08 98640000 - CMP [RAX+RCX+00006498],DL
		Write<uint32>((appBaseAddr + 0x1FD651 + 4), (enable) ? newOff : off); // dmc3.exe+1FD651 - 44 38 84 10 98640000 - CMP [RAX+RDX+00006498],R8L
		Write<uint32>((appBaseAddr + 0x20477A + 4), (enable) ? newOff : off); // dmc3.exe+20477A - 0FB6 8C 18 98640000 - MOVZX ECX,BYTE PTR [RAX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x204A45 + 4), (enable) ? newOff : off); // dmc3.exe+204A45 - 0FB6 8C 18 98640000 - MOVZX ECX,BYTE PTR [RAX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x204AD4 + 3), (enable) ? newOff : off); // dmc3.exe+204AD4 - 80 BC 18 98640000 03 - CMP BYTE PTR [RAX+RBX+00006498],03
		Write<uint32>((appBaseAddr + 0x204B4A + 3), (enable) ? newOff : off); // dmc3.exe+204B4A - 80 BC 18 98640000 03 - CMP BYTE PTR [RAX+RBX+00006498],03
		Write<uint32>((appBaseAddr + 0x20511E + 3), (enable) ? newOff : off); // dmc3.exe+20511E - 80 BC 18 98640000 05 - CMP BYTE PTR [RAX+RBX+00006498],05
		Write<uint32>((appBaseAddr + 0x205273 + 3), (enable) ? newOff : off); // dmc3.exe+205273 - 80 BC 18 98640000 05 - CMP BYTE PTR [RAX+RBX+00006498],05
		Write<uint32>((appBaseAddr + 0x20530B + 3), (enable) ? newOff : off); // dmc3.exe+20530B - 80 BC 18 98640000 05 - CMP BYTE PTR [RAX+RBX+00006498],05
		Write<uint32>((appBaseAddr + 0x2054D1 + 3), (enable) ? newOff : off); // dmc3.exe+2054D1 - 80 BC 18 98640000 05 - CMP BYTE PTR [RAX+RBX+00006498],05
		Write<uint32>((appBaseAddr + 0x206172 + 3), (enable) ? newOff : off); // dmc3.exe+206172 - 80 BC 18 98640000 09 - CMP BYTE PTR [RAX+RBX+00006498],09
		Write<uint32>((appBaseAddr + 0x206192 + 3), (enable) ? newOff : off); // dmc3.exe+206192 - 80 BC 18 98640000 09 - CMP BYTE PTR [RAX+RBX+00006498],09
		Write<uint32>((appBaseAddr + 0x2063A0 + 3), (enable) ? newOff : off); // dmc3.exe+2063A0 - 80 BC 19 98640000 09 - CMP BYTE PTR [RCX+RBX+00006498],09
		Write<uint32>((appBaseAddr + 0x206510 + 3), (enable) ? newOff : off); // dmc3.exe+206510 - 80 BC 19 98640000 09 - CMP BYTE PTR [RCX+RBX+00006498],09
		Write<uint32>((appBaseAddr + 0x208220 + 3), (enable) ? newOff : off); // dmc3.exe+208220 - 80 BC 1F 98640000 00 - CMP BYTE PTR [RDI+RBX+00006498],00
		Write<uint32>((appBaseAddr + 0x208281 + 3), (enable) ? newOff : off); // dmc3.exe+208281 - 80 BC 18 98640000 00 - CMP BYTE PTR [RAX+RBX+00006498],00
		Write<uint32>((appBaseAddr + 0x2086E5 + 3), (enable) ? newOff : off); // dmc3.exe+2086E5 - 80 BC 18 98640000 08 - CMP BYTE PTR [RAX+RBX+00006498],08
		Write<uint32>((appBaseAddr + 0x208713 + 3), (enable) ? newOff : off); // dmc3.exe+208713 - 80 BC 18 98640000 08 - CMP BYTE PTR [RAX+RBX+00006498],08
		Write<uint32>((appBaseAddr + 0x208CF8 + 3), (enable) ? newOff : off); // dmc3.exe+208CF8 - 80 BC 18 98640000 06 - CMP BYTE PTR [RAX+RBX+00006498],06
		Write<uint32>((appBaseAddr + 0x208DFF + 3), (enable) ? newOff : off); // dmc3.exe+208DFF - 80 BC 18 98640000 06 - CMP BYTE PTR [RAX+RBX+00006498],06
		Write<uint32>((appBaseAddr + 0x20D1B2 + 3), (enable) ? newOff : off); // dmc3.exe+20D1B2 - 80 BC 18 98640000 05 - CMP BYTE PTR [RAX+RBX+00006498],05
		Write<uint32>((appBaseAddr + 0x20E302 + 3), (enable) ? newOff : off); // dmc3.exe+20E302 - 80 BC 18 98640000 08 - CMP BYTE PTR [RAX+RBX+00006498],08
		Write<uint32>((appBaseAddr + 0x20E662 + 3), (enable) ? newOff : off); // dmc3.exe+20E662 - 80 BC 18 98640000 08 - CMP BYTE PTR [RAX+RBX+00006498],08
		Write<uint32>((appBaseAddr + 0x20E713 + 3), (enable) ? newOff : off); // dmc3.exe+20E713 - 80 BC 18 98640000 08 - CMP BYTE PTR [RAX+RBX+00006498],08
		Write<uint32>((appBaseAddr + 0x210A22 + 4), (enable) ? newOff : off); // dmc3.exe+210A22 - 44 38 84 18 98640000 - CMP [RAX+RBX+00006498],R8L
		Write<uint32>((appBaseAddr + 0x210C00 + 3), (enable) ? newOff : off); // dmc3.exe+210C00 - 80 BC 1F 98640000 00 - CMP BYTE PTR [RDI+RBX+00006498],00
		Write<uint32>((appBaseAddr + 0x210C40 + 3), (enable) ? newOff : off); // dmc3.exe+210C40 - 80 BC 19 98640000 00 - CMP BYTE PTR [RCX+RBX+00006498],00
		Write<uint32>((appBaseAddr + 0x2113D1 + 3), (enable) ? newOff : off); // dmc3.exe+2113D1 - 80 BC 37 98640000 00 - CMP BYTE PTR [RDI+RSI+00006498],00
		Write<uint32>((appBaseAddr + 0x2114C0 + 3), (enable) ? newOff : off); // dmc3.exe+2114C0 - 80 BC 37 98640000 00 - CMP BYTE PTR [RDI+RSI+00006498],00
		Write<uint32>((appBaseAddr + 0x2115E0 + 3), (enable) ? newOff : off); // dmc3.exe+2115E0 - 80 BC 37 98640000 00 - CMP BYTE PTR [RDI+RSI+00006498],00
		Write<uint32>((appBaseAddr + 0x211682 + 4), (enable) ? newOff : off); // dmc3.exe+211682 - 40 38 BC 30 98640000 - CMP [RAX+RSI+00006498],DIL
		Write<uint32>((appBaseAddr + 0x211723 + 3), (enable) ? newOff : off); // dmc3.exe+211723 - 80 BC 37 98640000 00 - CMP BYTE PTR [RDI+RSI+00006498],00
		Write<uint32>((appBaseAddr + 0x211782 + 4), (enable) ? newOff : off); // dmc3.exe+211782 - 40 38 BC 30 98640000 - CMP [RAX+RSI+00006498],DIL
		Write<uint32>((appBaseAddr + 0x212A3C + 3), (enable) ? newOff : off); // dmc3.exe+212A3C - 0FB6 81 98640000 - MOVZX EAX,BYTE PTR [RCX+00006498]
		Write<uint32>((appBaseAddr + 0x2155F6 + 3), (enable) ? newOff : off); // dmc3.exe+2155F6 - 48 81 C1 98640000 - ADD RCX,00006498
		Write<uint32>((appBaseAddr + 0x215702 + 4), (enable) ? newOff : off); // dmc3.exe+215702 - 44 38 B4 38 98640000 - CMP [RAX+RDI+00006498],R14L
		Write<uint32>((appBaseAddr + 0x215899 + 4), (enable) ? newOff : off); // dmc3.exe+215899 - 44 38 B4 38 98640000 - CMP [RAX+RDI+00006498],R14L
		Write<uint32>((appBaseAddr + 0x2158B2 + 4), (enable) ? newOff : off); // dmc3.exe+2158B2 - 44 38 B4 38 98640000 - CMP [RAX+RDI+00006498],R14L
		Write<uint32>((appBaseAddr + 0x215948 + 4), (enable) ? newOff : off); // dmc3.exe+215948 - 44 38 B4 38 98640000 - CMP [RAX+RDI+00006498],R14L
		Write<uint32>((appBaseAddr + 0x215972 + 4), (enable) ? newOff : off); // dmc3.exe+215972 - 44 38 B4 38 98640000 - CMP [RAX+RDI+00006498],R14L
		Write<uint32>((appBaseAddr + 0x2159CE + 4), (enable) ? newOff : off); // dmc3.exe+2159CE - 44 38 B4 38 98640000 - CMP [RAX+RDI+00006498],R14L
		Write<uint32>((appBaseAddr + 0x2159E2 + 4), (enable) ? newOff : off); // dmc3.exe+2159E2 - 44 38 B4 38 98640000 - CMP [RAX+RDI+00006498],R14L
		Write<uint32>((appBaseAddr + 0x215BD2 + 3), (enable) ? newOff : off); // dmc3.exe+215BD2 - 80 BC 38 98640000 07 - CMP BYTE PTR [RAX+RDI+00006498],07
		Write<uint32>((appBaseAddr + 0x215C1D + 4), (enable) ? newOff : off); // dmc3.exe+215C1D - 0FB6 9C 38 98640000 - MOVZX EBX,BYTE PTR [RAX+RDI+00006498]
		Write<uint32>((appBaseAddr + 0x215E82 + 3), (enable) ? newOff : off); // dmc3.exe+215E82 - 80 BC 38 98640000 07 - CMP BYTE PTR [RAX+RDI+00006498],07
		Write<uint32>((appBaseAddr + 0x215EA2 + 3), (enable) ? newOff : off); // dmc3.exe+215EA2 - 80 BC 38 98640000 07 - CMP BYTE PTR [RAX+RDI+00006498],07
		Write<uint32>((appBaseAddr + 0x21609D + 4), (enable) ? newOff : off); // dmc3.exe+21609D - 0FB6 B4 38 98640000 - MOVZX ESI,BYTE PTR [RAX+RDI+00006498]
		Write<uint32>((appBaseAddr + 0x2161D2 + 5), (enable) ? newOff : off); // dmc3.exe+2161D2 - 44 0FBE 8C 38 98640000 - MOVSX R9D,BYTE PTR [RAX+RDI+00006498]
		Write<uint32>((appBaseAddr + 0x2163E7 + 5), (enable) ? newOff : off); // dmc3.exe+2163E7 - 44 0FBE 8C 38 98640000 - MOVSX R9D,BYTE PTR [RAX+RDI+00006498]
		Write<uint32>((appBaseAddr + 0x216E42 + 3), (enable) ? newOff : off); // dmc3.exe+216E42 - 80 BC 38 98640000 05 - CMP BYTE PTR [RAX+RDI+00006498],05
		Write<uint32>((appBaseAddr + 0x217012 + 3), (enable) ? newOff : off); // dmc3.exe+217012 - 80 BC 38 98640000 05 - CMP BYTE PTR [RAX+RDI+00006498],05
		Write<uint32>((appBaseAddr + 0x2171E2 + 3), (enable) ? newOff : off); // dmc3.exe+2171E2 - 80 BC 38 98640000 05 - CMP BYTE PTR [RAX+RDI+00006498],05
		Write<uint32>((appBaseAddr + 0x217362 + 3), (enable) ? newOff : off); // dmc3.exe+217362 - 80 BC 38 98640000 05 - CMP BYTE PTR [RAX+RDI+00006498],05
		Write<uint32>((appBaseAddr + 0x217473 + 3), (enable) ? newOff : off); // dmc3.exe+217473 - 80 BC 38 98640000 05 - CMP BYTE PTR [RAX+RDI+00006498],05
		Write<uint32>((appBaseAddr + 0x218192 + 3), (enable) ? newOff : off); // dmc3.exe+218192 - 80 BC 18 98640000 06 - CMP BYTE PTR [RAX+RBX+00006498],06
		Write<uint32>((appBaseAddr + 0x218312 + 3), (enable) ? newOff : off); // dmc3.exe+218312 - 80 BC 18 98640000 06 - CMP BYTE PTR [RAX+RBX+00006498],06
		Write<uint32>((appBaseAddr + 0x2183E5 + 3), (enable) ? newOff : off); // dmc3.exe+2183E5 - 80 BC 18 98640000 06 - CMP BYTE PTR [RAX+RBX+00006498],06
		Write<uint32>((appBaseAddr + 0x218422 + 3), (enable) ? newOff : off); // dmc3.exe+218422 - 80 BC 18 98640000 06 - CMP BYTE PTR [RAX+RBX+00006498],06
		Write<uint32>((appBaseAddr + 0x218456 + 3), (enable) ? newOff : off); // dmc3.exe+218456 - 80 BC 18 98640000 06 - CMP BYTE PTR [RAX+RBX+00006498],06
		Write<uint32>((appBaseAddr + 0x2184B2 + 3), (enable) ? newOff : off); // dmc3.exe+2184B2 - 80 BC 18 98640000 06 - CMP BYTE PTR [RAX+RBX+00006498],06
		Write<uint32>((appBaseAddr + 0x2184F2 + 3), (enable) ? newOff : off); // dmc3.exe+2184F2 - 80 BC 18 98640000 06 - CMP BYTE PTR [RAX+RBX+00006498],06
		Write<uint32>((appBaseAddr + 0x218532 + 3), (enable) ? newOff : off); // dmc3.exe+218532 - 80 BC 18 98640000 06 - CMP BYTE PTR [RAX+RBX+00006498],06
		Write<uint32>((appBaseAddr + 0x21A462 + 3), (enable) ? newOff : off); // dmc3.exe+21A462 - 80 BC 18 98640000 0B - CMP BYTE PTR [RAX+RBX+00006498],0B
		Write<uint32>((appBaseAddr + 0x21A4B2 + 3), (enable) ? newOff : off); // dmc3.exe+21A4B2 - 80 BC 18 98640000 0B - CMP BYTE PTR [RAX+RBX+00006498],0B
		Write<uint32>((appBaseAddr + 0x21B7F4 + 3), (enable) ? newOff : off); // dmc3.exe+21B7F4 - 80 BC 18 98640000 0B - CMP BYTE PTR [RAX+RBX+00006498],0B
		Write<uint32>((appBaseAddr + 0x21B8C2 + 3), (enable) ? newOff : off); // dmc3.exe+21B8C2 - 80 BC 18 98640000 0B - CMP BYTE PTR [RAX+RBX+00006498],0B
		Write<uint32>((appBaseAddr + 0x21B8F2 + 3), (enable) ? newOff : off); // dmc3.exe+21B8F2 - 80 BC 18 98640000 0B - CMP BYTE PTR [RAX+RBX+00006498],0B
		Write<uint32>((appBaseAddr + 0x21BBB0 + 3), (enable) ? newOff : off); // dmc3.exe+21BBB0 - 80 BC 19 98640000 0B - CMP BYTE PTR [RCX+RBX+00006498],0B
		Write<uint32>((appBaseAddr + 0x21BBE0 + 3), (enable) ? newOff : off); // dmc3.exe+21BBE0 - 80 BC 19 98640000 0B - CMP BYTE PTR [RCX+RBX+00006498],0B
		Write<uint32>((appBaseAddr + 0x21C0A2 + 3), (enable) ? newOff : off); // dmc3.exe+21C0A2 - 80 BC 18 98640000 0B - CMP BYTE PTR [RAX+RBX+00006498],0B
		Write<uint32>((appBaseAddr + 0x21C3D2 + 3), (enable) ? newOff : off); // dmc3.exe+21C3D2 - 80 BC 18 98640000 0B - CMP BYTE PTR [RAX+RBX+00006498],0B
		Write<uint32>((appBaseAddr + 0x21C402 + 3), (enable) ? newOff : off); // dmc3.exe+21C402 - 80 BC 18 98640000 0B - CMP BYTE PTR [RAX+RBX+00006498],0B
		Write<uint32>((appBaseAddr + 0x21C6A3 + 3), (enable) ? newOff : off); // dmc3.exe+21C6A3 - 80 BC 18 98640000 0B - CMP BYTE PTR [RAX+RBX+00006498],0B
		Write<uint32>((appBaseAddr + 0x21C745 + 3), (enable) ? newOff : off); // dmc3.exe+21C745 - 80 BC 18 98640000 0B - CMP BYTE PTR [RAX+RBX+00006498],0B
		Write<uint32>((appBaseAddr + 0x21C842 + 3), (enable) ? newOff : off); // dmc3.exe+21C842 - 80 BC 18 98640000 0B - CMP BYTE PTR [RAX+RBX+00006498],0B
		Write<uint32>((appBaseAddr + 0x21D0D4 + 3), (enable) ? newOff : off); // dmc3.exe+21D0D4 - 80 BC 38 98640000 0B - CMP BYTE PTR [RAX+RDI+00006498],0B
		Write<uint32>((appBaseAddr + 0x21D102 + 3), (enable) ? newOff : off); // dmc3.exe+21D102 - 80 BC 38 98640000 0B - CMP BYTE PTR [RAX+RDI+00006498],0B
		Write<uint32>((appBaseAddr + 0x21E904 + 3), (enable) ? newOff : off); // dmc3.exe+21E904 - 80 BC 18 98640000 0B - CMP BYTE PTR [RAX+RBX+00006498],0B
		Write<uint32>((appBaseAddr + 0x21E932 + 3), (enable) ? newOff : off); // dmc3.exe+21E932 - 80 BC 18 98640000 0B - CMP BYTE PTR [RAX+RBX+00006498],0B
		Write<uint32>((appBaseAddr + 0x21F226 + 3), (enable) ? newOff : off); // dmc3.exe+21F226 - 80 BC 1F 98640000 0D - CMP BYTE PTR [RDI+RBX+00006498],0D
		Write<uint32>((appBaseAddr + 0x21F250 + 3), (enable) ? newOff : off); // dmc3.exe+21F250 - 80 BC 19 98640000 0D - CMP BYTE PTR [RCX+RBX+00006498],0D
		Write<uint32>((appBaseAddr + 0x2228F3 + 3), (enable) ? newOff : off); // dmc3.exe+2228F3 - 48 81 C1 98640000 - ADD RCX,00006498
		Write<uint32>((appBaseAddr + 0x2229A2 + 3), (enable) ? newOff : off); // dmc3.exe+2229A2 - 80 BC 38 98640000 0D - CMP BYTE PTR [RAX+RDI+00006498],0D
		Write<uint32>((appBaseAddr + 0x222B46 + 3), (enable) ? newOff : off); // dmc3.exe+222B46 - 80 BC 38 98640000 0B - CMP BYTE PTR [RAX+RDI+00006498],0B
		Write<uint32>((appBaseAddr + 0x222E92 + 3), (enable) ? newOff : off); // dmc3.exe+222E92 - 80 BC 38 98640000 0D - CMP BYTE PTR [RAX+RDI+00006498],0D
		Write<uint32>((appBaseAddr + 0x222F34 + 3), (enable) ? newOff : off); // dmc3.exe+222F34 - 80 BC 38 98640000 0D - CMP BYTE PTR [RAX+RDI+00006498],0D
		// Unknown
		// Write<uint32>((appBaseAddr + 0x1E2C33 + 4), (enable) ? newOff : off); // dmc3.exe+1E2C33 - 41 3A 84 18 98640000 - CMP AL,[R8+RBX+00006498]
		// Write<uint32>((appBaseAddr + 0x1E2CEA + 5), (enable) ? newOff : off); // dmc3.exe+1E2CEA - 41 0FB6 84 18 98640000 - MOVZX EAX,BYTE PTR [R8+RBX+00006498]
		// Write<uint32>((appBaseAddr + 0x1E3F9D + 4), (enable) ? newOff : off); // dmc3.exe+1E3F9D - 0FB6 8C 18 98640000 - MOVZX ECX,BYTE PTR [RAX+RBX+00006498]
		// Write<uint32>((appBaseAddr + 0x1FAB48 + 4), (enable) ? newOff : off); // dmc3.exe+1FAB48 - 0FB6 84 08 98640000 - MOVZX EAX,BYTE PTR [RAX+RCX+00006498]
		// Write<uint32>((appBaseAddr + 0x1FCFD4 + 2), (enable) ? newOff : off); // dmc3.exe+1FCFD4 - 80 B9 98640000 FF - CMP BYTE PTR [RCX+00006498],-01
		// Write<uint32>((appBaseAddr + 0x1FCFDD + 2), (enable) ? newOff : off); // dmc3.exe+1FCFDD - 88 91 98640000 - MOV [RCX+00006498],DL
		// Write<uint32>((appBaseAddr + 0x1FD4D9 + 3), (enable) ? newOff : off); // dmc3.exe+1FD4D9 - 38 94 08 98640000 - CMP [RAX+RCX+00006498],DL
		// Write<uint32>((appBaseAddr + 0x20E332 + 3), (enable) ? newOff : off); // dmc3.exe+20E332 - 80 BC 18 98640000 08 - CMP BYTE PTR [RAX+RBX+00006498],08
		// Write<uint32>((appBaseAddr + 0x20E363 + 3), (enable) ? newOff : off); // dmc3.exe+20E363 - 80 BC 18 98640000 08 - CMP BYTE PTR [RAX+RBX+00006498],08
		// Write<uint32>((appBaseAddr + 0x20EF5F + 3), (enable) ? newOff : off); // dmc3.exe+20EF5F - 80 BC 38 98640000 06 - CMP BYTE PTR [RAX+RDI+00006498],06
	}
	// 0x6499
	{
		constexpr auto off = offsetof(ActorData, weapons[1]);
		constexpr auto newOff = offsetof(ActorData, newWeapons[1]);
		static_assert(off == 0x6499);
		// Init Actor Dante
		Write<uint32>((appBaseAddr + 0x217C07 + 2), (enable) ? newOff : off); // dmc3.exe+217C07 - 88 81 99640000 - MOV [RCX+00006499],AL
		// Update Actor
		Write<uint32>((appBaseAddr + 0x1DF2E9 + 2), (enable) ? newOff : off); // dmc3.exe+1DF2E9 - C6 83 99640000 FF - MOV BYTE PTR [RBX+00006499],-01
		// func_2198D0
		Write<uint32>((appBaseAddr + 0x2198E5 + 3), (enable) ? newOff : off); // dmc3.exe+2198E5 - 0FB6 81 99640000 - MOVZX EAX,BYTE PTR [RCX+00006499]
		// func_2241F0
		Write<uint32>((appBaseAddr + 0x224205 + 3), (enable) ? newOff : off); // dmc3.exe+224205 - 0FB6 81 99640000 - MOVZX EAX,BYTE PTR [RCX+00006499]
		// Unknown
		// Write<uint32>((appBaseAddr + 0x1FCFE6 + 2), (enable) ? newOff : off); // dmc3.exe+1FCFE6 - 80 B9 99640000 FF - CMP BYTE PTR [RCX+00006499],-01
		// Write<uint32>((appBaseAddr + 0x1FCFEF + 2), (enable) ? newOff : off); // dmc3.exe+1FCFEF - 88 91 99640000 - MOV [RCX+00006499],DL
	}
	// 0x649A
	{
		constexpr auto off = offsetof(ActorData, weapons[2]);
		constexpr auto newOff = offsetof(ActorData, newWeapons[2]);
		static_assert(off == 0x649A);
		// Init Actor Dante
		Write<uint32>((appBaseAddr + 0x217C1A + 2), (enable) ? newOff : off); // dmc3.exe+217C1A - 88 81 9A640000 - MOV [RCX+0000649A],AL
		// Update Actor Dante
		Write<uint32>((appBaseAddr + 0x212F12 + 3), (enable) ? newOff : off); // dmc3.exe+212F12 - 48 8D 9E 9A640000 - LEA RBX,[RSI+0000649A]
		// Register Weapons
		Write<uint32>((appBaseAddr + 0x1DEE2A + 3), (enable) ? newOff : off); // dmc3.exe+1DEE2A - 48 8D AB 9A640000 - LEA RBP,[RBX+0000649A]
		// func_2198D0
		Write<uint32>((appBaseAddr + 0x2198F8 + 3), (enable) ? newOff : off); // dmc3.exe+2198F8 - 0FB6 81 9A640000 - MOVZX EAX,BYTE PTR [RCX+0000649A]
		// func_2241F0
		Write<uint32>((appBaseAddr + 0x224218 + 3), (enable) ? newOff : off); // dmc3.exe+224218 - 0FB6 81 9A640000 - MOVZX EAX,BYTE PTR [RCX+0000649A]
		// Unknown
		// Write<uint32>((appBaseAddr + 0x1FCFB0 + 2), (enable) ? newOff : off); // dmc3.exe+1FCFB0 - 80 B9 9A640000 FF - CMP BYTE PTR [RCX+0000649A],-01
		// Write<uint32>((appBaseAddr + 0x1FCFB9 + 2), (enable) ? newOff : off); // dmc3.exe+1FCFB9 - 88 91 9A640000 - MOV [RCX+0000649A],DL
	}
	// 0x649B
	{
		constexpr auto off = offsetof(ActorData, weapons[3]);
		constexpr auto newOff = offsetof(ActorData, newWeapons[3]);
		static_assert(off == 0x649B);
		// Init Actor Dante
		Write<uint32>((appBaseAddr + 0x217C2D + 2), (enable) ? newOff : off); // dmc3.exe+217C2D - 88 81 9B640000 - MOV [RCX+0000649B],AL
		// Update Actor
		Write<uint32>((appBaseAddr + 0x1DF2F9 + 2), (enable) ? newOff : off); // dmc3.exe+1DF2F9 - C6 83 9B640000 FF - MOV BYTE PTR [RBX+0000649B],-01
		// func_2198D0
		Write<uint32>((appBaseAddr + 0x21990B + 3), (enable) ? newOff : off); // dmc3.exe+21990B - 0FB6 81 9B640000 - MOVZX EAX,BYTE PTR [RCX+0000649B]
		// func_2241F0
		Write<uint32>((appBaseAddr + 0x22422B + 3), (enable) ? newOff : off); // dmc3.exe+22422B - 0FB6 81 9B640000 - MOVZX EAX,BYTE PTR [RCX+0000649B]
		// Unknown
		// Write<uint32>((appBaseAddr + 0x1FCFC2 + 2), (enable) ? newOff : off); // dmc3.exe+1FCFC2 - 80 B9 9B640000 FF - CMP BYTE PTR [RCX+0000649B],-01
		// Write<uint32>((appBaseAddr + 0x1FCFCB + 2), (enable) ? newOff : off); // dmc3.exe+1FCFCB - 88 91 9B640000 - MOV [RCX+0000649B],DL
	}
	// 0x649C
	{
		constexpr auto off = offsetof(ActorData, weapons[4]);
		constexpr auto newOff = offsetof(ActorData, newWeapons[4]);
		static_assert(off == 0x649C);
		// Init Actor Dante
		Write<uint32>((appBaseAddr + 0x217C40 + 2), (enable) ? newOff : off); // dmc3.exe+217C40 - 88 81 9C640000 - MOV [RCX+0000649C],AL
		// Init Actor Bob
		Write<uint32>((appBaseAddr + 0x226F5D + 2), (enable) ? newOff : off); // dmc3.exe+226F5D - C6 81 9C640000 FF - MOV BYTE PTR [RCX+0000649C],-01
		// Init Actor Lady
		Write<uint32>((appBaseAddr + 0x2196B4 + 2), (enable) ? newOff : off); // dmc3.exe+2196B4 - C6 81 9C640000 0B - MOV BYTE PTR [RCX+0000649C],0B
		// Init Actor Vergil
		Write<uint32>((appBaseAddr + 0x223D1B + 2), (enable) ? newOff : off); // dmc3.exe+223D1B - C6 81 9C640000 FF - MOV BYTE PTR [RCX+0000649C],-01
		// func_2198D0
		Write<uint32>((appBaseAddr + 0x21991E + 3), (enable) ? newOff : off); // dmc3.exe+21991E - 0FB6 81 9C640000 - MOVZX EAX,BYTE PTR [RCX+0000649C]
		// func_2241F0
		Write<uint32>((appBaseAddr + 0x22423E + 3), (enable) ? newOff : off); // dmc3.exe+22423E - 0FB6 81 9C640000 - MOVZX EAX,BYTE PTR [RCX+0000649C]
	}
	// 0x64A0
	{
		constexpr auto off = offsetof(ActorData, weaponDataAddr[0]);
		constexpr auto newOff = offsetof(ActorData, newWeaponDataAddr[0]);
		static_assert(off == 0x64A0);
		// Register Weapons
		Write<uint32>((appBaseAddr + 0x1DED55 + 3), (enable) ? newOff : off); // dmc3.exe+1DED55 - 48 8D B1 A0640000 - LEA RSI,[RCX+000064A0]
		// Other
		Write<uint32>((appBaseAddr + 0x1DFB82 + 3), (enable) ? newOff : off); // dmc3.exe+1DFB82 - 48 8D 99 A0640000 - LEA RBX,[RCX+000064A0]
		Write<uint32>((appBaseAddr + 0x1FACBB + 4), (enable) ? newOff : off); // dmc3.exe+1FACBB - 49 8B 8C CA A0640000 - MOV RCX,[R10+RCX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x1FAD5B + 4), (enable) ? newOff : off); // dmc3.exe+1FAD5B - 49 8B 8C C9 A0640000 - MOV RCX,[R9+RCX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x1FB84C + 3), (enable) ? newOff : off); // dmc3.exe+1FB84C - 48 8D B3 A0640000 - LEA RSI,[RBX+000064A0]
		Write<uint32>((appBaseAddr + 0x1FB9A7 + 3), (enable) ? newOff : off); // dmc3.exe+1FB9A7 - 48 8D B3 A0640000 - LEA RSI,[RBX+000064A0]
		Write<uint32>((appBaseAddr + 0x1FCAD4 + 3), (enable) ? newOff : off); // dmc3.exe+1FCAD4 - 49 8D 9E A0640000 - LEA RBX,[R14+000064A0]
		Write<uint32>((appBaseAddr + 0x1FCEC8 + 3), (enable) ? newOff : off); // dmc3.exe+1FCEC8 - 48 81 C7 A0640000 - ADD RDI,000064A0
		Write<uint32>((appBaseAddr + 0x2061AE + 4), (enable) ? newOff : off); // dmc3.exe+2061AE - 4C 8B 94 C3 A0640000 - MOV R10,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x210A48 + 4), (enable) ? newOff : off); // dmc3.exe+210A48 - 48 8B 8C C3 A0640000 - MOV RCX,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x210D2B + 4), (enable) ? newOff : off); // dmc3.exe+210D2B - 48 8B 8C C3 A0640000 - MOV RCX,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x2113FC + 4), (enable) ? newOff : off); // dmc3.exe+2113FC - 48 8B 8C C6 A0640000 - MOV RCX,[RSI+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x2114DD + 4), (enable) ? newOff : off); // dmc3.exe+2114DD - 48 8B 8C C6 A0640000 - MOV RCX,[RSI+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21160F + 4), (enable) ? newOff : off); // dmc3.exe+21160F - 48 8B 8C C6 A0640000 - MOV RCX,[RSI+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21169E + 4), (enable) ? newOff : off); // dmc3.exe+21169E - 48 8B 8C C6 A0640000 - MOV RCX,[RSI+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21174E + 4), (enable) ? newOff : off); // dmc3.exe+21174E - 48 8B 8C C6 A0640000 - MOV RCX,[RSI+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x2117B5 + 4), (enable) ? newOff : off); // dmc3.exe+2117B5 - 48 8B 8C C6 A0640000 - MOV RCX,[RSI+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x2158CE + 4), (enable) ? newOff : off); // dmc3.exe+2158CE - 48 8B 8C C7 A0640000 - MOV RCX,[RDI+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x2159FE + 4), (enable) ? newOff : off); // dmc3.exe+2159FE - 48 8B 8C C7 A0640000 - MOV RCX,[RDI+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x216EA9 + 4), (enable) ? newOff : off); // dmc3.exe+216EA9 - 48 8B 8C C7 A0640000 - MOV RCX,[RDI+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x218443 + 4), (enable) ? newOff : off); // dmc3.exe+218443 - 48 8B BC C3 A0640000 - MOV RDI,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x218472 + 4), (enable) ? newOff : off); // dmc3.exe+218472 - 48 8B BC C3 A0640000 - MOV RDI,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x2184D6 + 4), (enable) ? newOff : off); // dmc3.exe+2184D6 - 48 8B BC C3 A0640000 - MOV RDI,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x218516 + 4), (enable) ? newOff : off); // dmc3.exe+218516 - 48 8B BC C3 A0640000 - MOV RDI,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21854E + 4), (enable) ? newOff : off); // dmc3.exe+21854E - 48 8B BC C3 A0640000 - MOV RDI,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21A48F + 4), (enable) ? newOff : off); // dmc3.exe+21A48F - 4C 8B 8C C3 A0640000 - MOV R9,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21A4DF + 4), (enable) ? newOff : off); // dmc3.exe+21A4DF - 4C 8B 8C C3 A0640000 - MOV R9,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21B810 + 4), (enable) ? newOff : off); // dmc3.exe+21B810 - 4C 8B 8C C3 A0640000 - MOV R9,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21B8E1 + 4), (enable) ? newOff : off); // dmc3.exe+21B8E1 - 4C 8B 8C C3 A0640000 - MOV R9,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21B90E + 4), (enable) ? newOff : off); // dmc3.exe+21B90E - 4C 8B 8C C3 A0640000 - MOV R9,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21BBD4 + 4), (enable) ? newOff : off); // dmc3.exe+21BBD4 - 48 8B 8C C3 A0640000 - MOV RCX,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21BC78 + 4), (enable) ? newOff : off); // dmc3.exe+21BC78 - 48 8B 8C C3 A0640000 - MOV RCX,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21C0BE + 4), (enable) ? newOff : off); // dmc3.exe+21C0BE - 48 8B BC C3 A0640000 - MOV RDI,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21C3F1 + 4), (enable) ? newOff : off); // dmc3.exe+21C3F1 - 4C 8B 8C C3 A0640000 - MOV R9,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21C41E + 4), (enable) ? newOff : off); // dmc3.exe+21C41E - 4C 8B 8C C3 A0640000 - MOV R9,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21C6BF + 4), (enable) ? newOff : off); // dmc3.exe+21C6BF - 48 8B BC C3 A0640000 - MOV RDI,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21C761 + 4), (enable) ? newOff : off); // dmc3.exe+21C761 - 48 8B BC C3 A0640000 - MOV RDI,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21C85E + 4), (enable) ? newOff : off); // dmc3.exe+21C85E - 48 8B BC C3 A0640000 - MOV RDI,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21D0F3 + 4), (enable) ? newOff : off); // dmc3.exe+21D0F3 - 4C 8B 8C C7 A0640000 - MOV R9,[RDI+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21D11E + 4), (enable) ? newOff : off); // dmc3.exe+21D11E - 4C 8B 8C C7 A0640000 - MOV R9,[RDI+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21E923 + 4), (enable) ? newOff : off); // dmc3.exe+21E923 - 4C 8B 8C C3 A0640000 - MOV R9,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21E94E + 4), (enable) ? newOff : off); // dmc3.exe+21E94E - 4C 8B 8C C3 A0640000 - MOV R9,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21F2F7 + 4), (enable) ? newOff : off); // dmc3.exe+21F2F7 - 48 8B 8C C3 A0640000 - MOV RCX,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x222B62 + 4), (enable) ? newOff : off); // dmc3.exe+222B62 - 48 8B 8C C7 A0640000 - MOV RCX,[RDI+RAX*8+000064A0]
		// Unknown
		// Write<uint32>((appBaseAddr + 0x1FB777 + 3), (enable) ? newOff : off); // dmc3.exe+1FB777 - 48 8D B3 A0640000 - LEA RSI,[RBX+000064A0]
		// Write<uint32>((appBaseAddr + 0x1FB8F8 + 3), (enable) ? newOff : off); // dmc3.exe+1FB8F8 - 48 8D B3 A0640000 - LEA RSI,[RBX+000064A0]
	}
	// 0x64B0
	{
		constexpr auto off = offsetof(ActorData, weaponDataAddr[2]);
		constexpr auto newOff = offsetof(ActorData, newWeaponDataAddr[2]);
		static_assert(off == 0x64B0);
		// Register Weapons
		Write<uint32>((appBaseAddr + 0x1DEE3E + 3), (enable) ? newOff : off); // dmc3.exe+1DEE3E - 48 8D B3 B0640000 - LEA RSI,[RBX+000064B0]
	}
	// 0x64B8
	{
		constexpr auto off = offsetof(ActorData, weaponDataAddr[3]);
		constexpr auto newOff = offsetof(ActorData, newWeaponDataAddr[3]);
		static_assert(off == 0x64B8);
		// Register Weapons
		Write<uint32>((appBaseAddr + 0x1DEF27 + 3), (enable) ? newOff : off); // dmc3.exe+1DEF27 - 48 89 83 B8640000 - MOV [RBX+000064B8],RAX
		// Other
		Write<uint32>((appBaseAddr + 0x21AF95 + 3), (enable) ? newOff : off); // dmc3.exe+21AF95 - 48 8B 8F B8640000 - MOV RCX,[RDI+000064B8]
	}
	// 0x64C8
	{
		constexpr auto off = offsetof(ActorData, weaponStatus[0]);
		constexpr auto newOff = offsetof(ActorData, newWeaponStatus[0]);
		static_assert(off == 0x64C8);
		// Register Weapons
		Write<uint32>((appBaseAddr + 0x1DED48 + 3), (enable) ? newOff : off); // dmc3.exe+1DED48 - 48 8D B9 C8640000 - LEA RDI,[RCX+000064C8]
		// Other
		Write<uint32>((appBaseAddr + 0x1D9203 + 3), (enable) ? newOff : off); // dmc3.exe+1D9203 - C7 84 82 C8640000 00000000 - MOV [RDX+RAX*4+000064C8],00000000
		Write<uint32>((appBaseAddr + 0x1FAD1E + 4), (enable) ? newOff : off); // dmc3.exe+1FAD1E - 41 8B 84 89 C8640000 - MOV EAX,[R9+RCX*4+000064C8]
		Write<uint32>((appBaseAddr + 0x1FD162 + 4), (enable) ? newOff : off); // dmc3.exe+1FD162 - 44 39 8C 81 C8640000 - CMP [RCX+RAX*4+000064C8],R9D
		Write<uint32>((appBaseAddr + 0x1FD1E9 + 4), (enable) ? newOff : off); // dmc3.exe+1FD1E9 - 41 83 BC 8A C8640000 04 - CMP DWORD PTR [R10+RCX*4+000064C8],04
		Write<uint32>((appBaseAddr + 0x1FD1F4 + 4), (enable) ? newOff : off); // dmc3.exe+1FD1F4 - 45 89 84 8A C8640000 - MOV [R10+RCX*4+000064C8],R8D
		Write<uint32>((appBaseAddr + 0x2063BA + 3), (enable) ? newOff : off); // dmc3.exe+2063BA - 83 BC BB C8640000 01 - CMP DWORD PTR [RBX+RDI*4+000064C8],01
		Write<uint32>((appBaseAddr + 0x206418 + 3), (enable) ? newOff : off); // dmc3.exe+206418 - C7 84 BB C8640000 02000000 - MOV [RBX+RDI*4+000064C8],00000002
		Write<uint32>((appBaseAddr + 0x20644C + 3), (enable) ? newOff : off); // dmc3.exe+20644C - 83 BC BB C8640000 03 - CMP DWORD PTR [RBX+RDI*4+000064C8],03
		Write<uint32>((appBaseAddr + 0x206532 + 3), (enable) ? newOff : off); // dmc3.exe+206532 - C7 84 83 C8640000 01000000 - MOV [RBX+RAX*4+000064C8],00000001
		Write<uint32>((appBaseAddr + 0x210CDF + 3), (enable) ? newOff : off); // dmc3.exe+210CDF - C7 84 93 C8640000 01000000 - MOV [RBX+RDX*4+000064C8],00000001
		Write<uint32>((appBaseAddr + 0x215650 + 3), (enable) ? newOff : off); // dmc3.exe+215650 - 48 8D 87 C8640000 - LEA RAX,[RDI+000064C8]
		Write<uint32>((appBaseAddr + 0x215725 + 3), (enable) ? newOff : off); // dmc3.exe+215725 - 83 BC 9F C8640000 01 - CMP DWORD PTR [RDI+RBX*4+000064C8],01
		Write<uint32>((appBaseAddr + 0x215770 + 3), (enable) ? newOff : off); // dmc3.exe+215770 - C7 84 9F C8640000 02000000 - MOV [RDI+RBX*4+000064C8],00000002
		Write<uint32>((appBaseAddr + 0x215995 + 4), (enable) ? newOff : off); // dmc3.exe+215995 - 44 39 B4 87 C8640000 - CMP [RDI+RAX*4+000064C8],R14D
		Write<uint32>((appBaseAddr + 0x21F29E + 3), (enable) ? newOff : off); // dmc3.exe+21F29E - C7 84 93 C8640000 01000000 - MOV [RBX+RDX*4+000064C8],00000001
		Write<uint32>((appBaseAddr + 0x222941 + 3), (enable) ? newOff : off); // dmc3.exe+222941 - 48 8D 87 C8640000 - LEA RAX,[RDI+000064C8]
		Write<uint32>((appBaseAddr + 0x2229BE + 3), (enable) ? newOff : off); // dmc3.exe+2229BE - 39 B4 87 C8640000 - CMP [RDI+RAX*4+000064C8],ESI
		Write<uint32>((appBaseAddr + 0x222EAF + 3), (enable) ? newOff : off); // dmc3.exe+222EAF - 83 BC 87 C8640000 00 - CMP DWORD PTR [RDI+RAX*4+000064C8],00
		Write<uint32>((appBaseAddr + 0x222F57 + 3), (enable) ? newOff : off); // dmc3.exe+222F57 - 39 B4 87 C8640000 - CMP [RDI+RAX*4+000064C8],ESI
	}
	// 0x64D0
	{
		constexpr auto off = offsetof(ActorData, weaponStatus[2]);
		constexpr auto newOff = offsetof(ActorData, newWeaponStatus[2]);
		static_assert(off == 0x64D0);
		// Register Weapons
		Write<uint32>((appBaseAddr + 0x1DEE37 + 3), (enable) ? newOff : off); // dmc3.exe+1DEE37 - 48 8D BB D0640000 - LEA RDI,[RBX+000064D0]
	}
	// 0x64DC
	{
		constexpr auto off = offsetof(ActorData, weaponLevels[0]);
		constexpr auto newOff = offsetof(ActorData, newWeaponLevels[0]);
		static_assert(off == 0x64DC);
		// Init Actor Dante
		Write<uint32>((appBaseAddr + 0x217BFD + 2), (enable) ? newOff : off); // dmc3.exe+217BFD - 89 81 DC640000 - MOV [RCX+000064DC],EAX
		// Init Actor Bob
		Write<uint32>((appBaseAddr + 0x226F64 + 3), (enable) ? newOff : off); // dmc3.exe+226F64 - 4C 89 A1 DC640000 - MOV [RCX+000064DC],R12
		// Init Actor Lady
		Write<uint32>((appBaseAddr + 0x2196BB + 3), (enable) ? newOff : off); // dmc3.exe+2196BB - 4C 89 A1 DC640000 - MOV [RCX+000064DC],R12
		// Init Actor Vergil
		Write<uint32>((appBaseAddr + 0x223D25 + 2), (enable) ? newOff : off); // dmc3.exe+223D25 - 89 81 DC640000 - MOV [RCX+000064DC],EAX
		// func_2198D0
		Write<uint32>((appBaseAddr + 0x2198DC + 2), (enable) ? newOff : off); // dmc3.exe+2198DC - 8B 81 DC640000 - MOV EAX,[RCX+000064DC]
		// func_2241F0
		Write<uint32>((appBaseAddr + 0x2241FC + 2), (enable) ? newOff : off); // dmc3.exe+2241FC - 8B 81 DC640000 - MOV EAX,[RCX+000064DC]
		// Other
		Write<uint32>((appBaseAddr + 0x2061C1 + 4), (enable) ? newOff : off); // dmc3.exe+2061C1 - 44 8B 84 83 DC640000 - MOV R8D,[RBX+RAX*4+000064DC]
		Write<uint32>((appBaseAddr + 0x208704 + 4), (enable) ? newOff : off); // dmc3.exe+208704 - 44 8B 84 83 DC640000 - MOV R8D,[RBX+RAX*4+000064DC]
		Write<uint32>((appBaseAddr + 0x20E321 + 4), (enable) ? newOff : off); // dmc3.exe+20E321 - 44 8B 84 83 DC640000 - MOV R8D,[RBX+RAX*4+000064DC]
		Write<uint32>((appBaseAddr + 0x20E684 + 3), (enable) ? newOff : off); // dmc3.exe+20E684 - 8B BC 83 DC640000 - MOV EDI,[RBX+RAX*4+000064DC]
		Write<uint32>((appBaseAddr + 0x20E72F + 3), (enable) ? newOff : off); // dmc3.exe+20E72F - 8B BC 83 DC640000 - MOV EDI,[RBX+RAX*4+000064DC]
		Write<uint32>((appBaseAddr + 0x215EBE + 3), (enable) ? newOff : off); // dmc3.exe+215EBE - 83 BC 87 DC640000 01 - CMP DWORD PTR [RDI+RAX*4+000064DC],01
		Write<uint32>((appBaseAddr + 0x215ED5 + 3), (enable) ? newOff : off); // dmc3.exe+215ED5 - 83 BC 87 DC640000 02 - CMP DWORD PTR [RDI+RAX*4+000064DC],02
		Write<uint32>((appBaseAddr + 0x217496 + 3), (enable) ? newOff : off); // dmc3.exe+217496 - 8B 8C 87 DC640000 - MOV ECX,[RDI+RAX*4+000064DC]
		Write<uint32>((appBaseAddr + 0x218408 + 3), (enable) ? newOff : off); // dmc3.exe+218408 - 8B 8C 83 DC640000 - MOV ECX,[RBX+RAX*4+000064DC]
		// Unknown
		// Write<uint32>((appBaseAddr + 0x20872F + 4), (enable) ? newOff : off); // dmc3.exe+20872F - 44 8B 84 83 DC640000 - MOV R8D,[RBX+RAX*4+000064DC]
		// Write<uint32>((appBaseAddr + 0x20E351 + 4), (enable) ? newOff : off); // dmc3.exe+20E351 - 44 8B 84 83 DC640000 - MOV R8D,[RBX+RAX*4+000064DC]
		// Write<uint32>((appBaseAddr + 0x20E37F + 4), (enable) ? newOff : off); // dmc3.exe+20E37F - 44 8B 84 83 DC640000 - MOV R8D,[RBX+RAX*4+000064DC]
	}
	// 0x64E0
	{
		constexpr auto off = offsetof(ActorData, weaponLevels[1]);
		constexpr auto newOff = offsetof(ActorData, newWeaponLevels[1]);
		static_assert(off == 0x64E0);
		// Init Actor Dante
		Write<uint32>((appBaseAddr + 0x217C10 + 2), (enable) ? newOff : off); // dmc3.exe+217C10 - 89 81 E0640000 - MOV [RCX+000064E0],EAX
		// Init Actor Vergil
		Write<uint32>((appBaseAddr + 0x223D2E + 2), (enable) ? newOff : off); // dmc3.exe+223D2E - 89 81 E0640000 - MOV [RCX+000064E0],EAX
		// func_2198D0
		Write<uint32>((appBaseAddr + 0x2198EF + 2), (enable) ? newOff : off); // dmc3.exe+2198EF - 8B 81 E0640000 - MOV EAX,[RCX+000064E0]
		// func_2241F0
		Write<uint32>((appBaseAddr + 0x22420F + 2), (enable) ? newOff : off); // dmc3.exe+22420F - 8B 81 E0640000 - MOV EAX,[RCX+000064E0]
	}
	// 0x64E4
	{
		constexpr auto off = offsetof(ActorData, weaponLevels[2]);
		constexpr auto newOff = offsetof(ActorData, newWeaponLevels[2]);
		static_assert(off == 0x64E4);
		// Init Actor Dante
		Write<uint32>((appBaseAddr + 0x217C23 + 2), (enable) ? newOff : off); // dmc3.exe+217C23 - 89 81 E4640000 - MOV [RCX+000064E4],EAX
		// Init Actor Bob
		Write<uint32>((appBaseAddr + 0x226F6B + 3), (enable) ? newOff : off); // dmc3.exe+226F6B - 4C 89 A1 E4640000 - MOV [RCX+000064E4],R12
		// Init Actor Lady
		Write<uint32>((appBaseAddr + 0x2196C2 + 3), (enable) ? newOff : off); // dmc3.exe+2196C2 - 4C 89 A1 E4640000 - MOV [RCX+000064E4],R12
		// Init Actor Vergil
		Write<uint32>((appBaseAddr + 0x223D37 + 2), (enable) ? newOff : off); // dmc3.exe+223D37 - 89 81 E4640000 - MOV [RCX+000064E4],EAX
		// func_2198D0
		Write<uint32>((appBaseAddr + 0x219902 + 2), (enable) ? newOff : off); // dmc3.exe+219902 - 8B 81 E4640000 - MOV EAX,[RCX+000064E4]
		// func_2241F0
		Write<uint32>((appBaseAddr + 0x224222 + 2), (enable) ? newOff : off); // dmc3.exe+224222 - 8B 81 E4640000 - MOV EAX,[RCX+000064E4]
	}
	// 0x64E8
	{
		constexpr auto off = offsetof(ActorData, weaponLevels[3]);
		constexpr auto newOff = offsetof(ActorData, newWeaponLevels[3]);
		static_assert(off == 0x64E8);
		// Init Actor Dante
		Write<uint32>((appBaseAddr + 0x217C36 + 2), (enable) ? newOff : off); // dmc3.exe+217C36 - 89 81 E8640000 - MOV [RCX+000064E8],EAX
		// Init Actor Vergil
		Write<uint32>((appBaseAddr + 0x223D40 + 2), (enable) ? newOff : off); // dmc3.exe+223D40 - 89 81 E8640000 - MOV [RCX+000064E8],EAX
		// func_2198D0
		Write<uint32>((appBaseAddr + 0x219915 + 2), (enable) ? newOff : off); // dmc3.exe+219915 - 8B 81 E8640000 - MOV EAX,[RCX+000064E8]
		// func_2241F0
		Write<uint32>((appBaseAddr + 0x224235 + 2), (enable) ? newOff : off); // dmc3.exe+224235 - 8B 81 E8640000 - MOV EAX,[RCX+000064E8]
	}
	// 0x64EC
	{
		constexpr auto off = offsetof(ActorData, weaponLevels[4]);
		constexpr auto newOff = offsetof(ActorData, newWeaponLevels[4]);
		static_assert(off == 0x64EC);
		// Init Actor Dante
		Write<uint32>((appBaseAddr + 0x217C49 + 2), (enable) ? newOff : off); // dmc3.exe+217C49 - 89 81 EC640000 - MOV [RCX+000064EC],EAX
		// Init Actor Bob
		Write<uint32>((appBaseAddr + 0x226F72 + 3), (enable) ? newOff : off); // dmc3.exe+226F72 - 44 89 A1 EC640000 - MOV [RCX+000064EC],R12D
		// Init Actor Lady
		Write<uint32>((appBaseAddr + 0x2196C9 + 3), (enable) ? newOff : off); // dmc3.exe+2196C9 - 44 89 A1 EC640000 - MOV [RCX+000064EC],R12D
		// Init Actor Vergil
		Write<uint32>((appBaseAddr + 0x223D49 + 2), (enable) ? newOff : off); // dmc3.exe+223D49 - 89 81 EC640000 - MOV [RCX+000064EC],EAX
		// func_2198D0
		Write<uint32>((appBaseAddr + 0x219928 + 2), (enable) ? newOff : off); // dmc3.exe+219928 - 8B 81 EC640000 - MOV EAX,[RCX+000064EC]
		// func_2241F0
		Write<uint32>((appBaseAddr + 0x224248 + 2), (enable) ? newOff : off); // dmc3.exe+224248 - 8B 81 EC640000 - MOV EAX,[RCX+000064EC]
	}
	// 0x64F4
	{
		constexpr auto off = offsetof(ActorData, weaponTimers[0]);
		constexpr auto newOff = offsetof(ActorData, newWeaponTimers[0]);
		static_assert(off == 0x64F4);
		// Register Weapons
		Write<uint32>((appBaseAddr + 0x1DEF3D + 3), (enable) ? newOff : off); // dmc3.exe+1DEF3D - 4C 89 BB F4640000 - MOV [RBX+000064F4],R15
		// Other
		Write<uint32>((appBaseAddr + 0x2063C2 + 3), (enable) ? newOff : off); // dmc3.exe+2063C2 - C7 84 BB F4640000 00002041 - MOV [RBX+RDI*4+000064F4],41200000
		Write<uint32>((appBaseAddr + 0x206527 + 3), (enable) ? newOff : off); // dmc3.exe+206527 - C7 84 83 F4640000 00002042 - MOV [RBX+RAX*4+000064F4],42200000
		Write<uint32>((appBaseAddr + 0x210CD8 + 3), (enable) ? newOff : off); // dmc3.exe+210CD8 - 89 8C 93 F4640000 - MOV [RBX+RDX*4+000064F4],ECX
		Write<uint32>((appBaseAddr + 0x21560F + 3), (enable) ? newOff : off); // dmc3.exe+21560F - 48 8D 87 F4640000 - LEA RAX,[RDI+000064F4]
		Write<uint32>((appBaseAddr + 0x21577B + 3), (enable) ? newOff : off); // dmc3.exe+21577B - C7 84 9F F4640000 00009644 - MOV [RDI+RBX*4+000064F4],44960000
		Write<uint32>((appBaseAddr + 0x21F297 + 3), (enable) ? newOff : off); // dmc3.exe+21F297 - 89 8C 93 F4640000 - MOV [RBX+RDX*4+000064F4],ECX
		Write<uint32>((appBaseAddr + 0x22290C + 3), (enable) ? newOff : off); // dmc3.exe+22290C - 48 8D 87 F4640000 - LEA RAX,[RDI+000064F4]
	}
	// 0x64FC
	{
		constexpr auto off = offsetof(ActorData, weaponTimers[2]);
		constexpr auto newOff = offsetof(ActorData, newWeaponTimers[2]);
		static_assert(off == 0x64FC);
		// Register Weapons
		Write<uint32>((appBaseAddr + 0x1DEF44 + 3), (enable) ? newOff : off); // dmc3.exe+1DEF44 - 4C 89 BB FC640000 - MOV [RBX+000064FC],R15
	}
	// 0x6504
	{
		constexpr auto off = offsetof(ActorData, weaponTimers[4]);
		constexpr auto newOff = offsetof(ActorData, newWeaponTimers[4]);
		static_assert(off == 0x6504);
		// Register Weapons
		Write<uint32>((appBaseAddr + 0x1DEF4B + 3), (enable) ? newOff : off); // dmc3.exe+1DEF4B - 44 89 BB 04650000 - MOV [RBX+00006504],R15D
	}
	// 0x6950
	{
		constexpr auto off = offsetof(ActorData, bodyPartData[0][0]);
		constexpr auto newOff = offsetof(ActorData, newBodyPartData[0][0]);
		static_assert(off == 0x6950);
		// func_1DDAF0
		Write<uint32>((appBaseAddr + 0x1DDD63 + 3), (enable) ? newOff : off); // dmc3.exe+1DDD63 - 48 8D 8E 50690000 - LEA RCX,[RSI+00006950]
		// func_1DE280
		Write<uint32>((appBaseAddr + 0x1DE2F4 + 3), (enable) ? newOff : off); // dmc3.exe+1DE2F4 - 48 8D 8F 50690000 - LEA RCX,[RDI+00006950]
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF4CE + 3), (enable) ? newOff : off); // dmc3.exe+1EF4CE - 49 8D 8D 50690000 - LEA RCX,[R13+00006950]
		// Other
		Write<uint32>((appBaseAddr + 0x1EF90E + 3), (enable) ? newOff : off); // dmc3.exe+1EF90E - 48 8D 8B 50690000 - LEA RCX,[RBX+00006950]
		Write<uint32>((appBaseAddr + 0x1EF947 + 3), (enable) ? newOff : off); // dmc3.exe+1EF947 - 48 81 C1 50690000 - ADD RCX,00006950
		Write<uint32>((appBaseAddr + 0x1EFAC0 + 3), (enable) ? newOff : off); // dmc3.exe+1EFAC0 - 48 81 C1 50690000 - ADD RCX,00006950
		Write<uint32>((appBaseAddr + 0x1EFADE + 3), (enable) ? newOff : off); // dmc3.exe+1EFADE - 48 8D 8B 50690000 - LEA RCX,[RBX+00006950]
		Write<uint32>((appBaseAddr + 0x1EFB0E + 3), (enable) ? newOff : off); // dmc3.exe+1EFB0E - 48 81 C3 50690000 - ADD RBX,00006950
		Write<uint32>((appBaseAddr + 0x1EFC62 + 3), (enable) ? newOff : off); // dmc3.exe+1EFC62 - 48 81 C1 50690000 - ADD RCX,00006950
		Write<uint32>((appBaseAddr + 0x1EFD36 + 3), (enable) ? newOff : off); // dmc3.exe+1EFD36 - 48 81 C1 50690000 - ADD RCX,00006950
		Write<uint32>((appBaseAddr + 0x1EFFFE + 3), (enable) ? newOff : off); // dmc3.exe+1EFFFE - 48 81 C1 50690000 - ADD RCX,00006950
		Write<uint32>((appBaseAddr + 0x1F0052 + 3), (enable) ? newOff : off); // dmc3.exe+1F0052 - 48 81 C1 50690000 - ADD RCX,00006950
		Write<uint32>((appBaseAddr + 0x1F906A + 3), (enable) ? newOff : off); // dmc3.exe+1F906A - 48 81 C1 50690000 - ADD RCX,00006950
		Write<uint32>((appBaseAddr + 0x1F9080 + 3), (enable) ? newOff : off); // dmc3.exe+1F9080 - 48 8D 97 50690000 - LEA RDX,[RDI+00006950]
		// Unknown
		// Write<uint32>((appBaseAddr + 0x1F0446 + 3), (enable) ? newOff : off); // dmc3.exe+1F0446 - 48 81 C1 50690000 - ADD RCX,00006950
	}
	// 0x6A70
	{
		constexpr auto off = offsetof(ActorData, bodyPartData[0][1]);
		constexpr auto newOff = offsetof(ActorData, newBodyPartData[0][1]);
		static_assert(off == 0x6A70);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF477 + 3), (enable) ? newOff : off); // dmc3.exe+1EF477 - 49 8D 8D 706A0000 - LEA RCX,[R13+00006A70]
		// Other
		Write<uint32>((appBaseAddr + 0xB9C7C + 3), (enable) ? newOff : off); // dmc3.exe+B9C7C - 4C 8D B7 706A0000 - LEA R14,[RDI+00006A70]
		Write<uint32>((appBaseAddr + 0xCA512 + 3), (enable) ? newOff : off); // dmc3.exe+CA512 - 48 8D 8E 706A0000 - LEA RCX,[RSI+00006A70]
		Write<uint32>((appBaseAddr + 0xCA62B + 3), (enable) ? newOff : off); // dmc3.exe+CA62B - 48 8D 8E 706A0000 - LEA RCX,[RSI+00006A70]
		Write<uint32>((appBaseAddr + 0xCA97E + 3), (enable) ? newOff : off); // dmc3.exe+CA97E - 48 8D 8D 706A0000 - LEA RCX,[RBP+00006A70]
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
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF3AE + 3), (enable) ? newOff : off); // dmc3.exe+1EF3AE - 49 8D 8D 906B0000 - LEA RCX,[R13+00006B90]
	}
	// 0x6CB0
	{
		constexpr auto off = offsetof(ActorData, bodyPartData[1][1]);
		constexpr auto newOff = offsetof(ActorData, newBodyPartData[1][1]);
		static_assert(off == 0x6CB0);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF357 + 3), (enable) ? newOff : off); // dmc3.exe+1EF357 - 49 8D 8D B06C0000 - LEA RCX,[R13+00006CB0]
	}
	// 0x6DD0
	{
		constexpr auto off = offsetof(ActorData, bodyPartData[2][0]);
		constexpr auto newOff = offsetof(ActorData, newBodyPartData[2][0]);
		static_assert(off == 0x6DD0);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF282 + 3), (enable) ? newOff : off); // dmc3.exe+1EF282 - 49 8D 8D D06D0000 - LEA RCX,[R13+00006DD0]
	}
	// 0x6EF0
	{
		constexpr auto off = offsetof(ActorData, bodyPartData[2][1]);
		constexpr auto newOff = offsetof(ActorData, newBodyPartData[2][1]);
		static_assert(off == 0x6EF0);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF22B + 3), (enable) ? newOff : off); // dmc3.exe+1EF22B - 49 8D 8D F06E0000 - LEA RCX,[R13+00006EF0]
	}
	// 0x7540
	{
		constexpr auto off = offsetof(ActorData, submodelData[0]);
		constexpr auto newOff = offsetof(ActorData, newSubmodelData[0]);
		static_assert(off == 0x7540);
		// Update Actor Dante
		Write<uint32>((appBaseAddr + 0x2132C5 + 3), (enable) ? newOff : off); // dmc3.exe+2132C5 - 49 81 C4 40750000 - ADD R12,00007540
		Write<uint32>((appBaseAddr + 0x2136BF + 3), (enable) ? newOff : off); // dmc3.exe+2136BF - 49 81 C4 40750000 - ADD R12,00007540
		Write<uint32>((appBaseAddr + 0x213ACD + 3), (enable) ? newOff : off); // dmc3.exe+213ACD - 49 81 C4 40750000 - ADD R12,00007540
		Write<uint32>((appBaseAddr + 0x213D57 + 3), (enable) ? newOff : off); // dmc3.exe+213D57 - 49 81 C4 40750000 - ADD R12,00007540
		Write<uint32>((appBaseAddr + 0x21424F + 3), (enable) ? newOff : off); // dmc3.exe+21424F - 49 81 C4 40750000 - ADD R12,00007540
		Write<uint32>((appBaseAddr + 0x21463A + 3), (enable) ? newOff : off); // dmc3.exe+21463A - 49 81 C4 40750000 - ADD R12,00007540
		Write<uint32>((appBaseAddr + 0x2148B6 + 3), (enable) ? newOff : off); // dmc3.exe+2148B6 - 49 81 C4 40750000 - ADD R12,00007540
		// Update Actor Bob
		Write<uint32>((appBaseAddr + 0x2260CA + 3), (enable) ? newOff : off); // dmc3.exe+2260CA - 49 8D B6 40750000 - LEA RSI,[R14+00007540]
		Write<uint32>((appBaseAddr + 0x22648D + 3), (enable) ? newOff : off); // dmc3.exe+22648D - 48 81 C7 40750000 - ADD RDI,00007540
		Write<uint32>((appBaseAddr + 0x22669C + 3), (enable) ? newOff : off); // dmc3.exe+22669C - 48 81 C7 40750000 - ADD RDI,00007540
		Write<uint32>((appBaseAddr + 0x2268A2 + 3), (enable) ? newOff : off); // dmc3.exe+2268A2 - 48 81 C7 40750000 - ADD RDI,00007540
		// Write<uint32>((appBaseAddr + 0x226A03 + 3), (enable) ? newOff : off); // dmc3.exe+226A03 - 48 81 C7 40750000 - ADD RDI,00007540
		Write<uint32>((appBaseAddr + 0x226C92 + 3), (enable) ? newOff : off); // dmc3.exe+226C92 - 49 8D 8E 40750000 - LEA RCX,[R14+00007540]
		// Update Actor Lady
		Write<uint32>((appBaseAddr + 0x2193C2 + 3), (enable) ? newOff : off); // dmc3.exe+2193C2 - 48 8D B5 40750000 - LEA RSI,[RBP+00007540]
		// Update Actor Vergil
		Write<uint32>((appBaseAddr + 0x220F35 + 3), (enable) ? newOff : off); // dmc3.exe+220F35 - 49 81 C6 40750000 - ADD R14,00007540
		Write<uint32>((appBaseAddr + 0x2212C8 + 3), (enable) ? newOff : off); // dmc3.exe+2212C8 - 49 81 C6 40750000 - ADD R14,00007540
		Write<uint32>((appBaseAddr + 0x2216C3 + 3), (enable) ? newOff : off); // dmc3.exe+2216C3 - 49 81 C6 40750000 - ADD R14,00007540
		Write<uint32>((appBaseAddr + 0x22195B + 3), (enable) ? newOff : off); // dmc3.exe+22195B - 49 81 C6 40750000 - ADD R14,00007540
		Write<uint32>((appBaseAddr + 0x221BC4 + 4), (enable) ? newOff : off); // dmc3.exe+221BC4 - 4D 8D B4 24 40750000 - LEA R14,[R12+00007540]
		// Update Model Dante
		Write<uint32>((appBaseAddr + 0x214FAB + 3), (enable) ? newOff : off); // dmc3.exe+214FAB - 4D 8D AE 40750000 - LEA R13,[R14+00007540]
		Write<uint32>((appBaseAddr + 0x2152A1 + 3), (enable) ? newOff : off); // dmc3.exe+2152A1 - 49 8D B6 40750000 - LEA RSI,[R14+00007540]
		// Update Model Vergil
		Write<uint32>((appBaseAddr + 0x22221B + 3), (enable) ? newOff : off); // dmc3.exe+22221B - 4C 8D AD 40750000 - LEA R13,[RBP+00007540]
		Write<uint32>((appBaseAddr + 0x222449 + 3), (enable) ? newOff : off); // dmc3.exe+222449 - 4C 8D AD 40750000 - LEA R13,[RBP+00007540]
		Write<uint32>((appBaseAddr + 0x222702 + 3), (enable) ? newOff : off); // dmc3.exe+222702 - 48 8D B5 40750000 - LEA RSI,[RBP+00007540]
		// func_1DD480
		Write<uint32>((appBaseAddr + 0x1DD4D2 + 3), (enable) ? newOff : off); // dmc3.exe+1DD4D2 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		// func_1DDE40
		Write<uint32>((appBaseAddr + 0x1DDF1E + 3), (enable) ? newOff : off); // dmc3.exe+1DDF1E - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		// func_1DE160
		Write<uint32>((appBaseAddr + 0x1DE24C + 3), (enable) ? newOff : off); // dmc3.exe+1DE24C - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		// func_211F20
		Write<uint32>((appBaseAddr + 0x211F4D + 3), (enable) ? newOff : off); // dmc3.exe+211F4D - 4C 8D B9 40750000 - LEA R15,[RCX+00007540]
		Write<uint32>((appBaseAddr + 0x211F68 + 3), (enable) ? newOff : off); // dmc3.exe+211F68 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		// Other
		Write<uint32>((appBaseAddr + 0x1DD642 + 3), (enable) ? newOff : off); // dmc3.exe+1DD642 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x1DD7F2 + 3), (enable) ? newOff : off); // dmc3.exe+1DD7F2 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x1DD9A2 + 3), (enable) ? newOff : off); // dmc3.exe+1DD9A2 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x1DDFF0 + 3), (enable) ? newOff : off); // dmc3.exe+1DDFF0 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x1DE126 + 3), (enable) ? newOff : off); // dmc3.exe+1DE126 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
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
		Write<uint32>((appBaseAddr + 0x225BB8 + 3), (enable) ? newOff : off); // dmc3.exe+225BB8 - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x225C2A + 3), (enable) ? newOff : off); // dmc3.exe+225C2A - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x225CCF + 3), (enable) ? newOff : off); // dmc3.exe+225CCF - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x225D3B + 3), (enable) ? newOff : off); // dmc3.exe+225D3B - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x226D9F + 3), (enable) ? newOff : off); // dmc3.exe+226D9F - 48 8D 91 40750000 - LEA RDX,[RCX+00007540]
		Write<uint32>((appBaseAddr + 0x226DE9 + 3), (enable) ? newOff : off); // dmc3.exe+226DE9 - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x226E56 + 3), (enable) ? newOff : off); // dmc3.exe+226E56 - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x2272D8 + 3), (enable) ? newOff : off); // dmc3.exe+2272D8 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x227370 + 3), (enable) ? newOff : off); // dmc3.exe+227370 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x2273A8 + 3), (enable) ? newOff : off); // dmc3.exe+2273A8 - 48 81 C1 40750000 - ADD RCX,00007540
		// Unknown
		// Write<uint32>((appBaseAddr + 0x180ABD + 3), (enable) ? newOff : off); // dmc3.exe+180ABD - 48 8D 8F 40750000 - LEA RCX,[RDI+00007540]
		// Write<uint32>((appBaseAddr + 0x225AEE + 3), (enable) ? newOff : off); // dmc3.exe+225AEE - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		// Write<uint32>((appBaseAddr + 0x225B50 + 3), (enable) ? newOff : off); // dmc3.exe+225B50 - 48 81 C1 40750000 - ADD RCX,00007540
		// Write<uint32>((appBaseAddr + 0x226EC3 + 3), (enable) ? newOff : off); // dmc3.exe+226EC3 - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
	}
	// 0x7548
	{
		constexpr auto off = (offsetof(ActorData, submodelData[0]) + 8);
		constexpr auto newOff = (offsetof(ActorData, newSubmodelData[0]) + 8);
		static_assert(off == 0x7548);
		// Update Actor Vergil
		Write<uint32>((appBaseAddr + 0x221D07 + 3), (enable) ? newOff : off); // dmc3.exe+221D07 - 48 81 C7 48750000 - add rdi,00007548
	}
	// 0x9AC0
	{
		constexpr auto off = offsetof(ActorData, submodelInit[0]);
		constexpr auto newOff = offsetof(ActorData, newSubmodelInit[0]);
		static_assert(off == 0x9AC0);
		// Update Actor Dante
		Write<uint32>((appBaseAddr + 0x212C0D + 3), (enable) ? newOff : off); // dmc3.exe+212C0D - 44 89 B9 C09A0000 - MOV [RCX+00009AC0],R15D
		Write<uint32>((appBaseAddr + 0x21338B + 4), (enable) ? newOff : off); // dmc3.exe+21338B - 42 C6 84 2E C09A0000 01 - MOV BYTE PTR [RSI+R13+00009AC0],01
		Write<uint32>((appBaseAddr + 0x213709 + 3), (enable) ? newOff : off); // dmc3.exe+213709 - C6 84 37 C09A0000 01 - MOV BYTE PTR [RDI+RSI+00009AC0],01
		Write<uint32>((appBaseAddr + 0x213B1D + 3), (enable) ? newOff : off); // dmc3.exe+213B1D - C6 84 37 C09A0000 01 - MOV BYTE PTR [RDI+RSI+00009AC0],01
		Write<uint32>((appBaseAddr + 0x213D9E + 4), (enable) ? newOff : off); // dmc3.exe+213D9E - 41 C6 84 36 C09A0000 01 - MOV BYTE PTR [R14+RSI+00009AC0],01
		Write<uint32>((appBaseAddr + 0x214315 + 4), (enable) ? newOff : off); // dmc3.exe+214315 - 42 C6 84 2E C09A0000 01 - MOV BYTE PTR [RSI+R13+00009AC0],01
		Write<uint32>((appBaseAddr + 0x2146FC + 4), (enable) ? newOff : off); // dmc3.exe+2146FC - 42 C6 84 2E C09A0000 01 - MOV BYTE PTR [RSI+R13+00009AC0],01
		Write<uint32>((appBaseAddr + 0x214978 + 4), (enable) ? newOff : off); // dmc3.exe+214978 - 42 C6 84 36 C09A0000 01 - MOV BYTE PTR [RSI+R14+00009AC0],01
		// Update Actor Bob
		Write<uint32>((appBaseAddr + 0x225D8A + 2), (enable) ? newOff : off); // dmc3.exe+225D8A - C7 81 C09A0000 00000000 - MOV [RCX+00009AC0],00000000
		Write<uint32>((appBaseAddr + 0x226107 + 3), (enable) ? newOff : off); // dmc3.exe+226107 - 41 C6 86 C09A0000 01 - MOV BYTE PTR [R14+00009AC0],01
		Write<uint32>((appBaseAddr + 0x2264D6 + 4), (enable) ? newOff : off); // dmc3.exe+2264D6 - 42 C6 84 36 C09A0000 01 - MOV BYTE PTR [RSI+R14+00009AC0],01
		Write<uint32>((appBaseAddr + 0x2266EB + 4), (enable) ? newOff : off); // dmc3.exe+2266EB - 43 C6 84 34 C09A0000 01 - MOV BYTE PTR [R12+R14+00009AC0],01
		Write<uint32>((appBaseAddr + 0x2268F7 + 4), (enable) ? newOff : off); // dmc3.exe+2268F7 - 43 C6 84 34 C09A0000 01 - MOV BYTE PTR [R12+R14+00009AC0],01
		// Write<uint32>((appBaseAddr + 0x226A43 + 4), (enable) ? newOff : off); // dmc3.exe+226A43 - 42 C6 84 36 C09A0000 01 - MOV BYTE PTR [RSI+R14+00009AC0],01
		// Update Actor Vergil
		Write<uint32>((appBaseAddr + 0x22098E + 3), (enable) ? newOff : off); // dmc3.exe+22098E - 44 89 B1 C09A0000 - MOV [RCX+00009AC0],R14D
		Write<uint32>((appBaseAddr + 0x22116B + 4), (enable) ? newOff : off); // dmc3.exe+22116B - 42 88 9C 20 C09A0000 - MOV [RAX+R12+00009AC0],BL
		Write<uint32>((appBaseAddr + 0x22136C + 4), (enable) ? newOff : off); // dmc3.exe+22136C - 43 C6 84 27 C09A0000 01 - MOV BYTE PTR [R15+R12+00009AC0],01
		Write<uint32>((appBaseAddr + 0x221770 + 4), (enable) ? newOff : off); // dmc3.exe+221770 - 43 C6 84 27 C09A0000 01 - MOV BYTE PTR [R15+R12+00009AC0],01
		Write<uint32>((appBaseAddr + 0x221A0A + 4), (enable) ? newOff : off); // dmc3.exe+221A0A - 42 C6 84 25 C09A0000 01 - MOV BYTE PTR [RBP+R12+00009AC0],01
		Write<uint32>((appBaseAddr + 0x221DF9 + 4), (enable) ? newOff : off); // dmc3.exe+221DF9 - 42 C6 84 25 C09A0000 01 - MOV BYTE PTR [RBP+R12+00009AC0],01
		// Update Model Dante
		Write<uint32>((appBaseAddr + 0x214FE3 + 3), (enable) ? newOff : off); // dmc3.exe+214FE3 - 41 C6 86 C09A0000 01 - MOV BYTE PTR [R14+00009AC0],01
		Write<uint32>((appBaseAddr + 0x2152D6 + 3), (enable) ? newOff : off); // dmc3.exe+2152D6 - 41 C6 86 C09A0000 01 - MOV BYTE PTR [R14+00009AC0],01
		// Update Model Vergil
		Write<uint32>((appBaseAddr + 0x222253 + 2), (enable) ? newOff : off); // dmc3.exe+222253 - C6 85 C09A0000 01 - MOV BYTE PTR [RBP+00009AC0],01
		Write<uint32>((appBaseAddr + 0x222481 + 2), (enable) ? newOff : off); // dmc3.exe+222481 - C6 85 C09A0000 01 - MOV BYTE PTR [RBP+00009AC0],01
		Write<uint32>((appBaseAddr + 0x222737 + 2), (enable) ? newOff : off); // dmc3.exe+222737 - C6 85 C09A0000 01 - MOV BYTE PTR [RBP+00009AC0],01
		// func_211F20
		Write<uint32>((appBaseAddr + 0x211F3A + 3), (enable) ? newOff : off); // dmc3.exe+211F3A - 48 8D B9 C09A0000 - LEA RDI,[RCX+00009AC0]
		// Other
		Write<uint32>((appBaseAddr + 0x2203BD + 3), (enable) ? newOff : off); // dmc3.exe+2203BD - 48 8D B1 C09A0000 - LEA RSI,[RCX+00009AC0]
		Write<uint32>((appBaseAddr + 0x225997 + 3), (enable) ? newOff : off); // dmc3.exe+225997 - 48 8D 99 C09A0000 - LEA RBX,[RCX+00009AC0]
	}
	// 0x9AC4
	{
		constexpr auto off = offsetof(ActorData, submodelInit[4]);
		constexpr auto newOff = offsetof(ActorData, newSubmodelInit[4]);
		static_assert(off == 0x9AC4);
		// Update Actor Dante
		Write<uint32>((appBaseAddr + 0x212C14 + 3), (enable) ? newOff : off); // dmc3.exe+212C14 - 44 88 B9 C49A0000 - MOV [RCX+00009AC4],R15L
		// Update Actor Bob
		Write<uint32>((appBaseAddr + 0x225D97 + 2), (enable) ? newOff : off); // dmc3.exe+225D97 - C6 81 C49A0000 00 - MOV BYTE PTR [RCX+00009AC4],00
		// Update Actor Vergil
		Write<uint32>((appBaseAddr + 0x220997 + 3), (enable) ? newOff : off); // dmc3.exe+220997 - 44 88 B1 C49A0000 - MOV [RCX+00009AC4],R14L
	}
	// 0x9AC8
	{
		constexpr auto off = offsetof(ActorData, submodelInit[8]);
		constexpr auto newOff = offsetof(ActorData, newSubmodelInit[8]);
		static_assert(off == 0x9AC8);
		// Update Actor Bob
		Write<uint32>((appBaseAddr + 0x226318 + 3), (enable) ? newOff : off); // dmc3.exe+226318 - 49 89 B6 C89A0000 - MOV [R14+00009AC8],RSI
		// Update Actor Vergil
		Write<uint32>((appBaseAddr + 0x220CC4 + 4), (enable) ? newOff : off); // dmc3.exe+220CC4 - 4D 89 B4 24 C89A0000 - MOV [R12+00009AC8],R14
	}
	// 0x9AD0
	{
		constexpr auto off = offsetof(ActorDataDante, modelShadowData[0]);
		constexpr auto newOff = offsetof(ActorDataDante, newModelShadowData[0]);
		static_assert(off == 0x9AD0);
		// Update Actor Dante
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
		// Update Actor Bob
		// Write<uint32>((appBaseAddr + 0x22631F + 3), (enable) ? newOff : off); // dmc3.exe+22631F - 49 89 B6 D09A0000 - MOV [R14+00009AD0],RSI - Ignore!
		// Update Actor Vergil
		// Write<uint32>((appBaseAddr + 0x220CCF + 4), (enable) ? newOff : off); // dmc3.exe+220CCF - 4D 89 B4 24 D09A0000 - MOV [R12+00009AD0],R14 - Ignore!
		// Update Model Dante
		Write<uint32>((appBaseAddr + 0x214DED + 3), (enable) ? newOff : off); // dmc3.exe+214DED - 49 8B BE D09A0000 - MOV RDI,[R14+00009AD0]
		Write<uint32>((appBaseAddr + 0x214DFA + 3), (enable) ? newOff : off); // dmc3.exe+214DFA - 49 8D 8E D09A0000 - LEA RCX,[R14+00009AD0]
		// func_1DD480
		Write<uint32>((appBaseAddr + 0x1DD4FD + 3), (enable) ? newOff : off); // dmc3.exe+1DD4FD - 48 8D 8B D09A0000 - LEA RCX,[RBX+00009AD0]
		// func_1DDE40
		Write<uint32>((appBaseAddr + 0x1DDEFF + 3), (enable) ? newOff : off); // dmc3.exe+1DDEFF - 48 8D 8B D09A0000 - LEA RCX,[RBX+00009AD0]
		// func_211F20
		Write<uint32>((appBaseAddr + 0x211FC7 + 3), (enable) ? newOff : off); // dmc3.exe+211FC7 - 48 8D B3 D09A0000 - LEA RSI,[RBX+00009AD0]
		Write<uint32>((appBaseAddr + 0x211FF8 + 3), (enable) ? newOff : off); // dmc3.exe+211FF8 - 48 81 C1 D09A0000 - ADD RCX,00009AD0
		// Other
		Write<uint32>((appBaseAddr + 0x218999 + 3), (enable) ? newOff : off); // dmc3.exe+218999 - 48 81 C1 D09A0000 - ADD RCX,00009AD0
		Write<uint32>((appBaseAddr + 0x218EAC + 3), (enable) ? newOff : off); // dmc3.exe+218EAC - 48 8D 8F D09A0000 - LEA RCX,[RDI+00009AD0]
	}
	// 0x9AF0
	{
		constexpr auto off = offsetof(ActorDataVergil, modelShadowData[0]);
		constexpr auto newOff = offsetof(ActorDataVergil, newModelShadowData[0]);
		static_assert(off == 0x9AF0);
		// Update Actor Vergil
		Write<uint32>((appBaseAddr + 0x220ED2 + 4), (enable) ? newOff : off); // dmc3.exe+220ED2 - 4A 8B BC 23 F09A0000 - MOV RDI,[RBX+R12+00009AF0]
		Write<uint32>((appBaseAddr + 0x220EDD + 3), (enable) ? newOff : off); // dmc3.exe+220EDD - 48 8D 8B F09A0000 - LEA RCX,[RBX+00009AF0]
		Write<uint32>((appBaseAddr + 0x221262 + 4), (enable) ? newOff : off); // dmc3.exe+221262 - 4A 8B BC 23 F09A0000 - MOV RDI,[RBX+R12+00009AF0]
		Write<uint32>((appBaseAddr + 0x22126D + 3), (enable) ? newOff : off); // dmc3.exe+22126D - 48 8D 8B F09A0000 - LEA RCX,[RBX+00009AF0]
		Write<uint32>((appBaseAddr + 0x221663 + 4), (enable) ? newOff : off); // dmc3.exe+221663 - 4A 8B BC 23 F09A0000 - MOV RDI,[RBX+R12+00009AF0]
		Write<uint32>((appBaseAddr + 0x22166E + 3), (enable) ? newOff : off); // dmc3.exe+22166E - 48 8D 8B F09A0000 - LEA RCX,[RBX+00009AF0]
		// Update Model Vergil
		Write<uint32>((appBaseAddr + 0x222073 + 3), (enable) ? newOff : off); // dmc3.exe+222073 - 48 8B B5 F09A0000 - MOV RSI,[RBP+00009AF0]
		Write<uint32>((appBaseAddr + 0x222083 + 3), (enable) ? newOff : off); // dmc3.exe+222083 - 48 8D 8D F09A0000 - LEA RCX,[RBP+00009AF0]
		// func_1DE160
		Write<uint32>((appBaseAddr + 0x1DE22D + 3), (enable) ? newOff : off); // dmc3.exe+1DE22D - 48 8D 8B F09A0000 - LEA RCX,[RBX+00009AF0]
		// Other
		Write<uint32>((appBaseAddr + 0x1DD81D + 3), (enable) ? newOff : off); // dmc3.exe+1DD81D - 48 8D 8B F09A0000 - LEA RCX,[RBX+00009AF0]
		Write<uint32>((appBaseAddr + 0x1DD9CD + 3), (enable) ? newOff : off); // dmc3.exe+1DD9CD - 48 8D 8B F09A0000 - LEA RCX,[RBX+00009AF0]
		Write<uint32>((appBaseAddr + 0x1DE107 + 3), (enable) ? newOff : off); // dmc3.exe+1DE107 - 48 8D 8B F09A0000 - LEA RCX,[RBX+00009AF0]
		Write<uint32>((appBaseAddr + 0x22045C + 3), (enable) ? newOff : off); // dmc3.exe+22045C - 48 8D B3 F09A0000 - LEA RSI,[RBX+00009AF0]
		Write<uint32>((appBaseAddr + 0x22048A + 3), (enable) ? newOff : off); // dmc3.exe+22048A - 48 81 C1 F09A0000 - ADD RCX,00009AF0
		Write<uint32>((appBaseAddr + 0x2243B1 + 3), (enable) ? newOff : off); // dmc3.exe+2243B1 - 48 81 C1 F09A0000 - ADD RCX,00009AF0
		Write<uint32>((appBaseAddr + 0x224491 + 3), (enable) ? newOff : off); // dmc3.exe+224491 - 48 81 C1 F09A0000 - ADD RCX,00009AF0
	}
	// 0x9D10
	{
		constexpr auto off = offsetof(ActorDataDante, submodelShadowData[0]);
		constexpr auto newOff = offsetof(ActorDataDante, newSubmodelShadowData[0]);
		static_assert(off == 0x9D10);
		// Update Actor Dante
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
		// Update Model Dante
		Write<uint32>((appBaseAddr + 0x21522A + 3), (enable) ? newOff : off); // dmc3.exe+21522A - 49 8B BE 109D0000 - MOV RDI,[R14+00009D10]
		Write<uint32>((appBaseAddr + 0x215237 + 3), (enable) ? newOff : off); // dmc3.exe+215237 - 49 8D 8E 109D0000 - LEA RCX,[R14+00009D10]
		// func_1DD480
		Write<uint32>((appBaseAddr + 0x1DD528 + 3), (enable) ? newOff : off); // dmc3.exe+1DD528 - 48 8D 8B 109D0000 - LEA RCX,[RBX+00009D10]
		// func_1DDE40
		Write<uint32>((appBaseAddr + 0x1DDEE0 + 3), (enable) ? newOff : off); // dmc3.exe+1DDEE0 - 48 8D 8B 109D0000 - LEA RCX,[RBX+00009D10]
		// func_211F20
		Write<uint32>((appBaseAddr + 0x211F46 + 3), (enable) ? newOff : off); // dmc3.exe+211F46 - 4C 8D B1 109D0000 - LEA R14,[RCX+00009D10]
		Write<uint32>((appBaseAddr + 0x211F9D + 3), (enable) ? newOff : off); // dmc3.exe+211F9D - 48 8D 8B 109D0000 - LEA RCX,[RBX+00009D10]
		// Other
		Write<uint32>((appBaseAddr + 0x218E88 + 3), (enable) ? newOff : off); // dmc3.exe+218E88 - 48 81 C1 109D0000 - ADD RCX,00009D10
		Write<uint32>((appBaseAddr + 0x218F20 + 3), (enable) ? newOff : off); // dmc3.exe+218F20 - 48 8D 8F 109D0000 - LEA RCX,[RDI+00009D10]
	}
	// 0x9D30
	{
		constexpr auto off = offsetof(ActorDataVergil, submodelShadowData[0]);
		constexpr auto newOff = offsetof(ActorDataVergil, newSubmodelShadowData[0]);
		static_assert(off == 0x9D30);
		// Update Actor Vergil
		Write<uint32>((appBaseAddr + 0x220FB4 + 4), (enable) ? newOff : off); // dmc3.exe+220FB4 - 4A 8B BC 23 309D0000 - MOV RDI,[RBX+R12+00009D30]
		Write<uint32>((appBaseAddr + 0x220FBF + 4), (enable) ? newOff : off); // dmc3.exe+220FBF - 49 8D 8C 24 309D0000 - LEA RCX,[R12+00009D30]
		Write<uint32>((appBaseAddr + 0x22133E + 4), (enable) ? newOff : off); // dmc3.exe+22133E - 4A 8B BC 23 309D0000 - MOV RDI,[RBX+R12+00009D30]
		Write<uint32>((appBaseAddr + 0x221349 + 3), (enable) ? newOff : off); // dmc3.exe+221349 - 48 8D 8B 309D0000 - LEA RCX,[RBX+00009D30]
		Write<uint32>((appBaseAddr + 0x221741 + 4), (enable) ? newOff : off); // dmc3.exe+221741 - 4A 8B BC 23 309D0000 - MOV RDI,[RBX+R12+00009D30]
		Write<uint32>((appBaseAddr + 0x22174C + 4), (enable) ? newOff : off); // dmc3.exe+22174C - 49 8D 8C 24 309D0000 - LEA RCX,[R12+00009D30]
		Write<uint32>((appBaseAddr + 0x2219DB + 4), (enable) ? newOff : off); // dmc3.exe+2219DB - 4A 8B BC 23 309D0000 - MOV RDI,[RBX+R12+00009D30]
		Write<uint32>((appBaseAddr + 0x2219E6 + 4), (enable) ? newOff : off); // dmc3.exe+2219E6 - 49 8D 8C 24 309D0000 - LEA RCX,[R12+00009D30]
		Write<uint32>((appBaseAddr + 0x221DAD + 4), (enable) ? newOff : off); // dmc3.exe+221DAD - 4A 8B BC 23 309D0000 - MOV RDI,[RBX+R12+00009D30]
		Write<uint32>((appBaseAddr + 0x221DB8 + 4), (enable) ? newOff : off); // dmc3.exe+221DB8 - 49 8D 8C 24 309D0000 - LEA RCX,[R12+00009D30]
		// Update Model Vergil
		Write<uint32>((appBaseAddr + 0x222698 + 3), (enable) ? newOff : off); // dmc3.exe+222698 - 48 8B B5 309D0000 - MOV RSI,[RBP+00009D30]
		Write<uint32>((appBaseAddr + 0x2226A8 + 3), (enable) ? newOff : off); // dmc3.exe+2226A8 - 48 8D 8D 309D0000 - LEA RCX,[RBP+00009D30]
		// func_1DE160
		Write<uint32>((appBaseAddr + 0x1DE20E + 3), (enable) ? newOff : off); // dmc3.exe+1DE20E - 48 8D 8B 309D0000 - LEA RCX,[RBX+00009D30]
		// Other
		Write<uint32>((appBaseAddr + 0x1DD848 + 3), (enable) ? newOff : off); // dmc3.exe+1DD848 - 48 8D 8B 309D0000 - LEA RCX,[RBX+00009D30]
		Write<uint32>((appBaseAddr + 0x1DD9F8 + 3), (enable) ? newOff : off); // dmc3.exe+1DD9F8 - 48 8D 8B 309D0000 - LEA RCX,[RBX+00009D30]
		Write<uint32>((appBaseAddr + 0x1DE0E8 + 3), (enable) ? newOff : off); // dmc3.exe+1DE0E8 - 48 8D 8B 309D0000 - LEA RCX,[RBX+00009D30]
		Write<uint32>((appBaseAddr + 0x2203D0 + 3), (enable) ? newOff : off); // dmc3.exe+2203D0 - 4C 8D B1 309D0000 - LEA R14,[RCX+00009D30]
		Write<uint32>((appBaseAddr + 0x220425 + 3), (enable) ? newOff : off); // dmc3.exe+220425 - 48 8D 8B 309D0000 - LEA RCX,[RBX+00009D30]
		Write<uint32>((appBaseAddr + 0x22441E + 3), (enable) ? newOff : off); // dmc3.exe+22441E - 48 8D 8B 309D0000 - LEA RCX,[RBX+00009D30]
		Write<uint32>((appBaseAddr + 0x22454A + 3), (enable) ? newOff : off); // dmc3.exe+22454A - 48 81 C1 309D0000 - ADD RCX,00009D30
		Write<uint32>((appBaseAddr + 0x22470E + 3), (enable) ? newOff : off); // dmc3.exe+22470E - 48 81 C1 309D0000 - ADD RCX,00009D30
	}
	// 0xA300
	{
		constexpr auto off = offsetof(ActorDataDante, devilModelPhysicsMetadataPool[0][0]);
		constexpr auto newOff = offsetof(ActorDataDante, newDevilModelPhysicsMetadataPool[0][0]);
		static_assert(off == 0xA300);
		// Create Actor Dante
		Write<uint32>((appBaseAddr + 0x1DEC79 + 3), (enable) ? newOff : off); // dmc3.exe+1DEC79 - 48 81 C2 00A30000 - ADD RDX,0000A300
		// Update Actor Dante
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
		// 0x1460
		{
			constexpr auto off = (offsetof(ActorDataDante, devilModelPhysicsMetadataPool[0][0]) / 8);
			constexpr auto newOff = (offsetof(ActorDataDante, newDevilModelPhysicsMetadataPool[0][0]) / 8);
			static_assert(off == 0x1460);
			// Update Actor Dante
			Write<uint32>((appBaseAddr + 0x2132F2 + 2), (enable) ? newOff : off); // dmc3.exe+2132F2 - 48 05 60140000 - ADD RAX,00001460
			Write<uint32>((appBaseAddr + 0x21427C + 2), (enable) ? newOff : off); // dmc3.exe+21427C - 48 05 60140000 - ADD RAX,00001460
			Write<uint32>((appBaseAddr + 0x214667 + 2), (enable) ? newOff : off); // dmc3.exe+214667 - 48 05 60140000 - ADD RAX,00001460
			Write<uint32>((appBaseAddr + 0x2148E3 + 2), (enable) ? newOff : off); // dmc3.exe+2148E3 - 48 05 60140000 - ADD RAX,00001460
		}
	}
	// 0xA540
	{
		constexpr auto off = offsetof(ActorDataDante, devilSubmodelPhysicsData[0]);
		constexpr auto newOff = offsetof(ActorDataDante, newDevilSubmodelPhysicsData[0]);
		static_assert(off == 0xA540);
		// Update Actor Dante
		Write<uint32>((appBaseAddr + 0x2133CA + 3), (enable) ? newOff : off); // dmc3.exe+2133CA - 48 8D BE 40A50000 - LEA RDI,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x213746 + 3), (enable) ? newOff : off); // dmc3.exe+213746 - 48 8D BE 40A50000 - LEA RDI,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x213B53 + 3), (enable) ? newOff : off); // dmc3.exe+213B53 - 48 8D BE 40A50000 - LEA RDI,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x213DDD + 3), (enable) ? newOff : off); // dmc3.exe+213DDD - 48 8D BE 40A50000 - LEA RDI,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x213E60 + 3), (enable) ? newOff : off); // dmc3.exe+213E60 - 48 81 C1 40A50000 - ADD RCX,0000A540
		Write<uint32>((appBaseAddr + 0x214353 + 3), (enable) ? newOff : off); // dmc3.exe+214353 - 48 8D BE 40A50000 - LEA RDI,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x214736 + 3), (enable) ? newOff : off); // dmc3.exe+214736 - 48 8D BE 40A50000 - LEA RDI,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x2149B3 + 3), (enable) ? newOff : off); // dmc3.exe+2149B3 - 48 8D BE 40A50000 - LEA RDI,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x214A24 + 3), (enable) ? newOff : off); // dmc3.exe+214A24 - 48 81 C1 40A50000 - ADD RCX,0000A540
		// func_1DD480
		Write<uint32>((appBaseAddr + 0x1DD577 + 3), (enable) ? newOff : off); // dmc3.exe+1DD577 - 48 8D 8B 40A50000 - LEA RCX,[RBX+0000A540]
		// func_1DDE40
		Write<uint32>((appBaseAddr + 0x1DDEA2 + 3), (enable) ? newOff : off); // dmc3.exe+1DDEA2 - 48 8D 8B 40A50000 - LEA RCX,[RBX+0000A540]
		// Other
		Write<uint32>((appBaseAddr + 0x2121BC + 3), (enable) ? newOff : off); // dmc3.exe+2121BC - 48 8D 8E 40A50000 - LEA RCX,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x21229E + 3), (enable) ? newOff : off); // dmc3.exe+21229E - 48 8D 8E 40A50000 - LEA RCX,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x21236C + 3), (enable) ? newOff : off); // dmc3.exe+21236C - 48 8D 8E 40A50000 - LEA RCX,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x21244E + 3), (enable) ? newOff : off); // dmc3.exe+21244E - 48 8D 8E 40A50000 - LEA RCX,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x212530 + 3), (enable) ? newOff : off); // dmc3.exe+212530 - 48 8D 8E 40A50000 - LEA RCX,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x2125FB + 3), (enable) ? newOff : off); // dmc3.exe+2125FB - 48 8D 8E 40A50000 - LEA RCX,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x212703 + 3), (enable) ? newOff : off); // dmc3.exe+212703 - 48 8D 8E 40A50000 - LEA RCX,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x216737 + 3), (enable) ? newOff : off); // dmc3.exe+216737 - 48 8D 8F 40A50000 - LEA RCX,[RDI+0000A540]
		Write<uint32>((appBaseAddr + 0x2167A7 + 3), (enable) ? newOff : off); // dmc3.exe+2167A7 - 48 8D 8F 40A50000 - LEA RCX,[RDI+0000A540]
		Write<uint32>((appBaseAddr + 0x216817 + 3), (enable) ? newOff : off); // dmc3.exe+216817 - 48 8D 8F 40A50000 - LEA RCX,[RDI+0000A540]
		Write<uint32>((appBaseAddr + 0x216887 + 3), (enable) ? newOff : off); // dmc3.exe+216887 - 48 8D 8F 40A50000 - LEA RCX,[RDI+0000A540]
		Write<uint32>((appBaseAddr + 0x2168F7 + 3), (enable) ? newOff : off); // dmc3.exe+2168F7 - 48 8D 8F 40A50000 - LEA RCX,[RDI+0000A540]
		Write<uint32>((appBaseAddr + 0x216967 + 3), (enable) ? newOff : off); // dmc3.exe+216967 - 48 8D 8F 40A50000 - LEA RCX,[RDI+0000A540]
		Write<uint32>((appBaseAddr + 0x2169D7 + 3), (enable) ? newOff : off); // dmc3.exe+2169D7 - 48 8D 8F 40A50000 - LEA RCX,[RDI+0000A540]
	}
	// 0xAA00
	{
		constexpr auto off = offsetof(ActorDataDante, devilSubmodelPhysicsLinkData[0][0]);
		constexpr auto newOff = offsetof(ActorDataDante, newDevilSubmodelPhysicsLinkData[0][0]);
		static_assert(off == 0xAA00);
		// Update Actor Dante
		Write<uint32>((appBaseAddr + 0x2137AA + 3), (enable) ? newOff : off); // dmc3.exe+2137AA - 48 8D 96 00AA0000 - LEA RDX,[RSI+0000AA00]
		Write<uint32>((appBaseAddr + 0x213BAA + 3), (enable) ? newOff : off); // dmc3.exe+213BAA - 48 8D 96 00AA0000 - LEA RDX,[RSI+0000AA00]
		Write<uint32>((appBaseAddr + 0x213E8C + 3), (enable) ? newOff : off); // dmc3.exe+213E8C - 48 8D 96 00AA0000 - LEA RDX,[RSI+0000AA00]
		Write<uint32>((appBaseAddr + 0x21439E + 3), (enable) ? newOff : off); // dmc3.exe+21439E - 48 8D 96 00AA0000 - LEA RDX,[RSI+0000AA00]
		Write<uint32>((appBaseAddr + 0x21477E + 3), (enable) ? newOff : off); // dmc3.exe+21477E - 48 8D 96 00AA0000 - LEA RDX,[RSI+0000AA00]
		Write<uint32>((appBaseAddr + 0x214A50 + 3), (enable) ? newOff : off); // dmc3.exe+214A50 - 48 8D 96 00AA0000 - LEA RDX,[RSI+0000AA00]
		// func_1DD480
		Write<uint32>((appBaseAddr + 0x1DD59B + 3), (enable) ? newOff : off); // dmc3.exe+1DD59B - 48 8D 8B 00AA0000 - LEA RCX,[RBX+0000AA00]
		// func_1DDE40
		Write<uint32>((appBaseAddr + 0x1DDE83 + 3), (enable) ? newOff : off); // dmc3.exe+1DDE83 - 48 81 C1 00AA0000 - ADD RCX,0000AA00
	}
	// 0xAAC0
	{
		constexpr auto off = (offsetof(ActorDataDante, devilSubmodelPhysicsLinkData[0][0]) + 0xC0);
		constexpr auto newOff = (offsetof(ActorDataDante, newDevilSubmodelPhysicsLinkData[0][0]) + 0xC0);
		static_assert(off == 0xAAC0);
		// Update Actor Dante
		Write<uint32>((appBaseAddr + 0x213832 + 3), (enable) ? newOff : off); // dmc3.exe+213832 - 48 8D 96 C0AA0000 - LEA RDX,[RSI+0000AAC0]
		Write<uint32>((appBaseAddr + 0x213C36 + 3), (enable) ? newOff : off); // dmc3.exe+213C36 - 48 8D 96 C0AA0000 - LEA RDX,[RSI+0000AAC0]
		Write<uint32>((appBaseAddr + 0x213EED + 3), (enable) ? newOff : off); // dmc3.exe+213EED - 48 8D 96 C0AA0000 - LEA RDX,[RSI+0000AAC0]
		Write<uint32>((appBaseAddr + 0x21442A + 3), (enable) ? newOff : off); // dmc3.exe+21442A - 48 8D 96 C0AA0000 - LEA RDX,[RSI+0000AAC0]
		Write<uint32>((appBaseAddr + 0x21480A + 3), (enable) ? newOff : off); // dmc3.exe+21480A - 48 8D 96 C0AA0000 - LEA RDX,[RSI+0000AAC0]
		Write<uint32>((appBaseAddr + 0x214AB5 + 3), (enable) ? newOff : off); // dmc3.exe+214AB5 - 48 8D 96 C0AA0000 - LEA RDX,[RSI+0000AAC0]
	}
}

void ToggleModelCountAdjustments(bool enable)
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
		Write<uint32>((appBaseAddr + 0x1DE771 + 1), (enable) ? newCount : count); // dmc3.exe+1DE771 - BD 03000000 - mov ebp,00000003
	}

	// Model Physics Metadata Pool
	{
		constexpr uint32 count = (4 * 24);
		constexpr uint32 newCount = (7 * 24);
		// Create Actor Dante
		Write<uint32>((appBaseAddr + 0x1DEC63 + 2), (enable) ? newCount : count); // dmc3.exe+1DEC63 - 41 B9 60000000 - mov r9d,00000060
		// Create Actor Bob
		Write<uint32>((appBaseAddr + 0x1DEB4A + 2), (enable) ? newCount : count); // dmc3.exe+1DEB4A - 41 B9 60000000 - MOV R9D,00000060
		// Create Actor Lady
		Write<uint32>((appBaseAddr + 0x1DEA4E + 2), (enable) ? newCount : count); // dmc3.exe+1DEA4E - 41 B9 60000000 - MOV R9D,00000060
		// Create Actor Vergil
		Write<uint32>((appBaseAddr + 0x1DE935 + 2), (enable) ? newCount : count); // dmc3.exe+1DE935 - 41 B9 60000000 - MOV R9D,00000060
		// Free
		// Handled together with Model Allocation Data.
	}

	// Model Allocation Data
	{
		constexpr uint32 count = 209;
		constexpr uint32 newCount = 512;
		// Create Actor
		Write<uint32>((appBaseAddr + 0x1DDB95 + 2), (enable) ? newCount : count); // dmc3.exe+1DDB95 - 41 B8 D1000000 - mov r8d,000000D1
		// Create Actor Dante
		Write<uint32>((appBaseAddr + 0x1DD172 + 1), (enable) ? newCount : count); // dmc3.exe+1DD172 - B8 D1000000 - mov eax,000000D1
		// Create Actor Bob
		Write<uint32>((appBaseAddr + 0x1DD3E2 + 1), (enable) ? newCount : count); // dmc3.exe+1DD3E2 - B8 D1000000 - MOV EAX,000000D1
		// Create Actor Lady
		Write<uint32>((appBaseAddr + 0x1DD242 + 1), (enable) ? newCount : count); // dmc3.exe+1DD242 - B8 D1000000 - MOV EAX,000000D1
		// Create Actor Vergil
		Write<uint32>((appBaseAddr + 0x1DD312 + 1), (enable) ? newCount : count); // dmc3.exe+1DD312 - B8 D1000000 - MOV EAX,000000D1
		// Free
		Write<uint32>((appBaseAddr + 0x1DE40E + 2), (enable) ? newCount : count); // dmc3.exe+1DE40E - 41 B8 D1000000 - mov r8d,000000D1
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
		Write<uint8>((appBaseAddr + 0x211FBD + 2), (enable) ? static_cast<uint8>(newCount) : static_cast<uint8>(count)); // dmc3.exe+211FBD - 83 FE 05 - cmp esi,05
	}

	// Model Shadow Data
	{
		constexpr uint32 count = 3;
		constexpr uint32 newCount = 6;
		// Create
		Write<uint32>((appBaseAddr + 0x1DD51C + 2), (enable) ? newCount : count); // dmc3.exe+1DD51C - 41 B8 03000000 - mov r8d,00000003
		// Free
		Write<uint32>((appBaseAddr + 0x1DDF12 + 2), (enable) ? newCount : count); // dmc3.exe+1DDF12 - 41 B8 03000000 - mov r8d,00000003
		Write<uint8>((appBaseAddr + 0x21200E + 2), (enable) ? static_cast<uint8>(newCount) : static_cast<uint8>(count)); // dmc3.exe+21200E - 83 FF 03 - cmp edi,03
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

void ToggleWeaponCountAdjustments(bool enable)
{
	LogFunction(enable);

	constexpr uint8 count = 5;
	constexpr uint8 newCount = 10;

	Write<uint8>((appBaseAddr + 0x1D91EC + 2), (enable) ? newCount : count); // dmc3.exe+1D91EC - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x1E02B2 + 2), (enable) ? newCount : count); // dmc3.exe+1E02B2 - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x1EAE1E + 2), (enable) ? newCount : count); // dmc3.exe+1EAE1E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x1F59BD + 2), (enable) ? newCount : count); // dmc3.exe+1F59BD - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x1FACAB + 2), (enable) ? newCount : count); // dmc3.exe+1FACAB - 83 F8 05 - cmp eax,05
	Write<uint8>((appBaseAddr + 0x1FAD0B + 2), (enable) ? newCount : count); // dmc3.exe+1FAD0B - 83 F8 05 - cmp eax,05
	Write<uint8>((appBaseAddr + 0x1FAD4B + 2), (enable) ? newCount : count); // dmc3.exe+1FAD4B - 83 F8 05 - cmp eax,05
	Write<uint8>((appBaseAddr + 0x1FD14F + 3), (enable) ? newCount : count); // dmc3.exe+1FD14F - 41 83 FA 05 - cmp r10d,05
	Write<uint8>((appBaseAddr + 0x1FD180 + 3), (enable) ? newCount : count); // dmc3.exe+1FD180 - 41 83 F9 05 - cmp r9d,05
	Write<uint8>((appBaseAddr + 0x1FD1DB + 2), (enable) ? newCount : count); // dmc3.exe+1FD1DB - 83 F8 05 - cmp eax,05
	Write<uint8>((appBaseAddr + 0x1FD65D + 2), (enable) ? newCount : count); // dmc3.exe+1FD65D - 83 F8 05 - cmp eax,05
	Write<uint8>((appBaseAddr + 0x20617E + 2), (enable) ? newCount : count); // dmc3.exe+20617E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x20619E + 2), (enable) ? newCount : count); // dmc3.exe+20619E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x2063AC + 2), (enable) ? newCount : count); // dmc3.exe+2063AC - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x20651C + 2), (enable) ? newCount : count); // dmc3.exe+20651C - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x2086F1 + 2), (enable) ? newCount : count); // dmc3.exe+2086F1 - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x20E30E + 2), (enable) ? newCount : count); // dmc3.exe+20E30E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x20E66E + 2), (enable) ? newCount : count); // dmc3.exe+20E66E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x20E71F + 2), (enable) ? newCount : count); // dmc3.exe+20E71F - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x210A2E + 2), (enable) ? newCount : count); // dmc3.exe+210A2E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x210C0C + 2), (enable) ? newCount : count); // dmc3.exe+210C0C - 83 FF 05 - cmp edi,05
	Write<uint8>((appBaseAddr + 0x210C50 + 2), (enable) ? newCount : count); // dmc3.exe+210C50 - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x2113DD + 2), (enable) ? newCount : count); // dmc3.exe+2113DD - 83 FF 05 - cmp edi,05
	Write<uint8>((appBaseAddr + 0x2114CC + 2), (enable) ? newCount : count); // dmc3.exe+2114CC - 83 FF 05 - cmp edi,05
	Write<uint8>((appBaseAddr + 0x2115EC + 2), (enable) ? newCount : count); // dmc3.exe+2115EC - 83 FF 05 - cmp edi,05
	Write<uint8>((appBaseAddr + 0x21168E + 2), (enable) ? newCount : count); // dmc3.exe+21168E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21172F + 2), (enable) ? newCount : count); // dmc3.exe+21172F - 83 FF 05 - cmp edi,05
	Write<uint8>((appBaseAddr + 0x21178E + 2), (enable) ? newCount : count); // dmc3.exe+21178E - 83 F9 05 - cmp ecx,05
	Write<uint32>((appBaseAddr + 0x215602 + 1), (enable) ? static_cast<uint32>(newCount) : static_cast<uint32>(count)); // dmc3.exe+215602 - BA 05000000 - mov edx,00000005
	Write<uint8>((appBaseAddr + 0x215657 + 2), (enable) ? newCount : count); // dmc3.exe+215657 - 8D 4A 05 - lea ecx,[rdx+05]
	Write<uint8>((appBaseAddr + 0x21570E + 2), (enable) ? newCount : count); // dmc3.exe+21570E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x2158BE + 2), (enable) ? newCount : count); // dmc3.exe+2158BE - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21597E + 2), (enable) ? newCount : count); // dmc3.exe+21597E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x2159EE + 2), (enable) ? newCount : count); // dmc3.exe+2159EE - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x215BDE + 2), (enable) ? newCount : count); // dmc3.exe+215BDE - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x215E8E + 2), (enable) ? newCount : count); // dmc3.exe+215E8E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x215EAE + 2), (enable) ? newCount : count); // dmc3.exe+215EAE - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x216E4E + 2), (enable) ? newCount : count); // dmc3.exe+216E4E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x217022 + 2), (enable) ? newCount : count); // dmc3.exe+217022 - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x2171F2 + 2), (enable) ? newCount : count); // dmc3.exe+2171F2 - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x217372 + 2), (enable) ? newCount : count); // dmc3.exe+217372 - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21747F + 2), (enable) ? newCount : count); // dmc3.exe+21747F - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x2181A2 + 2), (enable) ? newCount : count); // dmc3.exe+2181A2 - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x218322 + 2), (enable) ? newCount : count); // dmc3.exe+218322 - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x2183F1 + 2), (enable) ? newCount : count); // dmc3.exe+2183F1 - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21842E + 2), (enable) ? newCount : count); // dmc3.exe+21842E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x218462 + 2), (enable) ? newCount : count); // dmc3.exe+218462 - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x2184BE + 2), (enable) ? newCount : count); // dmc3.exe+2184BE - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x2184FE + 2), (enable) ? newCount : count); // dmc3.exe+2184FE - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21853E + 2), (enable) ? newCount : count); // dmc3.exe+21853E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21A46E + 2), (enable) ? newCount : count); // dmc3.exe+21A46E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21A4BE + 2), (enable) ? newCount : count); // dmc3.exe+21A4BE - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21B800 + 2), (enable) ? newCount : count); // dmc3.exe+21B800 - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21B8CE + 2), (enable) ? newCount : count); // dmc3.exe+21B8CE - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21B8FE + 2), (enable) ? newCount : count); // dmc3.exe+21B8FE - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21BBBC + 2), (enable) ? newCount : count); // dmc3.exe+21BBBC - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21BBF0 + 2), (enable) ? newCount : count); // dmc3.exe+21BBF0 - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21C0AE + 2), (enable) ? newCount : count); // dmc3.exe+21C0AE - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21C3DE + 2), (enable) ? newCount : count); // dmc3.exe+21C3DE - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21C40E + 2), (enable) ? newCount : count); // dmc3.exe+21C40E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21C6AF + 2), (enable) ? newCount : count); // dmc3.exe+21C6AF - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21C751 + 2), (enable) ? newCount : count); // dmc3.exe+21C751 - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21C84E + 2), (enable) ? newCount : count); // dmc3.exe+21C84E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21D0E0 + 2), (enable) ? newCount : count); // dmc3.exe+21D0E0 - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21D10E + 2), (enable) ? newCount : count); // dmc3.exe+21D10E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21E910 + 2), (enable) ? newCount : count); // dmc3.exe+21E910 - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21E93E + 2), (enable) ? newCount : count); // dmc3.exe+21E93E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21F232 + 2), (enable) ? newCount : count); // dmc3.exe+21F232 - 83 FF 05 - cmp edi,05
	Write<uint8>((appBaseAddr + 0x21F260 + 2), (enable) ? newCount : count); // dmc3.exe+21F260 - 83 F9 05 - cmp ecx,05
	Write<uint32>((appBaseAddr + 0x2228FF + 1), (enable) ? static_cast<uint32>(newCount) : static_cast<uint32>(count)); // dmc3.exe+2228FF - BA 05000000 - mov edx,00000005
	Write<uint8>((appBaseAddr + 0x2229AE + 2), (enable) ? newCount : count); // dmc3.exe+2229AE - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x222B52 + 2), (enable) ? newCount : count); // dmc3.exe+222B52 - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x222E9E + 2), (enable) ? newCount : count); // dmc3.exe+222E9E - 83 FE 05 - cmp esi,05
	Write<uint8>((appBaseAddr + 0x222F40 + 2), (enable) ? newCount : count); // dmc3.exe+222F40 - 83 F9 05 - cmp ecx,05
}

#pragma endregion

#pragma region Mobility

bool MobilityFunction
(
	ActorData & actorData,
	uint8 & var,
	uint8(&array)[2]
)
{
	uint8 index = (actorData.devil) ? 1 : 0;

	if (var >= array[index])
	{
		return false;
	}

	var++;

	return true;
}

bool AirHike(ActorData & actorData)
{
	if (actorData.character != CHAR_DANTE)
	{
		return false;
	}

	return MobilityFunction
	(
		actorData,
		actorData.newAirHikeCount,
		activeConfig.airHikeCount
	);
}

bool KickJump(ActorData & actorData)
{
	return MobilityFunction
	(
		actorData,
		actorData.newKickJumpCount,
		activeConfig.kickJumpCount
	);
}

bool WallHike(ActorData & actorData)
{
	return MobilityFunction
	(
		actorData,
		actorData.newWallHikeCount,
		activeConfig.wallHikeCount
	);
}

template <uint32 event>
uint32 MobilityFunction
(
	ActorData & actorData,
	uint8 action,
	uint8 & var,
	uint8(&array)[2]
)
{
	uint8 index = (actorData.devil) ? 1 : 0;

	// Required, because there is no reset when hitting the floor.
	if constexpr (event != ACTOR_EVENT_DANTE_DASH)
	{
		if (actorData.state & STATE_ON_FLOOR)
		{
			var = 0;
		}
	}

	if (var >= array[index])
	{
		return 0;
	}

	var++;

	actorData.lastAction = actorData.action;
	actorData.action = action;

	return event;
}

auto Dash
(
	ActorData & actorData,
	uint8 action
)
{
	return MobilityFunction<ACTOR_EVENT_DANTE_DASH>
	(
		actorData,
		action,
		actorData.newDashCount,
		activeConfig.dashCount
	);
}

auto SkyStar
(
	ActorData & actorData,
	uint8 action
)
{
	return MobilityFunction<ACTOR_EVENT_DANTE_SKY_STAR>
	(
		actorData,
		action,
		actorData.newSkyStarCount,
		activeConfig.skyStarCount
	);
}

auto AirTrickDante
(
	ActorData & actorData,
	uint8 action
)
{
	actorData.var_3E10[26] = (actorData.state & STATE_ON_FLOOR) ? 1 : 0;

	return MobilityFunction<ACTOR_EVENT_DANTE_AIR_TRICK>
	(
		actorData,
		action,
		actorData.newAirTrickCount,
		activeConfig.airTrickCountDante
	);
}

auto AirTrickVergil
(
	ActorData & actorData,
	uint8 action
)
{
	return MobilityFunction<ACTOR_EVENT_VERGIL_AIR_TRICK>
	(
		actorData,
		action,
		actorData.newAirTrickCount,
		activeConfig.airTrickCountVergil
	);
}

auto TrickUp
(
	ActorData & actorData,
	uint8 action
)
{
	return MobilityFunction<ACTOR_EVENT_VERGIL_TRICK_UP>
	(
		actorData,
		action,
		actorData.newTrickUpCount,
		activeConfig.trickUpCount
	);
}

auto TrickDown
(
	ActorData & actorData,
	uint8 action
)
{
	return MobilityFunction<ACTOR_EVENT_VERGIL_TRICK_DOWN>
	(
		actorData,
		action,
		actorData.newTrickDownCount,
		activeConfig.trickDownCount
	);
}

void ResetDash(ActorData & actorData)
{
	LogFunction(actorData.operator byte8 *());

	actorData.newDashCount = 0;
}

void ResetSkyStar(ActorData & actorData)
{
	LogFunction(actorData.operator byte8 *());

	actorData.newAirHikeCount    = 0;
	actorData.newKickJumpCount   = 0;
	actorData.newWallHikeCount   = 0;
	actorData.newDashCount       = 0;
	actorData.newSkyStarCount    = 0;
	actorData.newAirTrickCount   = 0;
	actorData.newTrickUpCount    = 0;
	actorData.newTrickDownCount  = 0;
	actorData.newAirStingerCount = 0;

	if (actorData.state & STATE_ON_FLOOR)
	{
		switch (actorData.character)
		{
			case CHAR_DANTE:
			{
				switch (actorData.eventData[0].event)
				{
					case ACTOR_EVENT_DANTE_AIR_TRICK:
					{
						actorData.newAirTrickCount = 1;

						break;
					}
				}

				break;
			}
			case CHAR_VERGIL:
			{
				switch (actorData.eventData[0].event)
				{
					case ACTOR_EVENT_VERGIL_AIR_TRICK:
					{
						actorData.newAirTrickCount = 1;

						break;
					}
					case ACTOR_EVENT_VERGIL_TRICK_UP:
					{
						actorData.newTrickUpCount = 1;

						break;
					}
					case ACTOR_EVENT_VERGIL_TRICK_DOWN:
					{
						actorData.newTrickDownCount = 1;

						break;
					}
				}

				break;
			}
		}
	}
}

void ToggleMobility(bool enable)
{
	LogFunction();

	static bool run = false;

	// Air Hike
	{
		WriteAddress((appBaseAddr + 0x1E9AB0), (enable) ? (appBaseAddr + 0x1E9AB6) : (appBaseAddr + 0x1E9B3A), 6);
		/*
		dmc3.exe+1E9AB0 - 0F8E 84000000  - jng dmc3.exe+1E9B3A
		dmc3.exe+1E9AB6 - 48 89 7C 24 30 - mov [rsp+30],rdi
		*/
	}
	{
		auto addr     = (appBaseAddr + 0x1E9B4E);
		auto jumpAddr = (appBaseAddr + 0x1E9B53);
		/*
		dmc3.exe+1E9B4E - BA 02000000 - mov edx,00000002
		dmc3.exe+1E9B53 - 48 8B CB    - mov rcx,rbx
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};
		constexpr byte8 sect2[] =
		{
			0x84, 0xC0,                         // test al,al
			0x0F, 0x84, 0x00, 0x00, 0x00, 0x00, // je dmc3.exe+1E9B3A
		};
		constexpr uint32 size0 = 5;
		constexpr uint32 size1 = sizeof(sect1);
		constexpr uint32 size2 = sizeof(sect2);

		if (!run)
		{
			func = CreateFunction(AirHike, jumpAddr, true, false, size0, size1, size2);
			CopyMemory(func.sect0, addr, size0, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, size1);
			CopyMemory(func.sect2, sect2, size2);
			WriteAddress((func.sect2 + 2), (appBaseAddr + 0x1E9B3A), 6);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Kick Jump
	{
		WriteAddress((appBaseAddr + 0x1EA231), (enable) ? (appBaseAddr + 0x1EA233) : (appBaseAddr + 0x1EA222), 2);
		/*
		dmc3.exe+1EA231 - 7E EF          - jle dmc3.exe+1EA222
		dmc3.exe+1EA233 - 48 89 7C 24 48 - mov [rsp+48],rdi
		*/
	}
	{
		auto addr     = (appBaseAddr + 0x1EA384);
		auto jumpAddr = (appBaseAddr + 0x1EA389);
		/*
		dmc3.exe+1EA384 - BA 03000000       - mov edx,00000003
		dmc3.exe+1EA389 - C6 83 093F0000 04 - mov byte ptr [rbx+00003F09],04
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};
		constexpr byte8 sect2[] =
		{
			0x84, 0xC0,                         // test al,al
			0x0F, 0x84, 0x00, 0x00, 0x00, 0x00, // je dmc3.exe+1EA3DF
		};
		constexpr uint32 size0 = 5;
		constexpr uint32 size1 = sizeof(sect1);
		constexpr uint32 size2 = sizeof(sect2);

		if (!run)
		{
			func = CreateFunction(KickJump, jumpAddr, true, false, size0, size1, size2);
			CopyMemory(func.sect0, addr, size0, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, size1);
			CopyMemory(func.sect2, sect2, size2);
			WriteAddress((func.sect2 + 2), (appBaseAddr + 0x1EA3DF), 6);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Wall Hike
	{
		WriteAddress((appBaseAddr + 0x1E6084), (enable) ? (appBaseAddr + 0x1E608A) : (appBaseAddr + 0x1E62B5), 6);
		/*
		dmc3.exe+1E6084 - 0F8E 2B020000     - jng dmc3.exe+1E62B5
		dmc3.exe+1E608A - 48 8B 83 E83D0000 - mov rax,[rbx+00003DE8]
		*/
	}
	{
		auto addr     = (appBaseAddr + 0x1E6549);
		auto jumpAddr = (appBaseAddr + 0x1E654E);
		/*
		dmc3.exe+1E6549 - E8 F2A1FFFF - call dmc3.exe+1E0740
		dmc3.exe+1E654E - B0 01       - mov al,01
		*/

		static Function func = {};

		constexpr byte8 sect2[] =
		{
			0x84, 0xC0,                         // test al,al
			0x0F, 0x84, 0x00, 0x00, 0x00, 0x00, // je dmc3.exe+1E64A9
			0xE8, 0x00, 0x00, 0x00, 0x00,       // call dmc3.exe+1E0740
		};
		constexpr uint32 size0 = 5;
		constexpr uint32 size2 = sizeof(sect2);

		if (!run)
		{
			func = CreateFunction(WallHike, jumpAddr, true, false, 0, 0, size2);
			CopyMemory(func.sect2, sect2, size2);
			WriteAddress((func.sect2 + 2), (appBaseAddr + 0x1E64A9), 6);
			WriteCall((func.sect2 + 8), (appBaseAddr + 0x1E0740));
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	auto CreateMobilityFunction = [](void * funcAddr)
	{
		auto jumpAddr = (appBaseAddr + 0x1E666D);

		constexpr byte8 sect1[] =
		{
			0x48, 0x8B, 0xCB, // mov rcx,rbx
			0x8A, 0x57, 0x08, // mov dl,[rdi+08]
		};
		constexpr byte8 sect2[] =
		{
			0x85, 0xC0,                         // test eax,eax
			0x0F, 0x84, 0x00, 0x00, 0x00, 0x00, // je dmc3.exe+1E64A9
			0x8B, 0xD0,                         // mov edx,eax
		};
		constexpr uint32 size1 = sizeof(sect1);
		constexpr uint32 size2 = sizeof(sect2);
		auto func = CreateFunction(funcAddr, jumpAddr, true, false, 0, size1, size2);
		CopyMemory(func.sect1, sect1, size1);
		CopyMemory(func.sect2, sect2, size2);
		WriteAddress((func.sect2 + 2), (appBaseAddr + 0x1E64A9), 6);

		return func;
	};

	// Dash
	{
		auto addr = (appBaseAddr + 0x1E66CB);
		/*
		dmc3.exe+1E66CB - 8B 8B 58630000 - mov ecx,[rbx+00006358]
		dmc3.exe+1E66D1 - 85 C9          - test ecx,ecx
		*/

		static Function func = {};

		constexpr uint32 size0 = 6;

		if (!run)
		{
			func = CreateMobilityFunction(Dash);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Sky Star
	{
		auto addr = (appBaseAddr + 0x1E6689);
		/*
		dmc3.exe+1E6689 - 83 BB 58630000 01 - cmp dword ptr [rbx+00006358],01
		dmc3.exe+1E6690 - 0F8C 13FEFFFF     - jl dmc3.exe+1E64A9
		*/

		static Function func = {};

		constexpr uint32 size0 = 7;

		if (!run)
		{
			func = CreateMobilityFunction(SkyStar);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Air Trick Dante
	{
		auto addr = (appBaseAddr + 0x1E6612);
		/*
		dmc3.exe+1E6612 - 83 BB 58630000 02 - cmp dword ptr [rbx+00006358],02
		dmc3.exe+1E6619 - 0F85 8AFEFFFF     - jne dmc3.exe+1E64A9
		*/

		static Function func = {};

		constexpr uint32 size0 = 7;

		if (!run)
		{
			func = CreateMobilityFunction(AirTrickDante);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Air Trick Vergil
	{
		auto addr = (appBaseAddr + 0x1E6842);
		/*
		dmc3.exe+1E6842 - 8B 83 643E0000 - mov eax,[rbx+00003E64]
		dmc3.exe+1E6848 - A8 01          - test al,01
		*/

		static Function func = {};

		constexpr uint32 size0 = 6;

		if (!run)
		{
			func = CreateMobilityFunction(AirTrickVergil);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Trick Up
	{
		auto addr = (appBaseAddr + 0x1E67D5);
		/*
		dmc3.exe+1E67D5 - 83 BB 58630000 01 - cmp dword ptr [rbx+00006358],01
		dmc3.exe+1E67DC - 0F8C C7FCFFFF     - jl dmc3.exe+1E64A9
		*/

		static Function func = {};

		constexpr uint32 size0 = 7;

		if (!run)
		{
			func = CreateMobilityFunction(TrickUp);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Trick Down
	{
		auto addr = (appBaseAddr + 0x1E6768);
		/*
		dmc3.exe+1E6768 - 83 BB 58630000 02 - cmp dword ptr [rbx+00006358],02
		dmc3.exe+1E676F - 0F85 34FDFFFF     - jne dmc3.exe+1E64A9
		*/

		static Function func = {};

		constexpr uint32 size0 = 7;

		if (!run)
		{
			func = CreateMobilityFunction(TrickDown);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Reset Dash
	{
		auto addr     = (appBaseAddr + 0x1E0AFE);
		auto jumpAddr = (appBaseAddr + 0x1E0B05);
		/*
		dmc3.exe+1E0AFE - 40 88 BB 5C630000 - mov [rbx+0000635C],dil
		dmc3.exe+1E0B05 - 8B 83 003E0000    - mov eax,[rbx+00003E00]
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};
		constexpr uint32 size0 = 7;
		constexpr uint32 size1 = sizeof(sect1);

		if (!run)
		{
			func = CreateFunction(ResetDash, jumpAddr, true, true, size0, size1);
			CopyMemory(func.sect0, addr, size0, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, size1);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x1F8059);
		auto jumpAddr = (appBaseAddr + 0x1F8060);
		/*
		dmc3.exe+1F8059 - 40 88 BB 5C630000 - mov [rbx+0000635C],dil
		dmc3.exe+1F8060 - C6 83 153F0000 04 - mov byte ptr [rbx+00003F15],04
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};
		constexpr uint32 size0 = 7;
		constexpr uint32 size1 = sizeof(sect1);

		if (!run)
		{
			func = CreateFunction(ResetDash, jumpAddr, true, true, size0, size1);
			CopyMemory(func.sect0, addr, size0, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, size1);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x1F8383);
		auto jumpAddr = (appBaseAddr + 0x1F838A);
		/*
		dmc3.exe+1F8383 - 40 88 BB 5C630000 - mov [rbx+0000635C],dil
		dmc3.exe+1F838A - 48 89 BB C43E0000 - mov [rbx+00003EC4],rdi
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};
		constexpr uint32 size0 = 7;
		constexpr uint32 size1 = sizeof(sect1);

		if (!run)
		{
			func = CreateFunction(ResetDash, jumpAddr, true, true, size0, size1);
			CopyMemory(func.sect0, addr, size0, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, size1);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Reset Sky Star
	{
		auto addr     = (appBaseAddr + 0x1DFEAE);
		auto jumpAddr = (appBaseAddr + 0x1DFEB4);
		/*
		dmc3.exe+1DFEAE - 88 8B 5D630000 - mov [rbx+0000635D],cl
		dmc3.exe+1DFEB4 - 89 AB 74630000 - mov [rbx+00006374],ebp
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};
		constexpr uint32 size0 = 6;
		constexpr uint32 size1 = sizeof(sect1);

		if (!run)
		{
			func = CreateFunction(ResetSkyStar, jumpAddr, true, true, size0, size1);
			CopyMemory(func.sect0, addr, size0, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, size1);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x1DFFB6);
		auto jumpAddr = (appBaseAddr + 0x1DFFBC);
		/*
		dmc3.exe+1DFFB6 - 88 8B 5D630000    - mov [rbx+0000635D],cl
		dmc3.exe+1DFFBC - 40 88 AB AE3F0000 - mov [rbx+00003FAE],bpl
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};
		constexpr uint32 size0 = 6;
		constexpr uint32 size1 = sizeof(sect1);

		if (!run)
		{
			func = CreateFunction(ResetSkyStar, jumpAddr, true, true, size0, size1);
			CopyMemory(func.sect0, addr, size0, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, size1);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x1E07A2);
		auto jumpAddr = (appBaseAddr + 0x1E07A9);
		/*
		dmc3.exe+1E07A2 - 41 88 89 5D630000 - mov [r9+0000635D],cl
		dmc3.exe+1E07A9 - EB 06             - jmp dmc3.exe+1E07B1
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_r9,
		};
		constexpr uint32 size0 = 7;
		constexpr uint32 size1 = sizeof(sect1);

		if (!run)
		{
			func = CreateFunction(ResetSkyStar, jumpAddr, true, true, size0, size1);
			CopyMemory(func.sect0, addr, size0, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, size1);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x1E0D81);
		auto jumpAddr = (appBaseAddr + 0x1E0D87);
		/*
		dmc3.exe+1E0D81 - 88 8B 5D630000 - mov [rbx+0000635D],cl
		dmc3.exe+1E0D87 - 39 7B 78       - cmp [rbx+78],edi
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};
		constexpr uint32 size0 = 6;
		constexpr uint32 size1 = sizeof(sect1);

		if (!run)
		{
			func = CreateFunction(ResetSkyStar, jumpAddr, true, true, size0, size1);
			CopyMemory(func.sect0, addr, size0, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, size1);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x1E0F64);
		auto jumpAddr = (appBaseAddr + 0x1E0F6B);
		/*
		dmc3.exe+1E0F64 - 41 88 88 5D630000 - mov [r8+0000635D],cl
		dmc3.exe+1E0F6B - EB 5E             - jmp dmc3.exe+1E0FCB
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_r8,
		};
		constexpr uint32 size0 = 7;
		constexpr uint32 size1 = sizeof(sect1);

		if (!run)
		{
			func = CreateFunction(ResetSkyStar, jumpAddr, true, true, size0, size1);
			CopyMemory(func.sect0, addr, size0, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, size1);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x1E0FBD);
		auto jumpAddr = (appBaseAddr + 0x1E0FC4);
		/*
		dmc3.exe+1E0FBD - 41 88 88 5D630000 - mov [r8+0000635D],cl
		dmc3.exe+1E0FC4 - 41 FE 88 133F0000 - dec [r8+00003F13]
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_r8,
		};
		constexpr uint32 size0 = 7;
		constexpr uint32 size1 = sizeof(sect1);

		if (!run)
		{
			func = CreateFunction(ResetSkyStar, jumpAddr, true, true, size0, size1);
			CopyMemory(func.sect0, addr, size0, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, size1);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x1E16D2);
		auto jumpAddr = (appBaseAddr + 0x1E16D8);
		/*
		dmc3.exe+1E16D2 - 88 8B 5D630000 - mov [rbx+0000635D],cl
		dmc3.exe+1E16D8 - 39 7B 78       - cmp [rbx+78],edi
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};
		constexpr uint32 size0 = 6;
		constexpr uint32 size1 = sizeof(sect1);

		if (!run)
		{
			func = CreateFunction(ResetSkyStar, jumpAddr, true, true, size0, size1);
			CopyMemory(func.sect0, addr, size0, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, size1);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	run = true;
}







void PlayQuicksilverMotion
(
	byte8 * actorBaseAddr,
	uint32 archiveIndex,
	uint32 fileIndex
)
{
	if (!actorBaseAddr)
	{
		return;
	}
	auto & actorData = *reinterpret_cast<ActorData *>(actorBaseAddr);

	auto PlayMotion = [&]()
	{
		func_1EFB90
		(
			actorBaseAddr,
			archiveIndex,
			fileIndex,
			-1.0f,
			-1,
			2,
			5
		);
	};

	if (actorData.character == CHAR_VERGIL)
	{
		auto & motionArchive = actorData.motionArchives[3];
		auto lastMotionArchive = motionArchive;

		motionArchive = File_staticFiles[pl000_00_25];

		PlayMotion();

		motionArchive = lastMotionArchive;
	}
	else
	{
		PlayMotion();
	}
}








































#pragma endregion

#pragma region Magic Points Depletion Values

float32 * magicPointsDepletionValueQuicksilverDest  = 0;
float32 * magicPointsDepletionValueDoppelgangerDest = 0;
float32 * magicPointsDepletionValueDevilDest        = 0;

void InitMagicPointsDepletionValues()
{
	LogFunction();

	auto dest = HighAlloc(12);
	if (!dest)
	{
		Log("HighAlloc failed.");

		return;
	}

	magicPointsDepletionValueQuicksilverDest  = reinterpret_cast<float32 *>(dest + 0);
	magicPointsDepletionValueDoppelgangerDest = reinterpret_cast<float32 *>(dest + 4);
	magicPointsDepletionValueDevilDest        = reinterpret_cast<float32 *>(dest + 8);

	// Quicksilver
	{
		auto dest = (appBaseAddr + 0x1F8A40);

		constexpr byte8 buffer[] =
		{
			0xF3, 0x0F, 0x59, 0x0D, 0x00, 0x00, 0x00, 0x00, // mulss xmm1,[]
		};
		CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);

		WriteAddress(dest, magicPointsDepletionValueQuicksilverDest, 8);
		/*
		dmc3.exe+1F8A40 - F3 0F59 88 70010000 - mulss xmm1,[rax+00000170]
		dmc3.exe+1F8A48 - E8 238DFEFF         - call dmc3.exe+1E1770
		*/
	}

	// Doppelganger
	{
		auto dest = (appBaseAddr + 0x1F89D1);

		constexpr byte8 buffer[] =
		{
			0xF3, 0x0F, 0x59, 0x0D, 0x00, 0x00, 0x00, 0x00, // mulss xmm1,[]
		};
		CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);

		WriteAddress(dest, magicPointsDepletionValueDoppelgangerDest, 8);
		/*
		dmc3.exe+1F89D1 - F3 0F59 88 74010000 - mulss xmm1,[rax+00000174]
		dmc3.exe+1F89D9 - E8 928DFEFF         - call dmc3.exe+1E1770
		*/
	}

	// Devil
	{
		auto dest = (appBaseAddr + 0x1F8B49);

		constexpr byte8 buffer[] =
		{
			0xF3, 0x0F, 0x59, 0x0D, 0x00, 0x00, 0x00, 0x00, // mulss xmm1,[]
		};
		CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);

		WriteAddress(dest, magicPointsDepletionValueDevilDest, 8);
		/*
		dmc3.exe+1F8B49 - F3 0F59 88 78010000 - mulss xmm1,[rax+00000178]
		dmc3.exe+1F8B51 - E8 1A8CFEFF         - call dmc3.exe+1E1770
		*/
	}
}

export void UpdateMagicPointsDepletionValues()
{
	LogFunction();

	*magicPointsDepletionValueQuicksilverDest  = activeConfig.MagicPointsDepletionValues.quicksilver;
	*magicPointsDepletionValueDoppelgangerDest = activeConfig.MagicPointsDepletionValues.doppelganger;
	*magicPointsDepletionValueDevilDest        = activeConfig.MagicPointsDepletionValues.devil;
}

#pragma endregion

#pragma region Color

void SetColorAirHike
(
	ActorDataDante & actorData,
	byte8 * dest
)
{
	uint8 meleeWeaponIndex = static_cast<uint8>(actorData.meleeWeaponIndex);
	if (meleeWeaponIndex >= MELEE_WEAPON_COUNT_DANTE)
	{
		meleeWeaponIndex = 0;
	}

	memcpy(dest, activeConfig.Color.airHike[meleeWeaponIndex], 4);
}

void SetColorAura
(
	ActorData & actorData,
	byte8 * dest
)
{
	uint8 character = static_cast<uint8>(actorData.character);

	switch (character)
	{
		case CHAR_DANTE:
		{
			auto & actorData2 = *reinterpret_cast<ActorDataDante *>(&actorData);

			if (actorData2.sparda)
			{
				memcpy(dest, activeConfig.Color.Aura.sparda, 4);
			}
			else
			{
				uint8 meleeWeaponIndex = static_cast<uint8>(actorData2.meleeWeaponIndex);
				if (meleeWeaponIndex >= MELEE_WEAPON_COUNT_DANTE)
				{
					meleeWeaponIndex = 0;
				}

				memcpy(dest, activeConfig.Color.Aura.dante[meleeWeaponIndex], 4);
			}
			break;
		}
		case CHAR_VERGIL:
		{
			auto & actorData2 = *reinterpret_cast<ActorDataVergil *>(&actorData);

			if (actorData2.neroAngelo)
			{
				memcpy(dest, activeConfig.Color.Aura.neroAngelo, 4);
			}
			else
			{
				uint8 activeMeleeWeaponIndex = static_cast<uint8>(actorData2.activeMeleeWeaponIndex);
				if (activeMeleeWeaponIndex >= MELEE_WEAPON_COUNT_VERGIL)
				{
					activeMeleeWeaponIndex = 0;
				}

				memcpy(dest, activeConfig.Color.Aura.vergil[activeMeleeWeaponIndex], 4);
			}
			break;
		}
	}
}

// @Todo: Toggle.
void InitColor()
{
	LogFunction();

	// Air Hike
	{
		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};
		auto func = CreateFunction(SetColorAirHike, 0, true, true, 0, sizeof(sect1));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteCall((appBaseAddr + 0x1F66DD), func.addr);
		/*
		dmc3.exe+1F66DD - E8 1E66E9FF - call dmc3.exe+8CD00
		*/
	}

	// Trickster Sky Star
	{
		constexpr byte8 sect0[] =
		{
			0x48, 0xBF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rdi
			0x8B, 0x3F,                                                 // mov edi,[rdi]
			0x89, 0xB8, 0xE0, 0x00, 0x00, 0x00,                         // mov [rax+000000E0],edi
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x8E340), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint8 **>(func.sect0 + 2) = activeConfig.Color.Trickster.skyStar;
		WriteJump((appBaseAddr + 0x8E330), func.addr, 4);
		/*
		dmc3.exe+8E330 - 66 C7 80 E0000000 FF00  - mov word ptr [rax+000000E0],00FF
		dmc3.exe+8E340 - C7 80 DC000000 02000000 - mov [rax+000000DC],00000002
		*/
	}

	// Royalguard Ultimate Start
	{
		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx
			0x8B, 0x09,                                                 // mov ecx,[rcx]
			0x89, 0x88, 0xE0, 0x00, 0x00, 0x00,                         // mov [rax+000000E0],ecx
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x8E84C), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint8 **>(func.sect0 + 2) = activeConfig.Color.Royalguard.ultimate;
		WriteJump((appBaseAddr + 0x8E83C), func.addr, 4);
		/*
		dmc3.exe+8E83C - 66 C7 80 E0000000 8F70  - mov word ptr [rax+000000E0],708F
		dmc3.exe+8E84C - C7 80 DC000000 02000000 - mov [rax+000000DC],00000002
		*/
	}

	// Royalguard Ultimate End
	{
		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx
			0x8B, 0x09,                                                 // mov ecx,[rcx]
			0x89, 0x88, 0xE0, 0x00, 0x00, 0x00,                         // mov [rax+000000E0],ecx
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x91154), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint8 **>(func.sect0 + 2) = activeConfig.Color.Royalguard.ultimate;
		WriteJump((appBaseAddr + 0x91144), func.addr, 4);
		/*
		dmc3.exe+91144 - 66 C7 80 E0000000 8F70  - mov word ptr [rax+000000E0],708F
		dmc3.exe+91154 - C7 80 DC000000 02000000 - mov [rax+000000DC],00000002
		*/
	}

	// Doppelganger Clone
	{
		constexpr byte8 sect0[] =
		{
			0x48, 0xBE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rsi
			0x8B, 0x36,                                                 // mov esi,[rsi]
			0x89, 0xB7, 0x28, 0x3A, 0x00, 0x00,                         // mov [rdi+00003A28],esi
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x1FCD7D), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint8 **>(func.sect0 + 2) = activeConfig.Color.Doppelganger.clone;
		WriteJump((appBaseAddr + 0x1FCD73), func.addr, 5);
		/*
		dmc3.exe+1FCD73 - C7 87 283A0000 10101030 - mov [rdi+00003A28],30101010
		dmc3.exe+1FCD7D - 89 87 243A0000          - mov [rdi+00003A24],eax
		*/
	}

	// Aura Start
	{
		constexpr byte8 sect0[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, // call
			0x48, 0x8B, 0xC8,             // mov rcx,rax
			0x48, 0x8D, 0x55, 0xA7,       // lea rdx,[rbp-59]
		};
		constexpr byte8 sect2[] =
		{
			0xBA, 0x01, 0x00, 0x00, 0x00, // mov edx,00000001
		};
		auto func = CreateFunction(SetColorAura, (appBaseAddr + 0x8E457), true, true, sizeof(sect0), 0, sizeof(sect2));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteCall(func.sect0, GetActorBaseAddr[RBX]);
		WriteJump((appBaseAddr + 0x8E452), func.addr);
		/*
		dmc3.exe+8E452 - BA 01000000 - mov edx,00000001
		dmc3.exe+8E457 - E8 34C61600 - call dmc3.exe+1FAA90
		*/
	}

	// Aura Loop
	{
		constexpr byte8 sect0[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, // call
			0x48, 0x8B, 0xC8,             // mov rcx,rax
			0x48, 0x8D, 0x54, 0x24, 0x30, // lea rdx,[rsp+30]
		};
		constexpr byte8 sect2[] =
		{
			0x48, 0x8B, 0x06, // mov rax,[rsi]
			0x48, 0x85, 0xC0, // test rax,rax
		};
		auto func = CreateFunction(SetColorAura, (appBaseAddr + 0x90C69), true, true, sizeof(sect0), 0, sizeof(sect2));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteCall(func.sect0, GetActorBaseAddr[RDI]);
		WriteJump((appBaseAddr + 0x90C63), func.addr, 1);
		/*
		dmc3.exe+90C63 - 48 8B 06 - mov rax,[rsi]
		dmc3.exe+90C66 - 48 85 C0 - test rax,rax
		dmc3.exe+90C69 - 74 32    - je dmc3.exe+90C9D
		*/
	}

	// Aura Vergil Fix
	SetMemory((appBaseAddr + 0x90C32), 0x90, 4, MemoryFlags_VirtualProtectDestination);
	/*
	dmc3.exe+90C32 - 44 0FB6 EB - movzx r13d,bl
	*/
}

#pragma endregion

#pragma region Speed

byte8 * UpdateActorSpeedAddr = 0;

// @Todo: Quicksilver enemy speed.
// @Todo: Check turbo modifier.
// @Todo: Add quicksilver check.
// Geryon turns Quicksilver forcefully off.
// When hit by Geryon's Time Lag, Quicksilver is turned off.
// So we can easily check against quicksilver flag.





void UpdateActorSpeed(byte8 * baseAddr)
{
	if (!baseAddr)
	{
		return;
	}

	for_all(uint32, index, Actor_actorBaseAddr.count)
	{
		IntroduceActorData(actorBaseAddr, actorData, Actor_actorBaseAddr[index], continue);
		//IntroduceActorData(actorBaseAddr, actorData, index, continue);
		// auto actorBaseAddr = Actor_actorBaseAddr[index];
		// if (actorBaseAddr != baseAddr)
		// {
		// 	continue;
		// }
		// auto & actorData = *reinterpret_cast<ActorData *>(actorBaseAddr);

		auto value = (GetTurbo()) ? activeConfig.Speed.turbo : activeConfig.Speed.main;

		if (g_quicksilver)
		{
			switch (actorData.speedMode)
			{
				case 2:
				{
					value *= activeConfig.Speed.quicksilverActor;

					goto LoopContinue;
				}
			}
		}
		else
		{
			switch (actorData.speedMode)
			{
				case 1:
				{
					value = 0;

					goto LoopContinue;
				}
				case 2:
				{
					value *= 0.2f;

					goto LoopContinue;
				}
			}
		}

		if (!actorData.devil)
		{
			value *= activeConfig.Speed.human;
		}
		else
		{
			switch (actorData.character)
			{
				case CHAR_DANTE:
				{
					auto devilIndex = actorData.meleeWeaponIndex;
					if (devilIndex > 4)
					{
						devilIndex = 0;
					}

					if (actorData.sparda)
					{
						devilIndex = DEVIL_SPEED_DANTE_SPARDA;
					}

					value *= activeConfig.Speed.devilDante[devilIndex];

					break;
				}
				case CHAR_VERGIL:
				{
					auto devilIndex = actorData.queuedMeleeWeaponIndex;
					if (devilIndex > 2)
					{
						devilIndex = 0;
					}

					if (actorData.neroAngelo)
					{
						if (devilIndex > 1)
						{
							devilIndex = 0;
						}

						devilIndex += 3;
					}

					value *= activeConfig.Speed.devilVergil[devilIndex];

					break;
				}
			}
		}

		LoopContinue:;

		actorData.speed = value;
	}
}

void InitSpeed()
{
	LogFunction();

	{
		constexpr byte8 sect0[] =
		{
			0xF3, 0x0F, 0x11, 0x43, 0x14, // movss [rbx+14],xmm0
		};
		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};
		auto func = CreateFunction(UpdateActorSpeed, (appBaseAddr + 0x3261D2), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		UpdateActorSpeedAddr = func.addr;
		/*
		dmc3.exe+3261CD - F3 0F11 43 14 - movss [rbx+14],xmm0
		dmc3.exe+3261D2 - 48 83 C4 20   - add rsp,20
		*/
	}
}

void ToggleSpeed(bool enable)
{
	LogFunction(enable);

	// Devil Speed Values Dante
	{
		auto items = reinterpret_cast<float *>(appBaseAddr + 0x58B0B8);

		if (enable)
		{
			for_all(uint8, itemIndex, countof(activeConfig.Speed.devilDante))
			{
				auto & item = items[itemIndex];

				Write<float>(&item, 1.0f);
			}
		}
		else
		{
			CopyMemory(items, defaultConfig.Speed.devilDante, sizeof(defaultConfig.Speed.devilDante), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1F8C24 - F3 41 0F10 84 8C B8B05800 - MOVSS XMM0,[R12+RCX*4+0058B0B8]
		*/
	}

	// Devil Speed Values Vergil
	{
		auto items = reinterpret_cast<float *>(appBaseAddr + 0x58B0D8);

		if (enable)
		{
			for_all(uint8, itemIndex, countof(activeConfig.Speed.devilVergil))
			{
				auto & item = items[itemIndex];

				Write<float>(&item, 1.0f);
			}
		}
		else
		{
			CopyMemory(items, defaultConfig.Speed.devilVergil, sizeof(defaultConfig.Speed.devilVergil), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1F8C48 - F3 41 0F10 84 8C D8B05800 - MOVSS XMM0,[R12+RCX*4+0058B0D8]
		dmc3.exe+1F8C5B - F3 41 0F10 84 84 D8B05800 - MOVSS XMM0,[R12+RAX*4+0058B0D8]
		*/
	}

	// Update Actor Speed
	{
		auto dest = (appBaseAddr + 0x3261CD);
		if (enable)
		{
			WriteJump(dest, UpdateActorSpeedAddr);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0xF3, 0x0F, 0x11, 0x43, 0x14, // movss [rbx+14],xmm0
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+3261CD - F3 0F11 43 14 - movss [rbx+14],xmm0
		dmc3.exe+3261D2 - 48 83 C4 20   - add rsp,20
		*/
	}
}




#pragma endregion

#pragma region Sound

void UpdateGlobalCharacterCostume(byte8 * bodyPartDataAddr)
{
	if (!bodyPartDataAddr)
	{
		return;
	}
	auto & bodyPartData = *reinterpret_cast<BodyPartData *>(bodyPartDataAddr);

	if (!bodyPartData.motionArchives)
	{
		return;
	}

	IntroduceActorData
	(
		actorBaseAddr,
		actorData,
		(reinterpret_cast<byte8 *>(bodyPartData.motionArchives) - offsetof(ActorData, motionArchives)),
		return
	);









	g_character = static_cast<uint8>(actorData.character);
	g_costume = actorData.costume;
}

void ToggleSound(bool enable)
{
	static bool run = false;

	// Melee Weapon Sounds
	{
		auto addr     = (appBaseAddr + 0x59E3B);
		auto jumpAddr = (appBaseAddr + 0x59E40);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+59E3B - E8 F0FA2D00       - call dmc3.exe+339930
		dmc3.exe+59E40 - C6 83 09010000 01 - mov byte ptr [rbx+00000109],01
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(UpdateGlobalCharacterCostume, jumpAddr, true, true, 0, sizeof(sect1), size);
			CopyMemory(func.sect1, sect1, sizeof(sect1));
			CopyMemory(func.sect2, addr, size, MemoryFlags_VirtualProtectSource);
			WriteCall(func.sect2, (appBaseAddr + 0x339930));
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	run = true;
}







#pragma endregion



// @Todo: Recheck.
void ToggleMainActorFixes(bool enable)
{
	LogFunction(enable);

	{
		auto dest = (appBaseAddr + 0x1F83D7);
		if (enable)
		{
			SetMemory(dest, 0x90, 18, MemoryFlags_VirtualProtectDestination);
			constexpr byte8 buffer[] =
			{
				0x40, 0x38, 0xB7, 0x62, 0x63, 0x00, 0x00, // cmp [rdi+00006362],sil
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0x48, 0x8B, 0x0D, 0x4A, 0x8A, 0xA9, 0x00, // mov rcx,[dmc3.exe+C90E28]
				0x48, 0x8B, 0x41, 0x18,                   // mov rax,[rcx+18]
				0x40, 0x38, 0xB0, 0x62, 0x63, 0x00, 0x00, // cmp [rax+00006362],sil
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1F83D7 - 48 8B 0D 4A8AA900 - mov rcx,[dmc3.exe+C90E28]
		dmc3.exe+1F83DE - 48 8B 41 18       - mov rax,[rcx+18]
		dmc3.exe+1F83E2 - 40 38 B0 62630000 - cmp [rax+00006362],sil
		dmc3.exe+1F83E9 - 75 0E             - jne dmc3.exe+1F83F9
		*/
	}

	Write<uint32>((appBaseAddr + 0x1F5FC6 + 2), (enable) ? offsetof(ActorData, newIsClone) : offsetof(ActorData, isClone));
	/*
	dmc3.exe+1F5FC6 - 83 B9 C8CA0100 01 - cmp dword ptr [rcx+0001CAC8],01
	dmc3.exe+1F5FCD - 48 8B D9          - mov rbx,rcx
	*/
}

void ToggleStyleFixes(bool enable)
{
	// Disable Menu Controller
	Write<bool>((appBaseAddr + 0x23B110 + 1), (enable) ? false : true); // dmc3.exe+23B110 - B0 01 - mov al,01
	Write<bool>((appBaseAddr + 0x23B15D + 1), (enable) ? false : true); // dmc3.exe+23B15D - B0 01 - mov al,01
	Write<bool>((appBaseAddr + 0x23B1A1 + 1), (enable) ? false : true); // dmc3.exe+23B1A1 - B0 01 - mov al,01
	Write<bool>((appBaseAddr + 0x23B1E5 + 1), (enable) ? false : true); // dmc3.exe+23B1E5 - B0 01 - mov al,01

	// Force Style Updates
	{
		WriteAddress((appBaseAddr + 0x1F87BB), (enable) ? (appBaseAddr + 0x1F87DC) : (appBaseAddr + 0x1F8AC6), 6); // dmc3.exe+1F87BB - 0F84 05030000 - je dmc3.exe+1F8AC6
		WriteAddress((appBaseAddr + 0x1F87C4), (enable) ? (appBaseAddr + 0x1F87DC) : (appBaseAddr + 0x1F8AAC), 6); // dmc3.exe+1F87C4 - 0F84 E2020000 - je dmc3.exe+1F8AAC
		WriteAddress((appBaseAddr + 0x1F87CD), (enable) ? (appBaseAddr + 0x1F87DC) : (appBaseAddr + 0x1F8A00), 6); // dmc3.exe+1F87CD - 0F84 2D020000 - je dmc3.exe+1F8A00
		WriteAddress((appBaseAddr + 0x1F87D6), (enable) ? (appBaseAddr + 0x1F87DC) : (appBaseAddr + 0x1F8AF8), 6); // dmc3.exe+1F87D6 - 0F85 1C030000 - jne dmc3.exe+1F8AF8
		// Doppelganger
		WriteAddress((appBaseAddr + 0x1F880B), (enable) ? (appBaseAddr + 0x1F8A00) : (appBaseAddr + 0x1F8AF8), 6); // dmc3.exe+1F880B - 0F85 E7020000 - jne dmc3.exe+1F8AF8
		WriteAddress((appBaseAddr + 0x1F8852), (enable) ? (appBaseAddr + 0x1F8A00) : (appBaseAddr + 0x1F8AF8), 6); // dmc3.exe+1F8852 - 0F85 A0020000 - jne dmc3.exe+1F8AF8
		WriteAddress((appBaseAddr + 0x1F8862), (enable) ? (appBaseAddr + 0x1F8A00) : (appBaseAddr + 0x1F8AF8), 5); // dmc3.exe+1F8862 - E9 91020000   - jmp dmc3.exe+1F8AF8
		WriteAddress((appBaseAddr + 0x1F886E), (enable) ? (appBaseAddr + 0x1F8A00) : (appBaseAddr + 0x1F8AF8), 6); // dmc3.exe+1F886E - 0F84 84020000 - je dmc3.exe+1F8AF8
		WriteAddress((appBaseAddr + 0x1F89E1), (enable) ? (appBaseAddr + 0x1F8A00) : (appBaseAddr + 0x1F8AF8), 6); // dmc3.exe+1F89E1 - 0F82 11010000 - jb dmc3.exe+1F8AF8
		WriteAddress((appBaseAddr + 0x1F89FB), (enable) ? (appBaseAddr + 0x1F8A00) : (appBaseAddr + 0x1F8AF8), 5); // dmc3.exe+1F89FB - E9 F8000000   - jmp dmc3.exe+1F8AF8
		// Quicksilver
		WriteAddress((appBaseAddr + 0x1F8A07), (enable) ? (appBaseAddr + 0x1F8AAC) : (appBaseAddr + 0x1F8AF8), 6); // dmc3.exe+1F8A07 - 0F85 EB000000 - jne dmc3.exe+1F8AF8
		WriteAddress((appBaseAddr + 0x1F8A7D), (enable) ? (appBaseAddr + 0x1F8AAC) : (appBaseAddr + 0x1F8AF8), 2); // dmc3.exe+1F8A7D - 72 79         - jb dmc3.exe+1F8AF8
		WriteAddress((appBaseAddr + 0x1F8AAA), (enable) ? (appBaseAddr + 0x1F8AAC) : (appBaseAddr + 0x1F8AF8), 2); // dmc3.exe+1F8AAA - EB 4C         - jmp dmc3.exe+1F8AF8
		// Royalguard
		WriteAddress((appBaseAddr + 0x1F8AC4), (enable) ? (appBaseAddr + 0x1F8AC6) : (appBaseAddr + 0x1F8AF8), 2); // dmc3.exe+1F8AC4 - EB 32 - jmp dmc3.exe+1F8AF8
	}

	// Gunslinger Fixes
	{
		// Allow Charging
		WriteAddress((appBaseAddr + 0x21607C), (enable) ? (appBaseAddr + 0x216082) : (appBaseAddr + 0x216572), 6);
		/*
		dmc3.exe+21606F - 83 BF 38630000 01 - cmp dword ptr [rdi+00006338],01
		dmc3.exe+21607C - 0F85 F0040000     - jne dmc3.exe+216572
		dmc3.exe+216082 - 83 BF 943E0000 02 - cmp dword ptr [rdi+00003E94],02
		*/

		// Allow Charged Shot
		WriteAddress((appBaseAddr + 0x1E6AAD), (enable) ? (appBaseAddr + 0x1E6AB3) : (appBaseAddr + 0x1E64A9), 6);
		/*
		dmc3.exe+1E6AA7 - 3B 83 38630000 - cmp eax,[rbx+00006338]
		dmc3.exe+1E6AAD - 0F85 F6F9FFFF  - jne dmc3.exe+1E64A9
		dmc3.exe+1E6AB3 - 83 7B 78 00    - cmp dword ptr [rbx+78],00
		*/

		// Allow Wild Stomp
		Write<byte8>((appBaseAddr + 0x1E7F5F), (enable) ? 0xEB : 0x74);
		/*
		dmc3.exe+1E7F55 - 83 B9 38630000 01 - cmp dword ptr [rcx+00006338],01
		dmc3.exe+1E7F5F - 74 15             - je dmc3.exe+1E7F76
		*/
	}

	// Disable Dante Check
	Write<byte8>((appBaseAddr + 0x1E8F98), (enable) ? 0xEB : 0x74);
	/*
	dmc3.exe+1E8F98 - 74 0D - je dmc3.exe+1E8FA7
	dmc3.exe+1E8F9A - 32 C0 - xor al,al
	*/
}










bool DevilButtonCheck(ActorData & actorData)
{
	auto & playerData = GetPlayerData(actorData);

	bool condition = (actorData.buttons[0] & playerData.button);

	if (actorData.newEntityIndex == ENTITY_MAIN)
	{
		if (condition)
		{
			return false;
		}
	}
	else
	{
		if (!condition)
		{
			return false;
		}
	}

	return true;
}

// @Todo: Update.
void ActivateDevil(ActorData & actorData)
{
	switch (actorData.character)
	{
		case CHAR_DANTE:
		{
			auto & actorData2 = *reinterpret_cast<ActorDataDante *>(&actorData);
			UpdateForm(actorData2);
			break;
		}
		case CHAR_VERGIL:
		{
			auto & actorData2 = *reinterpret_cast<ActorDataVergil *>(&actorData);
			UpdateForm(actorData2);
			break;
		}
	}

	func_1F94D0(actorData, DEVIL_FLUX_START);
}

void DeactivateDevil(ActorData & actorData)
{
	switch (actorData.character)
	{
		case CHAR_DANTE:
		{
			auto & actorData2 = *reinterpret_cast<ActorDataDante *>(&actorData);
			UpdateForm(actorData2);
			break;
		}
		case CHAR_VERGIL:
		{
			auto & actorData2 = *reinterpret_cast<ActorDataVergil *>(&actorData);
			UpdateForm(actorData2);
			break;
		}
	}

	func_1F94D0(actorData, DEVIL_FLUX_END);
}








void UpdateColorMatrices(ActorData & actorData)
{
	if (actorData.visibility != 0)
	{
		actorData.visibility = (g_quicksilver) ? 2 : 1;
	}

	uint16 value = (g_quicksilver) ? 128 : 0;

	{
		auto dest = reinterpret_cast<byte8 *>(&actorData.newModelData[0]);

		*reinterpret_cast<uint16 *>(dest + 0x80 + 0x214) = value;
	}

	if (actorData.character == CHAR_BOB)
	{
		auto dest = reinterpret_cast<byte8 *>(&actorData);

		*reinterpret_cast<uint16 *>(dest + 0x13E10 + 0x214) = value;
	}

	for_all(uint8, weaponIndex, WEAPON_COUNT)
	{
		auto & weapon = actorData.newWeapons[weaponIndex];
		if (weapon >= MAX_WEAPON)
		{
			continue;
		}

		auto weaponDataAddr = actorData.newWeaponDataAddr[weaponIndex];
		if (!weaponDataAddr)
		{
			continue;
		}

		auto dest = reinterpret_cast<byte8 *>(weaponDataAddr);

		constexpr uint32 offs[MAX_WEAPON] =
		{
			0x280,
			0x880,
			0x340,
			0x300,
			0x3C0,
			0,
			0x280,
			0x400,
			0x200,
			0x280,
			0,
			0,
			0x3C0,
			0x280,
			0,
		};

		auto off = offs[weapon];

		switch (weapon)
		{
			case WEAPON_EBONY_IVORY:
			{
				*reinterpret_cast<uint16 *>(dest + 0x200 + 0x214) = value;
				*reinterpret_cast<uint16 *>(dest + 0x980 + 0x214) = value;

				break;
			}
			case WEAPON_YAMATO_VERGIL:
			case WEAPON_YAMATO_BOB:
			{
				*reinterpret_cast<uint16 *>(dest + 0xF00  + 0x214) = value;
				*reinterpret_cast<uint16 *>(dest + 0x1680 + 0x214) = value;

				break;
			}
			default:
			{
				*reinterpret_cast<uint16 *>(dest + off + 0x214) = value;

				break;
			}
		}
	}
}

inline void QuicksilverFunction
(
	byte8 * actorBaseAddr,
	bool enable
)
{
	if (!actorBaseAddr)
	{
		return;
	}
	else if (actorBaseAddr != Actor_actorBaseAddr[2])
	{
		return;
	}

	g_quicksilver = enable;

	for_all(uint32, index, Actor_actorBaseAddr.count)
	{
		IntroduceActorData(actorBaseAddr2, actorData2, Actor_actorBaseAddr[index], continue);

		UpdateColorMatrices(actorData2);
	}
}

void ActivateQuicksilver(byte8 * actorBaseAddr)
{
	if constexpr (debug)
	{
		LogFunction(actorBaseAddr);
	}

	QuicksilverFunction
	(
		actorBaseAddr,
		true
	);
}

void DeactivateQuicksilver(byte8 * actorBaseAddr)
{
	if constexpr (debug)
	{
		LogFunction(actorBaseAddr);
	}

	QuicksilverFunction
	(
		actorBaseAddr,
		false
	);
}

void ActivateDoppelganger(ActorData & actorData)
{
	LogFunction(actorData.operator byte8 *());

	if (!actorData.cloneActorBaseAddr)
	{
		return;
	}
	auto & cloneActorData = *reinterpret_cast<ActorData *>(actorData.cloneActorBaseAddr);

	memset(actorData.var_6438, 0, (actorData.var_6440 * 46));
	/*
	dmc3.exe+1E9222 - 33 D2             - xor edx,edx
	dmc3.exe+1E92A3 - 48 63 87 40640000 - movsxd rax,dword ptr [rdi+00006440]
	dmc3.exe+1E92AA - 48 8B 8F 38640000 - mov rcx,[rdi+00006438]
	dmc3.exe+1E92B1 - 4C 6B C0 2E       - imul r8,rax,2E
	dmc3.exe+1E92B5 - E8 30D91500       - call dmc3.exe+346BEA
	*/

	actorData.cloneRate = 0;

	func_1EAE60(actorData, 0);
	/*
	dmc3.exe+1E92D7 - 33 D2       - xor edx,edx
	dmc3.exe+1E92D9 - 48 8B CF    - mov rcx,rdi
	dmc3.exe+1E92DC - E8 7F1B0000 - call dmc3.exe+1EAE60
	*/

	ToggleActor(cloneActorData, true);
}

void DeactivateDoppelganger(ActorData & actorData)
{
	LogFunction(actorData.operator byte8 *());

	if (!actorData.cloneActorBaseAddr)
	{
		return;
	}
	auto & cloneActorData = *reinterpret_cast<ActorData *>(actorData.cloneActorBaseAddr);

	func_1EAE60(actorData, 1);
	/*
	dmc3.exe+1E9339 - B2 01       - mov dl,01
	dmc3.exe+1E9351 - 48 8B CF    - mov rcx,rdi
	dmc3.exe+1E9354 - E8 071B0000 - call dmc3.exe+1EAE60
	*/

	if (cloneActorData.devil)
	{
		cloneActorData.devil = false;

		DeactivateDevil(cloneActorData);
	}

	ToggleActor(cloneActorData, false);

	EndMotion(cloneActorData);
}



























bool EbonyIvoryRainStormCheck(ActorData & actorData)
{
	if (actorData.buttons[0] & GetBinding(BINDING_STYLE_ACTION))
	{
		return true;
	}

	return false;
}




bool DotShadowCheck(byte8 * dest)
{
	if (!dest)
	{
		return false;
	}

	switch (activeConfig.dotShadow)
	{
		case DOT_SHADOW_DISABLE:
		{
			return true;
		}
		case DOT_SHADOW_DISABLE_ACTOR_ONLY:
		{
			auto baseAddr = *reinterpret_cast<byte8 **>(dest + 0xC0);
			if (!baseAddr)
			{
				break;
			}

			for_all(uint32, index, Actor_actorBaseAddr.count)
			{
				if (baseAddr == Actor_actorBaseAddr[index])
				{
					return true;
				}
			}

			break;
		}
	}

	return false;
}




void ResetActorMode()
{
	LogFunction();

	for_all(uint32, index, Actor_actorBaseAddr.count)
	{
		IntroduceActorData(actorBaseAddr, actorData, Actor_actorBaseAddr[index], continue);
		//IntroduceActorData(actorBaseAddr, actorData, index, continue);
		// auto baseAddr = Actor_actorBaseAddr[index];
		// if (!baseAddr)
		// {
		// 	continue;
		// }
		// auto & actorData = *reinterpret_cast<ActorData *>(baseAddr);

		actorData.mode = ACTOR_MODE_DEFAULT;
		actorData.devil = false;

		// @Todo: Recheck.
		actorData.eventData[1].event = 36;

		DeactivateDevil(actorData);
	}
}





bool CollisionCheck(byte8 * collisionDataAddr)
{
	auto baseAddr = (collisionDataAddr - offsetof(ActorData, collisionData));

	for_all(uint32, index, Actor_actorBaseAddr.count)
	{
		//IntroduceActorData(actorBaseAddr, actorData, index, continue);
		// auto actorBaseAddr = Actor_actorBaseAddr[index];
		// if (!actorBaseAddr)
		// {
		// 	continue;
		// }
		IntroduceActorData(actorBaseAddr, actorData, Actor_actorBaseAddr[index], continue);

		if (actorBaseAddr != baseAddr)
		{
			continue;
		}
		// auto & actorData = *reinterpret_cast<ActorData *>(actorBaseAddr);

		return !actorData.newEnableCollision;
	}

	return false;
}



void ResetVisibility(ActorData & actorData)
{
	if (actorData.visibility != 0)
	{
		actorData.visibility = (g_quicksilver) ? 2 : 1;
	}
}



// void MagicPointsRunOut(ActorData & actorData)
// {
// 	LogFunction(actorData.operator byte8 *());

// 	Log("doppelganger %u", actorData.doppelganger);

// 	auto cloneActorBaseAddr = actorData.cloneBaseAddr;
// 	if (!cloneActorBaseAddr)
// 	{
// 		return;
// 	}
// 	auto & cloneActorData = *reinterpret_cast<ActorData *>(cloneActorBaseAddr);

// 	Log("doppelganger %u", cloneActorData.doppelganger);

// 	ToggleInput(cloneActorData, false);






// }





byte8  * UpdateModelDanteAddr               = 0;
byte8  * UpdateModelVergilAddr              = 0;
uint32 * modelPhysicsMetadataPoolOff        = 0;
byte8  * CoatUpdateDanteAddr                = 0;
byte8  * CoatUpdateVergilAddr               = 0;
byte8  * PositionUpdateEbonyIvoryAddr       = 0;
byte8  * PositionUpdateArtemisAddr          = 0;
byte8  * WeaponSwitchControllerDanteAddr    = 0;
byte8  * WeaponSwitchControllerVergilAddr   = 0;
byte8  * ActivateQuicksilverAddr            = 0;
byte8  * DeactivateQuicksilverAddr[2]       = {};


byte8  * ActivateDoppelgangerAddr           = 0;
byte8  * DeactivateDoppelgangerAddr[2] = {};



byte8  * DevilButtonCheckAddr         = 0;
byte8  * ActivateDevilAddr                  = 0;
byte8  * DeactivateDevilAddr                = 0;
byte8  * InputUpdateAddr[16]                = {};
byte8  * EbonyIvoryRainStormCheckAddr       = 0;
byte8  * SummonedSwordsQuicksilverCheckAddr = 0;
byte8  * DotShadowCheckAddr                 = 0;
byte8 * ResetActorModeAddr                  = 0;
byte8 * CollisionCheckAddr                  = 0;
byte8 * ResetVisibilityAddr[2]              = {};

byte8 * EnableVisibilityCheckAddr[2] = {};


byte8 * PlayQuicksilverMotionAddr[2] = {};


// byte8 * MagicPointsRunOutAddr = 0;



export void Actor_Init()
{
	LogFunction();

	InitGetActorBaseAddr();
	InitRegisterWeapon();
	InitIsWeaponReady();
	//InitMobility();
	InitColor();
	InitSpeed();

	if (!Actor_actorBaseAddr.Init(512))
	{
		Log("Actor_actorBaseAddr.Init failed.");
		return;
	}

	// Model Physics Metadata Pool Offsets
	{
		auto & off = modelPhysicsMetadataPoolOff;

		off = reinterpret_cast<uint32 *>(HighAlloc(64));
		if (!off)
		{
			Log("HighAlloc failed.");
			return;
		}

		for_all(uint32, index, 7)
		{
			off[index] = (index * 24);
		}
	}

	// Update Model Dante
	{
		auto func = CreateFunction(UpdateModel<ActorDataDante>);
		UpdateModelDanteAddr = func.addr;
	}

	// Update Model Vergil
	{
		auto func = CreateFunction(UpdateModel<ActorDataVergil>);
		UpdateModelVergilAddr = func.addr;
	}

	// Coat Update Dante
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
		CoatUpdateDanteAddr = func.addr;
		/*
		dmc3.exe+2120C4 - 48 8B 96 98180000 - mov rdx,[rsi+00001898]
		dmc3.exe+2120CB - 48 8D 8E 40750000 - lea rcx,[rsi+00007540]
		*/
	}

	// Coat Update Vergil
	{
		constexpr byte8 sect0[] =
		{
			0x80, 0xBE, 0xC0, 0xB8, 0x00, 0x00, 0x01, // cmp byte ptr [rsi+0000B8C0],01
			0x75, 0x12,                               // jne short
			0x80, 0xBE, 0x00, 0x00, 0x00, 0x00, 0x00, // cmp byte ptr [rsi+0000B8C0],02
			0x75, 0x09,                               // jne short
			0x48, 0x8B, 0x96, 0x00, 0x00, 0x00, 0x00, // mov rdx,[rsi+000018A8]
			0xEB, 0x07,                               // jmp short
			0x48, 0x8B, 0x96, 0x00, 0x00, 0x00, 0x00, // mov rdx,[rsi+00001898]
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x22050D), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ActorData, newForceFiles);
		*reinterpret_cast<uint32 *>(func.sect0 + 0xB) = offsetof(ActorData, newForceFilesCharacter);
		*reinterpret_cast<uint8 *>(func.sect0 + 0xF) = CHAR_LADY;
		*reinterpret_cast<uint32 *>(func.sect0 + 0x15) = offsetof(ActorData, newModelPhysicsMetadataPool[0][5]);
		*reinterpret_cast<uint32 *>(func.sect0 + 0x1E) = offsetof(ActorData, newModelPhysicsMetadataPool[0][3]);
		CoatUpdateVergilAddr = func.addr;
		/*
		dmc3.exe+220506 - 48 8B 96 98180000 - mov rdx,[rsi+00001898]
		dmc3.exe+22050D - 48 8D 8E 40750000 - lea rcx,[rsi+00007540]
		*/
	}

	// Position Update Ebony & Ivory
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
		PositionUpdateEbonyIvoryAddr = func.addr;
		/*
		dmc3.exe+22B60F - 0FB6 90 9E3E0000 - movzx edx,byte ptr [rax+00003E9E]
		dmc3.exe+22B616 - 8D 42 FD         - lea eax,[rdx-03]
		*/
	}

	// Position Update Artemis
	{
		constexpr byte8 sect0[] =
		{
			0x0F, 0xB6, 0x82, 0x9E, 0x3E, 0x00, 0x00, // movzx eax,byte ptr [rdx+00003E9E]
			0x80, 0xBA, 0x00, 0x00, 0x00, 0x00, 0x01, // cmp byte ptr [rdx+0000B8C0],01
			0x0F, 0x84, 0x00, 0x00, 0x00, 0x00,       // je dmc3.exe+22EC65
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x22EC2E), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint32 *>(func.sect0 + 9) = offsetof(ActorData, newForceFiles);
		WriteAddress((func.sect0 + 0xE), (appBaseAddr + 0x22EC65), 6);
		PositionUpdateArtemisAddr = func.addr;
		/*
		dmc3.exe+22EC27 - 0FB6 82 9E3E0000 - movzx eax,byte ptr [rdx+00003E9E]
		dmc3.exe+22EC2E - 3C 07            - cmp al,07
		*/
	}

	// Weapon Switch Controller Dante
	{
		auto func = CreateFunction(WeaponSwitchController<ActorDataDante>, 0, true, false);
		WeaponSwitchControllerDanteAddr = func.addr;
	}

	// Weapon Switch Controller Vergil
	{
		auto func = CreateFunction(WeaponSwitchController<ActorDataVergil>, 0, true, false);
		WeaponSwitchControllerVergilAddr = func.addr;
	}

	// Activate Quicksilver
	{
		constexpr byte8 sect0[] =
		{
			0xC6, 0x87, 0x61, 0x63, 0x00, 0x00, 0x01, // mov byte ptr [rdi+00006361],01
		};
		constexpr byte8 sect1[] =
		{
			mov_rcx_rdi,
		};
		auto func = CreateFunction(ActivateQuicksilver, (appBaseAddr + 0x1E94B1), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		ActivateQuicksilverAddr = func.addr;
		/*
		dmc3.exe+1E94AA - C6 87 61630000 01       - mov byte ptr [rdi+00006361],01
		dmc3.exe+1E94B1 - C7 87 40630000 02000000 - mov [rdi+00006340],00000002
		*/
	}

	// Deactivate Quicksilver
	{
		constexpr byte8 sect0[] =
		{
			0x40, 0x88, 0xB7, 0x61, 0x63, 0x00, 0x00, // mov [rdi+00006361],sil
		};
		constexpr byte8 sect1[] =
		{
			mov_rcx_rdi,
		};
		auto func = CreateFunction(DeactivateQuicksilver, (appBaseAddr + 0x1E9558), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		DeactivateQuicksilverAddr[0] = func.addr;
		/*
		dmc3.exe+1E9551 - 40 88 B7 61630000 - mov [rdi+00006361],sil
		dmc3.exe+1E9558 - 89 B7 40630000    - mov [rdi+00006340],esi
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0xC6, 0x81, 0x61, 0x63, 0x00, 0x00, 0x00, // mov byte ptr [rcx+00006361],00
		};
		auto func = CreateFunction(DeactivateQuicksilver, (appBaseAddr + 0x1EAC20), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		DeactivateQuicksilverAddr[1] = func.addr;
		/*
		dmc3.exe+1EAC19 - C6 81 61630000 00       - mov byte ptr [rcx+00006361],00
		dmc3.exe+1EAC20 - C7 81 40630000 00000000 - mov [rcx+00006340],00000000
		*/
	}





	// Activate Doppelganger
	{
		constexpr byte8 sect0[] =
		{
			0xC7, 0x87, 0x54, 0x64, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, // mov [rdi+00006454],00000001
		};
		constexpr byte8 sect1[] =
		{
			mov_rcx_rdi,
		};
		auto func = CreateFunction(ActivateDoppelganger, (appBaseAddr + 0x1E930E), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		ActivateDoppelgangerAddr = func.addr;
		/*
		dmc3.exe+1E9235 - C7 87 54640000 01000000 - mov [rdi+00006454],00000001
		dmc3.exe+1E923F - 8B 88 EC010000          - mov ecx,[rax+000001EC]
		dmc3.exe+1E930E - B0 01                   - mov al,01
		*/
	}

	// Deactivate Doppelganger
	{
		constexpr byte8 sect0[] =
		{
			0xC7, 0x87, 0x54, 0x64, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, // mov [rdi+00006454],00000002
		};
		constexpr byte8 sect1[] =
		{
			mov_rcx_rdi,
		};
		auto func = CreateFunction(DeactivateDoppelganger, (appBaseAddr + 0x1E930E), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		DeactivateDoppelgangerAddr[0] = func.addr;
		/*
		dmc3.exe+1E933B - C7 87 54640000 02000000 - mov [rdi+00006454],00000002
		dmc3.exe+1E9345 - 8B 88 EC010000          - mov ecx,[rax+000001EC]
		dmc3.exe+1E930E - B0 01                   - mov al,01
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0xC7, 0x87, 0x54, 0x64, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, // mov [rdi+00006454],00000002
		};
		constexpr byte8 sect1[] =
		{
			mov_rcx_rdi,
		};
		auto func = CreateFunction(DeactivateDoppelganger, (appBaseAddr + 0x1F8A00), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		DeactivateDoppelgangerAddr[1] = func.addr;
		/*
		dmc3.exe+1F89E9 - C7 87 54640000 02000000 - mov [rdi+00006454],00000002
		dmc3.exe+1F89F3 - 48 8B CF                - mov rcx,rdi
		dmc3.exe+1F8A00 - 80 BF 61630000 01       - cmp byte ptr [rdi+00006361],01
		*/
	}




























	// Devil Button Check
	{
		constexpr byte8 sect1[] =
		{
			mov_rcx_rdi,
		};
		constexpr byte8 sect2[] =
		{
			0x84, 0xC0,                               // test al,al
			0x0F, 0x84, 0x00, 0x00, 0x00, 0x00,       // je dmc3.exe+1E7926
			0x40, 0x38, 0xB7, 0x9B, 0x3E, 0x00, 0x00, // cmp [rdi+00003E9B],sil
		};
		auto func = CreateFunction(DevilButtonCheck, (appBaseAddr + 0x1E77E3), true, false, 0, sizeof(sect1), sizeof(sect2));
		memcpy(func.sect1, sect1, sizeof(sect1));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteAddress((func.sect2 + 2), (appBaseAddr + 0x1E7926), 6);
		DevilButtonCheckAddr = func.addr;
		/*
		dmc3.exe+1E77DC - 40 38 B7 9B3E0000 - cmp [rdi+00003E9B],sil
		dmc3.exe+1E77E3 - 0F85 D4000000     - jne dmc3.exe+1E78BD
		dmc3.exe+1E7926 - 0F28 74 24 50     - movaps xmm6,[rsp+50]
		*/
	}


















	// Activate Devil
	{
		auto func = CreateFunction(ActivateDevil);
		ActivateDevilAddr = func.addr;
	}

	// Deactivate Devil
	{
		auto func = CreateFunction(DeactivateDevil);
		DeactivateDevilAddr = func.addr;
	}

	// Input Updates
	{
		constexpr byte8 sect0[] =
		{
			0x0F, 0xB6, 0x93, 0x00, 0x00, 0x00, 0x00, // movzx edx,byte ptr [rbx+0000B8C0]
			0xE8, 0x00, 0x00, 0x00, 0x00,             // call dmc3.exe+32CC70
			0x66, 0x23, 0x83, 0x00, 0x00, 0x00, 0x00, // and ax,[rbx+0000B8C0]
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x1EBD32), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint32 *>(func.sect0 + 3) = offsetof(ActorData, newGamepad);
		WriteCall((func.sect0 + 7), (appBaseAddr + 0x32CC70));
		*reinterpret_cast<uint32 *>(func.sect0 + 0xF) = offsetof(ActorData, newButtonMask);
		InputUpdateAddr[0] = func.addr;
		/*
		dmc3.exe+1EBD2D - E8 3E0F1400 - call dmc3.exe+32CC70
		dmc3.exe+1EBD32 - 33 D2       - xor edx,edx
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0x0F, 0xB6, 0x93, 0x00, 0x00, 0x00, 0x00, // movzx edx,byte ptr [rbx+0000B8C0]
			0xE8, 0x00, 0x00, 0x00, 0x00,             // call dmc3.exe+32CC80
			0x66, 0x23, 0x83, 0x00, 0x00, 0x00, 0x00, // and ax,[rbx+0000B8C0]
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x1EBD47), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint32 *>(func.sect0 + 3) = offsetof(ActorData, newGamepad);
		WriteCall((func.sect0 + 7), (appBaseAddr + 0x32CC80));
		*reinterpret_cast<uint32 *>(func.sect0 + 0xF) = offsetof(ActorData, newButtonMask);
		InputUpdateAddr[1] = func.addr;
		/*
		dmc3.exe+1EBD42 - E8 390F1400      - call dmc3.exe+32CC80
		dmc3.exe+1EBD47 - 0FB7 93 E0740000 - movzx edx,word ptr [rbx+000074E0]
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0x66, 0x23, 0x8B, 0x00, 0x00, 0x00, 0x00, //and cx,[rbx+0000B8C0]
			0x66, 0x89, 0x8B, 0xE4, 0x74, 0x00, 0x00, //mov [rbx+000074E4],cx
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x1EBD6B), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint32 *>(func.sect0 + 3) = offsetof(ActorData, newButtonMask);
		InputUpdateAddr[2] = func.addr;
		/*
		dmc3.exe+1EBD64 - 66 89 8B E4740000 - mov [rbx+000074E4],cx
		dmc3.exe+1EBD6B - 66 23 D0          - and dx,ax
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0x66, 0x23, 0x93, 0x00, 0x00, 0x00, 0x00, //and dx,[rbx+0000B8C0]
			0x66, 0x89, 0x93, 0xE6, 0x74, 0x00, 0x00, //mov [rbx+000074E6],dx
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x1EBD7C), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint32 *>(func.sect0 + 3) = offsetof(ActorData, newButtonMask);
		InputUpdateAddr[3] = func.addr;
		/*
		dmc3.exe+1EBD75 - 66 89 93 E6740000 - mov [rbx+000074E6],dx
		dmc3.exe+1EBD7C - 33 D2             - xor edx,edx
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0x0F, 0xB6, 0x93, 0x00, 0x00, 0x00, 0x00, // movzx edx,byte ptr [rbx+0000B8C0]
			0xE8, 0x00, 0x00, 0x00, 0x00,             // call dmc3.exe+32CC10
			0x80, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x01, // cmp byte ptr [rbx+0000B8C0],01
			0x74, 0x03,                               // je short
			0x66, 0x31, 0xC0,                         // xor ax,ax
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x1EBD83), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint32 *>(func.sect0 + 3) = offsetof(ActorData, newGamepad);
		WriteCall((func.sect0 + 7), (appBaseAddr + 0x32CC10));
		*reinterpret_cast<uint32 *>(func.sect0 + 0xE) = offsetof(ActorData, newEnableRightStick);
		InputUpdateAddr[4] = func.addr;
		/*
		dmc3.exe+1EBD7E - E8 8D0E1400 - call dmc3.exe+32CC10
		dmc3.exe+1EBD83 - 33 D2       - xor edx,edx
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0x0F, 0xB6, 0x93, 0x00, 0x00, 0x00, 0x00, // movzx edx,byte ptr [rbx+0000B8C0]
			0xE8, 0x00, 0x00, 0x00, 0x00,             // call dmc3.exe+32CC10
			0x80, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x01, // cmp byte ptr [rbx+0000B8C0],01
			0x74, 0x03,                               // je short
			0x66, 0x31, 0xC0,                         // xor ax,ax
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x1EBD9C), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint32 *>(func.sect0 + 3) = offsetof(ActorData, newGamepad);
		WriteCall((func.sect0 + 7), (appBaseAddr + 0x32CC10));
		*reinterpret_cast<uint32 *>(func.sect0 + 0xE) = offsetof(ActorData, newEnableLeftStick);
		InputUpdateAddr[5] = func.addr;
		/*
		dmc3.exe+1EBD97 - E8 740E1400 - call dmc3.exe+32CC10
		dmc3.exe+1EBD9C - 45 33 C0    - xor r8d,r8d
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0x0F, 0xB6, 0x93, 0x00, 0x00, 0x00, 0x00, // movzx edx,byte ptr [rbx+0000B8C0]
			0xE8, 0x00, 0x00, 0x00, 0x00,             // call dmc3.exe+32CC50
			0x80, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x01, // cmp byte ptr [rbx+0000B8C0],01
			0x74, 0x03,                               // je short
			0x66, 0x31, 0xC0,                         // xor ax,ax
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x1EBDB4), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint32 *>(func.sect0 + 3) = offsetof(ActorData, newGamepad);
		WriteCall((func.sect0 + 7), (appBaseAddr + 0x32CC50));
		*reinterpret_cast<uint32 *>(func.sect0 + 0xE) = offsetof(ActorData, newEnableRightStick);
		InputUpdateAddr[6] = func.addr;
		/*
		dmc3.exe+1EBDAF - E8 9C0E1400 - call dmc3.exe+32CC50
		dmc3.exe+1EBDB4 - 33 D2       - xor edx,edx
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0x0F, 0xB6, 0x93, 0x00, 0x00, 0x00, 0x00, // movzx edx,byte ptr [rbx+0000B8C0]
			0xE8, 0x00, 0x00, 0x00, 0x00,             // call dmc3.exe+32CC50
			0x80, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x01, // cmp byte ptr [rbx+0000B8C0],01
			0x74, 0x03,                               // je short
			0x66, 0x31, 0xC0,                         // xor ax,ax
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x1EBE9D), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint32 *>(func.sect0 + 3) = offsetof(ActorData, newGamepad);
		WriteCall((func.sect0 + 7), (appBaseAddr + 0x32CC50));
		*reinterpret_cast<uint32 *>(func.sect0 + 0xE) = offsetof(ActorData, newEnableLeftStick);
		InputUpdateAddr[7] = func.addr;
		/*
		dmc3.exe+1EBE98 - E8 B30D1400       - call dmc3.exe+32CC50
		dmc3.exe+1EBE9D - 66 89 83 0A750000 - mov [rbx+0000750A],ax
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc3.exe+2ACD0
			0x44, 0x8B, 0xC7,             // mov r8d,edi
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x2AFC6), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteCall(func.sect0, (appBaseAddr + 0x2ACD0));
		InputUpdateAddr[8] = func.addr;
		/*
		dmc3.exe+2AFA5 - E8 26FDFFFF - call dmc3.exe+2ACD0
		dmc3.exe+2AFC6 - 49 6B C8 2C - imul rcx,r8,2C
		*/
	}



	// Ebony & Ivory Rain Storm Check
	{
		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};
		constexpr byte8 sect2[] =
		{
			0x84, 0xC0,                         // test al,al
			0x0F, 0x84, 0x00, 0x00, 0x00, 0x00, // je dmc3.exe+20CC14
		};
		auto func = CreateFunction(EbonyIvoryRainStormCheck, (appBaseAddr + 0x20CC20), true, false, 0, sizeof(sect1), sizeof(sect2));
		memcpy(func.sect1, sect1, sizeof(sect1));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteAddress((func.sect2 + 2), (appBaseAddr + 0x20CC14), 6);
		EbonyIvoryRainStormCheckAddr = func.addr;
		/*
		dmc3.exe+20CC0F - 0FA3 C1             - bt ecx,eax
		dmc3.exe+20CC12 - 72 0C               - jb dmc3.exe+20CC20
		dmc3.exe+20CC14 - BF 01000000         - mov edi,00000001
		dmc3.exe+20CC20 - F3 0F10 83 383E0000 - movss xmm0,[rbx+00003E38]
		*/
	}

	// // Summoned Swords Quicksilver Check
	// {
	// 	constexpr byte8 sect0[] =
	// 	{
	// 		0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax
	// 		0x8A, 0x00,                                                 // mov al,[rax]
	// 		0x84, 0xC0,                                                 // test al,al
	// 		0x75, 0x05,                                                 // jne short
	// 		0xF3, 0x0F, 0x5C, 0x43, 0x14,                               // subss xmm0,[rbx+14]
	// 	};
	// 	auto func = CreateFunction(0, (appBaseAddr + 0x1DB8FD), false, true, sizeof(sect0));
	// 	memcpy(func.sect0, sect0, sizeof(sect0));
	// 	*reinterpret_cast<bool **>(func.sect0 + 2) = &g_quicksilver;
	// 	SummonedSwordsQuicksilverCheckAddr = func.addr;
	// 	/*
	// 	dmc3.exe+1DB8F8 - F3 0F5C 43 14 - subss xmm0,[rbx+14]
	// 	dmc3.exe+1DB8FD - 0F2F F0       - comiss xmm6,xmm0
	// 	*/
	// }

	// Dot Shadow Check
	{
		constexpr byte8 sect2[] =
		{
			0x84, 0xC0,             // test al,al
			0x74, 0x01,             // je short
			0xC3,                   // ret
			0x40, 0x53,             // push rbx
			0x48, 0x83, 0xEC, 0x20, // sub rsp,20
		};
		auto func = CreateFunction(DotShadowCheck, (appBaseAddr + 0x93D66), true, false, 0, 0, sizeof(sect2));
		memcpy(func.sect2, sect2, sizeof(sect2));
		DotShadowCheckAddr = func.addr;
		/*
		dmc3.exe+93D60 - 40 53       - push rbx
		dmc3.exe+93D62 - 48 83 EC 20 - sub rsp,20
		dmc3.exe+93D66 - 48 8B D9    - mov rbx,rcx
		*/
	}

	// Reset Actor Mode
	{
		constexpr byte8 sect0[] =
		{
			0x48, 0x8B, 0x5C, 0x24, 0x50, // mov rbx,[rsp+50]
		};
		auto func = CreateFunction(ResetActorMode, (appBaseAddr + 0x1E14E6), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		ResetActorModeAddr = func.addr;
		/*
		dmc3.exe+1E14E1 - 48 8B 5C 24 50 - mov rbx,[rsp+50]
		dmc3.exe+1E14E6 - 48 83 C4 40    - add rsp,40
		*/
	}






	// Collision Check
	{
		constexpr byte8 sect2[] =
		{
			0x84, 0xC0,                   // test al,al
			0x74, 0x01,                   // je short
			0xC3,                         // ret
			0x48, 0x89, 0x5C, 0x24, 0x08, // mov [rsp+08],rbx
		};
		auto func = CreateFunction(CollisionCheck, (appBaseAddr + 0x5C325), true, false, 0, 0, sizeof(sect2));
		memcpy(func.sect2, sect2, sizeof(sect2));
		CollisionCheckAddr = func.addr;
		/*
		dmc3.exe+5C320 - 48 89 5C 24 08 - mov [rsp+08],rbx
		dmc3.exe+5C325 - 48 89 74 24 10 - mov [rsp+10],rsi
		*/
	}





	// Reset Visibility Air Trick Dante
	{
		constexpr byte8 sect0[] =
		{
			0x89, 0x8F, 0x20, 0x01, 0x00, 0x00, // mov [rdi+00000120],ecx
		};
		constexpr byte8 sect1[] =
		{
			mov_rcx_rdi,
		};
		auto func = CreateFunction(ResetVisibility, (appBaseAddr + 0x1F1F32), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		ResetVisibilityAddr[0] = func.addr;
		/*
		dmc3.exe+1F1F2C - 89 8F 20010000 - mov [rdi+00000120],ecx
		dmc3.exe+1F1F32 - 48 8B CF       - mov rcx,rdi
		*/
	}

	// Reset Visibility Air Trick Vergil, Trick Up & Trick Down
	{
		constexpr byte8 sect0[] =
		{
			0x89, 0xBB, 0x20, 0x01, 0x00, 0x00, // mov [rbx+00000120],edi
		};
		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};
		auto func = CreateFunction(ResetVisibility, (appBaseAddr + 0x1F0724), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		ResetVisibilityAddr[1] = func.addr;
		/*
		dmc3.exe+1F071E - 89 BB 20010000    - mov [rbx+00000120],edi
		dmc3.exe+1F0724 - 66 39 BB 1A3E0000 - cmp [rbx+00003E1A],di
		*/
	}









	// Enable Visibility Check
	{
		constexpr byte8 sect0[] =
		{
			0x48, 0x8B, 0xD9,                         // mov rbx,rcx
			0x80, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x01, // cmp byte ptr [rcx+0000B8C0],01
			0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,       // jne dmc3.exe+1DFD56
			0x83, 0xB9, 0x20, 0x01, 0x00, 0x00, 0x00, // cmp dword ptr [rcx+00000120],00
			0x0F, 0x84, 0x00, 0x00, 0x00, 0x00,       // je dmc3.exe+1DFD56
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x1DFD22), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint32 *>(func.sect0 + 5) = offsetof(ActorData, newEnableVisibility);
		WriteAddress((func.sect0 + 0xA), (appBaseAddr + 0x1DFD56), 6);
		WriteAddress((func.sect0 + 0x17), (appBaseAddr + 0x1DFD56), 6);
		EnableVisibilityCheckAddr[0] = func.addr;
		/*
		dmc3.exe+1DFD16 - 83 B9 20010000 00 - cmp dword ptr [rcx+00000120],00
		dmc3.exe+1DFD1D - 48 8B D9          - mov rbx,rcx
		dmc3.exe+1DFD20 - 74 34             - je dmc3.exe+1DFD56
		dmc3.exe+1DFD22 - 48 63 81 6C3E0000 - movsxd rax,dword ptr [rcx+00003E6C]
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0x80, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x01, // cmp byte ptr [rax+0000B8C0],01
			0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,       // jne dmc3.exe+1FDE7F
			0x83, 0xB8, 0x20, 0x01, 0x00, 0x00, 0x00, // cmp dword ptr [rax+00000120],00
			0x0F, 0x84, 0x00, 0x00, 0x00, 0x00,       // je dmc3.exe+1FDE7F
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x1FDE29), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ActorData, newEnableVisibility);
		WriteAddress((func.sect0 + 7), (appBaseAddr + 0x1FDE7F), 6);
		WriteAddress((func.sect0 + 0x14), (appBaseAddr + 0x1FDE7F), 6);
		EnableVisibilityCheckAddr[1] = func.addr;
		/*
		dmc3.exe+1FDE20 - 83 B8 20010000 00 - cmp dword ptr [rax+00000120],00
		dmc3.exe+1FDE27 - 74 56             - je dmc3.exe+1FDE7F
		dmc3.exe+1FDE29 - 48 89 5C 24 30    - mov [rsp+30],rbx
		*/
	}




	// Play Quicksilver Motion
	{
		auto func = CreateFunction(PlayQuicksilverMotion, (appBaseAddr + 0x1F63B7));
		PlayQuicksilverMotionAddr[0] = func.addr;
		/*
		dmc3.exe+1F63B2 - E8 D997FFFF - call dmc3.exe+1EFB90
		dmc3.exe+1F63B7 - BA 01000000 - mov edx,00000001
		*/
	}
	{
		auto func = CreateFunction(PlayQuicksilverMotion, (appBaseAddr + 0x1F63DB));
		PlayQuicksilverMotionAddr[1] = func.addr;
		/*
		dmc3.exe+1F63D6 - E8 B597FFFF    - call dmc3.exe+1EFB90
		dmc3.exe+1F63DB - FE 83 103E0000 - inc byte ptr [rbx+00003E10]
		*/
	}





	// // Magic Points Run Out
	// {
	// 	constexpr byte8 sect0[] =
	// 	{
	// 		0xC7, 0x81, 0xB8, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov [rcx+00003EB8],00000000
	// 	};
	// 	auto func = CreateFunction(MagicPointsRunOut, (appBaseAddr + 0x1E1860), true, true, sizeof(sect0));
	// 	memcpy(func.sect0, sect0, sizeof(sect0));
	// 	MagicPointsRunOutAddr = func.addr;
	// 	/*
	// 	dmc3.exe+1E1856 - C7 81 B83E0000 00000000 - mov [rcx+00003EB8],00000000
	// 	dmc3.exe+1E1860 - F3 0F10 81 B83E0000     - movss xmm0,[rcx+00003EB8]
	// 	*/
	// }












}

// @Todo: Remove.
export void Actor_MiniToggle(bool enable)
{
	LogFunction(enable);

	// Actor Data Size
	{
		constexpr uint32 size = (128 * 1024);
		// Dante
		Write<uint32>((appBaseAddr + 0x1DEBE1 + 1), (enable) ? size : ACTOR_DATA_SIZE_DANTE); // dmc3.exe+1DEBE1 - BA C0B80000 - mov edx,0000B8C0
		// Bob
		Write<uint32>((appBaseAddr + 0x1DEAC8 + 1), (enable) ? size : ACTOR_DATA_SIZE_BOB); // dmc3.exe+1DEAC8 - BA 80B60000 - mov edx,0000B680
		// Lady
		Write<uint32>((appBaseAddr + 0x1DE9CC + 1), (enable) ? size : ACTOR_DATA_SIZE_LADY); // dmc3.exe+1DE9CC - BA 80820000 - mov edx,00008280
		// Vergil
		Write<uint32>((appBaseAddr + 0x1DE8B3 + 1), (enable) ? size : ACTOR_DATA_SIZE_VERGIL); // dmc3.exe+1DE8B3 - BA C0B80000 - mov edx,0000B8C0
	}

	ToggleRelocations           (enable);
	ToggleModelCountAdjustments (enable);
	ToggleWeaponCountAdjustments(enable);

	// Update Model Dante
	{
		auto dest = (appBaseAddr + 0x212CB3);
		if (enable)
		{
			WriteCall(dest, UpdateModelDanteAddr);
		}
		else
		{
			WriteCall(dest, (appBaseAddr + 0x214D50));
		}
		/*
		dmc3.exe+212CB3 - E8 98200000       - call dmc3.exe+214D50
		dmc3.exe+212CB8 - 48 8D 86 A0380000 - lea rax,[rsi+000038A0]
		*/
	}
}




export void Actor_Toggle(bool enable)
{
	LogFunction(enable);

	ToggleRelocations           (enable);
	ToggleModelCountAdjustments (enable);
	ToggleWeaponCountAdjustments(enable);
	ToggleMainActorFixes        (enable);
	ToggleStyleFixes            (enable);
	ToggleIsWeaponReady         (enable);
	ToggleMobility              (enable);
	ToggleSpeed                 (enable);

	// Actor Data Size
	{
		constexpr uint32 size = (128 * 1024);
		// Dante
		Write<uint32>((appBaseAddr + 0x1DEBE1 + 1), (enable) ? size : ACTOR_DATA_SIZE_DANTE); // dmc3.exe+1DEBE1 - BA C0B80000 - mov edx,0000B8C0
		// Bob
		Write<uint32>((appBaseAddr + 0x1DEAC8 + 1), (enable) ? size : ACTOR_DATA_SIZE_BOB); // dmc3.exe+1DEAC8 - BA 80B60000 - mov edx,0000B680
		// Lady
		Write<uint32>((appBaseAddr + 0x1DE9CC + 1), (enable) ? size : ACTOR_DATA_SIZE_LADY); // dmc3.exe+1DE9CC - BA 80820000 - mov edx,00008280
		// Vergil
		Write<uint32>((appBaseAddr + 0x1DE8B3 + 1), (enable) ? size : ACTOR_DATA_SIZE_VERGIL); // dmc3.exe+1DE8B3 - BA C0B80000 - mov edx,0000B8C0
	}

	// Model Physics Metadata Pool Offsets
	{
		auto off = reinterpret_cast<byte8 *>(modelPhysicsMetadataPoolOff);
		auto defaultOff = (appBaseAddr + 0x4E0328);
		WriteAddress((appBaseAddr + 0x1FA60B), (enable) ? off : defaultOff, 7); // dmc3.exe+1FA60B - 48 8D 0D 165D2E00 - lea rcx,[dmc3.exe+4E0328]
		WriteAddress((appBaseAddr + 0x1FAA57), (enable) ? off : defaultOff, 7); // dmc3.exe+1FAA57 - 48 8D 0D CA582E00 - lea rcx,[dmc3.exe+4E0328]
		WriteAddress((appBaseAddr + 0x1FAA77), (enable) ? off : defaultOff, 7); // dmc3.exe+1FAA77 - 48 8D 15 AA582E00 - lea rdx,[dmc3.exe+4E0328]
		WriteAddress((appBaseAddr + 0x1FAA97), (enable) ? off : defaultOff, 7); // dmc3.exe+1FAA97 - 4C 8D 05 8A582E00 - lea r8,[dmc3.exe+4E0328]
		WriteAddress((appBaseAddr + 0x1FB031), (enable) ? off : defaultOff, 7); // dmc3.exe+1FB031 - 48 8D 3D F0522E00 - lea rdi,[dmc3.exe+4E0328]
		WriteAddress((appBaseAddr + 0x1FBAC4), (enable) ? off : defaultOff, 7); // dmc3.exe+1FBAC4 - 48 8D 3D 5D482E00 - lea rdi,[dmc3.exe+4E0328]
	}

	// Update Model Dante
	{
		auto dest = (appBaseAddr + 0x212CB3);
		if (enable)
		{
			WriteCall(dest, UpdateModelDanteAddr);
		}
		else
		{
			WriteCall(dest, (appBaseAddr + 0x214D50));
		}
		/*
		dmc3.exe+212CB3 - E8 98200000       - call dmc3.exe+214D50
		dmc3.exe+212CB8 - 48 8D 86 A0380000 - lea rax,[rsi+000038A0]
		*/
	}

	// Update Model Vergil
	{
		auto dest = (appBaseAddr + 0x220A30);
		if (enable)
		{
			WriteCall(dest, UpdateModelVergilAddr);
		}
		else
		{
			WriteCall(dest, (appBaseAddr + 0x221FE0));
		}
		/*
		dmc3.exe+220A30 - E8 AB150000          - call dmc3.exe+221FE0
		dmc3.exe+220A35 - 49 8D 84 24 A0380000 - lea rax,[r12+000038A0]
		*/
	}

	// Update Model Partitions Dante
	{
		auto dest = (appBaseAddr + 0x215577);
		if (enable)
		{
			SetMemory(dest, 0x90, 5, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			WriteCall(dest, (appBaseAddr + 0x2169F0));
		}
		/*
		dmc3.exe+215577 - E8 74140000       - call dmc3.exe+2169F0
		dmc3.exe+21557C - 48 81 C7 40750000 - add rdi,00007540
		*/
	}

	// Update Model Partitions Vergil
	{
		auto dest = (appBaseAddr + 0x22285C);
		if (enable)
		{
			SetMemory(dest, 0x90, 5, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			WriteCall(dest, (appBaseAddr + 0x223420));
		}
		/*
		dmc3.exe+22285C - E8 BF0B0000       - call dmc3.exe+223420
		dmc3.exe+222861 - 48 8D B7 40750000 - lea rsi,[rdi+00007540]
		*/
	}

	// Coat Update Dante
	{
		auto dest = (appBaseAddr + 0x2120C4);
		if (enable)
		{
			WriteJump(dest, CoatUpdateDanteAddr, 2);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0x48, 0x8B, 0x96, 0x98, 0x18, 0x00, 0x00, // mov rdx,[rsi+00001898]
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+2120C4 - 48 8B 96 98180000 - mov rdx,[rsi+00001898]
		dmc3.exe+2120CB - 48 8D 8E 40750000 - lea rcx,[rsi+00007540]
		*/
	}

	// Coat Update Vergil
	{
		auto dest = (appBaseAddr + 0x220506);
		if (enable)
		{
			WriteJump(dest, CoatUpdateVergilAddr, 2);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0x48, 0x8B, 0x96, 0x98, 0x18, 0x00, 0x00, // mov rdx,[rsi+00001898]
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+220506 - 48 8B 96 98180000 - mov rdx,[rsi+00001898]
		dmc3.exe+22050D - 48 8D 8E 40750000 - lea rcx,[rsi+00007540]
		*/
	}

	// Devil Coat Update Ignore Range Check
	{
		WriteAddress((appBaseAddr + 0x218982), (enable) ? (appBaseAddr + 0x218988) : (appBaseAddr + 0x218F81), 6);
		/*
		dmc3.exe+218982 - 0F87 F9050000     - ja dmc3.exe+218F81
		dmc3.exe+218988 - 83 BF 183A0000 01 - cmp dword ptr [rdi+00003A18],01
		*/
	}

	// Position Update Ebony & Ivory
	{
		auto dest = (appBaseAddr + 0x22B60F);
		if (enable)
		{
			WriteJump(dest, PositionUpdateEbonyIvoryAddr, 2);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0x0F, 0xB6, 0x90, 0x9E, 0x3E, 0x00, 0x00, // movzx edx,byte ptr [rax+00003E9E]
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+22B60F - 0FB6 90 9E3E0000 - movzx edx,byte ptr [rax+00003E9E]
		dmc3.exe+22B616 - 8D 42 FD         - lea eax,[rdx-03]
		*/
	}

	// Position Update Artemis
	{
		auto dest = (appBaseAddr + 0x22EC27);
		if (enable)
		{
			WriteJump(dest, PositionUpdateArtemisAddr, 2);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0x0F, 0xB6, 0x82, 0x9E, 0x3E, 0x00, 0x00, // movzx eax,byte ptr [rdx+00003E9E]
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+22EC27 - 0FB6 82 9E3E0000 - movzx eax,byte ptr [rdx+00003E9E]
		dmc3.exe+22EC2E - 3C 07            - cmp al,07
		*/
	}

	// Weapon Switch Controller Dante
	{
		auto dest = (appBaseAddr + 0x1E25EB);
		if (enable)
		{
			WriteCall(dest, WeaponSwitchControllerDanteAddr);
		}
		else
		{
			WriteCall(dest, (appBaseAddr + 0x1EA8E0));
		}
		/*
		dmc3.exe+1E25EB - E8 F0820000 - call dmc3.exe+1EA8E0
		dmc3.exe+1E25F0 - 48 8B CB    - mov rcx,rbx
		*/
	}

	// Weapon Switch Controller Vergil
	{
		auto dest = (appBaseAddr + 0x1E25E1);
		if (enable)
		{
			WriteCall(dest, WeaponSwitchControllerVergilAddr);
		}
		else
		{
			WriteCall(dest, (appBaseAddr + 0x1E6DD0));
		}
		/*
		dmc3.exe+1E25E1 - E8 EA470000 - call dmc3.exe+1E6DD0
		dmc3.exe+1E25E6 - EB 08       - jmp dmc3.exe+1E25F0
		*/
	}

	// Activate Quicksilver
	{
		auto dest = (appBaseAddr + 0x1E94AA);
		if (enable)
		{
			WriteJump(dest, ActivateQuicksilverAddr, 2);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0xC6, 0x87, 0x61, 0x63, 0x00, 0x00, 0x01, // mov byte ptr [rdi+00006361],01
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1E94AA - C6 87 61630000 01       - mov byte ptr [rdi+00006361],01
		dmc3.exe+1E94B1 - C7 87 40630000 02000000 - mov [rdi+00006340],00000002
		*/
	}

	// Deactivate Quicksilver
	{
		auto dest = (appBaseAddr + 0x1E9551);
		if (enable)
		{
			WriteJump(dest, DeactivateQuicksilverAddr[0], 2);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0x40, 0x88, 0xB7, 0x61, 0x63, 0x00, 0x00, // mov [rdi+00006361],sil
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1E9551 - 40 88 B7 61630000 - mov [rdi+00006361],sil
		dmc3.exe+1E9558 - 89 B7 40630000    - mov [rdi+00006340],esi
		*/
	}
	{
		auto dest = (appBaseAddr + 0x1EAC19);
		if (enable)
		{
			WriteJump(dest, DeactivateQuicksilverAddr[1], 2);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0xC6, 0x81, 0x61, 0x63, 0x00, 0x00, 0x00, // mov byte ptr [rcx+00006361],00
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1EAC19 - C6 81 61630000 00       - mov byte ptr [rcx+00006361],00
		dmc3.exe+1EAC20 - C7 81 40630000 00000000 - mov [rcx+00006340],00000000
		*/
	}







	// Activate Doppelganger
	{
		auto dest = (appBaseAddr + 0x1E9235);
		if (enable)
		{
			WriteJump(dest, ActivateDoppelgangerAddr, 5);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0xC7, 0x87, 0x54, 0x64, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, // mov [rdi+00006454],00000001
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1E9235 - C7 87 54640000 01000000 - mov [rdi+00006454],00000001
		dmc3.exe+1E923F - 8B 88 EC010000          - mov ecx,[rax+000001EC]
		dmc3.exe+1E930E - B0 01                   - mov al,01
		*/
	}

	// Deactivate Doppelganger
	{
		auto dest = (appBaseAddr + 0x1E933B);
		if (enable)
		{
			WriteJump(dest, DeactivateDoppelgangerAddr[0], 5);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0xC7, 0x87, 0x54, 0x64, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, // mov [rdi+00006454],00000002
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1E933B - C7 87 54640000 02000000 - mov [rdi+00006454],00000002
		dmc3.exe+1E9345 - 8B 88 EC010000          - mov ecx,[rax+000001EC]
		dmc3.exe+1E930E - B0 01                   - mov al,01
		*/
	}
	{
		auto dest = (appBaseAddr + 0x1F89E9);
		if (enable)
		{
			WriteJump(dest, DeactivateDoppelgangerAddr[1], 5);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0xC7, 0x87, 0x54, 0x64, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, // mov [rdi+00006454],00000002
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1F89E9 - C7 87 54640000 02000000 - mov [rdi+00006454],00000002
		dmc3.exe+1F89F3 - 48 8B CF                - mov rcx,rdi
		dmc3.exe+1F8A00 - 80 BF 61630000 01       - cmp byte ptr [rdi+00006361],01
		*/
	}

















	// Disable Doppelganger Rate Controller
	{
		Write<byte8>((appBaseAddr + 0x1E25C8), (enable) ? 0xEB : 0x75);
		/*
		dmc3.exe+1E25C1 - 80 BB 62630000 01 - cmp byte ptr [rbx+00006362],01
		dmc3.exe+1E25C8 - 75 08             - jne dmc3.exe+1E25D2
		*/
	}

	// Devil Doppelganger Check
	{
		Write<byte8>((appBaseAddr + 0x1E7775), (enable) ? 0xEB : 0x75);
		/*
		dmc3.exe+1E776E - 80 BF 62630000 01 - cmp byte ptr [rdi+00006362],01
		dmc3.exe+1E7775 - 75 0E             - jne dmc3.exe+1E7785
		*/
	}
	{
		auto dest = (appBaseAddr + 0x1E77DC);
		if (enable)
		{
			WriteJump(dest, DevilButtonCheckAddr, 2);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0x40, 0x38, 0xB7, 0x9B, 0x3E, 0x00, 0x00, // cmp [rdi+00003E9B],sil
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1E77DC - 40 38 B7 9B3E0000 - cmp [rdi+00003E9B],sil
		dmc3.exe+1E77E3 - 0F85 D4000000     - jne dmc3.exe+1E78BD
		*/
	}

	// Activate Devil
	{
		auto dest = (appBaseAddr + 0x1E78A5);
		if (enable)
		{
			SetMemory(dest, 0x90, 5, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			WriteCall(dest, (appBaseAddr + 0x1F92C0));
		}
		/*
		dmc3.exe+1E78A5 - E8 161A0100 - call dmc3.exe+1F92C0
		dmc3.exe+1E78AA - B2 01       - mov dl,01
		*/
	}
	{
		auto dest = (appBaseAddr + 0x1E78AF);
		if (enable)
		{
			WriteCall(dest, ActivateDevilAddr);
		}
		else
		{
			WriteCall(dest, (appBaseAddr + 0x1F94D0));
		}
		/*
		dmc3.exe+1E78AF - E8 1C1C0100       - call dmc3.exe+1F94D0
		dmc3.exe+1E78B4 - C6 87 AE3E0000 01 - mov byte ptr [rdi+00003EAE],01
		*/
	}

	// Deactivate Devil
	{
		auto dest = (appBaseAddr + 0x1E78C9);
		if (enable)
		{
			SetMemory(dest, 0x90, 5, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			WriteCall(dest, (appBaseAddr + 0x1F92C0));
		}
		/*
		dmc3.exe+1E78C9 - E8 F2190100       - call dmc3.exe+1F92C0
		dmc3.exe+1E78CE - 48 8B 87 E83D0000 - mov rax,[rdi+00003DE8]
		*/
	}
	{
		auto dest = (appBaseAddr + 0x1E78E6);
		if (enable)
		{
			WriteCall(dest, DeactivateDevilAddr);
		}
		else
		{
			WriteCall(dest, (appBaseAddr + 0x1F94D0));
		}
		/*
		dmc3.exe+1E78E6 - E8 E51B0100 - call dmc3.exe+1F94D0
		dmc3.exe+1E78EB - BA 01000000 - mov edx,00000001
		*/
	}

	// Input Updates
	{
		// Disable Actor Id Check
		WriteAddress((appBaseAddr + 0x1EBD1E), (enable) ? (appBaseAddr + 0x1EBD24) : (appBaseAddr + 0x1EBDBF), 6);
		/*
		dmc3.exe+1EBD1E - 0F85 9B000000 - jne dmc3.exe+1EBDBF
		dmc3.exe+1EBD24 - 33 D2         - xor edx,edx
		*/
	}
	{
		auto dest = (appBaseAddr + 0x1EBD2D);
		if (enable)
		{
			WriteJump(dest, InputUpdateAddr[0]);
		}
		else
		{
			WriteCall(dest, (appBaseAddr + 0x32CC70));
		}
		/*
		dmc3.exe+1EBD2D - E8 3E0F1400 - call dmc3.exe+32CC70
		dmc3.exe+1EBD32 - 33 D2       - xor edx,edx
		*/
	}
	{
		auto dest = (appBaseAddr + 0x1EBD42);
		if (enable)
		{
			WriteJump(dest, InputUpdateAddr[1]);
		}
		else
		{
			WriteCall(dest, (appBaseAddr + 0x32CC80));
		}
		/*
		dmc3.exe+1EBD42 - E8 390F1400      - call dmc3.exe+32CC80
		dmc3.exe+1EBD47 - 0FB7 93 E0740000 - movzx edx,word ptr [rbx+000074E0]
		*/
	}
	{
		auto dest = (appBaseAddr + 0x1EBD64);
		if (enable)
		{
			WriteJump(dest, InputUpdateAddr[2], 2);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0x66, 0x89, 0x8B, 0xE4, 0x74, 0x00, 0x00, // mov [rbx+000074E4],cx
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1EBD64 - 66 89 8B E4740000 - mov [rbx+000074E4],cx
		dmc3.exe+1EBD6B - 66 23 D0          - and dx,ax
		*/
	}
	{
		auto dest = (appBaseAddr + 0x1EBD75);
		if (enable)
		{
			WriteJump(dest, InputUpdateAddr[3], 2);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0x66, 0x89, 0x93, 0xE6, 0x74, 0x00, 0x00, // mov [rbx+000074E6],dx
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1EBD75 - 66 89 93 E6740000 - mov [rbx+000074E6],dx
		dmc3.exe+1EBD7C - 33 D2             - xor edx,edx
		*/
	}
	{
		auto dest = (appBaseAddr + 0x1EBD7E);
		if (enable)
		{
			WriteJump(dest, InputUpdateAddr[4]);
		}
		else
		{
			WriteCall(dest, (appBaseAddr + 0x32CC10));
		}
		/*
		dmc3.exe+1EBD7E - E8 8D0E1400 - call dmc3.exe+32CC10
		dmc3.exe+1EBD83 - 33 D2       - xor edx,edx
		*/
	}
	{
		auto dest = (appBaseAddr + 0x1EBD97);
		if (enable)
		{
			WriteJump(dest, InputUpdateAddr[5]);
		}
		else
		{
			WriteCall(dest, (appBaseAddr + 0x32CC10));
		}
		/*
		dmc3.exe+1EBD97 - E8 740E1400 - call dmc3.exe+32CC10
		dmc3.exe+1EBD9C - 45 33 C0    - xor r8d,r8d
		*/
	}
	{
		auto dest = (appBaseAddr + 0x1EBDAF);
		if (enable)
		{
			WriteJump(dest, InputUpdateAddr[6]);
		}
		else
		{
			WriteCall(dest, (appBaseAddr + 0x32CC50));
		}
		/*
		dmc3.exe+1EBDAF - E8 9C0E1400 - call dmc3.exe+32CC50
		dmc3.exe+1EBDB4 - 33 D2       - xor edx,edx
		*/
	}
	{
		auto dest = (appBaseAddr + 0x1EBE98);
		if (enable)
		{
			WriteJump(dest, InputUpdateAddr[7]);
		}
		else
		{
			WriteCall(dest, (appBaseAddr + 0x32CC50));
		}
		/*
		dmc3.exe+1EBE98 - E8 B30D1400       - call dmc3.exe+32CC50
		dmc3.exe+1EBE9D - 66 89 83 0A750000 - mov [rbx+0000750A],ax
		*/
	}

	// @Todo: Review.
	WriteAddress((appBaseAddr + 0x32D0AA), (enable) ? (appBaseAddr + 0x32D0B0) : (appBaseAddr + 0x32D346), 6);
	/*
	dmc3.exe+32D0AA - 0F85 96020000  - jne dmc3.exe+32D346
	dmc3.exe+32D0B0 - 4C 8D 44 24 38 - lea r8,[rsp+38]
	*/

	Write<uint8>((appBaseAddr + 0x2AF8F + 2), (enable) ? 3 : 1); // @Todo: MAX_PLAYER.
	/*
	dmc3.exe+2AF8F - 83 F9 01 - cmp ecx,01
	dmc3.exe+2AF92 - 76 11    - jna dmc3.exe+2AFA5
	*/

	{
		auto dest = (appBaseAddr + 0x2AFA5);
		if (enable)
		{
			WriteJump(dest, InputUpdateAddr[8]);
		}
		else
		{
			WriteCall(dest, (appBaseAddr + 0x2ACD0));
		}
		/*
		dmc3.exe+2AFA5 - E8 26FDFFFF - call dmc3.exe+2ACD0
		dmc3.exe+2AFC6 - 49 6B C8 2C - imul rcx,r8,2C
		*/
	}

	Write<byte32>((appBaseAddr + 0x32CFB6 + 3), (enable) ? 0x63C : 0x624);
	/*
	dmc3.exe+32CFB6 - 48 81 FE 24060000 - cmp rsi,00000624
	dmc3.exe+32CFBD - 0F8C 7DFEFFFF     - jl dmc3.exe+32CE40
	*/

	// // Update Collision Data
	// {
	// 	auto dest = (appBaseAddr + 0x1EEFFC);
	// 	if (enable)
	// 	{
	// 		WriteJump(dest, UpdateCollisionDataAddr);
	// 	}
	// 	else
	// 	{
	// 		WriteCall(dest, (appBaseAddr + 0x5C260));
	// 	}
	// 	/*
	// 	dmc3.exe+1EEFFC - E8 5FD2E6FF       - call dmc3.exe+5C260
	// 	dmc3.exe+1EF001 - 83 BE 943E0000 03 - cmp dword ptr [rsi+00003E94],03
	// 	*/
	// }

	// @Todo: Review.
	// Reset Lock-On
	{
		auto dest = (appBaseAddr + 0x1F8401);
		if (enable)
		{
			SetMemory(dest, 0x90, 7, MemoryFlags_VirtualProtectDestination);
			constexpr byte8 buffer[] =
			{
				mov_rcx_rdi,
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0x0F, 0xB6, 0x97, 0x18, 0x01, 0x00, 0x00, // movzx edx,byte ptr [rdi+00000118]
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1F8401 - 0FB6 97 18010000 - movzx edx,byte ptr [rdi+00000118]
		dmc3.exe+1F8408 - E8 5321FCFF      - call dmc3.exe+1BA560
		*/
	}
	{
		auto dest = (appBaseAddr + 0x1F90BD);
		if (enable)
		{
			SetMemory(dest, 0x90, 14, MemoryFlags_VirtualProtectDestination);
			constexpr byte8 buffer[] =
			{
				mov_rcx_rdi,
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0x0F, 0xB6, 0x97, 0x18, 0x01, 0x00, 0x00, // movzx edx,byte ptr [rdi+00000118]
				0x48, 0x8B, 0x0D, 0x5D, 0x7D, 0xA9, 0x00, // mov rcx,[dmc3.exe+C90E28]
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1F90BD - 0FB6 97 18010000  - movzx edx,byte ptr [rdi+00000118]
		dmc3.exe+1F90C4 - 48 8B 0D 5D7DA900 - mov rcx,[dmc3.exe+C90E28]
		*/
	}
	{
		auto dest = (appBaseAddr + 0x1BA560);
		if (enable)
		{
			SetMemory(dest, 0x90, 3, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0x48, 0x63, 0xC2, // movsxd rax,edx
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1BA560 - 48 63 C2       - movsxd rax,edx
		dmc3.exe+1BA563 - 41 B9 FF000000 - mov r9d,000000FF
		*/
	}
	{
		auto dest = (appBaseAddr + 0x1BA569);
		if (enable)
		{
			SetMemory(dest, 0x90, 9, MemoryFlags_VirtualProtectDestination);
			constexpr byte8 buffer[] =
			{
				0x4C, 0x8B, 0xC1, // mov r8,rcx
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0x4C, 0x8B, 0x44, 0xC1, 0x18, // mov r8,[rcx+rax*8+18]
				0x4C, 0x8D, 0x14, 0xC1,       // lea r10,[rcx+rax*8]
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1BA569 - 4C 8B 44 C1 18 - mov r8,[rcx+rax*8+18]
		dmc3.exe+1BA56E - 4C 8D 14 C1    - lea r10,[rcx+rax*8]
		*/
	}
	{
		auto dest = (appBaseAddr + 0x1BA5C5);
		if (enable)
		{
			SetMemory(dest, 0x90, 11, MemoryFlags_VirtualProtectDestination);
			constexpr byte8 buffer[] =
			{
				0x45, 0x89, 0x98, 0x40, 0x20, 0x00, 0x00, // mov [r8+00002040],r11d
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0x49, 0x8B, 0x42, 0x18,                   // mov rax,[r10+18]
				0x44, 0x89, 0x98, 0x08, 0x62, 0x00, 0x00, // mov [rax+00006208],r11d
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1BA5C5 - 49 8B 42 18       - mov rax,[r10+18]
		dmc3.exe+1BA5C9 - 44 89 98 08620000 - mov [rax+00006208],r11d
		*/
	}

	// // Disable Reset Visibility
	// {
	// 	auto dest = (appBaseAddr + 0x1F8AEE);
	// 	if (enable)
	// 	{
	// 		SetMemory(dest, 0x90, 10, MemoryFlags_VirtualProtectDestination);
	// 	}
	// 	else
	// 	{
	// 		constexpr byte8 buffer[] =
	// 		{
	// 			0xC7, 0x87, 0x20, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, // mov [rdi+00000120],00000001
	// 		};
	// 		CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
	// 	}
	// 	/*
	// 	dmc3.exe+1F8AEE - C7 87 20010000 01000000 - mov [rdi+00000120],00000001
	// 	dmc3.exe+1F8AF8 - 80 BF 9B3E0000 01       - cmp byte ptr [rdi+00003E9B],01
	// 	*/
	// }
	// {
	// 	auto dest = (appBaseAddr + 0x1F7CBA);
	// 	if (enable)
	// 	{
	// 		SetMemory(dest, 0x90, 10, MemoryFlags_VirtualProtectDestination);
	// 	}
	// 	else
	// 	{
	// 		constexpr byte8 buffer[] =
	// 		{
	// 			0xC7, 0x83, 0x20, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, // mov [rbx+00000120],00000001
	// 		};
	// 		CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
	// 	}
	// 	/*
	// 	dmc3.exe+1F7CBA - C7 83 20010000 01000000 - mov [rbx+00000120],00000001
	// 	dmc3.exe+1F7CC4 - E8 474E0000             - call dmc3.exe+1FCB10
	// 	*/
	// }
	// {
	// 	auto dest = (appBaseAddr + 0x1DFC7F);
	// 	if (enable)
	// 	{
	// 		SetMemory(dest, 0x90, 6, MemoryFlags_VirtualProtectDestination);
	// 	}
	// 	else
	// 	{
	// 		constexpr byte8 buffer[] =
	// 		{
	// 			0x89, 0x81, 0x20, 0x01, 0x00, 0x00, // mov [rcx+00000120],eax
	// 		};
	// 		CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
	// 	}
	// 	/*
	// 	dmc3.exe+1DFC7F - 89 81 20010000    - mov [rcx+00000120],eax
	// 	dmc3.exe+1DFC85 - 48 89 81 583E0000 - mov [rcx+00003E58],rax
	// 	*/
	// }
	// {
	// 	auto dest = (appBaseAddr + 0x1FCA43);
	// 	if (enable)
	// 	{
	// 		SetMemory(dest, 0x90, 6, MemoryFlags_VirtualProtectDestination);
	// 	}
	// 	else
	// 	{
	// 		constexpr byte8 buffer[] =
	// 		{
	// 			0x89, 0x91, 0x20, 0x01, 0x00, 0x00, // mov [rcx+00000120],edx
	// 		};
	// 		CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
	// 	}
	// 	/*
	// 	dmc3.exe+1FCA43 - 89 91 20010000 - mov [rcx+00000120],edx
	// 	dmc3.exe+1FCA49 - 8B EA          - mov ebp,edx
	// 	*/
	// }

	// Force Update Summoned Swords
	{
		WriteAddress((appBaseAddr + 0x1DAF30), (enable) ? (appBaseAddr + 0x1DAF36) : (appBaseAddr + 0x1DB099), 6);
		/*
		dmc3.exe+1DAF30 - 0F84 63010000     - je dmc3.exe+1DB099
		dmc3.exe+1DAF36 - C6 81 E80D0000 00 - mov byte ptr [rcx+00000DE8],00
		*/
	}

	// Dot Shadow Check
	{
		auto dest = (appBaseAddr + 0x93D60);
		if (enable)
		{
			WriteJump(dest, DotShadowCheckAddr, 1);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0x40, 0x53,             // push rbx
				0x48, 0x83, 0xEC, 0x20, // sub rsp,20
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+93D60 - 40 53       - push rbx
		dmc3.exe+93D62 - 48 83 EC 20 - sub rsp,20
		dmc3.exe+93D66 - 48 8B D9    - mov rbx,rcx
		*/
	}

	// Reset Actor Mode
	{
		auto dest = (appBaseAddr + 0x1E14E1);
		if (enable)
		{
			WriteJump(dest, ResetActorModeAddr);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0x48, 0x8B, 0x5C, 0x24, 0x50, // mov rbx,[rsp+50]
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1E14E1 - 48 8B 5C 24 50 - mov rbx,[rsp+50]
		dmc3.exe+1E14E6 - 48 83 C4 40    - add rsp,40
		*/
	}

	// // Disable Actor Data Copy Check
	// {
	// 	auto dest = (appBaseAddr + 0x2198D0);
	// 	if (enable)
	// 	{
	// 		WriteJump(dest, DisableActorDataCopyCheckAddr, 2);
	// 	}
	// 	else
	// 	{
	// 		constexpr byte8 buffer[] =
	// 		{
	// 			0x0F, 0xB6, 0x81, 0x98, 0x64, 0x00, 0x00, // movzx eax,byte ptr [rcx+00006498]
	// 		};
	// 		CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
	// 	}
	// 	/*
	// 	dmc3.exe+2198D0 - 0FB6 81 98640000 - movzx eax,byte ptr [rcx+00006498]
	// 	dmc3.exe+2198D7 - 45 33 C0         - xor r8d,r8d
	// 	*/
	// }

	// Collision Check
	{
		auto dest = (appBaseAddr + 0x5C320);
		if (enable)
		{
			WriteJump(dest, CollisionCheckAddr);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0x48, 0x89, 0x5C, 0x24, 0x08, // mov [rsp+08],rbx
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+5C320 - 48 89 5C 24 08 - mov [rsp+08],rbx
		dmc3.exe+5C325 - 48 89 74 24 10 - mov [rsp+10],rsi
		*/
	}

	// // Quicksilver Check
	// {
	// 	auto dest = (appBaseAddr + 0x1F8A00);
	// 	if (enable)
	// 	{
	// 		WriteJump(dest, QuicksilverCheckAddr, 2);
	// 	}
	// 	else
	// 	{
	// 		constexpr byte8 buffer[] =
	// 		{
	// 			0x80, 0xBF, 0x61, 0x63, 0x00, 0x00, 0x01, // cmp byte ptr [rdi+00006361],01
	// 		};
	// 		CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
	// 	}
	// 	/*
	// 	dmc3.exe+1F8A00 - 80 BF 61630000 01 - cmp byte ptr [rdi+00006361],01
	// 	dmc3.exe+1F8A07 - 0F85 9F000000     - jne dmc3.exe+1F8AAC
	// 	*/
	// }






	// Reset Visibility Air Trick Dante
	{
		auto dest = (appBaseAddr + 0x1F1F2C);
		if (enable)
		{
			WriteJump(dest, ResetVisibilityAddr[0], 1);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0x89, 0x8F, 0x20, 0x01, 0x00, 0x00, // mov [rdi+00000120],ecx
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1F1F2C - 89 8F 20010000 - mov [rdi+00000120],ecx
		dmc3.exe+1F1F32 - 48 8B CF       - mov rcx,rdi
		*/
	}

	// Reset Visibility Air Trick Vergil, Trick Up & Trick Down
	{
		auto dest = (appBaseAddr + 0x1F071E);
		if (enable)
		{
			WriteJump(dest, ResetVisibilityAddr[1], 1);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0x89, 0xBB, 0x20, 0x01, 0x00, 0x00, // mov [rbx+00000120],edi
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1F071E - 89 BB 20010000    - mov [rbx+00000120],edi
		dmc3.exe+1F0724 - 66 39 BB 1A3E0000 - cmp [rbx+00003E1A],di
		*/
	}





	// Enable Visibility Check
	{
		auto dest = (appBaseAddr + 0x1DFD16);
		if (enable)
		{
			WriteJump(dest, EnableVisibilityCheckAddr[0], 2);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0x83, 0xB9, 0x20, 0x01, 0x00, 0x00, 0x00, // cmp dword ptr [rcx+00000120],00
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1DFD16 - 83 B9 20010000 00 - cmp dword ptr [rcx+00000120],00
		dmc3.exe+1DFD1D - 48 8B D9          - mov rbx,rcx
		dmc3.exe+1DFD20 - 74 34             - je dmc3.exe+1DFD56
		dmc3.exe+1DFD22 - 48 63 81 6C3E0000 - movsxd rax,dword ptr [rcx+00003E6C]
		*/
	}
	{
		auto dest = (appBaseAddr + 0x1FDE20);
		if (enable)
		{
			WriteJump(dest, EnableVisibilityCheckAddr[1], 2);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0x83, 0xB8, 0x20, 0x01, 0x00, 0x00, 0x00, // cmp dword ptr [rax+00000120],00
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1FDE20 - 83 B8 20010000 00 - cmp dword ptr [rax+00000120],00
		dmc3.exe+1FDE27 - 74 56             - je dmc3.exe+1FDE7F
		dmc3.exe+1FDE29 - 48 89 5C 24 30    - mov [rsp+30],rbx
		*/
	}



	// Play Quicksilver Motion
	{
		auto dest = (appBaseAddr + 0x1F63B2);
		if (enable)
		{
			WriteJump(dest, PlayQuicksilverMotionAddr[0]);
		}
		else
		{
			WriteCall(dest, (appBaseAddr + 0x1EFB90));
		}
		/*
		dmc3.exe+1F63B2 - E8 D997FFFF - call dmc3.exe+1EFB90
		dmc3.exe+1F63B7 - BA 01000000 - mov edx,00000001
		*/
	}
	{
		auto dest = (appBaseAddr + 0x1F63D6);
		if (enable)
		{
			WriteJump(dest, PlayQuicksilverMotionAddr[1]);
		}
		else
		{
			WriteCall(dest, (appBaseAddr + 0x1EFB90));
		}
		/*
		dmc3.exe+1F63D6 - E8 B597FFFF    - call dmc3.exe+1EFB90
		dmc3.exe+1F63DB - FE 83 103E0000 - inc byte ptr [rbx+00003E10]
		*/
	}




	// // Magic Points Run Out
	// {
	// 	auto dest = (appBaseAddr + 0x1E1856);
	// 	if (enable)
	// 	{
	// 		WriteJump(dest, MagicPointsRunOutAddr, 5);
	// 	}
	// 	else
	// 	{
	// 		constexpr byte8 buffer[] =
	// 		{
	// 			0xC7, 0x81, 0xB8, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov [rcx+00003EB8],00000000
	// 		};
	// 		CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
	// 	}
	// 	/*
	// 	dmc3.exe+1E1856 - C7 81 B83E0000 00000000 - mov [rcx+00003EB8],00000000
	// 	dmc3.exe+1E1860 - F3 0F10 81 B83E0000     - movss xmm0,[rcx+00003EB8]
	// 	*/
	// }




	// Disable Set Style Data
	{
		auto dest = (appBaseAddr + 0x2BAA90);
		if (enable)
		{
			SetMemory(dest, 0x90, 7, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0x48, 0x89, 0x91, 0x10, 0x3D, 0x00, 0x00, // mov [rcx+00003D10],rdx
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+2BAA90 - 48 89 91 103D0000 - mov [rcx+00003D10],rdx
		dmc3.exe+2BAA97 - C3                - ret 
		*/
	}




	ToggleSound(enable);








}

export void ToggleAirHikeCoreAbility(bool enable)
{
	LogFunction(enable);

	Write<byte8>((appBaseAddr + 0x1E9B0E), (enable) ? 0xEB : 0x74);
	/*
	dmc3.exe+1E9B0E - 74 32    - je dmc3.exe+1E9B42
	dmc3.exe+1E9B10 - 80 F9 02 - cmp cl,02
	*/
}

export void ToggleRebellionInfiniteSwordPierce(bool enable)
{
	LogFunction(enable);

	{
		auto dest = (appBaseAddr + 0x1CC9A4);
		if (enable)
		{
			SetMemory(dest, 0x90, 5, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0x4B, 0x14, // subss xmm1,[rbx+14]
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1CC9A4 - F3 0F5C 4B 14 - subss xmm1,[rbx+14]
		dmc3.exe+1CC9A9 - 0F2F C1       - comiss xmm0,xmm1
		*/
	}
	{
		auto dest = (appBaseAddr + 0x1CDA1B);
		if (enable)
		{
			SetMemory(dest, 0x90, 4, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0xC1, // subss xmm0,xmm1
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1CDA1B - F3 0F5C C1             - subss xmm0,xmm1
		dmc3.exe+1CDA1F - 44 0F29 9C 24 A0000000 - movaps [rsp+000000A0],xmm11
		*/
	}
	{
		auto dest = (appBaseAddr + 0x1CDD64);
		if (enable)
		{
			SetMemory(dest, 0x90, 5, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0x4B, 0x14, // subss xmm1,[rbx+14]
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1CDD64 - F3 0F5C 4B 14 - subss xmm1,[rbx+14]
		dmc3.exe+1CDD69 - 0F2F C1       - comiss xmm0,xmm1
		*/
	}
	{
		auto dest = (appBaseAddr + 0x1CDDCE);
		if (enable)
		{
			SetMemory(dest, 0x90, 4, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0xCA, // subss xmm1,xmm2
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1CDDCE - F3 0F5C CA - subss xmm1,xmm2
		dmc3.exe+1CDDD2 - 0F2F C1    - comiss xmm0,xmm1
		*/
	}
	{
		auto dest = (appBaseAddr + 0x21562E);
		if (enable)
		{
			SetMemory(dest, 0x90, 5, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0x47, 0x14, // subss xmm0,[rdi+14]
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+21562E - F3 0F5C 47 14 - subss xmm0,[rdi+14]
		dmc3.exe+215633 - 0F2F F0       - comiss xmm6,xmm0
		*/
	}
}

export void ToggleYamatoForceEdgeInfiniteRoundTrip(bool enable)
{
	LogFunction(enable);

	{
		auto dest = (appBaseAddr + 0x1D86DD);
		if (enable)
		{
			SetMemory(dest, 0x90, 5, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0x47, 0x14, // subss xmm0,[rdi+14]
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1D86DD - F3 0F5C 47 14 - subss xmm0,[rdi+14]
		dmc3.exe+1D86E2 - 0F2F F0       - comiss xmm6,xmm0
		*/
	}
	{
		auto dest = (appBaseAddr + 0x222921);
		if (enable)
		{
			SetMemory(dest, 0x90, 5, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0x47, 0x14, // subss xmm0,[rdi+14]
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+222921 - F3 0F5C 47 14 - subss xmm0,[rdi+14]
		dmc3.exe+222926 - 0F2F F0       - comiss xmm6,xmm0
		*/
	}
}

export void ToggleEbonyIvoryFoursomeTime(bool enable)
{
	LogFunction(enable);

	WriteAddress((appBaseAddr + 0x1E24F6), (enable) ? (appBaseAddr + 0x1E24FC) : (appBaseAddr + 0x1E259C), 6);
	/*
	dmc3.exe+1E24F6 - 0F85 A0000000  - jne dmc3.exe+1E259C
	dmc3.exe+1E24FC - 48 89 7C 24 30 - mov [rsp+30],rdi
	*/

	WriteAddress((appBaseAddr + 0x20D188), (enable) ? (appBaseAddr + 0x20D18A) : (appBaseAddr + 0x20D1AB), 2);
	/*
	dmc3.exe+20D188 - 75 21               - jne dmc3.exe+20D1AB
	dmc3.exe+20D18A - F3 0F10 83 2C690000 - movss xmm0,[rbx+0000692C]
	*/
}

export void ToggleEbonyIvoryInfiniteRainStorm(bool enable)
{
	LogFunction(enable);

	auto dest = (appBaseAddr + 0x20CC0F);
	if (enable)
	{
		WriteJump(dest, EbonyIvoryRainStormCheckAddr);
	}
	else
	{
		constexpr byte8 buffer[] =
		{
			0x0F, 0xA3, 0xC1, // bt ecx,eax
			0x72, 0x0C,       // jb dmc3.exe+20CC20
		};
		CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
	}
	/*
	dmc3.exe+20CC0F - 0FA3 C1             - bt ecx,eax
	dmc3.exe+20CC12 - 72 0C               - jb dmc3.exe+20CC20
	dmc3.exe+20CC14 - BF 01000000         - mov edi,00000001
	dmc3.exe+20CC20 - F3 0F10 83 383E0000 - movss xmm0,[rbx+00003E38]
	*/
}

export void ToggleArtemisSwapNormalShotAndMultiLock(bool enable)
{
	LogFunction(enable);

	{
		auto dest = (appBaseAddr + 0x215C78);
		if (enable)
		{
			constexpr byte8 buffer[] =
			{
				0xC6, 0x87, 0x80, 0xB8, 0x00, 0x00, 0x01, // mov byte ptr [rdi+0000B880],01
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0x44, 0x88, 0xB7, 0x80, 0xB8, 0x00, 0x00, // mov [rdi+0000B880],r14l
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+215C78 - 44 88 B7 80B80000 - mov [rdi+0000B880],r14l
		dmc3.exe+215C7F - 83 F8 02          - cmp eax,02
		*/
	}

	Write<uint8>((appBaseAddr + 0x215CD4 + 6), (enable) ? 0 : 1);
	/*
	dmc3.exe+215CD4 - C6 87 80B80000 01 - mov byte ptr [rdi+0000B880],01
	dmc3.exe+215CDB - 44 0F28 C7        - movaps xmm8,xmm7
	*/
}

export void ToggleArtemisInstantFullCharge(bool enable)
{
	LogFunction(enable);

	WriteAddress((appBaseAddr + 0x215E42), (enable) ? (appBaseAddr + 0x215E48) : (appBaseAddr + 0x215F78), 6);
	/*
	dmc3.exe+215E42 - 0F82 30010000 - jb dmc3.exe+215F78
	dmc3.exe+215E48 - 0F2F C1       - comiss xmm0,xmm1
	*/
}

export void UpdateCrazyComboLevelMultiplier()
{
	LogFunction();

	Write<uint8>((appBaseAddr + 0x5898DE), activeConfig.crazyComboLevelMultiplier);
	Write<uint8>((appBaseAddr + 0x58999E), activeConfig.crazyComboLevelMultiplier);
	Write<uint8>((appBaseAddr + 0x589A5E), activeConfig.crazyComboLevelMultiplier);
}

export void ToggleChronoSwords(bool enable)
{
	return;
	// {
	// 	auto dest = (appBaseAddr + 0x1DB8F8);
	// 	if (enable)
	// 	{
	// 		WriteJump(dest, SummonedSwordsQuicksilverCheckAddr);
	// 	}
	// 	else
	// 	{
	// 		constexpr byte8 buffer[] =
	// 		{
	// 			0xF3, 0x0F, 0x5C, 0x43, 0x14, // subss xmm0,[rbx+14]
	// 		};
	// 		CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
	// 	}
	// 	/*
	// 	dmc3.exe+1DB8F8 - F3 0F5C 43 14 - subss xmm0,[rbx+14]
	// 	dmc3.exe+1DB8FD - 0F2F F0       - comiss xmm6,xmm0
	// 	*/
	// }
}

#pragma region Events

// @Todo: Add event tag.

export void Actor_CreateMainActor(byte8 * actorBaseAddr)
{
	if (!activeConfig.Actor.enable)
	{
		return;
	}

	LogFunction(actorBaseAddr);

	Actor_actorBaseAddr.Clear();

	File_dynamicFiles.Clear();

	Actor_actorBaseAddr[0] = actorBaseAddr;
	Actor_actorBaseAddr.count = 2;


	// if (!actorBaseAddr)
	// {
	// 	return;
	// }
	// auto & actorData = *reinterpret_cast<ActorData *>(actorBaseAddr);

	// actorData.shadow = 0;
	// actorData.lastShadow = 0;



}

export void Actor_CreateCloneActor(byte8 * actorBaseAddr)
{
	if (!activeConfig.Actor.enable)
	{
		return;
	}

	LogFunction(actorBaseAddr);

	Actor_actorBaseAddr[1] = actorBaseAddr;


	// if (!actorBaseAddr)
	// {
	// 	return;
	// }
	// auto & actorData = *reinterpret_cast<ActorData *>(actorBaseAddr);

	// actorData.shadow = 0;
	// actorData.lastShadow = 0;



}

export void Actor_Customize()
{
	if (!activeConfig.Actor.enable)
	{
		return;
	}

	LogFunction();

	SetMainActor(0);
}

export void Actor_Delete()
{
	if (!activeConfig.Actor.enable)
	{
		return;
	}

	LogFunction();

	SetMainActor(0);

	Actor_actorBaseAddr.Clear();

	File_dynamicFiles.Clear();
}


export void Actor_EventContinue()
{
	LogFunction();

	SetMainActor(0);
}





export void Actor_InGameCutsceneStart()
{
	LogFunction();

	for_each(uint32, index, 2, Actor_actorBaseAddr.count)
	{
		IntroduceActorData(actorBaseAddr, actorData, Actor_actorBaseAddr[index], continue);
		IntroduceActorData(actorBaseAddr2, actorData2, Actor_actorBaseAddr[0], continue);

		auto & playerData = GetPlayerData(actorData);

		if
		(
			(actorData.newPlayerIndex == 0) &&
			(actorData.newCharacterIndex == playerData.activeCharacterIndex) &&
			(actorData.newEntityIndex == ENTITY_MAIN)
		)
		{
			actorData.motionArchives[MOTION_GROUP_IN_GAME_CUTSCENE] = actorData2.motionArchives[MOTION_GROUP_IN_GAME_CUTSCENE];

			Log("doppelganger %u", actorData.doppelganger);

			if (actorData.doppelganger)
			{
				actorData.cloneStatus = CLONE_STATUS_DECOMMISSION;

				DeactivateDoppelganger(actorData);
			}

			break;
		}
	}

	// ToggleActor(0, true);
	// ToggleActor(1, false);

	// for_each(uint32, index, 2, Actor_actorBaseAddr.count)
	// {
	// 	ToggleActor(index, false);
	// }

	// SetMainActor(0);
}

export void Actor_InGameCutsceneEnd()
{
	LogFunction();

	// for_each(uint32, index, 2, Actor_actorBaseAddr.count)
	// {
	// 	IntroduceActorData(actorBaseAddr, actorData, Actor_actorBaseAddr[index], continue);

	// 	CommissionActor(actorData);
	// }




	// ToggleActor(0, false);
	// ToggleActor(1, false);

	// for_each(uint32, index, 2, Actor_actorBaseAddr.count)
	// {
	// 	//IntroduceActorData(actorBaseAddr, actorData, index, continue);

	// 	IntroduceActorData(actorBaseAddr, actorData, Actor_actorBaseAddr[index], continue);

	// 	CommissionActor(actorData);
	// }
}







export void Actor_MainLoopOnce()
{
	if (!activeConfig.Actor.enable)
	{
		return;
	}

	LogFunction();

	SpawnActors();

	// if (!InCutscene())
	// {
	// 	Actor_InGameCutsceneEnd();
	// }



	ToggleActor(0, false);
	ToggleActor(1, false);

	// for_each(uint32, index, 2, Actor_actorBaseAddr.count)
	// {
	// 	IntroduceActorData(actorBaseAddr, actorData, Actor_actorBaseAddr[index], continue);

	// 	CommissionActor(actorData);
	// }











	[&]()
	{
		IntroduceSessionData();
		IntroduceEventData(return);
		//IntroduceActorData(actorBaseAddr, actorData, 1, return);

		IntroduceActorData(actorBaseAddr, actorData, Actor_actorBaseAddr[1], return);








		if (sessionData.mission != 19)
		{
			return;
		}
		else if (eventData.room != 421)
		{
			return;
		}
		else if (actorData.character != CHAR_BOB)
		{
			return;
		}

		ToggleActor(actorData, true);

		actorData.doppelganger = true;

		Log("Toggled Bob.");
	}();
}

export void Actor_ActorLoop(byte8 * actorBaseAddr)
{
	if (!activeConfig.Actor.enable)
	{
		return;
	}

	if (!actorBaseAddr)
	{
		return;
	}
	auto & actorData = *reinterpret_cast<ActorData *>(actorBaseAddr);

	if (!actorData.newActorLoopRun)
	{
		actorData.newActorLoopRun = true;

		LogFunction(actorBaseAddr);
	}

	if (InCutscene())
	{
		return;
	}
	else if
	(
		(actorBaseAddr == Actor_actorBaseAddr[0]) ||
		(actorBaseAddr == Actor_actorBaseAddr[1])
	)
	{
		//IntroduceActorData(actorBaseAddr2, actorData2, 2, return);

		IntroduceActorData(actorBaseAddr2, actorData2, Actor_actorBaseAddr[2], return);









		// auto actorBaseAddr2 = Actor_actorBaseAddr[2];
		// if (!actorBaseAddr2)
		// {
		// 	return;
		// }
		// auto & actorData2 = *reinterpret_cast<ActorData *>(actorBaseAddr2);

		CopyState
		(
			actorData2,
			actorData
		);

		return;
	}

	UpdateModelPartitions(actorData);

	if (actorData.character == CHAR_VERGIL)
	{
		IsMeleeWeaponReadyVergilFix(actorData);
	}
}

#pragma endregion

#pragma region Scenes

export void Actor_SceneMain()
{
	LogFunction();

	Actor_Toggle(activeConfig.Actor.enable);
}

export void Actor_SceneMissionSelect()
{
	LogFunction();

	Actor_Toggle(activeConfig.Actor.enable);
}

export void Actor_SceneMissionStart()
{
	LogFunction();

	for_all(uint8, playerIndex, PLAYER_COUNT)
	{
		auto & playerData = GetPlayerData(playerIndex);

		playerData.activeCharacterIndex = playerData.lastCharacterIndex = playerData.characterIndex = 0;

		for_all(uint8, characterIndex, CHARACTER_COUNT){
		for_all(uint8, entityIndex   , ENTITY_COUNT   )
		{
			auto & characterData = GetCharacterData
			(
				playerIndex,
				characterIndex,
				entityIndex
			);

			memset
			(
				characterData.styleIndices,
				0,
				sizeof(characterData.styleIndices)
			);

			characterData.styleButtonIndex  = 0;
			characterData.meleeWeaponIndex  = 0;
			characterData.rangedWeaponIndex = 0;
		}}
	}
}

#pragma endregion

#ifdef __GARBAGE__
#endif
