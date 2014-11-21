//****************************************
//CrossShop  Demo0.01
//QQ：896793747
//****************************************
#ifndef __CrossShop__IndexViewController__
#define __CrossShop__IndexViewController__

#include <iostream>
#include "CrossApp.h"
#include "ShopDB.h"
#include "MessageController.h"

USING_NS_CC;

class IndexViewController : public CAViewController, CAScrollViewDelegate, public Sender
{

public:
	CREATE_FUNC(IndexViewController);

protected:

	void viewDidLoad();
	void viewDidUnload();

	void loadData(float dt=0);
	void loadFinished();

	void pushProductView(CAControl* sender, CCPoint point);

private:
	//数据相关
	std::vector<CATEGORY> m_vecCategorys;

	CADipSize m_size;
	CAScrollView* m_pScrollView;

	void OnComplete(void *pData);

	CAImageView *m_pImg;
	//loading动画
	CAActivityIndicatorView* m_pIndicatorView;
};


#endif /* defined(__CrossShop__IndexViewController__) */