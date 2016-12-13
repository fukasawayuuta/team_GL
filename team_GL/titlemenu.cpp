/*******************************************************************************
* �^�C�g�����F
* �t�@�C�����Ftitlemenu.cpp
* �쐬��	�FAT13B284 02 ������
* �쐬��	�F2016/11/30
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

#include "titlemenu.h"

#include "input.h"


//=============================================================================
//	�֐��� : CTitleMenu::CTitleMenu()
//	����   : �R���X�g���N�^
//			 �l�̃f�t�H���g��
//=============================================================================
CTitleMenu::CTitleMenu ( int Priority, OBJ_TYPE objType )
{
	m_HeightChange = 70.0f;
	m_Menu = TITLE_MENU_GAME;
}

//=============================================================================
//	�֐��� : CTitleMenu::CTitleMenu()
//	����   : �f�X�g���N�^
//=============================================================================
CTitleMenu::~CTitleMenu ()
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
	�֐��� : void CTitleMenu::Init ( Vector2 pos, Vector2 rot, float width, float height )
	����   : void�^
	�߂�l : pos, rot, width, height
	����   : �^�C�g�����j���[�̏���������
******************************************************************************/
void CTitleMenu::Init ( Vector2 pos, Vector2 rot, float width, float height )
{
	// �����l����
	m_Pos		= pos;
	m_Rot		= rot;
	m_Width		= width;
	m_Height	= height;

	// �t���Oon
	// m_bUse = true;

	// �Z���N�g���̃^�C���̌v��
	m_TimeCntSelect = 0;

	// �e���ڂ̍\���̂̏�����
	for( int CntTitleMenu = 0; CntTitleMenu < TITLE_MENU_MAX; CntTitleMenu++ ) {
		m_aTitleMenu[ CntTitleMenu ].pos		= Vector2( 0.0f, 0.0f );
		m_aTitleMenu[ CntTitleMenu ].fWidth		= 0.0f;
		m_aTitleMenu[ CntTitleMenu ].fHeight	= m_Height;
		m_aTitleMenu[ CntTitleMenu ].bUse		= false;
		m_aTitleMenu[ CntTitleMenu ].alfa		= 0.3f;
	}
	// �Q�[�����ڂ̂� �t���Oon
	m_aTitleMenu[ TITLE_MENU_GAME ].bUse = true;

	// �e�N�X�`����ǂݍ��݁A��������
	m_TexIdx[ 0 ] = CTexture::SetTexture( TEXTURE_TYPE_TITLE_MENU_GAME );
	m_TexIdx[ 1 ] = CTexture::SetTexture( TEXTURE_TYPE_TITLE_MENU_TUTORIAL );

} // InitTitleMenu�֐��̏I��

/******************************************************************************
== �֐��� �F void CTitleMenu::Uninit ( void )
== �߂�l �F void�^
== ����   �F void
== ���e   �F �^�C�g�����j���[�̏I������
******************************************************************************/
void CTitleMenu::Uninit ( void )
{
}

/******************************************************************************
== �֐��� �F void CTitleMenu::Update ( void )
== �߂�l �F void�^
== ����   �F void
== ���e   �F �^�C�g�����j���[�̍X�V����
******************************************************************************/
void CTitleMenu::Update ( void )
{
	/*****************************************
		�e�^�C�g�����j���[�̍��ڂ��o������
		������ǉ�����B
		���݂̎������e�F�Q�[���A�`���[�g���A��
		���݂̍��ڐ��@�F�Q��
		2016�N12��2�� 17:40:40
	*****************************************/


	// �^�C�g�����j���[ �g�p��
	if( CFade::Get( FADE_NONE ) ) {
		// �� �Z���N�g��
		if( CInput::GetKeyboardTrigger( DIK_UP ) ) {
			// ���l�������ɖ߂�
			m_TimeCntSelect = 0;
			// �e���ڂ����Z���N�g���̏���
			switch( m_Menu ) {

				case TITLE_MENU_GAME:
					m_Menu = TITLE_MENU_TUTORIAL;
					m_aTitleMenu[ TITLE_MENU_GAME ].bUse = false;
					m_aTitleMenu[ TITLE_MENU_TUTORIAL ].bUse = true;	// �`���[�g���A��
				//m_aTitleMenu[ TITLE_MENU_OPTION ].bUse = false;		// �I�v�V����
				//m_aTitleMenu[ TITLE_MENU_CREDIT ].bUse = false;		// �N���W�b�g
				//m_aTitleMenu[ TITLE_MENU_RUNKING ].bUse = true;,		// ���U���g
					break;

				case TITLE_MENU_TUTORIAL:
					m_Menu = TITLE_MENU_GAME;
					m_aTitleMenu[ TITLE_MENU_GAME ].bUse = true;
					m_aTitleMenu[ TITLE_MENU_TUTORIAL ].bUse = false;	// �`���[�g���A��
				//m_aTitleMenu[ TITLE_MENU_OPTION ].bUse = false;		// �I�v�V����
				//m_aTitleMenu[ TITLE_MENU_CREDIT ].bUse = false;		// �N���W�b�g
				//m_aTitleMenu[ TITLE_MENU_RUNKING ].bUse = true;,		// ���U���g
					break;

				/*                 
				   �I�v�V�����`�����L���O�̏���
				                   */

				default:
					break;
			}
		}

		// �� �Z���N�g��
		if( CInput::GetKeyboardTrigger( DIK_DOWN ) ) {
			// ���l�������ɖ߂�
			m_TimeCntSelect = 0;
			// �e���ڂ��牺�Z���N�g���̏���
			switch( m_Menu ) {

				case TITLE_MENU_GAME:
					m_Menu = TITLE_MENU_TUTORIAL;
					m_aTitleMenu[ TITLE_MENU_GAME ].bUse = false;
					m_aTitleMenu[ TITLE_MENU_TUTORIAL ].bUse = true;
					//m_aTitleMenu[ TITLE_MENU_OPTION ].bUse = false;		// �I�v�V����
					//m_aTitleMenu[ TITLE_MENU_CREDIT ].bUse = false;		// �N���W�b�g
					//m_aTitleMenu[ TITLE_MENU_RUNKING ].bUse = true;,		// ���U���g
					break;

				case TITLE_MENU_TUTORIAL:
					m_Menu = TITLE_MENU_GAME;
					m_aTitleMenu[ TITLE_MENU_GAME ].bUse = true;
					m_aTitleMenu[ TITLE_MENU_TUTORIAL ].bUse = false;
					//m_aTitleMenu[ TITLE_MENU_OPTION ].bUse = false;		// �I�v�V����
					//m_aTitleMenu[ TITLE_MENU_CREDIT ].bUse = false;		// �N���W�b�g
					//m_aTitleMenu[ TITLE_MENU_RUNKING ].bUse = true;,		// ���U���g
					break;

				/*                 
				   �I�v�V�����`�����L���O�̏���
				                   */

					default:
						break;
			}
		}

		// ���� ���莞
		if( CInput::GetKeyboardTrigger( DIK_RETURN ) ) {
			// �e���ڂ��猈�莞�̏���
			switch( m_Menu ) {
				case TITLE_MENU_GAME:		// �Q�[���։�ʑJ��
					CFade::Start( new CMatching );
					//m_bUse = false;
					break;

				case TITLE_MENU_TUTORIAL:	// �`���[�g���A���̉摜���o��
					break;

				/*                 
				   �I�v�V�����`�����L���O�̏���
				                   */

				default:
					break;
			}
		}
	}
	// �e���ڂ̐ݒ�
	for( int nCntTitleMenu = 0; nCntTitleMenu < TITLE_MENU_MAX; nCntTitleMenu++ ) {
		// �I�����̍��ڂ̏���
		if( m_aTitleMenu[ nCntTitleMenu ].bUse ) {
			// ���l�����̎���( 0.5f ~ 1.0f )�ƊԊu�ŕς���
			m_TimeCntSelect++;
			m_aTitleMenu[ nCntTitleMenu ].alfa = ( cosf( PI / FADETERM_TITLE_MENU * m_TimeCntSelect ) + 1 ) / 2 + FADETERM_MIN_SELECT;
			// ���ڂ����肳�ꂽ�Ƃ�
			if( CFade::Get( FADE_NONE ) == false ) {
				m_aTitleMenu[ nCntTitleMenu ].alfa = ( cosf( PI / 2 * m_TimeCntSelect ) + 1 ) / 2 + FADETERM_MIN_SELECT;
			}
		}
		// ��I�����̍��ڂ̏���
		else {
			// ���l���Œ�
			m_aTitleMenu[ nCntTitleMenu ].alfa = 0.3f;
		}
	}


} // UpdateTitleMenu�֐��̏I��

/******************************************************************************
== �֐��� �F void CTitleMenu::Draw ( void )
== �߂�l �F void�^
== ����   �F void
== ���e   �F �^�C�g�����j���[�̕`�揈��
******************************************************************************/
void CTitleMenu::Draw ( void )
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
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// ���e�X�g �L����
	glAlphaFunc(GL_GEQUAL, 0.09f );
	glEnable(GL_ALPHA_TEST);

	// �e�N�X�`���}�b�s���O�L����
	glEnable(GL_TEXTURE_2D);

	// UV�l�ƒ��_���W�̐ݒ� ( DirectX�`�� )
	for( int CntTitleMenu = 0; CntTitleMenu < TITLE_MENU_MAX; CntTitleMenu++ ) {

		// �e�N�X�`�����o�C���h
		glBindTexture( GL_TEXTURE_2D, m_TexIdx[ CntTitleMenu ] );

		//	�`��J�n
		glBegin( GL_TRIANGLE_STRIP );

		//	�F�ݒ�
		glColor4f( 1.0f, 1.0f, 1.0f, m_aTitleMenu[ CntTitleMenu ].alfa );

		//	���_���W�ݒ�
		glTexCoord2d( 0.0f, 1.0f );
		glVertex3f( m_Pos.x - ( m_Width * 0.5f ), m_Pos.y + ( m_aTitleMenu[ CntTitleMenu ].fHeight * 0.5f ) + ( m_HeightChange * CntTitleMenu ), 0.0f );
	
		glTexCoord2d( 1.0f, 1.0f );
		glVertex3f( m_Pos.x + ( m_Width * 0.5f ), m_Pos.y + ( m_aTitleMenu[ CntTitleMenu ].fHeight * 0.5f ) + ( m_HeightChange * CntTitleMenu ), 0.0f );
	
		glTexCoord2d( 0.0f, 0.0f );
		glVertex3f( m_Pos.x - ( m_Width * 0.5f ), m_Pos.y - ( m_aTitleMenu[ CntTitleMenu ].fHeight * 0.5f ) + ( m_HeightChange * CntTitleMenu ), 0.0f );
	
		glTexCoord2d( 1.0f, 0.0f );
		glVertex3f( m_Pos.x + ( m_Width * 0.5f ), m_Pos.y - ( m_aTitleMenu[ CntTitleMenu ].fHeight * 0.5f ) + ( m_HeightChange * CntTitleMenu ), 0.0f );

		glEnd();
		//	�`��I��
	}

	glEnable(GL_BLEND);
	glEnable(GL_LIGHTING);

	glBindTexture(GL_TEXTURE_2D, 0);

	// ���e�X�g������
	glDisable(GL_ALPHA_TEST);

    //�@�e�N�X�`���}�b�s���O������
    glDisable(GL_TEXTURE_2D);

	//	��������}�g���b�N�X�����ɖ߂�//////////////////////////////
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	//	�����܂Ń}�g���b�N�X�����ɖ߂�//////////////////////////////

} // DrawTitleMenu�֐��̏I��

/******************************************************************************
== �֐��� �F CTitleMenu* CTitleMenu::Create ( Vector2 pos, Vector2 rot, float width, float height )
== �߂�l �F CTitleMenu�^
== ����   �F pos, rot, width, height
== ���e   �F �^�C�g�����j���[�̐����ݒ�
******************************************************************************/
CTitleMenu *CTitleMenu::Create ( Vector2 pos, Vector2 rot, float width, float height )
{
	CTitleMenu *titleMenu;

	titleMenu = new CTitleMenu;
	titleMenu -> Init( pos, rot, width, height );

	return titleMenu;
}
