#ifndef GAMMA_API_BROWSING_H__
#define GAMMA_API_BROWSING_H__

/**
 * @file
 * Contains the browsing interface.
 *
 * <h3> Overview </h3>
 *
 * The browsing API is focus on two use cases:
 *  - Reading all names and displaying it. This is the case if a snapshot of the
 *    complete Gamma network should be made an every information is of relevance.
 *  - Navigating to specific levels and only displaying specific values. This
 *    is the case if a GUI displays the information of a Gamma network by using
 *    a tree view and only certain information are relevant.
 *
 * The first use case requires the functions:
 *  - ga_browse_startByIndices or ga_browse_startByAddress
 *  - ga_browse_getInfo or ga_browse_getIndices or ga_browse_getStrings
 *  - ga_browse_stop
 *
 *
 * The second use case requires the functions:
 *  - #ga_browse_getSpecInfoByIndices or #ga_browse_getSpecInfoByAddress

 *
 * <h3> Logical Browsing Structure </h3>
 *
 * The following graph shows how the elements (primitive) of the Browsing
 * API are related with each other. This is of importance to fully
 * understand the addressing.
 *
 * <pre>
 *
 * Level 1    Level 2    Level 3    Level 4     Level 5     Level 6
 * (system)   (index1)   (index2)   (index3)    (index4)    (index5)
 *
 * system (no aliases)
 *   |
 *   |------- node
 *   |          |
 *   |          |------- memory
 *   |                     |
 *   |                     |------- group
 *   |                                |
 *   |                                |------- PVArray
 *   |                                              |
 *   |                                              |------- PV array index
 *   |
 *   |------- action
 *   |
 *   |------- loop
 *   |
 *   |------- task
 *   |
 *   |------- IO
 *   |         |
 *   |         |------- I/O channel
 *   |
 *   |------- scheduler
 *             |
 *             |------- schedulerSlot
 *
 * </pre>
 *
 * The above graph consists of five levels. Each level represents an index.
 * The first and the second level is delimited by a ':' sign and all other
 * levels are delimited by a '.' sign. For example a variable has always
 * an address which consists of three levels/indices
 * "SystemIndex:NodeIndex.VariableIndex".
 *
 * In addition some primitives have aliases. An alias consists of at least
 * one name and can have up to N. For example a Variable can have the alias
 * "node1.array1.subarray2.variableX", "yet_another_name_for_the_variable", etc.
 * It's important to know that the alias of a variable has <b>nothing</b> to do
 * with the logical structure!
 *
 * <h3> Sample: Iterate Over All Variables </h3>
 *
 * For brevity this sample does <b>not</b> check error codes. Don't do this
 * in production code!
 *
 * The iteration over the variables will build a formatted list of the variables
 * within the current gamma network. A sample of how such a list looks is given below:
 * <pre>
 * System [0]
 *     Node [0]
 *         Memory [0]
 *             Group [0]
 *                 Variable [0]
 *                 Variable [1]
 *                 Variable [2]
 *     Node [1]
 *         Memory [0]
 *             Group [0]
 *                 Variable [0]
 * System [1]
 * System [2]
 *     Node [0]
 *         Memory [0]
 *             Group [0]
 *                 Variable [0]
 * </pre>
 *
 * @code
 * //
 * // THIS IS JUST DEMO CODE and COMES WITHOUT ANY ERROR HANDLING!
 * //
 * #define BROWSER_INFO_SIZE           ((uint32_t)20)
 *
 * void printVariables( void )
 * {
 *     size_t i = 0;
 *     size_t j = 0;
 *     size_t k = 0;
 *     size_t l = 0;
 *     size_t m = 0;
 *
 *     size_t numElementsSystem = 0;
 *     size_t numElementsNode = 0;
 *     size_t numElementsMemory = 0;
 *     size_t numElementsGroup = 0;
 *     size_t numElementsPVArray = 0;
 *
 *     gc_BrowserInfo systemInfo[BROWSER_INFO_SIZE];
 *     gc_BrowserInfo nodeInfo[BROWSER_INFO_SIZE];
 *     gc_BrowserInfo memoryInfo[BROWSER_INFO_SIZE];
 *     gc_BrowserInfo groupInfo[BROWSER_INFO_SIZE];
 *     gc_BrowserInfo pvArrayInfo[BROWSER_INFO_SIZE];
 *
 *     //First Level: Systems
 *     ga_browse_startByIndices( gc_BROWSING_TYPE_SYSTEM,
 *                               0, 0, 0, 0, 0, &numElementsSystem);
 *     ga_browse_getInfo( systemInfo, numElementsSystem, 0, 0 );
 *
 *     for( i = 0; i < numElementsSystem; ++i )
 *     {
 *         const gc_SystemInfo* curSystemInfo = &systemInfo[i].info.system;
 *         printf( "System [%d]\n", curSystemInfo->address );
 *
 *         //Second Level: Nodes of system
 *         ga_browse_startByIndices( gc_BROWSING_TYPE_NODE,
 *                                   curSystemInfo->address,
 *                                   0, 0, 0, 0,  &numElementsNode );
 *         ga_browse_getInfo( nodeInfo, numElementsNode, 0, 0 );
 *         ga_browse_stop();
 *
 *         for( j = 0; j < numElementsNode; ++j )
 *         {
 *             const gc_NodeInfo* curNodeInfo = &nodeInfo[j].info.node;
 *             printf( "    Node [%d]\n", curNodeInfo->address.index1 );
 *
 *             //Third Level: Memories of node
 *             ga_browse_startByIndices( gc_BROWSING_TYPE_MEMORY,
 *                                       curNodeInfo->address.system,
 *                                       curNodeInfo->address.index1,
 *                                       0, 0, 0, &numElementsMemory );
 *             ga_browse_getInfo( memoryInfo, numElementsMemory, 0, 0 );
 *             ga_browse_stop();
 *
 *             for( k = 0; k < numElementsMemory; ++k )
 *             {
 *                 const gc_MemoryInfo* curMemoryInfo = &memoryInfo[k].info.memory;
 *                 printf( "        Memory [%d]\n", curMemoryInfo->address.index2 );
 *
 *                 //Fourth Level: Groups of memory
 *                 ga_browse_startByIndices( gc_BROWSING_TYPE_GROUP,
 *                                           curMemoryInfo->address.system,
 *                                           curMemoryInfo->address.index1,
 *                                           curMemoryInfo->address.index2,
 *                                           0, 0, &numElementsGroup );
 *                 ga_browse_getInfo( groupInfo, numElementsGroup, 0, 0 );
 *                 ga_browse_stop();
 *
 *                 for( l = 0; l < numElementsGroup; ++l )
 *                 {
 *                     const gc_GroupInfo* curGroupInfo = &groupInfo[l].info.group;
 *                     printf( "            Group [%d]\n", curGroupInfo->address.index3 );
 *
 *                     //Fifth Level: PVArrays of group
 *                     ga_browse_startByAddress( gc_BROWSING_TYPE_PV_ARRAY,
 *                                               (const gc_Level5Address*)&curGroupInfo->address,
 *                                               &numElementsPVArray );
 *                     ga_browse_getInfo( pvArrayInfo, numElementsPVArray, 0, 0 );
 *                     ga_browse_stop();
 *
 *                     for( m = 0; m < numElementsPVArray; ++m )
 *                     {
 *                         printf( "                PVArray [%d]\n", pvArrayInfo[m].info.pvArray.address.index4 );
 *                     }
 *                 }
 *             }
 *         }
 *     }
 * }
 *
 * @endcode
 *
 * <h3> MT-Issues and State-Safety </h3>
 *
 * The Gamma Service stores all browsing information for a connected process in
 * an internal data structure. These information are only associated with the
 * process as a whole. Therefore if multiple threads within the process are using
 * the browsing interface undefined side-effect might occur. Therefore, on a
 * process-level, browsing can be thought of as a non-MT-safe singleton.
 *
 * Despite the above restriction browsing is still safe to be used in parallel
 * from multiple processes.
 *
 * <h3> Miscellaneous </h3>
 *
 * Please note the following miscellaneous hints:
 *  - The browsing interface uses the size_t type to index the user-data array,
 *    which are either input or output of the browsing API functions. In case
 *    systems with 32 bit and 64 bit are used the internal routines always use
 *    32 bits.
 *
 * @author  Copyright RST Industrie Automation GmbH
 */
/******************************************************************************
 * Header File Includes
 ******************************************************************************/
#include <gacommon/errorCodes.h>
#include <gaapi/platformDependencies.h>
#include <gaapi/dataTypes.h>


/******************************************************************************
 * Browsing Interface - Function Declarations
 ******************************************************************************/
/**
 * Starts browsing for the given #gc_BrowsingType. The system and index
 * parameters are used depending on the given browsingType.
 *
 * The call will return after a snapshot of the current system information has
 * been created. Only after this the functions ga_browse_getInfo,
 * ga_browse_getIndices and ga_browse_getStrings can be used to retrieve
 * the information.
 *
 * Successive call of ga_browse_startByIndices or ga_browse_startByAddress will
 * implicitly call ga_browse_stop to free claimed resources. But when browsing
 * is finished and no further calls to ga_browse_startByIndices or
 * ga_browse_startByAddress are issued the user must explicitly call
 * ga_browse_stop to free claimed resources.
 *
 * Depending on the used browsing type either ga_browse_getIndices or
 * ga_browse_getStrings is valid to be used. The function ga_browse_getInfo
 * is safe to be called for all types.
 *
 * <pre>
 * browsing type                           ga_browse_getIndices   ga_browse_getStrings
 * #gc_BROWSING_TYPE_SYSTEM                yes                    no
 * #gc_BROWSING_TYPE_NODE                  yes                    no
 * #gc_BROWSING_TYPE_ACTION                yes                    no
 * #gc_BROWSING_TYPE_LOOP                  yes                    no
 * #gc_BROWSING_TYPE_TASK                  yes                    no
 * #gc_BROWSING_TYPE_IO                    yes                    no
 * #gc_BROWSING_TYPE_SCHEDULER             yes                    no
 * #gc_BROWSING_TYPE_MEMORY                yes                    no
 * #gc_BROWSING_TYPE_GROUP                 yes                    no
 * #gc_BROWSING_TYPE_PV_ARRAY              yes                    no
 * #gc_BROWSING_TYPE_IO_INPUT              yes                    no
 * #gc_BROWSING_TYPE_IO_OUTPUT             yes                    no
 * #gc_BROWSING_TYPE_SCHEDULER_SLOT        yes                    no
 * #gc_BROWSING_TYPE_NODE_ALIAS            no                     yes
 * #gc_BROWSING_TYPE_ACTION_ALIAS          no                     yes
 * #gc_BROWSING_TYPE_LOOP_ALIAS            no                     yes
 * #gc_BROWSING_TYPE_TASK_ALIAS            no                     yes
 * #gc_BROWSING_TYPE_SCHEDULER_ALIAS       no                     yes
 * #gc_BROWSING_TYPE_MEMORY_ALIAS          no                     yes
 * #gc_BROWSING_TYPE_GROUP_ALIAS           no                     yes
 * #gc_BROWSING_TYPE_PV_ARRAY_ALIAS        no                     yes
 * #gc_BROWSING_TYPE_SCHEDULER_SLOT_ALIAS  no                     yes
 * </pre>
 *
 * The system and index parameters have the following valid combinations:
 *
 * <pre>
 * browsing type                           system  index1  index2  index3  index4
 * #gc_BROWSING_TYPE_SYSTEM                no      no      no      no      no
 * #gc_BROWSING_TYPE_NODE                  yes     no      no      no      no
 * #gc_BROWSING_TYPE_ACTION                yes     no      no      no      no
 * #gc_BROWSING_TYPE_LOOP                  yes     no      no      no      no
 * #gc_BROWSING_TYPE_TASK                  yes     no      no      no      no
 * #gc_BROWSING_TYPE_IO                    yes     no      no      no      no
 * #gc_BROWSING_TYPE_SCHEDULER             yes     no      no      no      no
 * #gc_BROWSING_TYPE_MEMORY                yes     yes     no      no      no
 * #gc_BROWSING_TYPE_IO_INPUT              yes     yes     no      no      no
 * #gc_BROWSING_TYPE_IO_OUTPUT             yes     yes     no      no      no
 * #gc_BROWSING_TYPE_SCHEDULER_SLOT        yes     yes     no      no      no
 * #gc_BROWSING_TYPE_NODE_ALIAS            yes     yes     no      no      no
 * #gc_BROWSING_TYPE_ACTION_ALIAS          yes     yes     no      no      no
 * #gc_BROWSING_TYPE_LOOP_ALIAS            yes     yes     no      no      no
 * #gc_BROWSING_TYPE_TASK_ALIAS            yes     yes     no      no      no
 * #gc_BROWSING_TYPE_GROUP                 yes     yes     yes     no      no
 * #gc_BROWSING_TYPE_MEMORY_ALIAS          yes     yes     yes     no      no
 * #gc_BROWSING_TYPE_SCHEDULER_SLOT_ALIAS  yes     yes     yes     no      no
 * #gc_BROWSING_TYPE_GROUP_ALIAS           yes     yes     yes     yes     no
 * #gc_BROWSING_TYPE_PV_ARRAY              yes     yes     yes     yes     no
 * #gc_BROWSING_TYPE_PV_ARRAY_ALIAS        yes     yes     yes     yes     yes
 * </pre>
 *
 * Internally this call retrieves the information from the data model and stores
 * it in an array.
 *
 * @param[in]   type            The browsing type of interest.
 * @param[in]   system          The system index.
 * @param[in]   index1          The index1. It's interpretation depends on the
 *                              used browsingType.
 * @param[in]   index2          The index2. It's interpretation depends on the
 *                              used browsingType.
 * @param[in]   index3          The index3. It's interpretation depends on the
 *                              used browsingType.
 * @param[in]   index4          The index4. It's interpretation depends on the
 *                              used browsingType.
 * @param[out]  numElements     Number of retrieve elements.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_browse_startByIndices( const gc_BrowsingType type,
                          const gc_SystemAddress system,
                          const gc_ObjectIndex index1,
                          const gc_ObjectIndex index2,
                          const gc_ObjectIndex index3,
                          const gc_ObjectIndex index4,
                          size_t* numElements );
/**
 * The behavior of this function is analog to ga_browse_startByIndices with the
 * only difference that instead of indices it uses gc_Level5Address types.
 *
 * The following code sample shows how to use the address:
 * @code
 *
 * size_t numElements = 0;
 * gc_SystemAddress sysAddress = 123;
 *
 * ga_browse_startByAddress( gc_BROWSING_TYPE_NODE,
 *                           (const gc_Level5Address*) &sysAddress,
 *                           &numElements );
 * ga_browse_stop();
 *
 * numElements = 0;
 * gc_Level3Address level3Address;
 * level3Address.system = 123;
 * level3Address.index1 = 1;
 * level3Address.index2 = 2;
 *
 * ga_browse_startByAddress( gc_BROWSING_TYPE_GROUP,
 *                           (const gc_Level5Address*) &level3Address,
 *                           &numElements );
 * ga_browse_stop();
 *
 * @endcode
 *
 * @param[in]   type            The browsing type of interest.
 * @param[in]   address         The address of the element of interest.
 * @param[out]  numElements     Number of retrieve elements.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_browse_startByAddress( const gc_BrowsingType type,
                          const gc_Level5Address* const address,
                          size_t* numElements );

/**
 * Retrieve enumerated information.
 * The method will not return more than max. If the number of requested elements
 * is less or equal to available elements, the method will return it all at once.
 *
 * Internally a part of the result vector is enriched with additional object information
 * and returned to the API.
 *
 * If ga_browse_startByIndices or ga_browse_startByAddress was not called
 * previously this function will return an error.
 *
 * If the caller knows the number of indices to retrieve the parameters
 * returnedIndicies and remainingIndices are optionally. Otherwise if the number
 * of indices to retrieve is unknown these parameters should be set and evaluated
 * by the caller.
 *
 * @param[out]  infos               Pointer to user buffer for storing the infos.
 * @param[in]   max                 Size of the user buffer.
 * @param[out]  returned            Number of returned elements. If this parameter
 *                                  is 0 it will not be written.
 * @param[out]  remaining           The number of remaining elements to retrieve.
 *                                  If this parameter is 0 it will not be written.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_MALLOC_FAILED \n
 *          #gc_ERROR_COM_INTERNAL_ERROR
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_browse_getInfo( gc_BrowserInfo* infos,
                   const size_t max,
                   size_t* returned,
                   size_t* remaining );

/**
 * Retrieves the full or only a part of the indices for the previously requested
 * browsing type. Calling this function will consume the indices.
 * The method will not return more than max. If the number of requested elements
 * is less or equal to available elements, the method will return it all at once.
 *
 * If ga_browse_startByIndices or ga_browse_startByAddress was not called
 * previously this function will return an error.
 *
 * If the caller knows the number of indices to retrieve the parameters
 * returnedIndicies and remainingIndices are optionally. Otherwise if the number
 * of indices to retrieve is unknown these parameters should be set and evaluated
 * by the caller.
 *
 * @note    This function will issue an RPC to the Gamma service.
 *
 * @param[out]  indices             Pointer to user buffer for storing the indices.
 * @param[in]   max                 Size of the user buffer. The number must be
 *                                  greater than 0.
 * @param[out]  returned            Number of returned indices. If this parameter
 *                                  0 it will not be written.
 * @param[out]  remaining           The number of remaining indices to retrieve.
 *                                  If this parameter is 0 it will not be written.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_browse_getIndices( gc_ObjectIndex* indices,
                      const size_t max,
                      size_t* returned,
                      size_t* remaining );

/**
 * Retrieves the strings for the previously requested browsing type.
 * The method will not return more than max. If the number of requested elements
 * is less or equal to available elements, the method will return it all at once.
 *
 * If ga_browse_startByIndices or ga_browse_startByAddress was not called
 * previously this function will return an error.
 *
 * If the caller knows the number of indices to retrieve the parameters
 * returnedIndicies and remainingIndices are optionally. Otherwise if the number
 * of indices to retrieve is unknown these parameters should be set and evaluated
 * by the caller.
 *
 * @param[out]  strings             Pointer to user buffer for storing the strings.
 *                                  If the retrieved string was too long to be
 *                                  stored in one of the strings' elements
 *                                  the function returns gc_ERROR_COM_STRING_TRUNCATED
 *                                  but does not abort copying the remaining
 *                                  strings in the strings buffer! Therefore
 *                                  such this error will indicated that <b>
 *                                  at least</b> one string was truncated.
 * @param[in]   max                 Size of the user buffer. The number must be
 *                                  greater than 0.
 * @param[out]  returned            Number of returned indices. If this parameter
 *                                  0 it will not be written.
 * @param[out]  remaining           The number of remaining indices to retrieve.
 *                                  If this parameter is 0 it will not be written.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_MALLOC_FAILED
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_browse_getStrings( gc_String1K* strings,
                      const size_t max,
                      size_t* returned,
                      size_t* remaining );

/**
 * Stops the current browsing and frees all internal resources.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_browse_stop( void );


/**
 * This method is used to query information about an specific object.
 *
 * @note    This function will not work with gc_BROWSING_TYPE_XXX_ALIAS!
 *
 * The generic system and index parameters have the following valid combinations:
 * <pre>
 * browsing type                      system   index1   index2   index3   index4
 * #gc_BROWSING_TYPE_SYSTEM           yes      no       no       no       no
 * #gc_BROWSING_TYPE_NODE             yes      yes      no       no       no
 * #gc_BROWSING_TYPE_ACTION           yes      yes      no       no       no
 * #gc_BROWSING_TYPE_LOOP             yes      yes      no       no       no
 * #gc_BROWSING_TYPE_TASK             yes      yes      no       no       no
 * #gc_BROWSING_TYPE_IO               yes      yes      no       no       no
 * #gc_BROWSING_TYPE_IO_INPUT         yes      yes      yes      no       no
 * #gc_BROWSING_TYPE_IO_OUTPUT        yes      yes      yes      no       no
 * #gc_BROWSING_TYPE_SCHEDULER_SLOT   yes      yes      yes      no       no
 * #gc_BROWSING_TYPE_MEMORY           yes      yes      yes      no       no
 * #gc_BROWSING_TYPE_GROUP            yes      yes      yes      yes      no
 * #gc_BROWSING_TYPE_PV_ARRAY         yes      yes      yes      yes      yes
 * </pre>
 *
 * @param[in]   type            Object type to get information about. Alias types
 *                              are not supported and cause an invalid argument
 *                              error.
 * @param[in]   system          The system index.
 * @param[in]   index1          The index1. It's interpretation depends on the
 *                              used browsingType.
 * @param[in]   index2          The index2. It's interpretation depends on the
 *                              used browsingType.
 * @param[in]   index3          The index3. It's interpretation depends on the
 *                              used browsingType.
 * @param[in]   index4          The index4. It's interpretation depends on the
 *                              used browsingType.
 * @param[in]   index5          The index5. It's interpretation depends on the
 *                              used browsingType.
 * @param[out]  info            Points to a single info field for storing the
 *                              retrieve information.
 *
 * @note    Currently the highest index is index4.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_browse_getSpecInfoByIndices( const gc_BrowsingType type,
                                const gc_SystemAddress system,
                                const gc_ObjectIndex index1,
                                const gc_ObjectIndex index2,
                                const gc_ObjectIndex index3,
                                const gc_ObjectIndex index4,
                                const gc_ObjectIndex index5,
                                gc_BrowserInfo* info );

/**
 * The behavior of this function is analog to #ga_browse_getSpecInfoByIndices
 * with the only difference that instead of indices it uses gc_Level6Address type.
 *
 * @note    This function will not work with gc_BROWSING_TYPE_XXX_ALIAS!
 *
 * The following code sample shows how to use the address:
 * @code
 *
 * gc_BrowsingInfo info;
 * gc_SystemAddress sysAddress = 123;
 *
 * ga_browse_getSpecInfoByAddress( gc_BROWSING_TYPE_SYSTEM,
 *                                 (const gc_Level6Address*) &sysAddress,
 *                                 &info );
 *
 *
 * gc_Level3Address level3Address;
 * level3Address.system = 123;
 * level3Address.index1 = 1;
 * level3Address.index2 = 2;
 *
 * ga_browse_getSpecInfoByAddress( gc_BROWSING_TYPE_MEMORY,
 *                                 (const gc_Level6Address*) &level3Address,
 *                                 &info );
 *
 * @endcode
 *
 * @param[in]   type            Object type to get information about. Alias types
 *                              are not supported and cause an invalid argument
 *                              error.
 * @param[in]   address         The address of the object of interest.
 * @param[out]  info            Points to a single info field for storing the
 *                              retrieve information.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_browse_getSpecInfoByAddress( const gc_BrowsingType type,
                                const gc_Level6Address* const address,
                                gc_BrowserInfo* info );


#endif /* GAMMA_API_BROWSING_H__ */
