#ifndef GAIO_LOG_H_
  #define GAIO_LOG_H_

/**
 * @file
 *
 * @author  Copyright RST Industrie Automation GmbH
 */
/******************************************************************************
 * Header File Includes
 ******************************************************************************/
#include <gaio/export.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Serverity of logged message
 */
typedef enum gi_Severity
{
    GI_SEVERITY_DEBUG,		///< log level type is DEBUG
    GI_SEVERITY_INFO,			///< log level type is INFO
    GI_SEVERITY_WARN,			///< log level type is WARN
    GI_SEVERITY_ERROR			///< log level type is ERROR
} gi_Severity;

/**
 * @brief
 *
 * Logging function pointer. Calling this method uses the gamma service error
 * logging facility to log messages.
 *
 * @param [in]  severity        Severity of message to be logged.
 * @param [in]  message         Pointer to message.
 */
typedef WINAPI void (*gi_Log)( const gi_Severity severity,
                               const char* const message );

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* GAIO_LOG_H_ */
