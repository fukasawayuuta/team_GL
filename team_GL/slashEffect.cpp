/******************************************************************************
	�^�C�g�����FSlashEffect
	�t�@�C�����FslashEffect.cpp
	�쐬��    �FAT-13B-284 11 ���쎛�C�F
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
#include "slashEffect.h"

const int DRAW_SPEED = 5;
const int TEXTURE_COLUMN = 5;
const int TEXTURE_ROW = 1;
const int DRAW_CNT = 5;
const float SLASHEFFECT_COLLISIONWIDTH = 15.0f;
const float SLASHEFFECT_COLLISIONHEIGHT = 80.0f;
const float MOVE_SPEED = 5.0f;

/******************************************************************************
	�֐��� : CSlashEffect::CSlashEffect()
	����   : �R���X�g���N�^
******************************************************************************/
CSlashEffect::CSlashEffect(int Priority, OBJ_TYPE objType) : CAnimationBoard(Priority, objType)
{
	m_nTexRow = TEXTURE_ROW;
	m_nTexColumn = TEXTURE_COLUMN;
	m_Move = Vector3(0.0f, 0.0f, 0.0f);
}

/******************************************************************************
	�֐��� : CSlashEffect::~CSlashEffect()
	����   : �f�X�g���N�^
******************************************************************************/
CSlashEffect::~CSlashEffect(void)
{
}

/******************************************************************************
	�֐��� : void CSlashEffect::Init(Vector3 pos, float width, float height)
	����   : void
	�߂�l : �Ȃ�
	����   : ����������
******************************************************************************/
void CSlashEffect::Init(Vector3 pos, int direction, float width, float height, int texIndex)
{
	m_Pos = pos;
	m_Width = width;
	m_Height = height;
	m_nDirection = direction;
	m_Move = Vector3(MOVE_SPEED, 0.0f, 0.0f) * (float)m_nDirection;
	m_Collision = Vector2(SLASHEFFECT_COLLISIONWIDTH, SLASHEFFECT_COLLISIONHEIGHT);
	m_nTexIdx = CTexture::SetTexture(texIndex);
}

/******************************************************************************
	�֐��� : void CSlashEffect::Uninit(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �I������
******************************************************************************/
void CSlashEffect::Uninit(void)
{
	m_Delete = true;
}

/******************************************************************************
	�֐��� : void CSlashEffect::Update(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �X�V����
******************************************************************************/
void CSlashEffect::Update(void)
{
	// �a����O�ɔ�΂�
	m_Pos += m_Move;

	// �p�^�[���`��X�V
	m_nCntAnim++;
	if (m_nCntAnim == DRAW_SPEED)
	{
		m_nCntAnim = 0;
		m_nPatternAnim++;

		// �G�t�F�N�g�̃A�j���[�V�������I����������
		if (m_nPatternAnim == DRAW_CNT - 1)
		{
			Uninit();
		}

	}
}

/******************************************************************************
	�֐��� : void CSlashEffect::Draw(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �`�揈���B
******************************************************************************/
void CSlashEffect::Draw(void)
{
	CAnimationBoard::Draw();
}

/******************************************************************************
	�֐��� : void CSlashEffect::Create(Vector3 pos, float width, float height)
	����   : pos, width, height
	�߂�l : �Ȃ�
	����   : �`�揈���B
******************************************************************************/
void CSlashEffect::Create(Vector3 pos, int direction, float width, float height, int texIndex)
{
	CSlashEffect *obj = new CSlashEffect;
	obj->Init(pos, direction, width, height, texIndex);
}

/******************************************************************************
	�֐��� : HitCheck
	����   : pos, width, height
	�߂�l : �Ȃ�
	����   : �����蔻��
******************************************************************************/
void CSlashEffect::HitCheck( Vector3 pos, float width, float height )
{
	if( abs( m_Pos.x - pos.x ) < (m_Collision.x + width) * 0.5f && abs( m_Pos.y - pos.y ) <  (m_Collision.y + height) * 0.5f )
	{
		this->Uninit();
	}
}