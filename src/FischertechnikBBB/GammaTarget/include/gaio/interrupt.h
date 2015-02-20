#ifndef GAIO_INTERRUPT_HPP_
  #define GAIO_INTERRUPT_HPP_

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

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Interrupt handler function pointer.
 * NOTE: Return as soon as possible! No exceptions!
 *
 * @param [in]  param           Interrupt parameters.
 * @param [in]  userData        User data pointer.
 */
typedef WINAPI void (*gi_InterruptHandler)( const gi_InterruptParameter param,
                                            const gi_UserData userData );

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* GAIO_INTERRUPT_HPP_ */
