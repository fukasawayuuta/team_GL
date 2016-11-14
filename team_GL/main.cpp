/******************************************************************************
	�^�C�g�����FOpenGL
	�t�@�C�����Fmain.cpp
	�쐬��    �FAT-13B-284 35 �[�V�C��
	�쐬��    �F2016/11/09
******************************************************************************/
/******************************************************************************
	scanf��warning�h�~
******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS

/******************************************************************************
	�C���N���[�h�t�@�C��
******************************************************************************/
#include "main.h"

/******************************************************************************
	�}�N����`
******************************************************************************/

#define PROJECTNAME ( "OpenGL_Test" )
#define ID_BUTTON000 ( 101 )

/******************************************************************************
	�\���̒�`
******************************************************************************/
/******************************************************************************
	�v���g�^�C�v�錾
******************************************************************************/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/******************************************************************************
	�O���[�o���ϐ�
******************************************************************************/
/******************************************************************************
	�֐����Fint WINAPI WinMain( HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLine , int nCmdShow )
	����  �FHINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLine , int nCmdShow
	�߂�l�F����I���Fint�^��0
	����  :���b�Z�[�W�E�B���h�E�������āA����ɑ΂��Ă̂���������B
******************************************************************************/
int WINAPI WinMain( HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLine , int nCmdShow )
{
	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX) ,			 //�������T�C�Y���w��
		CS_CLASSDC ,                     //�E�B���h�E�̃X�^�C����ݒ�
		WndProc,                         //�E�B���h�E�v���V�[�W���̃A�h���X( �֐��� )���w��
		0 ,                              //�g�p���Ȃ�
		0 ,                              //�g�p���Ȃ�
		hInstance ,                      //WinMain�̃C���X�^���X�n���h�����w��
		NULL ,                           //�g�p����A�C�R���̎w��
		LoadCursor(NULL , IDC_ARROW) ,	 //�}�E�X�J�[�\�����w��( �E�B���h�E�� )
		(HBRUSH)(COLOR_WINDOW + 1) ,	 //�N���C�A���g�̈�̔w�i�F��ݒ�
		NULL ,                           //���j���[�̐ݒ�
		PROJECTNAME ,                    //�E�B���h�E�N���X�̖��O( �j�b�N�l�[���I�� )
		NULL,                            //�������A�C�R�����ݒ肳�ꂽ�ꍇ�̏��
	};

	HWND hWnd;//�E�B���h�E�̃n���h��
	MSG msg;  //���b�Z�[�W

	RegisterClassEx(&wcex);//�E�B���h�E�N���X�̓o�^
	hWnd = CreateWindowEx( 0 ,
						   PROJECTNAME ,		 //�E�B���h�E�N���X�̖��O
						   "TEST" ,				 //�E�B���h�E�̖��O
						   WS_OVERLAPPEDWINDOW , //�E�B���h�E�̃X�^�C��
						   CW_USEDEFAULT ,		 //�����X���W
						   CW_USEDEFAULT ,		 //�����Y���W
						   600 ,				 //��  ( �����œ��� )
						   400 ,				 //����( �����œ��� )
						   NULL ,				 //�e�E�B���h�E�̃n���h��
						   NULL ,				 //���j���[�n���h�����́A�q�E�B���h�EID
						   hInstance ,			 //
						   NULL);//�E�B���h�E�̍쐬�f�[�^

	/* �E�B���h�E�̕\�� */
	ShowWindow(hWnd , nCmdShow);//��N���C�A���g�̈�
	UpdateWindow(hWnd);//�N���C�A���g�̈�

	/* ���b�Z�[�W���[�v */
	while(GetMessage(&msg, NULL, 0, 0) != 0) {
		/* ���b�Z�[�W�̖|��𑗏o */
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnregisterClass(PROJECTNAME, wcex.hInstance);//�E�B���h�E�N���X�̓o�^����

	return (int)msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	static HWND hWndButton000;

	switch( uMsg ) {
	case WM_DESTROY://�E�B���h�E��j��
		PostQuitMessage( 0 );//" WM_QUIT "���b�Z�[�W��Ԃ�
		break;

	case WM_KEYDOWN://�L�[�������ꂽ
		switch( wParam ) {
		case VK_ESCAPE://���z�L�[

			nID = MessageBox( hWnd , " �I�����܂����H " , "  " , MB_YESNO + MB_ICONQUESTION );

			if( nID == IDYES ) {
				DestroyWindow( hWnd );//�E�B���h�E��j��
			}
			break;
		}
		break;
	default :
		break;

	}

	return DefWindowProc( hWnd , uMsg , wParam , lParam );
}