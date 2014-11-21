//****************************************
//CrossShop  Demo0.01
//QQ：896793747
//****************************************
#include "RootWindow.h"
#include "CNString.h"

CAWindow* RootWindow::createWindow()
{
	CAWindow *pWindow = CAWindow::create();
	RootWindow* pFuntion = RootWindow::create();
	pWindow->setRootViewController(pFuntion);

	return pWindow;
}

RootWindow::RootWindow() :m_TabBarHeight(0.00), m_NavigationBarHeight(0.00)
{

}

RootWindow::~RootWindow()
{

}

void RootWindow::viewDidLoad()
{
	CATabBarController::viewDidLoad();
}

void RootWindow::viewDidUnload()
{
	CATabBarController::viewDidUnload();
}

bool RootWindow::init()
{
	//-----------首页-----------//
	IndexViewController *pIndexViewController = IndexViewController::create();
	pIndexViewController->setReceiver(this);
	CANavigationController* pIndexNavigationController = new CANavigationController();
	pIndexNavigationController->initWithRootViewController(pIndexViewController);
	pIndexNavigationController->setTabBarItem(CATabBarItem::create("", CAImage::create("source_material/footer_home_icon@2x.png"), CAImage::create("source_material/footer_home_active_icon@2x.png")));

	//-----------搜索页面-----------//
	m_pSearchViewController = SearchViewController::create();
	m_pSearchViewController->setReceiver(this);
	m_pSearchViewController->setTabBarItem(CATabBarItem::create("", CAImage::create("source_material/footer_search_icon@2x.png"), CAImage::create("source_material/footer_search_active_icon@2x.png")));

	//-----------购物车页面-----------//
	m_pCartListViewController = CartListViewController::create();
	m_pCartListViewController->setReceiver(this);
	CANavigationController* pCartListCartNavigationController = new CANavigationController();
	pCartListCartNavigationController->initWithRootViewController(m_pCartListViewController);
	pCartListCartNavigationController->setTabBarItem(CATabBarItem::create("", CAImage::create("source_material/footer_shopping_cart_icon@2x.png"), CAImage::create("source_material/footer_shopping_cart_active_icon@2x.png")));

	//-----------个人信息页面-----------//
	m_pProfileViewController = ProfileViewController::create();
	m_pProfileViewController->setReceiver(this);
	CANavigationController* pProfileNavigationController = new CANavigationController();
	pProfileNavigationController->initWithRootViewController(m_pProfileViewController);
	pProfileNavigationController->setTabBarItem(CATabBarItem::create("", CAImage::create("source_material/footer_user_icon@2x.png"), CAImage::create("source_material/footer_user_active_icon@2x.png")));

	std::vector<CAViewController*> vecControllerItem;
	vecControllerItem.push_back(pIndexNavigationController);
	vecControllerItem.push_back(m_pSearchViewController);
	vecControllerItem.push_back(pCartListCartNavigationController);
	vecControllerItem.push_back(pProfileNavigationController);
    
	this->initWithViewControllers(vecControllerItem);
	this->getTabBar()->showSelectedIndicator();
  
    return true;
}


float RootWindow::getTabBarHeight(void)
{
	return 0;
}

float RootWindow::getNavigationBarHeight(void)
{
	return 0;
}

void RootWindow::onMsgReceive(int enMsg, CAViewController *Sender)
{
	if (enMsg == LOGIN)
	{
		m_pSignInViewController = SignInViewController::create(this);
		Sender->presentModalViewController(m_pSignInViewController, true);
	}
	else if (enMsg == LOGIN_SUCCESS)
	{
		if (m_pCartListViewController->isViewRunning())
		{
			m_pCartListViewController->loadData();
		}
		if (m_pProfileViewController->isViewRunning())
		{
			m_pProfileViewController->loadData();
		}
	}
	else if (enMsg == LOGUP_SUCCESS)
	{
		if (m_pCartListViewController->isViewRunning())
		{
			m_pCartListViewController->loadData();
		}
		if (m_pProfileViewController->isViewRunning())
		{
			m_pProfileViewController->loadData();
		}
	}
}