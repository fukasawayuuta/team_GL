/******************************************************************************
	タイトル名 : Scene
	ファイル名 : Scene.h
	作成者     : AT-13C-284 36 深澤佑太
	作成日     : 2016/11/14
	更新日     : 
******************************************************************************/
/******************************************************************************
	インクルードガード
******************************************************************************/
#pragma once

/******************************************************************************
	インクルードファイル
******************************************************************************/
#include "main.h"
#include "renderer.h"

/******************************************************************************
	構造体宣言
******************************************************************************/
/******************************************************************************
	マクロ定義
******************************************************************************/
/******************************************************************************
	Class宣言
******************************************************************************/
//	オブジェクトタイプの列挙型
typedef enum {
	OBJ_TYPE_NONE = 0,
	OBJ_TYPE_2D,
	OBJ_TYPE_PLAYER,
	OBJ_TYPE_ENEMY,
	OBJ_TYPE_BOSS,
	OBJ_TYPE_FIELDOBJ,
	OBJ_TYPE_MAX
}OBJ_TYPE;

//	優先度の列挙型
typedef enum {
	PRIORITY_BACKGROUND = 0,	//	優先度1位(ドームとか床とか)
	PRIORITY_3D,				//	優先度2位(プレイヤーとか敵とか)
	PRIORITY_EFFECT,			//	エフェクトとか
	PRIORITY_2D,				//	優先度3位(2D関連)
	PRIORITY_MAX
}PRIORITY;

class CScene
{
public:

	CScene(int Priority = PRIORITY_3D, OBJ_TYPE objType = OBJ_TYPE_NONE);		//	コンストラクタ
	~CScene();	

	virtual void Init(void) {};			//	初期化関数
	virtual void Uninit(void) = 0;		//	終了関数
	virtual void Update(void) = 0;		//	更新関数
	virtual void Draw(void) = 0;		//	描画関数

	//	一括関数/////////////////////////////////////////////////////////////////////////////////////
	static void UpdateAll(void);		//	一括更新関数
	static void DrawAll(void);			//	一括描画関数
	static void ReleaseAll(void);		//	一括解放関数
	void Release(int Priority);			//	選択解放関数
	//	一括関数/////////////////////////////////////////////////////////////////////////////////////

	static CScene *GetList( int nPriority ){ return m_Top[ nPriority ] ; };
	static CScene *GetNext( CScene *pScene ){ return pScene->m_Next ; };
	static OBJ_TYPE GetObjtype( CScene *pScene ){ return pScene->m_type ; };

protected:
	OBJ_TYPE  m_type;			//	オブジェクトタイプ
	int     m_Priority;			//	優先度
	bool    m_Delete;			//	削除フラグ

	//	ポインタ関係/////////////////////////////////////////////////////////////////////////////////
	static CScene *m_Top[PRIORITY_MAX];		//	先頭のポインタ
	static CScene *m_Cur[PRIORITY_MAX];		//	現在のポインタ
	CScene *m_Prev;							//	前のポインタ
	CScene *m_Next;							//	次のポインタ
	//	ポインタ関係/////////////////////////////////////////////////////////////////////////////////
};

