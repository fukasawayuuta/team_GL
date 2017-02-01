/******************************************************************************
	タイトル名：OtherPlayer
	ファイル名：otherPlayer.cpp
	作成者    ：AT-13B-284 35 深澤佑太
	作成日    ：2017/01/16
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
#include "otherPlayer.h"


COtherPlayer::COtherPlayer(void)
{
	int dummy = 0;
}

COtherPlayer::~COtherPlayer(void)
{
}

void COtherPlayer::Init( int nId, Vector3 pos, float width, float height )
{
	m_Score = 0;
	m_Pos = pos;
	m_Width = width;
	m_Height = height;

	switch( nId )
	{
	case 0:
		m_nTexIdx = CTexture::SetTexture( TEXTURE_TYPE_PLAYER000 );
		break;
	case 1:
		m_nTexIdx = CTexture::SetTexture( TEXTURE_TYPE_PLAYER001 );
		break;
	case 2:
		m_nTexIdx = CTexture::SetTexture( TEXTURE_TYPE_PLAYER002 );
		break;
	case 3:
		m_nTexIdx = CTexture::SetTexture( TEXTURE_TYPE_PLAYER003 );
		break;
	}
}

void COtherPlayer::Uninit(void)
{
	int dummy = 0;
}

void COtherPlayer::Update(void)
{
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

void COtherPlayer::Draw(void)
{
	CPlayer::Draw();
}

COtherPlayer *COtherPlayer::Create( int nId, Vector3 pos, float width, float height )
{
	COtherPlayer *pScene = new COtherPlayer;
	pScene->Init( nId, pos, width, height );
	return pScene ;
}