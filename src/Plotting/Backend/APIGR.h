#pragma once

#ifndef GR_BACKEND
#if defined(_WIN32) && !defined(__GNUC__)
#ifdef COMPILING_GR_BACKEND_DLL
#define GR_BACKEND __declspec(dllexport)
#else
#define GR_BACKEND __declspec(dllimport)
#endif
#else
#define GR_BACKEND
#endif
#endif
