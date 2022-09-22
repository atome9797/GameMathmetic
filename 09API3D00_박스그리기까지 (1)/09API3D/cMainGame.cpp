#include "stdafx.h"
#include "cMainGame.h"


cMainGame::cMainGame()
// >> : 
	: m_hBitmap(NULL)
	, m_vEye(0, 0, -5)
	, m_vLookAt(0, 0, 0)
	, m_vUp(0, 1, 0)
	, m_vPosition(0, 0, 0)
	, m_vPosition2(0, 0, 0)
	//, m_fCameraDistance(5.0f)
	//, m_isLButtonDown(false)
	//, m_vCamRotAngle(0, 0, 0)
	, m_fBoxRotY(0.0f)
	, m_fBoxRotX(0.0f)
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
	
	// : ���ؽ� ����
	//m_vecVertex[0].push_back(cVector3(-1.0f, -1.0f, -1.0f) * 0.5); //8
	//m_vecVertex[0].push_back(cVector3(-1.0f, 1.0f, -1.0f) * 0.5);//4 
	//m_vecVertex[0].push_back(cVector3(1.0f, 1.0f, -1.0f) * 0.5); //3
	//m_vecVertex[0].push_back(cVector3(1.0f, -1.0f, -1.0f) * 0.5); //7
	//m_vecVertex[0].push_back(cVector3(-1.0f, -1.0f, 1.0f) * 0.5); //5
	//m_vecVertex[0].push_back(cVector3(-1.0f, 1.0f, 1.0f) * 0.5); //1
	//m_vecVertex[0].push_back(cVector3(1.0f, 1.0f, 1.0f) * 0.5); //2
	//m_vecVertex[0].push_back(cVector3(1.0f, -1.0f, 1.0f) * 0.5); //6

	//m_vecVertex[1].push_back(cVector3(6.0f, -1.0f, -1.0f) * 0.5); //8
	//m_vecVertex[1].push_back(cVector3(6.0f, 1.0f, -1.0f) * 0.5); //4
	//m_vecVertex[1].push_back(cVector3(8.0f, 1.0f, -1.0f) * 0.5); //3
	//m_vecVertex[1].push_back(cVector3(8.0f, -1.0f, -1.0f) * 0.5); //7
	//m_vecVertex[1].push_back(cVector3(6.0f, -1.0f, 1.0f) * 0.5); //5
	//m_vecVertex[1].push_back(cVector3(6.0f, 1.0f, 1.0f) * 0.5); //1
	//m_vecVertex[1].push_back(cVector3(8.0f, 1.0f, 1.0f) * 0.5); //2
	//m_vecVertex[1].push_back(cVector3(8.0f, -1.0f, 1.0f) * 0.5); //6


	for (int i = 0; i < 5; i++) {

		if (i < 2)
		{
			// : ���ؽ� ����
			m_vecVertex[i].push_back(cVector3(-1.0f + (i * 6.0f), -1.0f, -1.0f) * 0.5); //8
			m_vecVertex[i].push_back(cVector3(-1.0f + (i * 6.0f), 1.0f, -1.0f) * 0.5);//4 
			m_vecVertex[i].push_back(cVector3(1.0f + (i * 6.0f), 1.0f, -1.0f) * 0.5); //3
			m_vecVertex[i].push_back(cVector3(1.0f + (i * 6.0f), -1.0f, -1.0f) * 0.5); //7
			m_vecVertex[i].push_back(cVector3(-1.0f + (i * 6.0f), -1.0f, 1.0f) * 0.5); //5
			m_vecVertex[i].push_back(cVector3(-1.0f + (i * 6.0f), 1.0f, 1.0f) * 0.5); //1
			m_vecVertex[i].push_back(cVector3(1.0f + (i * 6.0f), 1.0f, 1.0f) * 0.5); //2
			m_vecVertex[i].push_back(cVector3(1.0f + (i * 6.0f), -1.0f, 1.0f) * 0.5); //6
		}
		else if(i >= 2 && i < 4){
			// : ���ؽ� ����
			m_vecVertex[i].push_back(cVector3(-1.0f + ((i - 2) * 6.0f), -1.0f, -1.0f) * 0.5); //8
			m_vecVertex[i].push_back(cVector3(-1.0f + ((i - 2) * 6.0f), 1.0f, -1.0f) * 0.5);//4 
			m_vecVertex[i].push_back(cVector3(1.0f + ((i - 2) * 6.0f), 1.0f, -1.0f) * 0.5); //3
			m_vecVertex[i].push_back(cVector3(1.0f + ((i - 2) * 6.0f), -1.0f, -1.0f) * 0.5); //7
			m_vecVertex[i].push_back(cVector3(-1.0f + ((i - 2) * 6.0f), -1.0f, 1.0f) * 0.5); //5
			m_vecVertex[i].push_back(cVector3(-1.0f + ((i - 2) * 6.0f), 1.0f, 1.0f) * 0.5); //1
			m_vecVertex[i].push_back(cVector3(1.0f + ((i - 2) * 6.0f), 1.0f, 1.0f) * 0.5); //2
			m_vecVertex[i].push_back(cVector3(1.0f + ((i - 2) * 6.0f), -1.0f, 1.0f) * 0.5); //6
		}
		else
		{
			m_vecVertex[i].push_back(cVector3(-1.0f, 1.0f, -1.0f)); //8
			m_vecVertex[i].push_back(cVector3(-1.0f, 2.0f, -1.0f) );//4 
			m_vecVertex[i].push_back(cVector3(4.0f, 2.0f, -1.0f) ); //3
			m_vecVertex[i].push_back(cVector3(4.0f, 1.0f, -1.0f)); //7
			m_vecVertex[i].push_back(cVector3(-1.0f, 1.0f, 5.0f)); //5
			m_vecVertex[i].push_back(cVector3(-1.0f, 2.0f, 5.0f) ); //1
			m_vecVertex[i].push_back(cVector3(4.0f, 2.0f, 5.0f)); //2
			m_vecVertex[i].push_back(cVector3(4.0f, 1.0f, 5.0f)); //6
		}
		
		// : �ε��� ����
		m_vecIndex[i].push_back(0);
		m_vecIndex[i].push_back(1);
		m_vecIndex[i].push_back(2);

		m_vecIndex[i].push_back(0);
		m_vecIndex[i].push_back(2);
		m_vecIndex[i].push_back(3);

		m_vecIndex[i].push_back(4);
		m_vecIndex[i].push_back(6);
		m_vecIndex[i].push_back(5);

		m_vecIndex[i].push_back(4);
		m_vecIndex[i].push_back(7);
		m_vecIndex[i].push_back(6);

		m_vecIndex[i].push_back(4);
		m_vecIndex[i].push_back(5);
		m_vecIndex[i].push_back(1);

		m_vecIndex[i].push_back(4);
		m_vecIndex[i].push_back(1);
		m_vecIndex[i].push_back(0);

		m_vecIndex[i].push_back(3);
		m_vecIndex[i].push_back(2);
		m_vecIndex[i].push_back(6);

		m_vecIndex[i].push_back(3);
		m_vecIndex[i].push_back(6);
		m_vecIndex[i].push_back(7);

		m_vecIndex[i].push_back(1);
		m_vecIndex[i].push_back(5);
		m_vecIndex[i].push_back(6);

		m_vecIndex[i].push_back(1);
		m_vecIndex[i].push_back(6);
		m_vecIndex[i].push_back(2);

		m_vecIndex[i].push_back(4);
		m_vecIndex[i].push_back(0);
		m_vecIndex[i].push_back(3);

		m_vecIndex[i].push_back(4);
		m_vecIndex[i].push_back(3);
		m_vecIndex[i].push_back(7);
	}
	
	//�׵���ķ� ����
	m_matWorld[0] = cMatrix::Identity(4);
	m_matWorld[1] = cMatrix::Identity(4);

	m_vPosition2.z += 5.0f;
	m_matWorld[1] = cMatrix::Translation(m_vPosition2);

	m_matWorld[2] = cMatrix::Identity(4);

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
		//m_fBoxRotY -= 0.1f;
	}
	if (GetKeyState('D') & 0x8000)
	{
		//m_fBoxRotY += 0.1f;
	}
	if (GetKeyState('W') & 0x8000)
	{
		m_fBoxRotX += 0.1f;
		m_vPosition.z += 0.1f;
		m_vPosition2.z += 0.1f;
	}
	if (GetKeyState('S') & 0x8000)
	{
		m_fBoxRotX -= 0.1f;
		m_vPosition.z -= 0.1f;
		m_vPosition2.z -= 0.1f;
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

	cMatrix matR_Y = cMatrix::RotationY(m_fBoxRotY);  // : Ű ���� ���� ȸ�� ����
	cMatrix matR_X = cMatrix::RotationX(m_fBoxRotX);  // : Ű ���� ���� ȸ�� ����

	//m_vBoxDirection = cVector3(0, 0, 1);
	//m_vBoxDirection = cVector3::TransformNormal(m_vBoxDirection, matR);

	// : �� ��� ���� �ϱ�.
	m_matWorld[0] = matR_X * matR_Y  * cMatrix::Translation(m_vPosition);
	m_matWorld[1] = matR_X * matR_Y  * cMatrix::Translation(m_vPosition2);
	m_matWorld[2] = cMatrix::Translation(m_vPosition);
	m_matView = cMatrix::View(m_vEye, m_vLookAt, m_vUp);
	m_matProj = cMatrix::Projection(PI / 2.0f,
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
	cMatrix matWVP = m_matWorld[0] * m_matView * m_matProj;
	
	for (size_t k = 0; k < 2; k++)
	{
		for (size_t i = 0; i < m_vecIndex[k].size(); i += 3)
		{
			cVector3 v1 = m_vecVertex[k][m_vecIndex[k][i]];
			cVector3 v2 = m_vecVertex[k][m_vecIndex[k][i + 1]];
			cVector3 v3 = m_vecVertex[k][m_vecIndex[k][i + 2]];

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
	}

	cMatrix matWVP2 = m_matWorld[1] * m_matView * m_matProj;

	for (size_t k = 2; k < 4; k++)
	{
		for (size_t i = 0; i < m_vecIndex[k].size(); i += 3)
		{
			cVector3 v1 = m_vecVertex[k][m_vecIndex[k][i]];
			cVector3 v2 = m_vecVertex[k][m_vecIndex[k][i + 1]];
			cVector3 v3 = m_vecVertex[k][m_vecIndex[k][i + 2]];

			// �� ���� �������� �����̽��� �̵�
			v1 = cVector3::TransformCoord(v1, matWVP2);
			v2 = cVector3::TransformCoord(v2, matWVP2);
			v3 = cVector3::TransformCoord(v3, matWVP2);

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
	}

	cMatrix matWVP3 = m_matWorld[2] * m_matView * m_matProj;


	for (size_t i = 0; i < m_vecIndex[4].size(); i += 3)
	{
		cVector3 v1 = m_vecVertex[4][m_vecIndex[4][i]];
		cVector3 v2 = m_vecVertex[4][m_vecIndex[4][i + 1]];
		cVector3 v3 = m_vecVertex[4][m_vecIndex[4][i + 2]];

		// �� ���� �������� �����̽��� �̵�
		v1 = cVector3::TransformCoord(v1, matWVP3);
		v2 = cVector3::TransformCoord(v2, matWVP3);
		v3 = cVector3::TransformCoord(v3, matWVP3);

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