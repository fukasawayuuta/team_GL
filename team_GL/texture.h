/*******************************************************************************
* タイトル名：
* ファイル名：textureGL.cpp
* 作成者	：AT13B284 10 小笠原啓太
* 作成日	：
********************************************************************************
* 更新履歴	：
*
*******************************************************************************/
/*******************************************************************************
* インクルードガード
*******************************************************************************/
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "main.h"

/*******************************************************************************
* インクルードファイル
*******************************************************************************/

/*******************************************************************************
* マクロ定義
*******************************************************************************/

/*******************************************************************************
* 構造体
*******************************************************************************/
// テクスチャタイプ名
typedef enum
{
	TEXTURE_TYPE_TEAMLOGO,			// オープニング
	TEXTURE_TYPE_TITLE_BG,			// タイトル
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
	TEXTURE_TYPE_RESULT_BG,			// リザルト
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
// テクスチャのパラメータ
typedef struct
{
	char *texName;	// ファイル名
}TEXTURE_PARAM;

/*******************************************************************************
* 前方宣言
*******************************************************************************/

/*******************************************************************************
* クラス宣言
*******************************************************************************/
// テクスチャクラス
class CTexture
{
	private:
		unsigned int m_nTexIdx;
		int m_nImageSize;	// サイズ
		int m_nWidth;		// 横幅
		int m_nHeight;		// 高さ
		int m_nBpp;			// 深度
		int m_nDiscrip;		// 格納方向

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

