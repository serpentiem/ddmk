const CHANNEL_SYSTEM       = 0;
const CHANNEL_COMMON       = 1;
const CHANNEL_STYLE_WEAPON = 2;
const CHANNEL_WEAPON1      = 3;
const CHANNEL_WEAPON2      = 4;
const CHANNEL_WEAPON3      = 5;
const CHANNEL_WEAPON4      = 6;
const CHANNEL_ENEMY        = 7;
const CHANNEL_ROOM         = 8;
const CHANNEL_MUSIC        = 9;
const CHANNEL_DEMO         = 10;
const MAX_CHANNEL          = 11;
const CHANNEL_IGNORE       = 12;
const CHANNEL_GLOBAL       = 13;

let channelNames =
[
	"CHANNEL_SYSTEM",
	"CHANNEL_COMMON",
	"CHANNEL_STYLE_WEAPON",
	"CHANNEL_WEAPON1",
	"CHANNEL_WEAPON2",
	"CHANNEL_WEAPON3",
	"CHANNEL_WEAPON4",
	"CHANNEL_ENEMY",
	"CHANNEL_ROOM",
	"CHANNEL_MUSIC",
	"CHANNEL_DEMO",
	"MAX_CHANNEL",
];

function GetChannelName(channelIndex)
{
	if (channelIndex >= MAX_CHANNEL)
	{
		return "";
	}

	return channelNames[channelIndex];
}



const HELPER_COMMON_DANTE_DEFAULT            = 0;
const HELPER_COMMON_DANTE_NO_COAT            = 1;
const HELPER_COMMON_VERGIL_DEFAULT           = 2;
const HELPER_COMMON_VERGIL_NERO_ANGELO       = 3;
const HELPER_STYLE_WEAPON_DANTE              = 4;
const HELPER_STYLE_WEAPON_VERGIL_DEFAULT     = 5;
const HELPER_STYLE_WEAPON_VERGIL_NERO_ANGELO = 6;
const HELPER_ENEMY_LESSER_ENEMIES                  = 7;
const HELPER_ENEMY_LADY                            = 8;
const HELPER_ENEMY_VERGIL                          = 9;
const HELPER_COUNT                           = 10;

let helperNames =
[
	"HELPER_COMMON_DANTE_DEFAULT",
	"HELPER_COMMON_DANTE_NO_COAT",
	"HELPER_COMMON_VERGIL_DEFAULT",
	"HELPER_COMMON_VERGIL_NERO_ANGELO",
	"HELPER_STYLE_WEAPON_DANTE",
	"HELPER_STYLE_WEAPON_VERGIL_DEFAULT",
	"HELPER_STYLE_WEAPON_VERGIL_NERO_ANGELO",
	"HELPER_ENEMY_LESSER_ENEMIES",
	"HELPER_ENEMY_LADY",
	"HELPER_ENEMY_VERGIL",
	"HELPER_COUNT",
];

function GetHelperName(helperIndex)
{
	if (helperIndex >= HELPER_COUNT)
	{
		return "";
	}

	return helperNames[helperIndex];
}



let fs = require("fs");
let vm = require("vm");

vm.runInThisContext(fs.readFileSync("dmc3_core.js", "utf8"));

ClearAll();

let c_debug = "";

c_debug += "local appBaseAddr = getAddress(\"dmc3.exe\")" + NEW_LINE;

let items =
[
	[ "dmc3.exe+264B6 - 48 8D 0D D377D400 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+264C8 - 48 8D 0D C177D400 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+4F295 - 48 8D 0D F4E9D100 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Update
	[ "dmc3.exe+4F2BD - 48 8D 0D CCE9D100 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Update
	[ "dmc3.exe+4F4EC - 48 8D 0D 9DE7D100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+4F4FB - 48 8D 0D 8EE7D100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+4F50B - 48 8D 0D 7EE7D100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+4F51A - 48 8D 0D 6FE7D100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+4F53F - 48 8D 0D 4AE7D100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+4F55D - 48 8D 0D 2CE7D100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+4F587 - 48 8D 0D 02E7D100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+4F595 - 48 8D 0D F4E6D100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+4F681 - 48 8D 0D 08E6D100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+4F6BD - 48 8D 0D CCE5D100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+4F6CC - 48 8D 0D BDE5D100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+4F6EB - 48 8D 0D 9EE5D100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+4F712 - 48 8D 0D 77E5D100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+4FE84 - 48 8D 0D 05DED100 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Options Volume Navigate Left
	[ "dmc3.exe+4FF34 - 48 8D 0D 55DDD100 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Menu Close Navigate
	[ "dmc3.exe+4FF88 - 48 8D 0D 01DDD100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+59DE0 - 48 8D 0D A93ED100 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_GLOBAL ], // Default Taunt
	[ "dmc3.exe+59E2F - 48 8D 0D 5A3ED100 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_GLOBAL ], // Default Melee Weapons Some Ranged Weapons
	[ "dmc3.exe+59E75 - 48 8D 0D 143ED100 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_GLOBAL ], // Default Enemy
	[ "dmc3.exe+59EBD - 48 8D 0D CC3DD100 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_GLOBAL ], // Default Step
	[ "dmc3.exe+59F69 - 48 8D 0D 203DD100 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_GLOBAL ], // Default Yamato Nero Angelo Helm Breaker
	[ "dmc3.exe+5A051 - 48 8D 0D 383CD100 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_GLOBAL ], // Default
	[ "dmc3.exe+5A087 - 48 8D 0D 023CD100 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_GLOBAL ], // Default Some Melee Weapons
	[ "dmc3.exe+5A0CA - 48 8D 0D BF3BD100 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_GLOBAL ], // Default
	[ "dmc3.exe+634A9 - 48 8D 0D E0A7D000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+635B2 - 48 8D 0D D7A6D000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+65D30 - 48 8D 0D 597FD000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Pride Boss Damage
	[ "dmc3.exe+65F35 - 48 8D 0D 547DD000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Pride Hit Floor
	[ "dmc3.exe+6608B - 48 8D 0D FE7BD000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Yamato Rapid Slash
	[ "dmc3.exe+66206 - 48 8D 0D 837AD000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Ebony & Ivory Wild Stomp
	[ "dmc3.exe+6693E - 48 8D 0D 4B73D000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Ebony & Ivory Wild Stomp
	[ "dmc3.exe+66C3A - 48 8D 0D 4F70D000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Pride Hit Floor
	[ "dmc3.exe+66ED7 - 48 8D 0D B26DD000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Agni & Rudra Sword Dance
	[ "dmc3.exe+66FA0 - 48 8D 0D E96CD000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 3
	[ "dmc3.exe+671A3 - 48 8D 0D E66AD000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 3
	[ "dmc3.exe+67283 - 48 8D 0D 066AD000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 3
	[ "dmc3.exe+67792 - 48 8D 0D F764D000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 1
	[ "dmc3.exe+67810 - 48 8D 0D 7964D000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Pride Boss Damage
	[ "dmc3.exe+68412 - 48 8D 0D 7758D000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Pride
	[ "dmc3.exe+6890A - 48 8D 0D 7F53D000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+68E4C - 48 8D 0D 3D4ED000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Helm Breaker
	[ "dmc3.exe+6927F - 48 8D 0D 0A4AD000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Pride Death
	[ "dmc3.exe+6930D - 48 8D 0D 7C49D000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Wrath Explosion
	[ "dmc3.exe+693D8 - 48 8D 0D B148D000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Pride
	[ "dmc3.exe+694AA - 48 8D 0D DF47D000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Either Enemy Damage or Rebellion Hit
	[ "dmc3.exe+695ED - 48 8D 0D 9C46D000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Pride
	[ "dmc3.exe+6A26C - 48 8D 0D 1D3AD000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Leviathan Laser
	[ "dmc3.exe+6AAF8 - 48 8D 0D 9131D000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 3
	[ "dmc3.exe+6ACFF - 48 8D 0D 8A2FD000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 3
	[ "dmc3.exe+6AE88 - 48 8D 0D 012ED000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 3
	[ "dmc3.exe+6B08F - 48 8D 0D FA2BD000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 3
	[ "dmc3.exe+6B218 - 48 8D 0D 712AD000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+6B41F - 48 8D 0D 6A28D000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+6B5A8 - 48 8D 0D E126D000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 3
	[ "dmc3.exe+6B810 - 48 8D 0D 7924D000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 3
	[ "dmc3.exe+6BB31 - 48 8D 0D 5821D000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 3
	[ "dmc3.exe+6BC68 - 48 8D 0D 2120D000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+6BE6F - 48 8D 0D 1A1ED000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+6C02B - 48 8D 0D 5E1CD000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Leviathan
	[ "dmc3.exe+6C18C - 48 8D 0D FD1AD000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Envy Death
	[ "dmc3.exe+6C338 - 48 8D 0D 5119D000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Leviathan
	[ "dmc3.exe+6C52B - 48 8D 0D 5E17D000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Leviathan
	[ "dmc3.exe+6C7CA - 48 8D 0D BF14D000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Leviathan
	[ "dmc3.exe+6CB49 - 48 8D 0D 4011D000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+6D7DA - 48 8D 0D AF04D000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+6D93C - 48 8D 0D 4D03D000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+6D9EA - 48 8D 0D 9F02D000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+6DA4A - 48 8D 0D 3F02D000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+6DD87 - 48 8D 0D 02FFCF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+6DE2E - 48 8D 0D 5BFECF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+6E0A7 - 48 8D 0D E2FBCF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+6F1B5 - 48 8D 0D D4EACF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+71A25 - 48 8D 0D 64C2CF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+72025 - 48 8D 0D 64BCCF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+72163 - 48 8D 0D 26BBCF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+722C4 - 48 8D 0D C5B9CF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+72D54 - 48 8D 0D 35AFCF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+73728 - 48 8D 0D 61A5CF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+739BF - 48 8D 0D CAA2CF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+73A70 - 48 8D 0D 19A2CF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+73B9E - 48 8D 0D EBA0CF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+740A3 - 48 8D 0D E69BCF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+74173 - 48 8D 0D 169BCF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+7481B - 48 8D 0D 6E94CF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+7497C - 48 8D 0D 0D93CF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+74B28 - 48 8D 0D 6191CF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+74D1B - 48 8D 0D 6E8FCF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+74F7A - 48 8D 0D 0F8DCF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+752F9 - 48 8D 0D 9089CF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+76CDC - 48 8D 0D AD6FCF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+76D67 - 48 8D 0D 226FCF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+77237 - 48 8D 0D 526ACF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+7747E - 48 8D 0D 0B68CF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+77521 - 48 8D 0D 6867CF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+7794E - 48 8D 0D 3B63CF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+785C8 - 48 8D 0D C156CF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+787AE - 48 8D 0D DB54CF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+78918 - 48 8D 0D 7153CF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+78AFE - 48 8D 0D 8B51CF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+78C68 - 48 8D 0D 2150CF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+78E4E - 48 8D 0D 3B4ECF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+78FB8 - 48 8D 0D D14CCF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+7920F - 48 8D 0D 7A4ACF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+7951D - 48 8D 0D 6C47CF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+79628 - 48 8D 0D 6146CF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+7980E - 48 8D 0D 7B44CF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+79F41 - 48 8D 0D 483DCF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+7A004 - 48 8D 0D 853CCF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+7AE84 - 48 8D 0D 052ECF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+7AEB4 - 48 8D 0D D52DCF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+7B326 - 48 8D 0D 6329CF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+7B625 - 48 8D 0D 6426CF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+7E9A0 - 48 8D 0D E9F2CE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+7EB75 - 48 8D 0D 14F1CE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+7ECAB - 48 8D 0D DEEFCE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+7EDF1 - 48 8D 0D 98EECE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+7F536 - 48 8D 0D 53E7CE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+7F8E8 - 48 8D 0D A1E3CE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+7FC4F - 48 8D 0D 3AE0CE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+7FDC0 - 48 8D 0D C9DECE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+7FEEE - 48 8D 0D 9BDDCE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+80083 - 48 8D 0D 06DCCE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+80153 - 48 8D 0D 36DBCE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+801CA - 48 8D 0D BFDACE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Hell Vanguard Death
	[ "dmc3.exe+8022A - 48 8D 0D 5FDACE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+807F9 - 48 8D 0D 90D4CE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+809F3 - 48 8D 0D 96D2CE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+81959 - 48 8D 0D 30C3CE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+81AB9 - 48 8D 0D D0C1CE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+81B04 - 48 8D 0D 85C1CE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+81C4B - 48 8D 0D 3EC0CE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+81CC9 - 48 8D 0D C0BFCE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+81D14 - 48 8D 0D 75BFCE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+81DE9 - 48 8D 0D A0BECE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+820E7 - 48 8D 0D A2BBCE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+82777 - 48 8D 0D 12B5CE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Hell Vanguard Death
	[ "dmc3.exe+8282B - 48 8D 0D 5EB4CE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+82AAE - 48 8D 0D DBB1CE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+82B6E - 48 8D 0D 1BB1CE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+83948 - 48 8D 0D 41A3CE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+83B2E - 48 8D 0D 5BA1CE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+83C98 - 48 8D 0D F19FCE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+83E7E - 48 8D 0D 0B9ECE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+83FE8 - 48 8D 0D A19CCE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+841CE - 48 8D 0D BB9ACE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+84338 - 48 8D 0D 5199CE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+8458F - 48 8D 0D FA96CE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+8489D - 48 8D 0D EC93CE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+849A8 - 48 8D 0D E192CE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+84B8E - 48 8D 0D FB90CE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+8D0F2 - 48 8D 0D 970BCE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Gun Shells
	[ "dmc3.exe+92159 - 48 8D 0D 30BBCD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+ADA91 - 48 8D 0D F801CC00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+ADB67 - 48 8D 0D 2201CC00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+B096A - 48 8D 0D 1FD3CB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+B0D77 - 48 8D 0D 12CFCB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+BECC9 - 48 8D 0D C0EFCA00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+BEE73 - 48 8D 0D 16EECA00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+D1E5B - 48 8D 0D 2EBEC900 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+D1F0B - 48 8D 0D 7EBDC900 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+D6CFB - 48 8D 0D 8E6FC900 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+D6DAB - 48 8D 0D DE6EC900 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+D94FD - 48 8D 0D 8C47C900 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Enigma Death
	[ "dmc3.exe+DB100 - 48 8D 0D 892BC900 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+DB1DC - 48 8D 0D AD2AC900 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+E008D - 48 8D 0D FCDBC800 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+E037D - 48 8D 0D 0CD9C800 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+E2AA5 - 48 8D 0D E4B1C800 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+E2B9A - 48 8D 0D EFB0C800 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+E8DD5 - 48 8D 0D B44EC800 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+E8ECA - 48 8D 0D BF4DC800 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+EE10A - 48 8D 0D 7FFBC700 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+EE21E - 48 8D 0D 6BFAC700 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+12EF29 - 48 8D 0D 60EDC300 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+12EFE8 - 48 8D 0D A1ECC300 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+135C68 - 48 8D 0D 2180C300 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Nevan Lightning Floor
	[ "dmc3.exe+135C90 - 48 8D 0D F97FC300 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Nevan Lightning Floor
	[ "dmc3.exe+13A811 - 48 8D 0D 7834C300 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+13A841 - 48 8D 0D 4834C300 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+14996E - 48 8D 0D 1B43C200 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+14FA32 - 48 8D 0D 57E2C100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+15021B - 48 8D 0D 6EDAC100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+1502A9 - 48 8D 0D E0D9C100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+1505BF - 48 8D 0D CAD6C100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+150E75 - 48 8D 0D 14CEC100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+151230 - 48 8D 0D 59CAC100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+151446 - 48 8D 0D 43C8C100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+15165C - 48 8D 0D 2DC6C100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+151713 - 48 8D 0D 76C5C100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+15224F - 48 8D 0D 3ABAC100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+15FE19 - 48 8D 0D 70DEC000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+15FED8 - 48 8D 0D B1DDC000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+165FE9 - 48 8D 0D A07CC000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+1660A8 - 48 8D 0D E17BC000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+16975C - 48 8D 0D 2D45C000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_ENEMY, HELPER_ENEMY_LADY ], // Boss Lady Shot
	[ "dmc3.exe+169800 - 48 8D 0D 8944C000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_ENEMY, HELPER_ENEMY_LADY ], // Boss Lady
	[ "dmc3.exe+1699AB - 48 8D 0D DE42C000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_ENEMY, HELPER_ENEMY_LADY ], // Boss Lady Shot
	[ "dmc3.exe+169A7B - 48 8D 0D 0E42C000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_ENEMY, HELPER_ENEMY_LADY ], // Boss Lady Hook
	[ "dmc3.exe+169D60 - 48 8D 0D 293FC000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+169EA6 - 48 8D 0D E33DC000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+169FFA - 48 8D 0D 8F3CC000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_ENEMY, HELPER_ENEMY_LADY ], // Boss Lady
	[ "dmc3.exe+16BD37 - 48 8D 0D 521FC000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_ENEMY, HELPER_ENEMY_LADY ], // Boss Lady Death
	[ "dmc3.exe+16D694 - 48 8D 0D F505C000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_ENEMY, HELPER_ENEMY_LADY ], // Boss Lady
	[ "dmc3.exe+16EFFB - 48 8D 0D 8EECBF00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_ENEMY, HELPER_ENEMY_LADY ], // Boss Lady
	[ "dmc3.exe+171E82 - 48 8D 0D 07BEBF00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_ENEMY, HELPER_ENEMY_LADY ], // Boss Lady Hook
	[ "dmc3.exe+17268E - 48 8D 0D FBB5BF00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_ENEMY, HELPER_ENEMY_LADY ], // Boss Lady
	[ "dmc3.exe+172700 - 48 8D 0D 89B5BF00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_ENEMY, HELPER_ENEMY_LADY ], // Boss Lady Hook
	[ "dmc3.exe+172753 - 48 8D 0D 36B5BF00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_ENEMY, HELPER_ENEMY_LADY ], // Boss Lady
	[ "dmc3.exe+172B9D - 48 8D 0D ECB0BF00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_ENEMY, HELPER_ENEMY_LADY ], // Boss Lady
	[ "dmc3.exe+172F86 - 48 8D 0D 03ADBF00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_ENEMY, HELPER_ENEMY_LADY ], // Boss Lady
	[ "dmc3.exe+17389D - 48 8D 0D ECA3BF00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_ENEMY, HELPER_ENEMY_LADY ], // Boss Lady Shot
	[ "dmc3.exe+173CFD - 48 8D 0D 8C9FBF00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_ENEMY, HELPER_ENEMY_LADY ], // Boss Lady
	[ "dmc3.exe+17542C - 48 8D 0D 5D88BF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+175873 - 48 8D 0D 1684BF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+175FCE - 48 8D 0D BB7CBF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+176043 - 48 8D 0D 467CBF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+17609D - 48 8D 0D EC7BBF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+1777D5 - 48 8D 0D B464BF00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_ENEMY, HELPER_ENEMY_VERGIL ], // Boss Vergil Taunt
	[ "dmc3.exe+178C29 - 48 8D 0D 6050BF00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_ENEMY, HELPER_ENEMY_VERGIL ], // Boss Vergil Devil Form
	[ "dmc3.exe+17B167 - 48 8D 0D 222BBF00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_ENEMY, HELPER_ENEMY_VERGIL ], // Boss Vergil Death
	[ "dmc3.exe+17B185 - 48 8D 0D 042BBF00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_ENEMY, HELPER_ENEMY_VERGIL ], // Boss Vergil Death
	[ "dmc3.exe+17B6C5 - 48 8D 0D C425BF00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_ENEMY, HELPER_ENEMY_VERGIL ], // Boss Vergil Melee Deflect
	[ "dmc3.exe+17CB9E - 48 8D 0D EB10BF00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_ENEMY, HELPER_ENEMY_VERGIL ], // Boss Vergil
	[ "dmc3.exe+17CBC6 - 48 8D 0D C310BF00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_ENEMY, HELPER_ENEMY_VERGIL ], // Boss Vergil
	[ "dmc3.exe+17CDD3 - 48 8D 0D B60EBF00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_ENEMY, HELPER_ENEMY_VERGIL ], // Boss Vergil Devil Form
	[ "dmc3.exe+17CF01 - 48 8D 0D 880DBF00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_ENEMY, HELPER_ENEMY_VERGIL ], // Boss Vergil
	[ "dmc3.exe+17CF44 - 48 8D 0D 450DBF00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_ENEMY, HELPER_ENEMY_VERGIL ], // Boss Vergil Bubble
	[ "dmc3.exe+17E2AD - 48 8D 0D DCF9BE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+1802E0 - 48 8D 0D A9D9BE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_ENEMY, HELPER_ENEMY_VERGIL ], // Boss Vergil Projectile Deflect
	[ "dmc3.exe+18097B - 48 8D 0D 0ED3BE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+1879B0 - 48 8D 0D D962BE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_ENEMY, HELPER_ENEMY_VERGIL ], // Boss Vergil Round Trip
	[ "dmc3.exe+187EC2 - 48 8D 0D C75DBE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+187F16 - 48 8D 0D 735DBE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+187F98 - 48 8D 0D F15CBE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+18802F - 48 8D 0D 5A5CBE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_ENEMY, HELPER_ENEMY_VERGIL ], // Boss Vergil Round Trip
	[ "dmc3.exe+1883C7 - 48 8D 0D C258BE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_ENEMY, HELPER_ENEMY_VERGIL ], // Boss Vergil Devil Form
	[ "dmc3.exe+18887B - 48 8D 0D 0E54BE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_ENEMY, HELPER_ENEMY_VERGIL ], // Boss Vergil Judgement Cut
	[ "dmc3.exe+188D30 - 48 8D 0D 594FBE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+188E3D - 48 8D 0D 4C4EBE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+188EE8 - 48 8D 0D A14DBE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+189806 - 48 8D 0D 8344BE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+18999F - 48 8D 0D EA42BE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+189D9A - 48 8D 0D EF3EBE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+18A1F3 - 48 8D 0D 963ABE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+18A308 - 48 8D 0D 8139BE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+18A490 - 48 8D 0D F937BE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+18A5FF - 48 8D 0D 8A36BE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+18D3C0 - 48 8D 0D C908BE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+18E9B9 - 48 8D 0D D0F2BD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+18EA78 - 48 8D 0D 11F2BD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+19742A - 48 8D 0D 5F68BD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+1980E0 - 48 8D 0D A95BBD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+198976 - 48 8D 0D 1353BD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+199F77 - 48 8D 0D 123DBD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+19A823 - 48 8D 0D 6634BD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+19BF3E - 48 8D 0D 4B1DBD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+19BFAB - 48 8D 0D DE1CBD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+19C8AD - 48 8D 0D DC13BD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+1A0691 - 48 8D 0D F8D5BC00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+1A3022 - 48 8D 0D 67ACBC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 3
	[ "dmc3.exe+1A3092 - 48 8D 0D F7ABBC00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+1A310D - 48 8D 0D 7CABBC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 3
	[ "dmc3.exe+1A31F2 - 48 8D 0D 97AABC00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+1A752B - 48 8D 0D 5E67BC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 8
	[ "dmc3.exe+1A75DD - 48 8D 0D AC66BC00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+1A761B - 48 8D 0D 6E66BC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 8 Tusk
	[ "dmc3.exe+1A9298 - 48 8D 0D F149BC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 8
	[ "dmc3.exe+1AF352 - 48 8D 0D 37E9BB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 8
	[ "dmc3.exe+1AF36D - 48 8D 0D 1CE9BB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 9
	[ "dmc3.exe+1AF38F - 48 8D 0D FAE8BB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 8
	[ "dmc3.exe+1AF3A6 - 48 8D 0D E3E8BB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 8
	[ "dmc3.exe+1AF3C7 - 48 8D 0D C2E8BB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 8
	[ "dmc3.exe+1AF446 - 48 8D 0D 43E8BB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 8
	[ "dmc3.exe+1AF462 - 48 8D 0D 27E8BB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 8
	[ "dmc3.exe+1AF474 - 48 8D 0D 15E8BB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 8
	[ "dmc3.exe+1AF516 - 48 8D 0D 73E7BB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 8
	[ "dmc3.exe+1AF594 - 48 8D 0D F5E6BB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 8
	[ "dmc3.exe+1AF5D8 - 48 8D 0D B1E6BB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 8
	[ "dmc3.exe+1B0995 - 48 8D 0D F4D2BB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Leviathan Laser
	[ "dmc3.exe+1B13DF - 48 8D 0D AAC8BB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+1B143B - 48 8D 0D 4EC8BB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+1B66E3 - 48 8D 0D A675BB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 3 Secret Mission 1 Blue Orb Spawn
	[ "dmc3.exe+1B6B67 - 48 8D 0D 2271BB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Collect Orb
	[ "dmc3.exe+1B6FFB - 48 8D 0D 8E6CBB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Collect Orb
	[ "dmc3.exe+1B9445 - 48 8D 0D 4448BB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Now Loading
	[ "dmc3.exe+1B949A - 48 8D 0D EF47BB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Now Loading
	[ "dmc3.exe+1B96A5 - 48 8D 0D E445BB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Stage Load
	[ "dmc3.exe+1B9706 - 48 8D 0D 8345BB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Stage Load
	[ "dmc3.exe+1B977B - 48 8D 0D 0E45BB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Stage Load
	[ "dmc3.exe+1B9791 - 48 8D 0D F844BB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Stage Load
	[ "dmc3.exe+1B97EE - 48 8D 0D 9B44BB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Stage Load
	[ "dmc3.exe+1B982F - 48 8D 0D 5A44BB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Stage Load
	[ "dmc3.exe+1B9845 - 48 8D 0D 4444BB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Stage Load
	[ "dmc3.exe+1B9B2A - 48 8D 0D 5F41BB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Now Loading
	[ "dmc3.exe+1B9B4A - 48 8D 0D 3F41BB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Now Loading
	[ "dmc3.exe+1B9B73 - 48 8D 0D 1641BB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Now Loading
	[ "dmc3.exe+1B9C5C - 48 8D 0D 2D40BB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Now Loading
	[ "dmc3.exe+1B9CB8 - 48 8D 0D D13FBB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Now Loading
	[ "dmc3.exe+1B9CC7 - 48 8D 0D C23FBB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Now Loading
	[ "dmc3.exe+1B9D4F - 48 8D 0D 3A3FBB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Now Loading
	[ "dmc3.exe+1B9DC4 - 48 8D 0D C53EBB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Now Loading
	[ "dmc3.exe+1B9E21 - 48 8D 0D 683EBB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Now Loading
	[ "dmc3.exe+1B9E5C - 48 8D 0D 2D3EBB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Now Loading
	[ "dmc3.exe+1B9E92 - 48 8D 0D F73DBB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Now Loading
	[ "dmc3.exe+1B9F40 - 48 8D 0D 493DBB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Now Loading
	[ "dmc3.exe+1B9F6A - 48 8D 0D 1F3DBB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Now Loading
	[ "dmc3.exe+1C46B5 - 48 8D 0D D495BA00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+1CBB03 - 48 8D 0D 8621BA00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Rebellion Drive
	[ "dmc3.exe+1CBF64 - 48 8D 0D 251DBA00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Rebellion Drive
	[ "dmc3.exe+1CD944 - 48 8D 0D 4503BA00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+1CD97B - 48 8D 0D 0E03BA00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Rebellion Sword Pierce Hurl Back
	[ "dmc3.exe+1CE059 - 48 8D 0D 30FCB900 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Rebellion Sword Pierce
	[ "dmc3.exe+1CE0AC - 48 8D 0D DDFBB900 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Rebellion Sword Pierce
	[ "dmc3.exe+1CE0D8 - 48 8D 0D B1FBB900 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+1CE9B8 - 48 8D 0D D1F2B900 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Spiral Crazy Combo
	[ "dmc3.exe+1CF013 - 48 8D 0D 76ECB900 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Spiral Shot
	[ "dmc3.exe+1CFDDC - 48 8D 0D ADDEB900 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Artemis Shot
	[ "dmc3.exe+1CFE53 - 48 8D 0D 36DEB900 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Artemis Shot
	[ "dmc3.exe+1D0010 - 48 8D 0D 79DCB900 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Artemis Shot
	[ "dmc3.exe+1D0A1E - 48 8D 0D 6BD2B900 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Artemis Shot
	[ "dmc3.exe+1D0F34 - 48 8D 0D 55CDB900 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Kalina Ann Shot
	[ "dmc3.exe+1D195D - 48 8D 0D 2CC3B900 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Kalina Ann Hysteric
	[ "dmc3.exe+1D255F - 48 8D 0D 2AB7B900 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Kalina Ann Grapple
	[ "dmc3.exe+1D34C4 - 48 8D 0D C5A7B900 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+1D34FA - 48 8D 0D 8FA7B900 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Kalina Ann Grapple
	[ "dmc3.exe+1D4520 - 48 8D 0D 6997B900 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Beowulf Fireball
	[ "dmc3.exe+1D6843 - 48 8D 0D 4674B900 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Nevan
	[ "dmc3.exe+1D6870 - 48 8D 0D 1974B900 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Nevan
	[ "dmc3.exe+1D6979 - 48 8D 0D 1073B900 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Nevan
	[ "dmc3.exe+1D6DF1 - 48 8D 0D 986EB900 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Nevan
	[ "dmc3.exe+1D7896 - 48 8D 0D F363B900 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Artemis Acid Rain
	[ "dmc3.exe+1D8165 - 48 8D 0D 245BB900 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Artemis Acid Rain
	[ "dmc3.exe+1D881E - 48 8D 0D 6B54B900 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_VERGIL_DEFAULT ], // Force Edge Round Trip
	[ "dmc3.exe+1D8EE7 - 48 8D 0D A24DB900 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_VERGIL_DEFAULT ], // Force Edge Round Trip
	[ "dmc3.exe+1D9383 - 48 8D 0D 0649B900 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_VERGIL_DEFAULT ], // Force Edge Round Trip
	[ "dmc3.exe+1D9C70 - 48 8D 0D 1940B900 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_VERGIL_DEFAULT ], // Summoned Swords
	[ "dmc3.exe+1DB4FC - 48 8D 0D 8D27B900 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_VERGIL_DEFAULT ], // Blistering Swords
	[ "dmc3.exe+1DB927 - 48 8D 0D 6223B900 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_VERGIL_DEFAULT ], // Summoned Swords
	[ "dmc3.exe+1DBA89 - 48 8D 0D 0022B900 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_VERGIL_DEFAULT ], // Summoned Swords
	[ "dmc3.exe+1DBE68 - 48 8D 0D 211EB900 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_VERGIL_DEFAULT ], // Storm Swords
	[ "dmc3.exe+1DC9C0 - 48 8D 0D C912B900 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_VERGIL_NERO_ANGELO ], // Yamato Nero Angelo Fireball
	[ "dmc3.exe+1DCD22 - 48 8D 0D 670FB900 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_VERGIL_NERO_ANGELO ], // Yamato Nero Angelo Fireball
	[ "dmc3.exe+1E0AD8 - 48 8D 0D B1D1B800 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // After Taunt
	[ "dmc3.exe+1E7828 - 48 8D 0D 6164B800 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Devil Form
	[ "dmc3.exe+1E78FF - 48 8D 0D 8A63B800 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Devil Form
	[ "dmc3.exe+1E9506 - 48 8D 0D 8347B800 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Quicksilver Time Lag
	[ "dmc3.exe+1E958B - 48 8D 0D FE46B800 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Quicksilver Time Lag
	[ "dmc3.exe+1EAC41 - 48 8D 0D 4830B800 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Quicksilver Deactivate Run Out
	[ "dmc3.exe+1EAEAA - 48 8D 0D DF2DB800 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Doppelganger Activate
	[ "dmc3.exe+1EAF41 - 48 8D 0D 482DB800 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Doppelganger Deactivate
	[ "dmc3.exe+1EAFA6 - 48 8D 0D E32CB800 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Doppelganger Activate
	[ "dmc3.exe+1EC095 - 48 8D 0D F41BB800 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Damage
	[ "dmc3.exe+1ED684 - 48 8D 0D 0506B800 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Deflect
	[ "dmc3.exe+1EDB09 - 48 8D 0D 8001B800 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Poison
	[ "dmc3.exe+1EDD11 - 48 8D 0D 78FFB700 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Death
	[ "dmc3.exe+1EE768 - 48 8D 0D 21F5B700 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Royalguard Break
	[ "dmc3.exe+1F109C - 48 8D 0D EDCBB700 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+1F3778 - 48 8D 0D 11A5B700 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Royalguard Block
	[ "dmc3.exe+1F413D - 48 8D 0D 4C9BB700 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+1F428A - 48 8D 0D FF99B700 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+1F8462 - 48 8D 0D 2758B700 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+1F8A8E - 48 8D 0D FB51B700 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Quicksilver Time Lag
	[ "dmc3.exe+1F8BC0 - 48 8D 0D C950B700 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+1F8F00 - 48 8D 0D 894DB700 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+1F8F7A - 48 8D 0D 0F4DB700 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Devil Form
	[ "dmc3.exe+1F9289 - 48 8D 0D 004AB700 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+1FEFC4 - 48 8D 0D C5ECB600 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Agni & Rudra Million Slash Crazy Combo
	[ "dmc3.exe+200631 - 48 8D 0D 58D6B600 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Ebony & Ivory Wild Stomp Crazy Combo
	[ "dmc3.exe+2016C3 - 48 8D 0D C6C5B600 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Beowulf Crazy Combo
	[ "dmc3.exe+201AE5 - 48 8D 0D A4C1B600 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Beowulf Straight
	[ "dmc3.exe+201B1A - 48 8D 0D 6FC1B600 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Beowulf Straight
	[ "dmc3.exe+201B3A - 48 8D 0D 4FC1B600 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Beowulf Straight
	[ "dmc3.exe+201CCE - 48 8D 0D BBBFB600 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Beowulf Straight
	[ "dmc3.exe+201CEB - 48 8D 0D 9EBFB600 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Beowulf Straight
	[ "dmc3.exe+204186 - 48 8D 0D 039BB600 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Nevan Crazy Combo
	[ "dmc3.exe+205E12 - 48 8D 0D 777EB600 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Rebellion Helm Breaker
	[ "dmc3.exe+206207 - 48 8D 0D 827AB600 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Kalina Ann Shot
	[ "dmc3.exe+20726E - 48 8D 0D 1B6AB600 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Cerberus Satellite Crazy Combo
	[ "dmc3.exe+207F30 - 48 8D 0D 595DB600 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Pole Dance
	[ "dmc3.exe+20809E - 48 8D 0D EB5BB600 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Pole Dance
	[ "dmc3.exe+208774 - 48 8D 0D 1555B600 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Spiral Shot
	[ "dmc3.exe+209E41 - 48 8D 0D 483EB600 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Agni & Rudra Tornado Crazy Combo
	[ "dmc3.exe+20B25D - 48 8D 0D 2C2AB600 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Beowulf Rising Dragon Crazy Combo
	[ "dmc3.exe+20C43E - 48 8D 0D 4B18B600 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Nevan Crazy Combo
	[ "dmc3.exe+20C761 - 48 8D 0D 2815B600 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Nevan
	[ "dmc3.exe+20C78D - 48 8D 0D FC14B600 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Nevan
	[ "dmc3.exe+20C7FC - 48 8D 0D 8D14B600 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Nevan
	[ "dmc3.exe+20C8B7 - 48 8D 0D D213B600 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Nevan
	[ "dmc3.exe+20D625 - 48 8D 0D 6406B600 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Artemis Acid Rain
	[ "dmc3.exe+20D78B - 48 8D 0D FE04B600 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Artemis Acid Rain Crazy Combo
	[ "dmc3.exe+20DD2D - 48 8D 0D 5CFFB500 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Cerberus Million Carats Crazy Combo
	[ "dmc3.exe+20E3CA - 48 8D 0D BFF8B500 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Spiral
	[ "dmc3.exe+20E6F3 - 48 8D 0D 96F5B500 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Spiral Crazy Combo
	[ "dmc3.exe+20E773 - 48 8D 0D 16F5B500 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Spiral Crazy Combo
	[ "dmc3.exe+20EE73 - 48 8D 0D 16EEB500 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Shotgun Gun Stinger Crazy Combo
	[ "dmc3.exe+210593 - 48 8D 0D F6D6B500 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Rebellion Dance Macabre
	[ "dmc3.exe+21072B - 48 8D 0D 5ED5B500 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Rebellion Dance Macabre Crazy Combo
	[ "dmc3.exe+211BD9 - 48 8D 0D B0C0B500 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Rebellion Million Stab Crazy Combo
	[ "dmc3.exe+2156B2 - 48 8D 0D D785B500 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Rebellion Sword Pierce Hurl Back
	[ "dmc3.exe+215B1E - 48 8D 0D 6B81B500 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Rebellion Charge
	[ "dmc3.exe+215DC5 - 48 8D 0D C47EB500 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Artemis Charge
	[ "dmc3.exe+215F64 - 48 8D 0D 257DB500 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Artemis Multi Charge
	[ "dmc3.exe+216037 - 48 8D 0D 527CB500 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Artemis Charge Air Charge
	[ "dmc3.exe+216177 - 48 8D 0D 127BB500 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Ebony & Ivory Charge
	[ "dmc3.exe+2161CB - 48 8D 0D BE7AB500 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Ebony & Ivory Charge
	[ "dmc3.exe+21638C - 48 8D 0D FD78B500 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Shotgun Charge
	[ "dmc3.exe+2163E0 - 48 8D 0D A978B500 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Shotgun Charge
	[ "dmc3.exe+21655A - 48 8D 0D 2F77B500 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Ebony & Ivory Charge
	[ "dmc3.exe+216CB4 - 48 8D 0D D56FB500 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Ebony & Ivory Normal Shot Air Shot
	[ "dmc3.exe+216D55 - 48 8D 0D 346FB500 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Ebony & Ivory Charge
	[ "dmc3.exe+216FF3 - 48 8D 0D 966CB500 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Ebony & Ivory Charge
	[ "dmc3.exe+218177 - 48 8D 0D 125BB500 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Shotgun Shot
	[ "dmc3.exe+21820B - 48 8D 0D 7E5AB500 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Shotgun Normal Shot Air Shot
	[ "dmc3.exe+218496 - 48 8D 0D F357B500 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_DANTE ], // Shotgun Gun Stinger
	[ "dmc3.exe+21CD6B - 48 8D 0D 1E0FB500 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_VERGIL_DEFAULT ], // Yamato Judgement Cut
	[ "dmc3.exe+21CE68 - 48 8D 0D 210EB500 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_VERGIL_DEFAULT ], // Yamato Judgement Cut
	[ "dmc3.exe+222CD0 - 48 8D 0D B9AFB400 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_VERGIL_NERO_ANGELO ], // Yamato Nero Angelo Fireball
	[ "dmc3.exe+222E54 - 48 8D 0D 35AEB400 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_VERGIL_DEFAULT ], // Yamato Charge
	[ "dmc3.exe+223022 - 48 8D 0D 67ACB400 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_VERGIL_DEFAULT ], // Force Edge Charge
	[ "dmc3.exe+223BB7 - 48 8D 0D D2A0B400 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_VERGIL_DEFAULT ], // Spiral Swords
	[ "dmc3.exe+22401F - 48 8D 0D 6A9CB400 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_VERGIL_DEFAULT ], // Blistering Swords
	[ "dmc3.exe+2240B8 - 48 8D 0D D19BB400 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_STYLE_WEAPON, HELPER_STYLE_WEAPON_VERGIL_DEFAULT ], // Storm Swords
	[ "dmc3.exe+238735 - 48 8D 0D 5455B300 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+23B290 - 48 8D 0D F929B300 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+23B349 - 48 8D 0D 4029B300 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Menu
	[ "dmc3.exe+23B357 - 48 8D 0D 3229B300 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Menu
	[ "dmc3.exe+23B5DA - 48 8D 0D AF26B300 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 3 Divinity Statue
	[ "dmc3.exe+23BB94 - 48 8D 0D F520B300 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 3 Divinity Statue
	[ "dmc3.exe+23BDB2 - 48 8D 0D D71EB300 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+23C183 - 48 8D 0D 061BB300 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+23C1CF - 48 8D 0D BA1AB300 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Door
	[ "dmc3.exe+23C282 - 48 8D 0D 071AB300 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Teleport
	[ "dmc3.exe+23C5CD - 48 8D 0D BC16B300 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 8
	[ "dmc3.exe+23D056 - 48 8D 0D 330CB300 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Stage Load
	[ "dmc3.exe+23D062 - 48 8D 0D 270CB300 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Stage Load
	[ "dmc3.exe+23D181 - 48 8D 0D 080BB300 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // New Item
	[ "dmc3.exe+23D1E1 - 48 8D 0D A80AB300 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // New Item
	[ "dmc3.exe+23D799 - 48 8D 0D F004B300 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Menu
	[ "dmc3.exe+23D7C9 - 48 8D 0D C004B300 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Menu
	[ "dmc3.exe+23D7E5 - 48 8D 0D A404B300 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Pause Restart Mission Yes
	[ "dmc3.exe+23D888 - 48 8D 0D 0104B300 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Pause Close
	[ "dmc3.exe+23D987 - 48 8D 0D 0203B300 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Pause Open
	[ "dmc3.exe+23DB83 - 48 8D 0D 0601B300 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+23DC8C - 48 8D 0D FDFFB200 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+241280 - 48 8D 0D 09CAB200 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Start Menu Start
	[ "dmc3.exe+2412A8 - 48 8D 0D E1C9B200 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Start Menu Start
	[ "dmc3.exe+241776 - 48 8D 0D 13C5B200 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+241A13 - 48 8D 0D 76C2B200 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+241B3D - 48 8D 0D 4CC1B200 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+241B4E - 48 8D 0D 3BC1B200 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2420B3 - 48 8D 0D D6BBB200 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Result
	[ "dmc3.exe+2420C4 - 48 8D 0D C5BBB200 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Result
	[ "dmc3.exe+243177 - 48 8D 0D 12ABB200 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Main Menu
	[ "dmc3.exe+243301 - 48 8D 0D 88A9B200 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Main Menu
	[ "dmc3.exe+243354 - 48 8D 0D 35A9B200 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Main Menu
	[ "dmc3.exe+2434A1 - 48 8D 0D E8A7B200 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Main Menu
	[ "dmc3.exe+2441C9 - 48 8D 0D C09AB200 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2444B4 - 48 8D 0D D597B200 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2486D8 - 48 8D 0D B155B200 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+248861 - 48 8D 0D 2854B200 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2489A0 - 48 8D 0D E952B200 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+248FB5 - 48 8D 0D D44CB200 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+24A3DC - 48 8D 0D AD38B200 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+24AFDF - 48 8D 0D AA2CB200 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Boss Vergil Judgement Cut Statue Break
	[ "dmc3.exe+24C74F - 48 8D 0D 3A15B200 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+24C9EA - 48 8D 0D 9F12B200 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+24CA2A - 48 8D 0D 5F12B200 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+24CA6A - 48 8D 0D 1F12B200 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+24F8D3 - 48 8D 0D B6E3B100 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 3 Battle Adjucator
	[ "dmc3.exe+24FDD8 - 48 8D 0D B1DEB100 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 3 Battle Adjucator
	[ "dmc3.exe+250EC0 - 48 8D 0D C9CDB100 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 3 Battle Adjucator
	[ "dmc3.exe+251491 - 48 8D 0D F8C7B100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+25161C - 48 8D 0D 6DC6B100 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 3 Battle Adjucator Break
	[ "dmc3.exe+252415 - 48 8D 0D 74B8B100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+252A90 - 48 8D 0D F9B1B100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+252C1C - 48 8D 0D 6DB0B100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+253A7B - 48 8D 0D 0EA2B100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+255587 - 48 8D 0D 0287B100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+256256 - 48 8D 0D 337AB100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2562F7 - 48 8D 0D 9279B100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+256339 - 48 8D 0D 5079B100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+25646F - 48 8D 0D 1A78B100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2599A4 - 48 8D 0D E542B100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+259BAC - 48 8D 0D DD40B100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+259DF0 - 48 8D 0D 993EB100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+259EDC - 48 8D 0D AD3DB100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+25AC1A - 48 8D 0D 6F30B100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+25B3E5 - 48 8D 0D A428B100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+25C2C1 - 48 8D 0D C819B100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+25C412 - 48 8D 0D 7718B100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+25C77C - 48 8D 0D 0D15B100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+25D351 - 48 8D 0D 3809B100 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+25DEC4 - 48 8D 0D C5FDB000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+25E0D3 - 48 8D 0D B6FBB000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Leviathan Laser
	[ "dmc3.exe+25E1D4 - 48 8D 0D B5FAB000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Leviathan
	[ "dmc3.exe+25E735 - 48 8D 0D 54F5B000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Leviathan
	[ "dmc3.exe+25E8AA - 48 8D 0D DFF3B000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Leviathan
	[ "dmc3.exe+25EB6E - 48 8D 0D 1BF1B000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Leviathan Death
	[ "dmc3.exe+25EDB3 - 48 8D 0D D6EEB000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Leviathan
	[ "dmc3.exe+25EF08 - 48 8D 0D 81EDB000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Leviathan
	[ "dmc3.exe+260AEF - 48 8D 0D 9AD1B000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+260BD3 - 48 8D 0D B6D0B000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+260C7F - 48 8D 0D 0AD0B000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+260D3E - 48 8D 0D 4BCFB000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+260D87 - 48 8D 0D 02CFB000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+261069 - 48 8D 0D 20CCB000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2611E4 - 48 8D 0D A5CAB000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+26126C - 48 8D 0D 1DCAB000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2612C3 - 48 8D 0D C6C9B000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2613A6 - 48 8D 0D E3C8B000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+261401 - 48 8D 0D 88C8B000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+261437 - 48 8D 0D 52C8B000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2615E9 - 48 8D 0D A0C6B000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+262840 - 48 8D 0D 49B4B000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2628A1 - 48 8D 0D E8B3B000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2629A6 - 48 8D 0D E3B2B000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+262A12 - 48 8D 0D 77B2B000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+262B19 - 48 8D 0D 70B1B000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+264272 - 48 8D 0D 179AB000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Leviathan
	[ "dmc3.exe+26437E - 48 8D 0D 0B99B000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+264E9A - 48 8D 0D EF8DB000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Leviathan
	[ "dmc3.exe+265EDD - 48 8D 0D AC7DB000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Leviathan
	[ "dmc3.exe+266373 - 48 8D 0D 1679B000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Leviathan
	[ "dmc3.exe+266852 - 48 8D 0D 3774B000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+266E3C - 48 8D 0D 4D6EB000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+266FD2 - 48 8D 0D B76CB000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+267D00 - 48 8D 0D 895FB000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+267DF5 - 48 8D 0D 945EB000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+267F10 - 48 8D 0D 795DB000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+268674 - 48 8D 0D 1556B000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+268C26 - 48 8D 0D 6350B000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+268D33 - 48 8D 0D 564FB000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+26967B - 48 8D 0D 0E46B000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+269A23 - 48 8D 0D 6642B000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+269A72 - 48 8D 0D 1742B000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+26A91D - 48 8D 0D 6C33B000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+26B548 - 48 8D 0D 4127B000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 3 Crystal
	[ "dmc3.exe+26B74C - 48 8D 0D 3D25B000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 3 Crystal Break
	[ "dmc3.exe+26C6D4 - 48 8D 0D B515B000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 17
	[ "dmc3.exe+26C876 - 48 8D 0D 1314B000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 17
	[ "dmc3.exe+26D252 - 48 8D 0D 370AB000 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 8
	[ "dmc3.exe+26D26B - 48 8D 0D 1E0AB000 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+26DC90 - 48 8D 0D F9FFAF00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 3
	[ "dmc3.exe+26DE2B - 48 8D 0D 5EFEAF00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 3
	[ "dmc3.exe+26E497 - 48 8D 0D F2F7AF00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 3
	[ "dmc3.exe+26E95B - 48 8D 0D 2EF3AF00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 3
	[ "dmc3.exe+26F588 - 48 8D 0D 01E7AF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+26FB6D - 48 8D 0D 1CE1AF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+272337 - 48 8D 0D 52B9AF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+272E9C - 48 8D 0D EDADAF00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 3
	[ "dmc3.exe+27331A - 48 8D 0D 6FA9AF00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 3
	[ "dmc3.exe+2733FF - 48 8D 0D 8AA8AF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+273FB1 - 48 8D 0D D89CAF00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 3
	[ "dmc3.exe+274198 - 48 8D 0D F19AAF00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission 3
	[ "dmc3.exe+2764BC - 48 8D 0D CD77AF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2764F4 - 48 8D 0D 9577AF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+27660A - 48 8D 0D 7F76AF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+277AAA - 48 8D 0D DF61AF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+27A932 - 48 8D 0D 5733AF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+27AB29 - 48 8D 0D 6031AF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+27B23F - 48 8D 0D 4A2AAF00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Options Brightness Select
	[ "dmc3.exe+27B2BA - 48 8D 0D CF29AF00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Options Brightness Exit
	[ "dmc3.exe+27B300 - 48 8D 0D 8929AF00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+280F4F - 48 8D 0D 3ACDAE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Switch Weapon
	[ "dmc3.exe+281DC5 - 48 8D 0D C4BEAE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Options Control Navigate Down
	[ "dmc3.exe+281E38 - 48 8D 0D 51BEAE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Options Control Navigate Up
	[ "dmc3.exe+281EB5 - 48 8D 0D D4BDAE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Options Control Navigate Right
	[ "dmc3.exe+281F24 - 48 8D 0D 65BDAE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Options Control Navigate Left
	[ "dmc3.exe+281F8D - 48 8D 0D FCBCAE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+281FE3 - 48 8D 0D A6BCAE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+282050 - 48 8D 0D 39BCAE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Options Control Default
	[ "dmc3.exe+282360 - 48 8D 0D 29B9AE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Options Control Set Button
	[ "dmc3.exe+283433 - 48 8D 0D 56A8AE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+283471 - 48 8D 0D 18A8AE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Guns
	[ "dmc3.exe+2835A2 - 48 8D 0D E7A6AE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Guns
	[ "dmc3.exe+2836EC - 48 8D 0D 9DA5AE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2837AA - 48 8D 0D DFA4AE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+283C87 - 48 8D 0D 02A0AE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customzie Switch Tab
	[ "dmc3.exe+283CB8 - 48 8D 0D D19FAE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Switch Tab
	[ "dmc3.exe+283CDD - 48 8D 0D AC9FAE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Guns Exit
	[ "dmc3.exe+283D1F - 48 8D 0D 6A9FAE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Guns
	[ "dmc3.exe+2848D9 - 48 8D 0D B093AE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+284925 - 48 8D 0D 6493AE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+284A48 - 48 8D 0D 4192AE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+284B92 - 48 8D 0D F790AE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+284C3B - 48 8D 0D 4E90AE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+284E1E - 48 8D 0D 6B8EAE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+284E63 - 48 8D 0D 268EAE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+284EA7 - 48 8D 0D E28DAE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+284EDF - 48 8D 0D AA8DAE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+285953 - 48 8D 0D 3683AE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Navigate
	[ "dmc3.exe+285DBC - 48 8D 0D CD7EAE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+285DEA - 48 8D 0D 9F7EAE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Item
	[ "dmc3.exe+285E18 - 48 8D 0D 717EAE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Item
	[ "dmc3.exe+285E46 - 48 8D 0D 437EAE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+285E74 - 48 8D 0D 157EAE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Item Select
	[ "dmc3.exe+285EA2 - 48 8D 0D E77DAE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+285F64 - 48 8D 0D 257DAE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Item Information
	[ "dmc3.exe+286035 - 48 8D 0D 547CAE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+286088 - 48 8D 0D 017CAE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Item Select No
	[ "dmc3.exe+286104 - 48 8D 0D 857BAE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Item
	[ "dmc3.exe+286211 - 48 8D 0D 787AAE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+286C6E - 48 8D 0D 1B70AE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Item Information
	[ "dmc3.exe+2872DF - 48 8D 0D AA69AE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Item Navigate Down
	[ "dmc3.exe+28731B - 48 8D 0D 6E69AE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Item Navigate Up
	[ "dmc3.exe+287379 - 48 8D 0D 1069AE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Switch Tab
	[ "dmc3.exe+2873B0 - 48 8D 0D D968AE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Switch Tab
	[ "dmc3.exe+2873F8 - 48 8D 0D 9168AE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Item Exit
	[ "dmc3.exe+288AC1 - 48 8D 0D C851AE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+288B5C - 48 8D 0D 2D51AE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Action
	[ "dmc3.exe+288BF9 - 48 8D 0D 9050AE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Action
	[ "dmc3.exe+288C92 - 48 8D 0D F74FAE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Action
	[ "dmc3.exe+288CD7 - 48 8D 0D B24FAE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Switch Tab
	[ "dmc3.exe+288D1C - 48 8D 0D 6D4FAE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Action Exit
	[ "dmc3.exe+289097 - 48 8D 0D F24BAE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Action
	[ "dmc3.exe+2890CA - 48 8D 0D BF4BAE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+28925F - 48 8D 0D 2A4AAE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Action
	[ "dmc3.exe+28947F - 48 8D 0D 0A48AE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2899C1 - 48 8D 0D C842AE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+28AE35 - 48 8D 0D 542EAE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+28AEA0 - 48 8D 0D E92DAE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Equip Information Close
	[ "dmc3.exe+28CDF3 - 48 8D 0D 960EAE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+28CE10 - 48 8D 0D 790EAE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Equip Select
	[ "dmc3.exe+28CE80 - 48 8D 0D 090EAE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Equip Information Open
	[ "dmc3.exe+28CECF - 48 8D 0D BA0DAE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Equip Switch Tab
	[ "dmc3.exe+28CEF0 - 48 8D 0D 990DAE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Equip Switch Tab
	[ "dmc3.exe+28CF5C - 48 8D 0D 2D0DAE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Equip Navigate Down
	[ "dmc3.exe+28D007 - 48 8D 0D 820CAE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Switch Tab
	[ "dmc3.exe+28D0EB - 48 8D 0D 9E0BAE00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Equip Select
	[ "dmc3.exe+28D139 - 48 8D 0D 500BAE00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+28E260 - 48 8D 0D 29FAAD00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Demo Digest Select
	[ "dmc3.exe+28E2A3 - 48 8D 0D E6F9AD00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Demo Digest Exit
	[ "dmc3.exe+28E2EA - 48 8D 0D 9FF9AD00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Demo Digest Navigate Down
	[ "dmc3.exe+28E331 - 48 8D 0D 58F9AD00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Demo Digest Navigate Up
	[ "dmc3.exe+28E37D - 48 8D 0D 0CF9AD00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Demo Digest Navigate Right
	[ "dmc3.exe+28E412 - 48 8D 0D 77F8AD00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Demo Digest Navigate Left
	[ "dmc3.exe+28EDD2 - 48 8D 0D B7EEAD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+28EE61 - 48 8D 0D 28EEAD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+28EEB7 - 48 8D 0D D2EDAD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+28EF46 - 48 8D 0D 43EDAD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+290409 - 48 8D 0D 80D8AD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+29063B - 48 8D 0D 4ED6AD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+29065D - 48 8D 0D 2CD6AD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+290A07 - 48 8D 0D 82D2AD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+290AA2 - 48 8D 0D E7D1AD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+290B4A - 48 8D 0D 3FD1AD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+290BF4 - 48 8D 0D 95D0AD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+290C45 - 48 8D 0D 44D0AD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+290CB4 - 48 8D 0D D5CFAD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+291336 - 48 8D 0D 53C9AD00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Options Game Options Navigate Up
	[ "dmc3.exe+291382 - 48 8D 0D 07C9AD00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Options Game Options Navigate Down
	[ "dmc3.exe+29144A - 48 8D 0D 3FC8AD00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Options Game Options Exit
	[ "dmc3.exe+291484 - 48 8D 0D 05C8AD00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Options Game Options Focus Exit
	[ "dmc3.exe+29239D - 48 8D 0D ECB8AD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+292453 - 48 8D 0D 36B8AD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2924FF - 48 8D 0D 8AB7AD00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Continue
	[ "dmc3.exe+2925FC - 48 8D 0D 8DB6AD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2926D0 - 48 8D 0D B9B5AD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+292777 - 48 8D 0D 12B5AD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+292796 - 48 8D 0D F3B4AD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2927F6 - 48 8D 0D 93B4AD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+292833 - 48 8D 0D 56B4AD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+292A29 - 48 8D 0D 60B2AD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+292AD4 - 48 8D 0D B5B1AD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+292B7B - 48 8D 0D 0EB1AD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+292C70 - 48 8D 0D 19B0AD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+292D2A - 48 8D 0D 5FAFAD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+292D7C - 48 8D 0D 0DAFAD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+292D9F - 48 8D 0D EAAEAD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+292DE4 - 48 8D 0D A5AEAD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+292EB5 - 48 8D 0D D4ADAD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+292ECE - 48 8D 0D BBADAD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+292F39 - 48 8D 0D 50ADAD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+292F6E - 48 8D 0D 1BADAD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+293250 - 48 8D 0D 39AAAD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+29562D - 48 8D 0D 5C86AD00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // New Item
	[ "dmc3.exe+2959A3 - 48 8D 0D E682AD00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // New Item
	[ "dmc3.exe+29648C - 48 8D 0D FD77AD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2964D9 - 48 8D 0D B077AD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+296514 - 48 8D 0D 7577AD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+296546 - 48 8D 0D 4377AD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+29A458 - 48 8D 0D 3138AD00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Menu Open Demo Digest
	[ "dmc3.exe+29A4A4 - 48 8D 0D E537AD00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Menu Close
	[ "dmc3.exe+29A6BA - 48 8D 0D CF35AD00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Menu Navigate Left
	[ "dmc3.exe+29A6EB - 48 8D 0D 9E35AD00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Menu Navigate Down
	[ "dmc3.exe+29A738 - 48 8D 0D 5135AD00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+29AC31 - 48 8D 0D 5830AD00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Menu Easy Automatic Select
	[ "dmc3.exe+29AC6E - 48 8D 0D 1B30AD00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Menu Easy Automatic Exit
	[ "dmc3.exe+29ACD4 - 48 8D 0D B52FAD00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Menu Easy Automatic Navigate Left
	[ "dmc3.exe+29AEAA - 48 8D 0D DF2DAD00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Menu Close Yes
	[ "dmc3.exe+29AEC4 - 48 8D 0D C52DAD00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Menu Close No
	[ "dmc3.exe+29BC5C - 48 8D 0D 2D20AD00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Start Navigate Left
	[ "dmc3.exe+29BCAC - 48 8D 0D DD1FAD00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Start Navigate Right
	[ "dmc3.exe+29BD81 - 48 8D 0D 081FAD00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Start Customize Select
	[ "dmc3.exe+29DF31 - 48 8D 0D 58FDAC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Options Default Yes
	[ "dmc3.exe+29DFC6 - 48 8D 0D C3FCAC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Options Navigate Down
	[ "dmc3.exe+29E03E - 48 8D 0D 4BFCAC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Options Navigate Up
	[ "dmc3.exe+29E0F1 - 48 8D 0D 98FBAC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Options Vibration Navigate
	[ "dmc3.exe+29E1CF - 48 8D 0D BAFAAC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Options Volume Navigate Right
	[ "dmc3.exe+29E273 - 48 8D 0D 16FAAC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Options Vibration Navigate
	[ "dmc3.exe+29E35D - 48 8D 0D 2CF9AC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Options Volume Navigate Left
	[ "dmc3.exe+29E3D9 - 48 8D 0D B0F8AC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Options Game Options Select
	[ "dmc3.exe+29E404 - 48 8D 0D 85F8AC00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+29FDBD - 48 8D 0D CCDEAC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Pause Restart Mission Navigate
	[ "dmc3.exe+29FDFE - 48 8D 0D 8BDEAC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Pause Restart Mission No
	[ "dmc3.exe+29FE52 - 48 8D 0D 37DEAC00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2A000C - 48 8D 0D 7DDCAC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Pause Quit Mission Navigate Right
	[ "dmc3.exe+2A004D - 48 8D 0D 3CDCAC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Pause Quit Mission Select
	[ "dmc3.exe+2A00A1 - 48 8D 0D E8DBAC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Pause Quit Mission Close
	[ "dmc3.exe+2A0281 - 48 8D 0D 08DAAC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Pause Navigate Up
	[ "dmc3.exe+2A02E3 - 48 8D 0D A6D9AC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Pause Navigate Down
	[ "dmc3.exe+2A03B8 - 48 8D 0D D1D8AC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Pause Enter
	[ "dmc3.exe+2A03F8 - 48 8D 0D 91D8AC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Pause Close
	[ "dmc3.exe+2A0B80 - 48 8D 0D 09D1AC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Result
	[ "dmc3.exe+2A0D41 - 48 8D 0D 48CFAC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Result
	[ "dmc3.exe+2A0EB2 - 48 8D 0D D7CDAC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Result
	[ "dmc3.exe+2A1DDC - 48 8D 0D ADBEAC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Result
	[ "dmc3.exe+2A2007 - 48 8D 0D 82BCAC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Result
	[ "dmc3.exe+2A347D - 48 8D 0D 0CA8AC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Result Navigate Right
	[ "dmc3.exe+2A34D6 - 48 8D 0D B3A7AC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Result Navigate Left
	[ "dmc3.exe+2A370A - 48 8D 0D 7FA5AC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Result Save Select
	[ "dmc3.exe+2A38D5 - 48 8D 0D B4A3AC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Result
	[ "dmc3.exe+2A396D - 48 8D 0D 1CA3AC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Result
	[ "dmc3.exe+2A3A3C - 48 8D 0D 4DA2AC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Result
	[ "dmc3.exe+2A3DB9 - 48 8D 0D D09EAC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Mission Result
	[ "dmc3.exe+2A4B8C - 48 8D 0D FD90AC00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2A4D0D - 48 8D 0D 7C8FAC00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2A5A40 - 48 8D 0D 4982AC00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2A5A99 - 48 8D 0D F081AC00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2A5C5E - 48 8D 0D 2B80AC00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2A5C8F - 48 8D 0D FA7FAC00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2A6253 - 48 8D 0D 367AAC00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2A6283 - 48 8D 0D 067AAC00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2A6BC9 - 48 8D 0D C070AC00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2A6C7C - 48 8D 0D 0D70AC00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2A6CC5 - 48 8D 0D C46FAC00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2A7D72 - 48 8D 0D 175FAC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // File Close
	[ "dmc3.exe+2A837F - 48 8D 0D 0A59AC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // File Video Close
	[ "dmc3.exe+2A9056 - 48 8D 0D 334CAC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Guns Change Tab Right
	[ "dmc3.exe+2A97C2 - 48 8D 0D C744AC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Guns Navigate Down
	[ "dmc3.exe+2AA97D - 48 8D 0D 0C33AC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // File Item Close
	[ "dmc3.exe+2AB48C - 48 8D 0D FD27AC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // File Video Open
	[ "dmc3.exe+2AB49B - 48 8D 0D EE27AC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // File Item Open
	[ "dmc3.exe+2AB616 - 48 8D 0D 7326AC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Guns Close
	[ "dmc3.exe+2AB6EC - 48 8D 0D 9D25AC00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2AB7E9 - 48 8D 0D A024AC00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2ADBCD - 48 8D 0D BC00AC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Status Enter
	[ "dmc3.exe+2ADC80 - 48 8D 0D 0900AC00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Status Navigate
	[ "dmc3.exe+2AE8A1 - 48 8D 0D E8F3AB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Item Unavailable
	[ "dmc3.exe+2AE960 - 48 8D 0D 29F3AB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2AEA60 - 48 8D 0D 29F2AB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2AEAA6 - 48 8D 0D E3F1AB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2AEAE5 - 48 8D 0D A4F1AB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2AEC40 - 48 8D 0D 49F0AB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2AEF8F - 48 8D 0D FAECAB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Item Close Information
	[ "dmc3.exe+2AF1E0 - 48 8D 0D A9EAAB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Item Select
	[ "dmc3.exe+2AF228 - 48 8D 0D 61EAAB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2AF2F6 - 48 8D 0D 93E9AB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2AF340 - 48 8D 0D 49E9AB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2AF3F4 - 48 8D 0D 95E8AB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2AF4A3 - 48 8D 0D E6E7AB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Item Navigate Up
	[ "dmc3.exe+2AF4FF - 48 8D 0D 8AE7AB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Item Close
	[ "dmc3.exe+2AF62B - 48 8D 0D 5EE6AB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2B1F61 - 48 8D 0D 28BDAB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Map Exit
	[ "dmc3.exe+2B21AA - 48 8D 0D DFBAAB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2B2279 - 48 8D 0D 10BAAB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2B22AA - 48 8D 0D DFB9AB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2B246A - 48 8D 0D 1FB8AB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2B2C84 - 48 8D 0D 05B0AB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2B2CB8 - 48 8D 0D D1AFAB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Map Exit
	[ "dmc3.exe+2B2D8A - 48 8D 0D FFAEAB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2B2DBB - 48 8D 0D CEAEAB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2B2E1F - 48 8D 0D 6AAEAB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2B419B - 48 8D 0D EE9AAB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Equip Exit
	[ "dmc3.exe+2B4207 - 48 8D 0D 829AAB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Equip Switch Tab
	[ "dmc3.exe+2B4286 - 48 8D 0D 039AAB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2B5DEE - 48 8D 0D 9B7EAB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2B5E28 - 48 8D 0D 617EAB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2B6CFB - 48 8D 0D 8E6FAB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2B6F38 - 48 8D 0D 516DAB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2B7040 - 48 8D 0D 496CAB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2B7348 - 48 8D 0D 4169AB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2B7450 - 48 8D 0D 3968AB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2B7752 - 48 8D 0D 3765AB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Style Information Navigate Right
	[ "dmc3.exe+2B792C - 48 8D 0D 5D63AB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Style Information Select
	[ "dmc3.exe+2B796D - 48 8D 0D 1C63AB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Style Information Close
	[ "dmc3.exe+2B8AE3 - 48 8D 0D A651AB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Style Navigate Down
	[ "dmc3.exe+2B8B55 - 48 8D 0D 3451AB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Style Information
	[ "dmc3.exe+2B8B8A - 48 8D 0D FF50AB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Style Select
	[ "dmc3.exe+2B8BFB - 48 8D 0D 8E50AB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Customize Style Exit
	[ "dmc3.exe+2B9343 - 48 8D 0D 4649AB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2B93EF - 48 8D 0D 9A48AB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2B9C8F - 48 8D 0D FA3FAB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2B9E38 - 48 8D 0D 513EAB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2BA360 - 48 8D 0D 2939AB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2BA382 - 48 8D 0D 0739AB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2BB6FF - 48 8D 0D 8A25AB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2BBFB2 - 48 8D 0D D71CAB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Main Menu Navigate Right
	[ "dmc3.exe+2BC001 - 48 8D 0D 881CAB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Main Menu Navigate Left
	[ "dmc3.exe+2BC075 - 48 8D 0D 141CAB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Main Menu Select Load Game
	[ "dmc3.exe+2BC0B1 - 48 8D 0D D81BAB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Main Menu Select Options
	[ "dmc3.exe+2BC52D - 48 8D 0D 5C17AB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2BC7D4 - 48 8D 0D B514AB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2BC859 - 48 8D 0D 3014AB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2BC970 - 48 8D 0D 1913AB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Main Menu New Game Tutorial Navigate Right
	[ "dmc3.exe+2BC9AE - 48 8D 0D DB12AB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Main Menu New Game Tutorial Navigate Left
	[ "dmc3.exe+2BCA0B - 48 8D 0D 7E12AB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Main Menu New Game Tutorial Select Off
	[ "dmc3.exe+2BCA80 - 48 8D 0D 0912AB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Main Menu New Game Tutorial Close
	[ "dmc3.exe+2BCC59 - 48 8D 0D 3010AB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Main Menu New Game Difficulty Navigate Right
	[ "dmc3.exe+2BCCB8 - 48 8D 0D D10FAB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Main Menu New Game Difficulty Navigate Left
	[ "dmc3.exe+2BCD04 - 48 8D 0D 850FAB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Main Menu New Game Difficulty Select
	[ "dmc3.exe+2BCD4B - 48 8D 0D 3E0FAB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Main Menu New Game Difficulty Close
	[ "dmc3.exe+2BCF14 - 48 8D 0D 750DAB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Main Menu New Game Orbs Navigate Right
	[ "dmc3.exe+2BCF52 - 48 8D 0D 370DAB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Main Menu New Game Orbs Navigate Left
	[ "dmc3.exe+2BCFC4 - 48 8D 0D C50CAB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2BD019 - 48 8D 0D 700CAB00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Main Menu New Game Orbs Close
	[ "dmc3.exe+2BD1C9 - 48 8D 0D C00AAB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2BD207 - 48 8D 0D 820AAB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2BD281 - 48 8D 0D 080AAB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2BDC7D - 48 8D 0D 0C00AB00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2BEC13 - 48 8D 0D 76F0AA00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Total Ranking Exit
	[ "dmc3.exe+2BF0AA - 48 8D 0D DFEBAA00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // File Library Style Exit
	[ "dmc3.exe+2BF25D - 48 8D 0D 2CEAAA00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // File Library Style Open
	[ "dmc3.exe+2BFFBB - 48 8D 0D CEDCAA00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2BFFF8 - 48 8D 0D 91DCAA00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2C003F - 48 8D 0D 4ADCAA00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2C007B - 48 8D 0D 0EDCAA00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2C00B8 - 48 8D 0D D1DBAA00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2C0158 - 48 8D 0D 31DBAA00 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+2C6EC8 - 48 8D 0D C16DAA00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Enemy Damage or Rebellion Hit
	[ "dmc3.exe+2C6EF2 - 48 8D 0D 976DAA00 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Ebony & Ivory Wild Stomp
	[ "dmc3.exe+32A39A - 48 8D 0D EF38A400 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+32A42C - 48 8D 0D 5D38A400 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+32A622 - 48 8D 0D 6736A400 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Load
	[ "dmc3.exe+32A8D8 - 48 8D 0D B133A400 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Save Exit
	[ "dmc3.exe+32ABAE - 48 8D 0D DB30A400 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Save Navigate Left
	[ "dmc3.exe+32ABF7 - 48 8D 0D 9230A400 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Save Navigate Right
	[ "dmc3.exe+32AC3D - 48 8D 0D 4C30A400 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Save Select
	[ "dmc3.exe+32AC70 - 48 8D 0D 1930A400 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Load Exit
	[ "dmc3.exe+32ACDE - 48 8D 0D AB2FA400 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+32AD24 - 48 8D 0D 652FA400 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+32AD6E - 48 8D 0D 1B2FA400 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+32ADAB - 48 8D 0D DE2EA400 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+32AE04 - 48 8D 0D 852EA400 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Save Select Navigate Right
	[ "dmc3.exe+32AE4F - 48 8D 0D 3A2EA400 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Save Select Navigate Left
	[ "dmc3.exe+32AED6 - 48 8D 0D B32DA400 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Save Select Exit
	[ "dmc3.exe+32AF18 - 48 8D 0D 712DA400 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Save Select Yes
	[ "dmc3.exe+337B79 - 48 8D 0D 1061A300 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+337BDD - 48 8D 0D AC60A300 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Update
	[ "dmc3.exe+338BBE - 48 8D 0D CB50A300 - LEA RCX,[dmc3.exe+D6DC90]" ], // 
	[ "dmc3.exe+34ED20 - 48 8D 0D 69EFA100 - LEA RCX,[dmc3.exe+D6DC90]", CHANNEL_IGNORE ], // Exit
];



tabCount = 1;

for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
{
	let item = items[itemIndex];

	let name         = item[0];
	let channelIndex = item[1];
	let helperIndex  = item[2];

	let match = name.match(/^dmc3\.exe\+([A-Za-z0-9]+) - ([\S\s]+) - ([\S\s]+)$/);
	if (!match)
	{
		console.log("No Match");

		return;
	}

	let offName     = match[1];
	let bytes       = match[2];
	let instruction = match[3];

	let off = parseInt(offName, 16);

	let addr = off;
	let jumpAddr = (off + 7);

	let addrName = addr.toString(16).toUpperCase();
	let jumpAddrName = jumpAddr.toString(16).toUpperCase();

	if (channelIndex == CHANNEL_IGNORE)
	{
		continue;
	}



	if (!channelIndex)
	{
		c_debug += "debug_setBreakpoint(appBaseAddr+0x" + offName + ")" + NEW_LINE;

		continue;
	}



	if (channelIndex == CHANNEL_GLOBAL)
	{
		ScopeStart();
		c += Tabs() + "auto addr     = (appBaseAddr + 0x" + addrName + ");" + NEW_LINE;
		c += Tabs() + "auto jumpAddr = (appBaseAddr + 0x" + jumpAddrName + ");" + NEW_LINE;
		c += Tabs() + "constexpr uint32 size = 7;" + NEW_LINE;
		c += Tabs() + "\/*" + NEW_LINE;
		c += Tabs() + "" + name + NEW_LINE;
		c += Tabs() + "dmc3.exe+" + jumpAddrName + NEW_LINE;
		c += Tabs() + "*\/" + NEW_LINE;
		c += NEW_LINE;
		c += Tabs() + "static Function func = {};" + NEW_LINE;
		c += NEW_LINE;
		c += Tabs() + "constexpr byte8 sect1[] =" + NEW_LINE;
		ScopeStart();
		c += Tabs() + "mov_rcx_rbx," + NEW_LINE;
		ScopeEnd
		(
			"}",
			ScopeFlags_Semicolon
		);
		c += NEW_LINE;
		c += Tabs() + "if (!run)" + NEW_LINE;
		ScopeStart();
		c += Tabs() + "backupHelper.Save(addr, size);" + NEW_LINE;
		c += Tabs() + "func = CreateFunction(UpdateGlobalHelperIndices, jumpAddr, true, true, size, sizeof(sect1));" + NEW_LINE;
		c += Tabs() + "CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);" + NEW_LINE;
		c += Tabs() + "CopyMemory(func.sect1, sect1, sizeof(sect1));" + NEW_LINE;
		c += Tabs() + "WriteAddress(func.sect0, (appBaseAddr + 0xD6DC90), 7);" + NEW_LINE;
		ScopeEnd();
		c += NEW_LINE;
		c += Tabs() + "if (enable)" + NEW_LINE;
		ScopeStart();
		c += Tabs() + "WriteJump(addr, func.addr, (size - 5));" + NEW_LINE;
		ScopeEnd();
		c += Tabs() + "else" + NEW_LINE;
		ScopeStart();
		c += Tabs() + "backupHelper.Restore(addr);" + NEW_LINE;
		ScopeEnd();
		ScopeEnd();

		continue;
	}










	ScopeStart();
	c += Tabs() + "auto addr     = (appBaseAddr + 0x" + addrName + ");" + NEW_LINE;
	c += Tabs() + "auto jumpAddr = (appBaseAddr + 0x" + jumpAddrName + ");" + NEW_LINE;
	c += Tabs() + "constexpr uint32 size = 7;" + NEW_LINE;
	c += Tabs() + "\/*" + NEW_LINE;
	c += Tabs() + "" + name + NEW_LINE;
	c += Tabs() + "dmc3.exe+" + jumpAddrName + NEW_LINE;
	c += Tabs() + "*\/" + NEW_LINE;
	c += NEW_LINE;
	c += Tabs() + "static Function func = {};" + NEW_LINE;
	c += NEW_LINE;
	c += Tabs() + "constexpr byte8 sect0[] =" + NEW_LINE;
	ScopeStart();
	c += Tabs() + "0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx,0" + NEW_LINE;
	c += Tabs() + "0xC6, 0x01, 0x00,                                           // mov byte ptr [rcx],0" + NEW_LINE;
	c += Tabs() + "0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,                   // lea rcx,[dmc3.exe+D6DC90]" + NEW_LINE;
	ScopeEnd
	(
		"}",
		ScopeFlags_Semicolon
	);
	c += NEW_LINE;
	c += Tabs() + "if (!run)" + NEW_LINE;
	ScopeStart();
	c += Tabs() + "backupHelper.Save(addr, size);" + NEW_LINE;
	c += Tabs() + "func = CreateFunction(0, jumpAddr, false, true, sizeof(sect0));" + NEW_LINE;
	c += Tabs() + "CopyMemory(func.sect0, sect0, sizeof(sect0));" + NEW_LINE;
	c += Tabs() + "*reinterpret_cast<uint8 **>(func.sect0 + 2) = &g_helperIndices[" + GetChannelName(channelIndex) + "];" + NEW_LINE;
	c += Tabs() + "*reinterpret_cast<uint8 *>(func.sect0 + 0xC) = " + GetHelperName(helperIndex) + ";"+ NEW_LINE;
	c += Tabs() + "WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0xD6DC90), 7);" + NEW_LINE;
	ScopeEnd();
	c += NEW_LINE;
	c += Tabs() + "if (enable)" + NEW_LINE;
	ScopeStart();
	c += Tabs() + "WriteJump(addr, func.addr, (size - 5));" + NEW_LINE;
	ScopeEnd();
	c += Tabs() + "else" + NEW_LINE;
	ScopeStart();
	c += Tabs() + "backupHelper.Restore(addr);" + NEW_LINE;
	ScopeEnd();
	ScopeEnd();



	// console.log("$" + match[1] + "$");
	// console.log("$" + match[2] + "$");
	// console.log("$" + match[3] + "$");
}

tabCount = 0;

c += NEW_LINE;






let c_new = c;

c = "";

let filename = "../Mary/Sound.ixx";

let file = fs.readFileSync(filename, "utf8");

let lines = GetLines(file);

if
(
	!Tag_Init
	(
		lines,
		/\/\/ \$RelocationDataStart$/,
		/\/\/ \$RelocationDataEnd$/
	)
)
{
	console.log("Tag_Init failed.");

	return;
}

Tag_CopyUntil(lines);

c += c_new;

Tag_CopyAfter(lines);

fs.writeFileSync(filename, c);
























fs.writeFileSync("new_dbst_breakpoints.txt", c_debug);

//fs.writeFileSync("new_dbst_funcs.txt", c);
