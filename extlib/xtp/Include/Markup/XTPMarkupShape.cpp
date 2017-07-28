// XTPMarkupShape.cpp: implementation of the CXTPMarkupShape class.
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
#include <math.h>

#include <Common/XTPVC80Helpers.h>

#include "XTPMarkupObject.h"
#include "XTPMarkupInputElement.h"
#include "XTPMarkupUIElement.h"
#include "XTPMarkupFrameworkElement.h"
#include "XTPMarkupShape.h"
#include "XTPMarkupDrawingContext.h"
#include "XTPMarkupBuilder.h"
#include "XTPMarkupThickness.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
// CXTPMarkupShape


CXTPMarkupDependencyProperty* CXTPMarkupShape::m_pFillProperty = NULL;
CXTPMarkupDependencyProperty* CXTPMarkupShape::m_pStrokeProperty = NULL;
CXTPMarkupDependencyProperty* CXTPMarkupShape::m_pStrokeThicknessProperty = NULL;
CXTPMarkupDependencyProperty* CXTPMarkupShape::m_pStretchProperty = NULL;
CXTPMarkupDependencyProperty* CXTPMarkupShape::m_pStrokeDashArrayProperty = NULL;
CXTPMarkupDependencyProperty* CXTPMarkupShape::m_pStrokeStartLineCapProperty = NULL;
CXTPMarkupDependencyProperty* CXTPMarkupShape::m_pStrokeEndLineCapProperty = NULL;
CXTPMarkupDependencyProperty* CXTPMarkupShape::m_pStrokeLineJoinProperty = NULL;

IMPLEMENT_MARKUPCLASS(L"Shape", CXTPMarkupShape, CXTPMarkupFrameworkElement)

void CXTPMarkupShape::RegisterMarkupClass()
{
	m_pFillProperty = CXTPMarkupDependencyProperty::Register(L"Fill", MARKUP_TYPE(CXTPMarkupBrush), MARKUP_TYPE(CXTPMarkupShape),
		new CXTPMarkupPropertyMetadata(NULL, CXTPMarkupPropertyMetadata::flagAffectsRender));

	m_pStrokeProperty = CXTPMarkupDependencyProperty::Register(L"Stroke", MARKUP_TYPE(CXTPMarkupBrush), MARKUP_TYPE(CXTPMarkupShape),
		new CXTPMarkupPropertyMetadata(NULL, CXTPMarkupPropertyMetadata::flagAffectsRender));

	m_pStrokeThicknessProperty = CXTPMarkupDependencyProperty::Register(L"StrokeThickness", MARKUP_TYPE(CXTPMarkupInt), MARKUP_TYPE(CXTPMarkupShape),
		new CXTPMarkupPropertyMetadata(NULL, CXTPMarkupPropertyMetadata::flagAffectsRender));

	m_pStretchProperty = CXTPMarkupDependencyProperty::Register(L"Stretch", MARKUP_TYPE(CXTPMarkupEnum), MARKUP_TYPE(CXTPMarkupShape),
		new CXTPMarkupPropertyMetadata(CXTPMarkupEnum::CreateValue(xtpMarkupStretchNone), &CXTPMarkupBuilder::ConvertStretch, CXTPMarkupPropertyMetadata::flagAffectsRender));

	m_pStrokeDashArrayProperty = CXTPMarkupDependencyProperty::Register(L"StrokeDashArray", MARKUP_TYPE(CXTPMarkupDoubleCollection), MARKUP_TYPE(CXTPMarkupShape),
		new CXTPMarkupPropertyMetadata(NULL, CXTPMarkupPropertyMetadata::flagAffectsMeasure));

	m_pStrokeStartLineCapProperty = CXTPMarkupDependencyProperty::Register(L"StrokeStartLineCap", MARKUP_TYPE(CXTPMarkupEnum), MARKUP_TYPE(CXTPMarkupShape),
		new CXTPMarkupPropertyMetadata(CXTPMarkupEnum::CreateValue(xtpMarkupLineCapFlat), &CXTPMarkupShape::ConvertLineCap, CXTPMarkupPropertyMetadata::flagAffectsRender));

	m_pStrokeEndLineCapProperty = CXTPMarkupDependencyProperty::Register(L"StrokeEndLineCap", MARKUP_TYPE(CXTPMarkupEnum), MARKUP_TYPE(CXTPMarkupShape),
		new CXTPMarkupPropertyMetadata(CXTPMarkupEnum::CreateValue(xtpMarkupLineCapFlat), &CXTPMarkupShape::ConvertLineCap, CXTPMarkupPropertyMetadata::flagAffectsRender));

	m_pStrokeLineJoinProperty = CXTPMarkupDependencyProperty::Register(L"StrokeLineJoin", MARKUP_TYPE(CXTPMarkupEnum), MARKUP_TYPE(CXTPMarkupShape),
		new CXTPMarkupPropertyMetadata(CXTPMarkupEnum::CreateValue(xtpMarkupLineJoinMiter), &CXTPMarkupShape::ConvertLineJoin, CXTPMarkupPropertyMetadata::flagAffectsRender));
}

CXTPMarkupShape::CXTPMarkupShape()
{
}

CXTPMarkupShape::~CXTPMarkupShape()
{

}

CXTPMarkupBrush* CXTPMarkupShape::GetFill() const
{
	return MARKUP_STATICCAST(CXTPMarkupBrush, GetValue(m_pFillProperty));
}

void CXTPMarkupShape::SetFill(CXTPMarkupBrush* brush)
{
	SetValue(m_pFillProperty, brush);
}

CXTPMarkupBrush* CXTPMarkupShape::GetStroke() const
{
	return MARKUP_STATICCAST(CXTPMarkupBrush, GetValue(m_pStrokeProperty));
}

void CXTPMarkupShape::SetStroke(CXTPMarkupBrush* brush)
{
	SetValue(m_pStrokeProperty, brush);
}

void CXTPMarkupShape::GetStrokeStyle(CXTPMarkupStrokeStyle* pStrokeStyle) const
{
	pStrokeStyle->pStrokeBrush = GetStroke();
	pStrokeStyle->nStrokeThickness = pStrokeStyle->pStrokeBrush ? GetStrokeThickness() : 0;
	pStrokeStyle->pStrokeDashArray = GetStrokeDashArray();
	pStrokeStyle->nStrokeStartLineCap = GetStrokeStartLineCap();
	pStrokeStyle->nStrokeEndLineCap = GetStrokeEndLineCap();
	pStrokeStyle->nStrokeLineJoin = GetStrokeLineJoin();
}

CXTPMarkupObject* CXTPMarkupShape::ConvertLineCap(CXTPMarkupBuilder* /*pBuilder*/, CXTPMarkupObject* pObject)
{
	if (IsStringObject(pObject))
	{
		LPCWSTR lpszValue = *((CXTPMarkupString*)pObject);
		int nLength = ((CXTPMarkupString*)pObject)->GetLength();

		if (nLength == 4 && _wcsicmp(lpszValue, L"Flat") == 0) return CXTPMarkupEnum::CreateValue(xtpMarkupLineCapFlat);
		if (nLength == 6 && _wcsicmp(lpszValue, L"Square") == 0) return CXTPMarkupEnum::CreateValue(xtpMarkupLineCapSquare);
		if (nLength == 5 && _wcsicmp(lpszValue, L"Round") == 0) return CXTPMarkupEnum::CreateValue(xtpMarkupLineCapRound);
		if (nLength == 8 && _wcsicmp(lpszValue, L"Triangle") == 0) return CXTPMarkupEnum::CreateValue(xtpMarkupLineCapTriangle);

	}
	return NULL;
}

CXTPMarkupObject* CXTPMarkupShape::ConvertLineJoin(CXTPMarkupBuilder* /*pBuilder*/, CXTPMarkupObject* pObject)
{
	if (IsStringObject(pObject))
	{
		LPCWSTR lpszValue = *((CXTPMarkupString*)pObject);
		int nLength = ((CXTPMarkupString*)pObject)->GetLength();

		if (nLength == 5 && _wcsicmp(lpszValue, L"Miter") == 0) return CXTPMarkupEnum::CreateValue(xtpMarkupLineJoinMiter);
		if (nLength == 5 && _wcsicmp(lpszValue, L"Bevel") == 0) return CXTPMarkupEnum::CreateValue(xtpMarkupLineJoinBevel);
		if (nLength == 5 && _wcsicmp(lpszValue, L"Round") == 0) return CXTPMarkupEnum::CreateValue(xtpMarkupLineJoinRound);

	}
	return NULL;
}


//////////////////////////////////////////////////////////////////////////
// CXTPMarkupPointCollection

IMPLEMENT_MARKUPCLASS(NULL, CXTPMarkupPointCollection, CXTPMarkupObject)

void CXTPMarkupPointCollection::RegisterMarkupClass()
{

}

CXTPMarkupPointCollection::CXTPMarkupPointCollection()
{
	m_rcBounds.SetRectEmpty();
}

CXTPMarkupPointCollection::CXTPMarkupPointCollection(CPointArray& arr)
{
	m_rcBounds.SetRectEmpty();

	m_arrPoints.Copy(arr);

	int nCount = (int)m_arrPoints.GetSize();

	if (nCount > 0)
	{
		m_rcBounds.SetRect(INT_MAX, INT_MAX, -INT_MAX, -INT_MAX);

		for (int i = 0; i < nCount; i++)
		{
			POINT& pt = m_arrPoints[i];
			if (pt.x > m_rcBounds.right) m_rcBounds.right = pt.x;
			if (pt.y > m_rcBounds.bottom) m_rcBounds.bottom = pt.y;
			if (pt.x < m_rcBounds.left) m_rcBounds.left = pt.x;
			if (pt.y < m_rcBounds.top) m_rcBounds.top = pt.y;
		}
	}
}


BOOL CXTPMarkupPointCollection::GetNextValue(LPCWSTR& lpszValue, int& nValue)
{
	while (*lpszValue == ' ') lpszValue++;
	LPCWSTR lpszNext = lpszValue;

	nValue = 0;
	int nSign = 1;
	if (*lpszNext == '-')
	{
		nSign = -1;
		lpszNext++;
	}

	if (*lpszNext == 0)
		return FALSE;

	while (*lpszNext != 0)
	{
		WCHAR c = *lpszNext;

		if (c == ' ' || c == ',')
		{
			if (lpszNext == lpszValue)
				return FALSE;
			lpszNext++;
			break;
		}

		if (c <'0' || c > '9')
			return FALSE;

		nValue = 10 * nValue + (c - '0');

		lpszNext++;
	}

	lpszValue = lpszNext;
	nValue *= nSign;

	return TRUE;
}

BOOL CXTPMarkupPointCollection::ConvertFromString(LPCWSTR lpszValue, CPointArray& arr)
{
	if (!lpszValue)
		return FALSE;

	while (*lpszValue != 0)
	{
		int x, y;
		if (!GetNextValue(lpszValue, x))
			return FALSE;

		if (!GetNextValue(lpszValue, y))
			return FALSE;

		while (*lpszValue == ' ') lpszValue++;

		POINT pt = {x, y};
		arr.Add(pt);
	}

	return TRUE;
}

CXTPMarkupObject* CXTPMarkupPointCollection::ConvertFrom(CXTPMarkupBuilder* /*pBuilder*/, CXTPMarkupObject* pObject) const
{
	if (IsStringObject(pObject))
	{
		CPointArray arr;
		if (ConvertFromString(*((CXTPMarkupString*)pObject), arr))
		{
			return new CXTPMarkupPointCollection(arr);
		}
	}

	return NULL;
}

//////////////////////////////////////////////////////////////////////////
// CXTPMarkupPolygon


CXTPMarkupDependencyProperty* CXTPMarkupPolygon::m_pPointsProperty = NULL;

IMPLEMENT_MARKUPCLASS(L"Polygon", CXTPMarkupPolygon, CXTPMarkupShape)

void CXTPMarkupPolygon::RegisterMarkupClass()
{
	m_pPointsProperty = CXTPMarkupDependencyProperty::Register(L"Points", MARKUP_TYPE(CXTPMarkupPointCollection), MARKUP_TYPE(CXTPMarkupPolygon),
		new CXTPMarkupPropertyMetadata(NULL, CXTPMarkupPropertyMetadata::flagAffectsMeasure));

}

CXTPMarkupPolygon::CXTPMarkupPolygon()
{
}

CXTPMarkupPolygon::~CXTPMarkupPolygon()
{

}

void CXTPMarkupPolygon::SetPoints(CXTPMarkupPointCollection* pPoints)
{
	SetValue(m_pPointsProperty, pPoints);
}

CXTPMarkupPointCollection* CXTPMarkupPolygon::GetPoints() const
{
	return MARKUP_STATICCAST(CXTPMarkupPointCollection, GetValue(m_pPointsProperty));
}

CSize CXTPMarkupPolygon::MeasureOverride(CXTPMarkupDrawingContext* /*pDC*/, CSize szAvailableSize)
{
	CXTPMarkupPointCollection* pPoints = GetPoints();
	if (!pPoints)
		return CSize(0, 0);
	CRect rcBounds = pPoints->GetBounds();

	CSize szBound(max(rcBounds.Width(), rcBounds.right), max(rcBounds.Height(),rcBounds.bottom));

	if (GetStretch() != xtpMarkupStretchNone)
	{
		if (szAvailableSize.cx < INT_MAX)
			szBound.cx = szAvailableSize.cx;

		if (szAvailableSize.cy < INT_MAX)
			szBound.cy = szAvailableSize.cy;
	}
	return szBound;
}

void CXTPMarkupPolygon::OnRender(CXTPMarkupDrawingContext* pDC)
{
	CXTPMarkupStrokeStyle strokeStyle;
	GetStrokeStyle(&strokeStyle);

	CXTPMarkupBrush* pFillBrush = GetFill();

	if (!strokeStyle.pStrokeBrush && !pFillBrush)
		return;

	CXTPMarkupPointCollection* pPoints = GetPoints();
	if (!pPoints)
		return;

	const CXTPMarkupPointCollection::CPointArray& arr = pPoints->GetPoints();

	if (GetStretch() != xtpMarkupStretchNone)
	{
		CXTPMarkupPointCollection::CPointArray arrStretch;
		pPoints->Stretch(arrStretch, GetRenderSize());

		pDC->Polygon(arrStretch.GetData(), (int)arrStretch.GetSize(), &strokeStyle, pFillBrush);
	}
	else
	{
		pDC->Polygon(arr.GetData(), (int)arr.GetSize(), &strokeStyle, pFillBrush);
	}
}

//////////////////////////////////////////////////////////////////////////
// CXTPMarkupPolyline


CXTPMarkupDependencyProperty* CXTPMarkupPolyline::m_pPointsProperty = NULL;

IMPLEMENT_MARKUPCLASS(L"Polyline", CXTPMarkupPolyline, CXTPMarkupShape)

void CXTPMarkupPolyline::RegisterMarkupClass()
{
	m_pPointsProperty = CXTPMarkupDependencyProperty::Register(L"Points", MARKUP_TYPE(CXTPMarkupPointCollection), MARKUP_TYPE(CXTPMarkupPolyline),
		new CXTPMarkupPropertyMetadata(NULL, CXTPMarkupPropertyMetadata::flagAffectsMeasure));
}

CXTPMarkupPolyline::CXTPMarkupPolyline()
{
}

CXTPMarkupPolyline::~CXTPMarkupPolyline()
{

}

void CXTPMarkupPolyline::SetPoints(CXTPMarkupPointCollection* pPoints)
{
	SetValue(m_pPointsProperty, pPoints);
}

CXTPMarkupPointCollection* CXTPMarkupPolyline::GetPoints() const
{
	return MARKUP_STATICCAST(CXTPMarkupPointCollection, GetValue(m_pPointsProperty));
}

CSize CXTPMarkupPolyline::MeasureOverride(CXTPMarkupDrawingContext* /*pDC*/, CSize szAvailableSize)
{
	CXTPMarkupPointCollection* pPoints = GetPoints();
	if (!pPoints)
		return CSize(0, 0);
	CRect rcBounds = pPoints->GetBounds();

	CSize szBound(max(rcBounds.Width(), rcBounds.right), max(rcBounds.Height(),rcBounds.bottom));

	if ((szBound.cx == 0 || szBound.cy == 0) && GetStroke())
	{
		int nStroke = (GetStrokeThickness() + 1) / 2;

		if (szBound.cy == 0) szBound.cy += nStroke;
		if (szBound.cx == 0) szBound.cx += nStroke;
	}

	if (GetStretch() != xtpMarkupStretchNone)
	{
		if (szAvailableSize.cx < INT_MAX)
			szBound.cx = szAvailableSize.cx;

		if (szAvailableSize.cy < INT_MAX)
			szBound.cy = szAvailableSize.cy;
	}
	return szBound;
}

void CXTPMarkupPointCollection::Stretch(CPointArray& arrStretch, CSize sz)
{
	const CPointArray& arr = GetPoints();
	arrStretch.Copy(arr);
	int nCount = (int)arrStretch.GetSize();

	CRect rc = GetBounds();
	if (rc.Width() == 0 && rc.Height() == 0)
		return;

	for (int i = 0; i < nCount; i++)
	{
		POINT& pt = arrStretch[i];
		if (rc.Width() != 0) pt.x = (pt.x - rc.left) * sz.cx / rc.Width();
		if (rc.Height() != 0) pt.y = (pt.y - rc.top) * sz.cy / rc.Height();
	}
}

void CXTPMarkupPolyline::OnRender(CXTPMarkupDrawingContext* pDC)
{
	CXTPMarkupStrokeStyle strokeStyle;
	GetStrokeStyle(&strokeStyle);

	if (strokeStyle.nStrokeThickness <= 0)
		return;

	CXTPMarkupPointCollection* pPoints = GetPoints();
	if (!pPoints)
		return;

	const CXTPMarkupPointCollection::CPointArray& arr = pPoints->GetPoints();

	if (GetStretch() != xtpMarkupStretchNone)
	{
		CXTPMarkupPointCollection::CPointArray arrStretch;
		pPoints->Stretch(arrStretch, GetRenderSize());

		pDC->Polyline(arrStretch.GetData(), (int)arrStretch.GetSize(), &strokeStyle);
	}
	else
	{
		pDC->Polyline(arr.GetData(), (int)arr.GetSize(), &strokeStyle);
	}
}




//////////////////////////////////////////////////////////////////////////
// CXTPMarkupRectangle

IMPLEMENT_MARKUPCLASS(L"Rectangle", CXTPMarkupRectangle, CXTPMarkupShape)

CXTPMarkupDependencyProperty* CXTPMarkupRectangle::m_pRadiusXProperty = NULL;
CXTPMarkupDependencyProperty* CXTPMarkupRectangle::m_pRadiusYProperty = NULL;

void CXTPMarkupRectangle::RegisterMarkupClass()
{
	m_pRadiusXProperty = CXTPMarkupDependencyProperty::Register(L"RadiusX", MARKUP_TYPE(CXTPMarkupInt), MARKUP_TYPE(CXTPMarkupRectangle),
		new CXTPMarkupPropertyMetadata(NULL, CXTPMarkupPropertyMetadata::flagAffectsRender));

	m_pRadiusYProperty = CXTPMarkupDependencyProperty::Register(L"RadiusY", MARKUP_TYPE(CXTPMarkupInt), MARKUP_TYPE(CXTPMarkupRectangle),
		new CXTPMarkupPropertyMetadata(NULL, CXTPMarkupPropertyMetadata::flagAffectsRender));

}

CXTPMarkupRectangle::CXTPMarkupRectangle()
{
}

CXTPMarkupRectangle::~CXTPMarkupRectangle()
{

}

CSize CXTPMarkupRectangle::MeasureOverride(CXTPMarkupDrawingContext* /*pDC*/, CSize szAvailableSize)
{
	CSize szBound(0, 0);

	if (GetStretch() != xtpMarkupStretchNone)
	{
		if (szAvailableSize.cx < INT_MAX)
			szBound.cx = szAvailableSize.cx;

		if (szAvailableSize.cy < INT_MAX)
			szBound.cy = szAvailableSize.cy;
	}

	return szBound;
}

void CXTPMarkupRectangle::OnRender(CXTPMarkupDrawingContext* pDC)
{
	CXTPMarkupBrush* pStrokeBrush = GetStroke();
	CXTPMarkupBrush* pFillBrush = GetFill();

	if (!pStrokeBrush && !pFillBrush)
		return;

	int nStroke = pStrokeBrush ? GetStrokeThickness() : 0;

	CRect rc(0, 0, GetRenderSize().cx, GetRenderSize().cy);
	if (rc.Width() == 0 || rc.Height() == 0)
		return;

	double nRadiusX = GetRadiusX(), nRadiusY = GetRadiusY();
	nRadiusX = min((double)(rc.Width() - nStroke) / 2, nRadiusX);
	nRadiusY = min((double)(rc.Height() - nStroke) / 2, nRadiusY);

	double* pnCorners = NULL;
	if (nRadiusX > 0 && nRadiusY > 0)
	{
		pnCorners = new double[8];
		pnCorners[0] = pnCorners[3] = pnCorners[4] = pnCorners[7] = (double)nRadiusY;
		pnCorners[1] = pnCorners[2] = pnCorners[5] = pnCorners[6] = (double)nRadiusX;
	}

	if (pFillBrush)
	{
		CRect rcFill(rc);
		rcFill.DeflateRect(nStroke / 2, nStroke / 2);

		pDC->FillRectangle(rcFill, pFillBrush, pnCorners);
	}

	if (nStroke > 0)
	{
		CXTPMarkupThickness strokeThickness(nStroke);
		pDC->DrawRectangle(rc, pStrokeBrush, &strokeThickness, pnCorners);
	}

	if (pnCorners) delete[] pnCorners;
}


//////////////////////////////////////////////////////////////////////////
// CXTPMarkupEllipse


IMPLEMENT_MARKUPCLASS(L"Ellipse", CXTPMarkupEllipse, CXTPMarkupShape)

void CXTPMarkupEllipse::RegisterMarkupClass()
{

}

CXTPMarkupEllipse::CXTPMarkupEllipse()
{
}

CXTPMarkupEllipse::~CXTPMarkupEllipse()
{

}

CSize CXTPMarkupEllipse::MeasureOverride(CXTPMarkupDrawingContext* /*pDC*/, CSize szAvailableSize)
{
	CSize szBound(0, 0);

	if (GetStretch() != xtpMarkupStretchNone)
	{
		if (szAvailableSize.cx < INT_MAX)
			szBound.cx = szAvailableSize.cx;

		if (szAvailableSize.cy < INT_MAX)
			szBound.cy = szAvailableSize.cy;
	}

	return szBound;
}

void CXTPMarkupEllipse::OnRender(CXTPMarkupDrawingContext* pDC)
{

	CXTPMarkupStrokeStyle strokeStyle;
	GetStrokeStyle(&strokeStyle);

	CXTPMarkupBrush* pFillBrush = GetFill();

	if (!strokeStyle.pStrokeBrush && !pFillBrush)
		return;

	pDC->Ellipse(CRect(0, 0, GetRenderSize().cx, GetRenderSize().cy), &strokeStyle, pFillBrush);
}

CXTPMarkupInputElement* CXTPMarkupEllipse::InputHitTestOverride(CPoint point) const
{
	if (m_szRenderSize.cx < 1 || m_szRenderSize.cy < 1)
		return (CXTPMarkupInputElement*)this;

   // Determine radii
	double a = m_szRenderSize.cx / 2;
	double b = m_szRenderSize.cy / 2;

	double x = point.x - a;
	double y = point.y - b;

	return ((x * x) / (a * a) + (y * y) / (b * b) <= 1) ? (CXTPMarkupInputElement*)this : NULL;
}


//////////////////////////////////////////////////////////////////////////
// CXTPMarkupLine


CXTPMarkupDependencyProperty* CXTPMarkupLine::m_pX1Property = NULL;
CXTPMarkupDependencyProperty* CXTPMarkupLine::m_pY1Property = NULL;
CXTPMarkupDependencyProperty* CXTPMarkupLine::m_pX2Property = NULL;
CXTPMarkupDependencyProperty* CXTPMarkupLine::m_pY2Property = NULL;


IMPLEMENT_MARKUPCLASS(L"Line", CXTPMarkupLine, CXTPMarkupShape)

void CXTPMarkupLine::RegisterMarkupClass()
{
	m_pX1Property = CXTPMarkupDependencyProperty::Register(L"X1", MARKUP_TYPE(CXTPMarkupInt), MARKUP_TYPE(CXTPMarkupLine),
		new CXTPMarkupPropertyMetadata(NULL, CXTPMarkupPropertyMetadata::flagAffectsMeasure));

	m_pY1Property = CXTPMarkupDependencyProperty::Register(L"Y1", MARKUP_TYPE(CXTPMarkupInt), MARKUP_TYPE(CXTPMarkupLine),
		new CXTPMarkupPropertyMetadata(NULL, CXTPMarkupPropertyMetadata::flagAffectsMeasure));

	m_pX2Property = CXTPMarkupDependencyProperty::Register(L"X2", MARKUP_TYPE(CXTPMarkupInt), MARKUP_TYPE(CXTPMarkupLine),
		new CXTPMarkupPropertyMetadata(NULL, CXTPMarkupPropertyMetadata::flagAffectsMeasure));

	m_pY2Property = CXTPMarkupDependencyProperty::Register(L"Y2", MARKUP_TYPE(CXTPMarkupInt), MARKUP_TYPE(CXTPMarkupLine),
		new CXTPMarkupPropertyMetadata(NULL, CXTPMarkupPropertyMetadata::flagAffectsMeasure));
}

CXTPMarkupLine::CXTPMarkupLine()
{
}

CXTPMarkupLine::~CXTPMarkupLine()
{

}

int CXTPMarkupLine::GetX1() const
{
	CXTPMarkupInt* pValue = MARKUP_STATICCAST(CXTPMarkupInt, GetValue(m_pX1Property));
	return pValue != NULL ? (int)*pValue : 0;
}

int CXTPMarkupLine::GetX2() const
{
	CXTPMarkupInt* pValue = MARKUP_STATICCAST(CXTPMarkupInt, GetValue(m_pX2Property));
	return pValue != NULL ? (int)*pValue : 0;
}

int CXTPMarkupLine::GetY1() const
{
	CXTPMarkupInt* pValue = MARKUP_STATICCAST(CXTPMarkupInt, GetValue(m_pY1Property));
	return pValue != NULL ? (int)*pValue : 0;
}

int CXTPMarkupLine::GetY2() const
{
	CXTPMarkupInt* pValue = MARKUP_STATICCAST(CXTPMarkupInt, GetValue(m_pY2Property));
	return pValue != NULL ? (int)*pValue : 0;
}

CSize CXTPMarkupLine::MeasureOverride(CXTPMarkupDrawingContext* /*pDC*/, CSize szAvailableSize)
{
	int x1 = GetX1();
	int x2 = GetX2();
	int y1 = GetY1();
	int y2 = GetY2();

	int x = max(x1, x2);
	int y = max(y1, y2);

	if ((x1 == x2 || y1 == y2) && GetStroke())
	{
		int nStroke = (GetStrokeThickness() + 1) / 2;

		if (x1 == x2) x += nStroke;
		if (y1 == y2) y += nStroke;
	}

	CSize szBound(x, y);

	if (GetStretch() != xtpMarkupStretchNone)
	{
		if (szAvailableSize.cx < INT_MAX)
			szBound.cx = szAvailableSize.cx;

		if (szAvailableSize.cy < INT_MAX)
			szBound.cy = szAvailableSize.cy;
	}
	return szBound;

}

void CXTPMarkupLine::GetPoints(int& x1, int& y1, int& x2, int& y2) const
{
	x1 = GetX1();
	x2 = GetX2();
	y1 = GetY1();
	y2 = GetY2();

	if (GetStretch() != xtpMarkupStretchNone)
	{
		int x = max(x1, x2);
		int y = max(y1, y2);

		CSize sz = GetRenderSize();
		if (x1 == x2)
			x1 = x2 = sz.cx / 2;
		else
		{
			x1 = (x1 == x ? sz.cx : 0);
			x2 = (x2 == x ? sz.cx : 0);
		}

		if (y1 == y2)
			y1 = y2 = sz.cy / 2;
		else
		{
			y1 = (y1 == y ? sz.cy : 0);
			y2 = (y2 == y ? sz.cy : 0);
		}
	}
}

void CXTPMarkupLine::OnRender(CXTPMarkupDrawingContext* pDC)
{
	CXTPMarkupStrokeStyle strokeStyle;
	GetStrokeStyle(&strokeStyle);

	if (strokeStyle.nStrokeThickness <= 0)
		return;

	int x1, x2, y1, y2;
	GetPoints(x1, y1, x2, y2);

	if (x1 == 0 && x2 == 0 && y1 == 0 && y2 == 0)
		return;

	pDC->DrawLine(x1, y1, x2, y2, &strokeStyle);
}

CXTPMarkupInputElement* CXTPMarkupLine::InputHitTestOverride(CPoint point) const
{
	if (!GetStroke())
		return NULL;

	int nStroke = GetStrokeThickness();
	if (nStroke == 0)
		return NULL;

	int x1, x2, y1, y2;
	GetPoints(x1, y1, x2, y2);

	double x = x2 - x1;
	double y = y2 - y1;

	double xp = point.x - x1;
	double yp = point.y - y1;

	double s = (double)nStroke / 2.0;

	if (xp + s < min(x, 0) || xp - s > max(x, 0) || yp + s < min(y, 0) || yp - s > max(y, 0))
		return NULL;

	if (x == 0)
		return fabs(xp) <= s ? (CXTPMarkupInputElement*)this : NULL;

	double yStroke = fabs(s / cos(atan(y / x)));

	double y0 = y * xp / (double)x;

	return fabs(y0 - yp) <= yStroke ? (CXTPMarkupInputElement*)this : NULL;
}



//////////////////////////////////////////////////////////////////////////
// CXTPMarkupPathGeometryBuilder

CXTPMarkupPathGeometryBuilder::CXTPMarkupPathGeometryBuilder()
{
	m_lpszValue = NULL;
	m_nLength = 0;
	m_nIndex = 0;
	m_cToken = 0;
	m_bFigureStarted = FALSE;
	m_pBuilder = 0;
	m_nFillRule = 0;
}

void CXTPMarkupPathGeometryBuilder::ThrowBadToken()
{
	if (m_pBuilder)
	{
		CString strError;
		strError.Format(_T("Unexpected token encountered at position '%i'"), m_nIndex);
		m_pBuilder->ThrowBuilderException(strError);
	}
	else
	{
		AfxThrowMemoryException();
	}
}

BOOL CXTPMarkupPathGeometryBuilder::SkipWhiteSpace(BOOL allowComma)
{
	BOOL flag = FALSE;

	while (More())
	{
		WCHAR c = m_lpszValue[m_nIndex];

		switch (c)
		{
		case '\t':
		case '\n':
		case '\r':
		case ' ':
			break;

		case ',':
			if (allowComma)
			{
				flag = TRUE;
				allowComma = FALSE;
			}
			else
			{
				ThrowBadToken();
			}
			break;

		default:
			return flag;
			break;
		}
		m_nIndex++;
	}
	return flag;
}

BOOL CXTPMarkupPathGeometryBuilder::More() const
{
	return m_nIndex < m_nLength;
}

BOOL CXTPMarkupPathGeometryBuilder::ReadToken()
{
	SkipWhiteSpace(FALSE);
	if (More())
	{
		m_cToken = m_lpszValue[m_nIndex++];
		return TRUE;
	}
	return FALSE;
}

BOOL CXTPMarkupPathGeometryBuilder::IsNumber(BOOL allowComma)
{
	BOOL flag = SkipWhiteSpace(allowComma);
	if (More())
	{
		m_cToken = m_lpszValue[m_nIndex];
		if ((m_cToken == '.') || (m_cToken == '-') || (m_cToken == '+') || ((m_cToken >= '0') && (m_cToken <= '9')))
		{
			return TRUE;
		}
	}
	if (flag)
	{
		ThrowBadToken();
	}
	return FALSE;
}


MARKUP_POINTF CXTPMarkupPathGeometryBuilder::ReadPoint(WCHAR cmd, BOOL allowcomma)
{
	MARKUP_POINTF pt;
	pt.x = ReadNumber(allowcomma);
	pt.y = ReadNumber(TRUE);
	if (cmd >= 'a')
	{
		pt.x += m_lastPoint.x;
		pt.y += m_lastPoint.y;
	}
	return pt;
}

float CXTPMarkupPathGeometryBuilder::ReadNumber(BOOL allowComma)
{
	if (!IsNumber(allowComma))
	{
		ThrowBadToken();
	}

	BOOL bSign = FALSE;

	if (m_lpszValue[m_nIndex] == '+')
	{
		m_nIndex++;
	}
	else if (m_lpszValue[m_nIndex] == '-')
	{
		m_nIndex++;
		bSign = TRUE;
	}

	float dValue = 0;

	while (m_lpszValue[m_nIndex] >= '0' && m_lpszValue[m_nIndex] <= '9')
	{
		WCHAR c = m_lpszValue[m_nIndex];
		dValue = 10 * dValue + (c - '0');

		m_nIndex++;
	}
	if (m_lpszValue[m_nIndex] == '.')
	{
		float dDecimal = 1;

		m_nIndex++;
		while (m_lpszValue[m_nIndex] >= '0' && m_lpszValue[m_nIndex] <= '9')
		{
			WCHAR c = m_lpszValue[m_nIndex];

			dDecimal /= 10;
			dValue += dDecimal * float(c - '0');

			m_nIndex++;
		}
	}


	return bSign ? -dValue : dValue;
}

void CXTPMarkupPathGeometryBuilder::EnsureFigure()
{
	if (!m_bFigureStarted)
	{
		BeginFigure(m_lastStart.x, m_lastStart.y);
		m_bFigureStarted = TRUE;
	}
}

MARKUP_POINTF CXTPMarkupPathGeometryBuilder::Reflect()
{
	MARKUP_POINTF pt = {(2.0f * m_lastPoint.x) - m_secondLastPoint.x, (2.0f * m_lastPoint.y) - m_secondLastPoint.y};
	return pt;
}

void CXTPMarkupPathGeometryBuilder::Parse(CXTPMarkupBuilder* pBuilder, LPCWSTR lpszValue, int nLength)
{
	m_pBuilder = pBuilder;
	m_lpszValue = lpszValue;
	m_nLength = nLength;

	m_arrPoints.RemoveAll();
	m_arrTypes.RemoveAll();

	MARKUP_POINTF ptZero = {0, 0};
	m_secondLastPoint = ptZero;
	m_lastPoint = ptZero;
	m_lastStart = ptZero;
	m_bFigureStarted = FALSE;

	BOOL bFirstToken = TRUE;
	WCHAR ch3 = ' ';

	while (ReadToken())
	{
		WCHAR cmd = m_cToken;
		if (bFirstToken)
		{
			if (cmd == 'F')
			{
				if (!IsNumber(FALSE))
					ThrowBadToken();

				if (m_lpszValue[m_nIndex] != '0' && m_lpszValue[m_nIndex] != '1')
					ThrowBadToken();

				m_nFillRule = m_lpszValue[m_nIndex] - '0';
				m_nIndex++;

				continue;
			}
			if ((cmd != 'M') && (cmd != 'm'))
			{
				ThrowBadToken();
			}
			bFirstToken = FALSE;
		}

		switch (cmd)
		{
			case 'L':
			case 'V':
			case 'H':
			case 'h':
			case 'l':
			case 'v':
			{
				EnsureFigure();
				do
				{
					switch (cmd)
					{
					case 'h':
						m_lastPoint.x += ReadNumber(FALSE);
						break;

					case 'l':
						m_lastPoint = ReadPoint(cmd, FALSE);
						break;

					case 'v':
						m_lastPoint.y += ReadNumber(FALSE);
						break;

					case 'H':
						m_lastPoint.x = ReadNumber(FALSE);
						break;

					case 'L':
						m_lastPoint = ReadPoint(cmd, FALSE);
						break;

					case 'V':
						m_lastPoint.y = ReadNumber(FALSE);
						break;
					}
					LineTo(m_lastPoint.x, m_lastPoint.y);
				}
				while (IsNumber(TRUE));
				ch3 = 'L';
				continue;
			}

			case 'M':
			case 'm':
			{
				m_lastPoint = ReadPoint(cmd, FALSE);
				BeginFigure(m_lastPoint.x, m_lastPoint.y);
				m_bFigureStarted = TRUE;
				m_lastStart = m_lastPoint;
				ch3 = 'M';
				while (IsNumber(TRUE))
				{
					m_lastPoint = ReadPoint(cmd, FALSE);
					LineTo(m_lastPoint.x, m_lastPoint.y);
					ch3 = 'L';
				}
				continue;
			}

			case 'S':
			case 'C':
			case 'c':
			case 's':
				{
					EnsureFigure();
					do
					{
						MARKUP_POINTF point;
						switch (cmd)
						{
						case 's':
						case 'S':
							if (ch3 == 'C')
							{
								point = Reflect();
							}
							else
							{
								point = m_lastPoint;
							}
							m_secondLastPoint = ReadPoint(cmd, FALSE);
							break;

						default:
							point = ReadPoint(cmd, FALSE);
							m_secondLastPoint = ReadPoint(cmd, TRUE);
							break;
						}
						m_lastPoint = ReadPoint(cmd, TRUE);
						BezierTo(point.x, point.y, m_secondLastPoint.x, m_secondLastPoint.y, m_lastPoint.x, m_lastPoint.y);
						ch3 = 'C';
					}
					while (IsNumber(TRUE));
					continue;
				}

			case 'Z':
			case 'z':
			{
				EnsureFigure();
				CloseFigure();
				m_bFigureStarted = FALSE;
				ch3 = 'Z';
				m_lastPoint = m_lastStart;
				continue;
			}

			default:
				ThrowBadToken();
		}
	}
}

CXTPMarkupPathGeometry* CXTPMarkupPathGeometryBuilder::CreateGeometry() const
{
	return new CXTPMarkupPathGeometry(m_arrPoints.GetData(), m_arrTypes.GetData(), (int)m_arrTypes.GetSize());
}

void CXTPMarkupPathGeometryBuilder::BeginFigure(float x, float y)
{
	MARKUP_POINTF startPoint = {x, y};
	m_arrPoints.Add(startPoint);
	m_arrTypes.Add(xtpMarkupPathPointTypeStart);
}

void CXTPMarkupPathGeometryBuilder::BezierTo(float x1, float y1, float x2, float y2, float x3, float y3)
{
	MARKUP_POINTF point1 = {x1, y1};
	MARKUP_POINTF point2 = {x2, y2};
	MARKUP_POINTF point3 = {x3, y3};

	m_arrPoints.Add(point1);
	m_arrPoints.Add(point2);
	m_arrPoints.Add(point3);

	m_arrTypes.Add(xtpMarkupPathPointTypeBezier);
	m_arrTypes.Add(xtpMarkupPathPointTypeBezier);
	m_arrTypes.Add(xtpMarkupPathPointTypeBezier);
}

void CXTPMarkupPathGeometryBuilder::BezierTo(float x1, float y1, float x2, float y2)
{
	BezierTo(x1, y1, x2, y2, x2, y2);
}

void CXTPMarkupPathGeometryBuilder::LineTo(float x, float y)
{
	MARKUP_POINTF point = {x, y};
	m_arrPoints.Add(point);
	m_arrTypes.Add(xtpMarkupPathPointTypeLine);
}

void CXTPMarkupPathGeometryBuilder::CloseFigure()
{
	if (m_arrTypes.GetSize() > 0)
	{
		m_arrTypes[m_arrTypes.GetSize() - 1] = BYTE(m_arrTypes[m_arrTypes.GetSize() - 1] | xtpMarkupPathPointTypeCloseSubpath);
	}
}


//////////////////////////////////////////////////////////////////////////
// CXTPMarkupPathGeometry

IMPLEMENT_MARKUPCLASS(NULL, CXTPMarkupPathGeometry, CXTPMarkupObject)

void CXTPMarkupPathGeometry::RegisterMarkupClass()
{

}

CXTPMarkupPathGeometry::CXTPMarkupPathGeometry()
{
	m_nCount = 0;
	m_pPoints = NULL;
	m_pTypes = NULL;
	m_rcBounds.SetRectEmpty();
	m_nFillRule = 0;
	m_nPixelOffsetMode = 0;
}

CXTPMarkupPathGeometry::CXTPMarkupPathGeometry(const MARKUP_POINTF* pPoints, const BYTE* pTypes, int nCount)
{
	m_nCount = nCount;
	m_pPoints = NULL;
	m_pTypes = NULL;
	m_nFillRule = 0;
	m_nPixelOffsetMode = 0;

	m_rcBounds.SetRectEmpty();

	if (nCount > 0)
	{
		m_pPoints = new MARKUP_POINTF[nCount];
		MEMCPY_S(m_pPoints, pPoints, sizeof(MARKUP_POINTF) * nCount);

		m_pTypes = new BYTE[nCount];
		MEMCPY_S(m_pTypes, pTypes, sizeof(BYTE) * nCount);
	}

	UpdateBounds();
}

void CXTPMarkupPathGeometry::UpdateBounds()
{
	m_rcBounds.SetRectEmpty();
	if (m_nCount > 0)
	{
		m_rcBounds.SetRect(INT_MAX, INT_MAX, -INT_MAX, -INT_MAX);

		for (int i = 0; i < m_nCount; i++)
		{
			const MARKUP_POINTF& pt = m_pPoints[i];
			if (pt.x > m_rcBounds.right) m_rcBounds.right = (LONG)ceil(pt.x);
			if (pt.y > m_rcBounds.bottom) m_rcBounds.bottom = (LONG)ceil(pt.y);
			if (pt.x < m_rcBounds.left) m_rcBounds.left = (LONG)floor(pt.x);
			if (pt.y < m_rcBounds.top) m_rcBounds.top = (LONG)floor(pt.y);
		}
	}
};

CXTPMarkupPathGeometry::~CXTPMarkupPathGeometry()
{
	if (m_pPoints)
	{
		delete[] m_pPoints;
	}
	if (m_pTypes)
	{
		delete[] m_pTypes;
	}
}

CXTPMarkupPathGeometry* CXTPMarkupPathGeometry::Stretch(CSize sz) const
{
	CXTPMarkupPathGeometry* pGeometry = new CXTPMarkupPathGeometry();

	pGeometry->m_pPoints = new MARKUP_POINTF[m_nCount];
	pGeometry->m_pTypes = new BYTE[m_nCount];
	pGeometry->m_nCount = m_nCount;
	pGeometry->m_nFillRule = m_nFillRule;

	CRect rc = GetBounds();
	if (rc.Width() == 0 || rc.Height() == 0)
		return pGeometry;

	for (int i = 0; i < m_nCount; i++)
	{
		MARKUP_POINTF pt = m_pPoints[i];
		pt.x = (pt.x - rc.left) * sz.cx / rc.Width();
		pt.y = (pt.y - rc.top) * sz.cy / rc.Height();
		pGeometry->m_pPoints[i] = pt;
	}

	MEMCPY_S(pGeometry->m_pTypes, m_pTypes, sizeof(BYTE) * m_nCount);
	pGeometry->UpdateBounds();

	return pGeometry;
}

CXTPMarkupObject* CXTPMarkupPathGeometry::ConvertFrom(CXTPMarkupBuilder* pBuilder, CXTPMarkupObject* pObject) const
{
	if (IsStringObject(pObject))
	{
		CXTPMarkupString* pString = (CXTPMarkupString*)pObject;

		CXTPMarkupPathGeometryBuilder builder;

		builder.Parse(pBuilder, (LPCWSTR)*pString, pString->GetLength());

		return builder.CreateGeometry();
	}

	return NULL;
}


//////////////////////////////////////////////////////////////////////////
// CXTPMarkupPath


CXTPMarkupDependencyProperty* CXTPMarkupPath::m_pDataProperty = NULL;

IMPLEMENT_MARKUPCLASS(L"Path", CXTPMarkupPath, CXTPMarkupShape)

void CXTPMarkupPath::RegisterMarkupClass()
{
	m_pDataProperty = CXTPMarkupDependencyProperty::Register(L"Data", MARKUP_TYPE(CXTPMarkupPathGeometry), MARKUP_TYPE(CXTPMarkupPath),
		new CXTPMarkupPropertyMetadata(NULL, CXTPMarkupPropertyMetadata::flagAffectsMeasure));
}

CXTPMarkupPath::CXTPMarkupPath()
{
}

CXTPMarkupPath::~CXTPMarkupPath()
{

}

CXTPMarkupPathGeometry* CXTPMarkupPath::GetGeometry() const
{
	return MARKUP_STATICCAST(CXTPMarkupPathGeometry, GetValue(m_pDataProperty));
}

CSize CXTPMarkupPath::MeasureOverride(CXTPMarkupDrawingContext* /*pDC*/, CSize szAvailableSize)
{
	CXTPMarkupPathGeometry* pGeometry = GetGeometry();
	if (!pGeometry)
		return CSize(0, 0);

	CRect rcBounds = pGeometry->GetBounds();

	CSize szBound(max(rcBounds.Width(), rcBounds.right), max(rcBounds.Height(),rcBounds.bottom));

	if (GetStretch() != xtpMarkupStretchNone)
	{
		if (szAvailableSize.cx < INT_MAX)
			szBound.cx = szAvailableSize.cx;

		if (szAvailableSize.cy < INT_MAX)
			szBound.cy = szAvailableSize.cy;
	}
	return szBound;
}

void CXTPMarkupPath::OnRender(CXTPMarkupDrawingContext* pDC)
{

	CXTPMarkupStrokeStyle strokeStyle;
	GetStrokeStyle(&strokeStyle);

	CXTPMarkupBrush* pFillBrush = GetFill();

	if (!strokeStyle.pStrokeBrush && !pFillBrush)
		return;

	CXTPMarkupPathGeometry* pGeometry = GetGeometry();
	if (!pGeometry)
		return;

	if (GetStretch() != xtpMarkupStretchNone)
	{
		CXTPMarkupPathGeometry* pGeometryStretch = pGeometry->Stretch(GetRenderSize());
		pDC->DrawPath(pGeometryStretch, &strokeStyle, pFillBrush);
		delete pGeometryStretch;
	}
	else
	{
		pDC->DrawPath(pGeometry, &strokeStyle, pFillBrush);
	}
}

