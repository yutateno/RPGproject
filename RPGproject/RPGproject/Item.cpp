#include "Item.h"

Item::Item()
{
	ID = 0;
	name = SearchName(ID);
}
Item::Item(int ID)
{
	this->ID = ID;
	name = SearchName(ID);
}
Item::~Item()
{

}

string Item::SearchName(int ID)
{
	string str;
	switch (ID)
	{
	case 0:
		str = "no_items";
		break;
	case 1:
		str = "test_item";
		break;
	case 2:
		str = "やく(にたちそうな)くさ";
		break;
	case 3:
		str = "清らかな水";
		break;
	case 4:
		str = "けむりダマ";
		break;
	case 5:
		str = "世界樹のハ";
		break;
	case 9:
		str = "なにもない";
		break;
	default:
		break;
	}

	return str;
}

string Item::GetName()
{
	return name;
}