/******************************************************************************
	タイトル名：player
	ファイル名：player.h
	作成者    ：AT-13B-284 10 小笠原啓太
	作成日    ：2016/12/05
******************************************************************************/
/******************************************************************************
	インクルードガード
******************************************************************************/
#pragma once

/******************************************************************************
	クラス宣言
******************************************************************************/
class CPlayer : public CAnimationBoard
{
public:
	CPlayer(int Priority = PRIORITY_3D, OBJ_TYPE objType = OBJ_TYPE_PLAYER);		//	コンストラクタ。
	~CPlayer();	//	デストラクタ。

	void Init(Vector3 pos, float width, float height);		//	初期化関数。
	void Uninit(void);		//	終了関数。
	void Update(void);		//	更新関数。
	void Draw(void);		//	描画関数
	void SetID(int id) {m_PlayerID = id;}		//	ID設定。
	int GetID(void) {return m_PlayerID;}		//	ID取得。

	void HitCheck( Vector3 pos, float width, float height );
	Vector3 GetMove(void) { return m_Move; }

	static CPlayer *Create(Vector3 pos, float width, float height);	//	作成関数。
private:
	// プレイヤーの状態
	typedef enum
	{
		STATE_WALK,
		STATE_ATTACK,
		STATE_DAMAGE,
		STATE_MAX
	}STATE;

	int m_Hp;
	int m_PlayerID;
	bool m_Jump;

	STATE m_State;
	Vector3 m_Move;			// 移動量
};
