#include "Treasure.h"

Treasure::Treasure()
{

}
Treasure::Treasure(int ID)
{
	// 画像
	Graph = LoadGraph("img\\treasure.png");

	// ステータス
	this->ID = ID;
	Initialize();
}
Treasure::~Treasure()
{
	// 画像削除
	// DeleteGraph(Graph);
}

void Treasure::Initialize()
{
	// ファイルオープン
	ifstream ifs("img\\treasure.csv");

	// マップデータ読み込み失敗
	if (!ifs)
	{
		// エラー
		return;
	}

	// 仮置き
	string str = "";
	int treasure[6] = { 0,0,0,0,0,0 };

	while (getline(ifs, str))
	{
		// ID合致ならステータス代入

		// 仮置き
		int i = 0;
		string token = "";
		istringstream stream(str);

		while (getline(stream, token, ','))
		{
			// 再検索
			if (i == 0 && !(stoi(token) == ID))
			{
				break;
			}

			// 代入してカウントアップ
			treasure[i] = stoi(token);
			i++;
		}

		// 検索終了
		if (i != 0)
		{
			// 各ステータス代入して終了
			open	= (bool)treasure[1];
			X		= treasure[2];
			Y		= treasure[3];
			itemID	= treasure[4];
			money	= treasure[5];
			break;
		}
	}
}

void Treasure::Opened()
{
	// 出力処理
}

void Treasure::Draw(int cameraX, int cameraY)
{
	// 空いていたら
	if (open)
	{
		DrawGraph(X - cameraX, Y - cameraY, Graph, true);
	}
	// 空いていなかったら
	else
	{
		DrawGraph(X - cameraX, Y - cameraY, Graph, true);
	}
}

int Treasure::GetID()
{
	return ID;
}
bool Treasure::GetOpen()
{
	return open;
}
int Treasure::GetX()
{
	return X;
}
int Treasure::GetY()
{
	return Y;
}
int Treasure::GetItemID()
{
	return itemID;
}
int Treasure::GetMoney()
{
	return money;
}