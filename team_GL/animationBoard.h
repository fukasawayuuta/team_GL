/******************************************************************************
	タイトル名：animationBoard
	ファイル名：animationBoard.h
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
class CAnimationBoard : public CScene3D
{
public:
	CAnimationBoard(int Priority = PRIORITY_3D, OBJ_TYPE objType = OBJ_TYPE_NONE);		//	コンストラクタ。
	~CAnimationBoard();	//	デストラクタ。

	void Init(Vector3 pos, float width, float height);		//	初期化関数。
	void Uninit(void);		//	終了関数。
	void Update(void);		//	更新関数。
	void Draw(void);		//	描画関数

	static CAnimationBoard *Create(Vector3 pos, float width, float height);	//	作成関数。
protected:
	int m_nTexRow;			// テクスチャ行数
	int m_nTexColumn;		// テクスチャ列数
	int m_nCntAnim;			// アニメーションカウンタ
	int m_nPatternAnim;		// パターンカウンタ
	int m_nRowAnim;			// 段カウンタ

	int m_nDirection;		// 向き 左：-1 右：1

	float m_fAlfa;			// アルファ値
};