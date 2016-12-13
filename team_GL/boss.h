#pragma once
class CBoss : public CAnimationBoard
{
public:
	CBoss(int Priority = PRIORITY_3D, OBJ_TYPE objType = OBJ_TYPE_ENEMY);
	~CBoss(void);

	void Init(Vector3 pos, float width, float height, int texIndex);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBoss *Create(Vector3 pos, float width, float height, int texIndex);
};

