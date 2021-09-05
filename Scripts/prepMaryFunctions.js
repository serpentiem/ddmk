// @Remove
helpers.push(["IntroducePlayerActorData", (args) =>
{
	let funcName = this.name;

	let lineIndex = GetLineIndex();

	let argCount = args.length;

	if (argCount < 3)
	{
		console.log(funcName);
		console.log(lineIndex + ": Too few arguments.");

		console.log("argCount " + argCount);
		console.log(args);

		return true;
	}
	else if (argCount > 4)
	{
		console.log(funcName);
		console.log(lineIndex + ": Too many arguments.");

		console.log("argCount " + argCount);
		console.log(args);

		return true;
	}



	// IntroducePlayerActorData(actorBaseAddrName, actorDataName, return);
	// IntroducePlayerActorData(actorBaseAddrName, actorBaseAddrSource, actorDataName, return);



	let actorBaseAddrName   = "";
	let actorBaseAddrSource = "";
	let actorDataName       = "";
	let returnal            = "";

	if (argCount == 3)
	{
		actorBaseAddrName = args[0];
		actorDataName     = args[1];
		returnal          = args[2];
	}
	else if (argCount == 4)
	{
		actorBaseAddrName   = args[0];
		actorBaseAddrSource = args[1];
		actorDataName       = args[2];
		returnal            = args[3];

		c += Tabs() + "auto " + actorBaseAddrName + " = " + actorBaseAddrSource + ";" + NEW_LINE;
	}

	c += Tabs() + "if (!" + actorBaseAddrName + ")" + NEW_LINE;

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();

	c += Tabs() + "auto & " + actorDataName + " = *reinterpret_cast<PlayerActorData *>(" + actorBaseAddrName + ");";

	return false;
}]);

helpers.push(["IntroduceMainActorData", (args) =>
{
	let funcName = this.name;

	let lineIndex = GetLineIndex();

	let argCount = args.length;

	if (argCount < 2)
	{
		console.log(funcName);
		console.log(lineIndex + ": Too few arguments.");

		console.log("argCount " + argCount);
		console.log(args);

		return true;
	}
	else if (argCount > 3)
	{
		console.log(funcName);
		console.log(lineIndex + ": Too many arguments.");

		console.log("argCount " + argCount);
		console.log(args);

		return true;
	}





	// IntroduceMainActorData(actorDataName, return);
	// IntroduceMainActorData(actorBaseAddrName, actorDataName, return);






	let poolName = "pool_" + lineIndex;

	let actorBaseAddrName = "";
	let actorDataName     = "";
	let returnal          = "";

	if (argCount == 2)
	{
		actorBaseAddrName = poolName + "[3]";
		actorDataName     = args[0];
		returnal          = args[1];
	}
	else if (argCount == 3)
	{
		actorBaseAddrName = args[0];
		actorDataName     = args[1];
		returnal          = args[2];
	}












	





	c += Tabs() + "auto " + poolName + " = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);" + NEW_LINE;




	c += Tabs() + "if" + NEW_LINE;

	ScopeStart("(");

	c += Tabs() + "!" + poolName + " ||" + NEW_LINE;
	c += Tabs() + "!" + poolName + "[3]" + NEW_LINE;

	ScopeEnd(")");

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();

	//c += NEW_LINE;



	if (argCount == 3)
	{
		c += Tabs() + "auto " + actorBaseAddrName + " = " + poolName + "[3];" + NEW_LINE;
	}






	c += Tabs() + "auto & " + actorDataName + " = *reinterpret_cast<PlayerActorData *>(" + actorBaseAddrName + ");";



	return false;
}]);







helpers.push(["IntroduceData", (args) =>
{
	let funcName = this.name;

	let lineIndex = GetLineIndex();

	let argCount = args.length;

	if (argCount < 4)
	{
		console.log(funcName);
		console.log(lineIndex + ": Too few arguments.");

		console.log("argCount " + argCount);
		console.log(args);

		return true;
	}
	else if (argCount > 5)
	{
		console.log(funcName);
		console.log(lineIndex + ": Too many arguments.");

		console.log("argCount " + argCount);
		console.log(args);

		return true;
	}



	// IntroduceData(baseAddrName, dataName, dataType, return);
	// IntroduceData(baseAddrName, baseAddrSource, dataName, dataType, return);

	let baseAddrName   = "";
	let baseAddrSource = "";
	let dataName       = "";
	let dataType       = "";
	let returnal       = "";

	if (argCount == 4)
	{
		baseAddrName = args[0];
		dataName     = args[1];
		dataType     = args[2];
		returnal     = args[3];
	}
	else if (argCount == 5)
	{
		baseAddrName   = args[0];
		baseAddrSource = args[1];
		dataName       = args[2];
		dataType       = args[3];
		returnal       = args[4];

		c += Tabs() + "auto " + baseAddrName + " = " + baseAddrSource + ";" + NEW_LINE;
	}

	c += Tabs() + "if (!" + baseAddrName + ")" + NEW_LINE;

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();

	c += Tabs() + "auto & " + dataName + " = *reinterpret_cast<" + dataType + " *>(" + baseAddrName + ");";

	return false;
}]);



helpers.push(["IntroducePlayerCharacterNewActorData", (args) =>
{
	let funcName = this.name;

	let lineIndex = GetLineIndex();

	let argCount = args.length;

	if (argCount > 3)
	{
		console.log(funcName);
		console.log(lineIndex + ": Too many arguments.");

		console.log("argCount " + argCount);
		console.log(args);

		return true;
	}



	// IntroducePlayerCharacterNewActorData();
	// IntroducePlayerCharacterNewActorData(playerIndex);
	// IntroducePlayerCharacterNewActorData(playerIndex, characterIndex);
	// IntroducePlayerCharacterNewActorData(playerIndex, characterIndex, entityIndex);

	let playerIndex    = "0";
	let characterIndex = "playerData.characterIndex";
	let entityIndex    = "ENTITY::MAIN";

	if (argCount >= 1)
	{
		playerIndex = args[0];
	}

	if (argCount >= 2)
	{
		characterIndex = args[1];
	}

	if (argCount >= 3)
	{
		entityIndex = args[2];
	}

	c += Tabs() + "auto & playerData = GetPlayerData(" + playerIndex + ");" + NEW_LINE;
	c += NEW_LINE;

	c += Tabs() + "auto & characterData = GetCharacterData(" + playerIndex + ", " + characterIndex + ", " + entityIndex + ");" + NEW_LINE;
	c += Tabs() + "auto & newActorData  = GetNewActorData (" + playerIndex + ", " + characterIndex + ", " + entityIndex + ");" + NEW_LINE;
	c += NEW_LINE;

	c += Tabs() + "auto & activeCharacterData = GetCharacterData(" + playerIndex + ", playerData.activeCharacterIndex, ENTITY::MAIN);" + NEW_LINE;
	c += Tabs() + "auto & activeNewActorData  = GetNewActorData (" + playerIndex + ", playerData.activeCharacterIndex, ENTITY::MAIN);" + NEW_LINE;
	c += NEW_LINE;

	c += Tabs() + "auto & leadCharacterData = GetCharacterData(" + playerIndex + ", 0, ENTITY::MAIN);" + NEW_LINE;
	c += Tabs() + "auto & leadNewActorData  = GetNewActorData (" + playerIndex + ", 0, ENTITY::MAIN);" + NEW_LINE;
	c += NEW_LINE;

	c += Tabs() + "auto & mainCharacterData = GetCharacterData(" + playerIndex + ", " + characterIndex + ", ENTITY::MAIN);" + NEW_LINE;
	c += Tabs() + "auto & mainNewActorData  = GetNewActorData (" + playerIndex + ", " + characterIndex + ", ENTITY::MAIN);" + NEW_LINE;
	c += NEW_LINE;



	return false;
}]);






helpers.push(["IntroduceEnemyCount", (args) =>
{
	let funcName = this.name;

	let lineIndex = GetLineIndex();

	let argCount = args.length;

	if (argCount < 1)
	{
		console.log(funcName);
		console.log(lineIndex + ": Too few arguments.");

		console.log("argCount " + argCount);
		console.log(args);

		return true;
	}
	else if (argCount > 1)
	{
		console.log(funcName);
		console.log(lineIndex + ": Too many arguments.");

		console.log("argCount " + argCount);
		console.log(args);

		return true;
	}


	// IntroduceEnemyCount(return);

	let returnal = args[0];

	let poolName = "pool_" + lineIndex;



	c += Tabs() + "auto " + poolName + " = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);" + NEW_LINE;
	c += Tabs() + "if" + NEW_LINE;

	ScopeStart("(");

	c += Tabs() + "!" + poolName + " ||" + NEW_LINE;
	c += Tabs() + "!" + poolName + "[8]" + NEW_LINE;

	ScopeEnd(")");

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();

	c += Tabs() + "auto & enemyCount = *reinterpret_cast<uint32 *>(" + poolName + "[8] + 0x28);" + NEW_LINE;






	return false;
}]);




helpers.push(["IntroduceEnemyVectorData", (args) =>
{
	let funcName = this.name;

	let lineIndex = GetLineIndex();

	let argCount = args.length;

	if (argCount < 1)
	{
		console.log(funcName);
		console.log(lineIndex + ": Too few arguments.");

		console.log("argCount " + argCount);
		console.log(args);

		return true;
	}
	else if (argCount > 1)
	{
		console.log(funcName);
		console.log(lineIndex + ": Too many arguments.");

		console.log("argCount " + argCount);
		console.log(args);

		return true;
	}


	// IntroduceEnemyVectorData(return);

	let returnal = args[0];

	let poolName = "pool_" + lineIndex;



	c += Tabs() + "auto " + poolName + " = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);" + NEW_LINE;
	c += Tabs() + "if" + NEW_LINE;

	ScopeStart("(");

	c += Tabs() + "!" + poolName + " ||" + NEW_LINE;
	c += Tabs() + "!" + poolName + "[8]" + NEW_LINE;

	ScopeEnd(")");

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();

	c += Tabs() + "auto & enemyVectorData = *reinterpret_cast<EnemyVectorData *>(" + poolName + "[8]);" + NEW_LINE;






	return false;
}]);
