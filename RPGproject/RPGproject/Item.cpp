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
		str = "無";
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
	default:
		break;
	}

	return str;
}

string Item::GetName()
{
	return name;
}

int Item::GetID()
{
	return ID;
}