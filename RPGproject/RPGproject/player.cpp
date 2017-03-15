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
	ID = 0;
	money = 500;

	attack = new Attack();
	attack->power = 1;
	attack->width = 0;

	// ���j���[�֌W
	ChoiseNum = 0;			// ���ڂ̐�
	// ���j���[
	menuFlag = false;		// ���j���[���J���Ă��邩�ǂ���
	menuWidth = 96;			// ����
	menuHeight = 48;		// ��
	menuX = 0;				// ���W
	menuY = 0;				// ���W
	menuChoiceNum = 2;		// ���ڂ̐�
	// �X�e�[�^�X
	statusWidth = 112;		// �X�e�[�^�X�̕�
	statusHeight = 96;		// �X�e�[�^�X�̍���
	statusX = 0;			// �X�e�[�^�X�̍��W
	statusY = 480 - statusHeight;		// �X�e�[�^�X�̍��W
	// �A�C�e�����
	itemFlag = false;		// �A�C�e����ʂ��J���Ă��邩�ǂ���
	itemUseFlag = false;	// �A�C�e�����g���Ă��邩�ǂ���
	itemWidth = 192;		// ����
	itemHeight = 176;		// ��
	itemX = menuX + menuWidth;			// ���W
	itemY = 0;				// ���W
	itemChoiseNum = 10;
	// �����g
	descriptionWidth = 320;	// ��
	descriptionHeight = 32;	// ����
	descriptionX = itemX;	// ���W
	descriptionY = itemY + itemHeight;	// ���W
	// ���O
	logX = statusX + statusWidth;		// ���W
	logWidth = 640 - logX;	// ��
	logHeight = 96;			// ����
	logY = 480 - logHeight;	// ���W
	// �J�[�\��
	cursorX = 0;			// ���΍��W
	cursorY = 0;			// ���΍��W
	
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
	// �v���C���[�{��
	DrawGraph(drawX, drawY, graph, true);

	// ���j���[���
	if (menuFlag)
	{
		// ���j���[
		Textbox::Draw(menuX, menuY, menuWidth, menuHeight, "�@�A�C�e��\n�@���ǂ�");
		// �X�e�[�^�X
		Textbox::Draw(statusX, statusY, statusWidth, statusHeight,
			name + "\n" +
			"HP:" + std::to_string(hp) + " / " + std::to_string(maxHP) + "\n" +
			"MP:" + std::to_string(mp) + " / " + std::to_string(maxMP) + "\n" +
			"LV:" + std::to_string(lv));

		// �J�[�\��
		DrawFormatString(8 + cursorX, 8 + cursorY * 16, WHITE, "��");
		// �A�C�e�����
		if (itemFlag)
		{
			// �w�i
			Textbox::Draw(itemX, itemY, itemWidth, itemHeight, "");
			// ����
			for (int i = 0, n = itemMax;i < n;i++)
			{
				Textbox::Draw(itemX, itemY + (i * 16), "�@" + item[i]->name);
			}
			Textbox::Draw(itemX, itemY + (itemChoiseNum - 1) * 16, "�@���ǂ�");
			// ����
			if (cursorY < itemMax)
			{
				Textbox::Draw(descriptionX, descriptionY, descriptionWidth, descriptionHeight, item[cursorY]->effectText[0]);
			}
		}
		// ���O
		if (itemUseFlag)
		{
			Textbox::Draw(logX, logY, logWidth, logHeight, item[cursorY]->effectText[1]);
		}
	}

	if (menuFlag)
	{
		// �J�[�\��
		DrawFormatString(8 + cursorX, 8 + cursorY * 16, WHITE, "��");
	}
}

void Player::Process()
{
	// ���j���[�J��
	if (KeyData::Get(KEY_INPUT_Q) == 1)
	{
		// ���j���[�����ɊJ���Ă���
		if (menuFlag)
		{
			// ���j���[�����
			CloseMenu();
		}
		// ���j���[���J���Ă��Ȃ�
		else
		{
			// ���ڐ��X�V
			ChoiseNum = menuChoiceNum;

			// ���j���[���J��
			menuFlag = true;
		}
	}

	// ���j���[���J���Ă��邩�ǂ����ŏ����𕪂���
	// ���j���[���J���Ă���Ƃ�
	if (menuFlag)
	{
		Menu();		// ���j���[���
	}
	// ���j���[���J���ĂȂ��Ƃ�
	else
	{
		Move();		// �ړ�
	}
}

void Player::Menu()
{
	// �J�[�\���̈ړ�
	// �A�C�e��������
	if (itemUseFlag)
	{

	}
	// �������ĂȂ��Ƃ�
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

	// ����
	if (KeyData::Get(KEY_INPUT_Z) == 1)
	{
		if (itemUseFlag)
		{
			// �A�C�e���g�p
			SellItem(cursorY);
			// ���O�����
			itemUseFlag = false;
		}
		else if (itemFlag)
		{
			// �A�C�e���I����
			if (cursorY < itemMax)
			{
				// ���O���J��
				itemUseFlag = true;
			}
			// [���ǂ�]�I����
			else
			{
				// �J�[�\���ړ�
				cursorX = 0;
				cursorY = 0;
				// ���ڂ̐�
				ChoiseNum = menuChoiceNum;
				// �A�C�e����ʂ����
				itemFlag = false;
			}
		}
		else if (menuFlag)
		{
			switch (cursorY)
			{
			case 0:		// ���j���[���
				// �J�[�\���ړ�
				cursorX = itemX;
				// ���ڂ̐�
				ChoiseNum = itemChoiseNum;
				// �A�C�e����ʂ��J��
				itemFlag = true;
				break;

			case 1:
				// ���j���[�����
				CloseMenu();
				break;

			default:
				// �G���[
				break;
			}
		}
	}
}
void Player::CloseMenu()
{
	// ������
	// �J�[�\��
	cursorX = 0;			// ���΍��W
	cursorY = 0;			// ���΍��W
	// ���ڂ̐�
	ChoiseNum = 0;

	// �A�C�e����ʂ����
	itemFlag = false;

	// ���j���[�����
	menuFlag = false;
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

bool Player::BuyItem(int ID) 
{
	for (int i = 0; i < itemMax; i++)
	{
		if (item[i]->ID == 0) {
			delete item[i];
			item[i] = new Item(ID);
			// �w������
			return true;
		}
	}

	// �w�����s
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