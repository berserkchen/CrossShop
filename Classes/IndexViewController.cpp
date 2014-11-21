//****************************************
//CrossShop  Demo0.01
//QQ£º896793747
//****************************************
#include "IndexViewController.h"
#include "ProductViewController.h"
#include "CNString.h"
#include "UI.h"

void IndexViewController::loadData(float dt)
{
	ShopDB::Instance()->Category(this, ShopDB_selector(IndexViewController::OnComplete));
	this->getView()->removeAllSubviews();

	CAView *pbgView = CAView::createWithFrame(CCRect(0, 0, m_size.width, m_size.height));
	pbgView->setColor(ccc4(238, 238, 238, 225));
	this->getView()->addSubview(pbgView);

	//¼ÓÔØ¶¯»­
	m_pIndicatorView = CAActivityIndicatorView::createWithCenter(CADipRect(m_size.width*0.5, m_size.height*0.5,
		m_size.width*0.2, m_size.width*0.2));
	m_pIndicatorView->setStyle(CAActivityIndicatorViewStyleGray);
	this->getView()->addSubview(m_pIndicatorView);
	m_pIndicatorView->startAnimating();
	m_pIndicatorView->setLoadingMinTime(0.5);
	m_pIndicatorView->setTargetOnCancel(this, callfunc_selector(IndexViewController::loadFinished));
}

void IndexViewController::viewDidLoad()
{
	CANavigationBarItem* item = CANavigationBarItem::create(CN_STRING("hangbandongtai"));
	this->setNavigationBarItem(item);
	item->release();
	


	m_size = this->getView()->getBounds().size;

	//this->loadData();
}

void IndexViewController::loadFinished()
{
	unsigned int categorysCount = m_vecCategorys.size();

	m_pScrollView = CAScrollView::createWithFrame(CCRect(0, 0, m_size.width, m_size.height));
	//m_pScrollView->setBackGroundColor(MiniColor_bg);
	m_pScrollView->setBounceHorizontal(false);
	m_pScrollView->setShowsHorizontalScrollIndicator(false);
	m_pScrollView->setViewSize(CCSize(m_size.width, 10 + (10 + (m_size.width - 30) / 1.7)*categorysCount));
	this->getView()->addSubview(m_pScrollView);

	for (int i = 0; i < categorysCount; i++)
	{
		ProductShowView *pProductShowView = ProductShowView::create(CCRect(10, 10 + (10 + (m_size.width - 30) / 1.7)*i, m_size.width - 30, (m_size.width - 30) / 1.7));
		pProductShowView->getClassLabel()->setText(m_vecCategorys[i].name);
		

		if (m_vecCategorys[i].goods.size()>0)
		{
			pProductShowView->getClassImg()->setImage(CAImage::create(m_vecCategorys[i].goods[0].img_thumb));
			pProductShowView->getLabel1()->setText(m_vecCategorys[i].goods[0].name);
			pProductShowView->getImg1()->setImage(CAImage::create(m_vecCategorys[i].goods[0].img_thumb));
			pProductShowView->getLabel1_price()->setText(m_vecCategorys[i].goods[0].shop_price);

			pProductShowView->getBtn1()->setUserData(&m_vecCategorys[i].goods[0].id);
			pProductShowView->getBtn1()->addTarget(this, CAControl_selector(IndexViewController::pushProductView), CAControlEventTouchUpInSide);
			//this->
		}

		if (m_vecCategorys[i].goods.size() > 1)
		{
			pProductShowView->getLabel2()->setText(m_vecCategorys[i].goods[1].name);
			pProductShowView->getImg2()->setImage(CAImage::create(m_vecCategorys[i].goods[1].img_thumb));
			pProductShowView->getLabel2_price()->setText(m_vecCategorys[i].goods[1].shop_price);

			pProductShowView->getBtn2()->setUserData(&m_vecCategorys[i].goods[1].id);
			pProductShowView->getBtn2()->addTarget(this, CAControl_selector(IndexViewController::pushProductView), CAControlEventTouchUpInSide);
		}

		m_pScrollView->addSubview(pProductShowView);
	}


}
	
	
void IndexViewController::pushProductView(CAControl* sender, CCPoint point)
{
	//µ±Î´µÇÂ¼Ê±£¬µ¯³öµÇÂ¼¿ò
	if (ShopDB::Instance()->getUser().id == 0 || ShopDB::Instance()->getUser().id == NULL)
	{
		this->sendMsg(LOGIN, this);
	}
	else
	{
		ProductViewController *pProductViewController = ProductViewController::create();
		pProductViewController->setId(*(unsigned int*)(sender->getUserData()));
		pProductViewController->setReceiver(m_pReceiver);
		CANavigationController *pProductNavigationController = new CANavigationController();
		pProductNavigationController->initWithRootViewController(pProductViewController);
		this->presentModalViewController(pProductNavigationController, true);
	}

}

void IndexViewController::viewDidUnload()
{}


void IndexViewController::OnComplete(void *pData)
{
	m_vecCategorys = (*(CategoryData*)pData).m_categorys;

	CCLog("******************CategoryData******************");
	for (int i = 0; i < m_vecCategorys.size(); i++)
	{
		CCLog("******************data%d******************", i);
		CCLog("id=%d", m_vecCategorys[i].id);
		CCLog("name=%s", m_vecCategorys[i].name.c_str());

		for (int j = 0; j < m_vecCategorys[i].goods.size(); j++)
		{
			CCLog("******************goods%d******************", j);
			CCLog("goods:id=%d", m_vecCategorys[i].goods[j].id);
			CCLog("goods:name=%s", m_vecCategorys[i].goods[j].name.c_str());
			CCLog("goods:market_price=%s", m_vecCategorys[i].goods[j].market_price.c_str());
			CCLog("goods:shop_price=%s", m_vecCategorys[i].goods[j].shop_price.c_str());
			CCLog("goods:promote_price=%s", m_vecCategorys[i].goods[j].promote_price.c_str());
			CCLog("goods:brief=%s", m_vecCategorys[i].goods[j].brief.c_str());
			CCLog("goods:img:thumb=%s", m_vecCategorys[i].goods[j].img_thumb.c_str());
			CCLog("goods:img:url=%s", m_vecCategorys[i].goods[j].img_url.c_str());
			CCLog("goods:img:small=%s", m_vecCategorys[i].goods[j].img_small.c_str());
		}
	}
	if (m_vecCategorys.empty())
	{
		CAScheduler::schedule(schedule_selector(IndexViewController::loadData), this, 0.5);
	}
	else
	{
		m_pIndicatorView->stopAnimating();
	}
}

