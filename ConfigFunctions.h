#ifdef NO_SAVE
void SaveConfigFunction()
#else
export void SaveConfig()
#endif
{
	#ifndef NO_SAVE
	LogFunction();
	#endif

	using namespace rapidjson;
	using namespace JSON;



	ToJSON(queuedConfig);



	StringBuffer stringBuffer;
	PrettyWriter<StringBuffer> prettyWriter(stringBuffer);

	root.Accept(prettyWriter);



	auto name = stringBuffer.GetString();
	auto size = strlen(name);

	if
	(
		!SaveFile
		(
			location,
			name,
			size
		)
	)
	{
		Log("SaveFile failed.");
	}
}



#ifdef NO_LOAD
void LoadConfigFunction()
#else
export void LoadConfig()
#endif
{
	#ifndef NO_LOAD
	LogFunction();
	#endif

	using namespace rapidjson;
	using namespace JSON;



	auto file = LoadFile(location);
	if (!file)
	{
		Log("LoadFile failed.");

		CreateMembers(defaultConfig);

		SaveConfig();

		return;
	}



	auto name = const_cast<const char *>(reinterpret_cast<char *>(file));

	auto & result = root.Parse(name);

	if (result.HasParseError())
	{
		auto code = result.GetParseError();
		auto off = result.GetErrorOffset();

		Log
		(
			"Parse failed. "
			#ifdef _WIN64
			"%u %llu",
			#else
			"%u %u",
			#endif
			code,
			off
		);

		return;
	}



	CreateMembers(defaultConfig);

	// At this point all file members have been applied. Extra or obsolete file members can exist.
	// If members were missing in the file they were created and have their default values.



	// The actual configs are still untouched though.
	// Let's update them!

	ToConfig(queuedConfig);

	CopyMemory
	(
		&activeConfig,
		&queuedConfig,
		sizeof(activeConfig)
	);



	SaveConfig();

	// SaveConfig here in case new members were created.
	// This way we don't have to rely on a later SaveConfig to update the file.
}



#ifdef NO_INIT
void InitConfigFunction()
#else
export void InitConfig()
#endif
{
	#ifndef NO_INIT
	LogFunction();
	#endif

	using namespace rapidjson;
	using namespace JSON;

	CreateDirectoryA(directoryName, 0);

	snprintf
	(
		location,
		sizeof(location),
		"%s/%s",
		directoryName,
		fileName
	);

	root.SetObject();

	g_allocator = &root.GetAllocator();
}
