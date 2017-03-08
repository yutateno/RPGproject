#include "Manager.h"
#include "SafeArea.h"

SafeArea::SafeArea() {
	this->endFlag = false;
	this->nextScene = eScene::S_End;
	this->step = eStep::Start;
	this->startCount = 0;
	this->endCount = 0;
	MapData();

	Gr_Wall = LoadGraph("Dungeon\\wall.png");
	Gr_Back = LoadGraph("img\\safearea_background.png");

	x = 0;
	y = 0;
	fieldflag = false;
	peopleflag = false;
	itemflag = false;
	healflag = false;
	healY = false;
	talkflag = false;
	shopflag = false;
	buyflag = false;
	sellflag = false;
	healcount = 0;
	shopcount = 0;
	shopmenu = 0;
	shopmY = 0;
	money = 0;
	premoney = 0;
	ID = 0;
	for (int i = 0; i < 9; i++) {
		item[i] = 0;
	}
	itemm = new Item();
}
SafeArea::~SafeArea() {
	DeleteGraph(Gr_Wall);
	DeleteGraph(Gr_Back);
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
	this->startCount++;

	if (this->startCount < 50) return;	// 50�t���[���ŊJ�n��ʏI��
	this->step = eStep::Main;
}

void SafeArea::UpDate_Main() {

	//// X�L�[�Ő퓬��ʂ�
	//if (KeyData::Get(KEY_INPUT_X) == 1) {
	//	this->nextScene = eScene::S_Battle;
	//	this->step = eStep::End;
	//}

	// ����̏ꏊ�s������t�B�[���h��ʂ�
	if (fieldflag == true) {
		this->nextScene = eScene::S_Field;
		this->step = eStep::End;
	}

	HealProcess();
	PeopleProcess();
	ShopProcess();
}

void SafeArea::UpDate_End() {
	this->endCount++;

	if (this->endCount < 50) return;	// 50�t���[���ŏI����ʏI��
	this->endFlag = true;
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
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "�J�n���%d", this->startCount);
}

void SafeArea::Draw_Main(int x, int y) {

	DrawGraph(0, 0, Gr_Back, false);

	for (int i = 0, n = (int)map.size(); i < n; i++) {
		for (int j = 0, m = (int)map[i].size(); j < m; j++) {
			//stoi �ŕ����𐔒l�ɕϊ�
			switch ((int)(stoi(map[i][j]) * 0.1)) {
			case 0:	//00
				break;

			case 1:	//��
				switch (stoi(map[i][j]) % 10) {
				case 0:	//10
					DrawGraph(j * 32 - x, i * 32 - y, Gr_Wall, false);
					break;

				case 1:
					DrawBox(j * 32 - x, i * 32 - y, j * 32 - x + 32, i * 32 - y + 32, BLUE, TRUE);	// �o��
					break;

				case 2:
					DrawBox(j * 32 - x, i * 32 - y, j * 32 - x + 32, i * 32 - y + 32, WHITE, TRUE);	// �ē��l
					break;

				case 3:
					DrawBox(j * 32 - x, i * 32 - y, j * 32 - x + 32, i * 32 - y + 32, YELLOW, TRUE);	// ���
					break;

				case 4:
					DrawBox(j * 32 - x, i * 32 - y, j * 32 - x + 32, i * 32 - y + 32, RED, TRUE);	// ����
					break;

				default:
					break;
				}
				break;

			default:
				break;
			}
		}
	}

	// �񕜓X��
	if (innflag == true && talkflag == true) {
		DrawFormatString(320, 150, BLACK, "�������F%d�~", premoney);
		DrawFormatString(320, 118, BLACK, "100�~");
		DrawFormatString(0, cursor * 0, BLACK, "���܂�܂����H");
		DrawFormatString(35, cursor * 1, BLACK, "�x�݂܂�");
		DrawFormatString(35, cursor * 2, BLACK, "��߂Ƃ��܂�");
		DrawBox(0, (healY + 1) * cursor, 32, 32 + ((healY + 1) * cursor), BLUE, true);
	}
	// �񕜕\��
	if (healcount > 0) {
		if (premoney > money) {
			DrawFormatString(320, 240, BLACK, "�񕜂��܂����B");
		}
		else {
			DrawFormatString(320, 240, BLACK, "�o������");
		}
	}

	// ���l�̃Z���t
	if (peopleflag == true && talkflag == true) {
		DrawFormatString(320, 240, BLACK, "�����͒��ł��B");
	}

	//�������֘A----------------------------------------------------
	if (itemflag == true && shopflag == true) {
		// ������
		DrawFormatString(320, 150, BLACK, "�������F%d�~", premoney);
		// �ŏ��̃��j���[
		if (shopmenu == 0) {
			DrawFormatString(35, cursor * 0, BLACK, "����");
			DrawFormatString(35, cursor * 1, BLACK, "����");
			DrawFormatString(35, cursor * 2, BLACK, "��߂�");
			DrawBox(0, shopmY * cursor, 32, 32 + (shopmY * cursor), BLUE, true);
			DrawFormatString(320, 240, BLACK, "���������[��");
		}
		// �����Ƃ��̃��j���[
		else if(shopmenu == 1) {
			DrawFormatString(35, cursor * 0, BLACK, "�₭(�ɂ���������)����");
			DrawFormatString(35, cursor * 1, BLACK, "���炩�Ȑ�");
			DrawFormatString(35, cursor * 2, BLACK, "���ނ�_�}");
			DrawFormatString(35, cursor * 3, BLACK, "���E���̃n");
			DrawFormatString(35, cursor * 4, BLACK, "�߂�");
			DrawBox(0, shopmY * cursor, 32, 32 + (shopmY * cursor), BLUE, true);
			DrawFormatString(320, 240, BLACK, "���𔃂��H");
			if (shopmY < 4) {
				DrawFormatString(320, 118, BLACK, "%d�~", money);
			}
		}
		// ����Ƃ��̃��j���[
		else {
			for (int i = 0; i < 9; i++)
			{
				DrawFormatString(35, cursor * i, BLACK, itemm->SearchName(item[i]).c_str());
			}
			DrawFormatString(35, cursor * 9, BLACK, "�߂�");
			DrawBox(0, shopmY * cursor, 32, 32 + (shopmY * cursor), BLUE, true);
			DrawFormatString(320, 240, BLACK, "���𔄂�H");
			if (shopmY != 9) {
				DrawFormatString(320, 118, BLACK, "%d�~", money);
			}
		}
	}
	// �X��̃Z���t
	// �������Ƃ�
	if (shopmenu == 1 && shopcount >= 0) {
		if (premoney > money) {
			DrawFormatString(320, 208, BLACK, "�܂��ǁ`");
		}
		else {
			DrawFormatString(320, 208, BLACK, "�o������");
		}
	}
	// �������Ƃ�
	if (shopmenu == 2 && shopcount >= 0) {
		// ���ȊO�𔄂����Ƃ�
		if (item[shopmY] != 0) {
			DrawFormatString(320, 208, BLACK, "�܂��ǁ`");
		}
		// ���𔄂�Ƃ�
		else {
			DrawFormatString(320, 208, BLACK, "�͂�");
		}
	}
	//--------------------------------------------------------------
}

void SafeArea::Draw_End() {
	DrawStringToHandle(0, 0, "���_���", WHITE, Font::Get(eFont::SELECT));
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "�I�����%d", this->endCount);
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
	// �h�̓X��ɐG�ꂽ��
	if (innflag == true) {
		if (KeyData::Get(KEY_INPUT_Z) == 1) {
			// �Z���t���o����
			money = 100;
			if (talkflag == true) {
				// �񕜗��񂾂�
				if (healY == 0) {
					// ���������
					if (premoney >= money) {
						premoney -= money;
						healflag = true;
					}
					// �����Ȃ����
					else {
						
					}
					healcount = heal;
					healY = 0;
				}
				// �񕜂�߂���
				else {
					healY = 0;
				}
				talkflag = false;
			}
			// �G�ꂽ�����̎�
			else {
				talkflag = true;
			}
		}
	}
	// �I����
	if (innflag == true && talkflag == true) {
		if (KeyData::Get(KEY_INPUT_UP) == 1) {
			healY = 0;
		}
		if (KeyData::Get(KEY_INPUT_DOWN) == 1) {
			healY = 1;
		}
	}
	// �񕜂̕\��
	if (healcount > 0) {
		healcount--;
	}
}

void SafeArea::PeopleProcess() {
	// ��ʐl�ɐG�ꂽ��
	if (peopleflag == true) {
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
}

void SafeArea::ShopProcess() {
	// ����ɐG�ꂽ��
	if (itemflag == true) {
		if (KeyData::Get(KEY_INPUT_Z) == 1) {
			// �������̍ŏ��̉��
			if (shopflag == true) {
				if (shopmenu == 0) {
					// �������������Ƃ�
					if (shopmY == 0) {
						shopmenu = 1;
					}
					// ������������Ƃ�
					else if (shopmY == 1) {
						shopmenu = 2;
					}
					// ��߂���������Ƃ�
					else {
						shopflag = false;
					}
					shopmY = 0;
				}
				// �������J�����Ƃ��̃V���b�v���
				else if (shopmenu == 1) {
					if (shopmY < 4) {
						if (premoney >= money) {
							ID = shopmY + 2;
							buyflag = true;
							premoney -= money;
						}
						else {

						}
						shopcount = shop;
					}
					else {
						shopmenu = 0;
						shopmY = 0;
					}
				}
				// ������J�����Ƃ��̃V���b�v���
				else if (shopmenu == 2) {
					// �߂�{�^��
					if (shopmY == 9) {
						shopmenu = 0;
						shopmY = 0;
					}
					// �Ȃɂ����甄��
					else {
						premoney += money;
						itemnum = shopmY;
						ID = item[shopmY];
						shopcount = shop;
						sellflag = true;
					}
				}
			}
			// �G�ꂽ�����̎�
			else {
				shopflag = true;
			}
		}
	}
	// �V���b�v�̔�����̉�b�\��
	if (shopcount >= 0) {
		shopcount--;
	}
	// �����Ƃ��̃V���b�v�̒l�i�\��
	if (shopmenu == 1) {
		switch (shopmY) {
		case 0:
			money = 10;
			break;
		case 1:
			money = 15;
			break;
		case 2:
			money = 10;
			break;
		case 3:
			money = 20;
			break;
		default:
			money = 0;
			break;
		}
	}
	// ����Ƃ��̃V���b�v�̒l�i�\��
	if (shopmenu == 2) {
		switch (item[shopmY]) {
		case 2:
			money = 5;
			break;
		case 3:
			money = 7;
			break;
		case 4:
			money = 5;
			break;
		case 5:
			money = 10;
			break;
		default:
			money = 0;
			break;
		}
	}
	// �V���b�v��ʂł̃J�[�\���ړ�
	if (shopflag == true && itemflag == true) {
		// ���������
		if (KeyData::Get(KEY_INPUT_UP) == 1) {
			// ��ԏザ��Ȃ����
			if (shopmY > 0) {
				shopmY--;
			}
			// ��ԏ�Ȃ�
			else {

			}
		}
		// ����������
		if (KeyData::Get(KEY_INPUT_DOWN) == 1) {
			if (shopmenu == 0) {
				// ��ԉ�����Ȃ����
				if (shopmY < 2) {
					shopmY++;
				}
				// ��ԉ��Ȃ�
				else {

				}
			}
			else if (shopmenu == 1) {
				// ��ԉ�����Ȃ����
				if (shopmY < 4) {
					shopmY++;
				}
				// ��ԉ��Ȃ�
				else {

				}
			}
			else {
				// ��ԉ�����Ȃ����
				if (shopmY < 9) {
					shopmY++;
				}
				// ��ԉ��Ȃ�
				else {

				}
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

void SafeArea::SetNum(int num) {
	itemnum = num;
}

int SafeArea::GetNum() {
	return itemnum;
}

void SafeArea::SetnumID(int num, int ID) {
	item[num] = ID;
}

void SafeArea::SetMoney(int money) {
	premoney = money;
}

int SafeArea::GetMoney() {
	return premoney;
}

eStep SafeArea::GetStep() {
	return step;
}