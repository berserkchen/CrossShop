//****************************************
//CrossShop  Demo0.01
//QQ：896793747
//****************************************
#ifndef __CrossShop__CartListViewController__
#define __CrossShop__CartListViewController__

#include <iostream>
#include "CrossApp.h"
#include "ShopDB.h"
#include "MessageController.h"

USING_NS_CC;

class CartListViewController : public CAViewController, CAScrollViewDelegate, public Sender
{

public:
	CREATE_FUNC(CartListViewController);
	void loadData(float dt = 0);

protected:

	void viewDidLoad();
	void viewDidUnload();

	void loadFinished();

	void pushProductView(CAControl* sender, CCPoint point);

private:
	//数据相关
	std::vector<CART_GOOD> m_vecCartGoods;
	CART_TOTAL m_cartTotal;

	CADipSize m_size;
	CAScrollView* m_pScrollView;

	void OnComplete(void *pData);

	CAImageView *m_pImg;
	//loading动画
	CAActivityIndicatorView* m_pIndicatorView;
};


#endif /* defined(__CrossShop__CartListViewController__) */