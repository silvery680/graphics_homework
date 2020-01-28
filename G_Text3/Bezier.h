#pragma once
class Bezier
{
public:
	Bezier();
	~Bezier();

	void DrawBezier(CDC * pDC);
	double Cni(const int & n, const int & i);
	long Fac(int m);

public:
	BOOL bFlag; //标志
	BOOL RightCheck;
	CPoint *P;//顶点
	int  CtrlPointNum;//控制多边形顶点个数
	int  n;//Bezier曲线的阶次
	int  N_MAX_POINT = 21;//控制多边形的最大顶点数
};

