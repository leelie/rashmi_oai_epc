///////////////////////////////////////////////////////////////////////////////
//
// 3 Way Networks Source File
//
///////////////////////////////////////////////////////////////////////////////
//
// NASPolishMaid.h
//
// Housekeeping thread, calling various virtuals that allow a user
// application to perform any periodic tidying and maintenance.  This is
// a bit of a avgue description, but I'm sure what I'll use it for right
// now!
//
// Copyright � 3 Way Networks, Ltd.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __NASPolishMaid_h_
#define __NASPolishMaid_h_

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Thread.h>

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

class NASApplication;

///////////////////////////////////////////////////////////////////////////////
// Class: NASPolishMaid
// Desc : Wake up every <user defined> period and call the NASApp class
//        virtual to allow periodic housekeeping to take place.
///////////////////////////////////////////////////////////////////////////////
class NASPolishMaid : public threeway::Thread  
{
public:
	// Construction / destruction.
	NASPolishMaid (NASApplication &nasApp, u32 cleaningPeriodInSeconds);
	virtual ~NASPolishMaid ();

private:

	// The actual thread implementation.
    virtual u32 ThreadProcedure ();

private:

	// Thread will wake every period below.  ** Time is SECONDS **
	u32 m_cleaningPeriod;

	// Callback on the NASApp class will be invoked when the timer expires.
	NASApplication &m_nasApp;
};



#endif
