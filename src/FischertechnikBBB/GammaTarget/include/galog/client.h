#ifndef GAMMA_LOG_CLIENT_H_
  #define GAMMA_LOG_CLIENT_H_

/**
 * @file
 *
 * Defines the interface of the Gamma Logging Client.
 *
 * <h3> Overview </h3>
 *
 * A client can be connected to a single data source (socket) of a service,
 * running a logging plugin. If the logging plugin is configured to provide
 * multiple, parallel data sources then the same amount of clients must be
 * created and connected to each data source (port). The configuration of the
 * service logging data source is done via the service XML configuration files
 * (for more information please read the documentation for these).
 *
 * <h3> Multithread-Safety </h3>
 *
 * This Client is optimized for single-threaded usage. Therefore it's not
 * safe to call the gl_Client functions from different contexts (threads).
 *
 * <h3> Data Consistency </h3>
 *
 * Currently the Gamma Logging Backend does not buffer the register/unregister
 * messages.
 *
 * These message contain the handle for associating e. g. #gl_LogPV message with
 * the corresponding PV! Therefore if a client connects, disconnect and connects
 * again the second connect will no longer receive the register messages and the
 * association between a #gl_LogPV message and the corresponding PV is no longer
 * possible.
 *
 * It's scheduled to fix this issue by buffering the register/unregister messages
 * at the Gamma Logging Backend. Until then please ensure to not 'lose' these
 * messages.
 *
 * <h3> Data Reception </h3>
 *
 * The data reception behavior might differ for the various #gl_ClientType, used
 * to instantiate a gl_ClientPtr (#gl_client_new). For example some implementations
 * might buffer a chunk of multiple messages. For more information see
 * #gl_client_getNextMessage.
 *
 * @author  Copyright RST Industrie Automation GmbH
 */
/******************************************************************************
 * Header File Includes
 ******************************************************************************/
#include <gacommon/errorCodes.h>
#include <galog/dataTypes.h>
#include <galog/platformDependencies.h>

/******************************************************************************
 * Creation/Deletion Function Declarations
 ******************************************************************************/
/**
 * Creates a new client.
 *
 * This client will be set up so it's ready to connect to a specific server,
 * but not connection is done within this function!
 *
 * The following code sample shows how to create a new client with a default
 * configuration:
 * @code
 * gl_ClientPtr client = 0;
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 *
 * returnValue = gl_client_new( &client, gl_CLIENT_TYPE_DEFAULT ) );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gl_client_new() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   me              This object pointer.
 * @param[in]   type            The client type to use. Must match the type of
 *                              the logging server (backend) to connect to later.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT
 */
gl_EXP gc_ErrorID gc_CALLCONV
gl_client_new( gl_ClientPtr* me,
               gl_ClientType type );

/**
 * Deletes a client. If the client is still connected to a server the socket
 * will be shut down!
 *
 * The following code sample shows how to delete a client.
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 *
 * returnValue = gl_client_delete( &client ) );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gl_client_delete() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   me              This object pointer.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT
 */
gl_EXP gc_ErrorID gc_CALLCONV
gl_client_delete( gl_ClientPtr* me );

/******************************************************************************
 * Run-Time Function Declarations
 ******************************************************************************/
/**
 * Connects to the given logging backend server and does an
 * internal handshake to validate both communication partners using the same
 * protocol and are correctly configurated.
 *
 * The following code sample shows how to connect to a logging server with an
 * already created client.
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 *
 * //The variable 'client' was already created via gl_client_new.
 *
 * //The connection will use the following configuration:
 * //Note that the ipAddress must be in host order. For this sample just let us
 * //assume that the IP address 1.2.3.4 will be mapped to 0x01020304. For a real
 * //usage sample please read your host systems manual for conversion informations!
 * //This is very important, because the representation might differ!
 * uint32_t ipAddress = 0x01020304;     //IP=1.2.3.4 - (host order required!)
 * uint16_t port = 2000;                //Port of the server is 2000
 * uint32_t sendTimeoutMS = 0;          //No timeout at all
 * uint32_t recvTimeoutMS = 0;          //No timeout at all
 *
 * returnValue = gl_client_connectByAddress( client, ipAddress, port,
 *                                           sendTimeoutMS, recvTimeoutMS ) );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gl_client_connectByAddress() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @note    It's only valid to connect to a server while no connection is active.
 *          To reconnect to another server a previous call to #gl_client_disconnect
 *          is required.
 *
 * @param[in]   me              This object pointer.
 * @param[in]   ipAddress       Binary IP address representation of server.
 *                              Must be in host order!
 * @param[in]   port            Connect to port of server.
 * @param[in]   sendTimeoutMS   Timeout for transmission (handshake).
 * @param[in]   recvTimeoutMS   Timeout for reception (#gl_client_getNextMessage).
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          \n
 *          #gc_ERROR_CLIENT_SOCKET_NO_SERVER_PORT
 */
gl_EXP gc_ErrorID gc_CALLCONV
gl_client_connectByAddress( gl_ClientPtr me,
                            uint32_t ipAddress,
                            uint16_t port,
                            uint32_t sendTimeoutMS,
                            uint32_t recvTimeoutMS );

/**
 * Overloaded version of gl_Client_connect, using a textual address, instead
 * the binary network representation of the socket address.
 *
 * The following code sample shows how to connect to a logging server with an
 * already created client.
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 *
 * //The variable 'client' was already created via gl_client_new.
 *
 * //The connection will use the following configuration:
 * const char* ipAddress = "1.2.3.4"    //No translation into network order required.
 * uint16_t port = 2000;                //Port of the server is 2000
 * uint32_t sendTimeoutMS = 0;          //No timeout at all
 * uint32_t recvTimeoutMS = 0;          //No timeout at all
 *
 * returnValue = gl_client_connectByName( client, ipAddress, port,
 *                                        sendTimeoutMS, recvTimeoutMS ) );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gl_client_connectByName() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @note    It's only valid to connect to a server while no connection is active.
 *          To reconnect to another server a previous call to #gl_client_disconnect
 *          is required.
 *
 * @param[in]   me              This object pointer.
 * @param[in]   address         The address can either be a DNS/Hostname or a
 *                              Dotted Decimal Notation of an IP address. The
 *                              function will internally first try to resolve
 *                              a DNS/Hostname and if this fails interprets the
 *                              address as Dotted Decimal Notation.
 *                              If the name could not be resolved into a valid
 *                              IP address the function will return
 *                              #gc_ERROR_COM_INVALID_ARGUMENT.
 * @param[in]   port            Connect to port of server.
 * @param[in]   sendTimeoutMS   Timeout for transmission (handshake).
 * @param[in]   recvTimeoutMS   Timeout for reception (#gl_client_getNextMessage).
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          \n
 *          #gc_ERROR_CLIENT_SOCKET_NO_SERVER_PORT
 */
gl_EXP gc_ErrorID gc_CALLCONV
gl_client_connectByName( gl_ClientPtr me,
                         const char* address,
                         uint16_t port,
                         uint32_t sendTimeoutMS,
                         uint32_t recvTimeoutMS );

/**
 * Disconnect the current connection or do nothing if no connection is active.
 *
 * This functions in conjunction with #gl_client_connectByName and
 * #gl_client_connectByAddress allows a single client instance to switch
 * connections.
 *
 * The following code sample shows how to disconnect from a logging server.
 * @code
 * gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 *
 * //The variable 'client' was already created via gl_client_new.
 *
 * returnValue = gl_client_disconnect( client ) );
 * if( gc_ERROR_SUCCESS.errorID != returnValue )
 * {
 *     fprintf( stderr, "Call to gl_client_disconnect() failed.\n" );
 *     fprintf( stderr, "Error ID=%d\n", returnValue );
 *     fprintf( stderr, "Error description=%s\n", gc_getErrorDescription( returnValue ) );
 *     exit( -1 );
 * }
 * @endcode
 *
 * @param[in]   me              This object pointer.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT
 */
gl_EXP gc_ErrorID gc_CALLCONV
gl_client_disconnect( gl_ClientPtr me );


/**
 * Retrieves the next message from the transmitted logged values. If currently
 * no values are transmitted the function will wait for the given timeout to
 * occur. If the timeout was set to 0 the function will wait for ever.
 *
 * The following sample shows how to use this function:
 * @code
 *
 * //Helper function to print a timestamp to stdout.
 * void printTimeStamp( gl_TimeStamp* t )
 * {
 *     printf( "eventHandle='%" PRIu64 "' actionHandle='%" PRIu64 "' frameNumber='%u' timespec='%lu,%lu'",
 *             t->eventHandle, t->actionHandle, t->frameNumber, t->timespec.tv_sec,
 *             t->timespec.tv_nsec );
 * }
 *
 * //This function will retrieve all logged message of the given client and writes
 * //them to stdout. All other logged messages are discarded.
 * void printPVMessages( gl_Client* client )
 * {
 *     gc_ErrorID returnValue = gc_ERROR_SUCCESS.errorID;
 *
 *     gl_Message* m = 0;       //Memory will be managed by the client. No need to
 *                              //provide memory from the user-application :-)
 *
 *     //Let's continuously retrieve all values.
 *     //Only print the numeric PVs. Ignore remaining message by only printing a
 *     //a reception acknowledgment.
 *     while( gc_ERROR_SUCCESS.errorID == (returnValue = gl_client_getNextMessage( client, &m ) ) )
 *     {
 *         //Let's print only UINT8 PVs. The other are discarded.
 *
 *         switch( m->type )
 *         {
 *             case gl_MESSAGE_TYPE_LOG_PV:
 *                 printf( "Log pv: pvHandle='%" PRIu64 "' dataType='%u', fieldType='%u', timeStamp={",
 *                          m->message.logPV.pvHandle,
 *                          m->message.logPV.value.type,
 *                          m->message.logPV.fieldType );
 *                 printTimeStamp( m->message.logPV.timeStamp );
 *                 printf( "} value='" );
 *                 switch( m->message.logPV.value.type )
 *                 {
 *                     case gc_DATA_TYPE_UINT_8:
 *                     case gc_DATA_TYPE_UINT_16:
 *                     case gc_DATA_TYPE_UINT_32:
 *                     case gc_DATA_TYPE_UINT_64:
 *                         printf( "%" PRIu64, m->message.logPV.value.data.numeric.uint64 );
 *                         break;
 *
 *                     case gc_DATA_TYPE_SINT_8:
 *                     case gc_DATA_TYPE_SINT_16:
 *                     case gc_DATA_TYPE_SINT_32:
 *                     case gc_DATA_TYPE_SINT_64:
 *                         printf( "%" PRId64, m->message.logPV.value.data.numeric.sint64 );
 *                         break;
 *
 *                     case gc_DATA_TYPE_IEEE_32:
 *                         printf( "%f", m->message.logPV.value.data.numeric.ieee32 );
 *                         break;
 *
 *                     case gc_DATA_TYPE_IEEE_64:
 *                         printf( "%lf", m->message.logPV.value.data.numeric.ieee64 );
 *                         break;
 *
 *                     default:
 *                         printf( "Ignoring logged PV with data type '%d'", m->message.logPV.value.type );
 *                 }
 *
 *             default:
 *                 printf( "Ignoring other message with type '%d'", m->type );
 *         }
 *
 *         printf( "\n" );
 *     }
 * }
 *
 * @endcode
 *
 * @note        Internally the client might buffer a chunk of received logged
 *              message from the Gamma Service (logging server). Therefore a
 *              connection loss to the Gamma Service might not be detected
 *              immediately.
 *
 * @note        If the Gamma Service was terminated ungracefully and therefore
 *              the logging server's socket too, then this function
 *              will return #gc_ERROR_CLIENT_SOCKET_RECEIVE_FAILED. When a
 *              graceful shut down of the Gamma Service was performed
 *              #gc_ERROR_CLIENT_SOCKET_WAS_CLOSED_BY_SERVER will be returned.
 *
 *
 * @param[in]   me          This object pointer.
 * @param[in]   message     Will point to the received message. The memory is
 *                          stored and managed within the client. Therefore
 *                          don't free it, because the client will take care
 *                          of this, when #gl_client_delete gets called.
 *                          The value is valid as long as no other function
 *                          of the gl_Client interface will be called.
 *
 * @return  #gc_ERROR_SUCCESS \n
 *          \n
 *          #gc_ERROR_COM_INVALID_ARGUMENT \n
 *          \n
 *          #gc_ERROR_CLIENT_TIMED_OUT \n
 *          #gc_ERROR_CLIENT_SOCKET_WAS_CLOSED_BY_SERVER\n
 *          #gc_ERROR_CLIENT_SOCKET_RECEIVE_FAILED\n
 *          \n
 *          #gc_ERROR_COM_INTERNAL_ERROR
 */
gl_EXP gc_ErrorID gc_CALLCONV
gl_client_getNextMessage( gl_ClientPtr me,
                          const gl_Message** message );



#endif /* GAMMA_LOG_CLIENT_H_ */
