///////////////////////////////////////////////////////////////////////////////
//
//Led_fsm.cpp
//
// Autogenerated from led.fsm
//
// See header file for documentation.
//
// Copyright radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "Led_fsm.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Static Data
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

using namespace Led;

namespace Led
{

/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
LedFsm::LedFsm(
    LedFsmInterface & interfaceClass,
    bool traceEnabled,
    const char * name 
    ) :
    mInterface(interfaceClass),
    mFsmTraceEnabled(traceEnabled),
    mName(name),
    mState(NULL),
    mTemperatureOK(*this ),
    mInitialState(*this ),
    mWrongTemperature(*this ),
    mFapError(*this ),
    mPowerOnSelfTest(*this ),
    mConnectToServer(*this ),
    mNoConnectionToServer(*this ),
    mNotOperational(*this ),
    mOperationalError(*this ),
    mOperational(*this ),
    mfsmEventQueue(),
    mFsmInjectInProgress(false),
    mEventCounter(0)
{
    // Initial State
    mTemperatureOK.Entry();
    mInitialState.Entry();

    if(NULL != mState)
    {
       while( !mState->RunToCompletion() )
       {
          continue;
       }
    }
}

/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
LedFsm::~LedFsm()
{
    RSYS_ASSERT_PRINTF(!mFsmInjectInProgress, "LedFsm deleted while event-inject in progress.");

    mfsmEventQueue.clear();
    mCurrentStateTransitionExitsList.clear();
}

/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
void LedFsm::InjectEventMapLoaded(void* event)
{
    shared_ptr<FsmEvent> fsmEvent(new FsmEvent_void_STAR_(event));
    Enqueue( LedFsm::FSM_EVENT_EventMapLoaded, fsmEvent);
}
/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
void LedFsm::InjectEventTemperatureOutOfRange(void* event)
{
    shared_ptr<FsmEvent> fsmEvent(new FsmEvent_void_STAR_(event));
    Enqueue( LedFsm::FSM_EVENT_EventTemperatureOutOfRange, fsmEvent);
}
/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
void LedFsm::InjectEventTemperatureInRange(void* event)
{
    shared_ptr<FsmEvent> fsmEvent(new FsmEvent_void_STAR_(event));
    Enqueue( LedFsm::FSM_EVENT_EventTemperatureInRange, fsmEvent);
}
/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
void LedFsm::InjectEventNoCalibration(void* event)
{
    shared_ptr<FsmEvent> fsmEvent(new FsmEvent_void_STAR_(event));
    Enqueue( LedFsm::FSM_EVENT_EventNoCalibration, fsmEvent);
}
/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
void LedFsm::InjectEventSelfTestOk(void* event)
{
    shared_ptr<FsmEvent> fsmEvent(new FsmEvent_void_STAR_(event));
    Enqueue( LedFsm::FSM_EVENT_EventSelfTestOk, fsmEvent);
}
/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
void LedFsm::InjectEventCannotConnectToServer(void* event)
{
    shared_ptr<FsmEvent> fsmEvent(new FsmEvent_void_STAR_(event));
    Enqueue( LedFsm::FSM_EVENT_EventCannotConnectToServer, fsmEvent);
}
/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
void LedFsm::InjectEventConnectedToServer(void* event)
{
    shared_ptr<FsmEvent> fsmEvent(new FsmEvent_void_STAR_(event));
    Enqueue( LedFsm::FSM_EVENT_EventConnectedToServer, fsmEvent);
}
/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
void LedFsm::InjectEventNotOperationalTimeout(void* event)
{
    shared_ptr<FsmEvent> fsmEvent(new FsmEvent_void_STAR_(event));
    Enqueue( LedFsm::FSM_EVENT_EventNotOperationalTimeout, fsmEvent);
}
/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
void LedFsm::InjectEventTransmitterEnabled(void* event)
{
    shared_ptr<FsmEvent> fsmEvent(new FsmEvent_void_STAR_(event));
    Enqueue( LedFsm::FSM_EVENT_EventTransmitterEnabled, fsmEvent);
}
/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
void LedFsm::InjectEventTransmitterDisabled(void* event)
{
    shared_ptr<FsmEvent> fsmEvent(new FsmEvent_void_STAR_(event));
    Enqueue( LedFsm::FSM_EVENT_EventTransmitterDisabled, fsmEvent);
}
/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
void LedFsm::Enqueue( EventId eventId, shared_ptr<FsmEvent> fsmEvent )
{
    RSYS_ASSERT(eventId < NUMBER_OF_INJECTABLE_EVENTS);

    // Reentrancy Protection is NOT intended to make thread-safe
    shared_ptr<QueuedFsmEvent>  qEvent(new QueuedFsmEvent(eventId, fsmEvent));
    mfsmEventQueue.push_back(qEvent);

    if(!mFsmInjectInProgress)
    {
        mFsmInjectInProgress = true;

        list< shared_ptr<QueuedFsmEvent> >::iterator event = mfsmEventQueue.begin();

        while( event != mfsmEventQueue.end() )
        {
            RSYS_ASSERT(*event);
            RSYS_ASSERT(mState);

            EventId queuedEventId = (*event)->mId;

            RSYS_ASSERT(queuedEventId < NUMBER_OF_INJECTABLE_EVENTS);

            if( !mState->DeferEvent( queuedEventId ) )
            {
                ++mEventCounter;

                if(mFsmTraceEnabled) { TRACE_PRINTF("%s.%u: %s <--(%s)-- ", mName.c_str(), mEventCounter, mState->mName.c_str(), mEventName[queuedEventId] ); }

                mState->Inject(queuedEventId, (*event)->mFsmEvent);

                while( !mState->RunToCompletion() )
                {
                    continue;
                }

                mfsmEventQueue.erase(event);
                event = mfsmEventQueue.begin();
            }
            else
            {
                if(mFsmTraceEnabled) { TRACE_PRINTF("%s.-: %s (%s deferred)", mName.c_str(), mState->mName.c_str(), mEventName[queuedEventId] ); };
                event++;
            }
        }

        mFsmInjectInProgress = false;
    }
    else
    {
        if(mFsmTraceEnabled) { TRACE_PRINTF("%s.-: (%s enqueued)", mName.c_str(), mEventName[eventId] ); }
    }
}

/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
const char * LedFsm::mEventName[NUMBER_OF_INJECTABLE_EVENTS] =
{
    "EventMapLoaded",
    "EventTemperatureOutOfRange",
    "EventTemperatureInRange",
    "EventNoCalibration",
    "EventSelfTestOk",
    "EventCannotConnectToServer",
    "EventConnectedToServer",
    "EventNotOperationalTimeout",
    "EventTransmitterEnabled",
    "EventTransmitterDisabled",
};

/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
void LedFsm::SimpleState::Inject(
    EventId eventId,
    shared_ptr<FsmEvent> fsmEvent
    )
{
    RSYS_ASSERT(eventId < NUMBER_OF_INJECTABLE_EVENTS);

    switch(eventId)
    {
        case LedFsm::FSM_EVENT_EventMapLoaded:
        {
            RSYS_ASSERT(FSM_EVENT_TYPE_void_STAR_ == fsmEvent->mEventType);
            shared_ptr<FsmEvent_void_STAR_> event = dynamic_pointer_cast<FsmEvent_void_STAR_>(fsmEvent);
            InjectEventMapLoaded(event->mEvent);
        }
        break;

        case LedFsm::FSM_EVENT_EventTemperatureOutOfRange:
        {
            RSYS_ASSERT(FSM_EVENT_TYPE_void_STAR_ == fsmEvent->mEventType);
            shared_ptr<FsmEvent_void_STAR_> event = dynamic_pointer_cast<FsmEvent_void_STAR_>(fsmEvent);
            InjectEventTemperatureOutOfRange(event->mEvent);
        }
        break;

        case LedFsm::FSM_EVENT_EventTemperatureInRange:
        {
            RSYS_ASSERT(FSM_EVENT_TYPE_void_STAR_ == fsmEvent->mEventType);
            shared_ptr<FsmEvent_void_STAR_> event = dynamic_pointer_cast<FsmEvent_void_STAR_>(fsmEvent);
            InjectEventTemperatureInRange(event->mEvent);
        }
        break;

        case LedFsm::FSM_EVENT_EventNoCalibration:
        {
            RSYS_ASSERT(FSM_EVENT_TYPE_void_STAR_ == fsmEvent->mEventType);
            shared_ptr<FsmEvent_void_STAR_> event = dynamic_pointer_cast<FsmEvent_void_STAR_>(fsmEvent);
            InjectEventNoCalibration(event->mEvent);
        }
        break;

        case LedFsm::FSM_EVENT_EventSelfTestOk:
        {
            RSYS_ASSERT(FSM_EVENT_TYPE_void_STAR_ == fsmEvent->mEventType);
            shared_ptr<FsmEvent_void_STAR_> event = dynamic_pointer_cast<FsmEvent_void_STAR_>(fsmEvent);
            InjectEventSelfTestOk(event->mEvent);
        }
        break;

        case LedFsm::FSM_EVENT_EventCannotConnectToServer:
        {
            RSYS_ASSERT(FSM_EVENT_TYPE_void_STAR_ == fsmEvent->mEventType);
            shared_ptr<FsmEvent_void_STAR_> event = dynamic_pointer_cast<FsmEvent_void_STAR_>(fsmEvent);
            InjectEventCannotConnectToServer(event->mEvent);
        }
        break;

        case LedFsm::FSM_EVENT_EventConnectedToServer:
        {
            RSYS_ASSERT(FSM_EVENT_TYPE_void_STAR_ == fsmEvent->mEventType);
            shared_ptr<FsmEvent_void_STAR_> event = dynamic_pointer_cast<FsmEvent_void_STAR_>(fsmEvent);
            InjectEventConnectedToServer(event->mEvent);
        }
        break;

        case LedFsm::FSM_EVENT_EventNotOperationalTimeout:
        {
            RSYS_ASSERT(FSM_EVENT_TYPE_void_STAR_ == fsmEvent->mEventType);
            shared_ptr<FsmEvent_void_STAR_> event = dynamic_pointer_cast<FsmEvent_void_STAR_>(fsmEvent);
            InjectEventNotOperationalTimeout(event->mEvent);
        }
        break;

        case LedFsm::FSM_EVENT_EventTransmitterEnabled:
        {
            RSYS_ASSERT(FSM_EVENT_TYPE_void_STAR_ == fsmEvent->mEventType);
            shared_ptr<FsmEvent_void_STAR_> event = dynamic_pointer_cast<FsmEvent_void_STAR_>(fsmEvent);
            InjectEventTransmitterEnabled(event->mEvent);
        }
        break;

        case LedFsm::FSM_EVENT_EventTransmitterDisabled:
        {
            RSYS_ASSERT(FSM_EVENT_TYPE_void_STAR_ == fsmEvent->mEventType);
            shared_ptr<FsmEvent_void_STAR_> event = dynamic_pointer_cast<FsmEvent_void_STAR_>(fsmEvent);
            InjectEventTransmitterDisabled(event->mEvent);
        }
        break;

        default:
            RSYS_ASSERT(false);
            break;
    }
}

/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
void LedFsm::InitialState::InjectEventMapLoaded(
    void* event
    )
{
    {
        mFsm.mState->Exit();
        mFsm.mPowerOnSelfTest.Entry();
    }
}

/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
void LedFsm::InitialState::InjectEventTemperatureOutOfRange(
    void* event
    )
{
    {
        mFsm.mState->Exit();
        mFsm.mState->Exit();
        mFsm.mWrongTemperature.Entry();
    }
}

// Event EventTemperatureInRange not handled in state InitialState

// Event EventNoCalibration not handled in state InitialState

// Event EventSelfTestOk not handled in state InitialState

// Event EventCannotConnectToServer deferred in state InitialState

// Event EventConnectedToServer deferred in state InitialState

// Event EventNotOperationalTimeout deferred in state InitialState

// Event EventTransmitterEnabled deferred in state InitialState

// Event EventTransmitterDisabled deferred in state InitialState

/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
bool LedFsm::InitialState::DeferEvent( EventId eventId ) const
{
    switch( eventId )
    {
        case LedFsm::FSM_EVENT_EventCannotConnectToServer:
            return true;

        case LedFsm::FSM_EVENT_EventConnectedToServer:
            return true;

        case LedFsm::FSM_EVENT_EventNotOperationalTimeout:
            return true;

        case LedFsm::FSM_EVENT_EventTransmitterEnabled:
            return true;

        case LedFsm::FSM_EVENT_EventTransmitterDisabled:
            return true;


        default:
            return false;
    }
}

// Event EventMapLoaded not handled in state WrongTemperature

// Event EventTemperatureOutOfRange not handled in state WrongTemperature

/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
void LedFsm::WrongTemperature::InjectEventTemperatureInRange(
    void* event
    )
{
    {
        mFsm.mState->Exit();
        mFsm.mTemperatureOK.Entry();
    }
}

// Event EventNoCalibration deferred in state WrongTemperature

// Event EventSelfTestOk deferred in state WrongTemperature

// Event EventCannotConnectToServer deferred in state WrongTemperature

// Event EventConnectedToServer deferred in state WrongTemperature

// Event EventNotOperationalTimeout deferred in state WrongTemperature

// Event EventTransmitterEnabled deferred in state WrongTemperature

// Event EventTransmitterDisabled deferred in state WrongTemperature

/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
bool LedFsm::WrongTemperature::DeferEvent( EventId eventId ) const
{
    switch( eventId )
    {
        case LedFsm::FSM_EVENT_EventNoCalibration:
            return true;

        case LedFsm::FSM_EVENT_EventSelfTestOk:
            return true;

        case LedFsm::FSM_EVENT_EventCannotConnectToServer:
            return true;

        case LedFsm::FSM_EVENT_EventConnectedToServer:
            return true;

        case LedFsm::FSM_EVENT_EventNotOperationalTimeout:
            return true;

        case LedFsm::FSM_EVENT_EventTransmitterEnabled:
            return true;

        case LedFsm::FSM_EVENT_EventTransmitterDisabled:
            return true;


        default:
            return false;
    }
}

// Event EventMapLoaded not handled in state FapError

// Event EventTemperatureOutOfRange not handled in state FapError

// Event EventTemperatureInRange not handled in state FapError

// Event EventNoCalibration not handled in state FapError

// Event EventSelfTestOk not handled in state FapError

// Event EventCannotConnectToServer not handled in state FapError

// Event EventConnectedToServer not handled in state FapError

// Event EventNotOperationalTimeout not handled in state FapError

// Event EventTransmitterEnabled not handled in state FapError

// Event EventTransmitterDisabled not handled in state FapError

// State FapError has no deferred events.

// Event EventMapLoaded deferred in state PowerOnSelfTest

/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
void LedFsm::PowerOnSelfTest::InjectEventTemperatureOutOfRange(
    void* event
    )
{
    {
        mFsm.mState->Exit();
        mFsm.mState->Exit();
        mFsm.mWrongTemperature.Entry();
    }
}

// Event EventTemperatureInRange not handled in state PowerOnSelfTest

/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
void LedFsm::PowerOnSelfTest::InjectEventNoCalibration(
    void* event
    )
{
    {
        mFsm.mState->Exit();
        mFsm.mState->Exit();
        mFsm.mFapError.Entry();
    }
}

/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
void LedFsm::PowerOnSelfTest::InjectEventSelfTestOk(
    void* event
    )
{
    {
        mFsm.mState->Exit();
        mFsm.mConnectToServer.Entry();
    }
}

// Event EventCannotConnectToServer deferred in state PowerOnSelfTest

// Event EventConnectedToServer deferred in state PowerOnSelfTest

// Event EventNotOperationalTimeout deferred in state PowerOnSelfTest

// Event EventTransmitterEnabled deferred in state PowerOnSelfTest

// Event EventTransmitterDisabled deferred in state PowerOnSelfTest

/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
bool LedFsm::PowerOnSelfTest::DeferEvent( EventId eventId ) const
{
    switch( eventId )
    {
        case LedFsm::FSM_EVENT_EventMapLoaded:
            return true;

        case LedFsm::FSM_EVENT_EventCannotConnectToServer:
            return true;

        case LedFsm::FSM_EVENT_EventConnectedToServer:
            return true;

        case LedFsm::FSM_EVENT_EventNotOperationalTimeout:
            return true;

        case LedFsm::FSM_EVENT_EventTransmitterEnabled:
            return true;

        case LedFsm::FSM_EVENT_EventTransmitterDisabled:
            return true;


        default:
            return false;
    }
}

// Event EventMapLoaded deferred in state ConnectToServer

/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
void LedFsm::ConnectToServer::InjectEventTemperatureOutOfRange(
    void* event
    )
{
    {
        mFsm.mState->Exit();
        mFsm.mState->Exit();
        mFsm.mWrongTemperature.Entry();
    }
}

// Event EventTemperatureInRange not handled in state ConnectToServer

// Event EventNoCalibration not handled in state ConnectToServer

// Event EventSelfTestOk not handled in state ConnectToServer

/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
void LedFsm::ConnectToServer::InjectEventCannotConnectToServer(
    void* event
    )
{
    {
        mFsm.mState->Exit();
        mFsm.mNoConnectionToServer.Entry();
    }
}

/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
void LedFsm::ConnectToServer::InjectEventConnectedToServer(
    void* event
    )
{
    {
        mFsm.mState->Exit();
        mFsm.mNotOperational.Entry();
    }
}

// Event EventNotOperationalTimeout deferred in state ConnectToServer

// Event EventTransmitterEnabled deferred in state ConnectToServer

// Event EventTransmitterDisabled deferred in state ConnectToServer

/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
bool LedFsm::ConnectToServer::DeferEvent( EventId eventId ) const
{
    switch( eventId )
    {
        case LedFsm::FSM_EVENT_EventMapLoaded:
            return true;

        case LedFsm::FSM_EVENT_EventNotOperationalTimeout:
            return true;

        case LedFsm::FSM_EVENT_EventTransmitterEnabled:
            return true;

        case LedFsm::FSM_EVENT_EventTransmitterDisabled:
            return true;


        default:
            return false;
    }
}

// Event EventMapLoaded deferred in state NoConnectionToServer

/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
void LedFsm::NoConnectionToServer::InjectEventTemperatureOutOfRange(
    void* event
    )
{
    {
        mFsm.mState->Exit();
        mFsm.mState->Exit();
        mFsm.mWrongTemperature.Entry();
    }
}

// Event EventTemperatureInRange not handled in state NoConnectionToServer

// Event EventNoCalibration not handled in state NoConnectionToServer

// Event EventSelfTestOk not handled in state NoConnectionToServer

// Event EventCannotConnectToServer deferred in state NoConnectionToServer

/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
void LedFsm::NoConnectionToServer::InjectEventConnectedToServer(
    void* event
    )
{
    {
        mFsm.mState->Exit();
        mFsm.mNotOperational.Entry();
    }
}

// Event EventNotOperationalTimeout deferred in state NoConnectionToServer

// Event EventTransmitterEnabled deferred in state NoConnectionToServer

// Event EventTransmitterDisabled deferred in state NoConnectionToServer

/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
bool LedFsm::NoConnectionToServer::DeferEvent( EventId eventId ) const
{
    switch( eventId )
    {
        case LedFsm::FSM_EVENT_EventMapLoaded:
            return true;

        case LedFsm::FSM_EVENT_EventCannotConnectToServer:
            return true;

        case LedFsm::FSM_EVENT_EventNotOperationalTimeout:
            return true;

        case LedFsm::FSM_EVENT_EventTransmitterEnabled:
            return true;

        case LedFsm::FSM_EVENT_EventTransmitterDisabled:
            return true;


        default:
            return false;
    }
}

// Event EventMapLoaded deferred in state NotOperational

/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
void LedFsm::NotOperational::InjectEventTemperatureOutOfRange(
    void* event
    )
{
    {
        mFsm.mState->Exit();
        mFsm.mState->Exit();
        mFsm.mWrongTemperature.Entry();
    }
}

// Event EventTemperatureInRange not handled in state NotOperational

// Event EventNoCalibration not handled in state NotOperational

// Event EventSelfTestOk not handled in state NotOperational

// Event EventCannotConnectToServer deferred in state NotOperational

// Event EventConnectedToServer deferred in state NotOperational

/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
void LedFsm::NotOperational::InjectEventNotOperationalTimeout(
    void* event
    )
{
    {
        mFsm.mState->Exit();
        mFsm.mOperationalError.Entry();
    }
}

/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
void LedFsm::NotOperational::InjectEventTransmitterEnabled(
    void* event
    )
{
    {
        mFsm.mState->Exit();
        mFsm.mOperational.Entry();
    }
}

// Event EventTransmitterDisabled deferred in state NotOperational

/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
bool LedFsm::NotOperational::DeferEvent( EventId eventId ) const
{
    switch( eventId )
    {
        case LedFsm::FSM_EVENT_EventMapLoaded:
            return true;

        case LedFsm::FSM_EVENT_EventCannotConnectToServer:
            return true;

        case LedFsm::FSM_EVENT_EventConnectedToServer:
            return true;

        case LedFsm::FSM_EVENT_EventTransmitterDisabled:
            return true;


        default:
            return false;
    }
}

// Event EventMapLoaded deferred in state OperationalError

/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
void LedFsm::OperationalError::InjectEventTemperatureOutOfRange(
    void* event
    )
{
    {
        mFsm.mState->Exit();
        mFsm.mState->Exit();
        mFsm.mWrongTemperature.Entry();
    }
}

// Event EventTemperatureInRange not handled in state OperationalError

// Event EventNoCalibration not handled in state OperationalError

// Event EventSelfTestOk not handled in state OperationalError

// Event EventCannotConnectToServer deferred in state OperationalError

// Event EventConnectedToServer deferred in state OperationalError

// Event EventNotOperationalTimeout deferred in state OperationalError

/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
void LedFsm::OperationalError::InjectEventTransmitterEnabled(
    void* event
    )
{
    {
        mFsm.mState->Exit();
        mFsm.mOperational.Entry();
    }
}

// Event EventTransmitterDisabled deferred in state OperationalError

/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
bool LedFsm::OperationalError::DeferEvent( EventId eventId ) const
{
    switch( eventId )
    {
        case LedFsm::FSM_EVENT_EventMapLoaded:
            return true;

        case LedFsm::FSM_EVENT_EventCannotConnectToServer:
            return true;

        case LedFsm::FSM_EVENT_EventConnectedToServer:
            return true;

        case LedFsm::FSM_EVENT_EventNotOperationalTimeout:
            return true;

        case LedFsm::FSM_EVENT_EventTransmitterDisabled:
            return true;


        default:
            return false;
    }
}

// Event EventMapLoaded deferred in state Operational

/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
void LedFsm::Operational::InjectEventTemperatureOutOfRange(
    void* event
    )
{
    {
        mFsm.mState->Exit();
        mFsm.mState->Exit();
        mFsm.mWrongTemperature.Entry();
    }
}

// Event EventTemperatureInRange not handled in state Operational

// Event EventNoCalibration not handled in state Operational

// Event EventSelfTestOk not handled in state Operational

// Event EventCannotConnectToServer deferred in state Operational

// Event EventConnectedToServer deferred in state Operational

// Event EventNotOperationalTimeout deferred in state Operational

// Event EventTransmitterEnabled deferred in state Operational

/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
void LedFsm::Operational::InjectEventTransmitterDisabled(
    void* event
    )
{
    {
        mFsm.mState->Exit();
        mFsm.mNotOperational.Entry();
    }
}

/*** WARNING: Code AUTO-GENERATED from led.fsm. Do not edit! ***/
bool LedFsm::Operational::DeferEvent( EventId eventId ) const
{
    switch( eventId )
    {
        case LedFsm::FSM_EVENT_EventMapLoaded:
            return true;

        case LedFsm::FSM_EVENT_EventCannotConnectToServer:
            return true;

        case LedFsm::FSM_EVENT_EventConnectedToServer:
            return true;

        case LedFsm::FSM_EVENT_EventNotOperationalTimeout:
            return true;

        case LedFsm::FSM_EVENT_EventTransmitterEnabled:
            return true;


        default:
            return false;
    }
}

} // -namespace-
