//****************************************
//CrossShop  Demo0.01
//QQ£º896793747
//****************************************
#ifndef __CrossShop__SignUpViewController__
#define __CrossShop__SignUpViewController__

#include <iostream>
#include "CrossApp.h"
#include "MessageController.h"

USING_NS_CC;

typedef struct
{
	CCRect account;
	CCRect email;
	CCRect passWord;
	CCRect confirm;
	CCRect signIn;
	CCRect prompt;
}SinUpRect;

class SignUpViewController : public CAViewController, public Sender
{
public:
	static SignUpViewController *create();

private:
	CATextField *m_pTextField_account;
	CATextField *m_pTextField_email;
	CATextField *m_pTextField_passWord;
	CATextField *m_pTextField_confirm;
	CAButton *m_pLink_signIn;
	CALabel *m_pLabel_prompt;

	SinUpRect m_controlRect;

protected:

	void viewDidLoad();

	void viewDidUnload();

	void diss(CAControl* sender, CCPoint point);

	void signUp(CAControl* sender, CCPoint point);

	void OnComplete(void *pData);

};


#endif /* defined(__CrossShop__SignUpViewController__) */
