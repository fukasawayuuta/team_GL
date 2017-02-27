/*******************************************************************************
* �^�C�g�����F
* �t�@�C�����Friver.cpp
* �쐬��	�FAT13B284 02 ������
* �쐬��	�F2017/02/08
********************************************************************************
* �X�V����	�F
*
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "main.h"
#include "manager.h"

#include "river.h"

//=============================================================================
//	�֐��� : CRiver::CRiver()
//	����   : �R���X�g���N�^
//=============================================================================
CRiver::CRiver( int Priority, OBJ_TYPE objType )
{
}

//=============================================================================
//	�֐��� : CRiver::~CRiver()
//	����   : �f�X�g���N�^
//=============================================================================
CRiver::~CRiver()
{
}

/*******************************************************************************
* �֐����Fvoid CRiver::Init ( void )
*
* ����	�F
* �߂�l�F
* ����	�F����������
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
* �֐����Fvoid CRiver::Uninit(void)
*
* ����	�F
* �߂�l�F
* ����	�F�I������
*******************************************************************************/
void CRiver::Uninit ( void )
{
}

/*******************************************************************************
* �֐����Fvoid CRiver::Update ( void )
*
* ����	�F
* �߂�l�F
* ����	�F�X�V����
*******************************************************************************/
void CRiver::Update ( void )
{
	m_Tex += 0.0003f;
}

/*******************************************************************************
* �֐����Fvoid CRiver::Draw ( void )
*
* ����	�F
* �߂�l�F
* ����	�F�`�揈��
*******************************************************************************/
void CRiver::Draw ( void )
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

/*******************************************************************************
* �֐����FCRiver *Create( void )
*
* ����	�F
* �߂�l�F
* ����	�F
*******************************************************************************/
CRiver *CRiver::Create( void )
{
	CRiver *pBg = new CRiver;
	pBg->Init();
	return pBg ;
}