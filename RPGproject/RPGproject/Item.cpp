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
		str = "ñ≥";
		break;
	case 1:
		str = "test_item";
		break;
	case 2:
		str = "Ç‚Ç≠(Ç…ÇΩÇøÇªÇ§Ç»)Ç≠Ç≥";
		break;
	case 3:
		str = "ê¥ÇÁÇ©Ç»êÖ";
		break;
	case 4:
		str = "ÇØÇﬁÇËÉ_É}";
		break;
	case 5:
		str = "ê¢äEé˜ÇÃÉn";
		break;
	default:
		break;
	}

	return str;
}
int Item::SearchPrice(int ID)
{
	int priceForID;
	switch (ID)
	{
	case 0:
		priceForID = 0;
		break;
	case 1:
		priceForID = 10;
		break;
	case 2:
		priceForID = 20;
		break;
	case 3:
		priceForID = 30;
		break;
	case 4:
		priceForID = 40;
		break;
	case 5:
		priceForID = 50;
		break;
	default:
		break;
	}

	return priceForID;
}

string Item::GetName()
{
	return name;
}

int Item::GetID()
{
	return ID;
}