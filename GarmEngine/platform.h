#pragma once

//
//Define pre processor macros for dll export import, and system macros
//

#ifdef _WIN32
#define GARM_SYS_WINDOWS
//Define to disable <windows.h> from defining min and max macros (for sdl...)
#ifndef NOMINMAX
#define NOMINMAX
#endif
#elif define(__linux__)
#define FULIO_SYS_LINUX
#elif define(__APPLE__)
#define FULIO_SYS_MACOS

#endif	//_WIN32

#ifndef GARM_STATIC_BUILD
#ifdef GARM_SYS_WINDOWS
#ifdef FULIO_NONCLIENT_BUILD
#define FULIO_API __declspec(dllexport)
#else
#define GARM_API __declspec(dllimport)
#endif
//Disable error for 
#ifdef _MSC_VER
#pragma warning(disable : 4251)
#endif	
#elif defined(GARM_SYS_LINUX) || defined(GARM_SYS_MACOS)
#ifdef __GNUC__ >= 4
#define GARM_API __attribute__ ((__visibility__("default")))
#else
#define GARM_API GARM_API
#endif

#else
#define GARM_API GARM_API
#endif
#endif