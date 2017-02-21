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
	default:
		break;
	}

	return str;
}

string Item::GetName()
{
	return name;
}