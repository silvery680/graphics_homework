#pragma once
class B3Curves
{
public:
	B3Curves();
	~B3Curves();

	void B3Curves_Print(CPoint q[], CDC * pDC);

public:
	BOOL	m_AbleToLeftBtn;//鼠标左键有效
	BOOL	m_AbleToMove;//鼠标移动点有效
	int		m_i;//控制点坐标编号
	CPoint	P[9];//鼠标点
};

