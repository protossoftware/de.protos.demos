#ifndef GAMMA_DMODEL_MEMORY_H__
#define GAMMA_DMODEL_MEMORY_H__

/**
 * @file
 *
 * Contains the complex interface for manipulating the memory objects of the Gamma
 * Data Model.
 *
 * Currently only SHM (shared memory) objects can be created (see gd_shm_xxx),
 * but the remaining interface uses the generic term 'memory' (see gd_memory_xxx).
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
 * Creates a SHM (shared memory) memory object.
 *
 * This version identifies the associated node by its address.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_Level2Address nodeAddress = { 0, 123 };    //already known!
 * gc_SHMConfig config;
 * gc_Handle handle = gc_INVALID_HANDLE;
 * gc_MemoryInfo info;
 *
 * //Setup the memory configuration
 * config.persistent = 0;   //Remove SHM after the last task has closed its handle to it.
 * config.size = 10000;     //Initial size in bytes.
 * config.permission = S_IRWXU | S_IRWXG | S_IRWXO;  //Linux-dependent setting using 0666 file permission.
 * strcpy( config.user, "userX" );      //The name of the owner is "userX"
 * strcpy( config.group, "groupX" );    //The group of ownership is "groupX"
 * strcpy( config.name, "shmXName" );   //The static name of the SHM.
 *
 * //Create a new memory
 * returnValue = gd_shm_createByAddress( &nodeAddress, &config, &handle, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_memory_createByAddress() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   nodeAddress      The address of the node, where the memory should
 *                               be created.
 * @param[in]   memoryConfig     The configuration for the memory to create.
 * @param[out]  memoryHandle     Will contain the handle of the created memory.
 * @param[out]  memoryInfo       Will contain the information of the created memory.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING
 */
gd_EXP gc_ErrorID gc_CALLCONV
gd_shm_createByAddress( const gc_Level2Address* const nodeAddress,
                        const gc_SHMConfig* const memoryConfig,
                        gc_Handle* const memoryHandle,
                        gc_MemoryInfo* const memoryInfo );

/**
 * Creates a SHM (shared memory) memory object.
 *
 * This version identifies the associated node by its scoped alias.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * const char* const scopedNodeAlias = ":Node1";
 * gc_SHMConfig config;
 * gc_Handle handleIndex = gc_INVALID_HANDLE;
 * gc_MemoryInfo info;
 *
 * //Setup the memory configuration
 * config.persistent = 0;   //Remove SHM after the last task has closed its handle to it.
 * config.size = 10000;     //Initial size in bytes.
 * config.permission = S_IRWXU | S_IRWXG | S_IRWXO;  //Linux-dependent setting using 0666 file permission.
 * strcpy( config.user, "userX" );      //The name of the owner is "userX"
 * strcpy( config.group, "groupX" );    //The group of ownership is "groupX"
 * strcpy( config.name, "shmXName" );   //The static name of the SHM.
 *
 * //Create a new memory
 * returnValue = gd_shm_createByAlias( scopedNodeAlias, &config, memoryAlias, &handleIndex, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_memory_createByAlias() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   scopedNodeAlias  The scoped alias of the node, where the memory
 *                               should be created.
 * @param[in]   memoryConfig     The configuration for the memory to create.
 * @param[out]  memoryHandle     Will contain the handle of the created memory.
 * @param[out]  memoryInfo       Will contain the information of the created memory.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING
 */
gd_EXP gc_ErrorID gc_CALLCONV
gd_shm_createByAlias( const char* const scopedNodeAlias,
                      const gc_SHMConfig* const memoryConfig,
                      gc_Handle* const memoryHandle,
                      gc_MemoryInfo* const memoryInfo );

/**
 * Opens an already existing memory.
 *
 * This version uses the address to find the memory.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_Level3Address memoryAddress = { 0, 1, 2 }; //Already known.
 * gc_MemoryInfo info;
 *
 * //Open an already existing memory
 * returnValue = gd_memory_openByAddress( &memoryAddress, &handleIndex, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_memory_openByAddress() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   memoryAddress   The address of the memory to open.
 * @param[out]  memoryHandle    Will contain the handle of the opened memory.
 * @param[out]  memoryInfo      Will contain the information of the opened memory.
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
gd_memory_openByAddress( const gc_Level3Address* const memoryAddress,
                         gc_Handle* const memoryHandle,
                         gc_MemoryInfo* const memoryInfo );
/**
 * Opens an already existing memory.
 *
 * This version uses the scoped alias to find the memory.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * const char* const scopedMemoryAlias = ":NodeX.Memory1";
 * gc_MemoryInfo info;
 *
 * //Open an already existing memory
 * returnValue = gd_memory_openByAlias( scopedMemoryAlias, &handleIndex, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_memory_openByAddress() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   scopedMemoryAlias  The address of the memory to open.
 * @param[out]  memoryHandle       Will contain the handle of the opened memory.
 * @param[out]  memoryInfo         Will contain the information of the opened memory.
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
gd_memory_openByAlias( const char* const scopedMemoryAlias,
                       gc_Handle* const memoryHandle,
                       gc_MemoryInfo* const memoryInfo );

/**
 * Finds an already existing memory.
 *
 * Unlike the function #gd_addAlias the name of the memory to
 * find must be a scoped name. This means either ":Memory", "*:Memory" must
 * be used. A name like "Memory1" is invalid and the function will return with
 * #gc_ERROR_COM_INVALID_ARGUMENT.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * const char* const name = ":Memory1";
 * gc_Level3Address address;
 *
 * //Retrieve the index of the memory.
 * returnValue = gd_memory_find( name, &address );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_memory_find() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   scopedMemoryAlias   The scoped alias of the memory to find.
 * @param[out]  memoryAddress       Will contain the address of the found memory.
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
gd_memory_find( const char* const scopedMemoryAlias,
                gc_Level3Address* const memoryAddress );

/**
 * Retrieves for the given memory address the gc_MemoryInfo.
 *
 * This version uses the address to find the memory.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_MemoryInfo info;                        //Will contain the info
 * gc_Level3Address address = { 0, 1, 2 };    //Already known
 *
 * //Retrieve the info structure of the memory.
 * returnValue = gd_memory_getInfoByAddress( &address, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_memory_getInfoByAddress() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   memoryAddress     The address of the memory.
 * @param[out]  memoryInfo        Will contain the memory information.
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
gd_memory_getInfoByAddress( const gc_Level3Address* const memoryAddress,
                            gc_MemoryInfo* const memoryInfo );

/**
 * Retrieves for the given memory alias the gc_MemoryInfo.
 *
 * This version uses the alias to find the memory.
 *
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_MemoryInfo info;                       //Will contain the info
 * const char* const alias = ":Memory1";     //The alias of the memory.
 *
 * //Retrieve the info structure of the memory.
 * returnValue = gd_memory_getInfoByAlias( alias, &info );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_memory_getInfoByAlias() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   scopedMemoryAlias   The scoped alias of the memory.
 * @param[out]  memoryInfo          Will contain the memory information.
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
gd_memory_getInfoByAlias( const char* const scopedMemoryAlias,
                          gc_MemoryInfo* const memoryInfo );

#endif /* GAMMA_DMODEL_MEMORY_H__ */
