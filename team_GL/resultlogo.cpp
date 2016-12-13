/******************************************************************************
	�^�C�g���� : ���U���g���S�N���X
	�t�@�C���� : resultlogo.cpp
	�쐬��     : AT-13B-284 02 ������
	�쐬��     : 2016/11/30
	�X�V��     : 
******************************************************************************/
/******************************************************************************
	�C���N���[�h�t�@�C��
******************************************************************************/

#include "main.h"
#include "manager.h"


#include "resultlogo.h"

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

//=============================================================================
//	�֐��� : CResultLogo::CResultLogo()
//	����   : �R���X�g���N�^
//			 �l�̃f�t�H���g��
//=============================================================================
CResultLogo::CResultLogo ( int Priority, OBJ_TYPE objType )
{
}

//=============================================================================
//	�֐��� : CResultLogo::~CResultLogo()
//	����   : �f�X�g���N�^
//=============================================================================
CResultLogo::~CResultLogo()
{
}

/******************************************************************************
	�֐��� : CResultLogo *CResultLogo::Create ( Vector2 pos, Vector2 rot, float width, float height, int index )
	����   : pos, rot, width, height, fileName
	�߂�l : �Ȃ�
	����   : ���U���g���S�̐�������
******************************************************************************/
CResultLogo *CResultLogo::Create ( Vector2 pos, Vector2 rot, float width, float height, int index )
{
	CResultLogo *resultlogo;

	resultlogo = new CResultLogo;
	resultlogo -> Init( pos, rot, width, height, index );

	return resultlogo;
}

/******************************************************************************
	�֐��� : void CResultLogo::Init ( Vector2 pos, Vector2 rot, float width, float height, int index )
	����   : pos, rot, width, height, fileName
	�߂�l : �Ȃ�
	����   : ���U���g���S�̏���������
******************************************************************************/
void CResultLogo::Init ( Vector2 pos, Vector2 rot, float width, float height, int index )
{
	// �����l����
	m_Pos		= pos;
	m_Rot		= rot;
	m_Width		= width;
	m_Height	= height;

	// �e�N�X�`����ǂݍ��݁A��������
	m_nTexIdx = CTexture::SetTexture( index );
}


/******************************************************************************
	�֐��� : void CResultLogo::Uninit ( void )
	����   : void
	�߂�l : �Ȃ�
	����   : ���U���g���S�̏I������
******************************************************************************/
void CResultLogo::Uninit ( void )
{
	if( m_nTexIdx ) {
		m_nTexIdx = 0;
	}
}


/******************************************************************************
	�֐��� : void CResultLogo::Update ( void )
	����   : void
	�߂�l : �Ȃ�
	����   : ���U���g���S�̍X�V����
******************************************************************************/
void CResultLogo::Update ( void )
{


}

/******************************************************************************
	�֐��� : void CResultLogo::Draw ( void )
	����   : void
	�߂�l : �Ȃ�
	����   : ���U���g���S�̕`�揈��
******************************************************************************/
void CResultLogo::Draw ( void )
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

	// ���e�X�g �L����
	glAlphaFunc(GL_GEQUAL, 0.09f );
	glEnable(GL_ALPHA_TEST);

	 //�@�e�N�X�`���}�b�s���O�L����
    glEnable(GL_TEXTURE_2D);
    //�@�e�N�X�`�����o�C���h
    glBindTexture(GL_TEXTURE_2D, m_nTexIdx);

	//	�`��J�n
	glBegin(GL_TRIANGLE_STRIP);

	//	�F�ݒ�
	glColor4f(1, 1, 1, 1);

	//	���_���W�ݒ�
	glTexCoord2d( 0.0, 1.0 );
    glVertex3f(m_Pos.x - ( m_Width * 0.5f ), m_Pos.y + (m_Height * 0.5f), 0.0f );

	glTexCoord2d( 1.0, 1.0 );
    glVertex3f(m_Pos.x + ( m_Width * 0.5f ), m_Pos.y + (m_Height * 0.5f), 0.0f );

	glTexCoord2d( 0.0f, 0.0f );
    glVertex3f(m_Pos.x - ( m_Width * 0.5f ), m_Pos.y - (m_Height * 0.5f), 0.0f );

	glTexCoord2d( 1.0f, 0.0f );
    glVertex3f(m_Pos.x + ( m_Width * 0.5f ), m_Pos.y - (m_Height * 0.5f), 0.0f );

	glEnd();
	//	�`��I��

	glEnable(GL_BLEND);
	glEnable(GL_LIGHTING);

	// ���e�X�g������
	glDisable(GL_ALPHA_TEST);

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
