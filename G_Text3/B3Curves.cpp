#include "stdafx.h"
#include "B3Curves.h"


B3Curves::B3Curves()
{
	m_AbleToLeftBtn = FALSE;
	m_AbleToMove = FALSE;
	m_i = -1;
	//初始化9个控制点
	P[0].x = -380; P[0].y = 50;
	P[1].x = -350; P[1].y = -50;
	P[2].x = -184; P[2].y = 120;
	P[3].x = -72; P[3].y = -133;
	P[4].x = 25; P[4].y = 200;
	P[5].x = 150; P[5].y = -50;
	P[6].x = 182; P[6].y = -260;
	P[7].x = 350; P[7].y = 150;
	P[8].x = 450; P[8].y = 50;
}


B3Curves::~B3Curves()
{
}


void B3Curves::B3Curves_Print(CPoint q[], CDC *pDC)
{
	// TODO: 在此处添加实现代码.
	CPoint p;
	double F03, F13, F23, F33;
	p.x = round((q[0].x + 4.0*q[1].x + q[2].x) / 6.0);//t＝0的起点x坐标
	p.y = round((q[0].y + 4.0*q[1].y + q[2].y) / 6.0);//t＝0的起点y坐标
	pDC->MoveTo(p);
	CPen NewPen(PS_SOLID, 2, RGB(255, 0, 0));//红笔画B样条曲线
	CPen *pOldPen = pDC->SelectObject(&NewPen);
	for (int i = 1; i < 7; i++)//6段样条曲线
	{
		for (double t = 0; t <= 1; t += 0.01)
		{
			F03 = (-t * t*t + 3 * t*t - 3 * t + 1) / 6;//计算F0,3(t)
			F13 = (3 * t*t*t - 6 * t*t + 4) / 6;//计算F1,3(t)
			F23 = (-3 * t*t*t + 3 * t*t + 3 * t + 1) / 6;//计算F2,3(t)
			F33 = t * t*t / 6;//计算B3,3(t)
			p.x = round(q[i - 1].x*F03 + q[i].x*F13 + q[i + 1].x*F23 + q[i + 2].x*F33);
			p.y = round(q[i - 1].y*F03 + q[i].y*F13 + q[i + 1].y*F23 + q[i + 2].y*F33);
			pDC->LineTo(p);
		}
	}
	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();
}
