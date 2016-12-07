/******************************************************************************
	�^�C�g�����Fplayer
	�t�@�C�����Fplayer.cpp
	�쐬��    �FAT-13B-284 10 ���}���[��
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
#include "player.h"
#include "input.h"

/******************************************************************************
	�}�N����`
******************************************************************************/
const float MOVE_SPEED = 3.0f;
const int DRAW_SPEED = 10;
const int TEXTURE_COLUMN = 7;
const int TEXTURE_ROW = 3;
const int WALK_DRAW = 4;

/******************************************************************************
	�֐��� : CPlayer::CPlayer(int Priority, OBJ_TYPE objType) : CAnimationBoard(Priority, objType)
	����   : �R���X�g���N�^
******************************************************************************/
CPlayer::CPlayer(int Priority, OBJ_TYPE objType) : CAnimationBoard(Priority, objType)
{
	m_nDirection = -1;
}

/******************************************************************************
	�֐��� : CPlayer::~CPlayer()
	����   : �f�X�g���N�^
******************************************************************************/
CPlayer::~CPlayer()
{
}

/******************************************************************************
	�֐��� : void CPlayer::Init(Vector3 pos, float width, float height)
	����   : void
	�߂�l : �Ȃ�
	����   : ����������
******************************************************************************/
void CPlayer::Init(Vector3 pos, float width, float height)
{
	m_Pos = pos;
	m_Rot = Vector3(0.0f, 0.0f, 0.0f);
	m_Scl = Vector3(1.0f, 1.0f, 1.0f);

	m_Width = width;
	m_Height = height;
	m_Depth = 0.0f;

	m_pTexture = new CTexture;
	m_nTexIdx = m_pTexture->CreateTexture("data\\TEXTURE\\player000.tga");
}

/******************************************************************************
	�֐��� : void CPlayer::Uninit(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �I������
******************************************************************************/
void CPlayer::Uninit(void)
{
	SAFE_RELEASE(m_pTexture);
}

/******************************************************************************
	�֐��� : void CPlayer::Update(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �X�V����
******************************************************************************/
void CPlayer::Update(void)
{
	// �ړ�
	if(CInput::GetKeyboardPress(DIK_A))
	{
		m_nDirection = -1;
		m_Pos.x -= MOVE_SPEED;
	}
	if(CInput::GetKeyboardPress(DIK_D))
	{
		m_nDirection = 1;
		m_Pos.x += MOVE_SPEED;
	}
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
	�֐��� : void CPlayer::Draw(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �`�揈���B
******************************************************************************/
void CPlayer::Draw(void)
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
	
	//	�`��J�n
	glBegin(GL_TRIANGLE_STRIP);

	//	�F�ݒ�
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	//	�@���ݒ�
	glNormal3f(0.0f, 1.0f, 0.0f);

	//	���_���W�ݒ�
	if (m_nDirection < 0)
	{
		glTexCoord2d(m_nPatternAnim * (1.0 / TEXTURE_COLUMN), 0.0);
		glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), m_Pos.z);

		glTexCoord2d(m_nPatternAnim * (1.0 / TEXTURE_COLUMN), 1.0 / TEXTURE_ROW);
		glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), m_Pos.z);

		glTexCoord2d(m_nPatternAnim * (1.0 / TEXTURE_COLUMN) + (1.0 / TEXTURE_COLUMN), 0.0);
		glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), m_Pos.z);

		glTexCoord2d(m_nPatternAnim * (1.0 / TEXTURE_COLUMN) + (1.0 / TEXTURE_COLUMN), 1.0 / TEXTURE_ROW);
		glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), m_Pos.z);
	}
	else if (m_nDirection > 0)
	{
		glTexCoord2d(m_nPatternAnim * (1.0 / TEXTURE_COLUMN) + (1.0 / TEXTURE_COLUMN), 0.0);
		glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), m_Pos.z);

		glTexCoord2d(m_nPatternAnim * (1.0 / TEXTURE_COLUMN) + (1.0 / TEXTURE_COLUMN), 1.0 / TEXTURE_ROW);
		glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), m_Pos.z);

		glTexCoord2d(m_nPatternAnim * (1.0 / TEXTURE_COLUMN), 0.0);
		glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), m_Pos.z);

		glTexCoord2d(m_nPatternAnim * (1.0 / TEXTURE_COLUMN), 1.0 / TEXTURE_ROW);
		glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), m_Pos.z);
	}

	glEnd();
	// �`��I��

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
	�֐��� : CPlayer *CPlayer::Create(Vector3 pos, float width, float height)
	����   :void
	�߂�l : obj
	����   : �쐬�֐��B 
******************************************************************************/
CPlayer *CPlayer::Create(Vector3 pos, float width, float height)
{
	CPlayer *obj = new CPlayer;
	obj->Init(pos, width, height);

	return obj;
}