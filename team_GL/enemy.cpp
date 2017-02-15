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
#include "sync.h"

const int DRAW_SPEED = 30;
const int TEXTURE_COLUMN = 5;
const int TEXTURE_ROW = 1;
const int WALK_DRAW = 5;
const float ENEMY_COLLISIONWIDTH = 15.0f;
const float ENEMY_COLLISIONHEIGHT = 80.0f;
const int HP_MAX = 100;

/******************************************************************************
	�֐��� : CEnemy::CEnemy()
	����   : �R���X�g���N�^
******************************************************************************/
CEnemy::CEnemy(int Priority, OBJ_TYPE objType) : CAnimationBoard(Priority, objType)
{
	m_nTexRow = TEXTURE_ROW;
	m_nTexColumn = TEXTURE_COLUMN;
	m_Hp = HP_MAX;
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
	m_Collision = Vector2(ENEMY_COLLISIONWIDTH, ENEMY_COLLISIONHEIGHT);
	m_nTexIdx = CTexture::SetTexture(texIndex);
	m_bUse = true;
	m_nId = 0;
}

/******************************************************************************
	�֐��� : void CEnemy::Uninit(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �I������
******************************************************************************/
void CEnemy::Uninit(void)
{
	m_Delete = true;
}

/******************************************************************************
	�֐��� : void CEnemy::Update(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �X�V����
******************************************************************************/
void CEnemy::Update(void)
{
	CSync::SetEnemyState( m_nId, m_bUse );
	m_bUse = CSync::GetEnemyUse( m_nId );

	if( !m_bUse )
		return;

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
	LifeCheck();
}

/******************************************************************************
	�֐��� : void CEnemy::Draw(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �`�揈���B
******************************************************************************/
void CEnemy::Draw(void)
{
	if( m_bUse )
		CAnimationBoard::Draw();
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

/******************************************************************************
	�֐��� : HitCheck
	����   : pos, width, height
	�߂�l : �Ȃ�
	����   : �����蔻��
******************************************************************************/
void CEnemy::HitCheck( Vector3 pos, float width, float height )
{
	if( abs( m_Pos.x - pos.x ) < m_Collision.x / 2 + width / 2 && abs( m_Pos.y - pos.y ) < m_Collision.y / 2 + height / 2 )
	{
		this->Uninit();
	}
}

/******************************************************************************
�֐��� : LifeCheck
����   : void
�߂�l : �Ȃ�
����   : �����蔻��
******************************************************************************/
void CEnemy::LifeCheck(void)
{
	if (m_Hp <= 0)
	{
		//Uninit();
		m_bUse = false;
	}
}