#ifndef FNTPSETSAMPLEMODECNF_H_
#define FNTPSETSAMPLEMODECNF_H_
///////////////////////////////////////////////////////////////////////////////
//
// FNTPSetSampleModeCnf.h
//
// Implementation of the FNTPSetSampleModeCnf message.
//
// Copyright � 3Way Networks Ltd
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <3waytypes.h>
#include <string>
#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

//////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Message Constants
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Message Structures
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Typedefs
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////
namespace threeway
{


class FNTPSetSampleModeCnf : public threeway::Serialisable
{
    static const u32 MESSAGE_DATA_LEN = 1;
public :
    FNTPSetSampleModeCnf():m_success(false){};
    FNTPSetSampleModeCnf(bool success):m_success(success) {};
    ~FNTPSetSampleModeCnf() {};
    virtual u32  GetSerialisationId() const {return(SERIALISATION_ID_FNTP_SET_SAMPLE_MODE_CNF);};
    virtual s32  Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen);
    bool GetSuccess() {return(m_success);}
    /**
     * Convert to string for debug.
     */
    virtual std::string ToString() const;
private:
    bool m_success;
};

}

#endif /*FNTPSETSAMPLEMODECNF_H_*/