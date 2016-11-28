/******************************************************************************
	タイトル名：Scene2D
	ファイル名：scene2D.cpp
	作成者    ：AT-13B-284 35 深澤佑太
	作成日    ：2016/11/18
******************************************************************************/
/******************************************************************************
	インクルードファイル
******************************************************************************/
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "scene.h"
#include "scene2D.h"

/******************************************************************************
	関数名 : CScene2D::CScene2D()
	説明   : コンストラクタ
******************************************************************************/
CScene2D::CScene2D(int Priority, OBJ_TYPE objType)
{
	m_Pos = Vector2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
	m_Rot = Vector2(0.0f, 0.0f);
	m_nTexIdx = 0;
}

/******************************************************************************
	関数名 : CScene2D::~CScene2D()
	説明   : デストラクタ
******************************************************************************/
CScene2D::~CScene2D()
{
}

/******************************************************************************
	関数名 : void CScene2D::Init(void)
	引数   : void
	戻り値 : なし
	説明   : 初期化処理
******************************************************************************/
void CScene2D::Init(int nIdx)
{
	m_Width = 200.0f;
	m_Height = 200.0f;

	m_nTexIdx = CTexture::SetTexture(nIdx);
}

/******************************************************************************
	関数名 : void CScene2D::Uninit(void)
	引数   : void
	戻り値 : なし
	説明   : 終了処理
******************************************************************************/
void CScene2D::Uninit(void)
{
}

/******************************************************************************
	関数名 : void CScene2D::Update(void)
	引数   : void
	戻り値 : なし
	説明   : 更新処理。
******************************************************************************/
void CScene2D::Update(void)
{

}

/******************************************************************************
	関数名 : void CScene2D::Draw(void)
	引数   : void
	戻り値 : なし
	説明   : 更新処理。
******************************************************************************/
void CScene2D::Draw(void)
{
	glDisable(GL_LIGHTING);
	//	ここからプロジェクションマトリクスの設定////////////////////
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 1);
	//	ここまでプロジェクションマトリクスの設定////////////////////

	//	ここからモデルビューマトリクスの設定////////////////////////
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	//	ここまでモデルビューマトリクスの設定////////////////////////

	/* 透明色を描けるようにする */
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	 //　テクスチャマッピング有効化
    glEnable(GL_TEXTURE_2D);
    //　テクスチャをバインド
    glBindTexture(GL_TEXTURE_2D, m_nTexIdx);

	//	描画開始
	glBegin(GL_TRIANGLE_STRIP);

	//	色設定
	glColor4f(1, 1, 1, 1);

	//	頂点座標設定
	glTexCoord2d(0.0, 1.0);
    glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), 0.0f);
	
	glTexCoord2d(1.0, 1.0);
    glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), 0.0f);
	
	glTexCoord2d(0.0, 0.0);
    glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), 0.0f);
	
	glTexCoord2d(1.0, 0.0);
    glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), 0.0f);
	
	glEnd();
	//	描画終了

	glEnable(GL_BLEND);
	glEnable(GL_LIGHTING);

	glBindTexture(GL_TEXTURE_2D, 0);
    //　テクスチャマッピング無効化
    glDisable(GL_TEXTURE_2D);

	//	ここからマトリックスを元に戻す//////////////////////////////
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	//	ここまでマトリックスを元に戻す//////////////////////////////
}

CScene2D *CScene2D::Create(int nIdx)
{
	CScene2D *obj = new CScene2D;
	obj->Init(nIdx);

	return obj;
}