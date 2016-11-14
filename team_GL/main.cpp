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

/******************************************************************************
	グローバル変数
******************************************************************************/
/******************************************************************************
	関数名：int WINAPI WinMain( HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLine , int nCmdShow )
	引数  ：HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLine , int nCmdShow
	戻り値：正常終了：int型の0
	説明  :メッセージウィンドウをだして、質問に対してのやり取りをする。
******************************************************************************/
int WINAPI WinMain( HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLine , int nCmdShow )
{
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
						   600 ,				 //幅  ( 整数で入力 )
						   400 ,				 //高さ( 整数で入力 )
						   NULL ,				 //親ウィンドウのハンドル
						   NULL ,				 //メニューハンドル又は、子ウィンドウID
						   hInstance ,			 //
						   NULL);//ウィンドウの作成データ

	/* ウィンドウの表示 */
	ShowWindow(hWnd , nCmdShow);//非クライアント領域
	UpdateWindow(hWnd);//クライアント領域

	/* メッセージループ */
	while(GetMessage(&msg, NULL, 0, 0) != 0) {
		/* メッセージの翻訳を送出 */
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

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

	return DefWindowProc( hWnd , uMsg , wParam , lParam );
}