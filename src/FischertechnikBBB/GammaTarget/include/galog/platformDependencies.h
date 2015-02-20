#ifndef GAMMA_LOG_PLATFORM_DEPENDENCIES_H__
    #define GAMMA_LOG_PLATFORM_DEPENDENCIES_H__
/**
 * @file
 * Abstracts platform dependent interface definitions for all headers
 * of the middleware.
 *
 * @author  (C)opyright by RST Industrie Automation GmbH
 */
/******************************************************************************
 * Platform Dependencies
 ******************************************************************************/
#include <gacommon/platformDependencies.h>


#if defined( __WIN32__ ) || defined( _WIN32 ) || defined( WIN32 )
    #if defined (GAMMA_LOG_AS_DLL)
        /******************** Export of global variables  *********************/
        #define gl_EXP_GLOBAL       gc_EXT_C __declspec(dllexport)
        #define gl_PUBLIC_GLOBAL    __declspec(dllexport)

        /**** Export of functions (pseudo-default -> no explicit naming!) *****/
        #define gl_EXP              gl_EXP_GLOBAL
        #define gl_PUBLIC           gl_PUBLIC_GLOBAL
    #else
        /******************** Import of global variables  *********************/
        #define gl_EXP_GLOBAL       gc_EXT_C __declspec(dllimport)
        #define gl_PUBLIC_GLOBAL    __declspec(dllimport)

        /**** Import of functions (pseudo-default -> no explicit naming!) *****/
        #define gl_EXP              gl_EXP_GLOBAL
        #define gl_PUBLIC           gl_PUBLIC_GLOBAL
    #endif
#else
    #define gl_EXP_GLOBAL       gc_EXT_C
    #define gl_PUBLIC_GLOBAL
    #define gl_EXP              gl_EXP_GLOBAL
    #define gl_PUBLIC           gl_PUBLIC_GLOBAL
#endif




#endif //GAMMA_LOG_PLATFORM_DEPENDENCIES_H__
