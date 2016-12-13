#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "scene.h"
#include "scene3D.h"
#include "animationBoard.h"
#include "boss.h"

const int DRAW_SPEED = 30;
const int TEXTURE_COLUMN = 4;
const int TEXTURE_ROW = 4;
const int WALK_DRAW = 4;

CBoss::CBoss(int Priority, OBJ_TYPE objType)
{
	m_nTexRow = TEXTURE_ROW;
	m_nTexColumn = TEXTURE_COLUMN;
}


CBoss::~CBoss(void)
{
}

void CBoss::Init(Vector3 pos, float width, float height, int texIndex)
{
	m_Pos = pos;
	m_Width = width;
	m_Height = height;
	m_nDirection = 1;
	m_nTexIdx = CTexture::SetTexture(texIndex);
}

void CBoss::Uninit(void)
{
}

void CBoss::Update(void)
{
	// パターン描画更新
	m_nCntAnim++;
	if (m_nCntAnim == DRAW_SPEED) {
		m_nCntAnim = 0;
		m_nPatternAnim++;
		if (m_nPatternAnim == WALK_DRAW) {
			m_nPatternAnim = 0;
		}
	}
}

void CBoss::Draw(void)
{
	CAnimationBoard::Draw();
}

CBoss * CBoss::Create(Vector3 pos, float width, float height, int texIndex)
{
	CBoss *obj = new CBoss;
	obj->Init(pos, width, height, texIndex);

	return obj;
}