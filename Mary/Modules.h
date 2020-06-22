#ifdef __INTELLISENSE__
#define export
#define import
#define module
#define ModuleName(...)
#else
#define ModuleName(...) __VA_ARGS__
#endif
