/******************************************************************************
	タイトル名 : titlemenu
	ファイル名 : titlemenu.h
	作成者     : AT-13B-284 02 阿部隆
	作成日     : 2016/11/02
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
const int FADETERM_TITLE_MENU = 60 * 1;	// 選択時の項目のフェード周期
const float FADETERM_MIN_SELECT = 0.7f;	// 選択時のフェード周期の最小値

/******************************************************************************
	型定義
******************************************************************************/
		// 各項目の種類の構造体
		typedef enum
		{
			TITLE_MENU_GAME = 0,	// ゲーム
			TITLE_MENU_TUTORIAL,	// チュートリアル
			TITLE_MENU_CREDIT,		// クレジット
			TITLE_MENU_GAME_EXIT,	// ゲーム終了
			TITLE_MENU_MAX			// この構造体の項目数 4
		} TITLE_MENU;
// タイトルメニュークラス
class CTitleMenu : CScene2D
{
	private:



		// 項目の構造体
		struct MENU
		{
			Vector2 pos;		// 項目の位置
			float	fWidth;		// 項目の幅
			float	fHeight;	// 項目の高さ
			float	alfa;		// 項目のα値
			bool	bUse;		// 項目のフラグ
		};

		MENU m_aTitleMenu[ TITLE_MENU_MAX ];// タイトルのメニューの種類
		static TITLE_MENU m_Menu;					// ポーズメニューのワーク

		int		m_TexIdx[ TITLE_MENU_MAX ];	// 各項目の画像データのワーク
		float	m_TimeCntSelect;			// セレクト時にタイムをカウント
		float	m_HeightChange;				// 項目の高さの間隔
		bool	m_bUse;						// タイトルメニュー全体のフラグ
		static bool bUse;					// ゲーム終了用 フラグ



	public:
		CTitleMenu( int Priority = PRIORITY_2D, OBJ_TYPE objType = OBJ_TYPE_NONE );
		~CTitleMenu();

		void Init		( Vector2 pos, Vector2 rot, float width, float height );
		void Uninit		( void );
		void Update		( void );
		void Draw		( void );

		static CTitleMenu *Create ( Vector2 pos, Vector2 rot, float width, float height );
		static bool Check	();
		static bool Get( TITLE_MENU State );
};

// =================================================================================== titleMenu.hの終了