/******************************************************************************
	�^�C�g�����FScene2D
	�t�@�C�����Fscene2D.cpp
	�쐬��    �FAT-13B-284 35 �[�V�C��
	�쐬��    �F2016/11/18
******************************************************************************/
/******************************************************************************
	�C���N���[�h�t�@�C��
******************************************************************************/
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "scene.h"
#include "scene2D.h"

/******************************************************************************
	�֐��� : CScene2D::CScene2D()
	����   : �R���X�g���N�^
******************************************************************************/
CScene2D::CScene2D(int Priority, OBJ_TYPE objType)
{
	m_Pos = Vector2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
	m_Rot = Vector2(0.0f, 0.0f);
	m_nTexIdx = 0;
}

/******************************************************************************
	�֐��� : CScene2D::~CScene2D()
	����   : �f�X�g���N�^
******************************************************************************/
CScene2D::~CScene2D()
{
}

/******************************************************************************
	�֐��� : void CScene2D::Init(void)
	����   : void
	�߂�l : �Ȃ�
	����   : ����������
******************************************************************************/
void CScene2D::Init(int nIdx)
{
	m_Width = 200.0f;
	m_Height = 200.0f;

	m_nTexIdx = CTexture::SetTexture(nIdx);
}

/******************************************************************************
	�֐��� : void CScene2D::Uninit(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �I������
******************************************************************************/
void CScene2D::Uninit(void)
{
}

/******************************************************************************
	�֐��� : void CScene2D::Update(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �X�V�����B
******************************************************************************/
void CScene2D::Update(void)
{

}

/******************************************************************************
	�֐��� : void CScene2D::Draw(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �X�V�����B
******************************************************************************/
void CScene2D::Draw(void)
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
    glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), 0.0f);
	
	glTexCoord2d(1.0, 1.0);
    glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), 0.0f);
	
	glTexCoord2d(0.0, 0.0);
    glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), 0.0f);
	
	glTexCoord2d(1.0, 0.0);
    glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), 0.0f);
	
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

CScene2D *CScene2D::Create(int nIdx)
{
	CScene2D *obj = new CScene2D;
	obj->Init(nIdx);

	return obj;
}