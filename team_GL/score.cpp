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
#include "scene2D.h"

#include "score.h"

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
CTGAImage *m_ScoreImage;

Vector2 CScore::m_Pos;	//	座標。
Vector2 CScore::m_Rot;	//	角度。
float CScore::m_Width;	//	横幅。
float CScore::m_Height;	//	縦幅。

//=============================================================================
//	関数名 : CScore::CScore()
//	説明   : コンストラクタ
//			 値のデフォルト化
//=============================================================================
CScore::CScore()
{
	m_TexIndex		= 0;
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
	関数名 : CScore *CScore::Create ( Vector2 pos, Vector2 rot, float width, float height, char* fileName )
	引数   : pos, rot, width, height, fileName
	戻り値 : なし
	説明   : スコアの生成処理
******************************************************************************/
CScore *CScore::Create ( Vector2 pos, Vector2 rot, float width, float height, char* fileName )
{
	CScore *score;

	score = new CScore;
	score -> Init( pos, rot, width, height, fileName );

	return score;
}

/******************************************************************************
	関数名 : void CScore::Init ( Vector2 pos, Vector2 rot, float width, float height, char* fileName )
	引数   : pos, rot, width, height, fileName
	戻り値 : なし
	説明   : スコアの初期化処理
******************************************************************************/
void CScore::Init ( Vector2 pos, Vector2 rot, float width, float height, char* fileName )
{
	// 引数値を代入
	m_Pos		= pos;
	m_Rot		= rot;
	m_Width		= width;
	m_Height	= height;

	// テクスチャを読み込み、生成する
	m_TexIndex = m_ScoreImage -> CreateTexture( fileName );
}


/******************************************************************************
	関数名 : void CScore::Uninit ( void )
	引数   : void
	戻り値 : なし
	説明   : スコアの終了処理
******************************************************************************/
void CScore::Uninit ( void )
{
	if( m_TexIndex ) {
		m_TexIndex = NULL;
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
	// スコアの更新順序
	m_Number[ 0 ] = m_nScore / 10000 % 10;
	m_Number[ 1 ] = m_nScore / 1000 % 10;
	m_Number[ 2 ] = m_nScore / 100 % 10;
	m_Number[ 3 ] = m_nScore / 10 % 10;
	m_Number[ 4 ] = m_nScore / 1 % 10;

	// スコアの動作確認関数( +1ずつ加算する )
	AddScore(1);

}

/******************************************************************************
	関数名 : void CScore::Draw ( void )
	引数   : void
	戻り値 : なし
	説明   : スコアの描画処理
******************************************************************************/
void CScore::Draw ( void )
{
	// 描画開始
	//CScene2D::DrawBegin();

	// テクスチャマッピングを有効化
	glEnable( GL_TEXTURE_2D );

///////////////////////////////////////

	// アルファブレンドを有効化
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glEnable( GL_BLEND );

	// テクスチャをバインドする
	glBindTexture( GL_TEXTURE_2D, m_TexIndex );

	// マトリクス設定
	glMatrixMode(GL_PROJECTION);

	glPushMatrix();
	// 単位行列化
	glLoadIdentity();

	// 正射影 設定
	glOrtho( 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 1 );

	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();

	// 描画の開始
	glBegin(GL_TRIANGLE_STRIP);

	// RGB値
	glColor4f( 1.0f, 1.0f, 1.0f, 1.0f);

	// UV値と頂点座標の設定 ( DirectX形式 )
	for( int CntScore = 0; CntScore < MAX_SCORE; CntScore++ ) {
		// [ 0 ]
		glTexCoord2d( 0.1f * m_Number[ CntScore ], 1.0f );
		glVertex3f( 
					m_Pos.x - ( m_Width * 0.5f ) + CntScore * ( m_Width + m_WidthChange ),
					m_Pos.y - (m_Height * 0.5f),
					0.0f );
		// [ 2 ]
		glTexCoord2d( 0.1f * m_Number[ CntScore ], 0.0f );
		glVertex3f( 
					m_Pos.x - ( m_Width * 0.5f ) + CntScore * ( m_Width + m_WidthChange ),
					m_Pos.y + (m_Height * 0.5f),
					0.0f );
		// [ 1 ]
		glTexCoord2d( 0.1f * m_Number[ CntScore ] + 0.1f, 1.0f );
		glVertex3f( 
					m_Pos.x + ( m_Width * 0.5f ) + CntScore * ( m_Width + m_WidthChange ),
					m_Pos.y - (m_Height * 0.5f),
					0.0f );

		// [ 3 ]
		glTexCoord2d( 0.1f * m_Number[ CntScore ] + 0.1f, 0.0f );
		glVertex3f( 
					m_Pos.x + ( m_Width * 0.5f ) + CntScore * ( m_Width + m_WidthChange ),
					m_Pos.y + (m_Height * 0.5f),
					0.0f );
	}

	// 描画の終了
	glEnd();

	// マトリクス終了の命令
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	// コマンドの実行
	glFlush();

	// 描画終了
	//CScene2D::DrawEnd();
	//////////////////////////

	// テクスチャを無効化
	glBindTexture( GL_TEXTURE_2D, 0 );

	// アルファブレンドを無効化
	glDisable( GL_BLEND );

	// テクスチャマッピングを無効化
	glDisable( GL_TEXTURE_2D );
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