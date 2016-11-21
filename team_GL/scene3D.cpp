/******************************************************************************
	�^�C�g�����FScene3D
	�t�@�C�����Fscene3D.cpp
	�쐬��    �FAT-13B-284 35 �[�V�C��
	�쐬��    �F2016/11/21
******************************************************************************/
/******************************************************************************
	�C���N���[�h�t�@�C��
******************************************************************************/
#include "main.h"
#include "rerender.h"
#include "manager.h"
#include "scene.h"
#include "scene3D.h"

/******************************************************************************
	�֐��� : CScene3D::CScene3D()
	����   : �R���X�g���N�^
******************************************************************************/
CScene3D::CScene3D()
{
}

/******************************************************************************
	�֐��� : CScene3D::~CScene3D()
	����   : �f�X�g���N�^
******************************************************************************/
CScene3D::~CScene3D()
{
}

/******************************************************************************
	�֐��� : void CScene3D::Init(void)
	����   : void
	�߂�l : �Ȃ�
	����   : ����������
******************************************************************************/
void CScene3D::Init(void)
{
	m_Pos = Vector3(0.0f, 0.0f, 0.0f);
	m_Rot = Vector3(0.0f, 0.0f, 0.0f);
	m_Scl = Vector3(1.0f, 1.0f, 1.0f);

	m_Width = 50.0f;
	m_Height = 50.0f;
	m_Depth = 0.0f;
}

/******************************************************************************
	�֐��� : void CScene3D::Uninit(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �I������
******************************************************************************/
void CScene3D::Uninit(void)
{

}

/******************************************************************************
	�֐��� : void CScene3D::Update(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �X�V����
******************************************************************************/
void CScene3D::Update(void)
{

}

/******************************************************************************
	�֐��� : void CScene3D::Draw(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �`�揈���B
******************************************************************************/
void CScene3D::Draw(void)
{
	glDisable(GL_LIGHTING);
	//	�������烂�f���r���[�}�g���N�X�̐ݒ�////////////////////////
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//	�����܂Ń��f���r���[�}�g���N�X�̐ݒ�////////////////////////

	glScalef(m_Scl.x, m_Scl.y, m_Scl.z);
	glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
	glRotatef(m_Rot.y, 0.0f ,1.0f, 0.0f);
	

	/* �����F��`����悤�ɂ��� */
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	 //�@�e�N�X�`���}�b�s���O�L����
    //glEnable(GL_TEXTURE_2D);
    //�@�e�N�X�`�����o�C���h
    //glBindTexture(GL_TEXTURE_2D, m_TexIndex);

	
	//	�`��J�n
	glBegin(GL_TRIANGLE_STRIP);

	//	�F�ݒ�
	glColor4f(1 , 1 , 1, 1);

	//	�@���ݒ�
	glNormal3f(0, 1, 0);

	//	���_���W�ݒ�
	glTexCoord2d(0.0, 1.0);
    glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), m_Pos.z);

	glTexCoord2d(1.0, 1.0);
    glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), m_Pos.z);

	glTexCoord2d(0.0, 0.0);
    glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), m_Pos.z);

	glTexCoord2d(1.0, 0.0);
    glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), m_Pos.z);

	glEnd();
	//	�`��I��

	glEnable(GL_BLEND);
	glEnable(GL_LIGHTING);

	 glBindTexture(GL_TEXTURE_2D, 0);
    //�@�e�N�X�`���}�b�s���O������
    glDisable(GL_TEXTURE_2D);

	//	��������}�g���b�N�X�����ɖ߂�//////////////////////////////
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	//	�����܂Ń}�g���b�N�X�����ɖ߂�//////////////////////////////
}

/******************************************************************************
	�֐��� : CScene3D *CScene3D::Create(void)
	����   :void
	�߂�l : obj
	����   : �쐬�֐��B 
******************************************************************************/
CScene3D *CScene3D::Create(void)
{
	CScene3D *obj = new CScene3D;
	obj->Init();

	return obj;
}