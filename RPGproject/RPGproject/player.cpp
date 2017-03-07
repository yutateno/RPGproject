#include "player.h"

Player::Player()
{
	// �X�e�[�^�X����
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

	attack = new Attack();
	attack->power = 1;
	attack->width = 0;

	menuFlag = false;
	cursorX = 0;
	cursorY = 0;
	listNum = 0;
	mItemFlag = false;
	mStatusFlag = false;

	// �摜�ǂݍ���
	graph = LoadGraph("img\\player.png");
}
Player::~Player()
{
	// �摜�̃f�[�^�폜
	DeleteGraph(graph);
}

void Player::aaaDraw()
{
	// �v���C���[�{��
	DrawGraph(320 - 16, 240 - 16, graph, true);
}
void Player::aaaDraw(int mapwidth, int mapheight)
{
	// �v���C���[�{�̂ƃ}�b�v�̌��ˍ������l�����`��p�^�[��
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
	DrawGraph(drawX, drawY, graph, true);		// �v���C���[�{��


	// ���j���[���
	if (menuFlag)
	{
		// �v���C���[�̃X�e�[�^�X
		DrawFormatString(0, 384, BLACK, "%s\nHP:%d/%d\nMP:%d/%d\nLV:%d", name.c_str(), hp, maxHP, mp, maxMP, lv);

		// ����
		DrawFormatString(0, 0, BLACK, "�@�A�C�e��\n�@�X�e�[�^�X");

		// �J�[�\��
		DrawFormatString(cursorX * 160, cursorY * 16, BLACK, "��");

		// �A�C�e�����
		if (mItemFlag)
		{
			for (int i = 0;i < itemMax;i++)
			{
				DrawFormatString(160, i * 16, BLACK, "�E%s", item[i]->GetName().c_str());
			}
		}
		else if (mStatusFlag)
		{
			DrawFormatString(160, 0, BLACK, "�@%s\n�@HP:%d/%d\n�@MP:%d/%d\n�@LV:%d\n", name.c_str(), hp, maxHP, mp, maxMP, lv);
		}
	}
}

void Player::Process()
{
	// ���j���[�J��
	if (KeyData::Get(KEY_INPUT_Q) == 1)
	{
		if (menuFlag)
		{
			if (cursorX == 0)
			{
				mItemFlag = false;
				mStatusFlag = false;
				menuFlag = false;
				listNum = 0;
			}
			else
			{
				mItemFlag = false;
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

	if (menuFlag) // ���j���[���J���Ă��邩�ǂ����ŏ����𕪂���
	{
		Menu();		// ���j���[���
	}
	else          // ���j���[���J���ĂȂ��Ƃ�
	{
		Move();		// �ړ�
	}
}

void Player::Menu()
{
	// �J�[�\���̈ړ�
	if (KeyData::Get(KEY_INPUT_UP) == 1 && cursorY > 0)
	{
		cursorY--;
	}
	else if (KeyData::Get(KEY_INPUT_DOWN) == 1 && cursorY < (listNum - 1))
	{
		cursorY++;
	}

	// ����
	if (KeyData::Get(KEY_INPUT_Z) == 1)
	{
		if (cursorX == 0)
		{
			cursorX++;
			if (cursorY == 0)
			{
				listNum = itemMax;
				mItemFlag = true;
			}
			else if (cursorY == 1)
			{
				mStatusFlag = true;
				listNum = 0;
			}
			else
			{
				// �G���[
				name = "���j���[��ʂł̃o�O";
			}
		}
		else if (cursorX == 1)
		{
			// �����ɃA�C�e���Ƃ��X�e�[�^�X�̂��Ƃ�����
		}
		else
		{
			// �G���[
			name = "���j���[��ʂł̃o�O";
		}

		// ��ԏ�ɖ߂�
		cursorY = 0;
	}
}
void Player::Move()
{
	// ���O�̍��W�ۑ�
	preX = x;
	preY = y;

	// �ꉞ�̕ی�
	if (speed > 30)
	{
		// �G���[
		name = "�X�s�[�h���}�b�v�`�b�v�̑傫���𒴂��Ă��܂�";
	}
	else
	{
		// �ړ�
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
void Player::SetDirection(Direction direction)
{
	this->direction = direction;
}
Direction Player::GetDirection()
{
	return direction;
}