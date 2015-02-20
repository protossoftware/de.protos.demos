#ifndef GAMMA_SCHED_TASK_H__
#define GAMMA_SCHED_TASK_H__

/**
 * @file
 * Specifies the Gamma Scheduling Interface.
 *
 * <h3> Overview </h3>
 *
 * A user process requires to define the following three functions and register
 * them via gs_registerTask for scheduling:
 *  - initialization (gs_initFrame)
 *  - main processing loop (gs_runFrame)
 *  - deinitialization (gs_deinitFrame)
 *
 * The initialization routine (#gs_initFrame) will be run once after scheduling
 * has been started via #gs_startScheduling.
 *
 * The deinitialization routine (#gs_deinitFrame) will be run once after
 * scheduling has been stopped. Either explicitly when the user has called
 * #gs_stopScheduling or implicitly in case of an error.
 *
 * The main processing routine (#gs_runFrame) will be run after the initialization.
 * The first frame number will be 1. The initialization and deinitialization
 * routines are not counted!
 *
 * The three routines are executing in a thread context. Therefore the main
 * routine executes independently of them.
 *
 * <h3> Error Propagation </h3>
 *
 * Whenever one of the functions, registered via #gs_task_register reports an
 * error the Gamma Service will log this and the scheduling of the corresponding
 * tasks stops. The user-application is able to retrieve the execution state
 * by calling #gs_task_getStatistics.
 *
 * It's important to distinguish the previously mentioned user-defined errors,
 * as returned by #gs_initFrame, #gs_runFrame and #gs_deinitFrame and Gamma
 * Scheduling errors, returned from the API functions.
 *
 * The API error codes are only returned from the API function calls.
 * The user-defined error codes are only accessible via the structure
 * #gs_TaskStatistics, which in turn will be created/updated via calls to
 * #gs_task_getStatistics and via #gs_task_wait. For more information
 * please read the API documentation of these API functions.
 *
 * <h3> Sample </h3>
 *
 * For brevity this sample does <b>not</b> check error codes. Don't do this
 * in production code!
 *
 * @code
 * #include <stdio.h>
 * #include <unistd.h>

 * #include <gasched/task.h>
 * #include <gasched/controller.h>
 * #include <gasched/sched.h>
 *
 *
 * //this is the real user data which is accessible via the userData argument.
 * typedef struct Data
 * {
 *   int x;
 *   double d;
 *  //etc.
 * } Data;
 * int32_t init( void* userData )
 * {
 *  //Setup all required resources.
 *  return 0;
 * }
 *
 * int32_t deinit( void* userData )
 * {
 *  //Release all acquired resources and set system in a well-defined state.
 *  return 0;
 * }
 *
 * int32_t run( void* userData,
 *              gs_Task taskHandle,
 *              const uint32_t* frameNumber )
 * {
 *     Data* data = (Data*)userData;
 *
 *     printf( "Running in frame %u\n", *frameNumber );
 *
 *     //Skip every 2nd frame
 *     gs_task_waitNextFrame( taskHandle, 2 );
 *     return 0;
 *  }
 *
 *
 *
 * int main()
 * {
 *      Data data;
 *      gs_Task handle;
 *      gs_TaskStatistics statistics;
 *
 *      //local scheduler (must match the name as set in the XML config file)
 *      const char* const schedulerName = ":scheduler1";
 *      const char* const taskName = "task1";
 *
 *      //Register the task.
 *      gs_task_register( &handle, taskName, &data, &init, &run, &deinit );
 *
 *
 *      //The registered task waits for the start of the scheduling.
 *      //Start scheduling.
 *      gs_startScheduling( schedulerName );
 *
 *      //Scheduling is now running. sleep a little bit...
 *      usleep( 10*1000L*1000L);
 *
 *      //Stop scheduling
 *      gs_stopScheduling( schedulerName );
 *
 *      //Wait for the task to finish (either by error or by success)
 *      gs_task_wait( handle, 0, &statistics );
 *
 *      printf( "Task's state: %u\n", statistics.state );
 *      printf( "Task's init error code: %u\n", statistics.errorCodes.init );
 *      printf( "Task's run error code: %u\n", statistics.errorCodes.run );
 *      printf( "Task's deinit error code: %u\n", statistics.errorCodes.deinit );
 *
 *
 *      //Clean up the resources acquired by the task.
 *      gs_task_unregister( &handle );
 *
 *      return 0;
 * }
 * @endcode
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
 * Registers a task with the Gamma service for scheduling.
 *
 * The user-defined error codes, returned from the callbacks (initFrame, runFrame,
 * and deinitFrame) determine how long the task will run and which
 * callbacks will be called. The following table gives an overview:
 *
 * <pre>
 * Callback:     Failure:   Action:
 * =============================================================================
 * initFrame     No         Continue with runFrame.
 * runFrame      No         Depending on the scheduler operation state either
 *                          continue with another call to runFrame or, if
 *                          the scheduler is going to stop the task continues
 *                          with deinitFrame.
 * deinitFrame    No        Scheduling done. End processing.
 * initFrame      Yes       Abort processing and stop. Don't call deinitFrame
 *                          because initFrame was never completed successfully.
 * runFrame       Yes       Call deinitFrame direclty without waiting for the
 *                          next scheduling cycle/frame. Further processing will
 *                          be aborted.
 * deinitFrame    yes       Scheduling already done. Error will be reported and
 *                          processing ends.
 *
 * </pre>
 * Note that after initFrame was called successfully the clean-up callback
 * deinitFrame will be called always.
 *
 * @param[out]  task            Handle to the registered task. Required for
 *                              cleanup.
 * @param[in]   taskName        Scoped name of the task. E.g. "schedulerX:TaskY"
 * @param[in]   userData        User data to specify. Will be forwarded to the
 *                              initTAsk, runFrame and deinitFrame function callbacks.
 *                              Optional.
 * @param[in]   initFrame       Pointer to callback for init. Mandatory.
 * @param[in]   runFrame        Pointer to callback for every frame frame. Mandatory.
 * @param[in]   deinitFrame     Pointer to callback for deinit. Mandatory.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR
 */
gs_EXP gc_ErrorID gc_CALLCONV
gs_task_register( gs_Task* const task,
                  const char* const taskName,
                  void* const userData,
                  const gs_initFrame initFrame,
                  const gs_runFrame runFrame,
                  const gs_deinitFrame deinitFrame );



/**
 * IMPORTANT:
 * The function
 *     gs_EXP gc_ErrorID gc_CALLCONV
 *     gs_task_unregister( gs_Task* task )
 *
 * has been removed from with v3.0.0 of this library! See changelog_gasched.txt.
 */

/**
 * Waits for the registered task to finish scheduling.
 *
 * User-defined error codes, returned from the callbacks are separately handled
 * (see gs_TaskStatistics::errorCode). Therefore this function will only return
 * error codes which are completely independent of the user-provided logic
 * within the callbacks!
 *
 * Use this function to ensure that the given task is no longer running and
 * all it's associated resources can be safely freed via gs_unregisterTask.
 *
 * It's <b>not</b> safe to call this function again after the previous call
 * has returned with success. In such a case the function will return
 * gc_ERROR_TASK_WAIT_FAILED.errorID. Also, if the task didn't even start in
 * the first place the same error will be returned.
 *
 * If the call will time out it's okay to recall the function until the processing
 * of the task has finished.
 *
 * @note        This function is not MT safe.
 *
 * @note        Do NOT call this function from any of the task callbacks.
 *              Otherwise scheduling will cause a deadlock and you will get
 *              an internal error!
 *
 * @param[in]   task            Task handle to wait for. If the function
 *                              successfully completes the internal resources
 *                              of the task object will released and the given
 *                              handle will be set to 0.
 * @param[in]   timeoutMS       Wait timeout in ms. 0 means eternity.
 * @param[out]  statistics      If the function has returned without an API error
 *                              task-specific statics are stored here.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_TASK_WAIT_FAILED \n
 *          #gc_ERROR_TASK_WAIT_TIMEOUT
 */
gs_EXP gc_ErrorID gc_CALLCONV
gs_task_wait( gs_Task* task,
              const uint32_t timeoutMS,
              gs_TaskStatistics* const statistics );

/**
 * Stops the execution of the task, independently of the the gascheduler state.
 *
 * Use this function, instead of #gs_task_wait(...), if you want to directly
 * stop scheduling for a single task, without affecting the scheduler and all
 * other tasks.
 *
 * Note that if you stop a task which has already been stopped you will get
 * an invalid argument error, because stop will also cleanup the acquired
 * resources of the task and then resets the task handle.
 *
 * @code
 * //Precondition:
 * //1. The task has been registered already.
 * //2. The scheduler is already running.
 *
 * //Here some time will pass and the task does process it's routines.
 * //Now the use-case scenario requires just to stop a single task without
 * //affecting the scheduler and all other tasks. Therefore, the following
 * //stop and cleanup commands are used.
 * //Note that the parameter signature is the same as #gs_task_wait.
 * gs_TaskStatistics statistics;
 * returnValue = gs_task_stop( &task, 10000, &statistics );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gs_task_stop() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //The cleanup (same as when #gs_task_wai is used)
 * returnValue = gs_task_unregister( &task );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gs_task_unregister() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * @endcode
 *
 *
 * @note        This function is not MT safe.
 *
 * @note        Do NOT call this function from any of the task callbacks.
 *              Otherwise scheduling will cause a deadlock and you will get
 *              an internal error!
 *
 * @param[in]   task            Task handle to stop for. If the function
 *                              successfully completes the internal resources
 *                              of the task object will released and the given
 *                              handle will be set to 0.
 * @param[out]  statistics      If the function has returned without an API error
 *                              task-specific statics are stored here.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_TASK_WAIT_FAILED \n
 *          #gc_ERROR_TASK_WAIT_TIMEOUT
 */
gs_EXP gc_ErrorID gc_CALLCONV
gs_task_stop( gs_Task* task,
              gs_TaskStatistics* const statistics );

/**
 * Retrieves the current statistics of the given task.
 *
 * @param[in]   task        The task of interest.
 * @param[out]  statistics  Will contain the task statistics.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT
 */
gs_EXP gc_ErrorID gc_CALLCONV
gs_task_getStatistics( const gs_ConstTask task,
                       gs_TaskStatistics* const statistics );

/**
 * Waits for the next frame in the current task. Use this function within the
 * runFrame callback (see gs_registerTask). If this function is called from any
 * other context the execution will be halted until the next frame.
 *
 * The execution of the frame will continue after this function!
 *
 * If this function fails its very likely that the complete scheduling of the
 * task will be corrupted, because this function operates on the same
 * synchronization primitives! The worst case is that after this function has
 * failed the run frame will block forever!
 *
 * @note    If this function gets called when the Scheduler has finished
 *          it will return with an error of #gc_ERROR_TASK_SCHED_FINISHED!
 *
 * @param[in]   task            Handle of the task.
 * @param[in]   framesToWait    Number of frames to wait. If 0 is given
 *                              no wait will occur and the function will
 *                              immediately return with success.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_TASK_SCHED_FINISHED
 */
gs_EXP gc_ErrorID gc_CALLCONV
gs_task_waitNextFrame( const gs_Task task,
                       const uint32_t framesToWait );





#endif /* GAMMA_SCHED_TASK_H__ */
