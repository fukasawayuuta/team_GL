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
class CScore;
class CPlayer : public CAnimationBoard
{
public:
	CPlayer(int Priority = PRIORITY_3D, OBJ_TYPE objType = OBJ_TYPE_PLAYER);		//	コンストラクタ。
	~CPlayer();	//	デストラクタ。

	void Init(Vector3 pos, float width, float height);		//	初期化関数。
	void Uninit(void);		//	終了関数。
	void Update(void);		//	更新関数。
	void Draw(void);		//	描画関数
	void SetID(int id) {
		m_PlayerID = id;
		switch( m_PlayerID )
		{
		case 0:
			m_nTexIdx = CTexture::SetTexture( TEXTURE_TYPE_PLAYER000 );
			break;
		case 1:
			m_nTexIdx = CTexture::SetTexture( TEXTURE_TYPE_PLAYER001 );
			break;
		case 2:
			m_nTexIdx = CTexture::SetTexture( TEXTURE_TYPE_PLAYER002 );
			break;
		case 3:
			m_nTexIdx = CTexture::SetTexture( TEXTURE_TYPE_PLAYER003 );
			break;
		}
	}		//	ID設定。
	int GetID(void) {return m_PlayerID;}		//	ID取得。

	void HitCheck( Vector3 pos, float width, float height );	// 当たり判定チェック
	Vector3 GetMove(void) { return m_Move; }					// 移動量取得
	void SetState(int state);									// 状態設定
	void UpdateState(void);										// 状態更新
	void UpdateAnimation(void);									// アニメーションの更新
	void SetMyscore( CScore *pScore ){ m_pMyscore = pScore; }
	int GetLife(void) { return m_Hp; }							// 現在ライフの取得
	int GetLifeMax(void) { return m_HpMax; }					// 最大ライフの取得

	static CPlayer *Create(Vector3 pos, float width, float height);	//	作成関数。
private:
	// プレイヤーの状態
	typedef enum
	{
		STATE_WALK,
		STATE_ATTACK,
		STATE_DAMAGE,
		STATE_DEATH,
		STATE_MAX
	}STATE;

	typedef enum
	{
		ANIM_ROW_WALK = 0,
		ANIM_ROW_ATTACK = 1,
		ANIM_ROW_DAMAGE = 2,
		ANIM_ROW_DEATH = 2,
		ANIM_ROW_MAX,
	}ANIM_ROW;

	int m_Hp;
	int m_HpMax;
	int m_PlayerID;
	int m_Score;
	bool m_Jump;

	int m_nState;			// 現在の状態
	int m_nStateCnt;		// 状態カウンタ
	Vector3 m_Move;			// 移動量
	Vector3 m_OldPos;		// 1フレーム前の座標
	CScore *m_pMyscore;		// スコアポインタ
	float m_fAlfaSpeed;		// アルファ値の加減速度

	void UpdateCollision(void);	// 当たり判定更新
};
