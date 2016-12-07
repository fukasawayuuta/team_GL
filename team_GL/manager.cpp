/******************************************************************************
	タイトル名：Manager
	ファイル名：manager.cpp
	作成者    ：AT-13B-284 35 深澤佑太
	作成日    ：2016/11/14
******************************************************************************/
#include "main.h"
#include "lib.h"
#include "renderer.h"
#include "mode.h"
#include "opening.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "scene.h"
#include "scene2D.h"
#include "manager.h"
#include "input.h"
#include "texture.h"

/*******************************************************************************
* グローバル変数
*******************************************************************************/
CRenderer *CManager::m_pRenderer;
CMode *CManager::m_pMode;

/******************************************************************************
	関数名 : CManager::CManager()
	説明   : コンストラクタ
******************************************************************************/
CManager::CManager(void)
{
}

/******************************************************************************
	関数名 : CManager::~CManager()
	説明   : コンストラクタ
******************************************************************************/
CManager::~CManager(void)
{
	
}

/******************************************************************************
	関数名 ; HRESULT CManager::Init( HINSTANCE hInstance , HWND hWnd , BOOL bWindow )
	引数   : hInstance, hWnd, bWindow
	戻り値 : S_OK, E_FAIL
	説明   : オブジェクトの作成し、画面幅や高さ、バックバッファの形式と数を指定し、
			 ウィンドウモードかフルスクリーンモードで出すかを指定し、
			 デバイスを作成する。

			 ポリゴンを描画するための初期化処理を入れてある。
******************************************************************************/
HRESULT CManager::Init(HINSTANCE hInstance , HWND hWnd , BOOL bWindow)
{
	// インプットの初期化
	CInput::InitKeyboard(hInstance, hWnd);
	// クラスの実体化
	m_pRenderer = CRenderer::Create(hInstance, hWnd, bWindow);
	// テクスチャの読み込み
	CTexture::Load();
	// フェードの初期化
	CFade::Init();
	// 最初のモードの設定
	SetMode(new COpening);
	return S_OK;
}

/******************************************************************************
	関数名 : void CManager::Uninit(void)
	引数   : void
	戻り値 : なし
	説明   : 解放処理
******************************************************************************/
void CManager::Uninit(void)
{
	if (m_pRenderer != NULL) {
		//	レンダラクラスの破棄
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	if (m_pMode != NULL) {
		//	モードクラスの破棄
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = NULL;
	}
	CInput::UninitKeyboard();
	// テクスチャの解放
	CTexture::Unload();
	CFade::Uninit();
}

/******************************************************************************
	関数名 : void CManager::Update(void)
	引数   : void
	戻り値 : なし
	説明   : Managerクラスの更新処理
******************************************************************************/
void CManager::Update(void)
{
	CInput::UpdateKeyboard();
	m_pRenderer->Update();
	m_pMode->Update();
	CFade::Update();
}

/******************************************************************************
	関数名 : void CManager::Update(void)
	引数   : void
	戻り値 : なし
	説明   : 描画処理
******************************************************************************/
void CManager::Draw(void)
{
	m_pRenderer->Begin();

	m_pMode->Draw();
	CFade::Draw();

	m_pRenderer->End();
}

/*******************************************************************************
* 関数名：void CManager::SetMode( CMode *mode )
*
* 引数	：
* 戻り値：
* 説明	：モード設定処理
*******************************************************************************/
void CManager::SetMode(CMode *mode)
{
	if (m_pMode != NULL)
	{// モードが設定されていたら終了
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = NULL;
	}
	m_pMode = mode;
	m_pMode->Init();
}