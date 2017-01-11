/******************************************************************************
	�^�C�g�����FEnemy
	�t�@�C�����Fenemy.h
	�쐬��    �FAT-13B-284 35 �[�V�C��
	�쐬��    �F2016/12/05
******************************************************************************/
/******************************************************************************
	�C���N���[�h�K�[�h
******************************************************************************/
#pragma once

/******************************************************************************
	�N���X�錾
******************************************************************************/
class CEnemy : public CAnimationBoard
{
public:
	CEnemy(int Priority = PRIORITY_3D, OBJ_TYPE objType = OBJ_TYPE_ENEMY);		//	�R���X�g���N�^�B
	~CEnemy(void);		//	�f�X�g���N�^�B

	void Init(Vector3 pos, float width, float height, int texIndex);		//	�������֐��B
	void Uninit(void);		//	�I���֐��B
	void Update(void);		//	�X�V�֐��B
	void Draw(void);		//	�`��֐��B

	static void Create(Vector3 pos, float width, float height, int texIndex);		//	�����֐��B
	Vector3 GetPosition( void ){ return m_Pos ; };
	float GetWidth( void ){ return m_Width ; };
	float GetHeight( void ){ return m_Height ; };
	void HitCheck( Vector3 pos, float width, float height );
};

