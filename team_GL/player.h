/******************************************************************************
	�^�C�g�����Fplayer
	�t�@�C�����Fplayer.h
	�쐬��    �FAT-13B-284 10 ���}���[��
	�쐬��    �F2016/12/05
******************************************************************************/
/******************************************************************************
	�C���N���[�h�K�[�h
******************************************************************************/
#pragma once

/******************************************************************************
	�N���X�錾
******************************************************************************/
class CPlayer : public CAnimationBoard
{
public:
	CPlayer(int Priority = PRIORITY_3D, OBJ_TYPE objType = OBJ_TYPE_PLAYER);		//	�R���X�g���N�^�B
	~CPlayer();	//	�f�X�g���N�^�B

	void Init(Vector3 pos, float width, float height);		//	�������֐��B
	void Uninit(void);		//	�I���֐��B
	void Update(void);		//	�X�V�֐��B
	void Draw(void);		//	�`��֐�
	void SetID(int id) {m_PlayerID = id;}		//	ID�ݒ�B
	int GetID(void) {return m_PlayerID;}		//	ID�擾�B

	void HitCheck( Vector3 pos, float width, float height );
	Vector3 GetMove(void) { return m_Move; }

	static CPlayer *Create(Vector3 pos, float width, float height);	//	�쐬�֐��B
private:
	// �v���C���[�̏��
	typedef enum
	{
		STATE_WALK,
		STATE_ATTACK,
		STATE_DAMAGE,
		STATE_MAX
	}STATE;

	int m_Hp;
	int m_PlayerID;
	bool m_Jump;

	STATE m_State;
	Vector3 m_Move;			// �ړ���
};
