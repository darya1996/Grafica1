
// Graphic1View.cpp : implementation of the CGraphic1View class
//

#include "stdafx.h"
#include "math.h"
#include "stdio.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Graphic1.h"
#endif

#include "Graphic1Doc.h"
#include "Graphic1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;
// CGraphic1View

IMPLEMENT_DYNCREATE(CGraphic1View, CView)

BEGIN_MESSAGE_MAP(CGraphic1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGraphic1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CGraphic1View construction/destruction

CGraphic1View::CGraphic1View()
{
	// TODO: add construction code here

}

CGraphic1View::~CGraphic1View()
{
}

BOOL CGraphic1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGraphic1View drawing
// Создаем собственную функцию

double my_function(double x, double e)
{
	double sum = 1.0;
	double x2 = x * x;
	double previous = 1.0;
	for (int k = 2; previous > e; k++)
	{
		previous *= x2 / ((2 * k - 1) * (2 * k - 2));
		if (k % 2 == 0)
			sum -= previous;
		else
			sum += previous;
	}
	return sum;
}


void CGraphic1View::OnDraw(CDC* pDC)
{
	CGraphic1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	FILE *file1;
	FILE *file2;
	
	file1=fopen("file1","w+");
	file2=fopen("file2", "w+");
	double a = -30, b = 30;
	double eps = 0.001; //эпсилон
	int nsegm = 300; //сегмент для шага
	double scalex = 160.0, scaley = 20.0;
	double x, y, z;
	double step; //шаг

	step = (b - a) / nsegm;
	// создаем перо для координатных осей
	CPen penAxe(PS_SOLID, 3, RGB(0, 0, 255));
	// создаем перо для рисования графика
	CPen penSin(PS_SOLID, 2, RGB(255, 0, 0));
	// сохраняем адрес старого пера (стандартного для windows)
	CPen *pOldPen = NULL;
	// создаем пустой прямоугольник (область рисования)
	CRect rcClient;
	// подключаемся ОС windows записывая параметры рабочей зоны в объект
	GetClientRect(&rcClient);
	// рисуем оси
	pOldPen = pDC->SelectObject(&penAxe);
	pDC->MoveTo(0, rcClient.CenterPoint().y);
	pDC->LineTo(rcClient.Width(), rcClient.CenterPoint().y);
	pDC->LineTo(rcClient.Width() - 8, rcClient.CenterPoint().y - 8);
	pDC->MoveTo(rcClient.Width(), rcClient.CenterPoint().y);
	pDC->LineTo(rcClient.Width() - 8, rcClient.CenterPoint().y + 8);
	pDC->MoveTo(rcClient.CenterPoint().x, 0);
	pDC->LineTo(rcClient.CenterPoint().x - 8, 8);
	pDC->MoveTo(rcClient.CenterPoint().x, 0);
	pDC->LineTo(rcClient.CenterPoint().x + 8, 8);
	pDC->MoveTo(rcClient.CenterPoint().x, 0);
	pDC->LineTo(rcClient.CenterPoint().x, rcClient.Height());
	pDC->SelectObject(&penSin);

	// рисуем график собственной функции
	x = a;
	y = my_function(x, eps);
	fprintf(file1, "%10.3f %10.3f %10.3f", x, y, z);
	fprintf(file2, "%10.3f %10.3f", x, y);
	pDC->MoveTo(rcClient.CenterPoint().x + (int)(x * scalex), rcClient.CenterPoint().y - 
		(int)(y * scaley));
	for (int i = 1; i <= nsegm; i++)
	{
		//z = my_function(x, eps);
		x += step;
		y = my_function(x, eps);
		z = sin(x) / x;
		double ab = abs(z - y);
		fprintf(file1,"%10.3f %10.3f %10.3f %10.3f",x,y,z,ab);
		fprintf(file2,"%10.3f %10.3f", x, y);
		pDC->LineTo(rcClient.CenterPoint().x + (int)(x*scalex), rcClient.CenterPoint().y -
			(int)(y*scaley));
	}
	// рисуем стандартную функцию sin(x)/x
	step = 0.025;
	for (x = a; x <= b; x += step)
	{
		y = sin(x) / x;
		pDC->SetPixel(rcClient.CenterPoint().x + (int)(x*scalex) + 1, rcClient.CenterPoint().y -
			(int)(y*scaley) + 1, RGB(0, 255, 0));
	}

	fclose(file1);
	fclose(file2);
	// TODO: add draw code for native data here
}


// CGraphic1View printing


void CGraphic1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGraphic1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGraphic1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGraphic1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CGraphic1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGraphic1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGraphic1View diagnostics

#ifdef _DEBUG
void CGraphic1View::AssertValid() const
{
	CView::AssertValid();
}

void CGraphic1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphic1Doc* CGraphic1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphic1Doc)));
	return (CGraphic1Doc*)m_pDocument;
}
#endif //_DEBUG


// CGraphic1View message handlers
