/******************************************************************************
	�^�C�g���� : ranking
	�t�@�C���� : ranking.h
	�쐬��     : AT-13B-284 02 ������
	�쐬��     : 2016/12/13
	�X�V��     : 
******************************************************************************/
/******************************************************************************
	�C���N���[�h�K�[�h
******************************************************************************/
#pragma once

/******************************************************************************
	�C���N���[�h�t�@�C��
******************************************************************************/
#include "scene.h"
#include "scene2D.h"
#include "texture.h"

/******************************************************************************
	�}�N����`
******************************************************************************/
const int RANKING_ALL = 4;				// �X�R�A�̌���

/******************************************************************************
	�^��`
******************************************************************************/

// �����L���O�N���X �ݒ�
class CRanking : public CScene2D
{
	private:
		//LPDIRECT3DTEXTURE9		m_Texture;
		//LPDIRECT3DVERTEXBUFFER9 m_VtxBuff;
		//int m_RankNumColor;

		int	m_TexIdx;						// �����L���O�̉摜�f�[�^�̃��[�N
		int m_nRanking[ RANKING_ALL + 1 ];	// �����L���O�̒l
		int m_RankNum;
		int m_TimeCnt;						// ���Ԍv��

		int m_PlayerRankTexIdx[ RANKING_ALL ];// �v���C���[�ԍ��̉摜�f�[�^�̃��[�N

		float m_RankNumColor_a;

	public:
		CRanking( int Priority = PRIORITY_2D, OBJ_TYPE objType = OBJ_TYPE_NONE );
		~CRanking();
		void Init	( Vector2 pos, Vector2 rot, float width, float height, int index );
		void Update	( void );
		void Draw	( void );
		void Uninit	( void );

		int Set		( int *RankingValue );
		static CRanking *Create ( Vector2 pos, Vector2 rot, float width, float height, int index );
};