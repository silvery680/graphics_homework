#pragma once
#include "Transformation_2D.h"
typedef struct cp3{
	double x;
	double y;
	double z;
	double w;
} CP3;

typedef struct face {
	int vN; //面的顶点数
	int *vI;//面的顶点索引
} CFace;

class Transformation_3D
{
public:
	Transformation_3D();
	~Transformation_3D();
	void SetNum(int en, int index);

public:
	CP3 P[8];//点表
	CFace F[6];//面表
	CP2 ScreenP;//屏幕坐标系的二维坐标点
	BOOL bDrawLine;
	int PtCount;

	CP2 p[4];

	double T[4][4];
	CP3 *POld;
	int num;
	void Identity();
	void MultiMatrix();
	void Translate(double tx, double ty, double tz);
	void RotateX(double beta);
	void RotateX(double beta, CP3 p);
	void RotateZ(double beta, CP3 p);
	void RotateZ(double beta);
	void ReflectX();
	void ReflectY();
	void ReflectZ();
	void ShearX(double d, double g);
	void ShearY(double b, double h);
	void ShearZ(double c, double f);
	void Scale(double sx, double sy, double sz);
	void SetPoint(double w, double l, double h);
	void RotateY(double beta);
	void RotateY(double beta, CP3 p);
};

