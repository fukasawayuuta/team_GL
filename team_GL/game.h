/*******************************************************************************
* �^�C�g�����F
* �t�@�C�����Fmode.h
* �쐬��	�FAT13B284 10 ���}���[��
* �쐬��	�F2016/11/14
********************************************************************************
* �X�V����	�F
*
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�K�[�h
*******************************************************************************/
#pragma once

/*******************************************************************************
* �N���X�錾
*******************************************************************************/
// �Q�[���N���X
class CCamera;
class CPlayer;
class COtherPlayer;
class COtherPlayerManager;
class CScore;
class CGame : public CMode
{
public:
	CGame();
	~CGame();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	CCamera* GetCamera(void) { return m_pCamera; }		// �J�����擾�֐�
	CPlayer* GetPlayer(void) { return m_pPlayer; }		// �v���C���[�擾�֐�
private:
	CCamera *m_pCamera;
	CPlayer *m_pPlayer;
	COtherPlayer *m_pOtherPlayer[ 3 ];
	int m_SoundSE_ID;
	COtherPlayerManager *m_pOtherManager;
	CScore *m_pScore[ 4 ];

	DWORD m_ExitCode;					//	�X���b�h�̏I������B
	static unsigned int __stdcall Recv( void* );
	unsigned int thID;
	HANDLE hth;

	int m_SendCnt;		//	���𑗂�^�C�~���O�J�E���^�B
};

