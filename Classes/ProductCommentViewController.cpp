//****************************************
//CrossShop  Demo0.01
//QQ£º896793747
//****************************************
#include "ProductCommentViewController.h"
#include "CNString.h"
#include "UI.h"

void ProductCommentViewController::viewDidLoad()
{
	CANavigationBarItem* item = CANavigationBarItem::create(CN_STRING("shangpinpinglun"));
	this->setNavigationBarItem(item);

	CCSize size = this->getView()->getBounds().size;
	CALabel *pLabel = CALabel::createWithCenter(CCRect(size.width / 2, size.height / 2, _px(500), _px(40)));
	pLabel->setTextAlignment(CATextAlignmentCenter);
	pLabel->setText(CN_STRING("haimeiyouliuyanyo"));
	pLabel->setFontSize(_px(40));
	pLabel->setColor(MiniColor_font1);
	this->getView()->addSubview(pLabel);
}

void ProductCommentViewController::viewDidUnload()
{
}