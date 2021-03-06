///////////////////////////////////////////////////////////////////////////////
//
// Tr069SocketClient_fsm_interface.h
//
// Autogenerated from Tr069SocketClient.fsm
//
// Fsm Interface Class
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __Tr069SocketClient_fsm_interface_h_
#define __Tr069SocketClient_fsm_interface_h_
///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/ThreadWithQueue.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Tr069HttpPostRequest.h"

namespace tr069
{

/*** WARNING: Code AUTO-GENERATED from Tr069SocketClient.fsm. Do not edit! ***/
class SocketClientFsmActionHandleTcpConnectReq
{
public:
    SocketClientFsmActionHandleTcpConnectReq() {}
    virtual ~SocketClientFsmActionHandleTcpConnectReq() {}

    typedef enum Outcome_tag
    {
        FSM_ACTION_SUCCESS,
        FSM_ACTION_CONNECTION_FAILURE,
    } Outcome;

    virtual Outcome HandleTcpConnectReq(shared_ptr<threeway::Queueable>) = 0;
};

/*** WARNING: Code AUTO-GENERATED from Tr069SocketClient.fsm. Do not edit! ***/
class SocketClientFsmActionSendHttpPost
{
public:
    SocketClientFsmActionSendHttpPost() {}
    virtual ~SocketClientFsmActionSendHttpPost() {}

    typedef enum Outcome_tag
    {
        FSM_ACTION_SUCCESS,
        FSM_ACTION_CONNECTION_FAILURE,
    } Outcome;

    virtual Outcome SendHttpPost(shared_ptr<HttpPostRequest>) = 0;
};

/*** WARNING: Code AUTO-GENERATED from Tr069SocketClient.fsm. Do not edit! ***/
class SocketClientFsmInterface :
    public SocketClientFsmActionHandleTcpConnectReq,
    public SocketClientFsmActionSendHttpPost
{
public:
    SocketClientFsmInterface() {}
    virtual ~SocketClientFsmInterface() {}
    
    // Actions
    virtual void HandleTcpConnectInd(shared_ptr<threeway::Queueable>) = 0;
    virtual void HandleTcpDisconnectReq(void*) = 0;
    virtual void RejectTcpConnectReq(shared_ptr<threeway::Queueable>) = 0;
    virtual void SendHttpPostButDoNotWaitForResponse(shared_ptr<HttpPostRequest>) = 0;
    
    // Entry/Exit
    
    // Guard Conditions
    virtual bool QueryAfterPostWaitForResponse(shared_ptr<HttpPostRequest>) = 0;
    
};
} // -namespace-

#endif // __Tr069SocketClient_fsm_interface_h_

