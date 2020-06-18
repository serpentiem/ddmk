#include "Color.h"

Cosmetics_Color_ApplyColor_t Cosmetics_Color_ApplyColor = 0;

byte8 ** AirHikeCache = 0;

struct ColorHelper
{
	uint32 off[3];
	uint32 & operator[](uint8 index)
	{
		return off[index];
	}
};

//PrivateStart;

ColorHelper colorHelperAuraDante[] =
{
	{ 0x8CD1F, 0x8CD20, 0x8CD24 },
	{ 0x8CD29, 0x8CD2A, 0x8CD2E },
	{ 0x8CD33, 0x8CD34, 0x8CD38 },
	{ 0x8CD3D, 0x8CD3E, 0x8CD42 },
	{ 0x8CD47, 0x8CD48, 0x8CD4C },
};

ColorHelper colorHelperAuraVergil[] =
{
	{ 0x8CD51, 0x8CD52, 0x8CD56 }, // Open
	{ 0x90C5C, 0x90C5D, 0x90C62 }, // Close
};

ColorHelper colorHelperAuraNeroAngelo[] =
{
	{ 0x8E438, 0x8E439, 0x8E43D }, // Open
	{ 0x90C4E, 0x90C4F, 0x90C54 }, // Close
};

ColorHelper colorHelperStyleTrickster[] =
{
	{ 0x8E336, 0x8E337, 0x8E338 },
};

ColorHelper colorHelperStyleRoyalguard[] =
{
	{ 0x8E843, 0x8E844, 0x8E84B }, // Open
	{ 0x9114B, 0x9114C, 0x91153 }, // Close
};

ColorHelper colorHelperStyleDoppelganger[] =
{
	{ 0x1FCD79, 0x1FCD7A, 0x1FCD7B },
};

ColorHelper * colorHelper[] =
{
	colorHelperAuraDante,
	colorHelperAuraVergil,
	colorHelperAuraNeroAngelo,
	colorHelperStyleTrickster,
	colorHelperStyleRoyalguard,
	colorHelperStyleDoppelganger,
};

uint8 colorHelperCount[] =
{
	countof(colorHelperAuraDante),
	countof(colorHelperAuraVergil),
	countof(colorHelperAuraNeroAngelo),
	countof(colorHelperStyleTrickster),
	countof(colorHelperStyleRoyalguard),
	countof(colorHelperStyleDoppelganger),
};

//PrivateEnd;

void Cosmetics_Color_AdjustConfig(CONFIG & config)
{
	LogFunction();

	constexpr uint8 count = (sizeof(Config.Cosmetics.Color) / 4);

	for (uint8 index = 0; index < count; index++)
	{
		((float32 *)&config.Cosmetics.Color)[index] /= 255;
	}
}

void Cosmetics_Color_UpdateColors(CONFIG & config)
{
	LogFunction();
	float32(*addr[])[4] =
	{
		config.Cosmetics.Color.Aura.dante,
		config.Cosmetics.Color.Aura.vergil,
		config.Cosmetics.Color.Aura.neroAngelo,
		config.Cosmetics.Color.Style.trickster,
		config.Cosmetics.Color.Style.royalguard,
		config.Cosmetics.Color.Style.doppelganger,
	};
	for (uint8 helperIndex = 0; helperIndex < countof(colorHelper); helperIndex++)
	{
		for (uint8 itemIndex = 0; itemIndex < colorHelperCount[helperIndex]; itemIndex++)
		{
			for (uint8 colorIndex = 0; colorIndex < 3; colorIndex++)
			{
				auto & off = colorHelper[helperIndex][itemIndex][colorIndex];
				auto color = (uint8)(addr[helperIndex][itemIndex][colorIndex] * 255);
				Write<uint8>((appBaseAddr + off), color);
			}
		}
	}
	// Doppelganger alpha.
	{
		auto color = (uint8)(config.Cosmetics.Color.Style.doppelganger[0][3] * 255);
		Write<uint8>((appBaseAddr + 0x1FCD7C), color);
	}
	for (uint8 itemIndex = 0; itemIndex < 5; itemIndex++)
	{
		for (uint8 colorIndex = 0; colorIndex < 3; colorIndex++)
		{
			auto color = (uint8)(config.Cosmetics.Color.AirHike.dante[itemIndex][colorIndex] * 255);
			Write<uint8>((AirHikeCache[itemIndex] + 1 + colorIndex), color);
		}
	}
}

void Cosmetics_Color_Init()
{
	LogFunction();
	// @Todo: Create permanent color wrapper.
	{
		FUNC func = CreateFunction((appBaseAddr + 0x1FCB10));
		Cosmetics_Color_ApplyColor = (Cosmetics_Color_ApplyColor_t)func.addr;
	}
	{
		byte8 sect0[] =
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
		*(byte8 ***)(func.sect0 + 0x16) = func.cache;
		func.cache[0] = (func.sect0 + 0x21);
		func.cache[1] = (func.sect0 + 0x29);
		func.cache[2] = (func.sect0 + 0x31);
		func.cache[3] = (func.sect0 + 0x39);
		func.cache[4] = (func.sect0 + 0x41);
		AirHikeCache = func.cache;
		WriteCall((appBaseAddr + 0x1F66DD), func.addr);
	}
	{
		auto addr = (appBaseAddr + 0x8E330); // Sky Star
		vp_memset(addr, 0x90, 16);
		byte8 buffer[] =
		{
			0xC7, 0x80, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov [rax+000000E0],color
		};
		vp_memcpy(addr, buffer, sizeof(buffer));
	}
}
