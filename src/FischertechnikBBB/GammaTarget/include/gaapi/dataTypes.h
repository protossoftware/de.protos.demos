#ifndef GAMMA_API_DATA_TYPES_H__
    #define GAMMA_API_DATA_TYPES_H__
/**
 * @file
 * Contains all GAAPI-specific data types.
 *
 * @note    All enums are considered to be of type 'int'.
 *
 * @author  (C)opyright since 2003 by RST Industrie-Automation GmbH
 */
/******************************************************************************
 * Header File Includes
 ******************************************************************************/
#include <gacommon/dataTypes.h>
#include <gaapi/platformDependencies.h>


/******************************************************************************
 * PV-specific Data Types
 ******************************************************************************/
/**
 * Handle (pointer) to a PV object.
 *
 * The internal structure of 'struct ga_PV' will never be known to the user of
 * the GAAPI. The handle will only refer (point) to a PV object in use. Therefore
 * the definition of 'struct PV' is not part of the public GAAPI interface.
 */
typedef struct ga_sPV* ga_PV;

/**
 * Same as #ga_PV, but with increased constness.
 */
typedef const struct ga_sPV* ga_ConstPV;

/**
 * This typedef does only exists to avoid compilation errors, because the type
 * ga_DataValue is considered deprecated. Instead of it it's advised to use
 * gc_NumericValue.
 */
gc_DEPRECATED typedef gc_NumericValue ga_DataValue;

///Process variables state information.
typedef enum ga_PVState
{
    ///PV's state is good. (Local variables state is always OK.)
    ga_PV_STATE_OK = 0,

    /**
     * PV's value has been changed and no new value has been sent
     * back to the client. For remote variables only.
     */
    ga_PV_STATE_PENDING = 1,

    /**
     * PV's value has been changed and no new value has been sent
     * back to the client within a certain timeout. For remote variables only.
     */
    ga_PV_STATE_DISC = 2,

    /**
     * PV has an I/O associated with it, but the I/O channel is faulty.
     * If the PV is remote this means that it's still connected. If it's
     * disconnected this state can't be queried.
     */
    ga_PV_STATE_FAULTY = 3

} ga_PVState;

/**
 * Checks if the given PV location is valid.
 */
#define ga_PVState_isValid( pvState ) \
    ( ga_PV_STATE_OK <= (pvState) && \
      ga_PV_STATE_FAULTY >= (pvState) )

/**
 * Specifies the real (original) location of a PV.
 *
 * Have a look at #ga_pv_getMetaConfig for
 * how to extract the meta flags from the #ga_MetaConfig.location
 * struct member.
 *
 *
 * @code
 * void sample(ga_PV pv)
 * {
 *      const char *dest = 0;
 *      gc_ErrorID  returnValue =  gc_ERROR_SUCCESS.errorID;
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
 *      // no GAAPI-allocated memeroy has to be freed , here.
 *      returnValue = ga_printPVLocation(metaConfig.location, &dest);
 *      if( gc_ERROR_SUCCESS.errorID != returnValue )
 *      {
 *          fprintf( stderr, "Call to ga_printPVState() failed.\n" );
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
typedef enum ga_PVLocation
{
    ///PV is locally available.
    ga_PV_LOCATION_LOCAL = 0,

    ///PV is remote.
    ga_PV_LOCATION_REMOTE = 1,

    ///PV is local and has an input I/O associated with it.
    ga_PV_LOCATION_LOCAL_IO_IN = 2,

    ///PV is local and has an output I/O associated with it.
    ga_PV_LOCATION_LOCAL_IO_OUT = 3,
} ga_PVLocation;

/**
 * Checks if the given PV location is valid.
 */
#define ga_PVLocation_isValid( pvLocation ) \
    ( ga_PV_LOCATION_LOCAL <= (pvLocation) && \
      ga_PV_LOCATION_LOCAL_IO_OUT >= (pvLocation) )


/**
 * Specifies process-specific properties of the Gamma Data Object (PV, FIFO, etc)
 * to be opened.
 *
 * A property is always set for a handle. This means that several handles
 * to the same Gamma Data Object in the data model can have different properties!
 *
 * For example the PV-specific function #ga_pv_getMetaConfig's documentation
 * describe how to extract the meta flags from the #ga_MetaConfig
 *
 * The structure element #ga_MetaConfig.pvProperties contains
 * the Properties of the opened Gamma Object.
 *
 * @note    For every enumerator a table exist, describing which concrete
 *          Gamma Data Object are using/providing the property.
 *
 * @code
 * //Sample with a PV handle.
 * void sample( ga_PV pv )
 * {
 *      const char *dest = 0;
 *      gc_ErrorID  returnValue = gc_ERROR_SUCCESS.errorID;
 *      const int useRPC = 1;
 *      ga_MetaConfig metaConfig;
 *      ga_pv_getMetaConfig( pv, &metaConfig, useRPC );
 *      if( gc_ERROR_SUCCESS.errorID != returnValue )
 *      {
 *          fprintf( stderr, "Call to ga_pv_getMetaConfig() failed.\n" );
 *          fprintf( stderr, "Error ID=%d\n", returnValue );
 *          fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *          exit( -1 );
 *      }
 *
 *
 *      returnValue = ga_printPVProperties(metaConfig.pvProperties,  "\t", &dest, 0);
 *      if( gc_ERROR_SUCCESS.errorID != returnValue )
 *      {
 *          fprintf( stderr, "Call to ga_printPVState() failed.\n" );
 *          fprintf( stderr, "Error ID=%d\n", returnValue );
 *          fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *          exit( -1 );
 *      }
 *      printf("%s\n", dest);
 *      fflush(stdout);
 *
 *      //free the GAAPI-allocated memory
 *      gc_freeMemory((void*)dest);
 * }
 * @endcode
 *
 */
typedef enum ga_PVProperty
{
    /**************************************************************************
     * Access Configuration for Remote Gamma Data Objects
     **************************************************************************/
    /**
     * PV Type:                   Description:
     * =========================================================================
     * PV                         #ga_pv_getValue/#ga_pv_putValue are configured
     *                            as followed:
     *                              - PV access is synchronous and will
     *                                always cause RPCs
     *
     * FIFO                       N/A network access is always via RPC.
     *
     * @note    If no access property is explicitly quoted this is the default.
     *
     * @note    Either #ga_PV_PROPERTY_ACC_BLOCKING or
     *                 #ga_PV_PROPERTY_ACC_NON_BLOCKING can be used.
     */
    ga_PV_PROPERTY_ACC_BLOCKING = 1 << 0,

    /**
     * PV Type:                   Description:
     * =========================================================================
     * PV                         #ga_pv_getValue/#ga_pv_putValue are configured
     *                            as followed:
     *                              - PV access is asynchronous and will
     *                                always access the SHM
     *
     * FIFO                       N/A
     *
     * @note    Either #ga_PV_PROPERTY_ACC_BLOCKING or
     *                 #ga_PV_PROPERTY_ACC_NON_BLOCKING can be used.
     */
    ga_PV_PROPERTY_ACC_NON_BLOCKING = 1 << 1,


    /**************************************************************************
     * Name Lookup of Gamma Data Objects Address
     **************************************************************************/
    /**
     * PV Type:                   Description:
     * =========================================================================
     * Single value               If the address does not explicitly define the
     * FIFO                       locality of the Gamma Data Object this flag
     *                            sets it to "only local". No network access will
     *                            be issued if the Gamma Data Objects was not
     *                            found on the local system.
     *
     * @note    Either #ga_PV_PROPERTY_LOOKUP_LOCAL or
     *                 #ga_PV_PROPERTY_LOOKUP_GLOBAL can be used.
     */
    ga_PV_PROPERTY_LOOKUP_LOCAL = 1 << 2,

    /**
     * PV Type:    Description:
     * =========================================================================
     * Single value               If the address does not explicitly define the
     * FIFO                       locality of the Gamma Data Objects this flag
     *                            sets it to "first local then global". If the
     *                            Gamma Data Objects was not found on the local
     *                            system the whole network will be searched for it.
     *
     * @note    If no lookup property is explicitly quoted this is the default.
     *
     * @note    Either #ga_PV_PROPERTY_LOOKUP_LOCAL or
     *                 #ga_PV_PROPERTY_LOOKUP_GLOBAL can be used.
     */
    ga_PV_PROPERTY_LOOKUP_GLOBAL = 1 << 3,


    /**************************************************************************
     * Gamma Data Objects Put Access While Full
     **************************************************************************/
    /**
     * PV Type:    Description:
     * =========================================================================
     * FIFO                       If the FIFO is full and another put access
     *                            (e.g. #ga_pv_put) takes place the oldest
     *                            value in the FIFO will be overwritten with the
     *                            new one. Therefore write semantics are analog
     *                            to a cyclic buffer with overwrite.
     *
     *                            This property will only be used for locally
     *                            available FIFOs. For remote FIFO the property
     *                            will implicitly default to
     *                            #ga_PV_PROPERTY_PUT_FULL_ERROR!
     *
     * PV                         Invalid property. Using it will cause an
     *                            error.
     *
     * @note    Either #ga_PV_PROPERTY_PUT_FULL_OVERWRITE or
     *                 #ga_PV_PROPERTY_PUT_FULL_BLOCK or
     *                 #ga_PV_PROPERTY_PUT_FULL_ERROR can be used.
     */
    ga_PV_PROPERTY_PUT_FULL_OVERWRITE = 1 << 4,


    /**
     * PV Type:    Description:
     * =========================================================================
     * FIFO                       If the FIFO is full and another put access
     *                            (e.g. #ga_pv_put) takes place the call
     *                            will wait until free space becomes available.
     *
     *                            To set the timeout to an arbitrary amount of
     *                            ms please read the documentation for
     *                            #ga_pv_putPropertyValue. The default is
     *                            to block forever (means 0 ms).
     *
     *                            This property will only be used for locally
     *                            available FIFOs. For remote FIFO the property
     *                            will implicitly default to
     *                            #ga_PV_PROPERTY_PUT_FULL_ERROR!
     *
     * PV                         Invalid property. Using it will cause an
     *                            error.
     *
     * @note    If no 'put request while full' property is explicitly quoted
     *          this is the default.
     *
     * @note    Either #ga_PV_PROPERTY_PUT_FULL_OVERWRITE or
     *                 #ga_PV_PROPERTY_PUT_FULL_BLOCK or
     *                 #ga_PV_PROPERTY_PUT_FULL_ERROR can be used.
     */
    ga_PV_PROPERTY_PUT_FULL_BLOCK = 1 << 5,

    /**
     * PV Type:    Description:
     * =========================================================================
     * FIFO                       If the FIFO is full and another put access
     *                            (e.g. #ga_pv_put) takes place the call
     *                            will return with error #gc_ERROR_PV_FIFO_FULL.
     *
     *                            This is the only put property which is also
     *                            be used for remote FIFOs.
     *
     * PV                         Invalid property. Using it will cause an
     *                            error.
     *
     * @note    Either #ga_PV_PROPERTY_PUT_FULL_OVERWRITE or
     *                 #ga_PV_PROPERTY_PUT_FULL_BLOCK or
     *                 #ga_PV_PROPERTY_PUT_FULL_ERROR can be used.
     */
    ga_PV_PROPERTY_PUT_FULL_ERROR = 1 << 6,


    /**************************************************************************
     * Gamma Data Objects Get Access While Empty
     **************************************************************************/
    /**
     * PV Type:    Description:
     * =========================================================================
     * FIFO                       If the FIFO is empty and another get access
     *                            (e.g. #ga_pv_get) takes place the call
     *                            will wait until a new element becomes available.
     *
     *                            To set the timeout to an arbitrary amount of
     *                            ms please read the documentation for
     *                            #ga_pv_putPropertyValue. The default is
     *                             to block forever (means 0 ms).
     *
     *                            This property will only be used for locally
     *                            available FIFOs. For remote FIFO the property
     *                            will implicitly default to
     *                            #ga_PV_PROPERTY_GET_EMPTY_ERROR!
     *
     * PV                         Invalid property. Using it will cause an
     *                            error.
     *
     * @note    If no 'get request while empty' property is explicitly quoted
     *          this is the default.
     *
     * @note    Either #ga_PV_PROPERTY_GET_EMPTY_BLOCK or
     *                 #ga_PV_PROPERTY_GET_EMPTY_ERROR can be used.
     */
    ga_PV_PROPERTY_GET_EMPTY_BLOCK = 1 << 7,

    /**
     * PV Type:    Description:
     * =========================================================================
     * FIFO                       If the FIFO is empty and another get access
     *                            (e.g. #ga_pv_get) takes place the call
     *                            will immediately return with an appropriate
     *                            error code.
     *
     *                            This is the only get property which is also
     *                            be used for remote FIFOs.
     *
     * PV                         Invalid property. Using it will cause an
     *                            error.
     *
     * @note    Either #ga_PV_PROPERTY_GET_EMPTY_BLOCK or
     *                 #ga_PV_PROPERTY_GET_EMPTY_ERROR can be used.
     */
    ga_PV_PROPERTY_GET_EMPTY_ERROR = 1 << 8,


} ga_PVProperty;

/**
 * Checks if the given PV property is valid.
 */
#define ga_PVProperty_isValid( property ) \
    ( ga_PV_PROPERTY_ACC_BLOCKING == (property) || \
      ga_PV_PROPERTY_ACC_NON_BLOCKING == (property) || \
      ga_PV_PROPERTY_LOOKUP_LOCAL == (property) || \
      ga_PV_PROPERTY_LOOKUP_GLOBAL == (property) || \
      ga_PV_PROPERTY_PUT_FULL_OVERWRITE == (property) || \
      ga_PV_PROPERTY_PUT_FULL_BLOCK == (property) || \
      ga_PV_PROPERTY_PUT_FULL_ERROR == (property) || \
      ga_PV_PROPERTY_GET_EMPTY_BLOCK == (property) || \
      ga_PV_PROPERTY_GET_EMPTY_ERROR == (property ) )

/**
 * Contains extraction masks for or'ed enumerators.
 */
enum
{
    /**************************************************************************
     * PV Property Masks
     **************************************************************************/
    ///Extraction mask.
    ga_PV_PROPERTY_ACC_MASK = ga_PV_PROPERTY_ACC_BLOCKING |
                              ga_PV_PROPERTY_ACC_NON_BLOCKING,

    ///Extraction mask
    ga_PV_PROPERTY_LOOKUP_MASK = ga_PV_PROPERTY_LOOKUP_LOCAL |
                                 ga_PV_PROPERTY_LOOKUP_GLOBAL,

    ///Extraction mask
    ga_PV_PROPERTY_PUT_FULL_MASK = ga_PV_PROPERTY_PUT_FULL_OVERWRITE |
                                   ga_PV_PROPERTY_PUT_FULL_BLOCK |
                                   ga_PV_PROPERTY_PUT_FULL_ERROR,

    ///Extraction mask
    ga_PV_PROPERTY_GET_EMPTY_MASK = ga_PV_PROPERTY_GET_EMPTY_BLOCK |
                                    ga_PV_PROPERTY_GET_EMPTY_ERROR,
};

///Every PV has these flags to indicate the configured/current meta functionalities.
typedef struct ga_MetaConfig
{
    ///State (ga_PVState) of the PV. This is a read-only property.
    ///Please not that for remote PVs this is the only state!
    ga_PVState state;

    ///The location (ga_PVLocation) of the PV. This is a read-only property.
    ga_PVLocation location;

    ///The properties of the PV as given by creation. This is a read-only property.
    gc_Flags32Bit pvProperties;

    ///The current configuration of the meta functionalities. Can be changed
    ///via ga_pv_changeMetaFunctions.
    gc_Flags32Bit flags;   ///See gc_MetaFlag
} ga_MetaConfig;


/**
 * Specifies the concrete type of the generic Gamma Data Object instance.
 */
typedef enum ga_PVType
{
    ga_PV_TYPE_SINGLE_VALUE = 0,     ///< Single value (scalar) PV.
    ga_PV_TYPE_FIFO = 1,              ///< FIFO PV.

    /**
     * This default not-set value is provided, to allow setting a PV type to
     * an invalid value before querying it. In case the application software has
     * an invalid value before querying it. In case the application software has
     * a logical error it can be cached! (E.g. the user forget to call
     * #ga_pv_getPVType(...).
     */
    ga_PV_TYPE_INVALID = 0xFF

} ga_PVType;

/**
 * Checks if the given PV type is valid.
 */
#define ga_PVType_isValid( pvType ) \
    ( ga_PV_TYPE_SINGLE_VALUE <= (pvType) && \
      ga_PV_TYPE_FIFO >= (pvType) )


/**
 * Holds the length informations of the FIFO.
 *
 * @note    DO NOT USE THIS INFORMATION STRUCTURE FOR PROCESS LOGIC, BECAUSE
 *          THESE INFORMATIONS ARE ONLY A SNAPSHOT AT A SPECIFIC TIME.
 *
 *          ONLY USE THIS INFORMATION FOR SOME KIND OF VISUALIZATION.
 */
typedef struct ga_FIFOLengthInfo
{
    /**
     * The number of free slots to write to.
     */
    uint32_t free;

    /**
     * The number of values which can hold information.
     */
    uint32_t used;

    /**
     * Maximum size of the FIFO.
     */
    uint32_t max;
} ga_FIFOLengthInfo;

/**
 * Callback for PV (only!) signaling.
 *
 * @param[in]   pv      This PV was signaled.
 * @param[in]   data    If user specified a corresponding user data pointer it
 *                      will be set to this.
 */
typedef void (gc_CALLCONV *ga_SignalCallback)( ga_PV pv,
                                               void* data );

/******************************************************************************
 * FIFO-specific Data Types
 ******************************************************************************/

typedef struct ga_sFIFO* ga_FIFO;

/**
 * Same as #ga_PV, but with increased constness.
 */
typedef const struct ga_sFIFO* ga_ConstFIFO;




#endif /* GAMMA_API_DATA_TYPES_H__ */

