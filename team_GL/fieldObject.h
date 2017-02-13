/******************************************************************************
	タイトル名：filedObject
	ファイル名：filedObject.h
	作成者    ：AT-13B-284 35 深澤佑太
	作成日    ：2016/11/28
******************************************************************************/
/******************************************************************************
	インクルードガード
******************************************************************************/
#pragma once

/******************************************************************************
	クラス宣言
******************************************************************************/
class CFieldObject : public CScene3D
{
public:
	typedef enum {
		OBJECT_TYPE_NONE = 0,			//	none.
		OBJECT_TYPE_BREAK_BLOCK,		//	壊れるブロック。
		OBJECT_TYPE_NOT_BREAK_BLOCK,	//	壊れないブロック。
		OBJECT_TYPE_MAX
	};

	CFieldObject(int Priority = PRIORITY_3D, OBJ_TYPE objType = OBJ_TYPE_FIELDOBJ);		//	コンストラクタ。
	~CFieldObject();	//	デストラクタ。

	void Init(Vector3 pos, Vector3 rot, float width, float height, int index);		//	初期化関数。
	void Uninit(void);		//	終了関数。
	void Update(void);		//	更新関数。
	void Draw(void);		//	描画関数。

	void SetActive(bool active) {m_IsActive = active;}		//	フラグをセットする関数。
	static CFieldObject *Create(Vector3 pos, Vector3 rot, float width, float height, int index);		//	生成関数。
	static void Load(void);
	bool HitCheck(Vector3 pos, float width, float height);

private:
	bool m_IsBreak;			//	壊れるかどうかのフラグ。
	bool m_IsActive;		//	いきているかどうかのフラグ。
};

