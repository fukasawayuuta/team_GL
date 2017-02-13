/******************************************************************************
	タイトル名 : スコアクラス
	ファイル名 : score.cpp
	作成者     : AT-13B-284 02 阿部隆
	作成日     : 2016/11/17
	更新日     : 
******************************************************************************/
/******************************************************************************
	インクルードファイル
******************************************************************************/
//#include "main.h"
//#include "manager.h"
//#include "rerender.h"
//
//#include "score.h"
#include "main.h"
#include "manager.h"
#include "scene.h"


#include "score.h"
#include "sync.h"

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
//	静的メンバ変数宣言/////////////////////////////////////////////////////////

//=============================================================================
//	関数名 : CScore::CScore()
//	説明   : コンストラクタ
//			 値のデフォルト化
//=============================================================================
CScore::CScore(int Priority, OBJ_TYPE objType)
{
	m_nScore		= 0;
	m_WidthChange	= 0;
}

//=============================================================================
//	関数名 : CScore::~CScore()
//	説明   : デストラクタ
//=============================================================================
CScore::~CScore()
{
}

/******************************************************************************
	関数名 : CScore *CScore::Create ( Vector2 pos, Vector2 rot, float width, float height, int index )
	引数   : pos, rot, width, height, fileName
	戻り値 : なし
	説明   : スコアの生成処理
******************************************************************************/
CScore *CScore::Create ( Vector2 pos, Vector2 rot, float width, float height, int index, int id )
{
	CScore *score;

	score = new CScore;
	score -> Init( pos, rot, width, height, index, id );

	return score;
}

/******************************************************************************
	関数名 : void CScore::Init ( Vector2 pos, Vector2 rot, float width, float height, int index )
	引数   : pos, rot, width, height, fileName
	戻り値 : なし
	説明   : スコアの初期化処理
******************************************************************************/
void CScore::Init ( Vector2 pos, Vector2 rot, float width, float height, int index, int id )
{
	// 引数値を代入
	m_Pos		= pos;
	m_Rot		= rot;
	m_Width		= width;
	m_Height	= height;

	m_nId = id;

	// テクスチャを読み込み、生成する
	m_nTexIdx = CTexture::SetTexture( index );
}


/******************************************************************************
	関数名 : void CScore::Uninit ( void )
	引数   : void
	戻り値 : なし
	説明   : スコアの終了処理
******************************************************************************/
void CScore::Uninit ( void )
{
	if( m_nTexIdx ) {
		m_nTexIdx = 0;
	}
}


/******************************************************************************
	関数名 : void CScore::Update ( void )
	引数   : void
	戻り値 : なし
	説明   : スコアの更新処理
******************************************************************************/
void CScore::Update ( void )
{
	m_nScore = CSync::SetScore( m_nId );

	// スコアの更新順序
	m_Number[ 0 ] = m_nScore / 10000 % 10;
	m_Number[ 1 ] = m_nScore / 1000 % 10;
	m_Number[ 2 ] = m_nScore / 100 % 10;
	m_Number[ 3 ] = m_nScore / 10 % 10;
	m_Number[ 4 ] = m_nScore / 1 % 10;

	// スコアの動作確認関数( +1ずつ加算する )
	//AddScore(1);

}

/******************************************************************************
	関数名 : void CScore::Draw ( void )
	引数   : void
	戻り値 : なし
	説明   : スコアの描画処理
******************************************************************************/
void CScore::Draw ( void )
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

	// UV値と頂点座標の設定 ( DirectX形式 )
	for( int CntScore = 0; CntScore < MAX_SCORE; CntScore++ ) {
		// [ 0 ]
		glTexCoord2d( 0.1f * m_Number[ CntScore ], 0.0f );
		glVertex3f( 
					m_Pos.x - ( m_Width * 0.5f ) + CntScore * ( m_Width + m_WidthChange ),
					m_Pos.y - (m_Height * 0.5f),
					0.0f );
		// [ 2 ]
		glTexCoord2d( 0.1f * m_Number[ CntScore ], 1.0f );
		glVertex3f( 
					m_Pos.x - ( m_Width * 0.5f ) + CntScore * ( m_Width + m_WidthChange ),
					m_Pos.y + (m_Height * 0.5f),
					0.0f );
		// [ 1 ]
		glTexCoord2d( 0.1f * m_Number[ CntScore ] + 0.1f, 0.0f );
		glVertex3f( 
					m_Pos.x + ( m_Width * 0.5f ) + CntScore * ( m_Width + m_WidthChange ),
					m_Pos.y - (m_Height * 0.5f),
					0.0f );

		// [ 3 ]
		glTexCoord2d( 0.1f * m_Number[ CntScore ] + 0.1f, 1.0f );
		glVertex3f( 
					m_Pos.x + ( m_Width * 0.5f ) + CntScore * ( m_Width + m_WidthChange ),
					m_Pos.y + (m_Height * 0.5f),
					0.0f );
	}

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

/******************************************************************************
	関数名 : void CScore::AddScore ( int value )
	引数   : void
	戻り値 : value
	説明   : スコアの加算処理
******************************************************************************/
void CScore::AddScore( int value )
{
	m_nScore += value;
}

/******************************************************************************
	関数名 : int CScore::GetScore ( void )
	引数   : 無し
	戻り値 : int型
	説明   : スコアの持ち込み処理
******************************************************************************/
int CScore::GetScore ( void )
{
	return m_nScore;
}