/*******************************************************************************
* タイトル名：
* ファイル名：title.cpp
* 作成者	：AT13B284 10 小笠原啓太
* 作成日	：2016/11/14
********************************************************************************
* 更新履歴	：
*
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "main.h"
#include "mode.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "scene.h"
#include "scene2D.h"
#include "input.h"

/*******************************************************************************
* 関数名：CTitle::CTitle()
*
* 引数	：
* 戻り値：
* 説明	：コンストラクタ
*******************************************************************************/
CTitle::CTitle()
{
}

/*******************************************************************************
* 関数名：CTitle::~CTitle()
*
* 引数	：
* 戻り値：
* 説明	：デストラクタ
*******************************************************************************/
CTitle::~CTitle()
{
}

/*******************************************************************************
* 関数名：void CTitle::Init( void )
*
* 引数	：
* 戻り値：
* 説明	：初期化処理
*******************************************************************************/
void CTitle::Init(void)
{
	CScene *scene;

	scene = CScene2D::Create("data\\TEXTURE\\title_test.tga");
}

/*******************************************************************************
* 関数名：void CTitle::Uninit( void )
*
* 引数	：
* 戻り値：
* 説明	：終了処理
*******************************************************************************/
void CTitle::Uninit(void)
{
	CScene::ReleaseAll();
}

/*******************************************************************************
* 関数名：void CTitle::Update( void )
*
* 引数	：
* 戻り値：
* 説明	：更新処理
*******************************************************************************/
void CTitle::Update(void)
{
	CScene::UpdateAll();

	if (CInput::GetKeyboardTrigger(DIK_RETURN))
	{
		CFade::Start(new CGame);
	}
}

/*******************************************************************************
* 関数名：void CTitle::Draw( void )
*
* 引数	：
* 戻り値：
* 説明	：描画処理
*******************************************************************************/
void CTitle::Draw(void)
{
	CScene::DrawAll();
}