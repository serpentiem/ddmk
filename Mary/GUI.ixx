module;
#include "../ImGui/imgui.h"

#include <stdio.h>

#include <xmmintrin.h>
export module GUI;

import Core;

#include "../Core/Macros.h"

import Vars;

import Windows;
import DXGI;
import D3D11;

import Core_GUI;

import ActorRelocations;
import Actor;
import Arcade;
import Camera;
import Config;
import Event;
import File;
import FMOD;
import Global;
import Graphics;
import HUD;
import Input;
import Internal;
import Item;
import Model;
import Scene;
import SoundRelocations;
import Sound;
import Speed;
import Training;
import Window;

using namespace Windows;
using namespace DXGI;
using namespace D3D11;

#define debug true

#include "Macros.h"



#pragma region Base

namespaceStart(FONT);
enum
{
	DEFAULT,
	MAIN,
	OVERLAY_8,
	OVERLAY_16,
	OVERLAY_32,
	OVERLAY_64,
	OVERLAY_128,
};
namespaceEnd();



void BuildFonts()
{
	auto & io = ImGui::GetIO();

	io.Fonts->AddFontDefault();

	char overlayFont[512];

	{
		char buffer[64];

		GetWindowsDirectoryA
		(
			buffer,
			sizeof(buffer)
		);

		snprintf
		(
			overlayFont,
			sizeof(overlayFont),
			"%s\\Fonts\\consola.ttf",
			buffer
		);
	}

	io.Fonts->AddFontFromFileTTF(overlayFont, 17 );
	io.Fonts->AddFontFromFileTTF(overlayFont, 8  );
	io.Fonts->AddFontFromFileTTF(overlayFont, 16 );
	io.Fonts->AddFontFromFileTTF(overlayFont, 32 );
	io.Fonts->AddFontFromFileTTF(overlayFont, 64 );
	io.Fonts->AddFontFromFileTTF(overlayFont, 128);

	io.Fonts->Build();
}

// @Merge
void TooltipHelper
(
	const char * name,
	const char * description,
	float x = 2048.0f
)
{
	ImGui::TextDisabled(name);

	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(x);
		ImGui::Text(description);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

void DescriptionHelper
(
	const char * description,
	float width = 500.0f
)
{
	ImGui::PushTextWrapPos(width);
	ImGui::Text(description);
	ImGui::PopTextWrapPos();
}

#pragma endregion

#pragma region Common

const char * buttonIndexNames[] =
{
	"Button 1",
	"Button 2",
	"Button 3",
	"Button 4",
};

const char * dataNames[] =
{
	"Data 0",
	"Data 1",
	"Data 2",
	"Data 3",
	"Data 4",
	"Data 5",
	"Data 6",
	"Data 7",
};

const char * buttonNames[] =
{
	"Nothing",
	"Left Trigger",
	"Right Trigger",
	"Left Shoulder",
	"Right Shoulder",
	"Y",
	"B",
	"A",
	"X",
	"Back",
	"Left Thumb",
	"Right Thumb",
	"Start",
	"Up",
	"Right",
	"Down",
	"Left",
};

constexpr byte16 buttons[] =
{
	0,
	GAMEPAD::LEFT_TRIGGER,
	GAMEPAD::RIGHT_TRIGGER,
	GAMEPAD::LEFT_SHOULDER,
	GAMEPAD::RIGHT_SHOULDER,
	GAMEPAD::Y,
	GAMEPAD::B,
	GAMEPAD::A,
	GAMEPAD::X,
	GAMEPAD::BACK,
	GAMEPAD::LEFT_THUMB,
	GAMEPAD::RIGHT_THUMB,
	GAMEPAD::START,
	GAMEPAD::UP,
	GAMEPAD::RIGHT,
	GAMEPAD::DOWN,
	GAMEPAD::LEFT,
};

const char * directionNames[] =
{
	"Up",
	"Right",
	"Down",
	"Left",
};

const char * playerIndexNames[] =
{
	"Player 1",
	"Player 2",
	"Player 3",
	"Player 4",
};

const char * characterIndexNames[] =
{
	"Character 1",
	"Character 2",
	"Character 3",
};

const char * entityNames[] =
{
	"Main",
	"Clone",
};

const char * entityEnumNames[] =
{
	"ENTITY::MAIN",
	"ENTITY::CLONE",
};

const char * characterNames[] =
{
	"Dante",
	"Bob",
	"Lady",
	"Vergil",
};

const char * newCharacterNames[] =
{
	"Dante",
	"Bob",
	"Lady",
	"Vergil",
	"Boss Lady",
	"Boss Vergil",
};

constexpr uint8 newCharacters[] =
{
	CHARACTER::DANTE,
	CHARACTER::BOB,
	CHARACTER::LADY,
	CHARACTER::VERGIL,
	CHARACTER::BOSS_LADY,
	CHARACTER::BOSS_VERGIL,
};

const char * collisionGroupNames[] =
{
	"Player",
	"Enemy"
};

constexpr uint8 collisionGroups[] =
{
	COLLISION_GROUP::PLAYER,
	COLLISION_GROUP::ENEMY,
};

const char * styleNamesDante[] =
{
	"Swordmaster",
	"Gunslinger",
	"Trickster",
	"Royalguard",
	"Quicksilver",
	"Doppelganger",
};

constexpr uint8 stylesDante[] =
{
	STYLE::SWORDMASTER,
	STYLE::GUNSLINGER,
	STYLE::TRICKSTER,
	STYLE::ROYALGUARD,
	STYLE::QUICKSILVER,
	STYLE::DOPPELGANGER,
};

const char * styleNamesVergil[] =
{
	"Dark Slayer",
	"Quicksilver",
	"Doppelganger",
};

constexpr uint8 stylesVergil[] =
{
	STYLE::DARK_SLAYER,
	STYLE::QUICKSILVER,
	STYLE::DOPPELGANGER,
};

const char * meleeWeaponNamesDante[] =
{
	"Rebellion",
	"Cerberus",
	"Agni & Rudra",
	"Nevan",
	"Beowulf",
};

constexpr uint8 meleeWeaponsDante[] =
{
	WEAPON::REBELLION,
	WEAPON::CERBERUS,
	WEAPON::AGNI_RUDRA,
	WEAPON::NEVAN,
	WEAPON::BEOWULF_DANTE,
};

const char * meleeWeaponNamesVergil[] =
{
	"Yamato",
	"Beowulf",
	"Yamato & Force Edge",
};

constexpr uint8 meleeWeaponsVergil[] =
{
	WEAPON::YAMATO_VERGIL,
	WEAPON::BEOWULF_VERGIL,
	WEAPON::YAMATO_FORCE_EDGE,
};

const char * rangedWeaponNamesDante[] =
{
	"Ebony & Ivory",
	"Shotgun",
	"Artemis",
	"Spiral",
	"Kalina Ann",
};

constexpr uint8 rangedWeaponsDante[] =
{
	WEAPON::EBONY_IVORY,
	WEAPON::SHOTGUN,
	WEAPON::ARTEMIS,
	WEAPON::SPIRAL,
	WEAPON::KALINA_ANN,
};

const char * weaponSwitchTypeNames[] =
{
	"Linear",
	"Arbitrary",
};

const char * stickNames[] =
{
	"Right Stick",
	"Left Stick",
};

const char * styleRankNames[] =
{
	"None",
	"Dope",
	"Crazy",
	"Blast",
	"Alright",
	"Sweet",
	"Showtime",
	"Stylish",
};

const char * missionNames[] =
{
	"Movie",
	"Mission 1",
	"Mission 2",
	"Mission 3",
	"Mission 4",
	"Mission 5",
	"Mission 6",
	"Mission 7",
	"Mission 8",
	"Mission 9",
	"Mission 10",
	"Mission 11",
	"Mission 12",
	"Mission 13",
	"Mission 14",
	"Mission 15",
	"Mission 16",
	"Mission 17",
	"Mission 18",
	"Mission 19",
	"Mission 20",
	"Bloody Palace",
};

const char * modeNames[] =
{
	"Easy",
	"Normal",
	"Hard",
	"Very Hard",
	"Dante Must Die",
	"Heaven or Hell",
};

constexpr uint32 modes[] =
{
	MODE::EASY,
	MODE::NORMAL,
	MODE::HARD,
	MODE::VERY_HARD,
	MODE::DANTE_MUST_DIE,
	MODE::HEAVEN_OR_HELL,
};

const char * floorNames[] =
{
	"Floor 1",
	"Floor 2",
	"Floor 3",
	"Floor 4",
	"Floor 5",
	"Floor 6",
	"Floor 7",
	"Floor 8",
	"Floor 9",
	"Floor 10",
	"Cerberus",
	"Gigapede",
	"Agni & Rudra",
	"Nevan",
	"Beowulf",
	"Geryon",
	"Doppelganger",
	"Leviathan",
	"Damned Chessmen",
	"Vergil 1",
	"Vergil 2",
	"Vergil 3",
	"Lady",
	"Arkham",
	"Jester 1",
	"Jester 2",
	"Jester 3",
};

const char * sceneNames[] =
{
	"SCENE::BOOT",
	"SCENE::INTRO",
	"SCENE::MAIN",
	"SCENE::MISSION_SELECT",
	"SCENE::LOAD",
	"SCENE::GAME",
	"SCENE::CUTSCENE",
	"SCENE::MISSION_START",
	"SCENE::MISSION_RESULT",
	"SCENE::GAME_OVER",
};

const char * eventNames[] =
{
	"EVENT::INIT",
	"EVENT::MAIN",
	"EVENT::TELEPORT",
	"EVENT::PAUSE",
	"EVENT::STATUS",
	"EVENT::OPTIONS",
	"EVENT::DEATH",
	"EVENT::GET_ITEM",
	"EVENT::MESSAGE",
	"EVENT::CUSTOMIZE",
	"EVENT::SAVE",
	"EVENT::DELETE",
	"EVENT::END",
};

const char * trackFilenames[] =
{
	"Battle_00.ogg",
	"Battle_01.ogg",
	"Battle_01b.ogg",
	"Battle_02.ogg",
	"Battle_03.ogg",
	"Battle_04.ogg",
	"Battle_05.ogg",
	"Battle_06.ogg",
	"Battle_07.ogg",
	"Battle_08.ogg",
	"Battle_0a.ogg",
	"Boss_01.ogg",
	"Boss_01b.ogg",
	"Boss_02.ogg",
	"Boss_02b.ogg",
	"Boss_03.ogg",
	"Boss_03b.ogg",
	"Boss_04.ogg",
	"Boss_04b.ogg",
	"Boss_05.ogg",
	"Boss_05b.ogg",
	"Boss_06.ogg",
	"Boss_06b.ogg",
	"Boss_07.ogg",
	"Boss_08.ogg",
	"Boss_08b.ogg",
	"Boss_09.ogg",
	"Continue.ogg",
	"dummy.ogg",
	"Hine_01.ogg",
	"Hine_02.ogg",
	"Jester.ogg",
	"Jikushinzou.ogg",
	"Kaze_01.ogg",
	"Kaze_02.ogg",
	"Kaze_03.ogg",
	"Kaze_04.ogg",
	"Kaze_05.ogg",
	"Kaze_06.ogg",
	"Lady.ogg",
	"m01_c00.ogg",
	"m01_v00.ogg",
	"m01_v01.ogg",
	"m01_v02.ogg",
	"m01_v03.ogg",
	"m01_v04.ogg",
	"m01_v05.ogg",
	"m01_v06.ogg",
	"m01_v07.ogg",
	"m01_v08.ogg",
	"m01_v09.ogg",
	"m02_c01.ogg",
	"m02_s00.ogg",
	"m03_b00.ogg",
	"m03_b01.ogg",
	"m03_c00.ogg",
	"m03_s00.ogg",
	"m03_s01.ogg",
	"m04_c00.ogg",
	"m04_s00.ogg",
	"m05_b00.ogg",
	"m05_c00.ogg",
	"m05_s00.ogg",
	"m06_c00.ogg",
	"m07_b00.ogg",
	"m07_s00.ogg",
	"m08_c00.ogg",
	"m09_b00.ogg",
	"m09_b01.ogg",
	"m09_c00.ogg",
	"m10_c00.ogg",
	"m10_s00.ogg",
	"m11_b00.ogg",
	"m11_b01.ogg",
	"m11_c00.ogg",
	"m11_s00.ogg",
	"m12_b00.ogg",
	"m12_b01.ogg",
	"m12_b02.ogg",
	"m12_c00.ogg",
	"m12_s00.ogg",
	"m13_b00.ogg",
	"m13_s00.ogg",
	"m14_s01.ogg",
	"m15_c00.ogg",
	"m15_s00.ogg",
	"m16_b00.ogg",
	"m16_c00.ogg",
	"m16_s00.ogg",
	"m17_b00.ogg",
	"m17_c00.ogg",
	"m17_s00.ogg",
	"m18_c00.ogg",
	"m18_s00.ogg",
	"m19_b00.ogg",
	"m19_b01.ogg",
	"m19_s00.ogg",
	"m20_b00.ogg",
	"m20_c00.ogg",
	"m20_s00.ogg",
	"m99_c00.ogg",
	"m99_c01.ogg",
	"m99_c03.ogg",
	"Maguma.ogg",
	"Mizu_01.ogg",
	"Mizu_02.ogg",
	"M_clear.ogg",
	"m_demo_02_001.ogg",
	"m_demo_04_004.ogg",
	"m_demo_04_004v.ogg",
	"m_demo_04_014.ogg",
	"m_demo_06_007.ogg",
	"m_demo_06_011.ogg",
	"m_demo_06_012.ogg",
	"m_demo_09_003.ogg",
	"m_demo_09_003v.ogg",
	"m_demo_10_002.ogg",
	"m_demo_10_002v.ogg",
	"m_demo_10_004.ogg",
	"m_demo_10_005.ogg",
	"m_demo_12_004.ogg",
	"m_demo_12_005.ogg",
	"m_demo_15_001.ogg",
	"m_demo_15_001v.ogg",
	"m_demo_19_001.ogg",
	"m_demo_19_016.ogg",
	"M_start.ogg",
	"M_start2.ogg",
	"Nausica.ogg",
	"Option.ogg",
	"Result.ogg",
	"Room_01.ogg",
	"Sm_clear.ogg",
	"Sm_failure.ogg",
	"Staffroll.ogg",
	"Stage_01.ogg",
	"Stage_02.ogg",
	"Stage_02b.ogg",
	"Stage_03.ogg",
	"Stage_04.ogg",
	"Stage_04b.ogg",
	"Stage_05.ogg",
	"Stage_05b.ogg",
	"Stage_06.ogg",
	"Stage_07.ogg",
	"Stage_08.ogg",
	"Stage_09.ogg",
	"Torocco.ogg",
	"T_boss.ogg",
	"T_bossb.ogg",
	"Versil_01.ogg",
	"Versil_02.ogg",
	"Versil_03.ogg",
	"ZZZ.ogg",
};

const char * trackNames[] =
{
	"Battle_00",
	"Battle_01",
	"Battle_01b",
	"Battle_02",
	"Battle_03",
	"Battle_04",
	"Battle_05",
	"Battle_06",
	"Battle_07",
	"Battle_08",
	"Battle_0a",
	"Boss_01",
	"Boss_01b",
	"Boss_02",
	"Boss_02b",
	"Boss_03",
	"Boss_03b",
	"Boss_04",
	"Boss_04b",
	"Boss_05",
	"Boss_05b",
	"Boss_06",
	"Boss_06b",
	"Boss_07",
	"Boss_08",
	"Boss_08b",
	"Boss_09",
	"Continue",
	"dummy",
	"Hine_01",
	"Hine_02",
	"Jester",
	"Jikushinzou",
	"Kaze_01",
	"Kaze_02",
	"Kaze_03",
	"Kaze_04",
	"Kaze_05",
	"Kaze_06",
	"Lady",
	"m01_c00",
	"m01_v00",
	"m01_v01",
	"m01_v02",
	"m01_v03",
	"m01_v04",
	"m01_v05",
	"m01_v06",
	"m01_v07",
	"m01_v08",
	"m01_v09",
	"m02_c01",
	"m02_s00",
	"m03_b00",
	"m03_b01",
	"m03_c00",
	"m03_s00",
	"m03_s01",
	"m04_c00",
	"m04_s00",
	"m05_b00",
	"m05_c00",
	"m05_s00",
	"m06_c00",
	"m07_b00",
	"m07_s00",
	"m08_c00",
	"m09_b00",
	"m09_b01",
	"m09_c00",
	"m10_c00",
	"m10_s00",
	"m11_b00",
	"m11_b01",
	"m11_c00",
	"m11_s00",
	"m12_b00",
	"m12_b01",
	"m12_b02",
	"m12_c00",
	"m12_s00",
	"m13_b00",
	"m13_s00",
	"m14_s01",
	"m15_c00",
	"m15_s00",
	"m16_b00",
	"m16_c00",
	"m16_s00",
	"m17_b00",
	"m17_c00",
	"m17_s00",
	"m18_c00",
	"m18_s00",
	"m19_b00",
	"m19_b01",
	"m19_s00",
	"m20_b00",
	"m20_c00",
	"m20_s00",
	"m99_c00",
	"m99_c01",
	"m99_c03",
	"Maguma",
	"Mizu_01",
	"Mizu_02",
	"M_clear",
	"m_demo_02_001",
	"m_demo_04_004",
	"m_demo_04_004v",
	"m_demo_04_014",
	"m_demo_06_007",
	"m_demo_06_011",
	"m_demo_06_012",
	"m_demo_09_003",
	"m_demo_09_003v",
	"m_demo_10_002",
	"m_demo_10_002v",
	"m_demo_10_004",
	"m_demo_10_005",
	"m_demo_12_004",
	"m_demo_12_005",
	"m_demo_15_001",
	"m_demo_15_001v",
	"m_demo_19_001",
	"m_demo_19_016",
	"M_start",
	"M_start2",
	"Nausica",
	"Option",
	"Result",
	"Room_01",
	"Sm_clear",
	"Sm_failure",
	"Staffroll",
	"Stage_01",
	"Stage_02",
	"Stage_02b",
	"Stage_03",
	"Stage_04",
	"Stage_04b",
	"Stage_05",
	"Stage_05b",
	"Stage_06",
	"Stage_07",
	"Stage_08",
	"Stage_09",
	"Torocco",
	"T_boss",
	"T_bossb",
	"Versil_01",
	"Versil_02",
	"Versil_03",
	"ZZZ",
};

static_assert(countof(trackFilenames) == countof(trackNames));

#pragma endregion

#pragma region Texture

struct TextureData
{
	bool enable;
	bool run;
	const char * label;
	ID3D11ShaderResourceView * textureAddr;

	uint32 lastX;
	uint32 lastY;

	void Render
	(
		Config::TextureData & activeData,
		Config::TextureData & queuedData
	);
	void Settings
	(
		Config::TextureData & activeData,
		Config::TextureData & queuedData
	);
	void SetPosition(Config::TextureData & data);
};

void TextureData::Render
(
	Config::TextureData & activeData,
	Config::TextureData & queuedData
)
{
	if
	(
		!enable ||
		!textureAddr
	)
	{
		return;
	}

	auto & activeSize = *reinterpret_cast<ImVec2 *>(&activeData.size);
	auto & queuedSize = *reinterpret_cast<ImVec2 *>(&queuedData.size);

	auto & activePos = *reinterpret_cast<ImVec2 *>(&activeData.pos);
	auto & queuedPos = *reinterpret_cast<ImVec2 *>(&queuedData.pos);

	if (!run)
	{
		run = true;

		ImGui::SetNextWindowPos(activePos);

		lastX = static_cast<uint32>(activeData.pos.x);
		lastY = static_cast<uint32>(activeData.pos.y);
	}

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(0, 0));

	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));

	if
	(
		ImGui::Begin
		(
			label,
			&enable,
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize
		)
	)
	{
		activePos = queuedPos = ImGui::GetWindowPos();

		uint32 x = static_cast<uint32>(activeData.pos.x);
		uint32 y = static_cast<uint32>(activeData.pos.y);

		if
		(
			(lastX != x) ||
			(lastY != y)
		)
		{
			lastX = x;
			lastY = y;

			GUI_save = true;
		}

		ImGui::Image
		(
			textureAddr,
			activeSize
		);
	}

	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(4);
}

void TextureData::Settings
(
	Config::TextureData & activeData,
	Config::TextureData & queuedData
)
{
	auto & activeSize = *reinterpret_cast<ImVec2 *>(&activeData.size);
	auto & queuedSize = *reinterpret_cast<ImVec2 *>(&queuedData.size);

	auto & activePos = *reinterpret_cast<ImVec2 *>(&activeData.pos);
	auto & queuedPos = *reinterpret_cast<ImVec2 *>(&queuedData.pos);

	ImGui::Text(label);

	if constexpr (debug)
	{
		GUI_Checkbox
		(
			"Enable",
			enable
		);
	}

	ImGui::PushItemWidth(150);

	GUI_Input2<float>
	(
		"Width",
		activeSize.x,
		queuedSize.x,
		1,
		"%g",
		ImGuiInputTextFlags_EnterReturnsTrue
	);
	GUI_Input2<float>
	(
		"Height",
		activeSize.y,
		queuedSize.y,
		1,
		"%g",
		ImGuiInputTextFlags_EnterReturnsTrue
	);

	if
	(
		GUI_Input2<float>
		(
			"X",
			activePos.x,
			queuedPos.x,
			1,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		)
	)
	{
		ImGui::SetWindowPos(label, activePos);
	}
	if
	(
		GUI_Input2<float>
		(
			"Y",
			activePos.y,
			queuedPos.y,
			1,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		)
	)
	{
		ImGui::SetWindowPos(label, activePos);
	}

	ImGui::PopItemWidth();
}

void TextureData::SetPosition(Config::TextureData & data)
{
	auto & pos = *reinterpret_cast<ImVec2 *>(&data.pos);

	ImGui::SetWindowPos(label, pos);
}

enum
{
	TEXTURE_ARROW_0,
	TEXTURE_ARROW_72,
	TEXTURE_ARROW_144,
	TEXTURE_ARROW_216,
	TEXTURE_ARROW_288,
	TEXTURE_BACKGROUND,
	TEXTURE_HIGHLIGHT,
	//TEXTURE_STENCIL,
	TEXTURE_WEAPON_REBELLION,
	TEXTURE_WEAPON_REBELLION_2,
	TEXTURE_WEAPON_FORCE_EDGE,
	TEXTURE_WEAPON_CERBERUS,
	TEXTURE_WEAPON_AGNI_RUDRA,
	TEXTURE_WEAPON_NEVAN,
	TEXTURE_WEAPON_BEOWULF_DANTE,
	TEXTURE_WEAPON_EBONY_IVORY,
	TEXTURE_WEAPON_SHOTGUN,
	TEXTURE_WEAPON_ARTEMIS,
	TEXTURE_WEAPON_SPIRAL,
	TEXTURE_WEAPON_KALINA_ANN,
	TEXTURE_WEAPON_YAMATO_VERGIL,
	TEXTURE_WEAPON_YAMATO_NERO_ANGELO,
	TEXTURE_WEAPON_BEOWULF_VERGIL,
	TEXTURE_WEAPON_BEOWULF_NERO_ANGELO,
	TEXTURE_WEAPON_YAMATO_FORCE_EDGE,
	TEXTURE_COUNT,
};

const char * textureFilenames[] =
{
	"arrow_0.png",
	"arrow_72.png",
	"arrow_144.png",
	"arrow_216.png",
	"arrow_288.png",
	"background.png",
	"highlight.png",
	//"stencil.png",
	"weapon_0000_0000.png",
	"weapon_0000_0001.png",
	"weapon_0000_0002.png",
	"weapon_0001.png",
	"weapon_0002.png",
	"weapon_0003.png",
	"weapon_0004.png",
	"weapon_0005.png",
	"weapon_0006.png",
	"weapon_0007.png",
	"weapon_0008.png",
	"weapon_0009.png",
	"weapon_0011_0000.png",
	"weapon_0011_0001.png",
	"weapon_0012_0000.png",
	"weapon_0012_0001.png",
	"weapon_0013.png",
};

ID3D11ShaderResourceView * textureAddrs[TEXTURE_COUNT] = {};

constexpr uint8 textureWeaponMap[WEAPON::MAX] =
{
	TEXTURE_WEAPON_REBELLION,
	TEXTURE_WEAPON_CERBERUS,
	TEXTURE_WEAPON_AGNI_RUDRA,
	TEXTURE_WEAPON_NEVAN,
	TEXTURE_WEAPON_BEOWULF_DANTE,
	TEXTURE_WEAPON_EBONY_IVORY,
	TEXTURE_WEAPON_SHOTGUN,
	TEXTURE_WEAPON_ARTEMIS,
	TEXTURE_WEAPON_SPIRAL,
	TEXTURE_WEAPON_KALINA_ANN,
	0,
	TEXTURE_WEAPON_YAMATO_VERGIL,
	TEXTURE_WEAPON_BEOWULF_VERGIL,
	TEXTURE_WEAPON_YAMATO_FORCE_EDGE,
	0,
};

constexpr uint8 textureArrowMap[5] =
{
	TEXTURE_ARROW_0,
	TEXTURE_ARROW_288,
	TEXTURE_ARROW_216,
	TEXTURE_ARROW_144,
	TEXTURE_ARROW_72,
};

bool g_showTextures = false;

void CreateTextures()
{
	char path[128];

	old_for_all(uint8, textureIndex, TEXTURE_COUNT)
	{
		snprintf
		(
			path,
			sizeof(path),
			"images/%s",
			textureFilenames[textureIndex]
		);

		textureAddrs[textureIndex] = CreateTexture
		(
			path,
			::D3D11::device
		);
	}
}

//TextureData stencil = {};

#pragma endregion

#pragma region Weapon Switch Controllers

struct WeaponSwitchControllerTextureData
{
	TextureData backgrounds[5];
	TextureData icons[5];
	TextureData highlights[5];
	TextureData arrow;
};

WeaponSwitchControllerTextureData meleeWeaponSwitchControllerTextureData = {};

const char * meleeWeaponSwitchControllerBackgroundNames[5] =
{
	"MeleeWeaponSwitchControllerBackground0",
	"MeleeWeaponSwitchControllerBackground1",
	"MeleeWeaponSwitchControllerBackground2",
	"MeleeWeaponSwitchControllerBackground3",
	"MeleeWeaponSwitchControllerBackground4",
};

const char * meleeWeaponSwitchControllerIconNames[5] =
{
	"MeleeWeaponSwitchControllerIcon0",
	"MeleeWeaponSwitchControllerIcon1",
	"MeleeWeaponSwitchControllerIcon2",
	"MeleeWeaponSwitchControllerIcon3",
	"MeleeWeaponSwitchControllerIcon4",
};

const char * meleeWeaponSwitchControllerHighlightNames[5] =
{
	"MeleeWeaponSwitchControllerHighlight0",
	"MeleeWeaponSwitchControllerHighlight1",
	"MeleeWeaponSwitchControllerHighlight2",
	"MeleeWeaponSwitchControllerHighlight3",
	"MeleeWeaponSwitchControllerHighlight4",
};

const char * meleeWeaponSwitchControllerArrowName = "MeleeWeaponSwitchControllerArrow";



WeaponSwitchControllerTextureData rangedWeaponSwitchControllerTextureData = {};

const char * rangedWeaponSwitchControllerBackgroundNames[5] =
{
	"RangedWeaponSwitchControllerBackground0",
	"RangedWeaponSwitchControllerBackground1",
	"RangedWeaponSwitchControllerBackground2",
	"RangedWeaponSwitchControllerBackground3",
	"RangedWeaponSwitchControllerBackground4",
};

const char * rangedWeaponSwitchControllerIconNames[5] =
{
	"RangedWeaponSwitchControllerIcon0",
	"RangedWeaponSwitchControllerIcon1",
	"RangedWeaponSwitchControllerIcon2",
	"RangedWeaponSwitchControllerIcon3",
	"RangedWeaponSwitchControllerIcon4",
};

const char * rangedWeaponSwitchControllerHighlightNames[5] =
{
	"RangedWeaponSwitchControllerHighlight0",
	"RangedWeaponSwitchControllerHighlight1",
	"RangedWeaponSwitchControllerHighlight2",
	"RangedWeaponSwitchControllerHighlight3",
	"RangedWeaponSwitchControllerHighlight4",
};

const char * rangedWeaponSwitchControllerArrowName = "RangedWeaponSwitchControllerArrow";


// @Todo: Templates.
void MeleeWeaponSwitchController()
{
	auto & textureData = meleeWeaponSwitchControllerTextureData;
	auto & activeConfigTextureData = activeConfig.meleeWeaponSwitchControllerTextureData;
	auto & queuedConfigTextureData = queuedConfig.meleeWeaponSwitchControllerTextureData;

	if (g_showTextures)
	{
		old_for_all(uint8, index, 5)
		{
			textureData.backgrounds[index].Render
			(
				activeConfigTextureData.backgrounds[index],
				queuedConfigTextureData.backgrounds[index]
			);
		}

		{
			constexpr uint8 textureIds[5] =
			{
				TEXTURE_WEAPON_REBELLION,
				TEXTURE_WEAPON_CERBERUS,
				TEXTURE_WEAPON_AGNI_RUDRA,
				TEXTURE_WEAPON_NEVAN,
				TEXTURE_WEAPON_BEOWULF_DANTE,
			};

			old_for_all(uint8, index, 5)
			{
				auto textureId = textureIds[index];
				if (textureId >= TEXTURE_COUNT)
				{
					textureId = 0;
				}

				textureData.icons[index].textureAddr = textureAddrs[textureId];

				textureData.icons[index].Render
				(
					activeConfigTextureData.icons[index],
					queuedConfigTextureData.icons[index]
				);
			}
		}

		textureData.highlights[0].Render
		(
			activeConfigTextureData.highlights[0],
			queuedConfigTextureData.highlights[0]
		);

		{
			textureData.arrow.textureAddr = textureAddrs[TEXTURE_ARROW_0];

			textureData.arrow.Render
			(
				activeConfigTextureData.arrow,
				queuedConfigTextureData.arrow
			);
		}

		if (activeConfig.forceIconFocus)
		{
			ImGui::SetWindowFocus(textureData.icons[0].label);
		}

		return;
	}



	IntroduceSessionData();

	if (!InGame())
	{
		return;
	}

	IntroduceMainActorData(actorData, return);

	auto & characterData = GetCharacterData(actorData);

	auto & gamepad = GetGamepad(actorData.newPlayerIndex);

	if
	(
		InCutscene() ||
		InCredits() ||
		!activeConfig.Actor.enable ||
		(characterData.meleeWeaponSwitchType != WEAPON_SWITCH_TYPE::ARBITRARY) ||
		!(
			(characterData.character == CHARACTER::DANTE ) ||
			(characterData.character == CHARACTER::VERGIL)
		)
	)
	{
		return;
	}

	if (!(gamepad.buttons[0] & GetBinding(BINDING::CHANGE_DEVIL_ARMS)))
	{
		return;
	}

	auto count = characterData.meleeWeaponCount;

	if (characterData.character == CHARACTER::VERGIL)
	{
		count = (IsNeroAngelo(actorData)) ? 2 : 3;
	}

	old_for_all(uint8, index, count)
	{
		textureData.backgrounds[index].Render
		(
			activeConfigTextureData.backgrounds[index],
			queuedConfigTextureData.backgrounds[index]
		);
	}

	{
		old_for_all(uint8, index, count)
		{
			auto weapon = characterData.meleeWeapons[index];
			if (weapon >= WEAPON::MAX)
			{
				weapon = 0;
			}

			auto textureId = textureWeaponMap[weapon];
			if (textureId >= TEXTURE_COUNT)
			{
				textureId = 0;
			}

			switch (weapon)
			{
				case WEAPON::REBELLION:
				{
					if (sessionData.unlockDevilTrigger)
					{
						textureId = TEXTURE_WEAPON_REBELLION_2;
					}

					if (actorData.sparda)
					{
						textureId = TEXTURE_WEAPON_FORCE_EDGE;
					}

					break;
				}
				case WEAPON::YAMATO_VERGIL:
				{
					if (IsNeroAngelo(actorData))
					{
						textureId = TEXTURE_WEAPON_YAMATO_NERO_ANGELO;
					}

					break;
				}
				case WEAPON::BEOWULF_VERGIL:
				{
					if (IsNeroAngelo(actorData))
					{
						textureId = TEXTURE_WEAPON_BEOWULF_NERO_ANGELO;
					}

					break;
				}
			}

			textureData.icons[index].textureAddr = textureAddrs[textureId];

			textureData.icons[index].Render
			(
				activeConfigTextureData.icons[index],
				queuedConfigTextureData.icons[index]
			);
		}
	}

	auto meleeWeaponIndex = characterData.meleeWeaponIndex;
	if (meleeWeaponIndex >= 5)
	{
		meleeWeaponIndex = 0;
	}

	textureData.highlights[meleeWeaponIndex].Render
	(
		activeConfigTextureData.highlights[meleeWeaponIndex],
		queuedConfigTextureData.highlights[meleeWeaponIndex]
	);

	{
		auto textureId = textureArrowMap[meleeWeaponIndex];

		textureData.arrow.textureAddr = textureAddrs[textureId];

		textureData.arrow.Render
		(
			activeConfigTextureData.arrow,
			queuedConfigTextureData.arrow
		);
	}

	if (activeConfig.forceIconFocus)
	{
		ImGui::SetWindowFocus(textureData.icons[meleeWeaponIndex].label);
	}
}

void RangedWeaponSwitchController()
{
	auto & textureData = rangedWeaponSwitchControllerTextureData;
	auto & activeConfigTextureData = activeConfig.rangedWeaponSwitchControllerTextureData;
	auto & queuedConfigTextureData = queuedConfig.rangedWeaponSwitchControllerTextureData;

	if (g_showTextures)
	{
		old_for_all(uint8, index, 5)
		{
			textureData.backgrounds[index].Render
			(
				activeConfigTextureData.backgrounds[index],
				queuedConfigTextureData.backgrounds[index]
			);
		}

		{
			constexpr uint8 textureIds[5] =
			{
				TEXTURE_WEAPON_EBONY_IVORY,
				TEXTURE_WEAPON_SHOTGUN,
				TEXTURE_WEAPON_ARTEMIS,
				TEXTURE_WEAPON_SPIRAL,
				TEXTURE_WEAPON_KALINA_ANN,
			};

			old_for_all(uint8, index, 5)
			{
				auto textureId = textureIds[index];
				if (textureId >= TEXTURE_COUNT)
				{
					textureId = 0;
				}

				textureData.icons[index].textureAddr = textureAddrs[textureId];

				textureData.icons[index].Render
				(
					activeConfigTextureData.icons[index],
					queuedConfigTextureData.icons[index]
				);
			}
		}

		textureData.highlights[0].Render
		(
			activeConfigTextureData.highlights[0],
			queuedConfigTextureData.highlights[0]
		);

		{
			textureData.arrow.textureAddr = textureAddrs[TEXTURE_ARROW_0];

			textureData.arrow.Render
			(
				activeConfigTextureData.arrow,
				queuedConfigTextureData.arrow
			);
		}

		if (activeConfig.forceIconFocus)
		{
			ImGui::SetWindowFocus(textureData.icons[0].label);
		}

		return;
	}



	IntroduceSessionData();

	if (!InGame())
	{
		return;
	}

	IntroduceMainActorData(actorData, return);

	auto & characterData = GetCharacterData(actorData);

	auto & gamepad = GetGamepad(actorData.newPlayerIndex);

	if
	(
		InCutscene() ||
		InCredits() ||
		!activeConfig.Actor.enable ||
		(characterData.rangedWeaponSwitchType != WEAPON_SWITCH_TYPE::ARBITRARY) ||
		(characterData.character != CHARACTER::DANTE)
	)
	{
		return;
	}

	if (!(gamepad.buttons[0] & GetBinding(BINDING::CHANGE_GUN)))
	{
		return;
	}

	auto count = characterData.rangedWeaponCount;

	old_for_all(uint8, index, count)
	{
		textureData.backgrounds[index].Render
		(
			activeConfigTextureData.backgrounds[index],
			queuedConfigTextureData.backgrounds[index]
		);
	}

	{
		old_for_all(uint8, index, count)
		{
			auto weapon = characterData.rangedWeapons[index];
			if (weapon >= WEAPON::MAX)
			{
				weapon = 0;
			}

			auto textureId = textureWeaponMap[weapon];
			if (textureId >= TEXTURE_COUNT)
			{
				textureId = 0;
			}

			textureData.icons[index].textureAddr = textureAddrs[textureId];

			textureData.icons[index].Render
			(
				activeConfigTextureData.icons[index],
				queuedConfigTextureData.icons[index]
			);
		}
	}

	auto rangedWeaponIndex = characterData.rangedWeaponIndex;
	if (rangedWeaponIndex >= 5)
	{
		rangedWeaponIndex = 0;
	}

	textureData.highlights[rangedWeaponIndex].Render
	(
		activeConfigTextureData.highlights[rangedWeaponIndex],
		queuedConfigTextureData.highlights[rangedWeaponIndex]
	);

	{
		auto textureId = textureArrowMap[rangedWeaponIndex];

		textureData.arrow.textureAddr = textureAddrs[textureId];

		textureData.arrow.Render
		(
			activeConfigTextureData.arrow,
			queuedConfigTextureData.arrow
		);
	}

	if (activeConfig.forceIconFocus)
	{
		ImGui::SetWindowFocus(textureData.icons[rangedWeaponIndex].label);
	}
}

void WeaponSwitchController()
{
	static bool run = false;
	if (!run)
	{
		run = true;

		// Melee
		{
			auto & textureData = meleeWeaponSwitchControllerTextureData;

			old_for_all(uint8, index, 5)
			{
				textureData.backgrounds[index] =
				{
					true,
					false,
					meleeWeaponSwitchControllerBackgroundNames[index],
					textureAddrs[TEXTURE_BACKGROUND]
				};
			}

			old_for_all(uint8, index, 5)
			{
				textureData.icons[index] =
				{
					true,
					false,
					meleeWeaponSwitchControllerIconNames[index]
				};
			}

			old_for_all(uint8, index, 5)
			{
				textureData.highlights[index] =
				{
					true,
					false,
					meleeWeaponSwitchControllerHighlightNames[index],
					textureAddrs[TEXTURE_HIGHLIGHT]
				};
			}

			textureData.arrow =
			{
				true,
				false,
				meleeWeaponSwitchControllerArrowName
			};
		}

		// Ranged
		{
			auto & textureData = rangedWeaponSwitchControllerTextureData;

			old_for_all(uint8, index, 5)
			{
				textureData.backgrounds[index] =
				{
					true,
					false,
					rangedWeaponSwitchControllerBackgroundNames[index],
					textureAddrs[TEXTURE_BACKGROUND]
				};
			}

			old_for_all(uint8, index, 5)
			{
				textureData.icons[index] =
				{
					true,
					false,
					rangedWeaponSwitchControllerIconNames[index]
				};
			}

			old_for_all(uint8, index, 5)
			{
				textureData.highlights[index] =
				{
					true,
					false,
					rangedWeaponSwitchControllerHighlightNames[index],
					textureAddrs[TEXTURE_HIGHLIGHT]
				};
			}

			textureData.arrow =
			{
				true,
				false,
				rangedWeaponSwitchControllerArrowName
			};
		}
	}

	MeleeWeaponSwitchController();
	RangedWeaponSwitchController();
}

void UpdateWeaponSwitchControllerTexturePositions()
{
	// Melee
	{
		auto & textureData = meleeWeaponSwitchControllerTextureData;
		auto & configTextureData = activeConfig.meleeWeaponSwitchControllerTextureData;

		old_for_all(uint8, index, 5)
		{
			textureData.backgrounds[index].SetPosition(configTextureData.backgrounds[index]);
		}

		old_for_all(uint8, index, 5)
		{
			textureData.highlights[index].SetPosition(configTextureData.highlights[index]);
		}


		old_for_all(uint8, index, 5)
		{
			textureData.icons[index].SetPosition(configTextureData.icons[index]);
		}

		textureData.arrow.SetPosition(configTextureData.arrow);
	}

	// Ranged
	{
		auto & textureData = rangedWeaponSwitchControllerTextureData;
		auto & configTextureData = activeConfig.rangedWeaponSwitchControllerTextureData;

		old_for_all(uint8, index, 5)
		{
			textureData.backgrounds[index].SetPosition(configTextureData.backgrounds[index]);
		}

		old_for_all(uint8, index, 5)
		{
			textureData.icons[index].SetPosition(configTextureData.icons[index]);
		}

		old_for_all(uint8, index, 5)
		{
			textureData.highlights[index].SetPosition(configTextureData.highlights[index]);
		}

		textureData.arrow.SetPosition(configTextureData.arrow);
	}
}

void WeaponSwitchControllerSettings()
{
	if (GUI_ResetButton())
	{
		ResetConfig(meleeWeaponSwitchControllerTextureData);
		ResetConfig(rangedWeaponSwitchControllerTextureData);

		UpdateWeaponSwitchControllerTexturePositions();

		ResetConfig(forceIconFocus);
	}
	ImGui::Text("");

	GUI_Checkbox2
	(
		"Force Icon Focus",
		activeConfig.forceIconFocus,
		queuedConfig.forceIconFocus
	);
	ImGui::Text("");

	GUI_Checkbox
	(
		"Show Textures",
		g_showTextures
	);
	ImGui::Text("");

	const float defaultWidth = 1920;
	const float defaultHeight = 1080;

	static float targetWidth = 1280;
	static float targetHeight = 720;

	ImGui::PushItemWidth(200);

	GUI_Input
	(
		"Target Width",
		targetWidth,
		1.0f,
		"%g"
	);

	GUI_Input
	(
		"Target Height",
		targetHeight,
		1.0f,
		"%g"
	);

	if (GUI_Button("Update"))
	{
		// Melee
		{
			const float multiplier = (targetWidth / defaultWidth);

			CopyMemory
			(
				&queuedConfig.meleeWeaponSwitchControllerTextureData,
				&defaultConfig.meleeWeaponSwitchControllerTextureData,
				sizeof(queuedConfig.meleeWeaponSwitchControllerTextureData)
			);

			auto & configTextureData = queuedConfig.meleeWeaponSwitchControllerTextureData;

			auto values = reinterpret_cast<float *>(&configTextureData);
			uint32 count = (sizeof(configTextureData) / 4);

			old_for_all(uint32, index, count)
			{
				auto & value = values[index];

				value *= multiplier;
			}

			CopyMemory
			(
				&activeConfig.meleeWeaponSwitchControllerTextureData,
				&queuedConfig.meleeWeaponSwitchControllerTextureData,
				sizeof(activeConfig.meleeWeaponSwitchControllerTextureData)
			);
		}

		// Ranged
		{
			const float multiplier = (targetWidth / defaultWidth);

			CopyMemory
			(
				&queuedConfig.rangedWeaponSwitchControllerTextureData,
				&defaultConfig.rangedWeaponSwitchControllerTextureData,
				sizeof(queuedConfig.rangedWeaponSwitchControllerTextureData)
			);

			auto & configTextureData = queuedConfig.rangedWeaponSwitchControllerTextureData;

			auto values = reinterpret_cast<float *>(&configTextureData);
			uint32 count = (sizeof(configTextureData) / 4);

			old_for_all(uint32, index, count)
			{
				auto & value = values[index];

				value *= multiplier;
			}

			CopyMemory
			(
				&activeConfig.rangedWeaponSwitchControllerTextureData,
				&queuedConfig.rangedWeaponSwitchControllerTextureData,
				sizeof(activeConfig.rangedWeaponSwitchControllerTextureData)
			);
		}

		UpdateWeaponSwitchControllerTexturePositions();

		GUI_save = true;
	}
	ImGui::Text("");

	ImGui::PopItemWidth();



	// Melee
	{
		auto & textureData = meleeWeaponSwitchControllerTextureData;
		auto & activeConfigTextureData = activeConfig.meleeWeaponSwitchControllerTextureData;
		auto & queuedConfigTextureData = queuedConfig.meleeWeaponSwitchControllerTextureData;

		old_for_all(uint8, index, 5)
		{
			textureData.backgrounds[index].Settings
			(
				activeConfigTextureData.backgrounds[index],
				queuedConfigTextureData.backgrounds[index]
			);
			ImGui::Text("");
		}

		old_for_all(uint8, index, 5)
		{
			textureData.icons[index].Settings
			(
				activeConfigTextureData.icons[index],
				queuedConfigTextureData.icons[index]
			);
			ImGui::Text("");
		}

		old_for_all(uint8, index, 5)
		{
			textureData.highlights[index].Settings
			(
				activeConfigTextureData.highlights[index],
				queuedConfigTextureData.highlights[index]
			);
			ImGui::Text("");
		}

		textureData.arrow.Settings
		(
			activeConfigTextureData.arrow,
			queuedConfigTextureData.arrow
		);
		ImGui::Text("");
	}

	// Ranged
	{
		auto & textureData = rangedWeaponSwitchControllerTextureData;
		auto & activeConfigTextureData = activeConfig.rangedWeaponSwitchControllerTextureData;
		auto & queuedConfigTextureData = queuedConfig.rangedWeaponSwitchControllerTextureData;

		old_for_all(uint8, index, 5)
		{
			textureData.backgrounds[index].Settings
			(
				activeConfigTextureData.backgrounds[index],
				queuedConfigTextureData.backgrounds[index]
			);
			ImGui::Text("");
		}

		old_for_all(uint8, index, 5)
		{
			textureData.icons[index].Settings
			(
				activeConfigTextureData.icons[index],
				queuedConfigTextureData.icons[index]
			);
			ImGui::Text("");
		}

		old_for_all(uint8, index, 5)
		{
			textureData.highlights[index].Settings
			(
				activeConfigTextureData.highlights[index],
				queuedConfigTextureData.highlights[index]
			);
			ImGui::Text("");
		}

		textureData.arrow.Settings
		(
			activeConfigTextureData.arrow,
			queuedConfigTextureData.arrow
		);
	}
}

#pragma endregion

#pragma region Actor

uint8 Actor_buttonIndices[PLAYER_COUNT] = {};

uint8 Actor_collisionGroupIndices[PLAYER_COUNT] = {};

uint8 Actor_newCharacterIndices[PLAYER_COUNT][CHARACTER_COUNT][ENTITY_COUNT] = {};

uint8 Actor_styleButtonIndices[PLAYER_COUNT][CHARACTER_COUNT][ENTITY_COUNT][STYLE_COUNT] = {};
uint8 Actor_styleIndices[PLAYER_COUNT][CHARACTER_COUNT][ENTITY_COUNT][STYLE_COUNT][2] = {};

uint8 Actor_meleeWeaponIndices[PLAYER_COUNT][CHARACTER_COUNT][ENTITY_COUNT][MELEE_WEAPON_COUNT] = {};
uint8 Actor_rangedWeaponIndices[PLAYER_COUNT][CHARACTER_COUNT][ENTITY_COUNT][RANGED_WEAPON_COUNT] = {};

uint8 Actor_removeBusyFlagButtonIndices[PLAYER_COUNT][4] = {};



void Actor_UpdateIndices()
{
	old_for_all(uint8, playerIndex, PLAYER_COUNT)
	{
		auto & activePlayerData = GetActivePlayerData(playerIndex);
		auto & queuedPlayerData = GetQueuedPlayerData(playerIndex);



		UpdateMapIndex
		(
			collisionGroups,
			Actor_collisionGroupIndices[playerIndex],
			queuedPlayerData.collisionGroup
		);

		UpdateMapIndex
		(
			buttons,
			Actor_buttonIndices[playerIndex],
			activePlayerData.button
		);

		old_for_all(uint8, characterIndex, CHARACTER_COUNT){
		old_for_all(uint8, entityIndex   , ENTITY_COUNT   )
		{
			auto & activeCharacterData = GetActiveCharacterData(playerIndex, characterIndex, entityIndex);
			auto & queuedCharacterData = GetQueuedCharacterData(playerIndex, characterIndex, entityIndex);



			UpdateMapIndex
			(
				newCharacters,
				Actor_newCharacterIndices[playerIndex][characterIndex][entityIndex],
				queuedCharacterData.character
			);



			old_for_all(uint8, styleIndex, STYLE_COUNT)
			{
				UpdateMapIndex
				(
					buttons,
					Actor_styleButtonIndices[playerIndex][characterIndex][entityIndex][styleIndex],
					queuedCharacterData.styleButtons[styleIndex]
				);

				switch (queuedCharacterData.character)
				{
					case CHARACTER::DANTE:
					{
						UpdateMapIndex
						(
							stylesDante,
							Actor_styleIndices[playerIndex][characterIndex][entityIndex][styleIndex][0],
							queuedCharacterData.styles[styleIndex][0]
						);
						UpdateMapIndex
						(
							stylesDante,
							Actor_styleIndices[playerIndex][characterIndex][entityIndex][styleIndex][1],
							queuedCharacterData.styles[styleIndex][1]
						);

						break;
					}
					case CHARACTER::VERGIL:
					{
						UpdateMapIndex
						(
							stylesVergil,
							Actor_styleIndices[playerIndex][characterIndex][entityIndex][styleIndex][0],
							queuedCharacterData.styles[styleIndex][0]
						);
						UpdateMapIndex
						(
							stylesVergil,
							Actor_styleIndices[playerIndex][characterIndex][entityIndex][styleIndex][1],
							queuedCharacterData.styles[styleIndex][1]
						);

						break;
					}
				}
			}

			if (queuedCharacterData.character != CHARACTER::DANTE)
			{
				continue;
			}

			old_for_all(uint8, meleeWeaponIndex, MELEE_WEAPON_COUNT_DANTE)
			{
				UpdateMapIndex
				(
					meleeWeaponsDante,
					Actor_meleeWeaponIndices[playerIndex][characterIndex][entityIndex][meleeWeaponIndex],
					queuedCharacterData.meleeWeapons[meleeWeaponIndex]
				);
			}

			old_for_all(uint8, rangedWeaponIndex, RANGED_WEAPON_COUNT_DANTE)
			{
				UpdateMapIndex
				(
					rangedWeaponsDante,
					Actor_rangedWeaponIndices[playerIndex][characterIndex][entityIndex][rangedWeaponIndex],
					queuedCharacterData.rangedWeapons[rangedWeaponIndex]
				);
			}
		}}



		old_for_all(uint8, buttonIndex, 4)
		{
			UpdateMapIndex
			(
				buttons,
				Actor_removeBusyFlagButtonIndices[playerIndex][buttonIndex],
				activePlayerData.removeBusyFlagButtons[buttonIndex]
			);
		}
	}
}

void Actor_CharacterTab
(
	uint8 playerIndex,
	uint8 characterIndex,
	uint8 entityIndex
)
{
	auto & activeCharacterData = GetActiveCharacterData(playerIndex, characterIndex, entityIndex);
	auto & queuedCharacterData = GetQueuedCharacterData(playerIndex, characterIndex, entityIndex);

	auto & mainActiveCharacterData = GetActiveCharacterData(playerIndex, characterIndex, ENTITY::MAIN);
	auto & mainQueuedCharacterData = GetQueuedCharacterData(playerIndex, characterIndex, ENTITY::MAIN);



	if
	(
		(entityIndex == ENTITY::CLONE) &&
		(mainQueuedCharacterData.character >= CHARACTER::MAX)
	)
	{
		return;
	}



	ImGui::Text(entityNames[entityIndex]);
	ImGui::Text("");

	ImGui::PushItemWidth(150);

	if
	(
		(playerIndex == 0) &&
		(characterIndex > 0)
	)
	{
		if
		(
			GUI_ComboMap
			(
				"Character",
				newCharacterNames,
				newCharacters,
				Actor_newCharacterIndices[playerIndex][characterIndex][entityIndex],
				queuedCharacterData.character
			)
		)
		{
			ApplyDefaultCharacterData(queuedCharacterData, queuedCharacterData.character);

			Actor_UpdateIndices();
		}
	}
	else
	{
		if
		(
			GUI_Combo
			(
				"Character",
				characterNames,
				queuedCharacterData.character
			)
		)
		{
			ApplyDefaultCharacterData(queuedCharacterData, queuedCharacterData.character);

			Actor_UpdateIndices();
		}
	}

	ImGui::PopItemWidth();



	if
	(
		!(
			(queuedCharacterData.character == CHARACTER::DANTE ) ||
			(queuedCharacterData.character == CHARACTER::VERGIL)
		)
	)
	{
		return;
	}



	ImGui::PushItemWidth(150.0f);

	// Costume
	{
		bool condition = queuedCharacterData.ignoreCostume;

		GUI_PushDisable(condition);

		GUI_Input
		(
			"Costume",
			queuedCharacterData.costume
		);

		GUI_PopDisable(condition);

		ImGui::SameLine();

		GUI_Checkbox
		(
			"Ignore",
			queuedCharacterData.ignoreCostume
		);
	}

	GUI_Checkbox
	(
		"Force Files",
		queuedCharacterData.forceFiles
	);

	{
		bool condition = !queuedCharacterData.forceFiles;

		GUI_PushDisable(condition);

		GUI_Combo
		(
			"Character",
			characterNames,
			queuedCharacterData.forceFilesCharacter
		);

		GUI_Input
		(
			"Costume",
			queuedCharacterData.forceFilesCostume
		);

		GUI_PopDisable(condition);
	}
	ImGui::Text("");



	ImGui::Text("Styles");

	old_for_all(uint8, styleIndex, STYLE_COUNT)
	{
		if constexpr (debug)
		{
			ImGui::Text("");
			ImGui::Text("%u", styleIndex);
		}

		GUI_ComboMap
		(
			"",
			buttonNames,
			buttons,
			Actor_styleButtonIndices[playerIndex][characterIndex][entityIndex][styleIndex],
			queuedCharacterData.styleButtons[styleIndex],
			ImGuiComboFlags_HeightLargest
		);

		if constexpr (!debug)
		{
			ImGui::SameLine();
		}

		switch (queuedCharacterData.character)
		{
			case CHARACTER::DANTE:
			{
				GUI_ComboMap
				(
					"",
					styleNamesDante,
					stylesDante,
					Actor_styleIndices[playerIndex][characterIndex][entityIndex][styleIndex][0],
					queuedCharacterData.styles[styleIndex][0]
				);

				if constexpr (!debug)
				{
					ImGui::SameLine();
				}

				GUI_ComboMap
				(
					"",
					styleNamesDante,
					stylesDante,
					Actor_styleIndices[playerIndex][characterIndex][entityIndex][styleIndex][1],
					queuedCharacterData.styles[styleIndex][1]
				);

				break;
			}
			case CHARACTER::VERGIL:
			{
				GUI_ComboMap
				(
					"",
					styleNamesVergil,
					stylesVergil,
					Actor_styleIndices[playerIndex][characterIndex][entityIndex][styleIndex][0],
					queuedCharacterData.styles[styleIndex][0]
				);

				if constexpr (!debug)
				{
					ImGui::SameLine();
				}

				GUI_ComboMap
				(
					"",
					styleNamesVergil,
					stylesVergil,
					Actor_styleIndices[playerIndex][characterIndex][entityIndex][styleIndex][1],
					queuedCharacterData.styles[styleIndex][1]
				);

				break;
			}
		}
	}

	ImGui::PopItemWidth();



	if
	(
		(
			(playerIndex == 0) &&
			(entityIndex == ENTITY::MAIN)
		) ||
		(queuedCharacterData.character == CHARACTER::DANTE)
	)
	{
		ImGui::Text("");
		ImGui::Text("Melee Weapons");
	}



	if
	(
		(playerIndex == 0) &&
		(entityIndex == ENTITY::MAIN)
	)
	{
		ImGui::PushItemWidth(200.0f);

		GUI_Combo
		(
			"",
			weaponSwitchTypeNames,
			queuedCharacterData.meleeWeaponSwitchType
		);
		ImGui::SameLine();

		switch (queuedCharacterData.meleeWeaponSwitchType)
		{
			case WEAPON_SWITCH_TYPE::LINEAR:
			{
				TooltipHelper
				(
					"(?)",
					"You can hold the taunt button during the switch to go back."
				);

				break;
			}
			case WEAPON_SWITCH_TYPE::ARBITRARY:
			{
				TooltipHelper
				(
					"(?)",
					"Hold the weapon switch button and select a weapon with the stick."
				);

				GUI_Combo
				(
					"",
					stickNames,
					queuedCharacterData.meleeWeaponSwitchStick
				);

				break;
			}
		}

		ImGui::PopItemWidth();
	}



	if (queuedCharacterData.character != CHARACTER::DANTE)
	{
		return;
	}



	ImGui::PushItemWidth(200.0f);

	GUI_Slider<uint8>
	(
		"",
		queuedCharacterData.meleeWeaponCount,
		1,
		MELEE_WEAPON_COUNT_DANTE
	);

	old_for_all(uint8, meleeWeaponIndex, MELEE_WEAPON_COUNT_DANTE)
	{
		bool condition = (meleeWeaponIndex >= queuedCharacterData.meleeWeaponCount);

		GUI_PushDisable(condition);

		GUI_ComboMap
		(
			"",
			meleeWeaponNamesDante,
			meleeWeaponsDante,
			Actor_meleeWeaponIndices[playerIndex][characterIndex][entityIndex][meleeWeaponIndex],
			queuedCharacterData.meleeWeapons[meleeWeaponIndex]
		);

		GUI_PopDisable(condition);
	}
	ImGui::Text("");



	ImGui::Text("Ranged Weapons");

	if
	(
		(playerIndex == 0) &&
		(entityIndex == ENTITY::MAIN)
	)
	{
		GUI_Combo
		(
			"",
			weaponSwitchTypeNames,
			queuedCharacterData.rangedWeaponSwitchType
		);

		ImGui::SameLine();

		switch (queuedCharacterData.rangedWeaponSwitchType)
		{
			case WEAPON_SWITCH_TYPE::LINEAR:
			{
				TooltipHelper
				(
					"(?)",
					"Hold the taunt button during the switch to go back."
				);

				break;
			}
			case WEAPON_SWITCH_TYPE::ARBITRARY:
			{
				TooltipHelper
				(
					"(?)",
					"Hold the weapon switch button and select a weapon with the stick."
				);

				GUI_Combo
				(
					"",
					stickNames,
					queuedCharacterData.rangedWeaponSwitchStick
				);

				break;
			}
		}
	}

	GUI_Slider<uint8>
	(
		"",
		queuedCharacterData.rangedWeaponCount,
		1,
		RANGED_WEAPON_COUNT_DANTE
	);

	old_for_all(uint8, rangedWeaponIndex, RANGED_WEAPON_COUNT_DANTE)
	{
		bool condition = (rangedWeaponIndex >= queuedCharacterData.rangedWeaponCount);

		GUI_PushDisable(condition);

		GUI_ComboMap
		(
			"",
			rangedWeaponNamesDante,
			rangedWeaponsDante,
			Actor_rangedWeaponIndices[playerIndex][characterIndex][entityIndex][rangedWeaponIndex],
			queuedCharacterData.rangedWeapons[rangedWeaponIndex]
		);

		GUI_PopDisable(condition);
	}

	ImGui::PopItemWidth();
}

void Actor_PlayerTab(uint8 playerIndex)
{
	auto & activePlayerData = GetActivePlayerData(playerIndex);
	auto & queuedPlayerData = GetQueuedPlayerData(playerIndex);



	ImGui::PushItemWidth(200.0f);

	{
		bool condition = (playerIndex == 0);
		// bool condition = false;

		GUI_PushDisable(condition);

		GUI_ComboMap
		(
			"Collision Group",
			collisionGroupNames,
			collisionGroups,
			Actor_collisionGroupIndices[playerIndex],
			queuedPlayerData.collisionGroup
		);

		GUI_PopDisable(condition);
	}
	ImGui::Text("");



	GUI_ComboMap2
	(
		"Button",
		buttonNames,
		buttons,
		Actor_buttonIndices[playerIndex],
		activePlayerData.button,
		queuedPlayerData.button,
		ImGuiComboFlags_HeightLargest
	);
	ImGui::SameLine();
	TooltipHelper
	(
		"(?)",
		"Multi-purpose button.\n"
		"Main purpose is to switch characters.\n"
		"While Doppelganger is active it's used to control the clone's state.\n"
		"Hold the button and switch style or weapon to trigger the action for the clone.\n"
	);
	ImGui::Text("");

	GUI_Slider<uint8>
	(
		"Character Count",
		queuedPlayerData.characterCount,
		1,
		CHARACTER_COUNT
	);
	ImGui::Text("");

	ImGui::PopItemWidth();



	if (ImGui::BeginTabBar("CharacterTabs"))
	{
		old_for_all(uint8, characterIndex, CHARACTER_COUNT)
		{
			auto condition = (characterIndex >= queuedPlayerData.characterCount);

			GUI_PushDisable(condition);

			if (ImGui::BeginTabItem(characterIndexNames[characterIndex]))
			{
				ImGui::Text("");

				old_for_all(uint8, entityIndex, ENTITY_COUNT)
				{
					Actor_CharacterTab
					(
						playerIndex,
						characterIndex,
						entityIndex
					);

					ImGui::Text("");
				}

				ImGui::EndTabItem();
			}

			GUI_PopDisable(condition);
		}

		ImGui::EndTabBar();
	}

	GUI_SectionEnd(SectionFlags_NoNewLine);
	ImGui::Text("");



	GUI_Checkbox2
	(
		"Remove Busy Flag",
		activePlayerData.removeBusyFlag,
		queuedPlayerData.removeBusyFlag
	);
	ImGui::SameLine();
	TooltipHelper
	(
		"(?)",
		"Removes the actor's busy flag which allows you to do insane combos or just look stupid."
	);
	ImGui::Text("");


	if (GUI_Button("Reset"))
	{
		ResetConfig(Actor.playerData[playerIndex].removeBusyFlag);
		ResetConfig(Actor.playerData[playerIndex].removeBusyFlagButtons);

		Actor_UpdateIndices();
	}
	ImGui::Text("");


	{
		bool condition = !activePlayerData.removeBusyFlag;

		GUI_PushDisable(condition);

		ImGui::PushItemWidth(200.0f);

		old_for_all(uint8, buttonIndex, 4)
		{
			GUI_ComboMap2
			(
				buttonIndexNames[buttonIndex],
				buttonNames,
				buttons,
				Actor_removeBusyFlagButtonIndices[playerIndex][buttonIndex],
				activePlayerData.removeBusyFlagButtons[buttonIndex],
				queuedPlayerData.removeBusyFlagButtons[buttonIndex],
				ImGuiComboFlags_HeightLargest
			);
		}

		ImGui::PopItemWidth();

		GUI_PopDisable(condition);
	}
}

void ActorSection()
{
	if (ImGui::CollapsingHeader("Actor"))
	{
		ImGui::Text("");

		DescriptionHelper("Custom actor creation and spawn system. Required for many features like character-, style- and weapon-switching.");
		ImGui::Text("");



		GUI_Checkbox
		(
			"Enable",
			queuedConfig.Actor.enable
		);
		ImGui::Text("");



		if (GUI_ResetButton())
		{
			CopyMemory
			(
				&queuedConfig.Actor,
				&defaultConfig.Actor,
				sizeof(queuedConfig.Actor)
			);

			old_for_all(uint8, playerIndex, PLAYER_COUNT)
			{
				ResetConfig(Actor.playerData[playerIndex].button);

				ResetConfig(Actor.playerData[playerIndex].removeBusyFlag);
				ResetConfig(Actor.playerData[playerIndex].removeBusyFlagButtons);
			}

			Actor_UpdateIndices();

			ResetConfig(resetPermissions);

			ResetConfig(enableBossLadyFixes);
			ResetConfig(enableBossVergilFixes);
			ToggleBossLadyFixes  (activeConfig.enableBossLadyFixes  );
			ToggleBossVergilFixes(activeConfig.enableBossVergilFixes);

			ResetConfig(enablePVPFixes);

			ResetConfig(forceSyncHitMagicPoints);
		}
		ImGui::Text("");



		ImGui::PushItemWidth(200.0f);

		GUI_Slider<uint8>
		(
			"Player Count",
			queuedConfig.Actor.playerCount,
			1,
			PLAYER_COUNT
		);
		ImGui::Text("");

		ImGui::PopItemWidth();



		if (ImGui::BeginTabBar("PlayerTabs"))
		{
			old_for_all(uint8, playerIndex, PLAYER_COUNT)
			{
				auto condition = (playerIndex >= queuedConfig.Actor.playerCount);

				GUI_PushDisable(condition);

				if (ImGui::BeginTabItem(playerIndexNames[playerIndex]))
				{
					ImGui::Text("");

					Actor_PlayerTab(playerIndex);

					ImGui::EndTabItem();
				}

				GUI_PopDisable(condition);
			}

			ImGui::EndTabBar();
		}

		GUI_SectionEnd();
		ImGui::Text("");



		GUI_Checkbox2
		(
			"Reset Permissions",
			activeConfig.resetPermissions,
			queuedConfig.resetPermissions
		);
		ImGui::SameLine();
		TooltipHelper
		(
			"(?)",
			"Press the taunt button to reset the actor's permissions.\n"
			"Useful when getting stuck."
		);
		ImGui::Text("");



		if
		(
			GUI_Checkbox2
			(
				"Enable Boss Lady Fixes",
				activeConfig.enableBossLadyFixes,
				queuedConfig.enableBossLadyFixes
			)
		)
		{
			ToggleBossLadyFixes(activeConfig.enableBossLadyFixes);
		}

		if
		(
			GUI_Checkbox2
			(
				"Enable Boss Vergil Fixes",
				activeConfig.enableBossVergilFixes,
				queuedConfig.enableBossVergilFixes
			)
		)
		{
			ToggleBossVergilFixes(activeConfig.enableBossVergilFixes);
		}

		GUI_Checkbox2
		(
			"Enable PVP Fixes",
			activeConfig.enablePVPFixes,
			queuedConfig.enablePVPFixes
		);
		ImGui::Text("");

		GUI_Checkbox2
		(
			"Force Sync Hit & Magic Points",
			activeConfig.forceSyncHitMagicPoints,
			queuedConfig.forceSyncHitMagicPoints
		);



		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Arcade

uint8 Arcade_modeIndex                 = 0;
uint8 Arcade_meleeWeaponIndexDante [2] = {};
uint8 Arcade_rangedWeaponIndexDante[2] = {};



void Arcade_UpdateIndices()
{
	UpdateMapIndex
	(
		modes,
		Arcade_modeIndex,
		activeConfig.Arcade.mode
	);

	UpdateMapIndex
	(
		meleeWeaponsDante,
		Arcade_meleeWeaponIndexDante[0],
		activeConfig.Arcade.weapons[0]
	);

	UpdateMapIndex
	(
		meleeWeaponsDante,
		Arcade_meleeWeaponIndexDante[1],
		activeConfig.Arcade.weapons[1]
	);

	UpdateMapIndex
	(
		rangedWeaponsDante,
		Arcade_rangedWeaponIndexDante[0],
		activeConfig.Arcade.weapons[2]
	);

	UpdateMapIndex
	(
		rangedWeaponsDante,
		Arcade_rangedWeaponIndexDante[1],
		activeConfig.Arcade.weapons[3]
	);
}

void ArcadeSection()
{
	if (ImGui::CollapsingHeader("Arcade"))
	{
		ImGui::Text("");

		DescriptionHelper("Go to a specific point in the game. Triggered in the main menu.");
		ImGui::Text("");

		if
		(
			GUI_Checkbox2
			(
				"Enable",
				activeConfig.Arcade.enable,
				queuedConfig.Arcade.enable
			)
		)
		{
			Arcade::Toggle(activeConfig.Arcade.enable);
		}
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			ResetConfig(Arcade);

			Arcade_UpdateIndices();

			Arcade::Toggle(activeConfig.Arcade.enable);
		}
		ImGui::Text("");

		ImGui::PushItemWidth(200);

		GUI_Combo2
		(
			"Mission",
			missionNames,
			activeConfig.Arcade.mission,
			queuedConfig.Arcade.mission,
			ImGuiComboFlags_HeightLargest
		);

		if
		(
			(activeConfig.Arcade.mission >= 1 ) &&
			(activeConfig.Arcade.mission <= 20)
		)
		{
			GUI_ComboMap2
			(
				"Mode",
				modeNames,
				modes,
				Arcade_modeIndex,
				activeConfig.Arcade.mode,
				queuedConfig.Arcade.mode
			);

			// Room
			{
				bool condition = activeConfig.Arcade.ignoreRoom;

				GUI_PushDisable(condition);

				GUI_InputDefault2
				(
					"Room",
					activeConfig.Arcade.room,
					queuedConfig.Arcade.room,
					defaultConfig.Arcade.room
				);

				GUI_PopDisable(condition);

				ImGui::SameLine();

				GUI_Checkbox2
				(
					"Ignore",
					activeConfig.Arcade.ignoreRoom,
					queuedConfig.Arcade.ignoreRoom
				);
			}

			// Position
			{
				bool condition = activeConfig.Arcade.ignorePosition;

				GUI_PushDisable(condition);

				GUI_InputDefault2
				(
					"Position",
					activeConfig.Arcade.position,
					queuedConfig.Arcade.position,
					defaultConfig.Arcade.position
				);

				GUI_PopDisable(condition);

				ImGui::SameLine();

				GUI_Checkbox2
				(
					"Ignore",
					activeConfig.Arcade.ignorePosition,
					queuedConfig.Arcade.ignorePosition
				);
			}
		}

		if (activeConfig.Arcade.mission == 21)
		{
			GUI_Combo2
			(
				"Floor",
				floorNames,
				activeConfig.Arcade.floor,
				queuedConfig.Arcade.floor,
				ImGuiComboFlags_HeightLargest
			);
		}

		if (activeConfig.Arcade.mission > 0)
		{
			GUI_InputDefault2
			(
				"Hit Points",
				activeConfig.Arcade.hitPoints,
				queuedConfig.Arcade.hitPoints,
				defaultConfig.Arcade.hitPoints,
				1000.0f,
				"%.0f"
			);
			GUI_InputDefault2
			(
				"Magic Points",
				activeConfig.Arcade.magicPoints,
				queuedConfig.Arcade.magicPoints,
				defaultConfig.Arcade.magicPoints,
				1000.0f,
				"%.0f"
			);
		}

		GUI_Combo2
		(
			"Character",
			characterNames,
			activeConfig.Arcade.character,
			queuedConfig.Arcade.character
		);
		GUI_InputDefault2
		(
			"Costume",
			activeConfig.Arcade.costume,
			queuedConfig.Arcade.costume,
			defaultConfig.Arcade.costume
		);

		if
		(
			(activeConfig.Arcade.mission > 0) &&
			(activeConfig.Arcade.character == CHARACTER::DANTE)
		)
		{
			GUI_Combo2
			(
				"Style",
				styleNamesDante,
				activeConfig.Arcade.style,
				queuedConfig.Arcade.style
			);
			GUI_ComboMap2
			(
				"Melee Weapon 1",
				meleeWeaponNamesDante,
				meleeWeaponsDante,
				Arcade_meleeWeaponIndexDante[0],
				activeConfig.Arcade.weapons[0],
				queuedConfig.Arcade.weapons[0]
			);
			GUI_ComboMap2
			(
				"Melee Weapon 2",
				meleeWeaponNamesDante,
				meleeWeaponsDante,
				Arcade_meleeWeaponIndexDante[1],
				activeConfig.Arcade.weapons[1],
				queuedConfig.Arcade.weapons[1]
			);
			GUI_ComboMap2
			(
				"Ranged Weapon 1",
				rangedWeaponNamesDante,
				rangedWeaponsDante,
				Arcade_rangedWeaponIndexDante[0],
				activeConfig.Arcade.weapons[2],
				queuedConfig.Arcade.weapons[2]
			);
			GUI_ComboMap2
			(
				"Ranged Weapon 2",
				rangedWeaponNamesDante,
				rangedWeaponsDante,
				Arcade_rangedWeaponIndexDante[1],
				activeConfig.Arcade.weapons[3],
				queuedConfig.Arcade.weapons[3]
			);
		}
		ImGui::PopItemWidth();

		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Bars

const char * barsNames[PLAYER_COUNT] =
{
	"Bars1",
	"Bars2",
	"Bars3",
	"Bars4",
};

bool showBars = false;



void BarsFunction
(
	float hitPoints,
	float magicPoints,
	const char * name,
	const char * label,
	Config::BarsData & activeData,
	Config::BarsData & queuedData
)
{
	if
	(
		!showBars &&
		!activeData.enable
	)
	{
		return;
	}

	auto & activePos = *reinterpret_cast<ImVec2 *>(&activeData.pos);
	auto & queuedPos = *reinterpret_cast<ImVec2 *>(&queuedData.pos);

	auto & lastX = activeData.lastX;
	auto & lastY = activeData.lastY;

	auto & run = activeData.run;
	if (!run)
	{
		run = true;

		ImGui::SetNextWindowPos(activePos);

		lastX = static_cast<uint32>(activeData.pos.x);
		lastY = static_cast<uint32>(activeData.pos.y);
	}

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(0, 0));

	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));

	if
	(
		ImGui::Begin
		(
			label,
			&activeData.enable,
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize
		)
	)
	{
		activePos = queuedPos = ImGui::GetWindowPos();

		auto x = static_cast<uint32>(activeData.pos.x);
		auto y = static_cast<uint32>(activeData.pos.y);

		if
		(
			(lastX != x) ||
			(lastY != y)
		)
		{
			lastX = x;
			lastY = y;

			GUI_save = true;
		}



		ImGui::PushStyleColor
		(
			ImGuiCol_PlotHistogram,
			*reinterpret_cast<ImVec4 *>(&activeData.hitColor)
		);
		ImGui::ProgressBar
		(
			hitPoints,
			*reinterpret_cast<ImVec2 *>(&activeData.size)
		);
		ImGui::PopStyleColor();



		ImGui::PushStyleColor
		(
			ImGuiCol_PlotHistogram,
			*reinterpret_cast<ImVec4 *>(&activeData.magicColor)
		);
		ImGui::ProgressBar
		(
			magicPoints,
			*reinterpret_cast<ImVec2 *>(&activeData.size)
		);
		ImGui::PopStyleColor();



		ImGui::Text(name);
	}

	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(4);
}

void BarsSettingsFunction
(
	const char * label,
	Config::BarsData & activeData,
	Config::BarsData & queuedData,
	Config::BarsData & defaultData
)
{
	auto & activePos = *reinterpret_cast<ImVec2 *>(&activeData.pos);
	auto & queuedPos = *reinterpret_cast<ImVec2 *>(&queuedData.pos);
	auto & defaultPos = *reinterpret_cast<ImVec2 *>(&defaultData.pos);



	GUI_Checkbox2
	(
		"Enable",
		activeData.enable,
		queuedData.enable
	);
	ImGui::Text("");

	if (GUI_ResetButton())
	{
		CopyMemory
		(
			&queuedData,
			&defaultData,
			sizeof(queuedData)
		);
		CopyMemory
		(
			&activeData,
			&queuedData,
			sizeof(activeData)
		);

		ImGui::SetWindowPos(label, activePos);
	}
	ImGui::Text("");

	bool condition = !activeData.enable;

	GUI_PushDisable(condition);

	GUI_Color2
	(
		"Hit Color",
		activeData.hitColor,
		queuedData.hitColor,
		ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview
	);
	GUI_Color2
	(
		"Magic Color",
		activeData.magicColor,
		queuedData.magicColor,
		ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview
	);
	ImGui::Text("");

	ImGui::PushItemWidth(150);

	GUI_InputDefault2
	(
		"Width",
		activeData.size.x,
		queuedData.size.x,
		defaultData.size.x,
		1.0f,
		"%g",
		ImGuiInputTextFlags_EnterReturnsTrue
	);
	GUI_InputDefault2
	(
		"Height",
		activeData.size.y,
		queuedData.size.y,
		defaultData.size.y,
		1.0f,
		"%g",
		ImGuiInputTextFlags_EnterReturnsTrue
	);

	if
	(
		GUI_InputDefault2<float>
		(
			"X",
			activePos.x,
			queuedPos.x,
			defaultPos.x,
			1,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		)
	)
	{
		ImGui::SetWindowPos(label, activePos);
	}
	if
	(
		GUI_InputDefault2<float>
		(
			"Y",
			activePos.y,
			queuedPos.y,
			defaultPos.y,
			1,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		)
	)
	{
		ImGui::SetWindowPos(label, activePos);
	}

	ImGui::PopItemWidth();

	GUI_PopDisable(condition);
}

void Bars()
{
	if
	(
		!showBars &&
		!InGame()
	)
	{
		return;
	}

	uint8 playerCount = (showBars) ? PLAYER_COUNT : activeConfig.Actor.playerCount;

	old_for_all(uint8, playerIndex, playerCount)
	{
		float hit   = 0.75f;
		float magic = 0.5f;

		[&]()
		{
			IntroducePlayerCharacterNewActorData(playerIndex);

			if (activeCharacterData.character >= CHARACTER::MAX)
			{
				hit   = 1.0f;
				magic = 1.0f;

				return;
			}

			IntroduceData(activeNewActorData.baseAddr, activeActorData, PlayerActorData, return);

			hit   = (activeActorData.hitPoints   / activeActorData.maxHitPoints  );
			magic = (activeActorData.magicPoints / activeActorData.maxMagicPoints);
		}();

		BarsFunction
		(
			hit,
			magic,
			playerIndexNames[playerIndex],
			barsNames[playerIndex],
			activeConfig.barsData[playerIndex],
			queuedConfig.barsData[playerIndex]
		);
	}
}

void BarsSettings()
{
	for_all(playerIndex, PLAYER_COUNT)
	{
		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart(playerIndexNames[playerIndex]);

		BarsSettingsFunction
		(
			barsNames[playerIndex],
			activeConfig.barsData[playerIndex],
			queuedConfig.barsData[playerIndex],
			defaultConfig.barsData[playerIndex]
		);
	}
}

void BarsSection()
{
	if (ImGui::CollapsingHeader("Bars"))
	{
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			ResetConfig(barsData);

			for_all(playerIndex, PLAYER_COUNT)
			{
				ImGui::SetWindowPos
				(
					barsNames[playerIndex],
					*reinterpret_cast<ImVec2 *>(&activeConfig.barsData[playerIndex].pos)
				);
			}
		}
		ImGui::Text("");



		GUI_Checkbox
		(
			"Show Bars",
			showBars
		);

		BarsSettings();



		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Boss Rush

void BossRush()
{
	if (ImGui::CollapsingHeader("Boss Rush"))
	{
		ImGui::Text("");

		DescriptionHelper("Go directly to boss battles.");
		ImGui::Text("");

		GUI_Checkbox2
		(
			"Enable",
			activeConfig.BossRush.enable,
			queuedConfig.BossRush.enable
		);
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			ResetConfig(BossRush);
		}
		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("Mission 5");
		GUI_Checkbox2
		(
			"Skip Jester",
			activeConfig.BossRush.Mission5.skipJester,
			queuedConfig.BossRush.Mission5.skipJester
		);
		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("Mission 12");
		GUI_Checkbox2
		(
			"Skip Jester",
			activeConfig.BossRush.Mission12.skipJester,
			queuedConfig.BossRush.Mission12.skipJester
		);
		GUI_Checkbox2
		(
			"Skip Geryon Part 1",
			activeConfig.BossRush.Mission12.skipGeryonPart1,
			queuedConfig.BossRush.Mission12.skipGeryonPart1
		);
		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("Mission 17");
		GUI_Checkbox2
		(
			"Skip Jester",
			activeConfig.BossRush.Mission17.skipJester,
			queuedConfig.BossRush.Mission17.skipJester
		);
		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("Mission 19");
		GUI_Checkbox2
		(
			"Skip Arkham Part 1",
			activeConfig.BossRush.Mission19.skipArkhamPart1,
			queuedConfig.BossRush.Mission19.skipArkhamPart1
		);

		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Camera

const char * cameraAutoAdjustNames[] =
{
	"Default",
	"Manual",
	"Disable",
};



export template <typename T>
void GUI_InputDefault2Camera
(
	const char * label,
	T & var,
	T & var2,
	T & var3,
	T & defaultVar,
	const T step = 1,
	const char * format = 0,
	ImGuiInputTextFlags flags = 0
)
{
	ImGui::PushItemWidth(150);
	GUI_Input
	(
		"",
		var,
		step,
		format,
		flags
	);
	ImGui::SameLine();
	GUI_InputDefault2
	(
		label,
		var2,
		var3,
		defaultVar,
		step,
		format,
		flags
	);
	ImGui::PopItemWidth();

	if constexpr (debug)
	{
		ImGui::Text("%f", var );
		ImGui::Text("%f", var2);
	}
}

void CameraSection()
{
	if (ImGui::CollapsingHeader("Camera"))
	{
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			ResetConfig(cameraInvertX      );
			ResetConfig(cameraAutoAdjust   );
			ResetConfig(disableCenterCamera);
			ResetConfig(disableBossCamera  );

			Camera::ToggleInvertX          (activeConfig.cameraInvertX    );
			Camera::ToggleDisableBossCamera(activeConfig.disableBossCamera);
		}
		ImGui::Text("");

		if
		(
			GUI_Checkbox2
			(
				"Invert X",
				activeConfig.cameraInvertX,
				queuedConfig.cameraInvertX
			)
		)
		{
			Camera::ToggleInvertX(activeConfig.cameraInvertX);
		}
		ImGui::Text("");

		ImGui::PushItemWidth(150.0f);
		GUI_Combo2<uint8>
		(
			"Auto Adjust",
			cameraAutoAdjustNames,
			activeConfig.cameraAutoAdjust,
			queuedConfig.cameraAutoAdjust
		);
		ImGui::PopItemWidth();
		ImGui::Text("");

		GUI_Checkbox2
		(
			"Disable Center Camera",
			activeConfig.disableCenterCamera,
			queuedConfig.disableCenterCamera
		);

		if
		(
			GUI_Checkbox2
			(
				"Disable Boss Camera",
				activeConfig.disableBossCamera,
				queuedConfig.disableBossCamera
			)
		)
		{
			Camera::ToggleDisableBossCamera(activeConfig.disableBossCamera);
		}

		GUI_SectionEnd();
		ImGui::Text("");



		GUI_SectionStart("Live");

		[&]()
		{
			if (g_scene != SCENE::GAME)
			{
				return;
			}

			IntroduceCameraData(return);

			ImGui::PushItemWidth(150.0f);

			GUI_Input
			(
				"FOV",
				cameraData.fov,
				0.1f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			ImGui::Text("");



			old_for_all(uint8, index, countof(cameraData.data))
			{
				ImGui::Text(dataNames[index]);
				GUI_Input
				(
					"X",
					cameraData.data[index].x,
					10.0f,
					"%g",
					ImGuiInputTextFlags_EnterReturnsTrue
				);
				GUI_Input
				(
					"Y",
					cameraData.data[index].y,
					10.0f,
					"%g",
					ImGuiInputTextFlags_EnterReturnsTrue
				);
				GUI_Input
				(
					"Z",
					cameraData.data[index].z,
					10.0f,
					"%g",
					ImGuiInputTextFlags_EnterReturnsTrue
				);
				GUI_Input
				(
					"A",
					cameraData.data[index].a,
					10.0f,
					"%g",
					ImGuiInputTextFlags_EnterReturnsTrue
				);
				ImGui::Text("");
			}



			GUI_Input
			(
				"Height",
				cameraData.height,
				10.0f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input
			(
				"Tilt",
				cameraData.tilt,
				0.05f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input
			(
				"Distance",
				cameraData.distance,
				10.0f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input
			(
				"Distance Lock-On",
				cameraData.distanceLockOn,
				10.0f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);

			ImGui::PopItemWidth();
		}();



		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Cosmetics

struct
{
	float32 airHike[5][4] =
	{
		{ 128,   0,   0, 200 },
		{  96, 128, 144, 200 },
		{ 160,  64,  16, 200 },
		{ 112,  64, 160, 200 },
		{ 128, 128, 128, 200 },
	};
	struct
	{
		float32 skyStar[4] = { 255, 0, 0, 200 };
	}
	Trickster;
	struct
	{
		float32 ultimate[4] = { 143, 112, 48, 200 };
	}
	Royalguard;
	struct
	{
		float32 clone[4] = { 16, 16, 16, 48 };
	}
	Doppelganger;
	struct
	{
		float32 dante[5][4] =
		{
			{ 128,   0,   0, 200 },
			{  96, 128, 144, 200 },
			{ 160,  64,  16, 200 },
			{ 112,  64, 160, 200 },
			{ 128, 128, 128, 200 },
		};
		float32 sparda[4] = { 128, 0, 0, 200 };
		float32 vergil[3][4] =
		{
			{ 32, 64, 128, 200 },
			{ 32, 64, 128, 200 },
			{ 32, 64, 128, 200 },
		};
		float32 neroAngelo[4] = { 64, 0, 255, 200 };
	}
	Aura;
}
Color;

void Color_UpdateValues()
{
	// LogFunction();

	constexpr uint8 itemCount = (sizeof(Color) / 4);

	auto items = reinterpret_cast<uint8 *>(activeConfig.Color.airHike);
	auto items2 = reinterpret_cast<float32 *>(Color.airHike);

	old_for_all(uint8, index, itemCount)
	{
		items2[index] = (static_cast<float32>(items[index]) / 255);
	}
}

void Cosmetics()
{
	if (ImGui::CollapsingHeader("Cosmetics"))
	{
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			ResetConfig(Color);

			Color_UpdateValues();

			ResetConfig(hideBeowulfDante);
			ResetConfig(hideBeowulfVergil);

			ResetConfig(noDevilForm);
			ToggleNoDevilForm(activeConfig.noDevilForm);
		}
		GUI_SectionEnd();
		ImGui::Text("");

		ImGui::Text("Color");
		ImGui::SameLine();
		TooltipHelper
		(
			"(?)",
			"Requires enabled Actor module."
		);
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			ResetConfig(Color);

			Color_UpdateValues();
		}
		ImGui::Text("");

		GUI_ColorPalette2
		(
			"Air Hike",
			activeConfig.Color.airHike,
			queuedConfig.Color.airHike,
			Color.airHike
		);
		ImGui::Text("");

		ImGui::Text("Trickster");
		GUI_Color2
		(
			"Sky Star",
			activeConfig.Color.Trickster.skyStar,
			queuedConfig.Color.Trickster.skyStar,
			Color.Trickster.skyStar
		);
		ImGui::Text("");

		ImGui::Text("Royalguard");
		GUI_Color2
		(
			"Ultimate",
			activeConfig.Color.Royalguard.ultimate,
			queuedConfig.Color.Royalguard.ultimate,
			Color.Royalguard.ultimate
		);
		ImGui::Text("");

		ImGui::Text("Doppelganger");
		GUI_Color2
		(
			"Clone",
			activeConfig.Color.Doppelganger.clone,
			queuedConfig.Color.Doppelganger.clone,
			Color.Doppelganger.clone
		);
		ImGui::Text("");

		ImGui::Text("Aura");
		GUI_ColorPalette2
		(
			"Dante",
			activeConfig.Color.Aura.dante,
			queuedConfig.Color.Aura.dante,
			Color.Aura.dante
		);
		GUI_Color2
		(
			"Sparda",
			activeConfig.Color.Aura.sparda,
			queuedConfig.Color.Aura.sparda,
			Color.Aura.sparda
		);
		GUI_ColorPalette2
		(
			"Vergil",
			activeConfig.Color.Aura.vergil,
			queuedConfig.Color.Aura.vergil,
			Color.Aura.vergil
		);
		GUI_Color2
		(
			"Nero Angelo",
			activeConfig.Color.Aura.neroAngelo,
			queuedConfig.Color.Aura.neroAngelo,
			Color.Aura.neroAngelo
		);
		GUI_SectionEnd();
		ImGui::Text("");

		ImGui::Text("Other");
		ImGui::SameLine();
		TooltipHelper
		(
			"(?)",
			"Requires enabled Actor module."
		);
		ImGui::Text("");

		GUI_Checkbox2
		(
			"Hide Beowulf Dante",
			activeConfig.hideBeowulfDante,
			queuedConfig.hideBeowulfDante
		);
		GUI_Checkbox2
		(
			"Hide Beowulf Vergil",
			activeConfig.hideBeowulfVergil,
			queuedConfig.hideBeowulfVergil
		);
		if
		(
			GUI_Checkbox2
			(
				"No Devil Form",
				activeConfig.noDevilForm,
				queuedConfig.noDevilForm
			)
		)
		{
			ToggleNoDevilForm(activeConfig.noDevilForm);
		}

		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Damage

void Damage()
{
	if (ImGui::CollapsingHeader("Damage"))
	{
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			ResetConfig(damageActorMultiplier);
			ResetConfig(damageEnemyMultiplier);
			ResetConfig(damageStyleRank);
		}
		ImGui::Text("");

		TooltipHelper
		(
			"(?)",
			"Multiplier values are for RECEIVED damage."
		);
		ImGui::Text("");



		if constexpr (debug)
		{
			static bool toggled = false;

			if (GUI_Button("One Hit Kill"))
			{

				if (!toggled)
				{
					toggled = true;

					activeConfig.damageActorMultiplier = queuedConfig.damageActorMultiplier = 1.0f;
					activeConfig.damageEnemyMultiplier = queuedConfig.damageEnemyMultiplier = 100.0f;
				}
				else
				{
					toggled = false;

					activeConfig.damageActorMultiplier = queuedConfig.damageActorMultiplier = 0;
					activeConfig.damageEnemyMultiplier = queuedConfig.damageEnemyMultiplier = 0;
				}
			}
		}



		ImGui::PushItemWidth(150);

		GUI_InputDefault2
		(
			"Actor Multiplier",
			activeConfig.damageActorMultiplier,
			queuedConfig.damageActorMultiplier,
			defaultConfig.damageActorMultiplier,
			0.1f,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		);

		GUI_InputDefault2
		(
			"Enemy Multiplier",
			activeConfig.damageEnemyMultiplier,
			queuedConfig.damageEnemyMultiplier,
			defaultConfig.damageEnemyMultiplier,
			0.1f,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		);

		GUI_Combo2
		(
			"Style Rank",
			styleRankNames,
			activeConfig.damageStyleRank,
			queuedConfig.damageStyleRank
		);

		ImGui::PopItemWidth();

		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Dante

// @Todo: Move.
template <typename T>
void ActionData
(
	const char * label,
	T(&vars)[2],
	T(&vars2)[2],
	T(&defaultVars)[2],
	T step = 1,
	const char * format = 0,
	ImGuiInputTextFlags flags = 0,
	float32 width = 150
)
{
	auto & style = ImGui::GetStyle();

	ImGui::PushItemWidth(width);
	GUI_InputDefault2
	(
		"",
		vars[0],
		vars2[0],
		defaultVars[0],
		step,
		format,
		flags
	);
	ImGui::SameLine(0, style.ItemInnerSpacing.x);
	GUI_InputDefault2
	(
		label,
		vars[1],
		vars2[1],
		defaultVars[1],
		step,
		format,
		flags
	);
	ImGui::PopItemWidth();
}

void Dante()
{
	if (ImGui::CollapsingHeader("Dante"))
	{
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			ResetConfig(airHikeCoreAbility);
			ToggleAirHikeCoreAbility(activeConfig.airHikeCoreAbility);

			ResetConfig(Royalguard);
			ToggleRoyalguardForceJustFrameRelease(activeConfig.Royalguard.forceJustFrameRelease);

			ResetConfig(Rebellion);
			ToggleRebellionInfiniteSwordPierce(activeConfig.Rebellion.infiniteSwordPierce);

			ResetConfig(EbonyIvory);
			ToggleEbonyIvoryFoursomeTime     (activeConfig.EbonyIvory.foursomeTime     );
			ToggleEbonyIvoryInfiniteRainStorm(activeConfig.EbonyIvory.infiniteRainStorm);

			ResetConfig(Artemis);
			ToggleArtemisSwapNormalShotAndMultiLock(activeConfig.Artemis.swapNormalShotAndMultiLock);
			ToggleArtemisInstantFullCharge         (activeConfig.Artemis.instantFullCharge         );

			ResetConfig(enableRebellionAirStinger);
			ResetConfig(enableRebellionNewDrive  );
			ResetConfig(enableRebellionQuickDrive);
			ResetConfig(enableCerberusAirRevolver);
			ResetConfig(enableNevanNewVortex     );
		}

		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("Air Hike");

		if
		(
			GUI_Checkbox2
			(
				"Core Ability",
				activeConfig.airHikeCoreAbility,
				queuedConfig.airHikeCoreAbility
			)
		)
		{
			ToggleAirHikeCoreAbility(activeConfig.airHikeCoreAbility);
		}
		ImGui::SameLine();
		TooltipHelper
		(
			"(?)",
			"Makes Air Hike available for all melee weapons."
		);

		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("Royalguard");

		if
		(
			GUI_Checkbox2
			(
				"Force Just Frame Release",
				activeConfig.Royalguard.forceJustFrameRelease,
				queuedConfig.Royalguard.forceJustFrameRelease
			)
		)
		{
			ToggleRoyalguardForceJustFrameRelease(activeConfig.Royalguard.forceJustFrameRelease);
		}

		GUI_SectionEnd();
		ImGui::Text("");

		ImGui::Text("Rebellion");
		ImGui::SameLine();
		TooltipHelper
		(
			"(?)",
			"Requires enabled Actor module.\n"
			"\n"
			"Left: Human Right: Devil"
		);
		ImGui::Text("");

		if
		(
			GUI_Checkbox2
			(
				"Infinite Sword Pierce",
				activeConfig.Rebellion.infiniteSwordPierce,
				queuedConfig.Rebellion.infiniteSwordPierce
			)
		)
		{
			ToggleRebellionInfiniteSwordPierce(activeConfig.Rebellion.infiniteSwordPierce);
		}
		ImGui::Text("");



		GUI_Checkbox2
		(
			"Enable Air Stinger",
			activeConfig.enableRebellionAirStinger,
			queuedConfig.enableRebellionAirStinger
		);
		GUI_Checkbox2
		(
			"Enable New Drive",
			activeConfig.enableRebellionNewDrive,
			queuedConfig.enableRebellionNewDrive
		);
		GUI_Checkbox2
		(
			"Enable Quick Drive",
			activeConfig.enableRebellionQuickDrive,
			queuedConfig.enableRebellionQuickDrive
		);
		ImGui::Text("");




		ActionData
		(
			"Stinger Duration",
			activeConfig.Rebellion.stingerDuration,
			queuedConfig.Rebellion.stingerDuration,
			defaultConfig.Rebellion.stingerDuration,
			1.0f,
			"%g"
		);
		ActionData
		(
			"Stinger Range",
			activeConfig.Rebellion.stingerRange,
			queuedConfig.Rebellion.stingerRange,
			defaultConfig.Rebellion.stingerRange,
			10.0f,
			"%g"
		);




		{
			bool condition = !activeConfig.enableRebellionAirStinger;

			GUI_PushDisable(condition);

			ActionData
			(
				"Air Stinger Count",
				activeConfig.Rebellion.airStingerCount,
				queuedConfig.Rebellion.airStingerCount,
				defaultConfig.Rebellion.airStingerCount
			);
			ActionData
			(
				"Air Stinger Duration",
				activeConfig.Rebellion.airStingerDuration,
				queuedConfig.Rebellion.airStingerDuration,
				defaultConfig.Rebellion.airStingerDuration,
				1.0f,
				"%g"
			);
			ActionData
			(
				"Air Stinger Range",
				activeConfig.Rebellion.airStingerRange,
				queuedConfig.Rebellion.airStingerRange,
				defaultConfig.Rebellion.airStingerRange,
				10.0f,
				"%g"
			);

			GUI_PopDisable(condition);
		}


		GUI_SectionEnd();
		ImGui::Text("");



		GUI_SectionStart("Cerberus");

		GUI_Checkbox2
		(
			"Enable Air Revolver",
			activeConfig.enableCerberusAirRevolver,
			queuedConfig.enableCerberusAirRevolver
		);

		GUI_SectionEnd();
		ImGui::Text("");



		GUI_SectionStart("Nevan");

		GUI_Checkbox2
		(
			"Enable New Vortex",
			activeConfig.enableNevanNewVortex,
			queuedConfig.enableNevanNewVortex
		);

		GUI_SectionEnd();
		ImGui::Text("");



		GUI_SectionStart("Ebony & Ivory");

		if
		(
			GUI_Checkbox2
			(
				"Foursome Time",
				activeConfig.EbonyIvory.foursomeTime,
				queuedConfig.EbonyIvory.foursomeTime
			)
		)
		{
			ToggleEbonyIvoryFoursomeTime(activeConfig.EbonyIvory.foursomeTime);
		}

		if
		(
			GUI_Checkbox2
			(
				"Infinite Rain Storm",
				activeConfig.EbonyIvory.infiniteRainStorm,
				queuedConfig.EbonyIvory.infiniteRainStorm
			)
		)
		{
			ToggleEbonyIvoryInfiniteRainStorm(activeConfig.EbonyIvory.infiniteRainStorm);
		}

		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("Artemis");

		if
		(
			GUI_Checkbox2
			(
				"Swap Normal Shot and Multi Lock",
				activeConfig.Artemis.swapNormalShotAndMultiLock,
				queuedConfig.Artemis.swapNormalShotAndMultiLock
			)
		)
		{
			ToggleArtemisSwapNormalShotAndMultiLock(activeConfig.Artemis.swapNormalShotAndMultiLock);
		}

		if
		(
			GUI_Checkbox2
			(
				"Instant Full Charge",
				activeConfig.Artemis.instantFullCharge,
				queuedConfig.Artemis.instantFullCharge
			)
		)
		{
			ToggleArtemisInstantFullCharge(activeConfig.Artemis.instantFullCharge);
		}

		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Debug

bool showFileDataWindow    = false;
bool showRegionDataWindow  = false;
bool showSoundWindow       = false;
bool showMissionDataWindow = false;
bool showActorWindow       = false;
bool showEventDataWindow   = false;

void MissionDataWindow()
{
	if (!showMissionDataWindow)
	{
		return;
	}

	IntroduceMissionData(return);

	IntroduceEventData(return);



	static bool run = false;
	if (!run)
	{
		run = true;

		ImGui::SetNextWindowSize
		(
			ImVec2
			(
				500,
				900
			)
		);
		ImGui::SetNextWindowPos
		(
			ImVec2
			(
				0,
				0
			)
		);
	}



	if (ImGui::Begin("MissionData", &showMissionDataWindow))
	{
		ImGui::Text("");






		ImGui::PushItemWidth(200);

		GUI_Input<uint32>
		(
			"Red Orbs",
			missionData.redOrbs,
			1000,
			"%u",
			ImGuiInputTextFlags_EnterReturnsTrue
		);

		ImGui::PopItemWidth();



		ImGui::Text("");




		ImGui::Text("Item Count");
		ImGui::Text("");

		ImGui::PushItemWidth(150);

		old_for_all(uint8, itemIndex, ITEM_COUNT)
		{
			ImGui::Text("%.4u %llX", itemIndex, &missionData.itemCounts[itemIndex]);
			ImGui::SameLine();

			GUI_Input<uint8>
			(
				itemNames[itemIndex],
				missionData.itemCounts[itemIndex],
				1,
				"%u",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
		}

		ImGui::PopItemWidth();

		ImGui::Text("");




		ImGui::Text("Buy Count");
		ImGui::Text("");

		ImGui::PushItemWidth(150);

		old_for_all(uint8, buyIndex, BUY_COUNT)
		{
			ImGui::Text("%.4u %llX", buyIndex, &missionData.buyCounts[buyIndex]);
			ImGui::SameLine();

			GUI_Input<uint8>
			(
				buyNames[buyIndex],
				missionData.buyCounts[buyIndex],
				1,
				"%u",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
		}

		ImGui::PopItemWidth();


		ImGui::Text("");

		if (GUI_Button("Status"))
		{
			eventData.event = EVENT::STATUS;
		}

		if (GUI_Button("Customize"))
		{
			eventData.event = EVENT::CUSTOMIZE;
		}






		ImGui::Text("");
	}

	ImGui::End();
}



struct FileContainer : Container<>
{
	const char * operator[](uint32 index);

	void Push(uint32 size);
};

const char * FileContainer::operator[](uint32 index)
{
	if (index >= count)
	{
		return 0;
	}

	auto & metadata = reinterpret_cast<Metadata *>(metadataAddr)[index];

	return reinterpret_cast<const char *>(dataAddr + metadata.off);
}

void FileContainer::Push(uint32 size)
{
	auto & metadata = reinterpret_cast<Metadata *>(metadataAddr)[count];

	metadata.off = pos;
	metadata.size = size;

	pos += size;
	count++;
}

void FileDataWindow()
{
	constexpr uint32 fileDataGroupItemCounts[] =
	{
		4,
		136,
		60,
		28,
		1,
		128,
		6,
	};
	constexpr uint8 fileDataGroupCount = static_cast<uint8>(countof(fileDataGroupItemCounts));
	static FileContainer fileDataGroupNames = {};
	static FileContainer fileDataGroupItemNames[fileDataGroupCount] = {};
	static FileContainer enemyFileDataItemNames = {};
	static FileContainer enemyFileDataMetadataItemNames = {};

	static bool run = false;
	if (!run)
	{
		run = true;

		{
			auto & container = fileDataGroupNames;

			container.Init
			(
				(fileDataGroupCount * 5),
				(fileDataGroupCount * sizeof(FileContainer::Metadata))
			);

			old_for_all(uint8, groupIndex, fileDataGroupCount)
			{
				auto dest = reinterpret_cast<char *>(container.dataAddr + container.pos);
				auto size = (container.dataSize - container.pos);

				snprintf
				(
					dest,
					size,
					"%.4u",
					groupIndex
				);

				container.Push(5);
			}
		}



		uint32 g_itemIndex = 0;

		old_for_all(uint8, groupIndex, fileDataGroupCount)
		{
			auto & container = fileDataGroupItemNames[groupIndex];
			auto & itemCount = fileDataGroupItemCounts[groupIndex];

			container.Init
			(
				(itemCount * 10),
				(itemCount * sizeof(FileContainer::Metadata))
			);

			old_for_all(uint32, itemIndex, itemCount)
			{
				auto dest = reinterpret_cast<char *>(container.dataAddr + container.pos);
				auto size = (container.dataSize - container.pos);

				snprintf
				(
					dest,
					size,
					"%.4u %.4u",
					itemIndex,
					g_itemIndex
				);

				container.Push(10);

				g_itemIndex++;
			}
		}



		{
			const uint32 itemCount = ENEMY_FILE_DATA_COUNT;

			auto & container = enemyFileDataItemNames;

			container.Init
			(
				(itemCount * 6),
				(itemCount * sizeof(FileContainer::Metadata))
			);


			old_for_all(uint32, itemIndex, itemCount)
			{
				auto dest = reinterpret_cast<char *>(container.dataAddr + container.pos);
				auto size = (container.dataSize - container.pos);

				snprintf
				(
					dest,
					size,
					"%.4u ",
					itemIndex
				);

				container.Push(6);
			}
		}


		{
			const uint32 itemCount = ENEMY::COUNT;

			auto & container = enemyFileDataMetadataItemNames;

			container.Init
			(
				(itemCount * 7),
				(itemCount * sizeof(FileContainer::Metadata))
			);


			old_for_all(uint32, itemIndex, itemCount)
			{
				auto dest = reinterpret_cast<char *>(container.dataAddr + container.pos);
				auto size = (container.dataSize - container.pos);

				snprintf
				(
					dest,
					size,
					"%.4u  ",
					itemIndex
				);

				container.Push(7);
			}
		}
	}



	if (!showFileDataWindow)
	{
		return;
	}



	static bool run2 = false;
	if (!run2)
	{
		run2 = true;

		ImGui::SetNextWindowSize
		(
			ImVec2
			(
				700,
				700
			)
		);
		ImGui::SetNextWindowPos
		(
			ImVec2
			(
				0,
				0
			)
		);
	}



	if (ImGui::Begin("FileData", &showFileDataWindow))
	{
		ImGui::Text("");

		auto GUI_FileData = [&](FileData & fileData)
		{
			ImGui::PushItemWidth(200);

			auto addr = &fileData;

			GUI_Input<uint64>
			(
				"this",
				*reinterpret_cast<uint64 *>(&addr),
				0,
				"%.16llX",
				ImGuiInputTextFlags_ReadOnly
			);
			GUI_Input<uint32>
			(
				"group",
				fileData.group,
				1,
				"%u",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input<uint32>
			(
				"status",
				fileData.status,
				1,
				"%u",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input<uint64>
			(
				"typeDataAddr",
				*reinterpret_cast<uint64 *>(&fileData.typeDataAddr),
				0,
				"%.16llX",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			if (fileData.typeDataAddr)
			{
				ImGui::Text((*fileData.typeDataAddr).typeName);
			}
			GUI_Input<uint64>
			(
				"file",
				*reinterpret_cast<uint64 *>(&fileData.file),
				0,
				"%.16llX",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			if (GUI_Button("Reset"))
			{
				SetMemory
				(
					&fileData,
					0,
					sizeof(fileData)
				);
			}

			ImGui::PopItemWidth();
		};

		auto GUI_FileDataMetadata = [&](FileDataMetadata & metadata)
		{
			ImGui::PushItemWidth(200);

			auto addr = &metadata;

			GUI_Input<uint64>
			(
				"this",
				*reinterpret_cast<uint64 *>(&addr),
				0,
				"%.16llX",
				ImGuiInputTextFlags_ReadOnly
			);

			GUI_Input<uint64>
			(
				"funcAddrs",
				*reinterpret_cast<uint64 *>(&metadata.funcAddrs),
				0,
				"%.16llX",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input<uint64>
			(
				"lastAddr",
				*reinterpret_cast<uint64 *>(&metadata.lastAddr),
				0,
				"%.16llX",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input<uint64>
			(
				"nextAddr",
				*reinterpret_cast<uint64 *>(&metadata.nextAddr),
				0,
				"%.16llX",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input<uint64>
			(
				"fileDataAddr",
				*reinterpret_cast<uint64 *>(&metadata.fileDataAddr),
				0,
				"%.16llX",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input<uint32>
			(
				"category",
				metadata.category,
				1,
				"%u",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input<uint32>
			(
				"fileSetIndex",
				metadata.fileSetIndex,
				1,
				"%u",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			if (GUI_Button("Reset"))
			{
				SetMemory
				(
					&metadata,
					0,
					sizeof(metadata)
				);
			}

			ImGui::PopItemWidth();
		};



		GUI_SectionStart("Default File Data");

		uint32 g_itemIndex = 0;

		old_for_all(uint32, groupIndex, fileDataGroupCount)
		{
			auto open = ImGui::CollapsingHeader(fileDataGroupNames[groupIndex]);

			auto & itemCount = fileDataGroupItemCounts[groupIndex];

			ImGui::Indent(20);

			old_for_all(uint32, itemIndex, itemCount)
			{
				if
				(
					open &&
					ImGui::CollapsingHeader(fileDataGroupItemNames[groupIndex][itemIndex])
				)
				{
					ImGui::Indent(20);

					auto & fileData = reinterpret_cast<FileData *>(appBaseAddr + 0xC99D30)[g_itemIndex];

					GUI_FileData(fileData);

					ImGui::Unindent(20);
				}

				g_itemIndex++;
			}

			ImGui::Unindent(20);
		}

		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("Enemy File Data");

		old_for_all(uint32, fileDataIndex, ENEMY_FILE_DATA_COUNT)
		{
			if (ImGui::CollapsingHeader(enemyFileDataItemNames[fileDataIndex]))
			{
				ImGui::Indent(20);

				GUI_FileData(enemyFileData[fileDataIndex]);

				ImGui::Unindent(20);
			}
		}

		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("Enemy File Data Metadata");

		old_for_all(uint32, index, ENEMY::COUNT)
		{
			if (ImGui::CollapsingHeader(enemyFileDataMetadataItemNames[index]))
			{
				ImGui::Indent(20);

				GUI_FileDataMetadata(enemyFileDataMetadata[index]);

				ImGui::Unindent(20);
			}
		}

		ImGui::Text("");
	}

	ImGui::End();
}



void ActorWindow()
{
	if (!showActorWindow)
	{
		return;
	}



	static bool run = false;
	if (!run)
	{
		run = true;

		ImGui::SetNextWindowSize
		(
			ImVec2
			(
				700,
				700
			)
		);
		ImGui::SetNextWindowPos
		(
			ImVec2
			(
				0,
				0
			)
		);
	}



	if (ImGui::Begin("ActorWindow", &showActorWindow))
	{
		ImGui::Text("");



		if (ImGui::CollapsingHeader("Default"))
		{
			ImGui::Text("");

			old_for_all(uint8, entityIndex, ENTITY_COUNT)
			{
				auto & newActorData = g_defaultNewActorData[entityIndex];

				//auto & characterName = characterIndexNames[characterIndex];
				auto & entityName = entityEnumNames[entityIndex];

				ImGui::Text(entityName);

				ImGui::PushItemWidth(150.0f);

				GUI_Input<byte64>
				(
					"baseAddr",
					*reinterpret_cast<byte64 *>(&newActorData.baseAddr),
					0,
					"%llX",
					ImGuiInputTextFlags_EnterReturnsTrue
				);
				GUI_Input<uint8>
				(
					"visibility",
					newActorData.visibility,
					1,
					"%u",
					ImGuiInputTextFlags_EnterReturnsTrue
				);
				GUI_Checkbox
				(
					"enableCollision",
					newActorData.enableCollision
				);
				[&]()
				{
					IntroduceData(newActorData.baseAddr, actorData, PlayerActorData, return);

					GUI_Input
					(
						"Speed",
						actorData.speed,
						1.0f,
						"%g",
						ImGuiInputTextFlags_EnterReturnsTrue
					);
					GUI_Input
					(
						"Speed Multiplier",
						actorData.speedMultiplier,
						1.0f,
						"%g",
						ImGuiInputTextFlags_EnterReturnsTrue
					);

					GUI_Input
					(
						"x",
						actorData.position.x,
						1.0f,
						"%g",
						ImGuiInputTextFlags_EnterReturnsTrue
					);
					GUI_Input
					(
						"y",
						actorData.position.y,
						1.0f,
						"%g",
						ImGuiInputTextFlags_EnterReturnsTrue
					);
					GUI_Input
					(
						"z",
						actorData.position.z,
						1.0f,
						"%g",
						ImGuiInputTextFlags_EnterReturnsTrue
					);
					GUI_Input
					(
						"a",
						actorData.position.a,
						1.0f,
						"%g",
						ImGuiInputTextFlags_EnterReturnsTrue
					);

					GUI_Input
					(
						"Hit Points",
						actorData.hitPoints,
						1.0f,
						"%g",
						ImGuiInputTextFlags_EnterReturnsTrue
					);
					GUI_Input
					(
						"Max Hit Points",
						actorData.maxHitPoints,
						1.0f,
						"%g",
						ImGuiInputTextFlags_EnterReturnsTrue
					);
					GUI_Input
					(
						"Magic Points",
						actorData.magicPoints,
						1.0f,
						"%g",
						ImGuiInputTextFlags_EnterReturnsTrue
					);
					GUI_Input
					(
						"Max Magic Points",
						actorData.maxMagicPoints,
						1.0f,
						"%g",
						ImGuiInputTextFlags_EnterReturnsTrue
					);
				}();

				ImGui::PopItemWidth();

				ImGui::Text("");
			}
		}



		old_for_all(uint8, playerIndex, PLAYER_COUNT)
		{
			auto & playerData = GetPlayerData(playerIndex);

			//auto playerName = playerNames[playerIndex];

			if (!ImGui::CollapsingHeader(playerIndexNames[playerIndex]))
			{
				continue;
			}

			ImGui::Text("");

			ImGui::PushItemWidth(150.0f);
			GUI_Input<uint8>
			(
				"characterCount",
				playerData.characterCount,
				1,
				"%u",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input<uint8>
			(
				"characterIndex",
				playerData.characterIndex,
				1,
				"%u",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input<uint8>
			(
				"lastCharacterIndex",
				playerData.lastCharacterIndex,
				1,
				"%u",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input<uint8>
			(
				"activeCharacterIndex",
				playerData.activeCharacterIndex,
				1,
				"%u",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input<uint8>
			(
				"collisionGroup",
				playerData.collisionGroup,
				1,
				"%u",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			ImGui::PopItemWidth();
			ImGui::Text("");

			ImGui::Indent(20);

			old_for_all(uint8, characterIndex, CHARACTER_COUNT)
			{
				auto & characterName = characterIndexNames[characterIndex];

				if (!ImGui::CollapsingHeader(characterName))
				{
					continue;
				}

				ImGui::Text("");

				old_for_all(uint8, entityIndex, ENTITY_COUNT)
				{
					auto & characterData = GetCharacterData(playerIndex, characterIndex, entityIndex);
					auto & newActorData  = GetNewActorData (playerIndex, characterIndex, entityIndex);

					//auto & characterName = characterIndexNames[characterIndex];
					auto & entityName = entityEnumNames[entityIndex];

					ImGui::Text(entityName);

					ImGui::PushItemWidth(150.0f);

					GUI_Input<uint8>
					(
						"character",
						characterData.character,
						1,
						"%u",
						ImGuiInputTextFlags_EnterReturnsTrue
					);
					GUI_Input<uint8>
					(
						"costume",
						characterData.costume,
						1,
						"%u",
						ImGuiInputTextFlags_EnterReturnsTrue
					);
					GUI_Input<byte64>
					(
						"baseAddr",
						*reinterpret_cast<byte64 *>(&newActorData.baseAddr),
						0,
						"%llX",
						ImGuiInputTextFlags_EnterReturnsTrue
					);
					GUI_Input<uint8>
					(
						"visibility",
						newActorData.visibility,
						1,
						"%u",
						ImGuiInputTextFlags_EnterReturnsTrue
					);
					GUI_Checkbox
					(
						"enableCollision",
						newActorData.enableCollision
					);
					[&]()
					{
						IntroduceData(newActorData.baseAddr, actorData, PlayerActorData, return);

						GUI_Input
						(
							"Speed",
							actorData.speed,
							1.0f,
							"%g",
							ImGuiInputTextFlags_EnterReturnsTrue
						);
						GUI_Input
						(
							"Speed Multiplier",
							actorData.speedMultiplier,
							1.0f,
							"%g",
							ImGuiInputTextFlags_EnterReturnsTrue
						);

						GUI_Input
						(
							"x",
							actorData.position.x,
							1.0f,
							"%g",
							ImGuiInputTextFlags_EnterReturnsTrue
						);
						GUI_Input
						(
							"y",
							actorData.position.y,
							1.0f,
							"%g",
							ImGuiInputTextFlags_EnterReturnsTrue
						);
						GUI_Input
						(
							"z",
							actorData.position.z,
							1.0f,
							"%g",
							ImGuiInputTextFlags_EnterReturnsTrue
						);
						GUI_Input
						(
							"a",
							actorData.position.a,
							1.0f,
							"%g",
							ImGuiInputTextFlags_EnterReturnsTrue
						);

						GUI_Input
						(
							"Hit Points",
							actorData.hitPoints,
							1.0f,
							"%g",
							ImGuiInputTextFlags_EnterReturnsTrue
						);
						GUI_Input
						(
							"Max Hit Points",
							actorData.maxHitPoints,
							1.0f,
							"%g",
							ImGuiInputTextFlags_EnterReturnsTrue
						);
						GUI_Input
						(
							"Magic Points",
							actorData.magicPoints,
							1.0f,
							"%g",
							ImGuiInputTextFlags_EnterReturnsTrue
						);
						GUI_Input
						(
							"Max Magic Points",
							actorData.maxMagicPoints,
							1.0f,
							"%g",
							ImGuiInputTextFlags_EnterReturnsTrue
						);
					}();

					ImGui::PopItemWidth();

					ImGui::Text("");
				}
			}

			ImGui::Unindent(20);

			ImGui::Text("");
		}



		ImGui::Text("");
	}

	ImGui::End();
}



void EventDataWindow()
{
	if (!showEventDataWindow)
	{
		return;
	}

	IntroduceEventData(return);

	static EventData eventData2 = {};

	static bool run = false;
	if (!run)
	{
		run = true;

		ImGui::SetNextWindowSize
		(
			ImVec2
			(
				700,
				700
			)
		);
		ImGui::SetNextWindowPos
		(
			ImVec2
			(
				0,
				0
			)
		);
	}



	if
	(
		ImGui::Begin
		(
			"EventData",
			&showEventDataWindow
		)
	)
	{
		ImGui::Text("");

		ImGui::PushItemWidth(150);

		GUI_Input<uint32>
		(
			"room",
			eventData2.room,
			1,
			"%u",
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		GUI_Input<uint32>
		(
			"position",
			eventData2.position,
			1,
			"%u",
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		GUI_Input<uint32>
		(
			"event",
			eventData2.event,
			1,
			"%u",
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		GUI_Input<uint32>
		(
			"subevent",
			eventData2.subevent,
			1,
			"%u",
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		GUI_Input<uint32>
		(
			"screen",
			eventData2.screen,
			1,
			"%u",
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		GUI_Input<uint32>
		(
			"nextScreen",
			eventData2.nextScreen,
			1,
			"%u",
			ImGuiInputTextFlags_EnterReturnsTrue
		);

		ImGui::PopItemWidth();

		ImGui::Text("");

		if (GUI_Button("Apply"))
		{
			eventData.room       = eventData2.room;
			eventData.position   = eventData2.position;
			eventData.event      = eventData2.event;
			eventData.subevent   = eventData2.subevent;
			eventData.screen     = eventData2.screen;
			eventData.nextScreen = eventData2.nextScreen;
		}

		ImGui::Text("");
	}

	ImGui::End();
}



void RegionDataWindow()
{
	static bool run = false;
	if (!run)
	{
		run = true;
	}

	if (!showRegionDataWindow)
	{
		return;
	}

	static bool run2 = false;
	if (!run2)
	{
		run2 = true;

		ImGui::SetNextWindowSize
		(
			ImVec2
			(
				700,
				700
			)
		);
		ImGui::SetNextWindowPos
		(
			ImVec2
			(
				0,
				0
			)
		);
	}

	if (ImGui::Begin("RegionData", &showRegionDataWindow))
	{
		ImGui::Text("");



		auto GUI_RegionData = [&](RegionData & regionData)
		{
			ImGui::PushItemWidth(200);

			GUI_Input<uint64>
			(
				"metadataAddr",
				*reinterpret_cast<uint64 *>(&regionData.metadataAddr),
				0,
				"%llX",
				ImGuiInputTextFlags_CharsHexadecimal |
				ImGuiInputTextFlags_ReadOnly
			);
			GUI_Input<uint64>
			(
				"dataAddr",
				*reinterpret_cast<uint64 *>(&regionData.dataAddr),
				0,
				"%llX",
				ImGuiInputTextFlags_CharsHexadecimal |
				ImGuiInputTextFlags_ReadOnly
			);
			GUI_Input<uint32>
			(
				"capacity",
				regionData.capacity,
				0,
				"%X",
				ImGuiInputTextFlags_CharsHexadecimal |
				ImGuiInputTextFlags_ReadOnly
			);
			GUI_Input<uint32>
			(
				"boundary",
				regionData.boundary,
				0,
				"%X",
				ImGuiInputTextFlags_CharsHexadecimal |
				ImGuiInputTextFlags_ReadOnly
			);
			GUI_Input<uint32>
			(
				"size",
				regionData.size,
				0,
				"%X",
				ImGuiInputTextFlags_ReadOnly
			);
			GUI_Input<uint32>
			(
				"pipe",
				regionData.pipe,
				0,
				"%u",
				ImGuiInputTextFlags_ReadOnly
			);
			GUI_Input<uint32>
			(
				"count",
				regionData.count,
				0,
				"%u",
				ImGuiInputTextFlags_ReadOnly
			);

			ImGui::PopItemWidth();
		};

		auto regionDataAddr = reinterpret_cast<RegionData *>(appBaseAddr + 0xCA8910);
		/*
		dmc3.exe+2C61BF - 4C 8D 25 4A279E00 - lea r12,[dmc3.exe+CA8910]
		dmc3.exe+2C61C6 - 44 8B C5          - mov r8d,ebp
		*/

		static uint32 count = 3;

		GUI_Input<uint32>
		(
			"Count",
			count,
			1,
			"%u",
			ImGuiInputTextFlags_EnterReturnsTrue
		);

		old_for_all(uint32, index, count)
		{
			auto & regionData = regionDataAddr[index];

			GUI_RegionData(regionData);
			ImGui::Text("");
		}

		ImGui::Text("");
	}
	ImGui::End();
}



void SoundWindow()
{
	if (!showSoundWindow)
	{
		return;
	}

	static bool run = false;
	if (!run)
	{
		run = true;

		ImGui::SetNextWindowSize(ImVec2(600, 650));
		ImGui::SetNextWindowPos(ImVec2(0, 0));
	}

	if (ImGui::Begin("Sound", &showSoundWindow))
	{
		ImGui::Text("");



		static uint32 fmodChannelIndex = 0;
		static FMOD_CHANNEL * fmodChannelAddr = 0;
		static float volume = 1.0f;
		static FMOD_RESULT fmodResult = 0;

		ImGui::PushItemWidth(200);
		if
		(
			GUI_Input<uint32>
			(
				"FMOD Channel Index",
				fmodChannelIndex,
				1,
				"%u",
				ImGuiInputTextFlags_EnterReturnsTrue
			)
		)
		{
			fmodChannelAddr = reinterpret_cast<FMOD_CHANNEL **>(appBaseAddr + 0x5DE3E0)[fmodChannelIndex];
		}
		GUI_Input<uint64>
		(
			"FMOD Channel Address",
			*reinterpret_cast<uint64 *>(&fmodChannelAddr),
			0,
			"%llX",
			ImGuiInputTextFlags_CharsHexadecimal |
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		GUI_Input<float>
		(
			"Volume",
			volume,
			0.1f,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		ImGui::PopItemWidth();
		ImGui::Text("");

		if (GUI_Button("SetVolume"))
		{
			fmodResult = FMOD_Channel_SetVolume
			(
				fmodChannelAddr,
				volume
			);
		}

		ImGui::Text("fmodResult %X", fmodResult);



		static byte8 * headMetadataAddr = 0;

		ImGui::PushItemWidth(200);
		GUI_Input<uint64>
		(
			"Head Metadata Address",
			*reinterpret_cast<uint64 *>(&headMetadataAddr),
			0,
			"%llX",
			ImGuiInputTextFlags_CharsHexadecimal |
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		ImGui::PopItemWidth();
		ImGui::Text("");

		[&]()
		{
			if (!headMetadataAddr)
			{
				return;
			}

			auto & headMetadata = *reinterpret_cast<HeadMetadata *>(headMetadataAddr);

			auto & vagiMetadata = *reinterpret_cast<VagiMetadata *>(headMetadataAddr + headMetadata.vagiMetadataOff);



			if (ImGui::CollapsingHeader("Vagi"))
			{
				ImGui::Text("");

				ImGui::PushItemWidth(200);

				GUI_Input<uint32>
				(
					"size",
					vagiMetadata.size,
					0,
					"%X",
					ImGuiInputTextFlags_CharsHexadecimal |
					ImGuiInputTextFlags_EnterReturnsTrue
				);
				GUI_Input<uint32>
				(
					"last",
					vagiMetadata.last,
					0
				);

				ImGui::Text("");

				auto itemCount = (vagiMetadata.last + 1);

				ImGui::Text("itemCount %u", itemCount);

				old_for_all(uint32, itemIndex, itemCount)
				{
					auto & item = vagiMetadata.items[itemIndex];

					ImGui::Text("");

					ImGui::Text("%u", itemIndex);
					GUI_Input<uint32>
					(
						"off",
						item.off,
						0,
						"%X",
						ImGuiInputTextFlags_CharsHexadecimal |
						ImGuiInputTextFlags_EnterReturnsTrue
					);
					GUI_Input<uint32>
					(
						"size",
						item.size,
						0,
						"%X",
						ImGuiInputTextFlags_CharsHexadecimal |
						ImGuiInputTextFlags_EnterReturnsTrue
					);
					GUI_Input<uint32>
					(
						"sampleRate",
						item.sampleRate,
						1000,
						"%u",
						ImGuiInputTextFlags_EnterReturnsTrue
					);
				}

				ImGui::PopItemWidth();

				ImGui::Text("");
			}
		}();

		ImGui::Text("");
	}
	ImGui::End();
}



void Debug()
{
	if (ImGui::CollapsingHeader("Debug"))
	{
		ImGui::Text("");

		if (GUI_Button("Actor"))
		{
			showActorWindow = true;
		}
		ImGui::SameLine();

		if (GUI_Button("EventData"))
		{
			showEventDataWindow = true;
		}
		ImGui::SameLine();

		if (GUI_Button("File Data"))
		{
			showFileDataWindow = true;
		}
		ImGui::SameLine();

		if (GUI_Button("Mission Data"))
		{
			showMissionDataWindow = true;
		}
		ImGui::SameLine();

		if (GUI_Button("Region Data"))
		{
			showRegionDataWindow = true;
		}
		ImGui::SameLine();

		if (GUI_Button("Sound"))
		{
			showSoundWindow = true;
		}
		ImGui::Text("");

		if (GUI_Button("Close All"))
		{
			showActorWindow       = false;
			showEventDataWindow   = false;
			showFileDataWindow    = false;
			showMissionDataWindow = false;
			showRegionDataWindow  = false;
			showSoundWindow       = false;
		}
		ImGui::Text("");



		IntroduceSessionData();

		GUI_Checkbox("One Hit Kill", sessionData.oneHitKill);
		ImGui::Text("");






		if
		(
			GUI_Checkbox2
			(
				"Force Visible HUD",
				activeConfig.forceVisibleHUD,
				queuedConfig.forceVisibleHUD
			)
		)
		{
			ToggleForceVisibleHUD(activeConfig.forceVisibleHUD);
		}
		ImGui::Text("");





		{
			static ModelData * modelDataAddr = 0;
			static BodyPartData * bodyPartDataAddr = 0;
			static NewArchiveMetadata * archiveAddr = 0;

			static uint16 cacheFileIndex = em034;

			static char buffer[8];
			static byte8 * file = 0;
			static uint32 fileIndex = 0;
			
			static char subbuffer[8];
			static byte8 * subfile = 0;
			static uint32 subfileIndex = 0;




			GUI_Input<byte64>
			(
				"modelDataAddr",
				*reinterpret_cast<byte64 *>(&modelDataAddr),
				0,
				"%llX",
				ImGuiInputTextFlags_EnterReturnsTrue |
				ImGuiInputTextFlags_CharsHexadecimal
			);

			GUI_Input<byte64>
			(
				"bodyPartDataAddr",
				*reinterpret_cast<byte64 *>(&bodyPartDataAddr),
				0,
				"%llX",
				ImGuiInputTextFlags_EnterReturnsTrue |
				ImGuiInputTextFlags_CharsHexadecimal
			);

			GUI_Input<byte64>
			(
				"archiveAddr",
				*reinterpret_cast<byte64 *>(&archiveAddr),
				0,
				"%llX",
				ImGuiInputTextFlags_EnterReturnsTrue |
				ImGuiInputTextFlags_CharsHexadecimal
			);




			// @Todo: Set Archive.

			GUI_Input<uint16>
			(
				"cacheFileIndex",
				cacheFileIndex,
				1,
				"%u",
				ImGuiInputTextFlags_EnterReturnsTrue
			);





			ImGui::PushItemWidth(50);
			ImGui::InputText
			(
				"",
				buffer,
				sizeof(buffer)
			);
			ImGui::PopItemWidth();
			ImGui::SameLine();

			ImGui::PushItemWidth(150);
			GUI_Input<byte64>
			(
				"",
				*reinterpret_cast<byte64 *>(&file),
				0,
				"%llX",
				ImGuiInputTextFlags_CharsHexadecimal |
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			ImGui::SameLine();
			GUI_Input<uint32>
			(
				"",
				fileIndex
			);
			ImGui::PopItemWidth();
			ImGui::SameLine();
			if (GUI_Button("Set File"))
			{
				[&]()
				{
					if (!archiveAddr)
					{
						return;
					}
					auto & archive = *archiveAddr;



					file = archive[fileIndex];

					SetMemory
					(
						buffer,
						0,
						sizeof(buffer)
					);


					if (!file)
					{
						return;
					}

					CopyMemory
					(
						buffer,
						file,
						4
					);
				}();
			}





			ImGui::PushItemWidth(50);
			ImGui::InputText
			(
				"",
				subbuffer,
				sizeof(subbuffer)
			);
			ImGui::PopItemWidth();
			ImGui::SameLine();
			ImGui::PushItemWidth(150);
			GUI_Input<uint64>
			(
				"",
				*reinterpret_cast<uint64 *>(&subfile),
				0,
				"%llX",
				ImGuiInputTextFlags_CharsHexadecimal |
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			ImGui::SameLine();
			GUI_Input<uint32>
			(
				"",
				subfileIndex
			);
			ImGui::PopItemWidth();
			ImGui::SameLine();
			// @Todo: Update.
			if (GUI_Button("Set Subfile"))
			{
				[&]()
				{
					auto subarchive = file;
					if (!subarchive)
					{
						return;
					}

					auto & subarchiveMetadata = *reinterpret_cast<ArchiveMetadata *>(subarchive);

					if
					(
						(subarchiveMetadata.signature[0] != 'P') ||
						(subarchiveMetadata.signature[1] != 'A') ||
						(subarchiveMetadata.signature[2] != 'C')
					)
					{
						MessageBoxA
						(
							0,
							"Wrong Signature",
							0,
							0
						);

						return;
					}

					if (subfileIndex >= subarchiveMetadata.fileCount)
					{
						MessageBoxA
						(
							0,
							"Out of range.",
							0,
							0
						);

						return;
					}

					auto subfileOff = subarchiveMetadata.fileOffs[subfileIndex];
					if (!subfileOff)
					{
						return;
					}

					subfile = (file + subfileOff);

					SetMemory
					(
						subbuffer,
						0,
						sizeof(subbuffer)
					);

					if (!subfile)
					{
						return;
					}

					CopyMemory
					(
						subbuffer,
						(subfile + 4),
						3
					);
				}();
			}





			if (GUI_Button("Play File Motion"))
			{
				[&]()
				{
					//IntroduceMainActorData(actorBaseAddr, actorData, return);
					if (!modelDataAddr)
					{
						return;
					}

					func_8AC80
					(
						//actorData.newModelData[0],
						*modelDataAddr,
						UPPER_BODY,
						file,
						0,
						false
					);
					func_8AC80
					(
						//actorData.newModelData[0],
						*modelDataAddr,
						LOWER_BODY,
						file,
						0,
						false
					);
				}();
			}

			if (GUI_Button("Play Subfile Motion"))
			{
				[&]()
				{
					if (!modelDataAddr)
					{
						return;
					}
					//IntroduceMainActorData(actorBaseAddr, actorData, return);

					func_8AC80
					(
						//actorData.newModelData[0],
						*modelDataAddr,
						UPPER_BODY,
						subfile,
						0,
						false
					);
					func_8AC80
					(
						//actorData.newModelData[0],
						*modelDataAddr,
						LOWER_BODY,
						subfile,
						0,
						false
					);

					//auto bodyPartData2

					auto & done1 = *reinterpret_cast<bool *>(reinterpret_cast<byte8 *>(&bodyPartDataAddr[0]) + 0xBA) = false;
					auto & done2 = *reinterpret_cast<bool *>(reinterpret_cast<byte8 *>(&bodyPartDataAddr[1]) + 0xBA) = false;
				}();
			}




		}












		{
			static vec4   __declspec(align(16)) position   = {};
			static vec4   __declspec(align(16)) multiplier = {};
			static __m128 __declspec(align(16)) height     = {};



			GUI_Input
			(
				"position x",
				position.x,
				1.0f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input
			(
				"position y",
				position.y,
				1.0f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input
			(
				"position z",
				position.z,
				1.0f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input
			(
				"position a",
				position.a,
				1.0f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);

			GUI_Input
			(
				"multiplier x",
				multiplier.x,
				1.0f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input
			(
				"multiplier y",
				multiplier.y,
				1.0f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input
			(
				"multiplier z",
				multiplier.z,
				1.0f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input
			(
				"multiplier a",
				multiplier.a,
				1.0f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);




			GUI_Input
			(
				"height x",
				height.m128_f32[0],
				1.0f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input
			(
				"height y",
				height.m128_f32[1],
				1.0f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input
			(
				"height z",
				height.m128_f32[2],
				1.0f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input
			(
				"height a",
				height.m128_f32[3],
				1.0f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);






			if (GUI_Button("Grenade"))
			{
				//HoboBreak();

				func_175210
				(
					&position,
					&multiplier,
					height
				);
			}
		}



		{
			static uint32 event = 0;
			static uint8 action = 0;
			static uint64 actorIndex = 0;

			GUI_Input<decltype(actorIndex)>
			(
				"actorIndex",
				actorIndex,
				1,
				"%llu",
				ImGuiInputTextFlags_EnterReturnsTrue
			);

			GUI_Input<uint32>
			(
				"event",
				event,
				1,
				"%u",
				ImGuiInputTextFlags_EnterReturnsTrue
			);

			GUI_Input<decltype(action)>
			(
				"action",
				action,
				1,
				"%u",
				ImGuiInputTextFlags_EnterReturnsTrue
			);



			if (GUI_Button("Event"))
			{

				[&]()
				{
					IntroduceData(g_playerActorBaseAddrs[actorIndex], actorData, PlayerActorData, return);

					actorData.action = action;

					func_1E09D0(actorData, event);
				}();
			}
		}



		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Enemy

void Enemy()
{
	if (ImGui::CollapsingHeader("Enemy"))
	{
		ImGui::Text("");



		if (GUI_ResetButton())
		{
			ResetConfig(enemyCount);
			ResetConfig(configCreateEnemyActorData);
			ResetConfig(enemyAutoSpawn);
		}
		ImGui::Text("");



		ImGui::PushItemWidth(200);



		GUI_Slider2<uint8>
		(
			"Enemy Count",
			activeConfig.enemyCount,
			queuedConfig.enemyCount,
			1,
			static_cast<uint8>(countof(activeConfig.configCreateEnemyActorData))
		);
		ImGui::Text("");

		GUI_Checkbox2
		(
			"Auto Spawn",
			activeConfig.enemyAutoSpawn,
			queuedConfig.enemyAutoSpawn
		);
		ImGui::Text("");


		if (GUI_Button("Create All"))
		{
			old_for_all(uint8, index, activeConfig.enemyCount)
			{
				auto & activeConfigCreateEnemyActorData = activeConfig.configCreateEnemyActorData[index];

				CreateEnemyActor(activeConfigCreateEnemyActorData);
			}
		}
		ImGui::Text("");

		if (GUI_Button("Kill All Ladies"))
		{
			[&]()
			{
				IntroduceEnemyVectorData(return);

				LogFunction();

				old_for_all(uint32, enemyIndex, countof(enemyVectorData.metadata))
				{
					auto & metadata = enemyVectorData.metadata[enemyIndex];

					IntroduceData(metadata.baseAddr, actorData, EnemyActorDataLady, continue);

					if
					(
						!actorData.baseAddr ||
						(actorData.enemy != ENEMY::LADY)
					)
					{
						continue;
					}

					actorData.event = EVENT_BOSS_LADY::DEATH;
					actorData.state = 0;
					actorData.friendly = false;
				}
			}();
		}
		ImGui::Text("");



		old_for_all(uint8, index, activeConfig.enemyCount)
		{
			auto & activeConfigCreateEnemyActorData = activeConfig.configCreateEnemyActorData[index];
			auto & queuedConfigCreateEnemyActorData = queuedConfig.configCreateEnemyActorData[index];

			ImGui::Text("%.4u", index);



			GUI_Combo2
			(
				"Enemy",
				enemyNames,
				activeConfigCreateEnemyActorData.enemy,
				queuedConfigCreateEnemyActorData.enemy
			);

			GUI_Input2<uint32>
			(
				"Variant",
				activeConfigCreateEnemyActorData.variant,
				queuedConfigCreateEnemyActorData.variant,
				1,
				"%u",
				ImGuiInputTextFlags_EnterReturnsTrue
			);

			GUI_Checkbox2
			(
				"Use Main Actor Data",
				activeConfigCreateEnemyActorData.useMainActorData,
				queuedConfigCreateEnemyActorData.useMainActorData
			);



			{
				bool condition = activeConfigCreateEnemyActorData.useMainActorData;

				GUI_PushDisable(condition);

				GUI_Input2<float>
				(
					"X",
					activeConfigCreateEnemyActorData.position.x,
					queuedConfigCreateEnemyActorData.position.x,
					10.0f,
					"%g",
					ImGuiInputTextFlags_EnterReturnsTrue
				);
				GUI_Input2<float>
				(
					"Y",
					activeConfigCreateEnemyActorData.position.y,
					queuedConfigCreateEnemyActorData.position.y,
					10.0f,
					"%g",
					ImGuiInputTextFlags_EnterReturnsTrue
				);
				GUI_Input2<float>
				(
					"Z",
					activeConfigCreateEnemyActorData.position.z,
					queuedConfigCreateEnemyActorData.position.z,
					10.0f,
					"%g",
					ImGuiInputTextFlags_EnterReturnsTrue
				);


				GUI_Input2<uint16>
				(
					"Rotation",
					activeConfigCreateEnemyActorData.rotation,
					queuedConfigCreateEnemyActorData.rotation,
					1,
					"%u",
					ImGuiInputTextFlags_EnterReturnsTrue
				);

				GUI_PopDisable(condition);
			}



			GUI_Input2<uint16>
			(
				"Spawn Method",
				activeConfigCreateEnemyActorData.spawnMethod,
				queuedConfigCreateEnemyActorData.spawnMethod,
				1,
				"%u",
				ImGuiInputTextFlags_EnterReturnsTrue
			);

			if (GUI_Button("Create"))
			{
				CreateEnemyActor(activeConfigCreateEnemyActorData);
			}

			ImGui::Text("");
		}



		ImGui::PopItemWidth();
	}
}

#pragma endregion

#pragma region Jukebox

void Jukebox()
{
	if (ImGui::CollapsingHeader("Jukebox"))
	{
		ImGui::Text("");

		static char path[512];
		static char filename[256];
		static uint32 index = 0;
		static bool run = false;

		if (!run)
		{
			run = true;

			snprintf
			(
				filename,
				sizeof(filename),
				"%s",
				trackFilenames[index]
			);
		}

		ImGui::PushItemWidth(200);

		ImGui::InputText
		(
			"Filename",
			filename,
			sizeof(filename)
		);

		if
		(
			GUI_Combo
			(
				"",
				trackNames,
				index
			)
		)
		{
			snprintf
			(
				filename,
				sizeof(filename),
				"%s",
				trackFilenames[index]
			);
		}

		ImGui::PopItemWidth();

		if (GUI_Button("Play Track"))
		{
			snprintf
			(
				path,
				sizeof(path),
				"afs/sound/%s",
				filename
			);

			PlayTrack(path);
		}

		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Lady

void Lady()
{
	if (ImGui::CollapsingHeader("Lady"))
	{
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			ResetConfig(kalinaAnnHookMultiplier);
			ResetConfig(kalinaAnnHookGrenadeHeight);
			ResetConfig(kalinaAnnHookGrenadeTime);
		}

		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("Kalina Ann");



		ImGui::PushItemWidth(200.0f);

		GUI_InputDefault2<float>
		(
			"Hook Multiplier X",
			activeConfig.kalinaAnnHookMultiplier.x,
			queuedConfig.kalinaAnnHookMultiplier.x,
			defaultConfig.kalinaAnnHookMultiplier.x,
			1.0f,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		GUI_InputDefault2<float>
		(
			"Hook Multiplier Y",
			activeConfig.kalinaAnnHookMultiplier.y,
			queuedConfig.kalinaAnnHookMultiplier.y,
			defaultConfig.kalinaAnnHookMultiplier.y,
			1.0f,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		GUI_InputDefault2<float>
		(
			"Hook Multiplier Z",
			activeConfig.kalinaAnnHookMultiplier.z,
			queuedConfig.kalinaAnnHookMultiplier.z,
			defaultConfig.kalinaAnnHookMultiplier.z,
			1.0f,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		GUI_InputDefault2<float>
		(
			"Hook Multiplier A",
			activeConfig.kalinaAnnHookMultiplier.a,
			queuedConfig.kalinaAnnHookMultiplier.a,
			defaultConfig.kalinaAnnHookMultiplier.a,
			1.0f,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		);

		GUI_InputDefault2<float>
		(
			"Hook Grenade Height",
			activeConfig.kalinaAnnHookGrenadeHeight,
			queuedConfig.kalinaAnnHookGrenadeHeight,
			defaultConfig.kalinaAnnHookGrenadeHeight,
			10.0f,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		);

		GUI_InputDefault2<float>
		(
			"Hook Grenade Time",
			activeConfig.kalinaAnnHookGrenadeTime,
			queuedConfig.kalinaAnnHookGrenadeTime,
			defaultConfig.kalinaAnnHookGrenadeTime,
			10.0f,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		);

		ImGui::PopItemWidth();



		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Mobility

void Mobility()
{
	if (ImGui::CollapsingHeader("Mobility"))
	{
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			ResetConfig(airHikeCount);
			ResetConfig(kickJumpCount);
			ResetConfig(wallHikeCount);
			ResetConfig(dashCount);
			ResetConfig(skyStarCount);
			ResetConfig(airTrickCountDante);
			ResetConfig(airTrickCountVergil);
			ResetConfig(trickUpCount);
			ResetConfig(trickDownCount);
		}
		ImGui::Text("");

		TooltipHelper
		(
			"(?)",
			"Requires enabled Actor module.\n"
			"\n"
			"Left: Human Right: Devil"
		);
		ImGui::Text("");

		ActionData
		(
			"Air Hike Count",
			activeConfig.airHikeCount,
			queuedConfig.airHikeCount,
			defaultConfig.airHikeCount
		);
		ActionData
		(
			"Kick Jump Count",
			activeConfig.kickJumpCount,
			queuedConfig.kickJumpCount,
			defaultConfig.kickJumpCount
		);
		ActionData
		(
			"Wall Hike Count",
			activeConfig.wallHikeCount,
			queuedConfig.wallHikeCount,
			defaultConfig.wallHikeCount
		);
		ActionData
		(
			"Dash Count",
			activeConfig.dashCount,
			queuedConfig.dashCount,
			defaultConfig.dashCount
		);
		ActionData
		(
			"Sky Star Count",
			activeConfig.skyStarCount,
			queuedConfig.skyStarCount,
			defaultConfig.skyStarCount
		);
		ActionData
		(
			"Air Trick Count Dante",
			activeConfig.airTrickCountDante,
			queuedConfig.airTrickCountDante,
			defaultConfig.airTrickCountDante
		);
		ActionData
		(
			"Air Trick Count Vergil",
			activeConfig.airTrickCountVergil,
			queuedConfig.airTrickCountVergil,
			defaultConfig.airTrickCountVergil
		);
		ActionData
		(
			"Trick Up Count",
			activeConfig.trickUpCount,
			queuedConfig.trickUpCount,
			defaultConfig.trickUpCount
		);
		ActionData
		(
			"Trick Down Count",
			activeConfig.trickDownCount,
			queuedConfig.trickDownCount,
			defaultConfig.trickDownCount
		);

		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Other

const char * dotShadowNames[] =
{
	"Enable",
	"Disable",
	"Disable Actor Only"
};



void Other()
{
	if (ImGui::CollapsingHeader("Other"))
	{
		ImGui::Text("");



		if (GUI_ResetButton())
		{
			ResetConfig(dotShadow);
			ResetConfig(depleteQuicksilver);
			ResetConfig(depleteDoppelganger);
			ResetConfig(depleteDevil);
			ResetConfig(crazyComboLevelMultiplier);
			ResetConfig(linearWeaponSwitchTimeout);
			ResetConfig(orbReach);

			UpdateCrazyComboLevelMultiplier();
		}
		ImGui::Text("");

		ImGui::PushItemWidth(200);

		GUI_Combo2
		(
			"Dot Shadow",
			dotShadowNames,
			activeConfig.dotShadow,
			queuedConfig.dotShadow
		);

		GUI_InputDefault2
		(
			"Deplete Quicksilver",
			activeConfig.depleteQuicksilver,
			queuedConfig.depleteQuicksilver,
			defaultConfig.depleteQuicksilver,
			1.0f,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		GUI_InputDefault2
		(
			"Deplete Doppelganger",
			activeConfig.depleteDoppelganger,
			queuedConfig.depleteDoppelganger,
			defaultConfig.depleteDoppelganger,
			1.0f,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		GUI_InputDefault2
		(
			"Deplete Devil",
			activeConfig.depleteDevil,
			queuedConfig.depleteDevil,
			defaultConfig.depleteDevil,
			1.0f,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		);

		if
		(
			GUI_InputDefault2
			(
				"Crazy Combo Level Multiplier",
				activeConfig.crazyComboLevelMultiplier,
				queuedConfig.crazyComboLevelMultiplier,
				defaultConfig.crazyComboLevelMultiplier
			)
		)
		{
			UpdateCrazyComboLevelMultiplier();
		}

		GUI_InputDefault2
		(
			"Linear Weapon Switch Timeout",
			activeConfig.linearWeaponSwitchTimeout,
			queuedConfig.linearWeaponSwitchTimeout,
			defaultConfig.linearWeaponSwitchTimeout,
			1.0f,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		);

		GUI_InputDefault2
		(
			"Orb Reach",
			activeConfig.orbReach,
			queuedConfig.orbReach,
			defaultConfig.orbReach,
			100.0f,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		);

		ImGui::PopItemWidth();



		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Overlays

template <typename T>
void OverlayFunction
(
	const char * label,
	Config::OverlayData & activeData,
	Config::OverlayData & queuedData,
	T & func
)
{
	if (!activeData.enable)
	{
		return;
	}

	auto & activePos = *reinterpret_cast<ImVec2 *>(&activeData.pos);
	auto & queuedPos = *reinterpret_cast<ImVec2 *>(&queuedData.pos);

	static uint32 lastX = 0;
	static uint32 lastY = 0;

	static bool run = false;
	if (!run)
	{
		run = true;

		ImGui::SetNextWindowPos(activePos);

		lastX = static_cast<uint32>(activeData.pos.x);
		lastY = static_cast<uint32>(activeData.pos.y);
	}

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(0, 0));

	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));

	if
	(
		ImGui::Begin
		(
			label,
			&activeData.enable,
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize
		)
	)
	{
		activePos = queuedPos = ImGui::GetWindowPos();

		uint32 x = static_cast<uint32>(activeData.pos.x);
		uint32 y = static_cast<uint32>(activeData.pos.y);

		if
		(
			(lastX != x) ||
			(lastY != y)
		)
		{
			lastX = x;
			lastY = y;

			GUI_save = true;
		}

		auto & io = ImGui::GetIO();
		ImGui::PushFont(io.Fonts->Fonts[FONT::OVERLAY_16]);

		ImGui::PushStyleColor
		(
			ImGuiCol_Text,
			*reinterpret_cast<ImVec4 *>(&activeData.color)
		);

		func();

		ImGui::PopStyleColor();
		ImGui::PopFont();
	}

	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(4);
}

template
<
	typename T,
	typename T2
>
void OverlaySettings
(
	const char * label,
	T & activeData,
	T & queuedData,
	T & defaultData,
	T2 & func
)
{
	auto & activePos = *reinterpret_cast<ImVec2 *>(&activeData.pos);
	auto & queuedPos = *reinterpret_cast<ImVec2 *>(&queuedData.pos);
	auto & defaultPos = *reinterpret_cast<ImVec2 *>(&defaultData.pos);

	GUI_Checkbox2
	(
		"Enable",
		activeData.enable,
		queuedData.enable
	);
	ImGui::Text("");

	if (GUI_ResetButton())
	{
		CopyMemory
		(
			&queuedData,
			&defaultData,
			sizeof(queuedData)
		);
		CopyMemory
		(
			&activeData,
			&queuedData,
			sizeof(activeData)
		);

		ImGui::SetWindowPos(label, activePos);
	}
	ImGui::Text("");

	bool condition = !activeData.enable;

	GUI_PushDisable(condition);

	GUI_Color2
	(
		"Color",
		activeData.color,
		queuedData.color,
		ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview
	);
	ImGui::Text("");

	ImGui::PushItemWidth(150);

	if
	(
		GUI_InputDefault2<float>
		(
			"X",
			activePos.x,
			queuedPos.x,
			defaultPos.x,
			1,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		)
	)
	{
		ImGui::SetWindowPos(label, activePos);
	}
	if
	(
		GUI_InputDefault2<float>
		(
			"Y",
			activePos.y,
			queuedPos.y,
			defaultPos.y,
			1,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		)
	)
	{
		ImGui::SetWindowPos(label, activePos);
	}

	ImGui::PopItemWidth();

	func();

	GUI_PopDisable(condition);
}

template <typename T>
void OverlaySettings
(
	const char * label,
	T & activeData,
	T & queuedData,
	T & defaultData
)
{
	auto Function = [](){};

	return OverlaySettings
	(
		label,
		activeData,
		queuedData,
		defaultData,
		Function
	);
}



const char * mainOverlayLabel = "MainOverlay";

void MainOverlayWindow()
{
	auto Function = [&]()
	{
		if (activeConfig.mainOverlayData.showFocus)
		{
			ImVec4 color = ImVec4(0, 1, 0, 1);
			if (GetForegroundWindow() != appWindow)
			{
				color = ImVec4(1, 0, 0, 1);
			}
			ImGui::PushStyleColor(ImGuiCol_Text, color);
			ImGui::Text("Focus");
			ImGui::PopStyleColor();
		}

		if (activeConfig.mainOverlayData.showFPS)
		{
			ImGui::Text("%.2f FPS", ImGui::GetIO().Framerate);
		}

		if (activeConfig.mainOverlayData.showSizes)
		{
			ImGui::Text
			(
				"g_windowSize %g %g",
				g_windowSize.x,
				g_windowSize.y
			);
			ImGui::Text
			(
				"g_clientSize %g %g",
				g_clientSize.x,
				g_clientSize.y
			);
			ImGui::Text
			(
				"g_renderSize %g %g",
				g_renderSize.x,
				g_renderSize.y
			);
		}

		if (activeConfig.mainOverlayData.showScene)
		{
			if (g_scene >= SCENE::COUNT)
			{
				ImGui::Text("Unknown");
			}
			else
			{
				ImGui::Text(sceneNames[g_scene]);
			}
		}

		if (activeConfig.mainOverlayData.showEventData)
		{
			[&]()
			{
				if (g_scene != SCENE::GAME)
				{
					return;
				}

				IntroduceEventData(return);

				if (eventData.event >= EVENT::COUNT)
				{
					ImGui::Text("Unknown");
				}
				else
				{
					ImGui::Text(eventNames[eventData.event]);
				}

				ImGui::Text("%u", eventData.room);
				ImGui::Text("%u", eventData.position);
			}();
		}

		if (activeConfig.mainOverlayData.showPosition)
		{
			[&]()
			{
				if (g_scene != SCENE::GAME)
				{
					return;
				}

				IntroduceMainActorData(actorData, return);

				ImGui::Text("X %g", actorData.position.x);
				ImGui::Text("Y %g", actorData.position.y);
				ImGui::Text("Z %g", actorData.position.z);
			}();
		}

		if
		(
			activeConfig.mainOverlayData.showFocus ||
			activeConfig.mainOverlayData.showFPS ||
			activeConfig.mainOverlayData.showSizes ||
			activeConfig.mainOverlayData.showScene ||
			activeConfig.mainOverlayData.showEventData ||
			activeConfig.mainOverlayData.showPosition
		)
		{
			ImGui::Text("");
		}

		if (activeConfig.mainOverlayData.showRegionData)
		{
			ImGui::Text("Region Data");

			auto Function = [&](RegionData & regionData) -> void
			{
				ImGui::Text("metadataAddr %llX", regionData.metadataAddr);
				ImGui::Text("dataAddr     %llX", regionData.dataAddr    );
				ImGui::Text("capacity     %u"  , regionData.capacity    );
				ImGui::Text("boundary     %X"  , regionData.boundary    );
				ImGui::Text("size         %X"  , regionData.size        );
				ImGui::Text("pipe         %u"  , regionData.pipe        );
				ImGui::Text("count        %u"  , regionData.count       );
			};

			auto regionDataAddr = reinterpret_cast<RegionData *>(appBaseAddr + 0xCA8910);
			/*
			dmc3.exe+2C61BF - 4C 8D 25 4A279E00 - lea r12,[dmc3.exe+CA8910]
			dmc3.exe+2C61C6 - 44 8B C5          - mov r8d,ebp
			*/

			constexpr uint8 count = 3;

			old_for_all(uint8, index, count)
			{
				auto & regionData = regionDataAddr[index];

				ImGui::Text("%.4u", index);
				Function(regionData);
				ImGui::Text("");
			}
		}
	};

	OverlayFunction
	(
		mainOverlayLabel,
		activeConfig.mainOverlayData,
		queuedConfig.mainOverlayData,
		Function
	);
}

void MainOverlaySettings()
{
	auto Function = [&]()
	{
		GUI_Checkbox2
		(
			"Show Focus",
			activeConfig.mainOverlayData.showFocus,
			queuedConfig.mainOverlayData.showFocus
		);
		GUI_Checkbox2
		(
			"Show FPS",
			activeConfig.mainOverlayData.showFPS,
			queuedConfig.mainOverlayData.showFPS
		);
		GUI_Checkbox2
		(
			"Show Sizes",
			activeConfig.mainOverlayData.showSizes,
			queuedConfig.mainOverlayData.showSizes
		);
		GUI_Checkbox2
		(
			"Show Scene",
			activeConfig.mainOverlayData.showScene,
			queuedConfig.mainOverlayData.showScene
		);
		GUI_Checkbox2
		(
			"Show Event Data",
			activeConfig.mainOverlayData.showEventData,
			queuedConfig.mainOverlayData.showEventData
		);
		GUI_Checkbox2
		(
			"Show Position",
			activeConfig.mainOverlayData.showPosition,
			queuedConfig.mainOverlayData.showPosition
		);
		GUI_Checkbox2
		(
			"Show Region Data",
			activeConfig.mainOverlayData.showRegionData,
			queuedConfig.mainOverlayData.showRegionData
		);
	};

	OverlaySettings
	(
		mainOverlayLabel,
		activeConfig.mainOverlayData,
		queuedConfig.mainOverlayData,
		defaultConfig.mainOverlayData,
		Function
	);
}



const char * overlay2Label = "Overlay2";

bool showMemoryData = true;
bool showBackupHelper = true;
bool showActorData = true;
bool showEnemyData = true;

struct Overlay2Data : Config::OverlayData
{
	Overlay2Data()
	{
		enable = true;

		pos.x = 250;
	}
};

Overlay2Data activeOverlay2Data;
Overlay2Data queuedOverlay2Data;
Overlay2Data defaultOverlay2Data;

void Overlay2Window()
{
	auto Function = [&]()
	{
		if (showMemoryData)
		{
			ImGui::Text("Memory Data");
			ImGui::Text("pos   %u", memoryData.pos);
			ImGui::Text("end   %u", memoryData.dataSize);
			ImGui::Text("count %u", memoryData.count);
			ImGui::Text("");
		}

		if (showBackupHelper)
		{
			ImGui::Text("Backup Helper");
			ImGui::Text("pos   %u", backupHelper.pos);
			ImGui::Text("end   %u", backupHelper.dataSize);
			ImGui::Text("count %u", backupHelper.count);
			ImGui::Text("");
		}

		if (showActorData)
		{
			ImGui::Text("Actor");
			ImGui::Text("");

			ImGui::Text("Player");

			old_for_all(uint64, index, g_playerActorBaseAddrs.count)
			{
				ImGui::Text("%.4u %.16llX", index, g_playerActorBaseAddrs[index]);
			}

			ImGui::Text("");
		}

		old_for_all(uint8, index, CHANNEL::MAX)
		{
			ImGui::Text("g_helperIndices[%u] %u", index, g_helperIndices[index]);
		}
		ImGui::Text("");

		ImGui::Text("g_haywireNeoGenerator %u", g_haywireNeoGenerator);
		ImGui::Text("");


		old_for_all(uint8, playerIndex, PLAYER_COUNT)
		{
			ImGui::Text("%.4u %g", playerIndex, g_hitPoints[playerIndex]);
		}
		ImGui::Text("");

		old_for_all(uint8, playerIndex, PLAYER_COUNT)
		{
			ImGui::Text("%.4u %g", playerIndex, g_magicPoints[playerIndex]);
		}
		ImGui::Text("");




		{
			auto & gamepad = GetGamepad(0);

			ImGui::Text("Gamepad");
			ImGui::Text("");

			old_for_all(uint8, buttonIndex, 4)
			{
				ImGui::Text("buttons[%u] %X", buttonIndex, gamepad.buttons[buttonIndex]);
			}
			ImGui::Text("");
		}

		[]()
		{
			auto & newActorData = GetNewActorData(0, 0, ENTITY::MAIN);

			IntroducePlayerActorData(newActorData.baseAddr, actorData, return);

			ImGui::Text("IsActive %u", IsActive(actorData));
		}();

		if (showEnemyData)
		{
			ImGui::Text("Enemy");

			[&]()
			{
				IntroduceEnemyVectorData(return);

				ImGui::Text("count %u", enemyVectorData.count);
				ImGui::Text("");

				old_for_all(uint32, index, enemyVectorData.count)
				{
					auto & metadata = enemyVectorData.metadata[index];

					ImGui::Text("baseAddr %llX", metadata.baseAddr);

					IntroduceData(metadata.baseAddr, actorData, EnemyActorData, continue);

					ImGui::Text("speed           %g", actorData.speed          );
					ImGui::Text("speedMultiplier %g", actorData.speedMultiplier);
					ImGui::Text("enemy           %u", actorData.enemy          );
					ImGui::Text("x               %g", actorData.position.x     );
					ImGui::Text("y               %g", actorData.position.y     );
					ImGui::Text("z               %g", actorData.position.z     );
					ImGui::Text("a               %g", actorData.position.a     );

					ImGui::Text("");
				}
			}();
		}
	};

	OverlayFunction
	(
		overlay2Label,
		activeOverlay2Data,
		queuedOverlay2Data,
		Function
	);
}

void Overlay2Settings()
{
	auto Function = [&]()
	{
		GUI_Checkbox
		(
			"Show Memory Data",
			showMemoryData
		);
		GUI_Checkbox
		(
			"Show Backup Helper",
			showBackupHelper
		);
		GUI_Checkbox
		(
			"Show Actor Data",
			showActorData
		);
		GUI_Checkbox
		(
			"Show Enemy Data",
			showEnemyData
		);
	};

	OverlaySettings
	(
		overlay2Label,
		activeOverlay2Data,
		queuedOverlay2Data,
		defaultOverlay2Data,
		Function
	);
}



const char * missionOverlayLabel = "MissionOverlay";

void MissionOverlayWindow()
{
	auto Function = [&]()
	{
		ImGui::Text("Mission");

		IntroduceMissionData(return);

		auto timeData = TimeData
		(
			static_cast<float>(missionData.frameCount),
			60.0f
		);

		ImGui::Text
		(
			"Time           %02u:%02u:%02u.%03u",
			timeData.hours,
			timeData.minutes,
			timeData.seconds,
			timeData.milliseconds
		);
		ImGui::Text("Damage         %u", missionData.damage);
		ImGui::Text("Orbs Collected %u", missionData.orbsCollected);
		ImGui::Text("Items Used     %u", missionData.itemsUsed);
		ImGui::Text("Kill Count     %u", missionData.killCount);

		IntroduceMainActorData(actorData, return);

		auto stylePoints = (actorData.styleData.quotient * 100.0f);

		ImGui::Text("Style Points   %.2f", stylePoints);
	};

	OverlayFunction
	(
		missionOverlayLabel,
		activeConfig.missionOverlayData,
		queuedConfig.missionOverlayData,
		Function
	);
}

void MissionOverlaySettings()
{
	OverlaySettings
	(
		missionOverlayLabel,
		activeConfig.missionOverlayData,
		queuedConfig.missionOverlayData,
		defaultConfig.missionOverlayData
	);
}



const char * newMovesOverlayLabelDante = "NewMovesOverlayDante";

void NewMovesOverlayWindowDante()
{
	auto Function = [&]()
	{
		ImGui::Text
		(
			"New Moves Dante\n"
			"\n"
			"Rebellion\n"
			"\n"
			"While Swordmaster is active hold B and press Y, Y: Quick Drive\n"
			"Lock-On + Left + Y: Drive\n"
			"While in air Lock-On + Forward + Y: Air Stinger\n"
			"\n"
			"Nevan\n"
			"\n"
			"While in devil form and in air No Lock-On + Any Direction + Y: Quick Vortex\n"
		);
	};

	OverlayFunction
	(
		newMovesOverlayLabelDante,
		activeConfig.newMovesOverlayDataDante,
		queuedConfig.newMovesOverlayDataDante,
		Function
	);
}

void NewMovesOverlaySettingsDante()
{
	OverlaySettings
	(
		newMovesOverlayLabelDante,
		activeConfig.newMovesOverlayDataDante,
		queuedConfig.newMovesOverlayDataDante,
		defaultConfig.newMovesOverlayDataDante
	);
}



const char * newMovesOverlayLabelVergil = "NewMovesOverlayVergil";

void NewMovesOverlayWindowVergil()
{
	auto Function = [&]()
	{
		ImGui::Text
		(
			"New Moves Vergil\n"
			"\n"
			"Yamato\n"
			"\n"
			"Lock-On + Left + Y: Judgement Cut\n"
			"\n"
			"Beowulf\n"
			"\n"
			"While in air Lock-On + Forward + Y: Air Lunar Phase\n"
			"\n"
			"Yamato & Force Edge\n"
			"\n"
			"Lock-On + Left  + Y: Round Trip\n"
			"Lock-On + Right + Y: Combo Part 4\n"
			"While in air Lock-On + Forward + Y: Air Stinger\n"
		);
	};

	OverlayFunction
	(
		newMovesOverlayLabelVergil,
		activeConfig.newMovesOverlayDataVergil,
		queuedConfig.newMovesOverlayDataVergil,
		Function
	);
}

void NewMovesOverlaySettingsVergil()
{
	OverlaySettings
	(
		newMovesOverlayLabelVergil,
		activeConfig.newMovesOverlayDataVergil,
		queuedConfig.newMovesOverlayDataVergil,
		defaultConfig.newMovesOverlayDataVergil
	);
}



const char * newMovesOverlayLabelBossLady = "NewMovesOverlayBossLady";

void NewMovesOverlayWindowBossLady()
{
	auto Function = [&]()
	{
		ImGui::Text
		(
			"New Moves Boss Lady\n"
			"\n"
			"Lock-On + Forward + A: Trooper Roll\n"
			"Lock-On + Right   + A: Wheel Right\n"
			"Lock-On + Back    + A: Wheel Back\n"
			"Lock-On + Left    + A: Wheel Left\n"
			"\n"
			"Right Trigger: Reload Pistol\n"
			"Left  Trigger: Reload SMG\n"
			"\n"
			"Lock-On + Back + X: Pistol Fall Back Shoot (Hold for crossbow)\n"
			"\n"
			"B: SMG Roundhouse\n"
			"\n"
			"                    Y: Kalina Ann Hook\n"
			"Lock-On + Forward + Y: Kalina Ann Charged Shot\n"
			"Lock-On + Back    + Y: Kalina Ann Hysteric\n"
			"\n"
			"Left Shoulder: Grenades\n"
		);
	};

	OverlayFunction
	(
		newMovesOverlayLabelBossLady,
		activeConfig.newMovesOverlayDataBossLady,
		queuedConfig.newMovesOverlayDataBossLady,
		Function
	);
}

void NewMovesOverlaySettingsBossLady()
{
	OverlaySettings
	(
		newMovesOverlayLabelBossLady,
		activeConfig.newMovesOverlayDataBossLady,
		queuedConfig.newMovesOverlayDataBossLady,
		defaultConfig.newMovesOverlayDataBossLady
	);
}



const char * newMovesOverlayLabelBossVergil = "NewMovesOverlayBossVergil";

void NewMovesOverlayWindowBossVergil()
{
	auto Function = [&]()
	{
		ImGui::Text
		(
			"New Moves Boss Vergil\n"
			"\n"
			"                    Y: Yamato Deflect\n"
			"Lock-On + Forward + Y: Yamato Super Judgement Cut Follow\n"
			"Lock-On + Back    + Y: Yamato Super Judgement Cut\n"
			"\n"
			"B: Block\n"
			"\n"
			"                    X: Shield\n"
			"Lock-On + Forward + X: Strong Shield\n"
			"Lock-On + Back    + X: Strong Shield 2\n"
			"\n"
			"Left Shoulder: Toggle Devil Form\n"
			"\n"
			"Left  Trigger: Taunt\n"
			"Right Trigger: Rest in Peace\n"
		);
	};

	OverlayFunction
	(
		newMovesOverlayLabelBossVergil,
		activeConfig.newMovesOverlayDataBossVergil,
		queuedConfig.newMovesOverlayDataBossVergil,
		Function
	);
}

void NewMovesOverlaySettingsBossVergil()
{
	OverlaySettings
	(
		newMovesOverlayLabelBossVergil,
		activeConfig.newMovesOverlayDataBossVergil,
		queuedConfig.newMovesOverlayDataBossVergil,
		defaultConfig.newMovesOverlayDataBossVergil
	);
}



void Overlays()
{
	if (ImGui::CollapsingHeader("Overlays"))
	{
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			ResetConfig(mainOverlayData              );
			ResetConfig(missionOverlayData           );
			ResetConfig(newMovesOverlayDataDante     );
			ResetConfig(newMovesOverlayDataVergil    );
			ResetConfig(newMovesOverlayDataBossLady  );
			ResetConfig(newMovesOverlayDataBossVergil);

			ImGui::SetWindowPos(mainOverlayLabel              , *reinterpret_cast<ImVec2*>(&activeConfig.mainOverlayData.pos              ));
			ImGui::SetWindowPos(missionOverlayLabel           , *reinterpret_cast<ImVec2*>(&activeConfig.missionOverlayData.pos           ));
			ImGui::SetWindowPos(newMovesOverlayLabelDante     , *reinterpret_cast<ImVec2*>(&activeConfig.newMovesOverlayDataDante.pos     ));
			ImGui::SetWindowPos(newMovesOverlayLabelVergil    , *reinterpret_cast<ImVec2*>(&activeConfig.newMovesOverlayDataVergil.pos    ));
			ImGui::SetWindowPos(newMovesOverlayLabelBossLady  , *reinterpret_cast<ImVec2*>(&activeConfig.newMovesOverlayDataBossLady.pos  ));
			ImGui::SetWindowPos(newMovesOverlayLabelBossVergil, *reinterpret_cast<ImVec2*>(&activeConfig.newMovesOverlayDataBossVergil.pos));
		}

		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("Main");

		MainOverlaySettings();

		GUI_SectionEnd();
		ImGui::Text("");



		if constexpr (debug)
		{
			GUI_SectionStart("2");

			Overlay2Settings();

			GUI_SectionEnd();
			ImGui::Text("");
		}



		GUI_SectionStart("Mission");

		MissionOverlaySettings();

		GUI_SectionEnd();
		ImGui::Text("");



		GUI_SectionStart("New Moves Dante");

		NewMovesOverlaySettingsDante();

		GUI_SectionEnd();
		ImGui::Text("");



		GUI_SectionStart("New Moves Vergil");

		NewMovesOverlaySettingsVergil();

		GUI_SectionEnd();
		ImGui::Text("");



		GUI_SectionStart("New Moves Boss Lady");

		NewMovesOverlaySettingsBossLady();

		GUI_SectionEnd();
		ImGui::Text("");



		GUI_SectionStart("New Moves Boss Vergil");

		NewMovesOverlaySettingsBossVergil();



		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Repair

void Repair()
{
	if (ImGui::CollapsingHeader("Repair"))
	{
		ImGui::Text("");

		DescriptionHelper
		(
			"Fix wrong values. "
			"Can be accessed while in the mission select menu. "
			"Save your game after applying a fix."
		);
		ImGui::Text("");



		bool condition = (g_scene != SCENE::MISSION_SELECT);

		GUI_PushDisable(condition);

		if (GUI_Button("Reset Weapons"))
		{
			[&]()
			{
				IntroduceSessionData();

				SetMemory
				(
					sessionData.weapons,
					0,
					sizeof(sessionData.weapons)
				);

				switch (sessionData.character)
				{
					case CHARACTER::DANTE:
					{
						sessionData.weapons[0] = WEAPON::REBELLION;
						sessionData.weapons[1] = WEAPON::CERBERUS;
						sessionData.weapons[2] = WEAPON::EBONY_IVORY;
						sessionData.weapons[3] = WEAPON::SHOTGUN;
						sessionData.weapons[4] = WEAPON::VOID;

						break;
					}
					case CHARACTER::VERGIL:
					{
						sessionData.weapons[0] = WEAPON::YAMATO_VERGIL;
						sessionData.weapons[1] = WEAPON::BEOWULF_VERGIL;
						sessionData.weapons[2] = WEAPON::YAMATO_FORCE_EDGE;
						sessionData.weapons[3] = WEAPON::VOID;
						sessionData.weapons[4] = WEAPON::VOID;

						break;
					}
				}

				sessionData.meleeWeaponIndex = 0;
				sessionData.rangedWeaponIndex = 2;
			}();
		}



		if (GUI_Button("Reset Weapon Levels"))
		{
			[&]()
			{
				IntroduceSessionData();

				SetMemory
				(
					sessionData.rangedWeaponLevels,
					0,
					sizeof(sessionData.rangedWeaponLevels)
				);
			}();
		}

		GUI_PopDisable(condition);



		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Speed

const char * devilSpeedNamesDante[] =
{
	"Rebellion",
	"Cerberus",
	"Agni & Rudra",
	"Nevan",
	"Beowulf",
	"Sparda",
};

const char * devilSpeedNamesVergil[] =
{
	"Yamato",
	"Beowulf",
	"Yamato & Force Edge",
	"Nero Angelo Yamato",
	"Nero Angelo Beowulf",
};



// @Todo: EnterReturnsTrue.
// @Todo: Apply rounding.

template <typename T>
bool GUI_InputDefault2Speed
(
	const char * label,
	T & var,
	T & var2,
	T & defaultVar,
	const T step = 1,
	const char * format = 0,
	ImGuiInputTextFlags flags = 0
)
{
	auto update = GUI_InputDefault2
	(
		label,
		var,
		var2,
		defaultVar,
		step,
		format,
		flags
	);

	if (update)
	{
		Speed::Toggle(true);
	}

	return update;
}

void SpeedSection()
{
	if (ImGui::CollapsingHeader("Speed"))
	{
		ImGui::Text("");



		if (GUI_ResetButton())
		{
			ResetConfig(Speed);
			Speed::Toggle(false);
		}
		ImGui::Text("");

		ImGui::PushItemWidth(200);

		GUI_InputDefault2Speed
		(
			"Main",
			activeConfig.Speed.main,
			queuedConfig.Speed.main,
			defaultConfig.Speed.main,
			0.1f,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		GUI_InputDefault2Speed
		(
			"Turbo",
			activeConfig.Speed.turbo,
			queuedConfig.Speed.turbo,
			defaultConfig.Speed.turbo,
			0.1f,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		GUI_InputDefault2Speed
		(
			"Enemy Actor",
			activeConfig.Speed.enemy,
			queuedConfig.Speed.enemy,
			defaultConfig.Speed.enemy,
			0.1f,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		GUI_SectionEnd();
		ImGui::Text("");

		ImGui::Text("Player Actor");
		ImGui::SameLine();
		TooltipHelper
		(
			"(?)",
			"Requires enabled Actor module."
		);
		ImGui::Text("");

		GUI_InputDefault2Speed
		(
			"Human",
			activeConfig.Speed.human,
			queuedConfig.Speed.human,
			defaultConfig.Speed.human,
			0.1f,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		//ImGui::Text("");

		ImGui::Text("Devil Dante");

		old_for_all(uint8, index, countof(activeConfig.Speed.devilDante))
		{
			GUI_InputDefault2Speed
			(
				devilSpeedNamesDante[index],
				activeConfig.Speed.devilDante[index],
				queuedConfig.Speed.devilDante[index],
				defaultConfig.Speed.devilDante[index],
				0.1f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
		}
		//ImGui::Text("");

		ImGui::Text("Devil Vergil");

		old_for_all(uint8, index, countof(activeConfig.Speed.devilVergil))
		{
			GUI_InputDefault2Speed
			(
				devilSpeedNamesVergil[index],
				activeConfig.Speed.devilVergil[index],
				queuedConfig.Speed.devilVergil[index],
				defaultConfig.Speed.devilVergil[index],
				0.1f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
		}
		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("Quicksilver");
		GUI_InputDefault2Speed
		(
			"Actor",
			activeConfig.Speed.quicksilverPlayerActor,
			queuedConfig.Speed.quicksilverPlayerActor,
			defaultConfig.Speed.quicksilverPlayerActor,
			0.1f,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		GUI_InputDefault2Speed
		(
			"Enemy",
			activeConfig.Speed.quicksilverEnemyActor,
			queuedConfig.Speed.quicksilverEnemyActor,
			defaultConfig.Speed.quicksilverEnemyActor,
			0.1f,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		);

		ImGui::PopItemWidth();



		ImGui::Text("");
	}
}

#pragma endregion

#pragma region System

const char * Graphics_vSyncNames[] =
{
	"Auto",
	"Force Off",
	"Force On",
};

const char * Sound_channelNames[CHANNEL::MAX] =
{
	"System",
	"Common",
	"Style Weapon",
	"Weapon 1",
	"Weapon 2",
	"Weapon 3",
	"Weapon 4",
	"Enemy",
	"Room",
	"Music",
	"Demo",
};



void System()
{
	if (ImGui::CollapsingHeader("System"))
	{
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			ResetConfig(skipIntro);
			ResetConfig(skipCutscenes);
			ToggleSkipIntro    (activeConfig.skipIntro    );
			ToggleSkipCutscenes(activeConfig.skipCutscenes);

			ResetConfig(preferLocalFiles);

			ResetConfig(frameRate);
			ResetConfig(vSync);
			UpdateFrameRate();

			ResetConfig(hideMainHUD);
			ToggleHideMainHUD(activeConfig.hideMainHUD);

			ResetConfig(hideLockOn);
			ToggleHideLockOn(activeConfig.hideLockOn);

			ResetConfig(hideBossHUD);
			ToggleHideBossHUD(activeConfig.hideBossHUD);

			ResetConfig(hideMouseCursor);

			ResetConfig(channelVolumes);
			UpdateVolumes();
			ResetConfig(soundIgnoreEnemyData);

			ResetConfig(forceWindowFocus);
			Window::ToggleForceFocus(activeConfig.forceWindowFocus);
		}
		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("Event");

		if
		(
			GUI_Checkbox2
			(
				"Skip Intro",
				activeConfig.skipIntro,
				queuedConfig.skipIntro
			)
		)
		{
			ToggleSkipIntro(activeConfig.skipIntro);
		}

		if
		(
			GUI_Checkbox2
			(
				"Skip Cutscenes",
				activeConfig.skipCutscenes,
				queuedConfig.skipCutscenes
			)
		)
		{
			ToggleSkipCutscenes(activeConfig.skipCutscenes);
		}

		GUI_SectionEnd();
		ImGui::Text("");



		GUI_SectionStart("File");
		GUI_Checkbox2
		(
			"Prefer Local Files",
			activeConfig.preferLocalFiles,
			queuedConfig.preferLocalFiles
		);

		GUI_SectionEnd();
		ImGui::Text("");



		GUI_SectionStart("Graphics");

		ImGui::PushItemWidth(150);

		if (GUI_ResetButton())
		{
			ResetConfig(frameRate);
			ResetConfig(vSync);

			UpdateFrameRate();
		}
		ImGui::Text("");

		if
		(
			GUI_InputDefault2
			(
				"Frame Rate",
				activeConfig.frameRate,
				queuedConfig.frameRate,
				defaultConfig.frameRate,
				1.0,
				"%.2f",
				ImGuiInputTextFlags_EnterReturnsTrue
			)
		)
		{
			UpdateFrameRate();
		}

		GUI_Combo2
		(
			"V-Sync",
			Graphics_vSyncNames,
			activeConfig.vSync,
			queuedConfig.vSync
		);

		ImGui::PopItemWidth();

		GUI_SectionEnd();
		ImGui::Text("");



		GUI_SectionStart("HUD");

		if
		(
			GUI_Checkbox2
			(
				"Hide Main",
				activeConfig.hideMainHUD,
				queuedConfig.hideMainHUD
			)
		)
		{
			ToggleHideMainHUD(activeConfig.hideMainHUD);
		}

		if
		(
			GUI_Checkbox2
			(
				"Hide Lock-On",
				activeConfig.hideLockOn,
				queuedConfig.hideLockOn
			)
		)
		{
			ToggleHideLockOn(activeConfig.hideLockOn);
		}

		if
		(
			GUI_Checkbox2
			(
				"Hide Boss",
				activeConfig.hideBossHUD,
				queuedConfig.hideBossHUD
			)
		)
		{
			ToggleHideBossHUD(activeConfig.hideBossHUD);
		}

		GUI_SectionEnd();
		ImGui::Text("");



		GUI_SectionStart("Input");

		GUI_Checkbox2
		(
			"Hide Mouse Cursor",
			activeConfig.hideMouseCursor,
			queuedConfig.hideMouseCursor
		);

		GUI_SectionEnd();
		ImGui::Text("");



		GUI_SectionStart("Sound");

		ImGui::Text("Channel Volumes");
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			ResetConfig(channelVolumes);

			UpdateVolumes();
		}
		ImGui::Text("");

		ImGui::PushItemWidth(150);

		old_for_all(uint8, channelIndex, CHANNEL::MAX)
		{
			if
			(
				GUI_InputDefault2
				(
					Sound_channelNames[channelIndex],
					activeConfig.channelVolumes[channelIndex],
					queuedConfig.channelVolumes[channelIndex],
					defaultConfig.channelVolumes[channelIndex],
					0.1f,
					"%g",
					ImGuiInputTextFlags_EnterReturnsTrue
				)
			)
			{
				SetVolume(channelIndex, activeConfig.channelVolumes[channelIndex]);
			}
		}

		ImGui::PopItemWidth();
		ImGui::Text("");

		GUI_Checkbox2
		(
			"Ignore Enemy Data",
			activeConfig.soundIgnoreEnemyData,
			queuedConfig.soundIgnoreEnemyData
		);
		ImGui::SameLine();
		TooltipHelper
		(
			"(?)",
			"Do not look at enemy data when updating the global indices.\n"
			"Most, if not all enemies will lose their sound effects if enabled.\n"
			"Intended as a workaround for playable bosses when the sound effect\n"
			"interferences from other enemies get too annoying."
		);



		GUI_SectionEnd();
		ImGui::Text("");



		GUI_SectionStart("Window");

		if
		(
			GUI_Checkbox2
			(
				"Force Focus",
				activeConfig.forceWindowFocus,
				queuedConfig.forceWindowFocus
			)
		)
		{
			Window::ToggleForceFocus(activeConfig.forceWindowFocus);
		}

		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Teleporter

void Teleporter()
{
	if (ImGui::CollapsingHeader("Teleporter"))
	{
		ImGui::Text("");

		auto Draw = []()
		{
			if (!InGame())
			{
				return false;
			}
			IntroduceEventData(return false);
			IntroduceNextEventData(return false);

			constexpr float width = 150;

			ImGui::PushItemWidth(width);
			ImGui::Text("Current");
			GUI_Input<uint32>("", eventData.room    , 0, "%u", ImGuiInputTextFlags_ReadOnly);
			GUI_Input<uint32>("", eventData.position, 0, "%u", ImGuiInputTextFlags_ReadOnly);
			ImGui::Text("Next");
			GUI_Input<uint16>("", nextEventData.room    , 1, "%u", 0);
			GUI_Input<uint16>("", nextEventData.position, 1, "%u", 0);
			if (GUI_Button("Teleport", ImVec2(width, ImGui::GetFrameHeight())))
			{
				eventData.event = EVENT::TELEPORT;
			}
			ImGui::PopItemWidth();

			return true;
		};

		if (!Draw())
		{
			ImGui::Text("Invalid Pointer");
		}

		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Textures

void Textures()
{
	if (ImGui::CollapsingHeader("Textures"))
	{
		ImGui::Text("");

		WeaponSwitchControllerSettings();

		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Training

void TrainingSection()
{
	if (ImGui::CollapsingHeader("Training"))
	{
		ImGui::Text("");



		if (GUI_ResetButton())
		{
			ResetConfig(infiniteHitPoints);
			Training::ToggleInfiniteHitPoints(activeConfig.infiniteHitPoints);

			ResetConfig(infiniteMagicPoints);
			Training::ToggleInfiniteMagicPoints(activeConfig.infiniteMagicPoints);

			ResetConfig(disableTimer);
			Training::ToggleDisableTimer(activeConfig.disableTimer);

			ResetConfig(infiniteBullets);
			Training::ToggleInfiniteBullets(activeConfig.infiniteBullets);
		}
		ImGui::Text("");

		if
		(
			GUI_Checkbox2
			(
				"Infinite Hit Points",
				activeConfig.infiniteHitPoints,
				queuedConfig.infiniteHitPoints
			)
		)
		{
			Training::ToggleInfiniteHitPoints(activeConfig.infiniteHitPoints);
		}

		if
		(
			GUI_Checkbox2
			(
				"Infinite Magic Points",
				activeConfig.infiniteMagicPoints,
				queuedConfig.infiniteMagicPoints
			)
		)
		{
			Training::ToggleInfiniteMagicPoints(activeConfig.infiniteMagicPoints);
		}

		if
		(
			GUI_Checkbox2
			(
				"Disable Timer",
				activeConfig.disableTimer,
				queuedConfig.disableTimer
			)
		)
		{
			Training::ToggleDisableTimer(activeConfig.disableTimer);
		}

		if
		(
			GUI_Checkbox2
			(
				"Infinite Bullets",
				activeConfig.infiniteBullets,
				queuedConfig.infiniteBullets
			)
		)
		{
			Training::ToggleInfiniteBullets(activeConfig.infiniteBullets);
		}



		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Vergil

const char * dergilNames[] =
{
	"Default",
	"Force Off",
	"Force On",
};



void Vergil()
{
	if (ImGui::CollapsingHeader("Vergil"))
	{
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			ResetConfig(Yamato);

			ResetConfig(YamatoForceEdge);
			ToggleYamatoForceEdgeInfiniteRoundTrip(activeConfig.YamatoForceEdge.infiniteRoundTrip);

			ResetConfig(SummonedSwords);
			ToggleChronoSwords(activeConfig.SummonedSwords.chronoSwords);

			ResetConfig(enableYamatoVergilNewJudgementCut );
			ResetConfig(enableBeowulfVergilAirRisingSun   );
			ResetConfig(beowulfVergilAirRisingSunCount    );
			ResetConfig(enableBeowulfVergilAirLunarPhase  );
			ResetConfig(enableYamatoForceEdgeNewComboPart4);
			ResetConfig(enableYamatoForceEdgeAirStinger   );
			ResetConfig(enableYamatoForceEdgeNewRoundTrip );

			ResetConfig(dergil);
			ToggleDergil(activeConfig.dergil);
		}

		GUI_SectionEnd();
		ImGui::Text("");

		ImGui::Text("Yamato");
		ImGui::SameLine();
		TooltipHelper
		(
			"(?)",
			"Requires enabled Actor module.\n"
			"\n"
			"Left: Human Right: Devil"
		);
		ImGui::Text("");

		GUI_Checkbox2
		(
			"Enable New Judgement Cut",
			activeConfig.enableYamatoVergilNewJudgementCut,
			queuedConfig.enableYamatoVergilNewJudgementCut
		);
		ImGui::Text("");

		ActionData
		(
			"Judgement Cut Count",
			activeConfig.Yamato.judgementCutCount,
			queuedConfig.Yamato.judgementCutCount,
			defaultConfig.Yamato.judgementCutCount
		);

		GUI_SectionEnd();
		ImGui::Text("");



		GUI_SectionStart("Beowulf");

		GUI_Checkbox2
		(
			"Enable Air Rising Sun",
			activeConfig.enableBeowulfVergilAirRisingSun,
			queuedConfig.enableBeowulfVergilAirRisingSun
		);
		ImGui::Text("");

		{
			bool condition = !activeConfig.enableBeowulfVergilAirRisingSun;

			GUI_PushDisable(condition);

			ActionData
			(
				"Air Rising Sun Count",
				activeConfig.beowulfVergilAirRisingSunCount,
				queuedConfig.beowulfVergilAirRisingSunCount,
				defaultConfig.beowulfVergilAirRisingSunCount
			);

			GUI_PopDisable(condition);
		}
		ImGui::Text("");

		GUI_Checkbox2
		(
			"Enable Air Lunar Phase",
			activeConfig.enableBeowulfVergilAirLunarPhase,
			queuedConfig.enableBeowulfVergilAirLunarPhase
		);

		GUI_SectionEnd();
		ImGui::Text("");



		ImGui::Text("Yamato & Force Edge");
		ImGui::SameLine();
		TooltipHelper
		(
			"(?)",
			"Requires enabled Actor module.\n"
			"\n"
			"Left: Human Right: Devil"
		);
		ImGui::Text("");

		if
		(
			GUI_Checkbox2
			(
				"Infinite Round Trip",
				activeConfig.YamatoForceEdge.infiniteRoundTrip,
				queuedConfig.YamatoForceEdge.infiniteRoundTrip
			)
		)
		{
			ToggleYamatoForceEdgeInfiniteRoundTrip(activeConfig.YamatoForceEdge.infiniteRoundTrip);
		}
		ImGui::Text("");

		GUI_Checkbox2
		(
			"Enable New Combo Part 4",
			activeConfig.enableYamatoForceEdgeNewComboPart4,
			queuedConfig.enableYamatoForceEdgeNewComboPart4
		);
		GUI_Checkbox2
		(
			"Enable Air Stinger",
			activeConfig.enableYamatoForceEdgeAirStinger,
			queuedConfig.enableYamatoForceEdgeAirStinger
		);
		GUI_Checkbox2
		(
			"Enable New Round Trip",
			activeConfig.enableYamatoForceEdgeNewRoundTrip,
			queuedConfig.enableYamatoForceEdgeNewRoundTrip
		);
		ImGui::Text("");

		ActionData
		(
			"Stinger Duration",
			activeConfig.YamatoForceEdge.stingerDuration,
			queuedConfig.YamatoForceEdge.stingerDuration,
			defaultConfig.YamatoForceEdge.stingerDuration,
			1.0f,
			"%g"
		);
		ActionData
		(
			"Stinger Range",
			activeConfig.YamatoForceEdge.stingerRange,
			queuedConfig.YamatoForceEdge.stingerRange,
			defaultConfig.YamatoForceEdge.stingerRange,
			10.0f,
			"%g"
		);

		{
			bool condition = !activeConfig.enableYamatoForceEdgeAirStinger;

			GUI_PushDisable(condition);

			ActionData
			(
				"Air Stinger Count",
				activeConfig.YamatoForceEdge.airStingerCount,
				queuedConfig.YamatoForceEdge.airStingerCount,
				defaultConfig.YamatoForceEdge.airStingerCount
			);

			ActionData
			(
				"Air Stinger Duration",
				activeConfig.YamatoForceEdge.airStingerDuration,
				queuedConfig.YamatoForceEdge.airStingerDuration,
				defaultConfig.YamatoForceEdge.airStingerDuration,
				1.0f,
				"%g"
			);
			ActionData
			(
				"Air Stinger Range",
				activeConfig.YamatoForceEdge.airStingerRange,
				queuedConfig.YamatoForceEdge.airStingerRange,
				defaultConfig.YamatoForceEdge.airStingerRange,
				10.0f,
				"%g"
			);

			GUI_PopDisable(condition);
		}



		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("Summoned Swords");

		if
		(
			GUI_Checkbox2
			(
				"Chrono Swords",
				activeConfig.SummonedSwords.chronoSwords,
				queuedConfig.SummonedSwords.chronoSwords
			)
		)
		{
			ToggleChronoSwords(activeConfig.SummonedSwords.chronoSwords);
		}
		ImGui::SameLine();
		TooltipHelper
		(
			"(?)",
			"Requires enabled Actor module."
		);

		GUI_SectionEnd();
		ImGui::Text("");



		ImGui::PushItemWidth(150.0f);

		if
		(
			GUI_Combo2
			(
				"Dergil",
				dergilNames,
				activeConfig.dergil,
				queuedConfig.dergil
			)
		)
		{
			ToggleDergil(activeConfig.dergil);
		}

		ImGui::PopItemWidth();



		ImGui::Text("");
	}
}

#pragma endregion



#pragma region Main

void UpdateGlobalScale()
{
	auto & io = ImGui::GetIO();

	io.FontGlobalScale = activeConfig.globalScale;
}

void Main()
{
	static bool run = false;

	if (!run)
	{
		run = true;



		ImGui::SetNextWindowSize(ImVec2(600, 650));

		if constexpr (debug)
		{
			ImGui::SetNextWindowPos(ImVec2(950, 50));
		}
		else
		{
			ImGui::SetNextWindowPos(ImVec2(0, 0));
		}

		//ImGuiIO & io = ImGui::GetIO();
		//io.FontDefault = io.Fonts->Fonts[FONT::MAIN];
		//ImGui::PushFont(io.Fonts->Fonts[FONT::OVERLAY_8 + activeConfig.Tools.Overlay.fontSizeIndex]);

		//ImGui::SetCurrentFont(io.Fonts->Fonts[FONT::OVERLAY_8]);
	}

	if
	(
		ImGui::Begin
		(
			"DDMK 2.7 Mary Nightly 5 September 2021",
			&g_show
		)
	)
	{
		ImGui::Text("");



		ImGui::PushItemWidth(150);

		if
		(
			GUI_InputDefault2
			(
				"Global Scale",
				activeConfig.globalScale,
				queuedConfig.globalScale,
				defaultConfig.globalScale,
				0.1f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			)
		)
		{
			UpdateGlobalScale();
		}

		ImGui::PopItemWidth();

		ImGui::Text("");



		ImGui::Text
		(
			"If you like my work and wish to support me, consider becoming my patron.\n"
			"You can click on the button below to open my Patreon page.\n"
			"\n"
			"Cheers!"
		);
		ImGui::Text("");

		if (GUI_Button("Open Patreon Page"))
		{
			ShellExecuteA
			(
				0,
				"open",
				"https://www.patreon.com/serpentiem",
				0,
				0,
				SW_SHOW
			);
		}
		ImGui::Text("");

		ActorSection();
		ArcadeSection();
		BarsSection();
		BossRush();
		CameraSection();
		Cosmetics();
		Damage();
		Dante();

		if constexpr (debug)
		{
			Debug();
		}

		Enemy();
		Jukebox();
		Lady();
		Mobility();
		Other();
		Overlays();
		Repair();
		SpeedSection();
		System();
		Teleporter();
		Textures();
		TrainingSection();
		Vergil();



		ImGui::Text("");
	}

	ImGui::End();
}

#pragma endregion

export void GUI_Render()
{
	static bool run = false;

	if (!run)
	{
		run = true;

		// LogFunction();

		CreateTextures();
	}

	GUI_id = 0;

	MainOverlayWindow();

	if constexpr (debug)
	{
		Overlay2Window();
	}

	MissionOverlayWindow();

	NewMovesOverlayWindowDante();
	NewMovesOverlayWindowVergil();
	NewMovesOverlayWindowBossLady();
	NewMovesOverlayWindowBossVergil();

	WeaponSwitchController();

	ItemWindow();

	if (showActorWindow)
	{
		ActorWindow();
	}

	Bars();



	if (g_show)
	{
		Main();

		if constexpr (debug)
		{

			MissionDataWindow();


			FileDataWindow();
			
			EventDataWindow();
			RegionDataWindow();
			SoundWindow();
		}
	}

	[&]()
	{
		auto & save        = GUI_save;
		auto & saveTimeout = GUI_saveTimeout;

		if (saveTimeout > 0)
		{
			saveTimeout -= 1.0f;
		}
		else if (saveTimeout < 0)
		{
			saveTimeout = 0;
		}

		if (save)
		{
			if (saveTimeout > 0)
			{
				return;
			}

			save = false;

			saveTimeout = 6;

			SaveConfig();
		}
	}();

	// static bool enable = true;
	// ImGui::ShowDemoWindow(&enable);
}

export void GUI_Init()
{
	LogFunction();

	BuildFonts();

	UpdateGlobalScale();

	Actor_UpdateIndices();
	Arcade_UpdateIndices();
	Color_UpdateValues();
}

#ifdef __GARBAGE__
#endif
