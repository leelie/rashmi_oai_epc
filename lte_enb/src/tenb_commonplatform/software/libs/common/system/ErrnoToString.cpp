///////////////////////////////////////////////////////////////////////////////
//
// ErrnoToString.cpp
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

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ErrnoToString.h"

namespace threeway
{
const char *ErrnoToString (int errorNumber)
{
    return strerror (errorNumber);
}

}
