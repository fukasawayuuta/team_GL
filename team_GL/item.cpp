/******************************************************************************
	タイトル名：Item
	ファイル名：item.cpp
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
#include "item.h"

const int DRAW_SPEED = 30;
const int TEXTURE_COLUMN = 4;
const int TEXTURE_ROW = 1;
const int WALK_DRAW = 4;
const float ITEM_COLLISIONWIDTH = 15.0f;
const float ITEM_COLLISIONHEIGHT = 80.0f;

/******************************************************************************
	関数名 : CItem::CItem()
	説明   : コンストラクタ
******************************************************************************/
CItem::CItem(int Priority, OBJ_TYPE objType) : CAnimationBoard(Priority, objType)
{
	m_nTexRow = TEXTURE_ROW;
	m_nTexColumn = TEXTURE_COLUMN;
}

/******************************************************************************
	関数名 : CItem::~CItem()
	説明   : デストラクタ
******************************************************************************/
CItem::~CItem(void)
{
}

/******************************************************************************
	関数名 : void CItem::Init(Vector3 pos, float width, float height)
	引数   : void
	戻り値 : なし
	説明   : 初期化処理
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
	関数名 : void CItem::Uninit(void)
	引数   : void
	戻り値 : なし
	説明   : 終了処理
******************************************************************************/
void CItem::Uninit(void)
{
	m_Delete = true;
}

/******************************************************************************
	関数名 : void CItem::Update(void)
	引数   : void
	戻り値 : なし
	説明   : 更新処理
******************************************************************************/
void CItem::Update(void)
{
	if( bOpen == false)
	{
		// パターン描画更新
		m_nCntAnim++;
		if (m_nCntAnim == DRAW_SPEED)
		{
			m_nCntAnim = 0;
			m_nPatternAnim++;

			// 宝箱が開くアニメーションが終わったら停止する
			if (m_nPatternAnim == WALK_DRAW - 1)
			{
				bOpen = true;
			}
		}
	}
}

/******************************************************************************
	関数名 : void CItem::Draw(void)
	引数   : void
	戻り値 : なし
	説明   : 描画処理。
******************************************************************************/
void CItem::Draw(void)
{
	CAnimationBoard::Draw();
}

/******************************************************************************
	関数名 : void CItem::Create(Vector3 pos, float width, float height)
	引数   : pos, width, height
	戻り値 : なし
	説明   : 描画処理。
******************************************************************************/
void CItem::Create(Vector3 pos, float width, float height, int texIndex)
{
	CItem *obj = new CItem;
	obj->Init(pos, width, height, texIndex);
}

/******************************************************************************
	関数名 : HitCheck
	引数   : pos, width, height
	戻り値 : なし
	説明   : 当たり判定
******************************************************************************/
void CItem::HitCheck( Vector3 pos, float width, float height )
{
	if (abs(m_Pos.x - pos.x) < (m_Collision.x + width) * 0.5f && abs(m_Pos.y - pos.y) <  (m_Collision.y + height) * 0.5f)
	{
		bOpen = true;
	}
}