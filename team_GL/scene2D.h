/******************************************************************************
	�^�C�g�����FScene2D
	�t�@�C�����Fscene2D.cpp
	�쐬��    �FAT-13B-284 35 �[�V�C��
	�쐬��    �F2016/11/18
******************************************************************************/
/******************************************************************************
	�C���N���[�h�K�[�h
******************************************************************************/
#pragma once

/******************************************************************************
	�N���X�錾
******************************************************************************/
class CTexture;
class CScene2D : public CScene
{
public:
	CScene2D(int Priority = PRIORITY_4, OBJ_TYPE objType = OBJ_TYPE_NONE);		//	�R���X�g���N�^�B
	~CScene2D();	//	�f�X�g���N�^�B
	void Init(char* fileName);	//	�������֐��B
	void Uninit(void);	//	�I���֐��B
	void Update(void);	//	�X�V�֐��B
	void Draw(void);	//	�`��֐��B

	static CScene2D *Create(char* fileName);
private:
	Vector2 m_Pos;		//	���W�B
	Vector2 m_Rot;		//	�p�x�B
	float m_Width;		//	�����B
	float m_Height;		//	�c���B
	CTexture *m_Texture;
};

