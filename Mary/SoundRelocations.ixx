export module SoundRelocations;

import Core;

#include "../Core/Macros.h"

import Config;
import Global;
import Vars;





void UpdateGlobalHelperIndices(byte8 * bodyPartDataAddr)
{

	//LogFunction(bodyPartDataAddr);


	IntroduceData(bodyPartDataAddr, bodyPartData, BodyPartData, return);

	if (!bodyPartData.motionArchives)
	{
		return;
	}

	//Log("bodyPartData.motionArchives %llX", bodyPartData.motionArchives);

/*
enemyMotionArchivesOffs
*/


	// NewActorData

	old_for_all(uint8, index, countof(motionArchivesOffs))
	{
		auto & off = motionArchivesOffs[index];

		auto baseAddr = (reinterpret_cast<byte8 *>(bodyPartData.motionArchives) - off);
		if (!baseAddr)
		{
			continue;
		}

		//Log("baseAddr %llX", baseAddr);

		old_for_all(uint8, playerIndex   , activeConfig.Actor.playerCount){
		old_for_all(uint8, characterIndex, CHARACTER_COUNT               ){
		old_for_all(uint8, entityIndex   , ENTITY_COUNT                  )
		{
			IntroducePlayerCharacterNewActorData(playerIndex, characterIndex, entityIndex);

			if (baseAddr != newActorData.baseAddr)
			{
				continue;
			}


			//Log("Match baseAddr %llX", baseAddr);


			if (characterData.character == CHARACTER::BOSS_LADY)
			{
				g_helperIndices[CHANNEL::ENEMY] = HELPER_ENEMY_LADY;
			}
			else if (characterData.character == CHARACTER::BOSS_VERGIL)
			{
				g_helperIndices[CHANNEL::ENEMY] = HELPER_ENEMY_VERGIL;
			}
			else
			{
				// Common
				{
					auto & helperIndex = g_helperIndices[CHANNEL::COMMON];

					switch (characterData.character)
					{
						case CHARACTER::DANTE:
						{
							helperIndex = HELPER_COMMON_DANTE_DEFAULT;

							switch (characterData.costume)
							{
								case COSTUME::DANTE_DEFAULT_NO_COAT:
								case COSTUME::DANTE_DMC1_NO_COAT:
								{
									helperIndex = HELPER_COMMON_DANTE_NO_COAT;

									break;
								}
							}

							break;
						}
						case CHARACTER::VERGIL:
						{
							helperIndex = HELPER_COMMON_VERGIL_DEFAULT;

							switch (characterData.costume)
							{
								case COSTUME::VERGIL_NERO_ANGELO:
								case COSTUME::VERGIL_NERO_ANGELO_INFINITE_MAGIC_POINTS:
								{
									helperIndex = HELPER_COMMON_VERGIL_NERO_ANGELO;

									break;
								}
							}

							break;
						}
					}
				}

				// Style Weapon
				{
					auto & helperIndex = g_helperIndices[CHANNEL::STYLE_WEAPON];

					switch (characterData.character)
					{
						case CHARACTER::DANTE:
						{
							helperIndex = HELPER_STYLE_WEAPON_DANTE;

							break;
						}
						case CHARACTER::VERGIL:
						{
							helperIndex = HELPER_STYLE_WEAPON_VERGIL_DEFAULT;

							switch (characterData.costume)
							{
								case COSTUME::VERGIL_NERO_ANGELO:
								case COSTUME::VERGIL_NERO_ANGELO_INFINITE_MAGIC_POINTS:
								{
									helperIndex = HELPER_STYLE_WEAPON_VERGIL_NERO_ANGELO;

									break;
								}
							}

							break;
						}
					}
				}
			}



			return;
		}}}
	}



	if (activeConfig.soundIgnoreEnemyData)
	{
		return;
	}





	// // g_enemyActorBaseAddrs
	// {
	// 	auto & helperIndex = g_helperIndices[CHANNEL::ENEMY];

	// 	//IntroduceEnemyVectorData(return);

	// 	old_for_all(uint8, index, countof(motionArchivesOffs))
	// 	{
	// 		auto & off = motionArchivesOffs[index];

	// 		auto baseAddr = (reinterpret_cast<byte8 *>(bodyPartData.motionArchives) - off);
	// 		if (!baseAddr)
	// 		{
	// 			continue;
	// 		}

	// 		old_for_all(uint64, enemyIndex, g_enemyActorBaseAddrs.count)
	// 		{
	// 			// auto & metadata = enemyVectorData.metadata[enemyIndex];

	// 			// if (baseAddr != metadata.baseAddr)
	// 			// {
	// 			// 	continue;
	// 			// }

	// 			IntroduceData(g_enemyActorBaseAddrs[enemyIndex], actorData, EnemyActorData, continue);

	// 			auto enemy = actorData.enemy;
	// 			if (enemy >= ENEMY::COUNT)
	// 			{
	// 				enemy = 0;
	// 			}

	// 			helperIndex = enemyHelperIndices[enemy];

	// 			//Log("Updated enemy channel. %u", enemy);

	// 			return;
	// 		}
	// 	}
	// }






















	// EnemyVectorData
	{
		auto & helperIndex = g_helperIndices[CHANNEL::ENEMY];

		IntroduceEnemyVectorData(return);

		old_for_all(uint8, index, countof(motionArchivesOffs))
		{
			auto & off = motionArchivesOffs[index];

			auto baseAddr = (reinterpret_cast<byte8 *>(bodyPartData.motionArchives) - off);
			if (!baseAddr)
			{
				continue;
			}

			old_for_all(uint32, enemyIndex, countof(enemyVectorData.metadata))
			{
				auto & metadata = enemyVectorData.metadata[enemyIndex];

				if (baseAddr != metadata.baseAddr)
				{
					continue;
				}

				IntroduceData(metadata.baseAddr, actorData, EnemyActorData, continue);

				auto enemy = actorData.enemy;
				if (enemy >= ENEMY::COUNT)
				{
					enemy = 0;
				}

				helperIndex = enemyHelperIndices[enemy];

				return;
			}
		}
	}
}

























namespaceStart(Sound);

export void ToggleRelocations(bool enable)
{
	LogFunction(enable);

	static bool run = false;

	// $RelocationDataStart

	{
		auto addr     = (appBaseAddr + 0x59DE0);
		auto jumpAddr = (appBaseAddr + 0x59DE7);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+59DE0 - 48 8D 0D A93ED100 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+59DE7
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(UpdateGlobalHelperIndices, jumpAddr, true, true, size, sizeof(sect1));
			CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, sizeof(sect1));
			WriteAddress(func.sect0, (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x59E2F);
		auto jumpAddr = (appBaseAddr + 0x59E36);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+59E2F - 48 8D 0D 5A3ED100 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+59E36
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(UpdateGlobalHelperIndices, jumpAddr, true, true, size, sizeof(sect1));
			CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, sizeof(sect1));
			WriteAddress(func.sect0, (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x59E75);
		auto jumpAddr = (appBaseAddr + 0x59E7C);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+59E75 - 48 8D 0D 143ED100 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+59E7C
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(UpdateGlobalHelperIndices, jumpAddr, true, true, size, sizeof(sect1));
			CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, sizeof(sect1));
			WriteAddress(func.sect0, (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x59EBD);
		auto jumpAddr = (appBaseAddr + 0x59EC4);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+59EBD - 48 8D 0D CC3DD100 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+59EC4
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(UpdateGlobalHelperIndices, jumpAddr, true, true, size, sizeof(sect1));
			CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, sizeof(sect1));
			WriteAddress(func.sect0, (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x59F69);
		auto jumpAddr = (appBaseAddr + 0x59F70);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+59F69 - 48 8D 0D 203DD100 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+59F70
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(UpdateGlobalHelperIndices, jumpAddr, true, true, size, sizeof(sect1));
			CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, sizeof(sect1));
			WriteAddress(func.sect0, (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x5A051);
		auto jumpAddr = (appBaseAddr + 0x5A058);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+5A051 - 48 8D 0D 383CD100 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+5A058
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(UpdateGlobalHelperIndices, jumpAddr, true, true, size, sizeof(sect1));
			CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, sizeof(sect1));
			WriteAddress(func.sect0, (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x5A087);
		auto jumpAddr = (appBaseAddr + 0x5A08E);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+5A087 - 48 8D 0D 023CD100 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+5A08E
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(UpdateGlobalHelperIndices, jumpAddr, true, true, size, sizeof(sect1));
			CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, sizeof(sect1));
			WriteAddress(func.sect0, (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x5A0CA);
		auto jumpAddr = (appBaseAddr + 0x5A0D1);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+5A0CA - 48 8D 0D BF3BD100 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+5A0D1
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(UpdateGlobalHelperIndices, jumpAddr, true, true, size, sizeof(sect1));
			CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, sizeof(sect1));
			WriteAddress(func.sect0, (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x16975C);
		auto jumpAddr = (appBaseAddr + 0x169763);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+16975C - 48 8D 0D 2D45C000 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+169763
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::ENEMY];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_ENEMY_LADY;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x169800);
		auto jumpAddr = (appBaseAddr + 0x169807);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+169800 - 48 8D 0D 8944C000 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+169807
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::ENEMY];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_ENEMY_LADY;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1699AB);
		auto jumpAddr = (appBaseAddr + 0x1699B2);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1699AB - 48 8D 0D DE42C000 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1699B2
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::ENEMY];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_ENEMY_LADY;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x169A7B);
		auto jumpAddr = (appBaseAddr + 0x169A82);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+169A7B - 48 8D 0D 0E42C000 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+169A82
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::ENEMY];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_ENEMY_LADY;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x169FFA);
		auto jumpAddr = (appBaseAddr + 0x16A001);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+169FFA - 48 8D 0D 8F3CC000 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+16A001
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::ENEMY];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_ENEMY_LADY;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x16BD37);
		auto jumpAddr = (appBaseAddr + 0x16BD3E);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+16BD37 - 48 8D 0D 521FC000 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+16BD3E
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::ENEMY];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_ENEMY_LADY;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x16D694);
		auto jumpAddr = (appBaseAddr + 0x16D69B);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+16D694 - 48 8D 0D F505C000 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+16D69B
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::ENEMY];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_ENEMY_LADY;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x16EFFB);
		auto jumpAddr = (appBaseAddr + 0x16F002);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+16EFFB - 48 8D 0D 8EECBF00 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+16F002
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::ENEMY];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_ENEMY_LADY;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x171E82);
		auto jumpAddr = (appBaseAddr + 0x171E89);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+171E82 - 48 8D 0D 07BEBF00 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+171E89
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::ENEMY];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_ENEMY_LADY;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x17268E);
		auto jumpAddr = (appBaseAddr + 0x172695);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+17268E - 48 8D 0D FBB5BF00 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+172695
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::ENEMY];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_ENEMY_LADY;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x172700);
		auto jumpAddr = (appBaseAddr + 0x172707);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+172700 - 48 8D 0D 89B5BF00 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+172707
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::ENEMY];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_ENEMY_LADY;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x172753);
		auto jumpAddr = (appBaseAddr + 0x17275A);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+172753 - 48 8D 0D 36B5BF00 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+17275A
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::ENEMY];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_ENEMY_LADY;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x172B9D);
		auto jumpAddr = (appBaseAddr + 0x172BA4);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+172B9D - 48 8D 0D ECB0BF00 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+172BA4
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::ENEMY];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_ENEMY_LADY;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x172F86);
		auto jumpAddr = (appBaseAddr + 0x172F8D);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+172F86 - 48 8D 0D 03ADBF00 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+172F8D
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::ENEMY];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_ENEMY_LADY;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x17389D);
		auto jumpAddr = (appBaseAddr + 0x1738A4);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+17389D - 48 8D 0D ECA3BF00 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1738A4
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::ENEMY];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_ENEMY_LADY;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x173CFD);
		auto jumpAddr = (appBaseAddr + 0x173D04);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+173CFD - 48 8D 0D 8C9FBF00 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+173D04
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::ENEMY];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_ENEMY_LADY;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1777D5);
		auto jumpAddr = (appBaseAddr + 0x1777DC);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1777D5 - 48 8D 0D B464BF00 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1777DC
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::ENEMY];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_ENEMY_VERGIL;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x178C29);
		auto jumpAddr = (appBaseAddr + 0x178C30);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+178C29 - 48 8D 0D 6050BF00 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+178C30
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::ENEMY];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_ENEMY_VERGIL;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x17B167);
		auto jumpAddr = (appBaseAddr + 0x17B16E);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+17B167 - 48 8D 0D 222BBF00 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+17B16E
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::ENEMY];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_ENEMY_VERGIL;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x17B185);
		auto jumpAddr = (appBaseAddr + 0x17B18C);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+17B185 - 48 8D 0D 042BBF00 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+17B18C
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::ENEMY];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_ENEMY_VERGIL;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x17B6C5);
		auto jumpAddr = (appBaseAddr + 0x17B6CC);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+17B6C5 - 48 8D 0D C425BF00 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+17B6CC
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::ENEMY];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_ENEMY_VERGIL;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x17CB9E);
		auto jumpAddr = (appBaseAddr + 0x17CBA5);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+17CB9E - 48 8D 0D EB10BF00 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+17CBA5
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::ENEMY];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_ENEMY_VERGIL;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x17CBC6);
		auto jumpAddr = (appBaseAddr + 0x17CBCD);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+17CBC6 - 48 8D 0D C310BF00 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+17CBCD
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::ENEMY];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_ENEMY_VERGIL;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x17CDD3);
		auto jumpAddr = (appBaseAddr + 0x17CDDA);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+17CDD3 - 48 8D 0D B60EBF00 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+17CDDA
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::ENEMY];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_ENEMY_VERGIL;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x17CF01);
		auto jumpAddr = (appBaseAddr + 0x17CF08);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+17CF01 - 48 8D 0D 880DBF00 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+17CF08
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::ENEMY];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_ENEMY_VERGIL;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x17CF44);
		auto jumpAddr = (appBaseAddr + 0x17CF4B);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+17CF44 - 48 8D 0D 450DBF00 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+17CF4B
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::ENEMY];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_ENEMY_VERGIL;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1802E0);
		auto jumpAddr = (appBaseAddr + 0x1802E7);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1802E0 - 48 8D 0D A9D9BE00 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1802E7
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::ENEMY];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_ENEMY_VERGIL;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1879B0);
		auto jumpAddr = (appBaseAddr + 0x1879B7);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1879B0 - 48 8D 0D D962BE00 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1879B7
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::ENEMY];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_ENEMY_VERGIL;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x18802F);
		auto jumpAddr = (appBaseAddr + 0x188036);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+18802F - 48 8D 0D 5A5CBE00 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+188036
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::ENEMY];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_ENEMY_VERGIL;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1883C7);
		auto jumpAddr = (appBaseAddr + 0x1883CE);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1883C7 - 48 8D 0D C258BE00 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1883CE
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::ENEMY];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_ENEMY_VERGIL;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x18887B);
		auto jumpAddr = (appBaseAddr + 0x188882);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+18887B - 48 8D 0D 0E54BE00 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+188882
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::ENEMY];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_ENEMY_VERGIL;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1CBB03);
		auto jumpAddr = (appBaseAddr + 0x1CBB0A);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1CBB03 - 48 8D 0D 8621BA00 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1CBB0A
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1CBF64);
		auto jumpAddr = (appBaseAddr + 0x1CBF6B);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1CBF64 - 48 8D 0D 251DBA00 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1CBF6B
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1CD97B);
		auto jumpAddr = (appBaseAddr + 0x1CD982);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1CD97B - 48 8D 0D 0E03BA00 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1CD982
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1CE059);
		auto jumpAddr = (appBaseAddr + 0x1CE060);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1CE059 - 48 8D 0D 30FCB900 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1CE060
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1CE0AC);
		auto jumpAddr = (appBaseAddr + 0x1CE0B3);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1CE0AC - 48 8D 0D DDFBB900 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1CE0B3
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1CE9B8);
		auto jumpAddr = (appBaseAddr + 0x1CE9BF);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1CE9B8 - 48 8D 0D D1F2B900 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1CE9BF
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1CF013);
		auto jumpAddr = (appBaseAddr + 0x1CF01A);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1CF013 - 48 8D 0D 76ECB900 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1CF01A
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1CFDDC);
		auto jumpAddr = (appBaseAddr + 0x1CFDE3);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1CFDDC - 48 8D 0D ADDEB900 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1CFDE3
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1CFE53);
		auto jumpAddr = (appBaseAddr + 0x1CFE5A);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1CFE53 - 48 8D 0D 36DEB900 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1CFE5A
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1D0010);
		auto jumpAddr = (appBaseAddr + 0x1D0017);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1D0010 - 48 8D 0D 79DCB900 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1D0017
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1D0A1E);
		auto jumpAddr = (appBaseAddr + 0x1D0A25);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1D0A1E - 48 8D 0D 6BD2B900 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1D0A25
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1D0F34);
		auto jumpAddr = (appBaseAddr + 0x1D0F3B);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1D0F34 - 48 8D 0D 55CDB900 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1D0F3B
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1D195D);
		auto jumpAddr = (appBaseAddr + 0x1D1964);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1D195D - 48 8D 0D 2CC3B900 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1D1964
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1D255F);
		auto jumpAddr = (appBaseAddr + 0x1D2566);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1D255F - 48 8D 0D 2AB7B900 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1D2566
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1D34FA);
		auto jumpAddr = (appBaseAddr + 0x1D3501);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1D34FA - 48 8D 0D 8FA7B900 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1D3501
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1D4520);
		auto jumpAddr = (appBaseAddr + 0x1D4527);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1D4520 - 48 8D 0D 6997B900 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1D4527
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1D6843);
		auto jumpAddr = (appBaseAddr + 0x1D684A);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1D6843 - 48 8D 0D 4674B900 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1D684A
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1D6870);
		auto jumpAddr = (appBaseAddr + 0x1D6877);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1D6870 - 48 8D 0D 1974B900 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1D6877
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1D6979);
		auto jumpAddr = (appBaseAddr + 0x1D6980);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1D6979 - 48 8D 0D 1073B900 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1D6980
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1D6DF1);
		auto jumpAddr = (appBaseAddr + 0x1D6DF8);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1D6DF1 - 48 8D 0D 986EB900 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1D6DF8
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1D7896);
		auto jumpAddr = (appBaseAddr + 0x1D789D);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1D7896 - 48 8D 0D F363B900 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1D789D
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1D8165);
		auto jumpAddr = (appBaseAddr + 0x1D816C);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1D8165 - 48 8D 0D 245BB900 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1D816C
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1D881E);
		auto jumpAddr = (appBaseAddr + 0x1D8825);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1D881E - 48 8D 0D 6B54B900 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1D8825
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_VERGIL_DEFAULT;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1D8EE7);
		auto jumpAddr = (appBaseAddr + 0x1D8EEE);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1D8EE7 - 48 8D 0D A24DB900 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1D8EEE
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_VERGIL_DEFAULT;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1D9383);
		auto jumpAddr = (appBaseAddr + 0x1D938A);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1D9383 - 48 8D 0D 0649B900 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1D938A
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_VERGIL_DEFAULT;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1D9C70);
		auto jumpAddr = (appBaseAddr + 0x1D9C77);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1D9C70 - 48 8D 0D 1940B900 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1D9C77
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_VERGIL_DEFAULT;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1DB4FC);
		auto jumpAddr = (appBaseAddr + 0x1DB503);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1DB4FC - 48 8D 0D 8D27B900 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1DB503
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_VERGIL_DEFAULT;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1DB927);
		auto jumpAddr = (appBaseAddr + 0x1DB92E);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1DB927 - 48 8D 0D 6223B900 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1DB92E
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_VERGIL_DEFAULT;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1DBA89);
		auto jumpAddr = (appBaseAddr + 0x1DBA90);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1DBA89 - 48 8D 0D 0022B900 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1DBA90
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_VERGIL_DEFAULT;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1DBE68);
		auto jumpAddr = (appBaseAddr + 0x1DBE6F);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1DBE68 - 48 8D 0D 211EB900 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1DBE6F
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_VERGIL_DEFAULT;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1DC9C0);
		auto jumpAddr = (appBaseAddr + 0x1DC9C7);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1DC9C0 - 48 8D 0D C912B900 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1DC9C7
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_VERGIL_NERO_ANGELO;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1DCD22);
		auto jumpAddr = (appBaseAddr + 0x1DCD29);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1DCD22 - 48 8D 0D 670FB900 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1DCD29
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_VERGIL_NERO_ANGELO;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1E9506);
		auto jumpAddr = (appBaseAddr + 0x1E950D);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1E9506 - 48 8D 0D 8347B800 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1E950D
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1E958B);
		auto jumpAddr = (appBaseAddr + 0x1E9592);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1E958B - 48 8D 0D FE46B800 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1E9592
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1EAC41);
		auto jumpAddr = (appBaseAddr + 0x1EAC48);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1EAC41 - 48 8D 0D 4830B800 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1EAC48
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1EAEAA);
		auto jumpAddr = (appBaseAddr + 0x1EAEB1);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1EAEAA - 48 8D 0D DF2DB800 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1EAEB1
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1EAF41);
		auto jumpAddr = (appBaseAddr + 0x1EAF48);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1EAF41 - 48 8D 0D 482DB800 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1EAF48
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1EAFA6);
		auto jumpAddr = (appBaseAddr + 0x1EAFAD);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1EAFA6 - 48 8D 0D E32CB800 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1EAFAD
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1EE768);
		auto jumpAddr = (appBaseAddr + 0x1EE76F);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1EE768 - 48 8D 0D 21F5B700 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1EE76F
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1F3778);
		auto jumpAddr = (appBaseAddr + 0x1F377F);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1F3778 - 48 8D 0D 11A5B700 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1F377F
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1F8A8E);
		auto jumpAddr = (appBaseAddr + 0x1F8A95);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1F8A8E - 48 8D 0D FB51B700 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1F8A95
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x1FEFC4);
		auto jumpAddr = (appBaseAddr + 0x1FEFCB);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1FEFC4 - 48 8D 0D C5ECB600 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+1FEFCB
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x200631);
		auto jumpAddr = (appBaseAddr + 0x200638);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+200631 - 48 8D 0D 58D6B600 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+200638
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x2016C3);
		auto jumpAddr = (appBaseAddr + 0x2016CA);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+2016C3 - 48 8D 0D C6C5B600 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+2016CA
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x201AE5);
		auto jumpAddr = (appBaseAddr + 0x201AEC);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+201AE5 - 48 8D 0D A4C1B600 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+201AEC
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x201B1A);
		auto jumpAddr = (appBaseAddr + 0x201B21);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+201B1A - 48 8D 0D 6FC1B600 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+201B21
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x201B3A);
		auto jumpAddr = (appBaseAddr + 0x201B41);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+201B3A - 48 8D 0D 4FC1B600 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+201B41
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x201CCE);
		auto jumpAddr = (appBaseAddr + 0x201CD5);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+201CCE - 48 8D 0D BBBFB600 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+201CD5
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x201CEB);
		auto jumpAddr = (appBaseAddr + 0x201CF2);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+201CEB - 48 8D 0D 9EBFB600 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+201CF2
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x204186);
		auto jumpAddr = (appBaseAddr + 0x20418D);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+204186 - 48 8D 0D 039BB600 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+20418D
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x205E12);
		auto jumpAddr = (appBaseAddr + 0x205E19);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+205E12 - 48 8D 0D 777EB600 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+205E19
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x206207);
		auto jumpAddr = (appBaseAddr + 0x20620E);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+206207 - 48 8D 0D 827AB600 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+20620E
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x20726E);
		auto jumpAddr = (appBaseAddr + 0x207275);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+20726E - 48 8D 0D 1B6AB600 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+207275
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x208774);
		auto jumpAddr = (appBaseAddr + 0x20877B);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+208774 - 48 8D 0D 1555B600 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+20877B
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x209E41);
		auto jumpAddr = (appBaseAddr + 0x209E48);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+209E41 - 48 8D 0D 483EB600 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+209E48
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x20B25D);
		auto jumpAddr = (appBaseAddr + 0x20B264);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+20B25D - 48 8D 0D 2C2AB600 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+20B264
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x20C43E);
		auto jumpAddr = (appBaseAddr + 0x20C445);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+20C43E - 48 8D 0D 4B18B600 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+20C445
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x20C761);
		auto jumpAddr = (appBaseAddr + 0x20C768);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+20C761 - 48 8D 0D 2815B600 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+20C768
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x20C78D);
		auto jumpAddr = (appBaseAddr + 0x20C794);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+20C78D - 48 8D 0D FC14B600 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+20C794
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x20C7FC);
		auto jumpAddr = (appBaseAddr + 0x20C803);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+20C7FC - 48 8D 0D 8D14B600 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+20C803
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x20C8B7);
		auto jumpAddr = (appBaseAddr + 0x20C8BE);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+20C8B7 - 48 8D 0D D213B600 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+20C8BE
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x20D625);
		auto jumpAddr = (appBaseAddr + 0x20D62C);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+20D625 - 48 8D 0D 6406B600 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+20D62C
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x20D78B);
		auto jumpAddr = (appBaseAddr + 0x20D792);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+20D78B - 48 8D 0D FE04B600 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+20D792
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x20DD2D);
		auto jumpAddr = (appBaseAddr + 0x20DD34);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+20DD2D - 48 8D 0D 5CFFB500 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+20DD34
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x20E3CA);
		auto jumpAddr = (appBaseAddr + 0x20E3D1);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+20E3CA - 48 8D 0D BFF8B500 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+20E3D1
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x20E6F3);
		auto jumpAddr = (appBaseAddr + 0x20E6FA);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+20E6F3 - 48 8D 0D 96F5B500 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+20E6FA
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x20E773);
		auto jumpAddr = (appBaseAddr + 0x20E77A);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+20E773 - 48 8D 0D 16F5B500 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+20E77A
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x20EE73);
		auto jumpAddr = (appBaseAddr + 0x20EE7A);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+20EE73 - 48 8D 0D 16EEB500 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+20EE7A
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x210593);
		auto jumpAddr = (appBaseAddr + 0x21059A);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+210593 - 48 8D 0D F6D6B500 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+21059A
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x21072B);
		auto jumpAddr = (appBaseAddr + 0x210732);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+21072B - 48 8D 0D 5ED5B500 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+210732
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x211BD9);
		auto jumpAddr = (appBaseAddr + 0x211BE0);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+211BD9 - 48 8D 0D B0C0B500 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+211BE0
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x2156B2);
		auto jumpAddr = (appBaseAddr + 0x2156B9);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+2156B2 - 48 8D 0D D785B500 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+2156B9
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x215B1E);
		auto jumpAddr = (appBaseAddr + 0x215B25);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+215B1E - 48 8D 0D 6B81B500 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+215B25
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x215DC5);
		auto jumpAddr = (appBaseAddr + 0x215DCC);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+215DC5 - 48 8D 0D C47EB500 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+215DCC
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x215F64);
		auto jumpAddr = (appBaseAddr + 0x215F6B);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+215F64 - 48 8D 0D 257DB500 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+215F6B
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x216037);
		auto jumpAddr = (appBaseAddr + 0x21603E);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+216037 - 48 8D 0D 527CB500 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+21603E
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x216177);
		auto jumpAddr = (appBaseAddr + 0x21617E);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+216177 - 48 8D 0D 127BB500 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+21617E
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x2161CB);
		auto jumpAddr = (appBaseAddr + 0x2161D2);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+2161CB - 48 8D 0D BE7AB500 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+2161D2
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x21638C);
		auto jumpAddr = (appBaseAddr + 0x216393);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+21638C - 48 8D 0D FD78B500 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+216393
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x2163E0);
		auto jumpAddr = (appBaseAddr + 0x2163E7);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+2163E0 - 48 8D 0D A978B500 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+2163E7
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x21655A);
		auto jumpAddr = (appBaseAddr + 0x216561);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+21655A - 48 8D 0D 2F77B500 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+216561
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x216CB4);
		auto jumpAddr = (appBaseAddr + 0x216CBB);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+216CB4 - 48 8D 0D D56FB500 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+216CBB
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x216D55);
		auto jumpAddr = (appBaseAddr + 0x216D5C);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+216D55 - 48 8D 0D 346FB500 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+216D5C
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x216FF3);
		auto jumpAddr = (appBaseAddr + 0x216FFA);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+216FF3 - 48 8D 0D 966CB500 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+216FFA
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x218177);
		auto jumpAddr = (appBaseAddr + 0x21817E);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+218177 - 48 8D 0D 125BB500 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+21817E
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x21820B);
		auto jumpAddr = (appBaseAddr + 0x218212);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+21820B - 48 8D 0D 7E5AB500 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+218212
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x218496);
		auto jumpAddr = (appBaseAddr + 0x21849D);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+218496 - 48 8D 0D F357B500 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+21849D
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_DANTE;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x21CD6B);
		auto jumpAddr = (appBaseAddr + 0x21CD72);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+21CD6B - 48 8D 0D 1E0FB500 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+21CD72
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_VERGIL_DEFAULT;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x21CE68);
		auto jumpAddr = (appBaseAddr + 0x21CE6F);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+21CE68 - 48 8D 0D 210EB500 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+21CE6F
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_VERGIL_DEFAULT;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x222CD0);
		auto jumpAddr = (appBaseAddr + 0x222CD7);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+222CD0 - 48 8D 0D B9AFB400 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+222CD7
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_VERGIL_NERO_ANGELO;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x222E54);
		auto jumpAddr = (appBaseAddr + 0x222E5B);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+222E54 - 48 8D 0D 35AEB400 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+222E5B
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_VERGIL_DEFAULT;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x223022);
		auto jumpAddr = (appBaseAddr + 0x223029);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+223022 - 48 8D 0D 67ACB400 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+223029
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_VERGIL_DEFAULT;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x223BB7);
		auto jumpAddr = (appBaseAddr + 0x223BBE);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+223BB7 - 48 8D 0D D2A0B400 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+223BBE
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_VERGIL_DEFAULT;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x22401F);
		auto jumpAddr = (appBaseAddr + 0x224026);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+22401F - 48 8D 0D 6A9CB400 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+224026
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_VERGIL_DEFAULT;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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
	{
		auto addr     = (appBaseAddr + 0x2240B8);
		auto jumpAddr = (appBaseAddr + 0x2240BF);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+2240B8 - 48 8D 0D D19BB400 - LEA RCX,[dmc3.exe+D6DC90]
		dmc3.exe+2240BF
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0
			0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[CHANNEL::STYLE_WEAPON];
			*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = HELPER_STYLE_WEAPON_VERGIL_DEFAULT;
			WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);
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

	// $RelocationDataEnd

	run = true;
}

namespaceEnd();
