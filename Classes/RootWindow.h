//****************************************
//CrossShop  Demo0.01
//QQ：896793747
//****************************************
#ifndef __MiniShop__RootWindow__
#define __MiniShop__RootWindow__

#include <iostream>
#include "CrossApp.h"
#include "ShopDB.h"
#include "MessageController.h"
#include "IndexViewController.h"
#include "SignInViewController.h"
#include "SearchViewController.h"
#include "CartListViewController.h"
#include "ProfileViewController.h"

USING_NS_CC;

class RootWindow : public CATabBarController, public Receiver
{
    
public:
	RootWindow();
	virtual ~RootWindow();

	static CAWindow* createWindow();

	virtual bool init();
	CREATE_FUNC(RootWindow);

protected:
	virtual void viewDidLoad();
	virtual void viewDidUnload();

public:
	float getTabBarHeight(void);
	float getNavigationBarHeight(void);

private:
	float m_TabBarHeight;
	float m_NavigationBarHeight;

	CANavigationController *m_pSignInViewController;
	SearchViewController *m_pSearchViewController;
	CartListViewController *m_pCartListViewController;
	ProfileViewController *m_pProfileViewController;
	//接收消息
	void onMsgReceive(int enMsg, CAViewController *Sender);
    
};


#endif /* defined(__MiniShop__RootWindow__) */
