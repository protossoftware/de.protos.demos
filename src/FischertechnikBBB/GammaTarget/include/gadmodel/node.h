#ifndef GAMMA_DMODEL_NODE_H__
#define GAMMA_DMODEL_NODE_H__

/**
 * @file
 *
 * Contains the complex interface for manipulating the nodes of the Gamma
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
 * Creates a node.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_NodeConfig config;
 * gc_Handle handleIndex = gc_INVALID_HANDLE;
 * gc_NodeInfo info;
 *
 * //Remove the node after the last using task has closed it's resource to it.
 * config.persistent = 0;
 * strcpy( config.name, "nodeXName" );      //The static name for the node.
 *
 * //Create a brand new node
 * returnValue = gd_node_create( &config, &handleIndex, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_node_create() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   nodeConfig     The configuration for the node to create.
 * @param[out]  nodeHandle     Will contain the handle of the created node.
 * @param[out]  nodeInfo       Will contain the information of the created node.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING
 */
gd_EXP gc_ErrorID gc_CALLCONV
gd_node_create( const gc_NodeConfig* const nodeConfig,
                gc_Handle* const nodeHandle,
                gc_NodeInfo* const nodeInfo );

/**
 * Opens an already existing node.
 *
 * This version uses the address to find the node.
 *
 * If the requested node was not found this function will return
 * #gc_ERROR_SERVICE_OBJECT_NOT_EXIST.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_Level2Address address;
 * gc_Handle handleIndex = gc_INVALID_HANDLE;
 * gc_NodeInfo info;
 *
 * //Set the address of the node to retrieve. Either the address is known or
 * //must be retrieved via user-input, config file, etc.
 * address.system = 0;          //Always local
 * address.local.index1 = 1;    //The first index
 *
 * //Open an already existing node
 * returnValue = gd_node_openByAddress( &address, &handleIndex, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_node_openByAddress() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   nodeAddress     The numerical address of the node.
 * @param[out]  nodeHandle      Will contain the handle of the opened node.
 * @param[out]  nodeInfo        Will contain the information of the opened node.
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
gd_node_openByAddress( const gc_Level2Address* const nodeAddress,
                       gc_Handle* const nodeHandle,
                       gc_NodeInfo* const nodeInfo );

/**
 * Opens an already existing node.
 *
 * This version uses the alias to find the node.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * const char* const alias = ":Node1";
 * gc_Handle handleIndex = gc_INVALID_HANDLE;
 * gc_NodeInfo info;
 *
 * //Open an already existing node
 * returnValue = gd_node_openByAlias( alias, &handleIndex, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_node_openByAlias() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   scopedNodeAlias       The scoped alias of the node.
 * @param[out]  nodeHandle            Will contain the handle of the node.
 * @param[out]  nodeInfo              Will contain the information of the node.
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
gd_node_openByAlias( const char* const scopedNodeAlias,
                     gc_Handle* const nodeHandle,
                     gc_NodeInfo* const nodeInfo );


/**
 * Finds a node.
 *
 * If the given name is global (e.g. "*:X") then a search through the whole
 * network is performed, which will cause a delay.
 *
 * Unlike the function #gd_addAlias the name of the node to find must be a
 * scoped name. This means either ":Node", "*:Node" must be used. A name like
 * "Node1" is invalid and the function will return with
 * #gc_ERROR_COM_INVALID_ARGUMENT.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_Handle handleIndex = gc_INVALID_HANDLE;
 * gc_NodeInfo info;
 * gc_Level2Address address;
 * const char* const name = ":Node1";     //Locally available.
 *
 * //Retrieve the address of the node.
 * returnValue = gd_node_find( name, &address );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_node_find() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //Use the previously retrieve address to open the node.
 * returnValue = gd_node_openByAddress( &address, &handle, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_node_openByAddress() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   scopedNodeAlias         The name of the node to find.
 * @param[out]  nodeAddress             Will contain the address of the node.
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
gd_node_find( const char* const scopedNodeAlias,
              gc_Level2Address* const nodeAddress );

/**
 * Retrieves for the given node address the gc_NodeInfo.
 *
 * This version uses the address to find the node.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_NodeInfo info;          //Will contain the info
 * gc_Level2Address address;    //Must be set to the address of the desired node.
 *
 * //Set the address of the node. Either the address is known or
 * //must be retrieved via user-input, config file, etc.
 * address.system = 0;          //Always local
 * address.local.index1 = 1;    //The first index
 *
 * //Retrieve the info structure of the node.
 * returnValue = gd_node_getInfoByAddress( &address, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_node_getInfoByAddress() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   nodeAddress     The address of the node.
 * @param[out]  nodeInfo        Will contain the node information.
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
gd_node_getInfoByAddress( const gc_Level2Address* const nodeAddress,
                          gc_NodeInfo* const nodeInfo );

/**
 * Retrieves for the given node alias the gc_NodeInfo.
 *
 * This version uses the alias to find the node.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_NodeInfo info;                       //Will contain the info
 * const char* const alias = ":Node1";     //The alias of the node.
 *
 * //Retrieve the info structure of the node.
 * returnValue = gd_node_getInfoByAlias( alias, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_node_getInfoByAlias() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   scopedNodeAlias   The scoped alias of the node.
 * @param[out]  nodeInfo          Will contain the node information.
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
gd_node_getInfoByAlias( const char* const scopedNodeAlias,
                        gc_NodeInfo* const nodeInfo );


#endif /* GAMMA_DMODEL_NODE_H__ */
