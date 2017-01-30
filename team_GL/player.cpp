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
#include "game.h"
#include "result.h"
#include "camera.h"
#include "sync.h"
#include "slashEffect.h"

/******************************************************************************
	�}�N����`
******************************************************************************/
const float MOVE_SPEED = 1.3f;								// �ړ����x
const int DRAW_SPEED_WALK = 10;								// �`��X�s�[�h(����)
const int DRAW_SPEED_ATTACK = 5;							// �`��X�s�[�h(�U��)
const int DRAW_SPEED_DAMAGE = 10;							// �`��X�s�[�h(��e)
const int TEXTURE_COLUMN = 7;								// �e�N�X�`���񕪊���
const int TEXTURE_ROW = 3;									// �e�N�X�`���s������
const int WALK_PATTERN = 4;									// �������[�V�����̃R�}��
const int ATTACK_PATTERN = 7;								// �U�����[�V�����̃R�}��
const int DAMAGE_PATTERN = 2;								// ��e���[�V�����̃R�}��
const float MOVE_ATTENUATION = 0.2f;						// �ړ��ʌ����W��
const float GRAVITY = -0.8f;								// �d��
const float GROUND = 0.0f;									// �n�ʂ̍���
const float JUMP_POWER = 15.0f;								// �W�����v��
const float PLAYER_COLLISIONWIDTH = 15.0f;					// �����蔻�蕝
const float PLAYER_COLLISIONHEIGHT = 80.0f;					// �����蔻�荂��
const int ATTACK_CNT = DRAW_SPEED_ATTACK * ATTACK_PATTERN;  // �U���J�E���^
const int DAMAGE_CNT = DRAW_SPEED_DAMAGE * DAMAGE_PATTERN;  // �_���[�W�J�E���^
const int SLASH_CNT = 20;

/******************************************************************************
	�֐��� : CPlayer::CPlayer(int Priority, OBJ_TYPE objType) : CAnimationBoard(Priority, objType)
	����   : �R���X�g���N�^
******************************************************************************/
CPlayer::CPlayer(int Priority, OBJ_TYPE objType) : CAnimationBoard(Priority, objType)
{
	m_nState = STATE_WALK;
	m_nStateCnt = 0;
	m_Move = Vector3(0.0f, 0.0f, 0.0f);
	m_Score = 0;
	m_nTexRow = TEXTURE_ROW;
	m_nTexColumn = TEXTURE_COLUMN;
	m_nDirection = 1;
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

	m_Collision = Vector2(PLAYER_COLLISIONWIDTH, PLAYER_COLLISIONHEIGHT);

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
			Vector2 collision = pEnemy->GetCollision();
			if( abs( m_Pos.x - pos.x ) < (m_Collision.x + collision.x) * 0.5f && abs( m_Pos.y - pos.y ) < (m_Collision.y + collision.y) * 0.5f )
			{
				m_Hp --;
				// ��Ԃ��e��Ԃ�
				SetState(STATE_DAMAGE);
			}
		}
		pScene = pScene->GetNext( pScene );
	}

	if( m_Hp <= 0 && CFade::Get( FADE_NONE ) )
	{
		//CFade::Start( new CResult );
	}

	if( CInput::GetKeyboardTrigger( DIK_G ) && m_nState == STATE_WALK)
	{// �U��
		SetState(STATE_ATTACK);
	}

	// �ړ�
	if(CInput::GetKeyboardPress(DIK_A) && m_nState != STATE_ATTACK)
	{// ���ړ�
		m_nDirection = -1;
		m_Move.x -= MOVE_SPEED;
	}
	if(CInput::GetKeyboardPress(DIK_D) && m_nState != STATE_ATTACK)
	{// �E�ړ�
		m_nDirection = 1;
		m_Move.x += MOVE_SPEED;
	}
	// �ړ��ʂ̌���
	m_Move.x += (0.0f - m_Move.x) * MOVE_ATTENUATION;
	
	if( CInput::GetKeyboardTrigger( DIK_SPACE ) && !m_Jump )
	{// �W�����v
		m_Jump = true;
		m_Move.y = JUMP_POWER;
	}
	
	// �d�͂̉��Z
	m_Move.y += GRAVITY;
	
	// �ʒu�̍X�V
	m_Pos += m_Move;

	if( m_Pos.y - m_Width / 2 <= GROUND )
	{
		m_Jump = false;
		m_Pos.y = GROUND + m_Width / 2;
	}

	// ��ԍX�V
	UpdateState();

	// �A�j���[�V�����X�V
	UpdateAnimation();
	//	�f�[�^���M�B
	CSync::Send(m_Pos, m_Score);
	// �J�����̒Ǐ]
	CGame *game = (CGame*)CManager::GetMode();
	CCamera *camera = game->GetCamera();
	camera->SetPosition(m_Pos.x);
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
	if( abs( m_Pos.x - pos.x ) < (m_Collision.x + width) * 0.5f && abs( m_Pos.y - pos.y ) < (m_Collision.y + height) * 0.5f )
	{
		m_Hp--;
	}
}

/******************************************************************************
�֐��� : UpdateAnimation
����   : void
�߂�l : void
����   : �A�j���[�V��������
******************************************************************************/
void CPlayer::UpdateAnimation(void)
{
	int drawCnt[STATE_MAX] = { DRAW_SPEED_WALK, DRAW_SPEED_ATTACK, DRAW_SPEED_DAMAGE };
	int patternCnt[STATE_MAX] = { WALK_PATTERN, ATTACK_PATTERN, DAMAGE_PATTERN };

	m_nRowAnim = m_nState;

	// �p�^�[���`��X�V
	m_nCntAnim++;
	if (m_nCntAnim >= drawCnt[m_nState])
	{
		m_nCntAnim = 0;
		m_nPatternAnim++;
		if (m_nPatternAnim >= patternCnt[m_nState])
		{
			m_nPatternAnim = 0;
		}
	}
}

/******************************************************************************
�֐��� : SetState
����   : int state
�߂�l : void
����   : ��Ԑݒ�
******************************************************************************/
void CPlayer::SetState(int state)
{
	if (m_nState != state)
	{
		m_nState = state;
		m_nPatternAnim = 0;
		m_nStateCnt = 0;
	}
}

/******************************************************************************
�֐��� : UpdateState
����   : void
�߂�l : void
����   : ��ԍX�V
******************************************************************************/
void CPlayer::UpdateState(void)
{
	m_nStateCnt++;

	switch (m_nState)
	{
	case STATE_WALK:
		break;
	case STATE_ATTACK:
		if (m_nStateCnt == SLASH_CNT)
		{
			CSlashEffect::Create(m_Pos, m_nDirection, 160.0f, 80.0f, TEXTURE_TYPE_EFFECT_SLASH);
		}
		if (m_nStateCnt >= ATTACK_CNT)
		{
			SetState(STATE_WALK);
		}
		break;
	case STATE_DAMAGE:
		if (m_nStateCnt >= DAMAGE_CNT)
		{
			SetState(STATE_WALK);
		}
		break;
	default:
		break;
	}
}