// Indexes.cpp : implementation file
//

#include "stdafx.h"
#include "NewProject01View.h"
#include "ZoomInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZoomInfo

//IMPLEMENT_DYNCREATE(CZoomInfo, CCmdTarget)

CZoomInfo::CZoomInfo(CSize size, CRect rc, bool bRightRect)
{
	m_szImageSize = size;
	m_rcZoomBoxRect = rc;
	m_nZoomX = 1;
	m_ptCP = CPoint( (int)(m_szImageSize.cx*0.5), (int)(m_szImageSize.cy*0.5));
	m_nMaxZoomFactor = 2048;
	m_bRightRect = bRightRect;

	ZoomOut(CPoint(0, 0));
}

CZoomInfo::~CZoomInfo()
{
}

/*
BEGIN_MESSAGE_MAP(CZoomInfo, CCmdTarget)
	//{{AFX_MSG_MAP(CZoomInfo)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
/////////////////////////////////////////////////////////////////////////////
// CZoomInfo message handlers

void CZoomInfo::SetZoomX(int num)
{
	m_nZoomX = num;

	m_nWingX = m_szImageSize.cx/(2*m_nZoomX)-1;
	m_nWingY = m_szImageSize.cy/(2*m_nZoomX)-1;
    m_nDeltX = m_nWingX*2+1;
	m_nDeltY = m_nWingY*2+1;
	if( m_bRightRect ){
		m_nWingY = m_nWingX;
		m_nDeltY = m_nDeltX;
		//m_fScaleY = m_fScaleX;
	}
    m_fScaleX = (float)m_nDeltX/(m_rcZoomBoxRect.Width()+1);
	m_fScaleY = (float)m_nDeltY/(m_rcZoomBoxRect.Height()+1);

	
}

void CZoomInfo::SetCenterPoint(CPoint p)
{
/*	int wingx = m_szImageSize.cx/(2*m_nZoomX)-1;
	int wingy = m_szImageSize.cy/(2*m_nZoomX)-1;
	int deltx = wingx*2+1;
	int delty = wingy*2+1;

	if( m_bRightRect ){
		m_nWingY = m_nWingX;
		m_nDeltY = m_nDeltX;
		m_fScaleY = m_fScaleX;
	}
*/	
	if( p.x-m_nWingX < 0 ) 					p.x = m_nWingX;
	if( p.y-m_nWingY < 0 ) 					p.y = m_nWingY;
	if( p.x+m_nWingX > m_szImageSize.cx-1 )	p.x = m_szImageSize.cx-1-m_nWingX;
	if( p.y+m_nWingY > m_szImageSize.cy-1 )	p.y = m_szImageSize.cy-1-m_nWingY;

	m_ptCP = p;
}

CPoint CZoomInfo::GetCenterPoint()
{
	return m_ptCP;
}

int CZoomInfo::GetZoomX()
{
	return m_nZoomX;
}

int CZoomInfo::IncreaseZoomX()
{
	if( m_nZoomX < m_nMaxZoomFactor )	m_nZoomX *= 2;

	m_nWingX = m_szImageSize.cx/(2*m_nZoomX)-1;
	m_nWingY = m_szImageSize.cy/(2*m_nZoomX)-1;
    m_nDeltX = m_nWingX*2+1;
	m_nDeltY = m_nWingY*2+1;
	if( m_bRightRect ){
		m_nWingY = m_nWingX;
		m_nDeltY = m_nDeltX;
		//m_fScaleY = m_fScaleX;
	}
    m_fScaleX = (float)m_nDeltX/(m_rcZoomBoxRect.Width()+1);
	m_fScaleY = (float)m_nDeltY/(m_rcZoomBoxRect.Height()+1);

	

	return m_nZoomX;
}

int CZoomInfo::DecreaseZoomX()
{
	if( m_nZoomX > 1 )	m_nZoomX /= 2;

	m_nWingX = m_szImageSize.cx/(2*m_nZoomX)-1;
	m_nWingY = m_szImageSize.cy/(2*m_nZoomX)-1;
    m_nDeltX = m_nWingX*2+1;
	m_nDeltY = m_nWingY*2+1;
	if( m_bRightRect ){
		m_nWingY = m_nWingX;
		m_nDeltY = m_nDeltX;
		//m_fScaleY = m_fScaleX;
	}
    m_fScaleX = (float)m_nDeltX/(m_rcZoomBoxRect.Width()+1);
	m_fScaleY = (float)m_nDeltY/(m_rcZoomBoxRect.Height()+1);

	

	return m_nZoomX;
}

CZoomInfo::CZoomInfo()
{

}

CRect CZoomInfo::GetSourceRect()
{
/*	int wingx = m_szImageSize.cx/(2*m_nZoomX) -1;
	int wingy = m_szImageSize.cy/(2*m_nZoomX) -1;
	int deltx = 2*wingx+1;
	int delty = 2*wingy+1;
	CRect ret;

	if( m_bRightRect ){
		wingy = wingx;
		delty = deltx;
	}
*/
	CRect ret;
		
	ret = CRect(m_ptCP.x-m_nWingX, m_ptCP.y-m_nWingY, m_nDeltX, m_nDeltY);

	return ret;
}

CPoint CZoomInfo::PToL(CPoint p)
{/*
	int wingx = m_szImageSize.cx/(2*m_nZoomX)-1;
	int wingy = m_szImageSize.cy/(2*m_nZoomX)-1;
	int deltx = wingx*2+1;
	int delty = wingy*2+1;
	float scalex = (float)deltx/m_rcZoomBoxRect.Width();
	float scaley = (float)delty/m_rcZoomBoxRect.Height();	
	CPoint ret;

	if( m_bRightRect ){
		wingy = wingx;
		delty = deltx;
		scaley = scalex;
	}*/	
	
/*	if( p.x-m_nWingX < 0 ) 					p.x = m_nWingX;
	if( p.y-m_nWingY < 0 ) 					p.y = m_nWingY;
	if( p.x+m_nWingX > m_szImageSize.cx-1 )	p.x = m_szImageSize.cx-1-m_nWingX;
	if( p.y+m_nWingY > m_szImageSize.cy-1 )	p.y = m_szImageSize.cy-1-m_nWingY;
*/
	CPoint ret;

	ret.x = (int)((m_ptCP.x-m_nWingX)+p.x*m_fScaleX);
	ret.y = (int)((m_ptCP.y-m_nWingY)+p.y*m_fScaleY);

	return ret;
}

int CZoomInfo::GetZoomBoxWidth()
{
	return m_rcZoomBoxRect.Width()+1;
}

int CZoomInfo::GetZoomBoxHeight()
{
	return m_rcZoomBoxRect.Height()+1;
}

bool CZoomInfo::IsInZoomBox(CPoint p)
{
	if( m_rcZoomBoxRect.left > p.x )		return false;
	if( m_rcZoomBoxRect.top > p.y )		return false;
	if( m_rcZoomBoxRect.right < p.x )		return false;
	if( m_rcZoomBoxRect.bottom < p.y )	return false;
	return true;
}

void CZoomInfo::ZoomIn(CPoint p)
{
	IncreaseZoomX();
	SetCenterPoint(p);
}

CRect CZoomInfo::GetZoomBoxRect()
{
	return m_rcZoomBoxRect;
}

void CZoomInfo::ZoomOut(CPoint p)
{
	DecreaseZoomX();
	SetCenterPoint(p);
}

CPoint CZoomInfo::LToP(CPoint p)
{
/*    int wingx = m_szImageSize.cx/(2*m_nZoomX)-1;
	int wingy = m_szImageSize.cy/(2*m_nZoomX)-1;
    int deltx = wingx*2+1;
	int delty = wingy*2+1;
    float scalex = (float)deltx/m_rcZoomBoxRect.Width();
	float scaley = (float)delty/m_rcZoomBoxRect.Height();
	CPoint ret;

	if( m_bRightRect ){
		wingy = wingx;
		delty = deltx;
		scaley = scalex;
	}
*/
	CPoint ret;

	ret.x = (int)(( p.x-(m_ptCP.x-m_nWingX) +0.5 )/m_fScaleX+0.5);
	ret.y = (int)(( p.y-(m_ptCP.y-m_nWingY) +0.5 )/m_fScaleY+0.5);

	return ret;
}

CPointFloat CZoomInfo::LToP(CPointFloat p)
{/*
	int wingx = m_szImageSize.cx/(2*m_nZoomX)-1;
	int wingy = m_szImageSize.cy/(2*m_nZoomX)-1;
    int deltx = wingx*2+1;
	int delty = wingy*2+1;
    float scalex = (float)deltx/m_rcZoomBoxRect.Width();
	float scaley = (float)delty/m_rcZoomBoxRect.Height();
	CPointFloat ret;

	if( m_bRightRect ){
		wingy = wingx;
		delty = deltx;
		scaley = scalex;
	}
	*/

	CPointFloat ret;

	ret.x = (float)(( p.x-(m_ptCP.x-m_nWingX)+0.5)/m_fScaleX);
	ret.y = (float)(( p.y-(m_ptCP.y-m_nWingY)+0.5)/m_fScaleY);

	return ret;
}

void CZoomInfo::SetZoomBoxRect(CRect rect)
{
	m_rcZoomBoxRect = rect;

	m_nWingX = m_szImageSize.cx/(2*m_nZoomX)-1;
	m_nWingY = m_szImageSize.cy/(2*m_nZoomX)-1;
    m_nDeltX = m_nWingX*2+1;
	m_nDeltY = m_nWingY*2+1;
	if( m_bRightRect ){
		m_nWingY = m_nWingX;
		m_nDeltY = m_nDeltX;
	}
    m_fScaleX = (float)m_nDeltX/(m_rcZoomBoxRect.Width()+1);
	m_fScaleY = (float)m_nDeltY/(m_rcZoomBoxRect.Height()+1);

	
//	m_fScaleY = m_fScaleX;
}

CRect CZoomInfo::GetImageRect()
{
	return CRect(0, 0, m_szImageSize.cx, m_szImageSize.cy);
}

CRect CZoomInfo::GetBound(CRect rect)
{
	//	returns physical bound of pixels defined by rect
	/*
    int wingx = m_szImageSize.cx/(2*m_nZoomX)-1;
	int wingy = m_szImageSize.cy/(2*m_nZoomX)-1;
    int deltx = wingx*2+1;
	int delty = wingy*2+1;
    float scalex = (float)deltx/m_rcZoomBoxRect.Width();
	float scaley = (float)delty/m_rcZoomBoxRect.Height();
	CPoint ret;

	if( m_bRightRect ){
		wingy = wingx;
		delty = deltx;
		scaley = scalex;
	}
*/
	rect.left = (int)(( rect.left-(m_ptCP.x-m_nWingX) )/m_fScaleX);
	rect.top = (int)(( rect.top-(m_ptCP.y-m_nWingY) )/m_fScaleY);
	rect.right = (int)(( rect.right-(m_ptCP.x-m_nWingX)+1 )/m_fScaleX)-1;
	rect.bottom = (int)(( rect.bottom-(m_ptCP.y-m_nWingY)+1 )/m_fScaleY)-1;

//	rect.top *= ((float)m_rcZoomBoxRect.Height()/m_rcZoomBoxRect.Width());
//	rect.bottom *= ((float)m_rcZoomBoxRect.Height()/m_rcZoomBoxRect.Width());

	return rect;
}


CPointFloat CZoomInfo::PToL_Float(CPoint p)
{/*
	int wingx = m_szImageSize.cx/(2*m_nZoomX)-1;
	int wingy = m_szImageSize.cy/(2*m_nZoomX)-1;
	int deltx = wingx*2+1;
	int delty = wingy*2+1;
	float scalex = (float)deltx/m_rcZoomBoxRect.Width();
	float scaley = (float)delty/m_rcZoomBoxRect.Height();	
	CPointFloat ret;

	if( m_bRightRect ){
		wingy = wingx;
		delty = deltx;
		scaley = scalex;
	}
*/
	CPointFloat ret;

	ret.x = (float)(((m_ptCP.x-m_nWingX)+p.x*m_fScaleX)-0.5);
	ret.y = (float)(((m_ptCP.y-m_nWingY)+p.y*m_fScaleY)-0.5);

	return ret;
}

int CZoomInfo::GetImageWidth()
{
	return m_szImageSize.cx;
}

int CZoomInfo::GetImageHeight()
{
	return m_szImageSize.cy;
}

void CZoomInfo::SetMaxZoomFactor(int nFactor)
{
	m_nMaxZoomFactor = nFactor;
}

CPoint CZoomInfo::GetWing()
{
	return CPoint(m_nWingX, m_nWingY);
}
