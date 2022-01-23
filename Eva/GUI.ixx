module;
#include "../ThirdParty/ImGui/imgui.h"
#include "../ThirdParty/ImGui/imgui_internal.h"

#include <stdio.h>
export module GUI;

import Core;
import Core_GUI;
import Core_ImGui;

#include "../Core/Macros.h"

import Windows;

using namespace Windows;

import GlobalBase;
import GUIBase;

import Actor;
import Arcade;
import Config;
import Event;
import Global;
import Graphics;
import Internal;
import HUD;
import Input;
import Training;
import Vars;
import Window;

#define debug false



bool visibleMain     = false;
bool lastVisibleMain = false;



#pragma region Common

const char * Graphics_vSyncNames[] =
{
	"Auto",
	"Force Off",
	"Force On",
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

byte16 buttons[] =
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

const char * missionNames[] =
{
	"Prologue",
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
	"Mission 21",
	"Mission 22",
	"Mission 23",
	"Mission 24",
};

const char * modeNames[] =
{
	"Easy",
	"Normal",
	"Hard",
	"Dante Must Die",
};

uint8 modes[] =
{
	MODE::EASY,
	MODE::NORMAL,
	MODE::HARD,
	MODE::DANTE_MUST_DIE,
};

const char * characterNames[] =
{
	"Dante",
	"LDK",
	"Super Dante",
};

const char * meleeWeaponNames[] =
{
	"Force Edge",
	"Alastor",
	"Ifrit",
	"Sparda",
};

uint8 meleeWeapons[] =
{
	WEAPON::FORCE_EDGE,
	WEAPON::ALASTOR,
	WEAPON::IFRIT,
	WEAPON::SPARDA,
};

const char * meleeWeaponFormNames[] =
{
	"Default",
	"Sparda",
	"Yamato",
};

const char * rangedWeaponNames[] =
{
	"Handgun",
	"Shotgun",
	"Grenadegun",
	"Nightmare Beta",
};

uint8 rangedWeapons[] =
{
	WEAPON::HANDGUN,
	WEAPON::SHOTGUN,
	WEAPON::GRENADEGUN,
	WEAPON::NIGHTMARE_BETA,
};

#pragma endregion





#pragma region Actor

uint8 meleeWeaponSwitchButtonIndex  = 0;
uint8 rangedWeaponSwitchButtonIndex = 0;

uint8 Actor_meleeWeaponIndices [MELEE_WEAPON_COUNT ] = {};
uint8 Actor_rangedWeaponIndices[RANGED_WEAPON_COUNT] = {};

uint8 roundTripReturnButtonIndex = 0;

uint8 resetStateButtonIndices[RESET_STATE_BUTTON_COUNT] = {};

uint8 chargeButtonIndex = 0;



void Actor_UpdateIndices()
{
	UpdateMapIndex
	(
		buttons,
		meleeWeaponSwitchButtonIndex,
		activeConfig.meleeWeaponSwitchButton
	);
	UpdateMapIndex
	(
		buttons,
		rangedWeaponSwitchButtonIndex,
		activeConfig.rangedWeaponSwitchButton
	);

	for_all(meleeWeaponIndex, MELEE_WEAPON_COUNT)
	{
		UpdateMapIndex
		(
			meleeWeapons,
			Actor_meleeWeaponIndices[meleeWeaponIndex],
			activeConfig.Actor.meleeWeapons[meleeWeaponIndex]
		);
	}
	for_all(rangedWeaponIndex, RANGED_WEAPON_COUNT)
	{
		UpdateMapIndex
		(
			rangedWeapons,
			Actor_rangedWeaponIndices[rangedWeaponIndex],
			activeConfig.Actor.rangedWeapons[rangedWeaponIndex]
		);
	}

	UpdateMapIndex
	(
		buttons,
		roundTripReturnButtonIndex,
		activeConfig.roundTripReturnButton
	);

	for_all(index, RESET_STATE_BUTTON_COUNT)
	{
		UpdateMapIndex
		(
			buttons,
			resetStateButtonIndices[index],
			activeConfig.resetStateButtons[index]
		);
	}

	UpdateMapIndex
	(
		buttons,
		chargeButtonIndex,
		activeConfig.chargeButton
	);
}

void ActorSection()
{
	if (ImGui::CollapsingHeader("Actor"))
	{
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			ResetConfig(Actor);

			ResetConfig(enableForceEdgeFixes);
			ToggleForceEdgeFixes(activeConfig.enableForceEdgeFixes);

			ResetConfig(enableSpardaFixes);
			ToggleSpardaFixes(activeConfig.enableSpardaFixes);

			ResetConfig(enableYamatoFixes);
			ToggleYamatoFixes(activeConfig.enableYamatoFixes);

			ResetConfig(airHikeCoreAbility);
			ToggleAirHikeCoreAbility(activeConfig.airHikeCoreAbility);

			ResetConfig(infiniteRoundTrip);
			ToggleInfiniteRoundTrip(activeConfig.infiniteRoundTrip);

			ResetConfig(enableRoundTripReturnController);
			ResetConfig(roundTripReturnButton);

			ResetConfig(enableMeleeWeaponSwitchController);
			ResetConfig(meleeWeaponSwitchButton);

			ResetConfig(enableRangedWeaponSwitchController);
			ResetConfig(rangedWeaponSwitchButton);

			ResetConfig(enableResetStateController);
			ResetConfig(resetStateButtons);

			ResetConfig(enableChargeController);
			ResetConfig(chargeButton);
			ToggleChargeFixes(activeConfig.enableChargeController);

			Actor_UpdateIndices();
		}
		GUI_SectionEnd();
		ImGui::Text("");



		GUI_SectionStart("Fixes");

		if
		(
			GUI_Checkbox2
			(
				"Enable Force Edge Fixes",
				activeConfig.enableForceEdgeFixes,
				queuedConfig.enableForceEdgeFixes
			)
		)
		{
			ToggleForceEdgeFixes(activeConfig.enableForceEdgeFixes);
		}
		ImGui::SameLine();
		TooltipHelper
		(
			"(?)",
			"Unlocks Stinger and Round Trip for Force Edge."
		);

		if
		(
			GUI_Checkbox2
			(
				"Enable Sparda Fixes",
				activeConfig.enableSpardaFixes,
				queuedConfig.enableSpardaFixes
			)
		)
		{
			ToggleSpardaFixes(activeConfig.enableSpardaFixes);
		}
		ImGui::SameLine();
		TooltipHelper
		(
			"(?)",
			"Unlocks the full potential of Sparda.\n"
			"\n"
			"You may need to re-equip it and change rooms once.\n"
			"\n"
			"If you want to keep using Sparda, save at the mission end screen.\n"
			"Saving during the mission will not work!"
		);

		if
		(
			GUI_Checkbox2
			(
				"Enable Yamato Fixes",
				activeConfig.enableYamatoFixes,
				queuedConfig.enableYamatoFixes
			)
		)
		{
			ToggleYamatoFixes(activeConfig.enableYamatoFixes);
		}
		ImGui::SameLine();
		TooltipHelper
		(
			"(?)",
			"Allows Dante to use Yamato.\n"
			"\n"
			"Click on Get Yamato while playing as Dante to unlock it."
		);
		ImGui::SameLine();
		if (GUI_Button("Get Yamato"))
		{
			ItemData item =
			{
				0,
				ITEM_0::YAMATO,
				1
			};

			AddUniqueItem(item);
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



		GUI_SectionStart("Round Trip");

		if
		(
			GUI_Checkbox2
			(
				"Infinite Round Trip",
				activeConfig.infiniteRoundTrip,
				queuedConfig.infiniteRoundTrip
			)
		)
		{
			ToggleInfiniteRoundTrip(activeConfig.infiniteRoundTrip);
		}
		ImGui::Text("");

		GUI_Checkbox2
		(
			"Enable Return Controller",
			activeConfig.enableRoundTripReturnController,
			queuedConfig.enableRoundTripReturnController
		);
		ImGui::Text("");

		{
			bool condition = !activeConfig.enableRoundTripReturnController;

			GUI_PushDisable(condition);

			ImGui::PushItemWidth(150.0f);

			GUI_ComboMap2
			(
				"",
				buttonNames,
				buttons,
				roundTripReturnButtonIndex,
				activeConfig.roundTripReturnButton,
				queuedConfig.roundTripReturnButton,
				ImGuiComboFlags_HeightLargest
			);

			ImGui::PopItemWidth();

			GUI_PopDisable(condition);
		}

		GUI_SectionEnd();
		ImGui::Text("");



		ImGui::Text("Melee Weapon Switch Controller");
		ImGui::SameLine();
		TooltipHelper
		(
			"(?)",
			"To make this work it's necessary to update internal pointers and refresh the screen.\n"
			"That's why you often see an empty frame when switching.\n"
			"\n"
			"Left : Melee Weapon\n"
			"Right: Melee Weapon Form"
		);
		ImGui::Text("");

		if
		(
			GUI_Checkbox2
			(
				"Enable",
				activeConfig.enableMeleeWeaponSwitchController,
				queuedConfig.enableMeleeWeaponSwitchController
			)
		)
		{
			ToggleMeleeWeaponSwitchController(activeConfig.enableMeleeWeaponSwitchController);
		}
		ImGui::Text("");

		{
			bool condition = !activeConfig.enableMeleeWeaponSwitchController;

			GUI_PushDisable(condition);

			ImGui::PushItemWidth(200.0f);

			GUI_ComboMap2
			(
				"",
				buttonNames,
				buttons,
				meleeWeaponSwitchButtonIndex,
				activeConfig.meleeWeaponSwitchButton,
				queuedConfig.meleeWeaponSwitchButton,
				ImGuiComboFlags_HeightLargest
			);

			GUI_Slider2<uint8>
			(
				"",
				activeConfig.Actor.meleeWeaponCount,
				queuedConfig.Actor.meleeWeaponCount,
				1,
				MELEE_WEAPON_COUNT
			);

			for_all(meleeWeaponIndex, MELEE_WEAPON_COUNT)
			{
				bool condition = (meleeWeaponIndex >= activeConfig.Actor.meleeWeaponCount);

				GUI_PushDisable(condition);

				GUI_ComboMap2
				(
					"",
					meleeWeaponNames,
					meleeWeapons,
					Actor_meleeWeaponIndices[meleeWeaponIndex],
					activeConfig.Actor.meleeWeapons[meleeWeaponIndex],
					queuedConfig.Actor.meleeWeapons[meleeWeaponIndex]
				);

				ImGui::SameLine();

				GUI_Combo2
				(
					"",
					meleeWeaponFormNames,
					activeConfig.Actor.meleeWeaponForms[meleeWeaponIndex],
					queuedConfig.Actor.meleeWeaponForms[meleeWeaponIndex]
				);

				GUI_PopDisable(condition);
			}

			ImGui::PopItemWidth();

			GUI_PopDisable(condition);
		}

		GUI_SectionEnd();
		ImGui::Text("");



		ImGui::Text("Ranged Weapon Switch Controller");
		ImGui::SameLine();
		TooltipHelper
		(
			"(?)",
			"Be careful: Switching while projectiles are on screen can freeze the game."
		);
		ImGui::Text("");

		if
		(
			GUI_Checkbox2
			(
				"Enable",
				activeConfig.enableRangedWeaponSwitchController,
				queuedConfig.enableRangedWeaponSwitchController
			)
		)
		{
			ToggleRangedWeaponSwitchController(activeConfig.enableRangedWeaponSwitchController);
		}
		ImGui::Text("");

		{
			bool condition = !activeConfig.enableRangedWeaponSwitchController;

			GUI_PushDisable(condition);

			ImGui::PushItemWidth(200.0f);

			GUI_ComboMap2
			(
				"",
				buttonNames,
				buttons,
				rangedWeaponSwitchButtonIndex,
				activeConfig.rangedWeaponSwitchButton,
				queuedConfig.rangedWeaponSwitchButton,
				ImGuiComboFlags_HeightLargest
			);

			GUI_Slider2<uint8>
			(
				"",
				activeConfig.Actor.rangedWeaponCount,
				queuedConfig.Actor.rangedWeaponCount,
				1,
				RANGED_WEAPON_COUNT
			);

			for_all(rangedWeaponIndex, RANGED_WEAPON_COUNT)
			{
				bool condition = (rangedWeaponIndex >= activeConfig.Actor.rangedWeaponCount);

				GUI_PushDisable(condition);

				GUI_ComboMap2
				(
					"",
					rangedWeaponNames,
					rangedWeapons,
					Actor_rangedWeaponIndices[rangedWeaponIndex],
					activeConfig.Actor.rangedWeapons[rangedWeaponIndex],
					queuedConfig.Actor.rangedWeapons[rangedWeaponIndex]
				);

				GUI_PopDisable(condition);
			}

			ImGui::PopItemWidth();

			GUI_PopDisable(condition);
		}

		GUI_SectionEnd();
		ImGui::Text("");






		GUI_SectionStart("Reset State Controller");

		GUI_Checkbox2
		(
			"Enable",
			activeConfig.enableResetStateController,
			queuedConfig.enableResetStateController
		);
		ImGui::SameLine();
		TooltipHelper
		(
			"(?)",
			"Resets the actor's state which allows you to immediately follow up with another action."
		);
		ImGui::Text("");



		{
			bool condition = !activeConfig.enableResetStateController;

			GUI_PushDisable(condition);

			ImGui::PushItemWidth(150.0f);

			for_all(index, 4)
			{
				GUI_ComboMap2
				(
					"",
					buttonNames,
					buttons,
					resetStateButtonIndices[index],
					activeConfig.resetStateButtons[index],
					queuedConfig.resetStateButtons[index],
					ImGuiComboFlags_HeightLargest
				);
			}




			ImGui::PopItemWidth();

			GUI_PopDisable(condition);
		}


		GUI_SectionEnd();
		ImGui::Text("");



		GUI_SectionStart("Charge Controller");


		// GUI_Input
		// (
		// 	"g_chargeValue",
		// 	g_chargeValue
		// );

		// GUI_Input
		// (
		// 	"g_maxChargeValue",
		// 	g_maxChargeValue
		// );



		if
		(
			GUI_Checkbox2
			(
				"Enable",
				activeConfig.enableChargeController,
				queuedConfig.enableChargeController
			)
		)
		{
			ToggleChargeFixes(activeConfig.enableChargeController);
		}
		ImGui::SameLine();
		TooltipHelper
		(
			"(?)",
			"Allows you to charge ranged weapons while being active."
		);
		ImGui::Text("");



		{
			bool condition = !activeConfig.enableChargeController;

			GUI_PushDisable(condition);

			ImGui::PushItemWidth(150.0f);

			GUI_ComboMap2
			(
				"",
				buttonNames,
				buttons,
				chargeButtonIndex,
				activeConfig.chargeButton,
				queuedConfig.chargeButton,
				ImGuiComboFlags_HeightLargest
			);

			ImGui::PopItemWidth();

			GUI_PopDisable(condition);
		}















		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Arcade

uint8 Arcade_modeIndex         = 0;
uint8 Arcade_meleeWeaponIndex  = 0;
uint8 Arcade_rangedWeaponIndex = 0;



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
		meleeWeapons,
		Arcade_meleeWeaponIndex,
		activeConfig.Arcade.meleeWeapon
	);

	UpdateMapIndex
	(
		rangedWeapons,
		Arcade_rangedWeaponIndex,
		activeConfig.Arcade.rangedWeapon
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

		GUI_ComboMap2
		(
			"Mode",
			modeNames,
			modes,
			Arcade_modeIndex,
			activeConfig.Arcade.mode,
			queuedConfig.Arcade.mode
		);

		// Track
		{
			bool condition = activeConfig.Arcade.ignoreTrack;

			GUI_PushDisable(condition);

			GUI_InputDefault2
			(
				"Track",
				activeConfig.Arcade.track,
				queuedConfig.Arcade.track,
				defaultConfig.Arcade.track
			);

			GUI_PopDisable(condition);

			ImGui::SameLine();

			GUI_Checkbox2
			(
				"Ignore",
				activeConfig.Arcade.ignoreTrack,
				queuedConfig.Arcade.ignoreTrack
			);
		}

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
				"X",
				activeConfig.Arcade.position.x,
				queuedConfig.Arcade.position.x,
				defaultConfig.Arcade.position.x,
				1.0f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);

			GUI_PopDisable(condition);

			ImGui::SameLine();

			GUI_Checkbox2
			(
				"Ignore",
				activeConfig.Arcade.ignorePosition,
				queuedConfig.Arcade.ignorePosition
			);

			GUI_PushDisable(condition);

			GUI_InputDefault2
			(
				"Y",
				activeConfig.Arcade.position.y,
				queuedConfig.Arcade.position.y,
				defaultConfig.Arcade.position.y,
				1.0f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_InputDefault2
			(
				"Z",
				activeConfig.Arcade.position.z,
				queuedConfig.Arcade.position.z,
				defaultConfig.Arcade.position.z,
				1.0f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_InputDefault2
			(
				"Rotation",
				activeConfig.Arcade.position.a,
				queuedConfig.Arcade.position.a,
				defaultConfig.Arcade.position.a,
				1.0f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);

			GUI_PopDisable(condition);
		}


		GUI_InputDefault2
		(
			"Hit Points",
			activeConfig.Arcade.hitPoints,
			queuedConfig.Arcade.hitPoints,
			defaultConfig.Arcade.hitPoints
		);
		GUI_InputDefault2
		(
			"Magic Points",
			activeConfig.Arcade.magicPoints,
			queuedConfig.Arcade.magicPoints,
			defaultConfig.Arcade.magicPoints
		);


		GUI_Combo2
		(
			"Character",
			characterNames,
			activeConfig.Arcade.character,
			queuedConfig.Arcade.character
		);


		GUI_ComboMap2
		(
			"Melee Weapon",
			meleeWeaponNames,
			meleeWeapons,
			Arcade_meleeWeaponIndex,
			activeConfig.Arcade.meleeWeapon,
			queuedConfig.Arcade.meleeWeapon
		);
		GUI_Combo2
		(
			"Melee Weapon Form",
			meleeWeaponFormNames,
			activeConfig.Arcade.meleeWeaponForm,
			queuedConfig.Arcade.meleeWeaponForm
		);
		GUI_ComboMap2
		(
			"Ranged Weapon",
			rangedWeaponNames,
			rangedWeapons,
			Arcade_rangedWeaponIndex,
			activeConfig.Arcade.rangedWeapon,
			queuedConfig.Arcade.rangedWeapon
		);

		ImGui::PopItemWidth();





		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Boss Rush

void BossRushSection()
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
		ImGui::Text("");

		GUI_SectionStart("Mission 22");

		GUI_Checkbox2
		(
			"Skip Mundus Part 1",
			activeConfig.BossRush.Mission22.skipMundusPart1,
			queuedConfig.BossRush.Mission22.skipMundusPart1
		);

		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Mission Select

uint8 MissionSelect_modeIndex = 0;

void MissionSelect_UpdateIndices()
{
	UpdateMapIndex
	(
		modes,
		MissionSelect_modeIndex,
		activeConfig.MissionSelect.mode
	);
}



void MissionSelectSection()
{
	if (ImGui::CollapsingHeader("Mission Select"))
	{
		ImGui::Text("");

		GUI_Checkbox2
		(
			"Enable",
			activeConfig.MissionSelect.enable,
			queuedConfig.MissionSelect.enable
		);
		ImGui::SameLine();
		TooltipHelper
		(
			"(?)",
			"Keep in mind that, unlike later entries in the series, your progress "
			"is not automatically adjusted for the selected mission. "
			"So depending on your overall progress the game may behave unexpectedly. "
			"Some areas may not be accessible, earlier items may still be available "
			"later in the game, etc.",
			400.0f
		);
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			ResetConfig(MissionSelect);

			MissionSelect_UpdateIndices();
		}
		ImGui::Text("");

		ImGui::PushItemWidth(200.0f);

		GUI_Combo2
		(
			"Mission",
			missionNames,
			activeConfig.MissionSelect.mission,
			queuedConfig.MissionSelect.mission,
			ImGuiComboFlags_HeightLargest
		);

		GUI_ComboMap2
		(
			"Mode",
			modeNames,
			modes,
			MissionSelect_modeIndex,
			activeConfig.MissionSelect.mode,
			queuedConfig.MissionSelect.mode
		);

		ImGui::PopItemWidth();

		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Overlays









const char * mainOverlayLabel = "MainOverlay";

void MainOverlayWindow()
{
	auto Function = [&]()
	{
		if (activeConfig.mainOverlayData.showFocus)
		{
			auto color = ImVec4(0, 1, 0, 1);
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

		if (activeConfig.mainOverlayData.showFrameRateMultiplier)
		{
			ImGui::Text("g_frameRateMultiplier %g", g_frameRateMultiplier);
		}

		if
		(
			activeConfig.mainOverlayData.showFocus               ||
			activeConfig.mainOverlayData.showFPS                 ||
			activeConfig.mainOverlayData.showSizes               ||
			activeConfig.mainOverlayData.showFrameRateMultiplier
		)
		{
			ImGui::Text("");
		}

		if (activeConfig.mainOverlayData.showEventData)
		{
			[&]()
			{
				IntroduceSessionData(return);
				IntroduceEventData(return);

				ImGui::Text("event     %.8X", sessionData.event  );
				ImGui::Text("track     %u"  , eventData.track    );
				ImGui::Text("room      %u"  , eventData.room     );
				ImGui::Text("nextTrack %u"  , eventData.nextTrack);
				ImGui::Text("nextRoom  %u"  , eventData.nextRoom );
			}();
			ImGui::Text("");
		}

		if (activeConfig.mainOverlayData.showPosition)
		{
			[&]()
			{
				IntroduceMainActorData(actorData, return);

				ImGui::Text("X        %g", actorData.position.x);
				ImGui::Text("Y        %g", actorData.position.y);
				ImGui::Text("Z        %g", actorData.position.z);
				ImGui::Text("Rotation %g", actorData.rotation  );
			}();

			ImGui::Text("");
		}

		if constexpr (debug)
		{
			ImGui::Text("meleeWeaponIndex  %u", activeConfig.Actor.meleeWeaponIndex );
			ImGui::Text("rangedWeaponIndex %u", activeConfig.Actor.rangedWeaponIndex);
			ImGui::Text("");

			[&]()
			{
				IntroduceSessionData(return);
				IntroduceMainActorData(actorData, return);

				ImGui::Text("state %X", sessionData.state);
				ImGui::Text("");

				for_all(index, 8)
				{
					ImGui::Text("state[%u] %X", index, actorData.state[index]);
				}
				ImGui::Text("");

				ImGui::Text("state[1] %u", actorData.state[1]);
				ImGui::Text("");

				{
					auto color = ImVec4(0, 1, 0, 1);

					if (sessionData.state & 0x200)
					{
						color = ImVec4(1, 0, 0, 1);
					}

					ImGui::PushStyleColor(ImGuiCol_Text, color);

					ImGui::Text("Busy");

					ImGui::PopStyleColor();
				}
			}();
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
			"Show Frame Rate Multiplier",
			activeConfig.mainOverlayData.showFrameRateMultiplier,
			queuedConfig.mainOverlayData.showFrameRateMultiplier
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


void Overlays()
{
	if (ImGui::CollapsingHeader("Overlays"))
	{
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			ResetConfig(mainOverlayData              );
			// ResetConfig(missionOverlayData           );
			// ResetConfig(newMovesOverlayDataDante     );
			// ResetConfig(newMovesOverlayDataVergil    );
			// ResetConfig(bossLadyActionsOverlayData  );
			// ResetConfig(bossVergilActionsOverlayData);

			ImGui::SetWindowPos(mainOverlayLabel              , *reinterpret_cast<ImVec2*>(&activeConfig.mainOverlayData.pos              ));
			// ImGui::SetWindowPos(missionOverlayLabel           , *reinterpret_cast<ImVec2*>(&activeConfig.missionOverlayData.pos           ));
			// ImGui::SetWindowPos(newMovesOverlayLabelDante     , *reinterpret_cast<ImVec2*>(&activeConfig.newMovesOverlayDataDante.pos     ));
			// ImGui::SetWindowPos(newMovesOverlayLabelVergil    , *reinterpret_cast<ImVec2*>(&activeConfig.newMovesOverlayDataVergil.pos    ));
			// ImGui::SetWindowPos(newMovesOverlayLabelBossLady  , *reinterpret_cast<ImVec2*>(&activeConfig.bossLadyActionsOverlayData.pos  ));
			// ImGui::SetWindowPos(newMovesOverlayLabelBossVergil, *reinterpret_cast<ImVec2*>(&activeConfig.bossVergilActionsOverlayData.pos));
		}

		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("Main");

		MainOverlaySettings();

		// GUI_SectionEnd();
		// ImGui::Text("");



		// if constexpr (debug)
		// {
		// 	GUI_SectionStart("2");

		// 	Overlay2Settings();

		// 	GUI_SectionEnd();
		// 	ImGui::Text("");
		// }



		// GUI_SectionStart("Mission");

		// MissionOverlaySettings();

		// GUI_SectionEnd();
		// ImGui::Text("");



		// GUI_SectionStart("New Moves Dante");

		// NewMovesOverlaySettingsDante();

		// GUI_SectionEnd();
		// ImGui::Text("");



		// GUI_SectionStart("New Moves Vergil");

		// NewMovesOverlaySettingsVergil();

		// GUI_SectionEnd();
		// ImGui::Text("");



		// GUI_SectionStart("New Moves Boss Lady");

		// NewMovesOverlaySettingsBossLady();

		// GUI_SectionEnd();
		// ImGui::Text("");



		// GUI_SectionStart("New Moves Boss Vergil");

		// NewMovesOverlaySettingsBossVergil();








		ImGui::Text("");
	}
}




#pragma endregion

#pragma region System

void System()
{
	if (ImGui::CollapsingHeader("System"))
	{
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			ResetConfig(skipIntro);
			ToggleSkipIntro(activeConfig.skipIntro);

			ResetConfig(disablePauseRestrictions);
			ToggleDisablePauseRestrictions(activeConfig.disablePauseRestrictions);

			ResetConfig(frameRate);
			ResetConfig(vSync);
			UpdateFrameRate();

			ResetConfig(hideMouseCursor);
			ResetConfig(gamepadName);
			ResetConfig(gamepadButton);

			ResetConfig(windowPosX);
			ResetConfig(windowPosY);
			ResetConfig(forceWindowFocus);
			ToggleForceWindowFocus(activeConfig.forceWindowFocus);
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
				"Disable Pause Restrictions",
				activeConfig.disablePauseRestrictions,
				queuedConfig.disablePauseRestrictions
			)
		)
		{
			ToggleDisablePauseRestrictions(activeConfig.disablePauseRestrictions);
		}

		ImGui::SameLine();
		TooltipHelper
		(
			"(?)",
			"Allows you to pause at any time. Use at your own risk."
		);

		//ImGui::Text("");





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
			GUI_InputDefault2<float>
			(
				"Frame Rate",
				activeConfig.frameRate,
				queuedConfig.frameRate,
				defaultConfig.frameRate,
				1,
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
		ImGui::Text("");



		ImGui::PushItemWidth(300);

		if
		(
			ImGui::InputText
			(
				"Gamepad Name",
				queuedConfig.gamepadName,
				sizeof(queuedConfig.gamepadName),
				ImGuiInputTextFlags_EnterReturnsTrue
			)
		)
		{
			::GUI::save = true;
		}

		GUI_Input2<byte8>
		(
			"Gamepad Button",
			activeConfig.gamepadButton,
			queuedConfig.gamepadButton,
			1,
			"%u",
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		ImGui::SameLine();
		TooltipHelper
		(
			"(?)",
			"Toggle Show Main"
		);

		ImGui::PopItemWidth();



		GUI_SectionEnd();
		ImGui::Text("");









		GUI_SectionStart("Window");

		ImGui::PushItemWidth(150);

		GUI_InputDefault2<int32>
		(
			"X",
			activeConfig.windowPosX,
			queuedConfig.windowPosX,
			defaultConfig.windowPosX,
			1,
			"%d",
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		GUI_InputDefault2<int32>
		(
			"Y",
			activeConfig.windowPosY,
			queuedConfig.windowPosY,
			defaultConfig.windowPosY,
			1,
			"%d",
			ImGuiInputTextFlags_EnterReturnsTrue
		);

		ImGui::PopItemWidth();

		ImGui::Text("");

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
			ToggleForceWindowFocus(activeConfig.forceWindowFocus);
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



		if (GUI_ResetButton())
		{
			ResetConfig(infiniteHitPoints);
			ToggleInfiniteHitPoints(activeConfig.infiniteHitPoints);

			ResetConfig(infiniteMagicPoints);
			ToggleInfiniteMagicPoints(activeConfig.infiniteMagicPoints);

			ResetConfig(disableTimer);
			ToggleDisableTimer(activeConfig.disableTimer);
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
			ToggleInfiniteHitPoints(activeConfig.infiniteHitPoints);
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
			ToggleInfiniteMagicPoints(activeConfig.infiniteMagicPoints);
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
			ToggleDisableTimer(activeConfig.disableTimer);
		}



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











bool showItemWindow = false;


void ItemWindow()
{

	if (!showItemWindow)
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



	if (ImGui::Begin("ItemWindow", &showItemWindow))
	{
		ImGui::Text("");

		[&]()
		{
			IntroduceSessionData(return);

			ImGui::PushItemWidth(150.0f);

			GUI_Input
			(
				"Count",
				sessionData.itemCount
			);
			ImGui::Text("");

			for_all(itemIndex, 50)
			{
				auto & item = sessionData.items[itemIndex];

				ImGui::Text("item[%u]", itemIndex);

				GUI_Input
				(
					"Category",
					item.category
				);
				GUI_Input
				(
					"Id",
					item.id
				);
				GUI_Input
				(
					"Count",
					item.count
				);

				ImGui::Text("");
			}

			ImGui::PopItemWidth();
		}();

		ImGui::Text("");
	}

	ImGui::End();
}







bool showActorWindow = false;


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

		[&]()
		{
			IntroduceMainActorData(actorData, return);

			ImGui::PushItemWidth(150.0f);

			GUI_Input
			(
				"X",
				actorData.position.x,
				1.0f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input
			(
				"Y",
				actorData.position.y,
				1.0f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input
			(
				"Z",
				actorData.position.z,
				1.0f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input
			(
				"A",
				actorData.position.a,
				1.0f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input
			(
				"Fast Rotation",
				actorData.rotation,
				0.1f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input
			(
				"Rotation",
				actorData.rotation,
				0.05f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input
			(
				"Slow Rotation",
				actorData.rotation,
				0.01f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);







			ImGui::PopItemWidth();
		}();

		ImGui::Text("");
	}

	ImGui::End();
}
















#pragma region Debug


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

		if (GUI_Button("Items"))
		{
			showItemWindow = true;
		}
		ImGui::Text("");




















		ImGui::PushItemWidth(150);

		static uint8 meleeWeapon = WEAPON::ALASTOR;
		static uint8 rangedWeapon = WEAPON::HANDGUN;
		static uint8 meleeWeaponForm = MELEE_WEAPON_FORM::DEFAULT;

		[&]()
		{
			IntroduceMainActorData(actorData, return);
			IntroduceWeaponData(return);

			GUI_Input
			(
				"meleeWeapon",
				meleeWeapon
			);
			ImGui::SameLine();
			GUI_Checkbox
			(
				"Update",
				weaponData.updateMeleeWeapon
			);

			GUI_Input
			(
				"rangedWeapon",
				rangedWeapon
			);
			ImGui::SameLine();
			GUI_Checkbox
			(
				"Update",
				weaponData.updateRangedWeapon
			);

			GUI_Input
			(
				"meleeWeaponForm",
				meleeWeaponForm
			);

			if (GUI_Button("Apply"))
			{
				actorData.meleeWeapon     = meleeWeapon;
				actorData.rangedWeapon    = rangedWeapon;
				actorData.meleeWeaponForm = meleeWeaponForm;

				func_3C8DC0();
			}
			ImGui::Text("");




			if (GUI_Button("Update Melee Weapon"))
			{
				actorData.meleeWeapon     = meleeWeapon;
				actorData.rangedWeapon    = rangedWeapon;
				actorData.meleeWeaponForm = meleeWeaponForm;

				func_2C99C0(meleeWeapon, 0);
			}
			ImGui::Text("");

			if (GUI_Button("Update Melee Weapon Form"))
			{
				actorData.meleeWeapon     = meleeWeapon;
				actorData.rangedWeapon    = rangedWeapon;
				actorData.meleeWeaponForm = meleeWeaponForm;

				func_2C4A00(meleeWeaponForm);
			}
			ImGui::Text("");

			if (GUI_Button("Update Ranged Weapon"))
			{
				actorData.meleeWeapon     = meleeWeapon;
				actorData.rangedWeapon    = rangedWeapon;
				actorData.meleeWeaponForm = meleeWeaponForm;

				func_2C4C50(rangedWeapon);
			}
			ImGui::Text("");





		}();


















		// if (GUI_Button("Alastor"))
		// {

		// 		actorData.meleeWeapon = WEAPON::ALASTOR;
		// 		actorData.meleeWeaponForm = MELEE_WEAPON_FORM::DEFAULT;

		// 		weaponData.update = true;

		// 		func_3C8DC0();


		// 	[&]()
		// 	{



		// 	}();
		// }
		// ImGui::Text("");


		// if (GUI_Button("Sparda"))
		// {
		// 	[&]()
		// 	{
		// 		IntroduceMainActorData(actorData, return);
		// 		IntroduceWeaponData(return);

		// 		actorData.meleeWeapon = WEAPON::SPARDA;
		// 		actorData.meleeWeaponForm = MELEE_WEAPON_FORM::SPARDA;

		// 		weaponData.update = true;

		// 		func_3C8DC0();
		// 	}();
		// }
		// ImGui::Text("");








		ImGui::PopItemWidth();



































		// GUI_SectionStart("Air Hike");


		// GUI_SectionEnd();
		// ImGui::Text("");














		if
		(
			GUI_Checkbox2
			(
				"Screen Effect Force Max Timer",
				activeConfig.screenEffectForceMaxTimer,
				queuedConfig.screenEffectForceMaxTimer
			)
		)
		{
			ToggleScreenEffectForceMaxTimer(activeConfig.screenEffectForceMaxTimer);
		}
		ImGui::Text("");



		if
		(
			GUI_Checkbox2
			(
				"Disable Player Actor Idle Timer",
				activeConfig.disablePlayerActorIdleTimer,
				queuedConfig.disablePlayerActorIdleTimer
			)
		)
		{
			ToggleDisablePlayerActorIdleTimer(activeConfig.disablePlayerActorIdleTimer);
		}
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

		// if
		// (
		// 	GUI_Checkbox2
		// 	(
		// 		"Disable Video Timer",
		// 		activeConfig.disableVideoTimer,
		// 		queuedConfig.disableVideoTimer
		// 	)
		// )
		// {
		// 	ToggleDisableVideoTimer(activeConfig.disableVideoTimer);
		// }
		// ImGui::Text("");




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



		[&]()
		{
			if (!InGame())
			{
				ImGui::Text("Invalid Pointer");

				return;
			}

			IntroduceSessionData(return);
			IntroduceEventData(return);
			IntroduceMainActorData(actorData, return);

			auto & nextPosition = *reinterpret_cast<vec4 *>(appBaseAddr + 0x27E82A0);



			if (GUI_Button("Clear"))
			{
				eventData.nextRoom = eventData.nextTrack = 0;

				SetMemory
				(
					&nextPosition,
					0,
					sizeof(nextPosition)
				);
			}
			ImGui::SameLine();

			if (GUI_Button("Current"))
			{
				eventData.nextTrack = eventData.track;
				eventData.nextRoom  = eventData.room;

				nextPosition.x = actorData.position.x;
				nextPosition.y = actorData.position.y;
				nextPosition.z = actorData.position.z;
				nextPosition.a = actorData.rotation;
			}
			ImGui::Text("");



			constexpr float width = 150.0f;

			ImGui::PushItemWidth(width);

			ImGui::Text("Current");

			GUI_Input<uint32>
			(
				"Track",
				eventData.track,
				0,
				"%u",
				ImGuiInputTextFlags_ReadOnly
			);

			GUI_Input<uint32>
			(
				"Room",
				eventData.room,
				0,
				"%u",
				ImGuiInputTextFlags_ReadOnly
			);

			GUI_Input<float>
			(
				"X",
				actorData.position.x,
				0,
				"%g",
				ImGuiInputTextFlags_ReadOnly
			);

			GUI_Input<float>
			(
				"Y",
				actorData.position.y,
				0,
				"%g",
				ImGuiInputTextFlags_ReadOnly
			);

			GUI_Input<float>
			(
				"Z",
				actorData.position.z,
				0,
				"%g",
				ImGuiInputTextFlags_ReadOnly
			);

			GUI_Input<float>
			(
				"Rotation",
				actorData.rotation,
				0,
				"%g",
				ImGuiInputTextFlags_ReadOnly
			);

			ImGui::Text("Next");

			GUI_Input<uint32>
			(
				"Track",
				eventData.nextTrack,
				1,
				"%u",
				ImGuiInputTextFlags_EnterReturnsTrue
			);

			GUI_Input<uint32>
			(
				"Room",
				eventData.nextRoom,
				1,
				"%u",
				ImGuiInputTextFlags_EnterReturnsTrue
			);

			GUI_Input<float>
			(
				"X",
				nextPosition.x,
				1,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);

			GUI_Input<float>
			(
				"Y",
				nextPosition.y,
				1,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);

			GUI_Input<float>
			(
				"Z",
				nextPosition.z,
				1,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);

			GUI_Input<float>
			(
				"Rotation",
				nextPosition.a,
				1,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);

			if
			(
				GUI_Button
				(
					"Teleport",
					ImVec2
					(
						width,
						ImGui::GetFrameHeight()
					)
				)
			)
			{
				sessionData.event |= EVENT::TELEPORT;
			}

			ImGui::PopItemWidth();
		}();



		ImGui::Text("");
	}
}

#pragma endregion







#pragma region Key Bindings






void ReloadRoom()
{
	if (!InGame())
	{
		return;
	}



	IntroduceSessionData(return);
	IntroduceEventData(return);
	IntroduceMainActorData(actorData, return);

	auto & nextPosition = *reinterpret_cast<vec4 *>(appBaseAddr + 0x27E82A0);





	eventData.nextTrack = eventData.track;
	eventData.nextRoom  = eventData.room;

	nextPosition.x = actorData.position.x;
	nextPosition.y = actorData.position.y;
	nextPosition.z = actorData.position.z;
	nextPosition.a = actorData.rotation;


	sessionData.event |= EVENT::TELEPORT;
}




// void MoveToMainActor()
// {
// 	if
// 	(
// 		!activeConfig.Actor.enable ||
// 		!InGame()
// 	)
// 	{
// 		return;
// 	}

// 	LogFunction();



// 	byte8 * mainActorBaseAddr = 0;

// 	{
// 		IntroducePlayerCharacterNewActorData();

// 		mainActorBaseAddr = activeNewActorData.baseAddr;
// 	}

// 	IntroduceData(mainActorBaseAddr, mainActorData, PlayerActorData, return);



// 	old_for_each(uint8, playerIndex, 1, activeConfig.Actor.playerCount)
// 	{
// 		auto & playerData = GetActivePlayerData(playerIndex);

// 		old_for_all(uint8, characterIndex, playerData.characterCount){
// 		old_for_all(uint8, entityIndex   , ENTITY_COUNT             )
// 		{
// 			IntroducePlayerCharacterNewActorData(playerIndex, characterIndex, entityIndex);

// 			IntroduceData(newActorData.baseAddr, actorData, PlayerActorData, continue);

// 			actorData.position = mainActorData.position;
// 		}}
// 	}
// }








export KeyBinding keyBindings[] =
{
	{
		"Toggle Show Main",
		activeConfig.keyData[0],
		queuedConfig.keyData[0],
		defaultConfig.keyData[0],
		ToggleShowMain,
		KeyFlags_AtLeastOneKey
	},
	{
		"Reload Room",
		activeConfig.keyData[1],
		queuedConfig.keyData[1],
		defaultConfig.keyData[1],
		ReloadRoom
	},
	// {
	// 	"Move To Main Actor",
	// 	activeConfig.keyData[2],
	// 	queuedConfig.keyData[2],
	// 	defaultConfig.keyData[2],
	// 	MoveToMainActor
	// },
};



void KeyBindings()
{
	if (ImGui::CollapsingHeader("Key Bindings"))
	{
		ImGui::Text("");

		// DescriptionHelper("");
		// ImGui::Text("");




		bool condition = false;

		for_all(index, countof(keyBindings))
		{
			auto & keyBinding = keyBindings[index];

			if (keyBinding.showPopup)
			{
				condition = true;

				break;
			}
		}

		GUI_PushDisable(condition);

		for_all(index, countof(keyBindings))
		{
			auto & keyBinding = keyBindings[index];

			keyBinding.Main();
		}

		GUI_PopDisable(condition);






		ImGui::Text("");
	}
}














#pragma endregion



























void Main()
{
	if (!g_showMain)
	{
		return;
	}



	static bool run = false;

	if (!run)
	{
		run = true;

		constexpr float width  = 600;
		constexpr float height = 650;

		ImGui::SetNextWindowSize(ImVec2(width, height));

		if constexpr (debug)
		{
			ImGui::SetNextWindowPos
			(
				ImVec2
				(
					((g_renderSize.x - width) / 2),
					100
				)
			);
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
			DDMK_TITLE_EVA,
			&g_showMain
		)
	)
	{
		ImGui::Text("");






		GamepadClose
		(
			visibleMain,
			lastVisibleMain,
			CloseMain
		);




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



		ImGui::Text(PATREON_TEXT);
		ImGui::Text("");

		if (GUI_Button("Open Patreon Page"))
		{
			ShellExecuteA
			(
				0,
				"open",
				PATREON_LINK,
				0,
				0,
				SW_SHOW
			);
		}
		ImGui::Text("");



		ActorSection();
		ArcadeSection();
		BossRushSection();

		if constexpr (debug)
		{
			Debug();
		}


		KeyBindings();
		MissionSelectSection();
		Overlays();
		System();
		Teleporter();
		Training();

		ImGui::Text("");

		GUI_Checkbox2
		(
			"Show Credits",
			activeConfig.showCredits,
			queuedConfig.showCredits
		);



		ImGui::Text("");
	}

	ImGui::End();
}

#pragma endregion




































export void GUI_Render()
{
	::GUI::id = 0;



	Welcome();
	Main();
	CreditsWindow();

	if constexpr (debug)
	{
		ActorWindow();
		ItemWindow();
	}



	MainOverlayWindow();



	HandleKeyBindings
	(
		keyBindings,
		countof(keyBindings)
	);



	HandleSaveTimer(activeConfig.frameRate);



	// static bool enable = true;
	// ImGui::ShowDemoWindow(&enable);
}

export void GUI_Init()
{
	LogFunction();

	BuildFonts();

	UpdateGlobalScale();

	GUI_UpdateStyle();

	Actor_UpdateIndices();
	Arcade_UpdateIndices();
	MissionSelect_UpdateIndices();
}
