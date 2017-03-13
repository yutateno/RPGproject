#include "Treasure.h"

Treasure::Treasure()
{

}
Treasure::Treasure(int ID)
{
	// 画像
	closeGraph = LoadGraph("treasure\\treasure.png");
	openGraph = LoadGraph("treasure\\treasure.png");

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
	ifstream ifs("treasure\\treasure.csv");

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

void Treasure::OpenProcess()
{
	// ----------------------------------------
	// ファイル処理ここから

	// 読み込みとそのチェック
	ifstream ifs("origin\\treasure.csv");
	if (!ifs)
	{
		return;
	}

	// 出力ファイル
	ofstream ofs("treasure\\treasure.csv");

	// 仮置き
	string treasure[6];
	string str;

	// ファイル置き換え
	for (int i = 0;i < ID;i++)
	{
		getline(ifs, str);
		ofs << str << endl;
	}
	getline(ifs, str);
	ofs << ID << "," << 1 << "," << X << "," << Y << "," << 0 << "," << 0 << endl;
	while (getline(ifs, str))
	{
		ofs << str << endl;
	}

	// ファイルを閉じる
	ifs.close();
	ofs.close();

	// 仮素材破棄
	for (int i = 0;i < 5;i++)
	{
		treasure[i].clear();
	}
	str.clear();

	// ファイル処理ここから
	// ----------------------------------------
	

	// 内部処理
	open = true;
	itemID = 0;
	money = 0;
}

void Treasure::Draw(int cameraX, int cameraY)
{
	// 空いていたら
	if (open)
	{
		DrawGraph(X - cameraX, Y - cameraY, openGraph, true);
	}
	// 空いていなかったら
	else
	{
		DrawGraph(X - cameraX, Y - cameraY, closeGraph, true);
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