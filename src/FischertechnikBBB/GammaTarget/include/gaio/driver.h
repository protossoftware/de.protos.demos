#ifndef GAIO_DRIVER_H_
  #define GAIO_DRIVER_H_

/**
 * @file
 *
 * @author  Copyright RST Industrie Automation GmbH
 */
/******************************************************************************
 * Header File Includes
 ******************************************************************************/
#include <gaio/export.h>
#include <gaio/types.h>
#include <gaio/log.h>
#include <gaio/interrupt.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief
 * Open io driver.
 *
 * @param [out]     driver      Pointer to opened driver.
 * @param [in]      logFunction Log function.
 * @param [in]      args        Argument string.
 *
 * @return error code.
 */
typedef WINAPI gi_ErrorCode (*gi_OpenDriver)( gi_DriverPtr* driver,
                                              gi_Log logFunction,
                                              const char* const args );

/**
 * @brief
 * Close io driver. Free all resources.
 *
 * @param [in, out] driver      Driver handle. Will be nulled.
 *
 * @return Error code.
 */
typedef WINAPI gi_ErrorCode (*gi_CloseDriver)( gi_DriverPtr* driver );

/**
 * @brief
 * Get driver state.
 *
 * @param [in]      driver      Pointer to driver.
 * @param [out]     state       Driver state.
 *
 * @return Error code.
 */
typedef WINAPI gi_ErrorCode (*gi_GetDriverState)( gi_ConstDriverPtr driver,
                                                  gi_State* state );

/**
 * @brief
 * Get io driver description
 *
 * @param [in]      driver      Pointer to driver.
 * @param [out]     decsription Description.
 *
 * @return Error code.
 */
typedef WINAPI gi_ErrorCode (*gi_GetDriverDescription)( gi_ConstDriverPtr driver,
                                                        gi_Description* description );

/**
 * @brief
 * Get number of channels.
 *
 * @param [in]      driver      Pointer to driver.
 * @param [in]      direction   IO Direction
 * @param [out]     channels    Number of channels.
 *
 * @return Error code.
 */
typedef WINAPI gi_ErrorCode (*gi_GetChannelCount)( gi_ConstDriverPtr driver,
                                                   const gi_Direction direction,
                                                   gi_ChannelID* channels );

/**
 * @brief
 * Get channel name (alias).
 *
 * @param [in]      driver      Pointer to driver
 * @param [in]      direction   IO direction
 * @param [in]      channel     Channel identifier.
 * @param [out]     name        Description.
 *
 * @return Error code.
 */
typedef WINAPI gi_ErrorCode (*gi_GetChannelName)( gi_ConstDriverPtr driver,
                                                  const gi_Direction direction,
                                                  const gi_ChannelID channel,
                                                  gi_Name* name );

/**
 * @brief
 * Get channel description.
 *
 * @param [in]      driver      Pointer to driver
 * @param [in]      direction   IO direction
 * @param [in]      channel     Channel identifier.
 * @param [out]     decsription Description.
 *
 * @return Error code.
 */
typedef WINAPI gi_ErrorCode (*gi_GetChannelDescription)( gi_ConstDriverPtr driver,
                                                         const gi_Direction direction,
                                                         const gi_ChannelID channel,
                                                         gi_Description* description );


/**
 * @brief
 * Get channel configuration.
 *
 * @param [in]      driver      Pointer to driver.
 * @param [in]      direction   IO Direction
 * @param [in]      channel     Channel identifier.
 * @param [out]     config      Channels configuration.
 *
 * @return Error code.
 */
typedef WINAPI gi_ErrorCode (*gi_GetChannelConfiguration)( gi_ConstDriverPtr driver,
                                                           const gi_Direction direction,
                                                           const gi_ChannelID channel,
                                                           gi_Config* config );

/**
 * @brief
 * Get channel state.
 *
 * @param [in]      driver      Pointer to driver.
 * @param [in]      direction   IO Direction
 * @param [in]      channel     Channel identifier.
 * @param [out]     state       Channels state.
 *
 * @return Error code.
 */
typedef WINAPI gi_ErrorCode (*gi_GetChannelState)( gi_ConstDriverPtr driver,
                                                   const gi_Direction direction,
                                                   const gi_ChannelID channel,
                                                   gi_State* state );

/**
 * @brief
 * Activate channel. Channels are being counted from 0. They all have
 * to be explicitly enabled.
 *
 * @param [in]      driver      Pointer to driver.
 * @param [in]      direction   IO Direction
 * @param [in]      channel     Channel identifier.
 *
 * @return Error code.
 */
typedef WINAPI gi_ErrorCode (*gi_EnableChannel)( gi_DriverPtr driver,
                                                 const gi_Direction direction,
                                                 const gi_ChannelID channel );

/**
 * @brief
 * Disable input channel. Input channels are being counted from 0. They all have
 * to be explicitly enabled.
 *
 * @param [in]      driver      Pointer to driver.
 * @param [in]      direction   IO Direction
 * @param [in]      channel     Channel identifier.
 *
 * @return Error code.
 */
typedef WINAPI gi_ErrorCode (*gi_DisableChannel)( gi_DriverPtr driver,
                                                  const gi_Direction direction,
                                                  const gi_ChannelID channel );

/**
 * @brief
 * Get value from input. The channel must have been be activated before.
 *
 * @param [in]      driver      Pointer to driver.
 * @param [in]      channel     Channel identifier.
 * @param [out]     type        Channels data type.
 * @param [out]     value       Channels value.
 * @param [out]     timestamp   Optional timestamp value.
 * @param [out]     isValid     Read datum is valid.
 *
 * @return Error codes.
 */
typedef WINAPI gi_ErrorCode (*gi_GetValue)( gi_ConstDriverPtr driver,
                                            const gi_ChannelID channel,
                                            gi_Type* type,
                                            gi_DataValue* value,
                                            gi_Timestamp* timestamp,
                                            uint32_t* isValid );

/**
 * put value to output. The channel must have been be activated before.
 *
 * @param [in]      driver      Pointer to driver.
 * @param [in]      channel     Channel identifier.
 * @param [in]      type        Values data type.
 * @param [in]      value       Channels value.
 * @param [in]      timestamp   Optional timestamp value (0 means not set).
 *
 * @return Error codes.
 */
typedef WINAPI gi_ErrorCode (*gi_PutValue)( gi_DriverPtr driver,
                                            const gi_ChannelID channel,
                                            const gi_Type type,
                                            const gi_DataValue* value,
                                            const gi_Timestamp* timestamp );


/**
 * Trigger io cycle. This function is for complex hardware which maintains
 * it's own shadow registers.
 *
 * @param [in]      driver      Pointer to driver.
 *
 * @return Error codes.
 */
typedef WINAPI gi_ErrorCode (*gi_Update)( gi_DriverPtr driver );

/**
 * Get number of available interrupts.
 *
 * @param [in]      driver      Pointer to driver.
 * @param [out]     count       Number of interrupts.
 *
 * @return Error codes. 0 on success.
 */
typedef WINAPI gi_ErrorCode (*gi_GetInterruptCount)( gi_ConstDriverPtr driver,
                                                     gi_InterruptID* const count );

/**
 * Get interrupt name.
 *
 * @param [in]      driver      Pointer to driver.
 * @param [in]      id          Interrupt id.
 * @param [out]     name        Interrupt name.
 *
 * @return Error codes. 0 on success.
 */
typedef WINAPI gi_ErrorCode (*gi_GetInterruptName)( gi_ConstDriverPtr driver,
                                                    const gi_InterruptID id,
                                                    gi_Name* name );

/**
 * Register interrupt handler. Any previous set handler shall be overwritten.
 * NOTE: Exceptions must not escape to the driver module!
 *
 * @param [in]      driver      Pointer to driver.
 * @param [in]      id          Interrupt id.
 * @param [in]      handler     Interrupt handler function.
 * @param [in]      userData    User data pointer.
 *
 * @return Error codes. 0 on success.
 */
typedef WINAPI gi_ErrorCode (*gi_RegisterInterruptHandler)( gi_DriverPtr driver,
                                                            const gi_InterruptID id,
                                                            gi_InterruptHandler handler,
                                                            gi_UserData userData );

/**
 * De-register interrupt handler.
 *
 * @param [in]      driver      Pointer to driver.
 * @param [in]      id          Interrupt id.
 *
 * @return Error codes. 0 on success.
 */
typedef WINAPI gi_ErrorCode (*gi_UnregisterInterruptHandler)( gi_DriverPtr driver,
                                                              const gi_InterruptID id );

#ifdef __cplusplus
} // extern "C"
#endif


#endif /* GAIO_DRIVER_H_ */
