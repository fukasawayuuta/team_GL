/******************************************************************************
	�^�C�g�����FCGame_UI
	�t�@�C�����Fgame_UI.h
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
class CGame_UI : public CScene2D
{
public:
	CGame_UI(int Priority = PRIORITY_2D, OBJ_TYPE objType = OBJ_TYPE_2D);		//	�R���X�g���N�^�B
	~CGame_UI(void);	//	�f�X�g���N�^�B

	virtual void Init(Vector2 pos, float width, float height, int texIndex);		//	�������֐��B
	virtual void Uninit(void);				//	�I���֐��B
	virtual void Update(void);				//	�X�V�֐��B
	virtual void Draw(void);				//	�`��֐��B

	static void Create(Vector2 pos, float width, float height, int texIndex);
};

