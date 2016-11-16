/*******************************************************************************
* �^�C�g�����F
* �t�@�C�����FVector3.h
* �쐬��	�FAT13B284 10 ���}���[��
* �쐬��	�F
********************************************************************************
* �X�V����	�F
*
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�K�[�h
*******************************************************************************/
#ifndef _VECTOR_H_
#define _VECTOR_H_

/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "main.h"

/*******************************************************************************
* �}�N����`
*******************************************************************************/

//*************************************
// �x�N�g���N���X
//*************************************
class Vector3
{
public:
	float x, y, z;	//	OpenGL�̎��͂���̃R�����g���O���� �upublic D3DXVECTOR3�v�������B

	Vector3() {}
	Vector3(float x, float y, float z);

	Vector3 operator += (const Vector3 Vec3);
	Vector3 operator -= (const Vector3 Vec3);

	Vector3 operator + (const Vector3 Vec3);
	Vector3 operator - (const Vector3 Vec3);

	Vector3 operator *= (float f);
	Vector3 operator /= (float f);

	Vector3 operator * (float f);
	Vector3 operator / (float f);

	Vector3 Normalize(void);

	operator float* ();
	operator const float* () const;

	float Length(void);
};

class Vector2
{
public:
	float x, y;

	Vector2() {}
	Vector2(float x, float y);

	Vector2 operator += (const Vector2 Vec2);
	Vector2 operator -= (const Vector2 Vec2);

	Vector2 operator + (const Vector2 Vec2);
	Vector2 operator - (const Vector2 Vec2);

	Vector2 operator *= (float f);
	Vector2 operator /= (float f);

	Vector2 operator * (float f);
	Vector2 operator / (float f);

	Vector2 Normalize(void);

	operator float* ();
	operator const float* () const;

	float Length(void);
};

#endif
