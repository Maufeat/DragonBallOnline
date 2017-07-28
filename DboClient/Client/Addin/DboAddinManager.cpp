#include "precomp_dboclient.h"
#include "DboAddinManager.h"

#include "NtlDebug.h"
#include "NtlSLEvent.h"

// Devil
#include "il.h"

CDBOAddinManager* CDBOAddinManager::m_pInstance = NULL;

CDBOAddinManager::CDBOAddinManager() 
{
    LinkMsg(g_EventScreenShot);    
}

CDBOAddinManager::~CDBOAddinManager() 
{
    UnLinkMsg(g_EventScreenShot);
}

void CDBOAddinManager::Init() 
{
    if(!m_pInstance)
    {
        m_pInstance = NTL_NEW CDBOAddinManager();
        ilInit();
    }    
}

void CDBOAddinManager::ShutDown() 
{
    if(m_pInstance)
    {
        ilShutDown();
        NTL_DELETE(m_pInstance);
    }
}

void CDBOAddinManager::HandleEvents( RWS::CMsg &pMsg ) 
{
    if(pMsg.Id == g_EventScreenShot)
    {
        // After you've taken screenshots of the coming event carried on
        OnEventScreenShot(pMsg);
    }
}

void CDBOAddinManager::OnEventScreenShot( RWS::CMsg& pMsg ) 
{
    // Convert to jpg files saved as PNG.
    SNtlEventScreenShot* pData = (SNtlEventScreenShot*)pMsg.pData;
    std::string strOrgfileName, strDestFileName;
    strOrgfileName = pData->strFileName;
    strOrgfileName.erase(strOrgfileName.end() - 4, strOrgfileName.end());
    strDestFileName = strOrgfileName;
    strOrgfileName += ".bmp";
    strDestFileName += ".jpg";

    ilLoadImage(strOrgfileName.c_str());
    ilSaveImage(strDestFileName.c_str());

    DeleteFile(strOrgfileName.c_str());
}