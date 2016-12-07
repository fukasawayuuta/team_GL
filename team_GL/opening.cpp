/*******************************************************************************
* タイトル名：
* ファイル名：opening.cpp
* 作成者	：AT13B284 02 阿部隆
* 作成日	：2016/11/30
********************************************************************************
* 更新履歴	：
*
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "main.h"
#include "mode.h"
#include "opening.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "scene.h"
#include "scene2D.h"
#include "input.h"
#include "texture.h"

/*******************************************************************************
* 関数名：COpening::COpening()
*
* 引数	：
* 戻り値：
* 説明	：コンストラクタ
*******************************************************************************/
COpening::COpening()
{
}

/*******************************************************************************
* 関数名：COpening::~COpening()
*
* 引数	：
* 戻り値：
* 説明	：デストラクタ
*******************************************************************************/
COpening::~COpening()
{
}

/*******************************************************************************
* 関数名：void COpening::Init( void )
*
* 引数	：
* 戻り値：
* 説明	：初期化処理
*******************************************************************************/
void COpening::Init ( void )
{
	CScene2D::Create( TEXTURE_TYPE_TEAMLOGO );
}

/*******************************************************************************
* 関数名：void COpening::Uninit( void )
*
* 引数	：
* 戻り値：
* 説明	：終了処理
*******************************************************************************/
void COpening::Uninit(void)
{
	CScene::ReleaseAll();
}

/*******************************************************************************
* 関数名：void COpening::Update( void )
*
* 引数	：
* 戻り値：
* 説明	：更新処理
*******************************************************************************/
void COpening::Update(void)
{
	CScene::UpdateAll();

	if( CInput::GetKeyboardTrigger( DIK_RETURN ) )
	{
		CFade::Start( new CTitle );
	}
}

/*******************************************************************************
* 関数名：void COpening::Draw( void )
*
* 引数	：
* 戻り値：
* 説明	：オープニングの背景(黒画面)の描画処理
*******************************************************************************/
void COpening::Draw(void)
{
	/* ライトを無効 */
	glDisable(GL_LIGHTING);
	/* デプステストの無効 */
	glDisable(GL_DEPTH_TEST);
	/* プロジェクションマトリクスの設定 */
	glMatrixMode(GL_PROJECTION);							// 射影変換行列設定
	glPushMatrix();											// 現在の射影変換行列を保存
	glLoadIdentity();										// 行列セット
	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1);		// 正射影変換設定

	/* モデルビューマトリクスの設定 */
	glMatrixMode(GL_MODELVIEW);								// モデルビュー変換行列設定
	glPushMatrix();											// 現在のモデルビュー行列を保存
	glLoadIdentity();										// 行列セット

	/* テクスチャオブジェクトの結合 */
	glBindTexture(GL_TEXTURE_2D, 0);

	/* 2Dポリゴン描画開始 */
	glBegin(GL_TRIANGLE_STRIP);

	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f( SCREEN_WIDTH, 0.0f, 0.0f);

	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(0.0f, SCREEN_HEIGHT, 0.0f);

	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	glEnd();
	/* 2Dポリゴン描画終了 */

	/* テクスチャオブジェクトの結合 */
	glBindTexture(GL_TEXTURE_2D, 0);

	glMatrixMode(GL_PROJECTION);	// 射影変換行列設定
	glPopMatrix();					// 射影変換行列を復元

	glMatrixMode(GL_MODELVIEW);		// モデルビュー変換行列設定
	glPopMatrix();					// モデルビュー行列を復元

	/* ライトを有効 */
	glEnable(GL_LIGHTING);
	/* デプステストを有効 */
	glEnable(GL_DEPTH_TEST);

	glFlush();						// コマンドの強制実行


	CScene::DrawAll();
}