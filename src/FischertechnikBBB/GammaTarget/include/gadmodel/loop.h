#ifndef GAMMA_DMODEL_LOOP_H__
#define GAMMA_DMODEL_LOOP_H__

/**
 * @file
 *
 * Contains the complex interface for manipulating loops of the Gamma
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
 * Function Declaration: Loop
 ******************************************************************************/
/**
 * Creates a loop.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_LoopConfig config;
 * gc_Handle handleIndex = gc_INVALID_HANDLE;
 * gc_LoopInfo info;
 *
 * //Remove the loop after the last using task has closed it's resource to it.
 * config.isPersistent = 0;
 * config.updateCycleUs = 100000;       //The loop interval is set to 100 ms.
 * strcpy( config.name, "LoopXName" );  //The static name of the loop.
 *
 * //Create a new loop
 * returnValue = gd_loop_create( &config, &handleIndex, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_loop_create() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   loopConfig      The configuration for the loop to create.
 * @param[out]  loopHandle      Will contain the handle of the loop.
 * @param[out]  loopInfo        Will contain the information of the loop.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING
 */
gd_EXP gc_ErrorID gc_CALLCONV
gd_loop_create( const gc_LoopConfig* const loopConfig,
                gc_Handle* const loopHandle,
                gc_LoopInfo* const loopInfo );

/**
 * Opens an already existing loop.
 *
 * This version uses the address to find the loop.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_Level2Address address;
 * gc_Handle handleIndex = gc_INVALID_HANDLE;
 * gc_LoopInfo info;
 *
 * //Set the address of the loop to open. Either the address is known or
 * //must be retrieved via user-input, config file, etc.
 * address.system = 0;          //Always local
 * address.local.index1 = 1;    //The first index
 *
 * //Open an already existing loop
 * returnValue = gd_loop_openByAddress( &address, &handleIndex, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_loop_openByAddress() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   loopAddress     The address of the loop. If this address does not
 *                              refer to an loop #gc_ERROR_SERVICE_OBJECT_NOT_EXIST will
 *                              be returned.
 * @param[out]  loopHandle      Will contain the handle of the loop.
 * @param[out]  loopInfo        Will contain the information of the loop.
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
gd_loop_openByAddress( const gc_Level2Address* const loopAddress,
                       gc_Handle* const loopHandle,
                       gc_LoopInfo* const loopInfo );

/**
 * Opens an already existing loop.
 *
 * This version uses the scoped alias to find the loop.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * const char* const scopedLoopAlias = ":Loop1"
 * gc_Handle handleIndex = gc_INVALID_HANDLE;
 * gc_LoopInfo info;
 *
 * //Open an already existing loop
 * returnValue = gd_loop_openByAlias( scopedLoopAlias, &handleIndex, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_loop_openByAlias() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   scopedLoopAlias     The address of the loop. If this address
 *                                  does not refer to an loop
 *                                  #gc_ERROR_SERVICE_OBJECT_NOT_EXIST will
 *                                  be returned.
 * @param[out]  loopHandle          Will contain the handle of the loop.
 * @param[out]  loopInfo            Will contain the information of the loop.
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
gd_loop_openByAlias( const char* const scopedLoopAlias,
                     gc_Handle* const loopHandle,
                     gc_LoopInfo* const loopInfo );

/**
 * Adds an action to the given loop.
 *
 * This version uses the addresses of the loop and action.
 *
 * After the action has been successfully added to the loop it will be issued
 * every time the loop's cycle has been finished.
 *
 * An action is allowed to be added to several different loops in parallel. But
 * it's not allowed to add the same action multiple times to a single loop.
 *
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_Level2Address loopAddress = { 1, 2 };     //Already known.
 * gc_Level2Address actionAddress = { 1, 2 };   //Already known.
 *
 * //Open an already existing loop
 * returnValue = gd_loop_addActionByAddress( &loopAddress, &actionAddress );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_loop_addActionByAddress() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   loopAddress         The address of the loop.
 * @param[in]   actionAddress       The address of the action.
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
gd_loop_addActionByAddress( const gc_Level2Address* const loopAddress,
                            const gc_Level2Address* const actionAddress );

/**
 * Adds an action to the given loop.
 *
 * This version uses the aliases of the loop and action.
 *
 * After the action has been successfully added to the loop it will be issued
 * every time the loop's cycle has been finished.
 *
 * An action is allowed to be added to several different loops in parallel. But
 * it's not allowed to add the same action multiple times to a single loop.
 *
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * const char* const scopedLoopAlias = ":Loop1";       //Already known.
 * const char* const scopedActionAlias = ":Action1";   //Already known.
 *
 * //Open an already existing loop
 * returnValue = gd_loop_addActionByAlias( &scopedLoopAlias, &scopedActionAlias );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_loop_addActionByAlias() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   scopedLoopAlias     The scoped alias of the loop.
 * @param[in]   scopedActionAlias   The scoped alias of the action.
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
gd_loop_addActionByAlias( const char* const scopedLoopAlias,
                          const char* const scopedActionAlias );

/**
 * Removes an action from the given loop.
 *
 * This version uses the addresses of the loop and action.
 *
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_Level2Address loopAddress = { 1, 2 };     //Already known.
 * gc_Level2Address actionAddress = { 1, 2 };   //Already known.
 *
 * //Open an already existing loop
 * returnValue = gd_loop_remActionByAddress( &loopAddress, &actionAddress );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_loop_remActionByAddress() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   loopAddress         The address of the loop.
 * @param[in]   actionAddress       The address of the action.
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
gd_loop_remActionByAddress( const gc_Level2Address* const loopAddress,
                            const gc_Level2Address* const actionAddress );

/**
 * Removes an action from the given loop.
 *
 * This version uses the aliases of the loop and action.
 *
 * @code
 * const char* const scopedLoopAlias = ":Loop1";       //Already known.
 * const char* const scopedActionAlias = ":Action1";   //Already known.
 *
 * //Open an already existing loop
 * returnValue = gd_loop_remActionByAlias( &scopedLoopAlias, &scopedActionAlias );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_loop_remActionByAlias() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   scopedLoopAlias     The scoped alias of the loop.
 * @param[in]   scopedActionAlias   The scoped alias of the action.
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
gd_loop_remActionByAlias( const char* const scopedLoopAlias,
                          const char* const scopedActionAlias );

/**
 * Finds a loop.
 *
 * If the given name is global (e.g. "*:X") then a search through the whole
 * network is performed, which will cause a delay.
 *
 * Unlike the function #gd_addAlias the name of the loop to find must be a
 * scoped alias. This means either ":Loop", "*:Loop" must be used. A name like
 * "Loop1" is invalid and the function will return with
 * #gc_ERROR_COM_INVALID_ARGUMENT.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_Handle handleIndex = gc_INVALID_HANDLE;
 * gc_LoopInfo info;
 * gc_Level2Address address;
 * const char* const name = ":Loop1";
 *
 *
 * //Retrieve the address of the loop.
 * returnValue = gd_loop_find( name, &address );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_loop_find() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //Use the previously retrieve address to open the loop.
 * returnValue = gd_loop_openByAddress( &address, &handle, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_loop_openByAddress() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   scopedLoopAlias      The scoped alias of the loop to find.
 * @param[out]  loopAddress          Will contain the address of the loop.
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
gd_loop_find( const char* const scopedLoopAlias,
              gc_Level2Address* const loopAddress );

/**
 * Retrieves for the given loop address the gc_ActionInfo.
 *
 * This version uses the address to find the loop.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_ActionInfo info;          //Will contain the info
 * gc_Level2Address address;    //Must be set to the address of the desired loop.
 *
 * //Set the address of the loop. Either the address is known or
 * //must be retrieved via user-input, config file, etc.
 * address.system = 0;          //Always local
 * address.local.index1 = 1;    //The first index
 *
 * //Retrieve the info structure of the loop.
 * returnValue = gd_loop_getInfoByAddress( &address, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_loop_getInfoByAddress() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   loopAddress     The address of the loop.
 * @param[out]  loopInfo        Will contain the loop information.
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
gd_loop_getInfoByAddress( const gc_Level2Address* const loopAddress,
                          gc_LoopInfo* const loopInfo );

/**
 * Retrieves for the given loop alias the gc_ActionInfo.
 *
 * This version uses the alias to find the loop.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_ActionInfo info;                      //Will contain the info
 * const char* const alias = ":Action1";    //The alias of the loop.
 *
 * //Retrieve the info structure of the loop.
 * returnValue = gd_loop_getInfoByAlias( alias, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_loop_getInfoByAlias() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   scopedLoopAlias   The scoped alias of the loop.
 * @param[out]  loopInfo          Will contain the loop information.
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
gd_loop_getInfoByAlias( const char* const scopedLoopAlias,
                        gc_LoopInfo* const loopInfo );

#endif /* GAMMA_DMODEL_LOOP_H__ */
