/******************************************************************************
	�^�C�g���� : �X�R�A�N���X
	�t�@�C���� : score.cpp
	�쐬��     : AT-13B-284 02 ������
	�쐬��     : 2016/11/17
	�X�V��     : 
******************************************************************************/
/******************************************************************************
	�C���N���[�h�t�@�C��
******************************************************************************/
//#include "main.h"
//#include "manager.h"
//#include "rerender.h"
//
//#include "score.h"
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "scene2D.h"

#include "score.h"

/******************************************************************************
	�}�N����`
******************************************************************************/
/******************************************************************************
	�^��`
******************************************************************************/
/******************************************************************************
	�v���g�^�C�v�錾
******************************************************************************/
/******************************************************************************
	�O���[�o���ϐ�
******************************************************************************/
//	�ÓI�����o�ϐ��錾/////////////////////////////////////////////////////////
CTGAImage *m_ScoreImage;

Vector2 CScore::m_Pos;	//	���W�B
Vector2 CScore::m_Rot;	//	�p�x�B
float CScore::m_Width;	//	�����B
float CScore::m_Height;	//	�c���B

//=============================================================================
//	�֐��� : CScore::CScore()
//	����   : �R���X�g���N�^
//			 �l�̃f�t�H���g��
//=============================================================================
CScore::CScore()
{
	m_TexIndex		= 0;
	m_nScore		= 0;
	m_WidthChange	= 0;
}

//=============================================================================
//	�֐��� : CScore::~CScore()
//	����   : �f�X�g���N�^
//=============================================================================
CScore::~CScore()
{
}

/******************************************************************************
	�֐��� : CScore *CScore::Create ( Vector2 pos, Vector2 rot, float width, float height, char* fileName )
	����   : pos, rot, width, height, fileName
	�߂�l : �Ȃ�
	����   : �X�R�A�̐�������
******************************************************************************/
CScore *CScore::Create ( Vector2 pos, Vector2 rot, float width, float height, char* fileName )
{
	CScore *score;

	score = new CScore;
	score -> Init( pos, rot, width, height, fileName );

	return score;
}

/******************************************************************************
	�֐��� : void CScore::Init ( Vector2 pos, Vector2 rot, float width, float height, char* fileName )
	����   : pos, rot, width, height, fileName
	�߂�l : �Ȃ�
	����   : �X�R�A�̏���������
******************************************************************************/
void CScore::Init ( Vector2 pos, Vector2 rot, float width, float height, char* fileName )
{
	// �����l����
	m_Pos		= pos;
	m_Rot		= rot;
	m_Width		= width;
	m_Height	= height;

	// �e�N�X�`����ǂݍ��݁A��������
	m_TexIndex = m_ScoreImage -> CreateTexture( fileName );
}


/******************************************************************************
	�֐��� : void CScore::Uninit ( void )
	����   : void
	�߂�l : �Ȃ�
	����   : �X�R�A�̏I������
******************************************************************************/
void CScore::Uninit ( void )
{
	if( m_TexIndex ) {
		m_TexIndex = NULL;
	}
}


/******************************************************************************
	�֐��� : void CScore::Update ( void )
	����   : void
	�߂�l : �Ȃ�
	����   : �X�R�A�̍X�V����
******************************************************************************/
void CScore::Update ( void )
{
	// �X�R�A�̍X�V����
	m_Number[ 0 ] = m_nScore / 10000 % 10;
	m_Number[ 1 ] = m_nScore / 1000 % 10;
	m_Number[ 2 ] = m_nScore / 100 % 10;
	m_Number[ 3 ] = m_nScore / 10 % 10;
	m_Number[ 4 ] = m_nScore / 1 % 10;

	// �X�R�A�̓���m�F�֐�( +1�����Z���� )
	AddScore(1);

}

/******************************************************************************
	�֐��� : void CScore::Draw ( void )
	����   : void
	�߂�l : �Ȃ�
	����   : �X�R�A�̕`�揈��
******************************************************************************/
void CScore::Draw ( void )
{
	// �`��J�n
	//CScene2D::DrawBegin();

	// �e�N�X�`���}�b�s���O��L����
	glEnable( GL_TEXTURE_2D );

///////////////////////////////////////

	// �A���t�@�u�����h��L����
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glEnable( GL_BLEND );

	// �e�N�X�`�����o�C���h����
	glBindTexture( GL_TEXTURE_2D, m_TexIndex );

	// �}�g���N�X�ݒ�
	glMatrixMode(GL_PROJECTION);

	glPushMatrix();
	// �P�ʍs��
	glLoadIdentity();

	// ���ˉe �ݒ�
	glOrtho( 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 1 );

	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();

	// �`��̊J�n
	glBegin(GL_TRIANGLE_STRIP);

	// RGB�l
	glColor4f( 1.0f, 1.0f, 1.0f, 1.0f);

	// UV�l�ƒ��_���W�̐ݒ� ( DirectX�`�� )
	for( int CntScore = 0; CntScore < MAX_SCORE; CntScore++ ) {
		// [ 0 ]
		glTexCoord2d( 0.1f * m_Number[ CntScore ], 1.0f );
		glVertex3f( 
					m_Pos.x - ( m_Width * 0.5f ) + CntScore * ( m_Width + m_WidthChange ),
					m_Pos.y - (m_Height * 0.5f),
					0.0f );
		// [ 2 ]
		glTexCoord2d( 0.1f * m_Number[ CntScore ], 0.0f );
		glVertex3f( 
					m_Pos.x - ( m_Width * 0.5f ) + CntScore * ( m_Width + m_WidthChange ),
					m_Pos.y + (m_Height * 0.5f),
					0.0f );
		// [ 1 ]
		glTexCoord2d( 0.1f * m_Number[ CntScore ] + 0.1f, 1.0f );
		glVertex3f( 
					m_Pos.x + ( m_Width * 0.5f ) + CntScore * ( m_Width + m_WidthChange ),
					m_Pos.y - (m_Height * 0.5f),
					0.0f );

		// [ 3 ]
		glTexCoord2d( 0.1f * m_Number[ CntScore ] + 0.1f, 0.0f );
		glVertex3f( 
					m_Pos.x + ( m_Width * 0.5f ) + CntScore * ( m_Width + m_WidthChange ),
					m_Pos.y + (m_Height * 0.5f),
					0.0f );
	}

	// �`��̏I��
	glEnd();

	// �}�g���N�X�I���̖���
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	// �R�}���h�̎��s
	glFlush();

	// �`��I��
	//CScene2D::DrawEnd();
	//////////////////////////

	// �e�N�X�`���𖳌���
	glBindTexture( GL_TEXTURE_2D, 0 );

	// �A���t�@�u�����h�𖳌���
	glDisable( GL_BLEND );

	// �e�N�X�`���}�b�s���O�𖳌���
	glDisable( GL_TEXTURE_2D );
}

/******************************************************************************
	�֐��� : void CScore::AddScore ( int value )
	����   : void
	�߂�l : value
	����   : �X�R�A�̉��Z����
******************************************************************************/
void CScore::AddScore( int value )
{
	m_nScore += value;
}