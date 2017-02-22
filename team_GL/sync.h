/******************************************************************************
	�^�C�g�����Fsync
	�t�@�C�����Fsync.h
	�쐬��    �FAT-13B-284 31 ���R�a�n
	�쐬��    �F2016/12/05
******************************************************************************/
/******************************************************************************
	�C���N���[�h�K�[�h
******************************************************************************/
#pragma once

#include"main.h"

/******************************************************************************
	�N���X�錾
******************************************************************************/
class CSync
{
private:
	static WSADATA m_Wsadata;
	static SOCKET m_Socket;
	static char m_SendData[ 128 ];
	static char m_RecvData[ 128 ];
	static SOCKADDR_IN m_addr;
	static Vector3 playerPos[ 4 ];
	static int playerScore[ 4 ];
	static int playerDirection[ 4 ];
	static int playerState[ 4 ];
	static int enemyId[ 20 ];
	static bool enemyUse[ 20 ];

public:
	CSync();
	~CSync();

	static int Init( void );
	static void Uninit( void );
	static void Send( Vector3 pos, int score, int direction, int state );
	static Vector3 Recv( void );
	static char *GetRecvData(void) {return m_RecvData;}
	static Vector3 GetPos( int id ){ return playerPos[ id ] ; }
	static int GetScore( int id ){ return playerScore[ id ] ; }
	static void SetEnemyState( int id, bool use ){ enemyUse[ id ] = use ; }
	static int GetEnemyId( int id ){ return enemyId[ id ] ; }
	static bool GetEnemyUse( int id ){ return enemyUse[ id ] ; }
	static void SetEnemyID(void);
};