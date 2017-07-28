// XTPReportBehaviorRowMouseButton.cpp : implementation of the CXTPReportBehaviorRowMouseButton class.
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

CXTPReportBehaviorRowModifier::CXTPReportBehaviorRowModifier()
	: bFocusRow            (FALSE)
	, bFocusRowTemporarily (FALSE)
	, bSelectRow           (FALSE)
	, bSelectRowTemporarily(FALSE)
	, bMultipleSelection   (FALSE)
	, bKeepSelection       (FALSE)
	, bKeepFocus           (FALSE)
{
}


void CXTPReportBehaviorRowModifier::Reset()
{
	bFocusRow             = FALSE;
	bFocusRowTemporarily  = FALSE;
	bSelectRow            = FALSE;
	bSelectRowTemporarily = FALSE;
	bMultipleSelection    = FALSE;
	bKeepSelection        = FALSE;
	bKeepFocus            = FALSE;
}

