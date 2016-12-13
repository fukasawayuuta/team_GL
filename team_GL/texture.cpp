/*******************************************************************************
* �^�C�g�����F
* �t�@�C�����Ftexture.cpp
* �쐬��	�FAT13B284 10 ���}���[��
* �쐬��	�F
********************************************************************************
* �X�V����	�F
*
*******************************************************************************/
/*******************************************************************************
* scanf��warning�΍�
*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "main.h"
//#include "glpng.h"
#include "renderer.h"
#include "texture.h"

/*******************************************************************************
* �}�N����`
*******************************************************************************/

/*******************************************************************************
* �O���[�o���ϐ�
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
* �֐����FCTexture::CTexture()
* 
* ����	�F
* �߂�l�F
* ����	�F�R���X�g���N�^
*******************************************************************************/
CTexture::CTexture()
{
}

/*******************************************************************************
* �֐����FCTexture::~CTexture()
* 
* ����	�F
* �߂�l�F
* ����	�F�f�X�g���N�^
*******************************************************************************/
CTexture::~CTexture()
{
}

/*******************************************************************************
* �֐����Fvoid CTexture::Init( void )
* 
* ����	�F
* �߂�l�F
* ����	�F����������
*******************************************************************************/
void CTexture::Init( void )
{
}

/*******************************************************************************
* �֐����Fvoid CTexture::Uninit( void )
* 
* ����	�F
* �߂�l�F
* ����	�F�I������
*******************************************************************************/
void CTexture::Uninit( void )
{

}

/*******************************************************************************
* �֐����Fvoid CTexture::Draw( void )
* 
* ����	�F
* �߂�l�F
* ����	�F�������
*******************************************************************************/
void CTexture::Release( void )
{
	if( m_nTexIdx != NULL )
	{
		glDeleteTextures( 1, &m_nTexIdx );
	}
}

/*******************************************************************************
* �֐����Fvoid CTexture::Load( void )
* 
* ����	�F
* �߂�l�F
* ����	�F�e�N�X�`���ǂݍ��ݏ���
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
* �֐����Fvoid CTexture::Unload( void )
* 
* ����	�F
* �߂�l�F
* ����	�F�e�N�X�`���������
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
* �֐����Funsigned int CTexture::CreateTexture( char *FileName )
* 
* ����	�F
* �߂�l�F
* ����	�F�`�揈��
*******************************************************************************/
unsigned int CTexture::CreateTexture( char *FileName )
{
	unsigned char header[ 18 ];
	unsigned char *image;

	/* �t�@�C���ǂݍ��� */
	FILE *file = fopen( FileName , "rb" );

	fread( header, 1, sizeof( header ), file );

	// ���ƍ��������߂�
	m_nWidth = header[ 13 ] * 256 + header[ 12 ];
	m_nHeight = header[ 15 ] * 256 + header[ 14 ];

	image = new unsigned char[ m_nWidth * m_nHeight * 4 ];

	// �r�b�g�̐[��
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

	// �F���̎擾
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

	glGenTextures( 1, &m_nTexIdx );					/* ��̃e�N�X�`���̐��� */
	glBindTexture( GL_TEXTURE_2D, m_nTexIdx );		/* �e�N�X�`���I�u�W�F�N�g�̊��蓖�� */

	//�@
	if ( m_nBpp == 24 ) glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );
	else if ( m_nBpp == 32 ) glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

	// �e�N�X�`�����g��E�k��������@�̎w��
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

	/* �e�N�X�`���̊��蓖�� */
	glTexImage2D( GL_TEXTURE_2D,
					0,				// �~�b�v�}�b�v
					m_Format,
					m_nWidth,		// ��
					m_nHeight,		// ����
					0,				// border
					m_Format,
					GL_UNSIGNED_BYTE,
					image );


	glBindTexture( GL_TEXTURE_2D, 0 );			/* �e�N�X�`���I�u�W�F�N�g�̊��蓖�� */

	delete[] image;

	return m_nTexIdx;
}

/*******************************************************************************
* �֐����Funsigned int CTexture::CreateTexture( char *FileName )
* 
* ����	�F
* �߂�l�F
* ����	�F�`�揈��
*******************************************************************************/
unsigned int CTexture::CreateTextureInverse( char *FileName )
{
	unsigned char header[ 18 ];
	unsigned char *image;

	/* �t�@�C���ǂݍ��� */
	FILE *file = fopen( FileName , "rb" );

	fread( header, 1, sizeof( header ), file );

	// ���ƍ��������߂�
	m_nWidth = header[ 13 ] * 256 + header[ 12 ];
	m_nHeight = header[ 15 ] * 256 + header[ 14 ];

	image = new unsigned char[ m_nWidth * m_nHeight * 4 ];

	// �r�b�g�̐[��
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

	// �F���̎擾
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

	glGenTextures( 1, &m_nTexIdx );					/* ��̃e�N�X�`���̐��� */
	glBindTexture( GL_TEXTURE_2D, m_nTexIdx );		/* �e�N�X�`���I�u�W�F�N�g�̊��蓖�� */

	//�@
	if ( m_nBpp == 24 ) glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );
	else if ( m_nBpp == 32 ) glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

	// �e�N�X�`�����g��E�k��������@�̎w��
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

	/* �e�N�X�`���̊��蓖�� */
	glTexImage2D( GL_TEXTURE_2D,
					0,				// �~�b�v�}�b�v
					m_Format,
					m_nWidth,		// ��
					m_nHeight,		// ����
					0,				// border
					m_Format,
					GL_UNSIGNED_BYTE,
					image );


	glBindTexture( GL_TEXTURE_2D, 0 );			/* �e�N�X�`���I�u�W�F�N�g�̊��蓖�� */

	delete[] image;

	return m_nTexIdx;
}

/*******************************************************************************
* �֐����Funsigned int CTexture::CreateTexture( char *FileName )
* 
* ����	�F
* �߂�l�F
* ����	�F�`�揈��
*******************************************************************************/
unsigned int CTexture::CreateTextureBMP( char *FileName )
{
	unsigned char header[ 54 ];
	unsigned char *image;

	int headerSize = 0;

	/* �t�@�C���ǂݍ��� */
	FILE *file = fopen( FileName , "rb" );

	fread( header, 1, sizeof( header ), file );

	// ���ƍ��������߂�
	m_nWidth = header[ 19 ] * 256 + header[ 18 ];
	m_nHeight = header[ 23 ] * 256 + header[ 22 ];

	// �r�b�g�̐[��
	m_nBpp = header[ 28 ];

	if( m_nBpp != 24 )
	{
		//MessageBox( "BMP��24bit�ł͂���܂���I" );
		return 0;
	}

	headerSize = header[ 10 ];

	image = new unsigned char[ m_nWidth * m_nHeight * 3 ];

	fseek( file, headerSize, SEEK_SET );

	// �F���̎擾
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

	glGenTextures( 1, &m_nTexIdx );				/* ��̃e�N�X�`���̐��� */
	glBindTexture( GL_TEXTURE_2D, m_nTexIdx );		/* �e�N�X�`���I�u�W�F�N�g�̊��蓖�� */

	glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );

	// �e�N�X�`�����g��E�k��������@�̎w��
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

	/* �e�N�X�`���̊��蓖�� */
	glTexImage2D( GL_TEXTURE_2D,
					0,				// �~�b�v�}�b�v
					GL_RGB,
					m_nWidth,		// ��
					m_nHeight,		// ����
					0,				// border
					GL_RGB,
					GL_UNSIGNED_BYTE,
					image );


	glBindTexture( GL_TEXTURE_2D, 0 );			/* �e�N�X�`���I�u�W�F�N�g�̊��蓖�� */

	delete[] image;

	return m_nTexIdx;
}
