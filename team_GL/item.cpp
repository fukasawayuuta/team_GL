/******************************************************************************
	�^�C�g�����FItem
	�t�@�C�����Fitem.cpp
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
#include "item.h"

const int DRAW_SPEED = 30;
const int TEXTURE_COLUMN = 4;
const int TEXTURE_ROW = 1;
const int WALK_DRAW = 4;
const float ITEM_COLLISIONWIDTH = 15.0f;
const float ITEM_COLLISIONHEIGHT = 80.0f;

/******************************************************************************
	�֐��� : CItem::CItem()
	����   : �R���X�g���N�^
******************************************************************************/
CItem::CItem(int Priority, OBJ_TYPE objType) : CAnimationBoard(Priority, objType)
{
	m_nTexRow = TEXTURE_ROW;
	m_nTexColumn = TEXTURE_COLUMN;
}

/******************************************************************************
	�֐��� : CItem::~CItem()
	����   : �f�X�g���N�^
******************************************************************************/
CItem::~CItem(void)
{
}

/******************************************************************************
	�֐��� : void CItem::Init(Vector3 pos, float width, float height)
	����   : void
	�߂�l : �Ȃ�
	����   : ����������
******************************************************************************/
void CItem::Init(Vector3 pos, float width, float height, int texIndex)
{
	m_Pos = pos;
	m_Width = width;
	m_Height = height;
	m_nDirection = 1;
	m_Collision = Vector2(ITEM_COLLISIONWIDTH, ITEM_COLLISIONHEIGHT);
	m_nTexIdx = CTexture::SetTexture(texIndex);

	bOpen = false;
}

/******************************************************************************
	�֐��� : void CItem::Uninit(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �I������
******************************************************************************/
void CItem::Uninit(void)
{
	m_Delete = true;
}

/******************************************************************************
	�֐��� : void CItem::Update(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �X�V����
******************************************************************************/
void CItem::Update(void)
{
	if( bOpen == false)
	{
		// �p�^�[���`��X�V
		m_nCntAnim++;
		if (m_nCntAnim == DRAW_SPEED)
		{
			m_nCntAnim = 0;
			m_nPatternAnim++;

			// �󔠂��J���A�j���[�V�������I��������~����
			if (m_nPatternAnim == WALK_DRAW - 1)
			{
				bOpen = true;
			}
		}
	}
}

/******************************************************************************
	�֐��� : void CItem::Draw(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �`�揈���B
******************************************************************************/
void CItem::Draw(void)
{
	CAnimationBoard::Draw();
}

/******************************************************************************
	�֐��� : void CItem::Create(Vector3 pos, float width, float height)
	����   : pos, width, height
	�߂�l : �Ȃ�
	����   : �`�揈���B
******************************************************************************/
void CItem::Create(Vector3 pos, float width, float height, int texIndex)
{
	CItem *obj = new CItem;
	obj->Init(pos, width, height, texIndex);
}

/******************************************************************************
	�֐��� : HitCheck
	����   : pos, width, height
	�߂�l : �Ȃ�
	����   : �����蔻��
******************************************************************************/
void CItem::HitCheck( Vector3 pos, float width, float height )
{
	if (abs(m_Pos.x - pos.x) < (m_Collision.x + width) * 0.5f && abs(m_Pos.y - pos.y) <  (m_Collision.y + height) * 0.5f)
	{
		bOpen = true;
	}
}