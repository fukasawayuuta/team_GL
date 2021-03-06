/*******************************************************************************
* タイトル名：
* ファイル名：titlemenu.cpp
* 作成者	：AT13B284 02 阿部隆
* 作成日	：2016/11/30
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
#include "input.h"
#include "fade.h"

#include "titlemenu.h"
#include "tutorial.h"
#include "credit.h"



//=============================================================================
//	関数名 : CTitleMenu::CTitleMenu()
//	説明   : コンストラクタ
//			 値のデフォルト化
//=============================================================================
CTitleMenu::CTitleMenu ( int Priority, OBJ_TYPE objType )
{
	m_HeightChange = 70.0f;
	m_Menu = TITLE_MENU_GAME;
}

//=============================================================================
//	関数名 : CTitleMenu::CTitleMenu()
//	説明   : デストラクタ
//=============================================================================
CTitleMenu::~CTitleMenu ()
{
}

bool CTitleMenu::bUse = false;
TITLE_MENU  CTitleMenu::m_Menu;

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
	関数名 : void CTitleMenu::Init ( Vector2 pos, Vector2 rot, float width, float height )
	引数   : void型
	戻り値 : pos, rot, width, height
	説明   : タイトルメニューの初期化処理
******************************************************************************/
void CTitleMenu::Init ( Vector2 pos, Vector2 rot, float width, float height )
{
	// 引数値を代入
	m_Pos		= pos;
	m_Rot		= rot;
	m_Width		= width;
	m_Height	= height;

	// フラグon
	// m_bUse = true;

	// セレクト時のタイムの計測
	m_TimeCntSelect = 0;

	// 各項目の構造体の初期化
	for( int CntTitleMenu = 0; CntTitleMenu < TITLE_MENU_MAX; CntTitleMenu++ ) {
		m_aTitleMenu[ CntTitleMenu ].pos		= Vector2( 0.0f, 0.0f );
		m_aTitleMenu[ CntTitleMenu ].fWidth		= 0.0f;
		m_aTitleMenu[ CntTitleMenu ].fHeight	= m_Height;
		m_aTitleMenu[ CntTitleMenu ].bUse		= false;
		m_aTitleMenu[ CntTitleMenu ].alfa		= 0.2f;
	}
	// ゲーム項目のみ フラグon
	m_aTitleMenu[ TITLE_MENU_GAME ].bUse = true;

	// テクスチャを読み込み、生成する
	m_TexIdx[ 0 ] = CTexture::SetTexture( TEXTURE_TYPE_TITLE_MENU_GAME );
	m_TexIdx[ 1 ] = CTexture::SetTexture( TEXTURE_TYPE_TITLE_MENU_TUTORIAL );
	m_TexIdx[ 2 ] = CTexture::SetTexture( TEXTURE_TYPE_TITLE_MENU_CREDIT );
	m_TexIdx[ 3 ] = CTexture::SetTexture( TEXTURE_TYPE_TITLE_MENU_GAME_EXIT );

} // InitTitleMenu関数の終了

/******************************************************************************
== 関数名 ： void CTitleMenu::Uninit ( void )
== 戻り値 ： void型
== 引数   ： void
== 内容   ： タイトルメニューの終了処理
******************************************************************************/
void CTitleMenu::Uninit ( void )
{
}

/******************************************************************************
== 関数名 ： void CTitleMenu::Update ( void )
== 戻り値 ： void型
== 引数   ： void
== 内容   ： タイトルメニューの更新処理
******************************************************************************/
void CTitleMenu::Update ( void )
{

	// タイトルメニュー 使用時
	if( CFade::Get( FADE_NONE ) ) {
		// フラグ on
		if( m_bUse ) {
			// 上 セレクト時
			if( CInput::GetKeyboardTrigger( DIK_UP ) ) {
				// α値を初期に戻す
				m_TimeCntSelect = 0;
				// 各項目から上セレクト時の処理
				switch( m_Menu ) {

					case TITLE_MENU_GAME:
						m_Menu = TITLE_MENU_GAME;
						//m_aTitleMenu[ TITLE_MENU_GAME ].bUse = true;
						//m_aTitleMenu[ TITLE_MENU_TUTORIAL ].bUse = false;	// チュートリアル
						//m_aTitleMenu[ TITLE_MENU_CREDIT ].bUse = false;		// クレジット
						//m_aTitleMenu[ TITLE_MENU_GAME_EXIT ].bUse = false;	// ゲーム 終了
						break;

					case TITLE_MENU_TUTORIAL:
						m_Menu = TITLE_MENU_GAME;
						m_aTitleMenu[ TITLE_MENU_GAME ].bUse = true;
						m_aTitleMenu[ TITLE_MENU_TUTORIAL ].bUse = false;	// チュートリアル
						m_aTitleMenu[ TITLE_MENU_CREDIT ].bUse = false;		// クレジット
						m_aTitleMenu[ TITLE_MENU_GAME_EXIT ].bUse = false;	// ゲーム 終了
						break;

					case TITLE_MENU_CREDIT:
						m_Menu = TITLE_MENU_TUTORIAL;
						m_aTitleMenu[ TITLE_MENU_GAME ].bUse = false;
						m_aTitleMenu[ TITLE_MENU_TUTORIAL ].bUse = true;	// チュートリアル
						m_aTitleMenu[ TITLE_MENU_CREDIT ].bUse = false;		// クレジット
						m_aTitleMenu[ TITLE_MENU_GAME_EXIT ].bUse = false;	// ゲーム 終了
						break;

					case TITLE_MENU_GAME_EXIT:
						m_Menu = TITLE_MENU_CREDIT;
						m_aTitleMenu[ TITLE_MENU_GAME ].bUse = false;
						m_aTitleMenu[ TITLE_MENU_TUTORIAL ].bUse = false;	// チュートリアル
						m_aTitleMenu[ TITLE_MENU_CREDIT ].bUse = true;		// クレジット
						m_aTitleMenu[ TITLE_MENU_GAME_EXIT ].bUse = false;	// ゲーム 終了
						break;

					default:
						break;
				}
			}

			// 下 セレクト時
			if( CInput::GetKeyboardTrigger( DIK_DOWN ) ) {
				// α値を初期に戻す
				m_TimeCntSelect = 0;
				// 各項目から下セレクト時の処理
				switch( m_Menu ) {

					case TITLE_MENU_GAME:
						m_Menu = TITLE_MENU_TUTORIAL;
						m_aTitleMenu[ TITLE_MENU_GAME ].bUse = false;
						m_aTitleMenu[ TITLE_MENU_TUTORIAL ].bUse = true;
						m_aTitleMenu[ TITLE_MENU_CREDIT ].bUse = false;		// クレジット
						m_aTitleMenu[ TITLE_MENU_GAME_EXIT ].bUse = false;	// ゲーム 終了
						break;

					case TITLE_MENU_TUTORIAL:
						m_Menu = TITLE_MENU_CREDIT;
						m_aTitleMenu[ TITLE_MENU_GAME ].bUse = false;
						m_aTitleMenu[ TITLE_MENU_TUTORIAL ].bUse = false;
						m_aTitleMenu[ TITLE_MENU_CREDIT ].bUse = true;		// クレジット
						m_aTitleMenu[ TITLE_MENU_GAME_EXIT ].bUse = false;	// ゲーム 終了
						break;

					case TITLE_MENU_CREDIT:
						m_Menu = TITLE_MENU_GAME_EXIT;
						m_aTitleMenu[ TITLE_MENU_GAME ].bUse = false;
						m_aTitleMenu[ TITLE_MENU_TUTORIAL ].bUse = false;
						m_aTitleMenu[ TITLE_MENU_CREDIT ].bUse = false;		// クレジット
						m_aTitleMenu[ TITLE_MENU_GAME_EXIT ].bUse = true;	// ゲーム 終了
						break;


					case TITLE_MENU_GAME_EXIT:
						m_Menu = TITLE_MENU_GAME_EXIT;
						//m_aTitleMenu[ TITLE_MENU_GAME ].bUse = false;
						//m_aTitleMenu[ TITLE_MENU_TUTORIAL ].bUse = false;
						//m_aTitleMenu[ TITLE_MENU_CREDIT ].bUse = false;		// クレジット
						//m_aTitleMenu[ TITLE_MENU_GAME_EXIT ].bUse = true;	// ゲーム 終了
						break;

						default:
							break;
				}
			}
		}

		// 項目 決定時
		if( CInput::GetKeyboardTrigger( DIK_RETURN ) ) {
			// 各項目から決定時の処理
			switch( m_Menu ) {
				case TITLE_MENU_GAME:		// ゲームへ画面遷移
					CFade::Start( new CMatching );
					m_bUse = false;
					break;

				case TITLE_MENU_TUTORIAL:	// チュートリアルの画像を出す
					if( m_bUse ) {
						m_bUse = false;		// フラグ off
						CTutorial::Start();	// 画像 表示
					} else {
						m_bUse = true;		// フラグ on
						CTutorial::End();	// 画像 非表示
					}
					break;

				case TITLE_MENU_CREDIT:	// クレジットの画像を出す
					if( m_bUse ) {
						m_bUse = false;		// フラグ off
						CCredit::Start();	// 画像 表示
					} else {
						m_bUse = true;		// フラグ on
						CCredit::End();	// 画像 非表示
					}
					break;

				case TITLE_MENU_GAME_EXIT:	// ゲームを終了させる
					bUse = true;
					//if( m_bUse ) {
					//	m_bUse = false;		// フラグ off
					//	bUse = true;
					//} else {
					//	m_bUse = true;		// フラグ on
					//	bUse = false;
					//}
					break;

				default:
					break;
			}
		}
	}
	//if( ( m_bUse == false ) && ( m_Menu == TITLE_MENU_GAME_EXIT ) ) {
		//bUse = false;
	//}

	// 各項目の設定
	for( int nCntTitleMenu = 0; nCntTitleMenu < TITLE_MENU_MAX; nCntTitleMenu++ ) {
		// 選択時の項目の処理
		if( m_aTitleMenu[ nCntTitleMenu ].bUse ) {
			// α値を一定の周期( 0.7f ~ 1.0f )と間隔で変える
			m_TimeCntSelect++;
			m_aTitleMenu[ nCntTitleMenu ].alfa = ( cosf( PI / FADETERM_TITLE_MENU * m_TimeCntSelect ) + 1 ) / 2 + FADETERM_MIN_SELECT;
			// 項目が決定されたとき
			if( CFade::Get( FADE_OUT ) ) {
				m_aTitleMenu[ nCntTitleMenu ].alfa = ( cosf( PI / 2 * m_TimeCntSelect ) + 1 ) / 2 + FADETERM_MIN_SELECT;
			}
		}
		// 非選択時の項目の処理
		else {
			// α値を固定
			m_aTitleMenu[ nCntTitleMenu ].alfa = 0.0f;
		}
	}


} // UpdateTitleMenu関数の終了

/******************************************************************************
== 関数名 ： void CTitleMenu::Draw ( void )
== 戻り値 ： void型
== 引数   ： void
== 内容   ： タイトルメニューの描画処理
******************************************************************************/
void CTitleMenu::Draw ( void )
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
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// αテスト 有効化
	glAlphaFunc(GL_GEQUAL, 1.0f );
	glEnable(GL_ALPHA_TEST);

	// テクスチャマッピング有効化
	glEnable(GL_TEXTURE_2D);

	// UV値と頂点座標の設定 ( DirectX形式 )
	for( int CntTitleMenu = 0; CntTitleMenu < TITLE_MENU_MAX; CntTitleMenu++ ) {

		// テクスチャをバインド
		glBindTexture( GL_TEXTURE_2D, m_TexIdx[ CntTitleMenu ] );

		//	描画開始
		glBegin( GL_TRIANGLE_STRIP );

		//	色設定
		glColor4f( m_aTitleMenu[ CntTitleMenu ].alfa, 0.0f, 0.0f, 1.0f );

		//	頂点座標設定
		glTexCoord2d( 0.0f, 1.0f );
		glVertex3f( m_Pos.x - ( m_Width * 0.5f ), m_Pos.y + ( m_aTitleMenu[ CntTitleMenu ].fHeight * 0.5f ) + ( m_HeightChange * CntTitleMenu ), 0.0f );
	
		glTexCoord2d( 1.0f, 1.0f );
		glVertex3f( m_Pos.x + ( m_Width * 0.5f ), m_Pos.y + ( m_aTitleMenu[ CntTitleMenu ].fHeight * 0.5f ) + ( m_HeightChange * CntTitleMenu ), 0.0f );
	
		glTexCoord2d( 0.0f, 0.0f );
		glVertex3f( m_Pos.x - ( m_Width * 0.5f ), m_Pos.y - ( m_aTitleMenu[ CntTitleMenu ].fHeight * 0.5f ) + ( m_HeightChange * CntTitleMenu ), 0.0f );
	
		glTexCoord2d( 1.0f, 0.0f );
		glVertex3f( m_Pos.x + ( m_Width * 0.5f ), m_Pos.y - ( m_aTitleMenu[ CntTitleMenu ].fHeight * 0.5f ) + ( m_HeightChange * CntTitleMenu ), 0.0f );

		glEnd();
		//	描画終了
	}

	glEnable(GL_BLEND);
	glEnable(GL_LIGHTING);

	glBindTexture(GL_TEXTURE_2D, 0);

	// αテスト無効化
	glDisable(GL_ALPHA_TEST);

    //　テクスチャマッピング無効化
    glDisable(GL_TEXTURE_2D);

	//	ここからマトリックスを元に戻す//////////////////////////////
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	//	ここまでマトリックスを元に戻す//////////////////////////////

} // DrawTitleMenu関数の終了

/******************************************************************************
== 関数名 ： CTitleMenu* CTitleMenu::Create ( Vector2 pos, Vector2 rot, float width, float height )
== 戻り値 ： CTitleMenu型
== 引数   ： pos, rot, width, height
== 内容   ： タイトルメニューの生成設定
******************************************************************************/
CTitleMenu *CTitleMenu::Create ( Vector2 pos, Vector2 rot, float width, float height )
{
	CTitleMenu *titleMenu;

	titleMenu = new CTitleMenu;
	titleMenu -> Init( pos, rot, width, height );

	return titleMenu;
}


/*******************************************************************************
* 関数名：bool CTitleMenu::Check ()
*
* 引数	：
* 戻り値：
* 説明	：windowsで終了させる為のフラグ管理
*******************************************************************************/
bool CTitleMenu::Check ()
{
	return ( bUse ) ? true:false;
	if( bUse ) {
		bUse = false;
	}
}

/*******************************************************************************
* 関数名：void CFade::Get ( FADE State )
*
* 引数	：
* 戻り値：
* 説明	：フェード無
*******************************************************************************/
bool CTitleMenu::Get ( TITLE_MENU menu )
{
	return ( m_Menu == menu ) ? true:false;
	//m_Menu = TITLE_MENU_GAME;
}