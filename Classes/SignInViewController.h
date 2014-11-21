//****************************************
//CrossShop  Demo0.01
//QQ：896793747
//****************************************
#ifndef __CrossShop__SignInViewControllerr__
#define __CrossShop__SignInViewControllerr__

#include <iostream>
#include "CrossApp.h"
#include "ShopDB.h"
#include "MessageController.h"

USING_NS_CC;

typedef struct
{
	CCRect account;
	CCRect passWord;
	CCRect signIn;
	CCRect signUp;
	CCRect prompt;
}SinInRect;

class SignInViewController : public CAViewController,public Sender
{

private:
	//数据相关
	std::vector<CATEGORY> m_categorys;

	//控件相关
	CATextField *m_pTextField_account;
	CATextField *m_pTextField_passWord;

	//CAButton *m_pBtn_signIn;
	CAButton *m_pLink_signUp;
	CALabel *m_pLabel_prompt;

	SinInRect m_controlRect;

	//std::vector<LoginData> m_vecLoginData;
	/*LoginData m_loginData;*/

public:
	static CANavigationController *create(Receiver* pReceiver);

protected:

	virtual bool init();

	void viewDidLoad();

	void viewDidUnload();

	void pushBack(CAControl* sender, CCPoint point);

	void signIn(CAControl* sender, CCPoint point);

	void pushSignUpViewController(CAControl* sender, CCPoint point);

	void OnComplete(void *pData);

};


#endif /* defined(__CrossShop__SignInViewControllerr__) */
