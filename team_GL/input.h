/******************************************************************************
* タ イ ト ル : 
* 説　　　明　: input.cppのヘッダファイル
* プログラム名: input.h
* 作　成　者　: AT-13B-284 No.31 中山和馬
* 作　成　日　: 2015/12/12
* 修　正　日　: 
* 変更履歴
* 2015/12/12  : 作成
* 著　作　権　: Copyright(c)2015 nakayama All rights reserved.
******************************************************************************/

/******************************************************************************
* 二重インクルード防止
******************************************************************************/
#ifndef _INPUT_H_
#define _INPUT_H_

/******************************************************************************
* インクルード宣言
******************************************************************************/
#include"dinput.h"

/******************************************************************************
* マクロ定義
******************************************************************************/
#define MAX_PAD ( 1 )
#define JPBTN_A ( 0 )
#define JPBTN_B ( 1 )
#define JPBTN_X ( 2 )
#define JPBTN_Y ( 3 )
#define JPBTN_LB ( 4 )
#define JPBTN_RB ( 5 )
#define JPBTN_BACK ( 6 )
#define JPBTN_START ( 7 )
#define JPBTN_LSTICK ( 8 )
#define JPBTN_RSTICK ( 9 )
#define POV_UP ( 0 )
#define POV_UR ( 4500 )
#define POV_RI ( 9000 )
#define POV_LR ( 13500 )
#define POV_DW ( 18000 )
#define POV_LL ( 22500 )
#define POV_LF ( 27000 )
#define POV_UL ( 31500 )
#define AXISBUFF ( 0 )
#define KEYBOARDMAX ( 256 )
#define JOYPADMAX ( 32 )

/******************************************************************************
* プロトタイプ宣言
******************************************************************************/
class CInput
{
private:
	static HRESULT InitInput( HINSTANCE hInstance, HWND hWnd );
	static void UninitInput( void );
	static void UpdateInput( void );
	static BOOL CALLBACK EnumJoyPadCallBack( const DIDEVICEINSTANCE* pdidInstance, VOID* pContext );
	static BOOL CALLBACK EnumAxesCallBack( LPCDIDEVICEOBJECTINSTANCE pddoi, LPVOID pvRef );

	static LPDIRECTINPUT8 m_pInput;
	static LPDIRECTINPUTDEVICE8 m_pDevKeyboard;
	static BYTE m_aKeyState[ KEYBOARDMAX ];
	static BYTE m_aKeyStateTrigger[ KEYBOARDMAX ];
	static BYTE m_aKeyStateRelease[ KEYBOARDMAX ];
	static int m_aKeyStateRepeat[ KEYBOARDMAX ];
	static int m_aKeyStateRepeatCount[ KEYBOARDMAX ];
	static LPDIRECTINPUTDEVICE8 m_pDevMouse;
	static LPDIRECTINPUTDEVICE8 m_pDevJoypad;
	static DIDEVCAPS m_diDevCaps;
	static DIMOUSESTATE m_aMouseState;
	static DIJOYSTATE m_aJoypadState;
	static BYTE m_aJoyState[ JOYPADMAX ];
	static BYTE m_aJoyStateTrigger[ JOYPADMAX ];
	static BYTE m_aJoyStateRelease[ JOYPADMAX ];
	static int m_aJoyStateRepeat[ JOYPADMAX ];
	static int m_aJoyStateRepeatCount[ JOYPADMAX ];
	static int m_nPovState;
	static int m_nPovStateTrigger;
	static int m_nPovStateRelease;
	static int m_nPovStateRepeat;
	static int m_nPovStateRepeatCount;

public:
	CInput();
	~CInput();

	static HRESULT InitKeyboard( HINSTANCE hInstance, HWND hWnd );
	static HRESULT InitMouse( HINSTANCE hInstance, HWND hWnd );
	static HRESULT InitJoypad( HINSTANCE hInstance, HWND hWnd );
	static DIMOUSESTATE *GetMouseState( void ){ return &m_aMouseState ; };
	static DIJOYSTATE *GetJoypadState( void ){ return &m_aJoypadState ; };
	static LONG GetRightStickVertical( void ){ return m_aJoypadState.lRy ; };
	static LONG GetRightStickHorizontal( void ){ return m_aJoypadState.lRx ; };
	static LONG GetLeftStickVertical( void ){ return m_aJoypadState.lY ; };
	static LONG GetLeftStickHorizontal( void ){ return m_aJoypadState.lX ; };
	static LONG GetTriggerButton( void ){ return m_aJoypadState.lZ ; };
	static void UninitKeyboard( void );
	static void UninitMouse( void );
	static void UninitJoypad( void );
	static void UpdateKeyboard( void );
	static void UpdateMouse( void );
	static void UpdateJoypad( void );
	static bool GetKeyboardPress( int nKey );
	static bool GetKeyboardTrigger( int nKey );
	static bool GetKeyboardRelease( int nKey );
	static bool GetKeyboardRepeat( int nKey );
	static bool GetJoypadPress( int nKey );
	static bool GetJoypadTrigger( int nKey );
	static bool GetJoypadRelease( int nKey );
	static bool GetJoypadRepeat( int nKey );
	static bool GetPovPress( int nKey );
	static bool GetPovTrigger( int nKey );
	static bool GetPovRelease( int nKey );
	static bool GetPovRepeat( int nKey );
};

#endif