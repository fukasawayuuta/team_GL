/******************************************************************************
	タイトル名：Enemy
	ファイル名：enemy.cpp
	作成者    ：AT-13B-284 35 深澤佑太
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
#include "enemy.h"

const int DRAW_SPEED = 30;
const int TEXTURE_COLUMN = 5;
const int TEXTURE_ROW = 1;
const int WALK_DRAW = 5;

/******************************************************************************
	関数名 : CEnemy::CEnemy()
	説明   : コンストラクタ
******************************************************************************/
CEnemy::CEnemy(int Priority, OBJ_TYPE objType) : CAnimationBoard(Priority, objType)
{
	m_nTexRow = TEXTURE_ROW;
	m_nTexColumn = TEXTURE_COLUMN;
}

/******************************************************************************
	関数名 : CEnemy::~CEnemy()
	説明   : デストラクタ
******************************************************************************/
CEnemy::~CEnemy(void)
{
}

/******************************************************************************
	関数名 : void CEnemy::Init(Vector3 pos, float width, float height)
	引数   : void
	戻り値 : なし
	説明   : 初期化処理
******************************************************************************/
void CEnemy::Init(Vector3 pos, float width, float height, int texIndex)
{
	m_Pos = pos;
	m_Width = width;
	m_Height = height;
	m_nDirection = 1;
	m_nTexIdx = CTexture::SetTexture(texIndex);
}

/******************************************************************************
	関数名 : void CEnemy::Uninit(void)
	引数   : void
	戻り値 : なし
	説明   : 終了処理
******************************************************************************/
void CEnemy::Uninit(void)
{

}

/******************************************************************************
	関数名 : void CEnemy::Update(void)
	引数   : void
	戻り値 : なし
	説明   : 更新処理
******************************************************************************/
void CEnemy::Update(void)
{
	// パターン描画更新
	m_nCntAnim++;
	if (m_nCntAnim == DRAW_SPEED)
	{
		m_nCntAnim = 0;
		m_nPatternAnim++;
		if (m_nPatternAnim == WALK_DRAW)
		{
			m_nPatternAnim = 0;
		}
	}
}

/******************************************************************************
	関数名 : void CEnemy::Draw(void)
	引数   : void
	戻り値 : なし
	説明   : 描画処理。
******************************************************************************/
void CEnemy::Draw(void)
{
	CAnimationBoard::Draw();
	//glDisable(GL_LIGHTING);
	////	ここからモデルビューマトリクスの設定////////////////////////
	//glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();
	////	ここまでモデルビューマトリクスの設定////////////////////////

	//glScalef(m_Scl.x, m_Scl.y, m_Scl.z);
	//glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
	//glRotatef(m_Rot.y, 0.0f ,1.0f, 0.0f);


	///* 透明色を描けるようにする */
	//glEnable(GL_BLEND); 
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	////　テクスチャマッピング有効化
 //   glEnable(GL_TEXTURE_2D);
 //   //　テクスチャをバインド
 //   glBindTexture(GL_TEXTURE_2D, m_nTexIdx);
	//
	////	描画開始
	//glBegin(GL_TRIANGLE_STRIP);

	////	色設定
	//glColor4f(1 , 1 , 1, 1);

	////	法線設定
	//glNormal3f(0, 1, 0);

	////	頂点座標設定
	//glTexCoord2d(m_nPatternAnim * (1.0 / TEXTURE_COLUMN), 0.0);
	//glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), m_Pos.z);

	//glTexCoord2d(m_nPatternAnim * (1.0 / TEXTURE_COLUMN), 1.0 / TEXTURE_ROW);
	//glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), m_Pos.z);

	//glTexCoord2d(m_nPatternAnim * (1.0 / TEXTURE_COLUMN) + (1.0 / TEXTURE_COLUMN), 0.0);
	//glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), m_Pos.z);

	//glTexCoord2d(m_nPatternAnim * (1.0 / TEXTURE_COLUMN) + (1.0 / TEXTURE_COLUMN), 1.0 / TEXTURE_ROW);
	//glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), m_Pos.z);

	//glEnd();
	////	描画終了

	//glEnable(GL_LIGHTING);

	// glBindTexture(GL_TEXTURE_2D, 0);
 //   //　テクスチャマッピング無効化
 //   glDisable(GL_TEXTURE_2D);

	////	ここからマトリックスを元に戻す//////////////////////////////
	//glMatrixMode(GL_MODELVIEW);
	//glPopMatrix();
	////	ここまでマトリックスを元に戻す//////////////////////////////
}

/******************************************************************************
	関数名 : void CEnemy::Create(Vector3 pos, float width, float height)
	引数   : pos, width, height
	戻り値 : なし
	説明   : 描画処理。
******************************************************************************/
void CEnemy::Create(Vector3 pos, float width, float height, int texIndex)
{
	CEnemy *obj = new CEnemy;
	obj->Init(pos, width, height, texIndex);
}