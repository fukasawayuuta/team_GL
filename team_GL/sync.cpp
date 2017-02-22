/*******************************************************************************
* �^�C�g�����Fsync
* �t�@�C�����Fsync.cpp
* �쐬��	�FAT13B284 31 ���R�a�n
* �쐬��	�F2016/12/05
********************************************************************************
* �X�V����	�F
*
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "scene.h"
#include "scene3D.h"
#include "animationBoard.h"
#include "player.h"
#include "otherPlayer.h"
#include "sync.h"
#include "otherPlayerManager.h"
#include "enemy.h"

WSADATA CSync::m_Wsadata;
SOCKET CSync::m_Socket;
char CSync::m_RecvData[ 128 ];
char CSync::m_SendData[ 128 ];
SOCKADDR_IN CSync::m_addr;
Vector3 CSync::playerPos[ 4 ];
int CSync::playerScore[ 4 ];
int CSync::enemyId[ 20 ];
bool CSync::enemyUse[ 20 ];

/*******************************************************************************
* �֐����FCSync
*
* ����	�F�Ȃ�
* �߂�l�F�Ȃ�
* ����	�F�R���X�g���N�^
*******************************************************************************/
CSync::CSync()
{
}

/*******************************************************************************
* �֐����F~CSync
*
* ����	�F�Ȃ�
* �߂�l�F�Ȃ�
* ����	�F�f�X�g���N�^
*******************************************************************************/
CSync::~CSync()
{
}

/*******************************************************************************
* �֐����FInit
*
* ����	�F�Ȃ�
* �߂�l�Fint nNumber
* ����	�F����������
*******************************************************************************/
int CSync::Init( void )
{
	FILE *fp = fopen( "./data/CONFIG/ipdata.txt", "r" );
	char ipaddress[ 16 ];
	int nNumber, port;
	fscanf( fp, "%s", &ipaddress );
	fscanf( fp, "%d", &port );
	WSAStartup( MAKEWORD( 2, 0 ), &m_Wsadata );
	m_Socket = socket( AF_INET, SOCK_STREAM, 0 );
	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htons( port );
	m_addr.sin_addr.s_addr = inet_addr( ipaddress );
	connect( m_Socket, ( SOCKADDR* )&m_addr, sizeof( m_addr ) );
	memset( m_RecvData, 0, sizeof( m_RecvData ) );
	recv( m_Socket, m_RecvData, sizeof( m_RecvData ), 0 );
	sscanf( m_RecvData, "%d", &nNumber );
	fclose( fp );
	return nNumber ;
}

/*******************************************************************************
* �֐����FUninit
*
* ����	�F�Ȃ�
* �߂�l�F�Ȃ�
* ����	�F�I������
*******************************************************************************/
void CSync::Uninit( void )
{
	closesocket( m_Socket );
	WSACleanup();
}

/*******************************************************************************
* �֐����FSend
*
* ����	�FVector3 pos
* �߂�l�F�Ȃ�
* ����	�F���M
*******************************************************************************/
void CSync::Send( Vector3 pos, int score )
{
	//memset( m_SendData, 0, sizeof( m_SendData ) );
	CScene *pScene = CScene::GetList( PRIORITY_3D );
	while( pScene )
	{
		if( pScene->GetObjtype( pScene ) == OBJ_TYPE_ENEMY )
		{
			CEnemy *pEnemy = ( CEnemy* )pScene;
			if( pEnemy )
			{
			}
		}
		pScene = pScene->GetNext( pScene );
	}

	sprintf( m_SendData, "%5.3f %5.3f %5.3f %d;%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d;",
		pos.x, pos.y, pos.z, score,
		enemyId[ 0 ], enemyUse[ 0 ], enemyId[ 1 ], enemyUse[ 1 ], enemyId[ 2 ], enemyUse[ 2 ], enemyId[ 3 ], enemyUse[ 3 ], enemyId[ 4 ],  enemyUse[ 4 ],
		enemyId[ 5 ], enemyUse[ 5 ],enemyId[ 6 ], enemyUse[ 6 ], enemyId[ 7 ], enemyUse[ 7 ], enemyId[ 8 ], enemyUse[ 8 ], enemyId[ 9 ], enemyUse[ 9 ],
		enemyId[ 10 ], enemyUse[ 10 ],enemyId[ 11 ], enemyUse[ 11 ], enemyId[ 12 ], enemyUse[ 12 ], enemyId[ 13 ], enemyUse[ 13 ], enemyId[ 14 ], enemyUse[ 14 ], 
		enemyId[ 15 ], enemyUse[ 15 ],enemyId[ 16 ], enemyUse[ 16 ], enemyId[ 17 ], enemyUse[ 17 ], enemyId[ 18 ], enemyUse[ 18 ], enemyId[ 19 ], enemyUse[ 19 ]);
	send( m_Socket, m_SendData, sizeof( m_SendData ), 0 );
}

/*******************************************************************************
* �֐����FRecv
*
* ����	�F�Ȃ�
* �߂�l�F�Ȃ�
* ����	�F��M
*******************************************************************************/
Vector3 CSync::Recv( void )
{
	//memset( m_RecvData, 0, sizeof( m_RecvData ) );
	recv( m_Socket, m_RecvData, sizeof( m_RecvData ), 0 );
	sscanf( m_RecvData, "%f %f %f %d, %f %f %f %d, %f %f %f %d, %f %f %f %d;%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d,%d %d;",
		&playerPos[ 0 ].x, &playerPos[ 0 ].y, &playerPos[ 0 ].z, &playerScore[ 0 ], &playerPos[ 1 ].x, &playerPos[ 1 ].y, &playerPos[ 1 ].z, &playerScore[ 1 ],
		&playerPos[ 2 ].x, &playerPos[ 2 ].y, &playerPos[ 2 ].z, &playerScore[ 2 ], &playerPos[ 3 ].x, &playerPos[ 3 ].y, &playerPos[ 3 ].z, &playerScore[ 3 ],
		&enemyId[ 0 ], &enemyUse[ 0 ], &enemyId[ 1 ], &enemyUse[ 1 ],&enemyId[ 2 ], &enemyUse[ 2 ],&enemyId[ 3 ], &enemyUse[ 3 ],&enemyId[ 4 ], &enemyUse[ 4 ],
		&enemyId[ 5 ], &enemyUse[ 5 ],&enemyId[ 6 ], &enemyUse[ 6 ],&enemyId[ 7 ], &enemyUse[ 7 ],&enemyId[ 8 ], &enemyUse[ 8 ],&enemyId[ 9 ], &enemyUse[ 9 ],
		&enemyId[ 10 ], &enemyUse[ 10 ],&enemyId[ 11 ], &enemyUse[ 11 ],&enemyId[ 12 ], &enemyUse[ 12 ],&enemyId[ 13 ], &enemyUse[ 13 ],&enemyId[ 14 ], &enemyUse[ 14 ], 
		&enemyId[ 15 ], &enemyUse[ 15 ],&enemyId[ 16 ], &enemyUse[ 16 ],&enemyId[ 17 ], &enemyUse[ 17 ],&enemyId[ 18 ], &enemyUse[ 18 ],&enemyId[ 19 ], &enemyUse[ 19 ] );
	COtherPlayerManager::CopyRecvData(m_RecvData);

	return Vector3( 0, 0, 0 ) ;
}

void CSync::SetEnemyID(void)
{
	CScene *scene = CScene::GetList(PRIORITY_3D);
	CScene *scene_next;

	int id = 0;

	while (scene != NULL) {
		scene_next = scene->GetNext(scene);

		if (scene->GetObjtype(scene) == OBJ_TYPE_ENEMY) {
			CEnemy *enemy = dynamic_cast<CEnemy *>(scene);
			enemyId[id] = enemy->GetId();

			++id;
		}

		scene = scene_next;
	}
}