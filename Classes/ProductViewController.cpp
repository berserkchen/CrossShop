//****************************************
//CrossShop  Demo0.01
//QQ：896793747
//****************************************
#include "ProductViewController.h"
#include "ProductParamViewController.h"
#include "ProductCommentViewController.h"
#include "CNString.h"
#include "UI.h"

void ProductViewController::loadData(float dt)
{
	ShopDB::Instance()->Goods(this, ShopDB_selector(ProductViewController::OnComplete), m_id, ShopDB::Instance()->getUser().id, ShopDB::Instance()->getUser().sid);
	this->getView()->removeAllSubviews();

	//加载动画
	m_pIndicatorView = CAActivityIndicatorView::createWithCenter(CADipRect(m_size.width*0.5, m_size.height*0.5,
		m_size.width*0.2, m_size.width*0.2));
	m_pIndicatorView->setStyle(CAActivityIndicatorViewStyleGray);
	this->getView()->addSubview(m_pIndicatorView);
	m_pIndicatorView->startAnimating();
	m_pIndicatorView->setLoadingMinTime(0.5);
	m_pIndicatorView->setTargetOnCancel(this, callfunc_selector(ProductViewController::loadFinished));
}


void ProductViewController::viewDidLoad()
{
	//CCLog("++++++++++++++++%s",m_goodData.name.c_str());
	CANavigationBarItem* item = CANavigationBarItem::create(CN_STRING("shangpingxiangqing"));
	CABarButtonItem *leftButtonItem = CABarButtonItem::create("", CAImage::create("source_material/btn_left_white.png"), CAImage::create("source_material/btn_left_white.png"));
	leftButtonItem->setTarget(this, CAControl_selector(ProductViewController::BtnLeftSelection));
	item->getLeftButtonItems()->removeAllObjects();
	item->addLeftButtonItem(leftButtonItem);
	this->setNavigationBarItem(item);

	m_size = this->getView()->getBounds().size;




	this->loadData();
}

void ProductViewController::loadFinished()
{

	//----------------------1级views---------------------//
	CAScrollView *pScrollView = CAScrollView::createWithFrame(CCRect(0, 0, m_size.width, m_size.height));
	pScrollView->setBounceHorizontal(false);
	//pScrollView->setBounceVertical(false);
	//pScrollView->setViewSize(CCSize(m_size.width, m_size.height * 1.2));
	pScrollView->setBackGroundColor(MiniColor_bg);
	pScrollView->setShowsHorizontalScrollIndicator(false);
	pScrollView->setShowsVerticalScrollIndicator(false);
	this->getView()->addSubview(pScrollView);

	CAImageView *pFooterView = CAImageView::createWithFrame(CCRect(0, m_size.height - 80, m_size.width, 80));
	pFooterView->setImage(CAImage::create("source_material/btn_square_disabled.png"));
	pFooterView->setAlpha(0.7);
	this->getView()->insertSubview(pFooterView, 1);



	//----------------------2级views---------------------//
	CAView *pView_title = CAView::createWithFrame(CCRect(m_size.width * 1 / 40, 0, m_size.width * 38 / 40, 100));
	pView_title->setColor(MiniColor_bg);
	pScrollView->addSubview(pView_title);

	CAView *pView_img = CAView::createWithFrame(CCRect(m_size.width * 1 / 40, 100, m_size.width * 38 / 40, 230));
	pView_img->setColor(MiniColor_bg);
	pScrollView->addSubview(pView_img);

	CAView *pView_infor = CAView::createWithFrame(CCRect(m_size.width * 1 / 40, 330, m_size.width * 38 / 40, 190));
	pView_infor->setColor(MiniColor_bg);
	pScrollView->addSubview(pView_infor);

	CAView *pView_list = CAView::createWithFrame(CCRect(m_size.width * 1 / 40, 520, m_size.width * 38 / 40, 200));
	pView_list->setColor(MiniColor_bg);
	pScrollView->addSubview(pView_list);

	//----------------------3级views---------------------//
	/*pView_title*/
	CALabel *pLabel_name = CALabel::createWithFrame(CCRect(0, 20, pView_title->getBounds().size.width, 30));
	pLabel_name->setText(m_goodData.name);
	pLabel_name->setFontSize(30);
	pView_title->addSubview(pLabel_name);

	CALabel *pLabel_price = CALabel::createWithFrame(CCRect(0, 50 + 5, pView_title->getBounds().size.width, 30));
	pLabel_price->setText(m_goodData.shop_price);
	pLabel_price->setFontSize(30);
	pLabel_price->setColor(CAColor_red);
	pView_title->addSubview(pLabel_price);

	/*pView_img*/
	if (m_goodData.pictures.size() > 0)
	{
		CAScale9ImageView *pPlane_Image1 = CAScale9ImageView::createWithFrame(CCRect(0, _px(10), _px(200), _px(200)));
		pPlane_Image1->setImage(CAImage::create("source_material/item_box_bg.png"));
		pView_img->addSubview(pPlane_Image1);

		CAImageView *pImage1 = CAImageView::createWithCenter(CCRect(pPlane_Image1->getBounds().size.width / 2, pPlane_Image1->getBounds().size.height / 2, _px(180), _px(180)));
		pImage1->setImage(CAImage::create(m_goodData.pictures[0].c_str()));
		pPlane_Image1->addSubview(pImage1);
	}
	if (m_goodData.pictures.size() > 1)
	{
		CAScale9ImageView *pPlane_Image2 = CAScale9ImageView::createWithFrame(CCRect(_px(210), _px(10), _px(200), _px(200)));
		pPlane_Image2->setImage(CAImage::create("source_material/item_box_bg.png"));
		pView_img->addSubview(pPlane_Image2);

		CAImageView *pImage2 = CAImageView::createWithCenter(CCRect(pPlane_Image2->getBounds().size.width / 2, pPlane_Image2->getBounds().size.height / 2, _px(180), _px(180)));
		pImage2->setImage(CAImage::create(m_goodData.pictures[1].c_str()));
		pPlane_Image2->addSubview(pImage2);
	}


	/*pView_infor*/
	CALabel *pLabel_infor1 = CALabel::createWithFrame(CCRect(0, 0, pView_infor->getBounds().size.width, 20));
	pLabel_infor1->setText(CCString::createWithFormat("%s:%d", CN_STRING("kucun").c_str(), m_goodData.goods_number)->getCString());
	pLabel_infor1->setColor(MiniColor_font2);
	pLabel_infor1->setFontSize(20);
	pView_infor->addSubview(pLabel_infor1);

	CALabel *pLabel_infor2 = CALabel::createWithFrame(CCRect(0, 30, pView_infor->getBounds().size.width, 20));
	pLabel_infor2->setText(CCString::createWithFormat("%s:%s", CN_STRING("shangdianjiage").c_str(), m_goodData.shop_price.c_str())->getCString());
	pLabel_infor2->setColor(MiniColor_font2);
	pLabel_infor2->setFontSize(20);
	pView_infor->addSubview(pLabel_infor2);

	CALabel *pLabel_infor3 = CALabel::createWithFrame(CCRect(0, 60, pView_infor->getBounds().size.width, 20));
	pLabel_infor3->setText(CCString::createWithFormat("%s:%s", CN_STRING("shangdianjiage").c_str(), m_goodData.market_price.c_str())->getCString());
	pLabel_infor3->setColor(MiniColor_font2);
	pLabel_infor3->setFontSize(20);
	pView_infor->addSubview(pLabel_infor3);

	for (int i = 0; i < m_goodData.rank_prices.size(); i++)
	{
		CALabel *pLabel_rank = CALabel::createWithFrame(CCRect(0, 90 + i*30, pView_infor->getBounds().size.width, 20));
		pLabel_rank->setText(CCString::createWithFormat("%s:%s", m_goodData.rank_prices[i].rank_name.c_str(), m_goodData.rank_prices[i].price.c_str())->getCString());
		pLabel_rank->setColor(MiniColor_font2);
		pLabel_rank->setFontSize(20);
		pView_infor->addSubview(pLabel_rank);
	}


	/*pView_list*/
	CAButton *pBth_list1 = UI::longButton(CCRect(pView_list->getBounds().size.width/2, 0, pView_list->getBounds().size.width, 60), CN_STRING("shuliang") + ":1");
	pView_list->addSubview(pBth_list1);

	CAButton *pBth_list2 = UI::longButton(CCRect(pView_list->getBounds().size.width/2, 70, pView_list->getBounds().size.width, 60), CN_STRING("jibencanshu"));
	pBth_list2->addTarget(this, CAControl_selector(ProductViewController::pushParamView), CAControlEventTouchUpInSide);
	pView_list->addSubview(pBth_list2);

	CAButton *pBth_list3 = UI::longButton(CCRect(pView_list->getBounds().size.width/2, 140, pView_list->getBounds().size.width, 60), CN_STRING("shangpinpinglun"));
	pBth_list3->addTarget(this, CAControl_selector(ProductViewController::pushCommentView), CAControlEventTouchUpInSide);
	pView_list->addSubview(pBth_list3);

	//----------------------pFooterView---------------------//
	CAButton *pBth_buy = UI::blueButton(CCRect(m_size.width / 2 - 100, pFooterView->getBounds().size.height / 2, 150, 60), CN_STRING("lijigoumai"));
	pFooterView->addSubview(pBth_buy);

	CAButton *pBth_putToBuyCar = UI::blueButton(CCRect(m_size.width / 2 + 100, pFooterView->getBounds().size.height / 2, 150, 60), CN_STRING("jiarugouwuche"));
	pFooterView->addSubview(pBth_putToBuyCar);
}

void ProductViewController::viewDidUnload()
{}

void ProductViewController::BtnLeftSelection(CAControl* sender, CCPoint point)
{
	this->dismissModalViewController(true);
}

void ProductViewController::pushParamView(CAControl* sender, CCPoint point)
{
	ProductParamViewController *pProductParamViewController = ProductParamViewController::create();
	pProductParamViewController->setGoodProperties(m_goodData.properties);
	this->getNavigationController()->pushViewController(pProductParamViewController, true);
}

void ProductViewController::pushCommentView(CAControl* sender, CCPoint point)
{
	ProductCommentViewController *pProductParamViewController = ProductCommentViewController::create();
	this->getNavigationController()->pushViewController(pProductParamViewController, true);

}


void ProductViewController::OnComplete(void *pData)
{
	m_goodData = (*(GoodData*)pData).m_good;
	STATUS status = (*(GoodData*)pData).getStatus();
	
	if (m_goodData.name.empty())
	{
		CAScheduler::schedule(schedule_selector(ProductViewController::loadData), this, 0.5);
	}
	else
	{
		m_pIndicatorView->stopAnimating();
		if (status.succeed == 0)
		{
			CAAlertView *pAlertView = CAAlertView::createWithText(CN_STRING("zhucheshibai").c_str(), status.error_desc.c_str(), CN_STRING("queding").c_str(), NULL);
			pAlertView->show();
			pAlertView->setTarget(this, CAAlertView_selector(ProductViewController::alertViewCallback));
		}
	}
}

void ProductViewController::alertViewCallback(int btnIndex)
{
	this->dismissModalViewController(true);
}