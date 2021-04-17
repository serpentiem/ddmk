

// @Todo: Move.



var fs = require("fs");

eval(fs.readFileSync("dmc3_core.js", "utf8"));

function CreateActorCheatEntry
(
	name,
	type,
	off,
	hex,
	actor
)
{
	CreateCheatEntry
	(
		name,
		hex,
		type,
		"Mary.Actor_actorBaseAddr",
		off.toString(16).toUpperCase(),
		(actor * 8).toString(16).toUpperCase()
	);
}

CheatTableStart();

GroupStart("__DEVIL_MODEL_METADATA_DANTE__", true);

for (var actor = 0; actor < 4; actor++)
{
	GroupStart(lz(actor), true);

	pos = 0xB600;

	GroupStart("Rebellion", false);
	CreateActorCheatEntry("modelIndex"               , "Byte", (pos + 0), false, actor);
	CreateActorCheatEntry("physicsMetadataIndex"     , "Byte", (pos + 1), false, actor);
	CreateActorCheatEntry("submodelIndex"            , "Byte", (pos + 2), false, actor);
	CreateActorCheatEntry("devilPhysicsMetadataIndex", "Byte", (pos + 3), false, actor);
	CreateActorCheatEntry("devilSubmodelIndex"       , "Byte", (pos + 4), false, actor);
	CreateActorCheatEntry("submodelIndex"            , "Byte", (pos + 5), false, actor);
	CreateActorCheatEntry("devilPhysicsMetadataIndex", "Byte", (pos + 6), false, actor);
	CreateActorCheatEntry("devilSubmodelIndex"       , "Byte", (pos + 7), false, actor);
	GroupEnd();
	pos += 8;

	GroupStart("Cerberus", false);
	CreateActorCheatEntry("modelIndex"               , "Byte", (pos + 0), false, actor);
	CreateActorCheatEntry("physicsMetadataIndex"     , "Byte", (pos + 1), false, actor);
	CreateActorCheatEntry("submodelIndex"            , "Byte", (pos + 2), false, actor);
	CreateActorCheatEntry("devilPhysicsMetadataIndex", "Byte", (pos + 3), false, actor);
	CreateActorCheatEntry("devilSubmodelIndex"       , "Byte", (pos + 4), false, actor);
	GroupEnd();
	pos += 5;

	GroupStart("Agni Rudra", false);
	CreateActorCheatEntry("modelIndex"               , "Byte", (pos + 0), false, actor);
	CreateActorCheatEntry("physicsMetadataIndex"     , "Byte", (pos + 1), false, actor);
	GroupEnd();
	pos += 2;

	GroupStart("Nevan", false);
	CreateActorCheatEntry("modelIndex"               , "Byte", (pos + 0), false, actor);
	CreateActorCheatEntry("physicsMetadataIndex"     , "Byte", (pos + 1), false, actor);
	CreateActorCheatEntry("submodelIndex"            , "Byte", (pos + 2), false, actor);
	CreateActorCheatEntry("devilPhysicsMetadataIndex", "Byte", (pos + 3), false, actor);
	CreateActorCheatEntry("devilSubmodelIndex"       , "Byte", (pos + 4), false, actor);
	CreateActorCheatEntry("submodelIndex"            , "Byte", (pos + 5), false, actor);
	CreateActorCheatEntry("devilPhysicsMetadataIndex", "Byte", (pos + 6), false, actor);
	CreateActorCheatEntry("devilSubmodelIndex"       , "Byte", (pos + 7), false, actor);
	GroupEnd();
	pos += 8;

	GroupStart("Beowulf", false);
	CreateActorCheatEntry("modelIndex"               , "Byte", (pos + 0), false, actor);
	CreateActorCheatEntry("physicsMetadataIndex"     , "Byte", (pos + 1), false, actor);
	CreateActorCheatEntry("submodelIndex"            , "Byte", (pos + 2), false, actor);
	CreateActorCheatEntry("devilPhysicsMetadataIndex", "Byte", (pos + 3), false, actor);
	CreateActorCheatEntry("devilSubmodelIndex"       , "Byte", (pos + 4), false, actor);
	GroupEnd();
	pos += 5;

	GroupStart("Sparda", false);
	CreateActorCheatEntry("modelIndex"               , "Byte", (pos + 0), false, actor);
	CreateActorCheatEntry("physicsMetadataIndex"     , "Byte", (pos + 1), false, actor);
	CreateActorCheatEntry("submodelIndex"            , "Byte", (pos + 2), false, actor);
	CreateActorCheatEntry("devilPhysicsMetadataIndex", "Byte", (pos + 3), false, actor);
	CreateActorCheatEntry("devilSubmodelIndex"       , "Byte", (pos + 4), false, actor);
	GroupEnd();
	pos += 5;

	GroupEnd();
}

GroupEnd();

CheatTableEnd();

fs.writeFileSync("devilModelMetadataDante.txt", c);
