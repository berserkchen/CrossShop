//****************************************
//CrossShop  Demo0.01
//QQ：896793747
//****************************************
#ifndef __CrossShop__ProfileViewController__
#define __CrossShop__ProfileViewController__

#include <iostream>
#include "CrossApp.h"
#include "ShopDB.h"
#include "UI.h"
#include "MessageController.h"

USING_NS_CC;

class ProfileViewController: public CAViewController, public Sender
{

public:
	CREATE_FUNC(ProfileViewController);
	void loadData(float dt = 0);

protected:

	void viewDidLoad();
	void viewDidUnload();
	void loadFinished();

	void pushAddressListView(CAControl* sender, CCPoint point);

private:
	////数据相关
	//std::vector<CATEGORY> m_vecCategorys;

	CADipSize m_size;
	CAScrollView* m_pScrollView;
	CALabel *m_pNameLabel;
	CALabel *m_pNameRank;
	InfoPromptView *m_pPrompt_payment;
	InfoPromptView *m_pPrompt_ship;
	InfoPromptView *m_pPrompt_receipt;
	InfoPromptView *m_pPrompt_history;


	void OnComplete(void *pData);
	//loading动画
	CAActivityIndicatorView* m_pIndicatorView;
};


#endif /* defined(__CrossShop__ProfileViewController__) */