/******************************************************************************
	タイトル名：Bat
	ファイル名：bat.h
	作成者    ：AT-13B-284 35 深澤佑太
	作成日    ：2016/12/14
******************************************************************************/
/******************************************************************************
	インクルードガード
******************************************************************************/
#pragma once

/******************************************************************************
	クラス宣言
******************************************************************************/
class CBat : public CEnemy
{
public:
	CBat(int Priority = PRIORITY_3D, OBJ_TYPE objType = OBJ_TYPE_ENEMY);		//	コンストラクタ。
	~CBat();		//	デストラクタ。

	void Init(Vector3 pos, float width, float height, int texIndex, int id);
	void Update(void);		//更新関数。
	static CBat *Create(Vector3 pos, float width, float height, int texIndex, int id);		//	生成関数。

private:
	int m_StateCnt;		//	ステートカウンター。
	float m_Movement;	//	移動スピード。
	bool m_TurnFlag;	//	振り返るフラグ。
	float m_FirstYCoordinate;		//	最初のY座標。
	float m_SinAngle;		//	sin波の角度。
};

