/******************************************************************************
	タイトル名：Manager
	ファイル名：manager.cpp
	作成者    ：AT-13B-284 35 深澤佑太
	作成日    ：2016/11/14
******************************************************************************/
#include "main.h"
#include "rerender.h"
#include "scene.h"
#include "scene2D.h"
#include "manager.h"


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
	//	クラスの実体化
	m_pRenderer = CRerenderer::Create(hInstance, hWnd, bWindow);
	CScene2D::Create();
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
	m_pRenderer->Uninit();
	if (m_pRenderer != NULL) {
		//	レンダラクラスの破棄
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	CScene::ReleaseAll();
}

/******************************************************************************
	関数名 : void CManager::Update(void)
	引数   : void
	戻り値 : なし
	説明   : Managerクラスの更新処理
******************************************************************************/
void CManager::Update(void)
{
	m_pRenderer->Update();
	CScene::UpdateAll();
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

	CScene::DrawAll();

	m_pRenderer->End();
}