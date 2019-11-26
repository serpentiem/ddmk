
// @Research: Give namespaces another go.
// @Research: Merge Core into a single translation unit.
//            The #includes kinda add up.

#pragma once
#include "Config.h"
#include "DataTypes.h"
#include "File.h"
#include "Log.h"
#ifdef _WIN64
#include "Memory.h"
#else
#include "Memory32.h"
#endif
#include "String.h"
#include "Utility.h"
#include "Vector.h"
#include "Windows.h"
