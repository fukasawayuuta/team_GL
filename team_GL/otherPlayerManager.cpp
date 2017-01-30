#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "scene.h"
#include "scene3D.h"
#include "animationBoard.h"
#include "player.h"
#include "otherPlayer.h"
#include "otherPlayerManager.h"
#include "mode.h"
#include "title.h"
#include "game.h"
#include "sync.h"

const int PLAYER_MAX = 4;
const int OTHER_PLAYER_NUM = PLAYER_MAX - 1;

char COtherPlayerManager::m_RecvData[128];

COtherPlayerManager::COtherPlayerManager(void)
{
}


COtherPlayerManager::~COtherPlayerManager(void)
{
}

void COtherPlayerManager::Init(void)
{
	CGame *game = (CGame *)CManager::GetMode();
	CPlayer *player = game->GetPlayer();
	int PlayerID = player->GetID();
	char recvData[128];
	strcpy(recvData, CSync::GetRecvData());
	Vector3 pos;
	int id = 0;
	int score = 0;

	m_OtherPlayer = new COtherPlayer[OTHER_PLAYER_NUM];

	for (int i = 0; i < PLAYER_MAX; i++) {
		if (PlayerID != i) {
			m_OtherPlayer[i].Init( i );
			//sscanf( (const char*)recvData, "%5.3f %5.3f %5.3f %d", &pos.x, &pos.y, &pos.z, &score );
			pos = Vector3( 100, 0, 0 );
			score = 0;
			m_OtherPlayer[i].SetPos(pos);
			m_OtherPlayer[i].SetScore(score);
		}
		else  {
			
		}
	}
}

void COtherPlayerManager::Uninit(void)
{
	for (int i = 0; i < OTHER_PLAYER_NUM; i++) {
		m_OtherPlayer[i].Uninit();
	}

	delete[] m_OtherPlayer;
	m_OtherPlayer = NULL;
}

void COtherPlayerManager::Update( void )
{
	CGame *game = (CGame *)CManager::GetMode();
	CPlayer *player = game->GetPlayer();
	int PlayerID = player->GetID();
	char recvData[ 128 ];
	strcpy( recvData, CSync::GetRecvData() );
	Vector3 pos;
	int id = 0;
	int score = 0;

	for (int i = 0; i < PLAYER_MAX; i++) {
		if (PlayerID != i) {
			//sscanf( (const char*)recvData, "%5.3f %5.3f %5.3f %d", &pos.x, &pos.y, &pos.z, &score );
			pos = Vector3( 50, 0, 100 );
			score = 0;
			m_OtherPlayer[id].SetPos(pos);
			m_OtherPlayer[id].SetScore(score);
		}
		else  {
			
		}
	}
}

COtherPlayerManager *COtherPlayerManager::Create(void)
{
	COtherPlayerManager *manager = new COtherPlayerManager;
	manager->Init();

	return manager;
}