/*******************************************************************************
* �^�C�g�����F
* �t�@�C�����Ffade.cpp
* �쐬��	�FAT13B284 10 ���}���[��
* �쐬��	�F
********************************************************************************
* �X�V����	�F
*
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"

/*******************************************************************************
* �}�N����`
*******************************************************************************/
const float WIDTH = SCREEN_WIDTH;
const float HEIGHT = SCREEN_HEIGHT;
const int FADE_COUNT = 30;

/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/
CMode *CFade::m_NextMode;
FADE CFade::m_State = FADE_IN;
int CFade::m_Count;
float CFade::m_Alfa;

/*******************************************************************************
* �֐����FCFade::CFade()
*
* ����	�F
* �߂�l�F
* ����	�F�R���X�g���N�^
*******************************************************************************/
CFade::CFade()
{
}

/*******************************************************************************
* �֐����FCFade::~CFade()
*
* ����	�F
* �߂�l�F
* ����	�F�f�X�g���N�^
*******************************************************************************/
CFade::~CFade()
{
}

/*******************************************************************************
* �֐����Fvoid CFade::Init( void )
*
* ����	�F
* �߂�l�F
* ����	�F����������
*******************************************************************************/
void CFade::Init(void)
{
}

/*******************************************************************************
* �֐����Fvoid CFade::Uninit( void )
*
* ����	�F
* �߂�l�F
* ����	�F�I������
*******************************************************************************/
void CFade::Uninit(void)
{
	m_NextMode = NULL;
}

/*******************************************************************************
* �֐����Fvoid CFade::Update( void )
*
* ����	�F
* �߂�l�F
* ����	�F�X�V����
*******************************************************************************/
void CFade::Update(void)
{
	// �t�F�[�h�̏���
	if (m_State == FADE_IN)
	{// �t�F�[�h�C��
		m_Alfa -= 1.0f / FADE_COUNT;
		if (m_Count > FADE_COUNT)
		{
			m_State = FADE_NONE;
			m_Count = 0;
			m_Alfa = 0.0f;
		}
	}
	else if (m_State == FADE_OUT)
	{// �t�F�[�h�A�E�g
		m_Alfa += 1.0f / FADE_COUNT;
		if (m_Count > FADE_COUNT)
		{
			CManager::SetMode(m_NextMode);
			m_State = FADE_IN;
			m_Count = 0;
			m_Alfa = 1.0f;
		}
	}
	
	// �J�E���^���Z
	m_Count++;
}

/*******************************************************************************
* �֐����Fvoid CFade::Draw( void )
*
* ����	�F
* �߂�l�F
* ����	�F�`�揈��
*******************************************************************************/
void CFade::Draw(void)
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

	glColor4f(0.0f, 0.0f, 0.0f, m_Alfa);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glColor4f(0.0f, 0.0f, 0.0f, m_Alfa);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(WIDTH, 0.0f, 0.0f);

	glColor4f(0.0f, 0.0f, 0.0f, m_Alfa);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(0.0f, HEIGHT, 0.0f);

	glColor4f(0.0f, 0.0f, 0.0f, m_Alfa);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(WIDTH, HEIGHT, 0.0f);

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
}

/*******************************************************************************
* �֐����Fvoid CFade::Start( CMode *NextMode )
*
* ����	�F
* �߂�l�F
* ����	�F�t�F�[�h�J�n����
*******************************************************************************/
void CFade::Start(CMode *NextMode)
{
	if (m_State == FADE_NONE)
	{
		m_NextMode = NextMode;
		m_State = FADE_OUT;
		m_Count = 0;
		m_Alfa = 0.0f;
	}
}