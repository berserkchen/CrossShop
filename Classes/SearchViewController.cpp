//****************************************
//CrossShop  Demo0.01
//QQ£º896793747
//****************************************
#include "SearchViewController.h"
#include "ProductViewController.h"
#include "CNString.h"
#include "UI.h"

SearchViewController::SearchViewController()
{
	m_categoryId = 0;
	m_keywords = "";
	m_vecVisibleGoods.clear();
	m_vecGoods.clear();
}

void SearchViewController::loadData(float dt)
{
	ShopDB::Instance()->Search(this, ShopDB_selector(SearchViewController::OnComplete), m_keywords, m_categoryId, "price_asc");

	//¼ÓÔØ¶¯»­
	m_pIndicatorView = CAActivityIndicatorView::createWithCenter(CADipRect(m_size.width*0.5, m_size.height*0.5,
		m_size.width*0.2, m_size.width*0.2));
	m_pIndicatorView->setStyle(CAActivityIndicatorViewStyleGray);
	this->getView()->addSubview(m_pIndicatorView);
	m_pIndicatorView->startAnimating();
	m_pIndicatorView->setTargetOnCancel(this, callfunc_selector(SearchViewController::loadFinished));

}


void SearchViewController::viewDidLoad()
{
	m_size = this->getView()->getBounds().size;

	m_pSearchView = CAView::createWithFrame(CCRect(0, 0, m_size.width, m_size.height / 9));
	m_pSearchView->setColor(ccc4(51, 204, 255, 255));
	this->getView()->addSubview(m_pSearchView);


	m_pSearchField = CATextField::createWithCenter(CCRect(m_size.width*3 / 7, m_pSearchView->getBounds().size.height / 2, m_size.width*2/3, _px(60)));
	m_pSearchField->setPlaceHolder(CN_STRING("yundanhao"));
	m_pSearchView->addSubview(m_pSearchField);

	CAButton *pSearchBtn = CAButton::createWithFrame(CCRect(m_size.width - m_pSearchField->getFrameOrigin().x-_px(70), m_pSearchField->getFrameOrigin().y, _px(70), _px(10)), CAButtonTypeRoundedRect);
	pSearchBtn->setTitleForState(CAControlStateAll, CN_STRING("suosuo"));
	pSearchBtn->addTarget(this, CAControl_selector(SearchViewController::clickSearchBtn), CAControlEventTouchUpInSide);
	m_pSearchView->addSubview(pSearchBtn);


	m_pFooterRefreshView = CAPullToRefreshView::create(CAPullToRefreshView::CAPullToRefreshTypeFooter);

	m_pConllectionView = CACollectionView::createWithFrame(CCRect(0, m_pSearchView->getBounds().size.height, m_size.width, m_size.height / 9 * 8));
	m_pConllectionView->setBackGroundColor(MiniColor_bg);
	m_pConllectionView->setAllowsSelection(true);
	m_pConllectionView->setAllowsMultipleSelection(true);
	m_pConllectionView->setCollectionViewDelegate(this);
	m_pConllectionView->setCollectionViewDataSource(this);
	m_pConllectionView->setScrollViewDelegate(this);
	m_pConllectionView->setFooterRefreshView(m_pFooterRefreshView);
	m_pConllectionView->setHoriInterval(_px(20));
	m_pConllectionView->setVertInterval(_px(20));
	this->getView()->addSubview(m_pConllectionView);

	//this->loadData();
}

void SearchViewController::loadFinished()
{
	m_pConllectionView->reloadData();
}

void SearchViewController::viewDidUnload()
{}


void SearchViewController::OnComplete(void *pData)
{
	m_vecGoods = (*(SearchData*)pData).getGoods();
	if (m_vecGoods.empty())
	{
		CAScheduler::schedule(schedule_selector(SearchViewController::loadData), this, 0.5);
	}
	else
	{
		for (int i = 0; i < m_vecGoods.size() && i < 6; i++)
		{
			m_vecVisibleGoods.push_back(m_vecGoods[i]);
		}
		m_pIndicatorView->stopAnimating();
	}
}

void SearchViewController::collectionViewDidSelectCellAtIndexPath(CACollectionView *collectionView, unsigned int section, unsigned int row, unsigned int item)
{
	//µ±Î´µÇÂ¼Ê±£¬µ¯³öµÇÂ¼¿ò
	if (ShopDB::Instance()->getUser().id == 0 || ShopDB::Instance()->getUser().id == NULL)
	{
		this->sendMsg(LOGIN, this);
	}
	else
	{
		ProductViewController *pProductViewController = ProductViewController::create();
		pProductViewController->setId(m_vecVisibleGoods[row * 2 + item].id);
		pProductViewController->setReceiver(m_pReceiver);
		CANavigationController *pProductNavigationController = new CANavigationController();
		pProductNavigationController->initWithRootViewController(pProductViewController);
		this->presentModalViewController(pProductNavigationController, true);
	}
}

void SearchViewController::collectionViewDidDeselectCellAtIndexPath(CACollectionView *collectionView, unsigned int section, unsigned int row, unsigned int item)
{

}

CACollectionViewCell* SearchViewController::collectionCellAtIndex(CACollectionView *collectionView, const CCSize& cellSize, unsigned int section, unsigned int row, unsigned int item)
{
	if (row * 2 + item >= m_vecVisibleGoods.size())
	{
		return NULL;
	}

	//CADipSize _size = cellSize;
	float itemWidth = cellSize.width / 6 * 4;
	CACollectionViewCell* pCell = collectionView->dequeueReusableCellWithIdentifier("CrossShop");
	if (pCell == NULL)
	{
		pCell = CACollectionViewCell::create("CrossShop");

		CAImageView* pItemImageView = CAImageView::createWithFrame(CADipRect((cellSize.width - itemWidth)/2, cellSize.height / 10, itemWidth, itemWidth));
		pItemImageView->setTag(99);
		pCell->addSubview(pItemImageView);

		CAView *pPriceView = CAView::createWithFrame(CADipRect(0, cellSize.height / 10 * 2, cellSize.width / 10*4, _px(35)));
		pPriceView->setColor(ccc4(230,62,42,210));
		pPriceView->setTag(200);
		pCell->addSubview(pPriceView);

		CALabel *pPriceText = CALabel::createWithCenter(CADipRect(pPriceView->getBounds().size.width / 10*6, pPriceView->getBounds().size.height / 2, pPriceView->getBounds().size.width, _px(25)));
		pPriceText->setColor(CAColor_white);
		pPriceText->setFontSize(_px(25));
		pPriceText->setTag(210);
		pPriceView->addSubview(pPriceText);


		CALabel* pItemText = CALabel::createWithCenter(CADipRect(cellSize.width*0.5, cellSize.height / 20 * 18, cellSize.width / 10 * 8, _px(20)));
		pItemText->setTag(100);
		//pItemText->setColor(ccc4(91, 91, 91, 225));
		pItemText->setFontSize(_px(20));
		pItemText->setTextAlignment(CATextAlignmentCenter);
		pItemText->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
		pCell->addSubview(pItemText);
	}
	CAImageView* pItemImageView = (CAImageView*)pCell->getSubviewByTag(99);

	pItemImageView->setImage(CAImage::create(m_vecVisibleGoods[row * 2 + item].img_thumb));

	CALabel* pItemText = (CALabel*)pCell->getSubviewByTag(100);
	pItemText->setText(m_vecVisibleGoods[row * 2 + item].name);

	CALabel *pPriceText = (CALabel*)pCell->getSubviewByTag(200)->getSubviewByTag(210);
	pPriceText->setText(m_vecVisibleGoods[row * 2 + item].shop_price);

	//p_Cell->setColor(CAColor_clear);
	pCell->setBackgroundView(CAScale9ImageView::createWithImage(CAImage::create("source_material/item_box_bg.png")));
	return pCell;
}

unsigned int SearchViewController::numberOfSections(CACollectionView *collectionView)
{
	return 1;
}

unsigned int SearchViewController::numberOfRowsInSection(CACollectionView *collectionView, unsigned int section)
{
	//return colorArr.size() % 3 == 0 ? colorArr.size() / 3 : colorArr.size() / 3 + 1;
	return m_vecVisibleGoods.size() % 2 == 0 ? m_vecVisibleGoods.size() / 2 : m_vecVisibleGoods.size() / 2 + 1;
}

unsigned int SearchViewController::numberOfItemsInRowsInSection(CACollectionView *collectionView, unsigned int section, unsigned int row)
{
	return 2;
}

unsigned int SearchViewController::collectionViewHeightForRowAtIndexPath(CACollectionView* collectionView, unsigned int section, unsigned int row)
{
	return collectionView->getViewSize().width/2;
}

void SearchViewController::scrollViewFooterBeginRefreshing(CAScrollView* view)
{
	CAScheduler::schedule(schedule_selector(SearchViewController::refreshData), this, 0.1, 0, CCRANDOM_0_1() * 2, false);
}

void SearchViewController::refreshData(float interval)
{
	for (int i = m_vecVisibleGoods.size(); i < m_vecVisibleGoods.size() + 4; i++)
	{
		if (m_vecGoods.size()>i)
			m_vecVisibleGoods.push_back(m_vecGoods[i]);
	}
	m_pConllectionView->reloadData();
}

void SearchViewController::clickSearchBtn(CAControl* sender, CCPoint point)
{
	m_keywords = m_pSearchField->getText();
	this->loadData();
}