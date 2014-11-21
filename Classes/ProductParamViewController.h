//****************************************
//CrossShop  Demo0.01
//QQ��896793747
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

	////����ֽӿڣ�������ʵ�֣�ѡ��cellʱ������
	//virtual void tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
	////����ֽӿڣ�������ʵ�֣�ȡ��ѡ��ʱ������
	//virtual void tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);
	//��ȡ��Ӧ��section��������cell����
	virtual unsigned int numberOfRowsInSection(CATableView *table, unsigned int section);
	////��ȡָ��cell(��ǰm_pTableView,cell����������,cell��������)
	virtual CATableViewCell* tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row);
	//��ȡtableview������section����
	virtual unsigned int numberOfSections(CATableView *table);
	//��ȡָ����cell�߶�(��ǰm_pTableView��cell����������cell��������)
	virtual unsigned int tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row);


protected:

	void viewDidLoad();

	void viewDidUnload();

};


#endif /* defined(__CrossShop__ProductParamViewController__) */