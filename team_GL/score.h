/******************************************************************************
	タイトル名 : score
	ファイル名 : score.h
	作成者     : AT-13B-284 02 阿部隆
	作成日     : 2016/11/14
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
#include "texture.h"
#include "scene2D.h"

/******************************************************************************
	構造体宣言
******************************************************************************/
/******************************************************************************
	マクロ定義
******************************************************************************/
const int MAX_SCORE = 5;								/* スコアの最大表示数 */

/******************************************************************************
	Class宣言
******************************************************************************/
//class CScene2D;

class CScore : public CScene2D
{
		private:
			int		m_Number [ MAX_SCORE ];	/* スコアの表示数 */
			int		m_nScore;				/* スコアの得点数 */
			float	m_WidthChange;			/* スコアの幅の間隔 */

			Vector2 m_Pos;		//	座標。
			Vector2 m_Rot;		//	角度。
			float m_Width;		//	横幅。
			float m_Height;		//	縦幅。
			int m_nId;

		public:
			CScore(int Priority = PRIORITY_2D, OBJ_TYPE objType = OBJ_TYPE_NONE);
			~CScore();
			void Init		( Vector2 pos, Vector2 rot, float height, float width, int index, int id );
			void Uninit		( void );
			void Draw		( void );
			void Update		( void );
			void AddScore	( int value );	// スコア 加算関数
			int GetScore	( void );	// スコア 持ち込み関数
			static CScore* Create ( Vector2 pos, Vector2 rot, float height, float width, int index, int id );

};

//==================================================================================== score.hの終了