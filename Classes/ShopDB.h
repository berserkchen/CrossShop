//****************************************
//CrossShop  Demo0.01
//QQ：896793747
//****************************************
#ifndef __CrossShop__ShopDB__
#define __CrossShop__ShopDB__

#include <list>
#include "CrossApp.h"
#include "CrossAppExt.h"
#include "Pic.h"
#include "Define.h"

USING_NS_CC;

USING_NS_CC_EXT;;



typedef void (CAObject::*SEL_ShopDBOnComplete)(void *pData);
#define ShopDB_selector(_SELECTOR) (SEL_ShopDBOnComplete)(&_SELECTOR)
class ShopDBHttpRequest;
typedef void (CAObject::*SEL_ShopDBOnHttpComplete)(ShopDBHttpRequest *pRequest, CSJson::Value *pJson);
#define ShopDB_httpselector(_SELECTOR) (SEL_ShopDBOnHttpComplete)(&_SELECTOR)

// Http请求方法，记录回调参数
class ShopDBHttpRequest : public CCHttpRequest
{
public:
	CAObject *pTarget; // 回调目标
	SEL_ShopDBOnComplete onComplete; // 回调函数
	SEL_ShopDBOnHttpComplete onHttpComplete; // HTTP完成函数
	void *pUserData; // 用户数据

	ShopDBHttpRequest(CAObject *pTarget, SEL_ShopDBOnComplete onComplete, SEL_ShopDBOnHttpComplete onHttpComplete, void *pUserData)
	{
		this->pTarget = pTarget;
		this->onComplete = onComplete;
		this->onHttpComplete = onHttpComplete;
		this->pUserData = pUserData;
	}
};


//登录，返回用户信息
class SignInData
{
public:
	CC_SYNTHESIZE(STATUS, m_status, Status);

	USER m_user;

	SignInData()
	{
		
	}
	// 从JSON序列化
	void ReadFromJson(CSJson::Value &node)
	{
		CCLog("******************SignInData******************");
		m_status.succeed = node["status"]["succeed"].asUInt();

		CCLog("m_succeed=%d", m_status.succeed);
		if (m_status.succeed == 0)
		{
			m_status.error_code = node["status"]["error_code"].asUInt();
			m_status.error_desc = node["status"]["error_desc"].asString();

			CCLog("m_error_code=%d", m_status.error_code);
			CCLog("m_error_desc=%s", m_status.error_desc.c_str());
		}
		else
		{
			m_user.sid = node["data"]["session"]["sid"].asString();
			m_user.uid = std::atoi(node["data"]["session"]["uid"].asString().c_str());

			m_user.id = std::atoi(node["data"]["user"]["id"].asString().c_str());
			m_user.name = node["data"]["user"]["name"].asString();
			m_user.rank_name = node["data"]["user"]["rank_name"].asString();
			m_user.rank_level = node["data"]["user"]["rank_level"].asUInt();
			m_user.collection_num = std::atoi(node["data"]["user"]["collection_num"].asString().c_str());
			m_user.email = node["data"]["user"]["email"].asString();

			m_user.await_pay = std::atoi(node["data"]["user"]["order_num"]["await_pay"].asString().c_str());
			m_user.await_ship = std::atoi(node["data"]["user"]["order_num"]["await_ship"].asString().c_str());
			m_user.shipped = std::atoi(node["data"]["user"]["order_num"]["shipped"].asString().c_str());
			m_user.finished = std::atoi(node["data"]["user"]["order_num"]["finished"].asString().c_str());

			CCLog("m_sid=%s", m_user.sid.c_str());
			CCLog("m_uid=%d", m_user.uid);
			CCLog("m_id=%d", m_user.id);
			CCLog("m_name=%s", m_user.name.c_str());
			CCLog("m_rank_name=%s", m_user.rank_name.c_str());
			CCLog("m_rank_level=%d", m_user.rank_level);
			CCLog("m_collection_num=%d", m_user.collection_num);
			CCLog("m_email=%s", m_user.email.c_str());
			CCLog("m_await_pay=%d", m_user.await_pay);
			CCLog("m_await_ship=%d", m_user.await_ship);
			CCLog("m_shipped=%d", m_user.shipped);
			CCLog("m_finished=%d", m_user.finished);
		}
	}
};

//注册，返回注册是否合法
class SignUpData
{
public:
	//status
	CC_SYNTHESIZE(STATUS, m_status, Status);

	USER m_user;

	SignUpData()
	{
	}
	// 从JSON序列化
	void ReadFromJson(CSJson::Value &node)
	{
		CCLog("******************SignUpData******************");
		m_status.succeed = node["status"]["succeed"].asUInt();

		CCLog("m_succeed=%d", m_status.succeed);
		if (m_status.succeed == 0)
		{
			m_status.error_code = node["status"]["error_code"].asUInt();
			m_status.error_desc = node["status"]["error_desc"].asString();

			CCLog("m_error_code=%d", m_status.error_code);
			CCLog("m_error_desc=%s", m_status.error_desc.c_str());
		}
		else
		{
			m_user.sid = node["data"]["session"]["sid"].asString();
			m_user.uid = std::atoi(node["data"]["session"]["uid"].asString().c_str());

			m_user.id = std::atoi(node["data"]["user"]["id"].asString().c_str());
			m_user.name = node["data"]["user"]["name"].asString();
			m_user.rank_name = node["data"]["user"]["rank_name"].asString();
			m_user.rank_level = node["data"]["user"]["rank_level"].asUInt();
			m_user.collection_num = std::atoi(node["data"]["user"]["collection_num"].asString().c_str());
			m_user.email = node["data"]["user"]["email"].asString();

			m_user.await_pay = std::atoi(node["data"]["user"]["order_num"]["await_pay"].asString().c_str());
			m_user.await_ship = std::atoi(node["data"]["user"]["order_num"]["await_ship"].asString().c_str());
			m_user.shipped = std::atoi(node["data"]["user"]["order_num"]["shipped"].asString().c_str());
			m_user.finished = std::atoi(node["data"]["user"]["order_num"]["finished"].asString().c_str());

			CCLog("m_sid=%s", m_user.sid.c_str());
			CCLog("m_uid=%d", m_user.uid);
			CCLog("m_id=%d", m_user.id);
			CCLog("m_name=%s", m_user.name.c_str());
			CCLog("m_rank_name=%s", m_user.rank_name.c_str());
			CCLog("m_rank_level=%d", m_user.rank_level);
			CCLog("m_collection_num=%d", m_user.collection_num);
			CCLog("m_email=%s", m_user.email.c_str());
			CCLog("m_await_pay=%d", m_user.await_pay);
			CCLog("m_await_ship=%d", m_user.await_ship);
			CCLog("m_shipped=%d", m_user.shipped);
			CCLog("m_finished=%d", m_user.finished);
		}
	}
};



class CategoryData
{
public:
	//std::string m_id[3];
	std::vector<CATEGORY> m_categorys;
	CategoryData()
	{
		m_categorys.clear();
	}
	// 从JSON序列化
	void ReadFromJson(CSJson::Value &node)
	{
		CSJson::Value &data = node["data"];

		if (data.isArray())
		{
			for (unsigned int i = 0; i < data.size(); ++i)
			{
				CATEGORY category_temp;
				category_temp.id = std::atoi(data[i]["id"].asString().c_str());
				category_temp.name = data[i]["name"].asString();

				CSJson::Value &goods = data[i]["goods"];
				if (goods.isArray())
				{
					for (unsigned int j = 0; j < goods.size(); ++j)
					{
						GOOD good_temp;
						good_temp.id = std::atoi(goods[j]["id"].asString().c_str());
						good_temp.name = goods[j]["name"].asString();
						good_temp.market_price = goods[j]["market_price"].asString();
						good_temp.shop_price = goods[j]["shop_price"].asString();
						good_temp.promote_price = goods[j]["promote_price"].asString();
						good_temp.brief = goods[j]["brief"].asString();
						good_temp.img_small = goods[j]["img"]["small"].asString();
						
						//处理图片
						good_temp.img_url = goods[j]["img"]["url"].asString();
						good_temp.img_thumb = PIC_LOAD(goods[j]["img"]["thumb"].asString().c_str());
						category_temp.goods.push_back(good_temp);
					}
				}
				m_categorys.push_back(category_temp);
			}


		}
	}
};

//商品信息
class GoodData
{
public:
	CC_SYNTHESIZE(STATUS, m_status, Status);
	GOOD m_good;
	GoodData()
	{
	}
	// 从JSON序列化
	void ReadFromJson(CSJson::Value &node)
	{
		m_status.succeed = node["status"]["succeed"].asUInt();

		if (m_status.succeed == 0)
		{
			m_status.error_code = node["status"]["error_code"].asUInt();
			m_status.error_desc = node["status"]["error_desc"].asString();
		}
		else
		{
			m_good.id = std::atoi(node["data"]["id"].asString().c_str());
			m_good.cat_id = std::atoi(node["data"]["cat_id"].asString().c_str());
			m_good.sn = node["data"]["goods_sn"].asString();
			m_good.name = node["data"]["goods_name"].asString();
			m_good.market_price = node["data"]["market_price"].asString();
			m_good.shop_price = node["data"]["shop_price"].asString();
			m_good.integral = node["data"]["integral"].asInt();

			m_good.click_count = std::atoi(node["data"]["click_count"].asString().c_str());
			m_good.brand_id = std::atoi(node["data"]["brand_id"].asString().c_str());
			m_good.goods_number = std::atoi(node["data"]["goods_number"].asString().c_str());
			m_good.goods_weight = node["data"]["goods_weight"].asString();

			//m_good.promote_price = node["data"]["promote_price"].asString();
			m_good.formated_promote_price = node["data"]["formated_promote_price"].asString();
			m_good.promote_start_date = node["data"]["promote_start_date"].asString();
			m_good.promote_end_date = node["data"]["promote_end_date"].asString();
			m_good.is_shipping = std::atoi(node["data"]["is_shipping"].asString().c_str());

			CSJson::Value &properties = node["data"]["properties"];
			if (properties.isArray())
			{
				for (unsigned int i = 0; i < properties.size(); ++i)
				{
					GOOD_PROPERTIE propertie_temp;
					propertie_temp.name = properties[i]["name"].asString();
					propertie_temp.value = properties[i]["value"].asString();
					m_good.properties.push_back(propertie_temp);
				}
			}

			CSJson::Value &pictures = node["data"]["pictures"];
			if (pictures.isArray())
			{
				for (unsigned int i = 0; i < pictures.size(); ++i)
				{
					std::string picture_temp;
					picture_temp = PIC_LOAD(pictures[i]["url"].asString().c_str());
					m_good.pictures.push_back(picture_temp);
				}
			}

			CSJson::Value &rank_prices = node["data"]["rank_prices"];
			if (rank_prices.isArray())
			{
				for (unsigned int i = 0; i < rank_prices.size(); ++i)
				{
					RANK_PRICE rank_prices_temp;
					rank_prices_temp.id = rank_prices[i]["id"].asInt();
					rank_prices_temp.rank_name = rank_prices[i]["rank_name"].asString();
					rank_prices_temp.price = rank_prices[i]["price"].asString();
					m_good.rank_prices.push_back(rank_prices_temp);
				}
			}
		}
	}
};

//搜索数据信息
class SearchData
{
public:
	CC_SYNTHESIZE(std::vector<GOOD>, m_goods, Goods);
	SearchData()
	{
	}
	// 从JSON序列化
	void ReadFromJson(CSJson::Value &node)
	{

		CSJson::Value &data = node["data"];
		if (data.isArray())
		{
			for (unsigned int i = 0; i < data.size(); ++i)
			{
				GOOD good_temp;
				good_temp.id = std::atoi(data[i]["goods_id"].asString().c_str());
				good_temp.name = data[i]["name"].asString();
				good_temp.market_price = data[i]["market_price"].asString();
				good_temp.shop_price = data[i]["shop_price"].asString();
				good_temp.img_thumb = PIC_LOAD(data[i]["img"]["thumb"].asString().c_str());

				m_goods.push_back(good_temp);
			}
		}


	}

};

//购物车列表数据
class CardListData
{
public:
	CC_SYNTHESIZE(std::vector<CART_GOOD>, m_goodLists, GoodLists);
	CC_SYNTHESIZE(CART_TOTAL, m_cartTotal, CartTotal);
	CC_SYNTHESIZE(STATUS, m_status, Status);

	CardListData()
	{
	}
	// 从JSON序列化
	void ReadFromJson(CSJson::Value &node)
	{
		m_status.succeed = node["status"]["succeed"].asUInt();

		if (m_status.succeed == 0)
		{
			m_status.error_code = node["status"]["error_code"].asUInt();
			m_status.error_desc = node["status"]["error_desc"].asString();
		}
		else
		{
			CSJson::Value &goods_list = node["data"]["goods_list"];
			if (goods_list.isArray())
			{
				for (unsigned int i = 0; i < goods_list.size(); ++i)
				{
					CART_GOOD good_temp;
					good_temp.rec_id = std::atoi(goods_list[i]["rec_id"].asString().c_str());
					good_temp.goods_id = std::atoi(goods_list[i]["goods_id"].asString().c_str());
					good_temp.goods_sn = goods_list[i]["goods_sn"].asString();
					good_temp.goods_name = goods_list[i]["goods_name"].asString();


					good_temp.market_price = goods_list[i]["market_price"].asString();
					good_temp.goods_price = goods_list[i]["goods_price"].asString();
					good_temp.goods_number = std::atoi(goods_list[i]["goods_number"].asString().c_str());
					good_temp.is_real = std::atoi(goods_list[i]["is_real"].asString().c_str());
					good_temp.extension_code = goods_list[i]["extension_code"].asString();
					good_temp.parent_id = std::atoi(goods_list[i]["parent_id"].asString().c_str());
					good_temp.pid = std::atoi(goods_list[i]["pid"].asString().c_str());
					good_temp.subtotal = goods_list[i]["subtotal"].asString();
					good_temp.goods_attr_id = goods_list[i]["goods_attr_id"].asString();

					good_temp.img_thumb = PIC_LOAD(goods_list[i]["img"]["thumb"].asString().c_str());

					m_goodLists.push_back(good_temp);
				}
			}

			m_cartTotal.goods_price = node["data"]["total"]["goods_price"].asString();
			m_cartTotal.market_price = node["data"]["total"]["market_price"].asString();
			m_cartTotal.saving = node["data"]["total"]["saving"].asString();
			m_cartTotal.save_rate = node["data"]["total"]["save_rate"].asString();
			m_cartTotal.goods_amount = std::atoi(node["data"]["total"]["goods_amount"].asString().c_str());
			m_cartTotal.real_goods_count = std::atoi(node["data"]["total"]["real_goods_count"].asString().c_str());
			m_cartTotal.virtual_goods_count = std::atoi(node["data"]["total"]["virtual_goods_count"].asString().c_str());
		}
	}

};

//个人中心相关数据
class ProfileData
{
public:
	CC_SYNTHESIZE(USER, m_user, User);

	ProfileData()
	{
	}
	// 从JSON序列化

	void ReadFromJson(CSJson::Value &node)
	{
		m_user.id = std::atoi(node["data"]["user"]["id"].asString().c_str());
		m_user.name = node["data"]["user"]["name"].asString();
		m_user.rank_name = node["data"]["user"]["rank_name"].asString();
		m_user.rank_level = node["data"]["user"]["rank_level"].asUInt();
		m_user.collection_num = std::atoi(node["data"]["user"]["collection_num"].asString().c_str());
		m_user.email = node["data"]["user"]["email"].asString();

		m_user.await_pay = std::atoi(node["data"]["user"]["order_num"]["await_pay"].asString().c_str());
		m_user.await_ship = std::atoi(node["data"]["user"]["order_num"]["await_ship"].asString().c_str());
		m_user.shipped = std::atoi(node["data"]["user"]["order_num"]["shipped"].asString().c_str());
		m_user.finished = std::atoi(node["data"]["user"]["order_num"]["finished"].asString().c_str());

	}

};


//收货地址列表
class AddressListData
{
public:
	CC_SYNTHESIZE(std::vector<ADDRESS>, m_addressList, AddressList);
	CC_SYNTHESIZE(STATUS, m_status, Status);

	AddressListData()
	{
	}

	// 从JSON序列化
	void ReadFromJson(CSJson::Value &node)
	{

	}
};


// 论坛数据库
class ShopDB : public CAObject
{
public:
	static ShopDB *m_pInstance;
	//USER m_userData;

	CC_SYNTHESIZE(USER, m_user, User);

	void HttpRequest(std::string url, const char *postData,CAObject *pTarget, SEL_ShopDBOnComplete onComplete, SEL_ShopDBOnHttpComplete onHttpComplete, void *pUserData = NULL, int nThread = 0);
	void HttpFinished(CCHttpClient* client, CCHttpResponse* response);

public:
	ShopDB();
	~ShopDB();
	static ShopDB* Instance();
	static void Release();
	std::string GetUrlHeader();
	//登录
	void SignIn(CAObject *pTarget, SEL_ShopDBOnComplete onComplete, std::string userName,std::string passWord);
	void SignInFinished(ShopDBHttpRequest *pRequest, CSJson::Value *pJson);
	//注册
	void SignUp(CAObject *pTarget, SEL_ShopDBOnComplete onComplete, std::string userName, std::string passWord, std::string email);
	void SignUpFinished(ShopDBHttpRequest *pRequest, CSJson::Value *pJson);

	//首页展示商品信息
	void Category(CAObject *pTarget, SEL_ShopDBOnComplete onComplete);
	void CategoryFinished(ShopDBHttpRequest *pRequest, CSJson::Value *pJson);

	//显示商品页
	void Goods(CAObject *pTarget, SEL_ShopDBOnComplete onComplete, unsigned int goods_id, unsigned int uid, std::string sid);
	void GoodsFinished(ShopDBHttpRequest *pRequest, CSJson::Value *pJson);

	//搜索页相关
	void Search(CAObject *pTarget, SEL_ShopDBOnComplete onComplete, std::string keywords, unsigned int category_id, std::string sort_by, unsigned int count=100);
	void SearchFinished(ShopDBHttpRequest *pRequest, CSJson::Value *pJson);

	//购物车列表
	void CartList(CAObject *pTarget, SEL_ShopDBOnComplete onComplete, unsigned int uid, std::string sid);
	void CartListFinished(ShopDBHttpRequest *pRequest, CSJson::Value *pJson);

	//个人信息读取
	void Profile(CAObject *pTarget, SEL_ShopDBOnComplete onComplete, unsigned int uid, std::string sid);
	void ProfileFinished(ShopDBHttpRequest *pRequest, CSJson::Value *pJson);

	//收货地址列表读取
	void AddressList(CAObject *pTarget, SEL_ShopDBOnComplete onComplete, unsigned int uid, std::string sid);
	void AddressListFinished(ShopDBHttpRequest *pRequest, CSJson::Value *pJson);


	//void OpenLogin(CAObject *pTarget, SEL_ShopDBOnComplete onComplete, std::string userName, std::string passWord);
	//void OpenLoginFinished(ShopDBHttpRequest *pRequest, CSJson::Value *pJson);


	//// 打开搜索
	//void Search(std::string strSearchKey, std::string strSearchType, CCObject *pTarget, SEL_BookDBOnComplete onComplete);
	//void SearchFinished(BookDBHttpRequest *pRequest, CSJson::Value *pJson);

	//// 打开图书简介
	//void GetBookInfo(BookData *pBook, CCObject *pTarget, SEL_BookDBOnComplete onComplete);
	//void GetBookInfoFinished(BookDBHttpRequest *pRequest, CSJson::Value *pJson);

	//// 打开目录
	//void GetBookMenu(BookData *pBook, CCObject *pTarget, SEL_BookDBOnComplete onComplete);
	//int GetBookMenuDownloadStatus(BookData *pBook, int menu);
	//int GetBookMenuReadStatus(BookData *pBook, int menu);
	//void GetBookMenuFinished(BookDBHttpRequest *pRequest, CSJson::Value *pJson);

	//// 下载图书
	//void DownloadBook(BookData *pBook, int start_menu, int end_menu, CCObject *pTarget, SEL_BookDBOnComplete onComplete);
	//void DownloadBookFinished(BookDBHttpRequest *pRequest, CSJson::Value *pJson);

	//// 阅读图书
	//void ReadBook(BookData *pBook, int menu, CCObject *pTarget, SEL_BookDBOnComplete onComplete);
	//void ReadBookFinished(BookDBHttpRequest *pRequest, CSJson::Value *pJson);

	//// 删除图书
	//void DeleteBook(BookData *pBook);

	//// 获得阅读过的图书
	//std::vector<BookData> GetLastReadBook();
	//bool FindLastReadBook(BookData *pOut, std::string strBookKey);
	//void AddLastReadBook(BookData *pData);
	//bool FindStorage(std::string strBookKey, BookData *pOut);
	//bool FindStorageBookData(BookData *pBook, CSJson::Value *pOut);
	//std::vector<BookData> GetStorage();
	//int GetDownloadingNum(){ return (int)m_mapDownloading.size(); }
	//int GetDownloadingMaxNum(){ return m_nDownloadingMaxNum; }

};


#endif