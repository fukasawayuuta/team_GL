/*******************************************************************************
* �^�C�g�����F
* �t�@�C�����Fgamebackground.cpp
* �쐬��	�FAT13B284 31 ���R�a�n
* �쐬��	�F2016/11/28
********************************************************************************
* �X�V����	�F
*
*******************************************************************************/
/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "scene3D.h"
#include "texture.h"
#include "gamebackground.h"

/*******************************************************************************
* �֐����FCGameBackground::CGameBackground()
*
* ����	�F
* �߂�l�F
* ����	�F�R���X�g���N�^
*******************************************************************************/
CGameBackground::CGameBackground(int Priority, OBJ_TYPE objType) : CScene3D(Priority, objType)
{
}

/*******************************************************************************
* �֐����FCGameBackground::~CGameBackground()
*
* ����	�F
* �߂�l�F
* ����	�F�f�X�g���N�^
*******************************************************************************/
CGameBackground::~CGameBackground()
{
}

/*******************************************************************************
* �֐����Fvoid CGameBackground::Init(void)
*
* ����	�F
* �߂�l�F
* ����	�F����������
*******************************************************************************/
void CGameBackground::Init(void)
{
	m_Pos = Vector3( 0.0f, 0.0f, -0.1f );
	m_Rot = Vector3( 0.0f, 0.0f, 0.0f );
	m_Scl = Vector3( 1.0f, 1.0f, 1.0f );
	m_TextureIndex = CTexture::SetTexture( TEXTURE_TYPE_GAME_BG );
	m_Width = SCREEN_WIDTH;
	m_Height = SCREEN_HEIGHT;
	m_Depth = 0.0f;
}

/*******************************************************************************
* �֐����Fvoid CGameBackground::Uninit(void)
*
* ����	�F
* �߂�l�F
* ����	�F�I������
*******************************************************************************/
void CGameBackground::Uninit(void)
{

}

/*******************************************************************************
* �֐����Fvoid CGameBackground::Update(void)
*
* ����	�F
* �߂�l�F
* ����	�F�X�V����
*******************************************************************************/
void CGameBackground::Update(void)
{
	
}

/*******************************************************************************
* �֐����Fvoid CGameBackground::Draw(void)
*
* ����	�F
* �߂�l�F
* ����	�F�`�揈��
*******************************************************************************/
void CGameBackground::Draw(void)
{
	glDisable(GL_LIGHTING);
	//	�������烂�f���r���[�}�g���N�X�̐ݒ�////////////////////////
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//	�����܂Ń��f���r���[�}�g���N�X�̐ݒ�////////////////////////

	glScalef(m_Scl.x, m_Scl.y, m_Scl.z);
	glTranslatef(m_Pos.x, m_Pos.y, m_Pos.z);
	glRotatef(m_Rot.y, 0.0f ,1.0f, 0.0f);

	//�@�e�N�X�`���}�b�s���O�L����
    glEnable(GL_TEXTURE_2D);
    //�@�e�N�X�`�����o�C���h
    glBindTexture(GL_TEXTURE_2D, m_TextureIndex);

	
	//	�`��J�n
	glBegin(GL_TRIANGLE_STRIP);

	//	�F�ݒ�
	glColor4f(1 , 1 , 1, 1);

	//	�@���ݒ�
	glNormal3f(0, 1, 0);

	//	���_���W�ݒ�
	glTexCoord2d(0.0, 0.0);
    glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), m_Pos.z);

	glTexCoord2d(0.0, 1.0);
    glVertex3f(m_Pos.x - (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), m_Pos.z);

	glTexCoord2d(1.0, 0.0);
    glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y + (m_Height * 0.5f), m_Pos.z);

	glTexCoord2d(1.0, 1.0);
    glVertex3f(m_Pos.x + (m_Width * 0.5f), m_Pos.y - (m_Height * 0.5f), m_Pos.z);

	glEnd();
	//	�`��I��

	glEnable(GL_LIGHTING);

	 glBindTexture(GL_TEXTURE_2D, 0);
    //�@�e�N�X�`���}�b�s���O������
    glDisable(GL_TEXTURE_2D);

	//	��������}�g���b�N�X�����ɖ߂�//////////////////////////////
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	//	�����܂Ń}�g���b�N�X�����ɖ߂�//////////////////////////////
}

/*******************************************************************************
* �֐����FCGameBackground *Create( void )
*
* ����	�F
* �߂�l�F
* ����	�F
*******************************************************************************/
CGameBackground *CGameBackground::Create( void )
{
	CGameBackground *pBg = new CGameBackground;
	pBg->Init();
	return pBg ;
}