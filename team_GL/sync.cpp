/*******************************************************************************
* タイトル名：sync
* ファイル名：sync.cpp
* 作成者	：AT13B284 31 中山和馬
* 作成日	：2016/12/05
********************************************************************************
* 更新履歴	：
*
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "sync.h"

WSADATA CSync::m_Wsadata;
SOCKET CSync::m_Socket;
char CSync::m_RecvData[ 128 ];
char CSync::m_SendData[ 128 ];
SOCKADDR_IN CSync::m_addr;

/*******************************************************************************
* 関数名：CSync
*
* 引数	：なし
* 戻り値：なし
* 説明	：コンストラクタ
*******************************************************************************/
CSync::CSync()
{
}

/*******************************************************************************
* 関数名：~CSync
*
* 引数	：なし
* 戻り値：なし
* 説明	：デストラクタ
*******************************************************************************/
CSync::~CSync()
{
}

/*******************************************************************************
* 関数名：Init
*
* 引数	：なし
* 戻り値：int nNumber
* 説明	：初期化処理
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
* 関数名：Uninit
*
* 引数	：なし
* 戻り値：なし
* 説明	：終了処理
*******************************************************************************/
void CSync::Uninit( void )
{
	closesocket( m_Socket );
	WSACleanup();
}

/*******************************************************************************
* 関数名：Send
*
* 引数	：Vector3 pos
* 戻り値：なし
* 説明	：送信
*******************************************************************************/
void CSync::Send( Vector3 pos )
{
	memset( m_SendData, 0, sizeof( m_SendData ) );
	sprintf( m_SendData, "%f %f %f", pos.x, pos.y, pos.z );
	send( m_Socket, m_SendData, sizeof( m_SendData ), 0 );
}

/*******************************************************************************
* 関数名：Recv
*
* 引数	：なし
* 戻り値：なし
* 説明	：受信
*******************************************************************************/
Vector3 CSync::Recv( void )
{
	Vector3 pos;
	memset( m_RecvData, 0, sizeof( m_RecvData ) );
	recv( m_Socket, m_RecvData, sizeof( m_RecvData ), 0 );
	sscanf( m_RecvData, "%f %f %f", &pos.x, &pos.y, &pos.z );
	return pos ;
}