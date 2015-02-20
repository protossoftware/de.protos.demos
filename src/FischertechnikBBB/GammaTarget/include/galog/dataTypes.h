#ifndef GAMMA_LOG_DATATYPES_H_
#define GAMMA_LOG_DATATYPES_H_

/**
 * @file
 *
 * @author  Copyright RST Industrie Automation GmbH
 */
/******************************************************************************
 * Header File Includes
 ******************************************************************************/
#include <gacommon/dataTypes.h>

/******************************************************************************
 * Basic Type Definitions
 ******************************************************************************/

 /**
 * A Client object is a forward declaration.
 *
 * The internal structure of 'struct gl_Client' will never be known to the user
 * A handle has to be used to  refer (point) to a Client object in use.
 * Therefore the definition of 'struct gl_Client' is not part of the public
 * GALOG interface.
 */
 struct gl_Client;
/**
 * Handle (pointer) to a Client object.
 *
 * The internal structure of 'struct gl_Client' will never be known to the user
 * of the GALOG. The handle will only refer (point) to a Client object in use.
 * Therefore the definition of 'struct gl_Client' is not part of the public
 * GALOG interface.
 */
typedef struct gl_Client* gl_ClientPtr;

/**
 * Same as #gl_ClientPtr, but with increased constness.
 */
typedef const struct gl_Client* gl_ConstClientPtr;

/**
 * The gl_Client is actually a wrapper for several DLLs/Shared Libraries,
 * containing a specific logging client that runs only with a specific logging
 * server (backend). Therefore the client must be set to the same type as
 * the server.
 *
 * @note    Currently only one type exists!
 */
typedef enum gl_ClientType
{
    ///The default client, with no domain-specific optimizations.
    gl_CLIENT_TYPE_DEFAULT
} gl_ClientType;

/**
 * Checks that the given gl_ClientType has a valid value.
 */
#define gl_ClientType_isValid( type ) \
    ( gl_CLIENT_TYPE_DEFAULT == (type) )

/******************************************************************************
 * Message-Specific Type Definitions: Base Types
 ******************************************************************************/
///Logging uses its own definition of a handle, because this type must have
///a fixed size (in contrast to #gc_Handle).
///If the source system only uses 32 bit handles the upper 32 bit are always
///zeroed out.
typedef uint64_t gl_Handle;

/**
 * The event type must be one of the following.
 */
typedef enum gl_EventType
{
    ///Event source was/is a loop.
    ///Is always a level 2 address.
    gl_EVENT_TYPE_LOOP = 0,

    ///Event source was/is a scheduler slot.
    ///Is always a level 3 address.
    gl_EVENT_TYPE_SCHEDULER_SLOT = 1,

    ///Event source was/is a hardware.
    ///Is always a level 3 address.
    gl_EVENT_TYPE_HW = 2,
} gl_EventType;

/**
 * Checks that the given gl_EventType has a valid value.
 */
#define gl_EventType_isValid( type ) \
    ( gl_EVENT_TYPE_LOOP == (type) || \
      gl_EVENT_TYPE_SCHEDULER_SLOT == (type) || \
      gl_EVENT_TYPE_HW == (type) )


/**
 * On 32 bit systems the sec and nsec elements have a size of 32 bit, but on a
 * 64 bit system the sizes are 64 bit!
 */
typedef struct gl_Timespec
{
    int64_t tv_sec;
    int64_t tv_nsec;
} gl_Timespec;


/******************************************************************************
 * Message-Specific Type Definitions: Register/Unregister Messages
 ******************************************************************************/
/**
 * Contains information of the registered event.
 */
typedef struct gl_RegisterEvent
{
    ///The numeric address of the registered event.
    ///Beware that the address's 'size' is defined by the type! See
    ///#gl_EventType
    gc_Level3Address eventAddress;

    ///The type of the event.
    gl_EventType eventType;

    ///The handle of the event.
    gl_Handle eventHandle;
} gl_RegisterEvent;


typedef struct gl_RegisterAction
{
    ///The numeric address of the registered action.
    gc_Level2Address actionAddress;

    ///The handle of the action.
    gl_Handle actionHandle;
} gl_RegisterAction;

typedef struct gl_RegisterPV
{
    ///The numeric address of the registered PV.
    gc_Level6Address pvAddress;

    ///The handle of the PV.
    gl_Handle pvHandle;

    ///The data type of the PV.
    gc_DataType dataType;
} gl_RegisterPV;


/**
 * For unregister only one structure exists. To get the specific type
 * (event/action/pv) se gl_Message!
 */
typedef struct gl_Unregister
{
    //The handle of the event, action or PV.
    gl_Handle handle;
} gl_Unregister;


/******************************************************************************
 * Message-Specific Type Definitions: Run-Time Messages
 ******************************************************************************/
/**
 * All gl_LogPV and gl_LogMeta are transmitted between a gl_BeginLogData and
 * a gl_EndLogData. These data structures contain common information about the
 * logged PVs/Meta Data for a given time frame.
 */
typedef struct gl_TimeStamp
{
    ///The handle of the event which initiated the action.
    gl_Handle eventHandle;

    ///The handle of the action which was initiated by the event and
    ///finally caused a new log data block to begin.
    gl_Handle actionHandle;

    ///The frame number of the block.
    uint32_t frameNumber;

    ///The time value of the block.
    gl_Timespec timespec;
} gl_TimeStamp;

typedef struct gl_LogPV
{
    ///The handle of the logged PV.
    gl_Handle pvHandle;

    ///The field type of the PV which was logged.
    gc_PVFieldType fieldType;

    ///The timestamp when the PV was logged.
    gl_TimeStamp* timeStamp;

    ///The logged value. This value must be placed at the end of the gl_LogPV
    ///structure to allow easy handling of strings/blobs.
    gc_Value value;
} gl_LogPV;

typedef struct gl_LogMeta
{
    ///The handle of the logged PV.
    gl_Handle pvHandle;

    ///The meta type which was logged.
    gc_MetaType metaType;

    ///The flags which were changed.
    gc_MetaFlag metaFlag;

    ///The timestamp when the meta information was logged.
    gl_TimeStamp* timeStamp;
} gl_LogMeta;


typedef struct gl_Overwrite
{
    //Nothing here!
} gl_Overwrite;

typedef enum gl_InfoType
{
    gl_INFO_TYPE_SERVER_IS_READY,   /// Connection is ready
    gl_INFO_TYPE_SERVER_IS_BUSY,    /// Server is busy and thus can't handle connection
} gl_InfoType;

typedef struct gl_Info
{
    gl_InfoType type;
} gl_Info;

/**
 * Identification code of the real message, contained within gl_Message.
 */
typedef enum gl_MessageType
{
    gl_MESSAGE_TYPE_REG_EVENT = 0,
    gl_MESSAGE_TYPE_REG_ACTION = 1,
    gl_MESSAGE_TYPE_REG_PV = 2,

    gl_MESSAGE_TYPE_UNREG_EVENT = 3,
    gl_MESSAGE_TYPE_UNREG_ACTION = 4,
    gl_MESSAGE_TYPE_UNREG_PV = 5,

    gl_MESSAGE_TYPE_LOG_PV = 7,
    gl_MESSAGE_TYPE_LOG_META = 8,

    gl_MESSAGE_TYPE_OVERWRITE = 9,
    gl_MESSAGE_TYPE_INFO = 10,
} gl_MessageType;


#define gl_MessageType_isValid( type ) \
    ( gl_MESSAGE_TYPE_REG_EVENT == (type) || \
      gl_MESSAGE_TYPE_REG_ACTION == (type) || \
      gl_MESSAGE_TYPE_REG_PV == (type) || \
      gl_MESSAGE_TYPE_UNREG_EVENT == (type) || \
      gl_MESSAGE_TYPE_UNREG_ACTION == (type) || \
      gl_MESSAGE_TYPE_UNREG_PV == (type) || \
      gl_MESSAGE_TYPE_LOG_PV == (type) || \
      gl_MESSAGE_TYPE_LOG_META == (type) || \
      gl_MESSAGE_TYPE_OVERWRITE == (type) || \
      gl_MESSAGE_TYPE_INFO == (type) )

/**
 * The client.h API provides functions to access a generic message. This data
 * type contains these messages.
 */
typedef struct gl_Message
{
    ///The actual type of the message.
    gl_MessageType type;

    union
    {
        gl_RegisterEvent regEvent;
        gl_RegisterAction regAction;
        gl_RegisterPV regPV;

        gl_Unregister unregister;

        gl_LogPV logPV;
        gl_LogMeta logMeta;

        gl_Overwrite overwrite;
        gl_Info info;
    } message;

} gl_Message;

#endif /* GAMMA_LOG_DATATYPES_H_ */
