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
	startCount = 50;
	endCount = 50;
	count = 0;
	lines = "";

	// �}�b�v�f�[�^�ǂݍ���
	MapData();

	// ����ȂɁH
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
	itemm = new Item();
	price = 0;

	// ���������Y��悭�Ȃ�
	itemPosition = 0;
	innflag = false;
}
SafeArea::~SafeArea() {
	// �摜�폜
	DeleteGraph(Gr_Wall);
	DeleteGraph(Gr_Back);
	DeleteGraph(Gr_Exit);
	DeleteGraph(Gr_Murabito);
	DeleteGraph(Gr_Shop);
	DeleteGraph(Gr_Yado);

	// �Q�Ɨp�A�C�e���폜
	delete 	itemm;
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
		this->Draw_Main(x, y);
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

void SafeArea::Draw_Main(int x, int y) {
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
			DrawGraph(j * 32 - x, i * 32 - y, graph, true);
		}
	}

	// �񕜓X��
	if (innflag == true && talkflag == true) {
		DrawFormatString(320, 150, BLACK, "�������F%d�~", money);
		DrawFormatString(320, 118, BLACK, "100�~");
		DrawFormatString(0, cursor * 0, BLACK, "���܂�܂����H");
		DrawFormatString(35, cursor * 1, BLACK, "�x�݂܂�");
		DrawFormatString(35, cursor * 2, BLACK, "��߂Ƃ��܂�");
		DrawBox(0, (healY + 1) * cursor, 32, 32 + ((healY + 1) * cursor), BLUE, true);
	}
	// �񕜕\��
	if (healcount > 0) {
		if (money > price) {
			DrawFormatString(320, 240, BLACK, "�񕜂��܂����B");
		}
		else {
			DrawFormatString(320, 240, BLACK, "�o������");
		}
	}

	// ���l�̃Z���t
	if (peopleflag == true) {
		lines = "�����͒��ł��B";
	}

	//�������֘A----------------------------------------------------
	if (itemflag == true && shopflag == true) {
		// �ŏ��̃��j���[
		if (shopmenu == START) {
			// �I����
			DrawFormatString(35, cursor * 0, BLACK, "����");
			DrawFormatString(35, cursor * 1, BLACK, "����");
			DrawFormatString(35, cursor * 2, BLACK, "��߂�");

			// �J�[�\��
			DrawBox(0, shopmY * cursor, 32, 32 + (shopmY * cursor), BLUE, true);

			// �Z���t
			lines = "���������[��";
		}
		// �����Ƃ��̃��j���[
		else if(shopmenu == BUY) {
			// �₭(�ɂ���������)����
			DrawFormatString(35, cursor * 0, BLACK, " %s ", itemm->SearchName(2).c_str());
			DrawFormatString(250, cursor * 0, BLACK, " %d ", itemm->SearchPrice(2));
			// ���炩�Ȑ�
			DrawFormatString(35, cursor * 1, BLACK, " %s ", itemm->SearchName(3).c_str());
			DrawFormatString(250, cursor * 1, BLACK, " %d ", itemm->SearchPrice(3));
			// ���ނ�_�}
			DrawFormatString(35, cursor * 2, BLACK, " %s ", itemm->SearchName(4).c_str());
			DrawFormatString(250, cursor * 2, BLACK, " %d ", itemm->SearchPrice(4));
			// ���E���̃n
			DrawFormatString(35, cursor * 3, BLACK, " %s ", itemm->SearchName(5).c_str());
			DrawFormatString(250, cursor * 3, BLACK, " %d ", itemm->SearchPrice(5));
			// �߂�
			DrawFormatString(35, cursor * 4, BLACK, "�߂�");

			// �J�[�\��
			DrawBox(0, shopmY * cursor, 32, 32 + (shopmY * cursor), BLUE, true);

			// �Z���t
			lines = "���𔃂��H";
		}
		// ����Ƃ��̃��j���[
		else if (shopmenu == SELL) {
			// �����A�C�e���ꗗ
			for (int i = 0; i < 9; i++)
			{
				DrawFormatString(35, cursor * i, BLACK, " %s ", itemm->SearchName(item[i]).c_str());
				DrawFormatString(250, cursor * i, BLACK, " %d ", itemm->SearchPrice(item[i]));
			}
			// �߂�
			DrawFormatString(35, cursor * 9, BLACK, "�߂�");

			// �J�[�\��
			DrawBox(0, shopmY * cursor, 32, 32 + (shopmY * cursor), BLUE, true);

			// �Z���t
			lines = "���𔄂�H";
		}
	}
	// �X��̃Z���t
	// �������Ƃ�
	if (shopmenu == BUY && shopcount >= 0) {
		if (money > price) {
			lines = "�܂��ǁ`";
		}
		else {
			lines = "�o������";
		}
	}
	// �������Ƃ�
	if (shopmenu == SELL && shopcount == (shop - 1)) {
		// ���ȊO�𔄂����Ƃ�
		// shopmY=9:�z��O�Q��
		if (shopmY != 9)
		{
			if (item[shopmY] != 0) {
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
	if (talkflag || shopflag)
	{
		// ������
		DrawFormatString(320, 150, BLACK, "�������F%d�~", money);

		// �b���Ă鑊��̃Z���t
		DrawFormatString(320, 240, BLACK, " %s ", lines.c_str(), money);
	}

	// debug-------------------------------------------------
	DrawFormatString(600, 450, BLACK, " %d ", innflag);
	// --------------------------------------------------------
}

void SafeArea::Draw_End() {
	DrawStringToHandle(0, 0, "���_���", WHITE, Font::Get(eFont::SELECT));
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "�I����� %d / %d", count, endCount);
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
					price = itemm->SearchPrice(2);
					ID = 2;
					break;
				case 1:		// ���炩�Ȑ�
					price = itemm->SearchPrice(3);
					ID = 3;
					break;
				case 2:		// ���ނ�_�}
					price = itemm->SearchPrice(4);
					ID = 4;
					break;
				case 3:		// ���E���̃n
					price = itemm->SearchPrice(5);
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
					price = itemm->SearchPrice(item[shopmY]);
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
	money += itemm->SearchPrice(ID);
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