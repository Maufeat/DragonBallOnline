/*****************************************************************************
 *
 * File			: LogInStage.h
 * Author		: HyungSuk, Jang
 * Copyright	: (주)NTL
 * Date			: 2005. 8. 17	
 * Abstract		: Login stage class
 *****************************************************************************
 * Desc         : 
 *
 *****************************************************************************/

#ifndef __LOGIN_STAGE_H__
#define __LOGIN_STAGE_H__

#include "NtlStage.h"
#include "ceventhandler.h"
#include "eventtimer.h"

#include "NtlStage.h"
#include "ceventhandler.h"
#include "eventtimer.h"

#include "NtlPLWorldEntity.h"
#include "NtlPLObject.h"
#include "NtlPLSky.h"
#include "NtlPLCharacter.h"
#include "CharGuiGroup.h"
#include "NtlSobAvatar.h"

#include "DboEvent.h"
#include "InputHandler.h"

class CLogInGuiGroup;
class CLogInStageState;

class CLogInStage : public CNtlStage, public RWS::CEventHandler
{
#define dRACE_NONE				RACE_COUNT

#define dCAMERA_STEP_DISTANCE	0.1f
#define dCAMERA_MOVE_TIME		0.1f

	struct sCameraData
	{
		RwV3d		v3Pos;
	};

	enum eCharHeightType
	{
		CHT_CHILD,
		CHT_ADULT,

		NUM_CHT
	};

	enum eZoomLevel
	{
		ZL_ZOOM_OUT,
		ZL_ZOOM_IN,

		NUM_ZL
	};

	struct sCameraZoom
	{
		RwReal				fElapsed;
		RwV3d				v3CameraSrcPos;
		RwV3d				v3CameraDestPos;
		RwV3d				v3CameraSrcDir;
		RwV3d				v3CameraDestDir;

		sCameraZoom()
			:fElapsed(0.f)
		{}
	};

private:

	RwBool				m_bAutoLogIn;
	RwV3d				m_vAvatarPos;
	RwV3d				m_vCameraPos;							// Camera Position
	RwV3d				m_vCameraPosAt;							// Camera가 보는 위치				
	CNtlPLWorldEntity	*m_pWorldEntity;						// Main World
	RwBool				m_bWorldAddCamera;						// World Add/Remove
	CLogInStageState	*m_pState;
	CLogInGuiGroup		*m_pGuiGroup;


	// 마우스 휠 스크롤에 따라 자연스러운 반응을 하기 위해 모든 휠 메세지 저장
	std::list<sCameraZoom>	m_listZoomMode;
	RwReal					m_fReservatedZoomStep;
	RwReal					m_fTotalZoomStep;
	RwReal					m_fTotalDistance;
	RwReal					m_fTotalDirDistance;

	sCameraData				m_CameraData[RACE_COUNT + 1][NUM_CHT][NUM_ZL];
	RwV3d					m_v3Dir[RACE_COUNT + 1][NUM_CHT][NUM_ZL];

public:

	CLogInStage(const char *pStageName);
	~CLogInStage();

	virtual bool Create(void);
	virtual void Destroy(void);

	virtual void HandleEvents(RWS::CMsg &pMsg);

// event handler
private:

	void EventProcUpdateTick(RwReal fElapsed);
	void LogInServerConnect(RWS::CMsg &pMsg);
	void LobbyServerConnect(RWS::CMsg &pMsg);
	void LoginStageStateEnter(RWS::CMsg &pMsg);
	void LoginStageStateExit(RWS::CMsg &pMsg);
	void LogInStageTimeOutEventHandler(RWS::CMsg &msg);
	void LogInMessageEventHandler(RWS::CMsg &msg);
	void CreateBackGroundStage();
	void TeleportStage();													//SetUpDefaultCamerabyRace에 의해서 설정된 곳으로 Teleport
																			//Teleport시 로딩이 일어난다.
	void DestroyBackGroundStage();

public:
	int	ActionGameExit(void);	
};

#endif