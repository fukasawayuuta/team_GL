/*******************************************************************************
* タイトル名：
* ファイル名：title.h
* 作成者	：AT13B284 10 小笠原啓太
* 作成日	：2016/11/14
********************************************************************************
* 更新履歴	：
*
*******************************************************************************/
/*******************************************************************************
* インクルードガード
*******************************************************************************/
#pragma once

/*******************************************************************************
* クラス宣言
*******************************************************************************/
// ゲームクラス
class CTitle : public CMode
{
public:
	CTitle();
	~CTitle();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
};

