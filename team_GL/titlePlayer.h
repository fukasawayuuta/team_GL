/******************************************************************************
	タイトル名：titlePlayer
	ファイル名：titlePlayer.h
	作成者    ：AT-13B-284 02 阿部　隆
	作成日    ：2017/02/13
******************************************************************************/
/******************************************************************************
	インクルードガード
******************************************************************************/
#pragma once
#include "animationBoard.h"

const int PLAYER_MAX = 4;

/******************************************************************************
	クラス宣言
******************************************************************************/

class CTitlePlayer : public CAnimationBoard
{
public:
	CTitlePlayer(int Priority = PRIORITY_3D, OBJ_TYPE objType = OBJ_TYPE_PLAYER);		//	コンストラクタ。
	~CTitlePlayer();	//	デストラクタ。

	void Init(Vector3 pos, float width, float height);		//	初期化関数。
	void Uninit(void);		//	終了関数。
	void Update(void);		//	更新関数。
	void Draw(void);		//	描画関数

	void SetState(int state);									// 状態設定
	void UpdateState(void);										// 状態更新
	void UpdateAnimation(void);									// アニメーションの更新

	static CTitlePlayer *Create(Vector3 pos, float width, float height);	//	作成関数。
private:
	// プレイヤーの状態
	typedef enum
	{
		STATE_WALK,
		STATE_ATTACK,
		STATE_DAMAGE,
		STATE_MAX
	}STATE;

	// プレイヤーの構造体
	struct PLAYER
	{
		Vector3 pos;		// プレイヤーの位置
		Vector3 move;		// プレイヤーの移動量
		int		state;		// プレイヤーの状態
	};

	bool m_Jump;

	int m_nState;			// 現在の状態
	int m_nStateCnt;		// 状態カウンタ
	Vector3 m_Move;			// 移動量

	int m_Time;			// 時間計測

};
