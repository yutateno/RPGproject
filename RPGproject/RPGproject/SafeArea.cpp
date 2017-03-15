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

	// UI
	playerUI_x = 420;
	playerUI_y = 420;
	anotherUI_x = 55;
	anotherUI_y = 50;
	conUI_x = 140;
	conUI_y = 140;
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

void SafeArea::Draw_End() {
	DrawStringToHandle(0, 0, "���_���", WHITE, Font::Get(eFont::SELECT));
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "�I����� %d / %d", count, endCount);
}

void SafeArea::Draw_UI() {
	// �񕜓X��
	if (innflag == true && talkflag == true) {
		// �R�}���h�{�b�N�X
		Textbox::Draw(anotherUI_x - 8, anotherUI_y - 8, 180, (cursor * 3) + 10, "���܂�܂����H");
		
		// �I����
		Textbox::Draw(anotherUI_x + 22, anotherUI_y + (cursor * 1), "�x�݁@�@100�~");
		Textbox::Draw(anotherUI_x + 22, anotherUI_y + (cursor * 2), "��߂�");

		// �J�[�\��
		DrawString(anotherUI_x + 5, anotherUI_y + (healY + 1) * cursor, "��", RED);
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

	// ���l�̃Z���t
	if (peopleflag == true && talkflag == true) {
		Textbox::Draw(conUI_x, conUI_y, 210, 35, "�����̓~���g�X�̒��ł��B");
	}

	//�������֘A----------------------------------------------------
	if (itemflag == true && shopflag == true) {
		// �ŏ��̃��j���[
		if (shopmenu == START || shopmenu == BUY || shopmenu == SELL) {
			// �R�}���h�{�b�N�X
			Textbox::Draw(anotherUI_x - 16, anotherUI_y - 16, 140, (cursor * 5) - 10, "���������[��");
			
			// �I����
			Textbox::Draw(anotherUI_x + 22, anotherUI_y + (cursor * 1) - 8, "����");
			Textbox::Draw(anotherUI_x + 22, anotherUI_y + (cursor * 2) - 8, "����");
			Textbox::Draw(anotherUI_x + 22, anotherUI_y + (cursor * 3) - 8, "��߂�");

			// �J�[�\��
			if (shopmenu == START) {
				DrawString(anotherUI_x + 5, anotherUI_y + ((shopmY + 1) * cursor), "��", RED);
			}
		}
		// �����Ƃ��̃��j���[
		if (shopmenu == BUY) {
			// �R�}���h�{�b�N�X
			Textbox::Draw(anotherUI_x + 34, anotherUI_y + 34, 320, (cursor * 5) + 40, "���𔃂��H");
			
			// ����
			for (int i = 2; i <= 5; i++) {
				Textbox::Draw(anotherUI_x + 72, anotherUI_y + (cursor * (i - 1)) + 42, Item::SearchName(i));
				DrawFormatString(anotherUI_x + 300, anotherUI_y + (cursor * (i - 1)) + 50, WHITE, "%d", Item::SearchPrice(i));
			}

			// �߂�
			Textbox::Draw(anotherUI_x + 72, anotherUI_y + (cursor * 5) + 42, "�߂�");

			// �J�[�\��
			DrawString(anotherUI_x + 55, anotherUI_y + ((shopmY + 1) * cursor) + 50, "��", RED);
		}
		// ����Ƃ��̃��j���[
		if (shopmenu == SELL) {
			// �{�b�N�X
			Textbox::Draw(anotherUI_x + 34, anotherUI_y + 34, 310, (cursor * 10) + 40, "���𔄂�H");
			
			// �����A�C�e���ꗗ
			for (int i = 0; i < itemMax; i++) {
				Textbox::Draw(anotherUI_x + 72, anotherUI_y + (cursor * (i + 1)) + 42, Item::SearchName(item[i]));
				DrawFormatString(anotherUI_x + 300, anotherUI_y + (cursor * (i + 1)) + 50, WHITE, "%d", Item::SearchPrice(item[i]));
			}
			
			// �߂�
			Textbox::Draw(anotherUI_x + 72, anotherUI_y + (cursor * 10) + 42, "�߂�");
			
			// �J�[�\��
			DrawString(anotherUI_x + 55, anotherUI_y + ((shopmY + 1) * cursor) + 50, "��", RED);
		}
	}
	// �X��̃Z���t
	// �������Ƃ�
	if (shopmenu == BUY && shopcount > 0) {
		if (money > price) {
			lines = "�܂��ǁ`";
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

	// �b���Ă�Ƃ����ʂ̏���
	if ((talkflag || shopflag) && !peopleflag)
	{
		// ������
		Textbox::Draw(playerUI_x, playerUI_y, 135, 35, "");
		DrawFormatString(playerUI_x + 8, playerUI_y + 8, WHITE, "�������F%d�~", money);
	}
	// �b���Ă鑊��̃Z���t
	if (((shopmenu == BUY || shopmenu == SELL) && shopcount > 0) || healcount > 0) {
		Textbox::Draw(conUI_x, conUI_y, 125, 35, lines);
	}
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
					// ���������}�C�i�X����
					money -= price;
				}
				else {
					// �������s��
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

void SafeArea::Refund()
{
	money += Item::SearchPrice(ID);
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

bool SafeArea::GetField() {
	return fieldflag;
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

void SafeArea::SetShop(bool flag) {
	shopflag = flag;
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

void SafeArea::SetTalk(bool flag) {
	talkflag = flag;
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

void SafeArea::SetID(int ID) {
	this->ID = ID;
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

eStep SafeArea::GetStep() {
	return step;
}