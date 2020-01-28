#include "stdafx.h"
#include "Transformation_3D.h"
#define PI 3.14159

Transformation_3D::Transformation_3D()
{
	//P[0].x = 0; P[0].y = 0; P[0].z = 0; P[0].w = 1.0;//后左下
	//P[1].x = 100; P[1].y = 0; P[1].z = 0; P[1].w = 1.0;//后右下
	//P[2].x = 100; P[2].y = 100; P[2].z = 0; P[2].w = 1.0;//后右上
	//P[3].x = 0; P[3].y = 100; P[3].z = 0; P[3].w = 1.0;//后左上
	//P[4].x = 0; P[4].y = 0; P[4].z = 100; P[4].w = 1.0;//前左下
	//P[5].x = 100; P[5].y = 0; P[5].z = 100; P[5].w = 1.0;//前右下
	//P[6].x = 100; P[6].y = 100; P[6].z = 100; P[6].w = 1.0;//前右上
	//P[7].x = 0; P[7].y = 100; P[7].z = 100; P[7].w = 1.0;//前左上 

	SetNum(4, 0); F[0].vI[0] = 4; F[0].vI[1] = 5; F[0].vI[2] = 6; F[0].vI[3] = 7;//前面
	SetNum(4, 1); F[1].vI[0] = 0; F[1].vI[1] = 3; F[1].vI[2] = 2; F[1].vI[3] = 1;//后面
	SetNum(4, 2); F[2].vI[0] = 0; F[2].vI[1] = 4; F[2].vI[2] = 7; F[2].vI[3] = 3;//左面
	SetNum(4, 3); F[3].vI[0] = 1; F[3].vI[1] = 2; F[3].vI[2] = 6; F[3].vI[3] = 5;//右面
	SetNum(4, 4); F[4].vI[0] = 2; F[4].vI[1] = 3; F[4].vI[2] = 7; F[4].vI[3] = 6;//顶面
	SetNum(4, 5); F[5].vI[0] = 0; F[5].vI[1] = 1; F[5].vI[2] = 5; F[5].vI[3] = 4;//底面

	POld = P;
	num = 8;
	bDrawLine = false;
	PtCount = 0;
}


Transformation_3D::~Transformation_3D()
{
}

void Transformation_3D::SetNum(int en, int index)
{
	F[index].vN = en;
	F[index].vI = new int[en];
}

void Transformation_3D::Identity()
{
	// TODO: 在此处添加实现代码.
	T[0][0] = 1.0; T[0][1] = 0.0; T[0][2] = 0.0; T[0][3] = 0.0;
	T[1][0] = 0.0; T[1][1] = 1.0; T[1][2] = 0.0; T[1][3] = 0.0;
	T[2][0] = 0.0; T[2][1] = 0.0; T[2][2] = 1.0; T[2][3] = 0.0;
	T[3][0] = 0.0; T[3][1] = 0.0; T[3][2] = 0.0; T[3][3] = 1.0;
}



void Transformation_3D::MultiMatrix()
{
	// TODO: 在此处添加实现代码.
	CP3 *PNew = new CP3[num];
	for (int i = 0; i < num; i++)
	{
		PNew[i] = POld[i];
	}
	for (int j = 0; j < num; j++)
	{
		POld[j].x = PNew[j].x*T[0][0] + PNew[j].y*T[1][0] + PNew[j].z*T[2][0] + PNew[j].w*T[3][0];
		POld[j].y = PNew[j].x*T[0][1] + PNew[j].y*T[1][1] + PNew[j].z*T[2][1] + PNew[j].w*T[3][1];
		POld[j].z = PNew[j].x*T[0][2] + PNew[j].y*T[1][2] + PNew[j].z*T[2][2] + PNew[j].w*T[3][2];
		POld[j].w = PNew[j].x*T[0][3] + PNew[j].y*T[1][3] + PNew[j].z*T[2][3] + PNew[j].w*T[3][3];
	}
	delete[]PNew;
}


void Transformation_3D::Translate(double tx, double ty, double tz)//平移变换矩阵
{
	// TODO: 在此处添加实现代码.
	Identity();
	T[3][0] = tx;
	T[3][1] = ty;
	T[3][2] = tz;
	MultiMatrix();
}


void Transformation_3D::RotateX(double beta)
{
	// TODO: 在此处添加实现代码.
	Identity();
	double rad = beta * PI / 180;
	T[1][1] = cos(rad); T[1][2] = sin(rad);
	T[2][1] = -sin(rad); T[2][2] = cos(rad);
	MultiMatrix();
}


void Transformation_3D::RotateX(double beta, CP3 p)
{
	// TODO: 在此处添加实现代码.
	Translate(-p.x, -p.y, -p.z);
	RotateX(beta);
	Translate(p.x, p.y, p.z);
}

void Transformation_3D::RotateY(double beta)
{
	// TODO: 在此处添加实现代码.
	Identity();
	double rad = beta * PI / 180;
	T[0][0] = cos(rad); T[0][2] = -sin(rad);
	T[2][0] = sin(rad); T[2][2] = cos(rad);
	MultiMatrix();
}

void Transformation_3D::RotateY(double beta, CP3 p)//相对于任意点的绕Y轴旋转变换矩阵
{
	Translate(-p.x, -p.y, -p.z);
	RotateY(beta);
	Translate(p.x, p.y, p.z);
}

void Transformation_3D::RotateZ(double beta)
{
	// TODO: 在此处添加实现代码.
	Identity();
	double rad = beta * PI / 180;
	T[0][0] = cos(rad); T[0][1] = sin(rad);
	T[1][0] = -sin(rad); T[1][1] = cos(rad);
	MultiMatrix();
}

void Transformation_3D::RotateZ(double beta, CP3 p)
{
	// TODO: 在此处添加实现代码.
	Translate(-p.x, -p.y, -p.z);
	RotateZ(beta);
	Translate(p.x, p.y, p.z);
}


void Transformation_3D::ReflectX()
{
	// TODO: 在此处添加实现代码.
	Identity();
	T[1][1] = -1;
	T[2][2] = -1;
	MultiMatrix();
}


void Transformation_3D::ReflectY()
{
	// TODO: 在此处添加实现代码.
	Identity();
	T[0][0] = -1;
	T[2][2] = -1;
	MultiMatrix();
}


void Transformation_3D::ReflectZ()
{
	// TODO: 在此处添加实现代码.
	Identity();
	T[0][0] = -1;
	T[1][1] = -1;
	MultiMatrix();
}


void Transformation_3D::ShearX(double d, double g)
{
	// TODO: 在此处添加实现代码.
	Identity();
	T[1][0] = d;
	T[2][0] = g;
	MultiMatrix();
}


void Transformation_3D::ShearY(double b, double h)
{
	// TODO: 在此处添加实现代码.
	Identity();
	T[0][1] = b;
	T[2][1] = h;
	MultiMatrix();
}


void Transformation_3D::ShearZ(double c, double f)
{
	// TODO: 在此处添加实现代码.
	Identity();
	T[0][2] = c;
	T[1][2] = f;
	MultiMatrix();
}




void Transformation_3D::Scale(double sx, double sy, double sz)
{
	// TODO: 在此处添加实现代码.
	Identity();
	T[0][0] = sx;
	T[1][1] = sy;
	T[2][2] = sz;
	MultiMatrix();
}


void Transformation_3D::SetPoint(double w, double l, double h)
{
	// TODO: 在此处添加实现代码.
	P[0].x = 0; P[0].y = 0; P[0].z = 0; P[0].w = 1;
	P[1].x = w; P[1].y = 0; P[1].z = 0; P[1].w = 1;
	P[2].x = w; P[2].y = h; P[2].z = 0; P[2].w = 1;
	P[3].x = 0; P[3].y = h; P[3].z = 0; P[3].w = 1;
	P[4].x = 0; P[4].y = 0; P[4].z = l; P[4].w = 1;
	P[5].x = w; P[5].y = 0; P[5].z = l; P[5].w = 1;
	P[6].x = w; P[6].y = h; P[6].z = l; P[6].w = 1;
	P[7].x = 0; P[7].y = h; P[7].z = l; P[7].w = 1;
}
