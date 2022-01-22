#define RAPIDJSON_NO_SIZETYPEDEFINE

namespace rapidjson
{

#ifdef _WIN64
typedef unsigned long long SizeType;
#else
typedef unsigned long      SizeType;
#endif

}



// #define RAPIDJSON_PARSE_DEFAULT_FLAGS (kParseCommentsFlag | kParseTrailingCommasFlag)



#include "../ThirdParty/rapidjson/document.h"
#include "../ThirdParty/rapidjson/prettywriter.h"
