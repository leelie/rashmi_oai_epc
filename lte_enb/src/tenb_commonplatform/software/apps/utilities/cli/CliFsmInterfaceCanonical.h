///////////////////////////////////////////////////////////////////////////////
//
// CliFsmInterfaceCanonical.h
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __CliFsmInterfaceCanonical_h_
#define __CliFsmInterfaceCanonical_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <boost/shared_ptr.hpp>
#include <system/Serialisable.h>

#include "CliFsmInterfaceStandard.h"

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace boost;

///////////////////////////////////////////////////////////////////////////////
// Local Constants
///////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Classes
/////////////////////////////////////////////////////////////////////////////////

class CliFsmInterfaceCanonical : public CliFsmInterfaceStandard
{
public:
    CliFsmInterfaceCanonical( shared_ptr<CliInput> input) :
        CliFsmInterfaceStandard( input )
    {}
    virtual ~CliFsmInterfaceCanonical() {}

    virtual void QuittingEntry();
    virtual void FeedbackCompletionResult(shared_ptr<CliExecuteCmdCnf> event);
    virtual void FeedbackProgress(shared_ptr<CliExecuteCmdProgressInd>) {};

};


#endif