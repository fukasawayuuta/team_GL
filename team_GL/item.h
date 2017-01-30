/******************************************************************************
	�^�C�g�����FItem
	�t�@�C�����Fitem.h
	�쐬��    �FAT-13B-284 11 ���쎛�C�F
	�쐬��    �F2016/12/05
******************************************************************************/
/******************************************************************************
	�C���N���[�h�K�[�h
******************************************************************************/
#pragma once

/******************************************************************************
	�N���X�錾
******************************************************************************/
class CItem : public CAnimationBoard
{
public:
	CItem(int Priority = PRIORITY_3D, OBJ_TYPE objType = OBJ_TYPE_2D);		//	�R���X�g���N�^�B
	~CItem(void);		//	�f�X�g���N�^�B

	void Init(Vector3 pos, float width, float height, int texIndex);		//	�������֐��B
	void Uninit(void);		//	�I���֐��B
	void Update(void);		//	�X�V�֐��B
	void Draw(void);		//	�`��֐��B

	static void Create(Vector3 pos, float width, float height, int texIndex);		//	�����֐��B
	Vector3 GetPosition( void ){ return m_Pos ; };
	void HitCheck( Vector3 pos, float width, float height );

private:
	bool bOpen;		// �󔠂��󂢂���Ԃǂ���
};