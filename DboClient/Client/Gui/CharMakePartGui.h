/******************************************************************************
* File			: CharMakePartGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2007. 10. 10
* Abstract		: 
*****************************************************************************
* Desc			: ĳ���͸� ����� ���� ĳ������ �� �κ��� �����ϴ� Ŭ����
*****************************************************************************/

#pragma once

#include <list>

// core
#include "ceventhandler.h"

// gui
#include "gui_button.h"

// presentation
#include "NtlPLGui.h"

// simulation
#include "Inputhandler.h"

// dbo
#include "Windowby3.h"
#include "SlotGui.h"
#include "CharMakeDisplayPart.h"

class CCharCreateGuiGui;


class CCharMakePartGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	enum eAttiribute
	{
		ATTIRIBUTE_RACE,
		ATTIRIBUTE_CLASS,
		ATTIRIBUTE_SEX,		
		ATTIRIBUTE_HAIR,
		ATTIRIBUTE_HAIR_COLOR,
		ATTIRIBUTE_FACE,
		ATTIRIBUTE_SKIN,		

		ATTIRIBUTE_NUM
	};

#define dNUM_LEFT_RIGHT_BUTTONS			(4)

	struct sCHAR_ATTRIBUTE
	{
		RwUInt8				byValue;		///< ���� ���õ� ��
		RwUInt8				byPostValue;	///< ������ ���õ� ��
		RwUInt8				byMaxValue;

		VOID Select(RwUInt8 byIndex)
		{
			byPostValue	= byValue;
			byValue		= byIndex;
		}

		RwUInt8 GetMaxValue()
		{
			return byMaxValue;
		}
	};

	CCharMakePartGui(const RwChar* pName);
	virtual ~CCharMakePartGui();

	RwBool		Create(CCharCreateGuiGui* pCreateGui);
	VOID		Destroy();

	VOID		SetPosition(RwInt32 iXPos, RwInt32 iYPos);

protected:
	CCharMakePartGui() {}
	virtual VOID	HandleEvents( RWS::CMsg &msg );

	VOID			EnableButtons(bool bEnable);
	VOID			UpdateAttribute();
	VOID			SetAttribute(RwUInt8 byAttribute, RwUInt8 byIndex);
	VOID			CheckEnableButton();
	VOID			ChangeModel(RwBool bSetDefaultCamera);

	VOID			CreateCharacter();

	RwUInt8			ConverIndexToClass(RwUInt8 byIndex);
	RwUInt8			ConverIndexToGenderbyRace(RwInt32 iRace);

	VOID			OnClick_RaceButton(gui::CComponent* pComponent);
	VOID			OnClick_ClassButton(gui::CComponent* pComponent);
	VOID			OnClick_SexButton(gui::CComponent* pComponent);
	VOID			OnClick_LeftButton(gui::CComponent* pComponent);
	VOID			OnClick_RightButton(gui::CComponent* pComponent);
	VOID			OnClick_RendomButton(gui::CComponent* pComponent);

	VOID			OnMove(RwInt32 iOldX, RwInt32 iOldY);
	VOID			OnPaint();
	VOID			OnPostPaint();

protected:
	gui::CSlot			m_slotRendomButton;
	gui::CSlot			m_slotMove;
	gui::CSlot			m_slotPaint;
	gui::CSlot			m_slotPostPaint;

	CWindowby3			m_Background_UP;	///< ��� ���
	CWindowby3			m_Background_DOWN;	///< ��� �ϴ�

	CSurfaceGui			m_srfTitleText;		///< Title text	

	gui::CButton*		m_pRendomButton;	///< �ڵ� ���� ��ư

	CCharCreateGuiGui*	m_pCreateGui;

	sDISPLAY_PARTS*		m_aptAttributeDisplay[ATTIRIBUTE_NUM];
	sCHAR_ATTRIBUTE		m_atAttributeChar[ATTIRIBUTE_NUM];
};