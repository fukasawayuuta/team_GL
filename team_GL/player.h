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
class CScore;
class CPlayer : public CAnimationBoard
{
public:
	CPlayer(int Priority = PRIORITY_3D, OBJ_TYPE objType = OBJ_TYPE_PLAYER);		//	�R���X�g���N�^�B
	~CPlayer();	//	�f�X�g���N�^�B

	void Init(Vector3 pos, float width, float height);		//	�������֐��B
	void Uninit(void);		//	�I���֐��B
	void Update(void);		//	�X�V�֐��B
	void Draw(void);		//	�`��֐�
	void SetID(int id) {
		m_PlayerID = id;
		switch( m_PlayerID )
		{
		case 0:
			m_nTexIdx = CTexture::SetTexture( TEXTURE_TYPE_PLAYER000 );
			break;
		case 1:
			m_nTexIdx = CTexture::SetTexture( TEXTURE_TYPE_PLAYER001 );
			break;
		case 2:
			m_nTexIdx = CTexture::SetTexture( TEXTURE_TYPE_PLAYER002 );
			break;
		case 3:
			m_nTexIdx = CTexture::SetTexture( TEXTURE_TYPE_PLAYER003 );
			break;
		}
	}		//	ID�ݒ�B
	int GetID(void) {return m_PlayerID;}		//	ID�擾�B

	void HitCheck( Vector3 pos, float width, float height );	// �����蔻��`�F�b�N
	Vector3 GetMove(void) { return m_Move; }					// �ړ��ʎ擾
	void SetState(int state);									// ��Ԑݒ�
	void UpdateState(void);										// ��ԍX�V
	void UpdateAnimation(void);									// �A�j���[�V�����̍X�V
	void SetMyscore( CScore *pScore ){ m_pMyscore = pScore; }
	int GetLife(void) { return m_Hp; }							// ���݃��C�t�̎擾
	int GetLifeMax(void) { return m_HpMax; }					// �ő僉�C�t�̎擾

	static CPlayer *Create(Vector3 pos, float width, float height);	//	�쐬�֐��B
private:
	// �v���C���[�̏��
	typedef enum
	{
		STATE_WALK,
		STATE_ATTACK,
		STATE_DAMAGE,
		STATE_DEATH,
		STATE_MAX
	}STATE;

	typedef enum
	{
		ANIM_ROW_WALK = 0,
		ANIM_ROW_ATTACK = 1,
		ANIM_ROW_DAMAGE = 2,
		ANIM_ROW_DEATH = 2,
		ANIM_ROW_MAX,
	}ANIM_ROW;

	int m_Hp;
	int m_HpMax;
	int m_PlayerID;
	int m_Score;
	bool m_Jump;

	int m_nState;			// ���݂̏��
	int m_nStateCnt;		// ��ԃJ�E���^
	Vector3 m_Move;			// �ړ���
	Vector3 m_OldPos;		// 1�t���[���O�̍��W
	CScore *m_pMyscore;		// �X�R�A�|�C���^
	float m_fAlfaSpeed;		// �A���t�@�l�̉������x

	void UpdateCollision(void);	// �����蔻��X�V
};
