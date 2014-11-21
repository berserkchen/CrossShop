//****************************************
//CrossShop  Demo0.01
//QQ��896793747
//****************************************
#include "ProductParamViewController.h"
#include "CNString.h"
#include "UI.h"

void ProductParamViewController::viewDidLoad()
{
	CANavigationBarItem* item = CANavigationBarItem::create(CN_STRING("jibencanshu"));
	this->setNavigationBarItem(item);


	CCSize size = this->getView()->getBounds().size;

	CATableView *pTableView = CATableView::createWithFrame(CADipRect(0, 0, size.width, size.height));
	pTableView->setTableViewDelegate(this);
	pTableView->setTableViewDataSource(this);
	pTableView->setBackGroundColor(CAColor_clear);
	this->getView()->addSubview(pTableView);
	
	if (m_vecCoodProperties.size() <= 0)
	{
		CALabel *pLabel = CALabel::createWithCenter(CCRect(size.width / 2, size.height / 2, _px(500), _px(40)));
		pLabel->setTextAlignment(CATextAlignmentCenter);
		pLabel->setText(CN_STRING("gaishangpingweishechanshu"));
		pLabel->setFontSize(_px(40));
		pLabel->setColor(MiniColor_font1);
		this->getView()->addSubview(pLabel);
	}
}

void ProductParamViewController::viewDidUnload()
{}

//��ȡ��Ӧ��section��������cell����
unsigned int ProductParamViewController::numberOfRowsInSection(CATableView *table, unsigned int section)
{
	return m_vecCoodProperties.size();
}
//��ȡָ��cell(��ǰm_pTableView,cell����������,cell��������)
CATableViewCell* ProductParamViewController::tableCellAtIndex(CATableView* table, const CCSize& cellSize, unsigned int section, unsigned int row)
{
	CATableViewCell *pCell = (CATableViewCell*)table->dequeueReusableCellWithIdentifier("MiniShop");
	if (pCell==NULL)
	{
		pCell = CATableViewCell::create("MiniShop");
		pCell->setBackgroundView(NULL);

		CALabel *pLabel_name = CALabel::createWithCenter(CCRect(cellSize.width / 3/2, cellSize.height / 2, cellSize.width / 3, 25));
		pLabel_name->setTextAlignment(CATextAlignmentRight);
		pLabel_name->setFontSize(25);
		pLabel_name->setColor(MiniColor_font1);
		pLabel_name->setText(m_vecCoodProperties[row].name);
		pCell->addSubview(pLabel_name);


		CALabel *pLabel_text = CALabel::createWithCenter(CCRect(cellSize.width / 3+cellSize.width * 2 / 3 / 2+50, cellSize.height / 2, cellSize.width * 2 / 3, 25));
		pLabel_text->setTextAlignment(CATextAlignmentLeft);
		pLabel_text->setFontSize(25);
		pLabel_text->setColor(MiniColor_font1);
		pLabel_text->setText(m_vecCoodProperties[row].value);
		pCell->addSubview(pLabel_text);


	}
	return pCell;
}
//��ȡtableview������section����
unsigned int ProductParamViewController::numberOfSections(CATableView *table)
{
	return 1;
}


//��ȡָ����cell�߶�(��ǰm_pTableView��cell����������cell��������)
unsigned int ProductParamViewController::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
	return 100;
}
