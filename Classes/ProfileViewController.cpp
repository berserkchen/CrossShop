//****************************************
//CrossShop  Demo0.01
//QQ£º896793747
//****************************************
#include "ProfileViewController.h"
#include "AddressListViewController.h"
#include "CNString.h"


void ProfileViewController::loadData(float dt)
{
	ShopDB::Instance()->Profile(this, ShopDB_selector(ProfileViewController::OnComplete), ShopDB::Instance()->getUser().uid, ShopDB::Instance()->getUser().sid);
	//this->getView()->removeAllSubviews();

	//¼ÓÔØ¶¯»­
	m_pIndicatorView = CAActivityIndicatorView::createWithCenter(CADipRect(m_size.width*0.5, m_size.height*0.5,
		m_size.width*0.2, m_size.width*0.2));
	m_pIndicatorView->setStyle(CAActivityIndicatorViewStyleGray);
	this->getView()->addSubview(m_pIndicatorView);
	m_pIndicatorView->startAnimating();
	m_pIndicatorView->setLoadingMinTime(0.5);
	m_pIndicatorView->stopAnimating();
	m_pIndicatorView->setTargetOnCancel(this, callfunc_selector(ProfileViewController::loadFinished));
}

void ProfileViewController::viewDidLoad()
{
	CANavigationBarItem* item = CANavigationBarItem::create(CN_STRING("gerenxinxi"));
	this->setNavigationBarItem(item);
	item->release();

	this->getView()->setColor(MiniColor_bg);

	m_size = this->getView()->getBounds().size;

	m_pScrollView = CAScrollView::createWithFrame(CCRect(0, 0, m_size.width, m_size.height * 2));
	m_pScrollView->setBackGroundColor(MiniColor_bg);
	m_pScrollView->setBounceHorizontal(false);
	m_pScrollView->setShowsHorizontalScrollIndicator(false);
	this->getView()->addSubview(m_pScrollView);

	CAImageView *pBgImg = CAImageView::createWithFrame(CCRect(0, -m_size.width / 2, m_size.width, m_size.width * 680 / 640));
	pBgImg->setImage(CAImage::create("user_bg.png"));
	m_pScrollView->addSubview(pBgImg);

	CAImageView *pUserItem = CAImageView::createWithFrame(CCRect(m_size.width / 10, m_size.width / 5, _px(150), _px(150)));
	pUserItem->setImage(CAImage::create("user_item.png"));
	m_pScrollView->addSubview(pUserItem);

	m_pNameLabel = CALabel::createWithFrame(CCRect(VIEW_RIGHT_X(pUserItem) + _px(20), pUserItem->getFrameOrigin().y + _px(30), _px(200), _px(40)));
	m_pNameLabel->setFontSize(_px(35));
	m_pNameLabel->setColor(CAColor_white);
	m_pScrollView->addSubview(m_pNameLabel);

	m_pNameRank = CALabel::createWithFrame(CCRect(m_pNameLabel->getFrameOrigin().x, VIEW_BOTTOM_Y(m_pNameLabel) + _px(20), _px(200), _px(20)));
	m_pNameRank->setFontSize(_px(20));
	m_pNameRank->setColor(CAColor_white);
	m_pScrollView->addSubview(m_pNameRank);

	CAScale9ImageView *pOrderPlane = UI::whitePlane(CCRect(m_size.width / 2, VIEW_BOTTOM_Y(pBgImg) + _px(70), m_size.width * 38 / 40, _px(100)));
	m_pScrollView->addSubview(pOrderPlane);

	float btnWidth = pOrderPlane->getBounds().size.width*18/20;

	CAButton *pBtn_payment = CAButton::createWithCenter(CCRect(btnWidth / 8+btnWidth/18, pOrderPlane->getBounds().size.height / 2, pOrderPlane->getBounds().size.height / 10 * 9, pOrderPlane->getBounds().size.height / 10 * 9), CAButtonTypeCustom);
	pBtn_payment->setImageForState(CAControlStateAll, CAImage::create("source_material/profile_payment_icon.png"));
	pBtn_payment->setTitleForState(CAControlStateAll, CN_STRING("daifukuan"));
	pOrderPlane->addSubview(pBtn_payment);

	m_pPrompt_payment = InfoPromptView::create(CCPoint(pBtn_payment->getBounds().size.width - _px(15), pBtn_payment->getFrameOrigin().y + _px(10)));
	pBtn_payment->insertSubview(m_pPrompt_payment,100);
	m_pPrompt_payment->setVisible(false);

	CAButton *pBtn_ship = CAButton::createWithCenter(CCRect(btnWidth / 8 * 3 + btnWidth / 18 , pOrderPlane->getBounds().size.height / 2, pOrderPlane->getBounds().size.height / 10 * 9, pOrderPlane->getBounds().size.height / 10 * 9), CAButtonTypeCustom);
	pBtn_ship->setImageForState(CAControlStateAll, CAImage::create("source_material/profileh_ship_icon.png"));
	pBtn_ship->setTitleForState(CAControlStateAll, CN_STRING("daifahuo"));
	pOrderPlane->addSubview(pBtn_ship);

	m_pPrompt_ship = InfoPromptView::create(CCPoint(pBtn_ship->getBounds().size.width - _px(15), pBtn_ship->getFrameOrigin().y + _px(10)));
	m_pPrompt_ship->setText("21");
	pBtn_ship->insertSubview(m_pPrompt_ship, 100);
	m_pPrompt_ship->setVisible(false);

	CAButton *pBtn_receipt = CAButton::createWithCenter(CCRect(btnWidth / 8 * 5 + btnWidth / 18 , pOrderPlane->getBounds().size.height / 2, pOrderPlane->getBounds().size.height / 10 * 9, pOrderPlane->getBounds().size.height / 10 * 9), CAButtonTypeCustom);
	pBtn_receipt->setImageForState(CAControlStateAll, CAImage::create("source_material/profile_receipt_icon.png"));
	pBtn_receipt->setTitleForState(CAControlStateAll, CN_STRING("daishouhuo"));
	pOrderPlane->addSubview(pBtn_receipt);

	m_pPrompt_receipt = InfoPromptView::create(CCPoint(pBtn_receipt->getBounds().size.width - _px(15), pBtn_receipt->getFrameOrigin().y + _px(10)));
	m_pPrompt_receipt->setText("21");
	pBtn_receipt->insertSubview(m_pPrompt_receipt, 100);
	m_pPrompt_receipt->setVisible(false);

	CAButton *pBtn_history = CAButton::createWithCenter(CCRect(btnWidth / 8 * 7 + btnWidth / 18 , pOrderPlane->getBounds().size.height / 2, pOrderPlane->getBounds().size.height / 10 * 9, pOrderPlane->getBounds().size.height / 10 * 9), CAButtonTypeCustom);
	pBtn_history->setImageForState(CAControlStateAll, CAImage::create("source_material/profile_history_icon.png"));
	pBtn_history->setTitleForState(CAControlStateAll, CN_STRING("lishidingdan"));
	pOrderPlane->addSubview(pBtn_history);

	m_pPrompt_history = InfoPromptView::create(CCPoint(pBtn_history->getBounds().size.width - _px(15), pBtn_history->getFrameOrigin().y + _px(10)));
	m_pPrompt_history->setText("21");
	pBtn_history->insertSubview(m_pPrompt_history, 100);
	m_pPrompt_history->setVisible(false);


	CAButton *Btn_address = UI::longButton(CCRect(m_size.width / 2,VIEW_BOTTOM_Y(pOrderPlane) + _px(50), m_size.width * 38 / 40, _px(60)), CN_STRING("shouhuodizhiguanli"));
	Btn_address->addTarget(this, CAControl_selector(ProfileViewController::pushAddressListView), CAControlEventTouchUpInSide);
	m_pScrollView->addSubview(Btn_address);


	if (ShopDB::Instance()->getUser().id == 0 || ShopDB::Instance()->getUser().id == NULL)
	{
		this->sendMsg(LOGIN, this);
	}
	else
	{
		//this->loadData();
	}
}

void ProfileViewController::loadFinished()
{
	if (ShopDB::Instance()->getUser().await_pay != 0)
	{
		m_pPrompt_payment->setText(CCString::createWithFormat("%d", ShopDB::Instance()->getUser().await_pay)->getCString());
		m_pPrompt_payment->setVisible(true);
	}
	else
	{
		m_pPrompt_payment->setVisible(false);
	}

	if (ShopDB::Instance()->getUser().await_ship != 0)
	{
		m_pPrompt_ship->setText(CCString::createWithFormat("%d", ShopDB::Instance()->getUser().await_ship)->getCString());
		m_pPrompt_ship->setVisible(true);
	}
	else
	{
		m_pPrompt_ship->setVisible(false);
	}

	if (ShopDB::Instance()->getUser().shipped != 0)
	{
		m_pPrompt_receipt->setText(CCString::createWithFormat("%d", ShopDB::Instance()->getUser().shipped)->getCString());
		m_pPrompt_receipt->setVisible(true);
	}
	else
	{
		m_pPrompt_receipt->setVisible(false);
	}

	if (ShopDB::Instance()->getUser().finished != 0)
	{
		m_pPrompt_history->setText(CCString::createWithFormat("%d", ShopDB::Instance()->getUser().finished)->getCString());
		m_pPrompt_history->setVisible(true);
	}
	else
	{
		m_pPrompt_history->setVisible(false);
	}

	m_pNameLabel->setText(ShopDB::Instance()->getUser().name);
	m_pNameRank->setText(ShopDB::Instance()->getUser().rank_name);
}
	
	
void ProfileViewController::pushAddressListView(CAControl* sender, CCPoint point)
{
	//AddressListViewController *pAddressListViewController = AddressListViewController::create();
	//CANavigationController *pAddressListNavigationController = new CANavigationController();
	//pAddressListNavigationController->initWithRootViewController(pAddressListViewController);
	//this->presentModalViewController(pAddressListNavigationController, true);
}

void ProfileViewController::viewDidUnload()
{}


void ProfileViewController::OnComplete(void *pData)
{

}

