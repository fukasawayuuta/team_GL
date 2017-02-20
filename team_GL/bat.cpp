/******************************************************************************
	タイトル名：Bat
	ファイル名：bat.cpp
	作成者    ：AT-13B-284 35 深澤佑太
	作成日    ：2016/12/14
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
#include "bat.h"

/******************************************************************************
	静的変数宣言
******************************************************************************/
const int DRAW_SPEED = 30;
const int TEXTURE_COLUMN = 5;
const int TEXTURE_ROW = 1;
const int WALK_DRAW = 5;

const int TURN_CNT = 180;
const float MOVEMENT = 1.0f;


/******************************************************************************
	関数名 : CBat::CBat(int Priority, OBJ_TYPE objType) : CEnemy(Priority, objType)
	説明   : コンストラクタ
******************************************************************************/
CBat::CBat(int Priority, OBJ_TYPE objType) : CEnemy(Priority, objType)
{
	m_StateCnt = 0;
	m_FirstYCoordinate = 0.0f;
	m_SinAngle = 0.0f;
	m_TurnFlag = false;
	m_Movement = MOVEMENT;
}

/******************************************************************************
	関数名 : CBat::~CBat(void)
	説明   : デストラクタ
******************************************************************************/
CBat::~CBat()
{
}

void CBat::Init(Vector3 pos, float width, float height, int texIndex, int id)
{
	CEnemy::Init(pos, width, height, texIndex, id);
	m_FirstYCoordinate = pos.y;
}

/******************************************************************************
	関数名 : void CBat::Update(void)
	引数   : void
	戻り値 : なし
	説明   : 更新処理
******************************************************************************/
void CBat::Update(void)
{
	CEnemy::Update();

	if (m_TurnFlag) {
		m_Pos.x += m_Movement;
		m_nDirection = 1;
	}
	else {
		m_Pos.x -= m_Movement;
		m_nDirection = -1;
	}

	m_Pos.y = m_FirstYCoordinate + sinf(m_SinAngle) * 10.0f;

	m_SinAngle += 0.1f;

	m_StateCnt = (m_StateCnt + 1) % 180;

	if (m_StateCnt == 0) {
		m_TurnFlag = !m_TurnFlag;
	}
}

/******************************************************************************
	関数名 : void CEnemy::Create(Vector3 pos, float width, float height)
	引数   : pos, width, height
	戻り値 : なし
	説明   : 描画処理。
******************************************************************************/
CBat * CBat::Create(Vector3 pos, float width, float height, int texIndex, int id)
{
	CBat *obj = new CBat;
	obj->Init(pos, width, height, texIndex, id);
	
	return obj;
}