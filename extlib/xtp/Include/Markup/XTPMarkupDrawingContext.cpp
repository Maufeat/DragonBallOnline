// XTPMarkupDrawingContext.cpp: implementation of the CXTPMarkupDrawingContext class.
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
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

#include "stdafx.h"

#include "Common/XTPIntel80Helpers.h"

#include "XTPMarkupObject.h"
#include "XTPMarkupDrawingContext.h"
#include "XTPMarkupContext.h"
#include "XTPMarkupBuilder.h"
#include "XTPMarkupDeviceContext.h"
#include "XTPMarkupThickness.h"

#include "GraphicLibrary/GdiPlus/GdiPlus.h"

#pragma warning(disable:4510)
#pragma warning(disable:4610)

using namespace Gdiplus;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


void CXTPMarkupDrawingContext::Register(BOOL bInit)
{
#ifndef _XTP_EXCLUDE_GDIPLUS
	CXTPMarkupGdiPlusDeviceContext::Register(bInit);
#endif
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXTPMarkupDrawingContext::CXTPMarkupDrawingContext(CXTPMarkupContext* pMarkupContext, HDC hDC, HDC hAttribDC /* = 0 */)
{
	m_hDC = hDC;
	m_hAttribDC = hAttribDC ? hAttribDC : hDC;
	m_bDeleteDC = FALSE;

	Init(pMarkupContext);
}

CXTPMarkupDrawingContext::CXTPMarkupDrawingContext(CXTPMarkupContext* pMarkupContext)
{
	m_hDC = CreateCompatibleDC(0);
	m_hAttribDC = m_hDC;
	m_bDeleteDC = TRUE;

	Init(pMarkupContext);
}

CXTPMarkupDrawingContext::CXTPMarkupDrawingContext(HDC hDC)
{
	m_hDC = hDC;
	m_hAttribDC = m_hDC;
	m_bDeleteDC = FALSE;

	Init(NULL);
}

CXTPMarkupDrawingContext::CXTPMarkupDrawingContext()
{
	m_hDC = CreateCompatibleDC(0);
	m_hAttribDC = m_hDC;
	m_bDeleteDC = TRUE;

	Init(NULL);
}

CXTPMarkupDrawingContext::CXTPMarkupDrawingContext(CXTPMarkupContext* /*pMarkupContext*/, GpGraphics* pGpGraphics)
{
	m_hDC = NULL;
	m_hAttribDC = NULL;
	m_bDeleteDC = FALSE;

	m_pDeviceContext = new CXTPMarkupGdiPlusExtendedDeviceContext(pGpGraphics);

	m_pSelectedFont = NULL;
	m_hOldFont = NULL;

	m_hDWP = NULL;

	m_rcClipBox.SetRectEmpty();
	m_pDeviceContext->GetClipBox(m_rcClipBox);
}

CXTPMarkupDrawingContext::CXTPMarkupDrawingContext(CXTPMarkupContext* /*pMarkupContext*/, Graphics* pGraphics)
{
	USES_PROTECTED_ACCESS(CXTPMarkupDrawingContext, Graphics, GpGraphics, nativeGraphics);

	GpGraphics* pGpGraphics = PROTECTED_ACCESS(Graphics, pGraphics, nativeGraphics);

	m_hDWP = NULL;

	m_hDC = NULL;
	m_hAttribDC = NULL;
	m_bDeleteDC = FALSE;

	m_pDeviceContext = new CXTPMarkupGdiPlusExtendedDeviceContext(pGpGraphics);

	m_pSelectedFont = NULL;
	m_hOldFont = NULL;

	m_rcClipBox.SetRectEmpty();
	m_pDeviceContext->GetClipBox(m_rcClipBox);
}

void CXTPMarkupDrawingContext::Init(CXTPMarkupContext* pMarkupContext)
{
	if (!pMarkupContext || pMarkupContext->IsGdiPlusEnabled())
	{
#ifndef _XTP_EXCLUDE_GDIPLUS
		m_pDeviceContext = new CXTPMarkupGdiPlusDeviceContext(m_hDC, m_hAttribDC);
#else
		m_pDeviceContext = new CXTPMarkupDeviceContext(m_hDC, m_hAttribDC);
#endif
	}
	else
	{
		m_pDeviceContext = new CXTPMarkupDeviceContext(m_hDC, m_hAttribDC);
	}

	m_pSelectedFont = NULL;
	m_hOldFont = NULL;

	m_rcClipBox.SetRectEmpty();
	m_pDeviceContext->GetClipBox(m_rcClipBox);

	m_hDWP = NULL;

	::SetBkMode(m_hDC, TRANSPARENT);
}

CXTPMarkupDrawingContext::~CXTPMarkupDrawingContext()
{
	SetFont(NULL);

	delete m_pDeviceContext;

	if (m_bDeleteDC)
	{
		DeleteDC(m_hDC);
	}
}

HDC CXTPMarkupDrawingContext::Detach()
{
	SetFont(NULL);

	HDC hDC = m_hDC;
	m_hDC = NULL;
	return hDC;
}

void CXTPMarkupDrawingContext::OffsetViewport(const POINT& ptVisualOffset)
{
	m_pDeviceContext->OffsetViewport(ptVisualOffset);

	m_pDeviceContext->GetClipBox(m_rcClipBox);
}

void CXTPMarkupDrawingContext::IntersectClipRect(const RECT& rcLayoutClip)
{
	m_pDeviceContext->IntersectClipRect(rcLayoutClip);

	m_pDeviceContext->GetClipBox(m_rcClipBox);
}

HRGN CXTPMarkupDrawingContext::SaveClipRegion()
{
	return m_pDeviceContext->SaveClipRegion();
}

void CXTPMarkupDrawingContext::RestoreClipRegion(HRGN hrgnClip)
{
	if (hrgnClip != NULL)
	{
		m_pDeviceContext->RestoreClipRegion(hrgnClip);

		m_pDeviceContext->GetClipBox(m_rcClipBox);
	}
}

void CXTPMarkupDrawingContext::FillSolidRect(CRect rc, COLORREF clr)
{
	CXTPMarkupSolidColorBrush brush(clr);
	m_pDeviceContext->FillRectangle(rc, &brush);

}
void CXTPMarkupDrawingContext::FillRectangle(CRect rc, CXTPMarkupBrush* pBrush, double* pCornerRadius)
{
	if (pCornerRadius)
		m_pDeviceContext->FillRoundRectangle(rc, pBrush, pCornerRadius);
	else
		m_pDeviceContext->FillRectangle(rc, pBrush);
}

void CXTPMarkupDrawingContext::DrawFrame(CRect rc, CXTPMarkupBrush* pBrush)
{
	CXTPMarkupThickness thickness(1);
	DrawRectangle(rc, pBrush, &thickness);
}

void CXTPMarkupDrawingContext::DrawTextLine(LPCWSTR lpszText, UINT nCount, LPCRECT lpRect)
{
	m_pDeviceContext->DrawString(lpszText, nCount, lpRect);
}

void CXTPMarkupDrawingContext::SetFont(CXTPMarkupFont* pFont)
{
	if (m_pSelectedFont == pFont)
		return;

	m_pDeviceContext->SetTextFont(pFont);

	MARKUP_RELEASE(m_pSelectedFont);
	m_pSelectedFont = pFont;
	MARKUP_ADDREF(m_pSelectedFont);
}

SIZE CXTPMarkupDrawingContext::GetTextExtent(LPCWSTR lpszText, int nCount) const
{
	return m_pDeviceContext->MeasureString(lpszText, nCount);
}


void CXTPMarkupDrawingContext::DrawLine(int x1, int y1, int x2, int y2, CXTPMarkupStrokeStyle* pStrokeStyle)
{
	if (!pStrokeStyle || pStrokeStyle->nStrokeThickness <= 0)
		return;

	m_pDeviceContext->DrawLine(x1, y1, x2, y2, pStrokeStyle);
}

void CXTPMarkupDrawingContext::Polygon(const POINT* points, int nCount, CXTPMarkupStrokeStyle* pStrokeStyle, CXTPMarkupBrush* pFillBrush)
{
	m_pDeviceContext->Polygon(points, nCount, pStrokeStyle, pFillBrush);
}

void CXTPMarkupDrawingContext::Polyline(const POINT* points, int nCount, CXTPMarkupStrokeStyle* pStrokeStyle)
{
	m_pDeviceContext->Polyline(points, nCount, pStrokeStyle);
}

void CXTPMarkupDrawingContext::Ellipse(CRect rc, CXTPMarkupStrokeStyle* pStrokeStyle, CXTPMarkupBrush* pFillBrush)
{
	m_pDeviceContext->Ellipse(rc, pStrokeStyle, pFillBrush);
}

void CXTPMarkupDrawingContext::DrawRectangle(CRect rc, CXTPMarkupBrush* pBrush, CXTPMarkupThickness* pThickness, double* pCornerRadius)
{
	if (!pThickness || !pBrush)
		return;

	if (pCornerRadius)
		m_pDeviceContext->DrawRoundRectangle(rc, pBrush, pThickness, pCornerRadius);
	else
		m_pDeviceContext->DrawRectangle(rc, pBrush, pThickness);
}

void CXTPMarkupDrawingContext::DrawPath(CXTPMarkupPathGeometry* pGeometry, CXTPMarkupStrokeStyle* pStrokeStyle, CXTPMarkupBrush* pFillBrush)
{
	m_pDeviceContext->DrawPath(pGeometry, pStrokeStyle, pFillBrush);
}

HDC CXTPMarkupDrawingContext::GetDC()
{
	return m_pDeviceContext->GetDC();
}

void CXTPMarkupDrawingContext::ReleaseDC(HDC hDC)
{
	m_pDeviceContext->ReleaseDC(hDC);
}

void CXTPMarkupDrawingContext::SetTextColor(CXTPMarkupBrush* pBrush)
{
	m_pDeviceContext->SetTextColor(pBrush);
}

//////////////////////////////////////////////////////////////////////////
// CXTPMarkupPrintingContext

CXTPMarkupPrintingContext::CXTPMarkupPrintingContext(CXTPMarkupContext* pMarkupContext, HDC hDC, HDC hAttribDC)
	: CXTPMarkupDrawingContext(pMarkupContext, hDC, hAttribDC)
{
}
CXTPMarkupPrintingContext::CXTPMarkupPrintingContext(HDC hDC, HDC hAttribDC)
	: CXTPMarkupDrawingContext(NULL, hDC, hAttribDC)
{
}



//////////////////////////////////////////////////////////////////////////
// CXTPMarkupBrush

IMPLEMENT_MARKUPCLASS(NULL, CXTPMarkupBrush, CXTPMarkupObject);

void CXTPMarkupBrush::RegisterMarkupClass()
{

}

COLORREF CXTPMarkupBrush::GetHintColor() const
{
	return 0;
}

CXTPMarkupObject* CXTPMarkupBrush::ConvertFrom(CXTPMarkupBuilder* /*pBuilder*/, CXTPMarkupObject* pObject) const
{
	if (IsStringObject(pObject))
	{
		COLORREF clr;
		if (CXTPMarkupColor::ConvertFromString(*((CXTPMarkupString*)pObject), clr))
		{
			return new CXTPMarkupSolidColorBrush((BYTE)(clr >> 24), clr & 0xFFFFFF);
		}
	}

	return NULL;
}


//////////////////////////////////////////////////////////////////////////
// CXTPMarkupSolidColorBrush

CXTPMarkupDependencyProperty* CXTPMarkupSolidColorBrush::m_pColorProperty = NULL;

IMPLEMENT_MARKUPCLASS(L"SolidColorBrush", CXTPMarkupSolidColorBrush, CXTPMarkupBrush);

void CXTPMarkupSolidColorBrush::RegisterMarkupClass()
{
	m_pColorProperty = CXTPMarkupDependencyProperty::Register(L"Color", MARKUP_TYPE(CXTPMarkupColor), MARKUP_TYPE(CXTPMarkupSolidColorBrush));
}

CXTPMarkupSolidColorBrush::CXTPMarkupSolidColorBrush()
{
}

CXTPMarkupSolidColorBrush::CXTPMarkupSolidColorBrush(COLORREF clr)
{
	SetValue(m_pColorProperty, new CXTPMarkupColor(clr | 0xFF000000));
}

CXTPMarkupSolidColorBrush::CXTPMarkupSolidColorBrush(BYTE nAlpha, COLORREF clr)
{
	SetValue(m_pColorProperty, new CXTPMarkupColor(nAlpha, clr));
}

BOOL CXTPMarkupSolidColorBrush::IsEqual(const CXTPMarkupObject* pObject) const
{
	if (!pObject)
		return FALSE;

	if (pObject->GetType() != MARKUP_TYPE(CXTPMarkupSolidColorBrush))
		return FALSE;

	return GetHintColor() == ((CXTPMarkupSolidColorBrush*)pObject)->GetHintColor();

}

COLORREF CXTPMarkupSolidColorBrush::GetHintColor() const
{
	CXTPMarkupColor* pColor = MARKUP_STATICCAST(CXTPMarkupColor, GetValue(m_pColorProperty));

	if (pColor)
	{
		return (*pColor) & 0xFFFFFF;
	}

	return 0;
}

CXTPMarkupColor* CXTPMarkupSolidColorBrush::GetColor() const
{
	return MARKUP_STATICCAST(CXTPMarkupColor, GetValue(m_pColorProperty));
}

//////////////////////////////////////////////////////////////////////////
// CXTPMarkupPoint

IMPLEMENT_MARKUPCLASS(NULL, CXTPMarkupPoint, CXTPMarkupObject);

void CXTPMarkupPoint::RegisterMarkupClass()
{

}

CXTPMarkupPoint::CXTPMarkupPoint()
{
	x = 0;
	y = 0;
}

CXTPMarkupPoint::CXTPMarkupPoint(double x, double y)
{
	this->x = x;
	this->y = y;
}

CXTPMarkupPoint& CXTPMarkupPoint::operator=(const CXTPMarkupPoint& srcPoint)
{
	x = srcPoint.x;
	y = srcPoint.y;
	return *this;
}

CXTPMarkupObject* CXTPMarkupPoint::ConvertFrom(CXTPMarkupBuilder* /*pBuilder*/, CXTPMarkupObject* pObject) const
{
	if (IsStringObject(pObject))
	{
		LPCWSTR lpszValue = *(CXTPMarkupString*)pObject;

		double x = 0, y = 0;
		if (!CXTPMarkupBuilder::ConvertDouble(lpszValue, x, _T(','), FALSE))
			return NULL;

		if (!CXTPMarkupBuilder::ConvertDouble(lpszValue, y))
			return NULL;

		return new CXTPMarkupPoint(x, y);
	}
	return NULL;
}


//////////////////////////////////////////////////////////////////////////
// CXTPMarkupGradientStop
CXTPMarkupDependencyProperty* CXTPMarkupGradientStop::m_pColorProperty = NULL;
CXTPMarkupDependencyProperty* CXTPMarkupGradientStop::m_pOffsetProperty = NULL;

IMPLEMENT_MARKUPCLASS(L"GradientStop", CXTPMarkupGradientStop, CXTPMarkupObject);

void CXTPMarkupGradientStop::RegisterMarkupClass()
{
	m_pColorProperty = CXTPMarkupDependencyProperty::Register(L"Color", MARKUP_TYPE(CXTPMarkupColor), MARKUP_TYPE(CXTPMarkupGradientStop));
	m_pOffsetProperty = CXTPMarkupDependencyProperty::Register(L"Offset", MARKUP_TYPE(CXTPMarkupDouble), MARKUP_TYPE(CXTPMarkupGradientStop));
}

CXTPMarkupGradientStop::CXTPMarkupGradientStop()
{

}

CXTPMarkupGradientStop::CXTPMarkupGradientStop(COLORREF clr, double dOffset)
{
	SetValue(m_pColorProperty, new CXTPMarkupColor(clr));
	SetValue(m_pOffsetProperty, new CXTPMarkupDouble(dOffset));
}

COLORREF CXTPMarkupGradientStop::GetColor() const
{
	CXTPMarkupColor* pColor = MARKUP_STATICCAST(CXTPMarkupColor, GetValue(m_pColorProperty));
	return pColor != NULL ? (COLORREF)*pColor : 0;
}

double CXTPMarkupGradientStop::GetOffset() const
{
	CXTPMarkupDouble* pOffset = MARKUP_STATICCAST(CXTPMarkupDouble, GetValue(m_pOffsetProperty));
	return pOffset != NULL ? (double)*pOffset : 0.0;

}


IMPLEMENT_MARKUPCLASS(L"", CXTPMarkupGradientStops, CXTPMarkupCollection);

void CXTPMarkupGradientStops::RegisterMarkupClass()
{
}

CXTPMarkupGradientStops::CXTPMarkupGradientStops()
{
	m_pElementType = MARKUP_TYPE(CXTPMarkupGradientStop);
}

//////////////////////////////////////////////////////////////////////////
// CXTPMarkupLinearGradientBrush

CXTPMarkupDependencyProperty* CXTPMarkupLinearGradientBrush::m_pStartPointProperty = NULL;
CXTPMarkupDependencyProperty* CXTPMarkupLinearGradientBrush::m_pEndPointProperty = NULL;
CXTPMarkupDependencyProperty* CXTPMarkupLinearGradientBrush::m_pGradientStopsProperty = NULL;

IMPLEMENT_MARKUPCLASS(L"LinearGradientBrush", CXTPMarkupLinearGradientBrush, CXTPMarkupBrush);

void CXTPMarkupLinearGradientBrush::RegisterMarkupClass()
{
	m_pStartPointProperty = CXTPMarkupDependencyProperty::Register(L"StartPoint", MARKUP_TYPE(CXTPMarkupPoint), MARKUP_TYPE(CXTPMarkupLinearGradientBrush));
	m_pEndPointProperty = CXTPMarkupDependencyProperty::Register(L"EndPoint", MARKUP_TYPE(CXTPMarkupPoint), MARKUP_TYPE(CXTPMarkupLinearGradientBrush));

	m_pGradientStopsProperty = CXTPMarkupDependencyProperty::Register(L"GradientStops", MARKUP_TYPE(CXTPMarkupGradientStops), MARKUP_TYPE(CXTPMarkupLinearGradientBrush));
}


CXTPMarkupLinearGradientBrush::CXTPMarkupLinearGradientBrush()
{
	SetValue(m_pGradientStopsProperty, new CXTPMarkupGradientStops());
}

CXTPMarkupLinearGradientBrush::CXTPMarkupLinearGradientBrush(CXTPMarkupGradientStops* pGradientStops)
{
	SetValue(m_pGradientStopsProperty, pGradientStops);
}

COLORREF CXTPMarkupLinearGradientBrush::GetHintColor() const
{
	CXTPMarkupGradientStops* pGradientStops = GetGradientStops();

	if (!pGradientStops || pGradientStops->GetCount() == 0)
		return 0;

	return pGradientStops->GetItem(0)->GetColor() & 0xFFFFFF;
}

CXTPMarkupLinearGradientBrush::~CXTPMarkupLinearGradientBrush()
{
}

void CXTPMarkupLinearGradientBrush::SetStartPoint(double x, double y)
{
	SetValue(m_pStartPointProperty, new CXTPMarkupPoint(x, y));
}

void CXTPMarkupLinearGradientBrush::SetEndPoint(double x, double y)
{
	SetValue(m_pEndPointProperty, new CXTPMarkupPoint(x, y));
}

void CXTPMarkupLinearGradientBrush::SetContentObject(CXTPMarkupBuilder* pBuilder, CXTPMarkupObject* pContent)
{
	CXTPMarkupGradientStops* pGradientStops = GetGradientStops();
	if (pGradientStops) pGradientStops->SetContentObject(pBuilder, pContent);
}


