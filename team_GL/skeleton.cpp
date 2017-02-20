/******************************************************************************
	タイトル名：skeleton
	ファイル名：skeleton.cpp
	作成者    ：AT-13B-284 35 深澤佑太
	作成日    ：2017/02/06
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
#include "skeleton.h"

const float MOVEMENT = 0.75f;
const int TURN_CNT = 300;

CSkeleton::CSkeleton(void)
{
	m_nTexRow = 1;
	m_nTexColumn = 3;
	m_Movement = MOVEMENT;
	m_TurnFlag = false;
	m_StateCnt = 0;
}


CSkeleton::~CSkeleton(void)
{
}

void CSkeleton::Update(void)
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

	m_StateCnt = (m_StateCnt + 1) % TURN_CNT;

	if (m_StateCnt == 0) {
		m_TurnFlag = !m_TurnFlag;
	}
}

void CSkeleton::Create(Vector3 pos, float width, float height, int texIndex, int id)
{
	CSkeleton *obj = new CSkeleton;
	obj->Init(pos, width, height, texIndex, id);
}