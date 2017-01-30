/******************************************************************************
	タイトル名：player
	ファイル名：player.cpp
	作成者    ：AT-13B-284 10 小笠原啓太
	作成日    ：2016/12/05
******************************************************************************/
/******************************************************************************
	インクルードファイル
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
	マクロ定義
******************************************************************************/
const float MOVE_SPEED = 1.3f;								// 移動速度
const int DRAW_SPEED_WALK = 10;								// 描画スピード(歩き)
const int DRAW_SPEED_ATTACK = 5;							// 描画スピード(攻撃)
const int DRAW_SPEED_DAMAGE = 10;							// 描画スピード(被弾)
const int TEXTURE_COLUMN = 7;								// テクスチャ列分割数
const int TEXTURE_ROW = 3;									// テクスチャ行分割数
const int WALK_PATTERN = 4;									// 歩きモーションのコマ数
const int ATTACK_PATTERN = 7;								// 攻撃モーションのコマ数
const int DAMAGE_PATTERN = 2;								// 被弾モーションのコマ数
const float MOVE_ATTENUATION = 0.2f;						// 移動量減衰係数
const float GRAVITY = -0.8f;								// 重力
const float GROUND = 0.0f;									// 地面の高さ
const float JUMP_POWER = 15.0f;								// ジャンプ量
const float PLAYER_COLLISIONWIDTH = 15.0f;					// 当たり判定幅
const float PLAYER_COLLISIONHEIGHT = 80.0f;					// 当たり判定高さ
const int ATTACK_CNT = DRAW_SPEED_ATTACK * ATTACK_PATTERN;  // 攻撃カウンタ
const int DAMAGE_CNT = DRAW_SPEED_DAMAGE * DAMAGE_PATTERN;  // ダメージカウンタ
const int SLASH_CNT = 20;

/******************************************************************************
	関数名 : CPlayer::CPlayer(int Priority, OBJ_TYPE objType) : CAnimationBoard(Priority, objType)
	説明   : コンストラクタ
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
	関数名 : CPlayer::~CPlayer()
	説明   : デストラクタ
******************************************************************************/
CPlayer::~CPlayer()
{
}

/******************************************************************************
	関数名 : void CPlayer::Init(Vector3 pos, float width, float height)
	引数   : void
	戻り値 : なし
	説明   : 初期化処理
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
	関数名 : void CPlayer::Uninit(void)
	引数   : void
	戻り値 : なし
	説明   : 終了処理
******************************************************************************/
void CPlayer::Uninit(void)
{
}

/******************************************************************************
	関数名 : void CPlayer::Update(void)
	引数   : void
	戻り値 : なし
	説明   : 更新処理
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
				// 状態を被弾状態に
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
	{// 攻撃
		SetState(STATE_ATTACK);
	}

	// 移動
	if(CInput::GetKeyboardPress(DIK_A) && m_nState != STATE_ATTACK)
	{// 左移動
		m_nDirection = -1;
		m_Move.x -= MOVE_SPEED;
	}
	if(CInput::GetKeyboardPress(DIK_D) && m_nState != STATE_ATTACK)
	{// 右移動
		m_nDirection = 1;
		m_Move.x += MOVE_SPEED;
	}
	// 移動量の減衰
	m_Move.x += (0.0f - m_Move.x) * MOVE_ATTENUATION;
	
	if( CInput::GetKeyboardTrigger( DIK_SPACE ) && !m_Jump )
	{// ジャンプ
		m_Jump = true;
		m_Move.y = JUMP_POWER;
	}
	
	// 重力の加算
	m_Move.y += GRAVITY;
	
	// 位置の更新
	m_Pos += m_Move;

	if( m_Pos.y - m_Width / 2 <= GROUND )
	{
		m_Jump = false;
		m_Pos.y = GROUND + m_Width / 2;
	}

	// 状態更新
	UpdateState();

	// アニメーション更新
	UpdateAnimation();
	//	データ送信。
	CSync::Send(m_Pos, m_Score);
	// カメラの追従
	CGame *game = (CGame*)CManager::GetMode();
	CCamera *camera = game->GetCamera();
	camera->SetPosition(m_Pos.x);
}

/******************************************************************************
	関数名 : void CPlayer::Draw(void)
	引数   : void
	戻り値 : なし
	説明   : 描画処理。
******************************************************************************/
void CPlayer::Draw(void)
{
	CAnimationBoard::Draw();
}

/******************************************************************************
	関数名 : CPlayer *CPlayer::Create(Vector3 pos, float width, float height)
	引数   :void
	戻り値 : obj
	説明   : 作成関数。 
******************************************************************************/
CPlayer *CPlayer::Create(Vector3 pos, float width, float height)
{
	CPlayer *obj = new CPlayer;
	obj->Init(pos, width, height);

	return obj;
}

/******************************************************************************
	関数名 : HitCheck
	引数   : Vector3 pos
	戻り値 : void
	説明   : 当たり判定 
******************************************************************************/
void CPlayer::HitCheck( Vector3 pos, float width, float height )
{
	if( abs( m_Pos.x - pos.x ) < (m_Collision.x + width) * 0.5f && abs( m_Pos.y - pos.y ) < (m_Collision.y + height) * 0.5f )
	{
		m_Hp--;
	}
}

/******************************************************************************
関数名 : UpdateAnimation
引数   : void
戻り値 : void
説明   : アニメーション処理
******************************************************************************/
void CPlayer::UpdateAnimation(void)
{
	int drawCnt[STATE_MAX] = { DRAW_SPEED_WALK, DRAW_SPEED_ATTACK, DRAW_SPEED_DAMAGE };
	int patternCnt[STATE_MAX] = { WALK_PATTERN, ATTACK_PATTERN, DAMAGE_PATTERN };

	m_nRowAnim = m_nState;

	// パターン描画更新
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
関数名 : SetState
引数   : int state
戻り値 : void
説明   : 状態設定
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
関数名 : UpdateState
引数   : void
戻り値 : void
説明   : 状態更新
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