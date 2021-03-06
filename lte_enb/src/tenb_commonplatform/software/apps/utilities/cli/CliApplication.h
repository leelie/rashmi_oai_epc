///////////////////////////////////////////////////////////////////////////////
//
// CliApplication.h
//
// CLI front-end application for talking to other apps that support CLIs.
// Provides console I/O for user.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CliApplication_h_
#define __CliApplication_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////
#include <string>
#include <string.h>
#include <set>
#include <sys/select.h>

#include <boost/shared_ptr.hpp>
#include <system/Serialisable.h>
#include <messaging/transport/SingleThreadedApplicationWithMessaging.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CliTypes.h"
#include "CliEvents.h"
#include "CliFsm.h"
#include "CliCommand.h"

using namespace std;
using namespace boost;

///////////////////////////////////////////////////////////////////////////////
// Local Constants
///////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Classes
/////////////////////////////////////////////////////////////////////////////////

/*
 * Application class
 */
class CliApplication: public threeway::SingleThreadedApplicationWithMessaging
{
private:
    // Is singleton so private constructor.
    CliApplication();

public:
    ~CliApplication();
    static CliApplication& GetInstance();

    static bool static_PreventTerminationOnIdle;

    int AppMain();

    /**
     * Handle timer expiry.
     */
    void HandleTimerExpiry(shared_ptr<TimerExpiry> );

    void HandleUserInputLine(shared_ptr<CliCommand>);

    void HandleTerminationSignal(void);

    void Init();

    /**
     * Member function to validate a command before it is dispatched.
     *
     * Returns false if command is not known
     * or the incorrect number of args supplied
     * or command in an inactive group.
     */
    bool ValidateCommand(const string& cmd, const string& args);

    bool m_detectedAnotherCliRunning;

    u16 GetLocalPort() const
    {
        return GetMessagingLocalPort();
    }

private:
    bool m_terminated;
    static CliApplication* s_instance;
	 void	ReadConfigFile(const char* configFile);

    void NewCommandGroup( const string & group )
    {
        m_groups.insert(group);
        TRACE_PRINTF("New command group %s.",group.c_str());
    }
    bool QueryCommandGroupActive( const string & group )
    {
        set<string>::const_iterator i = m_groups.find(group);

        bool found = (i != m_groups.end());

        return found;
    }
    set<string> m_groups;

    // Implement MessageHandler interface
    virtual bool MessageHandler(shared_ptr<threeway::MessageSerialisedData> & message);

    /**
     * Override and implement other event handling hook.
     */
    void HandleOtherEvent(shared_ptr<threeway::Queueable> event);

    void ParseCommandLineArguments();

    shared_ptr<CliFsm> m_fsm;

    // CLI handler functions used to implement local commands.
    static shared_ptr<CliResponse> CliCmdHelp(const CliArguments& argsIn) ;
    static shared_ptr<CliResponse> CliCmdNoKick(const CliArguments& argsIn);
    static shared_ptr<CliResponse> CliCmdNamespace(const CliArguments& argsIn) ;

    /*
     * Event/Message handler for incoming keys from input thread.
     */
    void HandleKeyEvent(CliAppNewKeyEvent keyEvent);

    /**
     * Member functions to process user commands.
     */
    void ProcessCommand(const string& cmd, const string& args);

    void ExitIfAnotherCliDetected();

    u32 GetSelectTimeout();
    shared_ptr<CliInputStdinInteractive> m_interactive;
    static const int oam_ret_zero = 0;
};

extern string & removeLeadingAndTrailingWhitespace( string & s );



#endif
