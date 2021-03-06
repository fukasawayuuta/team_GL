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
const int DRAW_SPEED = 30;			// 描画スピード
const int TEXTURE_COLUMN = 1;		// テクスチャ列分割数
const int TEXTURE_ROW = 1;			// テクスチャ行分割数

/******************************************************************************
	関数名 : CAnimationBoard::CAnimationBoard(int Priority, OBJ_TYPE objType) : CScene3D(Priority, objType)
	説明   : コンストラクタ
******************************************************************************/
CAnimationBoard::CAnimationBoard(int Priority, OBJ_TYPE objType) : CScene3D(Priority, objType)
{
	m_nCntAnim = 0;		
	m_nPatternAnim = 0;
	m_nRowAnim = 0;
	
	m_nDirection = -1;
	m_nTexRow = TEXTURE_COLUMN;
	m_nTexColumn = TEXTURE_ROW;
	m_fAlfa = 1.0f;
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
}

/******************************************************************************
	関数名 : void CAnimationBoard::Uninit(void)
	引数   : void
	戻り値 : なし
	説明   : 終了処理
******************************************************************************/
void CAnimationBoard::Uninit(void)
{
}

/******************************************************************************
	関数名 : void CAnimationBoard::Update(void)
	引数   : void
	戻り値 : なし
	説明   : 更新処理
******************************************************************************/
void CAnimationBoard::Update(void)
{
	// パターン描画更新
	m_nCntAnim++;
	if ((m_nCntAnim % DRAW_SPEED) == 0)
	{
		m_nPatternAnim++;
		if (m_nPatternAnim == TEXTURE_COLUMN)
		{
			m_nPatternAnim = 0;
		}
	}
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

	//　テクスチャマッピング有効化
    glEnable(GL_TEXTURE_2D);
    //　テクスチャをバインド
    glBindTexture(GL_TEXTURE_2D, m_nTexIdx);
	glDepthMask(GL_FALSE);
	//	描画開始
	glBegin(GL_TRIANGLE_STRIP);

	//	色設定
	glColor4f(1.0f, 1.0f, 1.0f, m_fAlfa);

	//	法線設定
	glNormal3f(0.0f, 1.0f, 0.0f);

	//	頂点座標設定
	if (m_nDirection < 0)
	{
		glTexCoord2d(m_nPatternAnim * (1.0 / m_nTexColumn), m_nRowAnim * (1.0 / m_nTexRow));
		glVertex3f(-m_Width * 0.5f, m_Height * 0.5f, 0.0f);

		glTexCoord2d(m_nPatternAnim * (1.0 / m_nTexColumn), m_nRowAnim * (1.0 / m_nTexRow) + (1.0 / m_nTexRow));
		glVertex3f(-m_Width * 0.5f, -m_Height * 0.5f, 0.0f);

		glTexCoord2d(m_nPatternAnim * (1.0 / m_nTexColumn) + (1.0 / m_nTexColumn), m_nRowAnim * (1.0 / m_nTexRow));
		glVertex3f(m_Width * 0.5f, m_Height * 0.5f, 0.0f);

		glTexCoord2d(m_nPatternAnim * (1.0 / m_nTexColumn) + (1.0 / m_nTexColumn), m_nRowAnim * (1.0 / m_nTexRow) + (1.0 / m_nTexRow));
		glVertex3f(m_Width * 0.5f, -m_Height * 0.5f, 0.0f);
	}
	else if (m_nDirection > 0)
	{
		glTexCoord2d(m_nPatternAnim * (1.0 / m_nTexColumn) + (1.0 / m_nTexColumn), m_nRowAnim * (1.0 / m_nTexRow));
		glVertex3f(-m_Width * 0.5f, m_Height * 0.5f, 0.0f);

		glTexCoord2d(m_nPatternAnim * (1.0 / m_nTexColumn) + (1.0 / m_nTexColumn), m_nRowAnim * (1.0 / m_nTexRow) + (1.0 / m_nTexRow));
		glVertex3f(-m_Width * 0.5f, -m_Height * 0.5f, 0.0f);

		glTexCoord2d(m_nPatternAnim * (1.0 / m_nTexColumn), m_nRowAnim * (1.0 / m_nTexRow));
		glVertex3f(m_Width * 0.5f, m_Height * 0.5f, 0.0f);

		glTexCoord2d(m_nPatternAnim * (1.0 / m_nTexColumn), m_nRowAnim * (1.0 / m_nTexRow) + (1.0 / m_nTexRow));
		glVertex3f(m_Width * 0.5f, -m_Height * 0.5f, 0.0f);
	}

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