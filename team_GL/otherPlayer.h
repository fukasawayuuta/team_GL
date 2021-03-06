#pragma once

const int DRAW_SPEED = 10;				// 描画スピード
const int WALK_DRAW = 4;				// 歩きモーションのコマ数

class COtherPlayer : public CPlayer
{
public:
	COtherPlayer(void);
	~COtherPlayer(void);
	void Init( int nId, Vector3 pos, float width, float height );
	void Update(void);
	void Uninit(void);
	void Draw(void);
	void SetPos(Vector3 pos) {m_Pos = pos;}
	void SetScore(int score) {m_Score = score;}

	static COtherPlayer *Create( int nId, Vector3 pos, float width, float height );

private:
	int m_Score;
	int m_nId;
};

