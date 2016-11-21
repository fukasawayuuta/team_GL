/******************************************************************************
	タイトル名：Manager
	ファイル名：manager.h
	作成者    ：AT-13B-284 35 深澤佑太
	作成日    ：2016/11/14
******************************************************************************/
/******************************************************************************
	インクルードガード
******************************************************************************/
#pragma once

/******************************************************************************
	インクルード宣言
******************************************************************************/

/******************************************************************************
	クラス宣言
******************************************************************************/
class CRenderer;
class CMode;
class CManager
{
public:
	CManager(void);
	~CManager(void);

	static HRESULT Init(HINSTANCE hInstance , HWND hWnd , BOOL bWindow);		//	初期化処理
	static void Uninit(void);													//	終了処理
	static void Update(void);													//	更新処理
	static void Draw(void);														//	描画処理

	static CRenderer  *GetRenderer(void) { return m_pRenderer; }
	static void SetMode(CMode *mode);
	static CMode *GetMode(void) {return m_pMode;}
private:
	static CRenderer *m_pRenderer;		//	レンダラークラス。
	static CMode *m_pMode;
};

