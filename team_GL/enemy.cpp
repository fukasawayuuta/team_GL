/******************************************************************************
	タイトル名：Enemy
	ファイル名：enemy.cpp
	作成者    ：AT-13B-284 35 深澤佑太
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
	関数名 : CEnemy::CEnemy()
	説明   : コンストラクタ
******************************************************************************/
CEnemy::CEnemy(int Priority, OBJ_TYPE objType) : CAnimationBoard(Priority, objType)
{
	m_nTexRow = TEXTURE_ROW;
	m_nTexColumn = TEXTURE_COLUMN;
	m_Hp = HP_MAX;
}

/******************************************************************************
	関数名 : CEnemy::~CEnemy()
	説明   : デストラクタ
******************************************************************************/
CEnemy::~CEnemy(void)
{
}

/******************************************************************************
	関数名 : void CEnemy::Init(Vector3 pos, float width, float height)
	引数   : void
	戻り値 : なし
	説明   : 初期化処理
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
	関数名 : void CEnemy::Uninit(void)
	引数   : void
	戻り値 : なし
	説明   : 終了処理
******************************************************************************/
void CEnemy::Uninit(void)
{
	m_Delete = true;
}

/******************************************************************************
	関数名 : void CEnemy::Update(void)
	引数   : void
	戻り値 : なし
	説明   : 更新処理
******************************************************************************/
void CEnemy::Update(void)
{
	CSync::SetEnemyState( m_nId, m_bUse );
	m_bUse = CSync::GetEnemyUse( m_nId );

	if( !m_bUse )
		return;

	// パターン描画更新
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
	関数名 : void CEnemy::Draw(void)
	引数   : void
	戻り値 : なし
	説明   : 描画処理。
******************************************************************************/
void CEnemy::Draw(void)
{
	if( m_bUse )
		CAnimationBoard::Draw();
}

/******************************************************************************
	関数名 : void CEnemy::Create(Vector3 pos, float width, float height)
	引数   : pos, width, height
	戻り値 : なし
	説明   : 描画処理。
******************************************************************************/
void CEnemy::Create(Vector3 pos, float width, float height, int texIndex)
{
	CEnemy *obj = new CEnemy;
	obj->Init(pos, width, height, texIndex);
}

/******************************************************************************
	関数名 : HitCheck
	引数   : pos, width, height
	戻り値 : なし
	説明   : 当たり判定
******************************************************************************/
void CEnemy::HitCheck( Vector3 pos, float width, float height )
{
	if( abs( m_Pos.x - pos.x ) < m_Collision.x / 2 + width / 2 && abs( m_Pos.y - pos.y ) < m_Collision.y / 2 + height / 2 )
	{
		this->Uninit();
	}
}

/******************************************************************************
関数名 : LifeCheck
引数   : void
戻り値 : なし
説明   : 当たり判定
******************************************************************************/
void CEnemy::LifeCheck(void)
{
	if (m_Hp <= 0)
	{
		//Uninit();
		m_bUse = false;
	}
}