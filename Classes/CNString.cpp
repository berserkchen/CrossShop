//****************************************
//CrossShop  Demo0.01
//QQ£º896793747
//****************************************
#include "CNString.h"

static CNString *cnString = new  CNString();

CNString::CNString()
{
	xmlDoc.LoadFile("xml/CN_String.xml");
}


CNString* CNString::shareCNString()
{
		return cnString;
}

string CNString::getCNString(string st)
{
	tinyxml2::XMLElement *scene = xmlDoc.RootElement();
	tinyxml2::XMLElement *node = scene->FirstChildElement("node");
	CCString xmlSring = node->FirstChildElement(st.c_str())->GetText();
	
	return xmlSring.getCString();
}
