#pragma once

#include "cVector3.h"	// << : 
#include "cMatrix.h"	// << : 

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

	// >> : 
private:
	HDC			m_MemDC;
	HBITMAP		m_hOldBitmap, m_hBitmap;

	std::vector<cVector3> m_vecVertex[5];
	std::vector<DWORD>		m_vecIndex[5];
	std::vector<cVector3>	m_vecLineVertex;

	cMatrix					m_matWorld[3];
	cMatrix					m_matView;
	cMatrix					m_matProj;
	cMatrix					m_matViewport;

	cVector3				m_vEye;
	cVector3				m_vLookAt;
	cVector3				m_vUp;
	cVector3				m_vPosition;
	cVector3				m_vPosition2;

	POINT					m_ptPrevMouse;
	bool					m_isLButtonDown;
	float					m_fCameraDistance;

	cVector3				m_vCamRotAngle;
	cVector3				m_vAxisXTextPosition;
	cVector3				m_vAxisZTextPosition;

	float					m_fBoxRotY;
	float					m_fBoxRotX;
	cVector3				m_vBoxDirection;

public:
	void Setup();
	void Update();
	void Render(HDC hdc);
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// >> : �߰� ���� 
	void SetGrid();
	void DrawGrid();
	bool IsBackFace(cVector3& v1, cVector3& v2, cVector3& v3);
	void Update_Move();
	// << : 
};

