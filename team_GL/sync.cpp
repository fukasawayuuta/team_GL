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
#include "sync.h"

WSADATA CSync::m_Wsadata;
SOCKET CSync::m_Socket;
char CSync::m_RecvData[ 128 ];
char CSync::m_SendData[ 128 ];
SOCKADDR_IN CSync::m_addr;

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
void CSync::Send( Vector3 pos )
{
	memset( m_SendData, 0, sizeof( m_SendData ) );
	sprintf( m_SendData, "%f %f %f", pos.x, pos.y, pos.z );
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
	Vector3 pos;
	memset( m_RecvData, 0, sizeof( m_RecvData ) );
	recv( m_Socket, m_RecvData, sizeof( m_RecvData ), 0 );
	sscanf( m_RecvData, "%f %f %f", &pos.x, &pos.y, &pos.z );
	return pos ;
}