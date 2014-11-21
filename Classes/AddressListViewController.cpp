//****************************************
//CrossShop  Demo0.01
//QQ：896793747
//****************************************
#include "AddressListViewController.h"
#include "CNString.h"
#include "UI.h"

void AddressListViewController::viewDidLoad()
{
	CANavigationBarItem* item = CANavigationBarItem::create(CN_STRING("shouhuodizhiguanli"));
	this->setNavigationBarItem(item);

	ShopDB::Instance()->AddressList(this, ShopDB_selector(AddressListViewController::OnComplete), ShopDB::Instance()->getUser().uid, ShopDB::Instance()->getUser().sid);


	CCSize size = this->getView()->getBounds().size;

	CATableView *pTableView = CATableView::createWithFrame(CADipRect(0, 0, size.width, size.height));
	pTableView->setTableViewDelegate(this);
	pTableView->setTableViewDataSource(this);
	pTableView->setBackGroundColor(CAColor_clear);
	this->getView()->addSubview(pTableView);
}

void AddressListViewController::viewDidUnload()
{}

//获取对应的section所包含的cell个数
unsigned int AddressListViewController::numberOfRowsInSection(CATableView *table, unsigned int section)
{
	return m_vecAddressList.size();
}
//获取指定cell(当前m_pTableView,cell所属的区域,cell所在行数)
CATableViewCell* AddressListViewController::tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row)
{
	CATableViewCell *pCell = (CATableViewCell*)table->dequeueReusableCellWithIdentifier("CrossShop");
	if (pCell==NULL)
	{
		pCell = CATableViewCell::create("CrossShop");
		pCell->setBackgroundView(NULL);

		CALabel *pLabel_name = CALabel::createWithCenter(CCRect(cellSize.width / 3/2, cellSize.height / 2, cellSize.width / 3, 25));
		pLabel_name->setTextAlignment(CATextAlignmentRight);
		pLabel_name->setFontSize(25);
		pLabel_name->setText(m_vecAddressList[row].address);
		pCell->addSubview(pLabel_name);


		CALabel *pLabel_text = CALabel::createWithCenter(CCRect(cellSize.width / 3+cellSize.width * 2 / 3 / 2+50, cellSize.height / 2, cellSize.width * 2 / 3, 25));
		pLabel_text->setTextAlignment(CATextAlignmentLeft);
		pLabel_text->setFontSize(25);
		pLabel_text->setText(m_vecAddressList[row].country_name);
		pCell->addSubview(pLabel_text);


	}
	return pCell;
}
//获取tableview包含的section个数
unsigned int AddressListViewController::numberOfSections(CATableView *table)
{
	return 1;
}


//获取指定的cell高度(当前m_pTableView、cell所属的区域、cell所在行数)
unsigned int AddressListViewController::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
	return 100;
}

void AddressListViewController::OnComplete(void *pData)
{

}