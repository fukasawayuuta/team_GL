/*******************************************************************************
* タイトル名：
* ファイル名：result.cpp
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
#include "texture.h"

/*******************************************************************************
* 関数名：CResult::CResult()
*
* 引数	：
* 戻り値：
* 説明	：コンストラクタ
*******************************************************************************/
CResult::CResult()
{
}

/*******************************************************************************
* 関数名：CResult::~CResult()
*
* 引数	：
* 戻り値：
* 説明	：デストラクタ
*******************************************************************************/
CResult::~CResult()
{
}

/*******************************************************************************
* 関数名：void CResult::Init( void )
*
* 引数	：
* 戻り値：
* 説明	：初期化処理
*******************************************************************************/
void CResult::Init(void)
{
	CScene2D::Create(TEXTURE_TYPE_RESULT_BG);
}

/*******************************************************************************
* 関数名：void CResult::Uninit( void )
*
* 引数	：
* 戻り値：
* 説明	：終了処理
*******************************************************************************/
void CResult::Uninit(void)
{
	CScene::ReleaseAll();
}

/*******************************************************************************
* 関数名：void CResult::Update( void )
*
* 引数	：
* 戻り値：
* 説明	：更新処理
*******************************************************************************/
void CResult::Update(void)
{
	CScene::UpdateAll();

	if (CInput::GetKeyboardTrigger(DIK_RETURN))
	{
		CFade::Start(new CTitle);
	}
}

/*******************************************************************************
* 関数名：void CResult::Draw( void )
*
* 引数	：
* 戻り値：
* 説明	：描画処理
*******************************************************************************/
void CResult::Draw(void)
{
	CScene::DrawAll();
}