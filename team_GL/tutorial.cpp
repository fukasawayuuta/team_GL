/******************************************************************************
	�^�C�g���� : �`���[�g���A���N���X
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
#include "tutorial.h"

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
//	�֐��� : CTutorial::CTutorial()
//	����   : �R���X�g���N�^
//			 �l�̃f�t�H���g��
//=============================================================================
CTutorial::CTutorial ( int Priority, OBJ_TYPE objType )
{
}

//=============================================================================
//	�֐��� : CTutorial::~CTutorial()
//	����   : �f�X�g���N�^
//=============================================================================
CTutorial::~CTutorial()
{
}

//	�ÓI�����o�ϐ��錾/////////////////////////////////////////////////////////
bool CTutorial::m_bUse;		//	�t���O
Vector2 CTutorial::m_Pos;	//	���W�B
Vector2 CTutorial::m_Rot;	//	�p�x�B
float CTutorial::m_Width;	//	�����B
float CTutorial::m_Height;	//	�c���B

/******************************************************************************
	�֐��� : CTutorial *CTutorial::Create ( Vector2 pos, Vector2 rot, float width, float height, int index )
	����   : pos, rot, width, height, fileName
	�߂�l : �Ȃ�
	����   : �`���[�g���A���̐�������
******************************************************************************/
CTutorial *CTutorial::Create ( Vector2 pos, Vector2 rot, float width, float height, int index )
{
	CTutorial *tutorial;

	tutorial = new CTutorial;
	tutorial -> Init( pos, rot, width, height, index );

	return tutorial;
}

/******************************************************************************
	�֐��� : void CTutorial::Init ( Vector2 pos, Vector2 rot, float width, float height, int index )
	����   : pos, rot, width, height, fileName
	�߂�l : �Ȃ�
	����   : �`���[�g���A���̏���������
******************************************************************************/
void CTutorial::Init ( Vector2 pos, Vector2 rot, float width, float height, int index )
{
	// �����l����
	m_Pos		= pos;
	m_Rot		= rot;
	m_Width		= width;
	m_Height	= height;

	// �����o�ϐ� ������
	m_bUse = false;

	// �e�N�X�`����ǂݍ��݁A��������
	m_nTexIdx = CTexture::SetTexture( index );
}


/******************************************************************************
	�֐��� : void CTutorial::Uninit ( void )
	����   : void
	�߂�l : �Ȃ�
	����   : �`���[�g���A���̏I������
******************************************************************************/
void CTutorial::Uninit ( void )
{
	if( m_nTexIdx ) {
		m_nTexIdx = 0;
	}
}


/******************************************************************************
	�֐��� : void CTutorial::Update ( void )
	����   : void
	�߂�l : �Ȃ�
	����   : �`���[�g���A���̍X�V����
******************************************************************************/
void CTutorial::Update ( void )
{
	if( m_bUse ) {
		if( m_Width < 800.0f ) {
			m_Width+=20;
		}
		if( m_Width < 600.0f ) {
			m_Height+=20;
		}
	} else {
		m_Width = m_Height = 0.0f;
	}

}

/******************************************************************************
	�֐��� : void CTutorial::Draw ( void )
	����   : void
	�߂�l : �Ȃ�
	����   : �`���[�g���A���̕`�揈��
******************************************************************************/
void CTutorial::Draw ( void )
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

	// �t���O on
	if( m_bUse ) {

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
	}

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

/******************************************************************************
	�֐��� : void CTutorial::Start ( void )
	����   : void
	�߂�l : �Ȃ�
	����   : �`���[�g���A���̊J�n����
******************************************************************************/
void CTutorial::Start ( void )
{
	m_Pos.x = SCREEN_WIDTH * 0.5f;
	m_Pos.y = 350.0f;
	m_bUse = true;
}

/******************************************************************************
	�֐��� : void CTutorial::End ( void )
	����   : void
	�߂�l : �Ȃ�
	����   : �`���[�g���A���̕��Ղ�����
******************************************************************************/
void CTutorial::End ( void )
{
	m_Pos.x = m_Pos.y = m_Width = m_Height = 0.0f;
	m_bUse = false;
}