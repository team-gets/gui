#pragma once

#ifndef PLOT_API
#if defined(_WIN32) && !defined(__GNUC__)
#ifdef COMPILING_PLOT_API_DLL
#define PLOT_API __declspec(dllexport)
#else
#define PLOT_API __declspec(dllimport)
#endif
#else
#define PLOT_API
#endif
#endif
