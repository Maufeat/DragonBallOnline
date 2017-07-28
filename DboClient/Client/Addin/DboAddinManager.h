#pragma once
#include "ceventhandler.h"

/// Addin Managed class libraries
/// At present, managing the Devil for a screenshot.
class CDBOAddinManager : public RWS::CEventHandler
{
public:
    CDBOAddinManager();
    ~CDBOAddinManager();

    static void Init();
    static void ShutDown();

protected:
    virtual void			HandleEvents(RWS::CMsg &pMsg); 

    void    OnEventScreenShot(RWS::CMsg& pMsg);                 ///< The screenshot was taken, change the file after processing

protected:
    static CDBOAddinManager* m_pInstance;

};