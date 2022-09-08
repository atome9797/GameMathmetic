#include "stdafx.h"
#include "cMatrix.h"


cMatrix::cMatrix()
{
}


cMatrix::~cMatrix()
{
}

// >> : 이하 구현 

// >> : cMatrix::cRow 
cMatrix::cRow::cRow()
{

}

cMatrix::cRow::cRow(int nDimension)
{
	Resize(nDimension);
}

void cMatrix::cRow::Resize(int nDimension)
{
	m_vecData.resize(nDimension);
}

float& cMatrix::cRow::operator[](int nIndex)
{
	return m_vecData[nIndex];
}
// << : cMatrix :: cRow 


// >> :cMatrix 
cMatrix::cMatrix(int nDimension)
{
	Resize(nDimension);
}

void cMatrix::Print()
{
	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			printf("%8.2f", (*this)[i][j]);
		}
		printf("\n");
	}
}

void cMatrix::Resize(int nDimension)
{
	m_vecData.resize(nDimension);
	for (size_t i = 0; i < nDimension; ++i)
		m_vecData[i].Resize(nDimension);
}

// : 차수 구하기 
int cMatrix::Dimension()
{
	return (int)m_vecData.size();
}

// : 
cMatrix cMatrix::Identity(int nDimension)
{
	cMatrix matRet(nDimension);

	for (int i = 0; i < nDimension; ++i)
	{
		for (int j = 0; j < nDimension; ++j)
		{
			matRet[i][j] = (i == j) ? 1 : 0;
		}
	}
	return matRet;
}

// : 
cMatrix::cRow& cMatrix::operator[](int nIndex)
{
	return m_vecData[nIndex];
}

// : 
bool cMatrix::operator==(cMatrix& mat)
{
	float fEpsilon = 0.0001f;
	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			if ((*this)[i][j] - fEpsilon > mat[i][j])
				return false;
			if ((*this)[i][j] + fEpsilon < mat[i][j])
				return false;
		}
	}
	return true;
}

// : 
bool cMatrix::operator!=(cMatrix& mat)
{
	return !((*this) == mat);
}

// : 
cMatrix cMatrix::operator+(cMatrix& mat)
{
	cMatrix matRet(Dimension());

	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = (*this)[i][j] + mat[i][j];
		}
	}
	return matRet;
}
// : 

// : 
cMatrix cMatrix::operator-(cMatrix& mat)
{
	cMatrix matRet(Dimension());

	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = (*this)[i][j] - mat[i][j];
		}
	}
	return matRet;
}

cMatrix cMatrix::operator*(cMatrix& mat)
{
	cMatrix matRet(Dimension());

	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = 0.f;
			for (int k = 0; k < Dimension(); ++k)
			{
				matRet[i][j] += ((*this)[i][k] * mat[k][j]);
			}
		}
	}
	return matRet;
}

cMatrix cMatrix::operator*(float f)
{
	cMatrix matRet(Dimension());

	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = (*this)[i][j] * f;
		}
	}
	return matRet;
}

// : 전치 행렬 
cMatrix cMatrix::Transpose()
{
	cMatrix matRet(Dimension());

	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = (*this)[j][i];
		}
	}
	return matRet;
}

// : 역 행렬
cMatrix cMatrix::Inverse(OUT float& fDeterminant)
{
	// : 
	cMatrix matRet = cMatrix::Identity(Dimension());
	// >> : 
	fDeterminant = Determinant();	// : 행렬식으로 역행렬이 존재 하는지 확인
	if (-0.0001f < fDeterminant && fDeterminant < 0.0001f)
		return matRet; // : 
	// << : 

	cMatrix matAdj = Adjoint();
	matRet = matAdj * (1 / fDeterminant);
	return matRet;
}

// : 행렬식
float cMatrix::Determinant()
{
	if (Dimension() == 2)
	{
		return (*this)[0][0] * (*this)[1][1] - (*this)[1][0] * (*this)[0][1];
	}

	float fDeterminant = 0.0f;

	for (int i = 0; i < Dimension(); ++i)
	{
		fDeterminant += ((*this)[i][0] * Cofactor(i, 0));
	}

	return fDeterminant;
}

// : 수반행렬
cMatrix cMatrix::Adjoint()
{
	cMatrix matRet(Dimension());

	// >> : cofactor을 tranpose 해서 전치행렬로 수반행렬 만들기
	for (int i = 0; i < Dimension(); ++i)
	{
		for (int j = 0; j < Dimension(); ++j)
		{
			matRet[i][j] = Cofactor(j, i); 
		}
	}
	return matRet;
}

// : 여인수
float cMatrix::Cofactor(int nRow, int nCol)
{
	int nConst = 1;

	// : (-1)^(row+col) 로 + , - 가 번갈아 나오도록 해야 하는데 
	// : 이걸 %2로 변경해서 처리 
	if ((nRow + nCol) % 2 != 0)
		nConst = -1;

	return nConst * Minor(nRow, nCol);
}

// : Minor - N x N 행렬의 (N-1) x (N-1)구하기
// : 인자로 넘어온 행,열을 제외한 것.
float cMatrix::Minor(int nRow, int nCol)
{
	cMatrix matMinor(Dimension() - 1);

	int nMinorRow = 0;
	int nMinorCol = 0;

	for (int i = 0; i < Dimension(); ++i)
	{
		if (nRow == i)
			continue;

		nMinorCol = 0;

		for (int j = 0; j < Dimension(); ++j)
		{
			if (nCol == j)
				continue;
			matMinor[nMinorRow][nMinorCol] = (*this)[i][j];
			++nMinorCol;
		}
		++nMinorRow;
	}

	return matMinor.Determinant();
}
// << :


// >> : 추가 -- 09API3D
#include "cVector3.h"		// << :추가 

cMatrix cMatrix::Translation(float x, float y, float z)
{
	cMatrix matRet = cMatrix::Identity(4);
	matRet[3][0] = x;
	matRet[3][1] = y;
	matRet[3][2] = z;
	return matRet;
}

cMatrix cMatrix::Translation(cVector3& v)
{
	cMatrix matRet = cMatrix::Identity(4);
	matRet[3][0] = v.x;
	matRet[3][1] = v.y;
	matRet[3][2] = v.z;
	return matRet;
}

cMatrix cMatrix::View(cVector3& vEye, cVector3& vLookAt, cVector3& vUp)
{
	cVector3 l = (vLookAt - vEye).Normalize();
	cVector3 r = cVector3::Cross(vUp, l).Normalize();
	cVector3 u = cVector3::Cross(l, r).Normalize();

	cMatrix matRet = cMatrix::Identity(4);
	matRet[0][0] = r.x; matRet[0][1] = u.x; matRet[0][2] = l.x;		/// : [0]
	matRet[1][0] = r.y; matRet[1][1] = u.y; matRet[1][2] = l.y;
	matRet[2][0] = r.z; matRet[2][1] = u.z; matRet[2][2] = l.z;

	matRet[3][0] = -cVector3::Dot(r, vEye);
	matRet[3][1] = -cVector3::Dot(u, vEye);
	matRet[3][2] = -cVector3::Dot(l, vEye);

	return matRet;
}

cMatrix cMatrix::View2(cVector3& vEye, cVector3& vLookAt, cVector3& vUp)
{
	cVector3 l = (vLookAt - vEye).Normalize2();
	cVector3 r = cVector3::Cross(vUp, l).Normalize2();
	cVector3 u = cVector3::Cross(l, r).Normalize2();

	cMatrix matRet = cMatrix::Identity(4);
	matRet[0][0] = r.x; matRet[0][1] = u.x; matRet[0][2] = l.x;		/// : [0]
	matRet[1][0] = r.y; matRet[1][1] = u.y; matRet[1][2] = l.y;
	matRet[2][0] = r.z; matRet[2][1] = u.z; matRet[2][2] = l.z;

	matRet[3][0] = -cVector3::Dot(r, vEye);
	matRet[3][1] = -cVector3::Dot(u, vEye);
	matRet[3][2] = -cVector3::Dot(l, vEye);

	return matRet;
}

cMatrix cMatrix::Projection(float fFovY, float fAspect, float fNearZ, float fFarZ)
{
	cMatrix matRet = cMatrix::Identity(4);

	float fScaleY = 1.0f / tanf(fFovY / 2.0f);
	float fScaleX = fScaleY / fAspect;

	matRet[0][0] = fScaleX;
	matRet[1][1] = fScaleY;
	matRet[2][2] = fFarZ / (fFarZ - fNearZ);
	matRet[2][3] = 1.0f;
	matRet[3][2] = -fFarZ * fNearZ / (fFarZ - fNearZ);
	matRet[3][3] = 0.0f;

	return matRet;
}

cMatrix cMatrix::Viewport(float x, float y, float w, float h, float minz, float maxz)
{
	cMatrix matRet = cMatrix::Identity(4);
	matRet[0][0] = w / 2.0f;
	matRet[1][1] = -h / 2.0f;
	matRet[2][2] = maxz - minz;
	matRet[3][0] = x + w / 2.0f;
	matRet[3][1] = y + h / 2.0f;
	matRet[3][2] = minz;
	return matRet;
}

cMatrix cMatrix::RotationX(float fAngle)
{
	cMatrix matRet = cMatrix::Identity(4);
	matRet[1][1] = cosf(fAngle);
	matRet[1][2] = sinf(fAngle);
	matRet[2][1] = -sinf(fAngle);
	matRet[2][2] = cosf(fAngle);
	return matRet;
}

cMatrix cMatrix::RotationY(float fAngle)
{
	cMatrix matRet = cMatrix::Identity(4);
	matRet[0][0] = cosf(fAngle);
	matRet[0][2] = -sinf(fAngle);
	matRet[2][0] = sinf(fAngle);
	matRet[2][2] = cosf(fAngle);
	return matRet;
}

cMatrix cMatrix::RotationZ(float fAngle)
{
	cMatrix matRet = cMatrix::Identity(4);
	matRet[0][0] = cosf(fAngle);
	matRet[0][1] = sinf(fAngle);
	matRet[1][0] = -sinf(fAngle);
	matRet[1][1] = cosf(fAngle);
	return matRet;
}
// << : 