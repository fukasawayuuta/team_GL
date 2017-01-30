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
}

COtherPlayer::~COtherPlayer(void)
{
}

void COtherPlayer::Init( int nId )
{
	m_Score = 0;
	m_Pos = Vector3( 0, 0, 0 );
	m_Width = 50.0f;
	m_Height = 100.0f;

	switch( nId )
	{
	case 0:
		m_nTexIdx = CTexture::SetTexture( TEXTURE_TYPE_PLAYER000 );
		break;
	case 1:
		m_nTexIdx = CTexture::SetTexture( TEXTURE_TYPE_PLAYER000 );
		break;
	case 2:
		m_nTexIdx = CTexture::SetTexture( TEXTURE_TYPE_PLAYER000 );
		break;
	case 3:
		m_nTexIdx = CTexture::SetTexture( TEXTURE_TYPE_PLAYER000 );
		break;
	}
}

void COtherPlayer::Uninit(void)
{

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