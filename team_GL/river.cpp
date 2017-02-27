/*******************************************************************************
* タイトル名：
* ファイル名：river.cpp
* 作成者	：AT13B284 02 阿部隆
* 作成日	：2017/02/08
********************************************************************************
* 更新履歴	：
*
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "main.h"
#include "manager.h"

#include "river.h"

//=============================================================================
//	関数名 : CRiver::CRiver()
//	説明   : コンストラクタ
//=============================================================================
CRiver::CRiver( int Priority, OBJ_TYPE objType )
{
}

//=============================================================================
//	関数名 : CRiver::~CRiver()
//	説明   : デストラクタ
//=============================================================================
CRiver::~CRiver()
{
}

/*******************************************************************************
* 関数名：void CRiver::Init ( void )
*
* 引数	：
* 戻り値：
* 説明	：初期化処理
*******************************************************************************/
void CRiver::Init ( void )
{
	m_Pos = Vector2( SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.91f );
	m_Rot = Vector2( 0.0f, 0.0f );
	m_nTexIdx = CTexture::SetTexture( TEXTURE_TYPE_TITLE_RIVER );
	m_Width = SCREEN_WIDTH;
	m_Height = SCREEN_HEIGHT * 0.17f;
	m_Tex = 0.0f;
}

/*******************************************************************************
* 関数名：void CRiver::Uninit(void)
*
* 引数	：
* 戻り値：
* 説明	：終了処理
*******************************************************************************/
void CRiver::Uninit ( void )
{
}

/*******************************************************************************
* 関数名：void CRiver::Update ( void )
*
* 引数	：
* 戻り値：
* 説明	：更新処理
*******************************************************************************/
void CRiver::Update ( void )
{
	m_Tex += 0.0003f;
}

/*******************************************************************************
* 関数名：void CRiver::Draw ( void )
*
* 引数	：
* 戻り値：
* 説明	：描画処理
*******************************************************************************/
void CRiver::Draw ( void )
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

	glTexCoord2d(0.0 + m_Tex, 1.0);
    glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), -0.998f );

	glTexCoord2d(1.0 + m_Tex, 1.0);
    glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), -0.998f );

	glTexCoord2d(0.0 + m_Tex, 0.0);
    glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), -0.998f );

	glTexCoord2d(1.0 + m_Tex, 0.0);
    glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), -0.998f );

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
* 関数名：CRiver *Create( void )
*
* 引数	：
* 戻り値：
* 説明	：
*******************************************************************************/
CRiver *CRiver::Create( void )
{
	CRiver *pBg = new CRiver;
	pBg->Init();
	return pBg ;
}