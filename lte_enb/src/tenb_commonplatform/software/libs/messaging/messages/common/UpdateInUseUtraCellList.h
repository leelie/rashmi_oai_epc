///////////////////////////////////////////////////////////////////////////////
//
// UpdateInUseUtraCellList.h
//
// Message sent to inform that eNodeB initial config is complete
//
// Copyright radisys Ltd
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __UpdateInUseUtraCellList_h_
#define __UpdateInUseUtraCellList_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <system/Serialisable.h>
#include <system/SerialisationIds.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Classes
///////////////////////////////////////////////////////////////////////////////

class UpdateInUseUtraCellList : public threeway::Serialisable
{
public:
    /**
     * Construction / destruction.
     */
    UpdateInUseUtraCellList();
    UpdateInUseUtraCellList(u32 msgType, void* data);
    virtual ~UpdateInUseUtraCellList() {};

    virtual u32 GetSerialisationId() const { return SERIALISATION_ID_UPDATE_UTRAINUSE_CELLLIST; }
    virtual s32 Serialise(u8* data, u32 dataMaxBytes) const;
    virtual bool DeSerialise(const u8* data, u32 dataLen) ;
     void *GetUtaCellCfg();
    virtual std::string ToString() const;

private:
    void *m_UtraCellCfg;
    u32   m_MsgType;
};

#endif
