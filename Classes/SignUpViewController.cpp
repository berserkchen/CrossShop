//****************************************
//CrossShop  Demo0.01
//QQ£º896793747
//****************************************
#include "SignUpViewController.h"
#include "CNString.h"
#include "ShopDB.h"
#include "UI.h"

SignUpViewController *SignUpViewController::create()
{
	SignUpViewController *pSignUpViewController = new SignUpViewController();
	if (pSignUpViewController && pSignUpViewController->init())
	{
		CANavigationBarItem* item = CANavigationBarItem::create(CN_STRING("yonghuzhuche"));
		CABarButtonItem *rightButtonItem = CABarButtonItem::create(CN_STRING("zhuche"), NULL, NULL);
		rightButtonItem->setTarget(pSignUpViewController, CAControl_selector(SignUpViewController::signUp));
		item->addRightButtonItem(rightButtonItem);
		pSignUpViewController->setNavigationBarItem(item);
		return pSignUpViewController;
	}
	return NULL;
}

void SignUpViewController::viewDidLoad()
{
	CCRect rect = this->getView()->getBounds();

	m_controlRect.prompt = CCRect(rect.size.width / 2, 50, rect.size.width - 10, 80);

	m_controlRect.account = CCRect(rect.size.width / 2, 100, rect.size.width - 10, 80);
	m_controlRect.email = CCRect(rect.size.width / 2, 180, rect.size.width - 10, 80);
	m_controlRect.passWord = CCRect(rect.size.width / 2, 260, rect.size.width - 10, 80);
	m_controlRect.confirm = CCRect(rect.size.width / 2, 340, rect.size.width - 10, 80);
	m_controlRect.signIn = CCRect(rect.size.width / 2, m_controlRect.confirm.origin.y + 130, rect.size.width - 200, 50);


	this->getView()->setColor(CAColor_gray);

	m_pTextField_account = UI::longTextField(m_controlRect.account, CN_STRING("zhanghao"));
	this->getView()->addSubview(m_pTextField_account);

	m_pTextField_email = UI::longTextField(m_controlRect.email, CN_STRING("youxiang"));
	this->getView()->addSubview(m_pTextField_email);

	m_pTextField_passWord = UI::longTextField(m_controlRect.passWord, CN_STRING("mima"));
	this->getView()->addSubview(m_pTextField_passWord);

	m_pTextField_confirm = UI::longTextField(m_controlRect.confirm, CN_STRING("querenmima"));
	this->getView()->addSubview(m_pTextField_confirm);


	m_pLink_signIn = CAButton::createWithCenter(m_controlRect.signIn, CAButtonTypeCustom);
	m_pLink_signIn->setTitleForState(CAControlStateAll, CN_STRING("dengluyiyouzhanghao"));
	m_pLink_signIn->addTarget(this, CAControl_selector(SignUpViewController::diss), CAControlEventTouchUpInSide);
	this->getView()->addSubview(m_pLink_signIn);

	m_pLabel_prompt = CALabel::createWithCenter(m_controlRect.prompt);
	m_pLabel_prompt->setTextAlignment(CATextAlignmentCenter);
	m_pLabel_prompt->setFontSize(25);
	m_pLabel_prompt->setColor(CAColor_red);
	this->getView()->addSubview(m_pLabel_prompt);

}


void SignUpViewController::viewDidUnload()
{
}


void SignUpViewController::diss(CAControl* sender, CCPoint point)
{
	this->getNavigationController()->popViewControllerAnimated(true);
}

void SignUpViewController::signUp(CAControl* sender, CCPoint point)
{
	string account = m_pTextField_account->getText();
	string email = m_pTextField_email->getText();
	string passWord = m_pTextField_passWord->getText();
	string confirm = m_pTextField_confirm->getText();

	if (passWord == confirm&&passWord.size()>5)
	{
		ShopDB::Instance()->SignUp(this, ShopDB_selector(SignUpViewController::OnComplete), account, passWord, email);
	}
	else if (passWord != confirm)
	{
		//µÇÂ¼Ê§°Ü
		CAAlertView *pAlertView = CAAlertView::createWithText(CN_STRING("zhucheshibai").c_str(), CN_STRING("liangcimimabutong").c_str(), CN_STRING("queding").c_str(), NULL);
		pAlertView->show();
	}
	else if (passWord.size()<5)
	{
		//µÇÂ¼Ê§°Ü
		CAAlertView *pAlertView = CAAlertView::createWithText(CN_STRING("zhucheshibai").c_str(), CN_STRING("mimachangdubuzu").c_str(), CN_STRING("queding").c_str(), NULL);
		pAlertView->show();
	}


}

void SignUpViewController::OnComplete(void *pData)
{
	SignUpData signUpData = *(SignUpData*)pData;

	if (signUpData.getStatus().succeed == 0)
	{
		//µÇÂ¼Ê§°Ü
		CAAlertView *pAlertView = CAAlertView::createWithText(CN_STRING("zhucheshibai").c_str(), signUpData.getStatus().error_desc.c_str(), CN_STRING("queding").c_str(), NULL);
		pAlertView->show();
	}
	else
	{
		//µÇÂ¼³É¹¦
		ShopDB::Instance()->setUser(signUpData.m_user);
		this->dismissModalViewController(true);
		this->sendMsg(LOGUP_SUCCESS, this);
		CCLog("%s", ShopDB::Instance()->getUser().name.c_str());
	}
}