/*******************************************************************************
* タイトル名：
* ファイル名：titlebackground.cpp
* 作成者	：AT13B284 02 阿部隆
* 作成日	：2016/12/05
********************************************************************************
* 更新履歴	：
*
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "main.h"
#include "manager.h"

#include "titlebackground.h"

//=============================================================================
//	関数名 : CTitleBackground::CTitleBackground()
//	説明   : コンストラクタ
//=============================================================================
CTitleBackground::CTitleBackground( int Priority, OBJ_TYPE objType )
{
}

//=============================================================================
//	関数名 : CTitleBackground::~CTitleBackground()
//	説明   : デストラクタ
//=============================================================================
CTitleBackground::~CTitleBackground()
{
}

/*******************************************************************************
* 関数名：void CTitleBackground::Init ( void )
*
* 引数	：
* 戻り値：
* 説明	：初期化処理
*******************************************************************************/
void CTitleBackground::Init ( void )
{
	m_Pos = Vector2( SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f );
	m_Rot = Vector2( 0.0f, 0.0f );
	m_nTexIdx = CTexture::SetTexture( TEXTURE_TYPE_TITLE_BG );
	m_Width = SCREEN_WIDTH;
	m_Height = SCREEN_HEIGHT;
}

/*******************************************************************************
* 関数名：void CTitleBackground::Uninit(void)
*
* 引数	：
* 戻り値：
* 説明	：終了処理
*******************************************************************************/
void CTitleBackground::Uninit ( void )
{
}

/*******************************************************************************
* 関数名：void CTitleBackground::Update ( void )
*
* 引数	：
* 戻り値：
* 説明	：更新処理
*******************************************************************************/
void CTitleBackground::Update ( void )
{
}

/*******************************************************************************
* 関数名：void CTitleBackground::Draw ( void )
*
* 引数	：
* 戻り値：
* 説明	：描画処理
*******************************************************************************/
void CTitleBackground::Draw ( void )
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

	//	頂点座標設定
	//glTexCoord2d(0.0, 0.0);
 //   glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), 0.0f );

	//glTexCoord2d(1.0, 0.0);
 //   glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), 0.0f );

	//glTexCoord2d(0.0, 1.0);
 //   glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), 0.0f );

	//glTexCoord2d(1.0, 1.0);
 //   glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), 0.0f );

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

/*******************************************************************************
* 関数名：CTitleBackground *Create( void )
*
* 引数	：
* 戻り値：
* 説明	：
*******************************************************************************/
CTitleBackground *CTitleBackground::Create( void )
{
	CTitleBackground *pBg = new CTitleBackground;
	pBg->Init();
	return pBg ;
}