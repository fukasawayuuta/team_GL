/*******************************************************************************
* タイトル名：
* ファイル名：mode.h
* 作成者	：AT13B284 10 小笠原啓太
* 作成日	：2016/11/14
********************************************************************************
* 更新履歴	：
*
*******************************************************************************/
/*******************************************************************************
* インクルードガード
*******************************************************************************/
#pragma once

/*******************************************************************************
* クラス宣言
*******************************************************************************/
// ゲームクラス
class CCamera;
class CPlayer;
class COtherPlayer;
class COtherPlayerManager;
class CScore;
class CGame : public CMode
{
public:
	CGame();
	~CGame();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	CCamera* GetCamera(void) { return m_pCamera; }		// カメラ取得関数
	CPlayer* GetPlayer(void) { return m_pPlayer; }		// プレイヤー取得関数
private:
	CCamera *m_pCamera;
	CPlayer *m_pPlayer;
	COtherPlayer *m_pOtherPlayer[ 3 ];
	int m_SoundSE_ID;
	COtherPlayerManager *m_pOtherManager;
	CScore *m_pScore[ 4 ];

	DWORD m_ExitCode;					//	スレッドの終了判定。
	static unsigned int __stdcall Recv( void* );
	unsigned int thID;
	HANDLE hth;

	int m_SendCnt;		//	情報を送るタイミングカウンタ。
};

