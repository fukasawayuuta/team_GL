/******************************************************************************
	タイトル名：SlashEffect
	ファイル名：slashEffect.h
	作成者    ：AT-13B-284 11 小野寺辰彦
	作成日    ：2016/12/05
******************************************************************************/
/******************************************************************************
	インクルードガード
******************************************************************************/
#pragma once

/******************************************************************************
	クラス宣言
******************************************************************************/
class CSlashEffect : public CAnimationBoard
{
public:
	CSlashEffect(int Priority = PRIORITY_3D, OBJ_TYPE objType = OBJ_TYPE_2D);		//	コンストラクタ。
	~CSlashEffect(void);		//	デストラクタ。

	void Init(Vector3 pos, int direction, float width, float height, int texIndex);		//	初期化関数。
	void Uninit(void);		//	終了関数。
	void Update(void);		//	更新関数。
	void Draw(void);		//	描画関数。

	static void Create(Vector3 pos, int direction, float width, float height, int texIndex);		//	生成関数。
	Vector3 GetPosition( void ){ return m_Pos ; };
	void HitCheck( Vector3 pos, float width, float height );
protected:
	Vector3 m_Move;			// 移動量

	void UpdateCollision(void); // 当たり判定更新
};