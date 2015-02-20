#ifndef GAMMA_DMODEL_LOCK_H__
#define GAMMA_DMODEL_LOCK_H__

/**
 * @file
 *
 * Contains the complex interface for manipulating groups of the Gamma
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
 * Function Declarations
 ******************************************************************************/
/**
 * Creates a group.
 *
 * This version uses the addresses of the references groups and memory.
 *
 * A group defines a synchronized access primitive. If consists of several
 * groups and one memory.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_Level3Address memoryAddress = { 0, 1, 2 };         //Already known.
 * gc_Level2Address netActionAddress = { 0, 10  };       //Already known.
 * gc_Level2Address sigActionAddress = { 0, 11 };        //Already known.
 * gc_Level2Address logActionAddress = { 0, 12 };        //Already known.
 * gc_GroupConfig config;
 * gc_Handle handle = gc_INVALID_HANDLE;
 * gc_GroupInfo info;
 *
 * //Remove the node after the last using task has closed it's resource to it.
 * config.isPersistent = false;
 * config.isLocked = false;                 //Initial locking state is false.
 * strcpy( config.name, "GroupXName" );     //The static name of the group.
 *
 * //Create a brand new group.
 * returnValue = gd_group_createByAddress( &memoryAddress, &netActionAddress
 *                                         &sigActionAddress, & logActionAddress
 *                                         &config, &handle, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_group_createByAddress() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 *
 * @param[in]   memoryAddress       The address of the memory where the group
 *                                  will exist.
 * @param[in]   sigActionAddress    The address of the group used for signaling.
 *                                  If 0 none will be used.
 * @param[in]   logActionAddress    The address of the group used for logging.
 *                                  If 0 none will be used.
 * @param[in]   groupConfig         The configuration for the group to create.
 * @param[out]  groupHandle         Will contain the handle of the group.
 * @param[out]  groupInfo           Will contain the information of the group.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING
 */
gd_EXP gc_ErrorID gc_CALLCONV
gd_group_createByAddress( const gc_Level3Address* const memoryAddress,
                          const gc_Level2Address* const sigActionAddress,
                          const gc_Level2Address* const logActionAddress,
                          const gc_GroupConfig* const groupConfig,
                          gc_Handle* const groupHandle,
                          gc_GroupInfo* const groupInfo );

/**
 * Creates a group.
 *
 * This version uses the scoped aliases of the references groups and memory.
 *
 * A group defines a synchronized access primitive. If consists of several
 * groups and one memory.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * const char* const scopedMemoryAlias = ":Memory1";            //Already known.
 * const char* const scopedNetGroupAlias = ":NetGroup";       //Already known.
 * const char* const scopedSigGroupAlias = ":SigGroup";       //Already known.
 * const char* const scopedlogGroupAlias = ":LogGroup";       //Already known.
 * gc_GroupConfig config;
 * gc_Handle handle = gc_INVALID_HANDLE;
 * gc_GroupInfo info;
 *
 * //Remove the node after the last using task has closed it's resource to it.
 * config.isPersistent = false;
 * config.isLocked = false;                 //Initial locking state is false.
 * strcpy( config.name, "GroupXName" );     //The static name of the group.
 *
 * //Create a brand new group.
 * returnValue = gd_group_createByAlias( &scopedMemoryAlias, &scopedNetGroupAlias
 *                                       &scopedSigGroupAlias, &scopedLogGroupAlias
 *                                       &config, &handle, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_group_createByAlias() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   scopedMemoryAlias       The scoped alias of the memory memory where
 *                                      the group will exist.
 * @param[in]   scopedSigActionAlias    The scoped alias of the group used for
 *                                      signaling.
 *                                      If 0 none will be used.
 * @param[in]   scopedLogActionAlias    The scoped alias of the group used for
 *                                      logging.
 *                                      If 0 none will be used.
 * @param[in]   groupConfig             The configuration for the group to create.
 * @param[out]  groupHandle             Will contain the handle of the group.
 * @param[out]  groupInfo               Will contain the information of the group.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING
 */
gd_EXP gc_ErrorID gc_CALLCONV
gd_group_createByAlias( const char* const scopedMemoryAlias,
                        const char* const scopedSigActionAlias,
                        const char* const scopedLogActionAlias,
                        const gc_GroupConfig* const groupConfig,
                        gc_Handle* const groupHandle,
                        gc_GroupInfo* const groupInfo );

/**
 * Opens an already existing group.
 *
 * This version uses the addresses of the group.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_Level4Address groupAddress = { 0, 1, 2, 3, };    //Already known.
 * gc_Handle handle = gc_INVALID_HANDLE;
 * gc_GroupInfo info;
 *
 * //Open an already existing group.
 * returnValue = gd_group_openByAddress( &groupAddress, &handle, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_group_openByAddress() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   groupAddress        The address of the group to open.
 * @param[out]  groupHandle         Will contain the handle of the group.
 * @param[out]  groupInfo           Will contain the information of the group.
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
gd_group_openByAddress( const gc_Level4Address* groupAddress,
                        gc_Handle* const groupHandle,
                        gc_GroupInfo* const groupInfo );

/**
 * Opens an already existing group.
 *
 * This version uses the scoped alias of the group.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * const char* const scopedGroupAlias = ":NodeX.MemoryY.Group1";    //Already known.
 * gc_Handle handle = gc_INVALID_HANDLE;
 * gc_GroupInfo info;
 *
 * //Open an already existing group.
 * returnValue = gd_group_openByAlias( scopedGroupAlias, &handle, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_group_openByAlias() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   scopedGroupAlias    The scoped alias of the group to open.
 * @param[out]  groupHandle         Will contain the handle of the group.
 * @param[out]  groupInfo           Will contain the information of the group.
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
gd_group_openByAlias( const char* const scopedGroupAlias,
                      gc_Handle* const groupHandle,
                      gc_GroupInfo* const groupInfo );


/**
 * Finds an already existing group.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * const char* const name = ":Group1";
 * gc_Level4Address groupAddress;
 *
 * //Retrieve the address of the group.
 * returnValue = gd_group_find( name, &groupAddress );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_group_find() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   scopedGroupAlias    The scoped name of the group.
 * @param[out]  groupAddress        Will contain the address of the found group.
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
gd_group_find( const char* const scopedGroupAlias,
               gc_Level4Address* const groupAddress );

/**
 * Retrieves for the given group address the gc_GroupInfo.
 *
 * This version uses the address to find the group.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_GroupInfo info;                      //Will contain the info
 * gc_Level2Address address = { 0, 1 };    //Already known.
 *
 * //Retrieve the info structure of the group.
 * returnValue = gd_group_getInfoByAddress( &address, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_group_getInfoByAddress() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   groupAddress     The address of the group.
 * @param[out]  groupInfo        Will contain the group information.
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
gd_group_getInfoByAddress( const gc_Level4Address* const groupAddress,
                           gc_GroupInfo* const groupInfo );

/**
 * Retrieves for the given group alias the gc_GroupInfo.
 *
 * This version uses the alias to find the group.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_GroupInfo info;                       //Will contain the info
 * const char* const alias = ":Group1";     //The alias of the group.
 *
 * //Retrieve the info structure of the group.
 * returnValue = gd_group_getInfoByAlias( alias, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_group_getInfoByAlias() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   scopedGroupAlias   The scoped alias of the group.
 * @param[out]  groupInfo          Will contain the group information.
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
gd_group_getInfoByAlias( const char* const scopedGroupAlias,
                         gc_GroupInfo* const groupInfo );

#endif /* GAMMA_DMODEL_LOCK_H__ */
