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
#include "fieldObject.h"
#include "score.h"

/******************************************************************************
マクロ定義
******************************************************************************/
const float MOVE_SPEED = 1.3f;								// 移動速度
const int DRAW_SPEED_WALK = 10;								// 描画スピード(歩き)
const int DRAW_SPEED_ATTACK = 5;							// 描画スピード(攻撃)
const int DRAW_SPEED_DAMAGE = 10;							// 描画スピード(被弾)
const int DRAW_SPEED_DEATH = 10;							// 描画スピード(死亡)
const int TEXTURE_COLUMN = 7;								// テクスチャ列分割数
const int TEXTURE_ROW = 4;									// テクスチャ行分割数
const int WALK_PATTERN = 4;									// 歩きモーションのコマ数
const int ATTACK_PATTERN = 7;								// 攻撃モーションのコマ数
const int DAMAGE_PATTERN = 2;								// 被弾モーションのコマ数
const int DEATH_PATTERN = 2;								// 死亡モーションのコマ数
const float MOVE_ATTENUATION = 0.2f;						// 移動量減衰係数
const float GRAVITY = -0.8f;								// 重力
const float GROUND = 0.0f;									// 地面の高さ
const float JUMP_POWER = 15.0f;								// ジャンプ量
const float PLAYER_COLLISIONWIDTH = 15.0f;					// 当たり判定幅
const float PLAYER_COLLISIONHEIGHT = 70.0f;					// 当たり判定高さ
const int ATTACK_CNT = DRAW_SPEED_ATTACK * ATTACK_PATTERN;  // 攻撃カウンタ
const int DAMAGE_CNT = DRAW_SPEED_DAMAGE * DAMAGE_PATTERN * 3;  // ダメージカウンタ
const int DEATH_CNT = 180;									// ダメージカウンタ
const int SLASH_CNT = 20;									// 斬撃の発生
const float MOVE_MAX = 50.0f;								// 速度の制限
const int LIFE_MAX = 100;									// ライフ最大値
const float ALFA_SPEED = 0.1f;								// アルファ値加減速度
const float ALFA_LIMIT = 0.1f;								// アルファ値限界値
const int DAMAGE_VALUE = 25;								// ダメージ値

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
	m_Hp = m_HpMax = LIFE_MAX;
	m_fAlfaSpeed = -ALFA_SPEED;
	m_pMyscore = NULL;
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
	m_OldPos = m_Pos;
	if (m_Hp <= 0 && CFade::Get(FADE_NONE))
	{
		//CFade::Start( new CResult );
	}
	if (m_Hp <= 0)
	{
		m_Hp = 0;
		SetState(STATE_DEATH);
	}

	if (CInput::GetKeyboardTrigger(DIK_G) && m_nState == STATE_WALK)
	{// 攻撃
		SetState(STATE_ATTACK);
	}

	// 移動
	if (CInput::GetKeyboardPress(DIK_A) && m_nState != STATE_ATTACK)
	{// 左移動
		m_nDirection = -1;
		m_Move.x -= MOVE_SPEED;
	}
	if (CInput::GetKeyboardPress(DIK_D) && m_nState != STATE_ATTACK)
	{// 右移動
		m_nDirection = 1;
		m_Move.x += MOVE_SPEED;
	}
	// 移動量の減衰
	m_Move.x += (0.0f - m_Move.x) * MOVE_ATTENUATION;

	if (CInput::GetKeyboardTrigger(DIK_SPACE) && !m_Jump)
	{// ジャンプ
		m_Jump = true;
		m_Move.y = JUMP_POWER;
	}

	// 重力の加算
	m_Move.y += GRAVITY;

	// 速度の制限
	if (m_Move.x > MOVE_MAX)
	{
		m_Move.x = MOVE_MAX;
	}
	else if (m_Move.x < -MOVE_MAX)
	{
		m_Move.x = -MOVE_MAX;
	}
	if (m_Move.y > MOVE_MAX)
	{
		m_Move.y = MOVE_MAX;
	}
	else if (m_Move.y < -MOVE_MAX)
	{
		m_Move.y = -MOVE_MAX;
	}
	// 位置の更新
	m_Pos += m_Move;

	if (m_Pos.y - m_Collision.y * 0.5f <= GROUND)
	{// 地面判定
		m_Jump = false;
		m_Pos.y = GROUND + m_Collision.y * 0.5f;
	}

	// 当たり判定更新
	UpdateCollision();

	// 状態更新
	UpdateState();

	// アニメーション更新
	UpdateAnimation();
	//	データ送信。
	if (m_pMyscore)
	{
		m_Score = m_pMyscore->GetScore();
	}
	
	CSync::Send(m_Pos, m_Score, m_nDirection, m_nState );
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
void CPlayer::HitCheck(Vector3 pos, float width, float height)
{
	if (abs(m_Pos.x - pos.x) < (m_Collision.x + width) * 0.5f && abs(m_Pos.y - pos.y) < (m_Collision.y + height) * 0.5f)
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
	int drawCnt[STATE_MAX] = { DRAW_SPEED_WALK, DRAW_SPEED_ATTACK, DRAW_SPEED_DAMAGE, DRAW_SPEED_DEATH };
	int patternCnt[STATE_MAX] = { WALK_PATTERN, ATTACK_PATTERN, DAMAGE_PATTERN, DEATH_PATTERN };
	int animCnt[STATE_MAX] = { ANIM_ROW_WALK, ANIM_ROW_ATTACK, ANIM_ROW_DAMAGE, ANIM_ROW_DEATH };

	m_nRowAnim = animCnt[m_nState];

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
	case STATE_DEATH:
		m_fAlfa += m_fAlfaSpeed;
		if (m_fAlfa <= ALFA_LIMIT || m_fAlfa >= 1.0f)
		{
			m_fAlfaSpeed = -m_fAlfaSpeed;
		}
		if (m_nStateCnt >= DEATH_CNT)
		{
			SetState(STATE_WALK);		// 歩行状態に移行
			m_Hp = m_HpMax;
			m_fAlfa = 1.0f;
		}
		break;
	default:
		break;
	}
}

/******************************************************************************
関数名 : UpdateCollision
引数   : void
戻り値 : void
説明   : 状態更新
******************************************************************************/
void CPlayer::UpdateCollision(void)
{
	CScene *pScene = CScene::GetList(PRIORITY_3D);
	while (pScene)
	{
		if (pScene->GetObjtype(pScene) == OBJ_TYPE_ENEMY)
		{// 敵との当たり判定
			CEnemy *pEnemy = (CEnemy*)pScene;
			if (pEnemy->GetUse())
			{
				if (m_nState != STATE_DEATH && m_nState != STATE_DAMAGE)
				{
					Vector3 pos = pEnemy->GetPosition();
					Vector2 collision = pEnemy->GetCollision();
					if (abs(m_Pos.x - pos.x) < (m_Collision.x + collision.x) * 0.5f && abs(m_Pos.y - pos.y) < (m_Collision.y + collision.y) * 0.5f)
					{
						m_Hp -= DAMAGE_VALUE;
						// 状態を被弾状態に
						SetState(STATE_DAMAGE);
					}
				}
			}
		}
		else if (pScene->GetObjtype(pScene) == OBJ_TYPE_FIELDOBJ)
		{// フィールドオブジェクトとの当たり判定
			CFieldObject *pObject = (CFieldObject*)pScene;
			if (pObject->HitCheck(m_Pos, m_Collision.x, m_Collision.y))
			{
				// 
				if (m_OldPos.y >= pObject->GetPos().y + (pObject->GetCollision().y + m_Collision.y) * 0.5f
					|| m_OldPos.y <= pObject->GetPos().y - (pObject->GetCollision().y + m_Collision.y) * 0.5f)
				{
					if (m_Move.y < 0)
					{
						m_Pos.y = pObject->GetPos().y + (pObject->GetCollision().y + m_Collision.y) * 0.5f;
						m_Move.y = 0.0f;
						m_Jump = false;
					}
					else if (m_Move.y > 0)
					{
						m_Pos.y = pObject->GetPos().y - (pObject->GetCollision().y + m_Collision.y) * 0.5f;
						m_Move.y = 0.0f;
					}
					else
					{
						m_Pos.x -= m_Move.x;
					}
				}
				else
				{
					m_Pos.x -= m_Move.x;
				}
			}
		}
		pScene = pScene->GetNext(pScene);
	}
}