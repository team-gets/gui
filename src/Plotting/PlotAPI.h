#pragma once

#ifndef PLOT_API
#if defined(_WIN32) && !defined(__GNUC__)
#define PLOT_API __declspec(dllimport)
#else
#define PLOT_API
#endif
#endif
