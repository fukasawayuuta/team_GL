/*******************************************************************************
* �^�C�g�����F
* �t�@�C�����Frank.cpp
* �쐬��	�FAT13B284 02 ������
* �쐬��	�F2016/12/13
* �������e	�F1�ʂ���S�ʂ̏��ʂ�\������
********************************************************************************
* �X�V����	�F
*
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "main.h"
#include "mode.h"
#include "matching.h"
#include "fade.h"

#include "rank.h"

//=============================================================================
//	�֐��� : CRank::CRank()
//	����   : �R���X�g���N�^
//			 �l�̃f�t�H���g��
//=============================================================================
CRank::CRank ( int Priority, OBJ_TYPE objType )
{
	m_HeightChange = 80.0f;

}

//=============================================================================
//	�֐��� : CRank::CRank()
//	����   : �f�X�g���N�^
//=============================================================================
CRank::~CRank ()
{
}

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

/******************************************************************************
	�֐��� : void CRank::Init ( Vector2 pos, Vector2 rot, float width, float height )
	����   : void�^
	�߂�l : pos, rot, width, height
	����   : �����N����������
******************************************************************************/
void CRank::Init ( Vector2 pos, Vector2 rot, float width, float height )
{
	// �����l����
	m_Pos		= pos;
	m_Rot		= rot;
	m_Width		= width;
	m_Height	= height;

	// �e���ڂ̍\���̂̏�����
	for( int CntRank = 0; CntRank < RANK_ALL; CntRank++ ) {
		m_Rank[ CntRank ].pos		= Vector2( 0.0f, 0.0f );
		m_Rank[ CntRank ].fWidth	= 0.0f;
		m_Rank[ CntRank ].fHeight	= m_Height;
		m_Rank[ CntRank ].alfa		= 1.0f;
	}

	// �e���ʂ̍����̏�����
	m_HeightChange = m_Height + 30;

	// �e���ʂ̊��蓖��
	m_RankID = RANK_ALL - 1;

	// �e�N�X�`����ǂݍ��݁A��������
	m_TexIdx[ 0 ] = CTexture::SetTexture( TEXTURE_TYPE_RANK_FIRST );
	m_TexIdx[ 1 ] = CTexture::SetTexture( TEXTURE_TYPE_RANK_SECOND );
	m_TexIdx[ 2 ] = CTexture::SetTexture( TEXTURE_TYPE_RANK_THIRD );
	m_TexIdx[ 3 ] = CTexture::SetTexture( TEXTURE_TYPE_RANK_FOURTH );

} // Initrank�֐��̏I��

/******************************************************************************
== �֐��� �F void CRank::Uninit ( void )
== �߂�l �F void�^
== ����   �F void
== ���e   �F �����N�I������
******************************************************************************/
void CRank::Uninit ( void )
{
}

/******************************************************************************
== �֐��� �F void CRank::Update ( void )
== �߂�l �F void�^
== ����   �F void
== ���e   �F �����N�X�V����
******************************************************************************/
void CRank::Update ( void )
{
	// �����N�̊��蓖�Ă��s����܂ŏ������s��
	if( m_RankID > -1 ) {
		// �����N����苗���܂œ����Ă��Ȃ��ꍇ
		if( m_Rank[ m_RankID ].pos.x < RANK_PLACE ) {
			m_Rank[ m_RankID ].pos.x += 20;
		} else if( m_Rank[ m_RankID ].pos.x >= RANK_PLACE ) {
			m_RankID--;	// �����N�̊��蓖�Ă�ς��Ă�
		}
	}
} // Updaterank�֐��̏I��

/******************************************************************************
== �֐��� �F void CRank::Draw ( void )
== �߂�l �F void�^
== ����   �F void
== ���e   �F �����N�`�揈��
******************************************************************************/
void CRank::Draw ( void )
{

	glDisable(GL_LIGHTING);
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
	//glEnable(GL_BLEND); 
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// ���e�X�g �L����
	glAlphaFunc(GL_GEQUAL, 0.5f );
	glEnable(GL_ALPHA_TEST);

	// �e�N�X�`���}�b�s���O�L����
	glEnable(GL_TEXTURE_2D);

	// UV�l�ƒ��_���W�̐ݒ� ( DirectX�`�� )
	for( int CntRank = 0; CntRank < RANK_ALL; CntRank++ ) {

		// �e�N�X�`�����o�C���h
		glBindTexture( GL_TEXTURE_2D, m_TexIdx[ CntRank ] );

		//	�`��J�n
		glBegin( GL_TRIANGLE_STRIP );

		//	�F�ݒ�
		glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );

		//	���_���W�ݒ�
		glTexCoord2d( 0.0f, 1.0f );
		glVertex3f( m_Pos.x - ( m_Width * 0.5f ) + m_Rank[ CntRank ].pos.x, m_Pos.y + ( m_Rank[ CntRank ].fHeight * 0.5f ) + ( m_HeightChange * CntRank ), 0.0f );
	
		glTexCoord2d( 1.0f, 1.0f );
		glVertex3f( m_Pos.x + ( m_Width * 0.5f ) + m_Rank[ CntRank ].pos.x, m_Pos.y + ( m_Rank[ CntRank ].fHeight * 0.5f ) + ( m_HeightChange * CntRank ), 0.0f );
	
		glTexCoord2d( 0.0f, 0.0f );
		glVertex3f( m_Pos.x - ( m_Width * 0.5f ) + m_Rank[ CntRank ].pos.x, m_Pos.y - ( m_Rank[ CntRank ].fHeight * 0.5f ) + ( m_HeightChange * CntRank ), 0.0f );
	
		glTexCoord2d( 1.0f, 0.0f );
		glVertex3f( m_Pos.x + ( m_Width * 0.5f ) + m_Rank[ CntRank ].pos.x, m_Pos.y - ( m_Rank[ CntRank ].fHeight * 0.5f ) + ( m_HeightChange * CntRank ), 0.0f );

		glEnd();
		//	�`��I��
	}


	glEnable(GL_BLEND);
	glEnable(GL_LIGHTING);

	glBindTexture(GL_TEXTURE_2D, 0);

    //�@�e�N�X�`���}�b�s���O������
    glDisable(GL_TEXTURE_2D);

	// ���e�X�g������
	glDisable(GL_ALPHA_TEST);

	//	��������}�g���b�N�X�����ɖ߂�//////////////////////////////
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	//	�����܂Ń}�g���b�N�X�����ɖ߂�//////////////////////////////

} // Drawrank�֐��̏I��

/******************************************************************************
== �֐��� �F CRank* CRank::Create ( Vector2 pos, Vector2 rot, float width, float height )
== �߂�l �F CRank�^
== ����   �F pos, rot, width, height
== ���e   �F �����N�����ݒ�
******************************************************************************/
CRank *CRank::Create ( Vector2 pos, Vector2 rot, float width, float height )
{
	CRank *rank;

	rank = new CRank;
	rank -> Init( pos, rot, width, height );

	return rank;
}
