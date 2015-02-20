#ifndef PVMETADATA_H_
#define PVMETADATA_H_

/**
 * @file
 * This header is an extension to the pv.h. It contains advanced meta
 * functionalities of the PV.
 *
 * <h3> Signal Handling Routine - Notes/Hints </h3>
 * When dealing with signaling and the Gamma callback routines the following
 * items must be known:
 * - The callback is implemented within the OS's signal handling routine. Therefore
 *   it would have the restrictions of these, but GAAPI forwards all these calls
 *   to an internal thread for dispatching. Therefore it's safe to even call
 *   non-safe functions (e.g. see POSIX.1-2003) from the callbacks. But please
 *   keep in mind that all callbacks of a PV will be executed in sequence!
 *
 * - The signal number is specified in the task section within the XML
 *   configuration files of the Gamma Service.
 *
 * - Signaling only works with local PVs (see #ga_PVLocation
 *   [#ga_pv_getMetaConfig]).
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
 * PV Interface - Complex Metadata Functionality
 ******************************************************************************/
/**
 * This function allows to manipulate the meta functionalities of a PV. For
 * example it allows to activate logging, deactivate signaling, etc. If the
 * meta functionality requires further parameter the function should be called
 * a posterior to #ga_pv_putPVField.
 *
 * The following example shows how to use this function:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * ga_PV pvHandle;              //Already opened by #ga_open_pv
 * gc_NumericValue dataValue;      //For setting minimum/maximum
 *
 * //Activation of minimum and maximum boundaries
 * //In the case of this example the data type of the PV is ga_DATA_TYPE_SINT_32.
 * //1. Set the minimum value
 * dataValue.sint32 = 100;
 * returnValue = ga_pv_putPVField( &pvHandle, &dataValue, ga_PV_FIELD_MIN );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_putPVField() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //2. Set the maximum value
 * dataValue.sint32 = 1000;
 * returnValue = ga_pv_putPVField( &pvHandle, &dataValue, ga_PV_FIELD_MAX );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_putPVField() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //3. Activate min/max boundary checks
 * returnValue = ga_pv_changeMetaFunctions( &pvHandle, gc_META_FLAG_MIN_ON |
 *                                                     gc_META_FLAG_MAX_ON );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_changeMetaFunctions() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //4. Activate signaling for this PV.
 * //   Please be advised, that in addition a callback handler must be set to
 * //   get informed, whenever the value of the PV changes (for more information
 * //   please read #ga_pv_changeSigCallback and #ga_changeGlobalSigCallback)
 * returnValue = ga_pv_changeMetaFunctions( &pvHandle,
 *                                          gc_META_FLAG_SIG_ON_SYNC_CHANGE |
 *                                          gc_META_FLAG_SIG_ON_PRIORITY_MIDDLE );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_changeMetaFunctions() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 *  //5. switch signaling off
 * returnValue = ga_pv_changeMetaFunctions( &pvHandle,
 *                                          gc_META_FLAG_SIG_OFF);
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_pv_changeMetaFunctions() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * The following table shows which GAAPI functions are using a meta functionality
 * if it is activated:\n
 * <pre>
 * meta functionality:              GAAPI function:
 * boundaries (min/max)             Only for ga_pv_putValue.
 * simulation                       Only used by ga_pv_getValue. In this case
 *                                  a simulated value, instead the original
 *                                  is read. The function ga_pv_putValue will
 *                                  always write on the original value and
 *                                  never on the simulated one.
 * signaling                        Done by the service. No GAAPI function will
 *                                  emit a signal.
 * logging                          Done by the service. No GAAPI function will
 *                                  log a value.
 * </pre>
 *
 * @note    The boundary values min/max are always inclusive.
 *
 * @note    Multiple activations/deactivations of meta functionalities will
 *          not cause an error.
 *
 * @note    This function only works for PVs with a numeric type. Strings/Blobs
 *          are currently not supported.
 *
 * @note    This function is only MT-safe, if the PV under change is associated
 *          with a lock.
 *
 * @note    The state of the meta functionalities is undefined, if the function
 *          fails the following errors:
 *           - gc_ERROR_PV_META_OP_NOT_AVAILABLE
 *           - gc_ERROR_COM_INTERNAL_ERROR
 *
 * @note    In case signal will be active (with or without other meta
 *          functionalities) and it is already activated the error
 *          #gc_ERROR_PV_SIG_ALREADY_ACTIVATED will be returned and NO other
 *          meta functionalities will have been changed.
 *
 * @note    In case signal will be deactivated without other meta functionalities
 *          and signaling is already deactivated the error code
 *          #gc_ERROR_PV_SIG_ALREADY_DEACTIVATED will be returned.
 *          If signal is already off and will be requested to be deactivated
 *          AND also other metafunctionalities will be deactivated/
 *          activated NO #gc_ERROR_PV_SIG_ALREADY_DEACTIVATED will be returned.
 *
 * @param[in]   pv          The PV of interest.
 * @param[in]   flags       Specifies the meta functions to change. The
 *                          logging, min/max and simulation meta functionalities
 *                          are a global property of the PV, but not signaling.
 *                          Signaling is a process-/thread-unique attribute of
 *                          a PV.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_PV_INVALID_DATA_TYPE \n
 *          #gc_ERROR_PV_META_OP_NOT_AVAILABLE \n
 *          #gc_ERROR_PV_INVALID_DATA_TYPE \n
 *          #gc_ERROR_PV_SIG_ALREADY_ACTIVATED \n
 *          #gc_ERROR_PV_SIG_ALREADY_DEACTIVATED \n
 *          \n
 *          #gc_ERROR_SERVICE_SYSTEM_NOT_FOUND \n
 *          #gc_ERROR_SERVICE_DUPLICATED_NAME \n
 *          #gc_ERROR_SERVICE_OBJECT_NOT_EXIST \n
 *          #gc_ERROR_SERVICE_NO_SUCH_HANDLE \n
 *          #gc_ERROR_SERVICE_BAD_BROWSING_STATE \n
 *          #gc_ERROR_SERVICE_OUT_OF_MEMORY \n
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_changeMetaFunctions( const ga_PV pv,
                           const gc_Flags32Bit flags );


/**
 * Retrieves the configuration of the meta functionality of the given PV pv and
 * stores them in metaConfig.
 *
 * This function is only MT-safe, if the PV under change is associated with a lock.
 * If this is not the case the retrieved metaConfig might have an undefined
 * value. This is the case if a concurrent process calls the API function
 * #ga_pv_changeMetaFunctions(...) while #ga_pv_getMetaConfig(...) is also processed.
 *
 * The useRPCs parameter specifies if the complete ga_MetaConfig structure
 * should be updated, by using the required RPCs. Therefore this flag gives
 * the user the flexibility to access local information at 'high speed' and
 * remote/RPC information with a much greater delay. The following table shows
 * which information are RPC-dependent:
 * <pre>
 * information/variable:            required useRPCs=1:
 * =============================================================================
 * state                            no
 * location                         no
 * pvProperty                       no
 * flags                            yes for:
 *                                    logging
 *                                    simulation
 *                                    minimum and maximum
 *                                  no for:
 *                                    signaling
 * </pre>
 *
 * The following code sample shows how to use this function:
 * @code
 * #include <gaapi/pvMetaData.h>
 * #include <gaapi/misc.h>
 *
 * //
 * // Sample function to print the meta configuration of the given PV handle
 * // to stdout.
 * //
 * // @param[in]    pvHandle    The PV of interest.
 * //
 * void printMetaConfigSample( ga_PV pvHandle )
 * {
 *     gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 *     ga_MetaConfig metaConfig;    //For storing the meta flag configuration
 *
 *     //1. Retrieve the current meta flag state
 *     returnValue = ga_pv_getMetaConfig( pvHandle, &metaConfig );
 *     if( gc_ERROR_SUCCESS.errorID != returnValue )
 *     {
 *         fprintf( stderr, "Call to ga_pv_getMetaConfig() failed.\n" );
 *         fprintf( stderr, "Error ID=%d\n", returnValue );
 *         fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *         exit( -1 );
 *     }
 *
 *     //2. Print the configuration (using utility function from misc.h)
 *     char* metaConfigTxt = 0;
 *     returnValue = ga_printPVMetaConfig( &metaConfig, 0, &metaConfigTxt, 0 );
 *     if( gc_ERROR_SUCCESS.errorID != returnValue )
 *     {
 *         fprintf( stderr, "Call to ga_printPVMetaConfig() failed.\n" );
 *         fprintf( stderr, "Error ID=%d\n", returnValue );
 *         fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *         exit( -1 );
 *     }
 *
 *     fprintf( stdout, "%s\n", metaConfigTxt );
 *
 *     //Don't forget to clean up the internally malloc'ed memory
 *     returnValue = gc_freeMemory( &metaConfigTxt );
 *     if( gc_ERROR_SUCCESS.errorID != returnValue )
 *     {
 *         fprintf( stderr, "Call to gc_freeMemory() failed.\n" );
 *         fprintf( stderr, "Error ID=%d\n", returnValue );
 *         fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *         exit( -1 );
 *     }
 * }
 *
 * @endcode
 *
 * @note    The retrieval of the metaConfig works for all PV data types.
 *
 * @param[in]   pv          The PV of interest.
 * @param[out]  metaConfig  Will contain the meta function at the time the
 *                          function was called.
 * @param[in]   useRPCs     Specifies the informations to be retrieved:
 *                           - If set to 'false': No RPCs are used. In this case the
 *                             value of the flag field won't be changed. Use this
 *                             option if run-time is important (e.g. if the
 *                             metaConfig.state parameter get's polled for
 *                             ga_DATA_OBJECT_STATE_OK, etc. )
 *                             Beware that some functions functions require
 *                             a <b>COMPLETELY</b> filled out ga_MetaConfig
 *                             to work!
 *                           - If set to 'true': All RPCs are issued to fill the
 *                             complete metaConfig parameter.
 *                             It's advised to use this option as default.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_PV_INVALID_DATA_TYPE \n
 *          #gc_ERROR_PV_META_OP_NOT_AVAILABLE \n
 *          \n
 *          #gc_ERROR_SERVICE_SYSTEM_NOT_FOUND \n
 *          #gc_ERROR_SERVICE_DUPLICATED_NAME \n
 *          #gc_ERROR_SERVICE_OBJECT_NOT_EXIST \n
 *          #gc_ERROR_SERVICE_NO_SUCH_HANDLE \n
 *          #gc_ERROR_SERVICE_BAD_BROWSING_STATE \n
 *          #gc_ERROR_SERVICE_OUT_OF_MEMORY \n
 *
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_getMetaConfig( const ga_ConstPV pv,
                     ga_MetaConfig* const metaConfig,
                     bool useRPCs );

/**
 * Explicitly gets an internal data field of PV. If meta functionalities
 * are used depends on the given #gc_PVFieldType. For more information please
 * read the documentation for it.
 *
 * The following code sample shows how to use this function:
 * @code
 * #include <gaapi/pvMetaData.h>
 * #include <gaapi/misc.h>
 *
 * //
 * // Sample function to retrieve the value of a specific PV and print it's
 * // value on stdout.
 * //
 * // @pre          The specific PV must have ALL meta functionalities
 * //               available for access.
 * //
 * // @param[in]    pvHandle    The PV of interest. Already opened via
 * //                           ga_pv_open.
 * // @param[in]    dataType    The data type of the PV of interest.
 * //
 * void sample( ga_PV pvHandle,
 *              gc_DataType dataType )
 * {
 *     gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 *     gc_NumericValue value;              //Will hold the current value of the given gc_PVFieldType.
 *     uint32_t i;                      //loop counter
 *     char* dataValueTxt = 0;          //Will hold the textual repr. of value.
 *     const char* fieldTypeTxt = 0;    //Will hold the textual repr. of gc_PVFieldType.
 *
 *
 *     //Iterate over the gc_PVFieldType and print the corresponding values on stdout.
 *     for( i = 1; i < ga_PV_FIELD_MAX; ++i )
 *     {
 *         //Get all data and create textual representations.
 *         returnValue = ga_pv_getPVField( pvHandle, &value, gc_PVFieldType( i ) );
 *         if( gc_ERROR_SUCCESS.errorID != returnValue )
 *         {
 *             fprintf( stderr, "Call to ga_pv_getPVField() failed.\n" );
 *             fprintf( stderr, "Error ID=%d\n", returnValue );
 *             fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *             exit( -1 );
 *         }
 *
 *         returnValue = gc_PVFieldType_print( gc_PVFieldType( i ), &fieldTypeTxt );
 *         if( gc_ERROR_SUCCESS.errorID != returnValue )
 *         {
 *             fprintf( stderr, "Call to gc_PVFieldType_print() failed.\n" );
 *             fprintf( stderr, "Error ID=%d\n", returnValue );
 *             fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *             exit( -1 );
 *         }
 *
 *         returnValue = ga_printDataValue( dataType, &value, &dataValueTxt, 0 );
 *         if( gc_ERROR_SUCCESS.errorID != returnValue )
 *         {
 *             fprintf( stderr, "Call to ga_printDataValue() failed.\n" );
 *             fprintf( stderr, "Error ID=%d\n", returnValue );
 *             fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *             exit( -1 );
 *         }
 *
 *         fprintf( stdout, "%s: %s\n", fieldTypeTxt, dataValueTxt );
 *
 *         //Clean up (only data value. field type is static)
 *         returnValue = gc_freeMemory( &metaConfigTxt );
 *         if( gc_ERROR_SUCCESS.errorID != returnValue )
 *         {
 *             fprintf( stderr, "Call to gc_freeMemory() failed.\n" );
 *             fprintf( stderr, "Error ID=%d\n", returnValue );
 *             fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *             exit( -1 );
 *         }
 *     }
 * }
 *
 * @endcode
 *
 * @note    This function is always MT-safe.
 * @note    This function always uses an RPC.
 * @note    This function only supports PVs with numeric data types.
 *
 * @param[in]       pv      The PV of interest.
 * @param[in,out]   value   Will contain the current field value of the PV.
 * @param[in]       type    The field type of the PV. See #gc_PVFieldType.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_PV_META_OP_NOT_AVAILABLE \n
 *          #gc_ERROR_PV_INVALID_DATA_TYPE \n
 *          \n
 *          #gc_ERROR_SERVICE_SYSTEM_NOT_FOUND \n
 *          #gc_ERROR_SERVICE_DUPLICATED_NAME \n
 *          #gc_ERROR_SERVICE_OBJECT_NOT_EXIST \n
 *          #gc_ERROR_SERVICE_NO_SUCH_HANDLE \n
 *          #gc_ERROR_SERVICE_BAD_BROWSING_STATE \n
 *          #gc_ERROR_SERVICE_OUT_OF_MEMORY \n
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_getPVField( const ga_ConstPV pv,
                  gc_NumericValue* const value,
                  const gc_PVFieldType type );

/**
 * Explicitly sets an internal data field of the PV. If meta functionalities
 * are used depends on the given #gc_PVFieldType. For more information please
 * read the documentation for it.
 *
 * The following code sample shows how to use this function:
 * @code
 * #include <gaapi/pvMetaData.h>
 *
 * //
 * // Sample function to reset all the ga_PVFieldValue's to the given
 * // user-defined gc_NumericValue.
 * //
 * // @pre          The specific PV must have ALL meta functionalities
 * //               available for access.
 * //
 * // @param[in]    pvHandle    The PV of interest. Already opened via
 * //                           ga_pv_open.
 * // @param[in]    resetValue  The reset value to use.
 * //
 * void sampleReset( const ga_PV pvHandle,
 *                   const gc_NumericValue* const resetValue )
 * {
 *     gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 *     uint32_t i;                      //loop counter
 *
 *     //Iterate over the gc_PVFieldType and print the corresponding values on stdout.
 *     for( i = 1; i < ga_PV_FIELD_MAX; ++i )
 *     {
 *         //Get all data and create textual representations.
 *         returnValue = ga_pv_putPVField( pvHandle, &resetValue, gc_PVFieldType( i ) );
 *         if( gc_ERROR_SUCCESS.errorID != returnValue )
 *         {
 *             fprintf( stderr, "Call to ga_pv_putPVField() failed.\n" );
 *             fprintf( stderr, "Error ID=%d\n", returnValue );
 *             fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *             exit( -1 );
 *         }
 *     }
 * }
 *
 * @endcode
 *
 * @note    This function is always MT-safe.
 * @note    This function always uses an RPC.
 * @note    This function only supports PVs with numeric data types.
 *
 * @param[in]       pv      The PV of interest.
 * @param[in]       value   Contains the value to copy into the PV field value.
 * @param[in]       type    The field type of the PV. See #gc_PVFieldType.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_PV_META_OP_NOT_AVAILABLE \n
 *          #gc_ERROR_PV_BOUND_REJECTED \n
 *          #gc_ERROR_PV_INVALID_DATA_TYPE \n
 *          \n
 *          #gc_ERROR_SERVICE_SYSTEM_NOT_FOUND \n
 *          #gc_ERROR_SERVICE_DUPLICATED_NAME \n
 *          #gc_ERROR_SERVICE_OBJECT_NOT_EXIST \n
 *          #gc_ERROR_SERVICE_NO_SUCH_HANDLE \n
 *          #gc_ERROR_SERVICE_BAD_BROWSING_STATE \n
 *          #gc_ERROR_SERVICE_OUT_OF_MEMORY
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_putPVField( const ga_ConstPV pv,
                  const gc_NumericValue* const value,
                  const gc_PVFieldType type );

/**
 * Normally and almost always the state of the PV is managed by the gaservice.
 * However, in very rare cases (this means you are 100% aware of the consequences
 * of your actions) it's okay to let a user-process change the state of the PV.
 *
 * E.g. the RST GammaV process gaPLCAdapter is used to map arbitrary, non-PV-based
 * I/O components to a data model. This allows to provide PLC semantics in an
 * environment where e.g. only messaging is used. In such a case the adapter
 * process is safe to manage the PV state on it's own.
 *
 * Here's a quick overview of the things to consider when you are going to
 * change the PV state manually:
 * 1) Avoidance of potential race conditions
 * 1.1) Are you the only user-process, which changes the PV state?
 * 1.2) Is the PV only locally available?
 * 1.3) Is the PV NOT associated with an I/O plugin?
 *
 * Only if you can answer the above questions with Yes it's safe to change
 * the PV state on your own. Otherwise, please evaluate you software design.
 *
 * The changed PV state is queryable by calling #ga_pv_getMetaConfig.
 *
 * @note    Only the state of a local PV can be changed. If you violate this
 *          requirement you will get an #gc_ERROR_COM_INVALID_ARGUMENT error.
 *
 * @param[in]       pv      The PV of interest.
 * @param[in]       state   New state of the PV.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 *          \n
 *          #gc_ERROR_PV_META_OP_NOT_AVAILABLE \n
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_setPVState( const ga_PV pv,
                  const ga_PVState state );



/******************************************************************************
 * PV Interface - Signaling Specific Metadata Functionality
 ******************************************************************************/
/**
 * Changes the signaling callback handler and it's associated user data pointer
 * for the given PV. If signaling was activated for the PV, but no handler
 * was set the global one will be called, if it was set. Otherwise nothing
 * will happen!
 *
 * The following code sample shows how to use this function:
 * @code
 * #include <gaapi/pvMetaData.h>
 * #include <gaapi/misc.h>
 *
 * //Specifies the 'real' userData as will be passed to the signaling callback.
 * typedef struct UserData
 * {
 *     char data[100];
 *     int i;
 *     //etc.
 * } UserData;
 *
 * ///The signaling callback to register.
 * ///The implementation relys on the support of printf in a asynchronous signal
 * ///handler context.
 * void gc_CALLCONV signalingCallback( ga_PV pv,
 *                                     void* userData )
 * {
 *     //Cast the userData to the real type
 *     UserData* ud = (UserData*)userData;
 *
 *     //Use the user data...
 *
 *     gc_ErrorID returnValue = 0;
 *     //Print the current PV value onto stdout.
 *     //...sorry, but ga_printPV() does not work here!
 *
 *     const int MAXIMUM_PRINT_SIZE = 256;
 *     char dest[MAXIMUM_PRINT_SIZE];
 *
 *     gc_DataType type = 0;
 *     gc_NumericValue value;
 *
 *     returnValue = ga_pv_getDataType(pv, &type);
 *     if( gc_ERROR_SUCCESS.errorID != returnValue )
 *     {
 *         fprintf( stderr, "Call to  ga_pv_getDataType() in signalingCallback() failed.\n" );
 *         fprintf( stderr, "Error ID=%d\n", returnValue );
 *         fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *         exit( -1 );
 *     }
 *     returnValue = ga_pv_getValue(pv, &value);
 *     if( gc_ERROR_SUCCESS.errorID != returnValue )
 *     {
 *         fprintf( stderr, "Call to  ga_pv_getValue() in signalingCallback() failed.\n" );
 *         fprintf( stderr, "Error ID=%d\n", returnValue );
 *         fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *         exit( -1 );
 *     }
 *
 *     returnValue = ga_printDataValue(type, &value, dest, MAXIMUM_PRINT_SIZE);
 *     if( gc_ERROR_SUCCESS.errorID != returnValue )
 *     {
 *         fprintf( stderr, "Call to  ga_printDataValue() in signalingCallback() failed.\n" );
 *         fprintf( stderr, "Error ID=%d\n", returnValue );
 *         fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *         exit( -1 );
 *     }
 *
 *     fprintf(stdout, "%s\n", dest);
 *     fflush(stdout);
 * }
 *
 * //
 * // Sample function to set and clear the PV-/thread-specific signaling callback.
 * //
 * // @pre       The specific PV must have ALL meta functionalities
 * //            available for access. In addition signaling is already
 * //            active for the PV.
 * //
 * // @param[in]    pvHandle    The PV of interest. Already opened via
 * //                           ga_pv_open.
 * void sample( ga_PV pv,
 *              void* userData )
 * {
 *     gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 *
 *     //(1a) Set the PV signal handler.
 *     returnValue = ga_pv_changeSigCallback( pv, &signalingCallback, userData );
 *     if( gc_ERROR_SUCCESS.errorID != returnValue )
 *     {
 *         fprintf( stderr, "Call to ga_pv_changeSigCallback() failed.\n" );
 *         fprintf( stderr, "Error ID=%d\n", returnValue );
 *         fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *         exit( -1 );
 *     }
 *
 *     // (1b) Activate Signaling for the PV
 *     ga_pv_changeMetaFunctions( pv,
 *                                gc_META_FLAG_SIG_ON_SYNC_CHANGE |
 *                                gc_META_FLAG_SIG_ON_PRIORITY_MIDDLE );
 *
 *     //The handler was successfully registered and the PV's signaling is activated.
 *     //Now whenever a signal will be sent the user-specified handler will be called.
 *     //The global signal handler is temporarily disabled
 *     //while the user-specified signal handler is set.
 *
 *     //(2) CLEAR  the PV and trigger PV's signal handler, once.
 *     gc_NumericValue value;
 *     value.uint64 = 0;
 *     returnValue = ga_pv_putPVField( pv, &value, gc_DATA_OBJECT_FIELD_VALUE );
 *     if( gc_ERROR_SUCCESS.errorID != returnValue )
 *     {
 *         fprintf( stderr, "Call to ga_pv_putPVField() failed.\n" );
 *         fprintf( stderr, "Error ID=%d\n", returnValue );
 *         fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *         exit( -1 );
 *     }
 *     usleep( 20 * 1000L ); // sleep for 20ms, to allow signal handler to interact
 *
 *
 *     //(3a) Reset The Signaling in the MetaFunctions of PV
 *
 *     returnValue =ga_pv_changeMetaFunctions( pv, gc_META_FLAG_SIG_OFF );
 *     if( gc_ERROR_SUCCESS.errorID != returnValue )
 *     {
 *         fprintf( stderr, "Call to ga_pv_changeMetaFunctions() failed.\n" );
 *         fprintf( stderr, "Error ID=%d\n", returnValue );
 *         fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *         exit( -1 );
 *     }
 *
 *     // (3b) Finally reset the PV signal handler. (will reactivate the global handler)
 *     returnValue = ga_pv_changeSigCallback( pv, 0, 0 );
 *     if( gc_ERROR_SUCCESS.errorID != returnValue )
 *     {
 *         fprintf( stderr, "Call to ga_pv_changeSigCallback() failed.\n" );
 *         fprintf( stderr, "Error ID=%d\n", returnValue );
 *         fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *         exit( -1 );
 *     }
 * }
 * @endcode
 *
 * @note    Every thread is able to register its own callback. But all callbacks
 *          will be processed sequentially in the internal signaling handling
 *          routine!
 *
 * @note    This function internally locks the signaling data structure and
 *          therefore the signaling handling routine. Therefore no parallel
 *          execution of signaling handlers will occur. In addition it's not
 *          possible to change a signaling handler if any other signal
 *          handler is processed.
 *
 * @note    If at least one of such a specialized callback gets registered the
 *          global callback won't be called any more for ONLY the referenced
 *          ga_PV handle. If signaling has been activated for multiple ga_PV
 *          handles the global signaling handle will still be active for the
 *          remaining ga_PV handles.
 *
 * @note    If two ga_PV handles within a thread refer to the same PV into the
 *          SHM and this function gets first called for ga_PV_0 and than for
 *          ga_PV_1 then ga_PV_1 will be used. Therefore the last call overwrites
 *          the configuration of the previous one.
 *
 * @note    If callback gets called with 0 to clear the specialized callback
 *          the userData will be reset too!
 *
 * @note    A callback is always associated with it's PV. If ga_pv_close will
 *          be called it will automatically unregister the callback
 *
 * @note    The code of the callback will be run within the signaling
 *          handler context of the operating system. Therefore the operations
 *          within the callback underly the same restrictions.
 *
 * @note    To setup/clear for a thread a callback this function must be
 *          installed <b>and</b> removed via the same thread context!
 *
 * @note    This function does only work for PVs of #ga_PVType
 *          #ga_PV_TYPE_SINGLE_VALUE!
 *
 * @param[in]   pv          The PV of interest.
 * @param[in]   callback    Points to a callback handler. A value of 0 will
 *                          clear the thread-specific handler.
 * @param[in]   userData    Points to user data which will be forwarded to
 *                          the callback handler whenever it will be called.
 *                          The user data won't be stored if callback is 0.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_changeSigCallback( const ga_PV pv,
                         ga_SignalCallback callback,
                         void* userData );

/**
 * Retrieves the currently installed signaling callback.
 *
 * The following code sample shows how to use this function:
 * @code
 * #include <gaapi/pvMetaData.h>
 * #include <gaapi/misc.h>
 *
 * //Retrieves the currently installed signaling callback and prints
 * //the information on stdout.
 * //
 * // @pre          The specific PV must have ALL meta functionalities
 * //               available for access. In addition signaling is already
 * //               active for the PV.
 * //
 * // @param[in]    pv    The PV of interest. Already opened via ga_pv_open.
 * void sample( ga_ConstPV pv )
 * {
 *     gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 *     ga_SignalCallback sigCallback = 0;
 *     void* userData = 0;
 *
 *     //(1) Get the handler.
 *     returnValue = ga_pv_getSigCallback( pv, &sigCallback, &userData );
 *     if( gc_ERROR_SUCCESS.errorID != returnValue )
 *     {
 *         fprintf( stderr, "Call to ga_pv_getSigCallback() failed.\n" );
 *         fprintf( stderr, "Error ID=%d\n", returnValue );
 *         fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *         exit( -1 );
 *     }
 *
 *     printf( "Currently installed is handler '0x%p' with userData '0x%p'\n ",
 *             sigCallback, userData );
 * }
 *
 * @endcode
 *
 * @note    This function does only work for PVs of #ga_PVType
 *          #ga_PV_TYPE_SINGLE_VALUE!
 *
 * @param[in]   pv          The PV of interest.
 * @param[out]  callback    Will contain the address of the registered callback.
 *                          If none was registered it will be 0.
 * @param[out]  userData    Will contain the address of the user data.
 *                          If none was registered it will be 0.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_getSigCallback( const ga_ConstPV pv,
                      ga_SignalCallback* const callback,
                      void** const userData );

/**
 * Sets/resets the global signaling callback. This callback will be used as default
 * for every signaled PV, if it does not have installed a individual signaling
 * handler via #ga_pv_changeSigCallback.
 *
 * The following code sample shows how to use this function:
 * @code
 * #include <gaapi/pvMetaData.h>
 * #include <gaapi/misc.h>
 *
 * //Specifies the 'real' userData as will be passed to the signaling callback.
 * typedef struct UserData
 * {
 *     char data[100];
 *     int i;
 *     //etc.
 * } UserData;
 *
 * ///The signaling callback to register.
 * ///The operating system must support printf in an asynchronous singal handler
 * ///context.
 * void gc_CALLCONV globalCallback( ga_PV pv,
 *                                  void* userData )
 * {
 *     //Cast the userData to the real type
 *     UserData* ud = (UserData*)userData;
 *
 *     //Use the user data...
 *
 *     //Print the current PV onto stdout.
 *     gc_ErrorID returnValue = ga_fprintPV( stdout, pv, 0 );
 *     if( gc_ERROR_SUCCESS.errorID != returnValue )
 *     {
 *         fprintf( stderr, "Call to ga_fprintPV() failed.\n" );
 *         fprintf( stderr, "Error ID=%d\n", returnValue );
 *         fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *         exit( -1 );
 *     }
 * }
 *
 * //
 * // Sample function to set and clear the global signaling callback.
 * //
 * // @param[in]    userData    The user data to associate with the global callback.
 * void sample( ga_PV pv,
 *              void* userData )
 * {
 *     gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 *
 *     //(1a) Set the global signal handler.
 *     returnValue = ga_changeGlobalSigCallback( &globalCallback, userData );
 *     if( gc_ERROR_SUCCESS.errorID != returnValue )
 *     {
 *         fprintf( stderr, "Call to ga_changeGlobalSigCallback() failed.\n" );
 *         fprintf( stderr, "Error ID=%d\n", returnValue );
 *         fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *         exit( -1 );
 *     }
 *
 *     // (1b) Activate Signaling for the PV
 *     ga_pv_changeMetaFunctions( pv,
 *                                gc_META_FLAG_SIG_ON_SYNC_CHANGE |
 *                                gc_META_FLAG_SIG_ON_PRIORITY_MIDDLE );
 *
 *     //The handler was successfully registered and the PV's signaling is
 *     //activated. Now whenever a signal will be sent the user-specified
 *     //handler will be called. The global signal handler is temporarily
 *     //disabled while the user-specified signal handler is set.
 *
 *     //(2) Clear the PV and trigger PV's signal handler, once.
 *     gc_NumericValue value;
 *     value.uint64 = 0;
 *     returnValue = ga_pv_putPVField( pv, &value, gc_DATA_OBJECT_FIELD_VALUE );
 *     if( gc_ERROR_SUCCESS.errorID != returnValue )
 *     {
 *         fprintf( stderr, "Call to ga_pv_putPVField() failed.\n" );
 *         fprintf( stderr, "Error ID=%d\n", returnValue );
 *         fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *         exit( -1 );
 *     }
 *     usleep( 20 * 1000L ); // sleep for 20ms, to allow signal handler  to interact
 *
 *
 *     //(3a) Reset The Signaling in the MetaFunctions of PV
 *     returnValue =ga_pv_changeMetaFunctions( pv, gc_META_FLAG_SIG_OFF );
 *     if( gc_ERROR_SUCCESS.errorID != returnValue )
 *     {
 *         fprintf( stderr, "Call to ga_pv_changeMetaFunctions() failed.\n" );
 *         fprintf( stderr, "Error ID=%d\n", returnValue );
 *         fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *         exit( -1 );
 *     }
 *
 *      //(3b) Finally reset the handler. (will reactivate the global handler)
 *      returnValue = ga_changeGlobalSigCallback( 0, 0 );
 *      if( gc_ERROR_SUCCESS.errorID != returnValue )
 *      {
 *          fprintf( stderr, "Call to ga_changeGlobalSigCallback() failed.\n" );
 *          fprintf( stderr, "Error ID=%d\n", returnValue );
 *          fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *          exit( -1 );
 *      }
 * }
 * @endcode
 *
 * @note    The ga_PV given to this callback is always the one of the PV object
 *          used to change the metafunctionality of signaling to on. However,
 *          signaling is a property of the ga_PV handle and NOT of the referenced
 *          PV. Therefore, the callbacks (global oder specific ones) are always
 *          set in reference to the ga_PV handles, which were used to activate
 *          signaling.
 *
 * @note    The code of the callback will be run within the a signal
 *          handler context of the operating system. Therefore the operations
 *          within the callback underly the same restrictions.
 *
 * @note    This function does only affects PVs of #ga_PVType
 *          #ga_PV_TYPE_SINGLE_VALUE!
 *
 * @param[in]   callback    Pointer to the callback function. If 0 the callback
 *                          will be disabled.
 * @param[in]   userData    Pointer to user data for the callback function.
 *                          The user data will be set always. No matter of
 *                          the value of callback.
 *
 * @return   #gc_ERROR_SUCCESS \n
 *           \n
 *           #gc_ERROR_COM_INTERNAL_ERROR \n
 *           \n
 *           #gc_ERROR_ATTACH_MISSING
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_changeGlobalSigCallback( ga_SignalCallback callback,
                            void* userData );

/**
 * Retrieves the currently installed global signaling callback.
 *
 * The following code sample shows how to use this function:
 * @code
 * #include <gaapi/pvMetaData.h>
 * #include <gaapi/misc.h>
 *
 * //Retrieves the currently installed signaling callback and prints
 * //the information on stdout.
 * void sample( void )
 * {
 *     gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 *     ga_SignalCallback sigCallback = 0;
 *     void* userData = 0;
 *
 *     //(1) Get the global Handler.
 *     returnValue = ga_pv_getGlobalCallback( &sigCallback, &userData );
 *     if( gc_ERROR_SUCCESS.errorID != returnValue )
 *     {
 *         fprintf( stderr, "Call to ga_pv_getGlobalCallback() failed.\n" );
 *         fprintf( stderr, "Error ID=%d\n", returnValue );
 *         fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *         exit( -1 );
 *     }
 *
 *     printf( "Currently installed is handler '0x%p' with userData '0x%p'\n ",
 *             sigCallback, userData );
 * }
 *
 * @endcode
 *
 * @param[out]  callback    Will contain the address of the registered callback.
 *                          If none was registered it will be 0.
 * @param[out]  userData    Will contain the address of the user data.
 *                          If none was registered it will be 0.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_getGlobalCallback( ga_SignalCallback* const callback,
                         void** const userData );

#endif /* PVMETADATA_H_ */
