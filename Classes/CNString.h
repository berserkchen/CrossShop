//****************************************
//CrossShop  Demo0.01
//QQ��896793747
//****************************************
#ifndef __CrossShop__CNString__
#define __CrossShop__CNString__

#include "CrossApp.h"

USING_NS_CC;


#define CN_STRING(x) CNString::shareCNString()->getCNString(x) 

class CNString
{
private:
	tinyxml2::XMLDocument xmlDoc;
public:
	CNString();
	//��õ���
	static CNString* shareCNString();
	//���XML����ַ�
	std::string getCNString(string st);
};

#endif //__CrossShop__CNString__