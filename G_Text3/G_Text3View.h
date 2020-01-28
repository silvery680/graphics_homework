
// G_Text3View.h: CGText3View 类的接口
//

#pragma once
#include "Transformation_2D.h"
#include "Transformation_3D.h"
#include "Bezier.h"
#include "B3Curves.h"

class CGText3View : public CView
{
protected: // 仅从序列化创建
	CGText3View() noexcept;
	DECLARE_DYNCREATE(CGText3View)

// 特性
public:
	CGText3Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CGText3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CRect rect;
// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	BOOL Model_3D;
	BOOL Model_2D;
	BOOL Model_Bezier;
	Transformation_2D Trans_2d;
	Transformation_3D Trans_3d;
	Bezier bezier;
	B3Curves b3Curves;
	void DoubleBuffer();
	void DrawObject(CDC * pDC);
	void DrawObject_3D(CDC * pDC);
	void Draw_B3Curves(CDC * pDC);
	void Draw_Bezier(CDC * pDC);
	void DrawPolygon(CDC * pDC);
	void DrawPolygon_3D(CDC * pDC);
	void WindowClear();
	CP2 Convert(CPoint point);
	CPoint Convert_Point(CPoint point);
	void ObliqueProject(CP3 p);
	void DrawCtrlPolygon(CDC * pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDrawpic();
	afx_msg void OnTran2d();
	afx_msg void OnUpdateTran2d(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDrawpic(CCmdUI *pCmdUI);
	afx_msg void OnTranup();
	afx_msg void OnTranright();
	afx_msg void OnTranleft();
	afx_msg void OnTrandown();
	afx_msg void OnRotation1();
	afx_msg void OnRotation2();
	afx_msg void OnReflectX();
	afx_msg void OnReflectY();
	afx_msg void OnXShearL();
	afx_msg void OnXShearR();
	afx_msg void OnYShearD();
	afx_msg void OnYShearU();
	afx_msg void OnTran3d();
	afx_msg void OnUpdateTran3d(CCmdUI *pCmdUI);
	afx_msg void OnZShearB();
	afx_msg void OnZShearF();
	afx_msg void OnReflectZ();
	afx_msg void OnRotation3();
	afx_msg void OnScalePlus();
	afx_msg void OnScaleMin();
	afx_msg void OnUpdateReflectZ(CCmdUI *pCmdUI);
	afx_msg void OnUpdateZShearB(CCmdUI *pCmdUI);
	afx_msg void OnUpdateZShearF(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRotation3(CCmdUI *pCmdUI);
	afx_msg void OnUpdateReflectX(CCmdUI *pCmdUI);
	afx_msg void OnUpdateReflectY(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRotation1(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRotation2(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTrandown(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTranleft(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTranright(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTranup(CCmdUI *pCmdUI);
	afx_msg void OnUpdateXShearL(CCmdUI *pCmdUI);
	afx_msg void OnUpdateXShearR(CCmdUI *pCmdUI);
	afx_msg void OnUpdateYShearD(CCmdUI *pCmdUI);
	afx_msg void OnUpdateYShearU(CCmdUI *pCmdUI);
	afx_msg void OnUpdateScaleMin(CCmdUI *pCmdUI);
	afx_msg void OnUpdateScalePlus(CCmdUI *pCmdUI);
	afx_msg void OnSetBezier();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	BOOL Model_B3Curves;
	afx_msg void OnSetB3curves();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // G_Text3View.cpp 中的调试版本
inline CGText3Doc* CGText3View::GetDocument() const
   { return reinterpret_cast<CGText3Doc*>(m_pDocument); }
#endif

