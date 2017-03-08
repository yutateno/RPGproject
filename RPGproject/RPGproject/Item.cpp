#include "Item.h"

Item::Item()
{
	ID = 0;
	name = SearchName(ID);
	price = SearchPrice(ID);
	effectText[0] = SearchEffectText(ID, false);
	effectText[1] = SearchEffectText(ID, true);
}
Item::Item(int ID)
{
	this->ID = ID;
	name = SearchName(ID);
	price = SearchPrice(ID);
	effectText[0] = SearchEffectText(ID, false);
	effectText[1] = SearchEffectText(ID, true);
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
		str = "��";
		break;
	case 1:
		str = "test_item";
		break;
	case 2:
		str = "�₭(�ɂ���������)����";
		break;
	case 3:
		str = "���炩�Ȑ�";
		break;
	case 4:
		str = "���ނ�_�}";
		break;
	case 5:
		str = "���E���̃n";
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
string Item::SearchEffectText(int ID, bool effected)
{
	string str;
	// ���ʕ�
	if (effected)
	{
		switch (ID)
		{
		case 0:
			str = "����͎g�p�ł��Ȃ�";
			break;
		case 1:
			str = "�e�X�g����";
			break;
		case 2:
			str = "HP�������񕜂���";
			break;
		case 3:
			str = "HP�����������񕜂���";
			break;
		case 4:
			str = "���Ȃ��͉��ɕ�܂ꂽ�E�E�E";
			break;
		case 5:
			str = "�K���ȋC���ɂȂ���";
			break;
		default:
			break;
		}
	}
	// ������
	else
	{
		switch (ID)
		{
		case 0:
			str = "�����ɂ͉����Ȃ�";
			break;
		case 1:
			str = "����̓e�X�g�p�̃A�C�e���ł�";
			break;
		case 2:
			str = "HP���񕜂������ȑ�";
			break;
		case 3:
			str = "�������ȏ㐅�f���ȉ�";
			break;
		case 4:
			str = "�q���ɑ�l�C";
			break;
		case 5:
			str = "���҂𐶂��Ԃ点�����ȗt����";
			break;
		default:
			break;
		}
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
int Item::GetPrice()
{
	return price;
}
string Item::GetEffectText(bool effected)
{
	if (effected)
	{
		return effectText[1];
	}
	else
	{
		return effectText[0];
	}
}