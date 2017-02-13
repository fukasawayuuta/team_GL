/*******************************************************************************
* �^�C�g�����F
* �t�@�C�����Fgame.cpp
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

/*******************************************************************************
* �ÓI�ϐ��錾
*******************************************************************************/
static int SEND_TIMING_COUNT = 2;

/*******************************************************************************
* �֐����FCGame::CGame()
*
* ����	�F
* �߂�l�F
* ����	�F�R���X�g���N�^
*******************************************************************************/
CGame::CGame()
{
	m_pCamera = NULL;
	m_SendCnt = 0;
	m_pPlayer = NULL;
}

/*******************************************************************************
* �֐����FCGame::~CGame()
*
* ����	�F
* �߂�l�F
* ����	�F�f�X�g���N�^
*******************************************************************************/
CGame::~CGame()
{
}

/*******************************************************************************
* �֐����Fvoid CGame::Init( void )
*
* ����	�F
* �߂�l�F
* ����	�F����������
*******************************************************************************/
void CGame::Init(void)
{
	//CSync::Init();
	m_pCamera = CCamera::Create();
	CGameBackground::Create();
	CScore::Create(Vector2(300.0f, 200.0f), Vector2(0.0f, 0.0f), 50.0f, 100.0f, TEXTURE_TYPE_NUMBER);
	CEnemy::Create(Vector3(100.0f, 25.0f, 0.0f), 50.0f, 100.0f, TEXTURE_TYPE_ENEMY001);
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
			Recv,	//	�X���b�h�Ƃ��Ď��s����֐���
			NULL,
			0,
			&thID);	//	�X���b�h��ID
	//CBoss::Create(Vector3(30.0f, 0.0f, 0.0f), 50.0f, 100.0f, TEXTURE_TYPE_BOSS);
	CBat::Create(Vector3(200.0f, 25.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_ENEMY001);
	CSkeleton::Create(Vector3(-200.0f, 25.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_ENEMY002);
	CSoundAL::Init();
	CGame_UI::Create(Vector2(SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT * 0.15f), 295.0f, 95.0f, TEXTURE_TYPE_GAUGE_IN);
	CGame_UI::Create(Vector2(SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT * 0.15f), 300.0f, 100.0f, TEXTURE_TYPE_GAUGE_FRAME);
	/*CFieldObject::Create(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(100.0f, 100.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);*/
	CFieldObject::Load();
	m_SoundSE_ID = CSoundAL::Load("data/SOUND/Select_SE.wav");
}

/*******************************************************************************
* �֐����Fvoid CGame::Uninit( void )
*
* ����	�F
* �߂�l�F
* ����	�F�I������
*******************************************************************************/
void CGame::Uninit(void)
{
	//	�X���b�h�̏�Ԏ擾�B
	GetExitCodeThread(hth, &m_ExitCode);
	//	�X���b�h�������Ă�����I���B
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
* �֐����Fvoid CGame::Update( void )
*
* ����	�F
* �߂�l�F
* ����	�F�X�V����
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
* �֐����Fvoid CGame::Draw( void )
*
* ����	�F
* �߂�l�F
* ����	�F�`�揈��
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