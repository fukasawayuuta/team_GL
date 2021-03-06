/******************************************************************************
	タイトル名 : レンダラクラス
	ファイル名 : renderer.cpp
	作成者     : AT-13C-284 36 深澤佑太
	作成日     : 2016/11/14
	更新日     : 
******************************************************************************/
/******************************************************************************
	インクルードファイル
******************************************************************************/
#include "renderer.h"
#include "input.h"

/******************************************************************************
	マクロ定義
******************************************************************************/
/******************************************************************************
	グローバル変数
******************************************************************************/
/******************************************************************************
	関数名 : CRerender::CRerender()
	説明   : コンストラクタ
******************************************************************************/
CRenderer::CRenderer(void)
{
}

/******************************************************************************
	関数名 : CRerender::~CRerender()
	説明   : デストラクタ
******************************************************************************/
CRenderer::~CRenderer(void)
{
}

/******************************************************************************
	関数名 ; HRESULT CRerender::Init( HINSTANCE hInstance , HWND hWnd , BOOL bWindow )
	引数   : hInstance, hWnd, bWindow
	戻り値 : S_OK, E_FAIL
	説明   : オブジェクトの作成し、画面幅や高さ、バックバッファの形式と数を指定し、
			 ウィンドウモードかフルスクリーンモードで出すかを指定し、
			 デバイスを作成する。

			 ポリゴンを描画するための初期化処理を入れてある。
******************************************************************************/
HRESULT CRenderer::Init(HINSTANCE hInstance , HWND hWnd , BOOL bWindow)
{
	// OpenGL初期化

    // ピクセルフォーマット初期化
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, //Flags
        PFD_TYPE_RGBA, //The kind of framebuffer. RGBA or palette.
        32, //Colordepth of the framebuffer.
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        24, //Number of bits for the depthbuffer
        8, //Number of bits for the stencilbuffer
        0, //Number of Aux buffers in the framebuffer.
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };

	m_Wnd = hWnd;

    m_DC = GetDC(hWnd);
    int format = ChoosePixelFormat(m_DC, &pfd);
    if (format == 0) {
        return 0; // 該当するピクセルフォーマットが無い
	}

    // OpenGLが使うデバイスコンテキストに指定のピクセルフォーマットをセット
    if (!SetPixelFormat(m_DC, format, &pfd)) {
        return 0; // DCへフォーマットを設定するのに失敗
	}

    // OpenGL contextを作成
    m_GLRC = wglCreateContext(m_DC);

    // 作成されたコンテキストがカレント（現在使用中のコンテキスト）か？
    if (!wglMakeCurrent(m_DC, m_GLRC)) {
        return 0; // 何か正しくないみたい…
	}
	/* デプステストを有効にする */
	glEnable(GL_DEPTH_TEST);

	return S_OK;
}

/******************************************************************************
	関数名 : void CRerender::Uninit(void)
	引数   : void
	戻り値 : なし
	説明   : カレントコンテキストを無効にする
			 カレントコンテキストを削除
			 デバイスコンテキスト解放
			 Sceneクラスの解放処理
******************************************************************************/
void CRenderer::Uninit(void)
{
    // カレントコンテキストを無効にする
    wglMakeCurrent(NULL, NULL);

    // カレントコンテキストを削除
    wglDeleteContext(m_GLRC);

    // デバイスコンテキスト解放
    ReleaseDC(m_Wnd, m_DC);
}

/******************************************************************************
	関数名 : void CRerender::Update(void)
	引数   : void
	戻り値 : なし
	説明   : Sceneクラスの更新処理
******************************************************************************/
void CRenderer::Update(void)
{
#ifdef _DEBUG
	if( CInput::GetKeyboardPress( DIK_F1 ) )
	{
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	}
	if( CInput::GetKeyboardPress( DIK_F2 ) )
	{
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	}
#endif
}

/******************************************************************************
	関数名 : void CRerender::Draw(HDC dc)
	引数   : void
	戻り値 : なし
	説明   : ポリゴンなどの描画処理
******************************************************************************/
void CRenderer::Draw(void)
{

}

/******************************************************************************
	関数名 : void CRerender::Begin(HDC dc)
	引数   : void
	戻り値 : なし
	説明   : 描画処理の準備
******************************************************************************/
void CRenderer::Begin(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);					//	クリアカラーの設定
	glClearDepth(1.0f);										//	クリア時の深度値を設定
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//	(バックバッファ | Zバッファ)
	glEnable(GL_DEPTH_TEST);								//「Zテスト」を有効にする
}
/******************************************************************************
	関数名 : void CRerender::End(HDC dc)
	引数   : void
	戻り値 : なし
	説明   : 描画処理の後処理
******************************************************************************/
void CRenderer::End(void)
{
	SwapBuffers(m_DC);			//	画面の更新
}
/******************************************************************************
	関数名 : void CRerender::End(HDC dc)
	引数   : void
	戻り値 : なし
	説明   : 描画処理の作成
******************************************************************************/
CRenderer *CRenderer::Create(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	CRenderer *obj = new CRenderer;
	obj->Init(hInstance, hWnd, bWindow);

	return obj;
}