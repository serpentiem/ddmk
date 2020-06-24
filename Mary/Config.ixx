#ifndef __MODULE_CONFIG__
#define __MODULE_CONFIG__

module;
#include "../Core/Core.h"

#include "Vars.h"
export module ModuleName(Config);

#pragma pack(push, 1)
export struct CONFIG
{
	struct
	{
		bool enable = false;
		uint8 playerCount = 1;
		uint8 character[MAX_PLAYER][MAX_ENTITY] =
		{
			// Player 0
			{
				CHAR_DANTE,
				CHAR_DANTE,
			},
			// Player 1
			{
				CHAR_BOB,
				CHAR_BOB,
			},
			// Player 2
			{
				CHAR_LADY,
				CHAR_LADY,
			},
			// Player 3
			{
				CHAR_VERGIL,
				CHAR_VERGIL,
			},
		};
		uint8 costume[MAX_PLAYER][MAX_ENTITY][MAX_CHAR] = {};
		uint8 meleeWeapon[MAX_PLAYER][MAX_ENTITY][MAX_CHAR][MAX_MELEE_WEAPON] =
		{
			// Player 0
			{
				// Entity 0
				{
					// Character 0
					{
						WEAPON_DANTE_REBELLION,
						WEAPON_DANTE_CERBERUS,
						WEAPON_DANTE_AGNI_RUDRA,
						WEAPON_DANTE_NEVAN,
						WEAPON_DANTE_BEOWULF,
					},
					// Character 1
					{
					},
					// Character 2
					{
					},
					// Character 3
					{
						WEAPON_VERGIL_YAMATO,
						WEAPON_VERGIL_BEOWULF,
						WEAPON_VERGIL_FORCE_EDGE,
					},
				},
				// Entity 1
				{
					// Character 0
					{
						WEAPON_DANTE_REBELLION,
						WEAPON_DANTE_CERBERUS,
						WEAPON_DANTE_AGNI_RUDRA,
						WEAPON_DANTE_NEVAN,
						WEAPON_DANTE_BEOWULF,
					},
					// Character 1
					{
					},
					// Character 2
					{
					},
					// Character 3
					{
						WEAPON_VERGIL_YAMATO,
						WEAPON_VERGIL_BEOWULF,
						WEAPON_VERGIL_FORCE_EDGE,
					},
				},
			},
			// Player 1
			{
				// Entity 0
				{
					// Character 0
					{
						WEAPON_DANTE_REBELLION,
						WEAPON_DANTE_CERBERUS,
						WEAPON_DANTE_AGNI_RUDRA,
						WEAPON_DANTE_NEVAN,
						WEAPON_DANTE_BEOWULF,
					},
					// Character 1
					{
					},
					// Character 2
					{
					},
					// Character 3
					{
						WEAPON_VERGIL_YAMATO,
						WEAPON_VERGIL_BEOWULF,
						WEAPON_VERGIL_FORCE_EDGE,
					},
				},
				// Entity 1
				{
					// Character 0
					{
						WEAPON_DANTE_REBELLION,
						WEAPON_DANTE_CERBERUS,
						WEAPON_DANTE_AGNI_RUDRA,
						WEAPON_DANTE_NEVAN,
						WEAPON_DANTE_BEOWULF,
					},
					// Character 1
					{
					},
					// Character 2
					{
					},
					// Character 3
					{
						WEAPON_VERGIL_YAMATO,
						WEAPON_VERGIL_BEOWULF,
						WEAPON_VERGIL_FORCE_EDGE,
					},
				},
			},
			// Player 2
			{
				// Entity 0
				{
					// Character 0
					{
						WEAPON_DANTE_REBELLION,
						WEAPON_DANTE_CERBERUS,
						WEAPON_DANTE_AGNI_RUDRA,
						WEAPON_DANTE_NEVAN,
						WEAPON_DANTE_BEOWULF,
					},
					// Character 1
					{
					},
					// Character 2
					{
					},
					// Character 3
					{
						WEAPON_VERGIL_YAMATO,
						WEAPON_VERGIL_BEOWULF,
						WEAPON_VERGIL_FORCE_EDGE,
					},
				},
				// Entity 1
				{
					// Character 0
					{
						WEAPON_DANTE_REBELLION,
						WEAPON_DANTE_CERBERUS,
						WEAPON_DANTE_AGNI_RUDRA,
						WEAPON_DANTE_NEVAN,
						WEAPON_DANTE_BEOWULF,
					},
					// Character 1
					{
					},
					// Character 2
					{
					},
					// Character 3
					{
						WEAPON_VERGIL_YAMATO,
						WEAPON_VERGIL_BEOWULF,
						WEAPON_VERGIL_FORCE_EDGE,
					},
				},
			},
			// Player 3
			{
				// Entity 0
				{
					// Character 0
					{
						WEAPON_DANTE_REBELLION,
						WEAPON_DANTE_CERBERUS,
						WEAPON_DANTE_AGNI_RUDRA,
						WEAPON_DANTE_NEVAN,
						WEAPON_DANTE_BEOWULF,
					},
					// Character 1
					{
					},
					// Character 2
					{
					},
					// Character 3
					{
						WEAPON_VERGIL_YAMATO,
						WEAPON_VERGIL_BEOWULF,
						WEAPON_VERGIL_FORCE_EDGE,
					},
				},
				// Entity 1
				{
					// Character 0
					{
						WEAPON_DANTE_REBELLION,
						WEAPON_DANTE_CERBERUS,
						WEAPON_DANTE_AGNI_RUDRA,
						WEAPON_DANTE_NEVAN,
						WEAPON_DANTE_BEOWULF,
					},
					// Character 1
					{
					},
					// Character 2
					{
					},
					// Character 3
					{
						WEAPON_VERGIL_YAMATO,
						WEAPON_VERGIL_BEOWULF,
						WEAPON_VERGIL_FORCE_EDGE,
					},
				},
			},
		};
		uint8 meleeWeaponCount[MAX_PLAYER][MAX_ENTITY][MAX_CHAR] =
		{
			// Player 0
			{
				// Entity 0
				{
					5,
					0,
					0,
					3,
				},
				// Entity 1
				{
					5,
					0,
					0,
					3,
				},
			},
			// Player 1
			{
				// Entity 0
				{
					5,
					0,
					0,
					3,
				},
				// Entity 1
				{
					5,
					0,
					0,
					3,
				},
			},
			// Player 2
			{
				// Entity 0
				{
					5,
					0,
					0,
					3,
				},
				// Entity 1
				{
					5,
					0,
					0,
					3,
				},
			},
			// Player 3
			{
				// Entity 0
				{
					5,
					0,
					0,
					3,
				},
				// Entity 1
				{
					5,
					0,
					0,
					3,
				},
			},
		};
		uint8 rangedWeapon[MAX_PLAYER][MAX_ENTITY][MAX_CHAR][MAX_RANGED_WEAPON] =
		{
			// Player 0
			{
				// Entity 0
				{
					// Character 0
					{
						WEAPON_DANTE_EBONY_IVORY,
						WEAPON_DANTE_SHOTGUN,
						WEAPON_DANTE_ARTEMIS,
						WEAPON_DANTE_SPIRAL,
						WEAPON_DANTE_KALINA_ANN,
					},
					// Character 1
					{
					},
					// Character 2
					{
					},
					// Character 3
					{
					},
				},
				// Entity 1
				{
					// Character 0
					{
						WEAPON_DANTE_EBONY_IVORY,
						WEAPON_DANTE_SHOTGUN,
						WEAPON_DANTE_ARTEMIS,
						WEAPON_DANTE_SPIRAL,
						WEAPON_DANTE_KALINA_ANN,
					},
					// Character 1
					{
					},
					// Character 2
					{
					},
					// Character 3
					{
					},
				},
			},
			// Player 1
			{
				// Entity 0
				{
					// Character 0
					{
						WEAPON_DANTE_EBONY_IVORY,
						WEAPON_DANTE_SHOTGUN,
						WEAPON_DANTE_ARTEMIS,
						WEAPON_DANTE_SPIRAL,
						WEAPON_DANTE_KALINA_ANN,
					},
					// Character 1
					{
					},
					// Character 2
					{
					},
					// Character 3
					{
					},
				},
				// Entity 1
				{
					// Character 0
					{
						WEAPON_DANTE_EBONY_IVORY,
						WEAPON_DANTE_SHOTGUN,
						WEAPON_DANTE_ARTEMIS,
						WEAPON_DANTE_SPIRAL,
						WEAPON_DANTE_KALINA_ANN,
					},
					// Character 1
					{
					},
					// Character 2
					{
					},
					// Character 3
					{
					},
				},
			},
			// Player 2
			{
				// Entity 0
				{
					// Character 0
					{
						WEAPON_DANTE_EBONY_IVORY,
						WEAPON_DANTE_SHOTGUN,
						WEAPON_DANTE_ARTEMIS,
						WEAPON_DANTE_SPIRAL,
						WEAPON_DANTE_KALINA_ANN,
					},
					// Character 1
					{
					},
					// Character 2
					{
					},
					// Character 3
					{
					},
				},
				// Entity 1
				{
					// Character 0
					{
						WEAPON_DANTE_EBONY_IVORY,
						WEAPON_DANTE_SHOTGUN,
						WEAPON_DANTE_ARTEMIS,
						WEAPON_DANTE_SPIRAL,
						WEAPON_DANTE_KALINA_ANN,
					},
					// Character 1
					{
					},
					// Character 2
					{
					},
					// Character 3
					{
					},
				},
			},
			// Player 3
			{
				// Entity 0
				{
					// Character 0
					{
						WEAPON_DANTE_EBONY_IVORY,
						WEAPON_DANTE_SHOTGUN,
						WEAPON_DANTE_ARTEMIS,
						WEAPON_DANTE_SPIRAL,
						WEAPON_DANTE_KALINA_ANN,
					},
					// Character 1
					{
					},
					// Character 2
					{
					},
					// Character 3
					{
					},
				},
				// Entity 1
				{
					// Character 0
					{
						WEAPON_DANTE_EBONY_IVORY,
						WEAPON_DANTE_SHOTGUN,
						WEAPON_DANTE_ARTEMIS,
						WEAPON_DANTE_SPIRAL,
						WEAPON_DANTE_KALINA_ANN,
					},
					// Character 1
					{
					},
					// Character 2
					{
					},
					// Character 3
					{
					},
				},
			},
		};
		uint8 rangedWeaponCount[MAX_PLAYER][MAX_ENTITY][MAX_CHAR] =
		{
			// Player 0
			{
				// Entity 0
				{
					5,
				},
				// Entity 1
				{
					5,
				},
			},
			// Player 1
			{
				// Entity 0
				{
					5,
				},
				// Entity 1
				{
					5,
				},
			},
			// Player 2
			{
				// Entity 0
				{
					5,
				},
				// Entity 1
				{
					5,
				},
			},
			// Player 3
			{
				// Entity 0
				{
					5,
				},
				// Entity 1
				{
					5,
				},
			},
		};
	}
	Actor;



	struct
	{
		bool   enable         = true;
		uint32 mission        = 17;
		uint32 mode           = MODE_NORMAL;
		uint32 room           = 900;
		uint32 position       = 0;
		bool   ignoreRoom     = false;
		bool   ignorePosition = false;
		uint8  floor          = 0;
		uint8  character      = CHAR_DANTE;
		uint8  costume        = 0;
		uint32 style          = STYLE_DANTE_TRICKSTER;
		// @Todo: Should be weapons.
		uint8  weapon[MAX_CHAR][5] =
		{
			// Dante
			{
				WEAPON_DANTE_REBELLION,
				WEAPON_DANTE_CERBERUS,
				WEAPON_DANTE_EBONY_IVORY,
				WEAPON_DANTE_SHOTGUN,
				WEAPON_VOID,
			},
			// Bob
			{
				WEAPON_BOB_YAMATO,
				WEAPON_VOID,
				WEAPON_VOID,
				WEAPON_VOID,
				WEAPON_VOID,
			},
			// Lady
			{
				WEAPON_VOID,
				WEAPON_VOID,
				9,
				WEAPON_VOID,
				11,
			},
			// Vergil
			{
				WEAPON_VERGIL_YAMATO,
				WEAPON_VERGIL_BEOWULF,
				WEAPON_VERGIL_FORCE_EDGE,
				WEAPON_VOID,
				WEAPON_VOID,
			},
		};
		float32 hitPoints   = 6000;
		float32 magicPoints = 3000;
	}
	Arcade;









	struct
	{
		float32 height      = 140;
		float32 tilt        = 0.25f;
		float32 zoom        = 460;
		float32 zoomLockOn  = 400;
		bool    applyConfig = false;
		uint32  rate        = 1000;
	}
	Camera;

















	struct
	{

		bool enable = false;



		struct
		{
			bool coreAbility = false;
			uint8 count[2] = { 1, 1 };
		}
		AirHike;
		struct
		{
			uint8 dashCount    [2] = { 3, 3 };
			uint8 skyStarCount [2] = { 1, 1 };
			uint8 airTrickCount[2] = { 1, 1 };
		}
		Trickster;
		struct
		{
			bool infiniteSwordPierce = false;
			float32 stingerDuration   [2] = { 16 , 16  };
			float32 stingerRange      [2] = { 560, 560 };
			float32 airStingerDuration[2] = { 16 , 16  };
			float32 airStingerRange   [2] = { 560, 560 };
		}
		Rebellion;
		struct
		{
			float32 revolverHeight[2] = { 6.5, 6.5 };
		}
		Cerberus;
		struct
		{
			float32 jetStreamDuration[2] = {};
			float32 jetStreamRange   [2] = {};
		}
		AgniAndRudra;
		struct
		{
			float32 reverbShockDuration[2] = { 12 , 12  };
			float32 reverbShockRange   [2] = { 300, 300 };
		}
		Nevan;
		struct
		{
			bool hide = false;
			float32 straightDuration   [2] = { 7   , 7    };
			float32 straightRange      [2] = { 350 , 350  };
			float32 airStraightDuration[2] = { 7   , 7    };
			float32 airStraightRange   [2] = { 350 , 350  };
			float32 risingDragonHeight [2] = { 37.5, 37.5 };
		}
		Beowulf;
		struct
		{
			bool foursomeTime      = false;
			bool infiniteRainStorm = false;
		}
		EbonyIvory;
		struct
		{
			float32 gunStingerDuration   [2] = { 8  , 8   };
			float32 gunStingerRange      [2] = { 200, 200 };
			float32 airGunStingerDuration[2] = { 8  , 8   };
			float32 airGunStingerRange   [2] = { 200, 200 };
		}
		Shotgun;
		struct
		{
			bool swapNormalShotAndMultiLock = false;
			bool instantFullCharge       = false;
		}
		Artemis;
		uint8 crazyComboLevelMultiplier = 6;
		float32 weaponSwitchTimeout = 1;
		bool summonedSwords = false;
	}
	Dante;

	// EbonyAndIvory
	// swapNormalShotAndMultiLock


	struct
	{
		bool skipIntro     = true;
		bool skipCutscenes = true;
	}
	Event;

	struct
	{
		bool preferLocalFiles = true;
	}
	File;


	struct
	{
		uint32 frameRate = 60;
		uint8  vSync     = 0;
	}
	Graphics;

	struct
	{
		bool hideMouseCursor = true;
	}
	Input;
	struct
	{
		bool forceFocus = true;
	}
	Window;








	struct
	{
		struct
		{
			float32 base  = 1;
			float32 turbo = 1.2f;
			float32 actor = 1;
			float32 enemy = 1;
		}
		Main;
		struct
		{
			float32 dante[6] =
			{
				1.1f,
				1.2f,
				1.05f,
				1.1f,
				1.05f,
				1.1f,
			};
			float32 vergil[3] =
			{
				1.2f,
				1.2f,
				1.2f,
			};
			float32 neroAngelo[3] =
			{
				1,
				1,
				1,
			};
		}
		Devil;
		struct
		{
			float32 actor = 1.05f;
			float32 enemy = 0.33f;
		}
		Quicksilver;
	}
	Speed;






	struct
	{
		bool enable              = false;
		bool infiniteHitPoints   = false;
		bool infiniteMagicPoints = false;
		bool disableTimer        = false;
	}
	Training;










	struct
	{
		struct
		{
			uint8 airTrickCount [2] = { 1, 1 };
			uint8 trickUpCount  [2] = { 1, 1 };
			uint8 trickDownCount[2] = { 1, 1 };
		}
		DarkSlayer;
		struct
		{
			float32 rapidSlashDuration    [2] = { 5  , 5   };
			float32 rapidSlashRange       [2] = { 330, 330 };
			float32 judgementCutRange     [2] = { 500, 500 };
			float32 judgementCutExtraCount[2] = { 2  , 2   };
		}
		Yamato;
		struct
		{
			float32 risingSunHeight[2] = { 504, 504 };
		}
		Beowulf;
		struct
		{
			float32 stingerDuration   [2] = { 16 , 16  };
			float32 stingerRange      [2] = { 560, 560 };
			float32 airStingerDuration[2] = { 16 , 16  };
			float32 airStingerRange   [2] = { 560, 560 };
		}
		ForceEdge;
	}
	Vergil;




























	struct
	{
		struct
		{
			bool forceSingleActor = false;
			bool disableIdleTimer = false;
		}
		Actor;
		struct
		{
			bool invertX = false;
		}
		Camera;
	}
	System;
	struct
	{
		struct
		{
			bool enable = false;
			struct
			{
				bool skipJester = false;
			}
			Mission5;
			struct
			{
				bool skipJester = false;
				bool skipGeryonBridgeBattle = false;
			}
			Mission12;
			struct
			{
				bool skipJester = false;
			}
			Mission17;
			struct
			{
				bool skipFirstPart = false;
			}
			Mission19;
		}
		BossRush;









		struct
		{
			bool  enable             = false;
			uint8 character          = CHAR_DANTE;
			bool  enableDevilTrigger = false;
		}
		Doppelganger;
		//struct
		//{
		//	bool enable = false;
		//	struct MOBILITY
		//	{
		//		struct
		//		{
		//			uint8 airHike = 1;
		//			uint8 dash[3] =
		//			{
		//				1,
		//				2,
		//				3,
		//			};
		//			uint8 skyStar  = 1;
		//			uint8 airTrick = 1;
		//		}
		//		Dante;
		//		struct
		//		{
		//			uint8 airTrick  = 1;
		//			uint8 trickUp   = 1;
		//			uint8 trickDown = 1;
		//		}
		//		Vergil;
		//	};
		//	MOBILITY Human;
		//	MOBILITY Devil;
		//}
		//Mobility;
		//struct
		//{
		//	bool  enable                      = false;
		//	uint8 actorCount                  = 1;
		//	uint8 character [3] = {};
		//	uint8 costume   [3] = {};
		//}
		//Multiplayer;
		struct
		{
			bool  enable   = false;
			float32 orbReach = 300;
			struct
			{
				float32 devil        = 11;
				float32 quicksilver  = 16.5f;
				float32 doppelganger = 16.5f;
			}
			MagicPointsDepletionRate;
		}
		Other;
		struct
		{
			bool   enable = false;
			byte16 button = GAMEPAD_UP;
		}
		ResetMotionState;
		struct
		{
			bool enable               = false;
			bool noDoubleTap          = false;
		}
		StyleSwitcher;
		struct
		{
			bool enable = false;
			struct
			{
				bool infiniteRoundTrip = false;
			}
			ForceEdge;
			struct
			{
				bool chronoSwords = false;
			}
			SummonedSwords;
			struct
			{
				float32 melee = 8;
			}
			WeaponSwitchTimeout;
		}
		Vergil;
		struct
		{
			bool  enable = false;
			uint8 devil  = DEVIL_DANTE_REBELLION;
			uint8 sword  = 0;
			struct
			{
				uint8 count     = 5;
				uint8 weapon[5] =
				{
					WEAPON_DANTE_REBELLION,
					WEAPON_DANTE_CERBERUS,
					WEAPON_DANTE_AGNI_RUDRA,
					WEAPON_DANTE_NEVAN,
					WEAPON_DANTE_BEOWULF,
				};
			}
			Melee;
			struct
			{
				uint8 count     = 5;
				uint8 weapon[5] =
				{
					WEAPON_DANTE_EBONY_IVORY,
					WEAPON_DANTE_SHOTGUN,
					WEAPON_DANTE_ARTEMIS,
					WEAPON_DANTE_SPIRAL,
					WEAPON_DANTE_KALINA_ANN,
				};
			}
			Ranged;
		}
		WeaponSwitcher;
	}
	Game;
	struct
	{
		struct
		{
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
				float32 vergil[1][4] =
				{
					{ 32, 64, 128, 200 },
				};
				float32 neroAngelo[1][4] =
				{
					{ 64, 0, 255, 200 },
				};
			}
			Aura;
			struct
			{
				float32 trickster[1][4] =
				{
					{ 255, 0, 0, 200 },
				};
				float32 royalguard[1][4] =
				{
					{ 143, 112, 48, 200 },
				};
				float32 doppelganger[1][4] =
				{
					{ 16, 16, 16, 48 },
				};
			}
			Style;
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
			}
			AirHike;
		}
		Color;
		struct
		{
			struct
			{
				bool hideModel = false;
			}
			Beowulf;
		}
		Dante;
		struct
		{
			bool noColor = false;
		}
		Doppelganger;
		struct
		{
			bool noDevilForm = false;
		}
		Other;
		struct
		{
			struct
			{
				bool hideModel = false;
			}
			Beowulf;
		}
		Vergil;
	}
	Cosmetics;
	struct
	{
		struct
		{
			bool    enable        = false;
			float32 x             = 0;
			float32 y             = 0;
			uint8   fontSizeIndex = 2;
			float32 color[4]      = { 1, 0, 0, 1 };
			bool    focus         = true;
			bool    memory        = true;
		}
		Overlay;
	}
	Tools;
};
#pragma pack(pop)

export CONFIG Config;
export CONFIG DefaultConfig;

#endif
