/*******************************************************************************
* タイトル名：
* ファイル名：gamebackground.h
* 作成者	：AT13B284 31 中山和馬
* 作成日	：2016/11/28
********************************************************************************
* 更新履歴	：
*
*******************************************************************************/
/*******************************************************************************
* インクルードガード
*******************************************************************************/
#pragma once

/*******************************************************************************
* クラス宣言
*******************************************************************************/
// ゲームクラス
class CTexture;
class CGameBackground : public CScene3D
{
private:
	int m_TextureIndex;

public:
	CGameBackground(int Priority = PRIORITY_BACKGROUND, OBJ_TYPE objType = OBJ_TYPE_NONE);
	~CGameBackground();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGameBackground *Create( void );
};

