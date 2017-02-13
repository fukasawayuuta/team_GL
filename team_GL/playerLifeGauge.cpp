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
#include "mode.h"
#include "game.h"
#include "texture.h"
#include "scene.h"
#include "scene2D.h"
#include "game_UI.h"
#include "playerLifeGauge.h"
#include "scene3D.h"
#include "animationBoard.h"
#include "player.h"

/******************************************************************************
�}�N����`
******************************************************************************/

/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/

/*******************************************************************************
* �֐����FCPlayerLifeGauge::CPlayerLifeGauge(int Priority, OBJ_TYPE objType) : CGame_UI(Priority, objType)
*
* ����	�F
* �߂�l�F
* ����	�F�R���X�g���N�^
*******************************************************************************/
CPlayerLifeGauge::CPlayerLifeGauge(int Priority, OBJ_TYPE objType) : CGame_UI(Priority, objType)
{
	m_fMax = 1.0f;
	m_fCurrent = 1.0f;
}

/*******************************************************************************
* �֐����FCPlayerLifeGauge::~CPlayerLifeGauge()
*
* ����	�F
* �߂�l�F
* ����	�F�f�X�g���N�^
*******************************************************************************/
CPlayerLifeGauge::~CPlayerLifeGauge()
{
}

/*******************************************************************************
* �֐����Fvoid CPlayerLifeGauge::Update(void)
*
* ����	�F
* �߂�l�F
* ����	�F�X�V����
*******************************************************************************/
void CPlayerLifeGauge::Update(void)
{
	CGame *game = (CGame*)CManager::GetMode();
	CPlayer *player = game->GetPlayer();
	m_fCurrent = (float)player->GetLife();
	m_fCurrent = m_fCurrent <= 0.0f ? 0.0f : m_fCurrent;
	m_fMax = (float)player->GetLifeMax();
}

/*******************************************************************************
* �֐����Fvoid CPlayerLifeGauge::Draw(void)
*
* ����	�F
* �߂�l�F
* ����	�F�`�揈��
*******************************************************************************/
void CPlayerLifeGauge::Draw(void)
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
	glTexCoord2d(0.0, 0.0);
	glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), 0.0f);

	glTexCoord2d(m_fCurrent / m_fMax, 0.0);
	glVertex3f(m_Pos.x - m_Width * 0.5f + m_Width * m_fCurrent / m_fMax, m_Pos.y - (m_Height * 0.5f), 0.0f);

	glTexCoord2d(0.0, 1.0);
	glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), 0.0f);

	glTexCoord2d(m_fCurrent / m_fMax, 1.0);
	glVertex3f(m_Pos.x - m_Width * 0.5f + m_Width * m_fCurrent / m_fMax, m_Pos.y + (m_Height * 0.5f), 0.0f);

	glEnd();
	//	�`��I��

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

/******************************************************************************
�֐��� : void CGame_UI::Create(Vector2 pos, float width, float height)
����   : void
�߂�l : �Ȃ�
����   : �`�揈���B
******************************************************************************/
CPlayerLifeGauge *CPlayerLifeGauge::Create(Vector2 pos, float width, float height, int texIndex)
{
	CPlayerLifeGauge *obj = new CPlayerLifeGauge;
	obj->Init(pos, width, height, texIndex);

	return obj;
}