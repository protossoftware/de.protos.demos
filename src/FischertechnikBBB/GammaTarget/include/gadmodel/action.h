#ifndef GAMMA_DMODEL_ACTION_H__
#define GAMMA_DMODEL_ACTION_H__

/**
 * @file gadmodel/action.h
 * Contains the complex interface for manipulating actions of the Gamma
 * Data Model.
 *
 * @headerfile  action.h "gadmodel/action.h"
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
 * Function Declarations
 ******************************************************************************/
/**
 * Creates an action.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_ActionConfig config;
 * gc_Handle handleIndex = gc_INVALID_HANDLE;
 * gc_ActionInfo info;
 *
 * //Remove the action after the last using task has closed it's resource to it.
 * config.isPersistent = 0;
 * srcpy( config.name, "actionXName" );     //The static name for the action.
 *
 * //Create a brand new action
 * returnValue = gd_action_create( &config, &handleIndex, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_action_create() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   actionConfig      Contains the configuration to use for the action.
 * @param[out]  actionHandle      Will contain the handle of the action.
 * @param[out]  actionInfo        Will contain the information of the action.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING
 */
gd_EXP gc_ErrorID gc_CALLCONV
gd_action_create( const gc_ActionConfig* const actionConfig,
                  gc_Handle* const actionHandle,
                  gc_ActionInfo* const actionInfo );

/**
 * Opens an already existing action.
 *
 * This version uses the address to find the action.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_Level2Address address;
 * gc_Handle handleIndex = gc_INVALID_HANDLE;
 * gc_ActionInfo info;
 *
 * //Set the address of the action to retrieve. Either the address is known or
 * //must be retrieved via user-input, config file, etc.
 * address.system = 0;          //Always local
 * address.local.index1 = 1;    //The first index
 *
 * //Open an already existing action
 * returnValue = gd_actin_openByAddress( &address, &handleIndex, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_action_openByAddress() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   actionAddress     The address of the action.
 * @param[out]  actionHandle      Will contain the handle of the action.
 * @param[out]  actionInfo        Will contain the information of the action.
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
gd_action_openByAddress( const gc_Level2Address* const actionAddress,
                         gc_Handle* const actionHandle,
                         gc_ActionInfo* const actionInfo );


/**
 * Opens an already existing action.
 *
 * This version uses the alias to find the action.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * const char* const alias = ":Action1";
 * gc_Handle handleIndex = gc_INVALID_HANDLE;
 * gc_ActionInfo info;
 *
 * //Open an already existing action
 * returnValue = gd_action_openByAlias( alias, &handleIndex, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_action_openByAlias() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   scopedActionAlias The scoped alias of the action.
 * @param[out]  actionHandle      Will contain the handle of the action.
 * @param[out]  actionInfo        Will contain the information of the action.
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
gd_action_openByAlias( const char* const scopedActionAlias,
                       gc_Handle* const actionHandle,
                       gc_ActionInfo* const actionInfo );

/**
 * Finds an already existing action.
 *
 * If the given name is global (e.g. "*:X") then a search through the whole
 * network is performed, which will cause a delay.
 *
 * Unlike the function #gd_addAlias the name of the action to
 * find must be a scoped name. This means either ":Action", "*:Action" must
 * be used. A name like "Action1" is invalid and the function will return with
 * #gc_ERROR_COM_INVALID_ARGUMENT.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_Handle handleIndex = gc_INVALID_HANDLE;
 * gc_ActionInfo info;
 * gc_Level2Address address;
 * const char* const name = ":Action1";
 *
 * //Retrieve the address of the action.
 * returnValue = gd_action_find( name, &address );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_findAction() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //Use the previously retrieve address to open the action via it's address.
 * returnValue = gd_action_openByAddress( &address, &handle, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_action_openByAddress() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   scopedActionAlias   The scoped alias of the action to find.
 * @param[out]  actionAddress       Will contain the address of the action.
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
gd_action_find( const char* const scopedActionAlias,
                gc_Level2Address* const actionAddress );

/**
 * Retrieves for the given action address the gc_ActionInfo.
 *
 * This version uses the address to find the action.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_ActionInfo info;                     //Will contain the info
 * gc_Level2Address address = { 0, 1 };    //Already known.
 *
 * //Retrieve the info structure of the action.
 * returnValue = gd_action_getInfoByAddress( &address, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_action_getInfoByAddress() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   actionAddress     The address of the action.
 * @param[out]  actionInfo        Will contain the action information.
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
gd_action_getInfoByAddress( const gc_Level2Address* const actionAddress,
                            gc_ActionInfo* const actionInfo );

/**
 * Retrieves for the given action alias the gc_ActionInfo.
 *
 * This version uses the alias to find the action.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_ActionInfo info;                       //Will contain the info
 * const char* const alias = ":Action1";     //The alias of the action.
 *
 * //Retrieve the info structure of the action.
 * returnValue = gd_action_getInfoByAlias( alias, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_action_getInfoByAlias() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   scopedActionAlias   The scoped alias of the action.
 * @param[out]  actionInfo          Will contain the action information.
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
gd_action_getInfoByAlias( const char* const scopedActionAlias,
                          gc_ActionInfo* const actionInfo );

#endif /* GAMMA_DMODEL_ACTION_H__ */
