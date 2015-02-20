#ifndef GAMMA_COMMON_CORE_H__
  #define GAMMA_COMMON_CORE_H__
/**
 * @file
 * Contains the core interface of the Gamma Middleware.
 *
 * 1. Multithread-Safety \n
 * \n
 * It's important to know that not all functions are multithread-safe and
 * mixing multithread-safe functions with one that are not safe will result
 * in undefined behavior. But it's allowed to mix multithread-safe functions
 * with each other. \n
 * \n
 *
 * 2. General API Usage \n
 * \n
 *
 *
 *
 * @author  (C)opyright by RST Industrie Automation GmbH
 */
/******************************************************************************
 * Header File Includes
 ******************************************************************************/
#include <gacommon/errorCodes.h>
#include <gacommon/dataTypes.h>
#include <gacommon/platformDependencies.h>

#include <stdarg.h>

/******************************************************************************
 * Interface - Initialization/Deinitialization
 ******************************************************************************/
/**
 * Attaches to the local gamma service.
 *
 * This operation must be done before all other API calls!
 *
 * The timeoutMS parameter can be used to let the operation wait for the given
 * milliseconds for the Gamma Service to start or respond to the initialization
 * of the communication.
 *
 * If the Gamma Service will be restarted after a previous successful call to
 * #gc_attachToService a further call to #gc_attachToService will report an
 * #gc_ERROR_ATTACH_CORRUPTED error. In this case please call #gc_detachFromService
 * to remove the corrupted connection information and finally call
 * #gc_attachToService to establish a new connection to the Gamma Service. Please
 * be advised that there will be absolutely no guarantee for any Gamma API
 * function (except #gc_attachToService/gc_detachFromService) to work as
 * expected, after the corruption state has been reached.
 *
 * The following code sample shows how to attach to the service:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 *
 * //Use default settings for port and timeout.
 * returnValue = gc_attachToService( 0, 0 );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gc_attachToService() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @note    This function is not multithread safe.
 * @note    This function is not safe to call in an multithread environment if
 *          a parallel thread allocates memory!
 *
 * @param[in] port      The RPC port to use to connect to the service. If
 *                      this option is set to 0 a default port will be used
 *                      and no further configurations are required. Otherwise
 *                      the service must be configured to use the same port
 *                      as the attach!
 * @param[in] timeoutMS Specifies the communication timeout, for connecting to the
 *                      Gamma Service.
 *                      If it's set to 0 the the attach will wait forever.
 *                      All other values are interpreted as milliseconds to wait
 *                      for the service to answer.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_ALREADY \n
 *          #gc_ERROR_ATTACH_FAILED \n
 *          #gc_ERROR_ATTACH_CORRUPTED
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_attachToService( const uint16_t port,
                    const uint32_t timeoutMS );

/**
 * Same as #gc_attachToService but with the option to specify a user-defined
 * task name.
 *
 * The difference between #gc_attachToService and this function is that former
 * will default the task name to "PID_XXX", whereas this function lets the user
 * define the name of the attached task object.
 *
 * @param[in] port      The RPC port to use to connect to the service. If
 *                      this option is set to 0 a default port will be used
 *                      and no further configurations are required. Otherwise
 *                      the service must be configured to use the same port
 *                      as the attach!
 * @param[in] timeoutMS Specifies the communication timeout. It is used in the
 *                      beginning as a maximum wait time for the service to
 *                      respond to the connection request and latter as the
 *                      timeout for all RPCs.
 *                      If it's set to 0 the the attach will wait forever
 *                      for the first connection response and all latter
 *                      RPC.
 *                      All other values are interpreted as milliseconds to wait
 *                      for the service to answer.
 * @param[in] taskName  The name of the task. The same name restrictions are
 *                      applied as for every other Gamma Data Model Object.
 *                      For example:
 *                      Name:                   Valid:
 *                      1234                    No - begins with a number
 *                      A-Task-123              No - contains '-' character
 *                      A_Task_123              yes
 *                      Task123                 yes
 *                      TASK_1!                 No - Contains '!' character
 *                      If the task name is invalid the function will
 *                      return #gc_ERROR_COM_INVALID_ARGUMENT.
 *                      In addition it is not valid for two tasks to share
 *                      the same task name. If one task tries to reuse another
 *                      tasks name this function will return
 *                      #gc_ERROR_SERVICE_DUPLICATED_NAME.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          \n
 *          #gc_ERROR_ATTACH_ALREADY \n
 *          #gc_ERROR_ATTACH_FAILED \n
 *          #gc_ERROR_ATTACH_CORRUPTED \n
 *          \n
 *          #gc_ERROR_SERVICE_DUPLICATED_NAME \n
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_attachToServiceByName( const uint16_t port,
                          const uint32_t timeoutMS,
                          const char* const taskName );

/**
 * Detach from local service.
 *
 * This call will properly detach from the service and cleans up all,
 * via gc_attachToService() acquired resources.
 *
 * The following code sample shows how to detach from the service:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 *
 * returnValue = gc_detachFromService();
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gc_detachFromService() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @note    This function is not multithread safe.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          #gc_ERROR_DETACH_DONE_BUT_CON_DEAD \n
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_detachFromService( void );

/**
 * Write message to gamma service log.
 *
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;;
 * const char* const MESSAGE = "Hello Gamma";
 * const int VALUE = 100;
 *
 * gc_logMessage( gc_LOG_SEVERITY_INFO, "%s: %i\n", MESSAGE, VALUE );
 * {
 *     fprintf( stderr, "Call to gc_logMessage() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * @endcode
 *
 * @note    This function can't use window's default calling convention WINAPI
 *          (stdcall), because it contains variadic arguments. Therefore the
 *          function uses the calling convention cdecl.
 *
 * @param [in] severity      Servicety of message to log. Possible enumeration values are:
 *                               - #gc_LOG_SEVERITY_INFO
 *                               - #gc_LOG_SEVERITY_WARNING
 *                               - #gc_LOG_SEVERITY_ERROR
 *
 * @param [in] format        Printf like format string.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 */
gc_EXP gc_ErrorID gc_CALLCONV_CDECL
gc_logMessage( const gc_LogSeverity severity,
               const char* const format,
               ... ) gc_PRINTF_FMT(2, 3);

/**
 * Write message to gamma service log. But accepting a variable arguments list.
 * @see gc_logMessage
 */
gc_EXP gc_ErrorID gc_CALLCONV_CDECL
gc_logMessage_va( const gc_LogSeverity severity,
                  const char* const format,
                  va_list ap );


/**
 * Validates that the current service instance is still running and alive.
 *
 * The validation is achieved by sending the Gamma Service a hello message.
 * In case of a communication error (dead socket, halted Gamma Service) the
 * isAlive flag will be set to false.
 *
 * @note:   It's important to know that even if a gaservice instance is running
 *          but this method does return 'isAlive = false' the gaservice instance
 *          is considered to be 'dead', because it was not able to fulfill the
 *          requested in the demanded time.
 *
 * @note:   Because of the distribute environment (RPCs, messaging) a gaservice
 *          which has returned 'isAlive = false' and then 'isAlive = true' is
 *          considered dead after the first 'isAlive = false' NO MATTER WHAT
 *          HAPPENS after.
 *
 * @note:   This function will update the internal session informations, as used
 *          by ALL handles (e.g. PV, FIFO, etc.). Therefore, if 'isAlive = false'
 *          occurs the data model access of all Handles will report a dead
 *          connection!
 *
 * @param[in,out]   isAlive     True:   Service is still alive.
 *                              False:  The last attached service instance is
 *                                      no longer running.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_isServiceAlive( bool* isAlive );

/**
 * Retrieve state information from task. This function performs an RPC call to
 * the middleware. In order to use the functions a successful attach is required.
 *
 * @param [in]  taskAddress     Address of task.
 *
 * @param [out] state           Task state.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_getTaskState( const gc_Level2Address* taskAddress,
                 gc_TaskState* const state );

/**
 * Change the state of the attached task. This function performs an RPC call to
 * the middleware. In order to use the functions a successful attach is required.
 *
 * @param [in]  state           Task state.
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_setCurrentTaskState( const gc_TaskState state );


/**
 * Get state of current task.
 *
 * @param [out]  state           Task state.
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_getCurrentTaskState( gc_TaskState* const state );

#endif /* GAMMA_COMMON_CORE_H__ */
