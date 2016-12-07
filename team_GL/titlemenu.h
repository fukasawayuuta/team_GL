/******************************************************************************
	�^�C�g���� : titlemenu
	�t�@�C���� : titlemenu.h
	�쐬��     : AT-13B-284 02 ������
	�쐬��     : 2016/11/02
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
const int FADETERM_TITLE_MENU = 60 * 1;	// �I�����̍��ڂ̃t�F�[�h����
const float FADETERM_MIN_SELECT = 0.5f;	// �I�����̃t�F�[�h�����̍ŏ��l

/******************************************************************************
	�^��`
******************************************************************************/

// �^�C�g�����j���[�N���X
class CTitleMenu : CScene2D
{
	private:

		// �e���ڂ̎�ނ̍\����
		typedef enum
		{
			TITLE_MENU_GAME = 0,	// �Q�[��
			TITLE_MENU_TUTORIAL,		// �`���[�g���A��
			//TITLE_MENU_OPTION,		// �I�v�V����
			//TITLE_MENU_CREDIT,		// �N���W�b�g
			//TITLE_MENU_RUNKING,		// ���U���g
			TITLE_MENU_MAX			// ���̍\���̂̍��ڐ� 4
		} TITLE_MENU;

		// ���ڂ̍\����
		struct MENU
		{
			Vector2 pos;		// ���ڂ̈ʒu
			float	fWidth;		// ���ڂ̕�
			float	fHeight;	// ���ڂ̍���
			float	alfa;		// ���ڂ̃��l
			bool	bUse;		// ���ڂ̃t���O
		};

		MENU m_aTitleMenu[ TITLE_MENU_MAX ];// �^�C�g���̃��j���[�̎��
		TITLE_MENU m_Menu;					// �|�[�Y���j���[�̃��[�N

		int		m_TexIdx[ TITLE_MENU_MAX ];	// �e���ڂ̉摜�f�[�^�̃��[�N
		float	m_TimeCntSelect;			// �Z���N�g���Ƀ^�C�����J�E���g
		float	m_HeightChange;				// ���ڂ̍����̊Ԋu
		// bool	m_bUse;						// �^�C�g�����j���[�S�̂̃t���O



	public:
		CTitleMenu( int Priority = PRIORITY_2D, OBJ_TYPE objType = OBJ_TYPE_NONE );
		~CTitleMenu();

		void Init		( Vector2 pos, Vector2 rot, float width, float height );
		void Uninit		( void );
		void Update		( void );
		void Draw		( void );

		static CTitleMenu *Create ( Vector2 pos, Vector2 rot, float width, float height );
};

// =================================================================================== titleMenu.h�̏I��