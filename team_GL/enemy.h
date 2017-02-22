/******************************************************************************
	タイトル名：Enemy
	ファイル名：enemy.h
	作成者    ：AT-13B-284 35 深澤佑太
	作成日    ：2016/12/05
******************************************************************************/
/******************************************************************************
	インクルードガード
******************************************************************************/
#pragma once

/******************************************************************************
	クラス宣言
******************************************************************************/
class CEnemy : public CAnimationBoard
{
public:
	CEnemy(int Priority = PRIORITY_3D, OBJ_TYPE objType = OBJ_TYPE_ENEMY);		//	コンストラクタ。
	~CEnemy(void);		//	デストラクタ。

	void Init(Vector3 pos, float width, float height, int texIndex, int id);		//	初期化関数。
	void Uninit(void);		//	終了関数。
	void Update(void);		//	更新関数。
	void Draw(void);		//	描画関数。

	static void Create(Vector3 pos, float width, float height, int texIndex, int id);		//	生成関数。
	Vector3 GetPosition( void ){ return m_Pos ; }
	Vector2 GetCollision( void ){ return m_Collision ; }
	void HitCheck( Vector3 pos, float width, float height );
	void SetDamage(int damage) { m_Hp -= damage; }
	int GetId( void ){ return m_nId ; }
	bool GetUse( void ){ return m_bUse ;}
	void DeleteCheck(void);
protected:
	int m_Hp;		// ヒットポイント
	int m_nId;
	bool m_bUse;

	void LifeCheck(void);
};

