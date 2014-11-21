//****************************************
//CrossShop  Demo0.01
//QQ：896793747
//****************************************
#ifndef __CrossShop__SearchViewController__
#define __CrossShop__SearchViewController__

#include <iostream>
#include "CrossApp.h"
#include "ShopDB.h"
#include "MessageController.h"

USING_NS_CC;

class SearchViewController :public CAViewController, CACollectionViewDelegate, CACollectionViewDataSource, CAScrollViewDelegate, public Sender
{

public:
	CREATE_FUNC(SearchViewController);

	CC_SYNTHESIZE(unsigned int, m_categoryId, CategoryId);
	CC_SYNTHESIZE(std::string, m_keywords, Keywords);

protected:
	SearchViewController();

	void viewDidLoad();
	void viewDidUnload();

	void loadData(float dt = 0);
	void loadFinished();

private:
	CADipSize m_size;
	std::vector<GOOD> m_vecGoods;
	std::vector<GOOD> m_vecVisibleGoods;

	void OnComplete(void *pData);

	//loading动画
	CAActivityIndicatorView* m_pIndicatorView;

	virtual void collectionViewDidSelectCellAtIndexPath(CACollectionView *collectionView, unsigned int section, unsigned int row, unsigned int item);
	virtual void collectionViewDidDeselectCellAtIndexPath(CACollectionView *collectionView, unsigned int section, unsigned int row, unsigned int item);

	virtual CACollectionViewCell* collectionCellAtIndex(CACollectionView *collectionView, const CCSize& cellSize, unsigned int section, unsigned int row, unsigned int item);
	virtual unsigned int numberOfSections(CACollectionView *collectionView);
	virtual unsigned int numberOfRowsInSection(CACollectionView *collectionView, unsigned int section);
	virtual unsigned int numberOfItemsInRowsInSection(CACollectionView *collectionView, unsigned int section, unsigned int row);
	virtual unsigned int collectionViewHeightForRowAtIndexPath(CACollectionView* collectionView, unsigned int section, unsigned int row);

	virtual void scrollViewFooterBeginRefreshing(CAScrollView* view);

	void refreshData(float interval);
	void clickSearchBtn(CAControl* sender, CCPoint point);

	//相关控件
	CACollectionView* m_pConllectionView;
	CAPullToRefreshView* m_pFooterRefreshView;
	CAView *m_pSearchView;
	CATextField *m_pSearchField;
};


#endif /* defined(__CrossShop__SearchViewController__) */