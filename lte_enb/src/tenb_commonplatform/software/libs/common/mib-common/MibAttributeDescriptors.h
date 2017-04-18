///////////////////////////////////////////////////////////////////////////////
//
// MibAttributeDescriptors.h
//
// Structures used in autogenerated MIB code.
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibAttributeDescriptors_h_
#define __MibAttributeDescriptors_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Trace.h>
#include <MibAttributeId.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Forward Declarations
///////////////////////////////////////////////////////////////////////////////

class ValidatorU32;
class ValidatorU32Array;
class ValidatorS32;
class ValidatorS32Array;
class ValidatorString;
class ValidatorStringArray;

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

typedef enum MibAttributeTypeTag
{
    MIB_ATTRIBUTE_TYPE_U32,
    MIB_ATTRIBUTE_TYPE_U32ARRAY,
    MIB_ATTRIBUTE_TYPE_S32,
    MIB_ATTRIBUTE_TYPE_S32ARRAY,
    MIB_ATTRIBUTE_TYPE_STRING,
    MIB_ATTRIBUTE_TYPE_STRINGARRAY,
    MIB_ATTRIBUTE_TYPE_ENUM,
    MIB_ATTRIBUTE_TYPE_ENUMARRAY
} MibAttributeType;

typedef enum MibAttributeAccessClassTag
{
    MIB_ACCESS_READ_WRITE = 0,
    MIB_ACCESS_READ_ONLY,
    MIB_ACCESS_WRITE_ONCE
} MibAttributeAccessClass;

typedef enum MibAttributeStorageClassTag
{
    MIB_STORAGE_VOLATILE = 0,
    MIB_STORAGE_NON_VOLATILE
} MibAttributeStorageClass;

// Keep all the generic info together because this is a consecutively ordered list
// ...and hence lookups are much faster than the sparsely populated containers
typedef struct MibAttributeCommonDescriptorTag
{
    MibAttributeId          mibAttributeId;
    MibAttributeType        mibAttributeType;
    const char*             mibAttributeName;
    bool                    hasDefault;
    bool                    mandatoryOnCreate;
    u16                     schema;
} MibAttributeCommonDescriptor;

typedef struct MibAttributeU32DescriptorTag
{
    MibAttributeId          mibAttributeId;
    u32                     minValue;
    u32                     maxValue;
    u32                     defaultValue;
    ValidatorU32*           validator;
} MibAttributeU32Descriptor;

typedef struct MibAttributeU32ArrayDescriptorTag
{
    MibAttributeId          mibAttributeId;
    u32                     minValue;
    u32                     maxValue;
    ValidatorU32Array*      validator;
    u32                     defaultValue;
    u32                     maxInstances;
} MibAttributeU32ArrayDescriptor;

typedef struct MibAttributeS32DescriptorTag
{
    MibAttributeId          mibAttributeId;
    s32                     minValue;
    s32                     maxValue;
    s32                     defaultValue;
    ValidatorS32*           validator;
} MibAttributeS32Descriptor;

typedef struct MibAttributeS32ArrayDescriptorTag
{
    MibAttributeId          mibAttributeId;
    s32                     minValue;
    s32                     maxValue;
    ValidatorS32Array*      validator;
    s32                     defaultValue;
    u32                     maxInstances;
} MibAttributeS32ArrayDescriptor;

typedef struct MibAttributeStringDescriptorTag
{
    MibAttributeId          mibAttributeId;
    s32                     minLength;
    s32                     maxLength;
    const char *            defaultValue;
    ValidatorString*        validator;
} MibAttributeStringDescriptor;

typedef struct MibAttributeStringArrayDescriptorTag
{
    MibAttributeId          mibAttributeId;
    s32                     minLength;
    s32                     maxLength;
    s32                     minValue; /* min value for numeric value taken as string */
    s32                     maxValue; /* max value for numeric value taken as string */
    ValidatorStringArray*   validator;
    const char *            defaultValue;
    u32                     maxInstances;
} MibAttributeStringArrayDescriptor;

typedef struct MibObjectAttributeDescriptorTag
{
    MibAttributeId mibAttributeId;
    MibAttributeAccessClass     accessClass;
    MibAttributeStorageClass    storageClass;
} MibObjectAttributeDescriptor;

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

const char * getMibAttributeTypeName(MibAttributeType type);
const char * getMibAttributeAccessClassName(MibAttributeAccessClass accessClass);
const char * getMibAttributeStorageClassName(MibAttributeStorageClass storageClass);

/*** These functions will assert if they do not find the id */
const MibAttributeU32Descriptor* getMibAttributeU32Descriptor(MibAttributeId id);
const MibAttributeU32ArrayDescriptor* getMibAttributeU32ArrayDescriptor(MibAttributeId id);
const MibAttributeS32Descriptor* getMibAttributeS32Descriptor(MibAttributeId id);
const MibAttributeS32ArrayDescriptor* getMibAttributeS32ArrayDescriptor(MibAttributeId id);
const MibAttributeStringDescriptor* getMibAttributeStringDescriptor(MibAttributeId id);
const MibAttributeStringArrayDescriptor* getMibAttributeStringArrayDescriptor(MibAttributeId id);
const MibAttributeCommonDescriptor* getMibAttributeCommonDesc(MibAttributeId id);

const char * getMibAttributeName(MibAttributeId id);
MibAttributeType getMibAttributeType(MibAttributeId id);

#endif