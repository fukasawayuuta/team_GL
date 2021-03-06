/******************************************************************************
	タイトル名：Scene3D
	ファイル名：scene3D.cpp
	作成者    ：AT-13B-284 35 深澤佑太
	作成日    ：2016/11/21
******************************************************************************/
/******************************************************************************
	インクルードファイル
******************************************************************************/
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "scene3D.h"

/******************************************************************************
	関数名 : CScene3D::CScene3D()
	説明   : コンストラクタ
******************************************************************************/
CScene3D::CScene3D(int Priority, OBJ_TYPE objType) : CScene(Priority, objType)
{
	m_Pos = Vector3(0.0f, 0.0f, 0.0f);
	m_Rot = Vector3(0.0f, 0.0f, 0.0f);
	m_Scl = Vector3(1.0f, 1.0f, 1.0f);
	m_Width = 0.0f;
	m_Height = 0.0f;
	m_Depth = 0.0f;
}

/******************************************************************************
	関数名 : CScene3D::~CScene3D()
	説明   : デストラクタ
******************************************************************************/
CScene3D::~CScene3D()
{
}

/******************************************************************************
	関数名 : void CScene3D::Init(void)
	引数   : void
	戻り値 : なし
	説明   : 初期化処理
******************************************************************************/
void CScene3D::Init(void)
{
	m_Pos = Vector3(0.0f, 0.0f, 0.0f);
	m_Rot = Vector3(0.0f, 0.0f, 0.0f);
	m_Scl = Vector3(1.0f, 1.0f, 1.0f);

	m_Width = 50.0f;
	m_Height = 50.0f;
	m_Depth = 0.0f;
}

/******************************************************************************
	関数名 : void CScene3D::Uninit(void)
	引数   : void
	戻り値 : なし
	説明   : 終了処理
******************************************************************************/
void CScene3D::Uninit(void)
{

}

/******************************************************************************
	関数名 : void CScene3D::Update(void)
	引数   : void
	戻り値 : なし
	説明   : 更新処理
******************************************************************************/
void CScene3D::Update(void)
{

}

/******************************************************************************
	関数名 : void CScene3D::Draw(void)
	引数   : void
	戻り値 : なし
	説明   : 描画処理。
******************************************************************************/
void CScene3D::Draw(void)
{
glDisable(GL_LIGHTING);
	//	ここからモデルビューマトリクスの設定////////////////////////
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//	ここまでモデルビューマトリクスの設定////////////////////////

	glScalef(m_Scl.x, m_Scl.y, m_Scl.z);
	glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
	glRotatef(m_Rot.y, 0.0f ,1.0f, 0.0f);

	//　テクスチャマッピング有効化
    glEnable(GL_TEXTURE_2D);
    //　テクスチャをバインド
    glBindTexture(GL_TEXTURE_2D, m_nTexIdx);
	glDepthMask(GL_FALSE);
	//	描画開始
	glBegin(GL_TRIANGLE_STRIP);

	//	色設定
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	//	法線設定
	glNormal3f(0.0f, 1.0f, 0.0f);

	//	頂点座標設定
	glTexCoord2d(0.0, 0.0);
    glVertex3f(-m_Width * 0.5f, m_Height * 0.5f, m_Pos.z);

	glTexCoord2d(0.0, 1.0);
    glVertex3f(-m_Width * 0.5f, -m_Height * 0.5f, m_Pos.z);

	glTexCoord2d(1.0, 0.0);
    glVertex3f(m_Width * 0.5f, m_Height * 0.5f, m_Pos.z);

	glTexCoord2d(1.0, 1.0);
    glVertex3f(m_Width * 0.5f, -m_Height * 0.5f, m_Pos.z);

	glEnd();
	// 描画終了

	glEnable(GL_LIGHTING);
	glDepthMask(GL_TRUE);
	glBindTexture(GL_TEXTURE_2D, 0);
    //　テクスチャマッピング無効化
    glDisable(GL_TEXTURE_2D);

	//	ここからマトリックスを元に戻す//////////////////////////////
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	//	ここまでマトリックスを元に戻す//////////////////////////////
}

/******************************************************************************
	関数名 : CScene3D *CScene3D::Create(void)
	引数   :void
	戻り値 : obj
	説明   : 作成関数。 
******************************************************************************/
CScene3D *CScene3D::Create(void)
{
	CScene3D *obj = new CScene3D;
	obj->Init();

	return obj;
}