/******************************************************************************
	タイトル名：sync
	ファイル名：sync.h
	作成者    ：AT-13B-284 31 中山和馬
	作成日    ：2016/12/05
******************************************************************************/
/******************************************************************************
	インクルードガード
******************************************************************************/
#pragma once

#include"main.h"

/******************************************************************************
	クラス宣言
******************************************************************************/
class CSync
{
private:
	static WSADATA m_Wsadata;
	static SOCKET m_Socket;
	static char m_SendData[ 128 ];
	static char m_RecvData[ 128 ];
	static SOCKADDR_IN m_addr;

public:
	CSync();
	~CSync();

	static int Init( void );
	static void Uninit( void );
	static void Send( Vector3 pos, int score );
	static Vector3 Recv( void );
	static char *GetRecvData(void) {return m_RecvData;}
};