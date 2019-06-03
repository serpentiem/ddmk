#include "Color.h"

ApplyColor_t ApplyColor = 0;

BYTE * AirHike = 0;

void Cosmetics_Color_Init()
{
	LogFunction();
	{
		BYTE sect1[] =
		{
			0x48, 0x83, 0xEC, 0x50,                                     //sub rsp,50
			0x0F, 0x29, 0x74, 0x24, 0x30,                               //movaps [rsp+30],xmm6
			0x48, 0x8B, 0xF1,                                           //mov rsi,rcx
			0x8B, 0xFA,                                                 //mov edi,edx
			0x4C, 0x8D, 0xA6, 0x00, 0x02, 0x00, 0x00,                   //lea r12,[rsi+00000200]
			0xF3, 0x0F, 0x10, 0x35, 0x00, 0x00, 0x00, 0x00,             //movss xmm6,[dmc3.exe+35D56C]
			0xC7, 0x86, 0x24, 0x3A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov [rsi+00003A24],00000000
			0x89, 0xBE, 0x28, 0x3A, 0x00, 0x00,                         //mov [rsi+00003A28],edi
			0xBB, 0x03, 0x00, 0x00, 0x00,                               //mov ebx,00000003
			0x49, 0x8B, 0xCC,                                           //mov rcx,r12
			0x49, 0x8B, 0x04, 0x24,                                     //mov rax,[r12]
			0xFF, 0x50, 0x20,                                           //call qword ptr [rax+20]
			0x3C, 0x01,                                                 //cmp al,01
			0x75, 0x29,                                                 //jne short
			0x49, 0x8B, 0xCC,                                           //mov rcx,r12
			0xE8, 0x00, 0x00, 0x00, 0x00,                               //call dmc3.exe+89DE0
			0x48, 0x8B, 0xC8,                                           //mov rcx,rax
			0x8B, 0x96, 0x28, 0x3A, 0x00, 0x00,                         //mov edx,[rsi+00003A28]
			0x0F, 0x28, 0xD6,                                           //movaps xmm2,xmm6
			0xE8, 0x00, 0x00, 0x00, 0x00,                               //call dmc3.exe+2F6730
			0x49, 0x8B, 0xCC,                                           //mov rcx,r12
			0xE8, 0x00, 0x00, 0x00, 0x00,                               //call dmc3.exe+89DE0
			0x48, 0x8B, 0xC8,                                           //mov rcx,rax
			0xE8, 0x00, 0x00, 0x00, 0x00,                               //call dmc3.exe+2F6DA0
			0x49, 0x81, 0xC4, 0x80, 0x07, 0x00, 0x00,                   //add r12,00000780
			0x83, 0xEB, 0x01,                                           //sub ebx,01
			0x75, 0xBD,                                                 //jne short
			0x48, 0x8B, 0xCE,                                           //mov rcx,rsi
			0x31, 0xD2,                                                 //xor edx,edx
			0x48, 0x8B, 0x06,                                           //mov rax,[rsi]
			0xFF, 0x50, 0x58,                                           //call qword ptr [rax+58]
			0x31, 0xDB,                                                 //xor ebx,ebx
			0x48, 0x8B, 0x8C, 0xDE, 0xA0, 0x64, 0x00, 0x00,             //mov rcx,[rsi+rbx*8+000064A0]
			0x48, 0x85, 0xC9,                                           //test rcx,rcx
			0x74, 0x08,                                                 //je short
			0x31, 0xD2,                                                 //xor edx,edx
			0x48, 0x8B, 0x01,                                           //mov rax,[rcx]
			0xFF, 0x50, 0x58,                                           //call qword ptr [rax+58]
			0x83, 0xC3, 0x01,                                           //add ebx,01
			0x83, 0xFB, 0x04,                                           //cmp ebx,04
			0x72, 0xE3,                                                 //jb short
			0x0F, 0x28, 0x74, 0x24, 0x30,                               //movaps xmm6,[rsp+30]
		};
		FUNC func = CreateFunction(0, 0, true, true, 0, sizeof(sect1));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteAddress((func.sect1 + 0x15), (appBaseAddr + 0x35D56C), 8);
		WriteCall((func.sect1 + 0x43), (appBaseAddr + 0x89DE0));
		WriteCall((func.sect1 + 0x54), (appBaseAddr + 0x2F6730));
		WriteCall((func.sect1 + 0x5C), (appBaseAddr + 0x89DE0));
		WriteCall((func.sect1 + 0x64), (appBaseAddr + 0x2F6DA0));
		ApplyColor = (ApplyColor_t)func.addr;
	}
	{
		BYTE sect0[] =
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
		*(BYTE ***)(func.sect0 + 0x16) = func.cache;
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
		BYTE * addr[][3] =
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
		BYTE * addr[] =
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
		BYTE * addr[] =
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
		BYTE * addr[] =
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
		BYTE * addr[] =
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
		BYTE * addr[] =
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
		BYTE * addr[] =
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
		BYTE * addr[][3] =
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
		BYTE * addr[] =
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
		BYTE * addr[] =
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
		BYTE * addr[] =
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
		BYTE * addr[] =
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
		BYTE * addr[] =
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
		BYTE * addr[] =
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
			BYTE buffer[] =
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
			BYTE buffer[] =
			{
				0x66, 0xC7, 0x80, 0xE0, 0x00, 0x00, 0x00, 0xFF, 0x00, //mov word ptr [rax+000000E0],00FF
				0x40, 0x88, 0xB8, 0xE2, 0x00, 0x00, 0x00,             //mov [rax+000000E2],dil
			};
			vp_memcpy((appBaseAddr + 0x8E330), buffer, sizeof(buffer));
		}
		Cosmetics_Color_ResetRGB();
	}
}
