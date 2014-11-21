//****************************************
//CrossShop  Demo0.01
//QQ：896793747
//****************************************
#ifndef __CrossShop__ProductParamViewController__
#define __CrossShop__ProductParamViewController__

#include <iostream>
#include "CrossApp.h"
#include "ShopDB.h"

USING_NS_CC;

class ProductParamViewController : public CAViewController, public CATableViewDataSource, public CATableViewDelegate
{

public:
	CREATE_FUNC(ProductParamViewController);

	CC_SYNTHESIZE(std::vector<GOOD_PROPERTIE>, m_vecCoodProperties, GoodProperties);

	////定义分接口，由子类实现，选中cell时触发。
	//virtual void tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
	////定义分接口，由子类实现，取消选择时触发。
	//virtual void tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
	//获取对应的section所包含的cell个数
	virtual unsigned int numberOfRowsInSection(CATableView *table, unsigned int section);
	////获取指定cell(当前m_pTableView,cell所属的区域,cell所在行数)
	virtual CATableViewCell* tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row);
	//获取tableview包含的section个数
	virtual unsigned int numberOfSections(CATableView *table);
	//获取指定的cell高度(当前m_pTableView、cell所属的区域、cell所在行数)
	virtual unsigned int tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);


protected:

	void viewDidLoad();

	void viewDidUnload();

};


#endif /* defined(__CrossShop__ProductParamViewController__) */