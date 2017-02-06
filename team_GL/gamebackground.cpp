/*******************************************************************************
* �^�C�g�����F
* �t�@�C�����Fgamebackground.cpp
* �쐬��	�FAT13B284 31 ���R�a�n
* �쐬��	�F2016/11/28
********************************************************************************
* �X�V����	�F
*
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "mode.h"
#include "game.h"
#include "scene.h"
#include "scene2D.h"
#include "scene3D.h"
#include "texture.h"
#include "gamebackground.h"
#include "animationBoard.h"
#include "player.h"

/*******************************************************************************
* �֐����FCGameBackground::CGameBackground()
*
* ����	�F
* �߂�l�F
* ����	�F�R���X�g���N�^
*******************************************************************************/
CGameBackground::CGameBackground(int Priority, OBJ_TYPE objType) : CScene2D(Priority, objType)
{
	m_dTexCoord = 0.0f;
}

/*******************************************************************************
* �֐����FCGameBackground::~CGameBackground()
*
* ����	�F
* �߂�l�F
* ����	�F�f�X�g���N�^
*******************************************************************************/
CGameBackground::~CGameBackground()
{
}

/*******************************************************************************
* �֐����Fvoid CGameBackground::Init(void)
*
* ����	�F
* �߂�l�F
* ����	�F����������
*******************************************************************************/
void CGameBackground::Init(void)
{
	m_Pos = Vector2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
	m_Rot = Vector2(0.0f, 0.0f);
	m_TextureIndex = CTexture::SetTexture(TEXTURE_TYPE_GAME_BG);
	m_Width = SCREEN_WIDTH;
	m_Height = SCREEN_HEIGHT;
	m_dTexCoord = 0.5f;
}

/*******************************************************************************
* �֐����Fvoid CGameBackground::Uninit(void)
*
* ����	�F
* �߂�l�F
* ����	�F�I������
*******************************************************************************/
void CGameBackground::Uninit(void)
{

}

/*******************************************************************************
* �֐����Fvoid CGameBackground::Update(void)
*
* ����	�F
* �߂�l�F
* ����	�F�X�V����
*******************************************************************************/
void CGameBackground::Update(void)
{
	CGame *game = (CGame*)CManager::GetMode();
	CPlayer *player = game->GetPlayer();
	Vector3 move = player->GetPos();
	m_dTexCoord = (double)move.x / SCREEN_WIDTH;
}

/*******************************************************************************
* �֐����Fvoid CGameBackground::Draw(void)
*
* ����	�F
* �߂�l�F
* ����	�F�`�揈��
*******************************************************************************/
void CGameBackground::Draw(void)
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
	glBindTexture(GL_TEXTURE_2D, m_TextureIndex);

	//	�`��J�n
	glBegin(GL_TRIANGLE_STRIP);

	//	�F�ݒ�
	glColor4f(1, 1, 1, 1);

	//	���_���W�ݒ�
	glTexCoord2d(m_dTexCoord - 0.5f, 1.0);
	glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), -0.999f);

	glTexCoord2d(m_dTexCoord + 0.5f, 1.0);
	glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), -0.999f);

	glTexCoord2d(m_dTexCoord - 0.5f, 0.0);
	glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), -0.999f);

	glTexCoord2d(m_dTexCoord + 0.5f, 0.0);
	glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), -0.999f);

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

/*******************************************************************************
* �֐����FCGameBackground *Create( void )
*
* ����	�F
* �߂�l�F
* ����	�F
*******************************************************************************/
CGameBackground *CGameBackground::Create( void )
{
	CGameBackground *pBg = new CGameBackground;
	pBg->Init();
	return pBg ;
}