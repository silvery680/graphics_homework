#include "stdafx.h"
#include "Transformation_2D.h"
#define PI 3.14159


Transformation_2D::Transformation_2D()
{
	num = 4;
	POld = p;
	PtCount = 0;
	bDrawLine = FALSE;
}


Transformation_2D::~Transformation_2D()
{
}


void Transformation_2D::MultiMatrix()
{
	// TODO: 在此处添加实现代码.
	CP2 *PNew = new CP2[num];
	for (int i = 0; i < num; i++)
	{
		PNew[i] = POld[i];
	}
	for (int j = 0; j < num; j++)
	{
		POld[j].x = PNew[j].x*T[0][0] + PNew[j].y*T[1][0] + PNew[j].w*T[2][0];
		POld[j].y = PNew[j].x*T[0][1] + PNew[j].y*T[1][1] + PNew[j].w*T[2][1];
		POld[j].w = PNew[j].x*T[0][2] + PNew[j].y*T[1][2] + PNew[j].w*T[2][2];
	}
	delete[]PNew;
}


void Transformation_2D::Identity()
{
	// TODO: 在此处添加实现代码.
	T[0][0] = 1.0; T[0][1] = 0.0; T[0][2] = 0.0;
	T[1][0] = 0.0; T[1][1] = 1.0; T[1][2] = 0.0;
	T[2][0] = 0.0; T[2][1] = 0.0; T[2][2] = 1.0;
}


void Transformation_2D::Translate(double tx, double ty)
{
	// TODO: 在此处添加实现代码
	Identity();
	T[2][0] = tx;
	T[2][1] = ty;
	MultiMatrix();
}



void Transformation_2D::Rotate(double beta)
{
	// TODO: 在此处添加实现代码.
	Identity();
	double rad = beta * PI / 180;
	T[0][0] = cos(rad); T[0][1] = sin(rad);
	T[1][0] = -sin(rad); T[1][1] = cos(rad);
	MultiMatrix();
}


void Transformation_2D::Rotate(double beta, CP2 p)
{
	// TODO: 在此处添加实现代码.
	Translate(-p.x, -p.y);
	Rotate(beta);
	Translate(p.x, p.y);
}


void Transformation_2D::ReflectX()
{
	// TODO: 在此处添加实现代码.
	Identity();
	T[0][0] = 1;
	T[1][1] = -1;
	MultiMatrix();
}


void Transformation_2D::ReflectY()
{
	// TODO: 在此处添加实现代码.
	Identity();
	T[0][0] = -1;
	T[1][1] = 1;
	MultiMatrix();
}


void Transformation_2D::Shear(double b, double c)
{
	// TODO: 在此处添加实现代码.
	Identity();
	T[0][1] = b;
	T[1][0] = c;
	MultiMatrix();
}


void Transformation_2D::Scale(double sx, double sy)
{
	// TODO: 在此处添加实现代码.
	Identity();
	T[0][0] = sx;
	T[1][1] = sy;
	MultiMatrix();
}
