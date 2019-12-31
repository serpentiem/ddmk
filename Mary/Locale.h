
// @Todo: Put common strings in their own space.

#pragma once
#include "../Core/Core.h"

struct LOCALE
{
	struct
	{
		// @Todo: Change to header.
		const char * label[4] =
		{
			"System",
			"Game",
			"Cosmetics",
			"Tools",
		};
	}
	Main;
	struct
	{
		const char * header = "Speed";
		struct
		{
			const char * header = "Frame Rate";
			const char * hint = "Requires restart. The numbers in green are the recommended values for the target frame rate.";
			const char * target = "Target";
			const char * multiplier = "Multiplier";
		}
		FrameRate;
		struct
		{
			const char * header = "Main";
			const char * base = "Base";
			const char * turbo = "Turbo";
			const char * actor = "Actor";
			const char * enemy = "Enemy";
		}
		Main;
		struct
		{
			const char * header = "Devil";
			struct
			{
				const char * header = "Dante";
				const char * label[6] =
				{
					"Rebellion",
					"Cerberus",
					"Agni & Rudra",
					"Nevan",
					"Beowulf",
					"Sparda",
				};
			}
			Dante;
			struct
			{
				const char * header = "Vergil";
				const char * label[3] =
				{
					"Yamato",
					"Beowulf",
					"Force Edge",
				};
			}
			Vergil;
			struct
			{
				const char * header = "Nero Angelo";
				const char * label[3] =
				{
					"Yamato",
					"Beowulf",
					"Force Edge",
				};
			}
			NeroAngelo;
		}
		Devil;
		struct
		{
			const char * header = "Quicksilver";
			const char * actor = "Actor";
			const char * enemy = "Enemy";
		}
		Quicksilver;
		const char * reset = "Reset";
	}
	Speed;
	struct
	{
		const char * header = "Teleporter";
		const char * current = "Current";
		const char * next = "Next";
		const char * teleport = "Teleport";
		const char * invalidPointer = "Invalid Pointer!";
	}
	Teleporter;
	struct
	{
		struct
		{
			const char * header = "Actor";
			const char * forceSingleActor = "Force Single Actor";
			const char * disableIdleTimer = "Disable Idle Timer";
		}
		Actor;
		struct
		{
			const char * header = "Camera";
			const char * invertX = "Invert X";
		}
		Camera;
		struct
		{
			const char * header = "Event";
			const char * skipIntro = "Skip Intro";
			const char * skipCutscenes = "Skip Cutscenes";
		}
		Event;
		struct
		{
			const char * header = "File";
			const char * preferLocalFiles = "Prefer Local Files";
		}
		File;
		struct
		{
			const char * header = "Input";
			const char * hideMouseCursor = "Hide Mouse Cursor";
		}
		Input;
		struct
		{
			const char * header = "Window";
			const char * forceFocus = "Force Focus";
		}
		Window;
	}
	System;
	struct
	{
		struct
		{
			const char * header = "Arcade";
			const char * description = "Allows you to jump from the main menu to a specific point in the game, bypassing all prompts and setting all variables automagically.";
			const char * enable = "Enable";
			struct
			{
				const char * label = "Mission";
				const char * items[22] =
				{
					"Cutscenes",
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
			}
			Mission;
			struct
			{
				const char * label = "Mode";
				const char * items[6] =
				{
					"Easy",
					"Normal",
					"Hard",
					"Very Hard",
					"Dante Must Die",
					"Heaven or Hell",
				};
			}
			Mode;
			const char * room = "Room";
			const char * ignoreRoom = "Ignore";
			const char * position = "Position";
			const char * ignorePosition = "Ignore";
			struct
			{
				struct
				{
					const char * label = "Floor";
					const char * items[27] =
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
						"Heart of Leviathan",
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
				}
				Floor;
			}
			BloodyPalace;
			struct
			{
				const char * label = "Character";
				const char * items[4] =
				{
					"Dante",
					"Bob",
					"Lady",
					"Vergil",
				};
			}
			Character;
			const char * costume = "Costume";
			struct
			{
				const char * label = "Style";
				const char * items[6] =
				{
					"Swordmaster",
					"Gunslinger",
					"Trickster",
					"Royalguard",
					"Quicksilver",
					"Doppelganger",
				};
			}
			Style;
			struct
			{
				const char * label[4] =
				{
					"Melee Weapon 1",
					"Melee Weapon 2",
					"Ranged Weapon 1",
					"Ranged Weapon 2",
				};
				const char * items[10] =
				{
					"Rebellion",
					"Cerberus",
					"Agni & Rudra",
					"Nevan",
					"Beowulf",
					"Ebony & Ivory",
					"Shotgun",
					"Artemis",
					"Spiral",
					"Kalina Ann",
				};
			}
			Equipment;
			const char * hitPoints = "Hit Points";
			const char * magicPoints = "Magic Points";
			const char * reset = "Reset";
		}
		Arcade;
		struct
		{
			const char * header = "Boss Rush";
			const char * description = "Go directly to the mission's boss battle(s).";
			const char * enable = "Enable";
			struct
			{
				const char * header = "Mission 5";
				const char * skipJester = "Skip Jester";
			}
			Mission5;
			struct
			{
				const char * header = "Mission 12";
				const char * skipJester = "Skip Jester";
				const char * skipGeryonBridgeBattle = "Skip Geryon Bridge Battle";
			}
			Mission12;
			struct
			{
				const char * header = "Mission 17";
				const char * skipJester = "Skip Jester";
			}
			Mission17;
			struct
			{
				const char * header = "Mission 19";
				const char * skipFirstPart = "Skip First Part";
			}
			Mission19;
			const char * reset = "Reset";
		}
		BossRush;
		struct
		{
			const char * header = "Dante";
			const char * enable = "Enable";
			struct
			{
				const char * header = "Rebellion";
				const char * infiniteSwordPierce = "Infinite Sword Pierce";
				const char * unlockQuickDrive = "Unlock Quick Drive";
				const char * unlockQuickDriveDescription = "While in Swordmaster hold the Style button and press the Melee Attack button twice to trigger it.";
			}
			Rebellion;
			struct
			{
				const char * header = "Ebony & Ivory";
				const char * foursomeTime = "Foursome Time";
				const char * foursomeTimeDescription = "Make Twosome Time fire two additional shots.";
				const char * infiniteRainStorm = "Infinite Rain Storm";
			}
			EbonyIvory;
			struct
			{
				const char * header = "Artemis";
				const char * swap = "Swap Normal Shot and Multi Lock";
				const char * instant = "Instant Full Charge";
			}
			Artemis;
			struct
			{
				const char * header = "Air Hike";
				const char * coreAbility = "Core Ability";
				const char * coreAbilityDescription = "If bought once for Rebellion, Air Hike will be accessible by all melee weapons, effectively making it a core ability.";
			}
			AirHike;
			struct
			{
				const char * header = "Crazy Combo";
				const char * levelMultiplier = "Level Multiplier";
			}
			CrazyCombo;
			struct
			{
				const char * header = "Weapon Switch Timeout";
				const char * melee = "Melee";
				const char * ranged = "Ranged";
			}
			WeaponSwitchTimeout;
			const char * reset = "Reset";
		}
		Dante;
		struct
		{
			const char * header = "Doppelganger";
			const char * enable = "Enable";
			struct
			{
				const char * label = "Character";
				const char * items[4] =
				{
					"Dante",
					"Bob",
					"Lady",
					"Vergil",
				};
			}
			Character;
			const char * enableDevilTrigger = "Enable Devil Trigger";
			const char * reset = "Reset";
		}
		Doppelganger;
		struct
		{
			const char * header = "Mobility";
			const char * description = "Control the number of times a move can be used. Different values can be set for human and devil form.";
			const char * enable = "Enable";
			struct
			{
				const char * header = "Dante";
				const char * airHike = "Air Hike";
				const char * dash[3] =
				{
					"Dash Level 1",
					"Dash Level 2",
					"Dash Level 3",
				};
				const char * skyStar = "Sky Star";
				const char * airTrick = "Air Trick";
			}
			Dante;
			struct
			{
				const char * header = "Vergil";
				const char * airTrick = "Air Trick";
				const char * trickUp = "Trick Up";
				const char * trickDown = "Trick Down";
			}
			Vergil;
			const char * reset = "Reset";
		}
		Mobility;
		struct
		{
			const char * header = "Multiplayer";
			const char * description = "The second row sets the costume.";
			const char * enable = "Enable";
			struct
			{
				const char * items[4] =
				{
					"Dante",
					"Bob",
					"Lady",
					"Vergil",
				};
			}
			Character;
			const char * reset = "Reset";
		}
		Multiplayer;
		struct
		{
			const char * header = "Other";
			const char * enable = "Enable";
			const char * orbReach = "Orb Reach";
			struct
			{
				const char * header = "Magic Points Depletion Rate";
				const char * devil = "Devil";
				const char * quicksilver = "Quicksilver";
				const char * doppelganger = "Doppelganger";
			}
			MagicPointsDepletionRate;
			const char * reset = "Reset";
		}
		Other;
		struct
		{
			const char * header = "Reset Motion State";
			const char * enable = "Enable";
			struct
			{
				const char * label = "Button";
				const char * items[16] =
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
					"D-Pad Up",
					"D-Pad Right",
					"D-Pad Down",
					"D-Pad Left",
				};
			}
			Button;
			const char * reset = "Reset";
		}
		ResetMotionState;
		struct
		{
			const char * header = "Style Switcher";
			const char * enable = "Enable";
			const char * noDoubleTap = "No Double Tap";
			const char * reset = "Reset";
		}
		StyleSwitcher;
		struct
		{
			const char * header = "Training";
			const char * enable = "Enable";
			const char * infiniteHitPoints = "Infinite Hit Points";
			const char * infiniteMagicPoints = "Infinite Magic Points";
			const char * disableTimer = "Disable Timer";
			const char * reset = "Reset";
		}
		Training;
		struct
		{
			const char * header = "Vergil";
			const char * enable = "Enable";
			struct
			{
				const char * header = "Force Edge";
				const char * infiniteRoundTrip = "Infinite Round Trip";
			}
			ForceEdge;
			struct
			{
				const char * header = "Summoned Swords";
				const char * chronoSwords = "Chrono Swords";
				const char * chronoSwordsDescription = "Summoned Swords will not fire straight away at the target but continue to levitate as long as Quicksilver is active.";
			}
			SummonedSwords;
			struct
			{
				const char * header = "Weapon Switch Timeout";
				const char * melee = "Melee";
			}
			WeaponSwitchTimeout;
			const char * reset = "Reset";
		}
		Vergil;
		struct
		{
			const char * header = "Weapon Switcher";
			const char * enable = "Enable";
			struct
			{
				const char * label = "Devil";
				const char * items[6] =
				{
					"Rebellion",
					"Cerberus",
					"Agni & Rudra",
					"Nevan",
					"Beowulf",
					"Sparda",
				};
			}
			Devil;
			struct
			{
				const char * label = "Sword";
				const char * items[4] =
				{
					"Auto",
					"Rebellion",
					"Rebellion 2",
					"Force Edge",
				};
			}
			Sword;
			struct
			{
				const char * header = "Melee";
			}
			Melee;
			struct
			{
				const char * header = "Ranged";
			}
			Ranged;
			struct
			{
				const char * items[10] =
				{
					"Rebellion",
					"Cerberus",
					"Agni & Rudra",
					"Nevan",
					"Beowulf",
					"Ebony & Ivory",
					"Shotgun",
					"Artemis",
					"Spiral",
					"Kalina Ann",
				};
			}
			Weapon;
			const char * reset = "Reset";
		}
		WeaponSwitcher;
	}
	Game;
	struct
	{
		struct
		{
			const char * header = "Color";
			struct
			{
				const char * header = "Aura";
				struct
				{
					const char * label = "Dante";
					const char * items[5] =
					{
						"Rebellion",
						"Cerberus",
						"Agni & Rudra",
						"Nevan",
						"Beowulf",
					};
				}
				Dante;
				struct
				{
					const char * label = "Vergil";
					const char * items[1] =
					{
						"Yamato",
					};

				}
				Vergil;
				struct
				{
					const char * label = "Nero Angelo";
					const char * items[1] =
					{
						"Yamato",
					};
				}
				NeroAngelo;
			}
			Aura;
			struct
			{
				const char * header = "Style";
				struct
				{
					const char * label = "Trickster";
					const char * items[1] =
					{
						"Sky Star",
					};
				}
				Trickster;
				struct
				{
					const char * label = "Royalguard";
					const char * items[1] =
					{
						"Ultimate",
					};
				}
				Royalguard;
				struct
				{
					const char * label = "Doppelganger";
					const char * items[1] =
					{
						"Color"
					};
				}
				Doppelganger;
			}
			Style;
			struct
			{
				const char * header = "Air Hike";
				struct
				{
					const char * label = "Dante";
					const char * items[5] =
					{
						"Rebellion",
						"Cerberus",
						"Agni & Rudra",
						"Nevan",
						"Beowulf",
					};
				}
				Dante;
			}
			AirHike;
			const char * reset = "Reset";
		}
		Color;
		struct
		{
			const char * header = "Dante";
			const char * hideBeowulf = "Hide Beowulf";
		}
		Dante;
		struct
		{
			const char * header = "Doppelganger";
			const char * noColor = "No Color";
		}
		Doppelganger;
		struct
		{
			const char * header = "Other";
			const char * noDevilForm = "No Devil Form";
		}
		Other;
		struct
		{
			const char * header = "Vergil";
			const char * hideBeowulf = "Hide Beowulf";
		}
		Vergil;
	}
	Cosmetics;
	struct
	{
		struct
		{
			const char * header = "Overlay";
			const char * enable = "Enable";
			struct
			{
				const char * items[5] =
				{
					"8",
					"16",
					"32",
					"64",
					"128",
				};
			}
			FontSize;
			const char * heapFrame = "Heap Frame";
			const char * focus = "Focus";
			const char * reset = "Reset";
		}
		Overlay;
		struct
		{
			const char * header = "Repair";
			const char * resetEquipment = "Reset Equipment";
			const char * resetRangedWeaponLevels = "Reset Ranged Weapon Levels";
		}
		Repair;
		struct
		{
			const char * header = "Speed";
		}
		Speed;
		struct
		{
			const char * header = "Teleporter";
		}
		Teleporter;
	}
	Tools;
};

extern LOCALE Locale;
