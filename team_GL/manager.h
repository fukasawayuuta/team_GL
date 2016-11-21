/******************************************************************************
	�^�C�g�����FManager
	�t�@�C�����Fmanager.h
	�쐬��    �FAT-13B-284 35 �[�V�C��
	�쐬��    �F2016/11/14
******************************************************************************/
/******************************************************************************
	�C���N���[�h�K�[�h
******************************************************************************/
#pragma once

/******************************************************************************
	�C���N���[�h�錾
******************************************************************************/

/******************************************************************************
	�N���X�錾
******************************************************************************/
class CRenderer;
class CMode;
class CManager
{
public:
	CManager(void);
	~CManager(void);

	static HRESULT Init(HINSTANCE hInstance , HWND hWnd , BOOL bWindow);		//	����������
	static void Uninit(void);													//	�I������
	static void Update(void);													//	�X�V����
	static void Draw(void);														//	�`�揈��

	static CRenderer  *GetRenderer(void) { return m_pRenderer; }
	static void SetMode(CMode *mode);
	static CMode *GetMode(void) {return m_pMode;}
private:
	static CRenderer *m_pRenderer;		//	�����_���[�N���X�B
	static CMode *m_pMode;
};

