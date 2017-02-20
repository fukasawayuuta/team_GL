#pragma once
class CSlime : public CEnemy
{
public:
	CSlime(void);
	~CSlime(void);

	void Update(void);

	static void Create(Vector3 pos, float width, float height, int texIndex, int id);

private:
	float m_Movement;	//	�ړ��X�s�[�h�B
	bool m_TurnFlag;	//	�U��Ԃ�t���O�B
	bool m_Alive;		//	�����Ă���t���O�B
	int m_StateCnt;		//	�X�e�[�g�J�E���^�[�B
};

