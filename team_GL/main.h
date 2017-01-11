/******************************************************************************
	タイトル名：OpenGL
	ファイル名：main.h
	作成者    ：AT-13B-284 35 深澤佑太
	作成日    ：2016/11/09
******************************************************************************/
/******************************************************************************
	インクルードガード
******************************************************************************/
#pragma once
#define _CRT_SECURE_NO_WARNINGS

/******************************************************************************
	インクルードファイル
******************************************************************************/
#pragma comment(lib, "OpenGL32.lib")		// OpenGLのライブラリとリンク
#pragma comment(lib, "glu32.lib")			// OpenGLのライブラリとリンク
#pragma comment( lib , "winmm.lib" )		//システム時刻取得に必要
#pragma comment( lib , "dxguid.lib" )		//DirectXコンポーネント使用に必要(細かい作業に必要)
#pragma comment( lib , "dinput8.lib" )		//入力処理に必要
#pragma comment( lib, "ws2_32.lib" )

#include<WinSock2.h>
#include <windows.h>
#include <gl/gl.h>
#include <gl/GLU.h>
#include <stdio.h>
#include <stdlib.h>
#define DIRECTINPUT_VERSION ( 0x0800 )//警告対処用
#include "dinput.h"			//入力処理に必要
#include <math.h>
#include "Vector.h"
#include "lib.h"
#include <process.h>

/******************************************************************************
	マクロ定義
******************************************************************************/
#define SCREEN_WIDTH ( 1280 )				//	画面幅
#define SCREEN_HEIGHT ( 720 )				//	画面高さ
#define PI (3.141592654f)
#define GL3DToRadian( degree ) ((degree) * (PI / 180.0f))
#define GL3DToDegree( radian ) ((radian) * (180.0f / PI)) 

/******************************************************************************
	クラス宣言
******************************************************************************/

/******************************************************************************
	プロトタイプ宣言
******************************************************************************/