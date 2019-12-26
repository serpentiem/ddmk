
// @Todo: Auto vars and update types.
// @Todo: Add Private.


#include "Sound.h"


constexpr bool debug = false;




#pragma region Global Definitions

enum SOUND_
{
	MAX_SOUND = 10000,
	MAX_SOUND_PER_CHANNEL = 625,
};

enum CHANNEL_
{
	CHANNEL_SYSTEM,
	CHANNEL_COMMON,
	CHANNEL_STYLE_WEAPON,
	CHANNEL_WEAPON1,
	CHANNEL_WEAPON2,
	CHANNEL_WEAPON3,
	CHANNEL_WEAPON4,
	CHANNEL_ENEMY,
	CHANNEL_ROOM,
	CHANNEL_MUSIC,
	CHANNEL_DEMO,
	MAX_CHANNEL = 16,
};

enum PROG_SECT_
{
	PROG_SECT_REBELLION,
	PROG_SECT_CERBERUS,
	PROG_SECT_AGNI_RUDRA,
	PROG_SECT_NEVAN,
	PROG_SECT_BEOWULF,
	PROG_SECT_EBONY_IVORY,
	PROG_SECT_SHOTGUN,
	PROG_SECT_ARTEMIS,
	PROG_SECT_SPIRAL,
	PROG_SECT_KALINA_ANN,
	PROG_SECT_YAMATO = 11,
	PROG_SECT_BEOWULF_VERGIL,
	PROG_SECT_FORCE_EDGE,
	PROG_SECT_SWORDMASTER = 100,
	PROG_SECT_GUNSLINGER,
	PROG_SECT_TRICKSTER,
	PROG_SECT_ROYALGUARD,
	PROG_SECT_QUICKSILVER,
	PROG_SECT_DOPPELGANGER,
	PROG_SECT_BATTLE_OF_BROTHERS,
	PROG_SECT_DARK_SLAYER,
	MAX_PROG_SECT,
};

struct HEAD
{
	byte signature[4];
	byte unknown[8];
	uint32 size;
	uint32 waveSize;
	uint32 progOff;
	uint32 smplOff;
	uint32 vagiOff;
};

struct PROG_METADATA
{
	byte signature[4];
	uint32 size;
	uint32 last;
};

struct PROG_SECT_METADATA
{
	uint8 itemCount;
	byte unknown[7];
};

struct PROG_SECT_ITEM
{
	byte unknown[12];
	uint16 id;
};

struct SMPL_METADATA
{
	byte signature[4];
	uint32 size;
	uint32 last;
};

struct SMPL_ITEM
{
	byte unknown[10];
	uint16 id;
};

struct VAGI_METADATA
{
	byte signature[4];
	uint32 size;
	uint32 last;
};

struct VAGI_ITEM
{
	uint32 off;
	uint32 size;
	byte unknown[4];
	uint32 sampleRate;
};

struct G_PROG
{
	byte * addr;
	uint64 pos;
	uint64 count;
	uint32 * off;
	uint8 id[MAX_PROG_SECT];

	PROG_SECT_METADATA & Push(PROG_SECT_METADATA & sect, uint8 index) // @Research: Convention for identical names.
	{
		off[count] = (uint32)pos;


		id[count] = index;






		PROG_SECT_METADATA & newSect = *(PROG_SECT_METADATA *)(addr + pos) = sect;
		pos += sizeof(PROG_SECT_METADATA);
		count++;
		return newSect;
	}
	PROG_SECT_ITEM & Push(PROG_SECT_ITEM & item)
	{
		PROG_SECT_ITEM & newItem = *(PROG_SECT_ITEM *)(addr + pos) = item;
		pos += sizeof(PROG_SECT_ITEM);
		return newItem;
	}
};

struct G_SMPL
{
	SMPL_ITEM * addr;
	uint64 count;
	SMPL_ITEM & Push(SMPL_ITEM & item)
	{
		SMPL_ITEM & newItem = addr[count] = item;
		count++;
		return newItem;
	}
};

struct G_VAGI
{
	VAGI_ITEM * addr;
	uint64 count;
	VAGI_ITEM & Push(VAGI_ITEM & item)
	{
		VAGI_ITEM & newItem = addr[count] = item;
		count++;
		return newItem;
	}
};

struct WAVE_ITEM
{
	byte * addr;
	uint32 size;
};

struct G_WAVE
{
	byte * addr;
	uint32 pos;
	uint32 count;
	uint32 * off;
	uint32 * size;
	byte * Push(byte * item, uint32 itemSize)
	{
		off[count] = pos;
		size[count] = itemSize;
		byte * newItem = (addr + pos);
		memcpy(newItem, item, itemSize);
		pos += itemSize;
		count++;
		return newItem;
	}
	WAVE_ITEM operator[](uint32 index)
	{
		WAVE_ITEM item = {};
		item.addr = (addr + off[index]);
		item.size = size[index];
		return item;
	}
};

struct SOUND_ITEM
{
	uint64 pos;
	uint64 size;
	FMOD_SOUND * sound;
};

struct G_ITEM
{
	SOUND_ITEM * addr;
	uint32 count;
	SOUND_ITEM & operator[](uint32 index)
	{
		return addr[index];
	}
};

uint64 posMap[MAX_CHANNEL] = {};

G_PROG   g_prog[MAX_CHANNEL] = {};
G_SMPL   g_smpl[MAX_CHANNEL] = {};
G_VAGI   g_vagi[MAX_CHANNEL] = {};
G_WAVE   g_wave[MAX_CHANNEL] = {};
byte   * g_map [MAX_CHANNEL] = {};
G_ITEM   g_item[MAX_CHANNEL] = {};

#pragma endregion

static void Decompile
(
	byte  * archive,
	uint8   channel,
	uint8   progId
)
{
	if constexpr (debug)
	{
		LogFunctionStart();
	}

	uint32 & fileCount = *(uint32 *)(archive + 4);
	uint16 smplCount = (uint16)g_smpl[channel].count;
	uint16 vagiCount = (uint16)g_vagi[channel].count;
	uint32 waveItemCount = 0;

	if constexpr (debug)
	{
		Log("archive   %llX", archive);
		Log("channel   %u"  , channel);
		Log("fileCount %u", fileCount);
		Log("");
	}

	for (uint8 fileIndex = 0; fileIndex < fileCount; fileIndex++)
	{
		uint32 fileOff = ((uint32 *)(archive + 8))[fileIndex];
		byte * file = (archive + fileOff);

		if constexpr (debug)
		{
			Log("file %u %llX", fileIndex, file);
			Log("");
		}

		Head:
		{
			byte signature[] = { 'H','e','a','d' };
			for (uint8 index = 0; index < countof(signature); index++)
			{
				if (file[index] != signature[index])
				{
					goto Wave;
				}
			}

			if constexpr (debug)
			{
				Log("Head");
				Log("");
			}

			HEAD & head = *(HEAD *)file;

			if constexpr (debug)
			{
				Log("Prog");
			}

			{
				PROG_METADATA & prog = *(PROG_METADATA *)(file + head.progOff);
				G_PROG & dest = g_prog[channel];
				if constexpr (debug)
				{
					Log("last %u", prog.last);
				}
				uint32 sectCount = (prog.last + 1);
				for (uint32 sectIndex = 0; sectIndex < sectCount; sectIndex++)
				{
					uint32 off = ((uint32 *)(file + head.progOff + 0x10))[sectIndex];
					if (off == 0xFFFFFFFF)
					{
						continue;
					}
					if constexpr (debug)
					{
						Log("off %X", off);
					}
					PROG_SECT_METADATA & sect = *(PROG_SECT_METADATA *)(file + head.progOff + off);
					dest.Push(sect, progId);

					for (uint8 itemIndex = 0; itemIndex < sect.itemCount; itemIndex++)
					{
						PROG_SECT_ITEM & item = ((PROG_SECT_ITEM *)(file + head.progOff + off + sizeof(PROG_SECT_METADATA)))[itemIndex];
						PROG_SECT_ITEM & newItem = dest.Push(item);
						newItem.id += smplCount;
					}
				}
				if constexpr (debug)
				{
					Log("g_prog[%u] addr  %llX", channel, dest.addr );
					Log("g_prog[%u] pos   %llX", channel, dest.pos  );
					Log("g_prog[%u] count %llu", channel, dest.count);
				}
			}
			if constexpr (debug)
			{
				Log("");
				Log("Smpl");
			}
			{
				SMPL_METADATA & smpl = *(SMPL_METADATA *)(file + head.smplOff);
				G_SMPL & dest = g_smpl[channel];
				if constexpr (debug)
				{
					Log("last %u", smpl.last);
				}
				uint32 itemCount = (smpl.last + 1);
				for (uint32 itemIndex = 0; itemIndex < itemCount; itemIndex++)
				{
					SMPL_ITEM & item = ((SMPL_ITEM *)(file + head.smplOff + 0x10))[itemIndex];
					SMPL_ITEM & newItem = dest.Push(item);
					newItem.id += vagiCount;
				}
				if constexpr (debug)
				{
					Log("g_smpl[%u] addr  %llX", channel, dest.addr );
					Log("g_smpl[%u] count %llu", channel, dest.count);
				}
			}
			if constexpr (debug)
			{
				Log("");
				Log("Vagi");
			}
			{
				VAGI_METADATA & vagi = *(VAGI_METADATA *)(file + head.vagiOff);
				G_VAGI & dest = g_vagi[channel];
				if constexpr (debug)
				{
					Log("last %u", vagi.last);
				}
				uint32 itemCount = (vagi.last + 1);
				for (uint32 itemIndex = 0; itemIndex < itemCount; itemIndex++)
				{
					VAGI_ITEM & item = ((VAGI_ITEM *)(file + head.vagiOff + 0x10))[itemIndex];
					VAGI_ITEM & newItem = dest.Push(item);
					newItem.off = 0;
				}
				if constexpr (debug)
				{
					Log("g_vagi[%u] addr  %llX", channel, dest.addr );
					Log("g_vagi[%u] count %llu", channel, dest.count);
				}
				waveItemCount = itemCount;
			}
			if constexpr (debug)
			{
				Log("");
			}
		}
		Wave:
		{
			byte signature[] = { 'V','A','G','p' };
			for (uint8 index = 0; index < countof(signature); index++)
			{
				if (file[index] != signature[index])
				{
					goto End;
				}
			}
			G_WAVE & dest = g_wave[channel];
			if constexpr (debug)
			{
				Log("Wave");
				Log("waveItemCount %u", waveItemCount);
			}
			uint32 filePos = 0;
			for (uint32 itemIndex = 0; itemIndex < waveItemCount; itemIndex++)
			{
				byte * item = (file + filePos);
				uint32 itemSize = (Reverse((uint32 *)(item + 0xC)) + 0x30);
				if constexpr (debug)
				{
					Log("item     %llX", item);
					Log("itemSize %X", itemSize);
				}
				dest.Push(item, itemSize);
				filePos += itemSize;
			}
			if constexpr (debug)
			{
				Log("g_wave[%u] addr  %llX", channel, dest.addr );
				Log("g_wave[%u] pos   %X"  , channel, dest.pos  );
				Log("g_wave[%u] count %u"  , channel, dest.count);
			}
		}
		End:;
	}
	if constexpr (debug)
	{
		LogFunctionEnd();
	}
}

static void Compile
(
	uint8 channel,
	uint8 maxProgSect
)
{
	if constexpr (debug)
	{
		LogFunctionStart();
	}




	dword error = 0;


	






	G_PROG   & progRoot = g_prog[channel];
	G_SMPL   & smplRoot = g_smpl[channel];
	G_VAGI   & vagiRoot = g_vagi[channel];
	G_WAVE   & waveRoot = g_wave[channel];
	byte   * & mapRoot  = g_map [channel];
	G_ITEM   & itemRoot = g_item[channel];

	







	byte * & addr = mapRoot;
	uint64 pos = 0;




	Head:
	{


		// @Check: Add to Core.


		//Align<uint64>(pos, 0x10, addr, 0xFF);
		//







		//auto Align = [&]()
		//{
		//	constexpr uint64 boundary = 0x10;
		//	uint64 remainder = (pos % boundary);
		//	if (remainder)
		//	{
		//		uint64 size = (boundary - remainder);
		//		memset((addr + pos), 0xFF, size);
		//		pos += size;
		//	}
		//};




		HEAD & head = *(HEAD *)(addr + pos);
		pos += sizeof(HEAD);


		// @Check: Add boundary variable.

		Align<uint64>(pos, 0x10, addr, 0xFF);

		Prog:
		{
			head.progOff = (uint32)pos;

			PROG_METADATA & prog = *(PROG_METADATA *)(addr + pos);
			pos += sizeof(PROG_METADATA);
			Align<uint64>(pos, 0x10, addr, 0xFF);

			uint32 * off = (uint32 *)(addr + pos);

			// @Optimize: Adjust datatypes with regards to MAX_PROG_SECT.

			for (uint8 sect = 0; sect < maxProgSect; sect++)
			{

				// if maxProgSect == 0

				//Log("Def not accessing this. %u", sect);
				off[sect] = 0xFFFFFFFF;
				pos += sizeof(uint32);
			}









			for (uint64 sect = 0; sect < progRoot.count; sect++)
			{
				uint8 & id = progRoot.id[sect];
				off[id] = progRoot.off[sect];
				off[id] += 0x10;
				off[id] += (maxProgSect * sizeof(uint32));
			}

			memcpy((addr + pos), progRoot.addr, progRoot.pos);
			pos += progRoot.pos;

			Align<uint64>(pos, 0x10, addr, 0xFF);

			prog.signature[0] = 'P';
			prog.signature[1] = 'r';
			prog.signature[2] = 'o';
			prog.signature[3] = 'g';
			prog.size = (uint32)(pos - head.progOff);
			prog.last = (maxProgSect == 0) ? 0 : (maxProgSect - 1);
		}

		Smpl:
		{
			head.smplOff = (uint32)pos;

			SMPL_METADATA & smpl = *(SMPL_METADATA *)(addr + pos);
			pos += sizeof(SMPL_METADATA);
			Align<uint64>(pos, 0x10, addr, 0xFF);


			



			uint64 size = (smplRoot.count * sizeof(SMPL_ITEM));
			memcpy((addr + pos), smplRoot.addr, size);
			pos += size;
			Align<uint64>(pos, 0x10, addr, 0xFF);

			smpl.signature[0] = 'S';
			smpl.signature[1] = 'm';
			smpl.signature[2] = 'p';
			smpl.signature[3] = 'l';
			smpl.size = (uint32)(pos - head.smplOff);
			smpl.last = (uint32)(smplRoot.count - 1);
		}

		Vagi:
		{
			head.vagiOff = (uint32)pos;

			VAGI_METADATA & vagi = *(VAGI_METADATA *)(addr + pos);
			pos += sizeof(VAGI_METADATA);
			Align<uint64>(pos, 0x10, addr, 0xFF);


			



			// @Optimize: Just go with itemCount.

			uint64 size = (vagiRoot.count * sizeof(VAGI_ITEM));
			memcpy((addr + pos), vagiRoot.addr, size);

			// @Optimize: Change datatypes for count.
			//Log("__UFF__ loop start addr %llX", addr);
			//Log("__UFF__ loop start pos  %llX", pos);

			for (uint64 itemIndex = 0; itemIndex < vagiRoot.count; itemIndex++)
			{
				static uint32 off = 0;
				VAGI_ITEM & item = ((VAGI_ITEM *)(addr + pos))[itemIndex];
				//Log("__UFF__ off   %X", off);
				//Log("");
				
				//Log("item      %llX", item);
				//Log("item size %u", item.size);
				//Log("item rate %u", item.sampleRate);

				item.off = off;
				off += item.size;
			}

			pos += size;
			Align<uint64>(pos, 0x10, addr, 0xFF);

			vagi.signature[0] = 'V';
			vagi.signature[1] = 'a';
			vagi.signature[2] = 'g';
			vagi.signature[3] = 'i';
			vagi.size = (uint32)(pos - head.vagiOff);
			vagi.last = (uint32)(vagiRoot.count - 1);
		}

		head.signature[0] = 'H';
		head.signature[1] = 'e';
		head.signature[2] = 'a';
		head.signature[3] = 'd';
	}

	Wave:
	{
		uint64 pos = posMap[channel];

		for (uint32 index = 0; index < waveRoot.count; index++)
		{
			WAVE_ITEM waveItem = waveRoot[index];

			if constexpr (debug)
			{
				Log("g_wave[%u][%u] addr %llX", channel, index, waveItem.addr);
				Log("g_wave[%u][%u] size %X"  , channel, index, waveItem.size);
			}



			FMOD_SYSTEM * FMOD_system = *(FMOD_SYSTEM **)(appBaseAddr + 0x5DE3D0);

			FMOD_CREATESOUNDEXINFO info = {};
			info.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
			info.length = waveItem.size;


			SOUND_ITEM & soundItem = itemRoot[index];



			


			soundItem.pos = pos;

			// true size : size from metadata + 0x30
			// vagi size : size from metadata + 0x10

			// In this case vagi size is used, so true size - 0x20.

			soundItem.size = (uint64)(waveItem.size - 0x20);

			// true size when registering them

			FMOD_RESULT result = FMOD_System_CreateSound
			(
				FMOD_system,
				waveItem.addr,
				FMOD_CREATECOMPRESSEDSAMPLE | FMOD_OPENMEMORY | FMOD_LOWMEM,
				&info,
				&soundItem.sound
			);
			if (result != FMOD_OK)
			{
				Log("FMOD_System_CreateSound failed. result %X", result);
				return;
			}

			itemRoot.count++;
			pos += soundItem.size;
		}
	}

	if constexpr (debug)
	{
		Log("g_map [%u] %llX", channel, mapRoot);
		Log("g_item[%u] %llX", channel, itemRoot.addr);

	}




	



	if constexpr (debug)
	{
		LogFunctionEnd();
	}
}






static bool InitPosMap()
{
	byte * file = LoadGameFile("SpuMap.bin");
	if (!file)
	{
		return false;
	}
	uint64 pos = 0x5020;
	for (uint8 channel = 0; channel < MAX_CHANNEL; channel++)
	{
		posMap[channel] = pos;
		pos += ((uint32 *)(file + 0x10))[channel];
		if constexpr (debug)
		{
			Log("posMap[%u] %llX", channel, posMap[channel]);
		}
	}
	return true;
}






static void Process()
{
	Compile(CHANNEL_STYLE_WEAPON, MAX_PROG_SECT);
}













bool System_Sound_Init()
{
	LogFunction();


	if (!InitPosMap())
	{
		return false;
	}





	dword error = 0;





	uint8 channelMap[] =
	{
		//CHANNEL_COMMON,
		CHANNEL_STYLE_WEAPON,
	};
	for (uint8 channelIndex = 0; channelIndex < countof(channelMap); channelIndex++)
	{
		uint8 & channel = channelMap[channelIndex];
		struct DPS
		{
			void * addr;
			uint64 size;
		};
		DPS var[] =
		{
			{ &g_prog[channel].addr, (1 * 1024 * 1024                          ) },
			{ &g_prog[channel].off , (MAX_SOUND_PER_CHANNEL * sizeof(uint32)   ) },
			{ &g_smpl[channel].addr, (MAX_SOUND_PER_CHANNEL * sizeof(SMPL_ITEM)) },
			{ &g_vagi[channel].addr, (MAX_SOUND_PER_CHANNEL * sizeof(VAGI_ITEM)) },
			{ &g_wave[channel].addr, (8 * 1024 * 1024                          ) },
			{ &g_wave[channel].off , (MAX_SOUND_PER_CHANNEL * sizeof(uint32)   ) },
			{ &g_wave[channel].size, (MAX_SOUND_PER_CHANNEL * sizeof(uint32)   ) },
			{ &g_map [channel]     , (1 * 1024 * 1024                          ) },
			{ &g_item[channel].addr, (1 * 1024 * 1024                          ) },
		};
		for (uint8 index = 0; index < countof(var); index++)
		{
			void * & addr = *(void **)var[index].addr;
			SetLastError(0);
			// @Todo: Add custom allocator.
			addr = VirtualAllocEx(appProcess, 0, var[index].size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
			error = GetLastError();
			if (!addr)
			{
				Log("VirtualAllocEx failed. %u %u %X", index, channel, error);
				return false;
			}
		}
		if constexpr (debug)
		{
			Log("g_prog[%u] addr %llX", channel, g_prog[channel].addr);
			Log("g_prog[%u] off  %llX", channel, g_prog[channel].off );
			Log("g_smpl[%u] addr %llX", channel, g_smpl[channel].addr);
			Log("g_vagi[%u] addr %llX", channel, g_vagi[channel].addr);
			Log("g_wave[%u] addr %llX", channel, g_wave[channel].addr);
			Log("g_wave[%u] off  %llX", channel, g_wave[channel].off );
			Log("g_wave[%u] size %llX", channel, g_wave[channel].size);
			Log("g_map [%u]      %llX", channel, g_map [channel]     );
			Log("g_item[%u] addr %llX", channel, g_item[channel].addr);
		}
	}





	{

		// @Todo: Move helper to global namespace.

		struct DPS
		{
			const char * archiveName;
			uint8 id;
		};
		DPS var[] =
		{
			{ "snd_wp00b.pac", PROG_SECT_REBELLION         , },
			{ "snd_wp01b.pac", PROG_SECT_CERBERUS          , },
			{ "snd_wp02b.pac", PROG_SECT_AGNI_RUDRA        , },
			{ "snd_wp03b.pac", PROG_SECT_NEVAN             , },
			{ "snd_wp04b.pac", PROG_SECT_BEOWULF           , },
			{ "snd_wp05b.pac", PROG_SECT_EBONY_IVORY       , },
			{ "snd_wp06b.pac", PROG_SECT_SHOTGUN           , },
			{ "snd_wp07b.pac", PROG_SECT_ARTEMIS           , },
			{ "snd_wp08b.pac", PROG_SECT_SPIRAL            , },
			{ "snd_wp09b.pac", PROG_SECT_KALINA_ANN        , },
			{ "snd_wp11b.pac", PROG_SECT_YAMATO            , },
			{ "snd_wp12b.pac", PROG_SECT_BEOWULF_VERGIL    , },
			{ "snd_wp13b.pac", PROG_SECT_FORCE_EDGE        , },
			{ "snd_sty02.pac", PROG_SECT_TRICKSTER         , },
			{ "snd_sty03.pac", PROG_SECT_ROYALGUARD        , },
			{ "snd_sty04.pac", PROG_SECT_QUICKSILVER       , },
			{ "snd_sty05.pac", PROG_SECT_DOPPELGANGER      , },
			{ "snd_sty06.pac", PROG_SECT_BATTLE_OF_BROTHERS, },
			{ "snd_sty07.pac", PROG_SECT_DARK_SLAYER       , },
		};
		char path[128] = {};
		for (uint8 index = 0; index < countof(var); index++)
		{
			snprintf(path, sizeof(path), "data\\dmc3\\GData.afs\\%s", var[index].archiveName);
			byte * archive = LoadGameFile(var[index].archiveName);
			if (!archive)
			{
				return false;
			}
			Decompile(archive, CHANNEL_STYLE_WEAPON, var[index].id);
		}
	}













	


	// @Todo: Def free memory!

	{
		FUNC func = CreateFunction(Process);
		WriteJump((appBaseAddr + 0x32901), func.addr);
	}







	// Fixes

	Write<byte>((appBaseAddr + 0x33995C), 0xEB); // Disable Id Check




	// Write itemCount.

	{
		byte sect0[] =
		{
			0x8B, 0x15, 0x00, 0x00, 0x00, 0x00,                         //mov edx,[dmc3.exe+5DE4F4]
			0x80, 0x79, 0x0C, 0x00,                                     //cmp byte ptr [rcx+0C],CHANNEL_STYLE_WEAPON
			0x75, 0x0C,                                                 //jne short
			0x48, 0xBA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rdx,&g_item[CHANNEL_STYLE_WEAPON].count
			0x8B, 0x12,                                                 //mov edx,[rdx]
		};
		FUNC func = CreateFunction(0, (appBaseAddr + 0x321CD), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteAddress(func.sect0, (appBaseAddr + 0x5DE4F4), 6);
		*(uint8 *)(func.sect0 + 9) = CHANNEL_STYLE_WEAPON;
		*(uint32 **)(func.sect0 + 0xE) = &g_item[CHANNEL_STYLE_WEAPON].count;
		// @Research: Toggle.
		WriteJump((appBaseAddr + 0x321C7), func.addr, 1);
	}


	// Write item.

	{
		byte sect0[] =
		{
			0x48, 0x8D, 0x3D, 0x00, 0x00, 0x00, 0x00,                   //lea rdi,[dmc3.exe+5DE5B0]
			0x80, 0x79, 0x0C, 0x00,                                     //cmp byte ptr [rcx+0C],CHANNEL_STYLE_WEAPON
			0x75, 0x0D,                                                 //jne short
			0x48, 0xBF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rdi,&g_item[CHANNEL_STYLE_WEAPON].addr
			0x48, 0x8B, 0x3F,                                           //mov rdi,[rdi]
		};
		FUNC func = CreateFunction(0, (appBaseAddr + 0x321E7), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteAddress(func.addr, (appBaseAddr + 0x5DE5B0), 7);
		*(uint8 *)(func.addr + 0xA) = CHANNEL_STYLE_WEAPON;
		*(SOUND_ITEM ***)(func.addr + 0xF) = &g_item[CHANNEL_STYLE_WEAPON].addr;
		// @Research: Toggle.
		WriteJump((appBaseAddr + 0x321E0), func.addr, 2);
	}




	// Write map.
	{
		byte sect0[] =
		{
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   //lea rcx,[dmc3.exe+D6E590]
			0x3C, 0x00,                                                 //cmp al,CHANNEL_STYLE_WEAPON
			0x75, 0x0D,                                                 //jne short
			0x48, 0xBA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rdx,&g_map[CHANNEL_STYLE_WEAPON]
			0x48, 0x8B, 0x12,                                           //mov rdx,[rdx]
		};
		FUNC func = CreateFunction(0, (appBaseAddr + 0x339F02), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteAddress(func.sect0, (appBaseAddr + 0xD6E590), 7);
		*(uint8 *)(func.sect0 + 8) = CHANNEL_STYLE_WEAPON;
		*(byte ***)(func.sect0 + 0xD) = &g_map[CHANNEL_STYLE_WEAPON];
		// @Research: Toggle.
		WriteJump((appBaseAddr + 0x339EFB), func.addr, 2);
	}





	return true;
}
