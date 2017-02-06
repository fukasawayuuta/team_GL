/******************************************************************************
	�^�C�g�����FScene3D
	�t�@�C�����Fscene3D.h
	�쐬��    �FAT-13B-284 35 �[�V�C��
	�쐬��    �F2016/11/21
******************************************************************************/
/******************************************************************************
	�C���N���[�h�K�[�h
******************************************************************************/
#pragma once

/******************************************************************************
	�N���X�錾
******************************************************************************/
class CScene3D : public CScene
{
public:
	CScene3D(int Priority = PRIORITY_3D, OBJ_TYPE objType = OBJ_TYPE_NONE);		//	�R���X�g���N�^�B
	~CScene3D();	//	�f�X�g���N�^�B

	void Init(void);		//	�������֐��B
	void Uninit(void);		//	�I���֐��B
	void Update(void);		//	�X�V�֐��B
	void Draw(void);		//	�`��֐�

	static CScene3D *Create(void);	//	�쐬�֐��B

	Vector3 GetPos(void) { return m_Pos; }
	Vector2 GetCollision(void) { return m_Collision; }
protected:
	Vector3 m_Pos;		//	���W�B
	Vector3 m_Rot;		//	�p�x�B
	Vector3 m_Scl;		//	�g�k���B
	float m_Width;		//	�����B
	float m_Height;		//	�c���B
	float m_Depth;		//	���s�B
	int m_nTexIdx;		//	�e�N�X�`���^�C�v�B

	Vector2 m_Collision;	// �����蔻��
};

