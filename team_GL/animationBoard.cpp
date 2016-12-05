/******************************************************************************
	タイトル名：animationBoard
	ファイル名：animationBoard.cpp
	作成者    ：AT-13B-284 35 小笠原啓太
	作成日    ：2016/12/05
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
#include "animationBoard.h"
#include "input.h"

/******************************************************************************
	マクロ定義
******************************************************************************/

/******************************************************************************
	関数名 : CAnimationBoard::CAnimationBoard(int Priority, OBJ_TYPE objType) : CScene3D(Priority, objType)
	説明   : コンストラクタ
******************************************************************************/
CAnimationBoard::CAnimationBoard(int Priority, OBJ_TYPE objType) : CScene3D(Priority, objType)
{
	m_nCntAnim = 0;		
	m_nPatternAnim = 0;
	m_pTexture = NULL;
}

/******************************************************************************
	関数名 : CAnimationBoard::~CAnimationBoard()
	説明   : デストラクタ
******************************************************************************/
CAnimationBoard::~CAnimationBoard()
{
}

/******************************************************************************
	関数名 : void CAnimationBoard::Init(Vector3 pos, float width, float height)
	引数   : void
	戻り値 : なし
	説明   : 初期化処理
******************************************************************************/
void CAnimationBoard::Init(Vector3 pos, float width, float height)
{
	m_Pos = pos;
	m_Rot = Vector3(0.0f, 0.0f, 0.0f);
	m_Scl = Vector3(1.0f, 1.0f, 1.0f);

	m_Width = width;
	m_Height = height;
	m_Depth = 0.0f;

	m_pTexture = new CTexture;
	m_nTexIdx = m_pTexture->CreateTexture("data\\TEXTURE\\player000.tga");
}

/******************************************************************************
	関数名 : void CAnimationBoard::Uninit(void)
	引数   : void
	戻り値 : なし
	説明   : 終了処理
******************************************************************************/
void CAnimationBoard::Uninit(void)
{
	SAFE_RELEASE(m_pTexture);
}

/******************************************************************************
	関数名 : void CAnimationBoard::Update(void)
	引数   : void
	戻り値 : なし
	説明   : 更新処理
******************************************************************************/
void CAnimationBoard::Update(void)
{
}

/******************************************************************************
	関数名 : void CAnimationBoard::Draw(void)
	引数   : void
	戻り値 : なし
	説明   : 描画処理。
******************************************************************************/
void CAnimationBoard::Draw(void)
{
	glDisable(GL_LIGHTING);
	//	ここからモデルビューマトリクスの設定////////////////////////
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//	ここまでモデルビューマトリクスの設定////////////////////////

	glScalef(m_Scl.x, m_Scl.y, m_Scl.z);
	glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
	glRotatef(m_Rot.y, 0.0f ,1.0f, 0.0f);


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
	glColor4f(1 , 1 , 1, 1);

	//	法線設定
	glNormal3f(0, 1, 0);

	//	頂点座標設定
	glTexCoord2d(0.0, 1.0);
    glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), m_Pos.z);

	glTexCoord2d(1.0, 1.0);
    glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), m_Pos.z);

	glTexCoord2d(0.0, 0.0);
    glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), m_Pos.z);

	glTexCoord2d(1.0, 0.0);
    glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), m_Pos.z);

	glEnd();
	//	描画終了

	glEnable(GL_LIGHTING);

	 glBindTexture(GL_TEXTURE_2D, 0);
    //　テクスチャマッピング無効化
    glDisable(GL_TEXTURE_2D);

	//	ここからマトリックスを元に戻す//////////////////////////////
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	//	ここまでマトリックスを元に戻す//////////////////////////////
}

/******************************************************************************
	関数名 : CAnimationBoard *CAnimationBoard::Create(Vector3 pos, float width, float height)
	引数   :void
	戻り値 : obj
	説明   : 作成関数。 
******************************************************************************/
CAnimationBoard *CAnimationBoard::Create(Vector3 pos, float width, float height)
{
	CAnimationBoard *obj = new CAnimationBoard;
	obj->Init(pos, width, height);

	return obj;
}