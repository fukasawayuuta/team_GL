/******************************************************************************
	タイトル名：filedObject
	ファイル名：filedObject.cpp
	作成者    ：AT-13B-284 35 深澤佑太
	作成日    ：2016/11/28
******************************************************************************/
/******************************************************************************
	インクルードファイル
******************************************************************************/
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "scene.h"
#include "scene3D.h"
#include "fieldObject.h"

/******************************************************************************
	関数名 : CFieldObject::CFieldObject()
	説明   : コンストラクタ
******************************************************************************/
CFieldObject::CFieldObject(int Priority, OBJ_TYPE objType) : CScene3D(Priority, objType)
{
	m_IsBreak = true;
	m_IsActive = true;
}

/******************************************************************************
	関数名 : CFieldObject::~CFieldObject()
	説明   : デストラクタ
******************************************************************************/
CFieldObject::~CFieldObject()
{
}

/******************************************************************************
	関数名 : void CFieldObject::Init(void)
	引数   : void
	戻り値 : なし
	説明   : 初期化処理
******************************************************************************/
void CFieldObject::Init(Vector3 pos, Vector3 rot, float width, float height, int index)
{
	m_Pos = pos;
	m_Rot = rot;
	m_Width = width;
	m_Height = height;
	m_nTexIdx = CTexture::SetTexture(index);
}

/******************************************************************************
	関数名 : void CFieldObject::Uninit(void)
	引数   : void
	戻り値 : なし
	説明   : 終了処理
******************************************************************************/
void CFieldObject::Uninit(void)
{

}

/******************************************************************************
	関数名 : void CFieldObject::Update(void)
	引数   : void
	戻り値 : なし
	説明   : 更新処理
******************************************************************************/
void CFieldObject::Update(void)
{

}

/******************************************************************************
	関数名 : void CFieldObject::Draw(void)
	引数   : void
	戻り値 : なし
	説明   : 描画処理。
******************************************************************************/
void CFieldObject::Draw(void)
{
	CScene3D::Draw();
}

/******************************************************************************
	関数名 : CFieldObject *CFieldObject::Create(void)
	引数   : void
	戻り値 : obj
	説明   : 作成関数。 
******************************************************************************/
CFieldObject *CFieldObject::Create(Vector3 pos, Vector3 rot, float width, float height, int index)
{
	CFieldObject *obj = new CFieldObject;
	obj->Init(pos, rot, width, height, index);

	return obj;
}