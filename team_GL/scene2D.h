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
	CScene2D(int Priority = PRIORITY_4, OBJ_TYPE objType = OBJ_TYPE_NONE);		//	コンストラクタ。
	~CScene2D();	//	デストラクタ。
	void Init(char* fileName);	//	初期化関数。
	void Uninit(void);	//	終了関数。
	void Update(void);	//	更新関数。
	void Draw(void);	//	描画関数。

	static CScene2D *Create(char* fileName);
private:
	Vector2 m_Pos;		//	座標。
	Vector2 m_Rot;		//	角度。
	float m_Width;		//	横幅。
	float m_Height;		//	縦幅。
	CTexture *m_Texture;
};

