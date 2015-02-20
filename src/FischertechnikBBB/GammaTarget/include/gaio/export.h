#ifndef GAIO_EXPORT_H_
  #define GAIO_EXPORT_H_

/**
 * @file
 *
 * @author  Copyright RST Industrie Automation GmbH
 */
/******************************************************************************
 * Header File Includes
 ******************************************************************************/

#if defined(__WIN32__) || defined(_WIN32)

    #if !defined(WINAPI)
        #define WINAPI __stdcall
    #endif

    #if defined (BUILD_IOPLUGIN)
        #define IOPLUGIN_EXP __declspec(dllexport)
    #else
        #define IOPLUGIN_EXP __declspec(dllimport)
    #endif

#else

#define WINAPI
#define IOPLUGIN_EXP __attribute__((visibility("default")))

#endif

#endif /* GAIO_EXPORT_H_ */
