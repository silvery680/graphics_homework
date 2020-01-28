#include "stdafx.h"
#include "Bezier.h"


Bezier::Bezier()
{
	P = new CPoint[N_MAX_POINT];
	bFlag = FALSE;
	RightCheck = FALSE;
	CtrlPointNum = 0;
}


Bezier::~Bezier()
{
}


void Bezier::DrawBezier(CDC *pDC)
{
	// TODO: 在此处添加实现代码.
	CPen NewPen, *pOldPen;
	NewPen.CreatePen(PS_SOLID, 3, RGB(87, 250, 255));//曲线颜色为蓝色
	pOldPen = pDC->SelectObject(&NewPen);
	pDC->MoveTo(P[0]);
	for (double t = 0.0; t <= 1.0; t += 0.01)
	{
		double x = 0, y = 0;
		for (int i = 0; i <= n; i++)
		{
			x += P[i].x*Cni(n, i)*pow(t, i)*pow(1 - t, n - i);
			y += P[i].y*Cni(n, i)*pow(t, i)*pow(1 - t, n - i);
		}
		pDC->LineTo(round(x), round(y));
	}
	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();
}


double Bezier::Cni(const int &n, const int &i)
{
	// TODO: 在此处添加实现代码.
	return double(Fac(n)) / (Fac(i)*Fac(n - i));
}




long Bezier::Fac(int m)
{
	// TODO: 在此处添加实现代码.
	long f;
	if (m == 0 || m == 1)
		f = 1;
	else
		f = m * Fac(m - 1);
	return f;
}
