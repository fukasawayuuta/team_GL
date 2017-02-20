#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "scene.h"
#include "scene3D.h"
#include "animationBoard.h"
#include "enemy.h"
#include "slime.h"

const float MOVEMENT = 0.25f;
const int TURN_CNT = 300;

CSlime::CSlime(void)
{
	m_nTexRow = 2;
	m_nTexColumn = 3;
	m_Alive = true;
	m_Movement = MOVEMENT;
	m_TurnFlag = false;
	m_StateCnt = 0;
}


CSlime::~CSlime(void)
{
}

void CSlime::Update(void)
{
	if (m_Alive == true) {
		m_nRowAnim = 0;
	}
	else {
		m_nRowAnim = 1;
	}

	// パターン描画更新
	m_nCntAnim++;
	if (m_nCntAnim == 60)
	{
		m_nCntAnim = 0;
		m_nPatternAnim++;
		if (m_nPatternAnim == 3)
		{
			m_nPatternAnim = 1;
		}
	}
	LifeCheck();

	if (m_TurnFlag) {
		m_Pos.x -= m_Movement;
		m_nDirection = 1;
	}
	else {
		m_Pos.x += m_Movement;
		m_nDirection = -1;
	}

	m_StateCnt = (m_StateCnt + 1) % TURN_CNT;

	if (m_StateCnt == 0) {
		m_TurnFlag = !m_TurnFlag;
	}
}

void CSlime::Create(Vector3 pos, float width, float height, int texIndex, int id)
{
	CSlime *obj = new CSlime;
	obj->Init(pos, width, height, texIndex, id);
}