#ifndef GAMMA_COMMON_DATA_TYPES_H__
    #define GAMMA_COMMON_DATA_TYPES_H__
/**
 * @file
 * Contains all GACOMMON-specific data types.
 *
 * @note    All enums are considered to be of type 'int'.
 *
 * @author  (C)opyright since 2003 by RST Industrie-Automation GmbH
 */
/******************************************************************************
 * Header File Includes
 ******************************************************************************/
#include <gacommon/platformDependencies.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


/******************************************************************************
 * Error Types
 ******************************************************************************/
///All GACOMMON functions return this ID to identify an error.
typedef int32_t gc_ErrorID;

/**
 * All GACOMMON errors are contained within a set of this types.
 * The list of all GACOMMON errors is specified in the header file
 * gaapi/errorCodes.h.
 */
typedef struct gc_Error
{
    ///The ID of the GACOMMON error.
    gc_ErrorID errorID;

    ///The textual description of the GACOMMON error.
    const char* description;
} gc_Error;


/******************************************************************************
 * Common Types
 ******************************************************************************/
/**
 * Gamma-specific abstraction of timespec, because not on all platforms this
 * struct is available.
 *
 * @note    Don't confuse this type with GALOG's gl_Timespec. The GACOMMON
 *          version is an abstraction of the timespec as used by the native
 *          timespec of some OS. The GALOG's version is an enhancement, using
 *          unified 64 bit fields!
 */
typedef struct gc_Timespec
{
    time_t tv_sec;  /* seconds */
    long tv_nsec;   /* nanoseconds */
} gc_Timespec;

/**
 *
 */
typedef union gc_Timestamp
{
    ///Generic timestamp.
    uint64_t        timestamp;

    ///Abstraction of a 32 bit timespec.
    struct
    {
        uint32_t    seconds;
        uint32_t    nanoseconds;
    };

} gc_Timestamp;


typedef char gc_String128[128];         ///< Generic 128 byte long string.
typedef char gc_String256[256];         ///< Generic 256 byte long string.
typedef char gc_String512[512];         ///< Generic 512 byte long string.
typedef char gc_String1K[1024];         ///< Generic 1K byte long string.


/**
 * Represents numeric data values.
 */
typedef union gc_NumericValue
{
    int8_t sint8;       ///< 8 bit signed
    uint8_t uint8;      ///< 8 bit unsigned
    int16_t sint16;     ///< 16 bit signed
    uint16_t uint16;    ///< 16 bit unsigned
    int32_t sint32;     ///< 32 bit signed
    uint32_t uint32;    ///< 32 bit unsigned
    int64_t sint64;     ///< 64 bit signed
    uint64_t uint64;    ///< 64 bit unsigned
    float ieee32;       ///< 32 bit floating point
    double ieee64;      ///< 64 bit floating point
} gc_NumericValue;

///All available data types for a PV.
typedef enum gc_DataType
{
    //Numeric data types.
    gc_DATA_TYPE_SINT_8 = 0,    ///< 8 bit signed
    gc_DATA_TYPE_UINT_8 = 1,    ///< 8 bit unsigned
    gc_DATA_TYPE_SINT_16 = 2,   ///< 16 bit signed
    gc_DATA_TYPE_UINT_16 = 3,   ///< 16 bit unsigned
    gc_DATA_TYPE_SINT_32 = 4,   ///< 32 bit signed
    gc_DATA_TYPE_UINT_32 = 5,   ///< 32 bit unsigned
    gc_DATA_TYPE_SINT_64 = 6,   ///< 64 bit signed
    gc_DATA_TYPE_UINT_64 = 7,   ///< 64 bit unsigned
    gc_DATA_TYPE_IEEE_32 = 8,   ///< 32 bit floating point
    gc_DATA_TYPE_IEEE_64 = 9,   ///< 64 bit floating point

    //Binary (container) data types.
    gc_DATA_TYPE_STRING = 10,   ///< string
    gc_DATA_TYPE_BLOB = 11,     ///< Binary Large Object

    gc_DATA_TYPE_INVALID = 0xFF ///< Should never occur!
} gc_DataType;

/**
 * Checks if the given data type is valid.
 */
#define gc_DataType_isValid( dataType ) \
    ( gc_DATA_TYPE_SINT_8 <= (dataType) && \
      gc_DATA_TYPE_BLOB >= (dataType) )

/**
 * Checks if the given data type is a numeric one.
 */
#define gc_DataType_isNumeric( dataType ) \
    ( gc_DATA_TYPE_SINT_8 <= (dataType) && \
      gc_DATA_TYPE_IEEE_64 >= (dataType) )

/**
 * Checks if the given data type is a complex one.
 */
#define gc_DataType_isComplex( dataType ) \
    ( gc_DATA_TYPE_STRING == (dataType) || \
      gc_DATA_TYPE_BLOB == (dataType) )


/**
 * Specifies the field type of a PV.\n
 * A PV comprises several internal data fields to implement the API requirements.
 */
typedef enum gc_PVFieldType
{
    ///Direct access to the PV value with meta functionalities.
    gc_PV_FIELD_VALUE = 1,

    ///Direct access to the original PV value without meta functionalities
    gc_PV_FIELD_ORIG = 2,

    ///Direct access to the simulation value of the PV.
    ///Only works if simulation is at least available (must not be active!).
    gc_PV_FIELD_SIM = 3,

    ///Direct access to the minimum value of the PV.
    ///Only works if min boundary is at least available (must not be active!).
    gc_PV_FIELD_MIN = 4,

    ///Direct access to the maximum value of the PV.
    ///Only works if max boundary is at least available (must not be active!).
    gc_PV_FIELD_MAX = 5
} gc_PVFieldType;


/**
 * Checks if the given PVFieldType is valid.
 */
#define gc_PVFieldType_isValid( fieldType ) \
    ( gc_PV_FIELD_VALUE == (fieldType) || \
      gc_PV_FIELD_ORIG == (fieldType) || \
      gc_PV_FIELD_SIM == (fieldType) || \
      gc_PV_FIELD_MIN == (fieldType) || \
      gc_PV_FIELD_MAX == (fieldType) )


/**
 * Specifies the meta type of an opened  PV.
 *
 */

typedef enum gc_MetaType
{
    gc_META_TYPE_LOGGING = 0,       ///< Current meta type is logging.
    gc_META_TYPE_SIMULATION = 1,    ///< Current meta type is simulation.
    gc_META_TYPE_MINIMUM = 2,       ///< Current meta type is minimum.
    gc_META_TYPE_MAXIMUM = 3,       ///< Current meta type is maximum.
} gc_MetaType;

#define gc_MetaType_isValid( metaType ) \
    ( gc_META_TYPE_LOGGING == (metaType) || \
      gc_META_TYPE_SIMULATION == (metaType) || \
      gc_META_TYPE_MINIMUM == (metaType) || \
      gc_META_TYPE_MAXIMUM == (metaType) )

/**
 * Specifies the severity when logging to the gamma service.
 */
typedef enum gc_LogSeverity
{
    gc_LOG_SEVERITY_INFO = 1,       ///< Log informational message
    gc_LOG_SEVERITY_WARNING = 2,    ///< Log warning message
    gc_LOG_SEVERITY_ERROR = 3       ///< Log error message
} gc_LogSeverity;

/**
 * Checks if the given severity is valid.
 */
#define gc_LogSeverity_isValid( severity )      \
    ( gc_LOG_SEVERITY_INFO == (severity) ||     \
      gc_LOG_SEVERITY_WARNING == (severity) ||  \
      gc_LOG_SEVERITY_ERROR == (severity) )
/**
 * These flags contains specific groups for every meta functionality.
 *
 * The memberscan be used directly,
 * or when specified by the GAAPI functions are or'ed
 * into a #gc_Flags32Bit value.
 *
 *
 * Sample Configurations:
 * @code
 * gc_Flags32Bit x;
 *
 * //Valid combinations
 * x = gc_META_FLAG_LOG_ON_SYNC_CHANGE |
 *     gc_META_FLAG_SIM_ON |
 *     gc_META_FLAG_MIN_OFF |
 *     gc_META_FLAG_MAX_OFF |
 *     gc_META_FLAG_SIG_ON_SYNC_CHANGE | gc_META_FLAG_SIG_ON_PRIORITY_MIDDLE;
 *
 * x = gc_META_FLAG_LOG_ON_SYNC_CHANGE |
 *     gc_META_FLAG_SIM_ON |
 *     gc_META_FLAG_MIN_OFF |
 *     gc_META_FLAG_MAX_OFF |
 *     gc_META_FLAG_SIG_OFF;
 *
 * //Invalid combinations
 * x = gc_META_FLAG_LOG_OFF;        //Missing the other flags!
 * x = gc_META_FLAG_LOG_OFF | gc_META_FLAG_LOG_ON_SYNC_CHANGE |  //two from log group!
 *     gc_META_FLAG_SIM_ON |
 *     gc_META_FLAG_MIN_OFF |
 *     gc_META_FLAG_MAX_OFF |
 *     gc_META_FLAG_SIG_OFF;
 * @endcode
 *
 * See #ga_pv_changeMetaFunctions for the valid combinations of the flags for
 * changing them.
 *
 * Have a look at #ga_pv_getMetaConfig for how to extract the meta flags
 * from the #ga_MetaConfig.
 * The structure element flag of #ga_MetaConfig contains the MetaFlags
 *
 * @code
 * void sample( ga_PV pv )
 * {
 *     gc_ErrorID  returnValue =  gc_ERROR_SUCCESS.errorID;
 *     const char *dest = 0;
 *     const int useRPC = 1;
 *     ga_MetaConfig metaConfig;
 *
 *     ga_pv_getMetaConfig( pv, &metaConfig,useRPC );   ///< use RPC
 *     if( gc_ERROR_SUCCESS.errorID != returnValue )
 *     {
 *         fprintf( stderr, "Call to ga_pv_getMetaConfig() failed.\n" );
 *         fprintf( stderr, "Error ID=%d\n", returnValue );
 *         fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *         exit( -1 );
 *     }
 *
 *     returnValue = ga_printMetaFlags( metaConfig.flags, "\t", &dest, 0 );
 *     if( gc_ERROR_SUCCESS.errorID != returnValue )
 *     {
 *         fprintf( stderr, "Call to ga_printMetaFlags() failed.\n" );
 *         fprintf( stderr, "Error ID=%d\n", returnValue );
 *         fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *         exit( -1 );
 *     }
 *     printf( "%s\n", dest );
 *     fflush( stdout );
 *
 *     //free the GAAPI-allocated memory
 *     gc_freeMemory( (void*)dest );
 * }
 * @endcode
 *
 *
 * Only a single flag of each flag group related to:
 *
 * <ul>
 *   <li> logging, </li>
 *   <li> simulation</li>
 *   <li> minimum processing </li>
 *   <li> maximum processing </li>
 *   <li> signaling </li>
 * </ul>
 *
 * can be active at a time:
 */
typedef enum gc_MetaFlag
{

    gc_META_FLAG_LOG_NOT_AVAILABLE = 1 << 0,        ///< Not allowed to set (currently)
    gc_META_FLAG_LOG_ON_ASYNC_ALWAYS = 1 << 1,      ///< done by GAAPI (currently not implemented)
    gc_META_FLAG_LOG_ON_ASYNC_CHANGE = 1 << 2,      ///< done by GAAPI (currently not implemented)

    /**
     * Logging is done within the configured loop cycle of the gaservice.
     *
     * @note    In case the PV is of PV type FIFO this meta functionality
     *          will cause the gaservice to create two FIFOs to support
     *          logging the writes. Therefore the actual FIFO size is at
     *          least N and it's possible that a user-process can write more
     *          than N values into the FIFO(, because of this double buffering).
     *          Please do NOT rely on this behavior, because this information is
     *          only provided to explain why (sometimes) it's possible to write
     *          more than N values into a FIFO! Therefore always assume that the
     *          maximum size of a FIFO is N and understand why sometimes this
     *          constraint did not occur.
     */
    gc_META_FLAG_LOG_ON_SYNC_CHANGE = 1 << 3,       ///< done by service
    gc_META_FLAG_LOG_OFF = 1 << 4,                  ///< deactivate logging

    gc_META_FLAG_SIM_NOT_AVAILABLE = 1 << 5,        ///< Not allowed to set (currently)
    gc_META_FLAG_SIM_ON = 1 << 6,                   ///< activate simulation
    gc_META_FLAG_SIM_OFF = 1 << 7,                  ///< deactivate simulation

    gc_META_FLAG_MIN_NOT_AVAILABLE = 1 << 8,        ///< Not allowed to set (currently)
    gc_META_FLAG_MIN_ON_REJECT = 1 << 9,
    gc_META_FLAG_MIN_ON_CHANGE_TO_BORDER = 1 << 10,
    gc_META_FLAG_MIN_OFF = 1 << 11,                 ///< deactivate Mimimum processing

    gc_META_FLAG_MAX_NOT_AVAILABLE = 1 << 12,       ///< Not allowed to set (currently)
    gc_META_FLAG_MAX_ON_REJECT = 1 << 13,
    gc_META_FLAG_MAX_ON_CHANGE_TO_BORDER = 1 << 14,
    gc_META_FLAG_MAX_OFF = 1 << 15,                 ///< deactivate Maximum processing

    gc_META_FLAG_SIG_NOT_AVAILABLE = 1 << 16,        ///< Not allowed to set (currently)
    gc_META_FLAG_SIG_ON_SYNC_CHANGE = 1 << 19,       ///< Signal synchronous to the service cycle

    ///If SIG_ON was set it's required to define the priority by or'ing one of
    ///these three flags too! If only the priority is given but no SIG_ON flag
    ///the priority will be ignored at all and no change of signaling will
    ///take place!
    gc_META_FLAG_SIG_ON_PRIORITY_LOW = 1 << 20,     ///< use low  priority
    gc_META_FLAG_SIG_ON_PRIORITY_MIDDLE = 1 << 21,  ///< use mid  priority
    gc_META_FLAG_SIG_ON_PRIORITY_HIGH = 1 << 22,    ///< use high  priority
    gc_META_FLAG_SIG_OFF = 1 << 23,                 ///< deactivate signaling

    ///Use this to deactivate all meta functionalities of a PV.
    ///If the PV type does not support one of the meta flags it'll be ignored.
    gc_META_FLAG_ALL_OFF = gc_META_FLAG_LOG_OFF |
                           gc_META_FLAG_SIM_OFF |
                           gc_META_FLAG_MIN_OFF |
                           gc_META_FLAG_MAX_OFF |
                           gc_META_FLAG_SIG_OFF
} gc_MetaFlag;

/**
 * Checks if the given metaFlag is valid.
 */
#define gc_MetaFlag_isValid( metaFlag) \
    ( gc_META_FLAG_LOG_NOT_AVAILABLE == (metaFlag) || \
      gc_META_FLAG_LOG_ON_ASYNC_ALWAYS == (metaFlag) || \
      gc_META_FLAG_LOG_ON_ASYNC_CHANGE == (metaFlag) || \
      gc_META_FLAG_LOG_ON_SYNC_CHANGE == (metaFlag) || \
      gc_META_FLAG_LOG_OFF == (metaFlag) || \
      \
      gc_META_FLAG_SIM_NOT_AVAILABLE == (metaFlag) || \
      gc_META_FLAG_SIM_ON == (metaFlag) || \
      gc_META_FLAG_SIM_OFF == (metaFlag) || \
      \
      gc_META_FLAG_MIN_NOT_AVAILABLE == (metaFlag) || \
      gc_META_FLAG_MIN_ON_REJECT == (metaFlag) || \
      gc_META_FLAG_MIN_ON_CHANGE_TO_BORDER == (metaFlag) || \
      gc_META_FLAG_MIN_OFF == (metaFlag) || \
      \
      gc_META_FLAG_MAX_NOT_AVAILABLE == (metaFlag) || \
      gc_META_FLAG_MAX_ON_REJECT == (metaFlag) || \
      gc_META_FLAG_MAX_ON_CHANGE_TO_BORDER == (metaFlag) || \
      gc_META_FLAG_MAX_OFF == (metaFlag) || \
      \
      gc_META_FLAG_SIG_NOT_AVAILABLE == (metaFlag) || \
      gc_META_FLAG_SIG_ON_SYNC_CHANGE == (metaFlag) || \
      gc_META_FLAG_SIG_ON_PRIORITY_LOW == (metaFlag) || \
      gc_META_FLAG_SIG_ON_PRIORITY_MIDDLE == (metaFlag) || \
      gc_META_FLAG_SIG_ON_PRIORITY_HIGH == (metaFlag) || \
      gc_META_FLAG_SIG_OFF == (metaFlag) || \
      \
      gc_META_FLAG_ALL_OFF == (metaFlag) )


/**
 * Contains extraction masks for or'ed enumerators.
 */
enum
{
    /**************************************************************************
     * Meta Flag Masks
     **************************************************************************/

    ///Mask for excluding Logging options.
    gc_META_FLAG_LOG_MASK = gc_META_FLAG_LOG_NOT_AVAILABLE |
                            gc_META_FLAG_LOG_ON_ASYNC_ALWAYS |
                            gc_META_FLAG_LOG_ON_ASYNC_CHANGE |
                            gc_META_FLAG_LOG_ON_SYNC_CHANGE |
                            gc_META_FLAG_LOG_OFF,

    ///Mask for excluding Simulation options.
    gc_META_FLAG_SIM_MASK = gc_META_FLAG_SIM_NOT_AVAILABLE |
                            gc_META_FLAG_SIM_ON |
                            gc_META_FLAG_SIM_OFF,

    ///Mask for excluding Minimum options.
    gc_META_FLAG_MIN_MASK = gc_META_FLAG_MIN_NOT_AVAILABLE |
                            gc_META_FLAG_MIN_ON_REJECT |
                            gc_META_FLAG_MIN_ON_CHANGE_TO_BORDER |
                            gc_META_FLAG_MIN_OFF,

    ///Mask for excluding Maximum options.
    gc_META_FLAG_MAX_MASK = gc_META_FLAG_MAX_NOT_AVAILABLE |
                            gc_META_FLAG_MAX_ON_REJECT |
                            gc_META_FLAG_MAX_ON_CHANGE_TO_BORDER |
                            gc_META_FLAG_MAX_OFF,

    ///Mask for excluding signaling options.
    gc_META_FLAG_SIG_MASK = gc_META_FLAG_SIG_NOT_AVAILABLE |
                            gc_META_FLAG_SIG_ON_SYNC_CHANGE |
                            gc_META_FLAG_SIG_OFF,

    ///Mask for excluding signaling priorities.
    ///These option will only be changed if the corresponding on flag was set!
    gc_META_FLAG_SIG_PRIO_MASK = gc_META_FLAG_SIG_ON_PRIORITY_LOW |
                                 gc_META_FLAG_SIG_ON_PRIORITY_MIDDLE |
                                 gc_META_FLAG_SIG_ON_PRIORITY_HIGH,
};

///Contains the version numbers of a Gamma library
typedef struct gc_VersionNumber
{
    ///Different major numbers indicate incompatibilities!
    uint32_t major;

    ///Will be increased if every new function, but library is still compatible.
    uint32_t minor;

    ///Will be increased for every bugfix.
    uint32_t release;

    ///Must be 0 for release. If not 0 a development library is used.
    uint32_t build;
} gc_VersionNumber;

typedef uint8_t gc_Flags8Bit;       ///< Generic 8 Bit flag field.
typedef uint16_t gc_Flags16Bit;     ///< Generic 16 Bit flag field.
typedef uint32_t gc_Flags32Bit;     ///< Generic 32 Bit flag field.



////// ------ Data Model Types (GADMODEL & Browsing)

/******************************************************************************
 * Basic Addressing Types
 ******************************************************************************/
typedef uint32_t    gc_SystemAddress;   ///< Address of a system.
typedef uint32_t    gc_ObjectIndex;     ///< Index of an object on a system.
typedef uintptr_t   gc_Handle;          ///< Index of generic handle.


#define gc_INVALID_SYSTEM_ADDRESS_VALUE         (0UL)
#define gc_LOCAL_SYSTEM_ADDRESS_VALUE           (0UL)

///An invalid index
#define gc_INVALID_OBJECT_INDEX                 (0xFFFFFFFFu)

// stdint.h defines UINTPTR_MAX, but only for c!!
#if __WORDSIZE == 64
    #define gc_INVALID_OFFSET_VALUE              (0xFFFFFFFFFFFFFFFFul)
#else
    #define gc_INVALID_OFFSET_VALUE              (0xFFFFFFFFu)
#endif

#define gc_INVALID_HANDLE                       (0)


typedef gc_ObjectIndex gc_LoopIndex;           ///< Index of a loop object.
typedef gc_ObjectIndex gc_ActionIndex;         ///< Index of an action object.
typedef gc_ObjectIndex gc_NodeIndex;           ///< Index of a node object.
typedef gc_ObjectIndex gc_TaskIndex;           ///< Index of a task object.
typedef gc_ObjectIndex gc_IOIndex;             ///< Index of an I/O object.
typedef gc_ObjectIndex gc_SchedulerIndex;      ///< Index of scheduler object.


typedef gc_ObjectIndex gc_MemoryIndex;         ///< Index of memory object.
typedef gc_ObjectIndex gc_LockIndex;           ///< Index of lock object.
typedef gc_ObjectIndex gc_VariableIndex;       ///< Index of variable object.
typedef gc_ObjectIndex gc_IOChannelIndex;      ///< Index of I/O channel object.
typedef gc_ObjectIndex gc_SchedulerSlotIndex;  ///< Index of scheduler slot object.

typedef gc_ObjectIndex gc_PVIndex;             ///< Index of PV object.

/**
 * Addressing structure for object with a level 2 address.
 *
 * These objects are:
 *  - node
 *  - action
 *  - loop
 *  - scheduler
 *  - I/O
 */
typedef struct gc_Level2Address
{
    gc_SystemAddress system;                    ///< Address of the system.
    gc_ObjectIndex index1;                      ///< First index.
} gc_Level2Address;

/**
 * Addressing structure for object with a level 3 address.
 *
 * These objects are:
 *  - memory
 */
typedef struct gc_Level3Address
{
    gc_SystemAddress system;                    ///< Address of the system.
    gc_ObjectIndex index1;                      ///< First index.
    gc_ObjectIndex index2;                      ///< Second index.
} gc_Level3Address;

/**
 * Addressing structure for object with a level 4 address.
 *
 * These objects are:
 *  - group
 */
typedef struct gc_Level4Address
{
    gc_SystemAddress system;                    ///< Address of the system.
    gc_ObjectIndex index1;                      ///< First index.
    gc_ObjectIndex index2;                      ///< Second index.
    gc_ObjectIndex index3;                      ///< Third index.
} gc_Level4Address;

/**
 * Addressing structure for object with a level 5 address.
 *
 * These objects are:
 *  - PVArray
 */
typedef struct gc_Level5Address
{
    gc_SystemAddress system;                    ///< Address of the system.
    gc_ObjectIndex index1;                      ///< First index.
    gc_ObjectIndex index2;                      ///< Second index.
    gc_ObjectIndex index3;                      ///< Third index.
    gc_ObjectIndex index4;                      ///< Forth index.
} gc_Level5Address;

/**
 * Addressing structure for object with a level 6 address.
 *
 * These objects are:
 *  - Alias of PVArray
 */
typedef struct gc_Level6Address
{
    gc_SystemAddress system;                    ///< Address of the system.
    gc_ObjectIndex index1;                      ///< First index.
    gc_ObjectIndex index2;                      ///< Second index.
    gc_ObjectIndex index3;                      ///< Third index.
    gc_ObjectIndex index4;                      ///< Forth index.
    gc_ObjectIndex index5;                      ///< Fifth index.
} gc_Level6Address;

/******************************************************************************
 * System Types
 ******************************************************************************/
typedef uint32_t gc_ProjectID[4];               ///< Unique ID of a project

typedef struct gc_SystemInfo
{
    gc_SystemAddress address;                   ///< The address of the system.
    gc_ProjectID projectID;                     ///< The project ID.
    gc_String256 name;                          ///< The name of the system.
    uint32_t clockPrecisionUsec;                ///< The configured clock precision in us.
    uint64_t startedAt;                         ///< Seconds since epoch (1.1.1970 0:00:00 +0)
} gc_SystemInfo;

/******************************************************************************
 * Loop Types
 ******************************************************************************/
/**
 * Contains the creation configuration for an loop.
 */
typedef struct gc_LoopConfig
{
    gc_String1K name;           ///< Unique name of the loop.
    bool isPersistent;          ///< Shall the loop be persistent?
    uint32_t updateCycleTicks;  ///< The cycle ticks of the loop.
} gc_LoopConfig;

/**
 * Contains the information for an already existing loop.
 */
typedef struct gc_LoopInfo
{
    gc_Level2Address address;   ///< The address of the loop.
    gc_String1K name;           ///< Unique name of the loop.
    bool isPersistent;          ///< Is the loop persistent?
    uint32_t cycleTimeUs;       ///< The cycle time of the loop.
    uint32_t minDurationUs;     ///< Minimum execution time of action.
    uint32_t maxDurationUs;     ///< Maximum execution time of action.
    uint32_t meanDurationUs;    ///< Mean execution time of action.
    uint32_t stdDevUs;          ///< Deviation of actions execution time.
} gc_LoopInfo;


/******************************************************************************
 * Action Types
 ******************************************************************************/
/**
 * Contains the creation configuration for an action.
 */
typedef struct gc_ActionConfig
{
    gc_String1K name;           ///< Unique name of the action.
    bool isPersistent;          ///< Shall the action be persistent?
} gc_ActionConfig;

/**
 * Contains the information for an already existing action.
 */
typedef struct gc_ActionInfo
{
    gc_Level2Address address;   ///< The address of the action.
    gc_String1K name;           ///< Unique name of the action.
    bool isPersistent;          ///< Persistence state of the action.
    uint32_t minDurationUs;     ///< Minimum execution time of action.
    uint32_t maxDurationUs;     ///< Maximum execution time of action.
    uint32_t meanDurationUs;    ///< Mean execution time of action.
    uint32_t stdDevUs;          ///< Deviation of actions execution time.
} gc_ActionInfo;


/******************************************************************************
 * Node Types
 ******************************************************************************/
/**
 * Contains the creation configuration for a node.
 */
typedef struct gc_NodeConfig
{
    gc_String1K name;           ///< Unique name of the node.
    bool isPersistent;          ///< Shall the node be persistent?
} gc_NodeConfig;

/**
 * Contains the information for an already existing node.
 */
typedef struct gc_NodeInfo
{
    /// The address of the node.
    gc_Level2Address address;
    gc_String1K name;           ///< Unique name of the node.
    bool isPersistent;          ///< Is the node persistent?
} gc_NodeInfo;


/******************************************************************************
 * Memory Types
 ******************************************************************************/
/**
 * Permission set for specifying the access permission of:
 *  - gc_SHMConfig
 *  - gc_MemoryInfo
 */
typedef enum gc_PermissionSet
{
    gc_PERMISSION_SET_USER_READ   = 1 << 0,
    gc_PERMISSION_SET_USER_WRITE  = 1 << 1,
    gc_PERMISSION_SET_GROUP_READ  = 1 << 2,
    gc_PERMISSION_SET_GROUP_WRITE = 1 << 3,
    gc_PERMISSION_SET_WORLD_READ  = 1 << 4,
    gc_PERMISSION_SET_WORLD_WRITE = 1 << 5,


    gc_PERMISSION_SET_ALL = gc_PERMISSION_SET_USER_READ |
                            gc_PERMISSION_SET_USER_WRITE |
                            gc_PERMISSION_SET_GROUP_READ |
                            gc_PERMISSION_SET_GROUP_WRITE |
                            gc_PERMISSION_SET_WORLD_READ |
                            gc_PERMISSION_SET_WORLD_WRITE,
} gc_PersmissionSet;


/**
 * Contains the creation configuration for a SHM (SHared Memory) region.
 */
typedef struct gc_SHMConfig
{
    gc_String1K name;           ///< Unique name of the SHM.
    bool isPersistent;          ///< Shall the node be persistent?
    uint32_t size;              ///< The size of the SHM
    uint32_t permission;        ///< Access permissions (see #gc_PermissionSet)

    /// The name of the user. If this field is blank then the user name is used
    /// under which the server has been started.
    gc_String512 user;

    /// The group of the user. If this field is blank then the user group is used
    /// under which the server has been started.
    gc_String512 group;
} gc_SHMConfig;

/**
 * Contains the information for an already existing 'abstract' memory region.
 * Currently only SHM memory regions exist and therefore no type identifier is
 * used.
 */
typedef struct gc_MemoryInfo
{
    gc_Level3Address address;   ///< The address of the memory.

    bool isPersistent;          ///< Is the memory persistent?
    uint32_t size;              ///< The maximum size the memory can have.
    uint32_t permission;        ///< Access permissions (see #gc_PermissionSet)

    gc_String512 user;          ///< The user name of the user, who owns the memory.
    gc_String512 group;         ///< The group name of the user, who owns the memory.
    gc_String512 name;          ///< The name of the memory.

    gc_String1K modelName;      ///< The name of the memory in the model.
} gc_MemoryInfo;


/******************************************************************************
 * Task Types
 ******************************************************************************/
typedef struct gc_TaskInfo
{
    gc_Level2Address address;    ///< The address of the task.

    gc_String1K name;            ///< Unique name of the task.
    uint32_t pid;                ///< The PID of the task.
    uint32_t signalNumber;       ///< The signal number.
    gc_MemoryInfo memory;        ///< This memory contains task-specific information
} gc_TaskInfo;


/******************************************************************************
 * I/O Types
 ******************************************************************************/
typedef enum gc_IOStates
{
    gc_IO_STATE_ENABLED,    ///< Hardware/Channel is enabled and ready to use
    gc_IO_STATE_DISABLED,   ///< Hardware/Channel is disabled
    gc_IO_STATE_FAULTY      ///< Hardware/Channel is defective
} gc_IOStates;

typedef struct gc_IOInfo
{
    gc_Level2Address address;           ///< The address of the I/O.

    uint32_t noInputChannels;           ///< Number of input channels.
    uint32_t noOutputChannels;          ///< Number of output channels.
    gc_IOStates state;                  ///< Current operational state of the HW.

    gc_String256 vendor;                ///< Name of Hardware vendor.
    gc_String256 description;           ///< Additional description.
    gc_String256 library;               ///< Name of the Gamma plug-in library.
    gc_String256 startParameters;       ///< Start parameters for the plug-in.
} gc_IOInfo;



/******************************************************************************
 * I/O Channel Types
 ******************************************************************************/
typedef struct gc_IOChannelInfo
{
    gc_Level3Address address;       ///< The address of the I/O.

    gc_DataType type;               ///< Data type of the I/O channel.
    bool isInputChannel;            ///< Is the I/O channel used for input (true) or output (false).
    gc_IOStates state;              ///< Current operation state of the channel.

    gc_String256 description;       ///< Additional description of the I/O channel.
} gc_IOChannelInfo;


/******************************************************************************
 * Scheduler Types
 ******************************************************************************/
typedef uint32_t gc_SchedulingTopologyItem;

/**
 * The scheduler topology consists of N x N elements, where row is always the
 * same as column (See #gc_SchedulerInfo element numSlots).
 */
typedef gc_SchedulingTopologyItem* gc_SchedulingTopology;

/**
 * Convenience macro to access the 'dynamic' linear topology array.
 *
 * @code
 * //Some scheduling topology retrieved via the browsing interface.
 * gc_SchedulingTopology topology = ... //Unknown, depends on your use case.
 * uint32_t numSlots = ...              //Unknown, depends on your use case.
 *
 * //Print the topology
 * for( uint32_t rowIndex = 0; rowIndex < numSlots; ++rowIndex )
 * {
 *     for( uint32_t columnIndex = 0; columnIndex < numSlots; ++columnIndex )
 *     {
 *         printf( "%4u ", gc_SchedulerTopology_get( topology,
 *                                                   rowIndex,
 *                                                   columnIndex,
 *                                                   numSlots ) );
 *     }
 *
 *     printf( "\n" );
 * }
 *
 * @endcode
 */
#define gc_SchedulerTopology_get( topology, \
                                  rowIndex, \
                                  columnIndex, \
                                  columnLength ) \
    (*((topology) + ((columnLength) * (rowIndex)) + (columnIndex)))


/**
 * Defines the state of the scheduler and the slots.
 */
typedef enum gc_SchedulerState
{
    gc_SCHED_STATE_STOPPED = 0,   ///< Scheduler is stopped.
    gc_SCHED_STATE_STARTING,      ///< Scheduler is calling slots initialization function.
    gc_SCHED_STATE_RUNNING,       ///< Scheduler is periodically calling slots run function.
    gc_SCHED_STATE_STOPPING,      ///< Scheduler is calling slots deinitialization function.
    gc_SCHED_STATE_ERROR,         ///< An error happened during initialization, run or cleanup.
} gc_SchedulerState;

/**
 * Convenience macro to query if the given state indicates that the scheduler
 * is still running. Note that the single gc_SCHED_STATE_RUNNING does not suffice,
 * because the startup and stopping of the slots are represented by two different
 * states!
 *
 * @param[in]   state       The state to query.
 *
 * @return      True:       State represents that the scheduler is still active.
 *              False:      State represents that the scheduler is not active.
 */
#define gc_SchedulerState_isActive( state ) \
    ( gc_SCHED_STATE_STARTING == (state) || \
      gc_SCHED_STATE_RUNNING  == (state) || \
      gc_SCHED_STATE_STOPPING == (state) )


/**
 * @note This structure places information on the heap. Therefore consider
 *       using #gc_SchedulerInfo_free to properly clear after it has been
 *       successfully retrieved from a GAMMA API function call.
 */
typedef struct gc_SchedulerInfo
{
    gc_Level2Address address;       ///< The address of the scheduler

    gc_String1K name;               ///< Unique name of the scheduler.
    bool isPersistent;              ///< Is the scheduler persistent?
    uint32_t numSlots;              ///< The number of slots to be scheduled

    ///The topology as an array.
    ///square matrix with rows=numSlots and columns=numSlots
    ///topology[row][column]
    ///For a convenient access please use #gc_SchedulerTopology_get
    gc_SchedulingTopology topology;

    /// Configuration of the scheduler.
    uint32_t cycleTicks;            ///< The schedulers cycle time in clock ticks
    uint32_t timeoutUs;             ///< Scheduling timeout. If the actual duration is
                                    ///< is higher, the scheuler will stop.
    uint32_t expectedMinUs;         ///< Minimum expected cycle duration. If the actual
                                    ///< duration is lower, the underrun counter gets incremented
    uint32_t expectedMaxUs;         ///< Maximum expected cycle duration. If the actual
                                    ///< duration is higher the underrun counter gets incremented
    uint32_t abortOnNumOverruns;    ///< Abort margin for overruns. Zero means disabled.
    uint32_t abortOnNumUnderruns;   ///< Abort margin for underruns. Zero means disabled.

    /// Statistics of the last execution.
    uint32_t minUs;                 ///< Minimum frame duration.
    uint32_t maxUs;                 ///< Maximum frame duration.
    uint32_t meanUs;                ///< Mean frame duration
    uint32_t stdDevUs;              ///< Standard deviation of frame duration.
    uint32_t numFrames;             ///< Number of executed frames.
    uint32_t overrunFrames;         ///< Number of frame duration overruns.
    uint32_t underrunFrames;        ///< Number of frame duration underruns

    /// State
    gc_SchedulerState state;        ///< The state of the scheduler

} gc_SchedulerInfo;


/******************************************************************************
 * Scheduler Slot Types
 ******************************************************************************/
typedef struct gc_SchedulerSlotInfo
{
    gc_Level3Address address;       ///< The address of the scheduler slot.

    gc_String1K name;               ///< Unique name of the scheduler slot.
    bool isAssigned;                ///< Is the slot used?

    /// Config:
    uint32_t timeoutUs;             ///< Slot scheduling timeout. If the actual duration is
                                    ///< is higher, the scheuler will stop.
    uint32_t expectedMinUs;         ///< Minimum expected slot duration. If the actual
                                    ///< duration is lower, the underrun counter gets incremented
    uint32_t expectedMaxUs;         ///< Maximum expected cycle duration. If the actual
                                    ///< duration is higher the underrun counter gets incremented
    uint32_t abortOnNumOverruns;    ///< Abort margin for overruns. Zero means disabled.
    uint32_t abortOnNumUnderruns;   ///< Abort margin for underruns. Zero means disabled.

    /// Status codes
    gc_SchedulerState state;        ///< Scheduler state of slot
    int32_t initState;              ///< Return code of initialization function call
    int32_t runState;               ///< Return code of run function call
    int32_t deinitState;            ///< Return code of cleanup function call

    /// Statistics:
    uint32_t minUs;                 ///< Minimum slot duration.
    uint32_t maxUs;                 ///< Maximum slot duration.
    uint32_t meanUs;                ///< Mean slot duration.
    uint32_t stdDevUs;              ///< Standard deviation of frame duration.
    uint32_t numFrames;             ///< Number of executed frames.
    uint32_t overrunFrames;         ///< Number of slot duration overruns.
    uint32_t underrunFrames;        ///< Number of slot duration underruns.
} gc_SchedulerSlotInfo;



/******************************************************************************
 * Group Types
 ******************************************************************************/
/**
 * Contains the creation configuration for a lock.
 */
typedef struct gc_GroupConfig
{
    gc_String1K name;           ///< Unique name of the group.
    bool isPersistent;          ///< Shall the node be persistent?
    bool isLocked;              ///< Initial state locking state of the group.
} gc_GroupConfig;

/**
 * Contains the information for an already existing lock.
 */
typedef struct gc_GroupInfo
{
    /// The address of the group.
    gc_Level4Address address;

    /// Unique name of the group.
    gc_String1K name;

    /// Address of the optionally network action
    gc_Level2Address netActionAddress;

    /// Address of the optionally signaling action
    gc_Level2Address sigActionAddress;

    /// Address of the optionally logging action
    gc_Level2Address logActionAddress;

    /// Is the lock persistent?
    bool isPersistent;

    /// Is the group currently locked?
    bool isLocked;

    /// The offset to the location of the lock in the associated memory.
    uintptr_t offset;
} gc_GroupInfo;


/******************************************************************************
 * Variable Types
 ******************************************************************************/
/**
 * @struct gc_Blob
 *
 * This data value is used to create BLOBs and strings.
 *
 * Please note that a string is simply a special kind of BLOB. The Gamma Data
 * Model internally only uses BLOB fields to store strings. Actually this
 * behavior is identically to Pascal strings.
 *
 * The data field is a zero-length array which must be used like in the
 * following code example:
 * @code
 * char dump[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };     ///< Sample data for the BLOB.
 *
 * //Malloc the needed memory.
 * const size_t MAX_SIZE = 1024;
 * gc_Blob* blob = 0;
 *
 * blob = (gc_Blob*)malloc( sizeof(gc_Blob) + sizeof(char) * MAX_SIZE );
 * if( !blob )
 * {
 *     printf( "malloc failed. Sorry :-(\n" );
 *     exit( 1 );
 * }
 *
 * //Assign the data fields of the BLOB and copy the content of the dump in it.
 * blob->maxLen = MAX_SIZE;
 * blob->len = sizeof( dump );
 * memcpy( blob->data, dump, sizeof( dump ) );
 *
 * //Now the BLOB is ready to be used.
 * @endcode
 *
 * The following sample shows how to use a BLOB to store a C string:
 * @code
 * const char* const s = "Test String to Store";
 *
 * //Malloc the memory as in the previous code sample
 * const size_t MAX_SIZE = 1024;
 * gc_Blob* blob = 0;
 *
 * blob = (gc_Blob*)malloc( sizeof(gc_Blob) + sizeof(char) * MAX_SIZE );
 * if( !blob )
 * {
 *     printf( "malloc failed. Sorry :-(\n" );
 *     exit( 1 );
 * }
 *
 * //Assign the fields. The only difference is :
 * blob->maxlen = MAX_SIZE;
 *
 * //Handle as Pascal string.
 * blob->len = strlen( s );                 //No need for '+1' to store the '\0'.
 * memcpy( blob.data, s, strlen( s ) );     //Don't copy the '\0' character.
 * @endcode
 *
 * To ease usage of this data type it's advised to use the utility functions
 * gc_Blob_x, found in the header file misc.h
 *
 * @note    The maximum size of a blob is 2^^32 bytes. The reason is to ensure
 *          compatibility between 32 and 64 bit systems. Therefore the #maxLen
 *          and #len arguments are of type uint32_t and not size_t.
 */
typedef struct gc_Blob
{
    uint32_t maxLen;                                ///< Maximum possible length in bytes.
    uint32_t len;                                   ///< Current length in bytes of data section.
#if defined(__GNUC__)
    char data[0] __attribute__ ((aligned (8)));     ///< Contains the data.
#elif defined( _MSC_VER )
    __declspec(align(8)) char data[1];              ///< MS 'patch'. Use 1, but actually use more!
#else
#error "Please specify correct 'construct' for creating zero-length arrays on this platform."
#endif
} gc_Blob;

/**
 * Defines a single field value of the Variable. Don't set the content of
 * this field directly. Use the XXX functions. The structure is not opaque to
 * allow easy read access without function overhead
 */
typedef struct gc_Value
{
    gc_DataType type;       ///< The data type of the value to create.

    /// The content of the union will be selected, depending on the used type.
    union
    {
        gc_NumericValue numeric;
        gc_Blob* blob;      ///< BLOB and string types (data model uses Pascal strings)
    } data;
} gc_Value;

/**
 * Specifies the state of an opened PV.
 *
 * Have a look at #ga_pv_getMetaConfig for how to extract the meta flags
 * from the struct #ga_MetaConfig.
 * The structure element #ga_MetaConfig.state contains the MetaState
 *
 *
 * @code
 * void sample(ga_PV pv)
 * {
 *      gc_ErrorID  returnValue =  gc_ERROR_SUCCESS.errorID;
 *      const char *dest = 0;
 *      const int useRPC=1;
 *      ga_MetaConfig metaConfig;
 *      ga_pv_getMetaConfig(pv, &metaConfig,useRPC);///< use RPC
 *      if( gc_ERROR_SUCCESS.errorID != returnValue )
 *      {
 *          fprintf( stderr, "Call to ga_pv_getMetaConfig() failed.\n" );
 *          fprintf( stderr, "Error ID=%d\n", returnValue );
 *          fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *          exit( -1 );
 *      }
 *
 *      // no need to call gc_freeMemory(dest);
 *      returnValue = ga_printDataObjectState(metaConfig.state, &dest);
 *      if( gc_ERROR_SUCCESS.errorID != returnValue )
 *      {
 *          fprintf( stderr, "Call to ga_printDataObjectState() failed.\n" );
 *          fprintf( stderr, "Error ID=%d\n", returnValue );
 *          fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *          exit( -1 );
 *      }
 *      printf("%s\n", dest);
 *      fflush(stdout);
  *
 * }
 * @endcode
 */
typedef enum gc_MetaState
{
    gc_META_STATE_DEACTIVATED = 0,  ///< Meta functionality is not available!

    ///Meta functionality is available but currently disabled.
    gc_META_STATE_DISABLED,

    ///See 'inherited' options. E.g #gc_Simulation, #gc_Logging, etc.
    gc_META_STATE_OPTION,

} gc_MetaState;

typedef enum gc_Simulation
{
    ///See #gc_META_STATE_DEACTIVATED
    gc_SIMULATION_DEACTIVATED = gc_META_STATE_DEACTIVATED,

    ///See #gc_META_STATE_DISABLED
    gc_SIMULATION_DISABLED = gc_META_STATE_DISABLED,

    ///Simulation is enabled (active).
    gc_SIMULATION_ENABLED = gc_META_STATE_OPTION,

} gc_Simulation;

/**
 * @brief
 * Logging flags. These flags are or'ed to the metaState
 */
typedef enum gc_Logging
{
    ///See #gc_META_STATE_DEACTIVATED
    gc_LOGGING_DEACTIVATED = gc_META_STATE_DEACTIVATED,

    ///See #gc_META_STATE_DISABLED
    gc_LOGGING_DISABLED = gc_META_STATE_DISABLED,

    ///Logging is active and ever write access will be logged, asynchronous
    ///to the service processing cycle.
    gc_LOGGING_ASYNCHRONOUS_ALWAYS = gc_META_STATE_OPTION,

    ///Logging is active and only write access, causing a value change will be
    ///logged, asynchronous to the service processing cycle.
    gc_LOGGING_ASYNCHRONOUS_ON_CHANGE,

    /// Logging is active and the service will log value changes within it's
    /// defined processing cycle.
    gc_LOGGING_SYNCHRONOUS,
} gc_Logging;

typedef enum gc_Boundary
{
    ///See #gc_META_STATE_DEACTIVATED
    gc_BOUNDARY_DEACTIVATED = gc_META_STATE_DEACTIVATED,

    ///See #gc_META_STATE_DISABLED
    gc_BOUNDARY_DISABLED = gc_META_STATE_DISABLED,

    ///Boundary check is active. If a boundary violation occurs the write
    ///access will be rejected and an error will be generated. For more
    ///information about the error propagation please read the GAAPI
    ///documentation.
    gc_BOUNDARY_REJECT = gc_META_STATE_OPTION,

    ///Boundary check is active. If a boundary violation occurs the write
    ///access cause the value to be set to it's boundary value. No error will
    ///be generated. For more information about the error propagation please
    ///read the GAAPI documentation.
    gc_BOUNDARY_CHANGE_TO_BORDER,
} gc_Boundary;

/**
 * Contains the creation configuration for a variable.
 */
typedef struct gc_PVArrayConfig
{
    gc_String1K name;               ///< Unique name of the PVArray.
    bool isPersistent;

    /**
     * false:  A static variable will be created. (Optimization for allocator)
     * true:   A non-static variable will be created (standard/default).
     */
    bool useDynamicMemory;
    uint32_t noElements;             ///< Number of consecutive PVs in this array.
    gc_Value initial;

    //Meta: min
    gc_Boundary minCheckingFlags;
    gc_Value initialMin;            ///< Ignored, if flag is set to deactivated.

    //Meta max
    gc_Boundary maxCheckingFlags;
    gc_Value initialMax;            ///< Ignored, if flag is set to deactivated.

    //Meta sim
    gc_Simulation simulationFlags;
    gc_Value initialSim;            ///< Ignored, if flag is set to deactivated.

    //Meta log
    gc_Logging loggingFlags;

    bool omitLegacyAlias;           ///< Flag to change creation of legacy alias,

} gc_PVArrayConfig;


/**
 * Contains the information for an already existing lock.
 */
typedef struct gc_PVArrayInfo
{
    ///The address of the variable.
    gc_Level5Address address;

    gc_String1K name;       ///< Unique name of the PVArray.

    gc_DataType type;       ///< The data type of the PVs within the PV array.
    uint32_t noElements;    ///< The number of elements of the PV array.
    uint32_t length;        ///< The length of the gc_Blob type, if it is one.

    bool isPersistent;
} gc_PVArrayInfo;

/******************************************************************************
 * Fifo Types
 ******************************************************************************/
typedef struct gc_FifoConfig
{
    gc_String1K name;               ///< Unique name of the Fifo.

    /**
     * true:  The Fifo will exist until deleted or the gasevice has shut down.
     * false: The Fifo will only exist as long as at least one user-process
     *        holds an handle. After that it will be automatically removed
     *        by the gaservice!
     */
    bool isPersistent;

    gc_DataType type;               ///< The data type of the fifos elements.
    uint32_t    typeLength;         ///< Maximum length if type is string or blob.

    /**
     * The length of Fifo. Must be a power of two! If it's NOT a power of two
     * then functions, which require a gc_FifoConfig parameter value might
     * report an #gc_ERROR_COM_INVALID_ARGUMENT error!
     */
    uint32_t    length;

    /**
     * true:  The Fifo will add a timestamp to all pushed elements.
     * false: The Fifo will NOT keep track of the timestamps.
     */
    bool        isUsingTimestamps;

    //Meta: min
    gc_Boundary minCheckingFlags;
    gc_Value    initialMin;         ///< Ignored, if flag is set to deactivated.

    //Meta max
    gc_Boundary maxCheckingFlags;
    gc_Value    initialMax;         ///< Ignored, if flag is set to deactivated.

    //Meta sim
    gc_Simulation simulationFlags;
    gc_Value    initialSim;         ///< Ignored, if flag is set to deactivated.

    //Meta log
    gc_Logging loggingFlags;

} gc_FifoConfig;

typedef struct gc_FifoInfo
{
    ///The address of the variable.
    gc_Level5Address address;

    gc_String1K name;       ///< Unique name of the PVArray.

    gc_DataType type;       ///< The data type of the PVs within the PV array.
    uint32_t typeLength;    ///< The maximum length of a complex data type.

    uint32_t length;        ///< The length of the Fifo.

    bool isPersistent;
    bool isUsingTimestamps;

} gc_FifoInfo;

/******************************************************************************
 * Browsing Types
 ******************************************************************************/
/**
 * Defines the browsing types. The brackets indicate the level of the type
 * and therefore the associated LevelXAddress.
 *
 * To query the level of a given gc_BrowsingType please us the macros below.
 */
typedef enum gc_BrowsingType
{
    gc_BROWSING_TYPE_SYSTEM,              ///< [1] - Browse all systems
    gc_BROWSING_TYPE_NODE,                ///< [2] - Browse all nodes of a system
    gc_BROWSING_TYPE_ACTION,              ///< [2] - Browse all actions of a system
    gc_BROWSING_TYPE_LOOP,                ///< [2] - Browse all loops of a system
    gc_BROWSING_TYPE_TASK,                ///< [2] - Browse all tasks of a system
    gc_BROWSING_TYPE_IO,                  ///< [2] - Browse all IOs of a system
    gc_BROWSING_TYPE_SCHEDULER,           ///< [2] - Browse all schedulers of a system

    gc_BROWSING_TYPE_MEMORY,              ///< [3] - Browse all memories system/node
    gc_BROWSING_TYPE_IO_INPUT,            ///< [3] - Browse all I/O input channels of system/IO
    gc_BROWSING_TYPE_IO_OUTPUT,           ///< [3] - Browse all I/O output channels of system/IO
    gc_BROWSING_TYPE_SCHEDULER_SLOT,      ///< [3] - Browse all scheduler items of a system/scheduler

    gc_BROWSING_TYPE_GROUP,               ///< [4] - Browse all groups of a system/node

    gc_BROWSING_TYPE_PV_ARRAY,            ///< [5] - Browse all variables of a system/node
    gc_BROWSING_TYPE_FIFO,                ///< [5] - Browse all fifos of a system/node

    gc_BROWSING_TYPE_NODE_ALIAS,          ///< [3] - Browse all node aliases
    gc_BROWSING_TYPE_LOOP_ALIAS,          ///< [3] - Browse all loop aliases
    gc_BROWSING_TYPE_ACTION_ALIAS,        ///< [3] - Browse all action aliases
    gc_BROWSING_TYPE_TASK_ALIAS,          ///< [3] - Browse all task aliases
    gc_BROWSING_TYPE_SCHEDULER_ALIAS,     ///< [3] - Browse all scheduler aliases

    gc_BROWSING_TYPE_PV_ARRAY_ALIAS,      ///< [6] - Browse all variable aliases
    gc_BROWSING_TYPE_FIFO_ALIAS,          ///< [6] - Browse all fifo aliases
    gc_BROWSING_TYPE_GROUP_ALIAS,         ///< [5] - Browse all group aliases
    gc_BROWSING_TYPE_MEMORY_ALIAS,        ///< [4] - Browse all memory aliases
    gc_BROWSING_TYPE_SCHEDULER_SLOT_ALIAS ///< [3] - Browse all scheduler slot aliases

} gc_BrowsingType;

/**
 * Queries the given type for level 1 compliance.
 *
 * @param[in]   type    Will be checked for level 1 compliance.
 *
 * @return      True:   Is level 1 compliant.
 *              False:  Is not level 1 compliant.
 */
#define gc_BrowsingType_isLevel1( type ) \
    (gc_BROWSING_TYPE_SYSTEM == (type))

/**
 * Like gc_BrowsingType_isLevel1, but checks for level 2 compliance.
 */
#define gc_BrowsingType_isLevel2( type ) \
    (gc_BROWSING_TYPE_NODE <= (type) && gc_BROWSING_TYPE_SCHEDULER >= (type))

/**
 * Like gc_BrowsingType_isLevel1, but checks for level 3 compliance.
 */
#define gc_BrowsingType_isLevel3( type ) \
    ((gc_BROWSING_TYPE_MEMORY <= (type) && gc_BROWSING_TYPE_SCHEDULER_SLOT >= (type)) || \
     (gc_BROWSING_TYPE_NODE_ALIAS <= (type) && gc_BROWSING_TYPE_SCHEDULER_ALIAS >= (type)) || \
     (gc_BROWSING_TYPE_SCHEDULER_SLOT_ALIAS == (type)))

/**
 * Like gc_BrowsingType_isLevel1, but checks for level 4 compliance.
 */
#define gc_BrowsingType_isLevel4( type ) \
    (gc_BROWSING_TYPE_GROUP == (type) || gc_BROWSING_TYPE_MEMORY_ALIAS == (type))

/**
 * Like gc_BrowsingType_isLevel1, but checks for level 5 compliance.
 */
#define gc_BrowsingType_isLevel5( type ) \
    (gc_BROWSING_TYPE_PV_ARRAY == (type) || gc_BROWSING_TYPE_GROUP_ALIAS == (type) || \
    gc_BROWSING_TYPE_FIFO == (type) )

/**
 * Like gc_BrowsingType_isLevel1, but checks for level 6 compliance.
 */
#define gc_BrowsingType_isLevel6( type ) \
    (gc_BROWSING_TYPE_PV_ARRAY_ALIAS == (type) || gc_BROWSING_TYPE_FIFO_ALIAS == (type))

typedef struct gc_BrowserInfo
{
    gc_BrowsingType type;               ///< The browsed type of this info object

    union
    {
        gc_SystemInfo system;

        gc_NodeInfo node;
        gc_ActionInfo action;
        gc_LoopInfo loop;
        gc_TaskInfo task;
        gc_IOInfo io;
        gc_SchedulerInfo scheduler;

        gc_MemoryInfo memory;
        gc_IOChannelInfo ioChannel;
        gc_SchedulerSlotInfo schedulerSlot;

        gc_GroupInfo group;

        gc_PVArrayInfo pvArray;
        gc_FifoInfo fifo;

        gc_String256 string;                ///< Single alias entry.
    } info;

} gc_BrowserInfo;

/******************************************************************************/
/* Miscellaneous types                                                        */
/******************************************************************************/
typedef enum gc_TaskState
{
    /**
     * Initial state of a task. It is up to the task to set its state to
     * operational.
     */
    gc_TASK_STATE_INITIALIZING,

    /**
     * Task is ready to serve requests.
     */
    gc_TASK_STATE_OPERATIONAL,

} gc_TaskState;

#endif /* GAMMA_COMMON_DATA_TYPES_H__ */

