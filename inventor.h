
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the INVENTOR_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// INVENTOR_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef WIN32
#ifndef __i386__
#define __i386__
#endif
#pragma warning(disable:4244) // float, double
#pragma warning(disable:4305) // float, double
#pragma warning(disable:4309) // float, double
#pragma warning(disable:4251) // export
#pragma warning(disable:4291) // no delete destructor
#include <windows.h>
#include <math.h>
#ifdef INVENTOR_EXPORTS
#define INVENTOR_API __declspec(dllexport)
#else
#define INVENTOR_API __declspec(dllimport)
#endif
#else
#define INVENTOR_API
#ifndef CALLBACK
#define CALLBACK
#endif
#endif

