// XTPReportBehavior.h: Declaration of the CXTPReportBehavior class.
//
// This file is a part of the XTREME REPORTCONTROL MFC class library.
// (c)1998-2011 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(__XTPREPORTBEHAVIOR_H__)
#define __XTPREPORTBEHAVIOR_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum XTPReportMouseButton
{
	xtpReportMouseButtonNone,
	xtpReportMouseButtonLeft,
	xtpReportMouseButtonMiddle,
	xtpReportMouseButtonRight
};


enum XTPReportMouseEvent
{
	xtpReportMouseEventButtonDown,
	xtpReportMouseEventButtonUp
};

enum XTPReportBehavior
{
	xtpReportBehaviorOutlook2003     = 0x00001100, // 11.0
	xtpReportBehaviorOutlook2007     = 0x00001200, // 12.0
	xtpReportBehaviorOutlook2010     = 0x00001400, // 14.0

	xtpReportBehaviorExcel2003       = 0x10001100, // 11.0
	xtpReportBehaviorExcel2007       = 0x10001200, // 12.0
	xtpReportBehaviorExcel2010       = 0x10001400, // 14.0

	//xtpReportBehaviorCodejock1300    = 0x20001300, // 13.0.0
	//xtpReportBehaviorCodejock1321    = 0x20001321, // 13.2.1
	//xtpReportBehaviorCodejock1330    = 0x20001330, // 13.3.0
	//xtpReportBehaviorCodejock1331    = 0x20001331, // 13.3.1
	xtpReportBehaviorCodejock1340    = 0x20001340, // 13.4.0
	xtpReportBehaviorCodejock1341    = 0x20001341, // 13.4.1
	xtpReportBehaviorCodejock1342    = 0x20001342, // 13.4.2
	xtpReportBehaviorCodejock1501    = 0x20001501, // 15.0.1
	xtpReportBehaviorCodejock1502    = 0x20001502, // 15.0.2
	xtpReportBehaviorCodejockDefault = 0x20000000
};


/////////////////////////////////////////////////////////////////////////////
// Key events
/////////////////////////////////////////////////////////////////////////////

class _XTP_EXT_CLASS CXTPReportBehaviorRowKeyDown
{

};

class _XTP_EXT_CLASS CXTPReportBehaviorRowKeyUp
{

};


/////////////////////////////////////////////////////////////////////////////
// Mouse events
/////////////////////////////////////////////////////////////////////////////

class _XTP_EXT_CLASS CXTPReportBehaviorRowModifier : public CXTPCmdTarget
{
public:

	CXTPReportBehaviorRowModifier();
	void Reset();

	BOOL bFocusRow;               // TRUE if the row gets the focus
	BOOL bFocusRowTemporarily;    // TRUE if the row gets the focus temporarily

	BOOL bSelectRow;              // TRUE if the row gets selected
	BOOL bSelectRowTemporarily;   // TRUE if the row gets selected temporarily
	BOOL bMultipleSelection;      // TRUE to enable multiple selection

	BOOL bKeepSelection;          // TRUE if multiple rows stay selected
	BOOL bKeepFocus;              //

protected:
};

class _XTP_EXT_CLASS CXTPReportBehaviorRowMouseButton : public CXTPCmdTarget
{
public:

	CXTPReportBehaviorRowMouseButton(
		XTPReportMouseButton button,
		XTPReportMouseEvent  event
		);
	virtual ~CXTPReportBehaviorRowMouseButton();

	void Reset();

public:

	CXTPReportBehaviorRowModifier *None;
	CXTPReportBehaviorRowModifier *Control;
	CXTPReportBehaviorRowModifier *Shift;

	BOOL bFocusColumn;            // TRUE if the column gets the focus
	BOOL bEnsureVisible;          // TRUE if the row gets visible

	BOOL bClick;                  // TRUE
	BOOL bContextMenu;            // TRUE if OnContextMenu / NM_RCLICK gets called.
	BOOL bCheckSelectedRows;      // TRUE

	BOOL bDragBegin;              // TRUE to begin drag
	BOOL bDragEnd;                // TRUE to end drag
	BOOL bDragSelectGroup;        // TRUE to select the entire group on drag

public:

	const XTPReportMouseButton m_button;
	const XTPReportMouseEvent  m_event;

protected:

};

class _XTP_EXT_CLASS CXTPReportBehaviorRowMouse : public CXTPCmdTarget
{
public:

	CXTPReportBehaviorRowMouse(XTPReportMouseEvent event);
	virtual ~CXTPReportBehaviorRowMouse();

	CXTPReportBehaviorRowMouseButton *Left;
	CXTPReportBehaviorRowMouseButton *Right;

protected:

};


class _XTP_EXT_CLASS CXTPReportBehaviorRow : public CXTPCmdTarget
{
public:
	CXTPReportBehaviorRow();
	virtual ~CXTPReportBehaviorRow();

public:
	CXTPReportBehaviorRowMouse *MouseDown;
	CXTPReportBehaviorRowMouse *MouseUp;

};


class _XTP_EXT_CLASS CXTPReportBehavior : public CXTPCmdTarget
{
public:

	CXTPReportBehavior(XTPReportBehavior behavior);
	virtual ~CXTPReportBehavior();

	void SetScheme(XTPReportBehavior behavior);

public:

	CXTPReportBehaviorRow *Row;
	CXTPReportBehaviorRow *GroupRow;


private:

	void SetSchemeOutlook();
	void SetSchemeExcel();
	void SetSchemeCodejock134x();
	void SetSchemeCodejock1501();
	void SetSchemeCodejock1502();
	void SetSchemeCodejockDefault();

	XTPReportBehavior m_scheme;      // The last set scheme

};

#endif //#if !defined(__XTPREPORTBEHAVIOR_H__)
