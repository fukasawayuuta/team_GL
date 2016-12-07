/*******************************************************************************
* �^�C�g�����F
* �t�@�C�����Fopening.cpp
* �쐬��	�FAT13B284 02 ������
* �쐬��	�F2016/11/30
********************************************************************************
* �X�V����	�F
*
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "main.h"
#include "mode.h"
#include "opening.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "scene.h"
#include "scene2D.h"
#include "input.h"
#include "texture.h"

/*******************************************************************************
* �֐����FCOpening::COpening()
*
* ����	�F
* �߂�l�F
* ����	�F�R���X�g���N�^
*******************************************************************************/
COpening::COpening()
{
}

/*******************************************************************************
* �֐����FCOpening::~COpening()
*
* ����	�F
* �߂�l�F
* ����	�F�f�X�g���N�^
*******************************************************************************/
COpening::~COpening()
{
}

/*******************************************************************************
* �֐����Fvoid COpening::Init( void )
*
* ����	�F
* �߂�l�F
* ����	�F����������
*******************************************************************************/
void COpening::Init ( void )
{
	CScene2D::Create( TEXTURE_TYPE_TEAMLOGO );
}

/*******************************************************************************
* �֐����Fvoid COpening::Uninit( void )
*
* ����	�F
* �߂�l�F
* ����	�F�I������
*******************************************************************************/
void COpening::Uninit(void)
{
	CScene::ReleaseAll();
}

/*******************************************************************************
* �֐����Fvoid COpening::Update( void )
*
* ����	�F
* �߂�l�F
* ����	�F�X�V����
*******************************************************************************/
void COpening::Update(void)
{
	CScene::UpdateAll();

	if( CInput::GetKeyboardTrigger( DIK_RETURN ) )
	{
		CFade::Start( new CTitle );
	}
}

/*******************************************************************************
* �֐����Fvoid COpening::Draw( void )
*
* ����	�F
* �߂�l�F
* ����	�F�I�[�v�j���O�̔w�i(�����)�̕`�揈��
*******************************************************************************/
void COpening::Draw(void)
{
	/* ���C�g�𖳌� */
	glDisable(GL_LIGHTING);
	/* �f�v�X�e�X�g�̖��� */
	glDisable(GL_DEPTH_TEST);
	/* �v���W�F�N�V�����}�g���N�X�̐ݒ� */
	glMatrixMode(GL_PROJECTION);							// �ˉe�ϊ��s��ݒ�
	glPushMatrix();											// ���݂̎ˉe�ϊ��s���ۑ�
	glLoadIdentity();										// �s��Z�b�g
	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1);		// ���ˉe�ϊ��ݒ�

	/* ���f���r���[�}�g���N�X�̐ݒ� */
	glMatrixMode(GL_MODELVIEW);								// ���f���r���[�ϊ��s��ݒ�
	glPushMatrix();											// ���݂̃��f���r���[�s���ۑ�
	glLoadIdentity();										// �s��Z�b�g

	/* �e�N�X�`���I�u�W�F�N�g�̌��� */
	glBindTexture(GL_TEXTURE_2D, 0);

	/* 2D�|���S���`��J�n */
	glBegin(GL_TRIANGLE_STRIP);

	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f( SCREEN_WIDTH, 0.0f, 0.0f);

	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(0.0f, SCREEN_HEIGHT, 0.0f);

	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	glEnd();
	/* 2D�|���S���`��I�� */

	/* �e�N�X�`���I�u�W�F�N�g�̌��� */
	glBindTexture(GL_TEXTURE_2D, 0);

	glMatrixMode(GL_PROJECTION);	// �ˉe�ϊ��s��ݒ�
	glPopMatrix();					// �ˉe�ϊ��s��𕜌�

	glMatrixMode(GL_MODELVIEW);		// ���f���r���[�ϊ��s��ݒ�
	glPopMatrix();					// ���f���r���[�s��𕜌�

	/* ���C�g��L�� */
	glEnable(GL_LIGHTING);
	/* �f�v�X�e�X�g��L�� */
	glEnable(GL_DEPTH_TEST);

	glFlush();						// �R�}���h�̋������s


	CScene::DrawAll();
}