/*******************************************************************************
* タイトル名：
* ファイル名：title.cpp
* 作成者	：AT13B284 10 小笠原啓太
* 作成日	：2016/11/14
********************************************************************************
* 更新履歴	：
*
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
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
* 関数名：CTitle::CTitle()
*
* 引数	：
* 戻り値：
* 説明	：コンストラクタ
*******************************************************************************/
CTitle::CTitle()
{
}

/*******************************************************************************
* 関数名：CTitle::~CTitle()
*
* 引数	：
* 戻り値：
* 説明	：デストラクタ
*******************************************************************************/
CTitle::~CTitle()
{
}

/*******************************************************************************
* 関数名：void CTitle::Init( void )
*
* 引数	：
* 戻り値：
* 説明	：初期化処理
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
* 関数名：void CTitle::Uninit( void )
*
* 引数	：
* 戻り値：
* 説明	：終了処理
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
* 関数名：void CTitle::Update( void )
*
* 引数	：
* 戻り値：
* 説明	：更新処理
*******************************************************************************/
void CTitle::Update(void)
{
	m_pCamera->Update();
	CScene::UpdateAll();
}

/*******************************************************************************
* 関数名：void CTitle::Draw( void )
*
* 引数	：
* 戻り値：
* 説明	：描画処理
*******************************************************************************/
void CTitle::Draw(void)
{
	m_pCamera->Set();
	CScene::DrawAll();
}