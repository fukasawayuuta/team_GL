/******************************************************************************
* タ イ ト ル : 
* 説　　　明　: キー入力の処理
* プログラム名: input.cpp
* 作　成　者　: AT-13B-284 No.32 中山和馬
* 作　成　日　: 2016/04/26
* 修　正　日　: 
* 変更履歴
* 2016/04/26  : 作成
* 著　作　権　: Copyright(c)2015 nakayama All rights reserved.
******************************************************************************/

/******************************************************************************
* インクルード宣言
******************************************************************************/
#include"input.h"

/******************************************************************************
* プロトタイプ宣言
******************************************************************************/

/******************************************************************************
* グローバル変数の宣言
******************************************************************************/
LPDIRECTINPUT8 CInput::m_pInput;
LPDIRECTINPUTDEVICE8 CInput::m_pDevKeyboard;
BYTE CInput::m_aKeyState[ KEYBOARDMAX ];
BYTE CInput::m_aKeyStateTrigger[ KEYBOARDMAX ];
BYTE CInput::m_aKeyStateRelease[ KEYBOARDMAX ];
int CInput::m_aKeyStateRepeat[ KEYBOARDMAX ];
int CInput::m_aKeyStateRepeatCount[ KEYBOARDMAX ];
LPDIRECTINPUTDEVICE8 CInput::m_pDevMouse;
LPDIRECTINPUTDEVICE8 CInput::m_pDevJoypad;
DIDEVCAPS CInput::m_diDevCaps;
DIJOYSTATE CInput::m_aJoypadState;
BYTE CInput::m_aJoyState[ JOYPADMAX ];
BYTE CInput::m_aJoyStateTrigger[ JOYPADMAX ];
BYTE CInput::m_aJoyStateRelease[ JOYPADMAX ];
int CInput::m_aJoyStateRepeat[ JOYPADMAX ];
int CInput::m_aJoyStateRepeatCount[ JOYPADMAX ];
int CInput::m_nPovState;
int CInput::m_nPovStateTrigger;
int CInput::m_nPovStateRelease;
int CInput::m_nPovStateRepeat;
int CInput::m_nPovStateRepeatCount;
DIMOUSESTATE CInput::m_aMouseState;

/******************************************************************************
* 関数名: 
* 引　数: 
* 戻り値: 
* 作成日: 2016/04/26
* 修正日: 
* 説　明: コンストラクタ
******************************************************************************/
CInput::CInput()
{
	m_pInput = NULL;
	m_pDevKeyboard = NULL;
	m_pDevMouse = NULL;
	m_pDevJoypad = NULL;
	for( int i = 0; i < KEYBOARDMAX; i ++ )
	{
		m_aKeyState[ i ] = 0;
		m_aKeyStateTrigger[ i ] = 0;
		m_aKeyStateRelease[ i ] = 0;
		m_aKeyStateRepeat[ i ] = 0;
		m_aKeyStateRepeatCount[ i ] = 0;
	}
	for( int j = 0; j < JOYPADMAX; j ++ )
	{
		m_aJoyState[ j ] = 0;
		m_aJoyStateTrigger[ j ] = 0;
		m_aJoyStateRelease[ j ] = 0;
		m_aJoyStateRepeat[ j ] = 0;
		m_aJoyStateRepeatCount[ j ] = 0;
	}
	m_nPovState = 0;
	m_nPovStateTrigger = 0;
	m_nPovStateRelease = 0;
	m_nPovStateRepeat = 0;
	m_nPovStateRepeatCount = 0;
}

/******************************************************************************
* 関数名: 
* 引　数: 
* 戻り値: 
* 作成日: 2016/04/26
* 修正日: 
* 説　明: デストラクタ
******************************************************************************/
CInput::~CInput()
{
}

/******************************************************************************
* 関数名: InitInput
* 引　数: HINSTANCE hInstance, HWND hWnd
* 戻り値: HRESULT型 S_OK E_FAIL
* 作成日: 2016/04/26
* 修正日: 
* 説　明: 初期化処理
******************************************************************************/
HRESULT CInput::InitInput( HINSTANCE hInstance, HWND hWnd )
{
	if( m_pInput == NULL )
	{
		if( FAILED( DirectInput8Create( hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, ( void** )&m_pInput, NULL ) ) )
		{
			return E_FAIL ;
		}
	}
	
	return S_OK ;
}

/******************************************************************************
* 関数名: UninitKeyboard
* 引　数: void 無し
* 戻り値: void 無し
* 作成日: 2016/04/26
* 修正日: 
* 説　明: 終了処理
******************************************************************************/
void CInput::UninitInput( void )
{
	if( m_pInput != NULL )
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

/******************************************************************************
* 関数名: UpdateInput
* 引　数: void 無し
* 戻り値: void 無し
* 作成日: 2016/04/26
* 修正日: 
* 説　明: 更新処理
******************************************************************************/
void CInput::UpdateInput( void )
{
}

/******************************************************************************
* 関数名: InitKeyboard
* 引　数: HINSTANCE hInstance, HWND hWnd
* 戻り値: HRESULT型 S_OK E_FAIL
* 作成日: 2016/04/26
* 修正日: 
* 説　明: キーボード初期化処理
******************************************************************************/
HRESULT CInput::InitKeyboard( HINSTANCE hInstance, HWND hWnd )
{
	if( FAILED( InitInput( hInstance, hWnd ) ) )
	{
		return E_FAIL ;
	}
	if( FAILED( m_pInput->CreateDevice( GUID_SysKeyboard, &m_pDevKeyboard, NULL ) ) )
	{
		return E_FAIL ;
	}
	if( FAILED( m_pDevKeyboard->SetDataFormat( &c_dfDIKeyboard ) ) )
	{
		return E_FAIL ;
	}
	if( FAILED( m_pDevKeyboard->SetCooperativeLevel( hWnd, ( DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) ) )
	{
		return E_FAIL ;
	}
	m_pDevKeyboard->Acquire();
	return S_OK ;
}

/******************************************************************************
* 関数名: UninitKeyboard
* 引　数: void 無し
* 戻り値: void 無し
* 作成日: 2016/04/26
* 修正日: 
* 説　明: 終了処理
******************************************************************************/
void CInput::UninitKeyboard( void )
{
	if( m_pDevKeyboard != NULL )
	{
		m_pDevKeyboard->Unacquire();
		m_pDevKeyboard->Release();
		m_pDevKeyboard = NULL;
	}
	UninitInput();
}

/******************************************************************************
* 関数名: InitMouse
* 引　数: HINSTANCE hInstance, HWND hWnd
* 戻り値: HRESULT型 S_OK E_FAIL
* 作成日: 2016/04/26
* 修正日: 
* 説　明: マウス初期化処理
******************************************************************************/
HRESULT CInput::InitMouse( HINSTANCE hInstance, HWND hWnd )
{
	if( FAILED( m_pInput->CreateDevice( GUID_SysMouse, &m_pDevMouse, NULL ) ) )
	{
		return E_FAIL ;
	}
	if( FAILED( m_pDevMouse->SetDataFormat( &c_dfDIMouse ) ) )
	{
		return E_FAIL ;
	}
	if( FAILED( m_pDevMouse->SetCooperativeLevel( hWnd, ( DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) ) )
	{
		return E_FAIL ;
	}
	m_pDevMouse->Acquire();
	return S_OK ;
}

/******************************************************************************
* 関数名: UninitMouse
* 引　数: void 無し
* 戻り値: void 無し
* 作成日: 2016/04/26
* 修正日: 
* 説　明: マウス終了処理
******************************************************************************/
void CInput::UninitMouse( void )
{
	if( m_pDevMouse != NULL )
		{
			m_pDevMouse->Unacquire();
			m_pDevMouse->Release();
			m_pDevMouse = NULL;
		}
	UninitInput();
}

/******************************************************************************
* 関数名: InitJoypad
* 引　数: HINSTANCE hInstance, HWND hWnd
* 戻り値: HRESULT型 S_OK E_FAIL
* 作成日: 2016/04/26
* 修正日: 
* 説　明: ゲームパッド初期化処理
******************************************************************************/
HRESULT CInput::InitJoypad( HINSTANCE hInstance, HWND hWnd )
{
	if( FAILED( m_pInput->EnumDevices( DI8DEVCLASS_GAMECTRL, CInput::EnumJoyPadCallBack, NULL, DIEDFL_ATTACHEDONLY ) ) || m_pDevJoypad == NULL )
	{
		return E_FAIL ;
	}
	if( FAILED( m_pDevJoypad->SetDataFormat( &c_dfDIJoystick ) ) )
	{
		return E_FAIL ;
	}
	if( FAILED( m_pDevJoypad->SetCooperativeLevel( hWnd, ( DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) ) )
	{
		return E_FAIL ;
	}
	if( FAILED( m_pDevJoypad->EnumObjects( CInput::EnumAxesCallBack, NULL, DIDFT_AXIS ) ) )
	{
		return E_FAIL ;
	}
	m_pDevJoypad->Acquire();
	return S_OK ;
}

/******************************************************************************
* 関数名: EnumJoyPadCallBack
* 引　数: const DIDEVICEINSTANCE* pdidInstance, VOID* pContext
* 戻り値: BOOL型 CALLBACK
* 作成日: 2016/04/26
* 修正日: 
* 説　明: ゲームパッド初期化処理
******************************************************************************/
BOOL CALLBACK CInput::EnumJoyPadCallBack( const DIDEVICEINSTANCE* pdidInstance, VOID* pContext )
{
	if( m_pDevJoypad == NULL )
	{
		if( FAILED( m_pInput->CreateDevice( pdidInstance->guidInstance, &m_pDevJoypad, NULL ) ) )
		{
			return DIENUM_CONTINUE ;
		}
		m_diDevCaps.dwSize = sizeof( DIDEVCAPS );
		if( FAILED( m_pDevJoypad->GetCapabilities( &m_diDevCaps ) ) )
		{
			m_pDevJoypad->Release();
			m_pDevJoypad = NULL;
			return DIENUM_CONTINUE ;
		}
		return DIENUM_CONTINUE ;
	}
	return DIENUM_STOP ;
}

/******************************************************************************
* 関数名: EnumAxesCallBack
* 引　数: const DIDEVICEINSTANCE* pdidInstance, VOID* pContext
* 戻り値: BOOL型 CALLBACK
* 作成日: 2016/04/26
* 修正日: 
* 説　明: アナログスティック初期化処理
******************************************************************************/
BOOL CALLBACK CInput::EnumAxesCallBack( LPCDIDEVICEOBJECTINSTANCE pddoi, LPVOID pvRef )
{
	DIPROPRANGE diprg;
	ZeroMemory( &diprg, sizeof( diprg ) );
	diprg.diph.dwSize = sizeof( diprg );
	diprg.diph.dwHeaderSize = sizeof( diprg.diph );
	diprg.diph.dwObj = pddoi->dwType;
	diprg.diph.dwHow = DIPH_BYID;
	diprg.lMin = -1000;
	diprg.lMax = 1000;
	if( FAILED( m_pDevJoypad->SetProperty( DIPROP_RANGE, &diprg.diph ) ) )
	{
		return DIENUM_STOP ;
	}
	return DIENUM_CONTINUE ;
}

/******************************************************************************
* 関数名: UninitJoypad
* 引　数: void 無し
* 戻り値: void 無し
* 作成日: 2016/04/26
* 修正日: 
* 説　明: ゲームパッド終了処理
******************************************************************************/
void CInput::UninitJoypad( void )
{
	if( m_pDevJoypad != NULL )
	{
		m_pDevJoypad->Unacquire();
		m_pDevJoypad->Release();
		m_pDevJoypad = NULL;
	}
}

/******************************************************************************
* 関数名: UpdateKeyboard
* 引　数: void 無し
* 戻り値: void 無し
* 作成日: 2016/04/26
* 修正日: 
* 説　明: 更新処理
******************************************************************************/
void CInput::UpdateKeyboard( void )
{
	BYTE aKeyState[ 256 ];
	if( SUCCEEDED( m_pDevKeyboard->GetDeviceState( sizeof( aKeyState ), &aKeyState[ 0 ] ) ) )
	{
		for( int nCntKey = 0; nCntKey < 256; nCntKey ++ )
		{
			m_aKeyStateTrigger[ nCntKey ] = ~m_aKeyState[ nCntKey ] & aKeyState[ nCntKey ];
			m_aKeyStateRelease[ nCntKey ] = m_aKeyState[ nCntKey ] & ~aKeyState[ nCntKey ];
			m_aKeyState[ nCntKey ] = aKeyState[ nCntKey ];
			if( aKeyState[ nCntKey ] )
			{
				m_aKeyStateRepeatCount[ nCntKey ] ++ ;
				if( m_aKeyStateRepeatCount[ nCntKey ] >= 20 )
				{
					m_aKeyStateRepeat[ nCntKey ] = 1;
				}
			}
			else
			{
				m_aKeyStateRepeatCount[ nCntKey ] = 0;
				m_aKeyStateRepeat[ nCntKey ] = 0;
			}
		}
	}
	else
	{
		m_pDevKeyboard->Acquire();
	}
}

/******************************************************************************
* 関数名: UpdateMouse
* 引　数: void 無し
* 戻り値: void 無し
* 作成日: 2016/04/26
* 修正日: 
* 説　明: マウス更新処理
******************************************************************************/
void CInput::UpdateMouse( void )
{
	DIMOUSESTATE aMouseState;
	if( SUCCEEDED( m_pDevMouse->GetDeviceState( sizeof( aMouseState ), &aMouseState ) ) )
	{
		m_aMouseState = aMouseState;
	}
	else
	{
		m_pDevMouse->Acquire();
	}
}

/******************************************************************************
* 関数名: UpdateJoypad
* 引　数: void 無し
* 戻り値: void 無し
* 作成日: 2016/04/26
* 修正日: 
* 説　明: ゲームパッド更新処理
******************************************************************************/
void CInput::UpdateJoypad( void )
{
	DIJOYSTATE aJoyState;

	if( FAILED( m_pDevJoypad->Poll() ) )
	{
		while( m_pDevJoypad->Acquire() == DIERR_INPUTLOST )
		{

		}
	}
	if( SUCCEEDED( m_pDevJoypad->GetDeviceState( sizeof( DIJOYSTATE ), &aJoyState ) ) )
	{
		for( int nCntKey = 0; nCntKey < 32; nCntKey ++ )
		{
			m_aJoyStateTrigger[ nCntKey ] = ~m_aJoyState[ nCntKey ] & aJoyState.rgbButtons[ nCntKey ];
			m_aJoyStateRelease[ nCntKey ] = m_aJoyState[ nCntKey ] & ~aJoyState.rgbButtons[ nCntKey ];
			m_aJoyState[ nCntKey ] = aJoyState.rgbButtons[ nCntKey ];
			if( aJoyState.rgbButtons[ nCntKey ] )
			{
				m_aJoyStateRepeatCount[ nCntKey ] ++ ;
				if( m_aJoyStateRepeatCount[ nCntKey ] >= 20 )
				{
					m_aJoyStateRepeat[ nCntKey ] = 1;
				}
			}
			else
			{
				m_aJoyStateRepeatCount[ nCntKey ] = 0;
				m_aJoyStateRepeat[ nCntKey ] = 0;
			}
		}

		m_nPovState = aJoyState.rgdwPOV[ 0 ];
		if( m_aJoypadState.rgdwPOV[ 0 ] != aJoyState.rgdwPOV[ 0 ] && m_aJoypadState.rgdwPOV[ 0 ] == -1 )
		{
			m_nPovStateTrigger = 1;
		}
		else
		{
			m_nPovStateTrigger = 0;
		}
		
		if( m_aJoypadState.rgdwPOV[ 0 ] != aJoyState.rgdwPOV[ 0 ] && m_aJoypadState.rgdwPOV[ 0 ] != -1 )
		{
			m_nPovStateRelease = 1;
		}
		else
		{
			m_nPovStateRelease = 0;
		}

		if( m_aJoypadState.rgdwPOV[ 0 ] == aJoyState.rgdwPOV[ 0 ] )
		{
			m_nPovStateRepeatCount ++ ;
			if( m_nPovStateRepeatCount >= 20 )
			{
				m_nPovStateRepeat = 1;
			}
		}
		else
		{
			m_nPovStateRepeat = 0;
			m_nPovStateRepeatCount = 0;
		}

		m_aJoypadState = aJoyState;
	}
	else
	{
		m_pDevJoypad->Acquire();
	}
}

/******************************************************************************
* 関数名: GetKeyboardPress
* 引　数: nKey
* 戻り値: bool
* 作成日: 2016/04/26
* 修正日: 
* 説　明: プレス処理
******************************************************************************/
bool CInput::GetKeyboardPress( int nKey )
{
	return ( m_aKeyState[ nKey ] & 0x80 ) ? true : false ;
}

/******************************************************************************
* 関数名: GetKeyboardPress
* 引　数: nKey
* 戻り値: bool
* 作成日: 2016/04/26
* 修正日: 
* 説　明: トリガ処理
******************************************************************************/
bool CInput::GetKeyboardTrigger( int nKey )
{
	return ( m_aKeyStateTrigger[ nKey ] & 0x80 ) ? true : false ;
}

/******************************************************************************
* 関数名: GetKeyboardPress
* 引　数: nKey
* 戻り値: bool
* 作成日: 2016/04/26
* 修正日: 
* 説　明: リリース処理
******************************************************************************/
bool CInput::GetKeyboardRelease( int nKey )
{
	return ( m_aKeyStateRelease[ nKey ] & 0x80 ) ? true : false ;
}

/******************************************************************************
* 関数名: GetKeyboardPress
* 引　数: nKey
* 戻り値: bool
* 作成日: 2016/04/26
* 修正日: 
* 説　明: リピート処理
******************************************************************************/
bool CInput::GetKeyboardRepeat( int nKey )
{
	return ( m_aKeyStateRepeat[ nKey ] == 1 ) ? true : false ;
}

/******************************************************************************
* 関数名: GetJoypadPress
* 引　数: nKey
* 戻り値: bool
* 作成日: 2016/04/26
* 修正日: 
* 説　明: プレス処理
******************************************************************************/
bool CInput::GetJoypadPress( int nKey )
{
	return ( m_aJoyState[ nKey ] & 0x80 ) ? true : false ;
}

/******************************************************************************
* 関数名: GetJoypadPress
* 引　数: nKey
* 戻り値: bool
* 作成日: 2016/04/26
* 修正日: 
* 説　明: トリガ処理
******************************************************************************/
bool CInput::GetJoypadTrigger( int nKey )
{
	return ( m_aJoyStateTrigger[ nKey ] & 0x80 ) ? true : false ;
}

/******************************************************************************
* 関数名: GetJoypadPress
* 引　数: nKey
* 戻り値: bool
* 作成日: 2016/04/26
* 修正日: 
* 説　明: リリース処理
******************************************************************************/
bool CInput::GetJoypadRelease( int nKey )
{
	return ( m_aJoyStateRelease[ nKey ] & 0x80 ) ? true : false ;
}

/******************************************************************************
* 関数名: GetJoypadRepeat
* 引　数: nKey
* 戻り値: bool
* 作成日: 2016/05/10
* 修正日: 
* 説　明: リピート処理
******************************************************************************/
bool CInput::GetJoypadRepeat( int nKey )
{
	return ( m_aJoyStateRepeat[ nKey ] == 1 ) ? true : false ;
}

/******************************************************************************
* 関数名: GetPovPress
* 引　数: nKey
* 戻り値: bool
* 作成日: 2016/04/26
* 修正日: 
* 説　明: プレス処理
******************************************************************************/
bool CInput::GetPovPress( int nKey )
{
	return ( m_nPovState == nKey ) ? true : false ;
}

/******************************************************************************
* 関数名: GetPovTrigger
* 引　数: nKey
* 戻り値: bool
* 作成日: 2016/04/26
* 修正日: 
* 説　明: トリガ処理
******************************************************************************/
bool CInput::GetPovTrigger( int nKey )
{
	if( m_aJoypadState.rgdwPOV[ 0 ] == nKey )
	{
		return ( m_nPovStateTrigger ) ? true : false ;
	}
	else
	{
		return false;
	}
}

/******************************************************************************
* 関数名: GetPovRelease
* 引　数: nKey
* 戻り値: bool
* 作成日: 2016/04/26
* 修正日: 
* 説　明: リリース処理
******************************************************************************/
bool CInput::GetPovRelease( int nKey )
{
	if( m_aJoypadState.rgdwPOV[ 0 ] != nKey )
	{
		return ( m_nPovStateRelease ) ? true : false ;
	}
	else
	{
		return false;
	}
}

/******************************************************************************
* 関数名: GetPovRelease
* 引　数: nKey
* 戻り値: bool
* 作成日: 2016/05/10
* 修正日: 
* 説　明: リピート処理
******************************************************************************/
bool CInput::GetPovRepeat( int nKey )
{
	if( m_aJoypadState.rgdwPOV[ 0 ] != nKey )
	{
		return ( m_nPovStateRepeat ) ? true : false ;
	}
	else
	{
		return false;
	}
}