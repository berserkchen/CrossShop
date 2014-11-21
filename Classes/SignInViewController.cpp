//****************************************
//CrossShop  Demo0.01
//QQ£º896793747
//****************************************
#include "SignInViewController.h"
#include "SignUpViewController.h"
#include "CNString.h"
#include "UI.h"

CANavigationController* SignInViewController::create(Receiver* pReceiver)
{                                       
	SignInViewController *pSignInViewController = new SignInViewController();
	if (pSignInViewController && pSignInViewController->init())
	{   
		CANavigationController *pSignInNavigationController = new CANavigationController();
		pSignInViewController->setReceiver(pReceiver);
		pSignInNavigationController->initWithRootViewController(pSignInViewController);
		pSignInViewController->autorelease();
		pSignInNavigationController->autorelease();
		return pSignInNavigationController;
	}                                   
	return NULL;                    
}

bool SignInViewController::init()
{
	CANavigationBarItem* item = CANavigationBarItem::create(CN_STRING("yonghudenglu"));
	CABarButtonItem *rightButtonItem = CABarButtonItem::create(CN_STRING("denglu"), NULL, NULL);
	rightButtonItem->setTarget(this, CAControl_selector(SignInViewController::signIn));

	CABarButtonItem *leftButtonItem = CABarButtonItem::create("", CAImage::create("source_material/btn_left_white.png"), CAImage::create("source_material/btn_left_blue.png"));
	leftButtonItem->setTarget(this, CAControl_selector(SignInViewController::pushBack));

	item->addRightButtonItem(rightButtonItem);
	item->addLeftButtonItem(leftButtonItem);

	this->setNavigationBarItem(item);

	item->release();

	return true;
}

void SignInViewController::viewDidLoad()
{
	CCRect rect = this->getView()->getBounds();

	m_controlRect.prompt = CCRect(rect.size.width / 2, 50, rect.size.width - 10, 80);

	m_controlRect.account = CCRect(rect.size.width / 2, 100, rect.size.width - 10, 80);
	m_controlRect.passWord = CCRect(rect.size.width / 2, 200, rect.size.width - 10, 80);
	m_controlRect.signUp = CCRect(rect.size.width / 2, m_controlRect.passWord.origin.y + 130, rect.size.width - 200, 50);

	this->getView()->setColor(CAColor_gray);

	m_pTextField_account = UI::longTextField(m_controlRect.account, CN_STRING("zhanghao"));
	this->getView()->addSubview(m_pTextField_account);

	m_pTextField_passWord = UI::longTextField(m_controlRect.passWord, CN_STRING("mima"));
	this->getView()->addSubview(m_pTextField_passWord);

	//m_pBtn_signIn = CAButton::createWithCenter(m_controlRect.signIn, CAButtonTypeSquareRect);
	//m_pBtn_signIn->setTitleForState(CAControlStateAll, CNString::shareCNString()->getCNString("denglu"));
	//m_pBtn_signIn->addTarget(this, CAControl_selector(SignInViewController::signIn), CAControlEventTouchUpInSide);
	//this->getView()->addSubview(m_pBtn_signIn);

	m_pLink_signUp = CAButton::createWithCenter(m_controlRect.signUp, CAButtonTypeCustom);
	m_pLink_signUp->setTitleForState(CAControlStateAll, CN_STRING("meiyouzhanghaozhucheyige"));
	m_pLink_signUp->setColor(CAColor_black);
	m_pLink_signUp->addTarget(this, CAControl_selector(SignInViewController::pushSignUpViewController), CAControlEventTouchUpInSide);
	this->getView()->addSubview(m_pLink_signUp);

	m_pLabel_prompt = CALabel::createWithCenter(m_controlRect.prompt);
	m_pLabel_prompt->setTextAlignment(CATextAlignmentCenter);
	m_pLabel_prompt->setFontSize(25);
	m_pLabel_prompt->setColor(CAColor_red);
	this->getView()->addSubview(m_pLabel_prompt);


}


void SignInViewController::viewDidUnload()
{
}


void SignInViewController::pushBack(CAControl* sender, CCPoint point)
{
	this->dismissModalViewController(true);
}

void SignInViewController::signIn(CAControl* sender, CCPoint point)
{

	string account = m_pTextField_account->getText();
	string passWord = m_pTextField_passWord->getText();

	ShopDB::Instance()->SignIn(this, ShopDB_selector(SignInViewController::OnComplete), account, passWord);
}


void SignInViewController::pushSignUpViewController(CAControl* sender, CCPoint point)
{
	SignUpViewController *pSignUpViewController = SignUpViewController::create();
	pSignUpViewController->setReceiver(m_pReceiver);
	this->getNavigationController()->pushViewController(pSignUpViewController, true);
	pSignUpViewController->release();
}

void SignInViewController::OnComplete(void *pData)
{
	SignInData signInData = *(SignInData*)pData;

	if (signInData.getStatus().succeed == 0)
	{
		//µÇÂ¼Ê§°Ü
		CAAlertView *pAlertView = CAAlertView::createWithText(CN_STRING("denglushibai").c_str(), signInData.getStatus().error_desc.c_str(), CN_STRING("queding").c_str(), NULL);
		pAlertView->show();
	}
	else
	{
		//µÇÂ¼³É¹¦
		ShopDB::Instance()->setUser(signInData.m_user);
		this->dismissModalViewController(true);
		this->sendMsg(LOGIN_SUCCESS,this);
		CCLog("%s", ShopDB::Instance()->getUser().sid.c_str());
	}


}
