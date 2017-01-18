#pragma once
class COtherPlayer : public CPlayer
{
public:
	COtherPlayer(void);
	~COtherPlayer(void);
	void Update(void);
	void Uninit(void);
	void SetPos(Vector3 pos) {m_Pos = pos;}
	void SetScore(int score) {m_Score = score;}

private:
	int m_Score;
};

