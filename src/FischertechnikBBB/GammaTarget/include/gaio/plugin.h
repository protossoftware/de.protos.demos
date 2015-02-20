#ifndef GAIO_PLUGIN_HPP_
  #define GAIO_PLUGIN_HPP_

/**
 * @file
 *
 * @author  Copyright RST Industrie Automation GmbH
 */
/******************************************************************************
 * Header File Includes
 ******************************************************************************/
#include <gaio/driver.h>
#include <gaio/filter.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Change this version number to indicate ABI changes.
 */
#define GAIO_PLUGIN_API_VERSION                     (3)

/**
 * All driver modules must import the symbol RST_CreateHardwarePlugin.
 *
 * This symbol will be resolved by dlopen/LoadLibrary to create the plugin.
 */
#define GAIO_CREATE_HARDWARE_PLUGIN_SYMBOL_NAME     ("RST_CreateHardwarePlugin")

/**
 * All filter modules must import the symbol RST_CreateFilterPlugin.
 *
 * This symbol will be resolved by dlopen/LoadLibrary to create the plugin.
 */
#define GAIO_CREATE_FILTER_PLUGIN_SYMBOL_NAME       ("RST_CreateFilterPlugin")

typedef uint32_t gi_PluginApiVersion;		///< type to contain Version of Plugin API
typedef const char* gi_PluginDescription;	///< type to contain Plugin Description

/**
 * Structure containing all Driver API function pointers.
 */
typedef struct gi_sHarwarePlugin
{
    gi_PluginApiVersion           version;					///< get API-version of this Plugin
    gi_PluginDescription          description;				///< get description of this Plugin

    gi_OpenDriver                 openDriver;				///< open this driver
    gi_CloseDriver                closeDriver;				///< close this driver
    gi_GetDriverState             getDriverState;			///< indicate driver state
    gi_GetDriverDescription       getDriverDescription; 	///< fetch driver description
    gi_GetChannelCount            getChannelCount;			///< get number of io channels
    gi_GetChannelName             getChannelName;           ///< get channel name
    gi_GetChannelDescription      getChannelDescription; 	///< get description of a channel
    gi_GetChannelConfiguration    getChannelConfiguration; 	///< get configuration of a channel
    gi_GetChannelState            getChannelState;  		///< get state  of a channel
    gi_EnableChannel              enableChannel;			///< enable a channel
    gi_DisableChannel             disableChannel;			///< disable a channel
    gi_GetValue                   getValue;					///< get value of channel
    gi_PutValue                   putValue;					///< put value of a channel
    gi_Update                     update;					///< update a channel
    gi_GetInterruptCount          getInterruptCount;		///< get number of available interrupts.
    gi_GetInterruptName           getInterruptName;         ///< get interrupt name.
    gi_RegisterInterruptHandler   registerInterrupt;		///< register an interrupt handler
    gi_UnregisterInterruptHandler unregisterInterrupt;		///< un-register an interrupt handler

} gi_HarwarePlugin;					///< API for HW Plugin

/**
 * Structure containing all Filter API functions.
 */
typedef struct gi_sFilterPlugin
{
    gi_PluginApiVersion           version;	    ///< API version of this Filter Plugin
    gi_OpenFilter                 openFilter;   ///< Open Filter
    gi_CloseFilter                closeFilter;  ///< Close Filter
    gi_ApplyFilter                applyFilter;  ///< Apply Filter

} gi_FilterPlugin;					///< API for Filter Plugin


/**
 * @brief
 * Create hardware plugin.
 *
 * @param [out]     plugin      Pointer to created plugin.
 * @param [in]      args        Argument string.
 *
 * @return GAIO error code.
 */
typedef WINAPI gi_ErrorCode (*gi_CreateHardwarePlugin)( gi_HarwarePlugin* plugin,
                                                        const char* const args );

/**
 * @brief
 * Create filter plugin.
 *
 * @param [out]     plugin      Pointer to created plugin.
 * @param [in]      args        Argument string.
 *
 * @return GAIO error code.
 */
typedef WINAPI gi_ErrorCode (*gi_CreateFilterPlugin)( gi_FilterPlugin* plugin,
                                                      const char* const args );




#ifdef __cplusplus
} // extern "C"
#endif

#endif /* GAIO_PLUGIN_HPP_ */
