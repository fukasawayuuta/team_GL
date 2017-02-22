/*******************************************************************************
* �^�C�g�����F
* �t�@�C�����Franking.cpp
* �쐬��	�FAT13B284 02 ������
* �쐬��	�F2016/12/13
* �������e	�F�����L���O�ƃv���C���[�ԍ���\������
********************************************************************************
* �X�V����	�F
*
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "main.h"
#include "manager.h"

#include "ranking.h"
#include "score.h"
/******************************************************************************
	�}�N����`
******************************************************************************/
/******************************************************************************
	�^��`
******************************************************************************/
/******************************************************************************
	�v���g�^�C�v�錾
******************************************************************************/
/******************************************************************************
	�O���[�o���ϐ�
******************************************************************************/

//=============================================================================
//	�֐��� : CRanking::CRanking()
//	����   : �R���X�g���N�^
//=============================================================================
CRanking::CRanking( int Priority, OBJ_TYPE objType )
{
}

//=============================================================================
//	�֐��� : CRanking::CRanking()
//	����   : �f�X�g���N�^
//=============================================================================
CRanking::~CRanking()
{
}

/******************************************************************************
	�֐��� : CRanking* CRank::Create ( Vector2 pos, Vector2 rot, float width, float height, int index )
	����   : pos, rot, width, height, index
	�߂�l : CRanking*
	����   : �����L���O�̐�������
******************************************************************************/
CRanking* CRanking::Create ( Vector2 pos, Vector2 rot, float width, float height, int index )
{
	CRanking *ranking;

	ranking = new CRanking;
	ranking -> Init( pos, rot, width, height, index );

	return ranking;
}


/******************************************************************************
	�֐��� : void CRanking::Init ( Vector2 pos, Vector2 rot, float width, float height )
	����   : void�^
	�߂�l : pos, rot, width, height
	����   : �����N����������
******************************************************************************/
void CRanking::Init ( Vector2 pos, Vector2 rot, float width, float height, int index )
{
	// �����l����
	m_Pos		= pos;
	m_Rot		= rot;
	m_Width		= width;
	m_Height	= height;

	// �����L���O�ɗ\�ߐ��l������
	for( int i = 0; i < RANKING_ALL; i++ ) {
		m_nRanking[ i ] = CManager::GetScore(i);
	}

	// �v���C���[�̃X�R�A������
	//m_nRanking[ RANKING_ALL ] = CScore::GetScore();

	// �����L���O�̏��ʂ�ݒ肷��
	m_RankNum = Set( m_nRanking );

	// ���Ԍv���̒l������������
	m_TimeCnt = 0;

	// �e�N�X�`����ǂݍ��݁A��������
	m_TexIdx = CTexture::SetTexture( index );

	// �v���C���[�ԍ��̃e�N�X�`����ǂݍ��݁A��������
	m_PlayerRankTexIdx[ 0 ] = CTexture::SetTexture( TEXTURE_TYPE_RANK_FIRST );
	m_PlayerRankTexIdx[ 1 ] = CTexture::SetTexture( TEXTURE_TYPE_RANK_SECOND );
	m_PlayerRankTexIdx[ 2 ] = CTexture::SetTexture( TEXTURE_TYPE_RANK_THIRD );
	m_PlayerRankTexIdx[ 3 ] = CTexture::SetTexture( TEXTURE_TYPE_RANK_FOURTH );

	// ���l��������
	m_RankNumColor_a = 1.0f;

}

/******************************************************************************
== �֐��� �F void CRanking::Uninit ( void )
== �߂�l �F void�^
== ����   �F void
== ���e   �F �����L���O �I������
******************************************************************************/
void CRanking::Uninit ( void )
{
}

/******************************************************************************
== �֐��� �F void CRanking::Update ( void )
== �߂�l �F void�^
== ����   �F void
== ���e   �F �����L���O �X�V����
******************************************************************************/
void CRanking::Update ( void )
{
}

/******************************************************************************
== �֐��� �F void CRanking::Draw ( void )
== �߂�l �F void�^
== ����   �F void
== ���e   �F �����L���O �`�揈��
******************************************************************************/
void CRanking::Draw ( void )
{

	int nRankingCnt;

	// ���Ԃ��J�E���g����
	m_TimeCnt++;

	// ��莞�Ԃ��ƂɃ��l��؂�ւ���
	if( m_TimeCnt >= 10 ) {
		// �J�E���g��0�ɖ߂�
		m_TimeCnt = 0;

		// ���l��؂�ւ���
		if( m_RankNumColor_a == 0.6f ) {
			m_RankNumColor_a = 0.3f;
		} else {
			m_RankNumColor_a = 0.6f;
		}
	}

	glDisable( GL_LIGHTING );

	//	��������v���W�F�N�V�����}�g���N�X�̐ݒ�////////////////////
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 1);
	//	�����܂Ńv���W�F�N�V�����}�g���N�X�̐ݒ�////////////////////

	//	�������烂�f���r���[�}�g���N�X�̐ݒ�////////////////////////
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	//	�����܂Ń��f���r���[�}�g���N�X�̐ݒ�////////////////////////

	// �����F��`����悤�ɂ���
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// ���e�X�g �L����
	glAlphaFunc( GL_GEQUAL, 0.2f );
	glEnable( GL_ALPHA_TEST );

	// �e�N�X�`���}�b�s���O�L����
	glEnable( GL_TEXTURE_2D );

	// �e�N�X�`�����o�C���h
	glBindTexture( GL_TEXTURE_2D, m_TexIdx );

	// �����L���O��UV�l�ƒ��_���W�̐ݒ�
	for( int j = 0; j < RANKING_ALL ; j++ ) {	// �����L���O�̃��[�v
		nRankingCnt = m_nRanking[ j ];
		for( int i = 0; i < MAX_SCORE ; i++ ) {	// �X�R�A�̃��[�v

			//	�`��J�n
			glBegin( GL_TRIANGLE_STRIP );

			// �F�ݒ�
			if( m_RankNum == j ) {
				glColor4f( 1.0f, 1.0f, 1.0f, m_RankNumColor_a );
			} else {
				glColor4f( 0.3f, 0.3f, 0.5f, 0.6f );
			}

			//	���_���W�ݒ�
			glTexCoord2d( ( float )( nRankingCnt % 10 * 0.1f ), 1.0f );
			glVertex3f( m_Pos.x - (float)( m_Width * ( i + 1.0f ) ),
						m_Pos.y + m_Height * (float)( j + 1.0f ),
						0.0f );
	
			glTexCoord2d( ( float )( ( nRankingCnt % 10 + 1.0f ) * 0.1f ), 1.0f );
			glVertex3f( m_Pos.x - (float)( m_Width * i ),
						m_Pos.y + m_Height * (float)( j + 1.0f ),
						0.0f );
	
			glTexCoord2d( ( float )( nRankingCnt % 10 * 0.1f ), 0.0f );
			glVertex3f( m_Pos.x - (float)( m_Width * ( i + 1.0f ) ),
						m_Pos.y + m_Height * (float)j,
						0.0f );
	
			glTexCoord2d( ( float )( ( nRankingCnt % 10 + 1.0f ) * 0.1f ), 0.0f );
			glVertex3f( m_Pos.x - (float)( m_Width * i ),
						m_Pos.y + m_Height * (float)j,
						0.0f );

			// �`�揈�� �I��
			glEnd();

			// �P�����ɃJ�E���g������������
			nRankingCnt = nRankingCnt * 0.1f;
		}
	}	// �����L���O�̕`��I��

	glBindTexture(GL_TEXTURE_2D, 0);

	// �v���C���[�ԍ���UV�l�ƒ��_���W�̐ݒ�
	for( int nCntPlayerRank = 0; nCntPlayerRank < RANKING_ALL; nCntPlayerRank++ ) {

		// �e�N�X�`�����o�C���h
		glBindTexture( GL_TEXTURE_2D, m_PlayerRankTexIdx[ nCntPlayerRank ] );

		//	�`��J�n
		glBegin( GL_TRIANGLE_STRIP );

		//	�F�ݒ�
		glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );

		//	���_���W�ݒ�
		glTexCoord2d( 0.0f, 1.0f );
		glVertex3f( m_Pos.x - ( m_Width * 0.5f ) -370, m_Pos.y + ( m_Height * 0.3f ) + ( 90 * nCntPlayerRank ) +60, 0.0f );
	
		glTexCoord2d( 1.0f, 1.0f );
		glVertex3f( m_Pos.x + ( m_Width * 0.5f ) -370, m_Pos.y + ( m_Height * 0.3f ) + ( 90 * nCntPlayerRank ) +60, 0.0f );
	
		glTexCoord2d( 0.0f, 0.0f );
		glVertex3f( m_Pos.x - ( m_Width * 0.5f ) -370, m_Pos.y - ( m_Height * 0.3f ) + ( 90 * nCntPlayerRank ) +60, 0.0f );
	
		glTexCoord2d( 1.0f, 0.0f );
		glVertex3f( m_Pos.x + ( m_Width * 0.5f ) -370, m_Pos.y - ( m_Height * 0.3f ) + ( 90 * nCntPlayerRank ) +60, 0.0f );

		//	�`��I��
		glEnd();

	}

	glBindTexture(GL_TEXTURE_2D, 0);

	// �v���C���[�ԍ� �\��

	glEnable(GL_BLEND);
	glEnable(GL_LIGHTING);



	// �e�N�X�`���}�b�s���O������
	glDisable(GL_TEXTURE_2D);

	// ���e�X�g������
	glDisable(GL_ALPHA_TEST);

	//	��������}�g���b�N�X�����ɖ߂�//////////////////////////////
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	//	�����܂Ń}�g���b�N�X�����ɖ߂�//////////////////////////////
}

/******************************************************************************
== �֐��� �F int CRanking::Set ( int *RankingValue )
== �߂�l �F void�^
== ����   �F *RankingValue
== ���e   �F �����L���O�̐ݒu����
******************************************************************************/
int CRanking::Set ( int *RankingValue )
{
	int RankNum = RANKING_ALL;	// �����L���O�̏���
	int Num;					// �m�ۂ���l

	// �X�R�A���������ɏ�փ\�[�g����
	for( int i = RANKING_ALL; i > 0; i-- ) {
		if( RankingValue[ i ] >= RankingValue[ i - 1 ] ) {
			Num = RankingValue[ i ];
			RankingValue[ i ] = RankingValue[ i - 1 ];
			RankingValue[ i - 1 ] = Num;
			RankNum--;
		} else {
			break;
		}
	}
	return RankNum;
}