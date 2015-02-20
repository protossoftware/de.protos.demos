#ifndef GAMMA_API_PV_H__
#define GAMMA_API_PV_H__
/**
 * @file
 * Defines the interface to a PV.
 *
 * <h3> 1. Multithread-Safety and Determinism </h3>
 *
 * It's important to know that not all functions are multithread-safe and
 * mixing multithread-safe functions with one that are not safe will result
 * in undefined behavior. But it's allowed to mix multithread-safe functions
 * with each other. \n
 * \n
 *
 * The API only provides deterministic access time for the functions
 * ga_pv_getValue(...) and ga_pv_putValue(...) all other functions should be
 * considered <b>not</b> deterministic if not quoted otherwise!
 *
 * <h3> 2. General API Usage </h3>
 *
 * The functions of this API are split in the following groups: \n
 *  - Creation and deletion of a PV\n
 *  - Basic access
 *  - Advanced access
 *  - Metadata functionality
 * \n
 *
 * <h3> 3. Locality and RPCs in conjunction with meta functionalities </h3>
 *  - Meta function configuration (read/write) are always done via RPC. Even if
 *    the PV is originated on the local system!
 *  - The functions ga_pv_putValue/ga_pv_getValue are the native access functions
 *    to the value of a PV. The location of the PV and the ga_PVPropertyies
 *    determine if the access is performed via RPC or SHM. For more information
 *    about this configuration properties please see #ga_pv_open, #ga_pv_putValue
 *    and #ga_pv_getValue.
 *
 *
 * <h3> 3.1 Boundaries </h3>
 *  - only check if locally. Otherwise there is no min/max set (like sim). In
 *    case of an error (invalid value) the service will set the PV state to
 *    an appropriate 'error state' (TBD).
 *
 * <h3> 3.2 How simulation/boundaries influences ga_pv_getValue and ga_pv_putValue </h3>
 *  - ga_putSimValue/ga_getSimValue/ga_getOrigValue is either a RPC (remote system)
 *    or direct memory access (local). Therefore no splitting of sim data field
 *    into read/write is required!
 *  - ga_pv_putValue/ga_pv_getValue is always local.
 *
 * <h3> 3.3 Memory map: Access </h3>
 * The following figure shows the access of a <b> local </b> PV. For remote
 * PVs the sim part is missing. \n
 *
 * <pre>
 *
 *                      |-------------|           always available
 * ga_pv_putValue ----> | write       |
 * (always)             |-------------|
 *                      | read        | --- no sim ---> ga_pv_getValue (always if local)
 * =====================|-------------|=============/==========================
 *                      | sim         | - with sim /   (only if local!)
 *                      |-------------|
 *                      | min         |
 *                      |-------------|
 *                      | max         |
 *                      |-------------|          only locally available
 * </pre>
 *
 * The fields sim/min/max are only usable if the PV has originated on the local
 * system and the meta data sim is available. Otherwise only write/read are available.
 * \n
 * The access to the min/max fields of the boundaries is only done via local
 * RPCs. No direct memory access is done!
 * \n
 * <h3> 4. Error Handling </h3>
 *  - local PV: Direct error codes in case of an error.
 *  - remote PV: No error codes. All values will be written into the mirrored
 *               PV. If this write access was not valid the gamma service will
 *               set the PV state to ???ga_PV_STATE_ERROR???
 *
 * The function ga_getOrigValue always reads the value of 'orig: read' and the
 * function ga_getSimValue always read the value of 'sim: read'.
 *
 * <h3> 5. Meta Functionalities </h3>
 * Meta functionalities are manipulatable by every process. There is no assurance
 * that if process 1 has set simulation no other process can deactivate it. The
 * responsibility for managing the meta functionality states are by the user.
 *
  *
 * @author  (C)opyright by RST Industrie Automation GmbH
 */
/******************************************************************************
 * Header File Includes
 ******************************************************************************/
#include <gacommon/errorCodes.h>
#include <gaapi/platformDependencies.h>
#include <gaapi/dataTypes.h>

/******************************************************************************
 * PV Interface - Creation/Deletion
 ******************************************************************************/
/**
 * Opens access to an already existing PV. To avoid memory leaks always close
 * opened PVs (see #ga_pv_close).
 *
 * The address of a PV is specified by the following EBNF:
 * <pre>
 * PVAddress     = [SystemAddress] Name { NameLevelDelimiter Name } [ Index ]
 * SystemAddress = [ Name | "*" ] SystenLevelDelimiter
 *
 * Index = "[" Number "]"
 *
 * Number = Number { Digit }
 * Name = C Identifier
 *
 * SystemLevelDelimiter = ":"
 * NameLevelDelimiter = "."
 * </pre>
 *
 * The address of a PV also specifies where to search for it. For example if
 * the system name is explicitly qualified than the PV must exist on it. Otherwise
 * an error will be reported. The following table shows how the different
 * settings work:
 *
 * <pre>
 * Sample:      Local/Global Search:
 * "X"          First local, if not found on the current system the search will
 *              comprise the network. If not found on the network an error
 *              will be reported.
 *              If the user specifies a lookup via the function's parameter pvProperty
 *              the search behavior can be restricted. For more information see
 *                  #ga_PV_PROPERTY_LOOKUP_LOCAL
 *                  #ga_PV_PROPERTY_LOOKUP_GLOBAL
 *
 *              Hint: Actually this lookup is a convenience. Internally the
 *              service always expects names with a ':' in it. The following
 *              entries explain these names.
 *
 * ":X"         Only local lookup is performed. If not found an error will be
 *              reported.
 *
 * "*:X"        Is the same as "X".
 *
 * "S:X"        Searches for the PV "X" on system "S". If not found there an
 *              error will be reported.
 * </pre>
 *
 * Yet another special case is array access. For the very first element the
 * index and brackets can be omitted. But not for the succeeding ones.
 * The following table shows some examples:
 *
 * <pre>
 * sample:          Description:
 * "S:X"            Opens the first index. This is equal to "S:X[0]"
 * "S:X[1]"         Opens the second index.
 * </pre>
 *
 * The parameter pvProperties defines policies for the PV handle (not the PV itself!).
 * The first policy group define how the functions #ga_pv_putValue and
 * #ga_pv_getValue behave, if the PV has it's origin on a remote system.
 * The following table summaries this:
 * <pre>
 * local PV:     ga_PV_PROPERTY_ACC_*:            Access:
 * ======================================================================================
 * yes (local)   *                                If a PV is local the access is always
 *                                                via SHM.
 *
 * no (remote)   ga_PV_PROPERTY_ACC_BLOCKING      The access is always done via RPC.
 *                                                No access to the SHM occurs. Therefore
 *                                                if another PV handle is used with
 *                                                a non-blocking policy it will not
 *                                                register the write operation until
 *                                                the service on the local and
 *                                                remote system have synchronized
 *                                                the written value.
 *
 * no (remote)   ga_PV_PROPERTY_ACC_NON_BLOCKING  The access is always local. The
 *                                                service itself will synchronize the
 *                                                local value with the remote
 *                                                system. If the value get's changed
 *                                                before this synchronization takes
 *                                                place the previous value will
 *                                                never be written to the remote system.
 *
 * </pre>
 *
 *
 * The following code sample shows how to open a PV:
 * @code
 *
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * ga_PV pvHandle = 0;
 * returnValue = ga_pv_open( &pvHandle, "x", ga_PV_PROPERTY_ACC_NON_BLOCKING |
 *                                           ga_PV_PROPERTY_LOOKUP_LOCAL );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_open() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * @endcode
 *
 * @param[in,out]   pv          The handle of the PV object will be stored here.
 * @param[in]       alias       The alias of the PV. If the alias specifies
 *                              the search pattern for the PV, e.g. "*:X", than
 *                              the lookup parameter of pvProperty will be ignored.
 * @param[in]       pvProperty  Locally specific property for the PV. The
 *                              lookup parameter will be only used if alias does
 *                              not explicitly specify one.
 *                              If no lookup was defined it will default to
 *                              'global'.
 *                              If no access types was defined it will default
 *                              to 'blocking'.
 *
 * @note    Function is MT-safe.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_MALLOC_FAILED \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_PV_NAME_TOO_LONG \n
 *          #gc_ERROR_PV_INVALID_SYNTAX \n
 *          \n
 *          #gc_ERROR_SERVICE_OBJECT_NOT_EXIST
 *
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_open( ga_PV* const pv,
            const char* const alias,
            gc_Flags32Bit pvProperty );

/**
 * Like ga_pv_open, but the index of the PV must not be specified as part of the
 * address but as a unsigned integer value.
 *
 * For detail informations please read the documentation of #ga_pv_open.
 *
 * The following code sample shows how this function comes in handy:
 * @code
 * //Open 'SIZE' PVs via a loop. All PVs have the name in common. Their only
 * //distinction is their index.
 * #define SIZE (10)
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * ga_PV pvHandles[SIZE];
 * int i = 0;
 * for( i = 0; i < SIZE; ++i )
 * {
 *     returnValue = ga_pv_openByIndex( &pvHandles[i],
 *                                      "x",
 *                                      i,
 *                                      ga_PV_PROPERTY_ACC_NON_BLOCKING |
 *                                      ga_PV_PROPERTY_LOOKUP_LOCAL );
 *     if( gc_ERROR_SUCCESS.errorID != returnValue )
 *     {
 *         fprintf( stderr, "Call to ga_pv_openByIndex() failed.\n" );
 *         fprintf( stderr, "Error ID=%d\n", returnValue );
 *         fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *         exit( -1 );
 *     }
 * }
 * @endcode
 *
 * @note    When this PV open function is used the userProvidedAddress (#ga_pv_getAddress)
 *          will default to alias[index]. E. g. let alias be "AliasForPVX" and
 *          index be "1234" the resulting userProvidedAddress will be
 *          "AliasForPVX[1234]".
 *
 * @note    This function can NOT be used for opening PVs of type FIFO, because
 *          a FIFO does NOT have an index! If this function is still called
 *          #gc_ERROR_SERVICE_OBJECT_NOT_EXIST will be returned.
 *
 * @param[in,out]   pv          The handle of the PV object will be stored here.
 * @param[in]       alias       The alias, without the index!
 * @param[in]       index       Index of the PV.
 * @param[in]       pvProperty  Locally specific property for the PV. The
 *                              lookup parameter will be only used if alias does
 *                              not explicitly specify one.
 *                              If no lookup was defined it will default to
 *                              'global'.
 *                              If no access types was defined it will default
 *                              to 'blocking'.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_MALLOC_FAILED \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_PV_NAME_TOO_LONG \n
 *          #gc_ERROR_PV_INVALID_SYNTAX \n
 *          \n
 *          #gc_ERROR_SERVICE_OBJECT_NOT_EXIST
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_openByIndex( ga_PV* const pv,
                   const char* const alias,
                   uint32_t index,
                   gc_Flags32Bit pvProperty );

/**
 * Like ga_pv_open, but the PV is completely addressed via it's numeric address.
 * Such a functionality comes in handy, if a PV was found via the browsing API
 * and should be opened.
 *
 * For detail informations please read the documentation of #ga_pv_open.
 *
 * The following code sample shows how this function comes in handy:
 * @code
 * //Some previously used function from browsing.h has returned a numeric
 * //address of a PV and now its required to open this one.
 * gc_Level6Address pvAddress;
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * ga_PV pvHandle = 0;
 * returnValue = ga_pv_openByAddress( &pvHandle,
 *                                    &pvAddress,
 *                                    ga_PV_PROPERTY_ACC_NON_BLOCKING |
 *                                    ga_PV_PROPERTY_LOOKUP_LOCAL );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_openByAddress() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in,out]   pv          The handle of the PV object will be stored here.
 * @param[in]       address     The numeric address of the PV to open.
 * @param[in]       pvProperty  Locally specific property for the PV. The
 *                              lookup parameter will be only used if alias does
 *                              not explicitly specify one.
 *                              If no lookup was defined it will default to
 *                              'global'.
 *                              If no access types was defined it will default
 *                              to 'blocking'.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_MALLOC_FAILED \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_SERVICE_OBJECT_NOT_EXIST
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_openByAddress( ga_PV* const pv,
                     const gc_Level6Address* address,
                     gc_Flags32Bit pvProperty );


/**
 * Explicitly opens the PV as a ga_PV_TYPE_FIFO.
 *
 * This function is an optimized version of the more general
 *  - #ga_pv_open
 *  - #ga_pv_openByIndex
 *  - #ga_pv_openByAddress
 *
 * The advantages of this function over the more general is that it does not
 * require the gaservice to 'find out' to which actual #ga_PVType the alias
 * belongs to. Therefore in some cases this function will operate with more
 * performance than the more general ones.
 *
 * The disadvantage of this function is that the caller requires to know the
 * actual #ga_PVType before opening the PV.
 *
 * @param[in,out]   pv          The handle of the PV object will be stored here.
 * @param[in]       alias       The alias of the PV. If the alias specifies
 *                              the search pattern for the PV, e.g. "*:X", than
 *                              the lookup parameter of pvProperty will be ignored.
 * @param[in]       pvProperty  Locally specific property for the PV. The
 *                              lookup parameter will be only used if alias does
 *                              not explicitly specify one.
 *                              If no lookup was defined it will default to
 *                              'global'.
 *                              If no access types was defined it will default
 *                              to 'blocking'.
 *
 * @note    Function is MT-safe.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_MALLOC_FAILED \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_PV_NAME_TOO_LONG \n
 *          #gc_ERROR_PV_INVALID_SYNTAX \n
 *          \n
 *          #gc_ERROR_SERVICE_OBJECT_NOT_EXIST
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_openFifo( ga_PV* const pv,
                const char* const alias,
                gc_Flags32Bit pvProperty );

/**
 * Explicitly opens the PV as a ga_PV_TYPE_SINGLE_VALUE.
 *
 * This function is an optimized version of the more general
 *  - #ga_pv_open
 *  - #ga_pv_openByIndex
 *  - #ga_pv_openByAddress
 *
 * The advantages of this function over the more general is that it does not
 * require the gaservice to 'find out' to which actual #ga_PVType the alias
 * belongs to. Therefore in some cases this function will operate with more
 * performance than the more general ones.
 *
 * The disadvantage of this function is that the caller requires to know the
 * actual #ga_PVType before opening the PV.
 *
 * @param[in,out]   pv          The handle of the PV object will be stored here.
 * @param[in]       alias       The alias of the PV. If the alias specifies
 *                              the search pattern for the PV, e.g. "*:X", than
 *                              the lookup parameter of pvProperty will be ignored.
 * @param[in]       pvProperty  Locally specific property for the PV. The
 *                              lookup parameter will be only used if alias does
 *                              not explicitly specify one.
 *                              If no lookup was defined it will default to
 *                              'global'.
 *                              If no access types was defined it will default
 *                              to 'blocking'.
 *
 * @note    Function is MT-safe.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_MALLOC_FAILED \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_PV_NAME_TOO_LONG \n
 *          #gc_ERROR_PV_INVALID_SYNTAX \n
 *          \n
 *          #gc_ERROR_SERVICE_OBJECT_NOT_EXIST
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_openSV( ga_PV* const pv,
              const char* const alias,
              gc_Flags32Bit pvProperty );


/**
 * Clones the given srcPV.
 *
 * This function is provided as a convenience and consistency interface. The
 * consistency ensures, that all PVs cloned via this function share the most
 * common information. E. g. if a PV was opened via ga_pv_open() it holds a
 * user-provided alias. To avoid dropping this information by cloning the
 * PV via ga_pv_openByAddress this function will automatically use the same
 * function call as was issued by the original PV.
 *
 * @note    The properties of the new PV are the same as the one of the src PV.
 *
 * @param[in,out]   pv          The handle of the PV object will be stored here.
 * @param[in]       srcPV       The source PV to be cloned.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_MALLOC_FAILED \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_SERVICE_OBJECT_NOT_EXIST
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_clone( ga_PV* const pv,
             ga_ConstPV const srcPV );


/**
 * Closes access to an previously opened PV object (see #ga_pv_open). This
 * function will free all local resources and sets the PV pointer to 0. The value
 * of the PV or any meta functionalities won't be changed by this operation.
 *
 * If this operation is called, while another ga_pv_* function is in progress the
 * behavior is undefined.
 *
 * This function does not check if a valid attach to the Gamma Service was done,
 * because its purpose is to release memory. In case the attach is missing and
 * therefore the state is not correctly no memory will be lost but an corresponding
 * error code will be returned.
 *
 * The following code sample shows how to close a PV:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * ga_PV pvHandle = 0;
 *
 * //The PV was previously opened via ga_pv_open
 * returnValue = ga_pv_close( &pvHandle );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_close() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * <h3> Signaling Resource Handling </h3>
 * If the user does not explicitly clear the signaling resources this function
 * will automatically clear them, to avoid resource leaks or segmentation faults.
 * The following rules give an overview.
 *
 * 1. This function deactivates signaling if:
 *  - No other PV handle is referencing signaling (see ga_pv_changeSigCallback)
 *  - This PV handle was used to activate signaling.
 *
 * 2. This function automatically removes the thread-specific callback, if it
 *    was registered previously via ga_pv_changeSigCallback.
 *
 * 3. This function automatically disables the global callback to avoid
 *    memory corruption, if signaling was activated via this PV. The thread-
 *    specific callbacks will be kept, if this does not violate rule (II).
 *
 * <h3> Corrupted Handle and Memory Management </h3>
 * Internally the PV handle references a complex data structure, containing
 * several management information. One of these information is the ID of the
 * opened PV. In case this ID gets corrupted (e.g. the Gamma Service dies before
 * the handle could be properly released) this function will still free all
 * malloced memory, but returns #gc_ERROR_PV_CLOSE_DONE_BUT_CORRUPTION.
 *
 *
 * @param[in,out]   pv   Points to an previously opened PV. After the PV has
 *                       been successfully closed the pointer will be set to 0.
 *
 * @note    Function is MT-safe, but do not remove a currently used PV object
 *          from another thread!
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_PV_CLOSE_DONE_BUT_CORRUPTION \n
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_close( ga_PV* const pv );


/******************************************************************************
 * PV Interface - Basic Numeric Access Functionality
 ******************************************************************************/
/**
 * Retrieves the value of a PV and uses all activated meta functionality, if
 * simulation is not active! Otherwise this function will retrieve the simulated
 * value of the PV!
 *
 * The following code sample shows how to retrieve a numeric PV value:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * ga_PV pvHandle = 0;
 * gc_NumericValue value;
 *
 * //(1) Open the PV
 * returnValue = ga_pv_open( &pvHandle, "x", ga_PV_PROPERTY_ACC_BLOCKING );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_open() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //(2) Get the value
 * returnValue = ga_pv_getValue( pvHandle, &value );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_getValue() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //(3) Write the value to stdout (hint: Assumption is that the data type is uint32_t!)
 * printf( "The value of the PV is '%u'\n", value.uint32 );
 *
 * //(4) Finally close the PV
 * returnValue = ga_pv_close( &pvHandle );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_close() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @note    This function will not check if the attachment to the service has
 *          already been done! If you attach, open a PV and then detach the
 *          behavior is undefined.
 *
 * @note    If the PV is locally available this function performs all meta
 *          functions and returns their corresponding error state, if they fail.
 *          Otherwise, if the PV is only remotely available the function will
 *          just read the mirrored value.
 *
 * @note    This function is only MT safe if(at least one):
 *           - The current operating system support atomic 32 bit integer
 *             assignment (PV type is [SINT8; UINT32].
 *           - The current operating system support atomic 64 bit floating
 *             point assignment (PV type is [IEEE32; IEEE64].
 *           - The PV is associated with a lock.
 *
 * @param[in]   pv      The PV of interest. Because of possible meta functions
 *                      the state of the PV object might change after this call!
 * @param[out]  value   The retrieved value will be stored here.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR
 *
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_getValue( const ga_ConstPV pv,
                gc_NumericValue* const value );

/**
 * Writes a value to a PV and uses all activated meta functionality. The semantics
 * of this function changes if simulation was activated for a PV. In this case
 * Signaling is temporarily disabled until simulation will be disabled!
 *
 * The following table shows the MT safety of this function:
 * <pre>
 * Has Lock:        Has Meta:       MT safety:
 * =============================================================================
 * true             true            Depends on the active meta functionality.
 *                                  (I) Boundaries (Min/Max)
 *                                  Sample:
 *                                   (1) PV is of type uint32_t.
 *                                   (2) PV uses min/max boundaries.
 *                                   (3) At t0 threadA sets
 *                                        min='1'
 *                                        max='10'
 *                                   (4) At t1 threadA sets
 *                                        min='100'
 *                                        max='200'
 *                                   (5) Between t0 and t1 threadB puts
 *                                        value='50'
 *                                  The result of this operation is undefined,
 *                                  because the change of the boundary values
 *                                  is not atomic. This means that between t0
 *                                  and t1 the follwing state could exist:
 *                                      min='1'
 *                                      max='200'    (max get's changed first)
 *                                  Alternatively the state coulbe be also:
 *                                      min='100'
 *                                      max='10'
 *                                  Therefore the put of threadB could be
 *                                  either success of a boundary violation.
 *
 *                                  Please be advice to not change the boundary
 *                                  values while another thread is processing
 *                                  application logic.
 *
 *                                  (II) Simulation, Logging, Signaling
 *                                  Yes
 *
 * true             false           Yes
 *
 * false            false           Depends on the following system-specific
 *                                  attributes:
 *                                   (1) The current operating system support
 *                                       atomic 32 bit integer assignment
 *                                       (PV type is [SINT8; UINT32].
 *                                   (2) The current operating system support
 *                                       atomic 64 bit floating point assignment
 *                                       (PV type is [IEEE32; IEEE64].
 *
 *                                  If none of the the above items is true the
 *                                  function should not be considered MT safe.
 *
 * false            true            Worst case combination of point (1) and
 *                                  point (3).
 * </pre>
 *
 * The following code sample shows how to write a numeric PV value:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * ga_PV pvHandle = 0;              //Will hold the handle.
 * gc_NumericValue value;              //Will contain the value to write.
 *
 * //(1) Open the PV
 * returnValue = ga_pv_open( &pvHandle, "x", ga_PV_PROPERTY_ACC_BLOCKING );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_open() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //(2) Set the value and write it. In this sample the data type of the PV is of uint32_t.
 * value.uint32 = 42;
 *
 * returnValue = ga_pv_putValue( pvHandle, &value );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_putValue() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //(3) Finally close the PV
 * returnValue = ga_pv_close( &pvHandle );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_close() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @note    This function will not check if the attachment to the service has
 *          already been done! If you attach, open a PV and then detach the
 *          behavior is undefined.
 *
 * @note    If the PV is locally available this function performs all meta
 *          functions and returns their corresponding error state, if they fail.
 *          Otherwise, if the PV is only remotely available the function will
 *          just write the value and won't be able to propagate the meta
 *          function's state.
 *
 * @note    The data exchange semantics for a PV with asynchronous access
 *          will be more explicit in the future. Currently if a local system
 *          'local' is accessing a remote PV 'PV' on the remote system 'remote'
 *          a local copy it 'PV' will be created on 'local'. The service will
 *          update the values between the 'remote' and 'local' system within the
 *          user-defined intervals as quoted in the XML configuration files
 *          of the service. Depending on chronological coincidence, if the
 *          value of 'PV' gets simultaneously changed on 'local' to 'X' and
 *          'remote' to 'Y' the value of 'PV' is either 'X' or 'Y'.
 *          Currently these exchange semantics are all hidden from the user
 *          by the service. To provide more maintainability and control it's
 *          planned to provide a user interface (XML configuration and API) for
 *          fully configure the value exchange semantics of the PVs.
 *
 * @param[in]   pv      The PV of interest.
 * @param[out]  value   The value to write.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR
 *
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_putValue( const ga_PV pv,
                const gc_NumericValue* const value );


/******************************************************************************
 * PV Interface - Basic String/BLOB Access Functionality
 ******************************************************************************/
/**
 * This function allows access to PVs with the non-numeric data type
 * #gc_DATA_TYPE_STRING and #gc_DATA_TYPE_BLOB. All meta functionalities are
 * currently disabled.
 *
 * If the data type of the PV is of string, the user does not have to write the
 * trailing 0 character by hand. The function will validate the data type and
 * write the 0 character if the data type is of string. On the other hand
 * if the data type is of BLOB no 0 character will be appended.
 *
 * To provide data integrity the access to the binary data value of a PV is
 * never done directly. A user-process can only manipulate a previously read
 * copy, manipulate it and finally write it back. These read (#ga_pv_getBinaryValue)
 * and write (#ga_pv_putBinaryValue) operations are internally locked via a
 * user-configured semaphore of the Gamma data model. (In detail: That's the group
 * element in the system configuration XML file.)
 *
 * To provide enough flexibility the destination has a type of void* and the
 * real type is defined by the value of the len argument. The following table
 * gives an overview:
 * <pre>
 * destLen Value:       Dest Type:      Description:
 * =============================================================================
 * 0                    char**          The memory for storing the source will
 *                                      be malloc'ed internally. The destination
 *                                      of the memory and it's copied content
 *                                      will be stored at *dest.
 *                                      To avoid memory corruption use
 *                                      gc_freeMemory(...) to free the internally
 *                                      malloc'ed memory.
 *
 * !=0                  char*           The content of the source will be
 *                                      copied at the address where dest points
 *                                      to. To avoid buffer overruns the len
 *                                      argument will limit the number of copied
 *                                      bytes. If the source is longer than len
 *                                      the copied content will be truncated.
 *
 * </pre>
 *
 * The following code sample shows how to retrieve a binary PV value:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * ga_PV pvHandle = 0;              //Will hold the PV handle.
 * char* binaryValue = 0;           //Will point to the binary PV value.
 * size_t actLen = 0;               //Will contain the actual length of the binary PV value.
 * char* beautifiedBinaryValue = 0; //Will contain a 'hex' output.
 *
 * //(1) Open the PV
 * returnValue = ga_pv_open( &pvHandle, "x", ga_PV_PROPERTY_ACC_BLOCKING );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_open() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //(2) Get the value and let the GAAPI malloc the memory for us.
 * returnValue = ga_pv_getBinaryValue( pvHandle, &binaryValue, 0, &actLen );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_getBinaryValue() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //(3) Write the BLOB 'beautified' into a buffer and write it to stdout.
 * //    Yet again let the GAAPI take care of memory allocation.
 * returnValue = gc_Blob_print( binaryValue, actLen, &beautifiedBinaryValue, 0, 0 );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_printBLOB() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * printf( stdout, "%s\n", beautifiedBinaryValue );
 *
 * //(4) Finally free all previously malloc'ed memory and close the PV
 * returnValue = gc_freeMemory( binaryValue );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gc_freeMemory() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * returnValue = gc_freeMemory( beautifiedBinaryValue );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gc_freeMemory() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * returnValue = ga_pv_close( &pvHandle );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_close() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 *
 * @note    If this function has internally malloc'ed memory to store the
 *          binary value than #gc_freeMemory must be used and not free.
 *          Otherwise memory corruptions might occur.
 *
 *
 * @param[in]       pv          The PV of interest. Because of possible meta functions
 *                              the state of the PV object might change after this call!
 * @param[in,out]   dest        The real type of the pointer depends on the len
 *                              argument! See above table.
 *                              The function will always malloc memory for dest
 *                              if destLen is 0! Therefore always clean up dest!
 *                              NB: In case actLen is 0 dest will have at least
 *                              1 byte allocated!
 * @param[in]       destLen     The available length of the buffer. It'll be always
 *                              counted without the trailing 0 character.
 *                              If destLen is 0 the dest argument will be interpreted
 *                              as type 'char**'.
 *                              If destLen is not 0 the dest argument will be interpreted
 *                              as type 'char*'.
 *                              For more information see above table.
 *                              If the binary data can not be stored in the dest,
 *                              because the destLen is to small this function
 *                              will return #gc_ERROR_COM_INVALID_ARGUMENT.
 * @param[out]      actLen      The actual length of the copied binary data into
 *                              dest. If this parameter is 0 it will not be set.
 *                              This comes in handy if a string gets retrieved,
 *                              but for BLOB types it's important to get the
 *                              actual length and the data, because a later
 *                              call got ga_pv_getLength does not guarantee that
 *                              the retrieved length is equal to the one before!
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          #gc_ERROR_COM_MALLOC_FAILED \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_PV_INVALID_DATA_TYPE \n
 *          #gc_ERROR_PV_LOCK_FAILED \n
 *          #gc_ERROR_PV_UNLOCK_FAILED \n
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_getBinaryValue( const ga_ConstPV pv,
                      void* dest,
                      size_t destLen,
                      size_t* actLen );

/**
 * Writes a binary value (#gc_DATA_TYPE_STRING or #gc_DATA_TYPE_BLOB) into the PV,
 * if the PV is of one of these data types. Otherwise an error will be returned.
 *
 * The call to this function will not use any meta functionalities.
 *
 * The following code sample shows how to write a binary PV value:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * ga_PV stringPV = 0;                          //Will hold the PV handle (datatype = string).
 * ga_PV blobPV = 0;                            //Will hold the PV handle (datatype = BLOB).
 * struct
 * {
 *     int i;
 *     char data[100];
 *     double d;
 * } blobData = { 0, { 'A' }, 1.2 };        //An abstract BLOB data
 *
 * //(1) Open the PVs
 * returnValue = ga_pv_open( &stringPV, "stringPV", ga_PV_PROPERTY_ACC_BLOCKING );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_open() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * returnValue = ga_pv_open( &blobPV, "blobPV", ga_PV_PROPERTY_ACC_BLOCKING );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_open() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //(2.1) Write a string into the PV.
 * //      Specify length with 0 to let the function internally apply strlen.
 * returnValue = ga_pv_putBinaryValue( stringPV, "First String Value", 0 );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_putBinaryValue() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //(2.2) Write the first 10 bytes of a string into the PV
 * returnValue = ga_pv_putBinaryValue( stringPV, "Second String Value", 10 );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_putBinaryValue() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //(3) Write the abstract BLOB data into the PV.
 * returnValue = ga_pv_putBinaryValue( stringPV, &blobData, sizeof( blobData ) );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_putBinaryValue() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //(4) Clean up
 * returnValue = ga_pv_close( &blobPV );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_close() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * returnValue = ga_pv_close( &stringPV );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_close() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @note    The special usage of len allows in-place copy of string 'constants'
 *          without code duplication or the introduction of a constant temporary.
 *
 * @param[in]   pv      The PV of interest.
 * @param[out]  src     Points to the binary data to write.
 * @param[in]   len     If the PV has a data type of BLOB this parameter
 *                      specifies how many bytes will be copied into the internal
 *                      binary value of the PV.
 *                      If the PV has a data type of STRING this parameter has
 *                      two meanings:
 *                      len == 0: Use strlen( src ) and copy the complete
 *                      string into the PV.
 *                      len != 0: Copy from the beginning of src until reaching
 *                      the byte # (len - 1). If the given len parameter is
 *                      longer than the actual string an gc_ERROR_COM_INVALID_ARGUMENT
 *                      will be returned.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_PV_INVALID_DATA_TYPE \n
 *          #gc_ERROR_PV_LOCK_FAILED \n
 *          #gc_ERROR_PV_UNLOCK_FAILED \n
 *
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_putBinaryValue( const ga_PV pv,
                      const void* src,
                      size_t len );

/**
 * Retrieves for a PV with the data type #gc_DATA_TYPE_STRING or #gc_DATA_TYPE_BLOB
 * the length information (current/maximum).
 *
 * The following code sample shows how to retrieve the length information:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * ga_PV pvHandle = 0;              //Will hold the handle of the PV.
 * size_t curLen = 0;               //Will contain the current length.
 * size_t maxLen = 0;               //Will contain the maximum length.
 *
 * //(1) Open the PVs
 * returnValue = ga_pv_open( &pvHandle, "x", ga_PV_PROPERTY_ACC_BLOCKING );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_open() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //(2) Retrieve the length information.
 * returnValue = ga_pv_getLength( pv, &curLen, &maxLen );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_getLength() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //(3) Clean up
 * returnValue = ga_pv_close( &pvHandle );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_close() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 *
 * @note    For strings the length is always without the '0' character.
 *
 * @note    Function is only MF-safe, if the PV is associated with a lock.
 *
 * @note    At least one of the length parameters must be not 0. Otherwise
 *          the function will fail!
 *
 * @param[in]   pv      The PV of interest.
 * @param[out]  curLen  The current length of the string/blob. If 0 the
 *                      information will not be stored.
 *                      If the PV's #ga_PVType is of ga_PV_TYPE_FIFO curLen will
 *                      always be 0.
 * @param[out]  maxLen  The maximum possible length of the string/blob. If 0
 *                      the information will not be stored.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_PV_INVALID_DATA_TYPE \n
 *          #gc_ERROR_PV_LOCK_FAILED \n
 *          #gc_ERROR_PV_UNLOCK_FAILED \n
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_getLength( const ga_PV pv,
                 size_t* curLen,
                 size_t* maxLen );

/**
 * Semantically the same as #ga_pv_getBinaryValue, but the return value is of
 * #gc_Blob.
 *
 * The following table gives an overview to decide when to use which function:
 * <pre>
 * #ga_pv_getBinaryValue                     #ga_pv_getBlob
 * =============================================================================
 * - intended as convenience function        - intended to map the 'native' structure
 *                                             of a PV with a data type of
 *                                             #gc_DATA_TYPE_BLOB or
 *                                             #gc_DATA_TYPE_STRING
 *
 * Usage scenario:                           Usage scenario:
 * Simply printing the value of              Retrieving the value of a BLOB PV
 * a string PV.                              to write it via group access to
 *                                           several other PVs.
 * </pre>
 *
 * @param[in]       pv          The PV of interest. Because of possible meta
 *                              functions the state of the PV object might
 *                              change after this call!
 * @param[in,out]   value       Must point to an already initialized
 *                              (#gc_Blob_init) gc_Blob variable. If the maxLen
 *                              is too short the gc_Blob will be realloced
 *                              (#gc_Blob_realloc).
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          #gc_ERROR_COM_MALLOC_FAILED \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_PV_INVALID_DATA_TYPE \n
 *          #gc_ERROR_PV_LOCK_FAILED \n
 *          #gc_ERROR_PV_UNLOCK_FAILED \n
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_getBlob( const ga_ConstPV pv,
               gc_Blob** const value );

/**
 * Semantically the same as #ga_pv_putBinaryValue, but the return value is of
 * #gc_Blob.
 *
 * The following table gives an overview to decide when to use which function:
 * <pre>
 * #ga_pv_putBinaryValue                     #ga_pv_putBlob
 * =============================================================================
 * - intended as convenience function        - intended to map the 'native' structure
 *                                             of a PV with a data type of
 *                                             #gc_DATA_TYPE_BLOB or
 *                                             #gc_DATA_TYPE_STRING
 *
 * Usage scenario:                           Usage scenario:
 * Writing the value of                      A previously, via #ga_pv_getBlob
 * a string PV, without the                  or #ga_pv_getGroup retrieved Blob
 * necessity of creating a                   value should be written (as-is)
 * gc_Blob temporary.                        to another PV.
 *
 * </pre>
 *
 * @param[in]       pv          The PV of interest.
 * @param[in,out]   value       Must point to an already initialized
 *                              (#gc_Blob_init) gc_Blob variable.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_PV_INVALID_DATA_TYPE \n
 *          #gc_ERROR_PV_LOCK_FAILED \n
 *          #gc_ERROR_PV_UNLOCK_FAILED \n
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_putBlob( const ga_PV pv,
               const gc_Blob* const value );

/**
 * All-in-one function, for retrieving the value of a PV.
 *
 * The purpose of this function is to provide an interface, to always retrieve
 * the value of a PV, without having to know if it's numerically or binary. The
 * disadvantage is that the performance is worse than calling #ga_pv_getValue or
 * #ga_pv_getBlob directly.
 *
 * The
 * main disadvantage in this case is that the performance will not cope with the
 * one as caused by calling the specific functions.
 *
 * The following table shows how the function dispatches the calls:
 * <pre>
 * Data Type:            Actual Function:
 * =============================================================================
 * Numeric               #ga_pv_getValue
 *                       Note: If the #ga_pv_getValue function gets called the
 *                             performance is best. In addition it's not required
 *                             to have the 'value' parameter be initialized
 *                             via #gc_Value_init as is required by calling
 *                             #ga_pv_get.
 *
 * BLOB/String           #ga_pv_getBlob
 * </pre>
 *
 * @note    If performance is of importance and the data type if numeric please
 *          be advised to call #ga_pv_getValue directly.
 *
 * @note    <b>Important:</b> Currently the name of the function might change
 *          in the future!
 *
 * @note    Available for PV type: \n
 *             - #ga_PV_TYPE_SINGLE_VALUE
 *             - #ga_PV_TYPE_FIFO.
 *
 * @param[in]       pv      The PV of interest.
 * @param[in]       value   Must point to an already, via #gc_Value_init initialized
 *                          #gc_Value.
 *                          If the data type of the PV match the one as specified
 *                          of the value the fields will be reused. E.g. if the
 *                          type is of #gc_DATA_TYPE_STRING or #gc_DATA_TYPE_BLOB
 *                          this function will automatically call #gc_Blob_realloc
 *                          for the data.blob field.
 *                          If the PV data type does not match the one of the
 *                          value the 'value' argument will be set-up to hold the
 *                          PV value. In this case the function will internally
 *                          call #gc_Value_free and #gc_Value_init with the
 *                          data type of the PV.
 *                          The type field will be set accordingly to the type
 *                          of the PV.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          #gc_ERROR_COM_MALLOC_FAILED \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_PV_INVALID_DATA_TYPE \n
 *          #gc_ERROR_PV_LOCK_FAILED \n
 *          #gc_ERROR_PV_UNLOCK_FAILED \n
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_get( const ga_ConstPV pv,
           gc_Value* const value );

/**
 * Like ga_pv_get but additionally retrieves the timestamp when the value was
 * written.
 *
 * The following code sample shows how to read a numeric PV value:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * ga_PV pvHandle = 0;              //Will hold the handle.
 * gc_Value value;                  //Will contain the value to write.
 * gc_Timestamp timestamp;          //Will hold the desired timestamp.
 *
 * //(1) Initialize the value.
 * //    NB: You can use any data type for reading, because the function internally
 *           will reinitialize the gc_Value type to match the real PV data type.
 * returnValue = gc_Value_init( &value, gc_DATA_TYPE_UINT_32, 0 );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gc_Value_init() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //(2) Open the PV with default properties.
 * //    --> The default properties will cause the FIFO get/put functions to
 *           block for the default timeout [ms] or a user-defined value. (see
 *           function #ga_pv_putPropertyValue).
 * returnValue = ga_pv_open( &pvHandle, "fifoX", 0 );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_open() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //(3) Retrieve the current value with the timestamp of the user as specified
 *       when he wrote it into the PV or with the timestamp, used by the Gamma
 *       hardware plugin.
 * returnValue = ga_pv_getWithTimestamp( pvHandle, &value, &timestamp );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_putWithTimestamp() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //(4) Use the utility function from gacommon/misc.h to pretty print the value
 *       of the PV.
 * char valuePrettyPrint[128] = { '\0' };
 * returnValue = gc_Value_print( &value, valuePrettyPrint, sizeof(valuePrettyPrint), 0 );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gc_Value_print() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * printf( "The value of the PV is: %s\n" % valuePrettyPrint );
 * printf( "The timestamp is: %u seconds, %u nanoseconds\n",
 *         timestamp.seconds, timestamp.nanoseconds );
 *
 * //(5) Finally close the PV
 * returnValue = ga_pv_close( &pvHandle );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_close() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @note    Available for PV type: \n
 *             - #ga_PV_TYPE_FIFO.
 *
 * @param[in]           pv          The PV of interest.
 * @param[in,out]       value       Will hold the current/next value of the PV.
 * @param[in,out]       timestamp   Will hold the timestamp corresponding to the
 *                                  retrieved value.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_PV_TYPE_INVALID_OPERATION
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_getWithTimestamp( const ga_ConstPV pv,
                        gc_Value* const value,
                        gc_Timestamp* const timestamp );


/**
 * All-in-one function, for writing the value of a PV.
 *
 * The purpose of this function is to provide an interface, to always write
 * the value of a PV, without having to know if it's numerically or binary. The
 * disadvantage is that the performance is worse than calling #ga_pv_putValue or
 * #ga_pv_putValue directly.
 *
 * The following table shows how the function dispatches the calls:
 * <pre>
 * Data Type:            Actual Function:
 * =============================================================================
 * Numeric               #ga_pv_putValue
 *                       Note: If the #ga_pv_putValue function gets called the
 *                             performance is best. In addition it's not required
 *                             to have the 'value' parameter be initialized
 *                             via #gc_Value_init as is required by calling
 *                             #ga_pv_get.
 *
 * BLOB/String           #ga_pv_putValue
 * </pre>
 *
 * @note    If performance is of importance and the data type if numeric please
 *          be advised to call #ga_pv_putValue directly.
 *
 * @note    <b>Important:</b> Currently the name of the function might change
 *          in the future!
 *
 * @note    Available for PV type: \n
 *             - #ga_PV_TYPE_SINGLE_VALUE
 *             - #ga_PV_TYPE_FIFO.
 *
 * @param[in]       pv      The PV of interest.
 * @param[in]       value   Must point to an gc_Value with the type field
 *                          matching the type of the PV, otherwise
 *                          #gc_ERROR_PV_INVALID_DATA_TYPE will be returned.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_PV_INVALID_DATA_TYPE \n
 *          #gc_ERROR_PV_LOCK_FAILED \n
 *          #gc_ERROR_PV_UNLOCK_FAILED \n
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_put( const ga_PV pv,
           const gc_Value* const value );


/**
 * Like ga_pv_put but additionally sets the timestamp.
 *
 * The following code sample shows how to write a numeric PV value:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * ga_PV pvHandle = 0;              //Will hold the handle.
 * gc_Value value;                  //Will contain the value to write.
 * gc_Timestamp timestamp;          //Will hold the desired timestamp.
 *
 * //(1) Initialize the value.
 * //    NB: If you don't know the data type of the PV at run-time, please call
 *           #ga_pv_getDataType a priori.
 * returnValue = gc_Value_init( &value, gc_DATA_TYPE_UINT_32, 0 );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gc_Value_init() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //(2) Open the PV with default properties.
 * //    --> The default properties will cause the FIFO get/put functions to
 *           block for the default timeout [ms] or a user-defined value. (see
 *           function #ga_pv_putPropertyValue).
 * returnValue = ga_pv_open( &pvHandle, "fifoX", 0 );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_open() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //(3) Set the value and write it. In this sample the data type of the PV is of uint32_t.
 * value.uint32 = 42;
 *
 * //(4) Set some arbitrary timestamp (alternatively you could read the systems
 * //    time - use seconds since epoche)
 * timestamp.seconds = 123456;
 * timestamp.nanoseconds = 98765;
 *
 * returnValue = ga_pv_putWithTimestamp( pvHandle, &value, &timestamp );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_putWithTimestamp() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //(3) Finally close the PV
 * returnValue = ga_pv_close( &pvHandle );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_close() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @note    Available for PV type: \n
 *             - #ga_PV_TYPE_FIFO.
 *
 * @param[in]       pv          The PV of interest.
 * @param[in]       value       The value to write to the PV.
 * @param[in]       timestamp   The timestamp value to set.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_PV_TYPE_INVALID_OPERATION
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_putWithTimestamp( const ga_PV pv,
                        const gc_Value* const value,
                        const gc_Timestamp* const timestamp );


/******************************************************************************
 * PV Interface - Common Metadata Functionality
 ******************************************************************************/
/**
 * Retrieves the data type of the given PV.
 *
 * The following code sample shows how to retrieve the data type:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * ga_PV pvHandle = 0;              //Will hold the handle of the PV.
 * gc_DataType dataType = 0;        //Will contain the data type.
 * const char* dataTypeTxt = 0;     //Will point to the textual repr. of data type.
 *
 * //(1) Open the PVs
 * returnValue = ga_pv_open( &pvHandle, "x", ga_PV_PROPERTY_ACC_BLOCKING );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_open() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //(2) Retrieve the data type information.
 * returnValue = ga_pv_getDataType( pvHandle, &dataType );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_getDataType() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //(2.1) Create a textual representation of the data type and print it on stdout
 * returnValue = ga_printDataType( dataType, &dataTypeTxt );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_printDataType() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * printf( "Data type is '%s'\n", dataTypeTxt );
 *
 * //(3) Clean up
 * returnValue = ga_pv_close( &pvHandle );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_close() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @note    Function is MT-safe.
 *
 * @param[in]       pv          The PV of interest.
 * @param[out]      dataType    Will contain the data type of the PV.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_getDataType( const ga_ConstPV pv,
                   gc_DataType* const dataType );

/**
 * Retrieves the user-provided and conform address of a PV.
 *
 * The user-provided address is the one as specified by #ga_pv_open. The conform
 * address is based on the user-provided one but extended so that it contains
 * the system qualification (see #ga_pv_open).
 *
 * The returned addresses are stored internally and therefore should not be
 * freed, otherwise the behavior is undefined.
 *
 * The following code sample shows how to retrieve the addresses:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * ga_PV pvHandle = 0;                      //Will hold the handle of the PV.
 * const char* userProvidedAddresse = 0;    //Will point to the user-provided address.
 * const char* conformAddress = 0;          //Will point to the conform address.
 * gc_Level6Address numericAddress;         //Will contain the numeric address.
 *
 * //(1) Open the PVs
 * returnValue = ga_pv_open( &pvHandle, "x", ga_PV_PROPERTY_ACC_BLOCKING );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_open() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //(2) Retrieve the addresses information.
 * returnValue = ga_pv_getAddress( pv, &userProvidedAddresse, &conformAddress, &numericAddress );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_getAddress() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * printf( "user-provided address: '%s'\n"
 *         "conform address: '%s'\n"
 *         "numeric address: %u.%u.%u.%u.%u.%u\n",
 *         userProvidedAddresse,
 *         conformAddress,
 *         numericAddress.system,
 *         numericAddress.index1,
 *         numericAddress.index2,
 *         numericAddress.index3,
 *         numericAddress.index4,
 *         numericAddress.index5 );
 *
 * //(3) Clean up
 * returnValue = ga_pv_close( &pvHandle );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_close() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * @endcode
 *
 * @note    Function is MT-safe.
 *
 * @note    Only the arguments of interest must be specified. The other can be
 *          set to NULL. If all arguments (expect pv) are NULL the call will be
 *          a NOP.
 *
 *
 * @param[in]   pv                      The PV of interest.
 * @param[out]  userProvidedAddress     The address as given by the user by
 *                                      calling ga_pv_open. Don't free it!
 *                                      If this parameter is of no interest,
 *                                      please specify the argument as NULL.
 *                                      <b>If the user did not specify a
 *                                         alias (see #ga_pv_open) this argument
 *                                         will be set to zero! </b>
 * @param[out]  conformAddress          The conform address as specified by
 *                                      ga_pv_open in combination with the
 *                                      property parameter.
 *                                      If this parameter is of no interest,
 *                                      please specify the argument as NULL.
 * @param[out]  numericAddress          The numeric address of the PV.
 *                                      If this parameter is of no interest,
 *                                      please specify the argument as NULL.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_getAddress( const ga_ConstPV pv,
                  const char** const userProvidedAddress,
                  const char** const conformAddress,
                  gc_Level6Address* const numericAddress );

/**
 * Tries to flush the internal data buffers of the PV, if the concrete PV
 * supports this operation. Otherwise an error will be returned.
 *
 * This flush will wait up to timeoutMS ms for flushing, if no data was in the
 * buffer. If there was data added just before the timeoutMS would have expired
 * the data will be flushed and the timeout will be reloaded! E.g. if the
 * timeoutMS was set to 2 seconds and an other process writes data every
 * second into the buffer ga_pv_flush will never return.
 *
 * @note    Available for PV type: \n
 *             - #ga_PV_TYPE_FIFO.
 *
 * @note    In case the PV has logging available (not even activated) it might
 *          happen that data will NOT be flushed, which logically should be.
 *          Reason is that internally the gaservice uses two FIFOs. One for
 *          put-access the other for get-access. This is required to log the
 *          values from the put-access FIFO and then move them into the get-access
 *          FIFO. Therefore it could happen, that while the gaservice is
 *          processing both FIFOs that the internal routine can't flush a
 *          value, which is currently in transition from one FIFO into the
 *          other!
 *
 * @param[in]       pv              The PV of interest.
 * @param[in]       timeoutMS       The timeout for flushing. This means that
 *                                  internally the 'flusher' waits at most this
 *                                  timeout if the FIFO is empty. After a flush
 *                                  took place the timeout will be reloaded!
 *                                  If the value is '0' this means that the
 *                                  flusher immediately returns when there are
 *                                  no other values to flush!
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_PV_TYPE_INVALID_OPERATION
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_flush( const ga_PV pv,
             uint32_t timeoutMS );

/**
 * If the PV type is of ga_PV_TYPE_FIFO this function returns the current and
 * maximum length of it. Otherwise an error will be returned.
 *
 * Beware of the commit-or-rollback semantics of the internal FIFO data
 * structure. Therefore a slot might be 'missing', because it's currently in
 * transition from used to free, or vice versa!
 *
 * Therefore the following formula must be used:
 *   free + used = max +/- 1
 *
 * We advise every developer, which wants to build robust application based
 * on the FIFOs to always rely on the internally handled synchronization
 * primitives and NOT to use this function for access. Use only this function
 * for temporary status information (e.g. a GUI shows you the current level of
 * the FIFO). If you do not consider this expect a lot of race condition
 * headache in your appliation's internal logic.
 *
 * @note    Available for PV type: \n
 *             - #ga_PV_TYPE_FIFO.
 *
 * @param[in]       pv                  The PV of interest.
 * @param[in,out]   lengthInfo          Will hold the length information of the PV.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_PV_TYPE_INVALID_OPERATION
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_getFifoLength( const ga_ConstPV pv,
                     ga_FIFOLengthInfo* lengthInfo );


/**
 * Retrieves the type of the PV.
 *
 * Don't mistake this function for ga_pv_getDataType! Former is the internal
 * type of the PV (e.g. it represents a simple single value or the values are
 * stored within a FIFO) and the latter one represents the data type of the
 * value(s) accessible via the PV.
 *
 * @note    Available for PV type: \n
 *             - #ga_PV_TYPE_SINGLE_VALUE
 *             - #ga_PV_TYPE_FIFO.
 *
 * @param[in]       pv            The PV of interest.
 * @param[in,out]   type          Will hold the concrete type of the PV.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_getPVType( const ga_ConstPV pv,
                 ga_PVType* type );

/**
 * Gets the value for a specific property.
 *
 * The PV type defines if the set operation is valid! Otherwise
 * #gc_ERROR_PV_TYPE_INVALID_OPERATION will be returned! In addition it's only
 * possible to put/get the value of an configured property. This means if the
 * blocking timeout of a FIFO should be set to X seconds the FIFO must have
 * been opened with this property, otherwise #gc_ERROR_COM_INVALID_ARGUMENT
 * will be returned!
 *
 * The following table shows which types support which put operation:
 *
 * PV Type:                         Property:
 * =============================================================================
 * #ga_PV_TYPE_SINGLE_VALUE         None supported!
 *
 * #ga_PV_TYPE_FIFO                 ga_PV_PROPERTY_GET_EMPTY_BLOCK:
 *                                   - PV must be configured with this property
 *                                   - if value.type is not gc_DATA_TYPE_UINT_32
 *                                     it will be cleared (gc_Value_free),
 *                                     reinitialized with the reqired data
 *                                     type and finally assigned!
 *
 *                                  ga_PV_PROPERTY_PUT_FULL_BLOCK:
 *                                   - PV must be configured with this property
 *                                   - if value.type is not gc_DATA_TYPE_UINT_32
 *                                     it will be cleared (gc_Value_free),
 *                                     reinitialized with the reqired data
 *                                     type and finally assigned!
 *
 * @note    If you wanna quickly edit some property just call this function and
 *          then use the created gc_Value to call put. Note that if the property
 *          is associated with a complex (blob/string) value the data must
 *          be freed!
 *
 *
 * @param[in]   pv                      The PV of interest.
 * @param[in]   property                Holds the property to get.
 * @param[in]   value                   This value will hold the value of the
 *                                      property. If the data types don't match
 *                                      the function will clean up the value
 *                                      and reinitialize it. If the property
 *                                      will hold a string/blob then don't forget
 *                                      to free the memory later!
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_getPropertyValue( const ga_ConstPV pv,
                        ga_PVProperty property,
                        gc_Value* value );

/**
 * Sets the value for a specific property.
 *
 * The PV type defines if the set operation is valid! Otherwise
 * #gc_ERROR_PV_TYPE_INVALID_OPERATION will be returned! In addition it's only
 * possible to put/get the value of an configured property. This means if the
 * blocking timeout of a FIFO should be set to X seconds the FIFO must have
 * been opened with this property, otherwise #gc_ERROR_COM_INVALID_ARGUMENT
 * will be returned!
 *
 * The following table shows which types support which put operation:
 *
 * PV Type:                        Property & Description (Prerequisites!):
 * =============================================================================
 * #ga_PV_TYPE_SINGLE_VALUE         None supported!
 *
 * #ga_PV_TYPE_FIFO                 ga_PV_PROPERTY_GET_EMPTY_BLOCK:
 *                                   - PV must be configured with this property
 *                                   - value.type must be gc_DATA_TYPE_UINT_32
 *
 *                                  ga_PV_PROPERTY_PUT_FULL_BLOCK:
 *                                   - PV must be configured with this property
 *                                   - value.type must be gc_DATA_TYPE_UINT_32
 *
 * @param[in]   pv                      The PV of interest.
 * @param[in]   property                Holds the property to set.
 * @param[in]   value                   Holds the value for the property with
 *                                      the expected type!
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_putPropertyValue( const ga_ConstPV pv,
                        ga_PVProperty property,
                        const gc_Value* value );


/******************************************************************************
 * PV Interface - Lock-Synchronized Block Access
 ******************************************************************************/
/**
 * The same as ga_pv_getValue but allows atomic access to multiple PVs.
 *
 * The atomicity of this operation is guaranteed by using a single lock, shared
 * between all PVs.
 *
 * The PV values will be read in exactly the same order as they are specified in
 * the array where PVs points to.
 *
 * The PVs and gc_NumericValues are associated via the same index of the arrays.
 *
 * If the lock is available for N PVs it's not required to quote all these PVs
 * in this function if only M are of interest (In this case M is less than N).
 *
 * If this function fails the value of the given output variables is undefined.
 * This means that some values might be read but others not.
 *
 * The following code sample shows how to retrieve a group of values:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * size_t SIZE = 10;                    //Number of PV/values.
 * size_t i;                            //Loop counter.
 * ga_PV pvHandle[SIZE] = { 0 };        //Will hold the handles of the PVs.
 * gc_NumericValue values[SIZE];           //Will contain the read values.
 *
 * //(1) Open multiple PVs and set values to write. For this sample the
 * //    data type of all PVs are uint32_t.
 * for( i = 0; i < SIZE; ++i )
 * {
 *     //For sample-purpose no error handling.
 *     //In production code using the below string manipulation code should be
 *     //considered unsafe.
 *     char pvName[100] = { 0 };
 *     sprintf( pvName, "x_%u", i );
 *
 *     returnValue = ga_pv_open( &pvHandle[i], pvName, ga_PV_PROPERTY_ACC_BLOCKING );
 *     if( gc_ERROR_SUCCESS.errorID != returnValue )
 *     {
 *         fprintf( stderr, "Call to ga_pv_open() failed.\n" );
 *         fprintf( stderr, "Error ID=%d\n", returnValue );
 *         fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *         exit( -1 );
 *     }
 * }
 *
 * //(2) Read all PV values and write them onto stdout.
 * returnValue = ga_pv_getGroup( pv, values, SIZE );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_getGroup() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * for( i = 0; i < SIZE; ++i )
 * {
 *      printf( "Value of PV # %u is '%u'\n", i, values[i].uint32 );
 * }
 *
 * //(3) Clean up all opened PVs.
 * for( i = 0; i < SIZE; ++i )
 * {
 *     returnValue = ga_pv_close( &pvHandle[i] );
 *     if( gc_ERROR_SUCCESS.errorID != returnValue )
 *     {
 *         fprintf( stderr, "Call to ga_pv_close() failed.\n" );
 *         fprintf( stderr, "Error ID=%d\n", returnValue );
 *         fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *         exit( -1 );
 *     }
 * }
 * @endcode
 *
 * @param[in]   pvs     Points to an array of PVs to be used for atomic access.
 *                      All PVs must use the same lock. Otherwise the function
 *                      will return
 * @param[out]  values  Points to an array gc_NumericValues to store the retrieved
 *                      values from the PV.
 * @param[in]   count   The length of pvs/values.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \
 *          \n
 *          #gc_ERROR_PV_NO_COMMON_LOCK
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_getGroup( const ga_ConstPV* pvs,
                gc_Value* values,
                const size_t count );

/**
 * The same as ga_pv_putValue but allows atomic access to multiple PVs.
 *
 * The atomicity of this operation is guaranteed by using a single lock, shared
 * between all PVs.
 *
 * The PV values will be written in exactly the same order as they are specified
 * in the array where pvs points to.
 *
 * The PVs and gc_NumericValues are associated via the same index of the arrays.
 *
 * If the lock is available for N PVs it's not required to quote all these PVs
 * in this function if only M are of interest (In this case M is less than N).
 *
 * If this function fails the value of the given PVs undefined. This means that
 * some values might be written and others not.
 *
 * The following code sample shows how to retrieve a group of values:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * size_t SIZE = 10;                    //Number of PV/values.
 * size_t i;                            //Loop counter.
 * ga_PV pvHandle[SIZE] = { 0 };        //Will hold the handles of the PVs.
 * gc_NumericValue values[SIZE];           //Will contain the read values.
 *
 * //(1) Open multiple PVs and set values to write. For this sample the
 * //    data type of all PVs are uint32_t.
 * for( i = 0; i < SIZE; ++i )
 * {
 *     //For sample-purpose no error handling.
 *     //In production code using the below string manipulation code should be
 *     //considered unsafe.
 *     char pvName[100] = { 0 };
 *     sprintf( pvName, "x_%u", i );
 *
 *     returnValue = ga_pv_open( &pvHandle[i], pvName, ga_PV_PROPERTY_ACC_BLOCKING );
 *     if( gc_ERROR_SUCCESS.errorID != returnValue )
 *     {
 *         fprintf( stderr, "Call to ga_pv_open() failed.\n" );
 *         fprintf( stderr, "Error ID=%d\n", returnValue );
 *         fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *         exit( -1 );
 *     }
 *
 *     values[i].uint32 = i;        //Assumption: size_t to uint32_t conversion is safe.
 * }
 *
 * //(2) Write all PV values
 * returnValue = ga_pv_putGroup( pvHandle, values, SIZE );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_getGroup() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //(3) Clean up all opened PVs.
 * for( i = 0; i < SIZE; ++i )
 * {
 *     returnValue = ga_pv_close( &pvHandle[i] );
 *     if( gc_ERROR_SUCCESS.errorID != returnValue )
 *     {
 *         fprintf( stderr, "Call to ga_pv_close() failed.\n" );
 *         fprintf( stderr, "Error ID=%d\n", returnValue );
 *         fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *         exit( -1 );
 *     }
 * }
 * @endcode
 *
 * @param[in]   pvs     Points to an array of PVs to be used for atomic access.
 *                      All PVs must use the same lock. Otherwise the function
 *                      will return
 * @param[out]  values  Points to an array gc_NumericValues to write to the PVs.
 * @param[in]   count   The length of pvs/values.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_PV_NO_COMMON_LOCK
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_putGroup( const ga_PV* pvs,
                const gc_Value* values,
                const size_t count );



/******************************************************************************
 * PV Interface - Identity Check
 ******************************************************************************/
/**
 * Tests two PV handles to reference the same PV object.
 *
 * This function does check the identity and not the equivalence of a PV.
 * The identity will validate that n PV handles are referencing the same
 * PV object in memory. The equivalence does only validate the 'equality' of
 * several PV object by using some data fields to compare.
 *
 * The identity of a PV can <b>NOT</b> be checked by simply comparing the pointers
 * of the PV handles. Only the API has access to the required internal information!
 *
 * The following code sample shows how to use this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * ga_PV pvA;                   //Already opened.
 * ga_PV pvB;                   //Already opened.
 * bool isIdentical = false;    //Will contain the identity information.
 *
 * //Do the two PV handles refer to the same PV object?
 * returnValue = ga_pv_isIdentical( pvA, pvB, &isIdentical );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_isIdentical() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * printf( "Do pvA and pvB refer to the same PV Object? %s",
 *         isIdentical ? "Yes" : "No" );
 *
 * @endcode
 *
 * @param[in]   pvA             The first PV handle to check against the second
 *                              one.
 * @param[in]   pvB             The second PV handle to check against the first
 *                              one.
 * @param[out]  isIdentical     True: pvA and pvB using the same PV object.
 *                              False: pvA and pvB are using different PV objects.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *           \n
 *           #gc_ERROR_ATTACH_MISSING \n
 *           \n
 *           #gc_ERROR_COM_INVALID_ARGUMENT \n
 *           #gc_ERROR_COM_INTERNAL_ERROR \n
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_isIdentical( const ga_ConstPV pvA,
                   const ga_ConstPV pvB,
                   bool* const isIdentical );


/******************************************************************************
 * PV Interface - Property
 ******************************************************************************/
/**
 * Sets the data model property field of a PV.
 *
 * Don't confuse this function with #ga_pv_putPropertyValue! The function
 * #ga_pv_putPropertyValue sets the PV handle's property, whereas this function
 * (#ga_pv_putDataModelProperty) sets the property field of the data model!
 *
 * @code
 *
 * //Change the property "propertyX".
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * ga_PV pv;                                //Already opened!
 * const char* propertyName = "propertyX";  //The name of the property to change.
 * gc_Value propertyValue;                  //Will hold the new value for the property.
 *
 * // Initialize the propertyValue.
 * // For this sample the assumption is that the data type of the property
 * // is #gc_DATA_TYPE_STRING.
 * returnValue = gc_Value_init( &propertyValue, gc_DATA_TYPE_STRING, 0 );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to  gc_Value_init() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * // Assign the future property value to the propertyValue variable, by using
 * // the following gacommon convenience function for string conversion:
 * returnValue = gc_Value_convertFromString( &propertyValue, "New Value for Property", true );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to  gc_Value_convertFromString() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * // Write the new property value into the data model.
 * returnValue = ga_pv_putDataModelProperty( pv, propertyName, &propertyValue);
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_putDataModelProperty() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //Cleanup all allocated resources (EXCLUDE pv handle!)
 * returnValue = gc_Value_free( &propertyValue );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gc_Value_free() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }

 * @endcode
 *
 * @param[in]   pv                      The PV of interest.
 * @param[in]   name                    The name of the property.
 * @param[in]   value                   Holds the value for the property with
 *                                      the expected type!
 * @param[in]   doCreateIfNotExists     Flag for defining the behavior of the
 *                                      function in case the property with the
 *                                      given name does not exist.
 *                                      True:   The property will be created.
 *                                      False:  The function returns with error
 *                                              #gc_ERROR_SERVICE_OBJECT_NOT_EXIST,
 *                                              indicating that the a property
 *                                              with the given name does not
 *                                              exist.
 *
 * @note:   A property field will be shared by all PVs indices. This means that
 *          PV[0] and PV[123] share the same property and therefore changes to
 *          PV[0]'s property PROPERTY will be also reflected in PV[123]'s
 *          property PROPERTY!
 *
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_SERVICE_OBJECT_NOT_EXIST \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_putDataModelProperty( const ga_PV pv,
                            const char* const name,
                            const gc_Value* const value,
                            const bool doCreateIfNotExists );


/**
 * Retrieves the given data model property field of a PV.
 *
 * Don't confuse this function with #ga_pv_getPropertyValue! The function
 * #ga_pv_getPropertyValue gets the PV handle's property, whereas this function
 * (#ga_pv_getDataModelProperty) gets the property field of the data model!
 *
 * @code
 *
 * //Get property "propertyX" and print it onto console.
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * ga_PV pv;                                //Already opened!
 * const char* propertyName = "propertyX";  //The name of the property to print.
 * gc_Value propertyValue;                  //Will hold the value of the property.
 *
 * // Initialize the propertyValue.
 * // If the data type does not match the actual one it'll be automatically
 * // reset by #ga_pv_getDataModelProperty(...).
 * returnValue = gc_Value_init( &propertyValue, gc_DATA_TYPE_STRING, 0 );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to  gc_Value_init() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //Retrieve the value of the property
 * returnValue = ga_pv_getDataModelProperty( pv, propertyName, &propertyValue);
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_getDataModelProperty() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * // Convert the binary representation of the property value into a textual
 * // one for pretty printing.
 * char* textualPropertyValue = 0;
 * returnValue = gc_Value_print( &propertyValue, &textualPropertyValue, 0, 0 );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gc_Value_print() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * printf( "The property '%s' has the value: '%s'", propertyName, textualPropertyValue );
 *
 * //Cleanup all allocated resources (EXCLUDE pv handle!)
 * returnValue = gc_Value_free( &propertyValue );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gc_Value_free() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * returnValue = gc_freeMemory( &textualPropertyValue );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gc_freeMemory() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   pv                      The PV of interest.
 * @param[in]   name                    The name of the property.
 * @param[in]   value                   This value will hold the value of the
 *                                      property. If the data types don't match
 *                                      the function will clean up the value
 *                                      and reinitialize it. If the property
 *                                      will hold a string/blob then don't forget
 *                                      to free the memory later!
 *
 * @note:   A property field will be shared by all PVs indices. This means that
 *          PV[0] and PV[123] share the same property and therefore changes to
 *          PV[0]'s property PROPERTY will be also reflected in PV[123]'s
 *          property PROPERTY!
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_getDataModelProperty( const ga_ConstPV pv,
                            const char* const name,
                            gc_Value* value );


/**
 * Retrieves all pv data model property names.
 *
 * @code
 *
 * //Get property names, print them and free them.
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * ga_PV pv;                   //Already opened!
 * size_t propertyNameCount = 0;
 * char** propertyNames = 0;
 *
 * // Retrieve all property names of the given PV handle
 * returnValue = ga_pv_getDataModelPropertyNames( pv, &propertyNameCount, &propertyNames );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_getDataModelPropertyNames() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * // print them on stdout
 * for( size_t i = 0; i < propertyNameCount; ++propertyNameCount )
 * {
 *     printf( "%s\n", propertyNames[i] );
 * }
 *
 * //free malloced meory
 * for( size_t i = 0; i < propertyNameCount; ++propertyNameCount )
 * {
 *     gc_freeMemory( propertyNames[i] );
 * }
 * gc_freeMemory( propertyNames );
 *
 * @endcode
 *
 * @param[in]       pv              The PV of interest.
 * @param[in,out]   returned        The number of returned propertyNames.
 * @param[in,out]   propertyNames   Pointer to property name array. The array is
 *                                  malloced. Ownership is passed to the caller.
 *                                  Use gc_freeMemory to clean up.
 *                                  The data structure is a two dimensional
 *                                  array on the heap.
 *                                  If no properties exist for the given PV
 *                                  the parameter 'returned' will be set to 0
 *                                  and the pointer of this parameter will
 *                                  NOT be changed.
 *
 *
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_getDataModelPropertyNames( const ga_ConstPV pv,
                                 size_t* const returned,
                                 char*** const propertyNames );

#endif  /* GAMMA_API_PV_H__ */
