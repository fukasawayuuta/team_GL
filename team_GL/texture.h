/*******************************************************************************
* �^�C�g�����F
* �t�@�C�����FtextureGL.cpp
* �쐬��	�FAT13B284 10 ���}���[��
* �쐬��	�F
********************************************************************************
* �X�V����	�F
*
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�K�[�h
*******************************************************************************/
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "main.h"

/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/

/*******************************************************************************
* �}�N����`
*******************************************************************************/

/*******************************************************************************
* �\����
*******************************************************************************/
// �e�N�X�`���^�C�v��
typedef enum
{
	TEXTURE_TYPE_TEAMLOGO,			// �I�[�v�j���O
	TEXTURE_TYPE_TITLE_BG,			// �^�C�g��
	TEXTURE_TYPE_TITLE_LOGO,
	TEXTURE_TYPE_TITLE_MENU_GAME,
	TEXTURE_TYPE_TITLE_MENU_TUTORIAL,
	TEXTURE_TYPE_MATCHING_BG,
	TEXTURE_TYPE_GAME_BG,
	TEXTURE_TYPE_NUMBER,
	TEXTURE_TYPE_GAUGE_FRAME,
	TEXTURE_TYPE_GAUGE_IN,
	TEXTURE_TYPE_PLAYER000,
	TEXTURE_TYPE_PLAYER001,
	TEXTURE_TYPE_PLAYER002,
	TEXTURE_TYPE_PLAYER003,
	TEXTURE_TYPE_ENEMY001,
	TEXTURE_TYPE_ENEMY002,
	TEXTURE_TYPE_ENEMY003,
	TEXTURE_TYPE_ENEMY004,
	TEXTURE_TYPE_BOSS,
	TEXTURE_TYPE_BLOCK,
	TEXTURE_TYPE_RESULT_BG,			// ���U���g
	TEXTURE_TYPE_RESULT_LOGO,
	TEXTURE_TYPE_RANK_FIRST,
	TEXTURE_TYPE_RANK_SECOND,
	TEXTURE_TYPE_RANK_THIRD,
	TEXTURE_TYPE_RANK_FOURTH,
	TEXTURE_TYPE_EFFECT_SLASH,
	TEXTURE_TYPE_ITEM,
	TEXTURE_TYPE_UI_HP,
	TEXTURE_TYPE_UI_1P,
	TEXTURE_TYPE_UI_2P,
	TEXTURE_TYPE_UI_3P,
	TEXTURE_TYPE_UI_4P,
	TEXTURE_TYPE_MAX
}TEXTURE_TYPE;
// �e�N�X�`���̃p�����[�^
typedef struct
{
	char *texName;	// �t�@�C����
}TEXTURE_PARAM;

/*******************************************************************************
* �O���錾
*******************************************************************************/

/*******************************************************************************
* �N���X�錾
*******************************************************************************/
// �e�N�X�`���N���X
class CTexture
{
	private:
		unsigned int m_nTexIdx;
		int m_nImageSize;	// �T�C�Y
		int m_nWidth;		// ����
		int m_nHeight;		// ����
		int m_nBpp;			// �[�x
		int m_nDiscrip;		// �i�[����

		unsigned int m_Format;
		int m_nInternalFormat;

		static CTexture *m_pTexture[TEXTURE_TYPE_MAX];
		static TEXTURE_PARAM m_TexParam[TEXTURE_TYPE_MAX];
	public:
		CTexture();
		~CTexture();
		void Init( void );
		void Uninit( void );
		void Release( void );

		static void Load(void);
		static void Unload(void);

		unsigned int CreateTexture( char *FileName );
		unsigned int CreateTextureInverse( char *FileName );
		unsigned int CreateTextureBMP( char *FileName );

		static int SetTexture(int nIdx){return m_pTexture[nIdx]->m_nTexIdx;}
};

#endif

