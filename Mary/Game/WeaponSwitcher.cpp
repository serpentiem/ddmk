#include "WeaponSwitcher.h"






byte * Melee_UpdateWeaponProxy  = 0;
byte * Ranged_UpdateWeaponProxy = 0;
uint8 Game_WeaponSwitcher_Melee_index  = 0;
uint8 Game_WeaponSwitcher_Ranged_index = 0;

typedef void(* Melee_UpdateIcon_t)();
typedef void(* Ranged_UpdateIcon_t)();
typedef void(* PlayCycleAnimation_t)(uint32, uint32);

Melee_UpdateIcon_t   Melee_UpdateIcon   = 0;
Ranged_UpdateIcon_t  Ranged_UpdateIcon  = 0;
PlayCycleAnimation_t PlayCycleAnimation = 0;

static uint8 Melee_GetActiveWeaponSlot(byte * baseAddr)
{
	uint8 motion = *(uint8 *)(baseAddr + 0x39B3);
	uint8 * equipment = (uint8 *)(baseAddr + 0x6498);
	for (uint8 slot = 0; slot < 2; slot++)
	{
		uint8 weapon = equipment[slot];
		if ((motion == (weapon + 3)) || (motion == (weapon + 13)))
		{
			return slot;
		}
	}
	return 0xFF;
}

static void Melee_UpdateWeapon(byte * baseAddr)
{
	uint8 & index = Game_WeaponSwitcher_Melee_index;
	index++;
	if (index >= Config.Game.WeaponSwitcher.Melee.count)
	{
		index = 0;
	}
	uint8 activeSlot = Melee_GetActiveWeaponSlot(baseAddr);
	uint8 & selectedWeapon = *(uint8 *)(baseAddr + 0x6490);
	if (activeSlot == 0)
	{
		selectedWeapon = 1;
	}
	else if (activeSlot == 1)
	{
		selectedWeapon = 0;
	}
	else
	{
		selectedWeapon = !selectedWeapon;
	}
	uint8 * equipment = (uint8 *)(baseAddr + 0x6498);
	uint8 & weapon = Config.Game.WeaponSwitcher.Melee.weapon[index];
	equipment[selectedWeapon] = weapon;
	uint8 actor = System_Actor_GetActorId(baseAddr);
	byte ** metadata = (byte **)(baseAddr + 0x64A0);
	metadata[selectedWeapon] = System_Weapon_weaponMetadata[actor][weapon];
	uint32 * flags = (uint32 *)(baseAddr + 0x64C8);
	if (flags[selectedWeapon])
	{
		flags[selectedWeapon] = 3;
	}
	uint8 & model = *(uint8 *)(baseAddr + 0x64F0);
	model = weapon;
	System_Weapon_Dante_UpdateExpertise(baseAddr);
	//updateModelAttributes[actor] = true;
	Melee_UpdateIcon();
	PlayCycleAnimation(WEAPON_ICON_SIDE_RIGHT, 0);


	auto & active = *(uint8 *)(baseAddr + 0x3E6C);
	auto & queue  = *(uint8 *)(baseAddr + 0x3E70);

	uint8 slot = 0;

	if (active == 1)
	{
		slot = 2;
	}
	if (active == 2)
	{
		slot = 1;
	}

	queue = slot;


	//switch (weapon)
	//{
	//case WEAPON_REBELLION:
	//	ApplyDevilRebellion(slot);
	//	break;
	//case WEAPON_CERBERUS:
	//	ApplyDevilCerberus(slot);
	//	break;
	//case WEAPON_AGNI_RUDRA:
	//	ApplyDevilAgniRudra(slot);
	//	break;
	//case WEAPON_NEVAN:
	//	ApplyDevilNevan(slot);
	//	break;
	//case WEAPON_BEOWULF:
	//	ApplyDevilBeowulf(slot);
	//	break;
	//}












}

static uint8 Ranged_GetActiveWeaponSlot(byte * baseAddr)
{
	uint8 motion = *(uint8 *)(baseAddr + 0x39B3);
	uint8 * equipment = (uint8 *)(baseAddr + 0x649A);
	for (uint8 slot = 0; slot < 2; slot++)
	{
		uint8 weapon = equipment[slot];
		if ((motion == (weapon + 3)) || (motion == (weapon + 13)))
		{
			return slot;
		}
	}
	return 0xFF;
}

static void Ranged_UpdateWeapon(byte * baseAddr)
{
	uint8 & index = Game_WeaponSwitcher_Ranged_index;
	index++;
	if (index >= Config.Game.WeaponSwitcher.Ranged.count)
	{
		index = 0;
	}
	uint8 activeSlot = Ranged_GetActiveWeaponSlot(baseAddr);
	uint8 & selectedWeapon = *(uint8 *)(baseAddr + 0x6494);
	selectedWeapon -= 2;
	if (activeSlot == 0)
	{
		selectedWeapon = 1;
	}
	else if (activeSlot == 1)
	{
		selectedWeapon = 0;
	}
	else
	{
		selectedWeapon = !selectedWeapon;
	}
	uint8 * equipment = (uint8 *)(baseAddr + 0x649A);
	uint8 & weapon = Config.Game.WeaponSwitcher.Ranged.weapon[index];
	equipment[selectedWeapon] = weapon;
	uint8 actor = System_Actor_GetActorId(baseAddr);
	byte ** metadata = (byte **)(baseAddr + 0x64B0);
	metadata[selectedWeapon] = System_Weapon_weaponMetadata[actor][weapon];
	selectedWeapon += 2;
	uint8 & model = *(uint8 *)(baseAddr + 0x64F1);
	model = weapon;
	System_Weapon_Dante_Ranged_UpdateLevels(baseAddr);
	System_Weapon_Dante_UpdateExpertise(baseAddr);

	


	
	Ranged_UpdateIcon();
	PlayCycleAnimation(WEAPON_ICON_SIDE_LEFT, 0);
}

void Game_WeaponSwitcher_Init()
{
	LogFunction();
	{
		byte sect1[] =
		{
			0x4C, 0x8B, 0xC2,                         //mov r8,rdx
			0x48, 0x8B, 0xD1,                         //mov rdx,rcx
			0x48, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, //mov rcx,[dmc3.exe+C90E28]
			0x48, 0x85, 0xC9,                         //test rcx,rcx
			0x74, 0x16,                               //je short
			0x48, 0x8B, 0x49, 0x58,                   //mov rcx,[rcx+58]
			0x48, 0x85, 0xC9,                         //test rcx,rcx
			0x74, 0x0D,                               //je short
			0x48, 0x8B, 0x09,                         //mov rcx,[rcx]
			0x48, 0x85, 0xC9,                         //test rcx,rcx
			0x74, 0x05,                               //je short
			0xE8, 0x00, 0x00, 0x00, 0x00,             //call dmc3.exe+280120
		};
		FUNC func = CreateFunction(0, 0, true, true, 0, sizeof(sect1));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteAddress((func.sect1 + 6), (appBaseAddr + 0xC90E28), 7);
		WriteCall((func.sect1 + 0x23), (appBaseAddr + 0x280120));
		PlayCycleAnimation = (PlayCycleAnimation_t)func.addr;
	}
	{
		byte sect1[] =
		{
			0x4C, 0x8B, 0x25, 0x00, 0x00, 0x00, 0x00,             //mov r12,[dmc3.exe+CF2680]
			0x4D, 0x8B, 0x64, 0x24, 0x30,                         //mov r12,[r12+30]
			0x49, 0x8D, 0x8C, 0x24, 0x80, 0x17, 0x00, 0x00,       //lea rcx,[r12+00001780]
			0xE8, 0x00, 0x00, 0x00, 0x00,                         //call dmc3.exe+897B0
			0x49, 0x8D, 0x8C, 0x24, 0x80, 0x17, 0x00, 0x00,       //lea rcx,[r12+00001780]
			0xE8, 0x00, 0x00, 0x00, 0x00,                         //call dmc3.exe+89450
			0x48, 0x31, 0xC0,                                     //xor rax,rax
			0xB9, 0x80, 0x07, 0x00, 0x00,                         //mov ecx,00000780
			0x49, 0x8D, 0xBC, 0x24, 0x80, 0x17, 0x00, 0x00,       //lea rdi,[r12+00001780]
			0xF3, 0xAA,                                           //repe stosb
			0x49, 0x8D, 0x8C, 0x24, 0x80, 0x17, 0x00, 0x00,       //lea rcx,[r12+00001780]
			0xE8, 0x00, 0x00, 0x00, 0x00,                         //call dmc3.exe+89270
			0x49, 0x8D, 0x8C, 0x24, 0x80, 0x17, 0x00, 0x00,       //lea rcx,[r12+00001780]
			0x4C, 0x8B, 0x2D, 0x00, 0x00, 0x00, 0x00,             //mov r13,[dmc3.exe+C90E28]
			0x4D, 0x8B, 0x6D, 0x18,                               //mov r13,[r13+18]
			0x49, 0x0F, 0xB6, 0x85, 0x90, 0x64, 0x00, 0x00,       //movzx rax,byte ptr [r13+00006490]
			0x4A, 0x0F, 0xB6, 0x84, 0x28, 0x98, 0x64, 0x00, 0x00, //movzx rax,byte ptr [rax+r13+00006498]
			0x4D, 0x8B, 0xAC, 0x24, 0xC8, 0x00, 0x00, 0x00,       //mov r13,[r12+000000C8]
			0x4D, 0x8B, 0x6D, 0x20,                               //mov r13,[r13+20]
			0x41, 0x8B, 0x94, 0xC5, 0xB4, 0x00, 0x00, 0x00,       //mov edx,[r13+rax*8+000000B4]
			0x4C, 0x01, 0xEA,                                     //add rdx,r13
			0x45, 0x8B, 0x84, 0xC5, 0xB0, 0x00, 0x00, 0x00,       //mov r8d,[r13+rax*8+000000B0]
			0x4D, 0x01, 0xE8,                                     //add r8,r13
			0xE8, 0x00, 0x00, 0x00, 0x00,                         //call dmc3.exe+89960
			0x49, 0x8D, 0x8C, 0x24, 0x80, 0x17, 0x00, 0x00,       //lea rcx,[r12+00001780]
			0xBA, 0x01, 0x00, 0x00, 0x00,                         //mov edx,00000001
			0xE8, 0x00, 0x00, 0x00, 0x00,                         //call dmc3.exe+89E30
		};
		FUNC func = CreateFunction(0, 0, true, true, 0 ,sizeof(sect1));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteAddress(func.sect1, (appBaseAddr + 0xCF2680), 7);
		WriteCall((func.sect1 + 0x14), (appBaseAddr + 0x897B0));
		WriteCall((func.sect1 + 0x21), (appBaseAddr + 0x89450));
		WriteCall((func.sect1 + 0x40), (appBaseAddr + 0x89270));
		WriteAddress((func.sect1 + 0x4D), (appBaseAddr + 0xC90E28), 7);
		WriteCall((func.sect1 + 0x8B), (appBaseAddr + 0x89960));
		WriteCall((func.sect1 + 0x9D), (appBaseAddr + 0x89E30));
		Melee_UpdateIcon = (Melee_UpdateIcon_t)func.addr;
	}
	{
		byte sect1[] =
		{
			0x4C, 0x8B, 0x25, 0x00, 0x00, 0x00, 0x00,             //mov r12,[dmc3.exe+CF2680]
			0x4D, 0x8B, 0x64, 0x24, 0x30,                         //mov r12,[r12+30]
			0x49, 0x8D, 0x8C, 0x24, 0x80, 0x08, 0x00, 0x00,       //lea rcx,[r12+00000880]
			0xE8, 0x00, 0x00, 0x00, 0x00,                         //call dmc3.exe+897B0
			0x49, 0x8D, 0x8C, 0x24, 0x80, 0x08, 0x00, 0x00,       //lea rcx,[r12+00000880]
			0xE8, 0x00, 0x00, 0x00, 0x00,                         //call dmc3.exe+89450
			0x48, 0x31, 0xC0,                                     //xor rax,rax
			0xB9, 0x80, 0x07, 0x00, 0x00,                         //mov ecx,00000780
			0x49, 0x8D, 0xBC, 0x24, 0x80, 0x08, 0x00, 0x00,       //lea rdi,[r12+00000880]
			0xF3, 0xAA,                                           //repe stosb
			0x49, 0x8D, 0x8C, 0x24, 0x80, 0x08, 0x00, 0x00,       //lea rcx,[r12+00000880]
			0xE8, 0x00, 0x00, 0x00, 0x00,                         //call dmc3.exe+89270
			0x49, 0x8D, 0x8C, 0x24, 0x80, 0x08, 0x00, 0x00,       //lea rcx,[r12+00000880]
			0x4C, 0x8B, 0x2D, 0x00, 0x00, 0x00, 0x00,             //mov r13,[dmc3.exe+C90E28]
			0x4D, 0x8B, 0x6D, 0x18,                               //mov r13,[r13+18]
			0x49, 0x0F, 0xB6, 0x85, 0x94, 0x64, 0x00, 0x00,       //movzx rax,byte ptr [r13+00006494]
			0x48, 0x83, 0xE8, 0x02,                               //sub rax,02
			0x4A, 0x0F, 0xB6, 0x84, 0x28, 0x9A, 0x64, 0x00, 0x00, //movzx rax,byte ptr [rax+r13+0000649A]
			0x48, 0x83, 0xE8, 0x05,                               //sub rax,05
			0x4D, 0x8B, 0xAC, 0x24, 0xC8, 0x00, 0x00, 0x00,       //mov r13,[r12+000000C8]
			0x4D, 0x8B, 0x6D, 0x20,                               //mov r13,[r13+20]
			0x41, 0x8B, 0x94, 0xC5, 0x84, 0x00, 0x00, 0x00,       //mov edx,[r13+rax*8+00000084]
			0x4C, 0x01, 0xEA,                                     //add rdx,r13
			0x45, 0x8B, 0x84, 0xC5, 0x80, 0x00, 0x00, 0x00,       //mov r8d,[r13+rax*8+00000080]
			0x4D, 0x01, 0xE8,                                     //add r8,r13
			0xE8, 0x00, 0x00, 0x00, 0x00,                         //call dmc3.exe+89960
			0x49, 0x8D, 0x8C, 0x24, 0x80, 0x08, 0x00, 0x00,       //lea rcx,[r12+00000880]
			0xBA, 0x01, 0x00, 0x00, 0x00,                         //mov edx,00000001
			0xE8, 0x00, 0x00, 0x00, 0x00,                         //call dmc3.exe+89E30
		};
		FUNC func = CreateFunction(0, 0, true, true, 0, sizeof(sect1));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteAddress(func.sect1, (appBaseAddr + 0xCF2680), 7);
		WriteCall((func.sect1 + 0x14), (appBaseAddr + 0x897B0));
		WriteCall((func.sect1 + 0x21), (appBaseAddr + 0x89450));
		WriteCall((func.sect1 + 0x40), (appBaseAddr + 0x89270));
		WriteAddress((func.sect1 + 0x4D), (appBaseAddr + 0xC90E28), 7);
		WriteCall((func.sect1 + 0x93), (appBaseAddr + 0x89960));
		WriteCall((func.sect1 + 0xA5), (appBaseAddr + 0x89E30));
		Ranged_UpdateIcon = (Ranged_UpdateIcon_t)func.addr;
	}
	{
		byte sect0[] =
		{
			0xBA, 0x04, 0x00, 0x00, 0x00, //mov edx,00000004
		};
		byte sect1[] =
		{
			0x48, 0x8B, 0xCF, //mov rcx,rdi
		};
		FUNC func = CreateFunction(Melee_UpdateWeapon, (appBaseAddr + 0x1EA9E4), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		Melee_UpdateWeaponProxy = func.addr;
	}
	{
		byte sect0[] =
		{
			0xBA, 0x07, 0x00, 0x00, 0x00, //mov edx,00000007
		};
		byte sect1[] =
		{
			0x48, 0x8B, 0xCF, //mov rcx,rdi
		};
		FUNC func = CreateFunction(Ranged_UpdateWeapon, (appBaseAddr + 0x1EAAD1), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		Ranged_UpdateWeaponProxy = func.addr;
	}
}

void Game_WeaponSwitcher_Toggle(bool enable)
{
	Log("%s %u", FUNC_NAME, enable);
	if (enable)
	{
		WriteJump((appBaseAddr + 0x1EA980), Melee_UpdateWeaponProxy, 2);
		WriteJump((appBaseAddr + 0x1EAA6D), Ranged_UpdateWeaponProxy, 2);
		//System_Actor_UpdateDevilModel(Config.Game.WeaponSwitcher.devil);
	}
	else
	{
		{
			byte buffer[] =
			{
				0x48, 0x63, 0x9F, 0x90, 0x64, 0x00, 0x00, //movsxd rbx,dword ptr [rdi+00006490]
			};
			vp_memcpy((appBaseAddr + 0x1EA980), buffer, sizeof(buffer));
		}
		{
			byte buffer[] =
			{
				0x48, 0x63, 0x9F, 0x94, 0x64, 0x00, 0x00, //movsxd rbx,dword ptr [rdi+00006494]
			};
			vp_memcpy((appBaseAddr + 0x1EAA6D), buffer, sizeof(buffer));
		}
		//System_Actor_ResetDevilModel();
	}
}
