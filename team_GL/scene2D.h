/******************************************************************************
	タイトル名：Scene2D
	ファイル名：scene2D.cpp
	作成者    ：AT-13B-284 35 深澤佑太
	作成日    ：2016/11/18
******************************************************************************/
/******************************************************************************
	インクルードガード
******************************************************************************/
#pragma once

/******************************************************************************
	クラス宣言
******************************************************************************/
class CTexture;
class CScene2D : public CScene
{
public:
	CScene2D(int Priority = PRIORITY_2D, OBJ_TYPE objType = OBJ_TYPE_NONE);		//	コンストラクタ。
	~CScene2D();	//	デストラクタ。
	virtual void Init(int nIdx);//	初期化関数。
	virtual void Uninit(void);	//	終了関数。
	virtual void Update(void);	//	更新関数。
	virtual void Draw(void);	//	描画関数。

	static CScene2D *Create(int nIdx);
protected:
	Vector2 m_Pos;		//	座標。
	Vector2 m_Rot;		//	角度。
	float m_Width;		//	横幅。
	float m_Height;		//	縦幅。
	int m_nTexIdx;
};

