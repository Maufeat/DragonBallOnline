#include "precomp_dboclient.h"
#include "LogInStage.h"

// shared
#include "NtlResultCode.h"

// network
#include "NtlClientNet.h"

// core
#include "NtlDebug.h"
#include "NtlEventQueue.h"
#include "NtlSystemInfo.h"

// simulation
#include "NtlNetSender.h"
#include "InputActionMap.h"
#include "NtlStorageManager.h"

// presentation
#include "NtlPLResourcePack.h"
#include "NtlCameraManager.h"

// dbo
#include "DboDef.h"
#include "DboGlobal.h"
#include "DboEvent.h"
#include "DboEventGenerator.h"
#include "DisplayStringDef.h"
#include "DisplayStringManager.h"
#include "LogInGuiGroup.h"
#include "LogInStageState.h"
#include "AlarmManager.h"
#include "CharStageState.h"

#include "DboApplication.h"
#include "MoviePlayer.h"

namespace
{
// zoom mode
#define dZOOM_NONE				0
#define dZOOM_IN				1
#define dZOOM_OUT				2
};

CLogInStage::CLogInStage(const char *pStageName)
:CNtlStage(pStageName),
m_pWorldEntity(NULL),
m_bWorldAddCamera(FALSE),
m_bAutoLogIn(FALSE),
m_pState(NULL),
m_pGuiGroup(NULL)
{
	m_listZoomMode.clear();

	// human child
	m_CameraData[RACE_HUMAN][CHT_CHILD][ZL_ZOOM_OUT].v3Pos.x = -347.356f;
	m_CameraData[RACE_HUMAN][CHT_CHILD][ZL_ZOOM_OUT].v3Pos.y = 52.825f;
	m_CameraData[RACE_HUMAN][CHT_CHILD][ZL_ZOOM_OUT].v3Pos.z = 325.413f;

	m_CameraData[RACE_HUMAN][CHT_CHILD][ZL_ZOOM_IN].v3Pos.x = -348.561f;
	m_CameraData[RACE_HUMAN][CHT_CHILD][ZL_ZOOM_IN].v3Pos.y = 52.54f;
	m_CameraData[RACE_HUMAN][CHT_CHILD][ZL_ZOOM_IN].v3Pos.z = 326.744f;

	m_v3Dir[RACE_HUMAN][CHT_CHILD][ZL_ZOOM_OUT].x = -348.027f;
	m_v3Dir[RACE_HUMAN][CHT_CHILD][ZL_ZOOM_OUT].y = 52.895f;
	m_v3Dir[RACE_HUMAN][CHT_CHILD][ZL_ZOOM_OUT].z = 326.154f;

	m_v3Dir[RACE_HUMAN][CHT_CHILD][ZL_ZOOM_IN].x = -349.232f;
	m_v3Dir[RACE_HUMAN][CHT_CHILD][ZL_ZOOM_IN].y = 52.61f;
	m_v3Dir[RACE_HUMAN][CHT_CHILD][ZL_ZOOM_IN].z = 327.485f;

	// human adult
	m_CameraData[RACE_HUMAN][CHT_ADULT][ZL_ZOOM_OUT]
		= m_CameraData[RACE_HUMAN][CHT_CHILD][ZL_ZOOM_OUT];

	m_CameraData[RACE_HUMAN][CHT_ADULT][ZL_ZOOM_IN].v3Pos.x = -348.71f;
	m_CameraData[RACE_HUMAN][CHT_ADULT][ZL_ZOOM_IN].v3Pos.y = 53.17f;
	m_CameraData[RACE_HUMAN][CHT_ADULT][ZL_ZOOM_IN].v3Pos.z = 326.908f;

	m_v3Dir[RACE_HUMAN][CHT_ADULT][ZL_ZOOM_OUT]
		= m_v3Dir[RACE_HUMAN][CHT_CHILD][ZL_ZOOM_OUT];

	m_v3Dir[RACE_HUMAN][CHT_ADULT][ZL_ZOOM_IN].x = -349.381f;
	m_v3Dir[RACE_HUMAN][CHT_ADULT][ZL_ZOOM_IN].y = 53.24f;
	m_v3Dir[RACE_HUMAN][CHT_ADULT][ZL_ZOOM_IN].z = 327.649f;

	// namek child
	m_CameraData[RACE_NAMEK][CHT_CHILD][ZL_ZOOM_OUT].v3Pos.x = 474.044f;
	m_CameraData[RACE_NAMEK][CHT_CHILD][ZL_ZOOM_OUT].v3Pos.y = 52.802f;
	m_CameraData[RACE_NAMEK][CHT_CHILD][ZL_ZOOM_OUT].v3Pos.z = 297.184f;

	m_CameraData[RACE_NAMEK][CHT_CHILD][ZL_ZOOM_IN].v3Pos.x = 473.084f;
	m_CameraData[RACE_NAMEK][CHT_CHILD][ZL_ZOOM_IN].v3Pos.y = 52.45f;
	m_CameraData[RACE_NAMEK][CHT_CHILD][ZL_ZOOM_IN].v3Pos.z = 298.589f;

	m_v3Dir[RACE_NAMEK][CHT_CHILD][ZL_ZOOM_OUT].x = 473.484f;
	m_v3Dir[RACE_NAMEK][CHT_CHILD][ZL_ZOOM_OUT].y = 52.872f;
	m_v3Dir[RACE_NAMEK][CHT_CHILD][ZL_ZOOM_OUT].z = 298.004f;

	m_v3Dir[RACE_NAMEK][CHT_CHILD][ZL_ZOOM_IN].x = 472.524f;
	m_v3Dir[RACE_NAMEK][CHT_CHILD][ZL_ZOOM_IN].y = 52.52f;
	m_v3Dir[RACE_NAMEK][CHT_CHILD][ZL_ZOOM_IN].z = 299.409f;

	// namek adult
	m_CameraData[RACE_NAMEK][CHT_ADULT][ZL_ZOOM_OUT]
		= m_CameraData[RACE_NAMEK][CHT_CHILD][ZL_ZOOM_OUT];

	m_CameraData[RACE_NAMEK][CHT_ADULT][ZL_ZOOM_IN].v3Pos.x = 472.856f;
	m_CameraData[RACE_NAMEK][CHT_ADULT][ZL_ZOOM_IN].v3Pos.y = 53.422f;
	m_CameraData[RACE_NAMEK][CHT_ADULT][ZL_ZOOM_IN].v3Pos.z = 298.924f;

	m_v3Dir[RACE_NAMEK][CHT_ADULT][ZL_ZOOM_OUT]
		= m_v3Dir[RACE_NAMEK][CHT_CHILD][ZL_ZOOM_OUT];

	m_v3Dir[RACE_NAMEK][CHT_ADULT][ZL_ZOOM_IN].x = 472.296f;
	m_v3Dir[RACE_NAMEK][CHT_ADULT][ZL_ZOOM_IN].y = 53.492f;
	m_v3Dir[RACE_NAMEK][CHT_ADULT][ZL_ZOOM_IN].z = 299.744f;


	// majin child
	m_CameraData[RACE_MAJIN][CHT_CHILD][ZL_ZOOM_OUT].v3Pos.x = 368.662f;
	m_CameraData[RACE_MAJIN][CHT_CHILD][ZL_ZOOM_OUT].v3Pos.y = 52.966f;
	m_CameraData[RACE_MAJIN][CHT_CHILD][ZL_ZOOM_OUT].v3Pos.z = -368.846f;

	m_CameraData[RACE_MAJIN][CHT_CHILD][ZL_ZOOM_IN].v3Pos.x = 367.596f;
	m_CameraData[RACE_MAJIN][CHT_CHILD][ZL_ZOOM_IN].v3Pos.y = 52.71f;
	m_CameraData[RACE_MAJIN][CHT_CHILD][ZL_ZOOM_IN].v3Pos.z = -367.788f;

	m_v3Dir[RACE_MAJIN][CHT_CHILD][ZL_ZOOM_OUT].x = 367.953f;
	m_v3Dir[RACE_MAJIN][CHT_CHILD][ZL_ZOOM_OUT].y = 53.001f;
	m_v3Dir[RACE_MAJIN][CHT_CHILD][ZL_ZOOM_OUT].z = -368.142f;

	m_v3Dir[RACE_MAJIN][CHT_CHILD][ZL_ZOOM_IN].x = 366.887f;
	m_v3Dir[RACE_MAJIN][CHT_CHILD][ZL_ZOOM_IN].y = 52.745f;
	m_v3Dir[RACE_MAJIN][CHT_CHILD][ZL_ZOOM_IN].z = -367.084f;

	// majin adult
	m_CameraData[RACE_MAJIN][CHT_ADULT][ZL_ZOOM_OUT]
		= m_CameraData[RACE_MAJIN][CHT_CHILD][ZL_ZOOM_OUT];

	m_CameraData[RACE_MAJIN][CHT_ADULT][ZL_ZOOM_IN].v3Pos.x = 367.859f;
	m_CameraData[RACE_MAJIN][CHT_ADULT][ZL_ZOOM_IN].v3Pos.y = 53.423f;
	m_CameraData[RACE_MAJIN][CHT_ADULT][ZL_ZOOM_IN].v3Pos.z = -368.049f;

	m_v3Dir[RACE_MAJIN][CHT_ADULT][ZL_ZOOM_OUT]
		= m_v3Dir[RACE_MAJIN][CHT_CHILD][ZL_ZOOM_OUT];

	m_v3Dir[RACE_MAJIN][CHT_ADULT][ZL_ZOOM_IN].x = 367.15f;
	m_v3Dir[RACE_MAJIN][CHT_ADULT][ZL_ZOOM_IN].y = 53.458f;
	m_v3Dir[RACE_MAJIN][CHT_ADULT][ZL_ZOOM_IN].z = -367.345f;

	// None character
	m_CameraData[dRACE_NONE][CHT_CHILD][ZL_ZOOM_OUT].v3Pos.x = -293.45f;
	m_CameraData[dRACE_NONE][CHT_CHILD][ZL_ZOOM_OUT].v3Pos.y = 53.12f;
	m_CameraData[dRACE_NONE][CHT_CHILD][ZL_ZOOM_OUT].v3Pos.z = -279.074f;

	m_CameraData[dRACE_NONE][CHT_CHILD][ZL_ZOOM_IN].v3Pos.x = -294.509f;
	m_CameraData[dRACE_NONE][CHT_CHILD][ZL_ZOOM_IN].v3Pos.y = 53.188f;
	m_CameraData[dRACE_NONE][CHT_CHILD][ZL_ZOOM_IN].v3Pos.z = -279.966f;

	m_v3Dir[dRACE_NONE][CHT_CHILD][ZL_ZOOM_OUT].x = -294.21f;
	m_v3Dir[dRACE_NONE][CHT_CHILD][ZL_ZOOM_OUT].y = 53.189f;
	m_v3Dir[dRACE_NONE][CHT_CHILD][ZL_ZOOM_OUT].z = -279.714f;

	m_v3Dir[dRACE_NONE][CHT_CHILD][ZL_ZOOM_IN].x = -295.269f;
	m_v3Dir[dRACE_NONE][CHT_CHILD][ZL_ZOOM_IN].y = 53.258f;
	m_v3Dir[dRACE_NONE][CHT_CHILD][ZL_ZOOM_IN].z = -280.606f;
}

CLogInStage::~CLogInStage()
{
}

bool CLogInStage::Create(void)
{
	NTL_FUNCTION("CLogInStage::Create" );

	// event 등록.
	LinkMsg(g_EventUpdateTick, 0);
	LinkMsg(g_EventLogInServerConnect, 0);
	LinkMsg(g_EventLobbyServerConnect, 0);
	LinkMsg(g_EventLogInStageStateEnter, 0);
	LinkMsg(g_EventLogInStageStateExit, 0);
	LinkMsg(g_EventLogInStageTimeOut, 0);
	LinkMsg(g_EventLoginMessage, 0);	

	m_pState	= NTL_NEW CLogInStageState;	

	m_pGuiGroup = NTL_NEW CLogInGuiGroup;
	if(!m_pGuiGroup->Create())
	{
		NTL_DELETE(m_pGuiGroup);
		NTL_RETURN(FALSE);
	}

	// avooo's commnet : 애플리케이션이 처음 실행될 때만 로고가 보이도록 하였다.
	//					 게임중 로그인 화면으로 돌아왔을 때 로고가 또 보이니 어색하다.
	static RwBool bFirstRunLogo = TRUE;
	if( bFirstRunLogo )
	{
		GetLogInStageState()->ChangeState(LOGIN_STATE_LOGO);

#ifndef NDEBUG
		RwBool bWindowMode = GetNtlStorageManager()->GetBoolData( dSTORAGE_GRAPHIC_WINDOW_MODE );
		RwInt32 nScreenWidth = GetNtlStorageManager()->GetIntData( dSTORAGE_GRAPHIC_SELECT_VIDEOWIDTH );
		RwInt32 nScreenHeight = GetNtlStorageManager()->GetIntData( dSTORAGE_GRAPHIC_SELECT_VIDEOHEIGHT );
		GetNtlStorageManager()->SetData( dSTORAGE_GRAPHIC_WINDOW_MODE, B2b(!NTL_DEBUG_WINDOW_MODE) );
		GetNtlStorageManager()->SetData( dSTORAGE_GRAPHIC_SELECT_VIDEOWIDTH, DEFAULT_SCREEN_WIDTH );
		GetNtlStorageManager()->SetData( dSTORAGE_GRAPHIC_SELECT_VIDEOHEIGHT, DEFAULT_SCREEN_HEIGHT );
		GetNtlStorageManager()->ApplyStorageType( eNTL_STORAGE_GRAPHIC, eNTL_STORAGE_APPLY_ALL );
		GetNtlStorageManager()->SetData( dSTORAGE_GRAPHIC_WINDOW_MODE, B2b(bWindowMode) );
		GetNtlStorageManager()->SetData( dSTORAGE_GRAPHIC_SELECT_VIDEOWIDTH, nScreenWidth );
		GetNtlStorageManager()->SetData( dSTORAGE_GRAPHIC_SELECT_VIDEOHEIGHT, nScreenHeight );
#else
		GetNtlStorageManager()->ApplyStorageType( eNTL_STORAGE_GRAPHIC, eNTL_STORAGE_APPLY_ALL );		
#endif

		GetNtlStorageManager()->ApplyStorageType( eNTL_STORAGE_SOUND, eNTL_STORAGE_APPLY_ALL );


		bFirstRunLogo = !bFirstRunLogo;
	}
	else
	{
		GetLogInStageState()->ChangeState(LOGIN_STATE_SERVER_CONNECT);
	}

	GetInputActionMap()->LinkGameExit(this, &CLogInStage::ActionGameExit);
	
	NTL_RETURN(TRUE);
}

void CLogInStage::Destroy(void)
{
	NTL_FUNCTION("CLogInStage::Destroy" );

	CNtlPostEffectCamera::SetPostEffectFilters(POST_EFFECT_FILTER_NONE);

	// event 해제.
	UnLinkMsg(g_EventUpdateTick);
	UnLinkMsg(g_EventLogInServerConnect);
	UnLinkMsg(g_EventLobbyServerConnect);
	UnLinkMsg(g_EventLogInStageStateEnter);
	UnLinkMsg(g_EventLogInStageStateExit);
	UnLinkMsg(g_EventLogInStageTimeOut);
	UnLinkMsg(g_EventLoginMessage);


	if (m_bWorldAddCamera)
	{
		RpWorldRemoveCamera(CNtlPLGlobal::m_pRpWorld, CNtlPLGlobal::m_RwCamera);
		m_bWorldAddCamera = FALSE;
	}

	if (m_pWorldEntity)
	{
		GetSceneManager()->DeleteEntity(m_pWorldEntity);
		m_pWorldEntity = NULL;
	}

	if(m_pGuiGroup)
	{
		m_pGuiGroup->Destroy();
		NTL_DELETE(m_pGuiGroup);
	}

	if(m_pState)
	{
		NTL_DELETE(m_pState);
	}

	GetInputActionMap()->UnLinkGameExit();

	NTL_RETURNVOID();
}

void CLogInStage::DestroyBackGroundStage()
{
	if (m_bWorldAddCamera)
	{
		RpWorldRemoveCamera(CNtlPLGlobal::m_pRpWorld, CNtlPLGlobal::m_RwCamera);
		m_bWorldAddCamera = FALSE;
	}

	if (m_pWorldEntity)
	{
		GetSceneManager()->DeleteEntity(m_pWorldEntity);
		m_pWorldEntity = NULL;
	}
}

void CLogInStage::CreateBackGroundStage()
{
	_getcwd(dGET_WORLD_PARAM()->CurWorkingFolderName, 256);
	strcpy(dGET_WORLD_PARAM()->CurDefaultTexPath, dGET_WORLD_PARAM()->CurWorkingFolderName);
	strcat(dGET_WORLD_PARAM()->CurDefaultTexPath, "\\texture\\ntlwe\\");

	std::string str = "\\world\\";
	str += "DBO_Select_Character";

	strcpy(dGET_WORLD_PARAM()->WorldProjectFolderName, dGET_WORLD_PARAM()->CurWorkingFolderName);
	strcat(dGET_WORLD_PARAM()->WorldProjectFolderName, str.c_str());

	str += "\\";
	str += "#######.gwp";

	FILE* pFile = NULL;
	SPackResFileData sPackFileData;
	RwBool bPack = GetNtlResourcePackManager()->LoadTerrain(str.c_str(), sPackFileData);

	if (bPack)
	{
		pFile = fopen(sPackFileData.strPackFileName.c_str(), "rb");
		if (pFile)
			fseek(pFile, sPackFileData.uiOffset, SEEK_SET);
	}
	else
	{
		std::string strWorldFileName = ".";
		strWorldFileName += str;
		pFile = fopen(strWorldFileName.c_str(), "rb");
	}

	// create a global world param
	if (pFile)
	{
		LoadFileWorldState(dGET_WORLD_PARAM(), pFile);
		fclose(pFile);
	}

	DBO_ASSERT(dNTL_WORLD_VERSION_COMPARE(dGET_WORLD_PARAM()->WorldVer, dNTL_WORLD_VERSION), "invalid world resource version. world(" << dGET_WORLD_PARAM()->WorldProjectFolderName << ") support_version(" << dNTL_WORLD_VERSION << ") resource_version(" << dGET_WORLD_PARAM()->WorldVer << ")");

	m_pWorldEntity = static_cast<CNtlPLWorldEntity*>(GetSceneManager()->CreateEntity(PLENTITY_WORLD, "NtlWorld"));

	m_vAvatarPos.x = -296.22f;
	m_vAvatarPos.y = 52.477f;
	m_vAvatarPos.z = -281.39f;

	m_vCameraPos = m_CameraData[dRACE_NONE][CHT_CHILD][ZL_ZOOM_OUT].v3Pos;
	m_vCameraPosAt = m_v3Dir[dRACE_NONE][CHT_CHILD][ZL_ZOOM_OUT];

	m_pWorldEntity->CreateWorld(m_vAvatarPos);

	RpWorldAddCamera(CNtlPLGlobal::m_pRpWorld, CNtlPLGlobal::m_RwCamera);
	m_bWorldAddCamera = TRUE;

	GetNtlGameCameraManager()->SetFov(60.f);
}


void CLogInStage::TeleportStage()
{
	m_pWorldEntity->SetPortalPosition(m_vAvatarPos);
	m_pWorldEntity->SetPlayerPosition(m_vAvatarPos);
	m_pWorldEntity->Update(0.8f);
	API_PL_CameraLookAt(CNtlPLGlobal::m_RwCamera, &m_vCameraPos, &m_vCameraPosAt);
}

void CLogInStage::HandleEvents(RWS::CMsg &pMsg)
{
	if(pMsg.Id == g_EventUpdateTick)
	{
		float fElapsed = *reinterpret_cast<float*>(pMsg.pData);
		EventProcUpdateTick(fElapsed);
	}
	else if(pMsg.Id == g_EventLogInServerConnect)
	{
		LogInServerConnect(pMsg);
	}
	else if(pMsg.Id == g_EventLobbyServerConnect)
	{
		LobbyServerConnect(pMsg);
	}
	else if(pMsg.Id == g_EventLogInStageStateEnter)
	{
		LoginStageStateEnter(pMsg);
	}
	else if(pMsg.Id == g_EventLogInStageStateExit)
	{
		LoginStageStateExit(pMsg);
	}
	else if(pMsg.Id == g_EventLogInStageTimeOut)
	{
		LogInStageTimeOutEventHandler(pMsg);
	}
	else if(pMsg.Id == g_EventLoginMessage)
	{
		LogInMessageEventHandler(pMsg);
	}
}

void CLogInStage::EventProcUpdateTick(RwReal fElapsed)
{
	GetLogInStageState()->Update(fElapsed);
}

void CLogInStage::LogInServerConnect(RWS::CMsg &pMsg)
{
	SDboEventServerConnect *pConnect = reinterpret_cast<SDboEventServerConnect*>( pMsg.pData );

	if(pConnect->byConnectType == SERVER_CONNECT_TYPE_CONNENCT_SUCCESS)
	{
		GetLogInStageState()->ChangeState(LOGIN_STATE_IDLE);
	}
	else if(pConnect->byConnectType == SERVER_CONNECT_TYPE_CONNENCT_FAIL)
	{
		GetLogInStageState()->ChangeState(LOGIN_STATE_SERVER_CONNECT_FAIL);
		GetAlarmManager()->AlarmMessage( DST_ACCOUNT_SERVER_CONNECT_FAIL );
	}
	else if(pConnect->byConnectType == SERVER_CONNECT_TYPE_CONNENCT_DISCONNECT)
	{
		GetAlarmManager()->AlarmMessage( DST_SERVER_DISCONNECT );
	}
}

void CLogInStage::LobbyServerConnect(RWS::CMsg &pMsg)
{
	SDboEventServerConnect *pConnect = reinterpret_cast<SDboEventServerConnect*>( pMsg.pData );

	if( pConnect->byConnectType == SERVER_CONNECT_TYPE_CONNENCT_SUCCESS )
	{
		GetLogInStageState()->ChangeState(LOGIN_STATE_CHAR_SERVER_LOGIN);
	}
	else if( pConnect->byConnectType == SERVER_CONNECT_TYPE_CONNENCT_FAIL )
	{
		m_bAutoLogIn = TRUE;
		GetLogInStageState()->ChangeState(LOGIN_STATE_CHAR_SERVER_CONNECT);
	}
}

void CLogInStage::LoginStageStateEnter(RWS::CMsg &pMsg)
{
	SDboEventLogInStageStateEnter *pStageStateEnter = reinterpret_cast<SDboEventLogInStageStateEnter*>(pMsg.pData);

	ELogInStageState eState = (ELogInStageState)pStageStateEnter->byState;

	switch(eState)
	{
	case LOGIN_STATE_LOGO:
		break;
	case LOGIN_STATE_SERVER_CONNECT:
		{

			CreateBackGroundStage();
			TeleportStage();

			// account server connect...
			SConfigData *pConfigData = GetDboGlobal()->GetConfigData();  
			SConnectData *pConnectData = GetDboGlobal()->GetConnectData();  
			CNtlClientNet *pNet = GetDboGlobal()->GetNetwork(); 


#ifdef NET_SERVER_SYNC
			pNet->Connect( (char*)pConfigData->strAddr.c_str(), (WORD)pConfigData->dwPort, &pConnectData->sAuthCon.hSocket, true, NETCLIENT_ENCODE_NONE );
#else
            CLoginPacketGenerator *pLoginPackGenerator = CDboGlobal::GetInstance()->GetLoginPacketGenerator(); 
            CNtlNetSender *pNetSender = pLoginPackGenerator->GetNetSender();
			pNetSender->SetData(INVALID_HSERVER, NULL); 
			GetLogInStageState()->ChangeState(LOGIN_STATE_IDLE);
#endif
		}
		break;
	case LOGIN_STATE_SERVER_CONNECT_FAIL:
		break;
	case LOGIN_STATE_IDLE:

		if(m_bAutoLogIn)
		{
			// 서버로 로그인 요청
			SUserData *pUserData = GetDboGlobal()->GetUserData();
			const BYTE* pMacAddress = GetSystemMacAddress();

			if( pMacAddress )
			{
				GetDboGlobal()->GetLoginPacketGenerator()->SendLonInReq(pUserData->wchUserID, pUserData->wchPassword, CLIENT_LVER, CLIENT_RVER, pMacAddress); 
				GetLogInStageState()->ChangeState(LOGIN_STATE_LOGINREQ);
			}
			else
			{
				GetAlarmManager()->AlarmMessage(L"Fail read MAC address", CAlarmManager::ALARM_TYPE_LOBBY_MSGBOX, MBW_POST_QUIT_MESSAGE);
			}
		}
		break;
	case LOGIN_STATE_LOGINREQ:
		break;
	case LOGIN_STATE_CHAR_SERVER_CONNECT:
		{
#ifdef NET_SERVER_SYNC

			SConnectData *pConData = GetDboGlobal()->GetConnectData();  
			CNtlClientNet *pNet = GetDboGlobal()->GetNetwork(); 

			SCharServerInfo sCharServerInfo;
			RwBool bExist = pConData->PopCharacterServer(&sCharServerInfo);
			if(bExist)
				pNet->Connect( (char*)sCharServerInfo.chServerIP, sCharServerInfo.wServerPort, &pConData->sCharCon.hSocket, TRUE, NETCLIENT_ENCODE_NONE );
			else
			{
				GetAlarmManager()->AlarmMessage( DST_CHAR_SERVER_CONNECT_FAIL );
				GetLogInStageState()->ChangeState(LOGIN_STATE_SERVER_CONNECT_FAIL);
			}
#else
			CLobbyPacketGenerator *pLobbyPacketGenerator = GetDboGlobal()->GetLobbyPacketGenerator(); 
			CNtlNetSender *pNetSender = pLobbyPacketGenerator->GetNetSender();
			pNetSender->SetData(INVALID_HSERVER, NULL); 

			GetLogInStageState()->ChangeState(LOGIN_STATE_CHAR_SERVER_LOGIN);
#endif
		}
		break;
	}
}

void CLogInStage::LoginStageStateExit(RWS::CMsg &pMsg)
{
}

void CLogInStage::LogInStageTimeOutEventHandler(RWS::CMsg &msg)
{
	SDboEventLogInStageTimeOut *pStageTimeOut = reinterpret_cast<SDboEventLogInStageTimeOut*>(msg.pData);

	ELogInStageState eState = (ELogInStageState)pStageTimeOut->byState;
	switch(eState)
	{
	case LOGIN_STATE_LOGO:
		break;
	case LOGIN_STATE_SERVER_CONNECT: 
		GetAlarmManager()->AlarmMessage( DST_ACCOUNT_SERVER_CONNECT_FAIL );
		break;
	case LOGIN_STATE_SERVER_CONNECT_FAIL:
		break;
	case LOGIN_STATE_IDLE:
		break;
	case LOGIN_STATE_LOGINREQ:
		GetAlarmManager()->AlarmMessage( AUTH_AUTHKEY_FAIL, TRUE );
		GetLogInStageState()->ChangeState(LOGIN_STATE_IDLE);
		break;
	case LOGIN_STATE_CHAR_SERVER_CONNECT:
		GetLogInStageState()->ChangeState(LOGIN_STATE_CHAR_SERVER_CONNECT);
		break;
	case LOGIN_STATE_CHAR_SERVER_LOGIN:
		GetAlarmManager()->AlarmMessage( CHARACTER_AUTHKEY_FAIL, TRUE );
		m_bAutoLogIn = FALSE;
		GetLogInStageState()->ChangeState(LOGIN_STATE_SERVER_CONNECT);
		break;
	}
}

void CLogInStage::LogInMessageEventHandler(RWS::CMsg &msg)
{
	SDboEventLoginMessage* pEvent = reinterpret_cast<SDboEventLoginMessage*>( msg.pData );

	switch(pEvent->byMessage)
	{
	case LOGIN_EVENT_FINISH_LOGO_PLAY:
		{
			Logic_SetOptionMovieStop();
			GetLogInStageState()->ChangeState(LOGIN_STATE_SERVER_CONNECT);
			break;
		}
	}
}

int CLogInStage::ActionGameExit(void)
{
	CDboApplication::GetInstance()->SetRenderEnable(TRUE);
	/*CDboApplication::GetInstance()->SetToggleScreenMode(TRUE);*/
	
	GetInputActionMap()->SetActive(FALSE);
	
	return TRUE;
}