/*******************************************************************************
* タイトル名：
* ファイル名：texture.cpp
* 作成者	：AT13B284 10 小笠原啓太
* 作成日	：
********************************************************************************
* 更新履歴	：
*
*******************************************************************************/
/*******************************************************************************
* scanfのwarning対策
*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "main.h"
//#include "glpng.h"
#include "renderer.h"
#include "texture.h"

/*******************************************************************************
* マクロ定義
*******************************************************************************/

/*******************************************************************************
* グローバル変数
*******************************************************************************/
CTexture *CTexture::m_pTexture[TEXTURE_TYPE_MAX];
TEXTURE_PARAM CTexture::m_TexParam[TEXTURE_TYPE_MAX] = 
{
	{ "data\\TEXTURE\\teamlogo_test.tga" },				// TEXTURE_TYPE_TEAMLOGO
	{ "data\\TEXTURE\\title_background_test.tga" },		// TEXTURE_TYPE_TITLE_BG
	{ "data\\TEXTURE\\titlelogo_test.tga" },			// TEXTURE_TYPE_TITLE_LOGO
	{ "data\\TEXTURE\\titlemenu_game_test.tga" },		// TEXTURE_TYPE_TITLE_MENU_GAME
	{ "data\\TEXTURE\\titlemenu_tutorial_test.tga" },	// TEXTURE_TYPE_TITLE_MENU_TUTORIAL
	{ "data\\TEXTURE\\matching_test.tga" },				// TEXTURE_TYPE_MATCHING_BG
	{ "data\\TEXTURE\\background_test.tga" },			// TEXTURE_TYPE_GAME_BG
	{ "data\\TEXTURE\\number.tga" },					// TEXTURE_TYPE_NUMBER
	{ "data\\TEXTURE\\gauge_frame.tga" },				// TEXTURE_TYPE_GAUGE_FRAME
	{ "data\\TEXTURE\\gauge_red_in.tga" },				// TEXTURE_TYPE_GAUGE_IN
	{ "data\\TEXTURE\\player000.tga" },					// TEXTURE_TYPE_PLAYER000
	{ "data\\TEXTURE\\enemy_bat.tga" },					// TEXTURE_TYPE_ENEMY001
	{ "data\\TEXTURE\\dragon.tga" },					// TEXTURE_TYPE_BOSS
	{ "data\\TEXTURE\\block002.tga" },
	{ "data\\TEXTURE\\result_bg.tga" },					// TEXTURE_TYPE_RESULT_BG
	{ "data\\TEXTURE\\ranking.tga" },					// TEXTURE_TYPE_RESULT_LOGO
	{ "data\\TEXTURE\\1st.tga" },						// TEXTURE_TYPE_RANK_FIRST
	{ "data\\TEXTURE\\2nd.tga" },						// TEXTURE_TYPE_RANK_SECOND
	{ "data\\TEXTURE\\3rd.tga" },						// TEXTURE_TYPE_RANK_THIRD
	{ "data\\TEXTURE\\4th.tga" },						// TEXTURE_TYPE_RANK_FOURTH
};

/*******************************************************************************
* 関数名：CTexture::CTexture()
* 
* 引数	：
* 戻り値：
* 説明	：コンストラクタ
*******************************************************************************/
CTexture::CTexture()
{
}

/*******************************************************************************
* 関数名：CTexture::~CTexture()
* 
* 引数	：
* 戻り値：
* 説明	：デストラクタ
*******************************************************************************/
CTexture::~CTexture()
{
}

/*******************************************************************************
* 関数名：void CTexture::Init( void )
* 
* 引数	：
* 戻り値：
* 説明	：初期化処理
*******************************************************************************/
void CTexture::Init( void )
{
}

/*******************************************************************************
* 関数名：void CTexture::Uninit( void )
* 
* 引数	：
* 戻り値：
* 説明	：終了処理
*******************************************************************************/
void CTexture::Uninit( void )
{

}

/*******************************************************************************
* 関数名：void CTexture::Draw( void )
* 
* 引数	：
* 戻り値：
* 説明	：解放処理
*******************************************************************************/
void CTexture::Release( void )
{
	if( m_nTexIdx != NULL )
	{
		glDeleteTextures( 1, &m_nTexIdx );
	}
}

/*******************************************************************************
* 関数名：void CTexture::Load( void )
* 
* 引数	：
* 戻り値：
* 説明	：テクスチャ読み込み処理
*******************************************************************************/
void CTexture::Load( void )
{
	for(int i = 0; i < TEXTURE_TYPE_MAX; i++)
	{
		m_pTexture[i] = new CTexture;
		m_pTexture[i]->Init();
		m_pTexture[i]->CreateTexture(m_TexParam[i].texName);
	}
}

/*******************************************************************************
* 関数名：void CTexture::Unload( void )
* 
* 引数	：
* 戻り値：
* 説明	：テクスチャ解放処理
*******************************************************************************/
void CTexture::Unload( void )
{
	for(int i = 0; i < TEXTURE_TYPE_MAX; i++)
	{
		if(m_pTexture[i] != NULL)
		{
			m_pTexture[i]->Uninit();
			m_pTexture[i]->Release();
			delete m_pTexture[i];
			m_pTexture[i] = NULL;
		}
	}
}

/*******************************************************************************
* 関数名：unsigned int CTexture::CreateTexture( char *FileName )
* 
* 引数	：
* 戻り値：
* 説明	：描画処理
*******************************************************************************/
unsigned int CTexture::CreateTexture( char *FileName )
{
	unsigned char header[ 18 ];
	unsigned char *image;

	/* ファイル読み込み */
	FILE *file = fopen( FileName , "rb" );

	fread( header, 1, sizeof( header ), file );

	// 幅と高さを決める
	m_nWidth = header[ 13 ] * 256 + header[ 12 ];
	m_nHeight = header[ 15 ] * 256 + header[ 14 ];

	image = new unsigned char[ m_nWidth * m_nHeight * 4 ];

	// ビットの深さ
	m_nBpp = header[ 16 ];

	// 24 bit
	if ( m_nBpp == 24 )
	{
		m_Format = GL_RGB;
		m_nInternalFormat = GL_RGB;
	}
	// 32 bit
	else if ( m_nBpp = 32 )
	{
		m_Format = GL_RGBA;
		m_nInternalFormat = GL_RGBA;
	}

	m_nDiscrip = header[ 17 ];

	// 色情報の取得
	// 24 bit
	if ( m_nBpp == 24 )
	{
		for( int y = m_nHeight - 1; y >= 0; y-- )
		{
			for( int x = 0; x < m_nWidth; x++ )
			{
				image[ ( y * m_nWidth + x ) * 3 + 2 ] = fgetc( file );
				image[ ( y * m_nWidth + x ) * 3 + 1 ] = fgetc( file );
				image[ ( y * m_nWidth + x ) * 3 + 0 ] = fgetc( file );
			}
		}
	}

	// 32 bit
	if ( m_nBpp == 32 )
	{
		for( int y = m_nHeight - 1; y >= 0; y-- )
		{
			for( int x = 0; x < m_nWidth; x++ )
			{
				image[ ( y * m_nWidth + x ) * 4 + 2 ] = fgetc( file );
				image[ ( y * m_nWidth + x ) * 4 + 1 ] = fgetc( file );
				image[ ( y * m_nWidth + x ) * 4 + 0 ] = fgetc( file );
				image[ ( y * m_nWidth + x ) * 4 + 3 ] = fgetc( file );
			}
		}
	}

	fclose( file );

	glGenTextures( 1, &m_nTexIdx );					/* 空のテクスチャの生成 */
	glBindTexture( GL_TEXTURE_2D, m_nTexIdx );		/* テクスチャオブジェクトの割り当て */

	//　
	if ( m_nBpp == 24 ) glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );
	else if ( m_nBpp == 32 ) glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

	// テクスチャを拡大・縮小する方法の指定
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

	/* テクスチャの割り当て */
	glTexImage2D( GL_TEXTURE_2D,
					0,				// ミップマップ
					m_Format,
					m_nWidth,		// 幅
					m_nHeight,		// 高さ
					0,				// border
					m_Format,
					GL_UNSIGNED_BYTE,
					image );


	glBindTexture( GL_TEXTURE_2D, 0 );			/* テクスチャオブジェクトの割り当て */

	delete[] image;

	return m_nTexIdx;
}

/*******************************************************************************
* 関数名：unsigned int CTexture::CreateTexture( char *FileName )
* 
* 引数	：
* 戻り値：
* 説明	：描画処理
*******************************************************************************/
unsigned int CTexture::CreateTextureInverse( char *FileName )
{
	unsigned char header[ 18 ];
	unsigned char *image;

	/* ファイル読み込み */
	FILE *file = fopen( FileName , "rb" );

	fread( header, 1, sizeof( header ), file );

	// 幅と高さを決める
	m_nWidth = header[ 13 ] * 256 + header[ 12 ];
	m_nHeight = header[ 15 ] * 256 + header[ 14 ];

	image = new unsigned char[ m_nWidth * m_nHeight * 4 ];

	// ビットの深さ
	m_nBpp = header[ 16 ];

	// 24 bit
	if ( m_nBpp == 24 )
	{
		m_Format = GL_RGB;
		m_nInternalFormat = GL_RGB;
	}
	// 32 bit
	else if ( m_nBpp = 32 )
	{
		m_Format = GL_RGBA;
		m_nInternalFormat = GL_RGBA;
	}

	m_nDiscrip = header[ 17 ];

	// 色情報の取得
	// 24 bit
	if ( m_nBpp == 24 )
	{
		for( int y = 0; y < m_nHeight; y++ )
		{
			for( int x = 0; x < m_nWidth; x++ )
			{
				image[ ( y * m_nWidth + x ) * 3 + 2 ] = fgetc( file );
				image[ ( y * m_nWidth + x ) * 3 + 1 ] = fgetc( file );
				image[ ( y * m_nWidth + x ) * 3 + 0 ] = fgetc( file );
			}
		}
	}

	// 32 bit
	if ( m_nBpp == 32 )
	{
		for( int y = 0; y < m_nHeight; y++ )
		{
			for( int x = 0; x < m_nWidth; x++ )
			{
				image[ ( y * m_nWidth + x ) * 4 + 2 ] = fgetc( file );
				image[ ( y * m_nWidth + x ) * 4 + 1 ] = fgetc( file );
				image[ ( y * m_nWidth + x ) * 4 + 0 ] = fgetc( file );
				image[ ( y * m_nWidth + x ) * 4 + 3 ] = fgetc( file );
			}
		}
	}

	fclose( file );

	glGenTextures( 1, &m_nTexIdx );					/* 空のテクスチャの生成 */
	glBindTexture( GL_TEXTURE_2D, m_nTexIdx );		/* テクスチャオブジェクトの割り当て */

	//　
	if ( m_nBpp == 24 ) glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );
	else if ( m_nBpp == 32 ) glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

	// テクスチャを拡大・縮小する方法の指定
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

	/* テクスチャの割り当て */
	glTexImage2D( GL_TEXTURE_2D,
					0,				// ミップマップ
					m_Format,
					m_nWidth,		// 幅
					m_nHeight,		// 高さ
					0,				// border
					m_Format,
					GL_UNSIGNED_BYTE,
					image );


	glBindTexture( GL_TEXTURE_2D, 0 );			/* テクスチャオブジェクトの割り当て */

	delete[] image;

	return m_nTexIdx;
}

/*******************************************************************************
* 関数名：unsigned int CTexture::CreateTexture( char *FileName )
* 
* 引数	：
* 戻り値：
* 説明	：描画処理
*******************************************************************************/
unsigned int CTexture::CreateTextureBMP( char *FileName )
{
	unsigned char header[ 54 ];
	unsigned char *image;

	int headerSize = 0;

	/* ファイル読み込み */
	FILE *file = fopen( FileName , "rb" );

	fread( header, 1, sizeof( header ), file );

	// 幅と高さを決める
	m_nWidth = header[ 19 ] * 256 + header[ 18 ];
	m_nHeight = header[ 23 ] * 256 + header[ 22 ];

	// ビットの深さ
	m_nBpp = header[ 28 ];

	if( m_nBpp != 24 )
	{
		//MessageBox( "BMPが24bitではありません！" );
		return 0;
	}

	headerSize = header[ 10 ];

	image = new unsigned char[ m_nWidth * m_nHeight * 3 ];

	fseek( file, headerSize, SEEK_SET );

	// 色情報の取得
	for( int y = m_nHeight - 1; y >= 0; y-- )
	{
		for( int x = 0; x < m_nWidth; x++ )
		{
			image[ ( y * m_nWidth + x ) * 3 + 2 ] = fgetc( file );
			image[ ( y * m_nWidth + x ) * 3 + 1 ] = fgetc( file );
			image[ ( y * m_nWidth + x ) * 3 + 0 ] = fgetc( file );
		}
	}

	fclose( file );

	glGenTextures( 1, &m_nTexIdx );				/* 空のテクスチャの生成 */
	glBindTexture( GL_TEXTURE_2D, m_nTexIdx );		/* テクスチャオブジェクトの割り当て */

	glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );

	// テクスチャを拡大・縮小する方法の指定
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

	/* テクスチャの割り当て */
	glTexImage2D( GL_TEXTURE_2D,
					0,				// ミップマップ
					GL_RGB,
					m_nWidth,		// 幅
					m_nHeight,		// 高さ
					0,				// border
					GL_RGB,
					GL_UNSIGNED_BYTE,
					image );


	glBindTexture( GL_TEXTURE_2D, 0 );			/* テクスチャオブジェクトの割り当て */

	delete[] image;

	return m_nTexIdx;
}
