/*******************************************************************************
* タイトル名：
* ファイル名：game.cpp
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
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "scene.h"
#include "scene2D.h"
#include "scene3D.h"
#include "score.h"
#include "camera.h"
#include "input.h"
#include "texture.h"
#include "gamebackground.h"
#include "game_UI.h"
#include "soundal.h"
#include "sync.h"
#include "animationBoard.h"
#include "player.h"
#include "enemy.h"
#include "boss.h"
#include "fieldObject.h"
#include "bat.h"

/*******************************************************************************
* 関数名：CGame::CGame()
*
* 引数	：
* 戻り値：
* 説明	：コンストラクタ
*******************************************************************************/
CGame::CGame()
{
	m_pCamera = NULL;
}

/*******************************************************************************
* 関数名：CGame::~CGame()
*
* 引数	：
* 戻り値：
* 説明	：デストラクタ
*******************************************************************************/
CGame::~CGame()
{
}

/*******************************************************************************
* 関数名：void CGame::Init( void )
*
* 引数	：
* 戻り値：
* 説明	：初期化処理
*******************************************************************************/
void CGame::Init(void)
{
	m_pCamera = CCamera::Create();
	CGameBackground::Create();
	CScore::Create(Vector2(300.0f, 200.0f), Vector2(0.0f, 0.0f), 50.0f, 100.0f, TEXTURE_TYPE_NUMBER);
	CEnemy::Create(Vector3(100.0f, 25.0f, 0.0f), 50.0f, 100.0f, TEXTURE_TYPE_ENEMY001);
	CPlayer::Create(Vector3(-100.0f, 0.0f, 0.0f), 50.0f, 100.0f);
	//CBoss::Create(Vector3(30.0f, 0.0f, 0.0f), 50.0f, 100.0f, TEXTURE_TYPE_BOSS);
	//CBat::Create(Vector3(100.0f, 25.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_ENEMY001);
	CSoundAL::Init();
	CGame_UI::Create(Vector2(SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT * 0.15f), 295.0f, 95.0f, TEXTURE_TYPE_GAUGE_IN);
	CGame_UI::Create(Vector2(SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT * 0.15f), 300.0f, 100.0f, TEXTURE_TYPE_GAUGE_FRAME);
	//CFieldObject::Create(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 100.0f, TEXTURE_TYPE_BLOCK);
	m_SoundSE_ID = CSoundAL::Load("data/SOUND/Select_SE.wav");
	//CSync::Init();
}

/*******************************************************************************
* 関数名：void CGame::Uninit( void )
*
* 引数	：
* 戻り値：
* 説明	：終了処理
*******************************************************************************/
void CGame::Uninit(void)
{
	CScene::ReleaseAll();
	if(m_pCamera)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}
	CSoundAL::Uninit();
	CSync::Uninit();
}

/*******************************************************************************
* 関数名：void CGame::Update( void )
*
* 引数	：
* 戻り値：
* 説明	：更新処理
*******************************************************************************/
void CGame::Update(void)
{
	CSync::Recv();
	m_pCamera->Update();
	CScene::UpdateAll();
	bool bEnd = true;
	CScene *pScene = CScene::GetList( PRIORITY_3D );
	while( pScene )
	{
		if( pScene->GetObjtype( pScene ) == OBJ_TYPE_ENEMY )
		{
			bEnd = false;
		}
		pScene = pScene->GetNext( pScene );
	}

	if (bEnd)
	{
		CFade::Start(new CResult);
		CSoundAL::Play(m_SoundSE_ID, false);
	}

	CSync::Send( Vector3( 0, 0, 0 ) );
}

/*******************************************************************************
* 関数名：void CGame::Draw( void )
*
* 引数	：
* 戻り値：
* 説明	：描画処理
*******************************************************************************/
void CGame::Draw(void)
{
	m_pCamera->Set();
	CScene::DrawAll();
}