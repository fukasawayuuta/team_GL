/******************************************************************************
	タイトル名：filedObject
	ファイル名：filedObject.cpp
	作成者    ：AT-13B-284 35 深澤佑太
	作成日    ：2016/11/28
******************************************************************************/
/******************************************************************************
	インクルードファイル
******************************************************************************/
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "scene.h"
#include "scene3D.h"
#include "fieldObject.h"

/*******************************************************************************
* マクロ定義
*******************************************************************************/
const float WIDTH = SCREEN_WIDTH;
const float HEIGHT = SCREEN_HEIGHT;
const int FADE_COUNT = 30;
const float GROUND = 0.0f;

/******************************************************************************
	関数名 : CFieldObject::CFieldObject()
	説明   : コンストラクタ
******************************************************************************/
CFieldObject::CFieldObject(int Priority, OBJ_TYPE objType) : CScene3D(Priority, objType)
{
	m_IsBreak = true;
	m_IsActive = true;
	m_Collision = Vector2(0.0f, 0.0f);
}

/******************************************************************************
	関数名 : CFieldObject::~CFieldObject()
	説明   : デストラクタ
******************************************************************************/
CFieldObject::~CFieldObject()
{
}

/******************************************************************************
	関数名 : void CFieldObject::Init(void)
	引数   : void
	戻り値 : なし
	説明   : 初期化処理
******************************************************************************/
void CFieldObject::Init(Vector3 pos, Vector3 rot, float width, float height, int index)
{
	m_Pos = pos;
	m_Rot = rot;
	m_Width = width;
	m_Height = height;
	m_Collision = Vector2(width, height);
	m_nTexIdx = CTexture::SetTexture(index);
}

/******************************************************************************
	関数名 : void CFieldObject::Uninit(void)
	引数   : void
	戻り値 : なし
	説明   : 終了処理
******************************************************************************/
void CFieldObject::Uninit(void)
{

}

/******************************************************************************
	関数名 : void CFieldObject::Update(void)
	引数   : void
	戻り値 : なし
	説明   : 更新処理
******************************************************************************/
void CFieldObject::Update(void)
{
	if (m_Pos.y - m_Height * 0.5f <= GROUND)
	{
		m_Pos.y = GROUND + m_Height * 0.5f;
	}
}

/******************************************************************************
	関数名 : void CFieldObject::Draw(void)
	引数   : void
	戻り値 : なし
	説明   : 描画処理。
******************************************************************************/
void CFieldObject::Draw(void)
{
	CScene3D::Draw();
}

/******************************************************************************
	関数名 : CFieldObject *CFieldObject::Create(void)
	引数   : void
	戻り値 : obj
	説明   : 作成関数。 
******************************************************************************/
CFieldObject *CFieldObject::Create(Vector3 pos, Vector3 rot, float width, float height, int index)
{
	CFieldObject *obj = new CFieldObject;
	obj->Init(pos, rot, width, height, index);

	return obj;
}

/******************************************************************************
関数名 : HitCheck
引数   : pos, width, height
戻り値 : なし
説明   : 当たり判定
******************************************************************************/
bool CFieldObject::HitCheck(Vector3 pos, float width, float height)
{
	if (abs(m_Pos.x - pos.x) < (m_Collision.x + width) * 0.5f && abs(m_Pos.y - pos.y) <  (m_Collision.y + height) * 0.5f)
	{
		return true;
	}
	return false;
}

/******************************************************************************
関数名 : Load
引数   : void
戻り値 : なし
説明   : 読み込み
******************************************************************************/
void CFieldObject::Load(void)
{
	// １個目の地面塊
	CFieldObject::Create(Vector3(   0.0f,  25.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(   0.0f,  75.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);

	// 空中塊
	CFieldObject::Create(Vector3( 150.0f, 150.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3( 200.0f, 150.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3( 250.0f, 150.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);

	// 空中塊
	CFieldObject::Create(Vector3( 425.0f, 200.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3( 475.0f, 200.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3( 525.0f, 200.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);

	// ２個目の地面塊
	CFieldObject::Create(Vector3( 700.0f,  25.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3( 750.0f,  25.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3( 800.0f,  25.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3( 750.0f,  75.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);

	// 空中塊
	CFieldObject::Create(Vector3( 950.0f, 125.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(1000.0f, 125.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(1050.0f, 125.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);

	// ３個目の地面塊
	CFieldObject::Create(Vector3(1200.0f,  25.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(1250.0f,  25.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(1300.0f,  25.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(1350.0f,  25.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(1400.0f,  25.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(1450.0f,  25.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(1500.0f,  25.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(1300.0f,  75.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(1350.0f,  75.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(1400.0f,  75.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(1450.0f,  75.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(1500.0f,  75.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(1400.0f, 125.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(1450.0f, 125.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(1500.0f, 125.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(1550.0f, 125.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(1600.0f, 125.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(1650.0f, 125.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);

	// 空中塊
	CFieldObject::Create(Vector3(1850.0f, 100.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(1900.0f, 100.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(1950.0f, 100.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);

	// 空中塊
	CFieldObject::Create(Vector3(2150.0f, 125.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(2200.0f, 125.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(2250.0f, 125.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);

	// ４個目の地面塊
	CFieldObject::Create(Vector3(2500.0f,  25.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(2550.0f,  25.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(2600.0f,  25.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(2650.0f,  25.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(2700.0f,  25.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(2750.0f,  25.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(2800.0f,  25.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(2850.0f,  25.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(2900.0f,  25.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(2550.0f,  75.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(2600.0f,  75.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(2650.0f,  75.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(2700.0f,  75.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(2750.0f,  75.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(2800.0f,  75.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(2850.0f,  75.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(2600.0f, 125.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(2650.0f, 125.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(2700.0f, 125.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(2750.0f, 125.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(2800.0f, 125.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(2650.0f, 175.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(2700.0f, 175.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(2750.0f, 175.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(2700.0f, 220.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);

	// ５個目の地面塊
	CFieldObject::Create(Vector3(3100.0f,  25.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(3150.0f,  25.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(3200.0f,  25.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(3250.0f,  25.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(3300.0f,  25.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(3350.0f,  25.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(3400.0f,  25.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(3200.0f,  75.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(3250.0f,  75.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(3300.0f,  75.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);

	// 空中塊
	CFieldObject::Create(Vector3(3500.0f, 150.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(3550.0f, 150.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(3600.0f, 150.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);

	// 空中塊
	CFieldObject::Create(Vector3(3800.0f,  75.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(3850.0f,  75.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(3900.0f,  75.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);

	// 空中塊
	CFieldObject::Create(Vector3(4100.0f, 125.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(4150.0f, 125.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
	CFieldObject::Create(Vector3(4200.0f, 125.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, TEXTURE_TYPE_BLOCK);
}