/******************************************************************************
	タイトル名：OpenGL
	ファイル名：main.cpp
	作成者    ：AT-13B-284 35 深澤佑太
	作成日    ：2016/11/09
******************************************************************************/
/******************************************************************************
	scanfのwarning防止
******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS

/******************************************************************************
	インクルードファイル
******************************************************************************/
#include "main.h"
#include "manager.h"
#include "titlemenu.h"

/******************************************************************************
	マクロ定義
******************************************************************************/

#define PROJECTNAME ( "OpenGL_Test" )
#define ID_BUTTON000 ( 101 )

/******************************************************************************
	構造体定義
******************************************************************************/
/******************************************************************************
	プロトタイプ宣言
******************************************************************************/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

/******************************************************************************
	グローバル変数
******************************************************************************/
 float g_nCountFPS;		//FPSカウンタ

/******************************************************************************
	関数名：int WINAPI WinMain( HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLine , int nCmdShow )
	引数  ：HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLine , int nCmdShow
	戻り値：正常終了：int型の0
	説明  :メッセージウィンドウをだして、質問に対してのやり取りをする。
******************************************************************************/
int WINAPI WinMain( HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLine , int nCmdShow )
{
	DWORD dwFrameCount;
	DWORD dwCurrentTime;
	DWORD dwEXecLastTime;
	DWORD dwFPSLastTime;

	dwFrameCount = 
	dwCurrentTime = 0;
	dwEXecLastTime = 
	dwFPSLastTime = timeGetTime();

	timeBeginPeriod(1);

	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX) ,			 //メモリサイズを指定
		CS_CLASSDC ,                     //ウィンドウのスタイルを設定
		WndProc,                         //ウィンドウプロシージャのアドレス( 関数名 )を指定
		0 ,                              //使用しない
		0 ,                              //使用しない
		hInstance ,                      //WinMainのインスタンスハンドルを指定
		NULL ,                           //使用するアイコンの指定
		LoadCursor(NULL , IDC_ARROW) ,	 //マウスカーソルを指定( ウィンドウ内 )
		(HBRUSH)(COLOR_WINDOW + 1) ,	 //クライアント領域の背景色を設定
		NULL ,                           //メニューの設定
		PROJECTNAME ,                    //ウィンドウクラスの名前( ニックネーム的な )
		NULL,                            //小さいアイコンが設定された場合の情報
	};

	HWND hWnd;//ウィンドウのハンドル
	MSG msg;  //メッセージ

	RegisterClassEx(&wcex);//ウィンドウクラスの登録
	hWnd = CreateWindowEx( 0 ,
						   PROJECTNAME ,		 //ウィンドウクラスの名前
						   "TEST" ,				 //ウィンドウの名前
						   WS_OVERLAPPEDWINDOW , //ウィンドウのスタイル
						   CW_USEDEFAULT ,		 //左上のX座標
						   CW_USEDEFAULT ,		 //左上のY座標
						   SCREEN_WIDTH ,		 //幅  ( 整数で入力 )
						   SCREEN_HEIGHT ,		 //高さ( 整数で入力 )
						   NULL ,				 //親ウィンドウのハンドル
						   NULL ,				 //メニューハンドル又は、子ウィンドウID
						   hInstance ,			 //
						   NULL);//ウィンドウの作成データ

	if( FAILED( Init( hInstance , hWnd , TRUE ) ) ) {//初期化処理
		return -1;
	}

	/* ウィンドウの表示 */
	ShowWindow(hWnd , nCmdShow);//非クライアント領域
	UpdateWindow(hWnd);//クライアント領域

	/* メッセージループ */
	while(1) {
		if( PeekMessage( &msg , NULL , 0 , 0 , PM_REMOVE ) != 0 ) { //Windowsが処理しているとき
			if( msg.message == WM_QUIT ) {
				break;
			}
			else {
				/* メッセージの翻訳を送出 */
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		}
		else {	//OpenGLが処理
			dwCurrentTime = timeGetTime();
			if((dwCurrentTime - dwFPSLastTime) >= 500) {
				g_nCountFPS = (dwFrameCount * 1000)/(dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}
			if((dwCurrentTime - dwEXecLastTime) >= (1000/60)) {
				dwEXecLastTime = dwCurrentTime;

				Update();		//	更新処理
				Draw();		//	描画処理
				dwFrameCount++;
			}
		}	
	}

	Uninit();		//	終了処理

	UnregisterClass(PROJECTNAME, wcex.hInstance);//ウィンドウクラスの登録解除

	return (int)msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	static HWND hWndButton000;

	switch( uMsg ) {
	case WM_DESTROY://ウィンドウを破棄
		PostQuitMessage( 0 );//" WM_QUIT "メッセージを返す
		break;

	case WM_KEYDOWN://キーが押された
		switch( wParam ) {
		case VK_ESCAPE://仮想キー

			nID = MessageBox( hWnd , " 終了しますか？ " , "  " , MB_YESNO + MB_ICONQUESTION );

			if( nID == IDYES ) {
				DestroyWindow( hWnd );//ウィンドウを破棄
			}
			break;
		}
		break;
	default :
		break;

	}

	// タイトル画面 ゲーム終了項目
	if( ( wParam == VK_RETURN ) ) {
		if( CTitleMenu::Check() ) {
			DestroyWindow( hWnd );//ウィンドウを破棄
		}
	}
	return DefWindowProc( hWnd , uMsg , wParam , lParam );
}
/********************************************************************
	関数名 : HRESULT Init( HINSTANCE hInstance , HWND hWnd , BOOL bWindow )
	引数   : hInstance, hWnd, bWindow
	戻り値 : S_OK
	説明   : OpenGLでの初期化処理
********************************************************************/
HRESULT Init( HINSTANCE hInstance , HWND hWnd , BOOL bWindow )
{
	// OpenGL初期化
	CManager::Init( hInstance, hWnd, bWindow );

	return S_OK;
}

/********************************************************************
	関数名 : void Uninit(HWND hWnd)
	引数   : hWnd
	戻り値 : なし
	説明   : OpenGLでの終了処理
********************************************************************/
void Uninit(void)
{
	// 後処理
	CManager::Uninit();
}

/********************************************************************
	関数名 :void Update(void)
	引数   : なし
	戻り値 : なし
	説明   : OpenGLでの更新処理
********************************************************************/
void Update(void)
{
	//	更新
	CManager::Update();
}

/********************************************************************
	関数名 : void Draw(HDC dc)
	引数   : dc
	戻り値 : なし
	説明   : OpenGLでの描画処理
********************************************************************/
void Draw(void)
{
	//	描画
	CManager::Draw();
}
