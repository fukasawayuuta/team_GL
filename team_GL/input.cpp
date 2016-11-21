/******************************************************************************
* �^ �C �g �� : 
* ���@�@�@���@: �L�[���͂̏���
* �v���O������: input.cpp
* ��@���@�ҁ@: AT-13B-284 No.32 ���R�a�n
* ��@���@���@: 2016/04/26
* �C�@���@���@: 
* �ύX����
* 2016/04/26  : �쐬
* ���@��@���@: Copyright(c)2015 nakayama All rights reserved.
******************************************************************************/

/******************************************************************************
* �C���N���[�h�錾
******************************************************************************/
#include"input.h"

/******************************************************************************
* �v���g�^�C�v�錾
******************************************************************************/

/******************************************************************************
* �O���[�o���ϐ��̐錾
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
* �֐���: 
* ���@��: 
* �߂�l: 
* �쐬��: 2016/04/26
* �C����: 
* ���@��: �R���X�g���N�^
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
* �֐���: 
* ���@��: 
* �߂�l: 
* �쐬��: 2016/04/26
* �C����: 
* ���@��: �f�X�g���N�^
******************************************************************************/
CInput::~CInput()
{
}

/******************************************************************************
* �֐���: InitInput
* ���@��: HINSTANCE hInstance, HWND hWnd
* �߂�l: HRESULT�^ S_OK E_FAIL
* �쐬��: 2016/04/26
* �C����: 
* ���@��: ����������
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
* �֐���: UninitKeyboard
* ���@��: void ����
* �߂�l: void ����
* �쐬��: 2016/04/26
* �C����: 
* ���@��: �I������
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
* �֐���: UpdateInput
* ���@��: void ����
* �߂�l: void ����
* �쐬��: 2016/04/26
* �C����: 
* ���@��: �X�V����
******************************************************************************/
void CInput::UpdateInput( void )
{
}

/******************************************************************************
* �֐���: InitKeyboard
* ���@��: HINSTANCE hInstance, HWND hWnd
* �߂�l: HRESULT�^ S_OK E_FAIL
* �쐬��: 2016/04/26
* �C����: 
* ���@��: �L�[�{�[�h����������
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
* �֐���: UninitKeyboard
* ���@��: void ����
* �߂�l: void ����
* �쐬��: 2016/04/26
* �C����: 
* ���@��: �I������
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
* �֐���: InitMouse
* ���@��: HINSTANCE hInstance, HWND hWnd
* �߂�l: HRESULT�^ S_OK E_FAIL
* �쐬��: 2016/04/26
* �C����: 
* ���@��: �}�E�X����������
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
* �֐���: UninitMouse
* ���@��: void ����
* �߂�l: void ����
* �쐬��: 2016/04/26
* �C����: 
* ���@��: �}�E�X�I������
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
* �֐���: InitJoypad
* ���@��: HINSTANCE hInstance, HWND hWnd
* �߂�l: HRESULT�^ S_OK E_FAIL
* �쐬��: 2016/04/26
* �C����: 
* ���@��: �Q�[���p�b�h����������
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
* �֐���: EnumJoyPadCallBack
* ���@��: const DIDEVICEINSTANCE* pdidInstance, VOID* pContext
* �߂�l: BOOL�^ CALLBACK
* �쐬��: 2016/04/26
* �C����: 
* ���@��: �Q�[���p�b�h����������
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
* �֐���: EnumAxesCallBack
* ���@��: const DIDEVICEINSTANCE* pdidInstance, VOID* pContext
* �߂�l: BOOL�^ CALLBACK
* �쐬��: 2016/04/26
* �C����: 
* ���@��: �A�i���O�X�e�B�b�N����������
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
* �֐���: UninitJoypad
* ���@��: void ����
* �߂�l: void ����
* �쐬��: 2016/04/26
* �C����: 
* ���@��: �Q�[���p�b�h�I������
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
* �֐���: UpdateKeyboard
* ���@��: void ����
* �߂�l: void ����
* �쐬��: 2016/04/26
* �C����: 
* ���@��: �X�V����
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
* �֐���: UpdateMouse
* ���@��: void ����
* �߂�l: void ����
* �쐬��: 2016/04/26
* �C����: 
* ���@��: �}�E�X�X�V����
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
* �֐���: UpdateJoypad
* ���@��: void ����
* �߂�l: void ����
* �쐬��: 2016/04/26
* �C����: 
* ���@��: �Q�[���p�b�h�X�V����
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
* �֐���: GetKeyboardPress
* ���@��: nKey
* �߂�l: bool
* �쐬��: 2016/04/26
* �C����: 
* ���@��: �v���X����
******************************************************************************/
bool CInput::GetKeyboardPress( int nKey )
{
	return ( m_aKeyState[ nKey ] & 0x80 ) ? true : false ;
}

/******************************************************************************
* �֐���: GetKeyboardPress
* ���@��: nKey
* �߂�l: bool
* �쐬��: 2016/04/26
* �C����: 
* ���@��: �g���K����
******************************************************************************/
bool CInput::GetKeyboardTrigger( int nKey )
{
	return ( m_aKeyStateTrigger[ nKey ] & 0x80 ) ? true : false ;
}

/******************************************************************************
* �֐���: GetKeyboardPress
* ���@��: nKey
* �߂�l: bool
* �쐬��: 2016/04/26
* �C����: 
* ���@��: �����[�X����
******************************************************************************/
bool CInput::GetKeyboardRelease( int nKey )
{
	return ( m_aKeyStateRelease[ nKey ] & 0x80 ) ? true : false ;
}

/******************************************************************************
* �֐���: GetKeyboardPress
* ���@��: nKey
* �߂�l: bool
* �쐬��: 2016/04/26
* �C����: 
* ���@��: ���s�[�g����
******************************************************************************/
bool CInput::GetKeyboardRepeat( int nKey )
{
	return ( m_aKeyStateRepeat[ nKey ] == 1 ) ? true : false ;
}

/******************************************************************************
* �֐���: GetJoypadPress
* ���@��: nKey
* �߂�l: bool
* �쐬��: 2016/04/26
* �C����: 
* ���@��: �v���X����
******************************************************************************/
bool CInput::GetJoypadPress( int nKey )
{
	return ( m_aJoyState[ nKey ] & 0x80 ) ? true : false ;
}

/******************************************************************************
* �֐���: GetJoypadPress
* ���@��: nKey
* �߂�l: bool
* �쐬��: 2016/04/26
* �C����: 
* ���@��: �g���K����
******************************************************************************/
bool CInput::GetJoypadTrigger( int nKey )
{
	return ( m_aJoyStateTrigger[ nKey ] & 0x80 ) ? true : false ;
}

/******************************************************************************
* �֐���: GetJoypadPress
* ���@��: nKey
* �߂�l: bool
* �쐬��: 2016/04/26
* �C����: 
* ���@��: �����[�X����
******************************************************************************/
bool CInput::GetJoypadRelease( int nKey )
{
	return ( m_aJoyStateRelease[ nKey ] & 0x80 ) ? true : false ;
}

/******************************************************************************
* �֐���: GetJoypadRepeat
* ���@��: nKey
* �߂�l: bool
* �쐬��: 2016/05/10
* �C����: 
* ���@��: ���s�[�g����
******************************************************************************/
bool CInput::GetJoypadRepeat( int nKey )
{
	return ( m_aJoyStateRepeat[ nKey ] == 1 ) ? true : false ;
}

/******************************************************************************
* �֐���: GetPovPress
* ���@��: nKey
* �߂�l: bool
* �쐬��: 2016/04/26
* �C����: 
* ���@��: �v���X����
******************************************************************************/
bool CInput::GetPovPress( int nKey )
{
	return ( m_nPovState == nKey ) ? true : false ;
}

/******************************************************************************
* �֐���: GetPovTrigger
* ���@��: nKey
* �߂�l: bool
* �쐬��: 2016/04/26
* �C����: 
* ���@��: �g���K����
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
* �֐���: GetPovRelease
* ���@��: nKey
* �߂�l: bool
* �쐬��: 2016/04/26
* �C����: 
* ���@��: �����[�X����
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
* �֐���: GetPovRelease
* ���@��: nKey
* �߂�l: bool
* �쐬��: 2016/05/10
* �C����: 
* ���@��: ���s�[�g����
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