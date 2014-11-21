//****************************************
//CrossShop  Demo0.01
//QQ£º896793747
//****************************************
#ifndef __CrossShop__ProductViewController__
#define __CrossShop__ProductViewController__

#include <iostream>
#include "CrossApp.h"
#include "ShopDB.h"
#include "MessageController.h"

USING_NS_CC;

class ProductViewController : public CAViewController, public CAScrollViewDelegate, public Sender
{

public:
	CREATE_FUNC(ProductViewController);

	CC_SYNTHESIZE(unsigned int, m_id, Id);

protected:
	void viewDidLoad();
	void viewDidUnload();

	void loadData(float dt = 0);
	void loadFinished();

private:
	CADipSize m_size;
	GOOD m_goodData;

	void BtnLeftSelection(CAControl* sender, CCPoint point);
	void pushParamView(CAControl* sender, CCPoint point);
	void pushCommentView(CAControl* sender, CCPoint point);
	void alertViewCallback(int btnIndex);

	void OnComplete(void *pData);

	//loading¶¯»­
	CAActivityIndicatorView* m_pIndicatorView;

};


#endif /* defined(__CrossShop__ProductViewController__) */