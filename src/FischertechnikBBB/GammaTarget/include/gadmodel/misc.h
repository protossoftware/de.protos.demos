#ifndef MISC_H_
#define MISC_H_

/**
 * @file
 * The comparison function for the addresses use the following relationship of
 * order:
 *  1. system
 *  2. index1
 *  3. index2
 *  4. index3
 *
 * For the remaining structures the comparison order is the same as the
 * declaration order!
 *
 * @author  Copyright RST Industrie Automation GmbH
 */
/******************************************************************************
 * Header File Includes
 ******************************************************************************/
#include <gacommon/errorCodes.h>
#include <gadmodel/dataTypes.h>
#include <gadmodel/platformDependencies.h>


/******************************************************************************
 * Common Data Model Manipulation Function Declaration
 ******************************************************************************/
/**
 * Closes a handle.
 *
 * The type of the handle to close is allowed to be arbitrary.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_Handle handle = gc_INVALID_HANDLE;
 *
 * //At this point its assumed, that the above handle was used and now should
 * //be cleaned up.
 *
 * //Close the used handle.
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
 * @param[in]   handle      The handle to be closed. If the close was successful
 *                          the handle will be reset to gc_INVALID_OBJECT_INDEX
 *                          to avoid reusing an obsolete handle!
 *
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING
 */
gd_EXP gc_ErrorID gc_CALLCONV
gd_closeHandle( gc_Handle* const handle );

/**
 * Adds an alias form the given #gd_AliasTypeID object type.
 *
 * The following code sample shows the usage of this function:
 * @code
 * //Create a Action
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_ActionConfig config;
 * gc_Handle handleIndex = gc_INVALID_HANDLE;
 * gc_ActionInfo info;
 *
 * //Remove the action after the last using task has closed it's resource to it.
 * config.isPersistent = 0;
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
 *
 * //Add an alias for this action
 * returnValue = gd_addAlias( gd_ALIAS_TYPE_ID_ACTION, handle, "Action1" );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_addAlias() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @note    The aliasType will be used to validate the handle type. But it's also
 *          planned remove this explicit quote.
 *
 * @param[in]   aliasType   Must specify the type of object. See #gd_AliasTypeID.
 * @param[in]   handle      The handle of the object.
 * @param[in]   alias       The alias to remove from the specified object.
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
gd_addAlias( const gd_AliasTypeID aliasType,
             const gc_Handle handle,
             const char* const alias );

/**
 * Removes an alias form the given #gd_AliasTypeID object type.
 *
 * The following code sample shows the usage of this function:
 * @code
 * //A action has been created previously...
 *
 * //Remove the existing alias from the action.
 * returnValue = gd_remAlias( gd_ALIAS_TYPE_ID_ACTION, "Action1" );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_remAlias() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @note    The aliasType will be used to validate the handle type. But it's also
 *          planned remove this explicit quote.
 *
 * @param[in]   aliasType   Must specify the type of object. See #gd_AliasTypeID.
 * @param[in]   alias       The alias to remove from the specified object.
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
gd_removeAlias( const gd_AliasTypeID aliasType,
                const char* const alias );

/**
 * Sets the default scope for all aliases used by this API, if none are
 * explicitly quoted by the user.
 *
 * All API functions, using scoped aliases require a scope. To ease usage of
 * the GADMODEL interface this function allows to set a default scope if
 * non was specified by the function call. For more information about the
 * available scopes please see #gd_DefaultScope
 *
 * @param[in]   defaultScope        The default scope to use if the user
 *                                  did not specify one explicitly.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 */
gd_EXP gc_ErrorID gc_CALLCONV
gd_setDefaultScope( const gd_DefaultScope defaultScope );


/**
 * Retrieves the currently active default scope.
 *
 * @param[out]  defaultScope        The default scope to use if the user
 *                                  did not specify one explicitly.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 */
gd_EXP gc_ErrorID gc_CALLCONV
gd_getDefaultScope( gd_DefaultScope* defaultScope );


/**
 * Activates/Deactivates the automatic creation of convenience alias names
 * in case a pv/fifo array gets created.
 *
 * @note:   If you don't change this setting the API will internally always
 *          use the statically preconfigured default of 'TRUE'.
 *
 * @param[in]   doAddConvenienceAlias   True: An additional convenience alias
 *                                            will be created.
 *                                      False: Only the user-given name will be
 *                                             used for the array.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 */
gd_EXP gc_ErrorID gc_CALLCONV
gd_setAutomaticConvenienceAlias( const bool doAddConvenienceAlias );


/**
 * Retrieves the currently set default action for creating convenience aliases.
 *
 * @param[in,out]   doAddConvenienceAlias   Will hold the current default
 *                                          action for creating convenience
 *                                          aliases.
 *                                          True: Creating a pv/fifo array
 *                                                will also create a convenience
 *                                                alias.
 *                                          False: Creating a pv/fifo array
 *                                                 will only create the name
 *                                                 given by the user and not
 *                                                 additional alias.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 */
gd_EXP gc_ErrorID gc_CALLCONV
gd_getAutomaticConvenienceAlias( bool* const doAddConvenienceAlias );


/******************************************************************************
 * Interface - GADMODEL Library Informations
 ******************************************************************************/
/**
 * Retrieves the version of the GADMODEL library.
 *
 * The following code sample shows how to retrieve the GADMODEL version information:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_VersionNumber versionNumer = { 0, 0, 0, 0 };
 *
 * //(1) Get the version number.
 * returnValue = gd_getVersion( &versionNumber );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_getVersion() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //(2) Write it onto stdout.
 * printf( "GADMODEL version: %u.%u.%u.%u\n", versionNumber.major,
 *                                            versionNumber.minor,
 *                                            versionNumber.release
 *                                            versionNumber.build );
 * @endcode
 *
 * @param[out]  versionNumber   Will contain the version number;
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT
 */
gd_EXP gc_ErrorID gc_CALLCONV
gd_getVersion( gc_VersionNumber* const versionNumber );

#endif /* MISC_H_ */
