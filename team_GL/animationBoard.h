/******************************************************************************
	�^�C�g�����FanimationBoard
	�t�@�C�����FanimationBoard.h
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
class CAnimationBoard : public CScene3D
{
public:
	CAnimationBoard(int Priority = PRIORITY_3D, OBJ_TYPE objType = OBJ_TYPE_NONE);		//	�R���X�g���N�^�B
	~CAnimationBoard();	//	�f�X�g���N�^�B

	void Init(Vector3 pos, float width, float height);		//	�������֐��B
	void Uninit(void);		//	�I���֐��B
	void Update(void);		//	�X�V�֐��B
	void Draw(void);		//	�`��֐�

	static CAnimationBoard *Create(Vector3 pos, float width, float height);	//	�쐬�֐��B
protected:
	CTexture *m_pTexture;	// �e�N�X�`���|�C���^

	int m_nCntAnim;			// �A�j���[�V�����J�E���^
	int m_nPatternAnim;		// �p�^�[���J�E���^
};