#ifndef GAMMA_COMMON_MISC_H__
  #define GAMMA_COMMON_MISC_H__

/**
 * @file
 *
 * Contains miscellaneous functions, to ease usage of the API. For example the
 * print X functions allows to easily create a textual representation of the
 * API data types.
 *
 * The following itemization gives an overview:
 *  - Textual output of often used data types.
 *  - Conversion from double/uint64/sint64 to gc_NumericValue vice versa.
 *  - Convenience functions for put/get.
 *
 *
 * @author  Copyright RST Industrie Automation GmbH
 */
/******************************************************************************
 * Header File Includes
 ******************************************************************************/
#include <gacommon/errorCodes.h>
#include <gacommon/platformDependencies.h>
#include <gacommon/dataTypes.h>


/******************************************************************************
 * GACOMMON Library Informations
 ******************************************************************************/
/**
 * Retrieves the version of the GACOMMON library.
 *
 * The following code sample shows how to retrieve the GACOMMON version information:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gc_VersionNumber versionNumer = { 0, 0, 0, 0 };
 *
 * //(1) Get the version number.
 * returnValue = gc_getVersion( &versionNumber );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gc_getVersion() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //(2) Write it onto stdout.
 * printf( "GACOMMON version: %u.%u.%u.%u\n", versionNumber.major,
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
gc_EXP gc_ErrorID gc_CALLCONV
gc_getVersion( gc_VersionNumber* const versionNumber );


/******************************************************************************
 * Miscellaneous Function Declarations
 ******************************************************************************/
/**
 * Frees all Library-malloc()ed memory.
 *
 * Whenever a GAmma library will malloc memory for the user this function must
 * be used to free the memory. Don't use free(), because on some platforms
 * every DLL has it's own heap and therefore calling free in the wrong context
 * will lead to memory corruption.
 *
 * @param[in]   memory  The memory to be freeed.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_freeMemory( void* memory );

/**
 * Triggers the execution of an action and returns <b>after</b> the service has
 * processed all actions, associated with it.
 *
 * This functionality is a light-weight mechanism for synchronizing the data
 * model with the application logic, without using e.g. the complete GASCHED
 * library.
 *
 * The following example (using GAAPI library) gives a use case for this function:
 * @code
 * //This sample uses a non-blocking local PV
 * ga_PV pv;                    //Set-up previously
 * gc_NumericValue value0;         //Contains the value0 to put.
 * gc_NumericValue value1;         //Contains the value1 to put.
 *
 * void loseInformation( void )
 * {
 *     ga_pv_putValue( &pv, &value0 );
 *     //After the value has been written into the data model the service might
 *     //still have 'cached' information (e.g. signaling), which are not up-to-date
 *     //with the current value of the PV. Therefore if another 'fast enough' put
 *     //occurs e.g. a signal might get lost (hint: signaling runs in a loop).
 *
 *     ga_pv_putValue( &pv, &value1 );
 *     //At this point it could have happened that value0 was never detected by
 *     //the service's processing cycle. Therefore, to set-up determined start values
 *     //etc. the user-application should either use a full GASCHED implementation
 *     //or, if sufficient, explicitly calls ga_triggerAction to trigger the
 *     //loop of the service.
 * }
 *
 * void preserveInformation( void )
 * {
 *     ga_pv_putValue( &pv, &value0 );
 *
 *     //Explicitly issue a RPC to the service for processing all routines,
 *     //associated with the given action.
 *     ga_triggerAction( ":LocalAction1" );
 *
 *     ga_pv_putValue( &pv, &value1 );
 * }
 * @endcode
 *
 * The following sample shows how the trigger interacts with the internal cycles
 * of the Gamma Service. In addition is explains why two ga_triggerAction calls
 * are require to ensure that all values are up to date.
 * <pre>
 *
 *
 * local system:                         |                  remote system:
 * ---------------------------------- cycle N ----------------------------------
 * 1) issue 1st trigger request       -------->       starts updating of values
 *                                       |
 * The ga_triggerAction call will return at this point!
 * Therefore the values might not be updated!
 *                                       |
 * 2) receive remote changes          <-------
 *                                       |
 * 3) transmit local changes          -------->
 *                                       |
 * ---------------------------------- cycle N ----------------------------------
 * 4) issue 2nd trigger request       -------->       starts updating of values
 *                                       |
 * Now when the call of ga_triggerAction returns it's
 * safe to assume that the values in the data model are all
 * at least the ones of cycle N. If it's now an issue that
 * some values form a logical set please use a lock to avoid
 * issues with interleaving values.
 *                                       |
 * 5) receive remote changes          <-------
 *                                       |
 * 6) transmit local changes          -------->
 *                                       |
 * </pre>
 *
 * @note    This function will issue at least one RPC to the service and will
 *          return only after the requested action and its associated processing
 *          routines (e.g. update of the complete data model) has been finished.
 *
 * @param[in]   actionName      The fully qualified (scoped) name of the
 *                              action. Valid names are ":Action!" or
 *                              "RemoteSystem:Action1".
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_triggerAction( const char* const actionName );



/**
 * Same as #gc_triggerAction but with the numerical address of the action.
 *
 * @param[in]   actionAddress   The numerical address of the action to trigger.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_triggerActionByAdress( const gc_Level2Address* actionAddress );


/******************************************************************************
 * Easy Print Function Declarations
 ******************************************************************************/
/**
 * Converts the given gc_DataType into a textual representation.
 *
 * @param[in]   dataType    The data type to convert. If it's not a valid one
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
gc_EXP gc_ErrorID gc_CALLCONV
gc_DataType_print( const gc_DataType dataType,
                   const char** dest );

/**
 * Converts the given gc_MetaFlags into a textual representation.
 *
 * @param[in]   metaFlag    To be converted. If it's not a valid one
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
gc_EXP gc_ErrorID gc_CALLCONV
gc_MetaFlag_print( const gc_MetaFlag metaFlag,
                   const char** const dest );

/**
 * Converts the given gc_MetaType into a textual representation.
 *
 * @param[in]   metaType    To be converted. If it's not a valid one
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
gc_EXP gc_ErrorID gc_CALLCONV
gc_MetaType_print( const gc_MetaType metaType,
                   const char** const dest );

/**
 * Converts the given gc_PVFieldType into a textual representation.
 *
 * @param[in]   fieldType   To be converted. If it's not a valid one
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
gc_EXP gc_ErrorID gc_CALLCONV
gc_DataObjectFieldType_print( const gc_PVFieldType fieldType,
                              const char** const dest );

/**
 * Deprecated. Please use gc_DataObjectFieldType_print.
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_PVFieldType_print( const gc_PVFieldType fieldType,
                      const char** const dest ) gc_DEPRECATED;

/**
 * Prints the content of a "BLOB" or any memory location pointed to by src
 * until srcLen in hex.
 *
 * To provide enough flexibility the destination has a type of void* and the
 * real type is defined by the value of the len argument. The following table
 * gives an overview:
 * <pre>
 * detLen value:        dest type:      description:
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
 * Sample Output:
 * <pre>
 * Address  |  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F | Dump
 * -----------------------------------------------------------------------------
 * 00000000 | 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 30 | 0000000000000000
 * *
 * 00000030 | 31 31 31 31 31 31 31 31 31 31 31 31 31 31 31 31 | 1111111111111111
 * 00000040 | 32 32 32 32 32 32 32 32 32 32 32 32 32 32 32 32 | 2222222222222222
 * 00000050 | 33 33 33                                        | 333
 *
 * </pre>
 * A '*' in a line tells that the following line(s) are the same as the above
 * one. The '*' does only appear in between the 2nd and next to last line.
 *
 * @param[in]       src             Source to print.
 * @param[in]       srcLen          Length of source to print
 * @param[in,out]   dest            The real type of the pointer depends on the
 *                                  len argument! See above table.
 * @param[in]       destLen         The available length of the buffer. It'll be
 *                                  always counted without the trailing 0 character.
 *                                  If len is 0 the dest argument will be interpreted
 *                                  as type 'char**'.
 *                                  If len is not 0 the dest argument will be
 *                                  interpreted as type 'char*'.
 *                                  For more information see above table.
 * @param[in]       indentation     Additional indentation parameter. If 0 none
 *                                  will be used.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_STRING_TRUNCATED \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          #gc_ERROR_COM_MALLOC_FAILED \n
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_printHex( const void* const src,
             const size_t srcLen,
             void* dest,
             size_t destLen,
             const char* indentation );

/**
 * Converts the given data value, depending on the given data type into a
 * textual representation.
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
 *
 * </pre>
 *
 * @param[in]       dataType    Numeric data type for the interpretation of value.
 * @param[in]       value       The value to 'print' into the dest.
 * @param[in,out]   dest        Points to either a user-provided array or a
 *                              char* to store the internally malloc'ed array.
 * @param[in]       len         The available length of the buffer. It'll be always
 *                              counted without the trailing 0 character.
 *                              If len is 0 the dest argument will be interpreted
 *                              as type 'char**'.
 *                              If len is not 0 the dest argument will be interpreted
 *                              as type 'char*'.
 *                              For more information see above table.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_STRING_TRUNCATED \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          #gc_ERROR_COM_MALLOC_FAILED \n
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_NumericValue_print( const gc_DataType dataType,
                       const gc_NumericValue* const value,
                       void* dest,
                       size_t len );



/**
 * Converts the given gc_Level2Address instance into a textual representation.
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
 *
 * </pre>
 *
 * @param[in]       level2Address   The level2Address to convert.
 * @param[in,out]   dest            Points to either a user-provided array or a
 *                                  char* to store the internally malloc'ed array.
 * @param[in]       len             The available length of the buffer. It'll be
 *                                  always counted without the trailing 0 character.
 *                                  If len is 0 the dest argument will be interpreted
 *                                  as type 'char**'.
 *                                  If len is not 0 the dest argument will be interpreted
 *                                  as type 'char*'.
 *                                  For more information see above table.
 * @param[in]       indentation     Additional indentation parameter (only for
 *                                  Blob). If 0 none will be used.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_STRING_TRUNCATED \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          #gc_ERROR_COM_MALLOC_FAILED \n
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_Level2Address_print( const gc_Level2Address* const level2Address,
                        const char* indentation,
                        void* dest,
                        size_t len );

gc_EXP gc_ErrorID gc_CALLCONV
gc_Level3Address_print( const gc_Level3Address* const level3Address,
                        const char* indentation,
                        void* dest,
                        size_t len );

gc_EXP gc_ErrorID gc_CALLCONV
gc_Level4Address_print( const gc_Level4Address* const level4Address,
                        const char* indentation,
                        void* dest,
                        size_t len );

gc_EXP gc_ErrorID gc_CALLCONV
gc_Level5Address_print( const gc_Level5Address* const level5Address,
                        const char* indentation,
                        void* dest,
                        size_t len );

gc_EXP gc_ErrorID gc_CALLCONV
gc_Level6Address_print( const gc_Level6Address* const level6Address,
                        const char* indentation,
                        void* dest,
                        size_t len );

/******************************************************************************
 * Conversion Function Declarations
 ******************************************************************************/
/**
 * Converts a data value to a IEEE64 floating point number depending on
 * the specified type. In addition if checkTruncation is set the function will
 * abort if the value can not be represented by the given data type. Otherwise
 * the C conversion semantics will be used.
 *
 * The range check also validates, that the new value is fully representable
 * tye a IEEE64 floating point.
 *
 * @param[in]   type                Data type of the dest.
 * @param[in]   src                 Source value to convert.
 * @param[out]  dest                Will contain the converted value.
 * @param[out]  checkTruncation     0: Don't check for truncation.
 *                                  1: Check for truncation.
 *
 * @return #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT  \n
 *          \n
 *          #gc_ERROR_COM_VALUE_TRUNCATION \n
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_NumericValue_convertToIEEE64( const gc_DataType type,
                                 const gc_NumericValue* const src,
                                 double* const dest,
                                 const bool checkTruncation );

/**
 * Converts a IEEE64 bit floating point number to a gc_NumericValue depending on
 * the specified type. In addition if checkTruncation is set the function will
 * abort if the value can not be represented by the given data type. Otherwise
 * the C conversion semantics will be used.
 *
 * The range check also validates, that the new value is able to fully represent
 * the IEEE64 floating point source..
 *
 * @param[in]   type                Data type of the dest.
 * @param[in]   src                 Source value to convert.
 * @param[out]  dest                Will contain the converted value.
 * @param[out]  checkTruncation     0: Don't check for truncation.
 *                                  1: Check for truncation.
 *
 * @return #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT  \n
 *          \n
 *          #gc_ERROR_COM_VALUE_TRUNCATION \n
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_NumericValue_convertFromIEEE64( const gc_DataType type,
                                   const double src,
                                   gc_NumericValue* const dest,
                                   const bool checkTruncation );

/**
 * Same as gc_NumericValue_convertToIEEE64 but for uint64_t.
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_NumericValue_convertToUINT64( const gc_DataType type,
                                 const gc_NumericValue* const src,
                                 uint64_t* const dest,
                                 const bool checkTruncation );

/**
 * Same as gc_NumericValue_convertFromIEEE64 but for uint64_t.
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_NumericValue_convertFromUINT64( const gc_DataType type,
                                   const uint64_t src,
                                   gc_NumericValue* const dest,
                                   const bool checkTruncation );

/**
 * Same as gc_NumericValue_convertToIEEE64 but for int64_t.
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_NumericValue_convertToSINT64( const gc_DataType type,
                                 const gc_NumericValue* const src,
                                 int64_t* const dest,
                                 const bool checkTruncation );

/**
 * Same as gc_NumericValue_convertFromIEEE64 but for uint64_t.
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_NumericValue_convertFromSINT64( const gc_DataType type,
                                   const int64_t src,
                                   gc_NumericValue* dest,
                                   const bool checkTruncation );


/******************************************************************************
 * Comparison Function Declaration: Addresses
 ******************************************************************************/
/**
 * Performs a numeric C style comparison of a and b.
 *
 * @param[in]   type        Data type used for comparison. Must be a numeric one.
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
gc_EXP gc_ErrorID gc_CALLCONV
gc_NumericValue_compare( const gc_DataType type,
                         const gc_NumericValue* const a,
                         const gc_NumericValue* const b,
                         int* const result );

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
gc_EXP gc_ErrorID gc_CALLCONV
gc_Level2Address_compare( const gc_Level2Address* const a,
                          const gc_Level2Address* const b,
                          int* const result );

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
gc_EXP gc_ErrorID gc_CALLCONV
gc_Level3Address_compare( const gc_Level3Address* const a,
                          const gc_Level3Address* const b,
                          int* const result );

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
gc_EXP gc_ErrorID gc_CALLCONV
gc_Level4Address_compare( const gc_Level4Address* const a,
                          const gc_Level4Address* const b,
                          int* const result );

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
gc_EXP gc_ErrorID gc_CALLCONV
gc_Level5Address_compare( const gc_Level5Address* const a,
                          const gc_Level5Address* const b,
                          int* const result );

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
gc_EXP gc_ErrorID gc_CALLCONV
gc_Level6Address_compare( const gc_Level6Address* const a,
                          const gc_Level6Address* const b,
                          int* const result );

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
gc_EXP gc_ErrorID gc_CALLCONV
gc_SystemInfo_compare( const gc_SystemInfo* const a,
                       const gc_SystemInfo* const b,
                       int* const result );

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
gc_EXP gc_ErrorID gc_CALLCONV
gc_LoopConfig_compare( const gc_LoopConfig* const a,
                       const gc_LoopConfig* const b,
                       int* const result );

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
gc_EXP gc_ErrorID gc_CALLCONV
gc_LoopInfo_compare( const gc_LoopInfo* const a,
                     const gc_LoopInfo* const b,
                     int* const result );

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
gc_EXP gc_ErrorID gc_CALLCONV
gc_ActionConfig_compare( const gc_ActionConfig* const a,
                         const gc_ActionConfig* const b,
                         int* const result );

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
gc_EXP gc_ErrorID gc_CALLCONV
gc_ActionInfo_compare( const gc_ActionInfo* const a,
                       const gc_ActionInfo* const b,
                       int* const result );

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
gc_EXP gc_ErrorID gc_CALLCONV
gc_NodeConfig_compare( const gc_NodeConfig* const a,
                       const gc_NodeConfig* const b,
                       int* const result );

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
gc_EXP gc_ErrorID gc_CALLCONV
gc_NodeInfo_compare( const gc_NodeInfo* const a,
                     const gc_NodeInfo* const b,
                     int* const result );

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
gc_EXP gc_ErrorID gc_CALLCONV
gc_SHMConfig_compare( const gc_SHMConfig* const a,
                      const gc_SHMConfig* const b,
                      int* const result );

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
gc_EXP gc_ErrorID gc_CALLCONV
gc_MemoryInfo_compare( const gc_MemoryInfo* const a,
                       const gc_MemoryInfo* const b,
                       int* const result );

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
gc_EXP gc_ErrorID gc_CALLCONV
gc_TaskInfo_compare( const gc_TaskInfo* const a,
                     const gc_TaskInfo* const b,
                     int* const result );

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
gc_EXP gc_ErrorID gc_CALLCONV
gc_IOInfo_compare( const gc_IOInfo* const a,
                   const gc_IOInfo* const b,
                   int* const result );

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
gc_EXP gc_ErrorID gc_CALLCONV
gc_IOChannelInfo_compare( const gc_IOChannelInfo* const a,
                          const gc_IOChannelInfo* const b,
                          int* const result );

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
gc_EXP gc_ErrorID gc_CALLCONV
gc_SchedulerInfo_compare( const gc_SchedulerInfo* const a,
                          const gc_SchedulerInfo* const b,
                          int* const result );

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
gc_EXP gc_ErrorID gc_CALLCONV
gc_SchedulerSlotInfo_compare( const gc_SchedulerSlotInfo* const a,
                              const gc_SchedulerSlotInfo* const b,
                              int* const result );

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
gc_EXP gc_ErrorID gc_CALLCONV
gc_GroupConfig_compare( const gc_GroupConfig* const a,
                        const gc_GroupConfig* const b,
                        int* const result );

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
gc_EXP gc_ErrorID gc_CALLCONV
gc_GroupInfo_compare( const gc_GroupInfo* const a,
                      const gc_GroupInfo* const b,
                      int* const result );

/**
 * Performs a numeric C style comparison of a and b.
 *
 * The comparison is not a binary one but a logical one. This means that the
 * value of the maxLen field is <b>not</b> compared. Only curLen and the
 * content will be compared.
 *
 * @param[in]   a           Used as: a compared to b. Not allowed to be 0.
 * @param[in]   b           Used as  a compared to b. Not allowed to be 0.
 * @param[in]   result      This parameter is not allowed to be 0.\n
 *                          <0: a < b \n
 *                          0: a == b \n
 *                          >0: a > b
 *
 *
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_Blob_compare( const gc_Blob* const a,
                 const gc_Blob* const b,
                 int* const result );

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
gc_EXP gc_ErrorID gc_CALLCONV
gc_Value_compare( const gc_Value* const a,
                  const gc_Value* const b,
                  int* const result );

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
gc_EXP gc_ErrorID gc_CALLCONV
gc_PVArrayConfig_compare( const gc_PVArrayConfig* const a,
                          const gc_PVArrayConfig* const b,
                          int* const result );

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
gc_EXP gc_ErrorID gc_CALLCONV
gc_PVArrayInfo_compare( const gc_PVArrayInfo* const a,
                        const gc_PVArrayInfo* const b,
                        int* const result );

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
gc_EXP gc_ErrorID gc_CALLCONV
gc_FifoConfig_compare( const gc_FifoConfig* const a,
                       const gc_FifoConfig* const b,
                       int* const result );

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
gc_EXP gc_ErrorID gc_CALLCONV
gc_FifoInfo_compare( const gc_FifoInfo* const a,
                     const gc_FifoInfo* const b,
                     int* const result );

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
gc_EXP gc_ErrorID gc_CALLCONV
gc_BrowserInfo_compare( const gc_BrowserInfo* const a,
                        const gc_BrowserInfo* const b,
                        int* const result );

/******************************************************************************
 * Helper Functions for: gc_Blob
 ******************************************************************************/
/**
 * Initializes a new blob and stores it's pointer at the given argument.
 *
 * @note    This call will use an <b>internal</b> malloc call to get the resources,
 *          therefore the memory must be freed via gc_Blob_free. Otherwise on
 *          some platforms the heap will be compromised.
 *
 * @param[in,out]   blob        Contains the address of the gc_Blob* where to store
 *                              the newly created BLOB.
 * @param[in]       maxLen      The maximum length of the BLOB.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_MALLOC_FAILED
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_Blob_init( gc_Blob** blob,
              const size_t maxLen );

/**
 * Frees the resources, allocated for the blob.
 *
 * @param[in]   dest    Will be freed and set to 0.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_Blob_free( gc_Blob** dest );

/**
 * The gc_Blob src will be cloned and stored at the given dest. Please be aware,
 * that the dest won't be freed. If dest holds already a blob please free it
 * before the call to this function.
 *
 * @note    This call will use an <b>internal</b> malloc call to get the resources,
 *          therefore the memory must be freed via gc_Blob_free. Otherwise on
 *          some platforms the heap will be compromised.
 *
 * @param[in,out]   dest    The pointer to the gc_Blob* dest.
 * @param[in]       src     The src to clone.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_MALLOC_FAILED
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_Blob_clone( gc_Blob** dest,
               const gc_Blob* src );

/**
 * Reallocs the memory of the blob and sets the max field accordingly.
 *
 * @note    The gc_Blob* functions use internally malloc. On some Operating
 *          Systems (Windows) a heap corruption occurs if not the same lib
 *          realloc as malloced the memory!
 *
 * @param[in,out]   dest        The destination to realloc.
 * @param[in]       maxLen      The new max length. The real size argument
 *                              of the realloc call will the increased by
 *                              the value of sizeof( gc_Blob ). Therefore
 *                              it's not possible to use this function as
 *                              realloc with a size parameter of '0'!
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_MALLOC_FAILED
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_Blob_realloc( gc_Blob** dest,
                 const size_t maxLen );

/**
 * Sets the content of the given BLOB to the given string.
 *
 * @note    This is just a convenience function, because a BLOB does 'know'
 *          the concept of a C string. Therefore copying the content of one
 *          BLOB to another is done by #gc_Blob_setBinary.
 *
 * @param[in,out]   blob        The blob to set.
 * @param[in]       string      The string to write into the blob.
 *                              If the string ist empty ("") then the whole
 *                              content of the Blob will be set to 0.
 * @param[in]       realloc     True:   Reallocs memory of blob if it can not
 *                                      hold the string.
 *                              False:  Writes only part of the string into the
 *                                      blob and reports an truncation error.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT\n
 *          #gc_ERROR_COM_STRING_TRUNCATED
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_Blob_setString( gc_Blob** blob,
                   const char* string,
                   const bool realloc );

/**
 * Creates (malloc) a new C string based on the data of the BLOB object.
 *
 * @param[in]   blob        The blob of interest.
 * @param[out]  dest        Will hold the newly malloced memory with the C string
 *                          content of the blob.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT\n
 *          #gc_ERROR_COM_MALLOC_FAILED
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_Blob_createCString( const gc_Blob* blob,
                       char** dest );

/**
 * Sets the content of the given blob to the binary data of the given source.
 *
 * To reset (all 0) the Blob just specify len/src as 0.
 *
 * @note    This function can be used to copy the content of one BLOB (src) to
 *          another (dest): gc_Blob_setBinary( &dest, src->data, src->len ).
 *
 * @param[in,out]   blob        The blob to set.
 * @param[in]       src         The binary source to write. If the len argument
 *                              is 0 this parameter is allowed to be 0 too, because
 *                              the operation does only 'reset' the Blob to 0!
 * @param[in]       len         The length of the binary src to write. Must be
 *                              greater than 0!
 * @param[in]       realloc     True:   Reallocs memory of blob if it can not
 *                                      hold the string.
 *                              False:  Writes only part of the string into the
 *                                      blob and reports an truncation error.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_STRING_TRUNCATED
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_Blob_setBinary( gc_Blob** blob,
                   const void* src,
                   const size_t len,
                   const bool realloc );



/**
 * Prints the blob content as hex into the given string.
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
 *
 * </pre>
 *
 * @param[in]       blob            The blob to print.
 * @param[in,out]   dest            Points to either a user-provided array or a
 *                                  char* to store the internally malloc'ed array.
 * @param[in]       len             The available length of the buffer. It'll be
 *                                  always counted without the trailing 0 character.
 *                                  If len is 0 the dest argument will be
 *                                  interpreted as type 'char**'.
 *                                  If len is not 0 the dest argument will be
 *                                  interpreted as type 'char*'.
 *                                  For more information see above table.
 * @param[in]       indentation     Additional indentation parameter (only for
 *                                  Blob). If 0 none will be used.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_STRING_TRUNCATED \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          #gc_ERROR_COM_MALLOC_FAILED \n
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_Blob_print( const gc_Blob* blob,
               void* dest,
               size_t len,
               const char* const indentation );


/******************************************************************************
 * Helper Functions for: gc_Value
 ******************************************************************************/
/**
 * Initializes a brand-new gc_Value.
 *
 * @note    This call will use an <b>internal</b> malloc call to get the resources,
 *          therefore the memory must be freed via gc_Value_free. Otherwise on
 *          some platforms the heap will be compromised.
 *
 * @param[in,out]   value       Points to the gc_Value to initialize.
 * @param[in]       dataType    The requested data type.
 * @param[in]       maxLen      If the data type is of #gc_DATA_TYPE_STRING or
 *                              #gc_DATA_TYPE_BLOB this parameter will be used,
 *                              otherwise it will be ignored. If the above
 *                              data types are used the argument is not allowed
 *                              to have a size of 0!
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_MALLOC_FAILED
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_Value_init( gc_Value* value,
               const gc_DataType dataType,
               const size_t maxLen );

/**
 * "Frees" the data of the gc_Value.
 *
 * Please be aware, that the gc_Value object as such can't be freed, because for
 * that a pointer to a pointer would be required. Therefore only additional
 * data fields are cleaned up (e.g. BLOB). The remaining fields are all set
 * to 0.
 *
 * @param[in]       value       Points to the gc_Value to 'free'
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_Value_free( gc_Value* value );

/**
 * Clones src and stores it at dest. Dest must not contain an existing gc_Value
 * object, otherwise it will <b>NOT</b> be freed and a resource leak occurs.
 *
 * @note    This call will use an <b>internal</b> malloc call to get the resources,
 *          therefore the memory must be freed via gc_Value_free. Otherwise on
 *          some platforms the heap will be compromised.
 *
 * @param[in]   dest    Points to the data location, where the cloned src
 *                      will be stored.
 * @param[in]   src     Points to the source to clone to dest.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_MALLOC_FAILED
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_Value_clone( gc_Value* dest,
                const gc_Value* src );


/**
 * Convenience function for converting the given string into the binary representation
 * of the gc_Value type.
 *
 * If the given string can't be converted to the data type of the gc_Value
 * object an error will be returned.
 *
 * @note    If the data type is BLOB/String and the src is longer than the value
 *          the function will automatically realloc the memory!
 *
 * @note    This function does NOT create a new gc_Value instance. It will only
 *          change an already created one!
 *
 * @param[in]       value   The value under operation. If the data type is
 *                          string/blob and the src is longer than the max
 *                          length the blob will be realloced to hold the src.
 * @param[in]       src     The string source to convert.
 * @param[in]       realloc True: Do realloc if the data type is BLOB/String
 *                                and the src requires more space to be stored.
 *                          False: Do not try to realloc. Copy as much as
 *                                 possible and return a truncation error.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_MALLOC_FAILED
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_Value_convertFromString( gc_Value* value,
                            const char* src,
                            const bool realloc );

/**
 * Converts the given data value, depending on the given data type into a
 * textual representation.
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
 *
 * </pre>
 *
 * @param[in]       value       The value to 'print' into the dest.
 * @param[in,out]   dest        Points to either a user-provided array or a
 *                              char* to store the internally malloc'ed array.
 * @param[in]       len         The available length of the buffer. It'll be always
 *                              counted without the trailing 0 character.
 *                              If len is 0 the dest argument will be interpreted
 *                              as type 'char**'.
 *                              If len is not 0 the dest argument will be interpreted
 *                              as type 'char*'.
 *                              For more information see above table.
 * @param[in]       indentation     Additional indentation parameter (only for
 *                                  Blob). If 0 none will be used.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_STRING_TRUNCATED \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          #gc_ERROR_COM_MALLOC_FAILED \n
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_Value_print( const gc_Value* const value,
                void* dest,
                size_t len,
                const char* const indentation );


/******************************************************************************
 * Helper Functions for: gc_PVArrayConfig
 ******************************************************************************/
/**
 * Initializes a gc_PVAraryConfig struct with default values, depending on the
 * given parameters. The content of the config object will be overwritten. No
 * free's will be called!
 *
 * @note    Use this function to set a gc_VariableConfig into a default state
 *          after it has been pushed on the stack/malloc'ed on the heap.
 *
 * @param[in]   config      Points to the gc_PVArrayConfig to initialize.
 * @param[in]   dataType    The data type for initialization.
 * @param[in]   maxLen      If the dataType is of #gc_DATA_TYPE_STRING or
 *                          #gc_DATA_TYPE_BLOB this arguments specifies the
 *                          maximum length of the blob field, otherwise it'll
 *                          be ignored.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_MALLOC_FAILED
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_PVArrayConfig_init( gc_PVArrayConfig* config,
                       const gc_DataType dataType,
                       const size_t maxLen );

/**
 * Initializes <b>all</b> fields of the PVArrayConfig.
 *
 * @param[in]   config              Points to the gc_PVArrayConfig to initialize.
 * @param[in]   name                For config.name
 *                                  If the length exceeds config.name's array
 *                                  size an invalid argument error will be returned.
 * @param[in]   isPersistent        For config.isPersistent
 * @param[in]   useDynamicMemory    For config.useDynamicMemory
 * @param[in]   noElements          For config.noElements
 * @param[in]   initial             For gc_Value_clone( &config.initial, initial )
 * @param[in]   minFlags            For config.minCheckingFlags
 * @param[in]   initMin             For gc_Value_clone( &config.initialMin, initMin )
 * @param[in]   maxFlags            For config.maxCheckingFlags
 * @param[in]   initMax             For gc_Value_clone( &config.initialMax, initMax )
 * @param[in]   simFlags            For config.simulationFlags
 * @param[in]   initSim             For gc_Value_clone( &config.initialSim, initSim )
 * @param[in]   logFlags            For config.loggingFlags
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_MALLOC_FAILED
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_PVArrayConfig_initAll( gc_PVArrayConfig* config,
                          const char* const name,
                          const bool isPersistent,
                          const bool useDynamicMemory,
                          const size_t noElements,
                          const gc_Value* initial,
                          const gc_Boundary minFlags,
                          const gc_Value* initMin,
                          const gc_Boundary maxFlags,
                          const gc_Value* initMax,
                          const gc_Simulation simFlags,
                          const gc_Value* initSim,
                          const gc_Logging logFlags );

/**
 * Clones src and stores it at dest. Dest must not contain an existing gc_PVArrayConfig
 * object, otherwise it will <b>NOT</b> be freed and a resource leak occurs.
 *
 * @note    The values are cloned via gc_Value_clone. Therefore use the gc_Value_xxx
 *          functions for access and memory management!
 *
 * @param[in]   dest    Points to the data location, where the cloned src
 *                      will be stored.
 * @param[in]   src     Points to the source to clone to dest.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_MALLOC_FAILED
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_PVArrayConfig_clone( gc_PVArrayConfig* dest,
                        const gc_PVArrayConfig* src );

/**
 * "Frees" the data of the config object.
 *
 * The object itself will not be freed, but all references memory will be freed.
 * Finally the object will be set to 0.
 *
 * @param[in]   config  Points to the config object to 'free'. This will really
 *                      call 'free' if the data type is for BLOB. Otherwise
 *                      only the fields will be reset to 0. To ease maintenance
 *                      it's advised to always call this function.
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_PVArrayConfig_free( gc_PVArrayConfig* config );

/******************************************************************************
 * Helper Functions for: gc_FifoConfig
 ******************************************************************************/
/**
 * Initializes a gc_FifoConfig struct with default values, depending on the
 * given parameters. The content of the config object will be overwritten. No
 * free's will be called!
 *
 * @note    Use this function to set a gc_FifoConfig into a default state
 *          after it has been pushed on the stack/malloc'ed on the heap.
 *
 * @param[in]   config      Points to the gc_FifoConfig to initialize.
 * @param[in]   length      The length of the fifo in number of elements. Must
 * @param[in]   dataType    The data type for initialization.
 * @param[in]   maxLen      If the dataType is of #gc_DATA_TYPE_STRING or
 *                          #gc_DATA_TYPE_BLOB this arguments specifies the
 *                          maximum length of the blob field, otherwise it'll
 *                          be ignored.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_MALLOC_FAILED
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_FifoConfig_init( gc_FifoConfig* config,
                    const size_t length,
                    const gc_DataType dataType,
                    const size_t maxLen );

/**
 * Initializes <b>all</b> fields of the FifoConfig.
 *
 * For more information about the constraints of each field please read the
 * documentation of #gc_FifoConfig.
 *
 * @param[in]   config              Points to the gc_FifoConfig to initialize.
 * @param[in]   name                For config.name
 *                                  If the length exceeds config.name's array
 *                                  size an invalid argument error will be returned.
 * @param[in]   isPersistent        For config.isPersistent.
 * @param[in]   type                For config.type
 * @param[in]   typeLength          For config.typeLength
 * @param[in]   length              For config.length
 *                                  Must be a multiple of 2!
 * @param[in]   isUsingTimestamps   For config.isUsingTimestamps
 * @param[in]   minFlags            For config.minCheckingFlags
 * @param[in]   initMin             For #gc_Value_clone( &config.initialMin, initMin )
 * @param[in]   maxFlags            For config.maxCheckingFlags
 * @param[in]   initMax             For #gc_Value_clone( &config.initialMax, initMax )
 * @param[in]   simFlags            For config.simulationFlags
 * @param[in]   initSim             For #gc_Value_clone( &config.initialSim, initSim )
 * @param[in]   logFlags            For config.loggingFlags
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_MALLOC_FAILED
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_FifoConfig_initAll( gc_FifoConfig* config,
                       const char* const name,
                       const bool isPersistent,
                       const gc_DataType type,
                       const uint32_t typeLength,
                       const uint32_t length,
                       const bool isUsingTimestamps,
                       const gc_Boundary minFlags,
                       const gc_Value* initMin,
                       const gc_Boundary maxFlags,
                       const gc_Value* initMax,
                       const gc_Simulation simFlags,
                       const gc_Value* initSim,
                       const gc_Logging logFlags );

/**
 * Clones src and stores it at dest. Dest must not contain an existing gc_FifoConfig
 * object, otherwise it will <b>NOT</b> be freed and a resource leak occurs.
 *
 * @note    The values are cloned via gc_Value_clone. Therefore use the gc_Value_xxx
 *          functions for access and memory management!
 *
 * @param[in]   dest    Points to the data location, where the cloned src
 *                      will be stored.
 * @param[in]   src     Points to the source to clone to dest.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_MALLOC_FAILED
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_FifoConfig_clone( gc_FifoConfig* dest,
                     const gc_FifoConfig* src );

/**
 * "Frees" the data of the config object.
 *
 * The object itself will not be freed, but all references memory will be freed.
 * Finally the object will be set to 0.
 *
 * @param[in]   config  Points to the config object to 'free'. This will really
 *                      call 'free' if the data type is for BLOB. Otherwise
 *                      only the fields will be reset to 0. To ease maintenance
 *                      it's advised to always call this function.
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_FifoConfig_free( gc_FifoConfig* config );

/******************************************************************************
 * Helper Functions for: gc_SchedulerInfo
 ******************************************************************************/
/**
 * Initializes a gc_SchedulerInfo structure with the given number of slots
 * for the topology.
 *
 * @note    There is currently no function to set all parameters, because this
 *          functions would have ~ 15 arguments and in addition all these
 *          fields are public anyway.
 *
 * @param[in,out]   info            Will hold the address of the created info record.
 * @param[in]       schedulerName   The name of the scheduler to assign.
 * @param[in]       slots           The initial size of numSlots.
 *
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_SchedulerInfo_init( gc_SchedulerInfo** const info,
                       const char* const schedulerName,
                       const uint32_t slots );

/**
 * Clones a SchedulerInfo.
 *
 * @param[in,out]   dest    Will hold the address of the cloned scheduler info.
 * @param[in]       src     The source of the clone operation.
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_SchedulerInfo_clone( gc_SchedulerInfo** const dest,
                        const gc_SchedulerInfo* src );

/**
 * Clears an already initialized gc_SchedulerInfo structure and frees all
 * resources.
 *
 * @param[in,out]   info    Will be freed and set to 0.
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_SchedulerInfo_free( gc_SchedulerInfo** info );

/**
 * Resizes the topology of the info to the given number of slots.
 *
 * This is a shrink and grow operation.
 *
 * @param[in,out]   info        Object to perform operation on.
 * @param[in]       numSlots    If 0: The 'logical' number of slots will be set
 *                              to 0, but the malloc'ed memory will be always at
 *                              least one slot to avoid SEGFAULTS.
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_SchedulerInfo_resize( gc_SchedulerInfo* const info,
                         const uint32_t numSlots );

/**
 * Convenience function for setting the topology.
 *
 * @param[in,out]   info        Will hold the new topology.
 * @param[in]       topology    The topology to set.
 * @param[in]       numSlots    The number of slots to copy. (NB: These are
 *                              in bytes numSlots * numSlots * slotFieldSize).
 *                              A topology is always a matrix!
 *                              A size of 0 will set the info->topology to 0
 *                              and immediatelly returns.
 * @param[in]       doResize    Should the info->topology field be realloced
 *                              to hold the new topology?
 *                              True:   Realloced if it's too small.
 *                              False:  Partial copy & return of truncation
 *                                      error.
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_SchedulerInfo_setTopology( gc_SchedulerInfo* const info,
                              const gc_SchedulingTopology topology,
                              const uint32_t numSlots,
                              const bool doResize );


/******************************************************************************
 * Helper Functions for: gc_BrowserInfo
 ******************************************************************************/
/**
 * Clears a browser info object, which resides on the stack.
 *
 * Use this function for a generic cleaning up after the browsing inteface
 * has returned the gc_BrowserInfos. Currently this function is only required
 * for the gc_BrowserInfo.info.scheduler field to free the topology memory.
 * Don't free this memory by hand, because otherwise there will be a
 * memory corruption!
 *
 * @param[in,out]   info    Info object on the stack to clean up.
 */
gc_EXP gc_ErrorID gc_CALLCONV
gc_BrowserInfo_clear( gc_BrowserInfo* info );



#endif /* GAMMA_COMMON_MISC_H__ */
