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

/******************************************************************************
	マクロ定義
******************************************************************************/
const float MOVE_SPEED = 1.0f;			// 移動速度
const int DRAW_SPEED = 10;				// 描画スピード
const int TEXTURE_COLUMN = 7;			// テクスチャ列分割数
const int TEXTURE_ROW = 3;				// テクスチャ行分割数
const int WALK_DRAW = 4;				// 歩きモーションのコマ数
const float MOVE_ATTENUATION = 0.2f;	// 移動量減衰係数

/******************************************************************************
	関数名 : CPlayer::CPlayer(int Priority, OBJ_TYPE objType) : CAnimationBoard(Priority, objType)
	説明   : コンストラクタ
******************************************************************************/
CPlayer::CPlayer(int Priority, OBJ_TYPE objType) : CAnimationBoard(Priority, objType)
{
	m_State = STATE_WALK;
	m_Move = Vector3(0.0f, 0.0f, 0.0f);

	m_nTexRow = TEXTURE_ROW;
	m_nTexColumn = TEXTURE_COLUMN;
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
	// 移動
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
	// 移動量の減衰
	m_Move.x += (0.0f - m_Move.x) * MOVE_ATTENUATION;
	// 位置の更新
	m_Pos += m_Move;

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