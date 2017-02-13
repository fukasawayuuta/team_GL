/******************************************************************************
	タイトル名：CGame_UI
	ファイル名：game_UI.h
	作成者    ：AT-13B-284 35 深澤佑太
	作成日    ：2016/12/05
******************************************************************************/
/******************************************************************************
	インクルードガード
******************************************************************************/
#pragma once

/******************************************************************************
	クラス宣言
******************************************************************************/
class CGame_UI : public CScene2D
{
public:
	CGame_UI(int Priority = PRIORITY_2D, OBJ_TYPE objType = OBJ_TYPE_2D);		//	コンストラクタ。
	~CGame_UI(void);	//	デストラクタ。

	virtual void Init(Vector2 pos, float width, float height, int texIndex);		//	初期化関数。
	virtual void Uninit(void);				//	終了関数。
	virtual void Update(void);				//	更新関数。
	virtual void Draw(void);				//	描画関数。

	static void Create(Vector2 pos, float width, float height, int texIndex);
};

