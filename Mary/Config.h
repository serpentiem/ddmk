#pragma once
#include "../Core/Core.h"

#include "Vars.h"

#pragma pack(push, 1)
struct CONFIG
{
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
		struct
		{
			bool skipIntro     = false;
			bool skipCutscenes = false;
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
	}
	System;
	struct
	{
		struct
		{
			bool   enable         = false;
			uint32 mission        = 1;
			uint32 mode           = MODE_NORMAL;
			uint16 room           = 0;
			bool   ignoreRoom     = false;
			uint16 position       = 0;
			bool   ignorePosition = false;
			struct
			{
				uint8 floor = 0;
			}
			BloodyPalace;
			uint8  character    = CHAR_DANTE;
			uint8  costume      = 0;
			uint32 style        = STYLE_TRICKSTER;
			uint8  equipment[4] =
			{
				WEAPON_REBELLION,
				WEAPON_CERBERUS,
				WEAPON_EBONY_IVORY,
				WEAPON_SHOTGUN,
			};
			float32 hitPoints   = 6000;
			float32 magicPoints = 3000;
		}
		Arcade;
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
			bool enable = false;
			struct
			{
				bool infiniteSwordPierce = false;
				bool unlockQuickDrive    = false;
			}
			Rebellion;
			struct
			{
				bool foursomeTime      = false;
				bool infiniteRainStorm = false;
			}
			EbonyIvory;
			struct
			{
				bool swap    = false;
				bool instant = false;
			}
			Artemis;
			struct
			{
				bool coreAbility = false;
			}
			AirHike;
			struct
			{
				uint8 levelMultiplier = 6;
			}
			CrazyCombo;
			struct
			{
				float32 melee  = 12;
				float32 ranged = 12;
			}
			WeaponSwitchTimeout;
		}
		Dante;
		struct
		{
			bool  enable             = false;
			uint8 character          = CHAR_DANTE;
			bool  enableDevilTrigger = false;
		}
		Doppelganger;
		struct
		{
			bool enable = false;
			struct MOBILITY
			{
				struct
				{
					uint8 airHike = 1;
					uint8 dash[3] =
					{
						1,
						2,
						3,
					};
					uint8 skyStar  = 1;
					uint8 airTrick = 1;
				}
				Dante;
				struct
				{
					uint8 airTrick  = 1;
					uint8 trickUp   = 1;
					uint8 trickDown = 1;
				}
				Vergil;
			};
			MOBILITY Human;
			MOBILITY Devil;
		}
		Mobility;
		struct
		{
			bool  enable                      = false;
			uint8 actorCount                  = 1;
			uint8 character [(MAX_ACTOR - 1)] = {};
			uint8 costume   [(MAX_ACTOR - 1)] = {};
		}
		Multiplayer;
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
			bool enable              = false;
			bool infiniteHitPoints   = false;
			bool infiniteMagicPoints = false;
			bool disableTimer        = false;
		}
		Training;
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
					WEAPON_REBELLION,
					WEAPON_CERBERUS,
					WEAPON_AGNI_RUDRA,
					WEAPON_NEVAN,
					WEAPON_BEOWULF,
				};
			}
			Melee;
			struct
			{
				uint8 count     = 5;
				uint8 weapon[5] =
				{
					WEAPON_EBONY_IVORY,
					WEAPON_SHOTGUN,
					WEAPON_ARTEMIS,
					WEAPON_SPIRAL,
					WEAPON_KALINA_ANN,
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




			MODEL_HELPER_FILE_HELPER modelHelperFileHelper[MAX_COSTUME_DANTE][MODEL_HELPER_MAX_PART] =
			{
				// Default
				{
					// Base
					{
						{ pl000, 1 },
						{ pl000, 0 },
						{ pl000, 8 },
						{ 0    , 0 },
					},
					// Coat
					{
						{ pl000, 12 },
						{ pl000, 0  },
						{ pl000, 14 },
						{ pl000, 13 },
					},
				},
				// Default No Coat
				{
					// Base
					{
						{ pl011, 1 },
						{ pl011, 0 },
						{ pl011, 8 },
						{ 0    , 0 },
					},
					// Amulet
					{
						{ pl011, 12 },
						{ pl011, 0  },
						{ 0    , 0  },
						{ pl011, 13 },
					},
				},
				// Default Torn
				{
					// Base
					{
						{ pl013, 1 },
						{ pl013, 0 },
						{ pl013, 8 },
						{ 0    , 0 },
					},
					// Coat
					{
						{ pl013, 12 },
						{ pl013, 0  },
						{ pl013, 14 },
						{ pl013, 13 },
					},
				},
				// DMC1
				{
					// Base
					{
						{ pl015, 1 },
						{ pl015, 0 },
						{ pl015, 8 },
						{ 0    , 0 },
					},
					// Coat
					{
						{ pl015, 12 },
						{ pl015, 0  },
						{ pl015, 14 },
						{ pl015, 13 },
					},
				},
				// DMC1 No Coat
				{
					// Base
					{
						{ pl016, 1 },
						{ pl016, 0 },
						{ pl016, 8 },
						{ 0    , 0 },
					},
					// Amulet
					{
						{ pl016, 12 },
						{ pl016, 0  },
						{ 0    , 0  },
						{ pl016, 13 },
					},
				},
				// Sparda
				{
					// Base
					{
						{ pl018, 1 },
						{ pl018, 0 },
						{ pl018, 8 },
						{ 0    , 0 },
					},
					// Coat
					{
						{ pl018, 12 },
						{ pl018, 0  },
						{ pl018, 14 },
						{ pl018, 13 },
					},
				},
				// Default Torn Infinite Magic Points
				{
					// Base
					{
						{ pl013, 1 },
						{ pl013, 0 },
						{ pl013, 8 },
						{ 0    , 0 },
					},
					// Coat
					{
						{ pl013, 12 },
						{ pl013, 0  },
						{ pl013, 14 },
						{ pl013, 13 },
					},
				},
				// Sparda Infinite Magic Points
				{
					// Base
					{
						{ pl018, 1 },
						{ pl018, 0 },
						{ pl018, 8 },
						{ 0    , 0 },
					},
					// Coat
					{
						{ pl018, 12 },
						{ pl018, 0  },
						{ pl018, 14 },
						{ pl018, 13 },
					},
				},
			};
			DEVIL_MODEL_HELPER_FILE_HELPER devilModelHelperFileHelper[MAX_DEVIL_DANTE][DEVIL_MODEL_HELPER_MAX_PART] =
			{
				// Rebellion
				{
					// Base
					{
						{ pl005, 1 },
						{ pl005, 0 },
						{ pl005, 6 },
						{ 0    , 0 },
					},
					// Coat
					{
						{ pl005, 2 },
						{ pl005, 0 },
						{ pl005, 7 },
						{ pl005, 3 },
					},
					// Wings
					{
						{ pl005, 4 },
						{ pl005, 0 },
						{ pl005, 8 },
						{ pl005, 5 },
					},
				},
				// Cerberus
				{
					// Base
					{
						{ pl006, 1 },
						{ pl006, 0 },
						{ pl006, 4 },
						{ 0    , 0 },
					},
					// Coat
					{
						{ 0, 0 },
						{ 0, 0 },
						{ 0, 0 },
						{ 0, 0 },
					},
					// Wings
					{
						{ pl006, 2 },
						{ pl006, 0 },
						{ pl006, 5 },
						{ pl006, 3 },
					},
				},
				// Agni Rudra
				{
					// Base
					{
						{ pl007, 1 },
						{ pl007, 0 },
						{ pl007, 2 },
						{ 0    , 0 },
					},
					// Coat
					{
						{ 0, 0 },
						{ 0, 0 },
						{ 0, 0 },
						{ 0, 0 },
					},
					// Wings
					{
						{ 0, 0 },
						{ 0, 0 },
						{ 0, 0 },
						{ 0, 0 },
					},
				},
				// Nevan
				{
					// Base
					{
						{ pl008, 1 },
						{ pl008, 0 },
						{ pl008, 6 },
						{ 0    , 0 },
					},
					// Coat
					{
						{ pl008, 2 },
						{ pl008, 0 },
						{ pl008, 7 },
						{ pl008, 3 },
					},
					// Wings
					{
						{ pl008, 4 },
						{ pl008, 0 },
						{ pl008, 8 },
						{ pl008, 5 },
					},
				},
				// Beowulf
				{
					// Base
					{
						{ pl009, 1 },
						{ pl009, 0 },
						{ pl009, 4 },
						{ 0    , 0 },
					},
					// Coat
					{
						{ 0, 0 },
						{ 0, 0 },
						{ 0, 0 },
						{ 0, 0 },
					},
					// Wings
					{
						{ pl009, 2 },
						{ pl009, 0 },
						{ pl009, 5 },
						{ pl009, 3 },
					},
				},
				// Sparda
				{
					// Base
					{
						{ pl017, 1 },
						{ pl017, 0 },
						{ pl017, 4 },
						{ 0    , 0 },
					},
					// Coat
					{
						{ 0, 0 },
						{ 0, 0 },
						{ 0, 0 },
						{ 0, 0 },
					},
					// Wings
					{
						{ pl017, 2 },
						{ pl017, 0 },
						{ pl017, 5 },
						{ pl017, 3 },
					},
				},
			};
		}
		Dante;
		struct
		{
			bool noColor = false;
		}
		Doppelganger;
		//struct
		//{
		//	MODEL_FILE_DATA DanteDefault;
		//	MODEL_FILE_DATA DanteDefaultNoCoat;
		//	MODEL_FILE_DATA DanteDefaultTorn;
		//	MODEL_FILE_DATA DanteDMC1;
		//	MODEL_FILE_DATA DanteDMC1NoCoat;
		//	MODEL_FILE_DATA DanteSparda;
		//	MODEL_FILE_DATA VergilDefault;
		//	MODEL_FILE_DATA VergilDefaultNoCoat;
		//	MODEL_FILE_DATA VergilSparda;
		//}
		//ModelHelper;



		//MODEL_FILE_DATA modelHelperDante [MAX_COSTUME_DANTE ];
		//MODEL_FILE_DATA modelHelperVergil[MAX_COSTUME_VERGIL];
		//
		//MODEL_FILE_DATA devilModelHelperDante [MAX_DEVIL_DANTE ];
		//MODEL_FILE_DATA devilModelHelperVergil[MAX_DEVIL_VERGIL];






		//struct
		//{
		//	MODEL_FILE_DATA DanteRebellion;
		//	MODEL_FILE_DATA DanteCerberus;
		//	MODEL_FILE_DATA DanteAgniRudra;
		//	MODEL_FILE_DATA DanteNevan;
		//	MODEL_FILE_DATA DanteBeowulf;
		//	MODEL_FILE_DATA DanteSparda;
		//	MODEL_FILE_DATA VergilYamato;
		//	MODEL_FILE_DATA VergilBeowulf;
		//	MODEL_FILE_DATA VergilNeroAngelo;
		//}
		//DevilModelHelper;
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

extern CONFIG Config;
extern CONFIG DefaultConfig;
