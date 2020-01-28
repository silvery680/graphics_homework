#pragma once

typedef struct cp2 {
	double x;//直线段端点x坐标
	double y;//直线段端点y坐标
	double w;//直线段w
} CP2;

class Transformation_2D
{
public:
	BOOL bDrawLine;
	int PtCount;
	CP2 p[4];
	CP2 *POld;
	double T[3][3];
	int num;
public:
	Transformation_2D();
	~Transformation_2D();
	void MultiMatrix();
	void Identity();
	void Translate(double tx, double ty);
	void Rotate(double beta);
	void Rotate(double beta, CP2 p);
	void ReflectX();
	void ReflectY();
	void Shear(double b, double c);
	void Scale(double sx, double sy);
};

