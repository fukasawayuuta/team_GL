/******************************************************************************
	タイトル名 : リザルトロゴクラス
	ファイル名 : resultlogo.cpp
	作成者     : AT-13B-284 02 阿部隆
	作成日     : 2016/11/30
	更新日     : 
******************************************************************************/
/******************************************************************************
	インクルードファイル
******************************************************************************/

#include "main.h"
#include "manager.h"


#include "resultlogo.h"

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
//	関数名 : CResultLogo::CResultLogo()
//	説明   : コンストラクタ
//			 値のデフォルト化
//=============================================================================
CResultLogo::CResultLogo ( int Priority, OBJ_TYPE objType )
{
}

//=============================================================================
//	関数名 : CResultLogo::~CResultLogo()
//	説明   : デストラクタ
//=============================================================================
CResultLogo::~CResultLogo()
{
}

/******************************************************************************
	関数名 : CResultLogo *CResultLogo::Create ( Vector2 pos, Vector2 rot, float width, float height, int index )
	引数   : pos, rot, width, height, fileName
	戻り値 : なし
	説明   : リザルトロゴの生成処理
******************************************************************************/
CResultLogo *CResultLogo::Create ( Vector2 pos, Vector2 rot, float width, float height, int index )
{
	CResultLogo *resultlogo;

	resultlogo = new CResultLogo;
	resultlogo -> Init( pos, rot, width, height, index );

	return resultlogo;
}

/******************************************************************************
	関数名 : void CResultLogo::Init ( Vector2 pos, Vector2 rot, float width, float height, int index )
	引数   : pos, rot, width, height, fileName
	戻り値 : なし
	説明   : リザルトロゴの初期化処理
******************************************************************************/
void CResultLogo::Init ( Vector2 pos, Vector2 rot, float width, float height, int index )
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
	関数名 : void CResultLogo::Uninit ( void )
	引数   : void
	戻り値 : なし
	説明   : リザルトロゴの終了処理
******************************************************************************/
void CResultLogo::Uninit ( void )
{
	if( m_nTexIdx ) {
		m_nTexIdx = 0;
	}
}


/******************************************************************************
	関数名 : void CResultLogo::Update ( void )
	引数   : void
	戻り値 : なし
	説明   : リザルトロゴの更新処理
******************************************************************************/
void CResultLogo::Update ( void )
{


}

/******************************************************************************
	関数名 : void CResultLogo::Draw ( void )
	引数   : void
	戻り値 : なし
	説明   : リザルトロゴの描画処理
******************************************************************************/
void CResultLogo::Draw ( void )
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

	//	描画開始
	glBegin(GL_TRIANGLE_STRIP);

	//	色設定
	glColor4f(1, 1, 1, 1);

	//	頂点座標設定
	glTexCoord2d( 0.0, 1.0 );
    glVertex3f(m_Pos.x - ( m_Width * 0.5f ), m_Pos.y + (m_Height * 0.5f), 0.0f );

	glTexCoord2d( 1.0, 1.0 );
    glVertex3f(m_Pos.x + ( m_Width * 0.5f ), m_Pos.y + (m_Height * 0.5f), 0.0f );

	glTexCoord2d( 0.0f, 0.0f );
    glVertex3f(m_Pos.x - ( m_Width * 0.5f ), m_Pos.y - (m_Height * 0.5f), 0.0f );

	glTexCoord2d( 1.0f, 0.0f );
    glVertex3f(m_Pos.x + ( m_Width * 0.5f ), m_Pos.y - (m_Height * 0.5f), 0.0f );

	glEnd();
	//	描画終了

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
