#pragma once
class B3Curves
{
public:
	B3Curves();
	~B3Curves();

	void B3Curves_Print(CPoint q[], CDC * pDC);

public:
	BOOL	m_AbleToLeftBtn;//��������Ч
	BOOL	m_AbleToMove;//����ƶ�����Ч
	int		m_i;//���Ƶ�������
	CPoint	P[9];//����
};

