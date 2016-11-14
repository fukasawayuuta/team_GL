/******************************************************************************
	�^�C�g�����FManager
	�t�@�C�����Fmanager.cpp
	�쐬��    �FAT-13B-284 35 �[�V�C��
	�쐬��    �F2016/11/14
******************************************************************************/
#include "main.h"
#include "rerender.h"
#include "manager.h"
#include "scene.h"

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
	//	�N���X�̎��̉�
	m_pRenderer = CRerenderer::Create(hInstance, hWnd, bWindow);
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
	m_pRenderer->Uninit();
	if (m_pRenderer != NULL) {
		//	�����_���N���X�̔j��
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	CScene::ReleaseAll();
}

/******************************************************************************
	�֐��� : void CManager::Update(void)
	����   : void
	�߂�l : �Ȃ�
	����   : Manager�N���X�̍X�V����
******************************************************************************/
void CManager::Update(void)
{
	m_pRenderer->Update();
	CScene::UpdateAll();
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

	CScene::DrawAll();

	m_pRenderer->End();
}