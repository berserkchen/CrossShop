//****************************************
//CrossShop  Demo0.01
//QQ£º896793747
//****************************************
#ifndef __CrossShop__MessageController__
#define __CrossShop__MessageController__

#include "CrossApp.h"
#include "ShopDB.h"

enum
{
	LOGIN = 0,
	LOGIN_SUCCESS,
	LOGUP_SUCCESS
};

class Receiver
{
public:
	virtual void onMsgReceive(int enMsg, CAViewController *Sender) = 0;
};

class Sender
{
protected:
	Receiver* m_pReceiver;
public:
	void setReceiver(Receiver* pReceiver)
	{
		m_pReceiver = pReceiver;
	}
	void sendMsg(int enMsg, CAViewController *Sender)
	{
		m_pReceiver->onMsgReceive(enMsg, Sender);
	}
};


#endif