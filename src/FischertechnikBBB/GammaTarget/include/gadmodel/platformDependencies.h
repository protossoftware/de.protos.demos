#ifndef GAMMA_DMODEL_PLATFORM_DEPENDENCIES_H__
    #define GAMMA_DMODEL_PLATFORM_DEPENDENCIES_H__
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
    #if defined (GAMMA_DMODEL_AS_DLL)
        /******************** Export of global variables  *********************/
        #define gd_EXP_GLOBAL       gc_EXT_C __declspec(dllexport)
        #define gd_PUBLIC_GLOBAL    __declspec(dllexport)


        /**** Export of functions (pseudo-default -> no explicit naming!) *****/
        #define gd_EXP              gd_EXP_GLOBAL
        #define gd_PUBLIC           gd_PUBLIC_GLOBAL
    #else
        /******************** Import of global variables  *********************/
        #define gd_EXP_GLOBAL       gc_EXT_C __declspec(dllimport)
        #define gd_PUBLIC_GLOBAL    __declspec(dllimport)

        /**** Import of functions (pseudo-default -> no explicit naming!) *****/
        #define gd_EXP              gd_EXP_GLOBAL
        #define gd_PUBLIC           gd_PUBLIC_GLOBAL
    #endif
#else
    #define gd_EXP_GLOBAL       gc_EXT_C
    #define gd_PUBLIC_GLOBAL
    #define gd_EXP              gd_EXP_GLOBAL
    #define gd_PUBLIC           gd_PUBLIC_GLOBAL
#endif




#endif //GAMMA_DMODEL_PLATFORM_DEPENDENCIES_H__
