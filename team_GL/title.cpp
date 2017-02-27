/*******************************************************************************
* �^�C�g�����F
* �t�@�C�����Ftitle.cpp
* �쐬��	�FAT13B284 10 ���}���[��
* �쐬��	�F2016/11/14
********************************************************************************
* �X�V����	�F
*
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "main.h"
#include "mode.h"
#include "camera.h"
#include "title.h"
#include "titlebackground.h"
#include "river.h"
#include "titlelogo.h"
#include "titlemenu.h"
#include "tutorial.h"
#include "credit.h"
#include "matching.h"
#include "result.h"
#include "fade.h"
#include "scene.h"
#include "scene2D.h"
#include "scene3D.h"

#include "camera.h"

#include "titlePlayer.h"

#include "input.h"
#include "texture.h"

/*******************************************************************************
* �֐����FCTitle::CTitle()
*
* ����	�F
* �߂�l�F
* ����	�F�R���X�g���N�^
*******************************************************************************/
CTitle::CTitle()
{
}

/*******************************************************************************
* �֐����FCTitle::~CTitle()
*
* ����	�F
* �߂�l�F
* ����	�F�f�X�g���N�^
*******************************************************************************/
CTitle::~CTitle()
{
}

/*******************************************************************************
* �֐����Fvoid CTitle::Init( void )
*
* ����	�F
* �߂�l�F
* ����	�F����������
*******************************************************************************/
void CTitle::Init(void)
{
	m_pCamera = CCamera::Create();
	CTitleBackground::Create();
	CTutorial::Create( Vector2( 0.0f, 0.0f ), Vector2( 0.0f, 0.0f ), 0.0f, 0.0f, TEXTURE_TYPE_RESULT_BG );
	CCredit::Create( Vector2( 0.0f, 0.0f ), Vector2( 0.0f, 0.0f ), 0.0f, 0.0f, TEXTURE_TYPE_CREDIT );
	CTitleLogo::Create( Vector2( SCREEN_WIDTH * 0.5f, 150.0f ), Vector2( 0.0f, 0.0f ), 400.0f, 100.0f, TEXTURE_TYPE_TITLE_LOGO );
	CTitleMenu::Create( Vector2( SCREEN_WIDTH * 0.5f, 450.0f ), Vector2( 0.0f, 0.0f ), 250.0f, 40.0f );
	m_pPlayer = CTitlePlayer::Create(Vector3(0.0f, 0.0f, 45.0f), 50.0f, 100.0f);
	CRiver::Create();
}

/*******************************************************************************
* �֐����Fvoid CTitle::Uninit( void )
*
* ����	�F
* �߂�l�F
* ����	�F�I������
*******************************************************************************/
void CTitle::Uninit(void)
{
	CScene::ReleaseAll();
	if(m_pCamera)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}
}

/*******************************************************************************
* �֐����Fvoid CTitle::Update( void )
*
* ����	�F
* �߂�l�F
* ����	�F�X�V����
*******************************************************************************/
void CTitle::Update(void)
{
	m_pCamera->Update();
	CScene::UpdateAll();
}

/*******************************************************************************
* �֐����Fvoid CTitle::Draw( void )
*
* ����	�F
* �߂�l�F
* ����	�F�`�揈��
*******************************************************************************/
void CTitle::Draw(void)
{
	m_pCamera->Set();
	CScene::DrawAll();
}