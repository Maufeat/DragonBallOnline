// XTPReportBehavior.cpp : implementation of the CXTPReportBehavior class.
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

#include "StdAfx.h"

#include "Common/XTPCustomHeap.h"

#include "XTPReportDefines.h"
#include "XTPReportBehavior.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif


CXTPReportBehaviorRow::CXTPReportBehaviorRow()
	: MouseDown(NULL)
	, MouseUp  (NULL)
{
	MouseDown = new CXTPReportBehaviorRowMouse(xtpReportMouseEventButtonDown);
	MouseUp   = new CXTPReportBehaviorRowMouse(xtpReportMouseEventButtonUp);

}

CXTPReportBehaviorRow::~CXTPReportBehaviorRow()
{
	SAFE_DELETE(MouseDown);
	SAFE_DELETE(MouseUp);
}


/////////////////////////////////////////////////////////////////////////////


CXTPReportBehaviorRowMouse::CXTPReportBehaviorRowMouse(
	XTPReportMouseEvent event)

	: Left (NULL)
	, Right(NULL)
{
	Left  = new CXTPReportBehaviorRowMouseButton(xtpReportMouseButtonLeft,  event);
	Right = new CXTPReportBehaviorRowMouseButton(xtpReportMouseButtonRight, event);

}

CXTPReportBehaviorRowMouse::~CXTPReportBehaviorRowMouse()
{
	SAFE_DELETE(Left);
	SAFE_DELETE(Right);
}




/////////////////////////////////////////////////////////////////////////////


CXTPReportBehavior::CXTPReportBehavior(XTPReportBehavior scheme)
	: Row     (NULL)
	, GroupRow(NULL)
	, m_scheme(scheme)
{
	Row      = new CXTPReportBehaviorRow();
	GroupRow = new CXTPReportBehaviorRow();
	SetScheme(scheme);

}

CXTPReportBehavior::~CXTPReportBehavior()
{
	SAFE_DELETE(Row);
	SAFE_DELETE(GroupRow);
}


void CXTPReportBehavior::SetScheme(XTPReportBehavior behavior)
{
	m_scheme = behavior;

	Row->MouseDown->Left ->Reset();
	Row->MouseDown->Right->Reset();
	Row->MouseUp  ->Left ->Reset();
	Row->MouseUp  ->Right->Reset();

	switch(behavior)
	{
	case xtpReportBehaviorOutlook2003:
	case xtpReportBehaviorOutlook2007:
	case xtpReportBehaviorOutlook2010:
		SetSchemeOutlook();
		break;

	case xtpReportBehaviorExcel2003:
	case xtpReportBehaviorExcel2007:
	case xtpReportBehaviorExcel2010:
		SetSchemeExcel();
		break;

	case xtpReportBehaviorCodejock1340:
	case xtpReportBehaviorCodejock1341:
	case xtpReportBehaviorCodejock1342:
		SetSchemeCodejock134x();
		break;

	case xtpReportBehaviorCodejock1501:
		SetSchemeCodejock1501();
		break;

	case xtpReportBehaviorCodejock1502:
		SetSchemeCodejock1502();
		break;

	case xtpReportBehaviorCodejockDefault:
		SetSchemeCodejockDefault();
		break;

	default:
		ASSERT(FALSE); // Invalid scheme
		break;
	}
}

void CXTPReportBehavior::SetSchemeExcel()
{
	//////////////////////////////////////////////////////////////////////////
	// Left mouse button
	//////////////////////////////////////////////////////////////////////////

	Row->MouseDown->Left->None->bFocusRow             = TRUE;
	Row->MouseDown->Left->None->bFocusRowTemporarily  = FALSE;
	Row->MouseDown->Left->None->bSelectRow            = TRUE;
	Row->MouseDown->Left->None->bSelectRowTemporarily = FALSE;
	Row->MouseDown->Left->bFocusColumn          = TRUE;
	Row->MouseDown->Left->bEnsureVisible        = FALSE;
	Row->MouseDown->Left->bClick                = TRUE;
	Row->MouseDown->Left->bContextMenu          = FALSE;
	Row->MouseDown->Left->bCheckSelectedRows    = FALSE;
	Row->MouseDown->Left->bDragBegin            = FALSE;
	Row->MouseDown->Left->bDragEnd              = FALSE;

	Row->MouseUp->Left->None->bFocusRow               = FALSE; // Set on mouse down
	Row->MouseUp->Left->None->bFocusRowTemporarily    = FALSE;
	Row->MouseUp->Left->None->bSelectRow              = FALSE; // Set on mouse down
	Row->MouseUp->Left->None->bSelectRowTemporarily   = FALSE;
	Row->MouseUp->Left->bFocusColumn            = FALSE; // Set on mouse down
	Row->MouseUp->Left->bEnsureVisible          = FALSE;
	Row->MouseUp->Left->bClick                  = FALSE; //
	Row->MouseUp->Left->bContextMenu            = FALSE;
	Row->MouseUp->Left->bCheckSelectedRows      = FALSE;
	Row->MouseUp->Left->bDragBegin              = FALSE;
	Row->MouseUp->Left->bDragEnd                = TRUE;

	//////////////////////////////////////////////////////////////////////////
	// Right mouse button
	//////////////////////////////////////////////////////////////////////////

	Row->MouseDown->Right->None->bFocusRow             = TRUE;
	Row->MouseDown->Right->None->bFocusRowTemporarily  = FALSE;
	Row->MouseDown->Right->None->bSelectRow            = TRUE;
	Row->MouseDown->Right->None->bSelectRowTemporarily = FALSE;
	Row->MouseDown->Right->bFocusColumn          = TRUE;
	Row->MouseDown->Right->bEnsureVisible        = FALSE;
	Row->MouseDown->Right->bClick                = FALSE;
	Row->MouseDown->Right->bContextMenu          = TRUE;
	Row->MouseDown->Right->bCheckSelectedRows    = FALSE;
	Row->MouseDown->Right->bDragBegin            = FALSE;
	Row->MouseDown->Right->bDragEnd              = FALSE;

	Row->MouseUp->Right->None->bFocusRow               = FALSE;
	Row->MouseUp->Right->None->bFocusRowTemporarily    = FALSE;
	Row->MouseUp->Right->None->bSelectRow              = FALSE;
	Row->MouseUp->Right->None->bSelectRowTemporarily   = FALSE;
	Row->MouseUp->Right->bFocusColumn            = FALSE;
	Row->MouseUp->Right->bEnsureVisible          = FALSE;
	Row->MouseUp->Right->bClick                  = FALSE;
	Row->MouseUp->Right->bContextMenu            = FALSE;
	Row->MouseUp->Right->bCheckSelectedRows      = FALSE;
	Row->MouseUp->Right->bDragBegin              = FALSE;
	Row->MouseUp->Right->bDragEnd                = TRUE;
}

void CXTPReportBehavior::SetSchemeCodejock134x()
{
	//////////////////////////////////////////////////////////////////////////
	// Left mouse button
	//////////////////////////////////////////////////////////////////////////

	Row->MouseDown->Left->None   ->bFocusRow              = TRUE;
	Row->MouseDown->Left->None   ->bFocusRowTemporarily   = FALSE;
	Row->MouseDown->Left->None   ->bSelectRow             = TRUE;
	Row->MouseDown->Left->None   ->bSelectRowTemporarily  = FALSE;
	Row->MouseDown->Left->None   ->bMultipleSelection     = FALSE;
	Row->MouseDown->Left->None   ->bKeepFocus             = TRUE;  // Drag multi selection
	Row->MouseDown->Left->None   ->bKeepSelection         = TRUE;  // Drag multi selection

	Row->MouseDown->Left->Shift  ->bFocusRow             = TRUE;
	Row->MouseDown->Left->Shift  ->bFocusRowTemporarily  = FALSE;
	Row->MouseDown->Left->Shift  ->bSelectRow            = TRUE;
	Row->MouseDown->Left->Shift  ->bSelectRowTemporarily = FALSE;
	Row->MouseDown->Left->Shift  ->bMultipleSelection    = TRUE;
	Row->MouseDown->Left->Shift  ->bKeepFocus            = FALSE; // Block selection
	Row->MouseDown->Left->Shift  ->bKeepSelection        = FALSE; // Block selection

	Row->MouseDown->Left->Control->bFocusRow             = FALSE;
	Row->MouseDown->Left->Control->bFocusRowTemporarily  = FALSE;
	Row->MouseDown->Left->Control->bSelectRow            = FALSE;
	Row->MouseDown->Left->Control->bSelectRowTemporarily = FALSE;
	Row->MouseDown->Left->Control->bMultipleSelection    = TRUE;
	Row->MouseDown->Left->Control->bKeepFocus            = TRUE;  // Copy multi selection
	Row->MouseDown->Left->Control->bKeepSelection        = TRUE;  // Copy multi selection

	Row->MouseDown->Left->bFocusColumn       = TRUE;
	Row->MouseDown->Left->bEnsureVisible     = TRUE;
	Row->MouseDown->Left->bClick             = FALSE;
	Row->MouseDown->Left->bContextMenu       = FALSE;
	Row->MouseDown->Left->bCheckSelectedRows = FALSE;
	Row->MouseDown->Left->bDragBegin         = TRUE;
	Row->MouseDown->Left->bDragEnd           = FALSE;

	//////////////////////////////////////////////////////////////////////////
	// Left mouse button up
	//////////////////////////////////////////////////////////////////////////

	Row->MouseUp->Left->None   ->bFocusRow             = TRUE;  // Drag multi selection
	Row->MouseUp->Left->None   ->bFocusRowTemporarily  = FALSE;
	Row->MouseUp->Left->None   ->bSelectRow            = TRUE;  // Drag multi selection
	Row->MouseUp->Left->None   ->bSelectRowTemporarily = FALSE;
	Row->MouseUp->Left->None   ->bMultipleSelection    = FALSE;
	Row->MouseUp->Left->None   ->bKeepFocus            = FALSE;
	Row->MouseUp->Left->None   ->bKeepSelection        = FALSE;

	Row->MouseUp->Left->Shift  ->bFocusRow             = FALSE;
	Row->MouseUp->Left->Shift  ->bFocusRowTemporarily  = FALSE;
	Row->MouseUp->Left->Shift  ->bSelectRow            = FALSE;
	Row->MouseUp->Left->Shift  ->bSelectRowTemporarily = FALSE;
	Row->MouseUp->Left->Shift  ->bMultipleSelection    = FALSE;
	Row->MouseUp->Left->Shift  ->bKeepFocus            = FALSE;
	Row->MouseUp->Left->Shift  ->bKeepSelection        = FALSE;

	Row->MouseUp->Left->Control->bFocusRow             = TRUE;
	Row->MouseUp->Left->Control->bFocusRowTemporarily  = FALSE;
	Row->MouseUp->Left->Control->bSelectRow            = TRUE;
	Row->MouseUp->Left->Control->bSelectRowTemporarily = FALSE;
	Row->MouseUp->Left->Control->bMultipleSelection    = TRUE;
	Row->MouseUp->Left->Control->bKeepFocus            = TRUE;  // Ctrl/Shift
	Row->MouseUp->Left->Control->bKeepSelection        = TRUE;  // Ctrl/Shift

	Row->MouseUp->Left->bFocusColumn       = FALSE;
	Row->MouseUp->Left->bEnsureVisible     = FALSE;
	Row->MouseUp->Left->bClick             = TRUE;
	Row->MouseUp->Left->bContextMenu       = FALSE;
	Row->MouseUp->Left->bCheckSelectedRows = FALSE;
	Row->MouseUp->Left->bDragBegin         = FALSE;
	Row->MouseUp->Left->bDragEnd           = TRUE;

	///////////////////////////////////////////////////////////////////////
	// Right mouse button down
	///////////////////////////////////////////////////////////////////////

	Row->MouseDown->Right->None   ->bFocusRow             = TRUE;
	Row->MouseDown->Right->None   ->bFocusRowTemporarily  = FALSE;
	Row->MouseDown->Right->None   ->bSelectRow            = TRUE;
	Row->MouseDown->Right->None   ->bSelectRowTemporarily = FALSE;
	Row->MouseDown->Right->None   ->bMultipleSelection    = FALSE;
	Row->MouseDown->Right->None   ->bKeepSelection        = TRUE;
	Row->MouseDown->Right->None   ->bKeepFocus            = FALSE;
	
	Row->MouseDown->Right->Shift  ->bFocusRow             = TRUE;
	Row->MouseDown->Right->Shift  ->bFocusRowTemporarily  = FALSE;
	Row->MouseDown->Right->Shift  ->bSelectRow            = TRUE;
	Row->MouseDown->Right->Shift  ->bSelectRowTemporarily = FALSE;
	Row->MouseDown->Right->Shift  ->bMultipleSelection    = FALSE;
	Row->MouseDown->Right->Shift  ->bKeepSelection        = TRUE;
	Row->MouseDown->Right->Shift  ->bKeepFocus            = FALSE;

	Row->MouseDown->Right->Control->bFocusRow             = TRUE;
	Row->MouseDown->Right->Control->bFocusRowTemporarily  = FALSE;
	Row->MouseDown->Right->Control->bSelectRow            = TRUE;
	Row->MouseDown->Right->Control->bSelectRowTemporarily = FALSE;
	Row->MouseDown->Right->Control->bMultipleSelection    = FALSE;
	Row->MouseDown->Right->Control->bKeepSelection        = TRUE;
	Row->MouseDown->Right->Control->bKeepFocus            = FALSE;

	Row->MouseDown->Right->bFocusColumn       = FALSE;
	Row->MouseDown->Right->bEnsureVisible     = TRUE;
	Row->MouseDown->Right->bClick             = FALSE;
	Row->MouseDown->Right->bContextMenu       = FALSE;
	Row->MouseDown->Right->bCheckSelectedRows = FALSE;
	Row->MouseDown->Right->bDragBegin         = FALSE;
	Row->MouseDown->Right->bDragEnd           = FALSE;

	///////////////////////////////////////////////////////////////////////
	// Right mouse button up
	///////////////////////////////////////////////////////////////////////

	Row->MouseUp->Right->None->bFocusRow               = TRUE;
	Row->MouseUp->Right->None->bSelectRow              = TRUE;
	Row->MouseUp->Right->None->bKeepSelection          = TRUE;
	
	Row->MouseUp->Right->bEnsureVisible = TRUE;
	Row->MouseUp->Right->bClick         = FALSE;
	Row->MouseUp->Right->bContextMenu   = TRUE;
	Row->MouseUp->Right->bDragEnd       = TRUE;
}

void CXTPReportBehavior::SetSchemeCodejock1501()
{
	//////////////////////////////////////////////////////////////////////////
	// Left mouse button down
	//////////////////////////////////////////////////////////////////////////
	
	Row->MouseDown->Left->None->bFocusRow              = TRUE;
	Row->MouseDown->Left->None->bFocusRowTemporarily   = FALSE;
	Row->MouseDown->Left->None->bSelectRow             = TRUE;
	Row->MouseDown->Left->None->bSelectRowTemporarily  = FALSE;
	Row->MouseDown->Left->None->bKeepFocus             = TRUE;  // Drag multi selection
	Row->MouseDown->Left->None->bKeepSelection         = TRUE;  // Drag multi selection
	
	Row->MouseDown->Left->bFocusColumn           = TRUE;
	Row->MouseDown->Left->bEnsureVisible         = TRUE;
	Row->MouseDown->Left->bClick                 = FALSE;
	Row->MouseDown->Left->bContextMenu           = FALSE;
	Row->MouseDown->Left->bCheckSelectedRows     = FALSE;
	Row->MouseDown->Left->bDragBegin             = TRUE;
	Row->MouseDown->Left->bDragEnd               = FALSE;

	//////////////////////////////////////////////////////////////////////////
	// Left mouse button up
	//////////////////////////////////////////////////////////////////////////

	Row->MouseUp->Left->None->bFocusRow                = TRUE;  // Drag multi selection
	Row->MouseUp->Left->None->bFocusRowTemporarily     = FALSE;
	Row->MouseUp->Left->None->bSelectRow               = TRUE;  // Drag multi selection
	Row->MouseUp->Left->None->bSelectRowTemporarily    = FALSE;
	
	Row->MouseUp->Left->bFocusColumn             = FALSE;
	Row->MouseUp->Left->bEnsureVisible           = FALSE;
	Row->MouseUp->Left->bClick                   = TRUE;
	Row->MouseUp->Left->bDragBegin               = FALSE;
	Row->MouseUp->Left->bDragEnd                 = TRUE;

	///////////////////////////////////////////////////////////////////////
	// Right mouse button
	///////////////////////////////////////////////////////////////////////

	Row->MouseUp->Right->bClick                  = TRUE;
	Row->MouseUp->Right->bContextMenu            = TRUE;
}

void CXTPReportBehavior::SetSchemeCodejock1502()
{
	//////////////////////////////////////////////////////////////////////////
	// Left mouse button down
	//////////////////////////////////////////////////////////////////////////

	Row->MouseDown->Left->None   ->bFocusRow              = TRUE;
	Row->MouseDown->Left->None   ->bFocusRowTemporarily   = FALSE;
	Row->MouseDown->Left->None   ->bSelectRow             = TRUE;
	Row->MouseDown->Left->None   ->bSelectRowTemporarily  = FALSE;
	Row->MouseDown->Left->None   ->bMultipleSelection     = FALSE;
	Row->MouseDown->Left->None   ->bKeepFocus             = TRUE;  // Drag multi selection
	Row->MouseDown->Left->None   ->bKeepSelection         = TRUE;  // Drag multi selection

	Row->MouseDown->Left->Control->bFocusRow              = FALSE; // 15.0.2
	Row->MouseDown->Left->Control->bFocusRowTemporarily   = FALSE;
	Row->MouseDown->Left->Control->bSelectRow             = FALSE; // 15.0.2
	Row->MouseDown->Left->Control->bSelectRowTemporarily  = FALSE;
	Row->MouseDown->Left->Control->bMultipleSelection     = FALSE;
	Row->MouseDown->Left->Control->bKeepFocus             = TRUE;  // Copy multi selection
	Row->MouseDown->Left->Control->bKeepSelection         = TRUE;  // Copy multi selection

	Row->MouseDown->Left->Shift  ->bFocusRow             = TRUE;
	Row->MouseDown->Left->Shift  ->bFocusRowTemporarily  = FALSE;
	Row->MouseDown->Left->Shift  ->bSelectRow            = TRUE;
	Row->MouseDown->Left->Shift  ->bSelectRowTemporarily = FALSE;
	Row->MouseDown->Left->Shift  ->bMultipleSelection    = TRUE;
	Row->MouseDown->Left->Shift  ->bKeepFocus            = FALSE; // Block selection
	Row->MouseDown->Left->Shift  ->bKeepSelection        = FALSE; // Block selection

	Row->MouseDown->Left->bFocusColumn       = TRUE;
	Row->MouseDown->Left->bEnsureVisible     = TRUE;
	Row->MouseDown->Left->bClick             = FALSE;
	Row->MouseDown->Left->bContextMenu       = FALSE;
	Row->MouseDown->Left->bCheckSelectedRows = FALSE;
	Row->MouseDown->Left->bDragBegin         = TRUE;
	Row->MouseDown->Left->bDragEnd           = FALSE;

	//////////////////////////////////////////////////////////////////////////
	// Left mouse button up
	//////////////////////////////////////////////////////////////////////////

	Row->MouseUp->Left->None   ->bFocusRow             = TRUE;  // Drag multi selection
	Row->MouseUp->Left->None   ->bFocusRowTemporarily  = FALSE;
	Row->MouseUp->Left->None   ->bSelectRow            = TRUE;  // Drag multi selection
	Row->MouseUp->Left->None   ->bSelectRowTemporarily = FALSE;
	Row->MouseUp->Left->None   ->bMultipleSelection    = FALSE;
	Row->MouseUp->Left->None   ->bKeepFocus            = FALSE;
	Row->MouseUp->Left->None   ->bKeepSelection        = FALSE;
	
	Row->MouseUp->Left->Control->bFocusRow             = TRUE;  // 15.0.2
	Row->MouseUp->Left->Control->bFocusRowTemporarily  = FALSE;
	Row->MouseUp->Left->Control->bSelectRow            = TRUE;  // 15.0.2
	Row->MouseUp->Left->Control->bSelectRowTemporarily = FALSE;
	Row->MouseUp->Left->Control->bMultipleSelection    = TRUE;
	Row->MouseUp->Left->Control->bKeepFocus            = FALSE;
	Row->MouseUp->Left->Control->bKeepSelection        = FALSE;

	Row->MouseUp->Left->Shift  ->bFocusRow             = FALSE;
	Row->MouseUp->Left->Shift  ->bFocusRowTemporarily  = FALSE;
	Row->MouseUp->Left->Shift  ->bSelectRow            = FALSE;
	Row->MouseUp->Left->Shift  ->bSelectRowTemporarily = FALSE;
	Row->MouseUp->Left->Shift  ->bKeepFocus            = FALSE;
	Row->MouseUp->Left->Shift  ->bKeepSelection        = FALSE;

	Row->MouseUp->Left->bFocusColumn        = FALSE;
	Row->MouseUp->Left->bEnsureVisible      = FALSE;
	Row->MouseUp->Left->bClick              = TRUE;
	Row->MouseUp->Left->bContextMenu        = FALSE;
	Row->MouseUp->Left->bCheckSelectedRows  = FALSE;
	Row->MouseUp->Left->bDragBegin          = FALSE;
	Row->MouseUp->Left->bDragEnd            = TRUE;

	///////////////////////////////////////////////////////////////////////
	// Right mouse button down
	///////////////////////////////////////////////////////////////////////

	Row->MouseDown->Right->None   ->bFocusRow             = TRUE;
	Row->MouseDown->Right->None   ->bFocusRowTemporarily  = FALSE;
	Row->MouseDown->Right->None   ->bSelectRow            = TRUE;
	Row->MouseDown->Right->None   ->bSelectRowTemporarily = FALSE;
	Row->MouseDown->Right->None   ->bMultipleSelection    = FALSE;
	Row->MouseDown->Right->None   ->bKeepFocus            = FALSE;
	Row->MouseDown->Right->None   ->bKeepSelection        = TRUE;
	
	Row->MouseDown->Right->Control->bFocusRow             = TRUE;  // 15.0.2
	Row->MouseDown->Right->Control->bFocusRowTemporarily  = FALSE;
	Row->MouseDown->Right->Control->bSelectRow            = TRUE;  // 15.0.2
	Row->MouseDown->Right->Control->bSelectRowTemporarily = FALSE;
	Row->MouseDown->Right->Control->bMultipleSelection    = FALSE; // 15.0.2
	Row->MouseDown->Right->Control->bKeepFocus            = FALSE;
	Row->MouseDown->Right->Control->bKeepSelection        = TRUE;

	Row->MouseDown->Right->Shift  ->bFocusRow             = TRUE;  // 15.0.2
	Row->MouseDown->Right->Shift  ->bFocusRowTemporarily  = FALSE;
	Row->MouseDown->Right->Shift  ->bSelectRow            = TRUE;  // 15.0.2
	Row->MouseDown->Right->Shift  ->bSelectRowTemporarily = FALSE;
	Row->MouseDown->Right->Shift  ->bMultipleSelection    = FALSE; // 15.0.2
	Row->MouseDown->Right->Shift  ->bKeepFocus            = FALSE;
	Row->MouseDown->Right->Shift  ->bKeepSelection        = TRUE;

	Row->MouseDown->Right->bFocusColumn       = FALSE;
	Row->MouseDown->Right->bEnsureVisible     = TRUE;  // 15.0.2
	Row->MouseDown->Right->bClick             = FALSE;
	Row->MouseDown->Right->bContextMenu       = FALSE;
	Row->MouseDown->Right->bCheckSelectedRows = FALSE;
	Row->MouseDown->Right->bDragBegin         = FALSE;
	Row->MouseDown->Right->bDragEnd           = FALSE;

	///////////////////////////////////////////////////////////////////////
	// Right mouse button up
	///////////////////////////////////////////////////////////////////////

	Row->MouseUp->Right->None   ->bFocusRow             = TRUE; // 15.0.2 bug
	Row->MouseUp->Right->None   ->bFocusRowTemporarily  = FALSE;
	Row->MouseUp->Right->None   ->bSelectRow            = TRUE; // 15.0.2 bug
	Row->MouseUp->Right->None   ->bSelectRowTemporarily = FALSE;
	Row->MouseUp->Right->None   ->bMultipleSelection    = FALSE;
	Row->MouseUp->Right->None   ->bKeepFocus            = FALSE;
	Row->MouseUp->Right->None   ->bKeepSelection        = TRUE;

	Row->MouseUp->Right->Control->bFocusRow             = TRUE; // 15.0.2 bug
	Row->MouseUp->Right->Control->bFocusRowTemporarily  = FALSE;
	Row->MouseUp->Right->Control->bSelectRow            = TRUE; // 15.0.2 bug
	Row->MouseUp->Right->Control->bSelectRowTemporarily = FALSE;
	Row->MouseUp->Right->Control->bMultipleSelection    = FALSE;
	Row->MouseUp->Right->Control->bKeepFocus            = FALSE;
	Row->MouseUp->Right->Control->bKeepSelection        = TRUE;

	Row->MouseUp->Right->Shift  ->bFocusRow             = TRUE; // 15.0.2 bug
	Row->MouseUp->Right->Shift  ->bFocusRowTemporarily  = FALSE;
	Row->MouseUp->Right->Shift  ->bSelectRow            = TRUE; // 15.0.2 bug
	Row->MouseUp->Right->Shift  ->bSelectRowTemporarily = FALSE;
	Row->MouseUp->Right->Shift  ->bMultipleSelection    = FALSE;
	Row->MouseUp->Right->Shift  ->bKeepFocus            = FALSE;
	Row->MouseUp->Right->Shift  ->bKeepSelection        = TRUE;

	Row->MouseUp->Right->bFocusColumn       = FALSE;
	Row->MouseUp->Right->bEnsureVisible     = TRUE;  // 15.0.2 bug (block scrolling only)
	Row->MouseUp->Right->bClick             = FALSE;
	Row->MouseUp->Right->bContextMenu       = TRUE;
	Row->MouseUp->Right->bCheckSelectedRows = FALSE;
	Row->MouseUp->Right->bDragBegin         = FALSE;
	Row->MouseUp->Right->bDragEnd           = FALSE;
}

void CXTPReportBehavior::SetSchemeCodejockDefault()
{
	//////////////////////////////////////////////////////////////////////////
	// Left mouse button down
	//////////////////////////////////////////////////////////////////////////

	Row->MouseDown->Left->None   ->bFocusRow             = TRUE;
	Row->MouseDown->Left->None   ->bFocusRowTemporarily  = FALSE;
	Row->MouseDown->Left->None   ->bSelectRow            = TRUE;
	Row->MouseDown->Left->None   ->bSelectRowTemporarily = FALSE;
	Row->MouseDown->Left->None   ->bMultipleSelection    = FALSE;
	Row->MouseDown->Left->None   ->bKeepFocus            = TRUE;  // Drag multi selection
	Row->MouseDown->Left->None   ->bKeepSelection        = TRUE;  // Drag multi selection

	Row->MouseDown->Left->Control->bFocusRow             = TRUE;
	Row->MouseDown->Left->Control->bFocusRowTemporarily  = FALSE;
	Row->MouseDown->Left->Control->bSelectRow            = TRUE;
	Row->MouseDown->Left->Control->bSelectRowTemporarily = FALSE;
	Row->MouseDown->Left->Control->bMultipleSelection    = TRUE;
	Row->MouseDown->Left->Control->bKeepFocus            = TRUE;  // Copy multi selection
	Row->MouseDown->Left->Control->bKeepSelection        = TRUE;  // Copy multi selection
	
	Row->MouseDown->Left->Shift  ->bFocusRow             = TRUE;
	Row->MouseDown->Left->Shift  ->bFocusRowTemporarily  = FALSE;
	Row->MouseDown->Left->Shift  ->bSelectRow            = TRUE;
	Row->MouseDown->Left->Shift  ->bSelectRowTemporarily = FALSE;
	Row->MouseDown->Left->Shift  ->bMultipleSelection    = TRUE;
	Row->MouseDown->Left->Shift  ->bKeepFocus            = FALSE; // Block selection
	Row->MouseDown->Left->Shift  ->bKeepSelection        = FALSE; // Block selection

	Row->MouseDown->Left->bFocusColumn            = TRUE;
	Row->MouseDown->Left->bEnsureVisible          = TRUE;
	Row->MouseDown->Left->bClick                  = FALSE;
	Row->MouseDown->Left->bContextMenu            = FALSE;
	Row->MouseDown->Left->bCheckSelectedRows      = FALSE;
	Row->MouseDown->Left->bDragBegin              = TRUE;
	Row->MouseDown->Left->bDragEnd                = FALSE;

	//////////////////////////////////////////////////////////////////////////
	// Left mouse button up
	//////////////////////////////////////////////////////////////////////////

	Row->MouseUp->Left->None   ->bFocusRow             = TRUE;  // Drag multi selection
	Row->MouseUp->Left->None   ->bFocusRowTemporarily  = FALSE;
	Row->MouseUp->Left->None   ->bSelectRow            = TRUE;  // Drag multi selection
	Row->MouseUp->Left->None   ->bSelectRowTemporarily = FALSE;
	Row->MouseUp->Left->None   ->bMultipleSelection    = FALSE;
	Row->MouseUp->Left->None   ->bKeepFocus            = FALSE;
	Row->MouseUp->Left->None   ->bKeepSelection        = FALSE;
	
	Row->MouseUp->Left->Shift  ->bFocusRow             = FALSE;
	Row->MouseUp->Left->Shift  ->bFocusRowTemporarily  = FALSE;
	Row->MouseUp->Left->Shift  ->bSelectRow            = FALSE;
	Row->MouseUp->Left->Shift  ->bSelectRowTemporarily = FALSE;
	Row->MouseUp->Left->Shift  ->bMultipleSelection    = TRUE;
	Row->MouseUp->Left->Shift  ->bKeepFocus            = FALSE;
	Row->MouseUp->Left->Shift  ->bKeepSelection        = FALSE;

	Row->MouseUp->Left->Control->bFocusRow             = FALSE;
	Row->MouseUp->Left->Control->bFocusRowTemporarily  = FALSE;
	Row->MouseUp->Left->Control->bSelectRow            = FALSE;
	Row->MouseUp->Left->Control->bSelectRowTemporarily = FALSE;
	Row->MouseUp->Left->Control->bMultipleSelection    = TRUE;
	Row->MouseUp->Left->Control->bKeepFocus            = TRUE;  // Ctrl/Shift
	Row->MouseUp->Left->Control->bKeepSelection        = TRUE;  // Ctrl/Shift
	
	Row->MouseUp->Left->bFocusColumn              = FALSE; // On mouse down
	Row->MouseUp->Left->bEnsureVisible            = FALSE; // On mouse down
	Row->MouseUp->Left->bClick                    = TRUE;
	Row->MouseUp->Left->bContextMenu              = FALSE;
	Row->MouseUp->Left->bCheckSelectedRows        = FALSE;
	Row->MouseUp->Left->bDragBegin                = FALSE;
	Row->MouseUp->Left->bDragEnd                  = TRUE;

	///////////////////////////////////////////////////////////////////////
	// Right mouse button down
	///////////////////////////////////////////////////////////////////////

	Row->MouseDown->Right->None   ->bFocusRow             = TRUE;
	Row->MouseDown->Right->None   ->bFocusRowTemporarily  = FALSE;
	Row->MouseDown->Right->None   ->bSelectRow            = TRUE;
	Row->MouseDown->Right->None   ->bSelectRowTemporarily = FALSE;
	Row->MouseDown->Right->None   ->bMultipleSelection    = FALSE;
	Row->MouseDown->Right->None   ->bKeepFocus            = TRUE;
	Row->MouseDown->Right->None   ->bKeepSelection        = TRUE;

	Row->MouseDown->Right->Control->bFocusRow             = TRUE;
	Row->MouseDown->Right->Control->bFocusRowTemporarily  = FALSE;
	Row->MouseDown->Right->Control->bSelectRow            = TRUE;
	Row->MouseDown->Right->Control->bSelectRowTemporarily = FALSE;
	Row->MouseDown->Right->Control->bMultipleSelection    = TRUE;
	Row->MouseDown->Right->Control->bKeepFocus            = TRUE;
	Row->MouseDown->Right->Control->bKeepSelection        = TRUE;

	Row->MouseDown->Right->Shift  ->bFocusRow             = TRUE;
	Row->MouseDown->Right->Shift  ->bFocusRowTemporarily  = FALSE;
	Row->MouseDown->Right->Shift  ->bSelectRow            = TRUE;
	Row->MouseDown->Right->Shift  ->bSelectRowTemporarily = FALSE;
	Row->MouseDown->Right->Shift  ->bMultipleSelection    = FALSE;
	Row->MouseDown->Right->Shift  ->bKeepFocus            = TRUE;
	Row->MouseDown->Right->Shift  ->bKeepSelection        = TRUE;

	Row->MouseDown->Right->bFocusColumn       = TRUE;
	Row->MouseDown->Right->bEnsureVisible     = TRUE;
	Row->MouseDown->Right->bClick             = FALSE;
	Row->MouseDown->Right->bContextMenu       = FALSE;
	Row->MouseDown->Right->bCheckSelectedRows = FALSE;
	Row->MouseDown->Right->bDragBegin         = FALSE;
	Row->MouseDown->Right->bDragEnd           = FALSE;

	///////////////////////////////////////////////////////////////////////
	// Right mouse button up
	///////////////////////////////////////////////////////////////////////

	Row->MouseUp->Right->None   ->bFocusRow             = FALSE;
	Row->MouseUp->Right->None   ->bFocusRowTemporarily  = FALSE;
	Row->MouseUp->Right->None   ->bSelectRow            = FALSE;
	Row->MouseUp->Right->None   ->bSelectRowTemporarily = FALSE;
	Row->MouseUp->Right->None   ->bMultipleSelection    = FALSE;
	Row->MouseUp->Right->None   ->bKeepSelection        = FALSE;
	Row->MouseUp->Right->None   ->bKeepFocus            = FALSE;

	Row->MouseUp->Right->Control->bFocusRow             = FALSE;
	Row->MouseUp->Right->Control->bFocusRowTemporarily  = FALSE;
	Row->MouseUp->Right->Control->bSelectRow            = FALSE;
	Row->MouseUp->Right->Control->bSelectRowTemporarily = FALSE;
	Row->MouseUp->Right->Control->bMultipleSelection    = FALSE;
	Row->MouseUp->Right->Control->bKeepSelection        = FALSE;
	Row->MouseUp->Right->Control->bKeepFocus            = FALSE;

	Row->MouseUp->Right->Shift  ->bFocusRow             = FALSE;
	Row->MouseUp->Right->Shift  ->bFocusRowTemporarily  = FALSE;
	Row->MouseUp->Right->Shift  ->bSelectRow            = FALSE;
	Row->MouseUp->Right->Shift  ->bSelectRowTemporarily = FALSE;
	Row->MouseUp->Right->Shift  ->bMultipleSelection    = FALSE;
	Row->MouseUp->Right->Shift  ->bKeepSelection        = FALSE;
	Row->MouseUp->Right->Shift  ->bKeepFocus            = FALSE;

	Row->MouseUp->Right->bFocusColumn       = FALSE;
	Row->MouseUp->Right->bEnsureVisible     = FALSE;
	Row->MouseUp->Right->bClick             = FALSE;
	Row->MouseUp->Right->bContextMenu       = TRUE;
	Row->MouseUp->Right->bCheckSelectedRows = FALSE;
	Row->MouseUp->Right->bDragBegin         = FALSE;
	Row->MouseUp->Right->bDragEnd           = FALSE;
}

/////////////////////////////////////////////////////////////////////////////

