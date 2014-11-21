//****************************************
//CrossShop  Demo0.01
//QQ£º896793747
//****************************************
#include "CartListViewController.h"
#include "ProductViewController.h"
#include "CNString.h"
#include "UI.h"

void CartListViewController::loadData(float dt)
{
	ShopDB::Instance()->CartList(this, ShopDB_selector(CartListViewController::OnComplete), ShopDB::Instance()->getUser().uid, ShopDB::Instance()->getUser().sid);

	CAView *pbgView = CAView::createWithFrame(CCRect(0, 0, m_size.width, m_size.height));
	pbgView->setColor(MiniColor_bg);
	this->getView()->addSubview(pbgView);

	//¼ÓÔØ¶¯»­
	m_pIndicatorView = CAActivityIndicatorView::createWithCenter(CADipRect(m_size.width*0.5, m_size.height*0.5,
		m_size.width*0.2, m_size.width*0.2));
	m_pIndicatorView->setStyle(CAActivityIndicatorViewStyleGray);
	this->getView()->addSubview(m_pIndicatorView);
	m_pIndicatorView->startAnimating();
	m_pIndicatorView->setLoadingMinTime(0.5);
	m_pIndicatorView->setTargetOnCancel(this, callfunc_selector(CartListViewController::loadFinished));
}

void CartListViewController::viewDidLoad()
{
	CANavigationBarItem* item = CANavigationBarItem::create(CN_STRING("fuwuwangdian"));
	this->setNavigationBarItem(item);
	item->release();


	m_size = this->getView()->getBounds().size;
	if (ShopDB::Instance()->getUser().id == 0 || ShopDB::Instance()->getUser().id == NULL)
	{
		this->sendMsg(LOGIN, this);
	}
	else
	{
		//this->loadData();
	}
}

void CartListViewController::loadFinished()
{

}
	
	
void CartListViewController::pushProductView(CAControl* sender, CCPoint point)
{
	ProductViewController *pProductViewController = ProductViewController::create();
	pProductViewController->setId(*(unsigned int*)(sender->getUserData()));
	pProductViewController->setReceiver(m_pReceiver);
	CANavigationController *pProductNavigationController = new CANavigationController();
	pProductNavigationController->initWithRootViewController(pProductViewController);
	this->presentModalViewController(pProductNavigationController, true);

}

void CartListViewController::viewDidUnload()
{}


void CartListViewController::OnComplete(void *pData)
{
	m_vecCartGoods = (*(CardListData*)pData).getGoodLists();

	m_pIndicatorView->stopAnimating();


	CALabel *pLabel = CALabel::createWithCenter(CCRect(m_size.width / 2, m_size.height / 2, _px(500), _px(40)));
	pLabel->setTextAlignment(CATextAlignmentCenter);
	pLabel->setText(CN_STRING("gouwucheshikongde"));
	pLabel->setFontSize(_px(40));
	pLabel->setColor(MiniColor_font1);
	this->getView()->addSubview(pLabel);

}

