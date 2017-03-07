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
		str = "‚â‚­(‚É‚½‚¿‚»‚¤‚È)‚­‚³";
		break;
	case 3:
		str = "´‚ç‚©‚È…";
		break;
	case 4:
		str = "‚¯‚Ş‚èƒ_ƒ}";
		break;
	case 5:
		str = "¢ŠE÷‚Ìƒn";
		break;
	case 9:
		str = "‚È‚É‚à‚È‚¢";
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