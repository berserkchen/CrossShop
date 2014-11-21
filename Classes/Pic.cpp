//****************************************
//CrossShop  Demo0.01
//QQ£º896793747
//****************************************
#include "Pic.h"

static Pic *pic = new  Pic();

Pic* Pic::getInstance()
{
	return pic;
}

std::string Pic::loadIconFromUrl(const char *url)
{
	if (url != NULL && url[0] != 0)
	{
		std::string strUrl = url;
		if (strncmp(strUrl.c_str(), "http://", 7) == 0)
			strUrl = &strUrl[7];
		for (int i = 0; i < strUrl.size(); i++)
		{
			if (strUrl[i] == '/' || strUrl[i] == '?' || strUrl[i] == '&') strUrl[i] = '_';
		}
		m_ret = CCFileUtils::sharedFileUtils()->getWritablePath();
		m_ret += strUrl;
		FILE *pFile = fopen(m_ret.c_str(), "rb");
		if (pFile != NULL)
		{
			fclose(pFile);
		}
		else
		{
			CCHttpClient* httpClient = CCHttpClient::getInstance();
			CCHttpRequest* httpReq = new CCHttpRequest();
			httpReq->setRequestType(CCHttpRequest::kHttpGet);
			httpReq->setUrl(url);
			httpReq->setResponseCallback(this, httpresponse_selector(Pic::onPicgRequestFinished));
			httpClient->setTimeoutForConnect(30);
			httpClient->send(httpReq);
			httpReq->release();
		}
		return m_ret;
	}
	else
	{
		return NULL;
	}	


}

void Pic::onPicgRequestFinished(CCHttpClient* client, CCHttpResponse* response)
{
	if (!response->isSucceed())
		return;

	std::vector<char> *data = response->getResponseData();
	int data_length = data->size();
	std::string strUrl = response->getHttpRequest()->getUrl();
	if (strncmp(strUrl.c_str(), "http://", 7) == 0)
		strUrl = &strUrl[7];
	for (int i = 0; i < strUrl.size(); i++)
	{
		if (strUrl[i] == '/' || strUrl[i] == '?' || strUrl[i] == '&') strUrl[i] = '_';
	}
	m_ret = CCFileUtils::sharedFileUtils()->getWritablePath();
	m_ret += strUrl;
	FILE *pWrite = fopen(m_ret.c_str(), "wb");
	fwrite(&(*data)[0], data_length, 1, pWrite);
	fclose(pWrite);
}