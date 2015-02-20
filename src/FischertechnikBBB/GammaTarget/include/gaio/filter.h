#ifndef GAIO_FILTER_HPP_
  #define GAIO_FILTER_HPP_

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

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Open filter function pointer.
 *
 * @param [in,out]  filter          Filter handle.
 * @param [in]      logFunction     Logging facility.
 * @param [in]      type            Data type.
 * @param [in]      args            Filter arguments.
 *
 * @return 0 on success.
 */
typedef WINAPI gi_ErrorCode (*gi_OpenFilter)( gi_FilterPtr* filter,
                                              gi_Log logFunction,
                                              const gi_Type type,
                                              const char* const args );

/**
 * Close filter function pointer.
 *
 * @param [in,out]  filter          Filter handle.
 *
 * @return 0 on success.
 */
typedef WINAPI gi_ErrorCode (*gi_CloseFilter)( gi_FilterPtr* filter );

/**
 * Apply Filter function pointer.
 *
 * @param [in]      filter          Filter handle.
 * @param [in,out]  value           Value to filter.
 *
 * @return Filtered output value.
 */
typedef WINAPI gi_ErrorCode (*gi_ApplyFilter)( gi_FilterPtr filter,
                                               gi_DataValue* const value );

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* GAIO_FILTER_HPP_ */
