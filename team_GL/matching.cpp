/*******************************************************************************
* タイトル名：
* ファイル名：matching.cpp
* 作成者	：AT13B284 31 中山和馬
* 作成日	：2016/11/28
********************************************************************************
* 更新履歴	：
*
*******************************************************************************/
/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "main.h"
#include "mode.h"
#include "matching.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "scene.h"
#include "scene2D.h"
#include "input.h"
#include "texture.h"

/*******************************************************************************
* 関数名：CMatching::CMatching()
*
* 引数	：
* 戻り値：
* 説明	：コンストラクタ
*******************************************************************************/
CMatching::CMatching()
{
}

/*******************************************************************************
* 関数名：CMatching::~CMatching()
*
* 引数	：
* 戻り値：
* 説明	：デストラクタ
*******************************************************************************/
CMatching::~CMatching()
{
}

/*******************************************************************************
* 関数名：void CMatching::Init( void )
*
* 引数	：
* 戻り値：
* 説明	：初期化処理
*******************************************************************************/
void CMatching::Init(void)
{
	CScene2D::Create(TEXTURE_TYPE_MATCHING_BG);
}

/*******************************************************************************
* 関数名：void CMatching::Uninit( void )
*
* 引数	：
* 戻り値：
* 説明	：終了処理
*******************************************************************************/
void CMatching::Uninit(void)
{
	CScene::ReleaseAll();
}

/*******************************************************************************
* 関数名：void CMatching::Update( void )
*
* 引数	：
* 戻り値：
* 説明	：更新処理
*******************************************************************************/
void CMatching::Update(void)
{
	CScene::UpdateAll();

	if (CInput::GetKeyboardTrigger(DIK_RETURN))
	{
		CFade::Start(new CGame);
	}
}

/*******************************************************************************
* 関数名：void CMatching::Draw( void )
*
* 引数	：
* 戻り値：
* 説明	：描画処理
*******************************************************************************/
void CMatching::Draw(void)
{
	CScene::DrawAll();
}