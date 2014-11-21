//****************************************
//CrossShop  Demo0.01
//QQ£º896793747
//****************************************
#ifndef __CrossShop__Pic__
#define __CrossShop__Pic__

#include "CrossApp.h"
#include "CrossAppExt.h"

USING_NS_CC;

USING_NS_CC_EXT;;


#define PIC_LOAD(x) Pic::getInstance()->loadIconFromUrl(x) 

class Pic : public CAObject
{
public:
	static Pic* getInstance();
	std::string loadIconFromUrl(const char *url);

	void onPicgRequestFinished(CCHttpClient* client, CCHttpResponse* response);
private:
	std::string m_ret;
};

#endif //__MiniShop__Pic__