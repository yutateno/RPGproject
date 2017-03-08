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

	menuFlag = false;
	cursorX = 0;
	cursorY = 0;
	listNum = 0;
	mItemFlag = false;
	mItemUseFlag = false;
	itemEffectText = "";
	mStatusFlag = false;

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
	DrawGraph(drawX, drawY, graph, true);		// プレイヤー本体


	// メニュー画面
	if (menuFlag)
	{
		// プレイヤーのステータス
		DrawFormatString(0, 384, BLACK, "%s\nHP:%d/%d\nMP:%d/%d\nLV:%d\nMoney:%d", name.c_str(), hp, maxHP, mp, maxMP, lv, money);

		// 項目
		DrawFormatString(0, 0, BLACK, "　アイテム\n　ステータス");

		// カーソル
		DrawFormatString(cursorX * 160, cursorY * 16, BLACK, "▲");

		// アイテム画面
		if (mItemFlag)
		{
			for (int i = 0;i < itemMax;i++)
			{
				DrawFormatString(160, i * 16, BLACK, "・%s", item[i]->GetName().c_str());
			}

			// アイテム使用中であれば
			if (mItemUseFlag)
			{
				DrawFormatString(32, 240, BLACK, "・%s", itemEffectText.c_str());
			}
			// アイテム使用中でなければ
			else
			{
				DrawFormatString(32, 240, BLACK, "・%s", item[cursorY]->GetEffectText(false).c_str());
			}
		}
		else if (mStatusFlag)
		{
			DrawFormatString(160, 0, BLACK, "　%s\n　HP:%d/%d\n　MP:%d/%d\n　LV:%d\n　Money:%d\n", name.c_str(), hp, maxHP, mp, maxMP, lv, money);
		}
	}
}

void Player::Process()
{
	// メニュー開閉
	if (KeyData::Get(KEY_INPUT_Q) == 1)
	{
		if (menuFlag)
		{
			if (cursorX == 0)
			{
				mItemFlag = false;
				mItemUseFlag = false;
				mStatusFlag = false;
				menuFlag = false;
				listNum = 0;
			}
			else
			{
				mItemFlag = false;
				mItemUseFlag = false;
				mStatusFlag = false;
			}
		}
		else
		{
			menuFlag = true;
			listNum = 2;
		}

		cursorX = 0;
		cursorY = 0;
	}

	if (menuFlag) // メニューを開いているかどうかで処理を分ける
	{
		Menu();		// メニュー画面
	}
	else          // メニューを開いてないとき
	{
		Move();		// 移動
	}
}

void Player::Menu()
{
	// カーソルの移動
	// アイテム使用中じゃなければ
	if (!mItemUseFlag)
	{
		if (KeyData::Get(KEY_INPUT_UP) == 1 && cursorY > 0)
		{
			cursorY--;
		}
		else if (KeyData::Get(KEY_INPUT_DOWN) == 1 && cursorY < (listNum - 1))
		{
			cursorY++;
		}
	}

	// 決定
	if (KeyData::Get(KEY_INPUT_Z) == 1)
	{
		// 最初の画面
		if (cursorX == 0)
		{
			// カーソルを右に
			cursorX++;

			// アイテムを選んだら
			if (cursorY == 0)
			{
				listNum = itemMax;
				mItemFlag = true;
			}
			// ステータスを選んだら
			else if (cursorY == 1)
			{
				mStatusFlag = true;
				listNum = 0;
			}
			else
			{
				// エラー
				name = "メニュー画面でのバグ";
			}

			// 一番上に戻す
			cursorY = 0;
		}
		else if (cursorX == 1)
		{
			// アイテム画面ならアイテム使用
			if (mItemFlag)
			{
				// アイテムを使った後
				if (mItemUseFlag)
				{
					mItemUseFlag = false;
					// 一番上に戻す
					cursorY = 0;
				}
				// アイテムを使う前
				else
				{
					// 効果文を逃がす
					itemEffectText = item[cursorY]->GetEffectText(true);
					// アイテムを消す
					SellItem(cursorY);
					mItemUseFlag = true;
				}
			}
		}
		else
		{
			// エラー
			name = "メニュー画面でのバグ";
		}
	}
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
		if (item[i]->GetID() == 0) {
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
	return item[num]->GetID();
}

void Player::SetMoney(int money)
{
	this->money = money;
}

int Player::GetMoney()
{
	return money;
}