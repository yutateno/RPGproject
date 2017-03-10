#pragma once

#include <string>

using std::string;

class Item
{
private:

public:
	int ID;						// 管理番号
	string name;				// 名前
	int price;					// 値段
	string effectText[2];		// 効果のテキスト

	Item();
	Item(int ID);
	~Item();

	static string SearchName(int ID);						// 管理番号から名前を検索する関数
	static int SearchPrice(int ID);							// 管理番号から値段を検索する関数
	static string SearchEffectText(int ID, bool effected);	// 管理番号から効果を検索する関数
};