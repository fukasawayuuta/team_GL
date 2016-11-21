/******************************************************************************
	�^�C�g���� : �����_���N���X
	�t�@�C���� : renderer.cpp
	�쐬��     : AT-13C-284 36 �[�V�C��
	�쐬��     : 2016/11/14
	�X�V��     : 
******************************************************************************/
/******************************************************************************
	�C���N���[�h�t�@�C��
******************************************************************************/
#include "renderer.h"

/******************************************************************************
	�}�N����`
******************************************************************************/
/******************************************************************************
	�O���[�o���ϐ�
******************************************************************************/
/******************************************************************************
	�֐��� : CRerender::CRerender()
	����   : �R���X�g���N�^
******************************************************************************/
CRenderer::CRenderer(void)
{
}

/******************************************************************************
	�֐��� : CRerender::~CRerender()
	����   : �f�X�g���N�^
******************************************************************************/
CRenderer::~CRenderer(void)
{
}

/******************************************************************************
	�֐��� ; HRESULT CRerender::Init( HINSTANCE hInstance , HWND hWnd , BOOL bWindow )
	����   : hInstance, hWnd, bWindow
	�߂�l : S_OK, E_FAIL
	����   : �I�u�W�F�N�g�̍쐬���A��ʕ��⍂���A�o�b�N�o�b�t�@�̌`���Ɛ����w�肵�A
			 �E�B���h�E���[�h���t���X�N���[�����[�h�ŏo�������w�肵�A
			 �f�o�C�X���쐬����B

			 �|���S����`�悷�邽�߂̏��������������Ă���B
******************************************************************************/
HRESULT CRenderer::Init(HINSTANCE hInstance , HWND hWnd , BOOL bWindow)
{
	// OpenGL������

    // �s�N�Z���t�H�[�}�b�g������
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
        return 0; // �Y������s�N�Z���t�H�[�}�b�g������
	}

    // OpenGL���g���f�o�C�X�R���e�L�X�g�Ɏw��̃s�N�Z���t�H�[�}�b�g���Z�b�g
    if (!SetPixelFormat(m_DC, format, &pfd)) {
        return 0; // DC�փt�H�[�}�b�g��ݒ肷��̂Ɏ��s
	}

    // OpenGL context���쐬
    m_GLRC = wglCreateContext(m_DC);

    // �쐬���ꂽ�R���e�L�X�g���J�����g�i���ݎg�p���̃R���e�L�X�g�j���H
    if (!wglMakeCurrent(m_DC, m_GLRC)) {
        return 0; // �����������Ȃ��݂����c
	}
	return S_OK;
}

/******************************************************************************
	�֐��� : void CRerender::Uninit(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �J�����g�R���e�L�X�g�𖳌��ɂ���
			 �J�����g�R���e�L�X�g���폜
			 �f�o�C�X�R���e�L�X�g���
			 Scene�N���X�̉������
******************************************************************************/
void CRenderer::Uninit(void)
{
    // �J�����g�R���e�L�X�g�𖳌��ɂ���
    wglMakeCurrent(NULL, NULL);

    // �J�����g�R���e�L�X�g���폜
    wglDeleteContext(m_GLRC);

    // �f�o�C�X�R���e�L�X�g���
    ReleaseDC(m_Wnd, m_DC);
}

/******************************************************************************
	�֐��� : void CRerender::Update(void)
	����   : void
	�߂�l : �Ȃ�
	����   : Scene�N���X�̍X�V����
******************************************************************************/
void CRenderer::Update(void)
{
	
}

/******************************************************************************
	�֐��� : void CRerender::Draw(HDC dc)
	����   : void
	�߂�l : �Ȃ�
	����   : �|���S���Ȃǂ̕`�揈��
******************************************************************************/
void CRenderer::Draw(void)
{

}

/******************************************************************************
	�֐��� : void CRerender::Begin(HDC dc)
	����   : void
	�߂�l : �Ȃ�
	����   : �`�揈���̏���
******************************************************************************/
void CRenderer::Begin(void)
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);					//	�N���A�J���[�̐ݒ�
	glClearDepth(1.0f);										//	�N���A���̐[�x�l��ݒ�
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//	(�o�b�N�o�b�t�@ | Z�o�b�t�@)
	glEnable(GL_DEPTH_TEST);								//�uZ�e�X�g�v��L���ɂ���
}
/******************************************************************************
	�֐��� : void CRerender::End(HDC dc)
	����   : void
	�߂�l : �Ȃ�
	����   : �`�揈���̌㏈��
******************************************************************************/
void CRenderer::End(void)
{
	SwapBuffers(m_DC);			//	��ʂ̍X�V
}
/******************************************************************************
	�֐��� : void CRerender::End(HDC dc)
	����   : void
	�߂�l : �Ȃ�
	����   : �`�揈���̍쐬
******************************************************************************/
CRenderer *CRenderer::Create(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	CRenderer *obj = new CRenderer;
	obj->Init(hInstance, hWnd, bWindow);

	return obj;
}