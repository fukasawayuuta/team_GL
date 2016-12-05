/*******************************************************************************
* タイトル名：
* ファイル名：gamebackground.cpp
* 作成者	：AT13B284 31 中山和馬
* 作成日	：2016/11/28
********************************************************************************
* 更新履歴	：
*
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "scene3D.h"
#include "texture.h"
#include "gamebackground.h"

/*******************************************************************************
* 関数名：CGameBackground::CGameBackground()
*
* 引数	：
* 戻り値：
* 説明	：コンストラクタ
*******************************************************************************/
CGameBackground::CGameBackground(int Priority, OBJ_TYPE objType) : CScene3D(Priority, objType)
{
}

/*******************************************************************************
* 関数名：CGameBackground::~CGameBackground()
*
* 引数	：
* 戻り値：
* 説明	：デストラクタ
*******************************************************************************/
CGameBackground::~CGameBackground()
{
}

/*******************************************************************************
* 関数名：void CGameBackground::Init(void)
*
* 引数	：
* 戻り値：
* 説明	：初期化処理
*******************************************************************************/
void CGameBackground::Init(void)
{
	m_Pos = Vector3( 0.0f, 0.0f, -0.1f );
	m_Rot = Vector3( 0.0f, 0.0f, 0.0f );
	m_Scl = Vector3( 1.0f, 1.0f, 1.0f );
	m_TextureIndex = CTexture::SetTexture( TEXTURE_TYPE_GAME_BG );
	m_Width = SCREEN_WIDTH;
	m_Height = SCREEN_HEIGHT;
	m_Depth = 0.0f;
}

/*******************************************************************************
* 関数名：void CGameBackground::Uninit(void)
*
* 引数	：
* 戻り値：
* 説明	：終了処理
*******************************************************************************/
void CGameBackground::Uninit(void)
{

}

/*******************************************************************************
* 関数名：void CGameBackground::Update(void)
*
* 引数	：
* 戻り値：
* 説明	：更新処理
*******************************************************************************/
void CGameBackground::Update(void)
{
	
}

/*******************************************************************************
* 関数名：void CGameBackground::Draw(void)
*
* 引数	：
* 戻り値：
* 説明	：描画処理
*******************************************************************************/
void CGameBackground::Draw(void)
{
	glDisable(GL_LIGHTING);
	//	ここからモデルビューマトリクスの設定////////////////////////
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//	ここまでモデルビューマトリクスの設定////////////////////////

	glScalef(m_Scl.x, m_Scl.y, m_Scl.z);
	glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
	glRotatef(m_Rot.y, 0.0f ,1.0f, 0.0f);

	//　テクスチャマッピング有効化
    glEnable(GL_TEXTURE_2D);
    //　テクスチャをバインド
    glBindTexture(GL_TEXTURE_2D, m_TextureIndex);

	
	//	描画開始
	glBegin(GL_TRIANGLE_STRIP);

	//	色設定
	glColor4f(1 , 1 , 1, 1);

	//	法線設定
	glNormal3f(0, 1, 0);

	//	頂点座標設定
	glTexCoord2d(0.0, 0.0);
    glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), m_Pos.z);

	glTexCoord2d(0.0, 1.0);
    glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), m_Pos.z);

	glTexCoord2d(1.0, 0.0);
    glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), m_Pos.z);

	glTexCoord2d(1.0, 1.0);
    glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), m_Pos.z);

	glEnd();
	//	描画終了

	glEnable(GL_LIGHTING);

	 glBindTexture(GL_TEXTURE_2D, 0);
    //　テクスチャマッピング無効化
    glDisable(GL_TEXTURE_2D);

	//	ここからマトリックスを元に戻す//////////////////////////////
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	//	ここまでマトリックスを元に戻す//////////////////////////////
}

/*******************************************************************************
* 関数名：CGameBackground *Create( void )
*
* 引数	：
* 戻り値：
* 説明	：
*******************************************************************************/
CGameBackground *CGameBackground::Create( void )
{
	CGameBackground *pBg = new CGameBackground;
	pBg->Init();
	return pBg ;
}