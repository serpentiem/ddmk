#pragma once
#include "../Core/Core.h"

struct LOCALE
{
	struct
	{
		const char * label[5] =
		{
			"Game",
			"Cosmetics",
			"System",
			"Tools",
			"Debug",
		};
	}
	Main;
	struct
	{
		const char * description =
			"Game\n"
			"\n"
			"Arcade\n"
			"\n"
			"Allows you to jump from the main menu to a specific point in the game,\n"
			"bypassing all prompts and setting all variables automagically.\n"
			"\n"
			"Boss Rush\n"
			"\n"
			"Go directly to a mission's boss battle.\n"
			"\n"
			"Dante\n"
			"\n"
			"Rebellion\n"
			"\n"
			"Infinite Sword Pierce\n"
			"\n"
			"Self-explanatory.\n"
			"\n"
			"Unlock Quick Drive\n"
			"\n"
			"Requires pl000_00_3.pac from the Demo to work.\n"
			"Extract it with AFSExplorer and save it as demo_pl000_00_3.pac\n"
			"in data\\dmc3\\GData.afs of your Devil May Cry HD Collection root directory.\n"
			"\n"
			"While in Swordmaster hold the Style button and press the Melee Attack button twice to trigger it.\n"
			"\n"
			"Ebony & Ivory\n"
			"\n"
			"Foursome Time\n"
			"\n"
			"Make Twosome Time fire two additional shots.\n"
			"\n"
			"Infinite Rain Storm\n"
			"\n"
			"Self-explanatory.\n"
			"\n"
			"Artemis\n"
			"\n"
			"Swap Normal Shot and Multi Lock\n"
			"\n"
			"Self-explanatory.\n"
			"\n"
			"Instant Full Charge\n"
			"\n"
			"Self-explanatory.\n"
			"\n"
			"Air Hike\n"
			"\n"
			"Core Ability\n"
			"\n"
			"If bought once for Rebellion, Air Hike will be accessible by\n"
			"all melee weapons, effectively making it a core ability.\n"
			"\n"
			"Crazy Combo\n"
			"\n"
			"Level Multiplier\n"
			"\n"
			"Self-explanatory.\n"
			"\n"
			"Weapon Switch Timeout\n"
			"\n"
			"Self-explanatory.\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"\n";
		struct
		{
			const char * header = "Arcade";
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
			}
			Rebellion;
			struct
			{
				const char * header = "Ebony & Ivory";
				const char * foursomeTime = "Foursome Time";
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
			const char * useEXVersion = "Use EX Version";
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
			const char * reset = "Reset";
		}
		Doppelganger;
		struct
		{
			const char * header = "Mobility";
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
			const char * spawnDelay = "Spawn Delay";
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
			const char * updateRate = "Update Rate";
			const char * reset = "Reset";
		}
		ResetMotionState;
		struct
		{
			const char * header = "Speed";
			const char * enable = "Enable";
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
				const char * header = "Dante";
				const char * rebellion = "Rebellion";
				const char * cerberus = "Cerberus";
				const char * agniRudra = "Agni & Rudra";
				const char * nevan = "Nevan";
				const char * beowulf = "Beowulf";
				const char * sparda = "Sparda";
			}
			Dante;
			struct
			{
				const char * header = "Vergil";
				const char * yamato = "Yamato";
				const char * beowulf = "Beowulf";
				const char * forceEdge = "Force Edge";
			}
			Vergil;
			struct
			{
				const char * header = "Nero Angelo";
				const char * yamato = "Yamato";
				const char * beowulf = "Beowulf";
				const char * forceEdge = "Force Edge";
			}
			NeroAngelo;
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
			const char * header = "Style Switcher";
			const char * enable = "Enable";
			const char * noDoubleTap = "No Double Tap";
			struct
			{
				const char * items[17] =
				{
					"Void",
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
			struct
			{
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
			const char * updateRate = "Update Rate";
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
				const char * timeout = "Timeout";
			}
			Melee;
			struct
			{
				const char * header = "Ranged";
				const char * timeout = "Timeout";
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
			const char * enable = "Enable";
			struct
			{
				const char * header = "Dante";
				struct
				{
					const char * label = "Aura";
					const char * items[5] =
					{
						"Rebellion",
						"Cerberus",
						"Agni & Rudra",
						"Nevan",
						"Beowulf",
					};
				}
				Aura;
				struct
				{
					const char * label = "Air Hike";
					const char * items[5] =
					{
						"Rebellion",
						"Cerberus",
						"Agni & Rudra",
						"Nevan",
						"Beowulf",
					};
				}
				AirHike;
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
			}
			Dante;
			struct
			{
				const char * header = "Vergil";
				struct
				{
					const char * label = "Aura";
					const char * items[1] =
					{
						"",
					};
				}
				Aura;
			}
			Vergil;
			struct
			{
				const char * header = "Nero Angelo";
				struct
				{
					const char * label = "Aura";
					const char * items[1] =
					{
						"",
					};
				}
				Aura;
			}
			NeroAngelo;
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
		struct
		{
			const char * header = "Weapon";
			const char * instantModelUpdate = "Instant Model Update";
		}
		Weapon;
	}
	Cosmetics;
	struct
	{
		struct
		{
			const char * header = "Cache";
			const char * enable = "Enable";
		}
		Cache;
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
			struct
			{
				const char * header = "Mouse";
				const char * hideCursor = "Hide Cursor";
				const char * updateRate = "Update Rate";
			}
			Mouse;
			const char * reset = "Reset";
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
		const char * teleporter = "Teleporter";
	}
	Tools;
	struct
	{
		struct
		{
			const char * header = "Overlay";
			const char * show = "Show";
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
			const char * cacheStats = "Cache Stats";
			const char * resetPosition = "Reset Position";
		}
		Overlay;
	}
	GUI;
	const char * restartRequired = "Restart required!";
};

extern LOCALE Locale;
