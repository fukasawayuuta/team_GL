/******************************************************************************
	�^�C�g�����FfiledObject
	�t�@�C�����FfiledObject.h
	�쐬��    �FAT-13B-284 35 �[�V�C��
	�쐬��    �F2016/11/28
******************************************************************************/
/******************************************************************************
	�C���N���[�h�K�[�h
******************************************************************************/
#pragma once

/******************************************************************************
	�N���X�錾
******************************************************************************/
class CFieldObject : public CScene3D
{
public:
	typedef enum {
		OBJECT_TYPE_NONE = 0,			//	none.
		OBJECT_TYPE_BREAK_BLOCK,		//	����u���b�N�B
		OBJECT_TYPE_NOT_BREAK_BLOCK,	//	���Ȃ��u���b�N�B
		OBJECT_TYPE_MAX
	};

	CFieldObject(int Priority = PRIORITY_3D, OBJ_TYPE objType = OBJ_TYPE_FIELDOBJ);		//	�R���X�g���N�^�B
	~CFieldObject();	//	�f�X�g���N�^�B

	void Init(Vector3 pos, Vector3 rot, float width, float height, int index);		//	�������֐��B
	void Uninit(void);		//	�I���֐��B
	void Update(void);		//	�X�V�֐��B
	void Draw(void);		//	�`��֐��B

	void SetActive(bool active) {m_IsActive = active;}		//	�t���O���Z�b�g����֐��B
	static CFieldObject *Create(Vector3 pos, Vector3 rot, float width, float height, int index);		//	�����֐��B
	static void Load(void);
	bool HitCheck(Vector3 pos, float width, float height);

private:
	bool m_IsBreak;			//	���邩�ǂ����̃t���O�B
	bool m_IsActive;		//	�����Ă��邩�ǂ����̃t���O�B
};

