#ifndef GAMMA_COMMON_PLATFORM_DEPENDENCIES_H__
    #define GAMMA_COMMON_PLATFORM_DEPENDENCIES_H__
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
#if defined( __WIN32__ ) || defined( _WIN32 ) || defined( WIN32 )
    #include <windows.h>
    #define gc_CALLCONV WINAPI
    #define gc_CALLCONV_CDECL CDECL
#else
    #define gc_CALLCONV       /* use default */
    #define gc_CALLCONV_CDECL /* use default */
#endif

#undef gc_EXT_C

#ifdef __cplusplus
    #define gc_EXT_C extern "C"
#else
    #define gc_EXT_C extern
#endif

#undef gc_EXP
#undef gc_PUBLIC

#if defined( __WIN32__ ) || defined( _WIN32 ) || defined( WIN32 )
    #if defined (GAMMA_COMMON_AS_DLL)
        /******************** Export of global variables  *********************/
        #define gc_EXP_GLOBAL       gc_EXT_C __declspec(dllexport)
        #define gc_PUBLIC_GLOBAL    __declspec(dllexport)


        /**** Export of functions (pseudo-default -> no explicit naming!) *****/
        #define gc_EXP              gc_EXP_GLOBAL
        #define gc_PUBLIC           gc_PUBLIC_GLOBAL
    #else
        /******************** Import of global variables  *********************/
        #define gc_EXP_GLOBAL       gc_EXT_C __declspec(dllimport)
        #define gc_PUBLIC_GLOBAL    __declspec(dllimport)

        /**** Import of functions (pseudo-default -> no explicit naming!) *****/
        #define gc_EXP              gc_EXP_GLOBAL
        #define gc_PUBLIC           gc_PUBLIC_GLOBAL
    #endif
#else
    #define gc_EXP_GLOBAL       gc_EXT_C
    #define gc_PUBLIC_GLOBAL
    #define gc_EXP              gc_EXP_GLOBAL
    #define gc_PUBLIC           gc_PUBLIC_GLOBAL
    #define gc_CALLCONV
#endif

#if defined(__GNUC__)
    #define gc_DEPRECATED
    #define gc_DEPRECATED_MSG( msg )
    #define gc_PRINTF_FMT( a, b )
#elif defined( _MSC_VER )
    #define gc_DEPRECATED
    #define gc_DEPRECATED_MSG( msg)
    #define gc_PRINTF_FMT( a, b )
#else
    #warning "Compiler not offically supported! Please Contact RST"
    #define gc_DEPRECATED
    #define gc_DEPRECATED_MSG( msg)
    #define gc_PRINTF_FMT( a, b )
#endif

#endif //GAMMA_COMMON_PLATFORM_DEPENDENCIES_H__
