module;
#include "../ImGui/imgui.h"
export module Item;

import Core;

#include "../Core/Macros.h"

import Core_GUI;

import Config;
import Global;
import Input;
import Sound;
import Vars;

#define debug false

struct ItemHelper
{
	const uint8    itemIndex;
	const uint8    buyIndex;
	const uint8    itemCount;
	const uint32 * prices;
	const uint8    priceCount;
};

// @Research: Moving to Vars causes internal compiler error in MSVC.
constexpr ItemHelper itemHelpers[] =
{
	{ ITEM_VITAL_STAR_SMALL, BUY_VITAL_STAR_SMALL, 30, itemVitalStarSmallPrices, static_cast<uint8>(countof(itemVitalStarSmallPrices)) },
	{ ITEM_VITAL_STAR_LARGE, BUY_VITAL_STAR_LARGE, 30, itemVitalStarLargePrices, static_cast<uint8>(countof(itemVitalStarLargePrices)) },
	{ ITEM_DEVIL_STAR      , BUY_DEVIL_STAR      , 10, itemDevilStarPrices     , static_cast<uint8>(countof(itemDevilStarPrices     )) },
	{ ITEM_HOLY_WATER      , BUY_HOLY_WATER      , 30, itemHolyWaterPrices     , static_cast<uint8>(countof(itemHolyWaterPrices     )) },
	{ ITEM_BLUE_ORB        , BUY_BLUE_ORB        , 6 , itemBlueOrbPrices       , static_cast<uint8>(countof(itemBlueOrbPrices       )) },
	{ ITEM_PURPLE_ORB      , BUY_PURPLE_ORB      , 7 , itemPurpleOrbPrices     , static_cast<uint8>(countof(itemPurpleOrbPrices     )) },
	{ ITEM_GOLD_ORB        , BUY_GOLD_ORB        , 3 , itemGoldOrbPrices       , static_cast<uint8>(countof(itemGoldOrbPrices       )) },
	{ ITEM_YELLOW_ORB      , BUY_YELLOW_ORB      , 99, itemYellowOrbPrices     , static_cast<uint8>(countof(itemYellowOrbPrices     )) },
};



uint8 selectIndex = 0;



void Open()
{
	ToggleCursor();

	ToggleDisableGetInput(true);

	selectIndex = 0;

	g_timeout = 30.0f;
};

void Close()
{
	g_showItemWindow     = false;
	g_lastShowItemWindow = false;

	ToggleCursor();

	ToggleDisableGetInput(false);

	PlaySound
	(
		0,
		3
	);
};









export void ItemWindow()
{

	// @Todo: Global and array.
	static bool executeUp = true;
	static bool executeDown = true;
	static bool executeA = true;
	static bool executeB = true;


	static bool executeUp2 = true;
	static bool executeDown2 = true;




	auto & gamepad = GetGamepad(0);

	//ENGINE_GAMEPAD gamepad = {};


	//static float timeout = 0;



	IntroduceMissionData(return);

	IntroduceEventData(return);





	auto GetItemCount = [&](const ItemHelper & itemHelper) -> uint8 &
	{
		return missionData.itemCounts[itemHelper.itemIndex];
	};

	auto GetBuyCount = [&](const ItemHelper & itemHelper) -> uint8 &
	{
		return missionData.buyCounts[itemHelper.buyIndex];
	};

	auto GetPrice = [&](const ItemHelper & itemHelper)
	{
		uint32 price = 0;

		auto & buyCount = GetBuyCount(itemHelper);

		if (buyCount >= itemHelper.priceCount)
		{
			price = itemHelper.prices[(itemHelper.priceCount - 1)];
		}
		else
		{
			price = itemHelper.prices[buyCount];
		}

		return price;
	};

	auto BuyItem = [&](uint8 itemHelperIndex)
	{
		auto & itemHelper = itemHelpers[itemHelperIndex];

		auto & itemCount = GetItemCount(itemHelper);
		auto & buyCount = GetBuyCount(itemHelper);
		auto price = GetPrice(itemHelper);

		if
		(
			(itemCount >= itemHelper.itemCount) ||
			(missionData.redOrbs < price)
		)
		{
			PlaySound
			(
				0,
				19
			);

			return;
		}

		itemCount++;
		buyCount++;

		if (buyCount > 254)
		{
			buyCount = 254;
		}

		missionData.redOrbs -= price;

		PlaySound
		(
			0,
			18
		);



		IntroduceMainActorData(mainActorData, return);
		IntroduceData(g_playerActorBaseAddrs[0], defaultMainActorData, PlayerActorData, return);

		if (itemHelper.itemIndex == ITEM_BLUE_ORB)
		{
			auto value = (mainActorData.hitPoints + 1000.0f);

			mainActorData.hitPoints = value;
			mainActorData.maxHitPoints = value;

			defaultMainActorData.hitPoints = value;
			defaultMainActorData.maxHitPoints = value;
		}
		else if (itemHelper.itemIndex == ITEM_PURPLE_ORB)
		{
			auto value = (mainActorData.magicPoints + 1000.0f);

			mainActorData.magicPoints = value;
			mainActorData.maxMagicPoints = value;

			defaultMainActorData.magicPoints = value;
			defaultMainActorData.maxMagicPoints = value;
		}
	};



	if (!g_showItemWindow)
	{
		return;
	}

	if (g_lastShowItemWindow != g_showItemWindow)
	{
		g_lastShowItemWindow = g_showItemWindow;

		Open();
	}

	static bool run = false;
	if (!run)
	{
		run = true;

		ImGui::SetNextWindowSize
		(
			ImVec2
			(
				350,
				350
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

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);

	if
	(
		ImGui::Begin
		(
			"ItemWindow",
			&g_showItemWindow,
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoResize
		)
	)
	{
		ImGui::Text("%u Red Orbs", missionData.redOrbs);
		ImGui::Text("");

		for_all(uint8, itemHelperIndex, countof(itemHelpers))
		{
			auto & itemHelper = itemHelpers[itemHelperIndex];

			auto & itemCount = GetItemCount(itemHelper);
			auto & buyCount = GetBuyCount(itemHelper);
			auto price = GetPrice(itemHelper);

			// if constexpr (debug)
			// {
			// 	ImGui::Text("%.4u", itemHelperIndex);
			// 	ImGui::SameLine();
			// }

			ImGui::Text("%u", price);
			ImGui::SameLine(60);

			ImGui::Text("%s", itemNames[itemHelper.itemIndex]);
			ImGui::SameLine(190);

			// ImGui::Text
			// (
			// 	"%u",
			// 	itemHelperIndex,
			// 	price,
			// 	itemNames[itemHelper.itemIndex]
			// );
			// ImGui::SameLine(200);

			ImGui::Text("%.2u / %.2u", itemCount, itemHelper.itemCount);
			ImGui::SameLine();

			// if constexpr (debug)
			// {
				
			// 	ImGui::Text("%u", buyCount);
			// 	ImGui::SameLine();
			// }

			if (GUI_Button("Buy"))
			{
				BuyItem(itemHelperIndex);
			}

			if (selectIndex == itemHelperIndex)
			{
				ImGui::SameLine();
				ImGui::Text("<-");
			}

			if constexpr (debug)
			{
				ImGui::Text("buyCount %u", buyCount);
			}





		}
		ImGui::Text("");

		if (GUI_Button("Close"))
		{
			Close();
		}
		ImGui::Text("");




		if (gamepad.buttons[0] & GAMEPAD_A)
		{
			if (executeA)
			{
				executeA = false;

				BuyItem(selectIndex);
			}
		}
		else
		{
			executeA = true;
		}






		if (gamepad.buttons[0] & GAMEPAD_UP)
		{
			if (executeUp)
			{
				executeUp = false;

				if (selectIndex > 0)
				{
					selectIndex--;
				}
				else
				{
					selectIndex = static_cast<uint8>(countof(itemHelpers) - 1);
				}

				PlaySound
				(
					0,
					2
				);
			}
		}
		else
		{
			executeUp = true;
		}



		if (gamepad.leftStickDirection[0] & GAMEPAD_UP)
		{
			if (executeUp2)
			{
				executeUp2 = false;

				if (selectIndex > 0)
				{
					selectIndex--;
				}
				else
				{
					selectIndex = static_cast<uint8>(countof(itemHelpers) - 1);
				}

				PlaySound
				(
					0,
					2
				);
			}
		}
		else
		{
			executeUp2 = true;
		}











		if (gamepad.buttons[0] & GAMEPAD_DOWN)
		{
			if (executeDown)
			{
				executeDown = false;

				if (selectIndex < static_cast<uint8>(countof(itemHelpers) - 1))
				{
					selectIndex++;
				}
				else
				{
					selectIndex = 0;
				}

				PlaySound
				(
					0,
					2
				);
			}
		}
		else
		{
			executeDown = true;
		}




		if (gamepad.leftStickDirection[0] & GAMEPAD_DOWN)
		{
			if (executeDown2)
			{
				executeDown2 = false;

				if (selectIndex < static_cast<uint8>(countof(itemHelpers) - 1))
				{
					selectIndex++;
				}
				else
				{
					selectIndex = 0;
				}

				PlaySound
				(
					0,
					2
				);
			}
		}
		else
		{
			executeDown2 = true;
		}



		if (gamepad.buttons[0] & GAMEPAD_B)
		{
			if (executeB)
			{
				executeB = false;

				if (g_timeout < 1)
				{
					Close();
				}
			}
		}
		else
		{
			executeB = true;
		}


















	}

	ImGui::End();

	ImGui::PopStyleVar(2);






	if (g_timeout > 0)
	{
		g_timeout--;
	}




}



namespaceStart(Item);

export void EventDelete()
{
	if (!activeConfig.Actor.enable)
	{
		return;
	}

	LogFunction();

	if (g_showItemWindow)
	{
		Close();
	}
}

export void TriggerCustomizeMenu()
{
	if (!activeConfig.Actor.enable)
	{
		return;
	}

	LogFunction();

	g_showItemWindow = true;
}






export void SceneMain()
{
	if (!activeConfig.Actor.enable)
	{
		return;
	}

	LogFunction();

	IntroduceSessionData();

	g_haywireNeoGenerator = false;
}

export void SceneMissionSelect()
{
	if (!activeConfig.Actor.enable)
	{
		return;
	}

	LogFunction();

	IntroduceSessionData();

	g_haywireNeoGenerator = false;
}

export void SceneMissionStart()
{
	if (!activeConfig.Actor.enable)
	{
		return;
	}

	LogFunction();

	IntroduceSessionData();

	g_haywireNeoGenerator =
	(
		(sessionData.mission == 12) &&
		!activeConfig.BossRush.enable
	) ? true : false;
}













namespaceEnd();
