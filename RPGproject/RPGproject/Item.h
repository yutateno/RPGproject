#pragma once

#include <string>

using std::string;

class Item
{
private:
	int ID;				// 管理番号
	string name;		// 名前

public:
	Item();
	Item(int ID);
	~Item();

	string SearchName(int ID);		// 管理番号から名前を検索する関数

	// ゲッターセッター
	string GetName();
};