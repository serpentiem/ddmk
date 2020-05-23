#pragma once
#include "../Core/Core.h"

#include "Vars.h"

#pragma pack(push, 1)

struct CONFIG
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
			bool enableAirStinger = false;
		}
		Rebellion;

		float32 meleeWeaponSwitchTimeout = 1;
		float32 rangedWeaponSwitchTimeout = 1;



	}
	Dante;







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
	}
	System;
	struct
	{
		struct
		{
			bool   enable         = true;
			uint32 mission        = 17;
			uint32 mode           = MODE_NORMAL;
			uint16 room           = 900;
			bool   ignoreRoom     = false;
			uint16 position       = 0;
			bool   ignorePosition = false;
			struct
			{
				uint8 floor = 0;
			}
			BloodyPalace;
			// @Todo: Update!
			uint8  character    = CHAR_DANTE;
			uint8  costume      = 0;
			uint32 style        = STYLE_DANTE_TRICKSTER;
			uint8  equipment[4] =
			{
				WEAPON_DANTE_REBELLION,
				WEAPON_DANTE_CERBERUS,
				WEAPON_DANTE_EBONY_IVORY,
				WEAPON_DANTE_SHOTGUN,
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
			uint8 character [3] = {};
			uint8 costume   [3] = {};
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
			bool enable              = true;
			bool infiniteHitPoints   = false;
			bool infiniteMagicPoints = true;
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

extern CONFIG Config;
extern CONFIG DefaultConfig;
