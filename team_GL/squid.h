#pragma once
class CSquid : public CEnemy
{
public:
	CSquid(void);
	~CSquid(void);

	void Init(Vector3 pos, float width, float height, int texIndex, int id);
	void Update(void);

	static void Create(Vector3 pos, float width, float height, int texIndex, int id);

private:
	float m_Movement;	//	�ړ��X�s�[�h�B
	bool m_Alive;		//	�����Ă���t���O�B
	bool m_Jump;		//	�W�����v�t���O�B
	int  m_StateCnt;	//	�X�e�[�g�J�E���^�B
	float m_InitPosY;	//	Y���W�����l�B
};

