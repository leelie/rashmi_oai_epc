///////////////////////////////////////////////////////////////////////////////
//
// ValidatorQOffsetFrequency.h
//
// A validator for QOffsetFrequency.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __ValidatorQOffsetFrequency_h_
#define __ValidatorQOffsetFrequency_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include "ValidatorStringArray.h"

///////////////////////////////////////////////////////////////////////////////
// Functions / Classes
///////////////////////////////////////////////////////////////////////////////

class ValidatorQOffsetFrequency: public ValidatorStringArray
{
public:

    ValidatorQOffsetFrequency() {};
    virtual ~ValidatorQOffsetFrequency() {};

    virtual bool ValidateStringArray(const std::vector<std::string>& value, u32 minLength, u32 maxLength, s32 minValue, s32 maxValue, u32 maxInstances, ValidationFailureDescriptor& failureDescriptor);
};

#endif