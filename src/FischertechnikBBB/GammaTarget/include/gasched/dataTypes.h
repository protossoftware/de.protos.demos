#ifndef GAMMA_SCHED_DATA_TYPES_H__
    #define GAMMA_SCHED_DATA_TYPES_H__
/**
 * @file
 * Contains all GASCHED-specific data types.
 *
 * @note    All enums are considered to be of type 'int'.
 *
 * @author  (C)opyright since 2003 by RST Industrie-Automation GmbH
 */
/******************************************************************************
 * Header File Includes
 ******************************************************************************/
#include <gacommon/dataTypes.h>


/******************************************************************************
 * Other Types
 ******************************************************************************/
/**
 * The current state of the task under schedule.
 */
typedef enum gs_TaskState
{
    ///Registration was successful and the task waits for the 'go' from the
    ///scheduler.
    gs_TASK_STATE_WAIT_FOR_SCHED_START = 0,

    /**
     * Task has successfully and without any error finished scheduling.
     *
     * This state will be reached when either:
     *  a) The scheduler has been stopped.
     *  b) The task has been stopped from further scheduling (see # gs_task_stop)
     */
    gs_TASK_STATE_WAIT_FOR_SCHED_DONE = 1,

    ///Task is active and is currently processing the gs_initTask callback.
    gs_TASK_STATE_DOING_INIT = 2,

    ///Task is active and is currently processing the gs_runFrame callback.
    gs_TASK_STATE_DOING_RUN_CYCLE = 3,

    ///Task is active and is currently processing the gs_deinitTask callback.
    gs_TASK_STATE_DOING_DEINIT = 4,

    ///Task has stopped and reported an error from gs_initFrame callback.
    gs_TASK_STATE_FAILED_INIT = 5,

    ///Task has stopped and reported an error from gs_runFrame callback.
    gs_TASK_STATE_FAILED_RUN_CYCLE = 6,

    ///Task has stopped and reported an error from gs_deinitFrame callback.
    gs_TASK_STATE_FAILED_DEINIT = 7,
} gs_TaskState;

/**
 * Contains statistics of the scheduled task.
 */
typedef struct gs_TaskStatistics
{
    gs_TaskState state;
    struct
    {
        int32_t init;
        int32_t run;
        int32_t deinit;
    } errorCodes;     ///< The return value of each callback must be stored separately
                      ///< Otherwise, if runFrame fails and also deinitFrame one error
                      ///< code will be swallowed/overwritten!

    ///From the schedulers point of view the task is always handled as a
    ///slot object and therefore it holds all the scheduling information.
    gc_SchedulerSlotInfo info;
} gs_TaskStatistics;


typedef struct Task* gs_Task;
typedef const struct Task* gs_ConstTask;


/**
 * This function will be called by the scheduling before the very first frame.
 * If initialization fails the function itself must release all resources, because
 * the gs_deinitTask will be called only after gs_initTask was successful.
 *
 * @param[in]   userData    User-specified data.
 *
 * @return  0:      Success
 *          !=0:    Error to aboard.
 */
typedef int32_t (*gs_initFrame)( void* userData );

/**
 * This function will be called for every scheduling frame after the initialization
 * was successful.
 *
 * @param[in]   userData        User-specific data.
 * @param[in]   taskHandle      The handle of the task.
 * @param[in]   frameNumber     The current scheduling frame number. The first
 *                              frame has the number 0. The init and deinit
 *                              frames will not counted!
 *
 * @return  0:      Success
 *          !=0:    Error to aboard.
 */
typedef int32_t (*gs_runFrame)( void* userData,
                                gs_Task taskHandle,
                                const uint32_t* frameNumber );

/**
 * This function will be called when scheduling ends. Thats the case for:
 *  - An error has occurred after the initialization was successful.
 *
 *  - Maximum number of scheduling frames have been reached and scheduling
 *    shuts down.
 *
 * @param[in]   userData    User-set data.
 *
 * @return  0:      Success
 *          !=0:    Error to aboard.
 */
typedef int32_t (*gs_deinitFrame)( void* userData );

#endif /* GAMMA_SCHED_DATA_TYPES_H__ */

