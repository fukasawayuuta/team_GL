/******************************************************************************
タイトル名：player
ファイル名：player.cpp
作成者    ：AT-13B-284 10 小笠原啓太
作成日    ：2016/12/05
******************************************************************************/
/******************************************************************************
インクルードファイル
******************************************************************************/
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "mode.h"
#include "game.h"
#include "texture.h"
#include "scene.h"
#include "scene2D.h"
#include "game_UI.h"
#include "playerLifeGauge.h"
#include "scene3D.h"
#include "animationBoard.h"
#include "player.h"

/******************************************************************************
マクロ定義
******************************************************************************/

/*******************************************************************************
* グローバル変数
*******************************************************************************/

/*******************************************************************************
* 関数名：CPlayerLifeGauge::CPlayerLifeGauge(int Priority, OBJ_TYPE objType) : CGame_UI(Priority, objType)
*
* 引数	：
* 戻り値：
* 説明	：コンストラクタ
*******************************************************************************/
CPlayerLifeGauge::CPlayerLifeGauge(int Priority, OBJ_TYPE objType) : CGame_UI(Priority, objType)
{
	m_fMax = 1.0f;
	m_fCurrent = 1.0f;
}

/*******************************************************************************
* 関数名：CPlayerLifeGauge::~CPlayerLifeGauge()
*
* 引数	：
* 戻り値：
* 説明	：デストラクタ
*******************************************************************************/
CPlayerLifeGauge::~CPlayerLifeGauge()
{
}

/*******************************************************************************
* 関数名：void CPlayerLifeGauge::Update(void)
*
* 引数	：
* 戻り値：
* 説明	：更新処理
*******************************************************************************/
void CPlayerLifeGauge::Update(void)
{
	CGame *game = (CGame*)CManager::GetMode();
	CPlayer *player = game->GetPlayer();
	m_fCurrent = (float)player->GetLife();
	m_fCurrent = m_fCurrent <= 0.0f ? 0.0f : m_fCurrent;
	m_fMax = (float)player->GetLifeMax();
}

/*******************************************************************************
* 関数名：void CPlayerLifeGauge::Draw(void)
*
* 引数	：
* 戻り値：
* 説明	：描画処理
*******************************************************************************/
void CPlayerLifeGauge::Draw(void)
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
	glTexCoord2d(0.0, 0.0);
	glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), 0.0f);

	glTexCoord2d(m_fCurrent / m_fMax, 0.0);
	glVertex3f(m_Pos.x - m_Width * 0.5f + m_Width * m_fCurrent / m_fMax, m_Pos.y - (m_Height * 0.5f), 0.0f);

	glTexCoord2d(0.0, 1.0);
	glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), 0.0f);

	glTexCoord2d(m_fCurrent / m_fMax, 1.0);
	glVertex3f(m_Pos.x - m_Width * 0.5f + m_Width * m_fCurrent / m_fMax, m_Pos.y + (m_Height * 0.5f), 0.0f);

	glEnd();
	//	描画終了

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

/******************************************************************************
関数名 : void CGame_UI::Create(Vector2 pos, float width, float height)
引数   : void
戻り値 : なし
説明   : 描画処理。
******************************************************************************/
CPlayerLifeGauge *CPlayerLifeGauge::Create(Vector2 pos, float width, float height, int texIndex)
{
	CPlayerLifeGauge *obj = new CPlayerLifeGauge;
	obj->Init(pos, width, height, texIndex);

	return obj;
}