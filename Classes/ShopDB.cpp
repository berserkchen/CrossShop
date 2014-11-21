//****************************************
//CrossShop  Demo0.01
//QQ£º896793747
//****************************************
#include "ShopDB.h"


ShopDB *ShopDB::m_pInstance = NULL;


ShopDB::ShopDB()
{
	ZeroMemory(&m_user, sizeof(m_user));
}
ShopDB::~ShopDB()
{
}
void ShopDB::Release()
{
	m_pInstance->release();
	m_pInstance = NULL;
}
ShopDB* ShopDB::Instance()
{
	if (m_pInstance == NULL) m_pInstance = new ShopDB();
	return m_pInstance;
}
std::string ShopDB::GetUrlHeader()
{
	return "http://discuz.app.51hengshui.com/ecshop/ECMobile/?url=";
}

void ShopDB::HttpRequest(std::string url, const char *postData, CAObject *pTarget, SEL_ShopDBOnComplete onComplete, SEL_ShopDBOnHttpComplete onHttpComplete, void *pUserData, int nThread)
{

	if (pTarget != NULL) pTarget->retain();
	CCHttpClient *httpClient = CCHttpClient::getInstance();
	CCHttpRequest* httpReq = new ShopDBHttpRequest(pTarget, onComplete, onHttpComplete, pUserData);
	httpReq->setRequestType(CCHttpRequest::kHttpPost);
	httpReq->setUrl(utf8_to_url_string(url.c_str()).c_str());
	httpReq->setResponseCallback(this, httpresponse_selector(ShopDB::HttpFinished));
	httpReq->setRequestData(postData, strlen(postData));
	httpClient->setTimeoutForConnect(30);
	httpClient->send(httpReq);
	httpReq->release();


}
void ShopDB::HttpFinished(CCHttpClient* client, CCHttpResponse* response)
{
	ShopDBHttpRequest *pRequest = (ShopDBHttpRequest*)response->getHttpRequest();
	if (!response->isSucceed())
	{
		if (pRequest->pTarget != NULL)
		{
			(pRequest->pTarget->*pRequest->onHttpComplete)(pRequest, NULL);
			pRequest->pTarget->release();
		}
		return;
	}
	std::vector<char> *data = response->getResponseData();
	int data_length = data->size();
	std::string res;
	for (int i = 0; i<data_length; ++i)
	{
		res += (*data)[i];
	}
	res += '\0';

	CCLog("%s", res.c_str());

	CSJson::Reader reader;
	CSJson::Value root;
	if (reader.parse(res.c_str(), root))
	{
		(this->*pRequest->onHttpComplete)(pRequest, &root);
		if (pRequest->pTarget != NULL)
			pRequest->pTarget->release();
		return;
	}
	else
	{
		(this->*pRequest->onHttpComplete)(pRequest, NULL);
		if (pRequest->pTarget != NULL)
			pRequest->pTarget->release();
		return;
	}
}
void ShopDB::SignIn(CAObject *pTarget, SEL_ShopDBOnComplete onComplete, string userName, string passWord)
{
	string url = GetUrlHeader()+"/user/signin";
	string str = "name=" + userName+ "&password=" + passWord;
	HttpRequest(url, str.c_str(), pTarget, onComplete, ShopDB_httpselector(ShopDB::SignInFinished));
}
void ShopDB::SignInFinished(ShopDBHttpRequest *pRequest, CSJson::Value *pJson)
{
	if (pJson == NULL) (pRequest->pTarget->*pRequest->onComplete)(NULL);
	else
	{
		SignInData signInData;
		signInData.ReadFromJson(*pJson);
		(pRequest->pTarget->*pRequest->onComplete)(&signInData);
	}

}

void ShopDB::SignUp(CAObject *pTarget, SEL_ShopDBOnComplete onComplete, std::string userName, std::string passWord, std::string email)
{
	string url = GetUrlHeader() + "/user/signup";
	CCLog("%s", url.c_str());
	string str = "name=" + userName + "&email=" + email + "&password=" + passWord + "&field={SIGNUP_FIELD_VALUE}";
	HttpRequest(url, str.c_str(), pTarget, onComplete, ShopDB_httpselector(ShopDB::SignUpFinished));
}

void ShopDB::SignUpFinished(ShopDBHttpRequest *pRequest, CSJson::Value *pJson)
{
	if (pJson == NULL) (pRequest->pTarget->*pRequest->onComplete)(NULL);
	else
	{
		SignUpData signUpData;
		signUpData.ReadFromJson(*pJson);
		(pRequest->pTarget->*pRequest->onComplete)(&signUpData);
	}
}

void ShopDB::Category(CAObject *pTarget, SEL_ShopDBOnComplete onComplete)
{
	string url = GetUrlHeader() + "/home/category";
	CCLog("%s", url.c_str());
	const char* postData = " ";
	HttpRequest(url, postData, pTarget, onComplete, ShopDB_httpselector(ShopDB::CategoryFinished));
}

void ShopDB::CategoryFinished(ShopDBHttpRequest *pRequest, CSJson::Value *pJson)
{
	if (pJson == NULL) (pRequest->pTarget->*pRequest->onComplete)(NULL);
	else
	{
		CategoryData categoryData;
		categoryData.ReadFromJson(*pJson);
		(pRequest->pTarget->*pRequest->onComplete)(&categoryData);
	}
}

void ShopDB::Goods(CAObject *pTarget, SEL_ShopDBOnComplete onComplete, unsigned int goods_id, unsigned int uid, std::string sid)
{
	string url = GetUrlHeader() + "/goods";
	CCLog("%s", url.c_str());

	CCString *str = CCString::createWithFormat("goods_id=%d&uid=%d&sid=%s", goods_id, uid, sid.c_str());

	HttpRequest(url, str->getCString(), pTarget, onComplete, ShopDB_httpselector(ShopDB::GoodsFinished));
}
void ShopDB::GoodsFinished(ShopDBHttpRequest *pRequest, CSJson::Value *pJson)
{
	if (pJson == NULL) (pRequest->pTarget->*pRequest->onComplete)(NULL);
	else
	{
		GoodData goodData;
		goodData.ReadFromJson(*pJson);
		(pRequest->pTarget->*pRequest->onComplete)(&goodData);
	}
}

//@error
void ShopDB::Search(CAObject *pTarget, SEL_ShopDBOnComplete onComplete, std::string keywords, unsigned int category_id, std::string sort_by, unsigned int count)
{
	string url = GetUrlHeader() + "/search";
	CCLog("%s", url.c_str());

	CSJson::Value root;
	CSJson::Value filter;
	CSJson::Value pagination;
	CSJson::Value price_range;
	CSJson::FastWriter writer;

	price_range["price_min"] = 0;
	price_range["price_max"] = 100;

	filter["keywords"] = "n";
	filter["sort_by"] = "is_hot";
	filter["brand_id"] = "1";
	filter["category_id"] = "1";
	filter["price_range"] = price_range;

	pagination["page"] = "1";
	pagination["count"] = "1";

	root["filter"] = filter;
	root["pagination"] = pagination;

	std::string str = writer.write(root);

	CCLog("%s", str.c_str());

	HttpRequest(url, str.c_str(), pTarget, onComplete, ShopDB_httpselector(ShopDB::SearchFinished));
}
void ShopDB::SearchFinished(ShopDBHttpRequest *pRequest, CSJson::Value *pJson)
{
	if (pJson == NULL) (pRequest->pTarget->*pRequest->onComplete)(NULL);
	else
	{
		SearchData searchData;
		searchData.ReadFromJson(*pJson);
		(pRequest->pTarget->*pRequest->onComplete)(&searchData);
	}
}

//@error
void ShopDB::CartList(CAObject *pTarget, SEL_ShopDBOnComplete onComplete, unsigned int uid, std::string sid)
{
	string url = GetUrlHeader() + "/cart/list";
	CCLog("%s", url.c_str());
	CCString *str = CCString::createWithFormat("uid=%d&sid=%s", uid,sid.c_str());
	HttpRequest(url, str->getCString(), pTarget, onComplete, ShopDB_httpselector(ShopDB::CartListFinished));
}

void ShopDB::CartListFinished(ShopDBHttpRequest *pRequest, CSJson::Value *pJson)
{
	if (pJson == NULL) (pRequest->pTarget->*pRequest->onComplete)(NULL);
	else
	{
		CardListData cardListData;
		cardListData.ReadFromJson(*pJson);
		(pRequest->pTarget->*pRequest->onComplete)(&cardListData);
	}
}

//@error
void ShopDB::Profile(CAObject *pTarget, SEL_ShopDBOnComplete onComplete, unsigned int uid, std::string sid)
{
	string url = GetUrlHeader() + "/user/info";
	CCLog("%s", url.c_str());

	CCString *str = CCString::createWithFormat("uid=%d&sid=%s", uid, sid.c_str());
	HttpRequest(url, str->getCString(), pTarget, onComplete, ShopDB_httpselector(ShopDB::ProfileFinished));
}

void ShopDB::ProfileFinished(ShopDBHttpRequest *pRequest, CSJson::Value *pJson)
{
	if (pJson == NULL) (pRequest->pTarget->*pRequest->onComplete)(NULL);
	else
	{
		ProfileData profileData;
		profileData.ReadFromJson(*pJson);
		(pRequest->pTarget->*pRequest->onComplete)(&profileData);
	}
}

//@error
void ShopDB::AddressList(CAObject *pTarget, SEL_ShopDBOnComplete onComplete, unsigned int uid, std::string sid)
{
	string url = GetUrlHeader() + "/address/list";
	CCLog("%s", url.c_str());

	CCString *str = CCString::createWithFormat("\{\"data\":\{\"session\":\{\"sid\":\"%s\"\}\}\}",sid.c_str());

	HttpRequest(url, str->getCString(), pTarget, onComplete, ShopDB_httpselector(ShopDB::AddressListFinished));
}
void ShopDB::AddressListFinished(ShopDBHttpRequest *pRequest, CSJson::Value *pJson)
{
	if (pJson == NULL) (pRequest->pTarget->*pRequest->onComplete)(NULL);
	else
	{
		AddressListData addressListData;
		addressListData.ReadFromJson(*pJson);
		(pRequest->pTarget->*pRequest->onComplete)(&addressListData);
	}
}