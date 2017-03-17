#include "Manager.h"
#include "SafeArea.h"

SafeArea::SafeArea() {
	// ����֌W
	endFlag = false;
	nextScene = eScene::S_End;

	// �摜�֌W
	Gr_Wall = LoadGraph("Dungeon\\wall.png");
	Gr_Back = LoadGraph("img\\safearea_background.png");
	Gr_Exit = LoadGraph("img\\exit.png");
	Gr_Murabito = LoadGraph("img\\murabito.png");
	Gr_Shop = LoadGraph("img\\shop.png");
	Gr_Yado = LoadGraph("img\\yado.png");
	graph = 0;

	// ���o�֌W
	step = eStep::Start;
	startCount = 30;
	endCount = 30;
	count = 0;
	lines = "";

	// �}�b�v�f�[�^�ǂݍ���
	MapData();

	// �J����
	x = 0;
	y = 0;

	// �e��t���O
	fieldflag = false;
	peopleflag = false;
	itemflag = false;
	healflag = false;
	healY = false;
	talkflag = false;
	shopflag = false;
	buyflag = false;
	sellflag = false;
	innflag = false;
	successflag = false;

	// �J�E���g�n
	healcount = 0;
	shopcount = 0;

	// UI�Ǘ��֌W
	shopmenu = START;
	shopmY = 0;

	// �[���v���C���[�v�f
	money = 0;
	ID = 0;
	for (int i = 0; i < 9; i++) {
		item[i] = 0;
	}

	// �Q�Ɨp�A�C�e���Ə�ɕϓ�����l�i
	price = 0;
	itemPosition = 0;
	itemMax = 9;

	// UI(�v���C���[.�������Ȃ�
	playerUI_x = 420;
	playerUI_y = 420;
	playerUI_height = 35;
	playerUI_width = 135;
	
	shopUI_x = 55;
	shopUI_y = 50;
	shopUI_width = 150;
	shopUI_second = 40;
	shopUI_se_width = 320;

	healUI_x = 55;
	healUI_y = 50;
	healUI_width = 180;
	
	conUI_x = 140;
	conUI_y = 140;
	conUI_width = 125;
	conUI_height = 35;
}
SafeArea::~SafeArea() {
	// �摜�폜
	DeleteGraph(Gr_Wall);
	DeleteGraph(Gr_Back);
	DeleteGraph(Gr_Exit);
	DeleteGraph(Gr_Murabito);
	DeleteGraph(Gr_Shop);
	DeleteGraph(Gr_Yado);
}

void SafeArea::UpDate() {
	switch (this->step) {
	case eStep::Start:	// �J�n���
		this->UpDate_Start();
		break;
	case eStep::Main:	// ���C���������
		this->UpDate_Main();
		break;
	case eStep::End:	// �I�����
		this->UpDate_End();
		break;
	default:
		this->endFlag = true;	// �G���[�I��
		break;
	}
}

void SafeArea::UpDate(int playerX, int playerY) {
	switch (this->step) {
	case eStep::Start:	// �J�n���
		this->UpDate_Start();
		break;
	case eStep::Main:	// ���C���������
		this->UpDate_Main();
		break;
	case eStep::End:	// �I�����
		this->UpDate_End();
		break;
	default:
		this->endFlag = true;	// �G���[�I��
		break;
	}
}

void SafeArea::UpDate_Start() {
	// �J�E���g�A�b�v
	count++;

	// startCount�������o
	if (count < startCount) return;
	// �J�E���g���Z�b�g�ƃX�e�b�v�i�s
	count = 0;
	step = eStep::Main;
}

void SafeArea::UpDate_Main() {
	// ����̏ꏊ�s������t�B�[���h��ʂ�
	if (fieldflag == true) {
		nextScene = eScene::S_Field;
		step = eStep::End;
	}

	// �h���ɘb�����������Ԃł����
	if (innflag)
	{
		HealProcess();		// �񕜃|�C���g(�h��)�̏���
	}
	// �\�����Ԃ̃J�E���g�_�E���J�E���g�_�E��
	if (healcount > 0) {
		healcount--;
	}

	// ���l�ɘb�����������Ԃł����
	if (peopleflag)
	{
		PeopleProcess();	// ���l(��b�v�f)
	}

	if (itemflag)
	{
		ShopProcess();		// �X
	}
	// �V���b�v�̔�����̉�b�\���̃J�E���g�_�E��
	if (shopcount >= 0) {
		shopcount--;
	}
}

void SafeArea::UpDate_End() {
	// �J�E���g�A�b�v
	count++;

	// endCount�������o
	if (count < endCount) return;
	// �J�E���g���Z�b�g�ƃV�[���I��
	count = 0;
	endFlag = true;
}

void SafeArea::Draw() {
	switch (this->step) {
	case eStep::Start:	// �J�n���
		this->Draw_Start();
		break;
	case eStep::Main:	// ���C���������
		this->Draw_Main();
		break;
	case eStep::End:	// �I�����
		this->Draw_End();
		break;
	default:
		this->endFlag = true;	// �G���[�I��
		break;
	}
}

void SafeArea::Draw_Start() {
	DrawStringToHandle(0, 0, "���_���", WHITE, Font::Get(eFont::SELECT));
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "�J�n��� %d / %d", count, startCount);
}

void SafeArea::Draw_Main() {
	SafeArea_Map();
}

void SafeArea::Draw_End() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150 - (count * 5));
	SafeArea_Map();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SafeArea::SafeArea_Map() {
	// �w�i
	DrawGraph(0, 0, Gr_Back, false);

	// �}�b�v�`�b�v�`��
	for (int i = 0, n = (int)map.size(); i < n; i++) {
		for (int j = 0, m = (int)map[i].size(); j < m; j++) {
			//stoi �ŕ����𐔒l�ɕϊ�
			switch ((int)(stoi(map[i][j]) * 0.1)) {
			case 0:	//00
				graph = 0;
				break;

			case 1:	//��
				switch (stoi(map[i][j]) % 10) {
				case 0:	//10
					graph = Gr_Wall;
					break;

				case 1:
					graph = Gr_Exit;	// �o��
					break;

				case 2:
					graph = Gr_Murabito;	// �ē��l
					break;

				case 3:
					graph = Gr_Shop;	// ���
					break;

				case 4:
					graph = Gr_Yado;	// ����
					break;

				default:
					// �G���[
					break;
				}
				break;

			default:
				// �G���[
				break;
			}

			// �`��
			DrawGraph(j * 32, i * 32, graph, true);
		}
	}
}

void SafeArea::Draw_UI() {
	// �񕜊֘A-----------------------------------------------------
	if (innflag == true && talkflag == true) {
		// �R�}���h�{�b�N�X
		Textbox::Draw(healUI_x, healUI_y, healUI_width, (cursor * 3) + 10, "���܂�܂����H\n\n�@�@�x�ށ@�@100�~\n\n�@�@��߂�");

		// �J�[�\��
		DrawString(healUI_x + 13, healUI_y + ((healY + 1) * cursor) + 13, "��", RED);
	}
	//--------------------------------------------------------------

	//�������֘A----------------------------------------------------
	if (itemflag == true && shopflag == true) {
		// �ŏ��̃��j���[
		if (shopmenu == START || shopmenu == BUY || shopmenu == SELL) {
			// �R�}���h�{�b�N�X
			Textbox::Draw(shopUI_x, shopUI_y, shopUI_width, (cursor * 5) - 10, "���������[��\n\n�@�@����\n\n�@�@����\n\n�@�@��߂�");

			// �J�[�\��
			if (shopmenu == START) {
				DrawString(shopUI_x + 10, shopUI_y + ((shopmY + 1) * cursor) + 15, "��", RED);
			}
		}
		// �����Ƃ��̃��j���[
		if (shopmenu == BUY) {
			// �R�}���h�{�b�N�X
			Textbox::Draw(shopUI_x + shopUI_second, shopUI_y + shopUI_second, shopUI_se_width, (cursor * 5) + 40, "���𔃂��H");
			
			// ����
			for (int i = 2; i <= 5; i++) {
				Textbox::Draw(shopUI_x + shopUI_second + 38, shopUI_y + (cursor * (i - 1)) + shopUI_second + 2, Item::SearchName(i));
				Textbox::Draw(shopUI_x + shopUI_second + 266, shopUI_y + (cursor*(i - 1)) + shopUI_second + 2, std::to_string(Item::SearchPrice(i)));
			}

			// �߂�
			Textbox::Draw(shopUI_x + shopUI_second + 38, shopUI_y + (cursor * 5) + shopUI_second + 2, "�߂�");

			// �J�[�\��
			DrawString(shopUI_x + shopUI_second + 15, shopUI_y + ((shopmY + 1) * cursor) + shopUI_second + 10, "��", RED);
		}
		// ����Ƃ��̃��j���[
		if (shopmenu == SELL) {
			// �{�b�N�X
			Textbox::Draw(shopUI_x + shopUI_second, shopUI_y + shopUI_second, shopUI_se_width, (cursor * 10) + 40, "���𔄂�H");
			
			// �����A�C�e���ꗗ
			for (int i = 0; i < itemMax; i++) {
				Textbox::Draw(shopUI_x + shopUI_second + 38, shopUI_y + (cursor * (i + 1)) + shopUI_second + 2, Item::SearchName(item[i]));
				Textbox::Draw(shopUI_x + shopUI_second + 266, shopUI_y + (cursor * (i + 1)) + shopUI_second + 2, std::to_string(Item::SearchPrice(item[i])));
			}
			
			// �߂�
			Textbox::Draw(shopUI_x + shopUI_second + 38, shopUI_y + (cursor * 10) + shopUI_second + 2, "�߂�");
			
			// �J�[�\��
			DrawString(shopUI_x + shopUI_second + 15, shopUI_y + ((shopmY + 1) * cursor) + shopUI_second + 10, "��", RED);
		}
	}
	//--------------------------------------------------------------

	// ������UI-----------------------------------------------------
	// �b���Ă�Ƃ����ʂ̏���
	if ((talkflag || shopflag) && !peopleflag)
	{
		// ������
		Textbox::Draw(playerUI_x, playerUI_y, playerUI_width, playerUI_height, "�������F"+std::to_string(money)+"�~");
	}
	//--------------------------------------------------------------

	//AI�̉�b��UI--------------------------------------------------
	// ���l�̃Z���t
	if (peopleflag == true && talkflag == true) {
		Textbox::Draw(conUI_x, conUI_y, conUI_width + 85, conUI_height, "�����̓~���g�X�̒��ł��B");
	}
	// �b���Ă鑊��̃Z���t
	if (((shopmenu == BUY || shopmenu == SELL) && shopcount > 0) || healcount > 0) {
		Textbox::Draw(conUI_x, conUI_y, conUI_width, conUI_height, lines);
	}
	// �񕜕\��
	if (healcount > 0) {
		if (money > price) {
			lines = "�񕜂��܂����B";
		}
		else {
			lines = "�o������";
		}
	}
	// �X��̃Z���t
	// �������Ƃ�
	if (shopmenu == BUY && shopcount > 0) {
		if (money > price) {
			if (successflag == false) {
				lines = "���t�ł�";
			}
			else {
				lines = "�܂��ǁ`";
			}
		}
		else {
			lines = "�o������";
		}
	}
	// �������Ƃ�
	if (shopmenu == SELL && shopcount > 0) {
		// ���ȊO�𔄂����Ƃ�
		// shopmY=9:�z��O�Q��
		if (shopmY != 9)
		{
			if (price != 0) {
				lines = "�܂��ǁ`";
			}
			// ���𔄂�Ƃ�
			else {
				lines = "�͂�";
			}
		}
	}
	//--------------------------------------------------------------
}

void SafeArea::MapData() {
	read_file.open("SafeAreaMap.txt");
	read_count = 0;
	while (getline(read_file, read_line)) {	// ��s���ǂݍ���
		map.resize(read_count + 1);
		for (int i = 0, n = (int)read_line.length(); i < n; i += 2) {
			map[read_count].push_back(read_line.substr(i, 2));
		}
		read_count++;	// ���̍s��
	}
	read_file.close();
}

void SafeArea::HealProcess() {
	// �h�̒l�i
	price = 100;

	if (KeyData::Get(KEY_INPUT_Z) == 1) {
		// ���ɘb���Ă���ꍇ
		if (talkflag == true) {
			// �񕜗��񂾂�
			if (healY == 0) {
				// ���������
				if (money >= price) {
					money -= price;
					healflag = true;
				}
				// �����Ȃ����
				else {
					// ���܂�Ȃ�
				}

				// �Z���t�\���ƑI���A�C�R�����W������
				healcount = heal;
				healY = 0;
			}
			// �񕜂�f��
			else {
				healY = 0;
			}

			// ��b�I��
			talkflag = false;
		}
		// �b���������ꍇ
		else
		{
			// ���܂邩�̑I���ɉf��
			talkflag = true;
		}
	}

	// �I����
	// �b�������Ă��Ԃ���
	if (talkflag == true) {
		if (KeyData::Get(KEY_INPUT_UP) == 1) {
			healY = 0;
		}
		if (KeyData::Get(KEY_INPUT_DOWN) == 1) {
			healY = 1;
		}
	}
}

void SafeArea::PeopleProcess() {
	if (KeyData::Get(KEY_INPUT_Z) == 1) {
		// �Z���t���o�Ă�����
		if (talkflag == false) {
			talkflag = true;
		}
		// �Z���t���o�Ă��Ȃ�������
		else {
			talkflag = false;
		}
	}
}

void SafeArea::ShopProcess() {
	if (KeyData::Get(KEY_INPUT_Z) == 1) {
		// ���ɘb�������Ă���ꍇ
		if (shopflag == true) {
			switch (shopmenu)
			{
			case START:
				// �w����ʂ�
				if (shopmY == 0) {
					shopmenu = BUY;
				}
				// ���p��ʂ�
				else if (shopmY == 1) {
					shopmenu = SELL;
				}
				// ��߂���������Ƃ�
				else {
					// �������I��
					shopflag = false;
				}

				// �J�[�\��������
				shopmY = 0;
				break;

			case BUY:
				switch (shopmY)
				{
				case 0:		// �₭(�ɂ���������)����
					price = Item::SearchPrice(2);
					ID = 2;
					break;
				case 1:		// ���炩�Ȑ�
					price = Item::SearchPrice(3);
					ID = 3;
					break;
				case 2:		// ���ނ�_�}
					price = Item::SearchPrice(4);
					ID = 4;
					break;
				case 3:		// ���E���̃n
					price = Item::SearchPrice(5);
					ID = 5;
					break;

				case 4:		// �߂�{�^��
					price = 0;
					ID = 0;

					// ������
					shopmenu = START;
					shopmY = 0;
					break;

				default:	// �G���[
					price = 0;
					ID = 0;
					break;
				}

				// ����������Ă����
				if (money >= price) {
					// Manager�ɏ���������t���O�𗧂Ă�
					buyflag = true;
					if (successflag == true) {
						// ���������}�C�i�X����
						money -= price;
					}
				}
				else {
					// �������s������ю��������t
				}

				// �Z���t�\�����ԍX�V
				shopcount = shop;
				break;

			case SELL:
				// shopmY=9:�z��O�Q��
				if (shopmY != 9)
				{
					// �l�i�Ƃ��̃A�C�e���̕ۊǏꏊ��ۑ�
					price = Item::SearchPrice(item[shopmY]);
					itemPosition = shopmY;

					// Manager�ɏ���������t���O�𗧂Ă�
					sellflag = true;

					// �A�C�e��������
					item[shopmY] = 0;

					// ���������v���X����
					money += price;
				}
				// �߂�I����
				else
				{
					// �l�i�Ƃ��̃A�C�e���̕ۊǏꏊ��ۑ�
					price = 0;
					itemPosition = 0;

					// ������
					shopmenu = START;
					shopmY = 0;
				}

				// �Z���t�\�����ԍX�V
				shopcount = shop;
				break;

			case END:
				break;

			default:
				// �G���[
				break;
			}
		}
		// �܂��b�������Ă��Ȃ��Ƃ�
		else {
			shopflag = true;
		}
	}

	// �V���b�v��ʂł̃J�[�\���ړ�
	if (shopflag == true) {
		// ���������
		if (KeyData::Get(KEY_INPUT_UP) == 1 && shopmY > 0) {
			shopmY--;
		}
		// ����������
		if (KeyData::Get(KEY_INPUT_DOWN) == 1) {
			switch (shopmenu)
			{
			case START:
				if (shopmY < 2) {
					shopmY++;
				}
				break;

			case BUY:
				if (shopmY < 4) {
					shopmY++;
				}
				break;

			case SELL:
				if (shopmY < 9) {
					shopmY++;
				}
				break;

			case END:
				break;

			default:
				// �G���[
				break;
			}
		}
	}
}

int SafeArea::GetMapData(int x, int y) {
	return stoi(map[(int)(y / 32)][(int)(x / 32)]);
}

int SafeArea::GetMapWidth() {
	return (int)map[0].size();
}
int SafeArea::GetMapHeight() {
	return (int)map.size();
}

void SafeArea::SetX(int x) {
	this->x = x;
}

int SafeArea::GetX() {
	return this->x;
}

void SafeArea::SetY(int y) {
	this->y = y;
}

int SafeArea::GetY() {
	return this->y;
}

void SafeArea::SetField(bool flag) {
	fieldflag = flag;
}

void SafeArea::SetPeople(bool flag) {
	peopleflag = flag;
}

bool SafeArea::GetPeople() {
	return peopleflag;
}

void SafeArea::SetItem(bool flag) {
	itemflag = flag;
}

bool SafeArea::GetItem() {
	return itemflag;
}

bool SafeArea::GetShop(){
	return shopflag;
}

void SafeArea::SetHeal(bool flag) {
	healflag = flag;
}

bool SafeArea::GetHeal() {
	return healflag;
}

bool SafeArea::GetTalk() {
	return talkflag;
}

void SafeArea::SetBuy(bool flag) {
	buyflag = flag;
}

bool SafeArea::GetBuy() {
	return buyflag;
}

void SafeArea::SetSell(bool flag) {
	sellflag = flag;
}

bool SafeArea::GetSell() {
	return sellflag;
}

void SafeArea::SetInn(bool flag) {
	innflag = flag;
}

bool SafeArea::GetInn() {
	return innflag;
}

int SafeArea::GetID() {
	return ID;
}

void SafeArea::SetItemPosition(int itemPosition) {
	this->itemPosition = itemPosition;
}

int SafeArea::GetItemPosition() {
	return itemPosition;
}

void SafeArea::SetnumID(int num, int ID) {
	item[num] = ID;
}

void SafeArea::SetMoney(int money) {
	this->money = money;
}

int SafeArea::GetMoney() {
	return money;
}

void SafeArea::SetSuccess(bool flag) {
	successflag = flag;
}

eStep SafeArea::GetStep() {
	return step;
}