/*******************************************************************************
* タイトル名：
* ファイル名：gamebackground.cpp
* 作成者	：AT13B284 31 中山和馬
* 作成日	：2016/11/28
********************************************************************************
* 更新履歴	：
*
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "mode.h"
#include "game.h"
#include "scene.h"
#include "scene2D.h"
#include "scene3D.h"
#include "texture.h"
#include "gamebackground.h"
#include "animationBoard.h"
#include "player.h"

/*******************************************************************************
* 関数名：CGameBackground::CGameBackground()
*
* 引数	：
* 戻り値：
* 説明	：コンストラクタ
*******************************************************************************/
CGameBackground::CGameBackground(int Priority, OBJ_TYPE objType) : CScene2D(Priority, objType)
{
	m_dTexCoord = 0.0f;
}

/*******************************************************************************
* 関数名：CGameBackground::~CGameBackground()
*
* 引数	：
* 戻り値：
* 説明	：デストラクタ
*******************************************************************************/
CGameBackground::~CGameBackground()
{
}

/*******************************************************************************
* 関数名：void CGameBackground::Init(void)
*
* 引数	：
* 戻り値：
* 説明	：初期化処理
*******************************************************************************/
void CGameBackground::Init(void)
{
	m_Pos = Vector2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
	m_Rot = Vector2(0.0f, 0.0f);
	m_TextureIndex = CTexture::SetTexture(TEXTURE_TYPE_GAME_BG);
	m_Width = SCREEN_WIDTH;
	m_Height = SCREEN_HEIGHT;
	m_dTexCoord = 0.5f;
}

/*******************************************************************************
* 関数名：void CGameBackground::Uninit(void)
*
* 引数	：
* 戻り値：
* 説明	：終了処理
*******************************************************************************/
void CGameBackground::Uninit(void)
{

}

/*******************************************************************************
* 関数名：void CGameBackground::Update(void)
*
* 引数	：
* 戻り値：
* 説明	：更新処理
*******************************************************************************/
void CGameBackground::Update(void)
{
	CGame *game = (CGame*)CManager::GetMode();
	CPlayer *player = game->GetPlayer();
	Vector3 move = player->GetPos();
	m_dTexCoord = (double)move.x / SCREEN_WIDTH;
}

/*******************************************************************************
* 関数名：void CGameBackground::Draw(void)
*
* 引数	：
* 戻り値：
* 説明	：描画処理
*******************************************************************************/
void CGameBackground::Draw(void)
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
	glBindTexture(GL_TEXTURE_2D, m_TextureIndex);

	//	描画開始
	glBegin(GL_TRIANGLE_STRIP);

	//	色設定
	glColor4f(1, 1, 1, 1);

	//	頂点座標設定
	glTexCoord2d(m_dTexCoord - 0.5f, 1.0);
	glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), -0.999f);

	glTexCoord2d(m_dTexCoord + 0.5f, 1.0);
	glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), -0.999f);

	glTexCoord2d(m_dTexCoord - 0.5f, 0.0);
	glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), -0.999f);

	glTexCoord2d(m_dTexCoord + 0.5f, 0.0);
	glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), -0.999f);

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

/*******************************************************************************
* 関数名：CGameBackground *Create( void )
*
* 引数	：
* 戻り値：
* 説明	：
*******************************************************************************/
CGameBackground *CGameBackground::Create( void )
{
	CGameBackground *pBg = new CGameBackground;
	pBg->Init();
	return pBg ;
}