// @Todo: Add description for arbitrary weapon switcher.

module;
#include "../Core/Core.h"

// @Todo: Define as extern.
#include <shellapi.h>

#include "../ImGui/imgui.h"

#include "Locale.h"
#include "Vars.h"

#include <d3d11.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"
export module GUI;

import Core_GUI;

import Actor;
import Arcade;
import Camera;
import Config;
import Event;
import File;
import FMOD;
import Global;
import Graphics;
import Internal;
import Input;
import Model;
import Other;
import Scene;
import Sound;
import Speed;
import Training;
import Window;

#define debug false

//float textWidth = 500.0f;

// @Todo: Create region.

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

// @Todo: Add event names.

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
	Log("%s %s", FUNC_NAME, filename);

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
		Log("stbi_load failed. %s", filename);

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

	D3D11_device->CreateTexture2D
	(
		&textureDesc,
		&subresourceData,
		&texture
	);

	shaderResourceViewDesc.Format              = DXGI_FORMAT_R8G8B8A8_UNORM;
	shaderResourceViewDesc.ViewDimension       = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MipLevels = textureDesc.MipLevels;

	D3D11_device->CreateShaderResourceView
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
	bool run;
	const char * label;
	bool enable;
	ID3D11ShaderResourceView * textureAddr;
	ImVec2 size;
	ImVec2 pos;

	void Render(ImGuiWindowFlags windowFlags = 0);
	void Render
	(
		void * sizeAddr,
		void * posAddr
	);
	void UpdatePosition(void * posAddr);
	void Settings();
	void Settings
	(
		void * sizeAddr,
		void * posAddr
	);
};

void TextureData::Render(ImGuiWindowFlags windowFlags)
{
	if
	(
		!enable ||
		!textureAddr
	)
	{
		return;
	}

	if (!run)
	{
		run = true;

		ImGui::SetNextWindowPos(pos);
	}

	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));

	if
	(
		ImGui::Begin
		(
			label,
			&enable,
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | windowFlags
		)
	)
	{
		pos = ImGui::GetWindowPos();

		ImGui::Image
		(
			textureAddr,
			size
		);
	}

	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(2);
}

void TextureData::Render
(
	void * sizeAddr,
	void * posAddr
)
{
	if
	(
		!enable      ||
		!textureAddr ||
		!sizeAddr    ||
		!posAddr
	)
	{
		return;
	}

	auto & size2 = *reinterpret_cast<ImVec2 *>(sizeAddr);
	auto & pos2 = *reinterpret_cast<ImVec2 *>(posAddr);

	if (!run)
	{
		run = true;

		ImGui::SetNextWindowPos(pos2);
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
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_AlwaysAutoResize
		)
	)
	{
		pos2 = ImGui::GetWindowPos();

		ImGui::Image
		(
			textureAddr,
			size2
		);
	}

	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(4);
}

void TextureData::UpdatePosition(void * posAddr)
{
	if (!posAddr)
	{
		return;
	}

	auto & pos2 = *reinterpret_cast<ImVec2 *>(posAddr);

	ImGui::SetWindowPos(label, pos2);
}

void TextureData::Settings()
{
	ImGui::Text(label);

	GUI_Checkbox
	(
		"Enable",
		enable
	);

	ImGui::PushItemWidth(200);

	GUI_Input<float>
	(
		"Width",
		size.x,
		1,
		"%g",
		ImGuiInputTextFlags_EnterReturnsTrue
	);
	GUI_Input<float>
	(
		"Height",
		size.y,
		1,
		"%g",
		ImGuiInputTextFlags_EnterReturnsTrue
	);

	if
	(
		GUI_Input<float>
		(
			"X",
			pos.x,
			1,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		)
	)
	{
		ImGui::SetWindowPos(label, pos);
	}
	if
	(
		GUI_Input<float>
		(
			"Y",
			pos.y,
			1,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		)
	)
	{
		ImGui::SetWindowPos(label, pos);
	}

	ImGui::PopItemWidth();
}

void TextureData::Settings
(
	void * sizeAddr,
	void * posAddr
)
{
	if
	(
		!sizeAddr ||
		!posAddr
	)
	{
		return;
	}

	auto & size2 = *reinterpret_cast<ImVec2 *>(sizeAddr);
	auto & pos2 = *reinterpret_cast<ImVec2 *>(posAddr);

	ImGui::Text(label);

	if constexpr (debug)
	{
		GUI_Checkbox
		(
			"Enable",
			enable
		);
	}

	ImGui::PushItemWidth(200);

	GUI_Input<float>
	(
		"Width",
		size2.x,
		1,
		"%g",
		ImGuiInputTextFlags_EnterReturnsTrue
	);
	GUI_Input<float>
	(
		"Height",
		size2.y,
		1,
		"%g",
		ImGuiInputTextFlags_EnterReturnsTrue
	);

	if
	(
		GUI_Input<float>
		(
			"X",
			pos2.x,
			1,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		)
	)
	{
		ImGui::SetWindowPos(label, pos2);
	}
	if
	(
		GUI_Input<float>
		(
			"Y",
			pos2.y,
			1,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		)
	)
	{
		ImGui::SetWindowPos(label, pos2);
	}

	ImGui::PopItemWidth();
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



void MeleeWeaponSwitchController()
{
	auto & textureData = meleeWeaponSwitchControllerTextureData;
	auto & textureData2 = activeConfig.meleeWeaponSwitchControllerTextureData2;

	if (g_showTextures)
	{
		for_all(uint8, index, 5)
		{
			textureData.backgrounds[index].Render
			(
				&textureData2.backgrounds[index].size,
				&textureData2.backgrounds[index].pos
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
					&textureData2.icons[index].size,
					&textureData2.icons[index].pos
				);
			}
		}

		textureData.highlights[0].Render
		(
			&textureData2.highlights[0].size,
			&textureData2.highlights[0].pos
		);

		{
			textureData.arrow.textureAddr = textureAddrs[TEXTURE_ARROW_0];

			textureData.arrow.Render
			(
				&textureData2.arrow.size,
				&textureData2.arrow.pos
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
			&textureData2.backgrounds[index].size,
			&textureData2.backgrounds[index].pos
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
				&textureData2.icons[index].size,
				&textureData2.icons[index].pos
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
		&textureData2.highlights[meleeWeaponIndex].size,
		&textureData2.highlights[meleeWeaponIndex].pos
	);

	{
		auto textureId = textureArrowMap[meleeWeaponIndex];

		textureData.arrow.textureAddr = textureAddrs[textureId];

		textureData.arrow.Render
		(
			&textureData2.arrow.size,
			&textureData2.arrow.pos
		);
	}
}

void RangedWeaponSwitchController()
{
	auto & textureData = rangedWeaponSwitchControllerTextureData;
	auto & textureData2 = activeConfig.rangedWeaponSwitchControllerTextureData2;

	if (g_showTextures)
	{
		for_all(uint8, index, 5)
		{
			textureData.backgrounds[index].Render
			(
				&textureData2.backgrounds[index].size,
				&textureData2.backgrounds[index].pos
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
					&textureData2.icons[index].size,
					&textureData2.icons[index].pos
				);
			}
		}

		textureData.highlights[0].Render
		(
			&textureData2.highlights[0].size,
			&textureData2.highlights[0].pos
		);

		{
			textureData.arrow.textureAddr = textureAddrs[TEXTURE_ARROW_0];

			textureData.arrow.Render
			(
				&textureData2.arrow.size,
				&textureData2.arrow.pos
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
			&textureData2.backgrounds[index].size,
			&textureData2.backgrounds[index].pos
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
				&textureData2.icons[index].size,
				&textureData2.icons[index].pos
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
		&textureData2.highlights[rangedWeaponIndex].size,
		&textureData2.highlights[rangedWeaponIndex].pos
	);

	{
		auto textureId = textureArrowMap[rangedWeaponIndex];

		textureData.arrow.textureAddr = textureAddrs[textureId];

		textureData.arrow.Render
		(
			&textureData2.arrow.size,
			&textureData2.arrow.pos
		);
	}
}

void WeaponSwitchController()
{
	static bool run = false;

	if (!run)
	{
		run = true;




		// stencil =
		// {
		// 	false,
		// 	"Stencil",
		// 	false,
		// 	textureAddrs[TEXTURE_STENCIL],
		// 	ImVec2
		// 	(
		// 		700,
		// 		700
		// 	),
		// 	ImVec2
		// 	(
		// 		1220,
		// 		380
		// 	)
		// };



		for_all(uint8, index, 5)
		{
			meleeWeaponSwitchControllerTextureData.backgrounds[index] =
			{
				false,
				meleeWeaponSwitchControllerBackgroundNames[index],
				true,
				textureAddrs[TEXTURE_BACKGROUND]
			};
		}

		for_all(uint8, index, 5)
		{
			meleeWeaponSwitchControllerTextureData.icons[index] =
			{
				false,
				meleeWeaponSwitchControllerIconNames[index],
				true
			};
		}

		for_all(uint8, index, 5)
		{
			meleeWeaponSwitchControllerTextureData.highlights[index] =
			{
				false,
				meleeWeaponSwitchControllerHighlightNames[index],
				true,
				textureAddrs[TEXTURE_HIGHLIGHT]
			};
		}

		meleeWeaponSwitchControllerTextureData.arrow =
		{
			false,
			meleeWeaponSwitchControllerArrowName,
			true
		};



		for_all(uint8, index, 5)
		{
			rangedWeaponSwitchControllerTextureData.backgrounds[index] =
			{
				false,
				rangedWeaponSwitchControllerBackgroundNames[index],
				true,
				textureAddrs[TEXTURE_BACKGROUND]
			};
		}

		for_all(uint8, index, 5)
		{
			rangedWeaponSwitchControllerTextureData.icons[index] =
			{
				false,
				rangedWeaponSwitchControllerIconNames[index],
				true
			};
		}

		for_all(uint8, index, 5)
		{
			rangedWeaponSwitchControllerTextureData.highlights[index] =
			{
				false,
				rangedWeaponSwitchControllerHighlightNames[index],
				true,
				textureAddrs[TEXTURE_HIGHLIGHT]
			};
		}

		rangedWeaponSwitchControllerTextureData.arrow =
		{
			false,
			rangedWeaponSwitchControllerArrowName,
			true
		};
	}

	//stencil.Render();

	MeleeWeaponSwitchController();
	RangedWeaponSwitchController();
}

void UpdateWeaponSwitchControllerTexturePositions()
{
	// Melee
	{
		auto & textureData = meleeWeaponSwitchControllerTextureData;
		auto & textureData2 = activeConfig.meleeWeaponSwitchControllerTextureData2;

		for_all(uint8, index, 5)
		{
			textureData.backgrounds[index].UpdatePosition(&textureData2.backgrounds[index].pos);
		}

		for_all(uint8, index, 5)
		{
			textureData.icons[index].UpdatePosition(&textureData2.icons[index].pos);
		}

		for_all(uint8, index, 5)
		{
			textureData.highlights[index].UpdatePosition(&textureData2.highlights[index].pos);
		}

		textureData.arrow.UpdatePosition(&textureData2.arrow.pos);
	}

	// Ranged
	{
		auto & textureData = rangedWeaponSwitchControllerTextureData;
		auto & textureData2 = activeConfig.rangedWeaponSwitchControllerTextureData2;

		for_all(uint8, index, 5)
		{
			textureData.backgrounds[index].UpdatePosition(&textureData2.backgrounds[index].pos);
		}

		for_all(uint8, index, 5)
		{
			textureData.icons[index].UpdatePosition(&textureData2.icons[index].pos);
		}

		for_all(uint8, index, 5)
		{
			textureData.highlights[index].UpdatePosition(&textureData2.highlights[index].pos);
		}

		textureData.arrow.UpdatePosition(&textureData2.arrow.pos);
	}
}

void WeaponSwitchControllerSettings()
{
	if (GUI_ResetButton())
	{
		ResetConfigGroup(meleeWeaponSwitchControllerTextureData2);
		ResetConfigGroup(rangedWeaponSwitchControllerTextureData2);

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
				&queuedConfig.meleeWeaponSwitchControllerTextureData2,
				&defaultConfig.meleeWeaponSwitchControllerTextureData2,
				sizeof(queuedConfig.meleeWeaponSwitchControllerTextureData2)
			);

			auto & textureData2 = queuedConfig.meleeWeaponSwitchControllerTextureData2;

			auto values = reinterpret_cast<float *>(&textureData2);
			uint32 count = (sizeof(textureData2) / 4);

			for_all(uint32, index, count)
			{
				auto & value = values[index];

				value *= multiplier;
			}

			CopyMemory
			(
				&activeConfig.meleeWeaponSwitchControllerTextureData2,
				&queuedConfig.meleeWeaponSwitchControllerTextureData2,
				sizeof(activeConfig.meleeWeaponSwitchControllerTextureData2)
			);
		}

		// Ranged
		{
			const float multiplier = (targetWidth / defaultWidth);

			CopyMemory
			(
				&queuedConfig.rangedWeaponSwitchControllerTextureData2,
				&defaultConfig.rangedWeaponSwitchControllerTextureData2,
				sizeof(queuedConfig.rangedWeaponSwitchControllerTextureData2)
			);

			auto & textureData2 = queuedConfig.rangedWeaponSwitchControllerTextureData2;

			auto values = reinterpret_cast<float *>(&textureData2);
			uint32 count = (sizeof(textureData2) / 4);

			for_all(uint32, index, count)
			{
				auto & value = values[index];

				value *= multiplier;
			}

			CopyMemory
			(
				&activeConfig.rangedWeaponSwitchControllerTextureData2,
				&queuedConfig.rangedWeaponSwitchControllerTextureData2,
				sizeof(activeConfig.rangedWeaponSwitchControllerTextureData2)
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
		auto & textureData2 = activeConfig.meleeWeaponSwitchControllerTextureData2;

		for_all(uint8, index, 5)
		{
			textureData.backgrounds[index].Settings
			(
				&textureData2.backgrounds[index].size,
				&textureData2.backgrounds[index].pos
			);
			ImGui::Text("");
		}

		for_all(uint8, index, 5)
		{
			textureData.icons[index].Settings
			(
				&textureData2.icons[index].size,
				&textureData2.icons[index].pos
			);
			ImGui::Text("");
		}

		for_all(uint8, index, 5)
		{
			textureData.highlights[index].Settings
			(
				&textureData2.highlights[index].size,
				&textureData2.highlights[index].pos
			);
			ImGui::Text("");
		}

		textureData.arrow.Settings
		(
			&textureData2.arrow.size,
			&textureData2.arrow.pos
		);
		ImGui::Text("");
	}

	// Ranged
	{
		auto & textureData = rangedWeaponSwitchControllerTextureData;
		auto & textureData2 = activeConfig.rangedWeaponSwitchControllerTextureData2;

		for_all(uint8, index, 5)
		{
			textureData.backgrounds[index].Settings
			(
				&textureData2.backgrounds[index].size,
				&textureData2.backgrounds[index].pos
			);
			ImGui::Text("");
		}

		for_all(uint8, index, 5)
		{
			textureData.icons[index].Settings
			(
				&textureData2.icons[index].size,
				&textureData2.icons[index].pos
			);
			ImGui::Text("");
		}

		for_all(uint8, index, 5)
		{
			textureData.highlights[index].Settings
			(
				&textureData2.highlights[index].size,
				&textureData2.highlights[index].pos
			);
			ImGui::Text("");
		}

		textureData.arrow.Settings
		(
			&textureData2.arrow.size,
			&textureData2.arrow.pos
		);
	}
}

#pragma endregion

#pragma region Overlay

// @Todo: Update.
bool Overlay_enable = true;
bool Overlay_run = false;
ImVec2 Overlay_size = ImVec2(300, 300);














void Overlay()
{
	if (!Overlay_run)
	{
		Overlay_run = true;
		ImGui::SetNextWindowSize(ImVec2(Overlay_size.x + 16, Overlay_size.y + 16));
		ImGui::SetNextWindowPos(ImVec2(0, 0));
	}
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1, 1));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));
	if (ImGui::Begin("GUI_Overlay", &Overlay_enable, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize))
	{
		auto & io = ImGui::GetIO();
		ImGui::PushFont(io.Fonts->Fonts[FONT_OVERLAY_16]);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 0, 0, 1));

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

		ImGui::Text("%.2f FPS", (ImGui::GetIO().Framerate));

		//ImGui::Text("g_scene %u", g_scene);

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





		[&]()
		{
			if (!InGame())
			{
				return;
			}

			IntroduceEventData(return);

			ImGui::Text("%u", eventData.room);
			ImGui::Text("%u", eventData.position);
		}();

		constexpr uint32 off[] =
		{
			0xCA8910,
			0xCA8938,
			0xCA8960,
		};
		for_all(uint8, index, countof(off))
		{
			auto & memoryObject = *reinterpret_cast<MEMORY_OBJECT *>(appBaseAddr + off[index]);
			ImGui::Text("__%.4u__", index);
			ImGui::Text("addr     %llX", memoryObject.addr    );
			ImGui::Text("end      %llX", memoryObject.end     );
			ImGui::Text("last     %X"  , memoryObject.last    );
			ImGui::Text("boundary %X"  , memoryObject.boundary);
			ImGui::Text("size     %X"  , memoryObject.size    );
			ImGui::Text("pipe     %u"  , memoryObject.pipe    );
			ImGui::Text("count    %u"  , memoryObject.count   );
		}

		ImGui::PopStyleColor();
		ImGui::PopFont();
	}
	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(3);
}



// @Todo: Update.
// bool Overlay_enable = true;
// bool Overlay_run = false;
// ImVec2 Overlay_size = ImVec2(300, 300);

void Overlay2()
{
	static bool run = false;
	if (!run)
	{
		run = true;
		ImGui::SetNextWindowSize(ImVec2((300 + 16), (300 + 16)));
		ImGui::SetNextWindowPos(ImVec2(200, 0));
	}
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1, 1));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));
	if (ImGui::Begin("GUI_Overlay2", &Overlay_enable, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize))
	{
		auto & io = ImGui::GetIO();
		ImGui::PushFont(io.Fonts->Fonts[FONT_OVERLAY_16]);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 0, 0, 1));


		ImGui::Text("Memory Data");
		ImGui::Text("pos   %u", memoryData.pos);
		ImGui::Text("end   %u", memoryData.end);
		ImGui::Text("count %u", memoryData.count);
		ImGui::Text("");

		ImGui::Text("Backup Helper");
		ImGui::Text("pos   %u", backupHelper.pos);
		ImGui::Text("end   %u", backupHelper.end);
		ImGui::Text("count %u", backupHelper.count);
		ImGui::Text("");








		ImGui::Text("Actor");

		for_all(uint32, index, Actor_actorBaseAddr.count)
		{
			ImGui::Text("%.4u %.16llX", index, Actor_actorBaseAddr[index]);
		}

		for_all(uint32, actorIndex, Actor_actorBaseAddr.count)
		{
			IntroduceActorData(actorBaseAddr, actorData, Actor_actorBaseAddr[actorIndex], continue);

			ImGui::Text("%.4u %u", actorIndex, IsActive(actorData));
		}




		if (Actor_actorBaseAddr.count > 0)
		{
			ImGui::Text("");
		}

		// //for_all(uint8, player, MAX_PLAYER)
		// {
		// 	constexpr uint8 player = 0;

		// 	for_all(uint8, direction, MAX_DIRECTION)
		// 	{
		// 		ImGui::Text("%.4u %.16llX", direction, g_actorBaseAddr[player][direction]);
		// 	}

		// 	auto & character       = g_character      [player];
		// 	auto & lastCharacter   = g_lastCharacter  [player];
		// 	auto & activeCharacter = g_activeCharacter[player];
		// 	auto & executeFunction = g_executeFunction[player];

		// 	ImGui::Text("character        %u", character      );
		// 	ImGui::Text("lastCharacter    %u", lastCharacter  );
		// 	ImGui::Text("activeCharacter  %u", activeCharacter);

		// 	for_all(uint8, direction, MAX_DIRECTION)
		// 	{
		// 		auto & executeButton = g_executeButton[player][direction];

		// 		ImGui::Text("executeButton[%u] %u", direction, executeButton );
		// 	}

		// 	ImGui::Text("executeFunction  %u", executeFunction);
		// }




		ImGui::PopStyleColor();
		ImGui::PopFont();
	}
	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(3);
}




void MissionOverlay()
{
	if (!activeConfig.MissionOverlay.enable)
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
				(300.0f + 16.0f),
				(300.0f + 16.0f)
			)
		);
		ImGui::SetNextWindowPos
		(
			ImVec2
			(
				static_cast<float>(activeConfig.MissionOverlay.x),
				static_cast<float>(activeConfig.MissionOverlay.y)
			)
		);
	}
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1, 1));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));
	if
	(
		ImGui::Begin
		(
			"GUI_MissionOverlay",
			&activeConfig.MissionOverlay.enable,
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize
		)
	)
	{
		{
			auto pos = ImGui::GetWindowPos();

			auto x = static_cast<uint32>(pos.x);
			auto y = static_cast<uint32>(pos.y);

			if
			(
				(activeConfig.MissionOverlay.x != x) ||
				(activeConfig.MissionOverlay.y != y)
			)
			{
				activeConfig.MissionOverlay.x = queuedConfig.MissionOverlay.x = x;
				activeConfig.MissionOverlay.y = queuedConfig.MissionOverlay.y = y;

				GUI_save = true;
			}
		}

		auto & io = ImGui::GetIO();

		ImGui::PushFont(io.Fonts->Fonts[FONT_OVERLAY_16]);

		ImGui::PushStyleColor
		(
			ImGuiCol_Text,
			*reinterpret_cast<ImVec4 *>(&activeConfig.MissionOverlay.color)
		);

		ImGui::Text("Mission");

		[&]()
		{
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
		}();

		ImGui::PopStyleColor();
		ImGui::PopFont();
	}
	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(3);
}

































#pragma endregion

#pragma region Actor

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
	LogFunction();

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
	GUI_Input2
	(
		"Costume",
		activeCharacterData.costume,
		queuedCharacterData.costume
	);
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

		if (queuedCharacterData.meleeWeaponSwitchType == WEAPON_SWITCH_TYPE_LINEAR)
		{
			ImGui::SameLine();
			TooltipHelper
			(
				"(?)",
				"Hold the taunt button during the switch to go back."
			);
		}

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

	if (queuedCharacterData.rangedWeaponSwitchType == WEAPON_SWITCH_TYPE_LINEAR)
	{
		ImGui::SameLine();
		TooltipHelper
		(
			"(?)",
			"Hold the taunt button during the switch to go back."
		);
	}

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
				(g_scene == SCENE_MAIN          ) ||
				(g_scene == SCENE_MISSION_SELECT)
			)
			{
				activeConfig.Actor.enable = queuedConfig.Actor.enable;

				Actor_Toggle(activeConfig.Actor.enable);
			}
		}
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			auto enable = activeConfig.Actor.enable;

			ResetConfigGroup(Actor);
			ResetConfigEntry(removeBusyFlag);
			ResetConfigEntry(resetPermissions);

			Actor_UpdateIndices();

			if
			(
				(g_scene == SCENE_MAIN          ) ||
				(g_scene == SCENE_MISSION_SELECT)
			)
			{
				Actor_Toggle(activeConfig.Actor.enable);
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
	LogFunction();

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
			ResetConfigGroup(Arcade);

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
			ResetConfigGroup(BossRush);
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
			ResetConfigGroup(Camera);
			ResetConfigEntry(disableCenterCamera);

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
	LogFunction();

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
			ResetConfigGroup(Color);

			ResetConfigEntry(hideBeowulfDante);
			ResetConfigEntry(hideBeowulfVergil);
			ResetConfigEntry(noDevilForm);

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
			ResetConfigGroup(Color);

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
			ResetConfigEntry(damageActorMultiplier);
			ResetConfigEntry(damageEnemyMultiplier);
			ResetConfigEntry(damageStyleRank);
		}
		ImGui::Text("");

		TooltipHelper
		(
			"(?)",
			"Multiplier values are for RECEIVED damage."
		);
		ImGui::Text("");

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
			ResetConfigEntry(airHikeCoreAbility);
			ResetConfigGroup(Rebellion);
			ResetConfigGroup(EbonyIvory);
			ResetConfigGroup(Artemis);

			ToggleAirHikeCoreAbility               (activeConfig.airHikeCoreAbility                );
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

void Debug()
{
	if (ImGui::CollapsingHeader("Debug"))
	{
		ImGui::Text("");

		IntroduceSessionData();

		GUI_Checkbox("One Hit Kill", sessionData.oneHitKill);

		ImGui::Text("");
	}
}

#pragma endregion

#pragma region GUI

void GUI()
{
	if (ImGui::CollapsingHeader("GUI"))
	{
		ImGui::Text("");

		WeaponSwitchControllerSettings();

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
			ResetConfigArray(airHikeCount);
			ResetConfigArray(kickJumpCount);
			ResetConfigArray(wallHikeCount);
			ResetConfigArray(dashCount);
			ResetConfigArray(skyStarCount);
			ResetConfigArray(airTrickCountDante);
			ResetConfigArray(airTrickCountVergil);
			ResetConfigArray(trickUpCount);
			ResetConfigArray(trickDownCount);
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

// @Todo: Move.
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
			ResetConfigEntry(dotShadow);
			ResetConfigEntry(depleteQuicksilver);
			ResetConfigEntry(depleteDoppelganger);
			ResetConfigEntry(depleteDevil);
			ResetConfigEntry(crazyComboLevelMultiplier);
			ResetConfigEntry(weaponSwitchTimeout);
			ResetConfigEntry(orbReach);

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
			"Weapon Switch Timeout",
			activeConfig.weaponSwitchTimeout,
			queuedConfig.weaponSwitchTimeout,
			defaultConfig.weaponSwitchTimeout,
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

#pragma region Repair

// @Todo: Add main actor.

void Repair()
{
	if (ImGui::CollapsingHeader("Repair"))
	{
		ImGui::Text("");

		if (GUI_Button("Reset Weapons"))
		{
			[&]()
			{
				if (!InGame())
				{
					return;
				}

				for_all(uint32, actorIndex, Actor_actorBaseAddr.count)
				{
					IntroduceActorData(actorBaseAddr, actorData, Actor_actorBaseAddr[actorIndex], continue);

					switch (actorData.character)
					{
						case CHAR_DANTE:
						{
							actorData.weapons[0] = WEAPON_REBELLION;
							actorData.weapons[1] = WEAPON_CERBERUS;
							actorData.weapons[2] = WEAPON_EBONY_IVORY;
							actorData.weapons[3] = WEAPON_SHOTGUN;
							actorData.weapons[4] = WEAPON_VOID;

							break;
						}
						case CHAR_VERGIL:
						{
							actorData.weapons[0] = WEAPON_YAMATO_VERGIL;
							actorData.weapons[1] = WEAPON_BEOWULF_VERGIL;
							actorData.weapons[2] = WEAPON_YAMATO_FORCE_EDGE;
							actorData.weapons[3] = WEAPON_VOID;
							actorData.weapons[4] = WEAPON_VOID;

							break;
						}
					}
				}
			}();
		}

		if (GUI_Button("Reset Ranged Weapon Levels"))
		{
			[&]()
			{
				if (!InGame())
				{
					return;
				}

				for_all(uint32, actorIndex, Actor_actorBaseAddr.count)
				{
					IntroduceActorData(actorBaseAddr, actorData, Actor_actorBaseAddr[actorIndex], continue);

					SetMemory
					(
						actorData.weaponLevels,
						0,
						sizeof(actorData.weaponLevels)
					);
				}
			}();
		}

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
			ResetConfigGroup(Speed);

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
			ResetConfigEntry(skipIntro);
			ResetConfigEntry(skipCutscenes);
			ResetConfigEntry(preferLocalFiles);
			ResetConfigEntry(frameRate);
			ResetConfigEntry(vSync);
			ResetConfigEntry(hideMouseCursor);
			ResetConfigArray(channelVolumes);
			ResetConfigEntry(forceWindowFocus);

			Event_ToggleSkipIntro(activeConfig.skipIntro);
			Event_ToggleSkipCutscenes(activeConfig.skipCutscenes);
			UpdateFrameRate();
			UpdateVolumes();
			Window_ToggleForceFocus(activeConfig.forceWindowFocus);
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
			Event_ToggleSkipIntro(activeConfig.skipIntro);
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
			Event_ToggleSkipCutscenes(activeConfig.skipCutscenes);
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
			ResetConfigEntry(frameRate);
			ResetConfigEntry(vSync);

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
			ResetConfigArray(channelVolumes);

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
			Window_ToggleForceFocus(activeConfig.forceWindowFocus);
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

#pragma region Training

void Training()
{
	if (ImGui::CollapsingHeader("Training"))
	{
		ImGui::Text("");

		auto ResetMissionOverlay = [&]()
		{
			ResetConfigGroup(MissionOverlay);

			ImGui::SetWindowPos
			(
				"GUI_MissionOverlay",
				ImVec2
				(
					static_cast<float>(activeConfig.MissionOverlay.x),
					static_cast<float>(activeConfig.MissionOverlay.y)
				)
			);
		};

		if (GUI_ResetButton())
		{
			ResetConfigEntry(infiniteHitPoints);
			ResetConfigEntry(infiniteMagicPoints);
			ResetConfigEntry(disableTimer);

			Training_ToggleInfiniteHitPoints  (activeConfig.infiniteHitPoints  );
			Training_ToggleInfiniteMagicPoints(activeConfig.infiniteMagicPoints);
			Training_ToggleDisableTimer       (activeConfig.disableTimer       );

			ResetMissionOverlay();
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

		GUI_SectionEnd();
		ImGui::Text("");


		GUI_SectionStart("Mission Overlay");

		GUI_Checkbox2
		(
			"Enable",
			activeConfig.MissionOverlay.enable,
			queuedConfig.MissionOverlay.enable
		);
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			ResetMissionOverlay();
		}
		ImGui::Text("");

		bool condition = !activeConfig.MissionOverlay.enable;

		GUI_PushDisable(condition);

		GUI_Color2
		(
			"Color",
			activeConfig.MissionOverlay.color,
			queuedConfig.MissionOverlay.color,
			ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview
		);

		GUI_PopDisable(condition);

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
			ResetConfigGroup(Yamato);
			ResetConfigGroup(YamatoForceEdge);
			ResetConfigGroup(SummonedSwords);

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

void Main()
{
	if (!Main_run)
	{
		Main_run = true;
		ImGui::SetNextWindowSize(ImVec2(600, 650));

		if constexpr (debug)
		{
			ImGui::SetNextWindowPos(ImVec2(650, 50));
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

	if (ImGui::Begin("DDMK 2.7 Mary Nightly 14 January 2021", &g_pause))
	{
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

		GUI();
		Jukebox();
		Mobility();
		Other();
		Repair();
		Speed();
		System();
		Teleporter();
		Training();
		Vergil();

		ImGui::Text("");
	}
	ImGui::End();
}

#pragma endregion

#pragma region Sound

// @Todo: Remake.

void Sound()
{
	return;
	static bool run = false;
	if (!run)
	{
		run = true;

		ImGui::SetNextWindowSize(ImVec2(600, 650));
		ImGui::SetNextWindowPos(ImVec2(0, 0));
	}

	if (ImGui::Begin("Sound", &g_pause))
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









			// ImGui::Text("%c", vagiMetadata.signature[0]);
			// ImGui::SameLine();
			// ImGui::Text("%c", vagiMetadata.signature[1]);
			// ImGui::SameLine();
			// ImGui::Text("%c", vagiMetadata.signature[2]);
			// ImGui::SameLine();
			// ImGui::Text("%c", vagiMetadata.signature[3]);



		}();

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

		LogFunction();

		CreateTextures();
	}

	GUI_id = 0;

	if constexpr (debug)
	{
		Overlay();
		Overlay2();
	}

	MissionOverlay();

	WeaponSwitchController();

	if (g_pause)
	{
		Main();

		// if constexpr (debug)
		// {
		// 	Sound();
		// }
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

	Actor_UpdateIndices();
	Arcade_UpdateIndices();
	Color_UpdateValues();

	
	
	
	//ResetPermissions_UpdateIndices();
}

#ifdef __GARBAGE__





		// [&]()
		// {
		// 	if (!magicPointsDepletionValueQuicksilverAddr)
		// 	{
		// 		return;
		// 	}
		// 	auto & magicPointsDepletionValueQuicksilver = *magicPointsDepletionValueQuicksilverAddr;

		// 	if
		// 	(
		// 		GUI_InputDefault2
		// 		(
		// 			"Quicksilver",
		// 			activeConfig.magicPointsDepletionValueQuicksilver,
		// 			queuedConfig.magicPointsDepletionValueQuicksilver,
		// 			defaultConfig.magicPointsDepletionValueQuicksilver,
		// 			1.0f,
		// 			"%g",
		// 			ImGuiInputTextFlags_EnterReturnsTrue
		// 		)
		// 	)
		// 	{
		// 		magicPointsDepletionValueQuicksilver = activeConfig.magicPointsDepletionValueQuicksilver;
		// 	}
		// }();

		// [&]()
		// {
		// 	if (!magicPointsDepletionValueDoppelgangerAddr)
		// 	{
		// 		return;
		// 	}
		// 	auto & magicPointsDepletionValueDoppelganger = *magicPointsDepletionValueDoppelgangerAddr;

		// 	if
		// 	(
		// 		GUI_InputDefault2
		// 		(
		// 			"Doppelganger",
		// 			activeConfig.magicPointsDepletionValueDoppelganger,
		// 			queuedConfig.magicPointsDepletionValueDoppelganger,
		// 			defaultConfig.magicPointsDepletionValueDoppelganger,
		// 			1.0f,
		// 			"%g",
		// 			ImGuiInputTextFlags_EnterReturnsTrue
		// 		)
		// 	)
		// 	{
		// 		magicPointsDepletionValueDoppelganger = activeConfig.magicPointsDepletionValueDoppelganger;
		// 	}
		// }();

		// [&]()
		// {
		// 	if (!magicPointsDepletionValueDevilAddr)
		// 	{
		// 		return;
		// 	}
		// 	auto & magicPointsDepletionValueDevil = *magicPointsDepletionValueDevilAddr;

		// 	if
		// 	(
		// 		GUI_InputDefault2
		// 		(
		// 			"Devil",
		// 			activeConfig.magicPointsDepletionValueDevil,
		// 			queuedConfig.magicPointsDepletionValueDevil,
		// 			defaultConfig.magicPointsDepletionValueDevil,
		// 			1.0f,
		// 			"%g",
		// 			ImGuiInputTextFlags_EnterReturnsTrue
		// 		)
		// 	)
		// 	{
		// 		magicPointsDepletionValueDevil = activeConfig.magicPointsDepletionValueDevil;
		// 	}
		// }();


#endif
