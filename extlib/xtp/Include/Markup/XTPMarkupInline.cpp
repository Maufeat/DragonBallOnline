// XTPMarkupInline.cpp: implementation of the CXTPMarkupInline class.
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

#include "Common/XTPSystemHelpers.h"
#include "Common/XTPResourceManager.h"

#include "XTPMarkupObject.h"
#include "XTPMarkupInputElement.h"
#include "XTPMarkupUIElement.h"
#include "XTPMarkupFrameworkElement.h"
#include "XTPMarkupControl.h"
#include "XTPMarkupResourceDictionary.h"
#include "XTPMarkupInline.h"
#include "XTPMarkupDrawingContext.h"
#include "XTPMarkupBuilder.h"
#include "XTPMarkupTextBlock.h"
#include "XTPMarkupContext.h"
#include "XTPMarkupButton.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
// CXTPMarkupFrameworkContentElement

CXTPMarkupDependencyProperty* CXTPMarkupFrameworkContentElement::m_pTagProperty = NULL;

IMPLEMENT_MARKUPCLASS(L"FrameworkContentElement", CXTPMarkupFrameworkContentElement, CXTPMarkupInputElement);

void CXTPMarkupFrameworkContentElement::RegisterMarkupClass()
{
	CXTPMarkupFrameworkElement::RegisterType();

	m_pTagProperty = CXTPMarkupFrameworkElement::m_pTagProperty->AddOwner(MARKUP_TYPE(CXTPMarkupFrameworkContentElement));
}

CXTPMarkupFrameworkContentElement::CXTPMarkupFrameworkContentElement()
{
}

void CXTPMarkupFrameworkContentElement::OnPropertyChanged(CXTPMarkupDependencyProperty* pProperty, CXTPMarkupObject* pOldValue, CXTPMarkupObject* pNewValue)
{
	CXTPMarkupInputElement::OnPropertyChanged(pProperty, pOldValue, pNewValue);

	FireTriggers(pProperty, pNewValue);

	if (pProperty->GetFlags() & CXTPMarkupPropertyMetadata::flagAffectsMeasure)
	{
		CXTPMarkupFrameworkElement* pParent = GetParent();
		if (pParent) pParent->InvalidateMeasure();
	}

	if (pProperty->GetFlags() & CXTPMarkupPropertyMetadata::flagAffectsArrange)
	{
		CXTPMarkupFrameworkElement* pParent = GetParent();
		if (pParent) pParent->InvalidateArrange();
	}

	if (pProperty->GetFlags() & CXTPMarkupPropertyMetadata::flagAffectsRender)
	{
		CXTPMarkupFrameworkElement* pParent = GetParent();
		if (pParent) pParent->InvalidateVisual();
	}
}

CXTPMarkupFrameworkElement* CXTPMarkupFrameworkContentElement::GetParent() const
{
	CXTPMarkupObject* pParent = m_pLogicalParent;
	while (pParent)
	{
		if (pParent->IsKindOf(MARKUP_TYPE(CXTPMarkupFrameworkElement)))
			return (CXTPMarkupFrameworkElement*)pParent;

		pParent = pParent->GetLogicalParent();
	}

	return NULL;
}


//////////////////////////////////////////////////////////////////////////
//
CXTPMarkupDependencyProperty* CXTPMarkupTextElement::m_pBackgroundProperty = NULL;
CXTPMarkupDependencyProperty* CXTPMarkupTextElement::m_pForegroundProperty = NULL;
CXTPMarkupDependencyProperty* CXTPMarkupTextElement::m_pFontSizeProperty = NULL;
CXTPMarkupDependencyProperty* CXTPMarkupTextElement::m_pFontWeightProperty = NULL;
CXTPMarkupDependencyProperty* CXTPMarkupTextElement::m_pFontFamilyProperty = NULL;
CXTPMarkupDependencyProperty* CXTPMarkupTextElement::m_pFontStyleProperty = NULL;
CXTPMarkupDependencyProperty* CXTPMarkupTextElement::m_pTextDecorationsProperty = NULL;
CXTPMarkupDependencyProperty* CXTPMarkupTextElement::m_pFontQualityProperty = NULL;
CXTPMarkupDependencyProperty* CXTPMarkupTextElement::m_pFontCharsetProperty = NULL;

//////////////////////////////////////////////////////////////////////////
// CXTPMarkupTextElement

IMPLEMENT_MARKUPCLASS(L"TextElement", CXTPMarkupTextElement, CXTPMarkupFrameworkContentElement);

void CXTPMarkupTextElement::RegisterMarkupClass()
{
	m_pBackgroundProperty = CXTPMarkupDependencyProperty::RegisterAttached(L"Background", MARKUP_TYPE(CXTPMarkupBrush), MARKUP_TYPE(CXTPMarkupTextElement),
			new CXTPMarkupPropertyMetadata(NULL, CXTPMarkupPropertyMetadata::flagInherited | CXTPMarkupPropertyMetadata::flagAffectsRender));

	m_pForegroundProperty = CXTPMarkupDependencyProperty::RegisterAttached(L"Foreground", MARKUP_TYPE(CXTPMarkupBrush), MARKUP_TYPE(CXTPMarkupTextElement),
		new CXTPMarkupPropertyMetadata(NULL, CXTPMarkupPropertyMetadata::flagInherited | CXTPMarkupPropertyMetadata::flagAffectsRender));

	m_pFontSizeProperty = CXTPMarkupDependencyProperty::RegisterAttached(L"FontSize", MARKUP_TYPE(CXTPMarkupInt), MARKUP_TYPE(CXTPMarkupTextElement),
		new CXTPMarkupPropertyMetadata(NULL, &CXTPMarkupBuilder::ConvertLength, CXTPMarkupPropertyMetadata::flagInherited | CXTPMarkupPropertyMetadata::flagAffectsMeasure));

	m_pFontWeightProperty = CXTPMarkupDependencyProperty::RegisterAttached(L"FontWeight", MARKUP_TYPE(CXTPMarkupEnum), MARKUP_TYPE(CXTPMarkupTextElement),
		new CXTPMarkupPropertyMetadata(NULL, &CXTPMarkupBuilder::ConvertFontWeight, CXTPMarkupPropertyMetadata::flagInherited | CXTPMarkupPropertyMetadata::flagAffectsMeasure));

	m_pFontFamilyProperty = CXTPMarkupDependencyProperty::RegisterAttached(L"FontFamily", MARKUP_TYPE(CXTPMarkupString), MARKUP_TYPE(CXTPMarkupTextElement),
		new CXTPMarkupPropertyMetadata(NULL, CXTPMarkupPropertyMetadata::flagInherited | CXTPMarkupPropertyMetadata::flagAffectsMeasure));

	m_pFontStyleProperty = CXTPMarkupDependencyProperty::RegisterAttached(L"FontStyle", MARKUP_TYPE(CXTPMarkupEnum), MARKUP_TYPE(CXTPMarkupTextElement),
		new CXTPMarkupPropertyMetadata(NULL, &CXTPMarkupBuilder::ConvertFontStyle, CXTPMarkupPropertyMetadata::flagInherited | CXTPMarkupPropertyMetadata::flagAffectsMeasure));

	m_pTextDecorationsProperty = CXTPMarkupDependencyProperty::RegisterAttached(L"TextDecorations", MARKUP_TYPE(CXTPMarkupEnum), MARKUP_TYPE(CXTPMarkupTextElement),
		new CXTPMarkupPropertyMetadata(NULL, &CXTPMarkupBuilder::ConvertTextDecorations, CXTPMarkupPropertyMetadata::flagInherited | CXTPMarkupPropertyMetadata::flagAffectsRender));

	m_pFontQualityProperty = CXTPMarkupDependencyProperty::RegisterAttached(L"FontQuality", MARKUP_TYPE(CXTPMarkupEnum), MARKUP_TYPE(CXTPMarkupTextElement),
		new CXTPMarkupPropertyMetadata(NULL, &CXTPMarkupBuilder::ConvertFontQuality, CXTPMarkupPropertyMetadata::flagInherited | CXTPMarkupPropertyMetadata::flagAffectsRender));

	m_pFontCharsetProperty = CXTPMarkupDependencyProperty::RegisterAttached(L"FontCharset", MARKUP_TYPE(CXTPMarkupInt), MARKUP_TYPE(CXTPMarkupTextElement),
		new CXTPMarkupPropertyMetadata(NULL, CXTPMarkupPropertyMetadata::flagInherited | CXTPMarkupPropertyMetadata::flagAffectsRender));

}

CXTPMarkupTextElement::CXTPMarkupTextElement()
{

}

CXTPMarkupTextElement::~CXTPMarkupTextElement()
{

}

void CXTPMarkupTextElement::SetBackground(CXTPMarkupBrush* pBrush)
{
	SetValue(m_pBackgroundProperty, pBrush);
}

void CXTPMarkupTextElement::SetBackground(COLORREF clr)
{
	SetValue(m_pBackgroundProperty, new CXTPMarkupSolidColorBrush(clr));
}

void CXTPMarkupTextElement::SetBackground(CXTPMarkupObject* pObject, CXTPMarkupBrush* pBrush)
{
	pObject->SetValue(m_pBackgroundProperty, pBrush);
}

CXTPMarkupBrush* CXTPMarkupTextElement::GetBackground() const
{
	return MARKUP_STATICCAST(CXTPMarkupBrush, GetValue(m_pBackgroundProperty));
}

void CXTPMarkupTextElement::SetForeground(CXTPMarkupBrush* pBrush)
{
	SetValue(m_pForegroundProperty, pBrush);
}

void CXTPMarkupTextElement::SetForeground(COLORREF clr)
{
	SetValue(m_pForegroundProperty, new CXTPMarkupSolidColorBrush(clr));
}

void CXTPMarkupTextElement::SetForeground(CXTPMarkupObject* pObject, CXTPMarkupBrush* pBrush)
{
	pObject->SetValue(m_pForegroundProperty, pBrush);
}

CXTPMarkupBrush* CXTPMarkupTextElement::GetForeground() const
{
	return MARKUP_STATICCAST(CXTPMarkupBrush, GetValue(m_pForegroundProperty));
}


void CXTPMarkupTextElement::SetFontSize(int nFontSize)
{
	SetValue(m_pFontSizeProperty, new CXTPMarkupInt(nFontSize));
}

int CXTPMarkupTextElement::GetFontSize() const
{
	CXTPMarkupInt* pFontSize = MARKUP_STATICCAST(CXTPMarkupInt, GetValue(m_pFontSizeProperty));
	if (!pFontSize)
		return -12;

	return *pFontSize;
}

void CXTPMarkupTextElement::SetFontWeight(int nFontWeight)
{
	SetValue(m_pFontWeightProperty, CXTPMarkupEnum::CreateValue(nFontWeight));
}

int CXTPMarkupTextElement::GetFontWeight() const
{
	CXTPMarkupEnum* pFontWeigh = MARKUP_STATICCAST(CXTPMarkupEnum, GetValue(m_pFontWeightProperty));
	if (!pFontWeigh)
		return FW_NORMAL;

	return *pFontWeigh;
}

void CXTPMarkupTextElement::SetFontStyle(int nFontStyle)
{
	SetValue(m_pFontStyleProperty, CXTPMarkupEnum::CreateValue(nFontStyle));
}

int CXTPMarkupTextElement::GetFontStyle() const
{
	CXTPMarkupEnum* pFontStyle = MARKUP_STATICCAST(CXTPMarkupEnum, GetValue(m_pFontStyleProperty));
	if (!pFontStyle)
		return 0;

	return *pFontStyle;
}

void CXTPMarkupTextElement::SetTextDecorations(int nTextDecorations)
{
	SetValue(m_pTextDecorationsProperty, CXTPMarkupEnum::CreateValue(nTextDecorations));
}

int CXTPMarkupTextElement::GetTextDecorations() const
{
	CXTPMarkupEnum* pTextDecorations = MARKUP_STATICCAST(CXTPMarkupEnum, GetValue(m_pTextDecorationsProperty));
	if (!pTextDecorations)
		return 0;

	return *pTextDecorations;
}


void CXTPMarkupTextElement::SetFontFamily(LPCWSTR lpszFontFamily)
{
	SetValue(m_pFontFamilyProperty, CXTPMarkupString::CreateValue(lpszFontFamily));

}
LPCWSTR CXTPMarkupTextElement::GetFontFamily() const
{
	CXTPMarkupString* pFontFamily = MARKUP_STATICCAST(CXTPMarkupString, GetValue(m_pFontFamilyProperty));
	if (!pFontFamily)
		return NULL;

	return *pFontFamily;
}

CXTPMarkupInputElement* CXTPMarkupFrameworkContentElement::InputHitTest(CPoint /*point*/) const
{
	return (CXTPMarkupInputElement*)this;
}

CRect CXTPMarkupFrameworkContentElement::GetBoundRect() const
{
	return GetParent()->GetBoundRect();
}

//////////////////////////////////////////////////////////////////////////
// CXTPMarkupInline

CXTPMarkupDependencyProperty* CXTPMarkupInline::m_pBaselineAlignmentProperty = NULL;

IMPLEMENT_MARKUPCLASS(NULL, CXTPMarkupInline, CXTPMarkupTextElement);

void CXTPMarkupInline::RegisterMarkupClass()
{
	m_pBaselineAlignmentProperty = CXTPMarkupDependencyProperty::Register(L"BaselineAlignment", MARKUP_TYPE(CXTPMarkupEnum), MARKUP_TYPE(CXTPMarkupInline),
		new CXTPMarkupPropertyMetadata(NULL, &CXTPMarkupBuilder::ConvertBaselineAlignment, CXTPMarkupPropertyMetadata::flagAffectsArrange));
}


CXTPMarkupInline::CXTPMarkupInline()
{
	m_nIndex = -1;
}

CXTPMarkupInline::~CXTPMarkupInline()
{

}

POSITION CXTPMarkupInline::GetContentStartPosition() const
{
	return MARKUP_POSITION_EOF;
};

void CXTPMarkupInline::GetContentNextPosition(POSITION& pos) const
{
	pos = NULL;
}

BOOL CXTPMarkupInline::IsWordBreakPosition(POSITION /*pos*/) const
{
	return FALSE;
}

BOOL CXTPMarkupInline::IsLineBreakPosition(POSITION /*pos*/) const
{
	return FALSE;
}

BOOL CXTPMarkupInline::IsCaretReturnPosition(POSITION /*pos*/) const
{
	return FALSE;
}

BOOL CXTPMarkupInline::IsWhiteSpacePosition(POSITION /*pos*/) const
{
	return FALSE;
}

void CXTPMarkupInline::PrepareMeasure(CXTPMarkupDrawingContext* /*pDC*/)
{

}


CSize CXTPMarkupInline::Measure(CXTPMarkupDrawingContext* /*pDC*/, POSITION /*posStart*/, POSITION /*posEnd*/)
{
	return CSize(0, 0);
}

int CXTPMarkupInline::GetBaseline() const
{
	return 0;
}

void CXTPMarkupInline::Arrange(CRect /*rcFinalRect*/, POSITION /*posStart*/, POSITION /*posEnd*/)
{

}

void CXTPMarkupInline::Render(CXTPMarkupDrawingContext* /*pDC*/, CRect /*rc*/, POSITION /*posStart*/, POSITION /*posEnd*/)
{

}

CXTPMarkupInline* CXTPMarkupInline::GetFirstInline() const
{
	return (CXTPMarkupInline*)this;
}

CXTPMarkupInline* CXTPMarkupInline::GetNextInline() const
{
	CXTPMarkupInlineCollection* pOwner = MARKUP_DYNAMICCAST(CXTPMarkupInlineCollection, m_pLogicalParent);

	if (!pOwner)
		return NULL;

	if (pOwner->GetCount() > m_nIndex + 1)
		return pOwner->GetInline(m_nIndex + 1)->GetFirstInline();

	if (MARKUP_DYNAMICCAST(CXTPMarkupSpan, pOwner->GetLogicalParent()))
		return ((CXTPMarkupSpan*)(pOwner->GetLogicalParent()))->GetNextInline();

	return NULL;
}

CXTPMarkupTextBlock* CXTPMarkupInline::GetTextBlock() const
{
	return MARKUP_STATICCAST(CXTPMarkupTextBlock, GetParent());
}


//////////////////////////////////////////////////////////////////////////
// CXTPMarkupRun

CXTPMarkupDependencyProperty* CXTPMarkupRun::m_pTextProperty = NULL;

IMPLEMENT_MARKUPCLASS(L"Run", CXTPMarkupRun, CXTPMarkupInline);

void CXTPMarkupRun::RegisterMarkupClass()
{
	m_pTextProperty = CXTPMarkupDependencyProperty::Register(L"Text", MARKUP_TYPE(CXTPMarkupString), MARKUP_TYPE(CXTPMarkupRun),
		new CXTPMarkupPropertyMetadata(NULL, CXTPMarkupPropertyMetadata::flagAffectsMeasure));
}


CXTPMarkupRun::CXTPMarkupRun()
{
	m_nBaseline = 0;
	m_pFont = NULL;
}

CXTPMarkupRun::~CXTPMarkupRun()
{
	MARKUP_RELEASE(m_pFont);
}

void CXTPMarkupRun::OnFinalRelease()
{
	MARKUP_RELEASE(m_pFont);

	CXTPMarkupInline::OnFinalRelease();
}

void CXTPMarkupRun::SetContentObject(CXTPMarkupBuilder* pBuilder, CXTPMarkupObject* pContent)
{
	if (IsStringObject(pContent))
	{
		SetValue(m_pTextProperty, pContent);
	}
	else
	{
		CXTPMarkupInline::SetContentObject(pBuilder, pContent);
	}
}

BOOL CXTPMarkupRun::HasContentObject() const
{
	return GetValue(m_pTextProperty) != NULL;
}

int CXTPMarkupRun::GetBaseline() const
{
	return m_nBaseline;
}

CString CXTPMarkupRun::GetText() const
{
	CXTPMarkupString* pString = MARKUP_STATICCAST(CXTPMarkupString, GetValue(m_pTextProperty));
	if (!pString)
		return _T("");

	return CString((LPCWSTR)*pString);
}

LPCWSTR CXTPMarkupRun::GetTextW() const
{
	CXTPMarkupString* pString = MARKUP_STATICCAST(CXTPMarkupString, GetValue(m_pTextProperty));
	if (!pString)
		return L"";

	return (LPCWSTR)*pString;
}


void CXTPMarkupRun::SetText(LPCWSTR lpszText)
{
	SetValue(m_pTextProperty, CXTPMarkupString::CreateValue(lpszText));
}

void CXTPMarkupRun::SetText(CXTPMarkupString* pText)
{
	SetValue(m_pTextProperty, pText);
}

POSITION CXTPMarkupRun::GetContentStartPosition() const
{
	CXTPMarkupString* pString = MARKUP_STATICCAST(CXTPMarkupString, GetValue(m_pTextProperty));
	if (!pString)
		return MARKUP_POSITION_EOF;

	LPCWSTR lpszText = (LPCWSTR)(*pString);

	if ((!lpszText) || (*lpszText == '\0'))
		return MARKUP_POSITION_EOF;

	return (POSITION)lpszText;
}

void CXTPMarkupRun::GetContentNextPosition(POSITION& pos) const
{
	if (!pos || pos == MARKUP_POSITION_EOF)
		return;

	LPCWSTR lpszText = (LPCWSTR)pos;
	if (*lpszText == '\0')
	{
		pos = MARKUP_POSITION_EOF;
	}
	else
	{
		lpszText++;
		pos = (POSITION)lpszText;
	}
}

BOOL CXTPMarkupRun::IsWordBreakPosition(POSITION pos) const
{
	if (!pos)
		return FALSE;
	LPCWSTR lpszText = (LPCWSTR)pos;

	return *lpszText == _T(' ') || *lpszText == _T('\t') || *lpszText == _T('\n');
}

BOOL CXTPMarkupRun::IsWhiteSpacePosition(POSITION pos) const
{
	if (!pos)
		return FALSE;

	LPCWSTR lpszText = (LPCWSTR)pos;

	return *lpszText == _T(' ') || *lpszText == _T('\t');
}

BOOL CXTPMarkupRun::IsLineBreakPosition(POSITION pos) const
{
	if (!pos)
		return FALSE;
	LPCWSTR lpszText = (LPCWSTR)pos;

	return *lpszText == _T('\n');
}

BOOL CXTPMarkupRun::IsCaretReturnPosition(POSITION pos) const
{
	if (!pos)
		return FALSE;
	LPCWSTR lpszText = (LPCWSTR)pos;

	return *lpszText == _T('\r');
}

void CXTPMarkupRun::GetLogFont(LOGFONT* pLogFont) const
{
	memcpy(pLogFont, GetMarkupContext()->GetDefaultLogFont(), sizeof(LOGFONT));

	CXTPMarkupInt* pFontSize = MARKUP_STATICCAST(CXTPMarkupInt, GetValue(m_pFontSizeProperty));
	if (pFontSize)
	{
		pLogFont->lfHeight = - *pFontSize;
	}

	CXTPMarkupEnum* pFontWeight = MARKUP_STATICCAST(CXTPMarkupEnum, GetValue(m_pFontWeightProperty));
	if (pFontWeight)
	{
		pLogFont->lfWeight = *pFontWeight;
	}

	CXTPMarkupEnum* pFontStyle = MARKUP_STATICCAST(CXTPMarkupEnum, GetValue(m_pFontStyleProperty));
	if (pFontStyle)
	{
		pLogFont->lfItalic = *pFontStyle ? (BYTE)1 : (BYTE)0;
	}

	CXTPMarkupEnum* pFontQuality = MARKUP_STATICCAST(CXTPMarkupEnum, GetValue(m_pFontQualityProperty));
	if (pFontQuality && XTPSystemVersion()->IsClearTypeTextQualitySupported())
	{
		pLogFont->lfQuality = (BYTE)*pFontQuality;
	}

	CXTPMarkupInt* pFontCharset = MARKUP_STATICCAST(CXTPMarkupInt, GetValue(m_pFontCharsetProperty));
	if (pFontCharset)
	{
		pLogFont->lfCharSet = (BYTE)*pFontCharset;
	}

	CXTPMarkupString* pFontFamily = MARKUP_STATICCAST(CXTPMarkupString, GetValue(m_pFontFamilyProperty));
	if (pFontFamily)
	{
		LPCWSTR lpszFaceName = *pFontFamily;
		LPTSTR lpszLogFontFaceName = pLogFont->lfFaceName;

		while ((*lpszLogFontFaceName++ = (TCHAR)*(lpszFaceName++)) != 0);
	}
}

void CXTPMarkupRun::PrepareMeasure(CXTPMarkupDrawingContext* pDC)
{
	LOGFONT lf;
	GetLogFont(&lf);

	if (m_pFont == NULL || !CXTPMarkupContext::CompareFont(&m_pFont->m_lf, &lf))
	{
		CXTPMarkupFont* pFont = GetMarkupContext()->GetFont(&lf);
		MARKUP_RELEASE(m_pFont);

		m_pFont = pFont;
	}

	pDC->SetFont(m_pFont);

	TEXTMETRIC tm;

	HDC hDC = pDC->GetDC();
	GetTextMetrics(hDC, &tm);
	pDC->ReleaseDC(hDC);

	m_nBaseline = tm.tmDescent;
}

CSize CXTPMarkupRun::Measure(CXTPMarkupDrawingContext* pDC, POSITION posStart, POSITION posEnd)
{
	if (posStart == NULL || posEnd == NULL || posEnd == MARKUP_POSITION_EOF)
		return CSize(0, 0);

	pDC->SetFont(m_pFont);

	if (posEnd == posStart)
	{
		SIZE sz = pDC->GetTextExtent(L" ", 1);
		return CSize(0, sz.cy);
	}

	LPCWSTR lpszText = (LPCWSTR)posStart;
	int nCount = int(posEnd - posStart) / sizeof(WCHAR);

	SIZE sz = pDC->GetTextExtent(lpszText, nCount);

	return sz;
}

void CXTPMarkupRun::Render(CXTPMarkupDrawingContext* pDC, CRect rc, POSITION posStart, POSITION posEnd)
{
	if (posStart == NULL || posEnd == NULL || posEnd == posStart || posEnd == MARKUP_POSITION_EOF)
		return;

	LPCWSTR lpszText = (LPCWSTR)posStart;
	UINT nCount = UINT(posEnd - posStart) / sizeof(WCHAR);

	pDC->SetFont(m_pFont);
	pDC->DrawTextLine(lpszText, nCount, rc);
}

//////////////////////////////////////////////////////////////////////////
// CXTPMarkupLineBreak

IMPLEMENT_MARKUPCLASS(L"LineBreak", CXTPMarkupLineBreak, CXTPMarkupRun);

void CXTPMarkupLineBreak::RegisterMarkupClass()
{

}

CXTPMarkupLineBreak::CXTPMarkupLineBreak()
{
	SetText(L"\n");
}

//////////////////////////////////////////////////////////////////////////
// CXTPMarkupInlineCollection

IMPLEMENT_MARKUPCLASS(NULL, CXTPMarkupInlineCollection, CXTPMarkupCollection);

void CXTPMarkupInlineCollection::RegisterMarkupClass()
{

}
CXTPMarkupInlineCollection::CXTPMarkupInlineCollection()
{
	m_pElementType = MARKUP_TYPE(CXTPMarkupInline);
}

CXTPMarkupInlineCollection::~CXTPMarkupInlineCollection()
{
}

void CXTPMarkupInlineCollection::OnItemAdded(CXTPMarkupObject* pItem, int nIndex)
{
	((CXTPMarkupInline*)pItem)->m_nIndex = nIndex;
}

void CXTPMarkupInlineCollection::SetContentObject(CXTPMarkupBuilder* pBuilder, CXTPMarkupObject* pContent)
{
	CXTPMarkupInputElement* pParent = MARKUP_DYNAMICCAST(CXTPMarkupInputElement, m_pLogicalParent);
	ASSERT(pParent);
	if (!pParent)
	{
		pBuilder->ThrowBuilderException(CXTPMarkupBuilder::FormatString(_T("'%ls' object cannot be added to '%ls'. Object cannot be converted to type 'CXTPMarkupInline'"),
			(LPCTSTR)pContent->GetType()->m_lpszClassName, (LPCTSTR)GetType()->m_lpszClassName));
	}

	if (IsStringObject(pContent))
	{
		CXTPMarkupRun* pRun = MARKUP_CREATE(CXTPMarkupRun, pParent->GetMarkupContext());
		pRun->SetText((CXTPMarkupString*)pContent);
		Add(pRun);
	}
	else if (pContent->IsKindOf(MARKUP_TYPE(CXTPMarkupInline)))
	{
		Add((CXTPMarkupInline*)pContent);
	}
	else if  (pContent->IsKindOf(MARKUP_TYPE(CXTPMarkupUIElement)))
	{
		CXTPMarkupInlineUIContainer* pInlineUIContainer = MARKUP_CREATE(CXTPMarkupInlineUIContainer, pParent->GetMarkupContext());
		pInlineUIContainer->SetChild((CXTPMarkupUIElement*)pContent);
		Add(pInlineUIContainer);
	}
	else
	{
		pBuilder->ThrowBuilderException(CXTPMarkupBuilder::FormatString(_T("'%ls' object cannot be added to '%ls'. Object cannot be converted to type 'CXTPMarkupInline'"),
			(LPCTSTR)pContent->GetType()->m_lpszClassName, (LPCTSTR)GetType()->m_lpszClassName));
	}
}


//////////////////////////////////////////////////////////////////////////
// CXTPMarkupSpan

IMPLEMENT_MARKUPCLASS(L"Span", CXTPMarkupSpan, CXTPMarkupInline);

void CXTPMarkupSpan::RegisterMarkupClass()
{

}

CXTPMarkupSpan::CXTPMarkupSpan()
{
	m_pInlines = new CXTPMarkupInlineCollection();
	m_pInlines->SetLogicalParent(this);
}

CXTPMarkupSpan::~CXTPMarkupSpan()
{
	if (m_pInlines)
	{
		m_pInlines->SetLogicalParent(NULL);
		m_pInlines->Release();
	}
}

void CXTPMarkupSpan::SetContentObject(CXTPMarkupBuilder* pBuilder, CXTPMarkupObject* pContent)
{
	m_pInlines->SetContentObject(pBuilder, pContent);
}
BOOL CXTPMarkupSpan::HasContentObject() const
{
	return m_pInlines->HasContentObject();
}

BOOL CXTPMarkupSpan::AllowWhiteSpaceContent() const
{
	return TRUE;
}


CXTPMarkupInline* CXTPMarkupSpan::GetFirstInline() const
{
	return m_pInlines->GetCount() > 0 ? m_pInlines->GetInline(0)->GetFirstInline() : (CXTPMarkupInline*)this;
}

//////////////////////////////////////////////////////////////////////////
// CXTPMarkupBold

IMPLEMENT_MARKUPCLASS(L"Bold", CXTPMarkupBold, CXTPMarkupSpan);

void CXTPMarkupBold::RegisterMarkupClass()
{

}

CXTPMarkupBold::CXTPMarkupBold()
{
	SetFontWeight(FW_BOLD);

}

//////////////////////////////////////////////////////////////////////////
// CXTPMarkupHyperlink

CXTPMarkupRoutedEvent* CXTPMarkupHyperlink::m_pClickEvent = NULL;

IMPLEMENT_MARKUPCLASS(L"Hyperlink", CXTPMarkupHyperlink, CXTPMarkupSpan);

void CXTPMarkupHyperlink::RegisterMarkupClass()
{
	CXTPMarkupStyle::RegisterType();
	CXTPMarkupButtonBase::RegisterType();
	CXTPMarkupSolidColorBrush::RegisterType();
	CXTPMarkupHyperlink::RegisterType();

	CXTPMarkupType* pType = MARKUP_TYPE(CXTPMarkupHyperlink);

	CXTPMarkupStyle* pStyle = new CXTPMarkupStyle();
	pStyle->GetSetters()->Add(new CXTPMarkupSetter(CXTPMarkupHyperlink::m_pTextDecorationsProperty, CXTPMarkupEnum::CreateValue(1)));
	pStyle->GetSetters()->Add(new CXTPMarkupSetter(CXTPMarkupHyperlink::m_pForegroundProperty, new CXTPMarkupSolidColorBrush(RGB(0, 0, 255))));
	pStyle->GetSetters()->Add(new CXTPMarkupSetter(CXTPMarkupHyperlink::m_pCursorProperty, new CXTPMarkupInt(32649)));

	CXTPMarkupTriggerCollection* pTriggers = new CXTPMarkupTriggerCollection();
	CXTPMarkupTrigger* pTrigger = new CXTPMarkupTrigger(CXTPMarkupHyperlink::m_pIsMouseOverProperty, CXTPMarkupBool::CreateTrueValue());
	CXTPMarkupSetterColection* pSetters = new CXTPMarkupSetterColection();
	pSetters->Add(new CXTPMarkupSetter(CXTPMarkupHyperlink::m_pForegroundProperty, new CXTPMarkupSolidColorBrush(RGB(255, 0, 0))));
	pTrigger->SetSetters(pSetters);
	pTriggers->Add(pTrigger);
	pStyle->SetTriggers(pTriggers);

	pType->SetTypeStyle(pStyle);

	m_pClickEvent = (CXTPMarkupRoutedEvent*)CXTPMarkupButtonBase::m_pClickEvent->AddOwner(MARKUP_TYPE(CXTPMarkupHyperlink));
}

CXTPMarkupHyperlink::CXTPMarkupHyperlink()
{
	m_bPressed = FALSE;
}

void CXTPMarkupHyperlink::OnMouseLeftButtonUp(CXTPMarkupMouseButtonEventArgs* e)
{
	if (m_bPressed)
	{
		m_bPressed = FALSE;
		OnClick();
		e->SetHandled();
	}
}

void CXTPMarkupHyperlink::OnMouseLeftButtonDown(CXTPMarkupMouseButtonEventArgs* e)
{
	m_bPressed = TRUE;
	e->SetHandled();
}

void CXTPMarkupHyperlink::OnClick()
{
	CXTPMarkupRoutedEventArgs* e = new CXTPMarkupRoutedEventArgs(m_pClickEvent, this);
	RaiseEvent(e);

	e->Release();
}

//////////////////////////////////////////////////////////////////////////
// CXTPMarkupItalic

IMPLEMENT_MARKUPCLASS(L"Italic", CXTPMarkupItalic, CXTPMarkupSpan);

void CXTPMarkupItalic::RegisterMarkupClass()
{

}

CXTPMarkupItalic::CXTPMarkupItalic()
{
	SetFontStyle(1);
}

//////////////////////////////////////////////////////////////////////////
// CXTPMarkupUnderline

IMPLEMENT_MARKUPCLASS(L"Underline", CXTPMarkupUnderline, CXTPMarkupSpan);

void CXTPMarkupUnderline::RegisterMarkupClass()
{

}

CXTPMarkupUnderline::CXTPMarkupUnderline()
{
	SetTextDecorations(1);
}

//////////////////////////////////////////////////////////////////////////
// CXTPMarkupInlineUIContainer

IMPLEMENT_MARKUPCLASS(L"InlineUIContainer", CXTPMarkupInlineUIContainer, CXTPMarkupInline);

void CXTPMarkupInlineUIContainer::RegisterMarkupClass()
{

}

CXTPMarkupInlineUIContainer::CXTPMarkupInlineUIContainer()
{
	m_pChild = NULL;
}

CXTPMarkupInlineUIContainer::CXTPMarkupInlineUIContainer(CXTPMarkupUIElement* pElement)
{
	m_pChild = NULL;
	SetChild(pElement);
}

CXTPMarkupInlineUIContainer::~CXTPMarkupInlineUIContainer()
{
	MARKUP_RELEASE(m_pChild);
}

CXTPMarkupUIElement* CXTPMarkupInlineUIContainer::GetChild() const
{
	return m_pChild;
}

void CXTPMarkupInlineUIContainer::SetChild(CXTPMarkupUIElement* pChild)
{
	if (m_pChild)
	{
		m_pChild->SetLogicalParent(NULL);
		MARKUP_RELEASE(m_pChild);
	}

	m_pChild = pChild;

	if (m_pChild)
	{
		m_pChild->SetLogicalParent(this);
	}
}


void CXTPMarkupInlineUIContainer::SetContentObject(CXTPMarkupBuilder* pBuilder, CXTPMarkupObject* pContent)
{
	if (!pContent->IsKindOf(MARKUP_TYPE(CXTPMarkupUIElement)))
	{
		pBuilder->ThrowBuilderException(CXTPMarkupBuilder::FormatString(_T("'%ls' object cannot be added to '%ls'. Object cannot be converted to type 'CXTPMarkupUIElement'"),
			(LPCTSTR)pContent->GetType()->m_lpszClassName, (LPCTSTR)GetType()->m_lpszClassName));
	}

	SetChild((CXTPMarkupUIElement*)pContent);
}

BOOL CXTPMarkupInlineUIContainer::HasContentObject() const
{
	return m_pChild != NULL;
}

POSITION CXTPMarkupInlineUIContainer::GetContentStartPosition() const
{
	return m_pChild ? MARKUP_POSITION_START : MARKUP_POSITION_EOF;
};

void CXTPMarkupInlineUIContainer::GetContentNextPosition(POSITION& pos) const
{
	pos = (pos == MARKUP_POSITION_START ? MARKUP_POSITION_END : MARKUP_POSITION_EOF);
}

BOOL CXTPMarkupInlineUIContainer::IsWordBreakPosition(POSITION pos) const
{
	return pos == MARKUP_POSITION_START || pos == MARKUP_POSITION_END;
}

CSize CXTPMarkupInlineUIContainer::Measure(CXTPMarkupDrawingContext* pDC, POSITION posStart, POSITION /*posEnd*/)
{
	if (!m_pChild || posStart != MARKUP_POSITION_START)
		return CSize(0, 0);

	m_pChild->Measure(pDC, CSize(32000, 32000));

	return m_pChild->GetDesiredSize();
}

void CXTPMarkupInlineUIContainer::Arrange(CRect rcFinalRect, POSITION posStart, POSITION /*posEnd*/)
{
	if (!m_pChild || posStart != MARKUP_POSITION_START)
		return;

	m_pChild->Arrange(rcFinalRect);
}

void CXTPMarkupInlineUIContainer::Render(CXTPMarkupDrawingContext* pDC, CRect /*rc*/, POSITION posStart, POSITION /*posEnd*/)
{
	if (!m_pChild  || posStart != MARKUP_POSITION_START)
		return;

	m_pChild->Render(pDC);
}

CXTPMarkupInputElement* CXTPMarkupInlineUIContainer::InputHitTest(CPoint point) const
{
	CXTPMarkupInputElement* pObject = m_pChild ? m_pChild->InputHitTest(point) : (CXTPMarkupInputElement*)this;

	if (pObject)
		return pObject;

	return (CXTPMarkupInputElement*)this;
}

