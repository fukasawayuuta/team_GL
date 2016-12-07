/******************************************************************************
	�^�C�g�����FManager
	�t�@�C�����Fmanager.cpp
	�쐬��    �FAT-13B-284 35 �[�V�C��
	�쐬��    �F2016/11/14
******************************************************************************/
#include "main.h"
#include "lib.h"
#include "renderer.h"
#include "mode.h"
#include "opening.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "scene.h"
#include "scene2D.h"
#include "manager.h"
#include "input.h"
#include "texture.h"

/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/
CRenderer *CManager::m_pRenderer;
CMode *CManager::m_pMode;

/******************************************************************************
	�֐��� : CManager::CManager()
	����   : �R���X�g���N�^
******************************************************************************/
CManager::CManager(void)
{
}

/******************************************************************************
	�֐��� : CManager::~CManager()
	����   : �R���X�g���N�^
******************************************************************************/
CManager::~CManager(void)
{
	
}

/******************************************************************************
	�֐��� ; HRESULT CManager::Init( HINSTANCE hInstance , HWND hWnd , BOOL bWindow )
	����   : hInstance, hWnd, bWindow
	�߂�l : S_OK, E_FAIL
	����   : �I�u�W�F�N�g�̍쐬���A��ʕ��⍂���A�o�b�N�o�b�t�@�̌`���Ɛ����w�肵�A
			 �E�B���h�E���[�h���t���X�N���[�����[�h�ŏo�������w�肵�A
			 �f�o�C�X���쐬����B

			 �|���S����`�悷�邽�߂̏��������������Ă���B
******************************************************************************/
HRESULT CManager::Init(HINSTANCE hInstance , HWND hWnd , BOOL bWindow)
{
	// �C���v�b�g�̏�����
	CInput::InitKeyboard(hInstance, hWnd);
	// �N���X�̎��̉�
	m_pRenderer = CRenderer::Create(hInstance, hWnd, bWindow);
	// �e�N�X�`���̓ǂݍ���
	CTexture::Load();
	// �t�F�[�h�̏�����
	CFade::Init();
	// �ŏ��̃��[�h�̐ݒ�
	SetMode(new COpening);
	return S_OK;
}

/******************************************************************************
	�֐��� : void CManager::Uninit(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �������
******************************************************************************/
void CManager::Uninit(void)
{
	if (m_pRenderer != NULL) {
		//	�����_���N���X�̔j��
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	if (m_pMode != NULL) {
		//	���[�h�N���X�̔j��
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = NULL;
	}
	CInput::UninitKeyboard();
	// �e�N�X�`���̉��
	CTexture::Unload();
	CFade::Uninit();
}

/******************************************************************************
	�֐��� : void CManager::Update(void)
	����   : void
	�߂�l : �Ȃ�
	����   : Manager�N���X�̍X�V����
******************************************************************************/
void CManager::Update(void)
{
	CInput::UpdateKeyboard();
	m_pRenderer->Update();
	m_pMode->Update();
	CFade::Update();
}

/******************************************************************************
	�֐��� : void CManager::Update(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �`�揈��
******************************************************************************/
void CManager::Draw(void)
{
	m_pRenderer->Begin();

	m_pMode->Draw();
	CFade::Draw();

	m_pRenderer->End();
}

/*******************************************************************************
* �֐����Fvoid CManager::SetMode( CMode *mode )
*
* ����	�F
* �߂�l�F
* ����	�F���[�h�ݒ菈��
*******************************************************************************/
void CManager::SetMode(CMode *mode)
{
	if (m_pMode != NULL)
	{// ���[�h���ݒ肳��Ă�����I��
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = NULL;
	}
	m_pMode = mode;
	m_pMode->Init();
}