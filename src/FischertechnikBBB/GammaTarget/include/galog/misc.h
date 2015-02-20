#ifndef GAMMA_LOG_MISC_H__
#define GAMMA_LOG_MISC_H__

/**
 * @file
 *
 * Contains miscellaneous functions, to ease usage of the API.
 *
 *
 * @author  Copyright RST Industrie Automation GmbH
 */
/******************************************************************************
 * Header File Includes
 ******************************************************************************/
#include <gacommon/errorCodes.h>
#include <galog/platformDependencies.h>
#include <galog/dataTypes.h>

#include <stdio.h>


/******************************************************************************
 * GALOG Library Informations
 ******************************************************************************/
/**
 * Retrieves the version of the GALOG library.
 *
 * The following code sample shows how to retrieve the GALOG version information:
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 * gl_VersionNumber versionNumer = { 0, 0, 0, 0 };
 *
 * //(1) Get the version number.
 * returnValue = gl_getVersion( &versionNumber );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gl_getVersion() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 *
 * //(2) Write it onto stdout.
 * printf( "GALOG version: %u.%u.%u.%u\n", versionNumber.major,
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
gl_EXP gc_ErrorID gc_CALLCONV
gl_getVersion( gc_VersionNumber* const versionNumber );


/******************************************************************************
 * Easy Print Function Declarations
 ******************************************************************************/
/**
 * Converts the given gl_PVState into a textual representation.
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
gl_EXP gc_ErrorID gc_CALLCONV
gl_EventType_print( const gl_EventType state,
                    const char** dest );

/**
 * Converts the given gl_MessageType into a textual representation.
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
gl_EXP gc_ErrorID gc_CALLCONV
gl_MessageType_print( const gl_MessageType type,
                      const char** dest );

/**
 * Converts the given gl_TimeStamp into a textual representation.
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
 *
 * @param[in]       timeStamp       The time stamp to print.
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
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_STRING_TRUNCATED \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          #gc_ERROR_COM_MALLOC_FAILED \n
 */
gl_EXP gc_ErrorID gc_CALLCONV
gl_TimeStamp_print( const gl_TimeStamp* const timeStamp,
                    const char* indentation,
                    void* dest,
                    size_t len );

/**
 * Converts the given gl_RegisterEvent into a textual representation.
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
 *
 * @param[in]       registerEvent   The register event to print.
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
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_STRING_TRUNCATED \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          #gc_ERROR_COM_MALLOC_FAILED \n
 */
gl_EXP gc_ErrorID gc_CALLCONV
gl_RegisterEvent_print( const gl_RegisterEvent* const registerEvent,
                        const char* indentation,
                        void* dest,
                        size_t len );

/**
 * Converts the given gl_RegisterAction into a textual representation.
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
 *
 * @param[in]       registerAction  The register event to print.
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
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_STRING_TRUNCATED \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          #gc_ERROR_COM_MALLOC_FAILED \n
 */
gl_EXP gc_ErrorID gc_CALLCONV
gl_RegisterAction_print( const gl_RegisterAction* const registerAction,
                         const char* indentation,
                         void* dest,
                         size_t len );

/**
 * Converts the given gl_RegisterPV into a textual representation.
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
 *
 * @param[in]       registerPV      The register event to print.
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
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_STRING_TRUNCATED \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          #gc_ERROR_COM_MALLOC_FAILED \n
 */
gl_EXP gc_ErrorID gc_CALLCONV
gl_RegisterPV_print( const gl_RegisterPV* const registerPV,
                     const char* indentation,
                     void* dest,
                     size_t len );

/**
 * Converts the given gl_Unregister into a textual representation.
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
 *
 * @param[in]       unregister      The register event to print.
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
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_STRING_TRUNCATED \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          #gc_ERROR_COM_MALLOC_FAILED \n
 */
gl_EXP gc_ErrorID gc_CALLCONV
gl_Unregister_print( const gl_Unregister* const unregister,
                     const char* indentation,
                     void* dest,
                     size_t len );

/**
 * Converts the given gl_LogPV into a textual representation.
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
 *
 * @param[in]       logPV           The register event to print.
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
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_STRING_TRUNCATED \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          #gc_ERROR_COM_MALLOC_FAILED \n
 */
gl_EXP gc_ErrorID gc_CALLCONV
gl_LogPV_print( const gl_LogPV* const logPV,
                const char* indentation,
                void* dest,
                size_t len );

/**
 * Converts the given gl_LogMeta into a textual representation.
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
 *
 * @param[in]       logMeta         The register event to print.
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
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_STRING_TRUNCATED \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          #gc_ERROR_COM_MALLOC_FAILED \n
 */
gl_EXP gc_ErrorID gc_CALLCONV
gl_LogMeta_print( const gl_LogMeta* const logMeta,
                  const char* indentation,
                  void* dest,
                  size_t len );


/**
 * Converts the given gl_Message into a textual representation.
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
 *
 * @param[in]       message         The message to print.
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
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          #gc_ERROR_COM_STRING_TRUNCATED \n
 *          #gc_ERROR_COM_INTERNAL_ERROR \n
 *          #gc_ERROR_COM_MALLOC_FAILED \n
 */
gl_EXP gc_ErrorID gc_CALLCONV
gl_Message_print( const gl_Message* const message,
                 const char* indentation,
                 void* dest,
                 size_t len );

/**
 * Writes the logged message into the given file stream.
 *
 * @param[in]   f               Destination file stream.
 * @param[in]   message         The message to print.
 * @param[in]   indentation     Additional indentation parameter. If 0 none
 *                              will be used.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT
 */
gl_EXP gc_ErrorID gc_CALLCONV
gl_Message_fprint( FILE* const f,
                  const gl_Message* const message,
                  const char* indentation );


#endif /* GAMMA_LOG_MISC_H__ */
