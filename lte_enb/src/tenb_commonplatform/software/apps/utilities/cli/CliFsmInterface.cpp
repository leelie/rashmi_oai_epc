///////////////////////////////////////////////////////////////////////////////
//
// CliApplication.h
//
// See header file for documentation.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////
#include <string.h>
#include <system/Trace.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "CliApplication.h"
#include "CliFsmInterface.h"

using namespace std;


void CliFsmInterface::FeedbackStopReason(shared_ptr<string> reason)
{
    if(!reason->empty())
    {
        TRACE_PRINTF_CONSOLE("%s\n",(*reason).c_str());
    }
}

void CliFsmInterface::FeedbackTimeout(void*)
{
    TRACE_PRINTF_CONSOLE("Timeout.");
}

void CliFsmInterface::FeedbackProgress(shared_ptr<CliExecuteCmdProgressInd> progressInd)
{
    const char * progressInfo = progressInd->GetProgressInfo();
    if(progressInfo)
    {
        TRACE_PRINTF_CONSOLE("%s",progressInfo);
    }
    else
    {
        TRACE_PRINTF_CONSOLE(".");
    }

    cout.flush();
}

void CliFsmInterface::FeedbackResponse(shared_ptr<CliExecuteCmdInd> commandInd)
{
    const char * resultString = commandInd->GetResult();

    if( resultString && strlen(resultString) )
    {
        TRACE_PRINTF_CONSOLE("%s",commandInd->GetResult());
        cout.flush();
    }
}

void CliFsmInterface::FeedbackCommandRejected(shared_ptr<CliCommand> c)
{
    CliCmdFile cliCmdFile( c->GetCommand().c_str() );

    if( cliCmdFile.found() )
    {
        TRACE_PRINTF_CONSOLE("%s:  syntax error.\n\tUsage: <ns>.%s",c->GetCommand().c_str(),cliCmdFile.GetShortDescription().c_str());
    }
    else
    {
          TRACE_PRINTF_CONSOLE("%s: : command not recognised.",c->GetCommand().c_str());
    }
}

void CliFsmInterface::SendCommandReq(shared_ptr<CliCommand> c)
{
    CliApplication & app = CliApplication::GetInstance();

    CliCmdFile cliCmdFile( c->GetCommand().c_str() );

    MessagingEntity targetEntity = cliCmdFile.GetMessagingEntity();

    string commandWithNamespace = c->GetCommand();
    string commandLessNamespace = commandWithNamespace.substr( commandWithNamespace.find_first_of('.') + 1 );

    CliExecuteCmdReq cliExecuteCmdReq( commandLessNamespace.c_str(), c->GetArguments().c_str());

    TRACE_PRINTF("Sending %s to %s", cliExecuteCmdReq.ToString().c_str(), MessagingEntityToString(targetEntity) );

    app.SendMessage(cliExecuteCmdReq, targetEntity, ENTITY_CLI);
}

// Entry/Exit
void CliFsmInterface::UserIoThreadRunningEntry()
{
    m_input->StartCommandLineInputThread();
}

void CliFsmInterface::UserIoThreadRunningExit()
{
    m_input->StopCommandLineInputThread();
}

void CliFsmInterface::AwaitCommandEntry()
{
    if (CliApplication::static_PreventTerminationOnIdle == false)
    {
        RSYS_ASSERT(m_timerId == NULL_TIMER);
        m_timerId = CliApplication::GetInstance().CreateTimer("CliIdleTimer", TimerEngineInterface::MinutesToTicks(5) );
    }

    m_input->GetNextCommand( GetPrompt() );
}

void CliFsmInterface::AwaitCommandExit()
{
    if (CliApplication::static_PreventTerminationOnIdle == false)
    {
        RSYS_ASSERT(m_timerId != NULL_TIMER);
        CliApplication::GetInstance().DeleteTimer( m_timerId );
    }
    m_timerId = NULL_TIMER;
}

void CliFsmInterface::CommandInProgressEntry()
{
    RSYS_ASSERT(m_timerId == NULL_TIMER);

    m_timerId = CliApplication::GetInstance().CreateTimer("CliCommandTimer", TimerEngineInterface::SecondsToTicks(commandTimelimit) );
}

void CliFsmInterface::CommandInProgressExit()
{
    RSYS_ASSERT(m_timerId != NULL_TIMER);

    CliApplication::GetInstance().DeleteTimer( m_timerId );

    m_timerId = NULL_TIMER;
}

void CliFsmInterface::QuittingEntry()
{
    TRACE_PRINTF_CONSOLE("Bye.\n");

    exit(0);
}

// Guard Conditions
bool CliFsmInterface::QueryCommandEmpty(shared_ptr<CliCommand> command)
{
    return command->empty();
}

bool CliFsmInterface::QueryQuitCommanded(shared_ptr<CliCommand> command)
{
    bool quit = (command->GetCommand() == "quit") || (command->GetCommand() == "exit") || (command->GetCommand() == "q");

    return quit;
}

bool CliFsmInterface::CommandLineParser(shared_ptr<CliCommand> command)
{
    return CliApplication::GetInstance().ValidateCommand( command->GetCommand(), command->GetArguments() );
}


