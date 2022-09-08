#pragma once

class cMatrix; // << : �߰� 

class cVector3
{
public:
	cVector3();
	~cVector3();

	float x, y, z; 

	/// : ������ �������̵�
	bool operator==(cVector3& vec);
	bool operator!=(cVector3& vec);
	cVector3 operator+(cVector3& vec);
	cVector3 operator-(cVector3& vec);
	cVector3 operator*(float f);
	cVector3 operator/(float f);

	/// : ���� , ����  
	static float Dot(cVector3& v1, cVector3& v2);
	static cVector3 Cross(cVector3& v1, cVector3& v2);
	float Length();
	cVector3 Normalize();
	cVector3 Normalize2();
	/// : ������ ������ ������ Dot �� Cross�� ��ü ���� �����ϳ�
	/// : ���ͳ����� ������� ������ ����.



	// >> : �߰� 
	cVector3(float _x, float _y, float _z); // : ������ �߰� 
	// class cMatrix; // << : ���� �߰� 
	static cVector3 TransformCoord(cVector3& v, cMatrix& mat);
	static cVector3 TransformNormal(cVector3& v, cMatrix& mat);
	// << :

};

