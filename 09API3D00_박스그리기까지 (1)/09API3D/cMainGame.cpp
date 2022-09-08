#include "stdafx.h"
#include "cMainGame.h"


cMainGame::cMainGame()
	// >> : 
	: m_hBitmap(NULL)
	, m_vEye(0, 0, -5)
	, m_vLookAt(0, 0, 0)
	, m_vUp(0, 1, 0)
	, m_vPosition(0, 0, 0)
	//, m_fCameraDistance(5.0f)
	//, m_isLButtonDown(false)
	//, m_vCamRotAngle(0, 0, 0)
	, m_fBoxRotY(0.0f)
	//, m_vBoxDirection(0, 0, 1)
	// << : 
{
	// >> : 
	//m_ptPrevMouse.x = 0;
	//m_ptPrevMouse.y = 0;
	// << : 
}


cMainGame::~cMainGame()
{
	// >> :
	SelectObject(m_MemDC, m_hOldBitmap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_MemDC);
	// << :
}

// >> : 

void cMainGame::Setup()
{
	HDC hdc = GetDC(g_hWnd);

	m_MemDC = CreateCompatibleDC(hdc);

	{
		RECT rc;
		GetClientRect(g_hWnd, &rc);
		m_hBitmap = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
		// SelectObject : ���ϰ����� ������ ��ü�� ��ȯ
		m_hOldBitmap = (HBITMAP)SelectObject(m_MemDC, m_hBitmap);
		ReleaseDC(g_hWnd, hdc);
	}

	// >> : p.136 �� �ִ� ��ǥ �״��.. ���ؽ� ��ǥ 

	{	// : ���ؽ� ����
		m_vecVertex.push_back(cVector3(-1.0f, -1.0f, -1.0f));
		m_vecVertex.push_back(cVector3(-1.0f, 1.0f, -1.0f));
		m_vecVertex.push_back(cVector3(1.0f, 1.0f, -1.0f));
		m_vecVertex.push_back(cVector3(1.0f, -1.0f, -1.0f));
		m_vecVertex.push_back(cVector3(-1.0f, -1.0f, 1.0f));
		m_vecVertex.push_back(cVector3(-1.0f, 1.0f, 1.0f));
		m_vecVertex.push_back(cVector3(1.0f, 1.0f, 1.0f));
		m_vecVertex.push_back(cVector3(1.0f, -1.0f, 1.0f));
	}

	{	// : �ε��� ����
		m_vecIndex.push_back(0);
		m_vecIndex.push_back(1);
		m_vecIndex.push_back(2);

		m_vecIndex.push_back(0);
		m_vecIndex.push_back(2);
		m_vecIndex.push_back(3);

		m_vecIndex.push_back(4);
		m_vecIndex.push_back(6);
		m_vecIndex.push_back(5);

		m_vecIndex.push_back(4);
		m_vecIndex.push_back(7);
		m_vecIndex.push_back(6);

		m_vecIndex.push_back(4);
		m_vecIndex.push_back(5);
		m_vecIndex.push_back(1);

		m_vecIndex.push_back(4);
		m_vecIndex.push_back(1);
		m_vecIndex.push_back(0);

		m_vecIndex.push_back(3);
		m_vecIndex.push_back(2);
		m_vecIndex.push_back(6);

		m_vecIndex.push_back(3);
		m_vecIndex.push_back(6);
		m_vecIndex.push_back(7);

		m_vecIndex.push_back(1);
		m_vecIndex.push_back(5);
		m_vecIndex.push_back(6);

		m_vecIndex.push_back(1);
		m_vecIndex.push_back(6);
		m_vecIndex.push_back(2);

		m_vecIndex.push_back(4);
		m_vecIndex.push_back(0);
		m_vecIndex.push_back(3);

		m_vecIndex.push_back(4);
		m_vecIndex.push_back(3);
		m_vecIndex.push_back(7);
	}

	m_matWorld = cMatrix::Identity(4);
	m_matView = cMatrix::Identity(4);
	m_matProj = cMatrix::Identity(4);
	m_matViewport = cMatrix::Identity(4);

	// : SetGrid()
}

void cMainGame::DrawGrid()
{
	int nNumHalfTile = 5;
	float fInterval = 1.0f;
	float fMax = nNumHalfTile * fInterval;
	float fMin = -nNumHalfTile * fInterval;
	for (int i = 1; i <= nNumHalfTile; ++i)
	{
		m_vecLineVertex.push_back(cVector3(fMin, 0, i * fInterval));
		m_vecLineVertex.push_back(cVector3(fMax, 0, i * fInterval));

		m_vecLineVertex.push_back(cVector3(fMin, 0, -i * fInterval));
		m_vecLineVertex.push_back(cVector3(fMax, 0, -i * fInterval));

		m_vecLineVertex.push_back(cVector3(i * fInterval, 0, fMin));
		m_vecLineVertex.push_back(cVector3(i * fInterval, 0, fMax));

		m_vecLineVertex.push_back(cVector3(-i * fInterval, 0, fMin));
		m_vecLineVertex.push_back(cVector3(-i * fInterval, 0, fMax));
	}

	m_vecLineVertex.push_back(cVector3(0, 0, fMin));
	m_vecLineVertex.push_back(cVector3(0, 0, fMax));

	m_vecLineVertex.push_back(cVector3(fMin, 0, 0));
	m_vecLineVertex.push_back(cVector3(fMax, 0, 0));

	m_vAxisXTextPosition = cVector3(fMax, 0, 0);
	m_vAxisZTextPosition = cVector3(0, 0, fMax);
}

void cMainGame::Update()
{
	if (GetKeyState('A') & 0x8000)
	{
		m_fBoxRotY -= 0.1f;
	}
	if (GetKeyState('D') & 0x8000)
	{
		m_fBoxRotY += 0.1f;
	}

	// : �̵� ��Ű�� 
	//Update_Move();	// : ���߿� �߰� 
	
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	// : ���콺�� ���� ȸ���̶� .. �̰� 1������ �̰� ���� ���ص� �ɵ�.
	/*
	cMatrix matRX = cMatrix::RotationX(m_vCamRotAngle.x);
	cMatrix matRY = cMatrix::RotationY(m_vCamRotAngle.y);
	cMatrix matR = matRX * matRY;
	m_vEye = cVector3(0, 5, -m_fCameraDistance);
	m_vEye = cVector3::TransformCoord(m_vEye, matR);

	m_vLookAt = m_vPosition;
	m_vEye = m_vEye + m_vPosition;
	matR = cMatrix::RotationY(m_fBoxRotY);
	*/
	m_vLookAt = cVector3(0.0f, 0.0f, 0.0f);
	m_vEye = cVector3(0.0f, 5.0f, -5.0f);

	cMatrix matR = cMatrix::RotationY(m_fBoxRotY);  // : Ű ���� ���� ȸ�� ����
	//m_vBoxDirection = cVector3(0, 0, 1);
	//m_vBoxDirection = cVector3::TransformNormal(m_vBoxDirection, matR);

	// : �� ��� ���� �ϱ�.
	m_matWorld = matR * cMatrix::Translation(m_vPosition);
	m_matView = cMatrix::View(m_vEye, m_vLookAt, m_vUp);
	m_matProj = cMatrix::Projection(PI / 4.0f,
		rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	m_matViewport = cMatrix::Viewport(0, 0, rc.right, rc.bottom, 0, 1);
}

void cMainGame::Render(HDC hdc)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	// ��ȭ���� �������
	PatBlt(m_MemDC, rc.left, rc.top, rc.right, rc.bottom, WHITENESS);

	// : Box �׸���..
	cMatrix matWVP = m_matWorld * m_matView * m_matProj;
	for (size_t i = 0; i < m_vecIndex.size(); i += 3)
	{
		cVector3 v1 = m_vecVertex[m_vecIndex[i]];
		cVector3 v2 = m_vecVertex[m_vecIndex[i + 1]];
		cVector3 v3 = m_vecVertex[m_vecIndex[i + 2]];

		// �� ���� �������� �����̽��� �̵�
		v1 = cVector3::TransformCoord(v1, matWVP);
		v2 = cVector3::TransformCoord(v2, matWVP);
		v3 = cVector3::TransformCoord(v3, matWVP);

		// : �Ⱥ��̴� �� �ɷ�����..
		/*
			�߰� ����.. 
			if (IsBackFace(v1, v2, v3))
				continue;
		*/

		// : ���̴� �鿡 ���� ����Ʈ ��ȯ ����
		v1 = cVector3::TransformCoord(v1, m_matViewport);
		v2 = cVector3::TransformCoord(v2, m_matViewport);
		v3 = cVector3::TransformCoord(v3, m_matViewport);

		// �ﰢ�� �׸���.
		MoveToEx(m_MemDC, v1.x, v1.y, NULL);
		LineTo(m_MemDC, v2.x, v2.y);
		LineTo(m_MemDC, v3.x, v3.y);
		LineTo(m_MemDC, v1.x, v1.y);
	}

	// >> : �׸��� �׸���
	// DrawGrid();

	// ��ȭ���� �׷��� ������ ȭ�鿡 ǥ��
	BitBlt(hdc, 0, 0, rc.right, rc.bottom, m_MemDC, 0, 0, SRCCOPY);

}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		// : ���콺 �� ����
		// : ���콺 �ٿ� �÷��� ��
		break;
	case WM_LBUTTONUP:
		// : ���콺 �ٿ� �÷��� reset
		break;
	case WM_MOUSEMOVE:
		// : ���콺 �ٿ� ���� �̵� �� ó�� 
		break;
	case WM_MOUSEWHEEL:
		// : ���콺 �� �̵����� ���� ī�޶� �Ÿ� ���� 
		break;
	}
}
// << : 
