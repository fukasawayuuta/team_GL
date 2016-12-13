/******************************************************************************
	�^�C�g�����FEnemy
	�t�@�C�����Fenemy.cpp
	�쐬��    �FAT-13B-284 35 �[�V�C��
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
#include "enemy.h"

const int DRAW_SPEED = 30;
const int TEXTURE_COLUMN = 5;
const int TEXTURE_ROW = 1;
const int WALK_DRAW = 5;

/******************************************************************************
	�֐��� : CEnemy::CEnemy()
	����   : �R���X�g���N�^
******************************************************************************/
CEnemy::CEnemy(int Priority, OBJ_TYPE objType) : CAnimationBoard(Priority, objType)
{
	m_nTexRow = TEXTURE_ROW;
	m_nTexColumn = TEXTURE_COLUMN;
}

/******************************************************************************
	�֐��� : CEnemy::~CEnemy()
	����   : �f�X�g���N�^
******************************************************************************/
CEnemy::~CEnemy(void)
{
}

/******************************************************************************
	�֐��� : void CEnemy::Init(Vector3 pos, float width, float height)
	����   : void
	�߂�l : �Ȃ�
	����   : ����������
******************************************************************************/
void CEnemy::Init(Vector3 pos, float width, float height, int texIndex)
{
	m_Pos = pos;
	m_Width = width;
	m_Height = height;
	m_nDirection = 1;
	m_nTexIdx = CTexture::SetTexture(texIndex);
}

/******************************************************************************
	�֐��� : void CEnemy::Uninit(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �I������
******************************************************************************/
void CEnemy::Uninit(void)
{

}

/******************************************************************************
	�֐��� : void CEnemy::Update(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �X�V����
******************************************************************************/
void CEnemy::Update(void)
{
	// �p�^�[���`��X�V
	m_nCntAnim++;
	if (m_nCntAnim == DRAW_SPEED)
	{
		m_nCntAnim = 0;
		m_nPatternAnim++;
		if (m_nPatternAnim == WALK_DRAW)
		{
			m_nPatternAnim = 0;
		}
	}
}

/******************************************************************************
	�֐��� : void CEnemy::Draw(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �`�揈���B
******************************************************************************/
void CEnemy::Draw(void)
{
	CAnimationBoard::Draw();
	//glDisable(GL_LIGHTING);
	////	�������烂�f���r���[�}�g���N�X�̐ݒ�////////////////////////
	//glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();
	////	�����܂Ń��f���r���[�}�g���N�X�̐ݒ�////////////////////////

	//glScalef(m_Scl.x, m_Scl.y, m_Scl.z);
	//glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
	//glRotatef(m_Rot.y, 0.0f ,1.0f, 0.0f);


	///* �����F��`����悤�ɂ��� */
	//glEnable(GL_BLEND); 
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	////�@�e�N�X�`���}�b�s���O�L����
 //   glEnable(GL_TEXTURE_2D);
 //   //�@�e�N�X�`�����o�C���h
 //   glBindTexture(GL_TEXTURE_2D, m_nTexIdx);
	//
	////	�`��J�n
	//glBegin(GL_TRIANGLE_STRIP);

	////	�F�ݒ�
	//glColor4f(1 , 1 , 1, 1);

	////	�@���ݒ�
	//glNormal3f(0, 1, 0);

	////	���_���W�ݒ�
	//glTexCoord2d(m_nPatternAnim * (1.0 / TEXTURE_COLUMN), 0.0);
	//glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), m_Pos.z);

	//glTexCoord2d(m_nPatternAnim * (1.0 / TEXTURE_COLUMN), 1.0 / TEXTURE_ROW);
	//glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), m_Pos.z);

	//glTexCoord2d(m_nPatternAnim * (1.0 / TEXTURE_COLUMN) + (1.0 / TEXTURE_COLUMN), 0.0);
	//glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), m_Pos.z);

	//glTexCoord2d(m_nPatternAnim * (1.0 / TEXTURE_COLUMN) + (1.0 / TEXTURE_COLUMN), 1.0 / TEXTURE_ROW);
	//glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), m_Pos.z);

	//glEnd();
	////	�`��I��

	//glEnable(GL_LIGHTING);

	// glBindTexture(GL_TEXTURE_2D, 0);
 //   //�@�e�N�X�`���}�b�s���O������
 //   glDisable(GL_TEXTURE_2D);

	////	��������}�g���b�N�X�����ɖ߂�//////////////////////////////
	//glMatrixMode(GL_MODELVIEW);
	//glPopMatrix();
	////	�����܂Ń}�g���b�N�X�����ɖ߂�//////////////////////////////
}

/******************************************************************************
	�֐��� : void CEnemy::Create(Vector3 pos, float width, float height)
	����   : pos, width, height
	�߂�l : �Ȃ�
	����   : �`�揈���B
******************************************************************************/
void CEnemy::Create(Vector3 pos, float width, float height, int texIndex)
{
	CEnemy *obj = new CEnemy;
	obj->Init(pos, width, height, texIndex);
}