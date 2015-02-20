#ifndef GAMMA_COMMON_ERROR_CODES_H__
  #define GAMMA_COMMON_ERROR_CODES_H__
/**
 * @file
 * Contains all error codes, used by the GAAPI.
 *
 * Whenever a function fails or succeeds it will return one of the below error
 * (status) codes.
 *
 * The main difference of the GAAPI to other C libraries is that it does not
 * use plain old C Defines for identifying error codes. This has the following
 * reasons:
 * - Maintainability. \n
 *   Define-error-codes are statically compiled into every application, using
 *   the library. This creates unnecessary compile-time dependencies, meaning
 *   whenever the library maintainer will change an error code ALL applications
 *   must be recompiled. If not the run-time behavior is undefined. \n
 *   The GAAPI avoids this issue, by supplying the developer with "Variable"
 *   error codes, meaning an error will be checked against a variable externally
 *   provided by the GAAPI. If this error code changes only the GAAPI will
 *   change but the application stays the same.
 *
 * - Usability. \n
 *   The GAAPI error codes are provide as either run-time textual
 *   representation or as a list, providing an overview of all error codes
 *   and their meaning. \n
 *   The first one allows the developer to instantly retrieve a verbose
 *   error message to identify failures and eases the process of fixing them.
 *
 * <b> Application Example </b>
 *
 * The following code shows how easily the error codes can be used to identify
 * an error in-detail:
 * @code
 * #include <gacommon/core.h>
 * #include <stdio.h>
 *
 * int main( int argc,
 *           char** argv )
 * {
 *     gc_ErrorID errorID;
 *
 *     //Attach to Gamma service
 *     if( gc_ERROR_SUCCESS.errorID != ( errorID = gc_attachToService() )
 *     {
 *         fprintf( stderr, "Call to gc_attachToService() failed.\n" );
 *         fprintf( stderr, "Error ID=%d\n", errorID );
 *         fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( errorID ) );
 *         return -1;
 *     }
 *
 *     return 0;
 * }
 * @endcode
 *
 * <b> Reading The Error Codes </b>
 *
 * For the GAAPI user the only relevant part are the #GC_DEFINE_ERROR defines.
 * The other two defines #GC_BEGIN_ERROR_SECTION and #GC_END_ERROR_SECTION
 * can be ignored.
 *
 *
 *
 * @author  (C)opyright by RST Industrie Automation GmbH
 */
/******************************************************************************
 * Header File Includes
 ******************************************************************************/
#include <gacommon/dataTypes.h>

/******************************************************************************
 * Helper Macro
 ******************************************************************************/
#ifndef GC_INTERNAL_ERROR_CODE_IMPLEMENTATION
///Only an implementation detail. Is of no relevance for the GAAPI user.
#define GC_BEGIN_ERROR_SECTION

///Only an implementation detail. Is of no relevance for the GAAPI user.
#define GC_END_ERROR_SECTION

/**
 * @param[in]   name        The name of the GAAPI error.
 * @param[in]   number      The number of the GAAPI error, as returned by all
 *                          GAAPI functions.
 * @param[in]   description The textual description of the GAAPI error.
 */
#define GC_DEFINE_ERROR( name, number, description ) \
    gc_EXP_GLOBAL const gc_Error name;

#endif

GC_BEGIN_ERROR_SECTION
/******************************************************************************
 * Error Codes: Common
 ******************************************************************************/
GC_DEFINE_ERROR( gc_ERROR_SUCCESS,
                 0,
                 "API function was successful!" )
GC_DEFINE_ERROR( gc_ERROR_COM_INVALID_ARGUMENT,
                 -1,
                 "Function unable to proceed, because of invalid argument value." )
GC_DEFINE_ERROR( gc_ERROR_COM_INTERNAL_ERROR,
                 -2,
                 "Internal processing error! Please look at the current working "
                 "directory of your launched process. If there's now a new text "
                 "file names 'rstErrorLog.txt' please send it to RST so that we "
                 "have a better traceability to fix the bug." )
GC_DEFINE_ERROR( gc_ERROR_COM_MALLOC_FAILED,
                 -3,
                 "Unable to process operation, because required memory could "
                 "not be allocated!" )
GC_DEFINE_ERROR( gc_ERROR_COM_NOT_IMPLEMENTED,
                 -4,
                 "The given function is currently not implemented or the given "
                 "parameters are currently not supported." )
GC_DEFINE_ERROR( gc_ERROR_COM_STRING_TRUNCATED,
                 -5,
                 "Unable to create the user-requested string, because the given "
                 "buffer is to small. The data in the buffer is not undefined! "
                 "Only the remaining part was truncated. Therefore it's still "
                 "safe put print the content of the buffer." )
GC_DEFINE_ERROR( gc_ERROR_COM_IO_ERROR,
                 -6,
                 "Failed to perform requested I/O operation. Is the I/O device "
                 "e.g. FILE, ... in sane state?" )
GC_DEFINE_ERROR( gc_ERROR_COM_VALUE_TRUNCATION,
                 -7,
                 "Detected potential value truncation. The conversion between "
                 "the two given types is not possible. Please check the minimum/"
                 "maximum range of source and destination." )
GC_DEFINE_ERROR( gc_ERROR_COM_BAD_STATE,
                 -8,
                 "Detected invalid logical state. Please validate, that at the "
                 "current system/API/etc. configuration supports the issued operation." )
GC_DEFINE_ERROR( gc_ERROR_COM_DEAD_CONNECTION,
                 -9,
                 "Connection to Gamma Service died. Therefore the requested operation "
                 "was unable to be performed. It's most likely that the Gamma Service "
                 "was stopped or the communication was blocked. In the former case "
                 "all information within the local data model are now in an "
                 "undefined state! Do NOT continue to process! " )
GC_DEFINE_ERROR( gc_ERROR_COM_TIMED_OUT_RPC,
                 -10,
                 "The last operation's RPC request to the Gamma Service timed out." )
GC_DEFINE_ERROR( gc_ERROR_COM_SHM_INVALID,
                 -11,
                 "The given operation requested to access a Shared Memory region "
                 "which does not exist or the user-process runs without the required "
                 "privileges. " )
GC_DEFINE_ERROR( gc_ERROR_COM_HIGH_LEVEL_INTERNAL_ERROR,
                 -12,
                 "Internal processing error within a higher level component (e.g. "
                 "C++, Python, etc.), but not within the C libraries. For more "
                 "information please read/access the higher level information "
                 "facilities." )
GC_DEFINE_ERROR( gc_ERROR_COM_SESSION_IS_DEAD,
                 -13,
                 "The access to the requested handle (PV, FIFO, etc.) can't be "
                 "processed, because the associated session with the gaservice "
                 "is no longer alive. Every gc_attachToService() will create a "
                 "new session which is only valid until gc_detachFromService() "
                 "will be called. After that all handles of this session are NO "
                 "LONGER available for access operations! Even if the function "
                 "gc_attachToService() gets recalled! In such a case a NEW "
                 "session will be created!" )


/******************************************************************************
* Error Codes: Service Attachment/Detachment
******************************************************************************/
GC_DEFINE_ERROR( gc_ERROR_ATTACH_MISSING,
                 -100,
                 "The requested API function requires a previously successful "
                 "call to gc_attachToService()" )
GC_DEFINE_ERROR( gc_ERROR_ATTACH_ALREADY,
                 -101,
                 "Unable to perform API operation, because the process is "
                 "already attached to gamma service!" )
GC_DEFINE_ERROR( gc_ERROR_ATTACH_FAILED,
                 -102,
                 "Failed to attach to gamma server. Either the service is not "
                 "running, a firewall blocks the connection or the given port "
                 "was invalid." )
GC_DEFINE_ERROR( gc_ERROR_ATTACH_CORRUPTED,
                 -103,
                 "The currently still existing attach information to the Gamma "
                 "Service are corrupted. Looks like that the Gamma Service "
                 "was shut down and restarted, but no detach was issued from "
                 "the client application. To purge the corruption please call "
                 "detach and then attach." )
GC_DEFINE_ERROR( gc_ERROR_DETACH_DONE_BUT_CON_DEAD,
                 -104,
                 "Cleaned up all internal resources, but the sending of a "
                 "'goodbye' message to the Gamma Service failed, because the "
                 "socket is dead." )

/******************************************************************************
* Error Codes: PV
******************************************************************************/
GC_DEFINE_ERROR( gc_ERROR_PV_INVALID_SYNTAX,
                 -200,
                 "Invalid PV name syntax." )
GC_DEFINE_ERROR( gc_ERROR_PV_NAME_TOO_LONG,
                 -201,
                 "The given PV name is too long!" )
GC_DEFINE_ERROR( gc_ERROR_PV_LOCK_FAILED,
                 -202,
                 "Unable to acquire lock for the given PV!" )
GC_DEFINE_ERROR( gc_ERROR_PV_UNLOCK_FAILED,
                 -203,
                 "Unable to release lock for the given PV!" )
GC_DEFINE_ERROR( gc_ERROR_PV_SIM_VALUE_SET_FAILED,
                 -204,
                 "Unable to change the simulation value of the PV! For more "
                 "information please read the service log." )
GC_DEFINE_ERROR( gc_ERROR_PV_SIM_VALUE_GET_FAILED,
                 -205,
                 "Unable to retrieve the simulation value of the PV! For more "
                 "information please read the service log." )
GC_DEFINE_ERROR( gc_ERROR_PV_INVALID_DATA_TYPE,
                 -206,
                 "The data type of the PV does not support the requested "
                 "operation." )
GC_DEFINE_ERROR( gc_ERROR_PV_META_OP_NOT_AVAILABLE,
                 -207,
                 "The given PV does not support the requested meta operation. "
                 "Please check, if the data model was configured for the given "
                 "PV to support the requested meta operation." )
GC_DEFINE_ERROR( gc_ERROR_PV_BOUND_REJECTED,
                 -208,
                 "Unable to write the requested value because it violates the "
                 "boundary conditions." )
GC_DEFINE_ERROR( gc_ERROR_PV_NO_COMMON_LOCK,
                 -209,
                 "This operation requires all given PVs to share the same lock. " )
GC_DEFINE_ERROR( gc_ERROR_PV_DATA_TYPE_MISMATCH,
                 -210,
                 "The data type of the get/put value does not match the actual "
                 "data type of the PV object. The requested operation was not "
                 "executed." )
GC_DEFINE_ERROR( gc_ERROR_PV_CLOSE_DONE_BUT_CORRUPTION,
                 -211,
                 "The memory of the PV handle was properly released, but "
                 "some internal information were no longer in a consistent "
                 "state! This is the case if the Gamma Service has been shut down "
                 "before the PV was closed." )
GC_DEFINE_ERROR( gc_ERROR_PV_FIFO_EMPTY,
                 -212,
                 "The FIFO does not contain an element to retrieve." )
GC_DEFINE_ERROR( gc_ERROR_PV_FIFO_FULL,
                 -213,
                 "The FIFO is full and therefore further elements can't be put "
                 "into it." )
GC_DEFINE_ERROR( gc_ERROR_PV_TYPE_INVALID_OPERATION,
                 -214,
                 "The PV uses a PV type (e.g. single value, fifo, etc.) which "
                 "does not support the requested operation!" )
GC_DEFINE_ERROR( gc_ERROR_PV_FIFO_WOULD_BLOCK,
                 -215,
                 "The access to the FIFO PV would block and therefore was not "
                 "carried out! Note that blocking means NOT that a parallel access "
                 "was blocked by another process, but that either for write operation "
                 "the FIFO was full or for a read operation the FIFO was empty." )
GC_DEFINE_ERROR( gc_ERROR_PV_SIG_ALREADY_ACTIVATED,
                 -216,
                 "Signaling couldn't be activated for the given PV, because it is "
                 "already active! If this is okay or a is an real error does "
                 "depend on your concrete use case!" )
GC_DEFINE_ERROR( gc_ERROR_PV_SIG_ALREADY_DEACTIVATED,
                 -217,
                 "Signaling couldn't be deactivated for the given PV, because it is "
                 "already deactived! If this is okay or a is an real error does "
                 "depend on your concrete use case!" )

/******************************************************************************
 * Error Codes: Originated from the Service (via RPC)
 ******************************************************************************/
GC_DEFINE_ERROR( gc_ERROR_SERVICE_SYSTEM_NOT_FOUND,
                 -300,
                 "Gamma Service reported: The given system was not found." )
GC_DEFINE_ERROR( gc_ERROR_SERVICE_DUPLICATED_NAME,
                 -301,
                 "Gamma Service reported: The given name does already exist. "
                 "Unable to set an alias which already exists." )
GC_DEFINE_ERROR( gc_ERROR_SERVICE_OBJECT_NOT_EXIST,
                 -302,
                 "Gamma Service reported: The given object (loop,pv,memory) "
                 "does not exist." )
GC_DEFINE_ERROR( gc_ERROR_SERVICE_NO_SUCH_HANDLE,
                 -303,
                 "Gamma Service reported: The given handle does not exist or a "
                 "handle of a different type was expected." )
GC_DEFINE_ERROR( gc_ERROR_SERVICE_BAD_BROWSING_STATE,
                 -304,
                 "Gamma Service reported: Bad Browsing state. E.g. it's not "
                 "possible access browsed data if browsing wasn't started "
                 "previously. Or a string list was set, but a index list was "
                 "requested or vice versa." )
GC_DEFINE_ERROR( gc_ERROR_SERVICE_OUT_OF_MEMORY,
                 -305,
                 "Gamma Service reported: Out of memory." )
GC_DEFINE_ERROR( gc_ERROR_SERVICE_INTERNAL_ERROR,
                 -306,
                 "Gamma Service reported: Fatal internal error. For more "
                 "information please read the log/console output of the "
                 "Gamma Service." )

/******************************************************************************
 * Error Codes: Task interface (GASCHED)
 ******************************************************************************/
GC_DEFINE_ERROR( gc_ERROR_TASK_CREATE_FAILED,
                 -400,
                 "Unable to create a task (thread). Maybe limit of threads per"
                 "process was reached or the caller does not have the required"
                 "privileges level?" )
GC_DEFINE_ERROR( gc_ERROR_TASK_WAIT_FAILED,
                 -401,
                 "Unable to wait for the given task. Has the task started yet?"
                 "Also it's not allowed to wait multiple times on the same task,"
                 "if a wait has returned with success!" )
GC_DEFINE_ERROR( gc_ERROR_TASK_WAIT_TIMEOUT,
                 -402,
                 "Waiting for the given task timed out!" )
GC_DEFINE_ERROR( gc_ERROR_TASK_KILL_FAILED,
                 -403,
                 "Killing the given task failed. Does the given thread run?" )
GC_DEFINE_ERROR( gc_ERROR_TASK_SCHED_FINISHED,
                 -404,
                 "Unable to process waitNextFrame, because the Gamma Service "
                 "Scheduler has finished operation." )
GC_DEFINE_ERROR( gc_ERROR_SCHEDULER_INVALID_STATE,
                 -405,
                 "The requested operation could not be performed, because the "
                 "Scheduler is not running in the required state!" )
GC_DEFINE_ERROR( gc_ERROR_SCHEDULER_USER_INIT_FUNCTION_FAILED,
                 -406,
                 "The user init function has returned a value not equal to 0!" )
GC_DEFINE_ERROR( gc_ERROR_SCHEDULER_USER_RUN_FUNCTION_FAILED,
                 -407,
                 "The user run function has returned a value not equal to 0!" )
GC_DEFINE_ERROR( gc_ERROR_SCHEDULER_USER_DEINIT_FUNCTION_FAILED,
                 -408,
                 "The user deinit function has returned a value not equal to 0!" )

/******************************************************************************
* Error Codes: Logging Client Interface (GALOG)
******************************************************************************/
GC_DEFINE_ERROR( gc_ERROR_CLIENT_LIB_NOT_FOUND,
                 -500,
                 "The given client type id was valid, but the library was not "
                 "found. Is the library installed in the Gamma default "
                 "installation directory?" )
GC_DEFINE_ERROR( gc_ERROR_CLIENT_SYM_NOT_FOUND,
                 -501,
                 "The client was able to open the library containing the "
                 "implementation to connect to the logging server, but the "
                 "requested symbol was not found." )
GC_DEFINE_ERROR( gc_ERROR_CLIENT_TIMED_OUT,
                 -502,
                 "Recv/Send (RPC) to the currently used Logging Plugin (not "
                 "the Gamma Service itself!) timed out." )
GC_DEFINE_ERROR( gc_ERROR_CLIENT_SOCKET_WAS_CLOSED_BY_SERVER,
                 -503,
                 "Socket was closed. Either from server or client side." )
GC_DEFINE_ERROR( gc_ERROR_CLIENT_SOCKET_RECEIVE_FAILED,
                 -504,
                  "Reception via the socket has failed." )
GC_DEFINE_ERROR( gc_ERROR_CLIENT_SOCKET_NO_SERVER_PORT,
                 -505,
                 "Unable to connect to the specified server ip and port, "
                 "because no such service is running!" )
GC_DEFINE_ERROR( gc_ERROR_CLIENT_SERVER_IS_BUSY,
                 -506,
                 "Unable to connect to the specified server because another "
                 "logging client is connected to the server!" )


GC_END_ERROR_SECTION


/******************************************************************************
 * Interface Declarations
 ******************************************************************************/
/**
 * Retrieves from the given error ID the textual STATIC description. The function is
 * safe to call with any number within the range of the gc_ErrorID data type
 * and therefore always returns a valid pointer!
 *
 * @param[in]   errorID             The ID of the error.
 *
 * @return      If the errorID was valid the corresponding error description
 *              will be returned. \n
 *              If the errorID was invalid an appropriate textual description
 *              will be returned, but never a 0 pointer.
 */
gc_EXP const char* gc_CALLCONV
gc_getErrorDescription( gc_ErrorID errorID );

/**
 * Retrieves from the current thread additional information from the error's
 * context. E.g. if function f() returns 'invalid argument' use this function
 * to get (if available) additional information of the exact cause.
 *
 * @note    Not all functions provide additional context information about the
 *          error. In such a case the returned string is emtpy.
 *
 * @note    If the previous function has returned success the value of the
 *          returned string is undefined and might refere to a previous
 *          error!
 *
 * @return  Always a string.
 *          If the length is 0 then no additional information has been
 *          provided.
 *          Otherwise the function returns a report, holding information for
 *          a) the library user to quickly fix the issue
 *          b) function/line/file information for RST, in case you need further
 *             support
 */
gc_EXP const char* gc_CALLCONV
gc_getErrorContextInfo();



#endif /* GAMMA_COMMON_ERROR_CODES_H__ */
