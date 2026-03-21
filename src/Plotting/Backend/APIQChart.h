#pragma once

#ifndef QCHART_BACKEND
#if defined(_WIN32) && !defined(__GNUC__)
#ifdef COMPILING_QCHART_BACKEND_DLL
#define QCHART_BACKEND __declspec(dllexport)
#else
#define QCHART_BACKEND __declspec(dllimport)
#endif // COMPILING_QCHART_BACKEND_DLL
#else
#define QCHART_BACKEND
#endif // _WIN32 && !__GNUC__
#endif // QCHART_BACKEND
