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
#include "enemy.h"
#include "fade.h"
#include "mode.h"
#include "result.h"

/******************************************************************************
	�}�N����`
******************************************************************************/
const float MOVE_SPEED = 1.0f;			// �ړ����x
const int DRAW_SPEED = 10;				// �`��X�s�[�h
const int TEXTURE_COLUMN = 7;			// �e�N�X�`���񕪊���
const int TEXTURE_ROW = 3;				// �e�N�X�`���s������
const int WALK_DRAW = 4;				// �������[�V�����̃R�}��
const float MOVE_ATTENUATION = 0.2f;	// �ړ��ʌ����W��
const int GRAVITY = -5.0f;
const float GROUND = 0.0f;
const int JUMP_POWER = 30.0f;
const float PLAYER_COLLISIONWIDTH = 15.0f;
const float PLAYER_COLLISIONHEIGHT = 80.0f;

/******************************************************************************
	�֐��� : CPlayer::CPlayer(int Priority, OBJ_TYPE objType) : CAnimationBoard(Priority, objType)
	����   : �R���X�g���N�^
******************************************************************************/
CPlayer::CPlayer(int Priority, OBJ_TYPE objType) : CAnimationBoard(Priority, objType)
{
	m_State = STATE_WALK;
	m_Move = Vector3(0.0f, 0.0f, 0.0f);

	m_nTexRow = TEXTURE_ROW;
	m_nTexColumn = TEXTURE_COLUMN;
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

	m_Hp = 200;
	m_Jump = false;

	m_fCollisionWidth = PLAYER_COLLISIONWIDTH;
	m_fCollisionHeight = PLAYER_COLLISIONHEIGHT;

	m_nTexIdx = CTexture::SetTexture(TEXTURE_TYPE_PLAYER000);
}

/******************************************************************************
	�֐��� : void CPlayer::Uninit(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �I������
******************************************************************************/
void CPlayer::Uninit(void)
{
}

/******************************************************************************
	�֐��� : void CPlayer::Update(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �X�V����
******************************************************************************/
void CPlayer::Update(void)
{
	CScene *pScene = CScene::GetList( PRIORITY_3D );
	while( pScene )
	{
		if( pScene->GetObjtype( pScene ) == OBJ_TYPE_ENEMY )
		{
			CEnemy *pEnemy = ( CEnemy* )pScene;
			Vector3 pos = pEnemy->GetPosition();
			float width = pEnemy->GetWidth();
			float height = pEnemy->GetHeight();
			if( abs( m_Pos.x - pos.x ) < m_fCollisionWidth / 2 + width / 2 && abs( m_Pos.y - pos.y ) < m_fCollisionHeight / 2 + height / 2 )
			{
				m_Hp --;
			}

			if( m_State == STATE_ATTACK )
			{
				pEnemy->Uninit();
			}
		}
		pScene = pScene->GetNext( pScene );
	}

	if( m_Hp <= 0 && CFade::Get( FADE_NONE ) )
	{
		//CFade::Start( new CResult );
	}

	if( CInput::GetKeyboardTrigger( DIK_G ) )
	{
		m_State = STATE_ATTACK;
	}

	// �ړ�
	if(CInput::GetKeyboardPress(DIK_A))
	{
		m_nDirection = -1;
		m_Move.x -= MOVE_SPEED;
	}
	if(CInput::GetKeyboardPress(DIK_D))
	{
		m_nDirection = 1;
		m_Move.x += MOVE_SPEED;
	}
	// �ړ��ʂ̌���
	m_Move.x += (0.0f - m_Move.x) * MOVE_ATTENUATION;
	
	if( CInput::GetKeyboardTrigger( DIK_SPACE ) && !m_Jump )
	{
		m_Jump = true;
		m_Move.y = JUMP_POWER;
	}
	
	m_Move.y += GRAVITY;
	
	// �ʒu�̍X�V
	m_Pos += m_Move;

	if( m_Pos.y - m_Width / 2 <= GROUND )
	{
		m_Jump = false;
		m_Pos.y = GROUND + m_Width / 2;
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
	CAnimationBoard::Draw();
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

/******************************************************************************
	�֐��� : HitCheck
	����   : Vector3 pos
	�߂�l : void
	����   : �����蔻�� 
******************************************************************************/
void CPlayer::HitCheck( Vector3 pos, float width, float height )
{
	if( abs( m_Pos.x - pos.x ) < m_fCollisionWidth / 2 + width / 2 && abs( m_Pos.y - pos.y ) < m_fCollisionHeight / 2 + height / 2 )
	{
		m_Hp --;
	}
}