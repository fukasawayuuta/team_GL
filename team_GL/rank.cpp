/*******************************************************************************
* タイトル名：
* ファイル名：rank.cpp
* 作成者	：AT13B284 02 阿部隆
* 作成日	：2016/12/13
* 処理内容	：1位から４位の順位を表示する
********************************************************************************
* 更新履歴	：
*
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "main.h"
#include "mode.h"
#include "matching.h"
#include "fade.h"

#include "rank.h"

//=============================================================================
//	関数名 : CRank::CRank()
//	説明   : コンストラクタ
//			 値のデフォルト化
//=============================================================================
CRank::CRank ( int Priority, OBJ_TYPE objType )
{
	m_HeightChange = 80.0f;

}

//=============================================================================
//	関数名 : CRank::CRank()
//	説明   : デストラクタ
//=============================================================================
CRank::~CRank ()
{
}

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

/******************************************************************************
	関数名 : void CRank::Init ( Vector2 pos, Vector2 rot, float width, float height )
	引数   : void型
	戻り値 : pos, rot, width, height
	説明   : ランク初期化処理
******************************************************************************/
void CRank::Init ( Vector2 pos, Vector2 rot, float width, float height )
{
	// 引数値を代入
	m_Pos		= pos;
	m_Rot		= rot;
	m_Width		= width;
	m_Height	= height;

	// 各項目の構造体の初期化
	for( int CntRank = 0; CntRank < RANK_ALL; CntRank++ ) {
		m_Rank[ CntRank ].pos		= Vector2( 0.0f, 0.0f );
		m_Rank[ CntRank ].fWidth	= 0.0f;
		m_Rank[ CntRank ].fHeight	= m_Height;
		m_Rank[ CntRank ].alfa		= 1.0f;
	}

	// 各順位の高さの初期化
	m_HeightChange = m_Height + 30;

	// 各順位の割り当て
	m_RankID = RANK_ALL - 1;

	// テクスチャを読み込み、生成する
	m_TexIdx[ 0 ] = CTexture::SetTexture( TEXTURE_TYPE_RANK_FIRST );
	m_TexIdx[ 1 ] = CTexture::SetTexture( TEXTURE_TYPE_RANK_SECOND );
	m_TexIdx[ 2 ] = CTexture::SetTexture( TEXTURE_TYPE_RANK_THIRD );
	m_TexIdx[ 3 ] = CTexture::SetTexture( TEXTURE_TYPE_RANK_FOURTH );

} // Initrank関数の終了

/******************************************************************************
== 関数名 ： void CRank::Uninit ( void )
== 戻り値 ： void型
== 引数   ： void
== 内容   ： ランク終了処理
******************************************************************************/
void CRank::Uninit ( void )
{
}

/******************************************************************************
== 関数名 ： void CRank::Update ( void )
== 戻り値 ： void型
== 引数   ： void
== 内容   ： ランク更新処理
******************************************************************************/
void CRank::Update ( void )
{
	// ランクの割り当てが尽きるまで処理を行う
	if( m_RankID > -1 ) {
		// ランクが一定距離まで動いていない場合
		if( m_Rank[ m_RankID ].pos.x < RANK_PLACE ) {
			m_Rank[ m_RankID ].pos.x += 20;
		} else if( m_Rank[ m_RankID ].pos.x >= RANK_PLACE ) {
			m_RankID--;	// ランクの割り当てを変えてる
		}
	}
} // Updaterank関数の終了

/******************************************************************************
== 関数名 ： void CRank::Draw ( void )
== 戻り値 ： void型
== 引数   ： void
== 内容   ： ランク描画処理
******************************************************************************/
void CRank::Draw ( void )
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

	// 透明色を描けるようにする
	//glEnable(GL_BLEND); 
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// αテスト 有効化
	glAlphaFunc(GL_GEQUAL, 0.5f );
	glEnable(GL_ALPHA_TEST);

	// テクスチャマッピング有効化
	glEnable(GL_TEXTURE_2D);

	// UV値と頂点座標の設定 ( DirectX形式 )
	for( int CntRank = 0; CntRank < RANK_ALL; CntRank++ ) {

		// テクスチャをバインド
		glBindTexture( GL_TEXTURE_2D, m_TexIdx[ CntRank ] );

		//	描画開始
		glBegin( GL_TRIANGLE_STRIP );

		//	色設定
		glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );

		//	頂点座標設定
		glTexCoord2d( 0.0f, 1.0f );
		glVertex3f( m_Pos.x - ( m_Width * 0.5f ) + m_Rank[ CntRank ].pos.x, m_Pos.y + ( m_Rank[ CntRank ].fHeight * 0.5f ) + ( m_HeightChange * CntRank ), 0.0f );
	
		glTexCoord2d( 1.0f, 1.0f );
		glVertex3f( m_Pos.x + ( m_Width * 0.5f ) + m_Rank[ CntRank ].pos.x, m_Pos.y + ( m_Rank[ CntRank ].fHeight * 0.5f ) + ( m_HeightChange * CntRank ), 0.0f );
	
		glTexCoord2d( 0.0f, 0.0f );
		glVertex3f( m_Pos.x - ( m_Width * 0.5f ) + m_Rank[ CntRank ].pos.x, m_Pos.y - ( m_Rank[ CntRank ].fHeight * 0.5f ) + ( m_HeightChange * CntRank ), 0.0f );
	
		glTexCoord2d( 1.0f, 0.0f );
		glVertex3f( m_Pos.x + ( m_Width * 0.5f ) + m_Rank[ CntRank ].pos.x, m_Pos.y - ( m_Rank[ CntRank ].fHeight * 0.5f ) + ( m_HeightChange * CntRank ), 0.0f );

		glEnd();
		//	描画終了
	}


	glEnable(GL_BLEND);
	glEnable(GL_LIGHTING);

	glBindTexture(GL_TEXTURE_2D, 0);

    //　テクスチャマッピング無効化
    glDisable(GL_TEXTURE_2D);

	// αテスト無効化
	glDisable(GL_ALPHA_TEST);

	//	ここからマトリックスを元に戻す//////////////////////////////
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	//	ここまでマトリックスを元に戻す//////////////////////////////

} // Drawrank関数の終了

/******************************************************************************
== 関数名 ： CRank* CRank::Create ( Vector2 pos, Vector2 rot, float width, float height )
== 戻り値 ： CRank型
== 引数   ： pos, rot, width, height
== 内容   ： ランク生成設定
******************************************************************************/
CRank *CRank::Create ( Vector2 pos, Vector2 rot, float width, float height )
{
	CRank *rank;

	rank = new CRank;
	rank -> Init( pos, rot, width, height );

	return rank;
}
