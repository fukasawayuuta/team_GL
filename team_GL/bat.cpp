/******************************************************************************
	�^�C�g�����FBat
	�t�@�C�����Fbat.cpp
	�쐬��    �FAT-13B-284 35 �[�V�C��
	�쐬��    �F2016/12/14
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
#include "bat.h"

/******************************************************************************
	�ÓI�ϐ��錾
******************************************************************************/
const int DRAW_SPEED = 30;
const int TEXTURE_COLUMN = 5;
const int TEXTURE_ROW = 1;
const int WALK_DRAW = 5;

const int TURN_CNT = 180;
const float MOVEMENT = 1.0f;


/******************************************************************************
	�֐��� : CBat::CBat(int Priority, OBJ_TYPE objType) : CEnemy(Priority, objType)
	����   : �R���X�g���N�^
******************************************************************************/
CBat::CBat(int Priority, OBJ_TYPE objType) : CEnemy(Priority, objType)
{
	m_StateCnt = 0;
	m_FirstYCoordinate = 0.0f;
	m_SinAngle = 0.0f;
	m_TurnFlag = false;
	m_Movement = MOVEMENT;
}

/******************************************************************************
	�֐��� : CBat::~CBat(void)
	����   : �f�X�g���N�^
******************************************************************************/
CBat::~CBat()
{
}

void CBat::Init(Vector3 pos, float width, float height, int texIndex, int id)
{
	CEnemy::Init(pos, width, height, texIndex, id);
	m_FirstYCoordinate = pos.y;
}

/******************************************************************************
	�֐��� : void CBat::Update(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �X�V����
******************************************************************************/
void CBat::Update(void)
{
	CEnemy::Update();

	if (m_TurnFlag) {
		m_Pos.x += m_Movement;
		m_nDirection = 1;
	}
	else {
		m_Pos.x -= m_Movement;
		m_nDirection = -1;
	}

	m_Pos.y = m_FirstYCoordinate + sinf(m_SinAngle) * 10.0f;

	m_SinAngle += 0.1f;

	m_StateCnt = (m_StateCnt + 1) % 180;

	if (m_StateCnt == 0) {
		m_TurnFlag = !m_TurnFlag;
	}
}

/******************************************************************************
	�֐��� : void CEnemy::Create(Vector3 pos, float width, float height)
	����   : pos, width, height
	�߂�l : �Ȃ�
	����   : �`�揈���B
******************************************************************************/
CBat * CBat::Create(Vector3 pos, float width, float height, int texIndex, int id)
{
	CBat *obj = new CBat;
	obj->Init(pos, width, height, texIndex, id);
	
	return obj;
}