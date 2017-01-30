#pragma once

const int DRAW_SPEED = 10;				// �`��X�s�[�h
const int WALK_DRAW = 4;				// �������[�V�����̃R�}��

class COtherPlayer : public CPlayer
{
public:
	COtherPlayer(void);
	~COtherPlayer(void);
	void Init( int nId );
	void Update(void);
	void Uninit(void);
	void Draw(void);
	void SetPos(Vector3 pos) {m_Pos = pos;}
	void SetScore(int score) {m_Score = score;}

private:
	int m_Score;
};

