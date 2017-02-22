#pragma once
class CSlime : public CEnemy
{
public:
	CSlime(int Priority = PRIORITY_3D, OBJ_TYPE objType = OBJ_TYPE_ENEMY);
	~CSlime(void);

	void Update(void);

	static void Create(Vector3 pos, float width, float height, int texIndex, int id);

private:
	float m_Movement;	//	移動スピード。
	bool m_TurnFlag;	//	振り返るフラグ。
	bool m_Alive;		//	生きているフラグ。
	int m_StateCnt;		//	ステートカウンター。
};

