/******************************************************************************
	�^�C�g���� : �^�C�g�����S�N���X
	�t�@�C���� : titlelogo.cpp
	�쐬��     : AT-13B-284 02 ������
	�쐬��     : 2016/11/30
	�X�V��     : 
******************************************************************************/
/******************************************************************************
	�C���N���[�h�t�@�C��
******************************************************************************/

#include "main.h"
#include "manager.h"


#include "titlelogo.h"

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
//	�֐��� : CTitleLogo::CTitleLogo()
//	����   : �R���X�g���N�^
//			 �l�̃f�t�H���g��
//=============================================================================
CTitleLogo::CTitleLogo ( int Priority, OBJ_TYPE objType )
{
}

//=============================================================================
//	�֐��� : CTitleLogo::~CTitleLogo()
//	����   : �f�X�g���N�^
//=============================================================================
CTitleLogo::~CTitleLogo()
{
}

/******************************************************************************
	�֐��� : CTitleLogo *CTitleLogo::Create ( Vector2 pos, Vector2 rot, float width, float height, int index )
	����   : pos, rot, width, height, fileName
	�߂�l : �Ȃ�
	����   : �^�C�g�����S�̐�������
******************************************************************************/
CTitleLogo *CTitleLogo::Create ( Vector2 pos, Vector2 rot, float width, float height, int index )
{
	CTitleLogo *titlelogo;

	titlelogo = new CTitleLogo;
	titlelogo -> Init( pos, rot, width, height, index );

	return titlelogo;
}

/******************************************************************************
	�֐��� : void CTitleLogo::Init ( Vector2 pos, Vector2 rot, float width, float height, int index )
	����   : pos, rot, width, height, fileName
	�߂�l : �Ȃ�
	����   : �^�C�g�����S�̏���������
******************************************************************************/
void CTitleLogo::Init ( Vector2 pos, Vector2 rot, float width, float height, int index )
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
	�֐��� : void CTitleLogo::Uninit ( void )
	����   : void
	�߂�l : �Ȃ�
	����   : �^�C�g�����S�̏I������
******************************************************************************/
void CTitleLogo::Uninit ( void )
{
	if( m_nTexIdx ) {
		m_nTexIdx = 0;
	}
}


/******************************************************************************
	�֐��� : void CTitleLogo::Update ( void )
	����   : void
	�߂�l : �Ȃ�
	����   : �^�C�g�����S�̍X�V����
******************************************************************************/
void CTitleLogo::Update ( void )
{


}

/******************************************************************************
	�֐��� : void CTitleLogo::Draw ( void )
	����   : void
	�߂�l : �Ȃ�
	����   : �^�C�g�����S�̕`�揈��
******************************************************************************/
void CTitleLogo::Draw ( void )
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

	//	���_���W�ݒ�
	glTexCoord2d(0.0, 1.0);
    glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), 0.0f );

	glTexCoord2d(1.0, 1.0);
    glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), 0.0f );

	glTexCoord2d(0.0, 0.0);
    glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), 0.0f );

	glTexCoord2d(1.0, 0.0);
    glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), 0.0f );

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
