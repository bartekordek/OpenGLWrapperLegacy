#pragma once

#include "CUL/UselessMacros.hpp"

#if _WIN32
#define OGLWL_WINDOWS
#define OGLWL_EXPORT
#else
#define OGLWL_LINUX
#define OGLWL_EXPORT
#endif

#if defined OGLWL_EXPORT && defined OGLWL_LINUX
#define OGLWLAPI
#define OGLWrapperLegacy_TEMPLATE
#elif defined OGLWL_EXPORT && defined OGLWL_WINDOWS
#define OGLWLAPI _declspec(dllexport)
#define OGLWrapperLegacy_TEMPLATE extern
#else
#define OGLWLAPI _declspec(dllimport)
#define OGLWrapperLegacy_TEMPLATE extern
#endif
/*TODO: Find a way to tell library name.
#ifdef _MSC_VER && SDL2Wrapper_DYNAMIC
#pragma comment(lib, "SDL2WrapperDynamic.lib")
#elif  MSC_VER
#pragma comment(lib, "SDL2WrapperStatic.lib")
#else
#pragma comment(lib, "libsdl2wrapper.a")
#endif
*/