// @Todo: Add description for arbitrary weapon switcher.
// @Todo: Add GUI_PushPopDisable to Arcade section.

module;
#include "../ImGui/imgui.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"
export module GUI;

import Core;

#include "../Core/Macros.h"

import Vars;

import Windows;
import DXGI;
import D3D11;

import Core_GUI;

import Actor;
import Arcade;
import Camera;
import Config;
import Enemy;
import Event;
import File;
import FMOD;
import Global;
import Graphics;
import Internal;
import Input;
import Item;
import Model;
import Scene;
import Sound;
import Speed;
import Training;
import Window;

using namespace Windows;
using namespace DXGI;
using namespace D3D11;

#define debug false





























#pragma region Common

const char * buttonNames[] =
{
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

byte16 buttons[] =
{
	GAMEPAD_LEFT_TRIGGER,
	GAMEPAD_RIGHT_TRIGGER,
	GAMEPAD_LEFT_SHOULDER,
	GAMEPAD_RIGHT_SHOULDER,
	GAMEPAD_Y,
	GAMEPAD_B,
	GAMEPAD_A,
	GAMEPAD_X,
	GAMEPAD_BACK,
	GAMEPAD_LEFT_THUMB,
	GAMEPAD_RIGHT_THUMB,
	GAMEPAD_START,
	GAMEPAD_UP,
	GAMEPAD_RIGHT,
	GAMEPAD_DOWN,
	GAMEPAD_LEFT,
};

const char * playerNames[MAX_PLAYER] =
{
	"Player 1",
	"Player 2",
	"Player 3",
	"Player 4",
};

const char * entityNames[MAX_ENTITY] =
{
	"Main",
	"Clone",
};

const char * directionNames[MAX_DIRECTION] =
{
	"Up",
	"Right",
	"Down",
	"Left",
};

const char * characterNames[] =
{
	"Dante",
	"Bob",
	"Lady",
	"Vergil",
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

uint8 stylesDante[] =
{
	STYLE_SWORDMASTER,
	STYLE_GUNSLINGER,
	STYLE_TRICKSTER,
	STYLE_ROYALGUARD,
	STYLE_QUICKSILVER,
	STYLE_DOPPELGANGER,
};

const char * styleNamesVergil[] =
{
	"Dark Slayer",
	"Quicksilver",
	"Doppelganger",
};

uint8 stylesVergil[] =
{
	STYLE_DARK_SLAYER,
	STYLE_QUICKSILVER,
	STYLE_DOPPELGANGER,
};

const char * meleeWeaponNamesDante[] =
{
	"Rebellion",
	"Cerberus",
	"Agni & Rudra",
	"Nevan",
	"Beowulf",
};

uint8 meleeWeaponsDante[] =
{
	WEAPON_REBELLION,
	WEAPON_CERBERUS,
	WEAPON_AGNI_RUDRA,
	WEAPON_NEVAN,
	WEAPON_BEOWULF_DANTE,
};

const char * meleeWeaponNamesVergil[] =
{
	"Yamato",
	"Beowulf",
	"Yamato & Force Edge",
};

uint8 meleeWeaponsVergil[] =
{
	WEAPON_YAMATO_VERGIL,
	WEAPON_BEOWULF_VERGIL,
	WEAPON_YAMATO_FORCE_EDGE,
};

const char * rangedWeaponNamesDante[] =
{
	"Ebony & Ivory",
	"Shotgun",
	"Artemis",
	"Spiral",
	"Kalina Ann",
};

uint8 rangedWeaponsDante[] =
{
	WEAPON_EBONY_IVORY,
	WEAPON_SHOTGUN,
	WEAPON_ARTEMIS,
	WEAPON_SPIRAL,
	WEAPON_KALINA_ANN,
};

const char * weaponSwitchTypeNames[] =
{
	"Linear",
	"Arbitrary",
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

uint32 modes[] =
{
	MODE_EASY,
	MODE_NORMAL,
	MODE_HARD,
	MODE_VERY_HARD,
	MODE_DANTE_MUST_DIE,
	MODE_HARD,
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
	"SCENE_BOOT",
	"SCENE_INTRO",
	"SCENE_MAIN",
	"SCENE_MISSION_SELECT",
	"SCENE_LOAD",
	"SCENE_GAME",
	"SCENE_CUTSCENE",
	"SCENE_MISSION_START",
	"SCENE_MISSION_RESULT",
	"SCENE_GAME_OVER",
};

const char * eventNames[] =
{
	"EVENT_INIT",
	"EVENT_MAIN",
	"EVENT_TELEPORT",
	"EVENT_PAUSE",
	"EVENT_STATUS",
	"EVENT_OPTIONS",
	"EVENT_DEATH",
	"EVENT_GET_ITEM",
	"EVENT_MESSAGE",
	"EVENT_CUSTOMIZE",
	"EVENT_SAVE",
	"EVENT_DELETE",
	"EVENT_END",
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

// const char * enemyNames[ENEMY_COUNT] =
// {
// 	"Pride",
// 	"Pride",
// 	"Pride",
// 	"Pride",
// 	"Gluttony",
// 	"Gluttony",
// 	"Gluttony",
// 	"Gluttony",
// 	"Lust",
// 	"Lust",
// 	"Lust",
// 	"Lust",
// 	"Sloth",
// 	"Sloth",
// 	"Sloth",
// 	"Sloth",
// 	"Wrath",
// 	"Wrath",
// 	"Wrath",
// 	"Wrath",
// 	"Greed",
// 	"Greed",
// 	"Greed",
// 	"Greed",
// 	"Abyss",
// 	"Envy",
// 	"Hell Vanguard",
// 	"Unknown",
// 	"Arachne",
// 	"The Fallen",
// 	"Dullahan",
// 	"Enigma",
// 	"Blood-Goyle",
// 	"Unknown",
// 	"Soul Eater",
// 	"Damned Chessmen Pawn",
// 	"Damned Chessmen Knight",
// 	"Damned Chessmen Bishop",
// 	"Damned Chessmen Rook",
// 	"Damned Chessmen Queen",
// 	"Damned Chessmen King",
// 	"Gigapede",
// 	"Unknown",
// 	"Cerberus",
// 	"Agni & Rudra All",
// 	"Agni & Rudra",
// 	"Agni & Rudra Black",
// 	"Agni & Rudra Red",
// 	"Agni & Rudra Blue",
// 	"Nevan",
// 	"Geryon",
// 	"Beowulf",
// 	"Doppelganger",
// 	"Arkham",
// 	"Unknown",
// 	"Lady",
// 	"Unknown",
// 	"Unknown",
// 	"Vergil",
// 	"Unknown",
// 	"Leviathan Heart",
// 	"Leviathan Other",
// 	"Jester",
// 	"Unknown",
// };

// static_assert(countof(enemyNames) == ENEMY_COUNT);

#pragma endregion

// @Todo: Update.
enum FONT_
{
	FONT_DEFAULT,
	FONT_MAIN,
	FONT_OVERLAY_8,
	FONT_OVERLAY_16,
	FONT_OVERLAY_32,
	FONT_OVERLAY_64,
	FONT_OVERLAY_128,
};

void BuildFonts()
{
	ImGuiIO & io = ImGui::GetIO();
	io.Fonts->AddFontDefault();
	char overlayFont[512];
	{
		char buffer[64];
		GetWindowsDirectoryA(buffer, sizeof(buffer));
		snprintf(overlayFont, sizeof(overlayFont), "%s\\Fonts\\consola.ttf", buffer);
	}
	io.Fonts->AddFontFromFileTTF(overlayFont, 17);
	io.Fonts->AddFontFromFileTTF(overlayFont, 8);
	io.Fonts->AddFontFromFileTTF(overlayFont, 16);
	io.Fonts->AddFontFromFileTTF(overlayFont, 32);
	io.Fonts->AddFontFromFileTTF(overlayFont, 64);
	io.Fonts->AddFontFromFileTTF(overlayFont, 128);
	io.Fonts->Build();
}

void TooltipHelper
(
	const char * name,
	const char * description
)
{
	ImGui::TextDisabled(name);
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::Text(description);
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

#pragma region Texture

// @Todo: Move to Core.

// @Research: Not neccessarily required.
struct ImageData
{
	void * addr;
	int width;
	int height;
};

ID3D11ShaderResourceView * CreateTexture(const char * filename)
{
	// Log("%s %s", FUNC_NAME, filename);

	ImageData                       imageData              = {};
	D3D11_TEXTURE2D_DESC            textureDesc            = {};
	D3D11_SUBRESOURCE_DATA          subresourceData        = {};
	ID3D11Texture2D *               texture                = 0;
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc = {};
	ID3D11ShaderResourceView *      shaderResourceView     = 0;

	imageData.addr = stbi_load
	(
		filename,
		&imageData.width,
		&imageData.height,
		0,
		4
	);

	if (!imageData.addr)
	{
		// Log("stbi_load failed. %s", filename);

		return 0;
	}

	textureDesc.Width            = imageData.width;
	textureDesc.Height           = imageData.height;
	textureDesc.MipLevels        = 1;
	textureDesc.ArraySize        = 1;
	textureDesc.Format           = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage            = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags        = D3D11_BIND_SHADER_RESOURCE;

	subresourceData.pSysMem     = imageData.addr;
	subresourceData.SysMemPitch = (textureDesc.Width * 4);

	::D3D11::device->CreateTexture2D
	(
		&textureDesc,
		&subresourceData,
		&texture
	);

	shaderResourceViewDesc.Format              = DXGI_FORMAT_R8G8B8A8_UNORM;
	shaderResourceViewDesc.ViewDimension       = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MipLevels = textureDesc.MipLevels;

	::D3D11::device->CreateShaderResourceView
	(
		texture,
		&shaderResourceViewDesc,
		&shaderResourceView
	);

	texture->Release();

	stbi_image_free(imageData.addr);

	return shaderResourceView;
}

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
		!enable      ||
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

constexpr uint8 textureWeaponMap[MAX_WEAPON] =
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

	for_all(uint8, textureIndex, TEXTURE_COUNT)
	{
		snprintf
		(
			path,
			sizeof(path),
			"images/%s",
			textureFilenames[textureIndex]
		);

		textureAddrs[textureIndex] = CreateTexture(path);
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
		for_all(uint8, index, 5)
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

			for_all(uint8, index, 5)
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

		return;
	}



	IntroduceSessionData();

	if (!InGame())
	{
		return;
	}

	IntroduceMainActorData(actorBaseAddr, actorData, return);

	auto & characterData = GetCharacterData(actorData);

	auto & gamepad = GetGamepad(actorData.newPlayerIndex);

	if
	(
		InCredits() ||
		!activeConfig.Actor.enable ||
		(characterData.meleeWeaponSwitchType != WEAPON_SWITCH_TYPE_ARBITRARY) ||
		!(
			(characterData.character == CHAR_DANTE ) ||
			(characterData.character == CHAR_VERGIL)
		)
	)
	{
		return;
	}

	if (!(gamepad.buttons[0] & GetBinding(BINDING_CHANGE_DEVIL_ARMS)))
	{
		return;
	}

	auto count = characterData.meleeWeaponCount;

	if (characterData.character == CHAR_VERGIL)
	{
		count = (IsNeroAngelo(actorData)) ? 2 : 3;
	}

	for_all(uint8, index, count)
	{
		textureData.backgrounds[index].Render
		(
			activeConfigTextureData.backgrounds[index],
			queuedConfigTextureData.backgrounds[index]
		);
	}

	{
		for_all(uint8, index, count)
		{
			auto weapon = characterData.meleeWeapons[index];
			if (weapon >= MAX_WEAPON)
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
				case WEAPON_REBELLION:
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
				case WEAPON_YAMATO_VERGIL:
				{
					if (IsNeroAngelo(actorData))
					{
						textureId = TEXTURE_WEAPON_YAMATO_NERO_ANGELO;
					}

					break;
				}
				case WEAPON_BEOWULF_VERGIL:
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
}

void RangedWeaponSwitchController()
{
	auto & textureData = rangedWeaponSwitchControllerTextureData;
	auto & activeConfigTextureData = activeConfig.rangedWeaponSwitchControllerTextureData;
	auto & queuedConfigTextureData = queuedConfig.rangedWeaponSwitchControllerTextureData;

	if (g_showTextures)
	{
		for_all(uint8, index, 5)
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

			for_all(uint8, index, 5)
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

		return;
	}



	IntroduceSessionData();

	if (!InGame())
	{
		return;
	}

	IntroduceMainActorData(actorBaseAddr, actorData, return);

	auto & characterData = GetCharacterData(actorData);

	auto & gamepad = GetGamepad(actorData.newPlayerIndex);

	if
	(
		InCredits() ||
		!activeConfig.Actor.enable ||
		(characterData.rangedWeaponSwitchType != WEAPON_SWITCH_TYPE_ARBITRARY) ||
		(characterData.character != CHAR_DANTE)
	)
	{
		return;
	}

	if (!(gamepad.buttons[0] & GetBinding(BINDING_CHANGE_GUN)))
	{
		return;
	}

	auto count = characterData.rangedWeaponCount;

	for_all(uint8, index, count)
	{
		textureData.backgrounds[index].Render
		(
			activeConfigTextureData.backgrounds[index],
			queuedConfigTextureData.backgrounds[index]
		);
	}

	{
		for_all(uint8, index, count)
		{
			auto weapon = characterData.rangedWeapons[index];
			if (weapon >= MAX_WEAPON)
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

			for_all(uint8, index, 5)
			{
				textureData.backgrounds[index] =
				{
					true,
					false,
					meleeWeaponSwitchControllerBackgroundNames[index],
					textureAddrs[TEXTURE_BACKGROUND]
				};
			}

			for_all(uint8, index, 5)
			{
				textureData.icons[index] =
				{
					true,
					false,
					meleeWeaponSwitchControllerIconNames[index]
				};
			}

			for_all(uint8, index, 5)
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

			for_all(uint8, index, 5)
			{
				textureData.backgrounds[index] =
				{
					true,
					false,
					rangedWeaponSwitchControllerBackgroundNames[index],
					textureAddrs[TEXTURE_BACKGROUND]
				};
			}

			for_all(uint8, index, 5)
			{
				textureData.icons[index] =
				{
					true,
					false,
					rangedWeaponSwitchControllerIconNames[index]
				};
			}

			for_all(uint8, index, 5)
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

		for_all(uint8, index, 5)
		{
			textureData.backgrounds[index].SetPosition(configTextureData.backgrounds[index]);
		}

		for_all(uint8, index, 5)
		{
			textureData.icons[index].SetPosition(configTextureData.icons[index]);
		}

		for_all(uint8, index, 5)
		{
			textureData.highlights[index].SetPosition(configTextureData.highlights[index]);
		}

		textureData.arrow.SetPosition(configTextureData.arrow);
	}

	// Ranged
	{
		auto & textureData = rangedWeaponSwitchControllerTextureData;
		auto & configTextureData = activeConfig.rangedWeaponSwitchControllerTextureData;

		for_all(uint8, index, 5)
		{
			textureData.backgrounds[index].SetPosition(configTextureData.backgrounds[index]);
		}

		for_all(uint8, index, 5)
		{
			textureData.icons[index].SetPosition(configTextureData.icons[index]);
		}

		for_all(uint8, index, 5)
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
	}
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

			for_all(uint32, index, count)
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

			for_all(uint32, index, count)
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

		for_all(uint8, index, 5)
		{
			textureData.backgrounds[index].Settings
			(
				activeConfigTextureData.backgrounds[index],
				queuedConfigTextureData.backgrounds[index]
			);
			ImGui::Text("");
		}

		for_all(uint8, index, 5)
		{
			textureData.icons[index].Settings
			(
				activeConfigTextureData.icons[index],
				queuedConfigTextureData.icons[index]
			);
			ImGui::Text("");
		}

		for_all(uint8, index, 5)
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

		for_all(uint8, index, 5)
		{
			textureData.backgrounds[index].Settings
			(
				activeConfigTextureData.backgrounds[index],
				queuedConfigTextureData.backgrounds[index]
			);
			ImGui::Text("");
		}

		for_all(uint8, index, 5)
		{
			textureData.icons[index].Settings
			(
				activeConfigTextureData.icons[index],
				queuedConfigTextureData.icons[index]
			);
			ImGui::Text("");
		}

		for_all(uint8, index, 5)
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

// @Todo: Re-evaluate active or queued.

const char * Actor_playerTabNames[PLAYER_COUNT] =
{
	"Player 1",
	"Player 2",
	"Player 3",
	"Player 4",
};

#define Actor_buttonNames buttonNames
#define Actor_buttons buttons

uint8 Actor_buttonIndices[PLAYER_COUNT] = {};

const char * Actor_characterTabNames[CHARACTER_COUNT] =
{
	"Character 1",
	"Character 2",
	"Character 3",
};

#define Actor_entityNames entityNames

#define Actor_characterNames characterNames

#define Actor_styleButtonNames buttonNames
#define Actor_styleButtons buttons

uint8 Actor_styleButtonIndices[PLAYER_COUNT][CHARACTER_COUNT][ENTITY_COUNT][STYLE_COUNT] = {};

#define Actor_styleNamesDante styleNamesDante
#define Actor_stylesDante stylesDante

#define Actor_styleNamesVergil styleNamesVergil
#define Actor_stylesVergil stylesVergil

uint8 Actor_styleIndices[PLAYER_COUNT][CHARACTER_COUNT][ENTITY_COUNT][STYLE_COUNT][2] = {};

#define Actor_meleeWeaponNamesDante meleeWeaponNamesDante
#define Actor_meleeWeaponsDante meleeWeaponsDante
#define Actor_meleeWeaponNamesVergil meleeWeaponNamesVergil
#define Actor_meleeWeaponsVergil meleeWeaponsVergil

uint8 Actor_meleeWeaponIndices[PLAYER_COUNT][CHARACTER_COUNT][ENTITY_COUNT][MELEE_WEAPON_COUNT] = {};

#define Actor_rangedWeaponNamesDante rangedWeaponNamesDante
#define Actor_rangedWeaponsDante rangedWeaponsDante

uint8 Actor_rangedWeaponIndices[PLAYER_COUNT][CHARACTER_COUNT][ENTITY_COUNT][RANGED_WEAPON_COUNT] = {};

#define Actor_weaponSwitchTypeNames weaponSwitchTypeNames

void Actor_UpdateIndices()
{
	// LogFunction();

	for_all(uint8, playerIndex, PLAYER_COUNT)
	{
		auto & playerData = GetPlayerData(playerIndex);

		UpdateMapIndex
		(
			Actor_buttons,
			Actor_buttonIndices[playerIndex],
			playerData.button
		);

		for_all(uint8, characterIndex, CHARACTER_COUNT){
		for_all(uint8, entityIndex   , ENTITY_COUNT   )
		{
			auto & characterData = GetCharacterData
			(
				playerIndex,
				characterIndex,
				entityIndex
			);

			for_all(uint8, styleIndex, STYLE_COUNT)
			{
				UpdateMapIndex
				(
					Actor_styleButtons,
					Actor_styleButtonIndices[playerIndex][characterIndex][entityIndex][styleIndex],
					characterData.styleButtons[styleIndex]
				);

				switch (characterData.character)
				{
					case CHAR_DANTE:
					{
						UpdateMapIndex
						(
							Actor_stylesDante,
							Actor_styleIndices[playerIndex][characterIndex][entityIndex][styleIndex][0],
							characterData.styles[styleIndex][0]
						);
						UpdateMapIndex
						(
							Actor_stylesDante,
							Actor_styleIndices[playerIndex][characterIndex][entityIndex][styleIndex][1],
							characterData.styles[styleIndex][1]
						);

						break;
					}
					case CHAR_VERGIL:
					{
						UpdateMapIndex
						(
							Actor_stylesVergil,
							Actor_styleIndices[playerIndex][characterIndex][entityIndex][styleIndex][0],
							characterData.styles[styleIndex][0]
						);
						UpdateMapIndex
						(
							Actor_stylesVergil,
							Actor_styleIndices[playerIndex][characterIndex][entityIndex][styleIndex][1],
							characterData.styles[styleIndex][1]
						);

						break;
					}
				}
			}

			if (characterData.character != CHAR_DANTE)
			{
				continue;
			}

			for_all(uint8, meleeWeaponIndex, MELEE_WEAPON_COUNT_DANTE)
			{
				UpdateMapIndex
				(
					Actor_meleeWeaponsDante,
					Actor_meleeWeaponIndices[playerIndex][characterIndex][entityIndex][meleeWeaponIndex],
					characterData.meleeWeapons[meleeWeaponIndex]
				);
			}

			for_all(uint8, rangedWeaponIndex, RANGED_WEAPON_COUNT_DANTE)
			{
				UpdateMapIndex
				(
					Actor_rangedWeaponsDante,
					Actor_rangedWeaponIndices[playerIndex][characterIndex][entityIndex][rangedWeaponIndex],
					characterData.rangedWeapons[rangedWeaponIndex]
				);
			}
		}}
	}
}

void Actor_CharacterTab
(
	uint8 playerIndex,
	uint8 characterIndex,
	uint8 entityIndex
)
{
	ImGui::Text(Actor_entityNames[entityIndex]);
	ImGui::Text("");

	auto & activeCharacterData = GetActiveCharacterData
	(
		playerIndex,
		characterIndex,
		entityIndex
	);
	auto & queuedCharacterData = GetQueuedCharacterData
	(
		playerIndex,
		characterIndex,
		entityIndex
	);

	ImGui::PushItemWidth(150);
	if
	(
		GUI_Combo2
		(
			"Character",
			Actor_characterNames,
			activeCharacterData.character,
			queuedCharacterData.character
		)
	)
	{
		ApplyDefaultCharacterData(activeCharacterData, activeCharacterData.character);
		ApplyDefaultCharacterData(queuedCharacterData, queuedCharacterData.character);

		Actor_UpdateIndices();
	}
	ImGui::PopItemWidth();

	if
	(
		(activeCharacterData.character == CHAR_BOB ) ||
		(activeCharacterData.character == CHAR_LADY)
	)
	{
		return;
	}

	ImGui::PushItemWidth(150);

	// Costume
	{
		bool condition = activeCharacterData.ignoreCostume;

		GUI_PushDisable(condition);

		GUI_Input2
		(
			"Costume",
			activeCharacterData.costume,
			queuedCharacterData.costume
		);

		GUI_PopDisable(condition);

		ImGui::SameLine();

		GUI_Checkbox2
		(
			"Ignore",
			activeCharacterData.ignoreCostume,
			queuedCharacterData.ignoreCostume
		);
	}

	GUI_Checkbox2
	(
		"Force Files",
		activeCharacterData.forceFiles,
		queuedCharacterData.forceFiles
	);
	{
		bool condition = !activeCharacterData.forceFiles;
		GUI_PushDisable(condition);
		GUI_Combo2
		(
			"Character",
			Actor_characterNames,
			activeCharacterData.forceFilesCharacter,
			queuedCharacterData.forceFilesCharacter
		);
		// GUI_Combo2
		// (
		// 	"Costume",
		// 	Actor_characterNames,
		// 	activeCharacterData.forceFilesCostume,
		// 	queuedCharacterData.forceFilesCostume
		// );

		GUI_Input2
		(
			"Costume",
			activeCharacterData.forceFilesCostume,
			queuedCharacterData.forceFilesCostume
		);





		GUI_PopDisable(condition);
	}
	ImGui::PopItemWidth();
	ImGui::Text("");

	ImGui::Text("Styles");
	ImGui::PushItemWidth(150);
	for_all(uint8, styleIndex, STYLE_COUNT)
	{
		if constexpr (debug)
		{
			ImGui::Text("");
			ImGui::Text("%u", styleIndex);
		}

		GUI_ComboMap2
		(
			"",
			Actor_styleButtonNames,
			Actor_styleButtons,
			Actor_styleButtonIndices[playerIndex][characterIndex][entityIndex][styleIndex],
			activeCharacterData.styleButtons[styleIndex],
			queuedCharacterData.styleButtons[styleIndex],
			ImGuiComboFlags_HeightLargest
		);

		if constexpr (!debug)
		{
			ImGui::SameLine();
		}

		switch (queuedCharacterData.character)
		{
			case CHAR_DANTE:
			{
				GUI_ComboMap2
				(
					"",
					styleNamesDante,
					stylesDante,
					Actor_styleIndices[playerIndex][characterIndex][entityIndex][styleIndex][0],
					activeCharacterData.styles[styleIndex][0],
					queuedCharacterData.styles[styleIndex][0]
				);
				if constexpr (!debug)
				{
					ImGui::SameLine();
				}
				GUI_ComboMap2
				(
					"",
					styleNamesDante,
					stylesDante,
					Actor_styleIndices[playerIndex][characterIndex][entityIndex][styleIndex][1],
					activeCharacterData.styles[styleIndex][1],
					queuedCharacterData.styles[styleIndex][1]
				);

				break;
			}
			case CHAR_VERGIL:
			{
				GUI_ComboMap2
				(
					"",
					styleNamesVergil,
					stylesVergil,
					Actor_styleIndices[playerIndex][characterIndex][entityIndex][styleIndex][0],
					activeCharacterData.styles[styleIndex][0],
					queuedCharacterData.styles[styleIndex][0]
				);
				if constexpr (!debug)
				{
					ImGui::SameLine();
				}
				GUI_ComboMap2
				(
					"",
					styleNamesVergil,
					stylesVergil,
					Actor_styleIndices[playerIndex][characterIndex][entityIndex][styleIndex][1],
					activeCharacterData.styles[styleIndex][1],
					queuedCharacterData.styles[styleIndex][1]
				);

				break;
			}
		}
	}
	ImGui::PopItemWidth();

	bool condition =
	(
		(
			(playerIndex == 0) &&
			(entityIndex == ENTITY_MAIN)
		) ||
		(queuedCharacterData.character == CHAR_DANTE)
	);

	if (condition)
	{
		ImGui::Text("");
		ImGui::Text("Melee Weapons");

		ImGui::PushItemWidth(200);
	}

	if
	(
		(playerIndex == 0) &&
		(entityIndex == ENTITY_MAIN)
	)
	{
		GUI_Combo2
		(
			"",
			Actor_weaponSwitchTypeNames,
			activeCharacterData.meleeWeaponSwitchType,
			queuedCharacterData.meleeWeaponSwitchType
		);

		ImGui::SameLine();

		switch (queuedCharacterData.meleeWeaponSwitchType)
		{
			case WEAPON_SWITCH_TYPE_LINEAR:
			{
				TooltipHelper
				(
					"(?)",
					"Hold the taunt button during the switch to go back."
				);

				break;
			}
			case WEAPON_SWITCH_TYPE_ARBITRARY:
			{
				TooltipHelper
				(
					"(?)",
					"Hold the weapon switch button and select a weapon with the right stick."
				);

				break;
			}
		}
	}

	if (queuedCharacterData.character == CHAR_DANTE)
	{
		GUI_Slider2<uint8>
		(
			"",
			activeCharacterData.meleeWeaponCount,
			queuedCharacterData.meleeWeaponCount,
			1,
			MELEE_WEAPON_COUNT_DANTE
		);
		for_all(uint8, meleeWeaponIndex, MELEE_WEAPON_COUNT_DANTE)
		{
			bool condition = (meleeWeaponIndex >= queuedCharacterData.meleeWeaponCount);
			GUI_PushDisable(condition);
			GUI_ComboMap2
			(
				"",
				Actor_meleeWeaponNamesDante,
				Actor_meleeWeaponsDante,
				Actor_meleeWeaponIndices[playerIndex][characterIndex][entityIndex][meleeWeaponIndex],
				activeCharacterData.meleeWeapons[meleeWeaponIndex],
				queuedCharacterData.meleeWeapons[meleeWeaponIndex]
			);
			GUI_PopDisable(condition);
		}
	}

	if (condition)
	{
		ImGui::PopItemWidth();
	}

	if (queuedCharacterData.character != CHAR_DANTE)
	{
		return;
	}

	ImGui::Text("");
	ImGui::Text("Ranged Weapons");

	ImGui::PushItemWidth(200);

	if
	(
		(playerIndex == 0) &&
		(entityIndex == ENTITY_MAIN)
	)
	{
		GUI_Combo2
		(
			"",
			Actor_weaponSwitchTypeNames,
			activeCharacterData.rangedWeaponSwitchType,
			queuedCharacterData.rangedWeaponSwitchType
		);

		ImGui::SameLine();

		switch (queuedCharacterData.rangedWeaponSwitchType)
		{
			case WEAPON_SWITCH_TYPE_LINEAR:
			{
				TooltipHelper
				(
					"(?)",
					"Hold the taunt button during the switch to go back."
				);

				break;
			}
			case WEAPON_SWITCH_TYPE_ARBITRARY:
			{
				TooltipHelper
				(
					"(?)",
					"Hold the weapon switch button and select a weapon with the right stick."
				);

				break;
			}
		}
	}

	GUI_Slider2<uint8>
	(
		"",
		activeCharacterData.rangedWeaponCount,
		queuedCharacterData.rangedWeaponCount,
		1,
		RANGED_WEAPON_COUNT_DANTE
	);
	for_all(uint8, rangedWeaponIndex, RANGED_WEAPON_COUNT_DANTE)
	{
		bool condition = (rangedWeaponIndex >= queuedCharacterData.rangedWeaponCount);
		GUI_PushDisable(condition);
		GUI_ComboMap2
		(
			"",
			Actor_rangedWeaponNamesDante,
			Actor_rangedWeaponsDante,
			Actor_rangedWeaponIndices[playerIndex][characterIndex][entityIndex][rangedWeaponIndex],
			activeCharacterData.rangedWeapons[rangedWeaponIndex],
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

	ImGui::PushItemWidth(200);
	GUI_ComboMap2
	(
		"Button",
		Actor_buttonNames,
		Actor_buttons,
		Actor_buttonIndices[playerIndex],
		activePlayerData.button,
		queuedPlayerData.button,
		ImGuiComboFlags_HeightLargest
	);
	ImGui::PopItemWidth();
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

	ImGui::PushItemWidth(200);
	GUI_Slider2<uint8>
	(
		"Character Count",
		activePlayerData.characterCount,
		queuedPlayerData.characterCount,
		1,
		CHARACTER_COUNT
	);
	ImGui::PopItemWidth();
	ImGui::Text("");

	if (ImGui::BeginTabBar("CharacterTabs"))
	{
		for_all(uint8, characterIndex, CHARACTER_COUNT)
		{
			auto condition = (characterIndex >= activePlayerData.characterCount);

			GUI_PushDisable(condition);

			if (ImGui::BeginTabItem(Actor_characterTabNames[characterIndex]))
			{
				ImGui::Text("");

				for_all(uint8, entityIndex, ENTITY_COUNT)
				{
					Actor_CharacterTab
					(
						playerIndex,
						characterIndex,
						entityIndex
					);

					if (entityIndex < (ENTITY_COUNT - 1))
					{
						ImGui::Text("");
					}
				}

				ImGui::EndTabItem();
			}

			GUI_PopDisable(condition);
		}

		ImGui::EndTabBar();
	}
}

void Actor()
{
	if (ImGui::CollapsingHeader("Actor"))
	{
		ImGui::Text("");

		DescriptionHelper("Custom actor creation and spawn system. Required for many features like character-, style- and weapon-switching.");
		ImGui::Text("");

		if
		(
			GUI_Checkbox
			(
				"Enable",
				queuedConfig.Actor.enable
			)
		)
		{
			if
			(
				// @Todo: Add SCENE_BOOT.
				(g_scene == SCENE_MAIN          ) ||
				(g_scene == SCENE_MISSION_SELECT)
			)
			{
				activeConfig.Actor.enable = queuedConfig.Actor.enable;

				Actor_Toggle(activeConfig.Actor.enable);
				Sound::ToggleRelocations(activeConfig.Actor.enable);
			}
		}
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			auto enable = activeConfig.Actor.enable;

			ResetConfig(Actor);
			ResetConfig(removeBusyFlag);
			ResetConfig(resetPermissions);

			Actor_UpdateIndices();

			if
			(
				(g_scene == SCENE_MAIN          ) ||
				(g_scene == SCENE_MISSION_SELECT)
			)
			{
				Actor_Toggle(activeConfig.Actor.enable);
				Sound::ToggleRelocations(activeConfig.Actor.enable);
			}
			else
			{
				activeConfig.Actor.enable = enable;
			}
		}
		ImGui::Text("");

		ImGui::PushItemWidth(200);
		GUI_Slider2<uint8>
		(
			"Player Count",
			activeConfig.Actor.playerCount,
			queuedConfig.Actor.playerCount,
			1,
			PLAYER_COUNT
		);
		ImGui::PopItemWidth();
		ImGui::Text("");

		if (ImGui::BeginTabBar("PlayerTabs"))
		{
			for_all(uint8, playerIndex, PLAYER_COUNT)
			{
				auto condition = (playerIndex >= queuedConfig.Actor.playerCount);

				GUI_PushDisable(condition);

				if (ImGui::BeginTabItem(Actor_playerTabNames[playerIndex]))
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
			"Remove Busy Flag",
			activeConfig.removeBusyFlag,
			queuedConfig.removeBusyFlag
		);
		ImGui::SameLine();
		TooltipHelper
		(
			"(?)",
			"Removes the actor's busy flag when switching styles.\n"
			"Allows you to do insane combos or just look stupid."
		);

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
	}
}

#pragma endregion

#pragma region Arcade

#define Arcade_missionNames missionNames

#define Arcade_modeNames modeNames
#define Arcade_modes modes
uint8 Arcade_modeIndex = 0;

#define Arcade_floorNames floorNames

#define Arcade_meleeWeaponNamesDante meleeWeaponNamesDante
#define Arcade_meleeWeaponsDante meleeWeaponsDante
uint8 Arcade_meleeWeaponIndexDante[2] = {};

#define Arcade_rangedWeaponNamesDante rangedWeaponNamesDante
#define Arcade_rangedWeaponsDante rangedWeaponsDante
uint8 Arcade_rangedWeaponIndexDante[2] = {};

void Arcade_UpdateIndices()
{
	// LogFunction();

	UpdateMapIndex
	(
		Arcade_modes,
		Arcade_modeIndex,
		activeConfig.Arcade.mode
	);

	UpdateMapIndex
	(
		Arcade_meleeWeaponsDante,
		Arcade_meleeWeaponIndexDante[0],
		activeConfig.Arcade.weapons[0]
	);

	UpdateMapIndex
	(
		Arcade_meleeWeaponsDante,
		Arcade_meleeWeaponIndexDante[1],
		activeConfig.Arcade.weapons[1]
	);

	UpdateMapIndex
	(
		Arcade_rangedWeaponsDante,
		Arcade_rangedWeaponIndexDante[0],
		activeConfig.Arcade.weapons[2]
	);

	UpdateMapIndex
	(
		Arcade_rangedWeaponsDante,
		Arcade_rangedWeaponIndexDante[1],
		activeConfig.Arcade.weapons[3]
	);
}

void Arcade()
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
			Arcade_Toggle(activeConfig.Arcade.enable);
		}
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			ResetConfig(Arcade);

			Arcade_UpdateIndices();

			Arcade_Toggle(activeConfig.Arcade.enable);
		}
		ImGui::Text("");

		ImGui::PushItemWidth(200);

		GUI_Combo2
		(
			"Mission",
			Arcade_missionNames,
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
				Arcade_modeNames,
				Arcade_modes,
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
				Arcade_floorNames,
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
			(activeConfig.Arcade.character == CHAR_DANTE)
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

#pragma region Boss Rush

void BossRush()
{
	if (ImGui::CollapsingHeader("Boss Rush"))
	{
		ImGui::Text("");

		ImGui::Text("Go directly to the boss battle.");
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

void Camera()
{
	if (ImGui::CollapsingHeader("Camera"))
	{
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			ResetConfig(Camera);
			ResetConfig(disableCenterCamera);

			Camera_ToggleInvertX(activeConfig.Camera.invertX);

			[]()
			{
				if (g_scene != SCENE_GAME)
				{
					return;
				}

				IntroduceCameraData(return);

				cameraData.height         = activeConfig.Camera.height;
				cameraData.tilt           = activeConfig.Camera.tilt;
				cameraData.distance       = activeConfig.Camera.distance;
				cameraData.distanceLockOn = activeConfig.Camera.distanceLockOn;
			}();
		}
		ImGui::Text("");

		if
		(
			GUI_Checkbox2
			(
				"Invert X",
				activeConfig.Camera.invertX,
				queuedConfig.Camera.invertX
			)
		)
		{
			Camera_ToggleInvertX(activeConfig.Camera.invertX);
		}

		GUI_Checkbox2
		(
			"Disable Center Camera",
			activeConfig.disableCenterCamera,
			queuedConfig.disableCenterCamera
		);

		[]()
		{
			if (g_scene != SCENE_GAME)
			{
				return;
			}

			IntroduceCameraData(return);

			GUI_SectionEnd();
			ImGui::Text("");

			TooltipHelper
			(
				"(?)",
				"Left: Live Right: Config"
			);
			ImGui::Text("");

			GUI_InputDefault2Camera
			(
				"Height",
				cameraData.height,
				activeConfig.Camera.height,
				queuedConfig.Camera.height,
				defaultConfig.Camera.height,
				10.0f,
				"%.0f",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_InputDefault2Camera
			(
				"Tilt",
				cameraData.tilt,
				activeConfig.Camera.tilt,
				queuedConfig.Camera.tilt,
				defaultConfig.Camera.tilt,
				0.05f,
				"%.2f",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_InputDefault2Camera
			(
				"Distance",
				cameraData.distance,
				activeConfig.Camera.distance,
				queuedConfig.Camera.distance,
				defaultConfig.Camera.distance,
				10.0f,
				"%.0f",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_InputDefault2Camera
			(
				"Distance Lock-On",
				cameraData.distanceLockOn,
				activeConfig.Camera.distanceLockOn,
				queuedConfig.Camera.distanceLockOn,
				defaultConfig.Camera.distanceLockOn,
				10.0f,
				"%.0f",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			ImGui::Text("");

			GUI_Checkbox2
			(
				"Apply Config",
				activeConfig.Camera.applyConfig,
				queuedConfig.Camera.applyConfig
			);
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

	for_all(uint8, index, itemCount)
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

			ResetConfig(hideBeowulfDante);
			ResetConfig(hideBeowulfVergil);
			ResetConfig(noDevilForm);

			Color_UpdateValues();
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
		GUI_Checkbox2
		(
			"No Devil Form",
			activeConfig.noDevilForm,
			queuedConfig.noDevilForm
		);

		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Damage

#define Damage_styleRankNames styleRankNames

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
			Damage_styleRankNames,
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
			ResetConfig(Royalguard);
			ResetConfig(Rebellion);
			ResetConfig(EbonyIvory);
			ResetConfig(Artemis);

			ToggleAirHikeCoreAbility               (activeConfig.airHikeCoreAbility                );
			ToggleRoyalguardForceJustFrameRelease  (activeConfig.Royalguard.forceJustFrameRelease  );
			ToggleRebellionInfiniteSwordPierce     (activeConfig.Rebellion.infiniteSwordPierce     );
			ToggleEbonyIvoryFoursomeTime           (activeConfig.EbonyIvory.foursomeTime           );
			ToggleEbonyIvoryInfiniteRainStorm      (activeConfig.EbonyIvory.infiniteRainStorm      );
			ToggleArtemisSwapNormalShotAndMultiLock(activeConfig.Artemis.swapNormalShotAndMultiLock);
			ToggleArtemisInstantFullCharge         (activeConfig.Artemis.instantFullCharge         );
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

bool showFileDataWindow = false;
bool showRegionDataWindow = false;
bool showSoundWindow = false;

bool showMissionDataWindow = false;

//bool showItemWindow = true;




// @Todo: Move to Vars.






















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

		// auto GetBuyIndex = [&](uint8 itemIndex) -> uint8
		// {
		// 	switch (itemIndex)
		// 	{
		// 		case ITEM_VITAL_STAR_SMALL:
		// 		{
		// 			return BUY_VITAL_STAR_SMALL;
		// 		}
		// 		case ITEM_VITAL_STAR_LARGE:
		// 		{
		// 			return BUY_VITAL_STAR_LARGE;
		// 		}
		// 		case ITEM_DEVIL_STAR:
		// 		{
		// 			return BUY_DEVIL_STAR;
		// 		}
		// 		case ITEM_HOLY_WATER:
		// 		{
		// 			return BUY_HOLY_WATER;
		// 		}
		// 		case ITEM_BLUE_ORB:
		// 		{
		// 			return BUY_BLUE_ORB;
		// 		}
		// 		case ITEM_PURPLE_ORB:
		// 		{
		// 			return BUY_PURPLE_ORB;
		// 		}
		// 		case ITEM_GOLD_ORB:
		// 		{
		// 			return BUY_GOLD_ORB;
		// 		}
		// 		case ITEM_YELLOW_ORB:
		// 		{
		// 			return BUY_YELLOW_ORB;
		// 		}
		// 	}

		// 	return 0;
		// };

		// auto GetMaxItemCount = [&](uint8 itemIndex)
		// {
		// 	switch (itemIndex)
		// 	{
		// 		case ITEM_VITAL_STAR_SMALL:
		// 		case ITEM_VITAL_STAR_LARGE:
		// 		{
		// 			return 30;
		// 		}
		// 		case ITEM_DEVIL_STAR:
		// 		{
		// 			return 10;
		// 		}
		// 		case ITEM_HOLY_WATER:
		// 		{
		// 			return 30;
		// 		}
		// 		case ITEM_BLUE_ORB:
		// 		{
		// 			return 6;
		// 		}
		// 		case ITEM_PURPLE_ORB:
		// 		{
		// 			return 7;
		// 		}
		// 		case ITEM_GOLD_ORB:
		// 		{
		// 			return 3;
		// 		}
		// 		case ITEM_YELLOW_ORB:
		// 		{
		// 			return 99;
		// 		}
		// 	}

		// 	return 0;
		// };















		// auto GetItemPrice = [&](uint8 itemIndex) -> uint32
		// {
		// 	if (itemIndex >= ITEM_COUNT)
		// 	{
		// 		itemIndex = 0;
		// 	}

		// 	auto buyIndex = GetBuyIndex(itemIndex);

		// 	auto & itemCount = missionData.itemCounts[itemIndex];
		// 	auto & buyCount = missionData.buyCounts[buyIndex];

		// 	const uint32 * prices = 0;
		// 	uint8 priceCount = 0;



		// 	switch (itemIndex)
		// 	{
		// 		case ITEM_VITAL_STAR_SMALL:
		// 		{
		// 			prices = itemVitalStarSmallPrices;

		// 			priceCount = countof(itemVitalStarSmallPrices);

		// 			break;
		// 		}
		// 	}



		// 	if (!prices)
		// 	{
		// 		return 0;
		// 	}



		// 	uint32 price = 0;

		// 	if (buyCount >= priceCount)
		// 	{
		// 		price = prices[(priceCount - 1)];
		// 	}
		// 	else
		// 	{
		// 		price = prices[buyCount];
		// 	}

		// 	return price;
		// };


		// for_all(uint8, itemHelperIndex, countof(itemHelpers))
		// {
		// 	auto & itemHelper = itemHelpers[itemHelperIndex];

		// 	auto & itemCount = missionData.itemCounts[itemHelper.itemIndex];
		// 	auto & buyCount = missionData.buyCounts[itemHelper.buyIndex];

		// 	uint32 price = 0;

		// 	if (buyCount >= itemHelper.priceCount)
		// 	{
		// 		price = itemHelper.prices[(itemHelper.priceCount - 1)];
		// 	}
		// 	else
		// 	{
		// 		price = itemHelper.prices[buyCount];
		// 	}


		// 	// if constexpr (debug)
		// 	// {
		// 	// 	ImGui::Text("%.4u", itemHelperIndex);
		// 	// 	ImGui::SameLine();
		// 	// }


		// 	ImGui::Text("%u", price);
		// 	ImGui::SameLine(60);

		// 	ImGui::Text("%s", itemNames[itemHelper.itemIndex]);
		// 	ImGui::SameLine(190);


		// 	// ImGui::Text
		// 	// (
		// 	// 	"%u",
		// 	// 	itemHelperIndex,
		// 	// 	price,
		// 	// 	itemNames[itemHelper.itemIndex]
		// 	// );
		// 	// ImGui::SameLine(200);

		// 	ImGui::Text("%.2u / %.2u", itemCount, itemHelper.itemCount);
		// 	ImGui::SameLine();





		// 	// if constexpr (debug)
		// 	// {
				
		// 	// 	ImGui::Text("%u", buyCount);
		// 	// 	ImGui::SameLine();
		// 	// }



			
			




		// 	auto BuyItem = [&]()
		// 	{
		// 		if
		// 		(
		// 			(itemCount >= itemHelper.itemCount) ||
		// 			(missionData.redOrbs < price)
		// 		)
		// 		{
		// 			PlaySound
		// 			(
		// 				0,
		// 				19
		// 			);

		// 			return;
		// 		}

		// 		itemCount++;
		// 		buyCount++;

		// 		if (buyCount > 254)
		// 		{
		// 			buyCount = 254;
		// 		}

		// 		missionData.redOrbs -= price;

		// 		PlaySound
		// 		(
		// 			0,
		// 			18
		// 		);
		// 	};








		// 	if (GUI_Button("Buy"))
		// 	{
		// 		BuyItem();
		// 	}


		// 	static uint8 selectIndex = 0;

		// 	if (selectIndex == itemHelperIndex)
		// 	{
		// 		ImGui::SameLine();
		// 		ImGui::Text("<-");
		// 	}

		// 	auto & gamepad = GetGamepad(0);

		// 	if (gamepad.buttons[0] & GAMEPAD_UP)
		// 	{
		// 		if (selectIndex > 0)
		// 		{
		// 			selectIndex--;
		// 		}
		// 		else
		// 		{
		// 			selectIndex = static_cast<uint8>(countof(itemHelpers) - 1);
		// 		}
		// 	}

		// 	if (gamepad.buttons[0] & GAMEPAD_DOWN)
		// 	{
		// 		if (selectIndex < static_cast<uint8>(countof(itemHelpers) - 1))
		// 		{
		// 			selectIndex++;
		// 		}
		// 		else
		// 		{
		// 			selectIndex = 0;
		// 		}
		// 	}











		// }

		// ImGui::Text("");






		// GUI_Input<uint8>
		// (
		// 	"Vital Star Small",
		// 	missionData.itemCounts[ITEM_VITAL_STAR_SMALL],
		// 	0,
		// 	"%u",
		// 	ImGuiInputTextFlags_EnterReturnsTrue
		// );

		// ImGui::Text("Vital Star Small");
		// ImGui::SameLine();

		// if (GUI_Button("Buy"))
		// {
		// 	auto & count = missionData.itemCounts[ITEM_VITAL_STAR_SMALL];

		// 	count++;



		// }







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

		for_all(uint8, itemIndex, ITEM_COUNT)
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

		for_all(uint8, buyIndex, BUY_COUNT)
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
			eventData.event = EVENT_STATUS;
		}

		if (GUI_Button("Customize"))
		{
			eventData.event = EVENT_CUSTOMIZE;
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

			for_all(uint8, groupIndex, fileDataGroupCount)
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

		for_all(uint8, groupIndex, fileDataGroupCount)
		{
			auto & container = fileDataGroupItemNames[groupIndex];
			auto & itemCount = fileDataGroupItemCounts[groupIndex];

			container.Init
			(
				(itemCount * 10),
				(itemCount * sizeof(FileContainer::Metadata))
			);

			for_all(uint32, itemIndex, itemCount)
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


			for_all(uint32, itemIndex, itemCount)
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
			const uint32 itemCount = ENEMY_COUNT;

			auto & container = enemyFileDataMetadataItemNames;

			container.Init
			(
				(itemCount * 7),
				(itemCount * sizeof(FileContainer::Metadata))
			);


			for_all(uint32, itemIndex, itemCount)
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

		for_all(uint32, groupIndex, fileDataGroupCount)
		{
			auto open = ImGui::CollapsingHeader(fileDataGroupNames[groupIndex]);

			auto & itemCount = fileDataGroupItemCounts[groupIndex];

			ImGui::Indent(20);

			for_all(uint32, itemIndex, itemCount)
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

		for_all(uint32, fileDataIndex, ENEMY_FILE_DATA_COUNT)
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

		for_all(uint32, index, ENEMY_COUNT)
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




/*

export struct EventData
{
	_(24);
	uint32 room; // 0x18
	uint32 position; // 0x1C
	uint32 event; // 0x20
	uint32 subevent; // 0x24
	uint32 screen; // 0x28
	uint32 nextScreen; // 0x2C
};

*/

bool showEventDataWindow = false;




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

		for_all(uint32, index, count)
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

				for_all(uint32, itemIndex, itemCount)
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

		if (GUI_Button("File Data"))
		{
			showFileDataWindow = true;
		}
		ImGui::SameLine();
		if (GUI_Button("EventData"))
		{
			showEventDataWindow = true;
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



		if (GUI_Button("Mission Data"))
		{
			showMissionDataWindow = true;
		}



		IntroduceSessionData();

		GUI_Checkbox("One Hit Kill", sessionData.oneHitKill);








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

		auto Function = [&]
		(
			Config::CreateEnemyData & activeConfigData,
			Config::CreateEnemyData & queuedConfigData,
			uint8 index
		)
		{
			GUI_Combo2
			(
				"Enemy",
				enemyNames,
				activeConfigData.enemy,
				queuedConfigData.enemy
			);

			GUI_Input2<uint32>
			(
				"Variant",
				activeConfigData.variant,
				queuedConfigData.variant,
				1,
				"%u",
				ImGuiInputTextFlags_EnterReturnsTrue
			);

			GUI_Checkbox2
			(
				"Use Main Actor Data",
				activeConfigData.useMainActorData,
				queuedConfigData.useMainActorData
			);



			bool condition = activeConfigData.useMainActorData;

			GUI_PushDisable(condition);

			GUI_Input2<float>
			(
				"X",
				activeConfigData.position.x,
				queuedConfigData.position.x,
				10.0f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input2<float>
			(
				"Y",
				activeConfigData.position.y,
				queuedConfigData.position.y,
				10.0f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input2<float>
			(
				"Z",
				activeConfigData.position.z,
				queuedConfigData.position.z,
				10.0f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);


			GUI_Input2<uint16>
			(
				"Rotation",
				activeConfigData.rotation,
				queuedConfigData.rotation,
				1,
				"%u",
				ImGuiInputTextFlags_EnterReturnsTrue
			);

			GUI_PopDisable(condition);



			GUI_Input2<uint16>
			(
				"Spawn Method",
				activeConfigData.spawnMethod,
				queuedConfigData.spawnMethod,
				1,
				"%u",
				ImGuiInputTextFlags_EnterReturnsTrue
			);

			GUI_Checkbox2
			(
				"Auto Spawn",
				activeConfigData.autoSpawn,
				queuedConfigData.autoSpawn
			);

			if (GUI_Button("Create"))
			{
				CreateEnemy(activeConfigData, index);
			}

			ImGui::SameLine();

			if (GUI_Button("Kill"))
			{
				KillEnemy(index);
			}
		};

		if (GUI_ResetButton())
		{
			ResetConfig(createEnemyCount);
			ResetConfig(createEnemyData);
		}
		ImGui::Text("");

		ImGui::PushItemWidth(200);

		GUI_Slider2<uint8>
		(
			"Create Enemy Count",
			activeConfig.createEnemyCount,
			queuedConfig.createEnemyCount,
			1,
			static_cast<uint8>(countof(activeConfig.createEnemyData))
		);
		ImGui::Text("");

		if (GUI_Button("Create All"))
		{
			for_all(uint8, index, activeConfig.createEnemyCount)
			{
				auto & activeConfigData = activeConfig.createEnemyData[index];

				CreateEnemy(activeConfigData, index);
			}
		}
		ImGui::Text("");

		{
			auto count = activeConfig.createEnemyCount;

			for_all(uint8, index, count)
			{
				auto & activeConfigData = activeConfig.createEnemyData[index];
				auto & queuedConfigData = queuedConfig.createEnemyData[index];

				ImGui::Text("%.4u", index);

				Function
				(
					activeConfigData,
					queuedConfigData,
					index
				);

				if (index < (count - 1))
				{
					ImGui::Text("");
				}
			}
		}

		ImGui::PopItemWidth();

		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Jukebox

#define Jukebox_trackFilenames trackFilenames
#define Jukebox_trackNames trackNames

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
				Jukebox_trackFilenames[index]
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
				Jukebox_trackNames,
				index
			)
		)
		{
			snprintf
			(
				filename,
				sizeof(filename),
				"%s",
				Jukebox_trackFilenames[index]
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
		ImGui::PushFont(io.Fonts->Fonts[FONT_OVERLAY_16]);

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

		//ImGui::Text("Borderless %u", IsBorderless());


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
			if (g_scene >= MAX_SCENE)
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
				// if (!InGame())
				// {
				// 	return;
				// }

				if (g_scene != SCENE_GAME)
				{
					return;
				}

				IntroduceEventData(return);

				if (eventData.event >= MAX_EVENT)
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
				// if (!InGame())
				// {
				// 	return;
				// }

				if (g_scene != SCENE_GAME)
				{
					return;
				}

				IntroduceMainActorData(actorBaseAddr, actorData, return);

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

			for_all(uint8, index, count)
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

			for_all(uint64, index, Actor_actorBaseAddrs.count)
			{
				ImGui::Text("%.4u %.16llX", index, Actor_actorBaseAddrs[index]);
			}

			ImGui::Text("");
		}

		//ImGui::Text("g_helperIndices[CHANNEL_ENEMY]")

		for_all(uint8, index, MAX_CHANNEL)
		{
			ImGui::Text("g_helperIndices[%u] %u", index, g_helperIndices[index]);
		}
		ImGui::Text("");


		ImGui::Text("g_show %u", g_show);
		ImGui::Text("g_lastShow %u", g_lastShow);
		ImGui::Text("g_showItemWindow %u", g_showItemWindow);
		ImGui::Text("g_lastShowItemWindow %u", g_lastShowItemWindow);
		ImGui::Text("g_timeout %g", g_timeout);
		ImGui::Text("");

		if (showEnemyData)
		{
			ImGui::Text("Enemy");

			auto firstBaseAddr = *reinterpret_cast<byte8 **>(appBaseAddr + 0xCF2550);
			auto lastBaseAddr = *reinterpret_cast<byte8 **>(appBaseAddr + 0xCF2750);
			auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);

			if
			(
				!firstBaseAddr ||
				!lastBaseAddr ||
				!pool ||
				!pool[8]
			)
			{
				return;
			}

			auto & count = *reinterpret_cast<uint32 *>(pool[8] + 0x28);
			auto dataAddr = reinterpret_cast<EnemyVectorData *>(pool[8] + 0x48);



			uint32 g_index = 0;

			for_all(uint32, index, 50)
			{
				auto & data = dataAddr[index];

				if
				(
					!data.baseAddr ||
					(data.baseAddr < firstBaseAddr) ||
					(data.baseAddr > lastBaseAddr)
				)
				{
					continue;
				}

				// @Todo: Create IntroduceEnemyData.
				auto & enemyData = *reinterpret_cast<EnemyData *>(data.baseAddr);

				ImGui::Text("%.4u", index);
				ImGui::Text("baseAddr %llX", data.baseAddr);
				ImGui::Text("enemy    %u", enemyData.enemy);
				ImGui::Text("X        %g", enemyData.position.x);
				ImGui::Text("Y        %g", enemyData.position.y);
				ImGui::Text("Z        %g", enemyData.position.z);
				ImGui::Text("A        %g", enemyData.position.a);
				ImGui::Text("");

				g_index++;

				if (g_index >= count)
				{
					break;
				}
			}

			if (count == 0)
			{
				ImGui::Text("");
			}
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

		auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
		if (!pool)
		{
			return;
		}

		IntroduceActorData(actorBaseAddr, actorData, pool[3], return);

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



void Overlays()
{
	if (ImGui::CollapsingHeader("Overlays"))
	{
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			ResetConfig(mainOverlayData);
			ResetConfig(missionOverlayData);

			ImGui::SetWindowPos
			(
				mainOverlayLabel,
				*reinterpret_cast<ImVec2 *>(&activeConfig.mainOverlayData.pos)
			);
			ImGui::SetWindowPos
			(
				missionOverlayLabel,
				*reinterpret_cast<ImVec2 *>(&activeConfig.missionOverlayData.pos)
			);
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

		bool condition = (g_scene != SCENE_MISSION_SELECT);

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
					case CHAR_DANTE:
					{
						sessionData.weapons[0] = WEAPON_REBELLION;
						sessionData.weapons[1] = WEAPON_CERBERUS;
						sessionData.weapons[2] = WEAPON_EBONY_IVORY;
						sessionData.weapons[3] = WEAPON_SHOTGUN;
						sessionData.weapons[4] = WEAPON_VOID;

						break;
					}
					case CHAR_VERGIL:
					{
						sessionData.weapons[0] = WEAPON_YAMATO_VERGIL;
						sessionData.weapons[1] = WEAPON_BEOWULF_VERGIL;
						sessionData.weapons[2] = WEAPON_YAMATO_FORCE_EDGE;
						sessionData.weapons[3] = WEAPON_VOID;
						sessionData.weapons[4] = WEAPON_VOID;

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




















		// if (GUI_Button("Reset Weapons"))
		// {
		// 	[&]()
		// 	{
		// 		if (!InGame())
		// 		{
		// 			return;
		// 		}

		// 		for_all(uint32, actorIndex, Actor_actorBaseAddrs.count)
		// 		{
		// 			IntroduceActorData(actorBaseAddr, actorData, Actor_actorBaseAddrs[actorIndex], continue);

		// 			switch (actorData.character)
		// 			{
		// 				case CHAR_DANTE:
		// 				{
		// 					actorData.weapons[0] = WEAPON_REBELLION;
		// 					actorData.weapons[1] = WEAPON_CERBERUS;
		// 					actorData.weapons[2] = WEAPON_EBONY_IVORY;
		// 					actorData.weapons[3] = WEAPON_SHOTGUN;
		// 					actorData.weapons[4] = WEAPON_VOID;

		// 					break;
		// 				}
		// 				case CHAR_VERGIL:
		// 				{
		// 					actorData.weapons[0] = WEAPON_YAMATO_VERGIL;
		// 					actorData.weapons[1] = WEAPON_BEOWULF_VERGIL;
		// 					actorData.weapons[2] = WEAPON_YAMATO_FORCE_EDGE;
		// 					actorData.weapons[3] = WEAPON_VOID;
		// 					actorData.weapons[4] = WEAPON_VOID;

		// 					break;
		// 				}
		// 			}
		// 		}
		// 	}();
		// }

		// if (GUI_Button("Reset Ranged Weapon Levels"))
		// {
		// 	[&]()
		// 	{
		// 		if (!InGame())
		// 		{
		// 			return;
		// 		}

		// 		for_all(uint32, actorIndex, Actor_actorBaseAddrs.count)
		// 		{
		// 			IntroduceActorData(actorBaseAddr, actorData, Actor_actorBaseAddrs[actorIndex], continue);

		// 			SetMemory
		// 			(
		// 				actorData.weaponLevels,
		// 				0,
		// 				sizeof(actorData.weaponLevels)
		// 			);
		// 		}
		// 	}();
		// }

		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Speed

// @Todo: Move to common and create links.
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
		UpdateSpeedValues();
	}

	return update;
}

void Speed()
{
	if (ImGui::CollapsingHeader("Speed"))
	{
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			ResetConfig(Speed);

			UpdateSpeedValues();
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
			"Enemy",
			activeConfig.Speed.enemy,
			queuedConfig.Speed.enemy,
			defaultConfig.Speed.enemy,
			0.1f,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		GUI_SectionEnd();
		ImGui::Text("");

		ImGui::Text("Actor");
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
		ImGui::Text("Devil Dante");
		for_all(uint8, index, countof(activeConfig.Speed.devilDante))
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
		ImGui::Text("Devil Vergil");
		for_all(uint8, index, countof(activeConfig.Speed.devilVergil))
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
			activeConfig.Speed.quicksilverActor,
			queuedConfig.Speed.quicksilverActor,
			defaultConfig.Speed.quicksilverActor,
			0.1f,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		GUI_InputDefault2Speed
		(
			"Enemy",
			activeConfig.Speed.quicksilverEnemy,
			queuedConfig.Speed.quicksilverEnemy,
			defaultConfig.Speed.quicksilverEnemy,
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

// @Todo: Move.
const char * Graphics_vSyncNames[] =
{
	"Auto",
	"Force Off",
	"Force On",
};

const char * Sound_channelNames[MAX_CHANNEL] =
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
			ResetConfig(preferLocalFiles);
			ResetConfig(frameRate);
			ResetConfig(vSync);
			ResetConfig(hideMouseCursor);
			ResetConfig(channelVolumes);
			ResetConfig(forceWindowFocus);

			ToggleSkipIntro(activeConfig.skipIntro);
			ToggleSkipCutscenes(activeConfig.skipCutscenes);
			UpdateFrameRate();
			UpdateVolumes();
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

		for_all(uint8, channelIndex, MAX_CHANNEL)
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

		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("Window");


		// if
		// (
		// 	GUI_Checkbox2
		// 	(
		// 		"Set Size",
		// 		activeConfig.Window.setSize,
		// 		queuedConfig.Window.setSize
		// 	)
		// )
		// {
		// }




		// {
		// 	auto condition = !activeConfig.Window.setSize;

		// 	GUI_PushDisable(condition);

		// 	ImGui::PushItemWidth(200);

		// 	GUI_InputDefault2<uint32>
		// 	(
		// 		"Width",
		// 		activeConfig.Window.width,
		// 		queuedConfig.Window.width,
		// 		defaultConfig.Window.width,
		// 		1,
		// 		"%u",
		// 		ImGuiInputTextFlags_EnterReturnsTrue
		// 	);
		// 	GUI_InputDefault2<uint32>
		// 	(
		// 		"Height",
		// 		activeConfig.Window.height,
		// 		queuedConfig.Window.height,
		// 		defaultConfig.Window.height,
		// 		1,
		// 		"%u",
		// 		ImGuiInputTextFlags_EnterReturnsTrue
		// 	);

		// 	ImGui::PopItemWidth();

		// 	GUI_PopDisable(condition);
		// }
		// ImGui::Text("");




		// if
		// (
		// 	GUI_Checkbox2
		// 	(
		// 		"Set Position",
		// 		activeConfig.Window.setPosition,
		// 		queuedConfig.Window.setPosition
		// 	)
		// )
		// {
		// }


		// {
		// 	auto condition = !activeConfig.Window.setPosition;

		// 	GUI_PushDisable(condition);

		// 	ImGui::PushItemWidth(200);

		// 	GUI_InputDefault2<int32>
		// 	(
		// 		"X",
		// 		activeConfig.Window.x,
		// 		queuedConfig.Window.x,
		// 		defaultConfig.Window.x,
		// 		1,
		// 		"%d",
		// 		ImGuiInputTextFlags_EnterReturnsTrue
		// 	);
		// 	GUI_InputDefault2<int32>
		// 	(
		// 		"Y",
		// 		activeConfig.Window.y,
		// 		queuedConfig.Window.y,
		// 		defaultConfig.Window.y,
		// 		1,
		// 		"%d",
		// 		ImGuiInputTextFlags_EnterReturnsTrue
		// 	);

		// 	ImGui::PopItemWidth();

		// 	GUI_PopDisable(condition);
		// }
		// ImGui::Text("");







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
				eventData.event = EVENT_TELEPORT;
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

void Training()
{
	if (ImGui::CollapsingHeader("Training"))
	{
		ImGui::Text("");






		// auto ResetMissionOverlay = [&]()
		// {
		// 	ResetConfig(MissionOverlay);

		// 	const char * label = "MissionOverlay";
		// 	auto & pos = *reinterpret_cast<ImVec2 *>(&activeConfig.missionOverlayData.pos);

		// 	ImGui::SetWindowPos(label, pos);



		// 	// ImGui::SetWindowPos
		// 	// (
		// 	// 	"MissionOverlay",
		// 	// 	pos
		// 	// 	// ImVec2
		// 	// 	// (
		// 	// 	// 	static_cast<float>(activeConfig.missionOverlayData.x),
		// 	// 	// 	static_cast<float>(activeConfig.missionOverlayData.y)
		// 	// 	// )
		// 	// );
		// };

		if (GUI_ResetButton())
		{
			ResetConfig(infiniteHitPoints);
			ResetConfig(infiniteMagicPoints);
			ResetConfig(disableTimer);

			Training_ToggleInfiniteHitPoints  (activeConfig.infiniteHitPoints  );
			Training_ToggleInfiniteMagicPoints(activeConfig.infiniteMagicPoints);
			Training_ToggleDisableTimer       (activeConfig.disableTimer       );

			//ResetMissionOverlay();
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
			Training_ToggleInfiniteHitPoints(activeConfig.infiniteHitPoints);
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
			Training_ToggleInfiniteMagicPoints(activeConfig.infiniteMagicPoints);
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
			Training_ToggleDisableTimer(activeConfig.disableTimer);
		}

		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Vergil

void Vergil()
{
	if (ImGui::CollapsingHeader("Vergil"))
	{
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			ResetConfig(Yamato);
			ResetConfig(YamatoForceEdge);
			ResetConfig(SummonedSwords);

			ToggleYamatoForceEdgeInfiniteRoundTrip(activeConfig.YamatoForceEdge.infiniteRoundTrip);
			ToggleChronoSwords                    (activeConfig.SummonedSwords.chronoSwords      );
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

		ActionData
		(
			"Judgement Cut Count",
			activeConfig.Yamato.judgementCutCount,
			queuedConfig.Yamato.judgementCutCount,
			defaultConfig.Yamato.judgementCutCount
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

		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Main

bool Main_run = false;

void UpdateGlobalWindowSize()
{
	if (!appWindow)
	{
		return;
	}

	RECT rect = {};

	GetWindowRect
	(
		appWindow,
		&rect
	);

	g_windowSize =
	{
		static_cast<float>(rect.right - rect.left),
		static_cast<float>(rect.bottom - rect.top)
	};

	Log
	(
		"%s %g %g",
		FUNC_NAME,
		g_windowSize.x,
		g_windowSize.y
	);
}

void UpdateGlobalClientSize()
{
	if (!appWindow)
	{
		return;
	}

	RECT rect = {};

	GetClientRect
	(
		appWindow,
		&rect
	);

	g_clientSize =
	{
		static_cast<float>(rect.right),
		static_cast<float>(rect.bottom)
	};

	Log
	(
		"%s %g %g",
		FUNC_NAME,
		g_clientSize.x,
		g_clientSize.y
	);
}

void UpdateGlobalRenderSize
(
	uint32 width,
	uint32 height
)
{
	g_renderSize =
	{
		static_cast<float>(width),
		static_cast<float>(height)
	};

	Log
	(
		"%s %g %g",
		FUNC_NAME,
		g_renderSize.x,
		g_renderSize.y
	);
}



void UpdateGlobalScale()
{
	auto & io = ImGui::GetIO();

	io.FontGlobalScale = activeConfig.globalScale;
}








// @Todo: Rename to MainWindow.
void Main()
{
	if (!Main_run)
	{
		Main_run = true;
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
		//io.FontDefault = io.Fonts->Fonts[FONT_MAIN];
		//ImGui::PushFont(io.Fonts->Fonts[FONT_OVERLAY_8 + activeConfig.Tools.Overlay.fontSizeIndex]);

		//ImGui::SetCurrentFont(io.Fonts->Fonts[FONT_OVERLAY_8]);
	}

	if
	(
		ImGui::Begin
		(
			"DDMK 2.7 Mary Nightly 26 April 2021",
			&g_show
		)
	)
	{
		ImGui::Text("");

		// if (GUI_Button("Item Window"))
		// {
		// 	g_showItemWindow = true;
		// }








		// if (GUI_Button("Toggle Get Input true"))
		// {
		// 	ToggleDisableGetInput(true);
		// }

		// if (GUI_Button("Toggle Get Input false"))
		// {
		// 	ToggleDisableGetInput(false);
		// }


		// GUI_Input<uint8>
		// (
		// 	"Sound::id",
		// 	Sound::id,
		// 	1,
		// 	"%u",
		// 	ImGuiInputTextFlags_EnterReturnsTrue
		// );





		// @Todo: Move to Debug.
		// ImGui::Text("");

		// {
		// 	static int32 group = 0;
		// 	static int32 index = 0;

		// 	ImGui::PushItemWidth(150);

		// 	// GUI_Input<uint8>
		// 	// (
		// 	// 	"Helper Index",
		// 	// 	g_helperIndices[CHANNEL_COMMON],
		// 	// 	1,
		// 	// 	"%u",
		// 	// 	ImGuiInputTextFlags_EnterReturnsTrue
		// 	// );


		// 	GUI_Input<int32>
		// 	(
		// 		"Group",
		// 		group,
		// 		1,
		// 		"%d",
		// 		ImGuiInputTextFlags_EnterReturnsTrue
		// 	);
		// 	GUI_Input<int32>
		// 	(
		// 		"Index",
		// 		index,
		// 		1,
		// 		"%d",
		// 		ImGuiInputTextFlags_EnterReturnsTrue
		// 	);

		// 	ImGui::PopItemWidth();

		// 	if (GUI_Button("Play Sound"))
		// 	{
		// 		PlaySound
		// 		(
		// 			group,
		// 			index
		// 		);
		// 	}
		// }

		// ImGui::Text("");



		// {
        //     static float window_scale = 1.0f;
        //     if (ImGui::DragFloat("window scale", &window_scale, 0.005f, 0.3f, 2.0f, "%.2f"))   // scale only this window
        //         ImGui::SetWindowFontScale(window_scale);
        //     ImGui::DragFloat("global scale", &io.FontGlobalScale, 0.005f, 0.3f, 2.0f, "%.2f");      // scale everything
		// }



// 		{
// 			ImGui::Text("Window");

// 			static RECT rect = {};
// 			static DWORD style = 0;
// 			ImGui::PushItemWidth(200);

// 			GUI_Input<uint32>
// 			(
// 				"Style",
// 				style,
// 				0,
// 				"%X",
// 				ImGuiInputTextFlags_EnterReturnsTrue |
// 				ImGuiInputTextFlags_CharsHexadecimal
// 			);

// 			ImGui::PopItemWidth();

// 			ImGui::Text("left   %d", rect.left);
// 			ImGui::Text("top    %d", rect.top);
// 			ImGui::Text("right  %d", rect.right);
// 			ImGui::Text("bottom %d", rect.bottom);

// 			static LONG width = 0;
// 			static LONG height = 0;

// 			auto UpdateSize = [&]()
// 			{
// 				width = (rect.right - rect.left);
// 				height = (rect.bottom - rect.top);
// 			};

// 			ImGui::Text("width %d", width);
// 			ImGui::Text("height %d", height);

// 			if (GUI_Button("Reset"))
// 			{

// 				SetMemory
// 				(
// 					&rect,
// 					0,
// 					sizeof(rect)
// 				);




// 				UpdateSize();
// 			}


// 			if (GUI_Button("GetWindowRect"))
// 			{
// 				GetWindowRect
// 				(
// 					appWindow,
// 					&rect
// 				);

// 				UpdateSize();
// 			}

// 			if (GUI_Button("AdjustWindowRect"))
// 			{
// 				AdjustWindowRect
// 				(
// 					&rect,
// 					style,
// 					0
// 				);

// 				UpdateSize();
// 			}





// 		}


// ImGui::Text("");
// ImGui::Text("");
// ImGui::Text("");
// ImGui::Text("");






















// 		ImGui::Text
// 		(
// 			"g_windowSize %g %g",
// 			g_windowSize.x,
// 			g_windowSize.y
// 		);

// 		ImGui::Text
// 		(
// 			"g_clientSize %g %g",
// 			g_clientSize.x,
// 			g_clientSize.y
// 		);

// 		ImGui::Text
// 		(
// 			"g_renderSize %g %g",
// 			g_renderSize.x,
// 			g_renderSize.y
// 		);


// 		if (GUI_Button("Update Client"))
// 		{
// 			UpdateGlobalClientSize();
// 		}












		// {
		// 	ImGui::Text("Client");

		// 	RECT rect = {};

		// 	GetClientRect
		// 	(
		// 		appWindow,
		// 		&rect
		// 	);

		// 	ImGui::Text("left   %d", rect.left);
		// 	ImGui::Text("top    %d", rect.top);
		// 	ImGui::Text("right  %d", rect.right);
		// 	ImGui::Text("bottom %d", rect.bottom);
		// }



		// {
		// 	auto & io = ImGui::GetIO();

		// 	GUI_Input<float>
		// 	(
		// 		"Width",
		// 		io.DisplaySize.x,
		// 		0,
		// 		"%g",
		// 		ImGuiInputTextFlags_EnterReturnsTrue
		// 	);
		// 	GUI_Input<float>
		// 	(
		// 		"Height",
		// 		io.DisplaySize.y,
		// 		0,
		// 		"%g",
		// 		ImGuiInputTextFlags_EnterReturnsTrue
		// 	);
		// }

		// if constexpr (debug)
		// {

			
			



		// 	// GUI_Input<uint8>
		// 	// (
		// 	// 	"g_action",
		// 	// 	g_action
		// 	// );

		// 	// if (GUI_Button("// Log run"))
		// 	// {
		// 	// 	// Log("MissionOverlay.run %u", activeConfig.missionOverlayData.run);
		// 	// }






		// if constexpr (debug)
		// {
		// 	static uint16 cacheFileIndex = em035;
		// 	static byte8 * file = 0;
		// 	static uint32 fileSize = 0;
		// 	static uint16 fileDataIndex = 233;

		// 	ImGui::PushItemWidth(200);
		// 	GUI_Input<uint16>
		// 	(
		// 		"Cache File Index",
		// 		cacheFileIndex
		// 	);
		// 	GUI_Input<uint64>
		// 	(
		// 		"File",
		// 		*reinterpret_cast<uint64 *>(&file),
		// 		0,
		// 		"%llX",
		// 		ImGuiInputTextFlags_EnterReturnsTrue |
		// 		ImGuiInputTextFlags_CharsHexadecimal
		// 	);
		// 	GUI_Input<uint32>
		// 	(
		// 		"File Size",
		// 		fileSize
		// 	);
		// 	GUI_Input<uint16>
		// 	(
		// 		"File Data Index",
		// 		fileDataIndex
		// 	);
		// 	ImGui::PopItemWidth();

		// 	if (GUI_Button("Load Pride"))
		// 	{
		// 		File_UpdateFileData(fileDataIndex, cacheFileIndex);
		// 	}
		// }

		// if constexpr (debug)
		// {
		// 	static char buffer[8];
		// 	static byte8 * file = 0;
		// 	static uint32 fileIndex = 0;
			
		// 	static char subbuffer[8];
		// 	static byte8 * subfile = 0;
		// 	static uint32 subfileIndex = 0;

		// 	ImGui::PushItemWidth(50);
		// 	ImGui::InputText
		// 	(
		// 		"",
		// 		buffer,
		// 		sizeof(buffer)
		// 	);
		// 	ImGui::PopItemWidth();
		// 	ImGui::SameLine();
		// 	ImGui::PushItemWidth(150);
		// 	GUI_Input<uint64>
		// 	(
		// 		"",
		// 		*reinterpret_cast<uint64 *>(&file),
		// 		0,
		// 		"%llX",
		// 		ImGuiInputTextFlags_CharsHexadecimal |
		// 		ImGuiInputTextFlags_EnterReturnsTrue
		// 	);
		// 	ImGui::SameLine();
		// 	GUI_Input<uint32>
		// 	(
		// 		"",
		// 		fileIndex
		// 	);
		// 	ImGui::PopItemWidth();
		// 	ImGui::SameLine();
		// 	if (GUI_Button("Set File"))
		// 	{
		// 		file = File_staticFiles[em034][fileIndex];

		// 		SetMemory
		// 		(
		// 			buffer,
		// 			0,
		// 			sizeof(buffer)
		// 		);

		// 		[&]()
		// 		{
		// 			if (!file)
		// 			{
		// 				return;
		// 			}

		// 			CopyMemory
		// 			(
		// 				buffer,
		// 				file,
		// 				4
		// 			);
		// 		}();
		// 	}








		// 	ImGui::PushItemWidth(50);
		// 	ImGui::InputText
		// 	(
		// 		"",
		// 		subbuffer,
		// 		sizeof(subbuffer)
		// 	);
		// 	ImGui::PopItemWidth();
		// 	ImGui::SameLine();
		// 	ImGui::PushItemWidth(150);
		// 	GUI_Input<uint64>
		// 	(
		// 		"",
		// 		*reinterpret_cast<uint64 *>(&subfile),
		// 		0,
		// 		"%llX",
		// 		ImGuiInputTextFlags_CharsHexadecimal |
		// 		ImGuiInputTextFlags_EnterReturnsTrue
		// 	);
		// 	ImGui::SameLine();
		// 	GUI_Input<uint32>
		// 	(
		// 		"",
		// 		subfileIndex
		// 	);
		// 	ImGui::PopItemWidth();
		// 	ImGui::SameLine();
		// 	if (GUI_Button("Set Subfile"))
		// 	{
		// 		[&]()
		// 		{
		// 			auto subarchive = file;
		// 			if (!subarchive)
		// 			{
		// 				return;
		// 			}

		// 			auto & subarchiveMetadata = *reinterpret_cast<ArchiveMetadata *>(subarchive);

		// 			if
		// 			(
		// 				(subarchiveMetadata.signature[0] != 'P') ||
		// 				(subarchiveMetadata.signature[1] != 'A') ||
		// 				(subarchiveMetadata.signature[2] != 'C')
		// 			)
		// 			{
		// 				MessageBoxA
		// 				(
		// 					0,
		// 					"Wrong Signature",
		// 					0,
		// 					0
		// 				);

		// 				return;
		// 			}

		// 			if (subfileIndex >= subarchiveMetadata.fileCount)
		// 			{
		// 				MessageBoxA
		// 				(
		// 					0,
		// 					"Out of range.",
		// 					0,
		// 					0
		// 				);

		// 				return;
		// 			}

		// 			auto subfileOff = subarchiveMetadata.fileOffs[subfileIndex];
		// 			if (!subfileOff)
		// 			{
		// 				return;
		// 			}

		// 			subfile = (file + subfileOff);

		// 			SetMemory
		// 			(
		// 				subbuffer,
		// 				0,
		// 				sizeof(subbuffer)
		// 			);

		// 			if (!subfile)
		// 			{
		// 				return;
		// 			}

		// 			CopyMemory
		// 			(
		// 				subbuffer,
		// 				(subfile + 4),
		// 				3
		// 			);
		// 		}();
		// 	}

		// 	if (GUI_Button("Play File Motion"))
		// 	{
		// 		[&]()
		// 		{
		// 			IntroduceMainActorData(actorBaseAddr, actorData, return);

		// 			func_8AC80
		// 			(
		// 				actorData.newModelData[0],
		// 				UPPER_BODY,
		// 				file,
		// 				0,
		// 				false
		// 			);
		// 			func_8AC80
		// 			(
		// 				actorData.newModelData[0],
		// 				LOWER_BODY,
		// 				file,
		// 				0,
		// 				false
		// 			);
		// 		}();
		// 	}

		// 	if (GUI_Button("Play Subfile Motion"))
		// 	{
		// 		[&]()
		// 		{
		// 			IntroduceMainActorData(actorBaseAddr, actorData, return);

		// 			func_8AC80
		// 			(
		// 				actorData.newModelData[0],
		// 				UPPER_BODY,
		// 				subfile,
		// 				0,
		// 				false
		// 			);
		// 			func_8AC80
		// 			(
		// 				actorData.newModelData[0],
		// 				LOWER_BODY,
		// 				subfile,
		// 				0,
		// 				false
		// 			);
		// 		}();
		// 	}

		// 	ImGui::Text("");
		// }





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

		Actor();
		Arcade();
		BossRush();
		Camera();
		Cosmetics();
		Damage();
		Dante();

		if constexpr (debug)
		{
			Debug();
		}

		Enemy();

		//GUI();
		Jukebox();
		Mobility();
		Other();
		Overlays();
		Repair();
		Speed();
		System();
		Teleporter();
		Textures();
		Training();
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

	WeaponSwitchController();

	ItemWindow();




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
