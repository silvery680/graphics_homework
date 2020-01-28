
// G_Text3View.cpp: CGText3View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "G_Text3.h"
#endif

#include "G_Text3Doc.h"
#include "G_Text3View.h"
#include "Transformation_2D.h"
#include "Transformation_3D.h"
#include "B3Curves.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGText3View

IMPLEMENT_DYNCREATE(CGText3View, CView)

BEGIN_MESSAGE_MAP(CGText3View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_Drawpic, &CGText3View::OnDrawpic)
	ON_COMMAND(ID_Tran_2d, &CGText3View::OnTran2d)
	ON_UPDATE_COMMAND_UI(ID_Tran_2d, &CGText3View::OnUpdateTran2d)
	ON_UPDATE_COMMAND_UI(ID_Drawpic, &CGText3View::OnUpdateDrawpic)
	ON_COMMAND(ID_TranUp, &CGText3View::OnTranup)
	ON_COMMAND(ID_TranRight, &CGText3View::OnTranright)
	ON_COMMAND(ID_TranLeft, &CGText3View::OnTranleft)
	ON_COMMAND(ID_TranDown, &CGText3View::OnTrandown)
	ON_COMMAND(ID_Rotation_1, &CGText3View::OnRotation1)
	ON_COMMAND(ID_Rotation_2, &CGText3View::OnRotation2)
	ON_COMMAND(ID_reflect_x, &CGText3View::OnReflectX)
	ON_COMMAND(ID_reflect_y, &CGText3View::OnReflectY)
	ON_COMMAND(ID_X_Shear_L, &CGText3View::OnXShearL)
	ON_COMMAND(ID_X_Shear_R, &CGText3View::OnXShearR)
	ON_COMMAND(ID_Y_Shear_D, &CGText3View::OnYShearD)
	ON_COMMAND(ID_Y_Shear_U, &CGText3View::OnYShearU)
	ON_COMMAND(ID_Tran_3d, &CGText3View::OnTran3d)
	ON_UPDATE_COMMAND_UI(ID_Tran_3d, &CGText3View::OnUpdateTran3d)
	ON_COMMAND(ID_Z_Shear_B, &CGText3View::OnZShearB)
	ON_COMMAND(ID_Z_Shear_F, &CGText3View::OnZShearF)
	ON_COMMAND(ID_reflect_z, &CGText3View::OnReflectZ)
	ON_COMMAND(ID_Rotation_3, &CGText3View::OnRotation3)
	ON_COMMAND(ID_Scale_Plus, &CGText3View::OnScalePlus)
	ON_COMMAND(ID_Scale_Min, &CGText3View::OnScaleMin)
	ON_UPDATE_COMMAND_UI(ID_reflect_z, &CGText3View::OnUpdateReflectZ)
	ON_UPDATE_COMMAND_UI(ID_Z_Shear_B, &CGText3View::OnUpdateZShearB)
	ON_UPDATE_COMMAND_UI(ID_Z_Shear_F, &CGText3View::OnUpdateZShearF)
	ON_UPDATE_COMMAND_UI(ID_Rotation_3, &CGText3View::OnUpdateRotation3)
	ON_UPDATE_COMMAND_UI(ID_reflect_x, &CGText3View::OnUpdateReflectX)
	ON_UPDATE_COMMAND_UI(ID_reflect_y, &CGText3View::OnUpdateReflectY)
	ON_UPDATE_COMMAND_UI(ID_Rotation_1, &CGText3View::OnUpdateRotation1)
	ON_UPDATE_COMMAND_UI(ID_Rotation_2, &CGText3View::OnUpdateRotation2)
	ON_UPDATE_COMMAND_UI(ID_TranDown, &CGText3View::OnUpdateTrandown)
	ON_UPDATE_COMMAND_UI(ID_TranLeft, &CGText3View::OnUpdateTranleft)
	ON_UPDATE_COMMAND_UI(ID_TranRight, &CGText3View::OnUpdateTranright)
	ON_UPDATE_COMMAND_UI(ID_TranUp, &CGText3View::OnUpdateTranup)
	ON_UPDATE_COMMAND_UI(ID_X_Shear_L, &CGText3View::OnUpdateXShearL)
	ON_UPDATE_COMMAND_UI(ID_X_Shear_R, &CGText3View::OnUpdateXShearR)
	ON_UPDATE_COMMAND_UI(ID_Y_Shear_D, &CGText3View::OnUpdateYShearD)
	ON_UPDATE_COMMAND_UI(ID_Y_Shear_U, &CGText3View::OnUpdateYShearU)
	ON_UPDATE_COMMAND_UI(ID_Scale_Min, &CGText3View::OnUpdateScaleMin)
	ON_UPDATE_COMMAND_UI(ID_Scale_Plus, &CGText3View::OnUpdateScalePlus)
	ON_COMMAND(ID_Set_Bezier, &CGText3View::OnSetBezier)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_Set_B3Curves, &CGText3View::OnSetB3curves)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CGText3View 构造/析构

CGText3View::CGText3View() noexcept
{
	// TODO: 在此处添加构造代码
	Model_2D = FALSE;
	Model_3D = FALSE;
	Model_Bezier = FALSE;
	Model_B3Curves = FALSE;
}

CGText3View::~CGText3View()
{
}

BOOL CGText3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CGText3View 绘图

void CGText3View::OnDraw(CDC* /*pDC*/)
{
	CGText3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (Model_2D || Model_3D || Model_Bezier || Model_B3Curves) DoubleBuffer();
	// TODO: 在此处为本机数据添加绘制代码
}


// CGText3View 打印

BOOL CGText3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CGText3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CGText3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CGText3View 诊断

#ifdef _DEBUG
void CGText3View::AssertValid() const
{
	CView::AssertValid();
}

void CGText3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGText3Doc* CGText3View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGText3Doc)));
	return (CGText3Doc*)m_pDocument;
}
#endif //_DEBUG


// CGText3View 消息处理程序


void CGText3View::DoubleBuffer()
{
	// TODO: 在此处添加实现代码.
	CDC* pDC = GetDC();
	GetClientRect(&rect);//获得客户区的大小
	pDC->SetMapMode(MM_ANISOTROPIC);//pDC自定义坐标系
	pDC->SetWindowExt(rect.Width(), rect.Height());//设置窗口范围
	pDC->SetViewportExt(rect.Width(), -rect.Height());//x轴水平向右，y轴垂直向上
	pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);//屏幕中心为原点
	CDC MemDC;//内存DC
	CBitmap NewBitmap, *pOldBitmap;//内存中承载图像的临时位图
	MemDC.CreateCompatibleDC(pDC);//建立与屏幕pDC兼容的MemDC 
	NewBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());//创建兼容位图 
	pOldBitmap = MemDC.SelectObject(&NewBitmap); //将兼容位图选入MemDC 
	MemDC.FillSolidRect(&rect, pDC->GetBkColor());//按原来背景填充客户区，否则是黑色
	MemDC.SetMapMode(MM_ANISOTROPIC);//MemDC自定义坐标系
	MemDC.SetWindowExt(rect.Width(), rect.Height());
	MemDC.SetViewportExt(rect.Width(), -rect.Height());
	MemDC.SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
	if (Model_2D)DrawObject(&MemDC);
	if (Model_3D)DrawObject_3D(&MemDC);
	if (Model_Bezier)Draw_Bezier(&MemDC);
	if (Model_B3Curves)Draw_B3Curves(&MemDC);
	pDC->BitBlt(-rect.Width() / 2, -rect.Height() / 2, rect.Width(), rect.Height(), &MemDC, -rect.Width() / 2, -rect.Height() / 2, SRCCOPY);//将内存位图拷贝到屏幕
	MemDC.SelectObject(pOldBitmap);//恢复位图
	NewBitmap.DeleteObject();//删除位图
	ReleaseDC(pDC);//释放DC	
}



void CGText3View::DrawObject(CDC *pDC)
{
	// TODO: 在此处添加实现代码.
	pDC->MoveTo(-rect.Width() / 2, 0);
	pDC->LineTo(rect.Width() / 2, 0);
	pDC->MoveTo(0, rect.Height() / 2);
	pDC->LineTo(0, -rect.Height() / 2);

	if (Trans_2d.PtCount >= 1)
	{
		CPen NewPen3, *pOldPen3;//定义3个像素宽度的画笔
		NewPen3.CreatePen(PS_SOLID, 3, RGB(87, 250, 255));
		pOldPen3 = pDC->SelectObject(&NewPen3);
		DrawPolygon(pDC);
		pDC->SelectObject(pOldPen3);
		NewPen3.DeleteObject();
	}
}

void CGText3View::DrawObject_3D(CDC *pDC)
{
	// TODO: 在此处添加实现代码.
	pDC->MoveTo(0, 0);//绘制x轴
	pDC->LineTo(rect.Width() / 2, 0);
	pDC->TextOut(rect.Width() / 2 - 20, -20, _T("x"));
	pDC->MoveTo(0, 0);//绘制y轴
	pDC->LineTo(0, rect.Height() / 2);
	pDC->TextOut(-20, rect.Height() / 2 - 20, _T("y"));
	pDC->MoveTo(0, 0);//绘制z轴
	pDC->LineTo(-rect.Width() / 2, -rect.Width() / 2);
	pDC->TextOut(-rect.Height() / 2 - 20, -rect.Height() / 2 + 20, _T("z"));
	pDC->TextOut(10, -10, _T("0"));
	
	CPen NewPen3, *pOldPen3;//定义3个像素宽度的画笔
	NewPen3.CreatePen(PS_SOLID, 3, RGB(87, 250, 255));
	pOldPen3 = pDC->SelectObject(&NewPen3);
	if(Trans_3d.PtCount >= 2)
	{
		DrawPolygon_3D(pDC);
	}
	if (Trans_3d.PtCount == 1)
	{
		CP2 t;
		for (int i = 0; i < 4; i++)//绘制多边形
		{
			if (i == 0)
			{
				pDC->MoveTo(Trans_3d.p[i].x, Trans_3d.p[i].y);
				t = Trans_3d.p[i];
			}
			else
			{
				pDC->LineTo(Trans_3d.p[i].x, Trans_3d.p[i].y);
			}
		}
		pDC->LineTo(t.x, t.y);//闭合多边形
	}
	if (Trans_3d.PtCount <= 1 && Trans_3d.bDrawLine) 
	{
		RECT tmp_rect;
		GetWindowRect(&tmp_rect);
		tmp_rect.bottom = (tmp_rect.bottom + tmp_rect.top)   / 2;
		tmp_rect.left   = (tmp_rect.left   + tmp_rect.right) / 2;
		ClipCursor(&tmp_rect);
	}

	pDC->SelectObject(pOldPen3);
	NewPen3.DeleteObject();
}

void CGText3View::Draw_B3Curves(CDC *pDC)
{
	// TODO: 在此处添加实现代码.
	CPen NewPen, *pOldPen;
	NewPen.CreatePen(PS_SOLID, 3, RGB(87, 250, 255));
	pOldPen = pDC->SelectObject(&NewPen);
	pDC->MoveTo(b3Curves.P[0]);
	pDC->Ellipse(b3Curves.P[0].x - 2, b3Curves.P[0].y - 2, b3Curves.P[0].x + 2, b3Curves.P[0].y + 2);//绘制控制多边形顶点
	for (int i = 1; i < 9; i++)
	{
		pDC->LineTo(b3Curves.P[i]);
		pDC->Ellipse(b3Curves.P[i].x - 2, b3Curves.P[i].y - 2, b3Curves.P[i].x + 2, b3Curves.P[i].y + 2);
	}
	if (b3Curves.m_i != -1)
	{
		CString	str;
		str.Format(_T("x=%d,y=%d"), b3Curves.P[b3Curves.m_i].x, b3Curves.P[b3Curves.m_i].y);
		pDC->TextOut(b3Curves.P[b3Curves.m_i].x + 5, b3Curves.P[b3Curves.m_i].y + 5, str);
	}
	b3Curves.B3Curves_Print(b3Curves.P, pDC);
}

void CGText3View::Draw_Bezier(CDC *pDC)
{
	// TODO: 在此处添加实现代码.
	pDC->MoveTo(-rect.Width() / 2, 0);
	pDC->LineTo(rect.Width() / 2, 0);
	pDC->MoveTo(0, rect.Height() / 2);
	pDC->LineTo(0, -rect.Height() / 2);

	DrawCtrlPolygon(pDC);

	if(bezier.RightCheck) 
	{
		if (0 != bezier.CtrlPointNum)
			bezier.DrawBezier(pDC);
	}
}

void CGText3View::DrawPolygon(CDC *pDC)
{
	// TODO: 在此处添加实现代码.
	CP2 t;
	for (int i = 0; i < 4; i++)//绘制多边形
	{
		if (i == 0)
		{
			pDC->MoveTo(Trans_2d.p[i].x, Trans_2d.p[i].y);
			t = Trans_2d.p[i];
		}
		else
		{
			pDC->LineTo(Trans_2d.p[i].x, Trans_2d.p[i].y);
		}
	}
	pDC->LineTo(t.x, t.y);//闭合多边形
}

void CGText3View::DrawPolygon_3D(CDC *pDC)
{
	// TODO: 在此处添加实现代码.
	for (int nFace = 0; nFace < 6; nFace++)
	{
		CP2 t;
		for (int nVertex = 0; nVertex < Trans_3d.F[nFace].vN; nVertex++)//顶点循环
		{
			ObliqueProject(Trans_3d.P[Trans_3d.F[nFace].vI[nVertex]]);//斜等测投影
			if (0 == nVertex)
			{
				pDC->MoveTo(Trans_3d.ScreenP.x, Trans_3d.ScreenP.y);
				t = Trans_3d.ScreenP;
			}
			else
				pDC->LineTo(Trans_3d.ScreenP.x, Trans_3d.ScreenP.y);
		}
		pDC->LineTo(t.x, t.y);//闭合多边形
	}
}



void CGText3View::DrawCtrlPolygon(CDC *pDC)
{
	// TODO: 在此处添加实现代码.
	CPen NewPen3, *pOldPen3;//定义3个像素宽度的画笔
	NewPen3.CreatePen(PS_SOLID, 3, RGB(87, 250, 255));
	pOldPen3 = pDC->SelectObject(&NewPen3);
	int temp = bezier.n;
	if (bezier.bFlag) temp++;
	for (int i = 0; i <= temp; i++)
	{
		if (0 == i)
		{
			pDC->MoveTo(bezier.P[i]);
		}
		else
		{
			pDC->LineTo(bezier.P[i]);
		}
	}
	pDC->SelectObject(pOldPen3);
	NewPen3.DeleteObject();
}

void CGText3View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (Model_2D)
	{
		if (Trans_2d.bDrawLine)
		{
			if (Trans_2d.PtCount == 1)
			{
				Trans_2d.p[2] = Convert(point);

				Trans_2d.p[1].w = 1.0;
				Trans_2d.p[1].x = Trans_2d.p[2].x;
				Trans_2d.p[1].y = Trans_2d.p[0].y;

				Trans_2d.p[3].w = 1.0;
				Trans_2d.p[3].x = Trans_2d.p[0].x;
				Trans_2d.p[3].y = Trans_2d.p[2].y;
				Trans_2d.PtCount++;
			}
			if (Trans_2d.PtCount < 1)
			{
				Trans_2d.p[0] = Convert(point);
				Trans_2d.PtCount++;
			}
		}
	}
	if (Model_3D) 
	{
		if (Trans_3d.bDrawLine)
		{
			if (Trans_3d.PtCount == 2)
			{
				CP2 tmp = Convert(point);
				Trans_3d.SetPoint((Trans_3d.p[0].x + Trans_3d.p[2].x) / 2.0,
					-tmp.y,
					(Trans_3d.p[0].y + Trans_3d.p[2].y) / 2.0);
				Trans_3d.bDrawLine = FALSE;
				Trans_3d.PtCount++;
			}
			if (Trans_3d.PtCount == 1)
			{
				Trans_3d.p[2] = Convert(point);

				Trans_3d.p[1].w = 1.0;
				Trans_3d.p[1].x = Trans_3d.p[2].x;
				Trans_3d.p[1].y = Trans_3d.p[0].y;

				Trans_3d.p[3].w = 1.0;
				Trans_3d.p[3].x = Trans_3d.p[0].x;
				Trans_3d.p[3].y = Trans_3d.p[2].y;
				ClipCursor(NULL);
				Trans_3d.PtCount++;
			}
		}
	}
	if (Model_Bezier) 
	{
		if (bezier.bFlag)
		{
			bezier.P[bezier.CtrlPointNum] = Convert_Point(point);
			if (bezier.CtrlPointNum < bezier.N_MAX_POINT - 1)//N_MAX_POINT为控制点个数的最大值
				bezier.CtrlPointNum++;
			else
				bezier.bFlag = FALSE;
				bezier.n = bezier.CtrlPointNum - 1;
		}
	}
	if (Model_B3Curves)
	{
		if (b3Curves.m_AbleToLeftBtn == TRUE)
			b3Curves.m_AbleToMove = TRUE;
	}
	CView::OnLButtonDown(nFlags, point);
}



CP2 CGText3View::Convert(CPoint point)
{
	// TODO: 在此处添加实现代码.
	GetClientRect(&rect);
	CP2 ptemp;
	ptemp.x = point.x - rect.Width() / 2;
	ptemp.y = rect.Height() / 2 - point.y;
	ptemp.w = 1.0;
	return ptemp;
}

CPoint CGText3View::Convert_Point(CPoint point)
{
	// TODO: 在此处添加实现代码.
	GetClientRect(&rect);
	POINT ptemp;
	ptemp.x = point.x - rect.Width() / 2;
	ptemp.y = rect.Height() / 2 - point.y;
	return ptemp;
}


void CGText3View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (Model_2D)
	{
		if (Trans_2d.bDrawLine)
		{
			if (Trans_2d.PtCount == 1)
			{
				Trans_2d.p[2] = Convert(point);

				Trans_2d.p[1].w = 1.0;
				Trans_2d.p[1].x = Trans_2d.p[2].x;
				Trans_2d.p[1].y = Trans_2d.p[0].y;

				Trans_2d.p[3].w = 1.0;
				Trans_2d.p[3].x = Trans_2d.p[0].x;
				Trans_2d.p[3].y = Trans_2d.p[2].y;
			}

			if (Trans_2d.PtCount < 1)
			{
				Trans_2d.p[0] = Convert(point);
			}

			Invalidate(FALSE);
		}
	}
	if (Model_3D)
	{
		if (Trans_3d.bDrawLine)
		{
			if (Trans_3d.PtCount == 1)
			{
				Trans_3d.p[0] = Convert(point);

				Trans_3d.p[1].w = 1.0;
				Trans_3d.p[1].x = Trans_3d.p[2].x;
				Trans_3d.p[1].y = Trans_3d.p[0].y;

				Trans_3d.p[3].w = 1.0;
				Trans_3d.p[3].x = Trans_3d.p[0].x;
				Trans_3d.p[3].y = Trans_3d.p[2].y;
			}
			if (Trans_3d.PtCount == 2)
			{
				CP2 tmp = Convert(point);
				Trans_3d.SetPoint((Trans_3d.p[0].x + Trans_3d.p[2].x) / 2.0,
					-tmp.y,
					(Trans_3d.p[0].y + Trans_3d.p[2].y) / 2.0);
			}
			if (Trans_3d.PtCount < 1)
			{
				Trans_3d.p[2].x = 0;
				Trans_3d.p[2].y = 0;

				RECT tmp_rect;
				GetWindowRect(&tmp_rect);
				tmp_rect.bottom = (tmp_rect.bottom + tmp_rect.top) / 2;
				tmp_rect.left = (tmp_rect.left + tmp_rect.right) / 2;
				SetCursorPos(tmp_rect.left, tmp_rect.bottom);
				Trans_3d.PtCount++;
			}
			Invalidate(FALSE);
		}
	}
	if (Model_Bezier)
	{
		if (bezier.bFlag != 0)
		{
			bezier.P[bezier.CtrlPointNum] = Convert_Point(point);
		}
		Invalidate(FALSE);
	}
	if (Model_B3Curves) 
	{
		CPoint temp = Convert_Point(point);
		if (TRUE == b3Curves.m_AbleToMove)
			b3Curves.P[b3Curves.m_i] = temp;
		b3Curves.m_i = -1;
		int i;
		for (i = 0; i < 9; i++)
		{
			if ((temp.x - b3Curves.P[i].x)*(temp.x - b3Curves.P[i].x) + (temp.y - b3Curves.P[i].y)*(temp.y - b3Curves.P[i].y) < 50)
			{
				b3Curves.m_i = i;
				b3Curves.m_AbleToLeftBtn = TRUE;
				SetCursor(LoadCursor(NULL, IDC_SIZEALL));//改变为十字箭头光标
				break;
			}
		}
		if (10 == i)
		{
			b3Curves.m_i = -1;
		}
		Invalidate(FALSE);
	}
	CView::OnMouseMove(nFlags, point);
}


void CGText3View::OnDrawpic()
{
	// TODO: 在此添加命令处理程序代码
	if (Model_2D) {
		Trans_2d.PtCount = 0;
		Trans_2d.bDrawLine = TRUE;
		MessageBox(_T("鼠标画矩形"), _T("跟你说一声"), MB_OKCANCEL);
	}
	if (Model_3D) {
		Trans_3d.PtCount = 0;
		Trans_3d.bDrawLine = TRUE;
		MessageBox(_T("想不画也得画"), _T("无语"), MB_OK);
	}
	if (Model_Bezier) {
		MessageBox(_T("左键绘制控制多边形，右键绘制曲线"), _T("提示"), MB_OK);
		bezier.bFlag = TRUE;
		bezier.RightCheck = FALSE;
		bezier.CtrlPointNum = 0;
		bezier.n = bezier.CtrlPointNum - 1;
	}
	
	Invalidate(FALSE);
}


void CGText3View::OnTran2d()
{
	// TODO: 在此添加命令处理程序代码
	if (Model_2D == TRUE) {
		Model_2D = FALSE;
		WindowClear();
	}
	else
	{
		Model_3D = FALSE;
		Model_Bezier = FALSE;
		Model_2D = TRUE;
		DoubleBuffer();
	}
}


void CGText3View::OnUpdateTran2d(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck((Model_2D) ? TRUE : FALSE);
}

void CGText3View::OnTran3d()
{
	// TODO: 在此添加命令处理程序代码
	if (Model_3D == TRUE) {
		Model_3D = FALSE;
		WindowClear();
	}
	else
	{
		Model_Bezier = FALSE;
		Model_2D = FALSE;
		Model_B3Curves = FALSE;
		Model_3D = TRUE;
		DoubleBuffer();
	}
}


void CGText3View::OnSetBezier()
{
	// TODO: 在此添加命令处理程序代码
	if (Model_Bezier == TRUE) {
		Model_Bezier = FALSE;
		WindowClear();
	}
	else
	{
		Model_Bezier = TRUE;
		Model_B3Curves = FALSE;
		Model_3D = FALSE;
		Model_2D = FALSE;
		DoubleBuffer();
	}
}

void CGText3View::OnSetB3curves()
{
	// TODO: 在此添加命令处理程序代码
	if (Model_B3Curves == TRUE) {
		Model_B3Curves = FALSE;
		WindowClear();
	}
	else
	{
		Model_B3Curves = TRUE;
		Model_Bezier = FALSE;
		Model_3D = FALSE;
		Model_2D = FALSE;
		DoubleBuffer();
	}
}

void CGText3View::OnUpdateTran3d(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck((Model_3D) ? TRUE : FALSE);
}

void CGText3View::OnUpdateDrawpic(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable((Model_2D || Model_3D || Model_Bezier) ? TRUE : FALSE);
}


void CGText3View::WindowClear()
{
	// TODO: 在此处添加实现代码.
	CDC *pDC = GetDC();
	RECT rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect, RGB(255, 255, 255));
}

void CGText3View::OnTranup()
{
	// TODO: 在此添加命令处理程序代码
	if (Model_2D) {
		Trans_2d.bDrawLine = FALSE;
		Trans_2d.Translate(0, 10);
	}
	if (Model_3D) {
		Trans_3d.Translate(0, 10, 0);
	}
	Invalidate(FALSE);
}


void CGText3View::OnTranright()
{
	// TODO: 在此添加命令处理程序代码
	if (Model_2D) {
		Trans_2d.bDrawLine = FALSE;
		Trans_2d.Translate(10, 0);
	}
	if (Model_3D) {
		Trans_3d.Translate(10, 0, 0);
	}
	Invalidate(FALSE);
}


void CGText3View::OnTranleft()
{
	// TODO: 在此添加命令处理程序代码
	if (Model_2D) {
		Trans_2d.bDrawLine = FALSE;
		Trans_2d.Translate(-10, 0);
	}
	if (Model_3D) {
		Trans_3d.Translate(-10, 0, 0);
	}
	Invalidate(FALSE);
}


void CGText3View::OnTrandown()
{
	// TODO: 在此添加命令处理程序代码
	if (Model_2D) {
		Trans_2d.bDrawLine = FALSE;
		Trans_2d.Translate(0, -10);
	}
	if (Model_3D) {
		Trans_3d.Translate(0, -10, 0);
	}
	Invalidate(FALSE);
}


void CGText3View::OnRotation1()//逆时针
{
	// TODO: 在此添加命令处理程序代码
	if (Model_2D) {
		CP2 temp;
		temp.x = (Trans_2d.p[0].x + Trans_2d.p[2].x) / 2;
		temp.y = (Trans_2d.p[0].y + Trans_2d.p[2].y) / 2;
		Trans_2d.Rotate(30, temp);
	}
	if (Model_3D) {
		Trans_3d.RotateZ(30, Trans_3d.P[0]);
	}
	Invalidate(FALSE);
}


void CGText3View::OnRotation2()//顺时针
{
	// TODO: 在此添加命令处理程序代码
	if (Model_2D) {
		CP2 temp;
		temp.x = (Trans_2d.p[0].x + Trans_2d.p[2].x) / 2;
		temp.y = (Trans_2d.p[0].y + Trans_2d.p[2].y) / 2;
		Trans_2d.Rotate(-30, temp);
	}
	if (Model_3D) {
		Trans_3d.RotateZ(-30, Trans_3d.P[0]);
	}
	Invalidate(FALSE);
}

void CGText3View::OnRotation3()
{
	// TODO: 在此添加命令处理程序代码
	if (Model_3D) {
		Trans_3d.RotateY(-30, Trans_3d.P[0]);
	}
	Invalidate(FALSE);
}

void CGText3View::OnReflectX()
{
	// TODO: 在此添加命令处理程序代码
	if (Model_2D) {
		Trans_2d.ReflectX();
	}
	if (Model_3D) {
		Trans_3d.ReflectX();
	}
	Invalidate(FALSE);
}


void CGText3View::OnReflectY()
{
	// TODO: 在此添加命令处理程序代码
	if (Model_2D) {
		Trans_2d.ReflectY();
	}
	if (Model_3D) {
		Trans_3d.ReflectY();
	}
	Invalidate(FALSE);
}

void CGText3View::OnReflectZ()
{
	// TODO: 在此添加命令处理程序代码
	if (Model_3D) {
		Trans_3d.ReflectZ();
	}
	Invalidate(FALSE);
}


void CGText3View::OnXShearL()
{
	// TODO: 在此添加命令处理程序代码
	if (Model_2D) Trans_2d.Shear(0, -1);
	if (Model_3D) Trans_3d.ShearX(-1, -1);
	Invalidate(FALSE);
}


void CGText3View::OnXShearR()
{
	// TODO: 在此添加命令处理程序代码
	if (Model_2D) Trans_2d.Shear(0, 1);
	if (Model_3D) Trans_3d.ShearX(1, 1);
	Invalidate(FALSE);
}


void CGText3View::OnYShearD()
{
	// TODO: 在此添加命令处理程序代码
	if (Model_2D) Trans_2d.Shear(1, 0);
	if (Model_3D) Trans_3d.ShearX(1, 1);
	Invalidate(FALSE);
}


void CGText3View::OnYShearU()
{
	// TODO: 在此添加命令处理程序代码
	if (Model_2D) Trans_2d.Shear(-1, 0);
	if (Model_3D) Trans_3d.ShearY(-1, -1);
	Invalidate(FALSE);
}


void CGText3View::ObliqueProject(CP3 p)
{
	// TODO: 在此处添加实现代码.
	Trans_3d.ScreenP.x = p.x - p.z / sqrt(2);
	Trans_3d.ScreenP.y = p.y - p.z / sqrt(2);
}


void CGText3View::OnZShearB()
{
	// TODO: 在此添加命令处理程序代码
	if (Model_3D) Trans_3d.ShearZ(1, 1);
	Invalidate(FALSE);
}


void CGText3View::OnZShearF()
{
	// TODO: 在此添加命令处理程序代码
	if (Model_3D) Trans_3d.ShearZ(-1, -1);
	Invalidate(FALSE);
}




void CGText3View::OnScalePlus()
{
	// TODO: 在此添加命令处理程序代码
	if (Model_3D) Trans_3d.Scale(2, 2, 2);
	if (Model_2D) Trans_2d.Scale(2, 2);
	Invalidate(FALSE);
}


void CGText3View::OnScaleMin()
{
	// TODO: 在此添加命令处理程序代码
	if (Model_3D) Trans_3d.Scale(0.5, 0.5, 0.5);
	if (Model_2D) Trans_2d.Scale(0.5, 0.5);
	Invalidate(FALSE);
}


void CGText3View::OnUpdateReflectZ(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable((Model_3D) ? TRUE : FALSE);
}


void CGText3View::OnUpdateZShearB(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable((Model_3D) ? TRUE : FALSE);
}


void CGText3View::OnUpdateZShearF(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable((Model_3D) ? TRUE : FALSE);
}


void CGText3View::OnUpdateRotation3(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable((Model_3D) ? TRUE : FALSE);
}


void CGText3View::OnUpdateReflectX(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable((Model_3D || Model_2D) ? TRUE : FALSE);
}


void CGText3View::OnUpdateReflectY(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable((Model_3D || Model_2D) ? TRUE : FALSE);
}


void CGText3View::OnUpdateRotation1(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable((Model_3D || Model_2D) ? TRUE : FALSE);
}


void CGText3View::OnUpdateRotation2(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable((Model_3D || Model_2D) ? TRUE : FALSE);
}


void CGText3View::OnUpdateTrandown(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable((Model_3D || Model_2D) ? TRUE : FALSE);
}


void CGText3View::OnUpdateTranleft(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable((Model_3D || Model_2D) ? TRUE : FALSE);
}


void CGText3View::OnUpdateTranright(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable((Model_3D || Model_2D) ? TRUE : FALSE);
}


void CGText3View::OnUpdateTranup(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable((Model_3D || Model_2D) ? TRUE : FALSE);
}


void CGText3View::OnUpdateXShearL(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable((Model_3D || Model_2D) ? TRUE : FALSE);
}


void CGText3View::OnUpdateXShearR(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable((Model_3D || Model_2D) ? TRUE : FALSE);
}


void CGText3View::OnUpdateYShearD(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable((Model_3D || Model_2D) ? TRUE : FALSE);
}


void CGText3View::OnUpdateYShearU(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable((Model_3D || Model_2D) ? TRUE : FALSE);
}


void CGText3View::OnUpdateScaleMin(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable((Model_3D || Model_2D) ? TRUE : FALSE);
}


void CGText3View::OnUpdateScalePlus(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable((Model_3D || Model_2D) ? TRUE : FALSE);
}





void CGText3View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	bezier.bFlag = FALSE;
	bezier.RightCheck = TRUE;
	CView::OnRButtonDown(nFlags, point);
}









void CGText3View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	b3Curves.m_AbleToLeftBtn = FALSE;
	b3Curves.m_AbleToMove = FALSE;
	b3Curves.m_i = 0;
	CView::OnLButtonUp(nFlags, point);
}
