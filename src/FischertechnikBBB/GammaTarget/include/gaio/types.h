#ifndef GAIO_TYPES_H_
  #define GAIO_TYPES_H_

/**
 * @file
 *
 * TODO    Use the GACOMMON types after the cyclic dependency has been
 *         resolved.
 *
 * @author  Copyright RST Industrie Automation GmbH
 */
/******************************************************************************
 * Header File Includes
 ******************************************************************************/
#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ERROR_RANGE_IO  (255)

/**
 * All Gamma IO error codes.
 * The returned error type is defined as uint32_t to allow
 * user defined error codes.
 */
typedef enum gi_ErrorCode
{
    GI_ERROR_SUCCESS = ERROR_RANGE_IO << 24,   ///< SUCCESS
    GI_ERROR_INVALID_ARGUMENT,      ///< Invalid pointer argument.
    GI_ERROR_NOMEM,                 ///< Out of memory.
    GI_ERROR_INVALID_DIRECTION,     ///< Invalid direction value.
    GI_ERROR_INVALID_CHANNEL,       ///< Channel value out of bounds.
    GI_ERROR_INVALID_TYPE,          ///< Data type mismatch.
    GI_ERROR_IS_ENABLED,            ///< Channel is (already) enabled.
    GI_ERROR_IS_DISABLED,           ///< Channel is disabled.
    GI_ERROR_IS_FAULTY,             ///< Channel is defective.
    GI_ERROR_NO_INTERRUPT,          ///< Hardware doesn't support interrupts
    GI_ERROR_UNKNOWN,               ///< Unknown internal error.
    GI_ERROR_NO_SUCH_DEVICE,        ///< If a specific device is not available.
    GI_ERROR_INIT_DEVICE_FAILED,    ///< Device initialization has failed.
    GI_ERROR_AGAIN,                 ///< Buffer full, try again

    GI_ERROR_USER = 0x1000          ///< User/driver defined errors start here
} gi_ErrorCode;

/**
 * IO Direction.
 */
typedef enum gi_Direction
{
    GI_DIR_INPUT,        ///< IO channel is of type input
    GI_DIR_OUTPUT        ///< IO channel is of type output
} gi_Direction;

/**
 * All possible IO data types.
 */
typedef enum gi_Type
{
    GI_TYPE_SINT8 = 0,         ///<   signed BYTE
    GI_TYPE_UINT8,             ///< unsigned BYTE
    GI_TYPE_SINT16,            ///<   signed WORD
    GI_TYPE_UINT16,            ///< unsigned WORD
    GI_TYPE_SINT32,            ///<   signed DWORD
    GI_TYPE_UINT32,            ///< unsigned DWORD
    GI_TYPE_SINT64,            ///<   signed QWORD
    GI_TYPE_UINT64,            ///< unsigned QWORD
    GI_TYPE_IEEE32,            ///< float  (32 bits)
    GI_TYPE_IEEE64             ///< double (64 bits)
} gi_Type;

/**
 * Data type container.
 */
typedef union gi_DataValue
{
    int8_t          sint8;     ///<   signed BYTE
    uint8_t         uint8;     ///< unsigned BYTE
    int16_t         sint16;    ///<   signed WORD
    uint16_t        uint16;    ///< unsigned WORD
    int32_t         sint32;    ///<   signed DWORD
    uint32_t        uint32;    ///< unsigned DWORD
    int64_t         sint64;    ///<   signed QWORD
    uint64_t        uint64;    ///< unsigned QWORD
    float           ieee32;    ///< float  (32 bits)
    double          ieee64;    ///< double (64 bits)
} gi_DataValue;

/**
 * Gamma IO channel state flags.
 */
typedef enum gi_StateFlags
{
    GI_STATE_ENABLED    = 0x0, ///< Hardware/Channel is enabled and ready to use
    GI_STATE_DISABLED   = 0x1, ///< Hardware/Channel is disabled
    GI_STATE_FAULTY     = 0x2  ///< Hardware/Channel is defective
} gi_StateFlags;

/**
 * Gamma IO channel state.
 */
typedef uint8_t gi_State;

#define GI_IS_ENABLED( state )        ( !(state & GI_STATE_DISABLED) )
#define GI_IS_FAULTY( state )         ( state & GI_STATE_FAULTY )

typedef enum gi_ChannelType
{
    GI_CHANNEL_TYPE_SIMPLE = 0,
    GI_CHANNEL_TYPE_CONSECUTIVE,

} gi_ChannelType;

/**
 * Channel configuration.
 */
typedef struct gi_Config
{
    gi_Type         type;
    uint32_t        isConsecutive;

} gi_Config;

/**
 * Channel Identifier.
 */
typedef uint32_t gi_ChannelID;

/**
 * Maximum length of description string.
 */
#define GI_DESCRIPTION_LENGTH         (512)

/**
 * description string.
 */
typedef struct gi_Description
{
    char name[GI_DESCRIPTION_LENGTH];
} gi_Description;


#define GI_NAME_LENGTH              (512)

/**
 * Name string.
 */
typedef struct gi_Name
{
    char name[GI_NAME_LENGTH];
} gi_Name;

/**
 * Opaque driver handle.
 */
typedef void* gi_DriverPtr;

/**
 * Constant opaque driver handle.
 */
typedef const void* gi_ConstDriverPtr;

/**
 * Opaque filter handle.
 */
typedef void* gi_FilterPtr;

/**
 * Constant opaque filter handle.
 */
typedef const void* gi_ConstFilterPtr;

/**
 * typedef for pointer to user data .
 */
typedef void* gi_UserData;

/**
 * Interrupt index.
 */
typedef uint32_t gi_InterruptID;
/**
 * Interrupt parameters.
 */
typedef struct gi_InterruptParameter
{
    gi_InterruptID    id;
} gi_InterruptParameter;

typedef union gi_Timestamp
{
    uint64_t timestamp;
    struct
    {
        uint32_t seconds;
        uint32_t nanoseconds;
    };
} gi_Timestamp;

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* GAIO_TYPES_H_ */
