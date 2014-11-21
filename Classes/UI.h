//****************************************
//CrossShop  Demo0.01
//QQ£º896793747
//****************************************
#ifndef __CrossShop__UI__
#define __CrossShop__UI__

#include <iostream>
#include "CrossApp.h"

USING_NS_CC;

#define VIEW_BOTTOM_Y(z) z->getBounds().size.height + z->getFrameOrigin().y
#define VIEW_RIGHT_X(z) z->getBounds().size.width+z->getFrameOrigin().x

static const CAColor4B MiniColor_bg = { 237, 237, 237, 225 };
static const CAColor4B MiniColor_font1 = { 52, 52, 52, 255 };
static const CAColor4B MiniColor_font2 = { 58, 58, 58, 255 };

class UI
{
public:
	//³¤ÌõtextFild¿Ø¼þ
	static CATextField *longTextField(CCRect Rect, std::string placeHolder);
	static CAButton *longButton(CCRect Rect, std::string title);
	static CAButton *blueButton(CCRect Rect, std::string title);
	static CAScale9ImageView *whitePlane(CCRect Rect);

	static float getBottomY(CAView *view);
	static float getRightX(CAView *view);
};

class ProductShowView : public CAScale9ImageView
{
public:
	static ProductShowView *create(CCRect Rect);

	CC_SYNTHESIZE_READONLY(CAButton *, m_pClassBtn, ClassBtn);
	CC_SYNTHESIZE_READONLY(CAButton *, m_pBtn1, Btn1);
	CC_SYNTHESIZE_READONLY(CAButton *, m_pBtn2, Btn2);

	CC_SYNTHESIZE_READONLY(CAImageView *, m_pClassImg, ClassImg);
	CC_SYNTHESIZE_READONLY(CAImageView *, m_pImg1, Img1);
	CC_SYNTHESIZE_READONLY(CAImageView *, m_pImg2, Img2);

	CC_SYNTHESIZE_READONLY(CALabel *, m_pClassLabel, ClassLabel);
	CC_SYNTHESIZE_READONLY(CALabel *, m_pLabel1, Label1);
	CC_SYNTHESIZE_READONLY(CALabel *, m_pLabel2, Label2);

	CC_SYNTHESIZE_READONLY(CALabel *, m_pLabel1_price, Label1_price);
	CC_SYNTHESIZE_READONLY(CALabel *, m_pLabel2_price, Label2_price);

private:
	virtual bool init(CCRect Rect);
	/*virtual*/ 
};

class InfoPromptView : public CAImageView
{
public:
	static InfoPromptView *create(CCPoint point);
	void setText(std::string text);

private:
	virtual bool init(CCPoint point);
	CALabel *m_prompText;

};


#endif /* defined(__CrossShop__UI__) */