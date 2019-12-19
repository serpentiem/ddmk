#include "Color.h"

byte * AirHike = 0;

void Cosmetics_Color_Init()
{
	LogFunction();
	{
		byte sect0[] =
		{
			0x48, 0x31, 0xC0,                                           //xor rax,rax
			0x8A, 0x83, 0x90, 0x64, 0x00, 0x00,                         //mov al,[rbx+00006490]
			0x8A, 0x84, 0x18, 0x98, 0x64, 0x00, 0x00,                   //mov al,[rax+rbx+00006498]
			0x3C, 0x04,                                                 //cmp al,04
			0x77, 0x0D,                                                 //ja short
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rcx,func.cache
			0xFF, 0x24, 0xC1,                                           //jmp qword ptr [rcx+rax*8]
			0xB8, 0x00, 0x00, 0x00, 0x00,                               //mov eax
			0x89, 0x02,                                                 //mov [rdx],eax
			0xC3,                                                       //ret
			0xB8, 0x00, 0x00, 0x00, 0x00,                               //mov eax
			0x89, 0x02,                                                 //mov [rdx],eax
			0xC3,                                                       //ret
			0xB8, 0x00, 0x00, 0x00, 0x00,                               //mov eax
			0x89, 0x02,                                                 //mov [rdx],eax
			0xC3,                                                       //ret
			0xB8, 0x00, 0x00, 0x00, 0x00,                               //mov eax
			0x89, 0x02,                                                 //mov [rdx],eax
			0xC3,                                                       //ret
			0xB8, 0x00, 0x00, 0x00, 0x00,                               //mov eax
			0x89, 0x02,                                                 //mov [rdx],eax
			0xC3,                                                       //ret
		};
		FUNC func = CreateFunction(0, 0, false, true, sizeof(sect0), 0, 0, 40);
		memcpy(func.sect0, sect0, sizeof(sect0));
		*(byte ***)(func.sect0 + 0x16) = func.cache;
		func.cache[0] = (func.addr + 0x21);
		func.cache[1] = (func.addr + 0x29);
		func.cache[2] = (func.addr + 0x31);
		func.cache[3] = (func.addr + 0x39);
		func.cache[4] = (func.addr + 0x41);
		AirHike = func.addr;
	}
}

void Cosmetics_Color_AdjustConfig()
{
	LogFunction();
	for (uint8 i = 0; i < sizeof(Config.Cosmetics.Color) / 4; i++)
	{
		((float32 *)&Config.Cosmetics.Color)[i] /= 255;
		((float32 *)&DefaultConfig.Cosmetics.Color)[i] /= 255;
	}
}

void Cosmetics_Color_UpdateRGB()
{
	LogFunction();
	// Aura
	// Dante
	{
		byte * addr[][3] =
		{
			{
				(appBaseAddr + 0x8CD1F),
				(appBaseAddr + 0x8CD20),
				(appBaseAddr + 0x8CD24),
			},
			{
				(appBaseAddr + 0x8CD29),
				(appBaseAddr + 0x8CD2A),
				(appBaseAddr + 0x8CD2E),
			},
			{
				(appBaseAddr + 0x8CD33),
				(appBaseAddr + 0x8CD34),
				(appBaseAddr + 0x8CD38),
			},
			{
				(appBaseAddr + 0x8CD3D),
				(appBaseAddr + 0x8CD3E),
				(appBaseAddr + 0x8CD42),
			},
			{
				(appBaseAddr + 0x8CD47),
				(appBaseAddr + 0x8CD48),
				(appBaseAddr + 0x8CD4C),
			},
		};
		for (uint8 devil = 0; devil < countof(addr); devil++)
		{
			for (uint8 i = 0; i < 3; i++)
			{
				Write<uint8>(addr[devil][i], (uint8)(Config.Cosmetics.Color.Dante.aura[devil][i] * 255));
			}
		}
	}
	// Vergil
	// Open
	{
		byte * addr[] =
		{
			(appBaseAddr + 0x8CD51),
			(appBaseAddr + 0x8CD52),
			(appBaseAddr + 0x8CD56),
		};
		for (uint8 i = 0; i < countof(addr); i++)
		{
			Write<uint8>(addr[i], (uint8)(Config.Cosmetics.Color.Vergil.aura[0][i] * 255));
		}
	}
	// Vergil
	// Close
	{
		byte * addr[] =
		{
			(appBaseAddr + 0x90C5C),
			(appBaseAddr + 0x90C5D),
			(appBaseAddr + 0x90C62),
		};
		for (uint8 i = 0; i < countof(addr); i++)
		{
			Write<uint8>(addr[i], (uint8)(Config.Cosmetics.Color.Vergil.aura[0][i] * 255));
		}
	}
	// Nero Angelo
	// Open
	{
		byte * addr[] =
		{
			(appBaseAddr + 0x8E438),
			(appBaseAddr + 0x8E439),
			(appBaseAddr + 0x8E43D),
		};
		for (uint8 i = 0; i < countof(addr); i++)
		{
			Write<uint8>(addr[i], (uint8)(Config.Cosmetics.Color.NeroAngelo.aura[0][i] * 255));
		}
	}
	// Close
	{
		byte * addr[] =
		{
			(appBaseAddr + 0x90C4E),
			(appBaseAddr + 0x90C4F),
			(appBaseAddr + 0x90C54),
		};
		for (uint8 i = 0; i < countof(addr); i++)
		{
			Write<uint8>(addr[i], (uint8)(Config.Cosmetics.Color.NeroAngelo.aura[0][i] * 255));
		}
	}
	// Air Hike
	{
		uint32 off[] =
		{
			0x22,
			0x2A,
			0x32,
			0x3A,
			0x42,
		};
		for (uint8 devil = 0; devil < countof(off); devil++)
		{
			for (uint8 i = 0; i < 3; i++)
			{
				Write<uint8>((AirHike + off[devil] + i), (uint8)(Config.Cosmetics.Color.Dante.airHike[devil][i] * 255));
			}
		}
	}
	// Sky Star
	{
		for (uint8 i = 0; i < 3; i++)
		{
			Write<uint8>((appBaseAddr + 0x8E336 + i), (uint8)(Config.Cosmetics.Color.Dante.trickster[0][i] * 255));
		}
	}
	// Ultimate
	// Open
	{
		byte * addr[] =
		{
			(appBaseAddr + 0x8E843),
			(appBaseAddr + 0x8E844),
			(appBaseAddr + 0x8E84B),
		};
		for (uint8 i = 0; i < countof(addr); i++)
		{
			Write<uint8>(addr[i], (uint8)(Config.Cosmetics.Color.Dante.royalguard[0][i] * 255));
		}
	}
	// Close
	{
		byte * addr[] =
		{
			(appBaseAddr + 0x9114B),
			(appBaseAddr + 0x9114C),
			(appBaseAddr + 0x91153),
		};
		for (uint8 i = 0; i < countof(addr); i++)
		{
			Write<uint8>(addr[i], (uint8)(Config.Cosmetics.Color.Dante.royalguard[0][i] * 255));
		}
	}
}

void Cosmetics_Color_ResetRGB()
{
	LogFunction();
	// Aura
	// Dante
	{
		byte * addr[][3] =
		{
			{
				(appBaseAddr + 0x8CD1F),
				(appBaseAddr + 0x8CD20),
				(appBaseAddr + 0x8CD24),
			},
			{
				(appBaseAddr + 0x8CD29),
				(appBaseAddr + 0x8CD2A),
				(appBaseAddr + 0x8CD2E),
			},
			{
				(appBaseAddr + 0x8CD33),
				(appBaseAddr + 0x8CD34),
				(appBaseAddr + 0x8CD38),
			},
			{
				(appBaseAddr + 0x8CD3D),
				(appBaseAddr + 0x8CD3E),
				(appBaseAddr + 0x8CD42),
			},
			{
				(appBaseAddr + 0x8CD47),
				(appBaseAddr + 0x8CD48),
				(appBaseAddr + 0x8CD4C),
			},
		};
		for (uint8 devil = 0; devil < countof(addr); devil++)
		{
			for (uint8 i = 0; i < 3; i++)
			{
				Write<uint8>(addr[devil][i], (uint8)(DefaultConfig.Cosmetics.Color.Dante.aura[devil][i] * 255));
			}
		}
	}
	// Vergil
	// Open
	{
		byte * addr[] =
		{
			(appBaseAddr + 0x8CD51),
			(appBaseAddr + 0x8CD52),
			(appBaseAddr + 0x8CD56),
		};
		for (uint8 i = 0; i < countof(addr); i++)
		{
			Write<uint8>(addr[i], (uint8)(DefaultConfig.Cosmetics.Color.Vergil.aura[0][i] * 255));
		}
	}
	// Vergil
	// Close
	{
		byte * addr[] =
		{
			(appBaseAddr + 0x90C5C),
			(appBaseAddr + 0x90C5D),
			(appBaseAddr + 0x90C62),
		};
		for (uint8 i = 0; i < countof(addr); i++)
		{
			Write<uint8>(addr[i], (uint8)(DefaultConfig.Cosmetics.Color.Vergil.aura[0][i] * 255));
		}
	}
	// Nero Angelo
	// Open
	{
		byte * addr[] =
		{
			(appBaseAddr + 0x8E438),
			(appBaseAddr + 0x8E439),
			(appBaseAddr + 0x8E43D),
		};
		for (uint8 i = 0; i < countof(addr); i++)
		{
			Write<uint8>(addr[i], (uint8)(DefaultConfig.Cosmetics.Color.NeroAngelo.aura[0][i] * 255));
		}
	}
	// Close
	{
		byte * addr[] =
		{
			(appBaseAddr + 0x90C4E),
			(appBaseAddr + 0x90C4F),
			(appBaseAddr + 0x90C54),
		};
		for (uint8 i = 0; i < countof(addr); i++)
		{
			Write<uint8>(addr[i], (uint8)(DefaultConfig.Cosmetics.Color.NeroAngelo.aura[0][i] * 255));
		}
	}
	// Ultimate
	// Open
	{
		byte * addr[] =
		{
			(appBaseAddr + 0x8E843),
			(appBaseAddr + 0x8E844),
			(appBaseAddr + 0x8E84B),
		};
		for (uint8 i = 0; i < countof(addr); i++)
		{
			Write<uint8>(addr[i], (uint8)(DefaultConfig.Cosmetics.Color.Dante.royalguard[0][i] * 255));
		}
	}
	// Close
	{
		byte * addr[] =
		{
			(appBaseAddr + 0x9114B),
			(appBaseAddr + 0x9114C),
			(appBaseAddr + 0x91153),
		};
		for (uint8 i = 0; i < countof(addr); i++)
		{
			Write<uint8>(addr[i], (uint8)(DefaultConfig.Cosmetics.Color.Dante.royalguard[0][i] * 255));
		}
	}
}

void Cosmetics_Color_Toggle(bool enable)
{
	Log("%s %u", FUNC_NAME, enable);
	if (enable)
	{
		WriteCall((appBaseAddr + 0x1F66DD), AirHike);
		{
			vp_memset((appBaseAddr + 0x8E330), 0x90, 16);
			byte buffer[] =
			{
				0xC7, 0x80, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov [rax+000000E0]
			};
			vp_memcpy((appBaseAddr + 0x8E330), buffer, sizeof(buffer));
		}
		Cosmetics_Color_UpdateRGB();
	}
	else
	{
		WriteCall((appBaseAddr + 0x1F66DD), (appBaseAddr + 0x8CD00));
		{
			byte buffer[] =
			{
				0x66, 0xC7, 0x80, 0xE0, 0x00, 0x00, 0x00, 0xFF, 0x00, //mov word ptr [rax+000000E0],00FF
				0x40, 0x88, 0xB8, 0xE2, 0x00, 0x00, 0x00,             //mov [rax+000000E2],dil
			};
			vp_memcpy((appBaseAddr + 0x8E330), buffer, sizeof(buffer));
		}
		Cosmetics_Color_ResetRGB();
	}
}
