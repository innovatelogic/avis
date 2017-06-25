#pragma once

#include "OEMBase.h"

#if (defined(ES_WINDOWS))
#ifdef CIE_PLOT_LIB_COMPILE
#define CIE_EXPORT _declspec(dllexport)
#define EXTERN_JUNK_EXPORT   extern JUNK_EXPORT

#else
#define CIE_EXPORT _declspec(dllimport)
#endif
#endif