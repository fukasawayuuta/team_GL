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
	float m_Movement;	//	移動スピード。
	bool m_Alive;		//	生きているフラグ。
	bool m_Jump;		//	ジャンプフラグ。
	int  m_StateCnt;	//	ステートカウンタ。
	float m_InitPosY;	//	Y座標初期値。
};

