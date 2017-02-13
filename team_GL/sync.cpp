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

WSADATA CSync::m_Wsadata;
SOCKET CSync::m_Socket;
char CSync::m_RecvData[ 128 ];
char CSync::m_SendData[ 128 ];
SOCKADDR_IN CSync::m_addr;
Vector3 CSync::playerPos[ 4 ];
int CSync::playerScore[ 4 ];

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
	sprintf( m_SendData, "%5.3f %5.3f %5.3f %d", pos.x, pos.y, pos.z, score);
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
	sscanf( m_RecvData, "%f %f %f %d, %f %f %f %d, %f %f %f %d, %f %f %f %d",
		&playerPos[ 0 ].x, &playerPos[ 0 ].y, &playerPos[ 0 ].z, &playerScore[ 0 ], &playerPos[ 1 ].x, &playerPos[ 1 ].y, &playerPos[ 1 ].z, &playerScore[ 1 ],
		&playerPos[ 2 ].x, &playerPos[ 2 ].y, &playerPos[ 2 ].z, &playerScore[ 2 ], &playerPos[ 3 ].x, &playerPos[ 3 ].y, &playerPos[ 3 ].z, &playerScore[ 3 ] );
	COtherPlayerManager::CopyRecvData(m_RecvData);

	return Vector3( 0, 0, 0 ) ;
}