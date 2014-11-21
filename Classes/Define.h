//****************************************
//CrossShop  Demo0.01
//QQ：896793747
//****************************************
#ifndef __CrossShop__Define__
#define __CrossShop__Define__
#include <list>
#include "CrossApp.h"

USING_NS_CC;

//用户数据结构
typedef struct user
{
	//session
	std::string sid;
	unsigned int uid;

	//user
	unsigned int id;
	std::string name;
	std::string rank_name;
	unsigned int rank_level;
	unsigned int collection_num;
	std::string email;

	//order_num
	unsigned int await_pay, await_ship, shipped, finished;

}USER;

//商品详情
typedef struct Good_Propertie
{
	std::string name;
	std::string value;
}GOOD_PROPERTIE;

//价格分级
typedef struct Rank_Price
{
	unsigned int id;
	std::string rank_name;
	std::string price;
}RANK_PRICE;

//商品信息
typedef struct Good
{
	//首页可读取信息
	unsigned int id;
	std::string name;
	std::string market_price;
	std::string shop_price;
	std::string promote_price;
	std::string img_thumb;
	std::string img_url;
	std::string img_small;
	std::string brief;

	//具体商品页信息
	unsigned int cat_id;
	std::string sn;
	unsigned int collected;
	int integral;
	unsigned int click_count;
	unsigned int brand_id;
	unsigned int goods_number;
	std::string goods_weight;
	std::string formated_promote_price;
	std::string promote_start_date;
	std::string promote_end_date;
	unsigned int is_shipping;
	std::vector<std::string> pictures;
	std::vector<RANK_PRICE> rank_prices;
	std::vector<GOOD_PROPERTIE> properties;
}GOOD;

//商品分类
typedef struct Category
{
	unsigned int id;
	std::string name;
	std::vector<GOOD> goods;
}CATEGORY;

//购物车商品信息
typedef struct Cart_Good
{
	unsigned int rec_id;
	unsigned int goods_id;
	std::string goods_sn;
	std::string goods_name;
	std::string market_price;
	std::string goods_price;
	unsigned int goods_number;
	unsigned int is_real;
	std::string extension_code;
	unsigned int parent_id;
	unsigned int is_shipping;
	unsigned int pid;
	std::string subtotal;
	std::string img_thumb;
	std::string goods_attr_id;
}CART_GOOD; 


//购物车总计
typedef struct Cart_Total
{
	std::string goods_price;
	std::string market_price;
	std::string saving;
	std::string save_rate;
	unsigned int goods_amount;
	unsigned int real_goods_count;
	unsigned int virtual_goods_count;
}CART_TOTAL;


//邮寄地址
typedef struct Address
{
	//简单信息
	unsigned int id;
	std::string consignee;	//姓名
	std::string address;
	std::string country_name;
	std::string province_name;
	std::string city_name;
	std::string district_name;
	unsigned int real_goods_count;
	unsigned int virtual_goods_count;
	unsigned int default_address;	//默认地址

	//详细信息
	std::string email;
	std::string zipcode;
	std::string mobile;
	std::string sign_building;
	std::string best_time;
	std::string tel;

	unsigned int country_id;
	unsigned int province_id;
	unsigned int city_id;
	unsigned int district_id;
}ADDRESS;

//状态信息
typedef struct Status
{
	unsigned int succeed;
	unsigned int error_code;
	std::string error_desc;
}STATUS;



#endif