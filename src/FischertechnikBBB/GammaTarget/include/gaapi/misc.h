#ifndef GAMMA_API_MISC_H__
#define GAMMA_API_MISC_H__

/**
 * @file
 *
 * Contains miscellaneous functions, to ease usage of the API. For example the
 * ga_printDataValue, ga_printPVState, etc. functions allows to easily create
 * a textual representation of the API data types (gc_NumericValue, ga_PV, etc.).
 *
 * The following itemization gives an overview:
 *  - Textual output of often used data types.
 *  - Convenience functions for put/get.
 *
 *
 * @author  Copyright RST Industrie Automation GmbH
 */
/******************************************************************************
 * Header File Includes
 ******************************************************************************/
#include <gacommon/errorCodes.h>
#include <gaapi/platformDependencies.h>
#include <gaapi/dataTypes.h>

#include <stdio.h>


/******************************************************************************
 * GAAPI Library Informations
 ******************************************************************************/
/**
 * Retrieves the version of the GAAPI library.
 *
 * The following code sample shows how to retrieve the GAAPI version information:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * ga_VersionNumber versionNumer = { 0, 0, 0, 0 };
 *
 * //(1) Get the version number.
 * returnValue = ga_getVersion( &versionNumber );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to ga_getVersion() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //(2) Write it onto stdout.
 * printf( "GAAPI version: %u.%u.%u.%u\n", versionNumber.major,
 *                                         versionNumber.minor,
 *                                         versionNumber.release
 *                                         versionNumber.build );
 *
 * @endcode
 *
 * @param[out]  versionNumber   Will contain the version number;
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_getVersion( gc_VersionNumber* const versionNumber );


/******************************************************************************
 * Miscellaneous Function Declarations
 ******************************************************************************/
/**
 * Waits on the PV state to change to state.
 *
 * E.g. this can be used to wait on a asynchronous (non-blocking) PV to have it's
 * value synchronized by the service with a remote system.
 *
 * @note    A state change can only be registered when an asynchronous
 *          (non-blocking ga_pv_getValue/ga_pv_putValue) access has occurred. If
 *          a blocking ga_pv_putPVField access has occurred the state will <b>not</b>
 *          change to ga_DATA_OBJECT_STATE_PENDING. Therefore only use this function
 *          to 'synchronize' with asynchronous (non-blocking) access!
 *
 * @param[in]   pv          PV of interest.
 * @param[in]   state       Desired final state.
 * @param[in]   timeoutMS   Overall timeout to wait.
 * @param[in]   intervalMS  Interval timeout. Must be bellow timeoutMS.
 * @param[out]  isOK        Has the state changed to the given one?
 *                          0:    false
 *                          !=0:  true
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_INTERNAL_ERROR
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_waitOnState( ga_ConstPV pv,
                   const ga_PVState state,
                   uint32_t timeoutMS,
                   uint32_t intervalMS,
                   bool* const isOK );


/******************************************************************************
 * Easy Print Function Declarations
 ******************************************************************************/
/**
 * Converts the given ga_PVState into a textual representation.
 *
 * @param[in]   state       To be converted. If it's not a valid one
 *                          #gc_ERROR_COM_INVALID_ARGUMENT will be returned
 *                          and dest will not be changed.
 * @param[out]  dest        Will contain the textual representation. Do NOT
 *                          free(...) this string. Internally it's a static
 *                          const string!
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_printPVState( const ga_PVState state,
                 const char** dest );


/**
 * Converts the given ga_PVLocation into a textual representation.
 *
 * @param[in]   location    To be converted. If it's not a valid one
 *                          #gc_ERROR_COM_INVALID_ARGUMENT will be returned
 *                          and dest will not be changed.
 * @param[out]  dest        Will contain the textual representation. Do NOT
 *                          free(...) this string. Internally it's a static
 *                          const string!
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_printPVLocation( const ga_PVLocation location,
                    const char** dest );

/**
 * Converts the given ga_PVType into a textual representation.
 *
 * @param[in]   type        To be converted. If it's not a valid one
 *                          #gc_ERROR_COM_INVALID_ARGUMENT will be returned
 *                          and dest will not be changed.
 * @param[out]  dest        Will contain the textual representation. Do NOT
 *                          free(...) this string. Internally it's a static
 *                          const string!
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_PVType_print( const ga_PVType type,
                 const char** dest );


/**
 * Converts the given ga_PVProperty into a textual representation.
 *
 * @param[in]   property    To be converted. If it's not a valid one
 *                          #gc_ERROR_COM_INVALID_ARGUMENT will be returned
 *                          and dest will not be changed.
 * @param[out]  dest        Will contain the textual representation. Do NOT
 *                          free(...) this string. Internally it's a static
 *                          const string!
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_printPVProperty( const ga_PVProperty property,
                    const char** dest );


/**
 * Converts the given PV properties 32 Bit value into a textual representation.
 * This only works, for valid combinations! For all other combinations an
 * gc_ERROR_COM_INVALID_ARGUMENT error will be returned.
 *
 * The len parameter specifies the real type of dest. The following table
 * gives an overview:
 * <pre>
 * len value:           dest type:      description:
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
 * </pre>
 *
 * @note:   This function does NOT sanitize the properties, because it does not
 *          know if the properties are for a FIFO or SingleValue PV! Therefore
 *          if a property group (access, lookup, etc) is not set it'll simple
 *          not bet printed!
 *
 *
 * @param[in]       pvProperties    Or'ed ga_PVProperty 32 Bit value.
 * @param[in]       indentation     Additional indentation parameter. If 0 none
 *                                  will be used.
 * @param[in,out]   dest            Points to either a user-provided array or a
 *                                  char* to store the internally malloc'ed array.
 * @param[in]       len             The available length of the buffer. It'll be
 *                                  always counted without the trailing 0 character.
 *                                  If len is 0 the dest argument will be interpreted
 *                                  as type 'char**'.
 *                                  If len is not 0 the dest argument will be
 *                                  interpreted as type 'char*'.
 *                                  For more information see above table.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_STRING_TRUNCATED \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          #gc_ERROR_COM_MALLOC_FAILED \n
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_printPVProperties( gc_Flags32Bit pvProperties,
                      const char* indentation,
                      void* dest,
                      size_t len );

/**
 * Utility function to print the PV data model property name and value.
 *
 * The purpose of this function is to provide a unified interface for printing
 * multiple data tuples. In case the layout might change only this function
 * will be changed, but the callers don't need to change their code.
 *
 * The len parameter specifies the real type of dest. The following table
 * gives an overview:
 * <pre>
 * len value:           dest type:      description:
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
 * </pre>
 *
 * @param[in]       propertyName    The name of the property.
 * @param[in]       propertValue    The value of the property.
 * @param[in]       indentation     Additional indentation parameter. If 0 none
 *                                  will be used.
 * @param[in,out]   dest            Points to either a user-provided array or a
 *                                  char* to store the internally malloc'ed array.
 * @param[in]       len             The available length of the buffer. It'll be
 *                                  always counted without the trailing 0 character.
 *                                  If len is 0 the dest argument will be interpreted
 *                                  as type 'char**'.
 *                                  If len is not 0 the dest argument will be
 *                                  interpreted as type 'char*'.
 *                                  For more information see above table.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_STRING_TRUNCATED \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          #gc_ERROR_COM_MALLOC_FAILED \n
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_printPVDataModelProperty( const char* const  propertyName,
                             const gc_Value* const propertValue,
                             const char* indentation,
                             void* dest,
                             size_t len );

/**
 * Utility function to printing multiple PV data model property tuples.
 *
 * This function is intended as an extension for querying the properties via
 * #ga_pv_getDataModelPropertyNames and #ga_pv_getDataModelProperty.
 * After a call to #ga_pv_getDataModelPropertyNames/#ga_pv_getDataModelProperty
 * and the name/value tuples have been created,
 * calling #ga_printPVDataModelProperties will produce a ready to print output
 * of tuples.
 *
 * The len parameter specifies the real type of dest. The following table
 * gives an overview:
 * <pre>
 * len value:           dest type:      description:
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
 * </pre>
 *
 * @param[in]       propertyCount   The number of property tuples.
 *                                  IMPORTANT: The length of propertyNames and
 *                                  propertValues must match!
 * @param[in]       propertyNames   Points to the array of property names.
 * @param[in]       propertValues   Points to the array of property values.
 * @param[in]       indentation     Additional indentation parameter. If 0 none
 *                                  will be used.
 * @param[in,out]   dest            Points to either a user-provided array or a
 *                                  char* to store the internally malloc'ed array.
 * @param[in]       len             The available length of the buffer. It'll be
 *                                  always counted without the trailing 0 character.
 *                                  If len is 0 the dest argument will be interpreted
 *                                  as type 'char**'.
 *                                  If len is not 0 the dest argument will be
 *                                  interpreted as type 'char*'.
 *                                  For more information see above table.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_STRING_TRUNCATED \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          #gc_ERROR_COM_MALLOC_FAILED \n
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_printPVDataModelProperties( const size_t propertyCount,
                               const char* const * const propertyNames,
                               const gc_Value* const propertValues,
                               const char* indentation,
                               void* dest,
                               size_t len );

/**
 * Converts the given meta flags 32 Bit value into a textual representation.
 * This only works, for valid combinations! For all other combinations an
 * #gc_ERROR_COM_INVALID_ARGUMENT error will be returned.
 *
 * The len parameter specifies the real type of dest. The following table
 * gives an overview:
 *  * <pre>
 * len value:           dest type:      description:
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
 * @param[in]       metaFlags       Or'ed gc_MetaFlag 32 Bit value.
 * @param[in]       indentation     Additional indentation parameter. If 0 none
 *                                  will be used.
 * @param[in,out]   dest            Points to either a user-provided array or a
 *                                  char* to store the internally malloc'ed array.
 * @param[in]       len             The available length of the buffer. It'll be
 *                                  always counted without the trailing 0 character.
 *                                  If len is 0 the dest argument will be interpreted
 *                                  as type 'char**'.
 *                                  If len is not 0 the dest argument will be
 *                                  interpreted as type 'char*'.
 *                                  For more information see above table.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_STRING_TRUNCATED \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          #gc_ERROR_COM_MALLOC_FAILED \n
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_printMetaFlags( const gc_Flags32Bit metaFlags,
                   const char* indentation,
                   void* dest,
                   size_t len );

/**
 * Converts the given ga_MetaConfig into a textual representation.
 *
 * If the flags field of the #ga_MetaConfig parameter does not contain
 * a valid flag the function will fail. A flag field is not considered
 * valid if the state is invalid (see #ga_MetaConfig and #gc_MetaFlag).
 *
 * The len parameter specifies the real type of dest. The following table
 * gives an overview:
 *  * <pre>
 * len value:           dest type:      description:
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
 * The output of a ga_MetaConfig variable will look like:
 * <pre>
 * state: okay
 * location: local
 * property: blocking access
 * metaFlags
 *     log: not available
 *     sim: off
 *     min: on (reject)
 *     max: on (reject)
 *     sig: on (sync, change)
 *     sig: priority high
 * </pre>
 *
 * @param[in]       config          To be converted.
 *                                  If the config was created via ga_pv_getMetaConfig
 *                                  and the RPC parameter to false the call will
 *                                  fail with gc_ERROR_COM_INVALID_ARGUMENT!
 * @param[in]       indentation     Additional indentation parameter. If 0 none
 *                                  will be used.
 * @param[in,out]   dest            Points to either a user-provided array or a
 *                                  char* to store the internally malloc'ed array.
 * @param[in]       len             The available length of the buffer. It'll be
 *                                  always counted without the trailing 0 character.
 *                                  If len is 0 the dest argument will be interpreted
 *                                  as type 'char**'.
 *                                  If len is not 0 the dest argument will be
 *                                  interpreted as type 'char*'.
 *                                  For more information see above table.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_STRING_TRUNCATED \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          #gc_ERROR_COM_MALLOC_FAILED \n
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_printMetaConfig( const ga_MetaConfig* const config,
                    const char* indentation,
                    void* dest,
                    size_t len );

/**
 * Prints all information of the PV into the given destination.
 *
 * To provide enough flexibility the destination has a type of void* and the
 * real type is defined by the value of the len argument. The following table
 * gives an overview:
 * <pre>
 * len value:           dest type:      description:
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
 * The output of a PV variable will look like:
 * <pre>
 * PVAddress: 'x1'
 * ConformPVAddress: 'SystemX:x1'
 * DataType: UINT32
 * Value: '1'
 * MetaConfig: state=okay
 *     location: local
 *     property: blocking access
 *     metaFlags
 *         log: not available
 *         sim: off
 *         min: on (reject)
 *         max" on (reject)
 *         sig: on (sync, change)
 *         sig: priority high
 *
 * </pre>
 *
 * Sample:
 * Input: ga_printPV( pv, buffer, sizeof(buffer) );<br>
 * buffer =<br>

 *
 * @note    If this function has internally malloced memory to store the
 *          textual representation than #gc_freeMemory must be used and not free.
 *
 * @param[in]       pv              The PV to print into dest.
 * @param[in]       indentation     Additional indentation parameter. If 0 none
 *                                  will be used.
 * @param[in,out]   dest            The real type of the pointer depends on the
 *                                  len argument! See above table.
 * @param[in]       len             The available length of the buffer. It'll be
 *                                  always counted without the trailing 0 character.
 *                                  If len is 0 the dest argument will be interpreted
 *                                  as type 'char**'.
 *                                  If len is not 0 the dest argument will be
 *                                  interpreted as type 'char*'.
 *                                  For more information see above table.
 *
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_STRING_TRUNCATED \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          #gc_ERROR_COM_MALLOC_FAILED \n
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_printPV( ga_ConstPV pv,
            const char* indentation,
            void* dest,
            size_t len );

/**
 * Same as #ga_printPV, but writes into a file stream. This can be either
 * a user-opened file or one of the C standard files stream 'stdout', ...
 *
 * @param[in]   f               Destination file stream.
 * @param[in]   pv              PV to write. This will cause access to some GAAPI
 *                              functions to retrieve the value, meta config, etc.!
 * @param[in]   indentation     Additional indentation parameter. If 0 none
 *                              will be used.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_STRING_TRUNCATED \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          #gc_ERROR_COM_MALLOC_FAILED \n
 *          #gc_ERROR_COM_IO_ERROR
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_fprintPV( FILE* const f,
             const ga_ConstPV pv,
             const char* indentation );



/******************************************************************************
 * PV Access Convenience Function
 ******************************************************************************/
/**
 * Convenience (not performance!) function for writing a double value to the PV.
 *
 * The data type of the PV will be handled internally to validate the write
 * access for:
 *  - The conversion is possible. E.g. #gc_DATA_TYPE_IEEE_64 to #gc_DATA_TYPE_BLOB
 *    is not possible. Therefore in such cases the function will return
 *    gc_ERROR_COM_INVALID_ARGUMENT.
 *  - The range of the actual PV data type can not hold the user-provided value.
 *    E.g it's not possible to write the value 99999 into a PV, which is of data
 *    type #gc_DATA_TYPE_SINT_8. In this case the function will return
 *    gc_ERROR_COM_VALUE_TRUNCATION.
 *
 * The advantage of this function compared to ga_pv_putValue is:
 *  - Ease of access
 *    - no data type required
 *    - internal handling of conversions
 *
 * The drawbacks of this function compared to ga_pv_putValue is:
 *  - performance penalty
 *    - read of real data type
 *    - conversion (including truncation checks)
 *
 * @param[in]   pv                  The PV of interest.
 * @param[in]   value               The value to write.
 * @param[in]   checkTruncation     0: Ignore conversion errors and don't return
 *                                  gc_ERROR_PV_DATATYPE_CONVERTION_FAILED in
 *                                  case of information loss.
 *                                  !=0: Check for conversion errors and do
 *                                  return gc_ERROR_PV_DATATYPE_CONVERTION_FAILED
 *                                  in case of information loss.
 *
 * @return #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT  \n
 *          #gc_ERROR_COM_VALUE_TRUNCATION \n
 *          \n
 *          #gc_ERROR_ATTACH_MISSING \n
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_putIEEE64( const ga_PV pv,
                 const double value,
                 const bool checkTruncation );

/**
 * Same as ga_pv_putIEEE64 but for get operation.
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_getIEEE64( const ga_ConstPV pv,
                 double* const value,
                 const bool checkTruncation );

/**
 * Same as ga_pv_putIEEE64 but for uint64_t.
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_putUINT64( const ga_PV pv,
                 const uint64_t value,
                 const bool checkTruncation );

/**
 * Same as ga_pv_getIEEE64 but for uint64_t.
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_getUINT64( const ga_ConstPV pv,
                 uint64_t* const value,
                 const bool checkTruncation );

/**
 * Same as ga_pv_putIEEE64 but for int64_t.
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_putSINT64( const ga_PV pv,
                 const int64_t value,
                 const bool checkTruncation );

/**
 * Same as ga_pv_getIEEE64 but for int64_t.
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_pv_getSINT64( const ga_ConstPV pv,
                 int64_t* const value,
                 const bool checkTruncation );


/******************************************************************************
 * Comparison Function Declaration
 ******************************************************************************/
/**
 * Performs a numeric C style comparison of a and b.
 *
 * @param[in]   a           Used as: a compared to b. Not allowed to be 0.
 * @param[in]   b           Used as  a compared to b. Not allowed to be 0.
 * @param[in]   result      This parameter is not allowed to be 0.\n
 *                          <0: a < b \n
 *                          0: a == b \n
 *                          >0: a > b
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT
 */
ga_EXP gc_ErrorID gc_CALLCONV
ga_MetaConfig_compare( const ga_MetaConfig* const a,
                       const ga_MetaConfig* const b,
                       int* const result );


#endif /* GAMMA_API_MISC_H__ */
