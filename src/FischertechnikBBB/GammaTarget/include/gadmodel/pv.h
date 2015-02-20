#ifndef GAMMA_DMODEL_PV_H__
#define GAMMA_DMODEL_PV_H__

/**
 * @file
 *
 * Unlike the other headers, which define manipulation function for the specific
 * Gamma Data Model object types (action, memory, node, etc) this header contains
 * utility (convenience) functions for directly creating a PV with default values.
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
 * Convenience function for creating a PV with a default configuration.
 *
 * The PV value will default to the ones as specified by #gc_PVArrayConfig_init.
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
 *
 *  - Loop
 *     - Will be associated with the above Net/Sig/Log actions.
 *     - gc_LoopConfig:
 *        - isPersistent = false
 *        - cycleTicks = 1
 *
 *  - Node:
 *     - gc_NodeConfig:
 *        - name = "GenNode"
 *        - isPersistent = false
 *
 *  - SHM:
 *     - gc_SHMConfig:
 *       - name = "GenMemory"
 *       - isPersistent = false
 *       - size = 10 * 1024 * 1024
 *       - permission = 0
 *       - user = ""
 *       - group = ""
 *
 *  - Group:
 *     - name = "GenGroup"
 *     - As actions Net/Sig/Log are used.
 *     - gc_GroupConfig:
 *        - isPersistent = false
 *        - isLocked = false
 *
 *  - PVArray:
 *     - gc_PVArrayConfig:
 *       - name = The one you specified as aliasName for this function call!
 *       - isPersistent = false
 *       - dynamicMemory = true
 *       - noElements = noElements (as specified via the function's argument)
 *       - initial = defaults as defined by #gc_PVArrayConfig_init( ..., dataType, maxLength, ... )
 *       - minCheckingFlags = gc_META_STATE_DISABLED
 *       - initialMin = defaults as defined by #gc_PVArrayConfig_init( ..., dataType, maxLength, ... )
 *       - maxCheckingFlags = gc_META_STATE_DISABLED
 *       - initialMax = defaults as defined by #gc_PVArrayConfig_init( ..., dataType, maxLength, ... )
 *       - simulationFlags = gc_META_STATE_DISABLED
 *       - initialSim = defaults as defined by #gc_PVArrayConfig_init( ..., dataType, maxLength, ... )
 *       - loggingFlags = gc_META_STATE_DISABLED
 *
 * The above mentioned components will be created by the first call to
 * this function. All further calls will either use the already created Data
 * Model Object or will recreate them.
 *
 * The internally wrapped function gd_pvArray_create* will automatically create
 * the following two alias names for opening the PV:
 *
 * <pre>
 * 1) \<SystemName\>:\<NodeName\>.\<MemoryName\>.\<GroupName\>.\<PVAlias\>
 * 2) \<SystemName\>:\<NodeName\>.\<PVAlias\>
 *
 * \<SystemName\> ::= Thats the name of the system you have specified in your
 *                  system XML file.
 * \<NodeName\>   ::= Will be always 'GenNode'
 * \<MemoryName\> ::= Will be always 'GenMemory'
 * \<GroupName\>  ::= Will be always 'GenGroup'
 * \<PVAlias\>    ::= Thats the pvAlias parameter you have specified when calling
 *                  gd_createPV.
 * </pre>
 *
 * The following example shows you some example names (The name of the
 * system is always 'SystemZ'):
 * <pre>
 * PV Alias                 Final Name:
 * -----------------------------------------------------------------------------
 * "PVX"                    "SystemZ:GenNode.GenMemory.GenGroup.PVX"
 *                          "SystemZ:GenNode.PVX"
 *                          "SystemZ:PVX"
 *
 * "PV.Alias.With.Dots"     "SystemZ:GenNode.GenMemory.GenGroup.PV.Alias.With.Dots"
 *                          "SystemZ:GenNode.PV.Alias.With.Dots"
 *                          "SystemZ:PV.Alias.With.Dots"
 *
 * </pre>
 * The following code sample shows the usage of this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_Handle handle = gc_INVALID_HANDLE;
 *
 * //Create a new PV
 * returnValue = gd_createPV( "PVArrayName",
 *                            gc_DATA_TYPE_IEEE_64,
 *                            10,               //10 consecutive 64 bit floating points
 *                            0,                //Won't be used
 *                            &handle );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gd_createPV() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //At this point the newly created PV is ready to be used.
 * //E.g. in conjunction with GAAPI the PV can be opened via ga_pv_open(...)
 * //or it can be browsed via the GAAPI's browsing interface, etc.
 * //For more information please read the documentation of these mentioned APIs.
 *
 * //For this sample we just open the PV via the ga_pv_open call:
 * //The composition of the final PV name is described in the above table.
 * //Because the PV is only local we can skip the system name.
 * ga_PV pvHandle = 0;
 * returnValue = ga_pv_open( &pvHandle, ":GenNode.PVArrayName", 0 );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_open() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //Now you can use the PV like any other statically created PV.
 * ...
 *
 *
 * //If the PV is no longer needed it can be safely closed as follows:
 * //Close the GAAPI PV handle.
 * returnValue = ga_pv_close( &pvHandle );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_close() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //Close the handle of the object in the data model to remove the PV from the
 * //data model.
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
 * @note    The PV will only and always be created on the local system!
 *
 * @note    If you quickly want to browse the data model but don't want to
 *          or have the time to write a program, using the Gamma Data Model
 *          Browsing API (located as a subset within the GAAPI). Just run
 *          the gacmd tool on your local system (where the data model resides you
 *          want to browse) and issue the following command:
 *              'gacmd sys -i 0 tree'
 *          For more information about the gacmd and using it to browse the
 *          data model in-detail please call the gacmd tool with the '-h' option.
 *
 * @param[in]   aliasName    The alias name for identifying the PV. Because
 *                           the Gamma Data Model does use PVArrays and not
 *                           PVs the aliasName will be used to set the name of
 *                           the PVArray. For latter accessing a PV within the
 *                           array the subscript operator must be appended. E.g. the
 *                           aliasName is "PVX", then the name of element 0, 1,
 *                           etc is ":PVX[0]", ":PVX[1]", etc. In addition the
 *                           first element (element #0) is allowed to skip the
 *                           subscript operator. Therefore ":PVX[0]" is also
 *                           identifiable as ":PVX".
 * @param[in]   dataType     The data type of the PV. The value of the PV will
 *                           be for numeric types 0, for strings "" and for
 *                           BLOBs NULL pointer.
 * @param[in]   noElements   Specifies the noElements of the PVArray, where the
 *                           PV will be put.
 * @param[in]   maxLength    If the data type is of BLOB/String this parameter
 *                           defines its maximum length.
 * @param[out]  handle       The handle to the PV (technically PVArray). Use
 *                           this handle for calling #gd_closeHandle after the
 *                           PV is no longer needed.
 */
gd_EXP gc_ErrorID gc_CALLCONV
gd_createPV( const char* const aliasName,
             const gc_DataType dataType,
             const uint32_t noElements,
             const uint32_t maxLength,
             gc_Handle* const handle );




#endif /* GAMMA_DMODEL_PV_H__ */
