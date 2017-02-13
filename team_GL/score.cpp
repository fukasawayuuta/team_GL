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


#include "score.h"
#include "sync.h"

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

//=============================================================================
//	�֐��� : CScore::CScore()
//	����   : �R���X�g���N�^
//			 �l�̃f�t�H���g��
//=============================================================================
CScore::CScore(int Priority, OBJ_TYPE objType)
{
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
	�֐��� : CScore *CScore::Create ( Vector2 pos, Vector2 rot, float width, float height, int index )
	����   : pos, rot, width, height, fileName
	�߂�l : �Ȃ�
	����   : �X�R�A�̐�������
******************************************************************************/
CScore *CScore::Create ( Vector2 pos, Vector2 rot, float width, float height, int index, int id )
{
	CScore *score;

	score = new CScore;
	score -> Init( pos, rot, width, height, index, id );

	return score;
}

/******************************************************************************
	�֐��� : void CScore::Init ( Vector2 pos, Vector2 rot, float width, float height, int index )
	����   : pos, rot, width, height, fileName
	�߂�l : �Ȃ�
	����   : �X�R�A�̏���������
******************************************************************************/
void CScore::Init ( Vector2 pos, Vector2 rot, float width, float height, int index, int id )
{
	// �����l����
	m_Pos		= pos;
	m_Rot		= rot;
	m_Width		= width;
	m_Height	= height;

	m_nId = id;

	// �e�N�X�`����ǂݍ��݁A��������
	m_nTexIdx = CTexture::SetTexture( index );
}


/******************************************************************************
	�֐��� : void CScore::Uninit ( void )
	����   : void
	�߂�l : �Ȃ�
	����   : �X�R�A�̏I������
******************************************************************************/
void CScore::Uninit ( void )
{
	if( m_nTexIdx ) {
		m_nTexIdx = 0;
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
	m_nScore = CSync::SetScore( m_nId );

	// �X�R�A�̍X�V����
	m_Number[ 0 ] = m_nScore / 10000 % 10;
	m_Number[ 1 ] = m_nScore / 1000 % 10;
	m_Number[ 2 ] = m_nScore / 100 % 10;
	m_Number[ 3 ] = m_nScore / 10 % 10;
	m_Number[ 4 ] = m_nScore / 1 % 10;

	// �X�R�A�̓���m�F�֐�( +1�����Z���� )
	//AddScore(1);

}

/******************************************************************************
	�֐��� : void CScore::Draw ( void )
	����   : void
	�߂�l : �Ȃ�
	����   : �X�R�A�̕`�揈��
******************************************************************************/
void CScore::Draw ( void )
{
	glDisable(GL_LIGHTING);
	//	��������v���W�F�N�V�����}�g���N�X�̐ݒ�////////////////////
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 1);
	//	�����܂Ńv���W�F�N�V�����}�g���N�X�̐ݒ�////////////////////

	//	�������烂�f���r���[�}�g���N�X�̐ݒ�////////////////////////
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	//	�����܂Ń��f���r���[�}�g���N�X�̐ݒ�////////////////////////

	/* �����F��`����悤�ɂ��� */
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	 //�@�e�N�X�`���}�b�s���O�L����
    glEnable(GL_TEXTURE_2D);
    //�@�e�N�X�`�����o�C���h
    glBindTexture(GL_TEXTURE_2D, m_nTexIdx);

	//	�`��J�n
	glBegin(GL_TRIANGLE_STRIP);

	//	�F�ݒ�
	glColor4f(1, 1, 1, 1);

	// UV�l�ƒ��_���W�̐ݒ� ( DirectX�`�� )
	for( int CntScore = 0; CntScore < MAX_SCORE; CntScore++ ) {
		// [ 0 ]
		glTexCoord2d( 0.1f * m_Number[ CntScore ], 0.0f );
		glVertex3f( 
					m_Pos.x - ( m_Width * 0.5f ) + CntScore * ( m_Width + m_WidthChange ),
					m_Pos.y - (m_Height * 0.5f),
					0.0f );
		// [ 2 ]
		glTexCoord2d( 0.1f * m_Number[ CntScore ], 1.0f );
		glVertex3f( 
					m_Pos.x - ( m_Width * 0.5f ) + CntScore * ( m_Width + m_WidthChange ),
					m_Pos.y + (m_Height * 0.5f),
					0.0f );
		// [ 1 ]
		glTexCoord2d( 0.1f * m_Number[ CntScore ] + 0.1f, 0.0f );
		glVertex3f( 
					m_Pos.x + ( m_Width * 0.5f ) + CntScore * ( m_Width + m_WidthChange ),
					m_Pos.y - (m_Height * 0.5f),
					0.0f );

		// [ 3 ]
		glTexCoord2d( 0.1f * m_Number[ CntScore ] + 0.1f, 1.0f );
		glVertex3f( 
					m_Pos.x + ( m_Width * 0.5f ) + CntScore * ( m_Width + m_WidthChange ),
					m_Pos.y + (m_Height * 0.5f),
					0.0f );
	}

	glEnd();
	//	�`��I��

	glEnable(GL_BLEND);
	glEnable(GL_LIGHTING);

	glBindTexture(GL_TEXTURE_2D, 0);
    //�@�e�N�X�`���}�b�s���O������
    glDisable(GL_TEXTURE_2D);

	//	��������}�g���b�N�X�����ɖ߂�//////////////////////////////
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	//	�����܂Ń}�g���b�N�X�����ɖ߂�//////////////////////////////
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

/******************************************************************************
	�֐��� : int CScore::GetScore ( void )
	����   : ����
	�߂�l : int�^
	����   : �X�R�A�̎������ݏ���
******************************************************************************/
int CScore::GetScore ( void )
{
	return m_nScore;
}