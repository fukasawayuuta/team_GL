/******************************************************************************
	�^�C�g�����FfiledObject
	�t�@�C�����FfiledObject.cpp
	�쐬��    �FAT-13B-284 35 �[�V�C��
	�쐬��    �F2016/11/28
******************************************************************************/
/******************************************************************************
	�C���N���[�h�t�@�C��
******************************************************************************/
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "scene.h"
#include "scene3D.h"
#include "fieldObject.h"

/******************************************************************************
	�֐��� : CFieldObject::CFieldObject()
	����   : �R���X�g���N�^
******************************************************************************/
CFieldObject::CFieldObject(int Priority, OBJ_TYPE objType) : CScene3D(Priority, objType)
{
	m_IsBreak = true;
	m_IsActive = true;
}

/******************************************************************************
	�֐��� : CFieldObject::~CFieldObject()
	����   : �f�X�g���N�^
******************************************************************************/
CFieldObject::~CFieldObject()
{
}

/******************************************************************************
	�֐��� : void CFieldObject::Init(void)
	����   : void
	�߂�l : �Ȃ�
	����   : ����������
******************************************************************************/
void CFieldObject::Init(Vector3 pos, Vector3 rot, float width, float height, int index)
{
	m_Pos = pos;
	m_Rot = rot;
	m_Width = width;
	m_Height = height;
	m_nTexIdx = CTexture::SetTexture(index);
}

/******************************************************************************
	�֐��� : void CFieldObject::Uninit(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �I������
******************************************************************************/
void CFieldObject::Uninit(void)
{

}

/******************************************************************************
	�֐��� : void CFieldObject::Update(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �X�V����
******************************************************************************/
void CFieldObject::Update(void)
{

}

/******************************************************************************
	�֐��� : void CFieldObject::Draw(void)
	����   : void
	�߂�l : �Ȃ�
	����   : �`�揈���B
******************************************************************************/
void CFieldObject::Draw(void)
{
	CScene3D::Draw();
}

/******************************************************************************
	�֐��� : CFieldObject *CFieldObject::Create(void)
	����   : void
	�߂�l : obj
	����   : �쐬�֐��B 
******************************************************************************/
CFieldObject *CFieldObject::Create(Vector3 pos, Vector3 rot, float width, float height, int index)
{
	CFieldObject *obj = new CFieldObject;
	obj->Init(pos, rot, width, height, index);

	return obj;
}