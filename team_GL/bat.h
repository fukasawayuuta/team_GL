/******************************************************************************
	�^�C�g�����FBat
	�t�@�C�����Fbat.h
	�쐬��    �FAT-13B-284 35 �[�V�C��
	�쐬��    �F2016/12/14
******************************************************************************/
/******************************************************************************
	�C���N���[�h�K�[�h
******************************************************************************/
#pragma once

/******************************************************************************
	�N���X�錾
******************************************************************************/
class CBat : public CEnemy
{
public:
	CBat(int Priority = PRIORITY_3D, OBJ_TYPE objType = OBJ_TYPE_ENEMY);		//	�R���X�g���N�^�B
	~CBat();		//	�f�X�g���N�^�B

	void Init(Vector3 pos, float width, float height, int texIndex, int id);
	void Update(void);		//�X�V�֐��B
	static CBat *Create(Vector3 pos, float width, float height, int texIndex, int id);		//	�����֐��B

private:
	int m_StateCnt;		//	�X�e�[�g�J�E���^�[�B
	float m_Movement;	//	�ړ��X�s�[�h�B
	bool m_TurnFlag;	//	�U��Ԃ�t���O�B
	float m_FirstYCoordinate;		//	�ŏ���Y���W�B
	float m_SinAngle;		//	sin�g�̊p�x�B
};

