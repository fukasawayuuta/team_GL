/******************************************************************************
	タイトル名：Item
	ファイル名：item.h
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
class CItem : public CAnimationBoard
{
public:
	CItem(int Priority = PRIORITY_3D, OBJ_TYPE objType = OBJ_TYPE_2D);		//	コンストラクタ。
	~CItem(void);		//	デストラクタ。

	void Init(Vector3 pos, float width, float height, int texIndex);		//	初期化関数。
	void Uninit(void);		//	終了関数。
	void Update(void);		//	更新関数。
	void Draw(void);		//	描画関数。

	static void Create(Vector3 pos, float width, float height, int texIndex);		//	生成関数。
	Vector3 GetPosition( void ){ return m_Pos ; };
	void HitCheck( Vector3 pos, float width, float height );

private:
	bool bOpen;		// 宝箱が空いた状態どうか
};