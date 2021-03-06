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
#include "otherPlayer.h"
#include "otherPlayerManager.h"
#include "skeleton.h"
#include "manager.h"
#include "slime.h"
#include "playerLifeGauge.h"
#include "squid.h"

/*******************************************************************************
* 静的変数宣言
*******************************************************************************/
static int SEND_TIMING_COUNT = 2;

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
	m_SendCnt = 0;
	m_pPlayer = NULL;
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
	//CSync::Init();
	m_pCamera = CCamera::Create();
	CGameBackground::Create();
	//CEnemy::Create(Vector3(100.0f, 25.0f, 0.0f), 50.0f, 100.0f, TEXTURE_TYPE_ENEMY001);
	m_pPlayer = CPlayer::Create(Vector3(-100.0f, 0.0f, 0.0f), 50.0f, 100.0f);
	m_pPlayer->SetID(CSync::Init());
	for( int i = 0; i < 3; i ++ )
	{
		if( i != m_pPlayer->GetID() )
		{
			m_pOtherPlayer[ i ] = COtherPlayer::Create( i, Vector3( -150.0f, 0.0f, 0.0f ), 50.0f, 100.0f );
		}
		else
		{
			m_pOtherPlayer[ i ] = COtherPlayer::Create( 3, Vector3( -150.0f, 0.0f, 0.0f ), 50.0f, 100.0f );
		}
	}
	hth =  (HANDLE)_beginthreadex(NULL,
			0,
			Recv,	//	スレッドとして実行する関数名
			NULL,
			0,
			&thID);	//	スレッドのID
	//CBoss::Create(Vector3(30.0f, 0.0f, 0.0f), 50.0f, 100.0f, TEXTURE_TYPE_BOSS);
	CSlime::Create(Vector3(		 150.0f, 190.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_ENEMY003,  0);
	CSlime::Create(Vector3(		 400.0f,  20.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_ENEMY003,  1);
	CBat::Create(Vector3(		 650.0f, 250.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_ENEMY001,  2);
	CSquid::Create(Vector3(		 750.0f, 125.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_ENEMY004,  3);
	CSkeleton::Create(Vector3(	1100.0f,  30.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_ENEMY002,  4);
	CSlime::Create(Vector3(		1175.0f,  65.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_ENEMY003,  5);
	CSlime::Create(Vector3(		1550.0f,  20.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_ENEMY003,  6);
	CBat::Create(Vector3(		2300.0f, 200.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_ENEMY001,  7);
	CSkeleton::Create(Vector3(	2200.0f,  30.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_ENEMY002,  8);
	CSquid::Create(Vector3(		2500.0f,  75.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_ENEMY004,  9);
	CSquid::Create(Vector3(		2600.0f, 175.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_ENEMY004, 10);
	CSquid::Create(Vector3(		2700.0f, 275.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_ENEMY004, 11);
	CSquid::Create(Vector3(		2800.0f, 175.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_ENEMY004, 12);
	CSquid::Create(Vector3(		2900.0f,  75.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_ENEMY004, 13);
	CSlime::Create(Vector3(		3200.0f, 115.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_ENEMY003, 14);
	CBat::Create(Vector3(		3500.0f, 200.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_ENEMY001, 15);
	CSkeleton::Create(Vector3(	3750.0f,  30.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_ENEMY002, 16);
	CBat::Create(Vector3(		4000.0f, 150.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_ENEMY001, 17);
	CSlime::Create(Vector3(		4100.0f,  20.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_ENEMY003, 18);
	CBat::Create(Vector3(		4300.0f, 225.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_ENEMY001, 19);

	CSync::SetEnemyID();

	CSoundAL::Init();

	for( int i = 0; i < 4; i ++ )
	{
		if( m_pPlayer->GetID() == i )
		{
			m_pScore[ i ] = CScore::Create(Vector2(SCREEN_WIDTH * 0.80f, SCREEN_HEIGHT * 0.1f + 45.0f * i), Vector2(0.0f, 0.0f), 40.0f, 45.0f, TEXTURE_TYPE_NUMBER, i );
			m_pPlayer->SetMyscore( m_pScore[ i ] );
		}
		else
		{
			m_pScore[ i ] = CScore::Create(Vector2(SCREEN_WIDTH * 0.80f, SCREEN_HEIGHT * 0.1f + 45.0f * i), Vector2(0.0f, 0.0f), 40.0f, 45.0f, TEXTURE_TYPE_NUMBER, i );
		}
		CGame_UI::Create( Vector2( SCREEN_WIDTH * 0.75, SCREEN_HEIGHT * 0.1f + 45.0f * i ), 40.0f, 45.0f, TEXTURE_TYPE_UI_1P + i );
	}
	CPlayerLifeGauge::Create(Vector2(SCREEN_WIDTH * 0.30f, SCREEN_HEIGHT * 0.1f), SCREEN_WIDTH * 0.5f, 40.0f, TEXTURE_TYPE_GAUGE_IN);
	CGame_UI::Create(Vector2(SCREEN_WIDTH * 0.30f, SCREEN_HEIGHT * 0.1f), SCREEN_WIDTH * 0.5f, 40.0f, TEXTURE_TYPE_GAUGE_FRAME);
	CGame_UI::Create(Vector2(SCREEN_WIDTH * 0.03f, SCREEN_HEIGHT * 0.1f), 37.0f, 37.0f, TEXTURE_TYPE_UI_HP);
	CFieldObject::Load();
	m_SoundSE_ID = CSoundAL::Load("data/SOUND/Select_SE.wav");
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
	for( int i = 0 ; i < 4; i ++ )
	{
		CManager::SetScore( i, m_pScore[ i ]->GetScore() );
	}

	//	スレッドの状態取得。
	GetExitCodeThread(hth, &m_ExitCode);
	//	スレッドがうごていたら終了。
	if (m_ExitCode == STILL_ACTIVE) {
		TerminateThread(hth, m_ExitCode);
	}

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

	if( CInput::GetKeyboardTrigger( DIK_RETURN ) ) {
		bEnd = true;
	}

	if (bEnd)
	{
		CFade::Start(new CResult);
		CSoundAL::Play(m_SoundSE_ID, false);
	}
	//if (m_SendCnt == 0)	CSync::Send( Vector3( 0, 0, 0 ), 0 );

	//m_pOtherManager->Update();
	m_SendCnt = (m_SendCnt + 1) % SEND_TIMING_COUNT;
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

unsigned int CGame::Recv(void*)
{
	while (1) {
		CSync::Recv();
	}
}