#ifndef GAMMA_SCHED_CONTROLLER_H__
  #define GAMMA_SCHED_CONTROLLER_H__

/**
 * @file
 *
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
 * Function Declaration
 ******************************************************************************/
/**
 * Issues an RPC for the given scheduler (either on the local or on a remote
 * system) to start scheduling and immediately returns without waiting for the
 * actual start.
 *
 * This operation does fails with #gc_ERROR_SCHEDULER_INVALID_STATE, when the
 * scheduler is not in the state #gc_SCHED_STATE_STOPPED.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 *
 * returValue = gs_startScheduling( "SystemS:Scheduler1" );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_createAction() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @note    Returns immediately after the request has been sent! To validate
 *          that the scheduler is in the appropriate run-time mode please
 *          validate this via calling #gs_getSchedulerStatistics and
 *          checking the #gc_SchedulerInfo member state.
 *
 * @param[in]   schedulerName       Name of the scheduler to start.
 * @param[in]   synchronous         If true, wait until the operation is
 *                                  finished.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_SCHEDULER_INVALID_STATE
 */
gs_EXP gc_ErrorID gc_CALLCONV
gs_startScheduling( const char* const schedulerName,
                    const bool synchronous );

/**
 * Issues an RPC for the given scheduler (either on the local or on a remote
 * system) to stop scheduling and immediately returns.
 *
 * This operation does fails with #gc_ERROR_SCHEDULER_INVALID_STATE, when the
 * scheduler is not in the state #gc_SCHED_STATE_RUNNING or #gc_SCHED_STATE_ERROR.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 *
 * returValue = gs_stopScheduling( "SystemS:Scheduler1" );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gs_stopScheduling() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @note    Returns after the scheduler has been stopped.
 *
 * @param[in]   schedulerName       Name of the scheduler to stop.
 * @param[in]   synchronous         If true, wait until the operation is
 *                                  finished.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR
 *          \n
 *          #gc_ERROR_SCHEDULER_INVALID_STATE
 */
gs_EXP gc_ErrorID gc_CALLCONV
gs_stopScheduling( const char* const schedulerName,
                   const bool synchronous );

/**
 * Issue an RPC to get scheduling statistics of the given task of the given
 * scheduler.
 *
 * @note    The
 *
 * @param[in]   schedulerName       Name of the scheduler of interest.
 * @param[out]  schedulerInfo       Behavior depends on the pointer value:
 *                                  0 == *schedulerInfo: The call will
 *                                  use #gc_SchedulerInfo_init to create a
 *                                  new info structure to store the data.
 *                                  0 != *schedulerInfo: The call will use
 *                                  #gc_SchedulerInfo_resize to ensure that
 *                                  the requested information can be stored.
 *
 *                                  To clean up the created data please use
 *                                  #gc_SchedulerInfo_free.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR
 */
gs_EXP gc_ErrorID gc_CALLCONV
gs_getSchedulerStatistics( const char* const schedulerName,
                           gc_SchedulerInfo** schedulerInfo );


/**
 * Issue an RPC to get scheduling statistics of the scheduled task (slot) of
 * the given scheduler.
 *
 * @param[in]   taskName            Scoped name of the task. E.g. "schedulerX:taskN"
 * @param[out]  taskInfo            Will hold the current scheduling information
 *                                  of the task.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR
 */
gs_EXP gc_ErrorID gc_CALLCONV
gs_getTaskStatistics( const char* const taskName,
                      gc_SchedulerSlotInfo* taskInfo );


#endif /* GAMMA_SCHED_CONTROLLER_H__ */
