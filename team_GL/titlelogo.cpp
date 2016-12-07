/******************************************************************************
	タイトル名 : タイトルロゴクラス
	ファイル名 : titlelogo.cpp
	作成者     : AT-13B-284 02 阿部隆
	作成日     : 2016/11/30
	更新日     : 
******************************************************************************/
/******************************************************************************
	インクルードファイル
******************************************************************************/

#include "main.h"
#include "manager.h"


#include "titlelogo.h"

/******************************************************************************
	マクロ定義
******************************************************************************/
/******************************************************************************
	型定義
******************************************************************************/
/******************************************************************************
	プロトタイプ宣言
******************************************************************************/
/******************************************************************************
	グローバル変数
******************************************************************************/

//=============================================================================
//	関数名 : CTitleLogo::CTitleLogo()
//	説明   : コンストラクタ
//			 値のデフォルト化
//=============================================================================
CTitleLogo::CTitleLogo ( int Priority, OBJ_TYPE objType )
{
}

//=============================================================================
//	関数名 : CTitleLogo::~CTitleLogo()
//	説明   : デストラクタ
//=============================================================================
CTitleLogo::~CTitleLogo()
{
}

/******************************************************************************
	関数名 : CTitleLogo *CTitleLogo::Create ( Vector2 pos, Vector2 rot, float width, float height, int index )
	引数   : pos, rot, width, height, fileName
	戻り値 : なし
	説明   : タイトルロゴの生成処理
******************************************************************************/
CTitleLogo *CTitleLogo::Create ( Vector2 pos, Vector2 rot, float width, float height, int index )
{
	CTitleLogo *titlelogo;

	titlelogo = new CTitleLogo;
	titlelogo -> Init( pos, rot, width, height, index );

	return titlelogo;
}

/******************************************************************************
	関数名 : void CTitleLogo::Init ( Vector2 pos, Vector2 rot, float width, float height, int index )
	引数   : pos, rot, width, height, fileName
	戻り値 : なし
	説明   : タイトルロゴの初期化処理
******************************************************************************/
void CTitleLogo::Init ( Vector2 pos, Vector2 rot, float width, float height, int index )
{
	// 引数値を代入
	m_Pos		= pos;
	m_Rot		= rot;
	m_Width		= width;
	m_Height	= height;

	// テクスチャを読み込み、生成する
	m_nTexIdx = CTexture::SetTexture( index );
}


/******************************************************************************
	関数名 : void CTitleLogo::Uninit ( void )
	引数   : void
	戻り値 : なし
	説明   : タイトルロゴの終了処理
******************************************************************************/
void CTitleLogo::Uninit ( void )
{
	if( m_nTexIdx ) {
		m_nTexIdx = 0;
	}
}


/******************************************************************************
	関数名 : void CTitleLogo::Update ( void )
	引数   : void
	戻り値 : なし
	説明   : タイトルロゴの更新処理
******************************************************************************/
void CTitleLogo::Update ( void )
{


}

/******************************************************************************
	関数名 : void CTitleLogo::Draw ( void )
	引数   : void
	戻り値 : なし
	説明   : タイトルロゴの描画処理
******************************************************************************/
void CTitleLogo::Draw ( void )
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
    glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), 0.0f );

	glTexCoord2d(1.0, 1.0);
    glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), 0.0f );

	glTexCoord2d(0.0, 0.0);
    glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), 0.0f );

	glTexCoord2d(1.0, 0.0);
    glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), 0.0f );

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
