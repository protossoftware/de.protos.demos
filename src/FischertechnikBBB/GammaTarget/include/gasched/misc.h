#ifndef GAMMA_SCHED_MISC_H__
  #define GAMMA_SCHED_MISC_H__

/**
 * @file
 *
 * @author  Copyright RST Industrie Automation GmbH
 */
/******************************************************************************
 * Header File Includes
 ******************************************************************************/
#include <gacommon/errorCodes.h>
#include <gasched/platformDependencies.h>
#include <gasched/dataTypes.h>



/******************************************************************************
 * Interface - GASCHED Library Informations
 ******************************************************************************/
/**
 * Retrieves the version of the GASCHED library.
 *
 * The following code sample shows how to retrieve the GASCHED version information:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * ga_VersionNumber versionNumer = { 0, 0, 0, 0 };
 *
 * //(1) Get the version number.
 * returnValue = gs_getVersion( &versionNumber );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gs_getVersion() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //(2) Write it onto stdout.
 * printf( "GASCHED version: %u.%u.%u.%u\n", versionNumber.major,
 *                                           versionNumber.minor,
 *                                           versionNumber.release
 *                                           versionNumber.build );
 *
 * @endcode
 *
 * @param[out]  versionNumber   Will contain the version number;
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT
 */
gs_EXP gc_ErrorID gc_CALLCONV
gs_getVersion( gc_VersionNumber* const versionNumber );


/**
 * Checks if the given scheduler exists.
 *
 * Use this function to prevalidate that a user-specified scheduler with the given
 * name of "System:SchedulerName" exists at all.
 *
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * const char* const schedulerName = ":Scheduler"
 * bool exists = false;
 *
 * //(1) Get the version number.
 * returnValue = gs_hasScheduler( schedulerName, &exists );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gs_hasScheduler() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //(2) Evaluate existence of the scheduler
 * printf( "The given scheduler '%s' does %s exist.\n", schedulerName, exists ? "", "not" );
 *
 * @endcode
 *
 *
 * @param[in]   schedulerName       Name of the scheduler of interest.
 * @param[out]  exists              will hold the status of the schedulers
 *                                  existence:
 *                                    True:  Exists
 *                                    False: Does not exist.
 *
 *                                  In case the function does not return
 *                                  gc_ERROR_SUCCESS the value of exists is
 *                                  undefined!
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT
 */
gs_EXP gc_ErrorID gc_CALLCONV
gs_hasScheduler( const char* const schedulerName,
                 bool* const exists );


#endif /* GAMMA_SCHED_MISC_H__ */
