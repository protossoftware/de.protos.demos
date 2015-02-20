#ifndef GAMMA_API_PLATFORM_DEPENDENCIES_H__
    #define GAMMA_API_PLATFORM_DEPENDENCIES_H__
/**
 * @file
 * Abstracts platform dependent interface definitions for all headers
 * of the middleware.
 *
 * This header file is only required for the calling conventions and the
 * handling of Shared Libraries (DLLs) under Windows. A user can ignore it.
 *
 * @author  (C)opyright by RST Industrie Automation GmbH
 */
/******************************************************************************
 * Platform Dependencies
 ******************************************************************************/
#include <gacommon/platformDependencies.h>

#if defined( __WIN32__ ) || defined( _WIN32 ) || defined( WIN32 )
    #if defined (GAMMA_API_AS_DLL)
        /******************** Export of global variables  *********************/
        #define ga_EXP_GLOBAL       gc_EXT_C __declspec(dllexport)
        #define ga_PUBLIC_GLOBAL    __declspec(dllexport)

        /**** Export of functions (pseudo-default -> no explicit naming!) *****/
        #define ga_EXP              ga_EXP_GLOBAL
        #define ga_PUBLIC           ga_PUBLIC_GLOBAL
    #else
        /******************** Import of global variables  *********************/
        #define ga_EXP_GLOBAL       gc_EXT_C __declspec(dllimport)
        #define ga_PUBLIC_GLOBAL    __declspec(dllimport)

        /**** Import of functions (pseudo-default -> no explicit naming!) *****/
        #define ga_EXP              ga_EXP_GLOBAL
        #define ga_PUBLIC           ga_PUBLIC_GLOBAL
    #endif
#else
    #define ga_EXP_GLOBAL       gc_EXT_C
    #define ga_PUBLIC_GLOBAL
    #define ga_EXP              ga_EXP_GLOBAL
    #define ga_PUBLIC           ga_PUBLIC_GLOBAL
#endif




#endif //GAMMA_API_PLATFORM_DEPENDENCIES_H__
