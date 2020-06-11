#include "Actor.h"

Vector<byte8 *> Actor_actorBaseAddr;

struct IsWeaponReadyProxyHelper_t
{
	uint32 off[2];
	uint8 weaponType;
};

RegisterWeapon_t RegisterWeapon[MAX_WEAPON] = {};

constexpr IsWeaponReadyProxyHelper_t IsWeaponReadyProxyHelper[] =
{
	{ 0x2288D3, 0x2288D8, WEAPON_TYPE_MELEE  }, // Dante Agni & Rudra
	{ 0x2295B7, 0x2295BC, WEAPON_TYPE_MELEE  }, // Dante Vergil Beowulf
	{ 0x229E9D, 0       , WEAPON_TYPE_MELEE  }, // Vergil Force Edge
	{ 0x22AD86, 0x22AD8B, WEAPON_TYPE_MELEE  }, // Dante Nevan
	{ 0x22B723, 0       , WEAPON_TYPE_RANGED }, // Dante Ebony & Ivory Air
	{ 0x22B753, 0       , WEAPON_TYPE_RANGED }, // Dante Ebony & Ivory
	{ 0x22C186, 0       , WEAPON_TYPE_RANGED }, // Dante Lady Kalina Ann
	{ 0x22C1A5, 0       , WEAPON_TYPE_RANGED }, // Dante Kalina Ann Grapple
	{ 0x22CBC8, 0x22CBCD, WEAPON_TYPE_RANGED }, // Dante Artemis
	{ 0x22D432, 0x22D437, WEAPON_TYPE_MELEE  }, // Vergil Nero Angelo Sword
	{ 0x22E09A, 0x22E09F, WEAPON_TYPE_MELEE  }, // Vergil Yamato
	{ 0x22FB1C, 0x22FB21, WEAPON_TYPE_MELEE  }, // Dante Cerberus
	{ 0x2304BF, 0       , WEAPON_TYPE_RANGED }, // Dante Spiral
	{ 0x230DD3, 0       , WEAPON_TYPE_RANGED }, // Dante Shotgun Shot
	{ 0x230E16, 0       , WEAPON_TYPE_RANGED }, // Dante Shotgun
	{ 0x23163F, 0       , WEAPON_TYPE_MELEE  }, // Dante Rebellion
	{ 0x232005, 0       , WEAPON_TYPE_MELEE  }, // Bob Yamato Combo 1 Part 3
	{ 0x232056, 0       , WEAPON_TYPE_MELEE  }, // Bob Yamato
};

byte8 * IsWeaponReadyProxyFuncAddr[countof(IsWeaponReadyProxyHelper)] = {};


























template <typename T>
bool IsWeaponReadyFunction
(
	T     & actorData,
	uint8   weapon,
	uint8 * map,
	uint8   mapItemCount,
	uint8   index
)
{
	if (IsWeaponActive(actorData, weapon))
	{
		return true;
	}

	for_all(uint8, mapIndex, mapItemCount)
	{
		auto & mapItem = map[mapIndex];
		if (mapItem == weapon)
		{
			continue;
		}
		if (IsWeaponActive(actorData, mapItem))
		{
			return false;
		}
	}

	if (map[index] == weapon)
	{
		return true;
	}

	return false;
}

template
<
	typename T,
	uint8 weaponType
>
bool IsWeaponReady
(
	byte8 * baseAddr,
	uint8 weapon
)
{
	auto & actorData = *reinterpret_cast<T *>(baseAddr);
	if constexpr (weaponType == WEAPON_TYPE_MELEE)
	{
		auto result = IsWeaponReadyFunction
		(
			actorData,
			weapon,
			actorData.newMeleeWeapon,
			actorData.newMeleeWeaponCount,
			actorData.newMeleeWeaponIndex
		);
		if constexpr (typematch(T, ACTOR_DATA_DANTE))
		{
			if (result)
			{
				UpdateModelPartitionConfig(actorData, weapon);
			}
		}
		return result;
	}
	else
	{
		return IsWeaponReadyFunction
		(
			actorData,
			weapon,
			actorData.newRangedWeapon,
			actorData.newRangedWeaponCount,
			actorData.newRangedWeaponIndex
		);
	}
}

IsWeaponReady_t IsMeleeWeaponReady[MAX_CHAR] =
{
	IsWeaponReady<ACTOR_DATA_DANTE, WEAPON_TYPE_MELEE>,
	0,
	0,
	IsWeaponReady<ACTOR_DATA_VERGIL, WEAPON_TYPE_MELEE>,
};

IsWeaponReady_t IsRangedWeaponReady[MAX_CHAR] =
{
	IsWeaponReady<ACTOR_DATA_DANTE, WEAPON_TYPE_MELEE>,
	0,
	0,
	0,
};

template <uint8 weaponType>
bool IsWeaponReadyProxy(byte8 * baseAddr)
{
	auto & weapon = *reinterpret_cast<uint8 *>(baseAddr + 0x112);
	auto actorBaseAddr = *reinterpret_cast<byte8 **>(baseAddr + 0x120);
	if (!actorBaseAddr)
	{
		return true;
	}
	auto & actorData = *reinterpret_cast<ACTOR_DATA *>(actorBaseAddr);
	auto character = actorData.character;
	if (character >= MAX_CHAR)
	{
		character = CHAR_DANTE;
	}
	auto & func = (weaponType == WEAPON_TYPE_MELEE) ? IsMeleeWeaponReady[character] : IsRangedWeaponReady[character];
	if (!func)
	{
		return true;
	}
	return func(actorData, weapon);
}

auto IsMeleeWeaponReadyProxy  = IsWeaponReadyProxy<WEAPON_TYPE_MELEE >;
auto IsRangedWeaponReadyProxy = IsWeaponReadyProxy<WEAPON_TYPE_RANGED>;

void ToggleUpdateWeapon(bool enable)
{
	LogFunction(enable);

	for_all(uint8, index, countof(IsWeaponReadyProxyHelper))
	{
		auto & item = IsWeaponReadyProxyHelper[index];

		byte8 * addr = 0;
		byte8 * jumpAddr = 0;

		addr = (appBaseAddr + item.off[0]);
		jumpAddr = (item.off[1]) ? (appBaseAddr + item.off[1]) : 0;

		if (enable)
		{
			WriteJump(addr, IsWeaponReadyProxyFuncAddr[index]);
		}
		else
		{
			if (jumpAddr)
			{
				WriteCall(addr, (appBaseAddr + 0x1FDE10));
			}
			else
			{
				WriteJump(addr, (appBaseAddr + 0x1FDE10));
			}
		}
	}

	auto WriteHelper = [&]
	(
		uint32 callOff,
		uint32 jumpOff,
		uint32 jumpDestOff
		)
	{
		if (enable)
		{
			WriteJump((appBaseAddr + callOff), (appBaseAddr + callOff + 5));
			WriteAddress((appBaseAddr + jumpOff), (appBaseAddr + jumpOff + 2), 2);
		}
		else
		{
			WriteCall((appBaseAddr + callOff), (appBaseAddr + 0x1FD3E0));
			WriteAddress((appBaseAddr + jumpOff), (appBaseAddr + jumpDestOff), 2);
		}
	};

	WriteHelper(0x2288A4, 0x2288CE, 0x2288D8); // Dante Agni & Rudra
	/*
	dmc3.exe+2288A4 - E8 374BFDFF - call dmc3.exe+1FD3E0
	dmc3.exe+2288CE - 74 08       - je dmc3.exe+2288D8
	*/
	WriteHelper(0x229E8C, 0x229E93, 0x229EA2); // Vergil Force Edge
	/*
	dmc3.exe+229E8C - E8 4F35FDFF - call dmc3.exe+1FD3E0
	dmc3.exe+229E93 - 74 0D       - je dmc3.exe+229EA2
	*/
	WriteHelper(0x22AD2D, 0x22AD39, 0x22AD8B); // Dante Nevan
	/*
	dmc3.exe+22AD2D - E8 AE26FDFF - call dmc3.exe+1FD3E0
	dmc3.exe+22AD39 - 74 50       - je dmc3.exe+22AD8B
	*/
	WriteHelper(0x22FAD4, 0x22FADB, 0x22FB21); // Dante Cerberus
	/*
	dmc3.exe+22FAD4 - E8 07D9FCFF - call dmc3.exe+1FD3E0
	dmc3.exe+22FADB - 74 44       - je dmc3.exe+22FB21
	*/
	WriteHelper(0x23162E, 0x231635, 0x231644); // Dante Rebellion
	/*
	dmc3.exe+23162E - E8 ADBDFCFF - call dmc3.exe+1FD3E0
	dmc3.exe+231635 - 74 0D       - je dmc3.exe+231644
	*/
}





























// @Todo: Add devil support and Nero Angelo exceptions.
// @Todo: Check for WEAPON_VOID and same weapon.
// @Todo: Create templates.

//bool WeaponSwitchVergil(ACTOR_DATA_VERGIL & actorData)
//{
//	if (actorData.devilState == 2)
//	{
//		return true;
//	}
//	if (actorData.moveOnly)
//	{
//		return false;
//	}
//
//
//	{
//		if (!(actorData.buttons[2] & GetBinding(ACTION_CHANGE_DEVIL_ARMS)))
//		{
//			goto sect0;
//		}
//		if (0 < actorData.weaponSwitchTimeout[0])
//		{
//			goto sect0;
//		}
//		auto addr = actorData.actionData[3];
//		auto & timeout = *reinterpret_cast<float32 *>(addr + 0x348);
//		actorData.weaponSwitchTimeout[0] = timeout;
//		actorData.weaponSwitchTimeout[1] = timeout;
//
//		auto & queuedWeaponIndex = actorData.weaponIndex[1];
//		queuedWeaponIndex++;
//		if (queuedWeaponIndex >= 3)
//		{
//			queuedWeaponIndex = 0;
//		}
//
//		auto g_pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
//		auto hud = *reinterpret_cast<byte8 **>(g_pool[11]);
//
//		// @Todo: In the future just update the weapon icon and use 0.
//		func_280160
//		(
//			hud,
//			(queuedWeaponIndex < 2) ? 1 : 0,
//			(queuedWeaponIndex < 2) ? queuedWeaponIndex : 0,
//			1
//		);
//		*reinterpret_cast<bool *>(reinterpret_cast<byte8 *>(&actorData) + 0x648C) = true;
//		func_1EB0E0(actorData, 4);
//
//		if (actorData.devil || (actorData.devilState == 1))
//		{
//			func_1F92C0(actorData, 1);
//			func_1F97F0(actorData, true);
//		}
//	}
//	sect0:;
//
//
//
//
//
//	{
//		if (!(actorData.buttons[2] & GetBinding(ACTION_CHANGE_GUN)))
//		{
//			goto sect1;
//		}
//		if (0 < actorData.weaponSwitchTimeout[1])
//		{
//			goto sect1;
//		}
//		auto addr = actorData.actionData[3];
//		auto & timeout = *reinterpret_cast<float32 *>(addr + 0x348);
//		actorData.weaponSwitchTimeout[0] = timeout;
//		actorData.weaponSwitchTimeout[1] = timeout;
//
//		auto & queuedWeaponIndex = actorData.weaponIndex[1];
//
//
//		if (queuedWeaponIndex > 0)
//		{
//			queuedWeaponIndex--;
//		}
//		else
//		{
//			queuedWeaponIndex = 2;
//		}
//
//
//
//
//		auto g_pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
//		auto hud = *reinterpret_cast<byte8 **>(g_pool[11]);
//
//		// @Todo: In the future just update the weapon icon and use 0.
//		func_280160
//		(
//			hud,
//			(queuedWeaponIndex < 2) ? 1 : 0,
//			(queuedWeaponIndex < 2) ? queuedWeaponIndex : 0,
//			0
//		);
//		*reinterpret_cast<bool *>(reinterpret_cast<byte8 *>(&actorData) + 0x648C) = true;
//		func_1EB0E0(actorData, 4);
//
//		if (actorData.devil || (actorData.devilState == 1))
//		{
//			func_1F92C0(actorData, 1);
//			func_1F97F0(actorData, true);
//		}
//
//
//
//	}
//	sect1:;
//
//	return true;
//}





// MODEL_PARTITION_CONFIG_DEFAULT
// MODEL_PARTITION_CONFIG_BEOWULF

//
//enum MODEL_PARTITION_CONFIG
//{
//	MODEL_PARTITION_CONFIG_DEFAULT,
//	MODEL_PARTITION_CONFIG_BEOWULF,
//};
//
//template
//<
//	uint8 modelPartitionConfig,
//	typename T
//>
//void ApplyModelPartitionConfig(T & actorData)
//{
//	auto & modelData = actorData.modelData[0];
//	auto dest = func_89DE0(modelData);
//	if constexpr (modelPartitionConfig == MODEL_PARTITION_CONFIG_DEFAULT)
//	{
//		func_2F7350(dest, 3);
//		func_2F74E0(dest, 4);
//		func_2F74E0(dest, 5);
//		func_2F7350(dest, 6);
//	}
//	else
//	{
//		func_2F74E0(dest, 3);
//		func_2F7350(dest, 4);
//		func_2F7350(dest, 5);
//		func_2F74E0(dest, 6);
//	}
//}




















//auto ApplyDefaultModelPartitionConfig = ApplyModelPartitionConfig<MODEL_PARTITION_CONFIG_DEFAULT, ACTOR_DATA_DANTE>;

//inline void ApplyDefaultModelPartitionConfig(ACTOR_DATA_DANTE & actorData)
//{
//	auto & modelData = actorData.modelData[0];
//	auto dest = func_89DE0(modelData);
//	func_2F7350(dest, 3);
//	func_2F74E0(dest, 4);
//	func_2F74E0(dest, 5);
//	func_2F7350(dest, 6);
//}
//
//inline void ApplyBeowulfModelPartitionConfig(ACTOR_DATA_DANTE & actorData)
//{
//	auto & modelData = actorData.modelData[0];
//	auto dest = func_89DE0(modelData);
//	func_2F74E0(dest, 3);
//	func_2F7350(dest, 4);
//	func_2F7350(dest, 5);
//	func_2F74E0(dest, 6);
//}










void MeleeWeaponSwitchControllerDante(ACTOR_DATA_DANTE & actorData)
{

	// @Todo: Fix!
	if (actorData.newGamepad != 0)
	{
		return;
	}




	// if weapon count is 1 dont do nothing










	auto & gamepad = GetGamepad(actorData.newGamepad);
	auto & execute = actorData.newExecuteMeleeWeaponSwitch;

	if (!(gamepad.buttons[0] & GetBinding(BINDING_CHANGE_DEVIL_ARMS)))
	{
		execute = true;
		return;
	}

	if (!execute)
	{
		return;
	}

	execute = false;

	// @Research: Check assembly.
	if (0 < actorData.meleeWeaponSwitchTimeout)
	{
		return;
	}

	actorData.meleeWeaponSwitchTimeout = Config.Dante.weaponSwitchTimeout;

	actorData.newMeleeWeaponIndex++;
	if (actorData.newMeleeWeaponIndex >= actorData.newMeleeWeaponCount)
	{
		actorData.newMeleeWeaponIndex = 0;
	}

	auto & newMeleeWeapon = actorData.newMeleeWeapon[actorData.newMeleeWeaponIndex];
	if ((newMeleeWeapon >= WEAPON_DANTE_REBELLION) && (newMeleeWeapon <= WEAPON_DANTE_BEOWULF))
	{
		actorData.meleeWeaponIndex = 0;
		if (actorData.meleeWeaponStatus[0] != WEAPON_STATUS_READY)
		{
			goto sect0;
		}
		if (IsWeaponActive(actorData, actorData.meleeWeapon[0]) && (actorData.state & STATE_BUSY))
		{
			goto sect0;
		}
		goto sect1;
		sect0:;
		actorData.meleeWeaponIndex = 1;
		sect1:;
		auto & meleeWeapon     = actorData.meleeWeapon    [actorData.meleeWeaponIndex];
		auto & meleeWeaponData = actorData.meleeWeaponData[actorData.meleeWeaponIndex];
		meleeWeapon     = newMeleeWeapon;
		meleeWeaponData = actorData.newMeleeWeaponData[(newMeleeWeapon - WEAPON_DANTE_REBELLION)];
	}
	else if ((newMeleeWeapon >= WEAPON_VERGIL_YAMATO) && (newMeleeWeapon <= WEAPON_VERGIL_FORCE_EDGE))
	{
		auto parentActorData = actorData;
		if (parentActorData.newParentBaseAddr)
		{
			goto sect2;
		}
		if (!parentActorData.newChildBaseAddr[CHAR_VERGIL])
		{
			goto sect2;
		}
		auto & childActorData = *reinterpret_cast<ACTOR_DATA_VERGIL *>(parentActorData.newChildBaseAddr[CHAR_VERGIL]);
		if (childActorData.character != CHAR_VERGIL)
		{
			goto sect2;
		}
		childActorData.queuedMeleeWeaponIndex = (newMeleeWeapon - WEAPON_VERGIL_YAMATO);
	}
	sect2:;

	// @Todo: Update enum.
	HUD_UpdateWeaponIcon
	(
		HUD_BOTTOM::MELEE_WEAPON_1,
		HUD_weaponIcon[newMeleeWeapon].model,
		HUD_weaponIcon[newMeleeWeapon].texture
	);

	// @Todo: Use better pointer.
	auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
	auto hud = *reinterpret_cast<byte8 **>(pool[11]);
	func_280120(hud, 1, 0);

	func_1EB0E0(actorData, 4);
}

void RangedWeaponSwitchControllerDante(ACTOR_DATA_DANTE & actorData)
{

	// @Todo: Fix!
	if (actorData.newGamepad != 0)
	{
		return;
	}


	auto & gamepad = GetGamepad(actorData.newGamepad);
	auto & execute = actorData.newExecuteRangedWeaponSwitch;

	if (!(gamepad.buttons[0] & GetBinding(BINDING_CHANGE_GUN)))
	{
		execute = true;
		return;
	}

	if (!execute)
	{
		return;
	}

	execute = false;

	// @Research: Check assembly.
	if (0 < actorData.rangedWeaponSwitchTimeout)
	{
		return;
	}

	actorData.rangedWeaponSwitchTimeout = Config.Dante.weaponSwitchTimeout;

	actorData.newRangedWeaponIndex++;
	if (actorData.newRangedWeaponIndex >= actorData.newRangedWeaponCount)
	{
		actorData.newRangedWeaponIndex = 0;
	}

	auto & newRangedWeapon = actorData.newRangedWeapon[actorData.newRangedWeaponIndex];
	if ((newRangedWeapon >= WEAPON_DANTE_EBONY_IVORY) && (newRangedWeapon <= WEAPON_DANTE_KALINA_ANN))
	{
		actorData.rangedWeaponIndex = 0;
		if (actorData.rangedWeaponStatus[0] != WEAPON_STATUS_READY)
		{
			goto sect0;
		}
		if (IsWeaponActive(actorData, actorData.rangedWeapon[0]) && (actorData.state & STATE_BUSY))
		{
			goto sect0;
		}
		goto sect1;
		sect0:;
		actorData.rangedWeaponIndex = 1;
		sect1:;
		auto & rangedWeapon     = actorData.rangedWeapon    [actorData.rangedWeaponIndex];
		auto & rangedWeaponData = actorData.rangedWeaponData[actorData.rangedWeaponIndex];
		rangedWeapon     = newRangedWeapon;
		rangedWeaponData = actorData.newRangedWeaponData[(newRangedWeapon - WEAPON_DANTE_EBONY_IVORY)];
		actorData.rangedWeaponIndex += 2;
	}

	// @Todo: Update enum.
	HUD_UpdateWeaponIcon
	(
		HUD_BOTTOM::RANGED_WEAPON_1,
		HUD_weaponIcon[newRangedWeapon].model,
		HUD_weaponIcon[newRangedWeapon].texture
	);

	// @Todo: Use better pointer.
	auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
	auto hud = *reinterpret_cast<byte8 **>(pool[11]);
	func_280120(hud, 0, 0);

	func_1EB0E0(actorData, 7);
	func_1EB0E0(actorData, 9);

	auto UpdateCommitment = [&]()
	{
		auto & modelData = actorData.modelData[actorData.activeModelIndex];
		auto & lowerMotionData = actorData.motionData[BODY_PART_LOWER];
		auto & upperMotionData = actorData.motionData[BODY_PART_UPPER];
		auto & newRangedWeapon = actorData.newRangedWeapon[actorData.newRangedWeaponIndex];

		if (actorData.state & STATE_BUSY)
		{
			return;
		}
		if (!(gamepad.buttons[0] & GetBinding(BINDING_LOCK_ON)))
		{
			return;
		}

		actorData.activeWeapon = newRangedWeapon;

		if (GetRelativeTiltDirection(actorData) != TILT_DIRECTION_NEUTRAL)
		{
			return;
		}

		auto & group = lowerMotionData.group = (MOTION_GROUP_DANTE_REBELLION + newRangedWeapon);
		auto & index = lowerMotionData.index = upperMotionData.index;

		uint8 id = (pl000_00_0 + group);
		if (newRangedWeapon == WEAPON_DANTE_ARTEMIS)
		{
			if (index == 5)
			{
				index = 3;
			}
		}
		else
		{
			if (index == 3)
			{
				index = 5;
			}
		}
		byte8 * motionFile = File_staticFiles[id][index];
		func_8AC80(modelData, BODY_PART_LOWER, motionFile, 0, false);
	};

	UpdateCommitment();
}










bool WeaponSwitchControllerDante(ACTOR_DATA_DANTE & actorData)
{
	if (actorData.devilState == 2)
	{
		return true;
	}
	if (actorData.moveOnly)
	{
		return false;
	}

	MeleeWeaponSwitchControllerDante (actorData);
	RangedWeaponSwitchControllerDante(actorData);

	return true;
}








inline void RegisterWeapon_Init()
{
	RegisterWeapon[WEAPON_DANTE_REBELLION  ] = func_2310B0;
	RegisterWeapon[WEAPON_DANTE_CERBERUS   ] = func_22EC90;
	RegisterWeapon[WEAPON_DANTE_AGNI_RUDRA ] = func_227870;
	RegisterWeapon[WEAPON_DANTE_NEVAN      ] = func_22A1E0;
	RegisterWeapon[WEAPON_DANTE_BEOWULF    ] = func_228CF0;
	RegisterWeapon[WEAPON_DANTE_EBONY_IVORY] = func_22B0C0;
	RegisterWeapon[WEAPON_DANTE_SHOTGUN    ] = func_2306B0;
	RegisterWeapon[WEAPON_DANTE_ARTEMIS    ] = func_22C4A0;
	RegisterWeapon[WEAPON_DANTE_SPIRAL     ] = func_2300A0;
	RegisterWeapon[WEAPON_DANTE_KALINA_ANN ] = func_22BA30;
	RegisterWeapon[WEAPON_VERGIL_YAMATO    ] = func_22D960;
	RegisterWeapon[WEAPON_VERGIL_BEOWULF   ] = func_228CF0;
	RegisterWeapon[WEAPON_VERGIL_FORCE_EDGE] = func_2298E0;
	RegisterWeapon[WEAPON_BOB_YAMATO       ] = func_231A30;
}






void Actor_Init()
{




	if (!Actor_actorBaseAddr.Init(512))
	{

		Log("Actor_actorBaseAddr.Init failed.");

		return;
	}










	// Temporary Fixes

	// Disable Vergil Weapon Switch Controller
	{
		byte8 sect0[] =
		{
			0xB0, 0x01, //mov al,01
			0xC3,       //ret
			0x90,       //nop
			0x90,       //nop
		};
		vp_memcpy((appBaseAddr + 0x1E6DD0), sect0, sizeof(sect0));
	}

	Write<uint32>((appBaseAddr + 0x1EBD19), offsetof(ACTOR_DATA, newGamepad));

	{
		Write<byte8>((appBaseAddr + 0x27E800), 0xEB);
		Write<byte8>((appBaseAddr + 0x27DF3E), 0xEB);
		Write<byte16>((appBaseAddr + 0x280DB9), 0xE990);
	}










	LogFunction();

	RegisterWeapon_Init();

	// Adjust actor data size.
	{
		constexpr uint32 size = (0xB8C0 + 512);
		Write<uint32>((appBaseAddr + 0x1DE8B4), size); // Vergil
		Write<uint32>((appBaseAddr + 0x1DE9CD), size); // Lady
		Write<uint32>((appBaseAddr + 0x1DEAC9), size); // Bob
		Write<uint32>((appBaseAddr + 0x1DEBE2), size); // Dante
	}

	//{
	//	auto func = CreateFunction(WeaponSwitchVergil, 0, true, false);
	//	WriteCall((appBaseAddr + 0x1E25E1), func.addr);
	//}
	{
		auto func = CreateFunction(WeaponSwitchControllerDante, 0, true, false);
		WriteCall((appBaseAddr + 0x1E25EB), func.addr);
	}

	{
		byte8 sect2[] =
		{
			0x84, 0xC0,                   //test al,al
			0x74, 0x05,                   //je short
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+1FDE10
		};
		for_all(uint8, index, countof(IsWeaponReadyProxyHelper))
		{
			auto & item = IsWeaponReadyProxyHelper[index];
			byte8 * jumpAddr = (item.off[1]) ? (appBaseAddr + item.off[1]) : 0;
			auto func = CreateFunction
			(
				(item.weaponType == WEAPON_TYPE_MELEE) ? IsMeleeWeaponReadyProxy : IsRangedWeaponReadyProxy,
				jumpAddr,
				true,
				false,
				0,
				0,
				sizeof(sect2)
			);
			memcpy(func.sect2, sect2, sizeof(sect2));
			if (jumpAddr)
			{
				WriteCall((func.sect2 + 4), (appBaseAddr + 0x1FDE10));
			}
			else
			{
				WriteJump((func.sect2 + 4), (appBaseAddr + 0x1FDE10));
			}
			IsWeaponReadyProxyFuncAddr[index] = func.addr;
		}
	}






	{
		constexpr byte8 sect0[] =
		{
			0x53,                                     //push rbx
			0x48, 0x83, 0xEC, 0x20,                   //sub rsp,20
			0x80, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, //cmp byte ptr [rcx+0000B8C0],04
			0x0F, 0x83, 0x00, 0x00, 0x00, 0x00,       //jae dmc3.exe+1EBF90
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x1EBCF6), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint32 *>(func.addr + 7) = offsetof(ACTOR_DATA, newGamepad);
		*reinterpret_cast<uint8 *>(func.addr + 0xB) = MAX_PLAYER;
		WriteAddress((func.addr + 0xC), (appBaseAddr + 0x1EBF90), 6);
		WriteJump((appBaseAddr + 0x1EBCF0), func.addr, 1);
		/*
		dmc3.exe+1EBCF0 - 40 53             - push rbx
		dmc3.exe+1EBCF2 - 48 83 EC 20       - sub rsp,20
		dmc3.exe+1EBCF6 - 48 8B 05 2B51AA00 - mov rax,[dmc3.exe+C90E28]
		*/
	}




	{
		constexpr byte8 sect0[] =
		{
			0x66, 0x23, 0x83, 0x00, 0x00, 0x00, 0x00, //and ax,[rbx+0000B8C0]
			0x66, 0x89, 0x83, 0xE0, 0x74, 0x00, 0x00, //mov [rbx+000074E0],ax
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x1EBD3B), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint32 *>(func.sect0 + 3) = offsetof(ACTOR_DATA, newButtonMask);
		WriteJump((appBaseAddr + 0x1EBD34), func.addr, 2);
		/*
		dmc3.exe+1EBD34 - 66 89 83 E0740000 - mov [rbx+000074E0],ax
		dmc3.exe+1EBD3B - 48 8D 0D CE8CB600 - lea rcx,[dmc3.exe+D54A10]
		*/
	}

	{
		constexpr byte8 sect0[] =
		{
			0x66, 0x23, 0x83, 0x00, 0x00, 0x00, 0x00, //and ax,[rbx+0000B8C0]
			0x66, 0x89, 0x83, 0xE2, 0x74, 0x00, 0x00, //mov [rbx+000074E2],ax
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x1EBD5B), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint32 *>(func.sect0 + 3) = offsetof(ACTOR_DATA, newButtonMask);
		WriteJump((appBaseAddr + 0x1EBD54), func.addr, 2);
		/*
		dmc3.exe+1EBD54 - 66 89 83 E2740000 - mov [rbx+000074E2],ax
		dmc3.exe+1EBD5B - 66 23 CA          - and cx,dx
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
		*reinterpret_cast<uint32 *>(func.sect0 + 3) = offsetof(ACTOR_DATA, newButtonMask);
		WriteJump((appBaseAddr + 0x1EBD64), func.addr, 2);
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
		*reinterpret_cast<uint32 *>(func.sect0 + 3) = offsetof(ACTOR_DATA, newButtonMask);
		WriteJump((appBaseAddr + 0x1EBD75), func.addr, 2);
		/*
		dmc3.exe+1EBD75 - 66 89 93 E6740000 - mov [rbx+000074E6],dx
		dmc3.exe+1EBD7C - 33 D2             - xor edx,edx
		*/
	}

	{
		constexpr byte8 sect0[] =
		{
			0x80, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x01, //cmp byte ptr [rbx+0000B8C0],01
			0x74, 0x03,                               //je short
			0x66, 0x31, 0xC0,                         //xor ax,ax
			0x66, 0x89, 0x83, 0x0A, 0x75, 0x00, 0x00, //mov [rbx+0000750A],ax
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x1EBEA4), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ACTOR_DATA, newEnableLeftStick);
		WriteJump((appBaseAddr + 0x1EBE9D), func.addr, 2);
		/*
		dmc3.exe+1EBE9D - 66 89 83 0A750000   - mov [rbx+0000750A],ax
		dmc3.exe+1EBEA4 - F3 0F10 8B DC3E0000 - movss xmm1,[rbx+00003EDC]
		*/
	}
}























#ifdef __GARBAGE__
//{
//	// Walk, Run
//	// Swordmaster, Trickster Dash, Royalguard Release
//	// Melee Attack
//	constexpr byte8 sect0[] =
//	{
//		0xF3, 0x0F, 0x11, 0x8B, 0x80, 0x00, 0x00, 0x00, //movss [rbx+00000080],xmm1
//	};
//	constexpr byte8 sect1[] =
//	{
//		0x48, 0x8B, 0xCB, //mov rcx,rbx
//	};
//	auto func = CreateFunction(UpdatePosition, (appBaseAddr + 0x1FC027), true, true, sizeof(sect0), sizeof(sect1));
//	memcpy(func.sect0, sect0, sizeof(sect0));
//	memcpy(func.sect1, sect1, sizeof(sect1));
//	WriteJump((appBaseAddr + 0x1FC01F), func.addr, 3);
//	/*
//	dmc3.exe+1FC01F - F3 0F11 8B 80000000 - movss [rbx+00000080],xmm1
//	dmc3.exe+1FC027 - E9 4E030000         - jmp dmc3.exe+1FC37A
//	*/
//}







//{
//	constexpr byte8 sect2[] =
//	{
//		0x84, 0xC0,                   //test al,al
//		0x74, 0x05,                   //je short
//		0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+1F5450
//	};
//	auto func = CreateFunction(FreeWalk, (appBaseAddr + 0x1F6FD1), true, false, 0, 0, sizeof(sect2));
//	memcpy(func.sect2, sect2, sizeof(sect2));
//	WriteCall((func.sect2 + 4), (appBaseAddr + 0x1F5450));
//	//WriteJump((appBaseAddr + 0x1F6FCC), func.addr);
//	/*
//	dmc3.exe+1F6FCC - E8 7FE4FFFF - call dmc3.exe+1F5450
//	dmc3.exe+1F6FD1 - E9 02020000 - jmp dmc3.exe+1F71D8
//	*/
//}






//{
//	constexpr byte8 sect1[] =
//	{
//		0x4C, 0x8B, 0xC3, //mov r8,rbx
//	};
//	auto func = CreateFunction(WritePosition_1FC017, (appBaseAddr + 0x1FC027), true, true, 0, sizeof(sect1));
//	memcpy(func.sect1, sect1, sizeof(sect1));
//	//WriteJump((appBaseAddr + 0x1FC017), func.addr, 3);
//	/*
//	dmc3.exe+1FC017 - F3 0F11 83 88000000 - movss [rbx+00000088],xmm0
//	dmc3.exe+1FC01F - F3 0F11 8B 80000000 - movss [rbx+00000080],xmm1
//	dmc3.exe+1FC027 - E9 4E030000         - jmp dmc3.exe+1FC37A
//	*/
//}






//{
//	constexpr byte8 sect0[] =
//	{
//		0x66, 0x89, 0xAE, 0xB0, 0x39, 0x00, 0x00, //mov [rsi+000039B0],bp
//	};
//	constexpr byte8 sect1[] =
//	{
//		0x48, 0x8B, 0xCE, //mov rcx,rsi
//	};
//	auto func = CreateFunction(WriteLowerBodyMotionData, (appBaseAddr + 0x1EFC97), true, true, sizeof(sect0), sizeof(sect1));
//	memcpy(func.sect0, sect0, sizeof(sect0));
//	memcpy(func.sect1, sect1, sizeof(sect1));
//	WriteJump((appBaseAddr + 0x1EFC90), func.addr, 2);
//	/*
//	dmc3.exe+1EFC90 - 66 89 AE B0390000       - mov [rsi+000039B0],bp
//	dmc3.exe+1EFC97 - C7 86 C2390000 00000000 - mov [rsi+000039C2],00000000
//	*/
//}
//{
//	constexpr byte8 sect0[] =
//	{
//		0x66, 0x89, 0xAE, 0xB2, 0x39, 0x00, 0x00, //mov [rsi+000039B2],bp
//	};
//	constexpr byte8 sect1[] =
//	{
//		0x48, 0x8B, 0xCE, //mov rcx,rsi
//	};
//	auto func = CreateFunction(WriteUpperBodyMotionData, (appBaseAddr + 0x1EFC8D), true, true, sizeof(sect0), sizeof(sect1));
//	memcpy(func.sect0, sect0, sizeof(sect0));
//	memcpy(func.sect1, sect1, sizeof(sect1));
//	WriteJump((appBaseAddr + 0x1EFC86), func.addr, 2);
//	/*
//	dmc3.exe+1EFC86 - 66 89 AE B2390000 - mov [rsi+000039B2],bp
//	dmc3.exe+1EFC8D - 8D 51 01          - lea edx,[rcx+01]
//	*/
//}






//{
//	constexpr byte8 sect0[] =
//	{
//		0x48, 0x8B, 0x5C, 0x24, 0x20,       //mov rbx,[rsp+20]
//		0x84, 0xC0,                         //test al,al
//		0x0F, 0x84, 0x00, 0x00, 0x00, 0x00, //je dmc3.exe+1E5F57
//	};
//	auto func = CreateFunction(LogMotionData, (appBaseAddr + 0x1E5F57), true, true, sizeof(sect0));
//	memcpy(func.sect0, sect0, sizeof(sect0));
//	WriteAddress((func.sect0 + 7), (appBaseAddr + 0x1E5F57), 6);
//	//WriteJump((appBaseAddr + 0x1E5F52), func.addr);
//	/*
//	dmc3.exe+1E5F52 - 48 8B 5C 24 20 - mov rbx,[rsp+20]
//	dmc3.exe+1E5F57 - 48 8B 6C 24 28 - mov rbp,[rsp+28]
//	*/
//}



//{
//	constexpr byte8 sect0[] =
//	{
//		0x89, 0x83, 0x64, 0x3E, 0x00, 0x00, //mov [rbx+00003E64],eax
//	};
//	constexpr byte8 sect1[] =
//	{
//		0x48, 0x8B, 0xCB, //mov rcx,rbx
//	};
//	auto func = CreateFunction(WriteMotionState, (appBaseAddr + 0x1E0510), true, true, sizeof(sect0), sizeof(sect1));
//	memcpy(func.sect0, sect0, sizeof(sect0));
//	memcpy(func.sect1, sect1, sizeof(sect1));
//	WriteJump((appBaseAddr + 0x1E050A), func.addr, 1);
//	/*
//	dmc3.exe+1E050A - 89 83 643E0000 - mov [rbx+00003E64],eax
//	dmc3.exe+1E0510 - 48 83 C4 40    - add rsp,40
//	*/
//}

//{
//	constexpr byte8 sect0[] =
//	{
//		0x89, 0x83, 0x64, 0x3E, 0x00, 0x00, //mov [rbx+00003E64],eax
//	};
//	constexpr byte8 sect1[] =
//	{
//		0x48, 0x8B, 0xCB, //mov rcx,rbx
//	};
//	auto func = CreateFunction(WriteMotionState, (appBaseAddr + 0x1E0952), true, true, sizeof(sect0), sizeof(sect1));
//	memcpy(func.sect0, sect0, sizeof(sect0));
//	memcpy(func.sect1, sect1, sizeof(sect1));
//	WriteJump((appBaseAddr + 0x1E094C), func.addr, 1);
//	/*
//	dmc3.exe+1E094C - 89 83 643E0000 - mov [rbx+00003E64],eax
//	dmc3.exe+1E0952 - 85 F6          - test esi,esi
//	*/
//}


//{
//	constexpr byte8 sect0[] =
//	{
//		0x89, 0x8B, 0x64, 0x3E, 0x00, 0x00, //mov [rbx+00003E64],ecx
//	};
//	constexpr byte8 sect1[] =
//	{
//		0x48, 0x8B, 0xCB, //mov rcx,rbx
//	};
//	auto func = CreateFunction(WriteMotionState, (appBaseAddr + 0x1E0AA8), true, true, sizeof(sect0), sizeof(sect1));
//	memcpy(func.sect0, sect0, sizeof(sect0));
//	memcpy(func.sect1, sect1, sizeof(sect1));
//	WriteJump((appBaseAddr + 0x1E0AA2), func.addr, 1);
//	/*
//	dmc3.exe+1E0AA2 - 89 8B 643E0000        - mov [rbx+00003E64],ecx
//	dmc3.exe+1E0AA8 - EB 0A                 - jmp dmc3.exe+1E0AB4
//	*/
//}

//{
//	constexpr byte8 sect0[] =
//	{
//		0x89, 0x83, 0x64, 0x3E, 0x00, 0x00, //mov [rbx+00003E64],eax
//	};
//	constexpr byte8 sect1[] =
//	{
//		0x48, 0x8B, 0xCB, //mov rcx,rbx
//	};
//	auto func = CreateFunction(WriteMotionState, (appBaseAddr + 0x1E0AB4), true, true, sizeof(sect0), sizeof(sect1));
//	memcpy(func.sect0, sect0, sizeof(sect0));
//	memcpy(func.sect1, sect1, sizeof(sect1));
//	WriteJump((appBaseAddr + 0x1E0AAE), func.addr, 1);
//	/*
//	dmc3.exe+1E0AAE - 89 83 643E0000    - mov [rbx+00003E64],eax
//	dmc3.exe+1E0AB4 - 83 BB 043E0000 12 - cmp dword ptr [rbx+00003E04],12
//	*/
//}



//{
//	constexpr byte8 sect0[] =
//	{
//		0x89, 0x91, 0x64, 0x3E, 0x00, 0x00, //mov [rcx+00003E64],edx
//	};
//	auto func = CreateFunction(WriteMotionState, (appBaseAddr + 0x1E0B7C), true, true, sizeof(sect0));
//	memcpy(func.sect0, sect0, sizeof(sect0));
//	WriteJump((appBaseAddr + 0x1E0B76), func.addr, 1);
//	/*
//	dmc3.exe+1E0B76 - 89 91 643E0000 - mov [rcx+00003E64],edx
//	dmc3.exe+1E0B7C - 8B C2          - mov eax,edx
//	*/
//}

//{
//	constexpr byte8 sect0[] =
//	{
//		0x89, 0x83, 0x64, 0x3E, 0x00, 0x00, //mov [rbx+00003E64],eax
//	};
//	constexpr byte8 sect1[] =
//	{
//		0x48, 0x8B, 0xCB, //mov rcx,rbx
//	};
//	auto func = CreateFunction(WriteMotionState, (appBaseAddr + 0x1E146F), true, true, sizeof(sect0), sizeof(sect1));
//	memcpy(func.sect0, sect0, sizeof(sect0));
//	memcpy(func.sect1, sect1, sizeof(sect1));
//	WriteJump((appBaseAddr + 0x1E1469), func.addr, 1);
//	/*
//	dmc3.exe+1E1469 - 89 83 643E0000    - mov [rbx+00003E64],eax
//	dmc3.exe+1E146F - 40 88 B3 103E0000 - mov [rbx+00003E10],sil
//	*/
//}


//{
//	constexpr byte8 sect0[] =
//	{
//		0x89, 0x91, 0x64, 0x3E, 0x00, 0x00, //mov [rcx+00003E64],edx
//	};
//	auto func = CreateFunction(WriteMotionState, (appBaseAddr + 0x1E175E), true, true, sizeof(sect0));
//	memcpy(func.sect0, sect0, sizeof(sect0));
//	WriteJump((appBaseAddr + 0x1E1758), func.addr, 1);
//	/*
//	dmc3.exe+1E1758 - 89 91 643E0000 - mov [rcx+00003E64],edx
//	dmc3.exe+1E175E - 8B C2          - mov eax,edx
//	*/
//}




















//{
//	constexpr byte8 sect2[] =
//	{
//		0x84, 0xC0,                   //test al,al
//		0x74, 0x01,                   //je short
//		0xC3,                         //ret
//		0x48, 0x89, 0x5C, 0x24, 0x08, //mov [rsp+08],rbx
//	};
//	auto func = CreateFunction(PlayMotion, (appBaseAddr + 0x1EFB95), true, false, 0, 0, sizeof(sect2));
//	memcpy(func.sect2, sect2, sizeof(sect2));
//	//WriteJump((appBaseAddr + 0x1EFB90), func.addr);
//	/*
//	dmc3.exe+1EFB90 - 48 89 5C 24 08 - mov [rsp+08],rbx
//	dmc3.exe+1EFB95 - 48 89 6C 24 10 - mov [rsp+10],rbp
//	*/
//}



//{
//	constexpr byte8 sect0[] =
//	{
//		0x89, 0x83, 0x64, 0x3E, 0x00, 0x00, //mov [rbx+00003E64],eax
//	};
//	constexpr byte8 sect1[] =
//	{
//		0x48, 0x8B, 0xCB, //mov rcx,rbx
//	};
//	auto func = CreateFunction(WriteMotionState, (appBaseAddr + 0x1E0952), true, true, sizeof(sect0), sizeof(sect1));
//	memcpy(func.sect0, sect0, sizeof(sect0));
//	memcpy(func.sect1, sect1, sizeof(sect1));
//	//WriteJump((appBaseAddr + 0x1E094C), func.addr, 1);
//	/*
//	dmc3.exe+1E094C - 89 83 643E0000 - mov [rbx+00003E64],eax
//	dmc3.exe+1E0952 - 85 F6          - test esi,esi
//	*/
//}










// Add missing lower body update when switching ranged weapons with Dante.

//{
//	byte8 sect0[] =
//	{
//		0xE8, 0x00, 0x00, 0x00, 0x00,                   //call dmc3.exe+1F99F0
//		0x48, 0x8B, 0xCB,                               //mov rcx,rbx
//		0x31, 0xD2,                                     //xor edx,edx
//		0x45, 0x31, 0xC9,                               //xor r9d,r9d
//		0xF3, 0x0F, 0x10, 0x15, 0x00, 0x00, 0x00, 0x00, //movss xmm2,[dmc3.exe+4C6068]
//		0xE8, 0x00, 0x00, 0x00, 0x00,                   //call dmc3.exe+1F99F0
//	};
//	auto func = CreateFunction(0, (appBaseAddr + 0x1F4F98), false, true, sizeof(sect0));
//	memcpy(func.sect0, sect0, sizeof(sect0));
//	WriteAddress(func.sect0, (appBaseAddr + 0x1F99F0), 5);
//	WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0x4C6068), 8);
//	WriteAddress((func.sect0 + 0x15), (appBaseAddr + 0x1F99F0), 5);
//	//WriteJump((appBaseAddr + 0x1F4F93), func.addr);
//	/*
//	dmc3.exe+1F4F93 - E8 584A0000       - call dmc3.exe+1F99F0
//	dmc3.exe+1F4F98 - 80 BB AE3E0000 01 - cmp byte ptr [rbx+00003EAE],01
//	*/
//}



//// @Research: Lady has different actor_data size. Geez, quite the turn.

//// Increase ACTOR_DATA size.
//{
//	constexpr uint32 size = (0xB8C0 + 512);
//	Write<uint32>((appBaseAddr + 0x1DE5FA), size);
//	Write<uint32>((appBaseAddr + 0x1DE67A), size);
//	Write<uint32>((appBaseAddr + 0x1DE8B4), size);
//	Write<uint32>((appBaseAddr + 0x1DEBE2), size);
//}


//Write<byte32>((appBaseAddr + 0x1EBD19), offsetof(ACTOR_DATA, gamepad));


//
//
//template
//<
//	typename T,
//	uint8 weaponType = WEAPON_TYPE_MELEE
//>
//bool IsWeaponReady
//(
//	T & actorData,
//	uint8 weapon
//)
//{
//
//
//	// auto &
//
//	uint8 * weaponMap = 0;
//	uint8 weaponCount = 0;
//	uint8 weaponIndex = 0;
//
//	//if constexpr (typematch(T, ACTOR_DATA_DANTE))
//	//{
//	//	if constexpr (weaponType == WEAPON_TYPE_MELEE)
//	//	{
//	//		weaponMap = actorData.meleeWeaponMap;
//	//		weaponCount = 2;
//	//		weaponIndex = actorData.meleeWeaponIndex;
//	//	}
//	//	else
//	//	{
//	//		weaponMap = actorData.rangedWeaponMap;
//	//		weaponCount = 2;
//	//		weaponIndex = (actorData.rangedWeaponIndex - 2);
//	//	}
//	//}
//	//else if constexpr (typematch(T, ACTOR_DATA_VERGIL))
//	//{
//	//	weaponMap = actorData.meleeWeaponMap;
//	//	weaponCount = 3;
//	//	weaponIndex = actorData.queuedMeleeWeaponIndex;
//	//}
//
//
//	if constexpr (weaponType == WEAPON_TYPE_MELEE)
//	{
//		weaponMap = actorData.newMeleeWeaponMap;
//		weaponCount = actorData.newMeleeWeaponCount;
//		weaponIndex = actorData.newMeleeWeaponIndex;
//	}
//	else
//	{
//		weaponMap = actorData.newRangedWeaponMap;
//		weaponCount = actorData.newRangedWeaponCount;
//		weaponIndex = actorData.newRangedWeaponIndex;
//	}
//
//
//
//
//
//
//
//
//	if (IsWeaponActive<T>(actorData, weapon))
//	{
//		return true;
//	}
//
//	for (uint8 index = 0; index < weaponCount; index++)
//	{
//		if (weaponMap[index] == weapon)
//		{
//			continue;
//		}
//		if (IsWeaponActive<T>(actorData, weaponMap[index]))
//		{
//			return false;
//		}
//	}
//
//	//if constexpr (typematch(T, ACTOR_DATA_VERGIL))
//	//{
//	//	if (actorData.activeMeleeWeaponIndex != actorData.queuedMeleeWeaponIndex)
//	//	{
//	//		actorData.activeMeleeWeaponIndex = actorData.queuedMeleeWeaponIndex;
//	//	}
//	//}
//
//	if (weaponMap[weaponIndex] == weapon)
//	{
//		return true;
//	}
//
//	//if constexpr (typematch(T, ACTOR_DATA_VERGIL))
//	//{
//	//	if ((weapon == WEAPON_VERGIL_YAMATO) && (weaponMap[weaponIndex] == WEAPON_VERGIL_FORCE_EDGE))
//	//	{
//	//		return true;
//	//	}
//	//}
//
//	return false;
//}















// @Todo: Update.

//template
//<
//	typename T,
//	uint8 weaponType = WEAPON_TYPE_MELEE
//>
//bool IsWeaponReady
//(
//	T & actorData,
//	uint8 weapon
//)
//{
//	uint8 * weaponMap = 0;
//	uint8 weaponCount = 0;
//	uint8 weaponIndex = 0;
//
//	if constexpr (typematch(T, ACTOR_DATA_DANTE))
//	{
//		if constexpr (weaponType == WEAPON_TYPE_MELEE)
//		{
//			weaponMap = actorData.meleeWeaponMap;
//			weaponCount = 2;
//			weaponIndex = actorData.meleeWeaponIndex;
//		}
//		else
//		{
//			weaponMap = actorData.rangedWeaponMap;
//			weaponCount = 2;
//			weaponIndex = (actorData.rangedWeaponIndex - 2);
//		}
//	}
//	else if constexpr (typematch(T, ACTOR_DATA_VERGIL))
//	{
//		weaponMap = actorData.meleeWeaponMap;
//		weaponCount = 3;
//		weaponIndex = actorData.queuedMeleeWeaponIndex;
//	}
//
//	if (IsWeaponActive<T>(actorData, weapon))
//	{
//		return true;
//	}
//
//	for (uint8 index = 0; index < weaponCount; index++)
//	{
//		if (weaponMap[index] == weapon)
//		{
//			continue;
//		}
//		if (IsWeaponActive<T>(actorData, weaponMap[index]))
//		{
//			return false;
//		}
//	}
//
//	if constexpr (typematch(T, ACTOR_DATA_VERGIL))
//	{
//		if (actorData.activeMeleeWeaponIndex != actorData.queuedMeleeWeaponIndex)
//		{
//			actorData.activeMeleeWeaponIndex = actorData.queuedMeleeWeaponIndex;
//		}
//	}
//
//	if (weaponMap[weaponIndex] == weapon)
//	{
//		return true;
//	}
//
//	if constexpr (typematch(T, ACTOR_DATA_VERGIL))
//	{
//		if ((weapon == WEAPON_VERGIL_YAMATO) && (weaponMap[weaponIndex] == WEAPON_VERGIL_FORCE_EDGE))
//		{
//			return true;
//		}
//	}
//
//	return false;
//}


//void * IsMeleeWeaponReady[MAX_CHAR] =
//{
//	IsWeaponReady<ACTOR_DATA_DANTE, WEAPON_TYPE_MELEE>,
//	0,
//	0,
//	IsWeaponReady<ACTOR_DATA_VERGIL, WEAPON_TYPE_MELEE>,
//};
//
//void * IsRangedWeaponReady[MAX_CHAR] =
//{
//	IsWeaponReady<ACTOR_DATA_DANTE, WEAPON_TYPE_RANGED>,
//	0,
//	0,
//	0,
//};




//template <typename T, uint8 weaponType>
//bool IsWeaponReadyProxyFunction(byte8 * baseAddr);
//
//template <>
//bool IsWeaponReadyProxyFunction<ACTOR_DATA_DANTE, WEAPON_TYPE_MELEE>(byte8 * baseAddr)
//{
//
//}





//// @Research: Very treacherous.
//
//struct
//{
//	uint8 newMeleeWeaponMap[5] =
//	{
//		WEAPON_DANTE_REBELLION,
//		WEAPON_DANTE_CERBERUS,
//		WEAPON_VERGIL_YAMATO,
//		//WEAPON_DANTE_AGNI_RUDRA,
//		WEAPON_DANTE_NEVAN,
//		WEAPON_DANTE_BEOWULF,
//	};
//	uint8 newMeleeWeaponCount = 3;
//	uint8 newRangedWeaponMap[5] =
//	{
//		WEAPON_DANTE_EBONY_IVORY,
//		WEAPON_DANTE_SHOTGUN,
//		WEAPON_DANTE_ARTEMIS,
//		WEAPON_DANTE_SPIRAL,
//		WEAPON_DANTE_KALINA_ANN,
//	};
//	uint8 newRangedWeaponCount = 5;
//}
//Dante;



// @Todo: If actor has no parent, has child, child's weapon yamato is still active, keep hiding weapon.


















inline bool IsWeaponActiveDante
(
	byte8 * baseAddr,
	uint8 weapon
)
{
	auto & actorData = *reinterpret_cast<ACTOR_DATA_DANTE *>(baseAddr);
	auto & motionData = actorData.motionData[BODY_PART_UPPER];
	if (weapon == WEAPON_VOID)
	{
		return false;
	}
	if (motionData.group == (MOTION_GROUP_DANTE_REBELLION + weapon))
	{
		return true;
	}
	if (motionData.group == (MOTION_GROUP_DANTE_SWORDMASTER_REBELLION + weapon))
	{
		return true;
	}
	return false;
}

inline bool IsWeaponActiveVergil
(
	byte8 * baseAddr,
	uint8 weapon
)
{
	auto & actorData = *reinterpret_cast<ACTOR_DATA_VERGIL *>(baseAddr);
	auto & motionData = actorData.motionData[BODY_PART_UPPER];
	if (weapon == WEAPON_VOID)
	{
		return false;
	}

	return false;
}




























//template <typename T>
//bool IsWeaponActive
//(
//	T & actorData,
//	uint8 weapon
//)
//{
//	auto & motionData = actorData.motionData[BODY_PART_UPPER];
//	if (weapon == WEAPON_VOID)
//	{
//		return false;
//	}
//	if constexpr (typematch(T, ACTOR_DATA_DANTE))
//	{
//		if (motionData.group == (MOTION_GROUP_DANTE_REBELLION + weapon))
//		{
//			return true;
//		}
//		if (motionData.group == (MOTION_GROUP_DANTE_SWORDMASTER_REBELLION + weapon))
//		{
//			return true;
//		}
//	}
//	else if constexpr (typematch(T, ACTOR_DATA_VERGIL))
//	{
//		if (motionData.group == (MOTION_GROUP_VERGIL_YAMATO + (weapon - WEAPON_VERGIL_YAMATO)))
//		{
//			return true;
//		}
//	}
//	return false;
//}

template <typename T>
bool IsWeaponActive(T & actorData)
{
	auto & motionData = actorData.motionData[BODY_PART_UPPER];
	if constexpr (typematch(T, ACTOR_DATA_DANTE))
	{
		if ((motionData.group >= MOTION_GROUP_DANTE_REBELLION) && (motionData.group <= MOTION_GROUP_DANTE_GUNSLINGER_KALINA_ANN))
		{
			return true;
		}
	}
	else if constexpr (typematch(T, ACTOR_DATA_VERGIL))
	{
		if ((motionData.group >= MOTION_GROUP_VERGIL_YAMATO) && (motionData.group <= MOTION_GROUP_VERGIL_FORCE_EDGE))
		{
			return true;
		}
	}
	return false;
}










template <typename T>
bool IsActive(T & actorData)
{
	auto & motionData = actorData.motionData[BODY_PART_UPPER];
	if constexpr (typematch(T, ACTOR_DATA_DANTE))
	{
		if ((motionData.group == MOTION_GROUP_DANTE_BASE) && (motionData.index == 14))
		{
			return true;
		}
		if ((motionData.group == MOTION_GROUP_DANTE_TAUNTS))
		{
			return true;
		}
	}
	else if constexpr (typematch(T, ACTOR_DATA_VERGIL))
	{
		if ((motionData.group == MOTION_GROUP_VERGIL_BASE) && (motionData.index == 14))
		{
			return true;
		}
		if ((motionData.group == MOTION_GROUP_VERGIL_TAUNTS))
		{
			return true;
		}
	}
	return IsWeaponActive(actorData);
}






//
//
//inline bool IsWeaponActive
//(
//	byte8 * baseAddr,
//	uint8 weapon
//)
//{
//	auto & actorData = *reinterpret_cast<ACTOR_DATA *>(baseAddr);
//	auto & motionData = actorData.motionData[BODY_PART_UPPER];
//	if (weapon == WEAPON_VOID)
//	{
//		return false;
//	}
//	switch (actorData.character)
//	{
//	case CHAR_DANTE:
//	{
//		if (motionData.group == (MOTION_GROUP_DANTE_REBELLION + weapon))
//		{
//			return true;
//		}
//		if (motionData.group == (MOTION_GROUP_DANTE_SWORDMASTER_REBELLION + weapon))
//		{
//			return true;
//		}
//		break;
//	}
//	case CHAR_VERGIL:
//	{
//		if (motionData.group == (MOTION_GROUP_VERGIL_YAMATO + (weapon - WEAPON_VERGIL_YAMATO)))
//		{
//			return true;
//		}
//		break;
//	}
//	}
//	return false;
//}
//
//inline bool IsWeaponActive(byte8 * baseAddr)
//{
//	auto & actorData = *reinterpret_cast<ACTOR_DATA *>(baseAddr);
//	auto & motionData = actorData.motionData[BODY_PART_UPPER];
//	switch (actorData.character)
//	{
//	case CHAR_DANTE:
//	{
//		if ((motionData.group >= MOTION_GROUP_DANTE_REBELLION) && (motionData.group <= MOTION_GROUP_DANTE_GUNSLINGER_KALINA_ANN))
//		{
//			return true;
//		}
//		break;
//	}
//	case CHAR_VERGIL:
//	{
//		if ((motionData.group >= MOTION_GROUP_VERGIL_YAMATO) && (motionData.group <= MOTION_GROUP_VERGIL_FORCE_EDGE))
//		{
//			return true;
//		}
//		break;
//	}
//	}
//	return false;
//}
//
//
//
//
//
//inline bool IsActive(byte8 * baseAddr)
//{
//	auto & actorData = *reinterpret_cast<ACTOR_DATA *>(baseAddr);
//	auto & motionData = actorData.motionData[BODY_PART_UPPER];
//	switch (actorData.character)
//	{
//	case CHAR_DANTE:
//	{
//		if ((motionData.group == MOTION_GROUP_DANTE_BASE) && (motionData.index == 14))
//		{
//			return true;
//		}
//		if ((motionData.group == MOTION_GROUP_DANTE_TAUNTS))
//		{
//			return true;
//		}
//		break;
//	}
//	case CHAR_VERGIL:
//	{
//		if ((motionData.group == MOTION_GROUP_VERGIL_BASE) && (motionData.index == 14))
//		{
//			return true;
//		}
//		if ((motionData.group == MOTION_GROUP_VERGIL_TAUNTS))
//		{
//			return true;
//		}
//		break;
//	}
//	}
//	return IsWeaponActive(baseAddr);
//}
//
//
//









//#define IsWeaponActive_sect0
//#define IsWeaponActiveSect0
//#define IsWeaponActive_Sect0
//#define IsWeaponActive_code0
//#define IsWeaponActiveCode0
//#define IsWeaponActive_code0
//#define IsWeaponActive
// #define sect0
// #define Section0
// Section0End
// SectionEnd0
// Section
// goto sect0;
// goto SectionEnd0
// part0
// Part0
// Code0

// Code1

//
//#define Code0 \
//auto & motionData = actorData.motionData[BODY_PART_UPPER];\
//if (weapon == WEAPON_VOID)\
//{\
//	return false;\
//}\
//
//#define Code1 \
//return false
//
//template <typename T>
//bool IsWeaponReady
//(
//	T & actorData,
//	uint8 weapon
//);
//
//template <>
//bool IsWeaponReady<ACTOR_DATA_DANTE>
//(
//	ACTOR_DATA_DANTE & actorData,
//	uint8 weapon
//)
//{
//	Code0;
//	if (motionData.group == (MOTION_GROUP_DANTE_REBELLION + weapon))
//	{
//		return true;
//	}
//	if (motionData.group == (MOTION_GROUP_DANTE_SWORDMASTER_REBELLION + weapon))
//	{
//		return true;
//	}
//	Code1;
//}
//
//template <>
//bool IsWeaponReady<ACTOR_DATA_VERGIL>
//(
//	ACTOR_DATA_VERGIL & actorData,
//	uint8 weapon
//)
//{
//	Code0;
//	if (motionData.group == (MOTION_GROUP_VERGIL_YAMATO + (weapon - WEAPON_VERGIL_YAMATO)))
//	{
//		return true;
//	}
//	Code1;
//}
//
//#undef Code1
//#undef Code0
//
//










////template <typename T>
//bool IsWeaponActive2
//(
//	ACTOR_DATA & actorData,
//	uint8 weapon
//)
//{
//	auto & motionData = actorData.motionData[BODY_PART_UPPER];
//	if (weapon == WEAPON_VOID)
//	{
//		return false;
//	}
//	if (actorData.character == CHAR_DANTE)
//	{
//		if (motionData.group == (MOTION_GROUP_DANTE_REBELLION + weapon))
//		{
//			return true;
//		}
//		if (motionData.group == (MOTION_GROUP_DANTE_SWORDMASTER_REBELLION + weapon))
//		{
//			return true;
//		}
//	}
//	else if (actorData.character == CHAR_VERGIL)
//	{
//		if (motionData.group == (MOTION_GROUP_VERGIL_YAMATO + (weapon - WEAPON_VERGIL_YAMATO)))
//		{
//			return true;
//		}
//	}
//	return false;
//}




//{
//	auto & meleeWeaponIndex = actorData.weaponIndex[0];
//	auto & meleeWeaponSwitchTimeout = actorData.weaponSwitchTimeout[0];

//	if (!(actorData.buttons[2] & GetBinding(ACTION_CHANGE_DEVIL_ARMS)))
//	{
//		goto sect0;
//	}
//	if (0 < meleeWeaponSwitchTimeout)
//	{
//		goto sect0;
//	}

//	auto & timeout = *reinterpret_cast<float32 *>(actorData.actionData[3] + 0x2F4);
//	meleeWeaponSwitchTimeout = timeout;

//	if (meleeWeaponIndex < 1)
//	{
//		meleeWeaponIndex++;
//	}
//	else
//	{
//		meleeWeaponIndex = 0;
//	}

//	auto g_pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
//	auto hud = *reinterpret_cast<byte8 **>(g_pool[11]);

//	func_280120(hud, 1, meleeWeaponIndex);

//	func_1EB0E0(actorData, 4);

//	if (actorData.devil || (actorData.devilState == 1))
//	{
//		func_1F92C0(actorData, 1);
//		func_1F97F0(actorData, true);
//	}
//}
//sect0:;


//auto & gamepad = GetGamepad(0);


//{
//	if (!(gamepad.buttons[2] & GetBinding(BINDING_CHANGE_DEVIL_ARMS)))
//	{
//		goto sect0;
//	}
//	if (0 < actorData.meleeWeaponSwitchTimeout)
//	{
//		goto sect0;
//	}

//	//auto & timeout = *reinterpret_cast<float32 *>(actorData.actionData[3] + 0x2F4);
//	float32 timeout = 1;
//	actorData.meleeWeaponSwitchTimeout = timeout;




//	//actorData.meleeWeaponIndex++;

//	//if (actorData.meleeWeaponIndex >= 2)
//	//{
//	//	actorData.meleeWeaponIndex = 0;
//	//}


//	//actorData.meleeWeaponIndex = (IsWeaponActive(actorData, actorData.meleeWeaponMap[0])) ? 1 : 0;



//	// @Research: It's not that simple. Also check weaponFlags for things like Sword Pierce or Grapple.
//	
//	if (!IsWeaponActive(actorData, actorData.meleeWeaponMap[0]))
//	{
//		actorData.meleeWeaponIndex = 0;
//	}
//	else
//	{
//		actorData.meleeWeaponIndex = 1;
//	}












//	actorData.newMeleeWeaponIndex++;

//	if (actorData.newMeleeWeaponIndex >= actorData.newMeleeWeaponCount)
//	{
//		actorData.newMeleeWeaponIndex = 0;
//	}


//	if (actorData.newMeleeWeaponMap[actorData.newMeleeWeaponIndex] != WEAPON_VERGIL_YAMATO)
//	{
//		actorData.meleeWeaponMap[actorData.meleeWeaponIndex] = actorData.newMeleeWeaponMap[actorData.newMeleeWeaponIndex];
//		actorData.meleeWeaponData[actorData.meleeWeaponIndex] = actorData.newMeleeWeaponData[actorData.newMeleeWeaponIndex];
//	}















//	{
//		auto & id = actorData.newMeleeWeaponMap[actorData.newMeleeWeaponIndex];
//		HUD_UpdateWeaponIcon(2, HUD_weaponIcon[id].model, HUD_weaponIcon[id].texture);
//	}


//	//HUD_UpdateWeaponIcon(0, HUD_weaponIcon[actorData.newMeleeWeaponMap[actorData]])


//	auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
//	auto hud = *reinterpret_cast<byte8 **>(pool[11]);
//	func_280120(hud, 1, 0);

//	func_1EB0E0(actorData, 4);

//	//if (actorData.devil || (actorData.devilState == 1))
//	//{
//	//	func_1F92C0(actorData, 1);
//	//	func_1F97F0(actorData, true);
//	//}
//}
//sect0:;




//return true;



























//inline void InitActorDante
//(
//	ACTOR_DATA_DANTE & actorData,
//	byte8 * sessionData
//)
//{
//	return func_217B90(actorData, sessionData);
//}
//
//inline void UpdateActorDante(ACTOR_DATA_DANTE & actorData)
//{
//	return func_212BE0(actorData);
//}




















//inline void UpdateRangedWeaponsDante
//(
//	ACTOR_DATA_DANTE & actorData,
//	uint8 player,
//	uint8 entity
//)
//{
//
//}

//inline void UpdateWeaponsDante
//(
//	ACTOR_DATA_DANTE & actorData,
//	uint8 player,
//	uint8 entity
//)
//{
//	memset((reinterpret_cast<byte8 *>(&actorData) + 0x648C), 0, (0x6510 - 0x648C));
//	UpdateMeleeWeaponsDante(actorData, player, entity);
//	UpdateRangedWeaponsDante(actorData, player, entity);
//}





















//ACTOR_DATA_DANTE * CreateActorDante
//(
//	uint8 player,
//	uint8 entity
//)
//{
//	auto g_pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
//	auto sessionData = (g_pool[1] + 0x16C);
//
//	auto baseAddr = func_1DE820(CHAR_DANTE, 0, false);
//	if (!baseAddr)
//	{
//		return 0;
//	}
//
//	auto & actorData = *reinterpret_cast<ACTOR_DATA_DANTE *>(baseAddr);
//
//	InitActorDante(actorData, sessionData);
//
//	actorData.costume = Config.Actor.costume[player][entity][CHAR_DANTE];
//	File_UpdateCostumeFileItems(actorData);
//
//	UpdateActorDante(actorData);
//
//	for_all(uint8, index, countof(motionHelperDante))
//	{
//		auto & group       = motionHelperDante[index].group;
//		auto & cacheFileId = motionHelperDante[index].cacheFileId;
//
//		auto & metadata = File_staticFiles[cacheFileId];
//
//		actorData.motionArchive[group] = File_dynamicFiles.Push(metadata.addr, metadata.size);
//	}
//
//	UpdateWeaponsDante(actorData, player, entity);
//
//	func_1DFC20(actorData);
//
//	return &actorData;
//}









//inline void InitActorVergil
//(
//	ACTOR_DATA_VERGIL & actorData,
//	byte8 * sessionData
//)
//{
//	return func_223CB0(actorData, sessionData);
//}
//
//inline void UpdateActorVergil(ACTOR_DATA_VERGIL & actorData)
//{
//	return func_220970(actorData);
//}

//inline void UpdateMeleeWeaponsVergil
//(
//	ACTOR_DATA_VERGIL & actorData,
//	uint8 player,
//	uint8 entity
//)
//{
//
//}

//void UpdateWeaponsVergil
//(
//	ACTOR_DATA_VERGIL & actorData,
//	uint8 player,
//	uint8 entity
//)
//{
//	memset((reinterpret_cast<byte8 *>(&actorData) + 0x648C), 0, (0x6510 - 0x648C));
//	UpdateMeleeWeaponsVergil(actorData, player, entity);
//}

//ACTOR_DATA_VERGIL * CreateActorVergil
//(
//	uint8 player,
//	uint8 entity
//)
//{
//	auto g_pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
//	auto sessionData = (g_pool[1] + 0x16C);
//
//	auto baseAddr = func_1DE820(CHAR_VERGIL, 0, false);
//	if (!baseAddr)
//	{
//		return 0;
//	}
//
//	auto & actorData = *reinterpret_cast<ACTOR_DATA_VERGIL *>(baseAddr);
//
//	InitActorVergil(actorData, sessionData);
//
//	actorData.costume = Config.Actor.costume[player][entity][CHAR_VERGIL];
//	File_UpdateCostumeFileItems(actorData);
//
//	UpdateActorVergil(actorData);
//
//	//for_all(uint8, index, countof(motionHelperVergil))
//	//{
//	//	auto & motionId    = motionHelperVergil[index].motionId;
//	//	auto & cacheFileId = motionHelperVergil[index].cacheFileId;
//
//	//	actorData.motionArchive[motionId] = File_staticFiles[cacheFileId];
//	//}
//
//	UpdateWeaponsVergil(actorData, player, entity);
//
//	func_1DFC20(actorData);
//
//	return &actorData;
//}






#endif
