/******************************************************************************
	タイトル名 : チュートリアルクラス
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
#include "tutorial.h"

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
//	関数名 : CTutorial::CTutorial()
//	説明   : コンストラクタ
//			 値のデフォルト化
//=============================================================================
CTutorial::CTutorial ( int Priority, OBJ_TYPE objType )
{
}

//=============================================================================
//	関数名 : CTutorial::~CTutorial()
//	説明   : デストラクタ
//=============================================================================
CTutorial::~CTutorial()
{
}

//	静的メンバ変数宣言/////////////////////////////////////////////////////////
bool CTutorial::m_bUse;		//	フラグ
Vector2 CTutorial::m_Pos;	//	座標。
Vector2 CTutorial::m_Rot;	//	角度。
float CTutorial::m_Width;	//	横幅。
float CTutorial::m_Height;	//	縦幅。

/******************************************************************************
	関数名 : CTutorial *CTutorial::Create ( Vector2 pos, Vector2 rot, float width, float height, int index )
	引数   : pos, rot, width, height, fileName
	戻り値 : なし
	説明   : チュートリアルの生成処理
******************************************************************************/
CTutorial *CTutorial::Create ( Vector2 pos, Vector2 rot, float width, float height, int index )
{
	CTutorial *tutorial;

	tutorial = new CTutorial;
	tutorial -> Init( pos, rot, width, height, index );

	return tutorial;
}

/******************************************************************************
	関数名 : void CTutorial::Init ( Vector2 pos, Vector2 rot, float width, float height, int index )
	引数   : pos, rot, width, height, fileName
	戻り値 : なし
	説明   : チュートリアルの初期化処理
******************************************************************************/
void CTutorial::Init ( Vector2 pos, Vector2 rot, float width, float height, int index )
{
	// 引数値を代入
	m_Pos		= pos;
	m_Rot		= rot;
	m_Width		= width;
	m_Height	= height;

	// メンバ変数 初期化
	m_bUse = false;

	// テクスチャを読み込み、生成する
	m_nTexIdx = CTexture::SetTexture( index );
}


/******************************************************************************
	関数名 : void CTutorial::Uninit ( void )
	引数   : void
	戻り値 : なし
	説明   : チュートリアルの終了処理
******************************************************************************/
void CTutorial::Uninit ( void )
{
	if( m_nTexIdx ) {
		m_nTexIdx = 0;
	}
}


/******************************************************************************
	関数名 : void CTutorial::Update ( void )
	引数   : void
	戻り値 : なし
	説明   : チュートリアルの更新処理
******************************************************************************/
void CTutorial::Update ( void )
{
	if( m_bUse ) {
		if( m_Width < 800.0f ) {
			m_Width+=20;
		}
		if( m_Width < 600.0f ) {
			m_Height+=20;
		}
	} else {
		m_Width = m_Height = 0.0f;
	}

}

/******************************************************************************
	関数名 : void CTutorial::Draw ( void )
	引数   : void
	戻り値 : なし
	説明   : チュートリアルの描画処理
******************************************************************************/
void CTutorial::Draw ( void )
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
	// αテスト 有効化
	glAlphaFunc(GL_GEQUAL, 0.09f );
	glEnable(GL_ALPHA_TEST);

	 //　テクスチャマッピング有効化
    glEnable(GL_TEXTURE_2D);
    //　テクスチャをバインド
    glBindTexture(GL_TEXTURE_2D, m_nTexIdx);

	// フラグ on
	if( m_bUse ) {

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
	}

	glEnable(GL_BLEND);
	glEnable(GL_LIGHTING);

	// αテスト無効化
	glDisable(GL_ALPHA_TEST);

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
	関数名 : void CTutorial::Start ( void )
	引数   : void
	戻り値 : なし
	説明   : チュートリアルの開始処理
******************************************************************************/
void CTutorial::Start ( void )
{
	m_Pos.x = SCREEN_WIDTH * 0.5f;
	m_Pos.y = 350.0f;
	m_bUse = true;
}

/******************************************************************************
	関数名 : void CTutorial::End ( void )
	引数   : void
	戻り値 : なし
	説明   : チュートリアルの平易さ処理
******************************************************************************/
void CTutorial::End ( void )
{
	m_Pos.x = m_Pos.y = m_Width = m_Height = 0.0f;
	m_bUse = false;
}