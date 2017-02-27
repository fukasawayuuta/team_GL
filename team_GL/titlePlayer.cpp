/******************************************************************************
	�^�C�g�����FtitlePlayer
	�t�@�C�����FtitlePlayer.cpp
	�쐬��    �FAT-13B-284 10 �����@��
	�쐬��    �F2017/02/13
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

#include "titlePlayer.h"


/******************************************************************************
	�}�N����`
******************************************************************************/
const float MOVE_SPEED = 1.0f;								// �ړ����x
const int DRAW_SPEED_WALK = 7;								// �`��X�s�[�h(����)
const int DRAW_SPEED_ATTACK = 5;							// �`��X�s�[�h(�U��)
const int DRAW_SPEED_DAMAGE = 10;							// �`��X�s�[�h(��e)
const int TEXTURE_COLUMN = 7;								// �e�N�X�`���񕪊���
const int TEXTURE_ROW = 3;									// �e�N�X�`���s������
const int WALK_PATTERN = 4;									// �������[�V�����̃R�}��
const int ATTACK_PATTERN = 7;								// �U�����[�V�����̃R�}��
const int DAMAGE_PATTERN = 2;								// ��e���[�V�����̃R�}��
const float MOVE_ATTENUATION = 0.2f;						// �ړ��ʌ����W��
const float GRAVITY = -5.0f;								// �d��
const float GROUND = 0.0f;									// �n�ʂ̍���
const float JUMP_POWER = 30.0f;								// �W�����v��
const float PLAYER_COLLISIONWIDTH = 15.0f;					// �����蔻�蕝
const float PLAYER_COLLISIONHEIGHT = 80.0f;					// �����蔻�荂��
const int ATTACK_CNT = DRAW_SPEED_ATTACK * ATTACK_PATTERN;  // �U���J�E���^
const int DAMAGE_CNT = DRAW_SPEED_DAMAGE * DAMAGE_PATTERN;  // �_���[�W�J�E���^
const int SLASH_CNT = 20;


/******************************************************************************
	�֐��� : CTitlePlayer::CTitlePlayer(int Priority, OBJ_TYPE objType) : CAnimationBoard(Priority, objType)
	����   : �R���X�g���N�^
******************************************************************************/
CTitlePlayer::CTitlePlayer(int Priority, OBJ_TYPE objType) : CAnimationBoard(Priority, objType)
{
	m_nState = STATE_WALK;
	m_nStateCnt = 0;
	m_Move = Vector3(0.0f, 0.0f, 0.0f);
	m_nTexRow = TEXTURE_ROW;
	m_nTexColumn = TEXTURE_COLUMN;
	m_nDirection = 1;
	m_Time = 0;
}

/******************************************************************************
	�֐��� : CTitlePlayer::~CTitlePlayer()
	����   : �f�X�g���N�^
******************************************************************************/
CTitlePlayer::~CTitlePlayer()
{
}

/******************************************************************************
	�֐��� : void CTitlePlayer::Init(Vector3 pos, float width, float height)
	����   : void
	�߂�l : �Ȃ�
	����   : ����������
******************************************************************************/
void CTitlePlayer::Init(Vector3 pos, float width, float height)
{
	m_Pos = pos;
	m_Rot = Vector3(0.0f, 0.0f, 0.0f);
	m_Scl = Vector3(1.0f, 1.0f, 1.0f);

	m_Width = width;
	m_Height = height;
	m_Depth = 0.0f;

	m_Jump = false;

	m_Collision = Vector2(PLAYER_COLLISIONWIDTH, PLAYER_COLLISIONHEIGHT);

	m_nTexIdx = CTexture::SetTexture(TEXTURE_TYPE_PLAYER000);
}

/******************************************************************************
	�֐��� : void CTitlePlayer::Uninit(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �I������
******************************************************************************/
void CTitlePlayer::Uninit(void)
{
}

/******************************************************************************
	�֐��� : void CTitlePlayer::Update(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �X�V����
******************************************************************************/
void CTitlePlayer::Update(void)
{

	//if( m_Hp <= 0 && CFade::Get( FADE_NONE ) )
	//{
	//	//CFade::Start( new CResult );
	//}

	//if( CInput::GetKeyboardTrigger( DIK_G ) && m_nState == STATE_WALK)
	//{// �U��
	//	SetState(STATE_ATTACK);
	//}

	//// �ړ�
	//if(CInput::GetKeyboardPress(DIK_A) && m_nState != STATE_ATTACK)
	//{// ���ړ�
	//	m_nDirection = -1;
	//	m_Move.x -= MOVE_SPEED;
	//}
	//if(CInput::GetKeyboardPress(DIK_D) && m_nState != STATE_ATTACK)
	//{// �E�ړ�
	//	m_nDirection = 1;
	//	m_Move.x += MOVE_SPEED;
	//}
	//// �ړ��ʂ̌���
	//m_Move.x += (0.0f - m_Move.x) * MOVE_ATTENUATION;
	//
	//if( CInput::GetKeyboardTrigger( DIK_SPACE ) && !m_Jump )
	//{// �W�����v
	//	m_Jump = true;
	//	m_Move.y = JUMP_POWER;
	//}

	// ���l�����̎���( 0.7f ~ 1.0f )�ƊԊu�ŕς���
	m_Time++;
	m_Pos.x = ( ( cosf( PI / 120 * m_Time ) - 1 ) / 2 + 0.5f ) * 150.0f;

	m_Pos.y = 0;

	// �d�͂̉��Z
	m_Move.y += GRAVITY;

	// �ʒu�̍X�V
	m_Pos += m_Move;

	if( m_Pos.y - m_Width / 2 <= GROUND )
	{
		m_Jump = false;
		m_Pos.y = GROUND + m_Width / 2 + 10;
	}

	// ��ԍX�V
	UpdateState();

	// �A�j���[�V�����X�V
	UpdateAnimation();

}

/******************************************************************************
	�֐��� : void CTitlePlayer::Draw(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �`�揈���B
******************************************************************************/
void CTitlePlayer::Draw(void)
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
	glDepthMask(GL_FALSE);
	//	�`��J�n
	glBegin(GL_TRIANGLE_STRIP);

	//	�F�ݒ�
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	//	�@���ݒ�
	glNormal3f(0.0f, 1.0f, 0.0f);

	//	���_���W�ݒ�
	if (m_nDirection < 0)
	{
		glTexCoord2d(m_nPatternAnim * (1.0 / m_nTexColumn), m_nRowAnim * (1.0 / m_nTexRow));
		glVertex3f(-m_Width * 0.5f + m_Pos.x, m_Height * 0.5f + m_Pos.y, -0.9997f);

		glTexCoord2d(m_nPatternAnim * (1.0 / m_nTexColumn), m_nRowAnim * (1.0 / m_nTexRow) + (1.0 / m_nTexRow));
		glVertex3f(-m_Width * 0.5f + m_Pos.x, -m_Height * 0.5f + m_Pos.y, -0.9997f);

		glTexCoord2d(m_nPatternAnim * (1.0 / m_nTexColumn) + (1.0 / m_nTexColumn), m_nRowAnim * (1.0 / m_nTexRow));
		glVertex3f(m_Width * 0.5f + m_Pos.x, m_Height * 0.5f + m_Pos.y, -0.9997f);

		glTexCoord2d(m_nPatternAnim * (1.0 / m_nTexColumn) + (1.0 / m_nTexColumn), m_nRowAnim * (1.0 / m_nTexRow) + (1.0 / m_nTexRow));
		glVertex3f(m_Width * 0.5f + m_Pos.x, -m_Height * 0.5f + m_Pos.y, -0.9997f);
	}
	else if (m_nDirection > 0)
	{
		glTexCoord2d(m_nPatternAnim * (1.0 / m_nTexColumn) + (1.0 / m_nTexColumn), m_nRowAnim * (1.0 / m_nTexRow));
		glVertex3f(-m_Width * 0.5f + m_Pos.x, m_Height * 0.5f + m_Pos.y, -0.9997f);

		glTexCoord2d(m_nPatternAnim * (1.0 / m_nTexColumn) + (1.0 / m_nTexColumn), m_nRowAnim * (1.0 / m_nTexRow) + (1.0 / m_nTexRow));
		glVertex3f(-m_Width * 0.5f + m_Pos.x, -m_Height * 0.5f + m_Pos.y, -0.9997f);

		glTexCoord2d(m_nPatternAnim * (1.0 / m_nTexColumn), m_nRowAnim * (1.0 / m_nTexRow));
		glVertex3f(m_Width * 0.5f + m_Pos.x, m_Height * 0.5f + m_Pos.y, -0.9997f);

		glTexCoord2d(m_nPatternAnim * (1.0 / m_nTexColumn), m_nRowAnim * (1.0 / m_nTexRow) + (1.0 / m_nTexRow));
		glVertex3f(m_Width * 0.5f + m_Pos.x, -m_Height * 0.5f + m_Pos.y, -0.9997f);
	}

	glEnd();
	// �`��I��

	glEnable(GL_LIGHTING);
	glDepthMask(GL_TRUE);
	glBindTexture(GL_TEXTURE_2D, 0);
    //�@�e�N�X�`���}�b�s���O������
    glDisable(GL_TEXTURE_2D);

	//	��������}�g���b�N�X�����ɖ߂�//////////////////////////////
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	//	�����܂Ń}�g���b�N�X�����ɖ߂�//////////////////////////////
}

/******************************************************************************
	�֐��� : CTitlePlayer *CTitlePlayer::Create(Vector3 pos, float width, float height)
	����   :void
	�߂�l : obj
	����   : �쐬�֐��B 
******************************************************************************/
CTitlePlayer *CTitlePlayer::Create(Vector3 pos, float width, float height)
{
	CTitlePlayer *obj = new CTitlePlayer;
	obj->Init(pos, width, height);

	return obj;
}

/******************************************************************************
�֐��� : UpdateAnimation
����   : void
�߂�l : void
����   : �A�j���[�V��������
******************************************************************************/
void CTitlePlayer::UpdateAnimation(void)
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
void CTitlePlayer::SetState(int state)
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
void CTitlePlayer::UpdateState(void)
{
	m_nStateCnt++;

	switch (m_nState)
	{
	case STATE_WALK:
		break;
	case STATE_ATTACK:
		if (m_nStateCnt == SLASH_CNT)
		{
			//CSlashEffect::Create(m_Pos, m_nDirection, 40.0f, 80.0f, TEXTURE_TYPE_EFFECT_SLASH);
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