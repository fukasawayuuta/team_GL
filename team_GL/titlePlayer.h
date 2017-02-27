/******************************************************************************
	�^�C�g�����FtitlePlayer
	�t�@�C�����FtitlePlayer.h
	�쐬��    �FAT-13B-284 02 �����@��
	�쐬��    �F2017/02/13
******************************************************************************/
/******************************************************************************
	�C���N���[�h�K�[�h
******************************************************************************/
#pragma once
#include "animationBoard.h"

const int PLAYER_MAX = 4;

/******************************************************************************
	�N���X�錾
******************************************************************************/

class CTitlePlayer : public CAnimationBoard
{
public:
	CTitlePlayer(int Priority = PRIORITY_3D, OBJ_TYPE objType = OBJ_TYPE_PLAYER);		//	�R���X�g���N�^�B
	~CTitlePlayer();	//	�f�X�g���N�^�B

	void Init(Vector3 pos, float width, float height);		//	�������֐��B
	void Uninit(void);		//	�I���֐��B
	void Update(void);		//	�X�V�֐��B
	void Draw(void);		//	�`��֐�

	void SetState(int state);									// ��Ԑݒ�
	void UpdateState(void);										// ��ԍX�V
	void UpdateAnimation(void);									// �A�j���[�V�����̍X�V

	static CTitlePlayer *Create(Vector3 pos, float width, float height);	//	�쐬�֐��B
private:
	// �v���C���[�̏��
	typedef enum
	{
		STATE_WALK,
		STATE_ATTACK,
		STATE_DAMAGE,
		STATE_MAX
	}STATE;

	// �v���C���[�̍\����
	struct PLAYER
	{
		Vector3 pos;		// �v���C���[�̈ʒu
		Vector3 move;		// �v���C���[�̈ړ���
		int		state;		// �v���C���[�̏��
	};

	bool m_Jump;

	int m_nState;			// ���݂̏��
	int m_nStateCnt;		// ��ԃJ�E���^
	Vector3 m_Move;			// �ړ���

	int m_Time;			// ���Ԍv��

};
