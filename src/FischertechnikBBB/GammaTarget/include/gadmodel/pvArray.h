#ifndef GAMMA_DMODEL_PVARRAY_H__
#define GAMMA_DMODEL_PVARRAY_H__

/**
 * @file
 *
 * Contains the complex interface for manipulating the PVArray objects of the Gamma
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
 * Function Declaration: PVArray
 ******************************************************************************/
/**
 * Creates a PVArray.
 *
 * This version identifies the associated group by its address.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_Level4Address groupAddress = { 0, 1, 2, 3 };    //already known!
 * gc_PVArrayConfig config;
 * gc_Handle handle = gc_INVALID_HANDLE;
 * gc_PVArrayInfo info;             //Will contain the info data after creation.
 *
 * //Setup the configuration for the PVArray to create.
 * gc_PVArrayConfig_init( config );
 * strcpy( info.name, "pvArrayXName" );     //The static name of the PVArray.
 *
 * //Create a new PVArray
 * returnValue = gd_pvArray_createByAddress( &groupAddress, &config, &handle, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_pvArray_createByAddress() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   groupAddress        The address of the group, where the PVArray
 *                                  will be put.
 * @param[in]   pvArrayConfig       The configuration for the PVArray to create.
 * @param[out]  pvArrayHandle       Will contain the handle of the PVArray.
 * @param[out]  pvArrayInfo         Will contain the information of the PVArray.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING
 */
gd_EXP gc_ErrorID gc_CALLCONV
gd_pvArray_createByAddress( const gc_Level4Address* const groupAddress,
                            const gc_PVArrayConfig* const pvArrayConfig,
                            gc_Handle* const pvArrayHandle,
                            gc_PVArrayInfo* const pvArrayInfo );

/**
 * Creates a PVArray.
 *
 * This version identifies the associated group by its scoped alias.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * const char* const groupAlias = ":Group";    //already known!
 * gc_PVArrayConfig config;
 * gc_Handle handle = gc_INVALID_HANDLE;
 * gc_PVArrayInfo info;             //Will contain the info data after creation.
 *
 * //Setup the configuration for the PVArray to create.
 * gc_PVArrayConfig_init( config );
 * strcpy( info.name, "pvArrayXName" );     //The static name of the PVArray.
 *
 * //Create a new PVArray
 * returnValue = gd_pvArray_createByAlias( &groupAlias, &config, &handle, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_pvArray_createByAlias() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   scopedGroupAlias    The scoped alias of the group, where the PVArray
 *                                  will be put.
 * @param[in]   pvArrayConfig       The configuration for the PVArray to create.
 * @param[out]  pvArrayHandle       Will contain the handle of the PVArray.
 * @param[out]  pvArrayInfo         Will contain the information of the PVArray.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING
 */
gd_EXP gc_ErrorID gc_CALLCONV
gd_pvArray_createByAlias( const char* const scopedGroupAlias,
                          const gc_PVArrayConfig* const pvArrayConfig,
                          gc_Handle* const pvArrayHandle,
                          gc_PVArrayInfo* const pvArrayInfo );



/**
 * Opens an already existing PVArray.
 *
 * This version uses the address to find the PVArray.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_Level5Address address = { 0, 1, 2, 3, 4 };   //Already known.
 * gc_Handle handle;
 * gc_PVArrayInfo info;
 *
 * //Open an already existing PVArray
 * returnValue = gd_pvArray_openByAddress( &address, &handle, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_pvArray_openByAddress() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   pvArrayAddress      The address of the PVArray.
 * @param[out]  pvArrayHandle       Will contain the handle of the PVArray.
 * @param[out]  pvArrayInfo         Will contain the information of the PVArray.
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
gd_pvArray_openByAddress( const gc_Level5Address* const pvArrayAddress,
                          gc_Handle* const pvArrayHandle,
                          gc_PVArrayInfo* const pvArrayInfo );

/**
 * Opens an already existing PVArray.
 *
 * This version uses the address to find the PVArray.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * const char* const address = ":NodeX.MemoryY.GroupZ.pvArray";    //Already known.
 * gc_Handle handle;
 * gc_PVArrayInfo info;
 *
 * //Open an already existing PVArray
 * returnValue = gd_pvArray_openByAlias( &address, &handle, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_pvArray_openByAlias() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   scopedPVArrayAlias  The scoped alias of the PVArray.
 * @param[out]  pvArrayHandle       Will contain the handle of the PVArray.
 * @param[out]  pvArrayInfo         Will contain the information of the PVArray.
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
gd_pvArray_openByAlias( const char* const scopedPVArrayAlias,
                        gc_Handle* const pvArrayHandle,
                        gc_PVArrayInfo* const pvArrayInfo );


/**
 * Finds a PVArray.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * const char* const name = ":PVArrayX";
 * gc_Level5Address address;
 *
 * //Retrieve the index of the PVArray.
 * returnValue = gd_pvArray_find( name, &address );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_pvArray_find() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   scopedPVArrayAlias    The scoped alias of the PVArray to find.
 * @param[out]  pvArrayAddress        Will contain the address of the PVArray.
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
gd_pvArray_find( const char* const scopedPVArrayAlias,
                 gc_Level5Address* const pvArrayAddress );

/**
 * Retrieves for the given PVArray address the gc_PVArrayInfo.
 *
 * This version uses the address to find the PVArray.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_PVArrayInfo info;                              //Will contain the info
 * gc_Level5Address address = { 0, 1, 2, 3, 4 };     //Already known
 *
 * //Retrieve the info structure of the PVArray.
 * returnValue = gd_pvArray_getInfoByAddress( &address, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_pvArray_getInfoByAddress() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   pvArrayAddress     The address of the PVArray.
 * @param[out]  pvArrayInfo        Will contain the PVArray information.
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
gd_pvArray_getInfoByAddress( const gc_Level5Address* const pvArrayAddress,
                             gc_PVArrayInfo* const pvArrayInfo );

/**
 * Retrieves for the given PVArray alias the gc_PVArrayInfo.
 *
 * This version uses the alias to find the PVArray.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_PVArrayInfo info;                      //Will contain the info
 * const char* const alias = ":PVArray";     //The alias of the PVArray.
 *
 * //Retrieve the info structure of the PVArray.
 * returnValue = gd_pvArray_getInfoByAlias( alias, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_pvArray_getInfoByAlias() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   scopedPVArrayAlias   The scoped alias of the PVArray.
 * @param[out]  pvArrayInfo          Will contain the PVArray information.
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
gd_pvArray_getInfoByAlias( const char* const scopedPVArrayAlias,
                           gc_PVArrayInfo* const pvArrayInfo );

#endif /* GAMMA_DMODEL_PVARRAY_H__ */
