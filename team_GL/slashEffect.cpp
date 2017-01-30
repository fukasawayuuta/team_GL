/******************************************************************************
	タイトル名：SlashEffect
	ファイル名：slashEffect.cpp
	作成者    ：AT-13B-284 11 小野寺辰彦
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
#include "slashEffect.h"
#include "enemy.h"

const int DRAW_SPEED = 5;			// 
const int TEXTURE_COLUMN = 5;		// テクスチャ列分割数
const int TEXTURE_ROW = 1;			// テクスチャ行分割数
const int DRAW_CNT = 5;				// 描画速度
const float SLASHEFFECT_COLLISIONWIDTH = 15.0f;
const float SLASHEFFECT_COLLISIONHEIGHT = 80.0f;
const float MOVE_SPEED = 5.0f;		// 移動速度
const int DAMAGE_VALUE = 100;		// 与えるダメージ

/******************************************************************************
	関数名 : CSlashEffect::CSlashEffect()
	説明   : コンストラクタ
******************************************************************************/
CSlashEffect::CSlashEffect(int Priority, OBJ_TYPE objType) : CAnimationBoard(Priority, objType)
{
	m_nTexRow = TEXTURE_ROW;
	m_nTexColumn = TEXTURE_COLUMN;
	m_Move = Vector3(0.0f, 0.0f, 0.0f);
}

/******************************************************************************
	関数名 : CSlashEffect::~CSlashEffect()
	説明   : デストラクタ
******************************************************************************/
CSlashEffect::~CSlashEffect(void)
{
}

/******************************************************************************
	関数名 : void CSlashEffect::Init(Vector3 pos, float width, float height)
	引数   : void
	戻り値 : なし
	説明   : 初期化処理
******************************************************************************/
void CSlashEffect::Init(Vector3 pos, int direction, float width, float height, int texIndex)
{
	m_Pos = pos;
	m_Width = width;
	m_Height = height;
	m_nDirection = direction;
	m_Move = Vector3(MOVE_SPEED, 0.0f, 0.0f) * (float)m_nDirection;
	m_Collision = Vector2(width, height);
	m_nTexIdx = CTexture::SetTexture(texIndex);
}

/******************************************************************************
	関数名 : void CSlashEffect::Uninit(void)
	引数   : void
	戻り値 : なし
	説明   : 終了処理
******************************************************************************/
void CSlashEffect::Uninit(void)
{
	m_Delete = true;
}

/******************************************************************************
	関数名 : void CSlashEffect::Update(void)
	引数   : void
	戻り値 : なし
	説明   : 更新処理
******************************************************************************/
void CSlashEffect::Update(void)
{
	// 斬撃を前に飛ばす
	m_Pos += m_Move;

	UpdateCollision();

	// パターン描画更新
	m_nCntAnim++;
	if (m_nCntAnim % DRAW_SPEED == 0)
	{
		m_nPatternAnim++;

		// エフェクトのアニメーションが終わったら消去
		if (m_nPatternAnim % DRAW_CNT == 0)
		{
			Uninit();
		}
	}
}

/******************************************************************************
	関数名 : void CSlashEffect::Draw(void)
	引数   : void
	戻り値 : なし
	説明   : 描画処理。
******************************************************************************/
void CSlashEffect::Draw(void)
{
	CAnimationBoard::Draw();
}

/******************************************************************************
	関数名 : void CSlashEffect::Create(Vector3 pos, float width, float height)
	引数   : pos, width, height
	戻り値 : なし
	説明   : 描画処理。
******************************************************************************/
void CSlashEffect::Create(Vector3 pos, int direction, float width, float height, int texIndex)
{
	CSlashEffect *obj = new CSlashEffect;
	obj->Init(pos, direction, width, height, texIndex);
}

/******************************************************************************
	関数名 : HitCheck
	引数   : pos, width, height
	戻り値 : なし
	説明   : 当たり判定
******************************************************************************/
void CSlashEffect::HitCheck( Vector3 pos, float width, float height )
{
	if( abs( m_Pos.x - pos.x ) < (m_Collision.x + width) * 0.5f && abs( m_Pos.y - pos.y ) <  (m_Collision.y + height) * 0.5f )
	{
		this->Uninit();
	}
}

/******************************************************************************
関数名 : UpdateCollision
引数   : pos, width, height
戻り値 : なし
説明   : 当たり判定
******************************************************************************/
void CSlashEffect::UpdateCollision(void)
{
	CScene *pScene = CScene::GetList(PRIORITY_3D);
	while (pScene)
	{
		if (pScene->GetObjtype(pScene) == OBJ_TYPE_ENEMY)
		{
			CEnemy *pEnemy = (CEnemy*)pScene;
			Vector3 pos = pEnemy->GetPosition();
			Vector2 collision = pEnemy->GetCollision();
			if (abs(m_Pos.x - pos.x) < (m_Collision.x + collision.x) * 0.5f && abs(m_Pos.y - pos.y) < (m_Collision.y + collision.y) * 0.5f)
			{
				pEnemy->SetDamage(DAMAGE_VALUE);
			}
		}
		pScene = pScene->GetNext(pScene);
	}
}