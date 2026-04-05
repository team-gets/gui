#pragma once

#ifndef FS_API
#if defined(_WIN32) && !defined(__GNUC__)
#ifdef COMPILING_FS_API_DLL
#define FS_API __declspec(dllexport)
#else
#define FS_API __declspec(dllimport)
#endif
#else
#define FS_API
#endif
#endif
