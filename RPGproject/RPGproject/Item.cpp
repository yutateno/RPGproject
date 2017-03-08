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
	// 効果文
	if (effected)
	{
		switch (ID)
		{
		case 0:
			str = "これは使用できない";
			break;
		case 1:
			str = "テスト成功";
			break;
		case 2:
			str = "HPが少し回復した";
			break;
		case 3:
			str = "HPがそこそこ回復した";
			break;
		case 4:
			str = "あなたは煙に包まれた・・・";
			break;
		case 5:
			str = "幸せな気分になった";
			break;
		default:
			break;
		}
	}
	// 説明文
	else
	{
		switch (ID)
		{
		case 0:
			str = "そこには何もない";
			break;
		case 1:
			str = "これはテスト用のアイテムです";
			break;
		case 2:
			str = "HPが回復しそうな草";
			break;
		case 3:
			str = "水道水以上水素水以下";
			break;
		case 4:
			str = "子供に大人気";
			break;
		case 5:
			str = "死者を生き返らせそうな葉っぱ";
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