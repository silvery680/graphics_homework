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
	BOOL bFlag; //��־
	BOOL RightCheck;
	CPoint *P;//����
	int  CtrlPointNum;//���ƶ���ζ������
	int  n;//Bezier���ߵĽ״�
	int  N_MAX_POINT = 21;//���ƶ���ε���󶥵���
};

