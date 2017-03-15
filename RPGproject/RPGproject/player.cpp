#include "player.h"

Player::Player()
{
	// ステータスたち
	name = "pine";
	lv = 1;
	exp = 0;
	maxHP = 10;
	hp = 10;
	maxMP = 10;
	mp = 10;
	x = 320 - 16;
	preX = x;
	drawX = x;
	y = 240 - 16;
	preY = y;
	drawY = y;
	direction = DOWN;
	speed = 2;
	itemMax = 9;
	for (int i = 0;i < itemMax;i++)
	{
		item[i] = new Item();
	}
	ID = 0;
	money = 500;

	attack = new Attack();
	attack->power = 1;
	attack->width = 0;

	// メニュー関係
	ChoiseNum = 0;			// 項目の数
	// メニュー
	menuFlag = false;		// メニューを開いているかどうか
	menuWidth = 96;			// 高さ
	menuHeight = 48;		// 幅
	menuX = 0;				// 座標
	menuY = 0;				// 座標
	menuChoiceNum = 2;		// 項目の数
	// ステータス
	statusWidth = 112;		// ステータスの幅
	statusHeight = 96;		// ステータスの高さ
	statusX = 0;			// ステータスの座標
	statusY = 480 - statusHeight;		// ステータスの座標
	// アイテム画面
	itemFlag = false;		// アイテム画面を開いているかどうか
	itemUseFlag = false;	// アイテムを使っているかどうか
	itemWidth = 192;		// 高さ
	itemHeight = 176;		// 幅
	itemX = menuX + menuWidth;			// 座標
	itemY = 0;				// 座標
	itemChoiseNum = 10;
	// 説明枠
	descriptionWidth = 320;	// 幅
	descriptionHeight = 32;	// 高さ
	descriptionX = itemX;	// 座標
	descriptionY = itemY + itemHeight;	// 座標
	// ログ
	logX = statusX + statusWidth;		// 座標
	logWidth = 640 - logX;	// 幅
	logHeight = 96;			// 高さ
	logY = 480 - logHeight;	// 座標
	// カーソル
	cursorX = 0;			// 相対座標
	cursorY = 0;			// 相対座標
	
	// 画像読み込み
	graph = LoadGraph("img\\player.png");
}
Player::~Player()
{
	// 画像のデータ削除
	DeleteGraph(graph);
}

void Player::aaaDraw()
{
	// プレイヤー本体
	DrawGraph(320 - 16, 240 - 16, graph, true);
}
void Player::aaaDraw(int mapwidth, int mapheight)
{
	// プレイヤー本体とマップの兼ね合いを考えた描画パターン
	if (x < 320 - 16)
	{
		drawX = x;
	}
	else if (x > (mapwidth * 32 - 32) - (320 - 16))
	{
		drawX = x - (mapwidth * 32 - 640);
	}
	else
	{
		drawX = 320 - 16;
	}

	if (y < 240 - 16)
	{
		drawY = y;
	}
	else if (y >(mapheight * 32 - 32) - (240 - 16))
	{
		drawY = y - (mapheight * 32 - 480);
	}
	else
	{
		drawY = 240 - 16;
	}
	// プレイヤー本体
	DrawGraph(drawX, drawY, graph, true);

	// メニュー画面
	if (menuFlag)
	{
		// メニュー
		Textbox::Draw(menuX, menuY, menuWidth, menuHeight, "　アイテム\n　もどる");
		// ステータス
		Textbox::Draw(statusX, statusY, statusWidth, statusHeight,
			name + "\n" +
			"HP:" + std::to_string(hp) + " / " + std::to_string(maxHP) + "\n" +
			"MP:" + std::to_string(mp) + " / " + std::to_string(maxMP) + "\n" +
			"LV:" + std::to_string(lv));

		// カーソル
		DrawFormatString(8 + cursorX, 8 + cursorY * 16, WHITE, "▼");
		// アイテム画面
		if (itemFlag)
		{
			// 背景
			Textbox::Draw(itemX, itemY, itemWidth, itemHeight, "");
			// 文字
			for (int i = 0, n = itemMax;i < n;i++)
			{
				Textbox::Draw(itemX, itemY + (i * 16), "　" + item[i]->name);
			}
			Textbox::Draw(itemX, itemY + (itemChoiseNum - 1) * 16, "　もどる");
			// 説明
			if (cursorY < itemMax)
			{
				Textbox::Draw(descriptionX, descriptionY, descriptionWidth, descriptionHeight, item[cursorY]->effectText[0]);
			}
		}
		// ログ
		if (itemUseFlag)
		{
			Textbox::Draw(logX, logY, logWidth, logHeight, item[cursorY]->effectText[1]);
		}
	}

	if (menuFlag)
	{
		// カーソル
		DrawFormatString(8 + cursorX, 8 + cursorY * 16, WHITE, "▼");
	}
}

void Player::Process()
{
	// メニュー開閉
	if (KeyData::Get(KEY_INPUT_Q) == 1)
	{
		// メニューが既に開いている
		if (menuFlag)
		{
			// メニューを閉じる
			CloseMenu();
		}
		// メニューを開いていない
		else
		{
			// 項目数更新
			ChoiseNum = menuChoiceNum;

			// メニューを開く
			menuFlag = true;
		}
	}

	// メニューを開いているかどうかで処理を分ける
	// メニューを開いているとき
	if (menuFlag)
	{
		Menu();		// メニュー画面
	}
	// メニューを開いてないとき
	else
	{
		Move();		// 移動
	}
}

void Player::Menu()
{
	// カーソルの移動
	// アイテム処理中
	if (itemUseFlag)
	{

	}
	// 処理してないとき
	else
	{
		if (KeyData::Get(KEY_INPUT_UP) == 1 && cursorY != 0)
		{
			cursorY--;
		}
		else if (KeyData::Get(KEY_INPUT_DOWN) == 1 && cursorY < (ChoiseNum - 1))
		{
			cursorY++;
		}
	}

	// 決定
	if (KeyData::Get(KEY_INPUT_Z) == 1)
	{
		if (itemUseFlag)
		{
			// アイテム使用
			SellItem(cursorY);
			// ログを閉じる
			itemUseFlag = false;
		}
		else if (itemFlag)
		{
			// アイテム選択時
			if (cursorY < itemMax)
			{
				// ログを開く
				itemUseFlag = true;
			}
			// [もどる]選択時
			else
			{
				// カーソル移動
				cursorX = 0;
				cursorY = 0;
				// 項目の数
				ChoiseNum = menuChoiceNum;
				// アイテム画面を閉じる
				itemFlag = false;
			}
		}
		else if (menuFlag)
		{
			switch (cursorY)
			{
			case 0:		// メニュー画面
				// カーソル移動
				cursorX = itemX;
				// 項目の数
				ChoiseNum = itemChoiseNum;
				// アイテム画面を開く
				itemFlag = true;
				break;

			case 1:
				// メニューを閉じる
				CloseMenu();
				break;

			default:
				// エラー
				break;
			}
		}
	}
}
void Player::CloseMenu()
{
	// 初期化
	// カーソル
	cursorX = 0;			// 相対座標
	cursorY = 0;			// 相対座標
	// 項目の数
	ChoiseNum = 0;

	// アイテム画面を閉じる
	itemFlag = false;

	// メニューを閉じる
	menuFlag = false;
}
void Player::Move()
{
	// 直前の座標保存
	preX = x;
	preY = y;

	// 一応の保険
	if (speed > 30)
	{
		// エラー
		name = "スピードがマップチップの大きさを超えています";
	}
	else
	{
		// 移動
		if (KeyData::Get(KEY_INPUT_UP) > 0)
		{
			y -= speed;
			direction = UP;
		}
		else if (KeyData::Get(KEY_INPUT_DOWN) > 0)
		{
			y += speed;
			direction = DOWN;
		}
		else if (KeyData::Get(KEY_INPUT_LEFT) > 0)
		{
			x -= speed;
			direction = LEFT;
		}
		else if (KeyData::Get(KEY_INPUT_RIGHT) > 0)
		{
			x += speed;
			direction = RIGHT;
		}
	}
}
void Player::MoveReset()
{
	x = preX;
	y = preY;
}

bool Player::BuyItem(int ID) 
{
	for (int i = 0; i < itemMax; i++)
	{
		if (item[i]->ID == 0) {
			delete item[i];
			item[i] = new Item(ID);
			// 購入成功
			return true;
		}
	}

	// 購入失敗
	return false;
}

void Player::SellItem(int num)
{
	delete item[num];
	item[num] = new Item(0);
}

bool Player::GetmenuFlag()
{
	return menuFlag;
}

void Player::SetName(string name)
{
	this->name = name;
}
string Player::GetName()
{
	return name;
}
void Player::SetLV(int lv)
{
	this->lv = lv;
}
int Player::GetLV()
{
	return lv;
}
void Player::SetEXP(int exp)
{
	this->exp = exp;
}
int Player::GetEXP()
{
	return exp;
}
void Player::SetX(int x)
{
	this->x = x;
}
int Player::GetX()
{
	return x;
}
void Player::SetY(int y)
{
	this->y = y;
}
int Player::GetY()
{
	return y;
}
void Player::SetMaxHP(int maxHP)
{
	this->maxHP = maxHP;
}
int Player::GetMaxHP()
{
	return maxHP;
}
void Player::SetMaxMP(int maxMP)
{
	this->maxMP = maxMP;
}
int Player::GetMaxMP()
{
	return maxMP;
}
void Player::SetHP(int hp)
{
	this->hp = hp;
}
int Player::GetHP()
{
	return hp;
}
void Player::SetMP(int mp)
{
	this->mp = mp;
}
int Player::GetMP()
{
	return mp;
}
void Player::SetATK(int width)
{
	attack->width = width;
}
int Player::GetATK()
{
	return attack->power + GetRand(attack->width);
}
void Player::SetPower(int power)
{
	attack->power = power;
}
int Player::GetPower()
{
	return attack->power;
}
string Player::GetATKName()
{
	return attack->name;
}
void Player::SetATKName(string name)
{
	this->attack->name = name;
}
void Player::SetDirection(Direction direction)
{
	this->direction = direction;
}
Direction Player::GetDirection()
{
	return direction;
}

int Player::GetID(int num)
{
	return item[num]->ID;
}

void Player::SetMoney(int money)
{
	this->money = money;
}

int Player::GetMoney()
{
	return money;
}