#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "scene.h"
#include "scene3D.h"
#include "animationBoard.h"
#include "enemy.h"
#include "squid.h"
#include "sync.h"

const float MOVEMENT = 100.0f;
const int   JUMP_CNT = 300;
const float GRAVITY = 0.8f;

CSquid::CSquid(int Priority, OBJ_TYPE objType) : CEnemy(Priority, objType)
{
	m_nTexRow = 1;
	m_nTexColumn = 2;
	m_Alive = true;
	m_Movement = MOVEMENT;
	m_Jump = false;
	m_StateCnt = 0;
	m_InitPosY = 0;
}

CSquid::~CSquid(void)
{
}

void CSquid::Init(Vector3 pos, float width, float height, int texIndex, int id)
{
	CEnemy::Init(pos, width, height, texIndex, id);
	m_InitPosY = pos.y;
}

void CSquid::Update(void)
{
	CEnemy::Update();
	CSync::SetEnemyState( m_nId, m_bUse );
	m_bUse = CSync::GetEnemyUse( m_nId );

	if( !m_bUse )
		return;

	// パターン描画更新
	m_nCntAnim++;
	if (m_nCntAnim == 60)
	{
		m_nCntAnim = 0;
		m_nPatternAnim++;
		if (m_nPatternAnim == 2)
		{
			m_nPatternAnim = 0;
		}
	}
	LifeCheck();
	DeleteCheck();

	m_StateCnt = (m_StateCnt + 1) % JUMP_CNT;
	if (m_StateCnt == 0) {
		m_Pos.y = m_Movement;
	}

	m_Pos.y -= GRAVITY;

	if (m_Pos.y < m_InitPosY) {
		m_Pos.y = m_InitPosY;
	}
}

void CSquid::Create(Vector3 pos, float width, float height, int texIndex, int id)
{
	CSquid *obj = new CSquid;
	obj->Init(pos, width, height, texIndex, id);
}