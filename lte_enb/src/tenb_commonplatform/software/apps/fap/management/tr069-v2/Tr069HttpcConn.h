///////////////////////////////////////////////////////////////////////////////
//
// <File name>
//
// <Description of class/module>
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069HttpcConn_h_
#define __Tr069HttpcConn_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <nanohttp/nanohttp-client.h>
#include <comms/IPv4Address.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

//#include "Tr069Csoap.h"


using namespace std;

namespace tr069
{

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class HttpcConn {

public:
    HttpcConn( const threeway::IPv4Address & localIpaddress ) : m_conn(NULL), m_localIpaddress(localIpaddress) { memset( &m_hurl, 0, sizeof(m_hurl));  }

    ~HttpcConn(){ Disconnect(); }

    bool Connect(const string & url );
    void Disconnect( void );
    void SendTcpConnectionFailureInd();
    void SendTcpConnectCnf();

    bool QueryConnected() const { return (m_conn)? true:false; }

    httpc_conn_t* get(void) { return m_conn; }

    std::string * url(void) {return &m_url;}
    hurl_t & hurl(void) {return m_hurl;}

    bool Post( const string & txSoapEnvelope, hresponse_t ** response  );

private:
    bool WriteToSocket(string& envelope);
    static const int PostReplyTimeoutInSeconds;
    bool hsocket_open_ipsec(hsocket_t * dsock, const char *hostname, int port);
    void httpc_header_add_date(void);
    void httpc_header_free( void );
    void httpc_header_new(
            hreq_method_t method,
            size_t txContentLength,
            std::string & txMessage );

    hurl_t m_hurl;
    std::string m_url;
    httpc_conn_t *m_conn;
    threeway::IPv4Address m_localIpaddress;

};

}

#endif
