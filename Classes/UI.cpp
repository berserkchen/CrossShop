//****************************************
//CrossShop  Demo0.01
//QQ£º896793747
//****************************************
#include "UI.h"
#include "CNString.h"

float UI::getBottomY(CAView *view)
{
	return view->getBounds().size.height + view->getFrameOrigin().y;
}

float UI::getRightX(CAView *view)
{
	return view->getBounds().size.width + view->getFrameOrigin().x;
}

CATextField *UI::longTextField(CCRect Rect, std::string placeHolder)
{
	CATextField *pTextField = CATextField::createWithCenter(Rect);
	pTextField->setFontSize(25);
	pTextField->setPlaceHolder(placeHolder);
	return pTextField;
}

CAButton *UI::longButton(CCRect Rect, std::string title)
{
	CAButton *pButton = CAButton::createWithCenter(Rect, CAButtonTypeSquareRect);

	pButton->setBackGroundViewForState(CAControlStateNormal, CAScale9ImageView::createWithImage(CAImage::create("source_material/item_box_bg.png")));
	pButton->setBackGroundViewForState(CAControlStateHighlighted, CAScale9ImageView::createWithImage(CAImage::create("source_material/item_box_highlighted.png")));
	pButton->setTitleColorForState(CAControlStateNormal, CAColor_white);
	
	CALabel *pLabel = CALabel::createWithCenter(CCRect(_px(150 + 20), Rect.size.height / 2, _px(300), _px(20)));
	pLabel->setText(title);
	pLabel->setFontSize(_px(20));
	pLabel->setColor(MiniColor_font1);
	pButton->addSubview(pLabel);

	CAImageView *pImg = CAImageView::createWithCenter(CCRect(Rect.size.width - 30, Rect.size.height / 2, _px(12), _px(20)));
	pImg->setImage(CAImage::create("source_material/arrow_right.png"));
	pButton->addSubview(pImg);
	return pButton;
}

CAButton *UI::blueButton(CCRect Rect, std::string title)
{
	CAButton *pButton = CAButton::createWithCenter(Rect, CAButtonTypeSquareRect);
	pButton->setTitleForState(CAControlStateAll, title);
	pButton->setTitleColorForState(CAControlStateAll,CAColor_white);
	pButton->setBackGroundViewForState(CAControlStateNormal, CAScale9ImageView::createWithImage(CAImage::create("source_material/btn_rounded3D_normal.png")));
	pButton->setBackGroundViewForState(CAControlStateHighlighted, CAScale9ImageView::createWithImage(CAImage::create("source_material/btn_rounded3D_highlighted.png")));
	return pButton;
}

CAScale9ImageView *UI::whitePlane(CCRect Rect)
{
	CAScale9ImageView *pImgView = CAScale9ImageView::createWithCenter(Rect);
	pImgView->setImage(CAImage::create("source_material/item_box_bg.png"));
	return pImgView;
}

ProductShowView *ProductShowView::create(CCRect Rect)
{
	ProductShowView *pProductShowView = new ProductShowView();
	if (pProductShowView&&pProductShowView->init(Rect))
	{
		return pProductShowView;
	}
	CC_SAFE_DELETE(pProductShowView);
	return NULL;
}

bool ProductShowView::init(CCRect Rect)
{
	this->setFrame(Rect);
	this->setImage(CAImage::create("source_material/item_box_bg.png"));

	CAScale9ImageView *pLine1 = CAScale9ImageView::createWithCenter(CCRect(Rect.size.width / 2, Rect.size.height / 2, 2, Rect.size.height/20*19));
	pLine1->setImage(CAImage::create("source_material/indicator.png"));
	this->addSubview(pLine1);

	CAScale9ImageView *pLine2 = CAScale9ImageView::createWithFrame(CCRect(Rect.size.width / 2, Rect.size.height / 2, Rect.size.width / 2/20 * 19, 2));
	pLine2->setImage(CAImage::create("source_material/indicator.png"));
	this->addSubview(pLine2);

	m_pClassLabel = CALabel::createWithFrame(CCRect(10, 15, 100, 25));
	//m_pClassLabel->setText(title);
	m_pClassLabel->setFontSize(25);
	this->addSubview(m_pClassLabel);

	m_pClassImg = CAImageView::createWithFrame(CCRect(20, 50, 280, 280));
	this->addSubview(m_pClassImg);

	m_pLabel1 = CALabel::createWithFrame(CCRect(Rect.size.width / 2 + 20, 15, 200, 20));
	/*m_pLabel1->setText(title);*/
	m_pLabel1->setFontSize(20);
	this->addSubview(m_pLabel1);

	m_pLabel1_price = CALabel::createWithFrame(CCRect(Rect.size.width / 2 + 20, 45, 100, 20));
	m_pLabel1_price->setFontSize(20);
	m_pLabel1_price->setColor(CAColor_red);
	this->addSubview(m_pLabel1_price);

	m_pLabel2 = CALabel::createWithFrame(CCRect(Rect.size.width / 2 + 20, Rect.size.height / 2 + 15, 200, 20));
	m_pLabel2->setFontSize(20);
	this->addSubview(m_pLabel2);

	m_pLabel2_price = CALabel::createWithFrame(CCRect(Rect.size.width / 2 + 20, Rect.size.height / 2 + 45, 100, 20));
	m_pLabel2_price->setFontSize(20);
	m_pLabel2_price->setColor(CAColor_red);
	this->addSubview(m_pLabel2_price);

	m_pImg1 = CAImageView::createWithFrame(CCRect(Rect.size.width - 150, 10+35, 130, 130));
	this->addSubview(m_pImg1);

	m_pImg2 = CAImageView::createWithFrame(CCRect(Rect.size.width - 150, Rect.size.height / 2 + 10 + 35, 130, 130));
	this->addSubview(m_pImg2);

	m_pClassBtn = CAButton::createWithFrame(CCRect(0, 0, Rect.size.width / 2, Rect.size.height), CAButtonTypeCustom);
	this->addSubview(m_pClassBtn);
	m_pBtn1 = CAButton::createWithFrame(CCRect(Rect.size.width / 2, 0, Rect.size.width / 2, Rect.size.height / 2), CAButtonTypeCustom);
	this->addSubview(m_pBtn1);
	m_pBtn2 = CAButton::createWithFrame(CCRect(Rect.size.width / 2, Rect.size.height / 2, Rect.size.width / 2, Rect.size.height / 2), CAButtonTypeCustom);
	this->addSubview(m_pBtn2);

	return true;
}

InfoPromptView *InfoPromptView::create(CCPoint point)
{
	InfoPromptView *pInfoPromptView = new InfoPromptView();
	if (pInfoPromptView&&pInfoPromptView->init(point))
	{
		return pInfoPromptView;
	}
	CC_SAFE_DELETE(pInfoPromptView);
	return NULL;
}

bool InfoPromptView::init(CCPoint point)
{
	this->setCenter(CCRect(point.x, point.y,_px(32),_px(32)));
	this->setImage(CAImage::create("source_material/info_Prompt.png"));

	m_prompText = CALabel::createWithCenter(CCRect(this->getBounds().size.width / 2, this->getBounds().size.height / 2, _px(50), _px(20)));
	m_prompText->setColor(CAColor_white);
	m_prompText->setFontSize(_px(20));
	m_prompText->setTextAlignment(CATextAlignmentCenter);
	this->addSubview(m_prompText);
	return true;
}

void InfoPromptView::setText(std::string text)
{
	m_prompText->setText(text);
}