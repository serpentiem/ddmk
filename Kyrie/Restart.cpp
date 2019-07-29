#include "Restart.h"

bool restart = false;

// We only call this function when there is a config change
// involving something that requires a system module.

void EvaluateApplicationRestart()
{
	LogFunction();
	if (System_Actor_enableSpawnExtension)
	{
		// If the system module was turned on by something
		// check if everything that requires it is disabled.
		//if (!Config.Game.Arcade.enable && !Config.Game.Multiplayer.enable)
		if (!Config.Game.Multiplayer.enable)
		{
			goto True;
		}
	}
	else
	{
		// If not, check if something requires it.
		//if (Config.Game.Arcade.enable || Config.Game.Multiplayer.enable)
		if (Config.Game.Multiplayer.enable)
		{
			goto True;
		}
	}
	if (System_Actor_enableCharacterDataConverter)
	{
		if (!Config.Game.Multiplayer.enable)
		{
			goto True;
		}
	}
	else
	{
		if (Config.Game.Multiplayer.enable)
		{
			goto True;
		}
	}
	if (System_Actor_enableCostumeFixes)
	{
		if (!Config.Game.Multiplayer.enable)
		{
			goto True;
		}
	}
	else
	{
		if (Config.Game.Multiplayer.enable)
		{
			goto True;
		}
	}
	if (System_File_enableLoadAssetsExtension)
	{
		if (!Config.Game.Multiplayer.enable)
		{
			goto True;
		}
	}
	else
	{
		if (Config.Game.Multiplayer.enable)
		{
			goto True;
		}
	}
	if (System_Memory_enableReplaceAllocationFunctions)
	{
		if (!Config.System.Memory.replaceAllocationFunctions)
		{
			goto True;
		}
	}
	else
	{
		if (Config.System.Memory.replaceAllocationFunctions)
		{
			goto True;
		}
	}
	False:
	restart = false;
	return;
	True:
	restart = true;
	return;
}
