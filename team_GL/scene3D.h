/******************************************************************************
	タイトル名：Scene3D
	ファイル名：scene3D.h
	作成者    ：AT-13B-284 35 深澤佑太
	作成日    ：2016/11/21
******************************************************************************/
/******************************************************************************
	インクルードガード
******************************************************************************/
#pragma once

/******************************************************************************
	クラス宣言
******************************************************************************/
class CScene3D : public CScene
{
public:
	CScene3D(int Priority = PRIORITY_3D, OBJ_TYPE objType = OBJ_TYPE_NONE);		//	コンストラクタ。
	~CScene3D();	//	デストラクタ。

	void Init(void);		//	初期化関数。
	void Uninit(void);		//	終了関数。
	void Update(void);		//	更新関数。
	void Draw(void);		//	描画関数

	static CScene3D *Create(void);	//	作成関数。

	Vector3 GetPos(void) { return m_Pos; }
	Vector2 GetCollision(void) { return m_Collision; }
protected:
	Vector3 m_Pos;		//	座標。
	Vector3 m_Rot;		//	角度。
	Vector3 m_Scl;		//	拡縮率。
	float m_Width;		//	横幅。
	float m_Height;		//	縦幅。
	float m_Depth;		//	奥行。
	int m_nTexIdx;		//	テクスチャタイプ。

	Vector2 m_Collision;	// 当たり判定
};

