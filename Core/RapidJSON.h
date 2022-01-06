



#include "Macros.h"


#define RAPIDJSON_NO_SIZETYPEDEFINE

namespaceStart(rapidjson);

#ifdef _WIN64
typedef unsigned long long SizeType;
#else
typedef unsigned long      SizeType;
#endif

namespaceEnd();



// #define RAPIDJSON_PARSE_DEFAULT_FLAGS (kParseCommentsFlag | kParseTrailingCommasFlag)




#include "../ThirdParty/rapidjson/document.h"
#include "../ThirdParty/rapidjson/prettywriter.h"












