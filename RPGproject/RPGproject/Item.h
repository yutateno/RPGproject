#pragma once

#include <string>

using std::string;

class Item
{
private:
	int ID;				// 管理番号
	string name;		// 名前
	int price;			// 値段

public:
	Item();
	Item(int ID);
	~Item();

	string SearchName(int ID);		// 管理番号から名前を検索する関数
	int SearchPrice(int ID);		// 管理番号から値段を検索する関数

	// ゲッターセッター
	string GetName();
	int GetID();
};