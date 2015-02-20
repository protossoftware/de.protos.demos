#ifndef GAMMA_DMODEL_FIFO_H__
#define GAMMA_DMODEL_FIFO_H__

/**
 * @file
 *
 * Contains the complex interface for manipulating the Fifo objects of the Gamma
 * Data Model.
 *
 * @author  Copyright RST Industrie Automation GmbH
 */
/******************************************************************************
 * Header File Includes
 ******************************************************************************/
#include <gacommon/errorCodes.h>
#include <gadmodel/platformDependencies.h>
#include <gadmodel/dataTypes.h>

/******************************************************************************
 * Function Declaration: Fifo
 ******************************************************************************/
/**
 * Convenience function for creating a Fifo with a default configuration.
 *
 * If the data type is of #gc_DATA_TYPE_STRING or #gc_DATA_TYPE_BLOB a
 * maximum length as specified by the functions argument maxLength is used.
 * Otherwise the argument will be ignored.
 *
 * The following itemization gives an overview of the default Gamma Data Model
 * used by this functions:
 *  - Net/Sig/Log Actions:
 *     - Three actions are created. One for Networking (called Net), one for
 *       Signaling (called Sig) and one for Logging (called Log).
 *     - gc_ActionConfig:
 *        - isPersistent = false
 *  - Loop
 *     - Will be associated with the above Net/Sig/Log actions.
 *     - gc_LoopConfig:
 *        - isPersistent = false
 *        - cycleTicks = 1
 *  - Node:
 *     - gc_NodeConfig:
 *        - isPersistent = false
 *  - SHM:
 *     - gc_SHMConfig:
 *       - isPersistent = false
 *       - size = 10 * 1024 * 1024
 *       - permission = 0
 *       - user = ""
 *       - group = ""
 *  - Group:
 *     - As actions Net/Sig/Log are used.
 *     - gc_GroupConfig:
 *        - isPersistent = false
 *        - isLocked = false
 *  - Fifo:
 *     - gc_PVArrayConfig:
 *       - isPersistent = false
 *       - usesTimestamps = false
 *       - length = Length of the fifo
 *       - minCheckingFlags = gc_META_STATE_DISABLED
 *       - maxCheckingFlags = gc_META_STATE_DISABLED
 *       - simulationFlags = gc_META_STATE_DISABLED
 *       - loggingFlags = gc_META_STATE_DISABLED
 *
 * The above mentioned components will be created by the first call to
 * this function. All further calls will either use the already created Data
 * Model Object or will recreate them.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_Handle handle = gc_INVALID_HANDLE;
 *
 * //Create a new PV
 * returnValue = gd_createFifo( "FifoName",
 *                              64
 *                              gc_DATA_TYPE_IEEE_64,
 *                              0,                //Won't be used
 *                             &handle );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_createFifo() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //At this point the newly created Fifo is ready to be used.
 * //E.g. in conjunction with GAAPI the Fifo can be opened via ga_fifo_open(...)
 * //or it can be browsed via the GAAPI's browsing interface, etc.
 * //For more information please read the documentation of these mentioned APIs.
 *
 * //If the Fifo is no longer needed it can be safely closed as follows:
 * returnValue = gd_closeHandle( handle );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_closeHandle() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @note    This function is not MT-safe.
 *
 * @param[in]   aliasName    The alias name for identifying the Fifo.
 * @param[in]   length       The length/size of the fifo. This value must be
 *                           a power of two.
 * @param[in]   dataType     The data type of the PV. The value of the PV will
 *                           be for numeric types 0, for strings "" and for
 *                           BLOBs NULL pointer.
 * @param[in]   maxLength    If the data type is of BLOB/String this parameter
 *                           defines its maximum length.
 * @param[out]  handle       The handle to the PV (technically PVArray). Use
 *                           this handle for calling #gd_closeHandle after the
 *                           PV is no longer needed.
 */
gd_EXP gc_ErrorID gc_CALLCONV
gd_createFifo( const char* const aliasName,
               const uint32_t length,
               const gc_DataType dataType,
               const uint32_t maxLength,
               gc_Handle* const handle);

/**
 * Creates a FifoArray.
 *
 * This version identifies the associated group by its address.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_Level4Address groupAddress = { 0, 1, 2, 3 };    //already known!
 * gc_FifoConfig config;
 * gc_Handle handle = gc_INVALID_HANDLE;
 * gc_FifoInfo info;             //Will contain the info data after creation.
 *
 * //Setup the configuration for the Fifo to create.
 * gc_FifoConfig_init( config );
 * strcpy( info.name, "fifoXName" );     //The static name of the Fifo.
 *
 * //Create a new Fifo
 * returnValue = gd_fifo_createByAddress( &groupAddress, &config, &handle, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_fifo_createByAddress() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   groupAddress        The address of the group, where the Fifo
 *                                  will be put.
 * @param[in]   fifoConfig          The configuration for the Fifo to create.
 * @param[out]  fifoHandle          Will contain the handle of the Fifo.
 * @param[out]  fifoInfo            Will contain the information of the Fifo.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING
 */
gd_EXP gc_ErrorID gc_CALLCONV
gd_fifo_createByAddress( const gc_Level4Address* const groupAddress,
                         const gc_FifoConfig* const fifoConfig,
                         gc_Handle* const fifoHandle,
                         gc_FifoInfo* const fifoInfo );

/**
 * Creates a Fifo.
 *
 * This version identifies the associated group by its scoped alias.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * const char* const groupAlias = ":Group";    //already known!
 * gc_FifoConfig config;
 * gc_Handle handle = gc_INVALID_HANDLE;
 * gc_FifoInfo info;             //Will contain the info data after creation.
 *
 * //Setup the configuration for the Fifo to create.
 * gc_FifoConfig_init( config );
 * strcpy( info.name, "fifoXName" );     //The static name of the Fifo.
 *
 * //Create a new Fifo
 * returnValue = gd_fifo_createByAlias( &groupAlias, &config, &handle, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_fifo_createByAlias() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   scopedGroupAlias    The scoped alias of the group, where the Fifo
 *                                  will be put.
 * @param[in]   fifoConfig       The configuration for the Fifo to create.
 * @param[out]  fifoHandle       Will contain the handle of the Fifo.
 * @param[out]  fifoInfo         Will contain the information of the Fifo.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING
 */
gd_EXP gc_ErrorID gc_CALLCONV
gd_fifo_createByAlias( const char* const scopedGroupAlias,
                       const gc_FifoConfig* const fifoConfig,
                       gc_Handle* const fifoHandle,
                       gc_FifoInfo* const fifoInfo );



/**
 * Opens an already existing Fifo.
 *
 * This version uses the address to find the Fifo.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_Level5Address address = { 0, 1, 2, 3, 4 };   //Already known.
 * gc_Handle handle;
 * gc_FifoInfo info;
 *
 * //Open an already existing Fifo
 * returnValue = gd_fifo_openByAddress( &address, &handle, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_fifo_openByAddress() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   fifoAddress      The address of the Fifo.
 * @param[out]  fifoHandle       Will contain the handle of the Fifo.
 * @param[out]  fifoInfo         Will contain the information of the Fifo.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_SERVICE_OBJECT_NOT_EXIST
 */
gd_EXP gc_ErrorID gc_CALLCONV
gd_fifo_openByAddress( const gc_Level5Address* const fifoAddress,
                       gc_Handle* const fifoHandle,
                       gc_FifoInfo* const fifoInfo );

/**
 * Opens an already existing Fifo.
 *
 * This version uses the address to find the Fifo.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * const char* const address = ":NodeX.MemoryY.GroupZ.fifo";    //Already known.
 * gc_Handle handle;
 * gc_FifoInfo info;
 *
 * //Open an already existing Fifo
 * returnValue = gd_fifo_openByAlias( &address, &handle, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_fifo_openByAlias() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   scopedFifoAlias  The scoped alias of the Fifo.
 * @param[out]  fifoHandle       Will contain the handle of the Fifo.
 * @param[out]  fifoInfo         Will contain the information of the Fifo.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_SERVICE_OBJECT_NOT_EXIST
 */
gd_EXP gc_ErrorID gc_CALLCONV
gd_fifo_openByAlias( const char* const scopedFifoAlias,
                     gc_Handle* const fifoHandle,
                     gc_FifoInfo* const fifoInfo );


/**
 * Finds a Fifo.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * const char* const name = ":FifoX";
 * gc_Level5Address address;
 *
 * //Retrieve the index of the Fifo.
 * returnValue = gd_fifo_find( name, &address );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_fifo_find() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   scopedFifoAlias    The scoped alias of the Fifo to find.
 * @param[out]  fifoAddress        Will contain the address of the Fifo.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_SERVICE_OBJECT_NOT_EXIST
 */
gd_EXP gc_ErrorID gc_CALLCONV
gd_fifo_find( const char* const scopedFifoAlias,
              gc_Level5Address* const fifoAddress );

/**
 * Retrieves for the given Fifo address the gc_FifoInfo.
 *
 * This version uses the address to find the Fifo.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_FifoInfo info;                              //Will contain the info
 * gc_Level5Address address = { 0, 1, 2, 3, 4 };     //Already known
 *
 * //Retrieve the info structure of the Fifo.
 * returnValue = gd_fifo_getInfoByAddress( &address, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_fifo_getInfoByAddress() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   fifoAddress     The address of the Fifo.
 * @param[out]  fifoInfo        Will contain the Fifo information.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_SERVICE_OBJECT_NOT_EXIST
 */
gd_EXP gc_ErrorID gc_CALLCONV
gd_fifo_getInfoByAddress( const gc_Level5Address* const fifoAddress,
                          gc_FifoInfo* const fifoInfo );

/**
 * Retrieves for the given Fifo alias the gc_FifoInfo.
 *
 * This version uses the alias to find the Fifo.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_FifoInfo info;                      //Will contain the info
 * const char* const alias = ":Fifo";     //The alias of the Fifo.
 *
 * //Retrieve the info structure of the Fifo.
 * returnValue = gd_fifo_getInfoByAlias( alias, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_fifo_getInfoByAlias() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   scopedFifoAlias   The scoped alias of the Fifo.
 * @param[out]  fifoInfo          Will contain the Fifo information.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_SERVICE_OBJECT_NOT_EXIST
 */
gd_EXP gc_ErrorID gc_CALLCONV
gd_fifo_getInfoByAlias( const char* const scopedFifoAlias,
                        gc_FifoInfo* const fifoInfo );

#endif /* GAMMA_DMODEL_PVARRAY_H__ */
