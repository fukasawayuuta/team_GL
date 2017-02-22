/*******************************************************************************
* タイトル名：
* ファイル名：ranking.cpp
* 作成者	：AT13B284 02 阿部隆
* 作成日	：2016/12/13
* 処理内容	：ランキングとプレイヤー番号を表示する
********************************************************************************
* 更新履歴	：
*
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "main.h"
#include "manager.h"

#include "ranking.h"
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

//=============================================================================
//	関数名 : CRanking::CRanking()
//	説明   : コンストラクタ
//=============================================================================
CRanking::CRanking( int Priority, OBJ_TYPE objType )
{
}

//=============================================================================
//	関数名 : CRanking::CRanking()
//	説明   : デストラクタ
//=============================================================================
CRanking::~CRanking()
{
}

/******************************************************************************
	関数名 : CRanking* CRank::Create ( Vector2 pos, Vector2 rot, float width, float height, int index )
	引数   : pos, rot, width, height, index
	戻り値 : CRanking*
	説明   : ランキングの生成処理
******************************************************************************/
CRanking* CRanking::Create ( Vector2 pos, Vector2 rot, float width, float height, int index )
{
	CRanking *ranking;

	ranking = new CRanking;
	ranking -> Init( pos, rot, width, height, index );

	return ranking;
}


/******************************************************************************
	関数名 : void CRanking::Init ( Vector2 pos, Vector2 rot, float width, float height )
	引数   : void型
	戻り値 : pos, rot, width, height
	説明   : ランク初期化処理
******************************************************************************/
void CRanking::Init ( Vector2 pos, Vector2 rot, float width, float height, int index )
{
	// 引数値を代入
	m_Pos		= pos;
	m_Rot		= rot;
	m_Width		= width;
	m_Height	= height;

	// ランキングに予め数値を入れる
	for( int i = 0; i < RANKING_ALL; i++ ) {
		m_nRanking[ i ] = CManager::GetScore(i);
	}

	// プレイヤーのスコアを入れる
	//m_nRanking[ RANKING_ALL ] = CScore::GetScore();

	// ランキングの順位を設定する
	m_RankNum = Set( m_nRanking );

	// 時間計測の値を初期化する
	m_TimeCnt = 0;

	// テクスチャを読み込み、生成する
	m_TexIdx = CTexture::SetTexture( index );

	// プレイヤー番号のテクスチャを読み込み、生成する
	m_PlayerRankTexIdx[ 0 ] = CTexture::SetTexture( TEXTURE_TYPE_RANK_FIRST );
	m_PlayerRankTexIdx[ 1 ] = CTexture::SetTexture( TEXTURE_TYPE_RANK_SECOND );
	m_PlayerRankTexIdx[ 2 ] = CTexture::SetTexture( TEXTURE_TYPE_RANK_THIRD );
	m_PlayerRankTexIdx[ 3 ] = CTexture::SetTexture( TEXTURE_TYPE_RANK_FOURTH );

	// α値を初期化
	m_RankNumColor_a = 1.0f;

}

/******************************************************************************
== 関数名 ： void CRanking::Uninit ( void )
== 戻り値 ： void型
== 引数   ： void
== 内容   ： ランキング 終了処理
******************************************************************************/
void CRanking::Uninit ( void )
{
}

/******************************************************************************
== 関数名 ： void CRanking::Update ( void )
== 戻り値 ： void型
== 引数   ： void
== 内容   ： ランキング 更新処理
******************************************************************************/
void CRanking::Update ( void )
{
}

/******************************************************************************
== 関数名 ： void CRanking::Draw ( void )
== 戻り値 ： void型
== 引数   ： void
== 内容   ： ランキング 描画処理
******************************************************************************/
void CRanking::Draw ( void )
{

	int nRankingCnt;

	// 時間をカウントする
	m_TimeCnt++;

	// 一定時間ごとにα値を切り替える
	if( m_TimeCnt >= 10 ) {
		// カウントを0に戻す
		m_TimeCnt = 0;

		// α値を切り替える
		if( m_RankNumColor_a == 0.6f ) {
			m_RankNumColor_a = 0.3f;
		} else {
			m_RankNumColor_a = 0.6f;
		}
	}

	glDisable( GL_LIGHTING );

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
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// αテスト 有効化
	glAlphaFunc( GL_GEQUAL, 0.2f );
	glEnable( GL_ALPHA_TEST );

	// テクスチャマッピング有効化
	glEnable( GL_TEXTURE_2D );

	// テクスチャをバインド
	glBindTexture( GL_TEXTURE_2D, m_TexIdx );

	// ランキングのUV値と頂点座標の設定
	for( int j = 0; j < RANKING_ALL ; j++ ) {	// ランキングのループ
		nRankingCnt = m_nRanking[ j ];
		for( int i = 0; i < MAX_SCORE ; i++ ) {	// スコアのループ

			//	描画開始
			glBegin( GL_TRIANGLE_STRIP );

			// 色設定
			if( m_RankNum == j ) {
				glColor4f( 1.0f, 1.0f, 1.0f, m_RankNumColor_a );
			} else {
				glColor4f( 0.3f, 0.3f, 0.5f, 0.6f );
			}

			//	頂点座標設定
			glTexCoord2d( ( float )( nRankingCnt % 10 * 0.1f ), 1.0f );
			glVertex3f( m_Pos.x - (float)( m_Width * ( i + 1.0f ) ),
						m_Pos.y + m_Height * (float)( j + 1.0f ),
						0.0f );
	
			glTexCoord2d( ( float )( ( nRankingCnt % 10 + 1.0f ) * 0.1f ), 1.0f );
			glVertex3f( m_Pos.x - (float)( m_Width * i ),
						m_Pos.y + m_Height * (float)( j + 1.0f ),
						0.0f );
	
			glTexCoord2d( ( float )( nRankingCnt % 10 * 0.1f ), 0.0f );
			glVertex3f( m_Pos.x - (float)( m_Width * ( i + 1.0f ) ),
						m_Pos.y + m_Height * (float)j,
						0.0f );
	
			glTexCoord2d( ( float )( ( nRankingCnt % 10 + 1.0f ) * 0.1f ), 0.0f );
			glVertex3f( m_Pos.x - (float)( m_Width * i ),
						m_Pos.y + m_Height * (float)j,
						0.0f );

			// 描画処理 終了
			glEnd();

			// １桁毎にカウントを初期化する
			nRankingCnt = nRankingCnt * 0.1f;
		}
	}	// ランキングの描画終了

	glBindTexture(GL_TEXTURE_2D, 0);

	// プレイヤー番号のUV値と頂点座標の設定
	for( int nCntPlayerRank = 0; nCntPlayerRank < RANKING_ALL; nCntPlayerRank++ ) {

		// テクスチャをバインド
		glBindTexture( GL_TEXTURE_2D, m_PlayerRankTexIdx[ nCntPlayerRank ] );

		//	描画開始
		glBegin( GL_TRIANGLE_STRIP );

		//	色設定
		glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );

		//	頂点座標設定
		glTexCoord2d( 0.0f, 1.0f );
		glVertex3f( m_Pos.x - ( m_Width * 0.5f ) -370, m_Pos.y + ( m_Height * 0.3f ) + ( 90 * nCntPlayerRank ) +60, 0.0f );
	
		glTexCoord2d( 1.0f, 1.0f );
		glVertex3f( m_Pos.x + ( m_Width * 0.5f ) -370, m_Pos.y + ( m_Height * 0.3f ) + ( 90 * nCntPlayerRank ) +60, 0.0f );
	
		glTexCoord2d( 0.0f, 0.0f );
		glVertex3f( m_Pos.x - ( m_Width * 0.5f ) -370, m_Pos.y - ( m_Height * 0.3f ) + ( 90 * nCntPlayerRank ) +60, 0.0f );
	
		glTexCoord2d( 1.0f, 0.0f );
		glVertex3f( m_Pos.x + ( m_Width * 0.5f ) -370, m_Pos.y - ( m_Height * 0.3f ) + ( 90 * nCntPlayerRank ) +60, 0.0f );

		//	描画終了
		glEnd();

	}

	glBindTexture(GL_TEXTURE_2D, 0);

	// プレイヤー番号 表示

	glEnable(GL_BLEND);
	glEnable(GL_LIGHTING);



	// テクスチャマッピング無効化
	glDisable(GL_TEXTURE_2D);

	// αテスト無効化
	glDisable(GL_ALPHA_TEST);

	//	ここからマトリックスを元に戻す//////////////////////////////
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	//	ここまでマトリックスを元に戻す//////////////////////////////
}

/******************************************************************************
== 関数名 ： int CRanking::Set ( int *RankingValue )
== 戻り値 ： void型
== 引数   ： *RankingValue
== 内容   ： ランキングの設置処理
******************************************************************************/
int CRanking::Set ( int *RankingValue )
{
	int RankNum = RANKING_ALL;	// ランキングの順位
	int Num;					// 確保する値

	// スコアが高い順に上へソートする
	for( int i = RANKING_ALL; i > 0; i-- ) {
		if( RankingValue[ i ] >= RankingValue[ i - 1 ] ) {
			Num = RankingValue[ i ];
			RankingValue[ i ] = RankingValue[ i - 1 ];
			RankingValue[ i - 1 ] = Num;
			RankNum--;
		} else {
			break;
		}
	}
	return RankNum;
}