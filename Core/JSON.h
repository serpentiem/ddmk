


// @Todo: Check array item count at compile-time.
// @Todo: Check Get type.





// Inconsistent value and value-less versions, because we can't have nice things.

rapidjson::Document root = {};

rapidjson::Value::AllocatorType * g_allocator = 0;













bool IsString(rapidjson::Value & member)
{
	return member.IsString();
}



void GetString
(
	char * buffer,
	new_size_t bufferSize,
	rapidjson::Value & member
)
{
	auto name = member.GetString();

	snprintf
	(
		buffer,
		bufferSize,
		"%s",
		name
	);
}



void SetString
(
	rapidjson::Value & member,
	const char * value
)
{
	member.SetString
	(
		rapidjson::StringRef
		(
			value,
			strlen(value)
		)
	);
}



template
<
	typename T,
	new_size_t length
>
rapidjson::Value & CreateString
(
	rapidjson::Value & member,
	T (&name)[length],
	const char * value
)
{
	auto & allocator = *g_allocator;

	if (!member.HasMember(name))
	{
		rapidjson::Value newMember = {};

		member.AddMember
		(
			name,
			newMember,
			allocator
		);
	}



	auto & member2 = member[name];

	if (!IsString(member2))
	{
		Log("value !IsString %s", name);

		SetString(member2, value);
	}

	return member2;
}






















template <typename T>
bool Is(rapidjson::Value & member)
{
	     if constexpr (TypeMatch<T, bool        >::value){ return member.IsBool  (); }
	else if constexpr (TypeMatch<T, int8        >::value){ return member.IsInt   (); }
	else if constexpr (TypeMatch<T, int16       >::value){ return member.IsInt   (); }
	else if constexpr (TypeMatch<T, int32       >::value){ return member.IsInt   (); }
	else if constexpr (TypeMatch<T, int64       >::value){ return member.IsInt64 (); }
	else if constexpr (TypeMatch<T, uint8       >::value){ return member.IsUint  (); }
	else if constexpr (TypeMatch<T, uint16      >::value){ return member.IsUint  (); }
	else if constexpr (TypeMatch<T, uint32      >::value){ return member.IsUint  (); }
	else if constexpr (TypeMatch<T, uint64      >::value){ return member.IsUint64(); }
	else if constexpr (TypeMatch<T, float       >::value){ return member.IsFloat (); }
	else if constexpr (TypeMatch<T, double      >::value){ return member.IsDouble(); }
	else if constexpr (TypeMatch<T, const char *>::value){ return member.IsString(); }
	else if constexpr (TypeMatch<T, struct_t    >::value){ return member.IsObject(); }
	else if constexpr (TypeMatch<T, array_t     >::value){ return member.IsArray (); }
}



#pragma region Get

template <typename T>
T Get(rapidjson::Value & member)
{
	     if constexpr (TypeMatch<T, bool        >::value){ return                member.GetBool  () ; }
	else if constexpr (TypeMatch<T, int8        >::value){ return static_cast<T>(member.GetInt   ()); }
	else if constexpr (TypeMatch<T, int16       >::value){ return static_cast<T>(member.GetInt   ()); }
	else if constexpr (TypeMatch<T, int32       >::value){ return static_cast<T>(member.GetInt   ()); }
	else if constexpr (TypeMatch<T, int64       >::value){ return static_cast<T>(member.GetInt64 ()); }
	else if constexpr (TypeMatch<T, uint8       >::value){ return static_cast<T>(member.GetUint  ()); }
	else if constexpr (TypeMatch<T, uint16      >::value){ return static_cast<T>(member.GetUint  ()); }
	else if constexpr (TypeMatch<T, uint32      >::value){ return static_cast<T>(member.GetUint  ()); }
	else if constexpr (TypeMatch<T, uint64      >::value){ return static_cast<T>(member.GetUint64()); }
	else if constexpr (TypeMatch<T, float       >::value){ return                member.GetFloat () ; }
	else if constexpr (TypeMatch<T, double      >::value){ return                member.GetDouble() ; }
	else if constexpr (TypeMatch<T, const char *>::value){ return                member.GetString() ; }
}



template
<
	typename T,
	new_size_t count
>
void GetArray
(
	T (&values)[count],
	rapidjson::Value & member
)
{
	for_all(index, count)
	{
		auto & member2 = member[index];
		auto & value   = values[index];

		value = Get<T>(member2);
	}
}



template
<
	typename T,
	new_size_t count,
	new_size_t count2
>
void GetArray2
(
	T (&values)[count][count2],
	rapidjson::Value & member
)
{
	for_all(index , count )
	for_all(index2, count2)
	{
		auto & member2 = member[index][index2];
		auto & value   = values[index][index2];

		value = Get<T>(member2);
	}
}



template
<
	typename T,
	new_size_t count,
	new_size_t count2,
	new_size_t count3
>
void GetArray3
(
	T (&values)[count][count2][count3],
	rapidjson::Value & member
)
{
	for_all(index , count )
	for_all(index2, count2)
	for_all(index3, count3)
	{
		auto & member2 = member[index][index2][index3];
		auto & value   = values[index][index2][index3];

		value = Get<T>(member2);
	}
}

#pragma endregion



#pragma region Set

template <typename T>
void Set(rapidjson::Value & member) = delete;


template <>
void Set<array_t>(rapidjson::Value & member)
{
	member.SetArray();
}

template <>
void Set<struct_t>(rapidjson::Value & member)
{
	member.SetObject();
}



template <typename T>
void Set
(
	rapidjson::Value & member,
	T value
)
{
	     if constexpr (TypeMatch<T, bool        >::value){ member.SetBool  (value); }
	else if constexpr (TypeMatch<T, int8        >::value){ member.SetInt   (value); }
	else if constexpr (TypeMatch<T, int16       >::value){ member.SetInt   (value); }
	else if constexpr (TypeMatch<T, int32       >::value){ member.SetInt   (value); }
	else if constexpr (TypeMatch<T, int64       >::value){ member.SetInt64 (value); }
	else if constexpr (TypeMatch<T, uint8       >::value){ member.SetUint  (value); }
	else if constexpr (TypeMatch<T, uint16      >::value){ member.SetUint  (value); }
	else if constexpr (TypeMatch<T, uint32      >::value){ member.SetUint  (value); }
	else if constexpr (TypeMatch<T, uint64      >::value){ member.SetUint64(value); }
	else if constexpr (TypeMatch<T, float       >::value){ member.SetFloat (value); }
	else if constexpr (TypeMatch<T, double      >::value){ member.SetDouble(value); }
	else if constexpr (TypeMatch<T, const char *>::value){ member.SetString(value); }
}



template
<
	typename T,
	new_size_t count
>
void SetArray
(
	rapidjson::Value & member,
	T (&values)[count]
)
{
	for_all(index, count)
	{
		auto & member2 = member[index];
		auto & value   = values[index];

		Set<T>(member2, value);
	}
}



template
<
	typename T,
	new_size_t count,
	new_size_t count2
>
void SetArray2
(
	rapidjson::Value & member,
	T (&values)[count][count2]
)
{
	for_all(index , count )
	for_all(index2, count2)
	{
		auto & member2 = member[index][index2];
		auto & value   = values[index][index2];

		Set<T>(member2, value);
	}
}



template
<
	typename T,
	new_size_t count,
	new_size_t count2,
	new_size_t count3
>
void SetArray3
(
	rapidjson::Value & member,
	T (&values)[count][count2][count3]
)
{
	for_all(index , count )
	for_all(index2, count2)
	for_all(index3, count3)
	{
		auto & member2 = member[index][index2][index3];
		auto & value   = values[index][index2][index3];

		Set<T>(member2, value);
	}
}

#pragma endregion



#pragma region Create




// The 2 separate versions are required for proper compile-time type checking.

template
<
	typename T,
	typename T2,
	new_size_t length
>
rapidjson::Value & Create
(
	rapidjson::Value & member,
	T2 (&name)[length]
)
{
	auto & allocator = *g_allocator;

	if (!member.HasMember(name))
	{
		rapidjson::Value newMember = {};

		member.AddMember
		(
			name,
			newMember,
			allocator
		);
	}



	auto & member2 = member[name];

	if (!Is<T>(member2))
	{
		Log("value-less !Is %s", name);

		Set<T>(member2);
	}

	return member2;
}








template
<
	typename T,
	typename T2,
	new_size_t length
>
rapidjson::Value & Create
(
	rapidjson::Value & member,
	T2 (&name)[length],
	T & value
)
{
	auto & allocator = *g_allocator;

	if (!member.HasMember(name))
	{
		rapidjson::Value newMember = {};

		member.AddMember
		(
			name,
			newMember,
			allocator
		);
	}



	auto & member2 = member[name];

	if (!Is<T>(member2))
	{
		Log("value !Is %s", name);

		Set<T>(member2, value);
	}

	return member2;
}



// template
// <
// 	typename T,
// 	typename T2,
// 	new_size_t length,
// 	typename... Args
// >
// rapidjson::Value & Create
// (
// 	rapidjson::Value & member,
// 	T2 (&name)[length],
// 	Args... args
// )
// {
// 	auto & allocator = *g_allocator;

// 	if (!member.HasMember(name))
// 	{
// 		rapidjson::Value newMember = {};

// 		member.AddMember
// 		(
// 			name,
// 			newMember,
// 			allocator
// 		);
// 	}



// 	auto & member2 = member[name];

// 	if (!Is<T>(member2))
// 	{
// 		constexpr new_size_t argCount = sizeof...(args);

// 		if constexpr (argCount == 0)
// 		{
// 			Log("value-less !Is %s", name);
// 		}
// 		else
// 		{
// 			Log("value !Is %s", name);
// 		}



// 		Set<T>(member2, args...);
// 	}

// 	return member2;
// }



void UpdateCount
(
	rapidjson::Value & member,
	new_size_t count
)
{
	if (!member.IsArray())
	{
		return;
	}

	auto & allocator = *g_allocator;

	auto count2 = member.Size();



	if (count2 < count)
	{
		auto diff = (count - count2);

		for_all(index, diff)
		{
			rapidjson::Value newMember = {};

			member.PushBack
			(
				newMember,
				allocator
			);
		}
	}



	if (count2 > count)
	{
		auto diff = (count2 - count);

		for_all(index, diff)
		{
			member.PopBack();
		}
	}
}



/*
Successful calls to CreateArray guarantee that:

* The array exists.
* The count is correct.
* The type of every single item is correct.
*/



// value-less

template
<
	typename T,
	new_size_t count,
	typename T2,
	new_size_t length
>
rapidjson::Value & CreateArray
(
	rapidjson::Value & member,
	T2 (&name)[length]
)
{
	auto & newMember = Create<array_t>(member, name);

	UpdateCount(newMember, count);

	for_all(index, count)
	{
		auto & member2 = newMember[index];

		if (!Is<T>(member2))
		{
			Set<T>(member2);
		}
	}

	return newMember;
}



template
<
	typename T,
	new_size_t count,
	new_size_t count2,
	typename T2,
	new_size_t length
>
rapidjson::Value & CreateArray2
(
	rapidjson::Value & member,
	T2 (&name)[length]
)
{
	auto & newMember = CreateArray<array_t, count>(member, name);

	for_all(index, count)
	{
		auto & member2 = newMember[index];

		UpdateCount(member2, count2);
	}

	for_all(index , count ){
	for_all(index2, count2)
	{
		auto & member2 = newMember[index][index2];

		if (!Is<T>(member2))
		{
			Set<T>(member2);
		}
	}}

	return newMember;
}



template
<
	typename T,
	new_size_t count,
	new_size_t count2,
	new_size_t count3,
	typename T2,
	new_size_t length
>
rapidjson::Value & CreateArray3
(
	rapidjson::Value & member,
	T2 (&name)[length]
)
{
	auto & newMember = CreateArray2<array_t, count, count2>(member, name);

	for_all(index , count ){
	for_all(index2, count2)
	{
		auto & member2 = newMember[index][index2];

		UpdateCount(member2, count3);
	}}

	for_all(index , count ){
	for_all(index2, count2){
	for_all(index3, count3)
	{
		auto & member2 = newMember[index][index2][index3];

		if (!Is<T>(member2))
		{
			Set<T>(member2);
		}
	}}}

	return newMember;
}



// value

template
<
	typename T,
	new_size_t count,
	typename T2,
	new_size_t length
>
rapidjson::Value & CreateArray
(
	rapidjson::Value & member,
	T2 (&name)[length],
	T (&values)[count]
)
{
	auto & newMember = Create<array_t>(member, name);

	UpdateCount(newMember, count);

	for_all(index, count)
	{
		auto & member2 = newMember[index];
		auto & value   = values   [index];

		if (!Is<T>(member2))
		{
			Set<T>(member2, value);
		}
	}

	return newMember;
}



template
<
	typename T,
	new_size_t count,
	new_size_t count2,
	typename T2,
	new_size_t length
>
rapidjson::Value & CreateArray2
(
	rapidjson::Value & member,
	T2 (&name)[length],
	T (&values)[count][count2]
)
{
	auto & newMember = CreateArray<array_t, count>(member, name);

	for_all(index, count)
	{
		auto & member2 = newMember[index];

		UpdateCount(member2, count2);
	}

	for_all(index , count ){
	for_all(index2, count2)
	{
		auto & member2 = newMember[index][index2];
		auto & value   = values   [index][index2];

		if (!Is<T>(member2))
		{
			Set<T>(member2, value);
		}
	}}

	return newMember;
}



template
<
	typename T,
	new_size_t count,
	new_size_t count2,
	new_size_t count3,
	typename T2,
	new_size_t length
>
rapidjson::Value & CreateArray3
(
	rapidjson::Value & member,
	T2 (&name)[length],
	T (&values)[count][count2][count3]
)
{
	auto & newMember = CreateArray2<array_t, count, count2>(member, name);

	for_all(index , count ){
	for_all(index2, count2)
	{
		auto & member2 = newMember[index][index2];

		UpdateCount(member2, count3);
	}}

	for_all(index , count ){
	for_all(index2, count2){
	for_all(index3, count3)
	{
		auto & member2 = newMember[index][index2][index3];
		auto & value   = values   [index][index2][index3];

		if (!Is<T>(member2))
		{
			Set<T>(member2, value);
		}
	}}}

	return newMember;
}



#pragma endregion
