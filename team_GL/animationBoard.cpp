/******************************************************************************
	�^�C�g�����FanimationBoard
	�t�@�C�����FanimationBoard.cpp
	�쐬��    �FAT-13B-284 35 ���}���[��
	�쐬��    �F2016/12/05
******************************************************************************/
/******************************************************************************
	�C���N���[�h�t�@�C��
******************************************************************************/
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "scene.h"
#include "scene3D.h"
#include "animationBoard.h"
#include "input.h"

/******************************************************************************
	�}�N����`
******************************************************************************/
const int DRAW_SPEED = 30;			// �`��X�s�[�h
const int TEXTURE_COLUMN = 1;		// �e�N�X�`���񕪊���
const int TEXTURE_ROW = 1;			// �e�N�X�`���s������

/******************************************************************************
	�֐��� : CAnimationBoard::CAnimationBoard(int Priority, OBJ_TYPE objType) : CScene3D(Priority, objType)
	����   : �R���X�g���N�^
******************************************************************************/
CAnimationBoard::CAnimationBoard(int Priority, OBJ_TYPE objType) : CScene3D(Priority, objType)
{
	m_nCntAnim = 0;		
	m_nPatternAnim = 0;
	
	m_nDirection = -1;
	m_nTexRow = TEXTURE_COLUMN;
	m_nTexColumn = TEXTURE_ROW;
}

/******************************************************************************
	�֐��� : CAnimationBoard::~CAnimationBoard()
	����   : �f�X�g���N�^
******************************************************************************/
CAnimationBoard::~CAnimationBoard()
{
}

/******************************************************************************
	�֐��� : void CAnimationBoard::Init(Vector3 pos, float width, float height)
	����   : void
	�߂�l : �Ȃ�
	����   : ����������
******************************************************************************/
void CAnimationBoard::Init(Vector3 pos, float width, float height)
{
	m_Pos = pos;
	m_Rot = Vector3(0.0f, 0.0f, 0.0f);
	m_Scl = Vector3(1.0f, 1.0f, 1.0f);

	m_Width = width;
	m_Height = height;
	m_Depth = 0.0f;
}

/******************************************************************************
	�֐��� : void CAnimationBoard::Uninit(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �I������
******************************************************************************/
void CAnimationBoard::Uninit(void)
{
}

/******************************************************************************
	�֐��� : void CAnimationBoard::Update(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �X�V����
******************************************************************************/
void CAnimationBoard::Update(void)
{
	// �p�^�[���`��X�V
	m_nCntAnim++;
	if (m_nCntAnim == DRAW_SPEED)
	{
		m_nCntAnim = 0;
		m_nPatternAnim++;
		if (m_nPatternAnim == TEXTURE_COLUMN)
		{
			m_nPatternAnim = 0;
		}
	}
}

/******************************************************************************
	�֐��� : void CAnimationBoard::Draw(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �`�揈���B
******************************************************************************/
void CAnimationBoard::Draw(void)
{
	glDisable(GL_LIGHTING);
	//	�������烂�f���r���[�}�g���N�X�̐ݒ�////////////////////////
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//	�����܂Ń��f���r���[�}�g���N�X�̐ݒ�////////////////////////

	glScalef(m_Scl.x, m_Scl.y, m_Scl.z);
	glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
	glRotatef(m_Rot.y, 0.0f ,1.0f, 0.0f);

	//�@�e�N�X�`���}�b�s���O�L����
    glEnable(GL_TEXTURE_2D);
    //�@�e�N�X�`�����o�C���h
    glBindTexture(GL_TEXTURE_2D, m_nTexIdx);
	glDepthMask(GL_FALSE);
	//	�`��J�n
	glBegin(GL_TRIANGLE_STRIP);

	//	�F�ݒ�
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	//	�@���ݒ�
	glNormal3f(0.0f, 1.0f, 0.0f);

	//	���_���W�ݒ�
	if (m_nDirection < 0)
	{
		glTexCoord2d(m_nPatternAnim * (1.0 / m_nTexColumn), 0.0);
		glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), m_Pos.z);

		glTexCoord2d(m_nPatternAnim * (1.0 / m_nTexColumn), 1.0 / m_nTexRow);
		glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), m_Pos.z);

		glTexCoord2d(m_nPatternAnim * (1.0 / m_nTexColumn) + (1.0 / m_nTexColumn), 0.0);
		glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), m_Pos.z);

		glTexCoord2d(m_nPatternAnim * (1.0 / m_nTexColumn) + (1.0 / m_nTexColumn), 1.0 / m_nTexRow);
		glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), m_Pos.z);
	}
	else if (m_nDirection > 0)
	{
		glTexCoord2d(m_nPatternAnim * (1.0 / m_nTexColumn) + (1.0 / m_nTexColumn), 0.0);
		glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), m_Pos.z);

		glTexCoord2d(m_nPatternAnim * (1.0 / m_nTexColumn) + (1.0 / m_nTexColumn), 1.0 / m_nTexRow);
		glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), m_Pos.z);

		glTexCoord2d(m_nPatternAnim * (1.0 / m_nTexColumn), 0.0);
		glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), m_Pos.z);

		glTexCoord2d(m_nPatternAnim * (1.0 / m_nTexColumn), 1.0 / m_nTexRow);
		glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), m_Pos.z);
	}

	glEnd();
	// �`��I��

	glEnable(GL_LIGHTING);
	glDepthMask(GL_TRUE);
	glBindTexture(GL_TEXTURE_2D, 0);
    //�@�e�N�X�`���}�b�s���O������
    glDisable(GL_TEXTURE_2D);

	//	��������}�g���b�N�X�����ɖ߂�//////////////////////////////
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	//	�����܂Ń}�g���b�N�X�����ɖ߂�//////////////////////////////
}

/******************************************************************************
	�֐��� : CAnimationBoard *CAnimationBoard::Create(Vector3 pos, float width, float height)
	����   :void
	�߂�l : obj
	����   : �쐬�֐��B 
******************************************************************************/
CAnimationBoard *CAnimationBoard::Create(Vector3 pos, float width, float height)
{
	CAnimationBoard *obj = new CAnimationBoard;
	obj->Init(pos, width, height);

	return obj;
}