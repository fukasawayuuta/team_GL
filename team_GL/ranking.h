/******************************************************************************
	タイトル名 : ranking
	ファイル名 : ranking.h
	作成者     : AT-13B-284 02 阿部隆
	作成日     : 2016/12/13
	更新日     : 
******************************************************************************/
/******************************************************************************
	インクルードガード
******************************************************************************/
#pragma once

/******************************************************************************
	インクルードファイル
******************************************************************************/
#include "scene.h"
#include "scene2D.h"
#include "texture.h"

/******************************************************************************
	マクロ定義
******************************************************************************/
const int RANKING_ALL = 4;				// スコアの桁数

/******************************************************************************
	型定義
******************************************************************************/

// ランキングクラス 設定
class CRanking : public CScene2D
{
	private:
		//LPDIRECT3DTEXTURE9		m_Texture;
		//LPDIRECT3DVERTEXBUFFER9 m_VtxBuff;
		//int m_RankNumColor;

		int	m_TexIdx;						// ランキングの画像データのワーク
		int m_nRanking[ RANKING_ALL + 1 ];	// ランキングの値
		int m_RankNum;
		int m_TimeCnt;						// 時間計測

		int m_PlayerRankTexIdx[ RANKING_ALL ];// プレイヤー番号の画像データのワーク

		float m_RankNumColor_a;

	public:
		CRanking( int Priority = PRIORITY_2D, OBJ_TYPE objType = OBJ_TYPE_NONE );
		~CRanking();
		void Init	( Vector2 pos, Vector2 rot, float width, float height, int index );
		void Update	( void );
		void Draw	( void );
		void Uninit	( void );

		int Set		( int *RankingValue );
		static CRanking *Create ( Vector2 pos, Vector2 rot, float width, float height, int index );
};