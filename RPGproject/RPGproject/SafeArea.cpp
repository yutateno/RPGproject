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
	talkflag = false;
	shopflag = false;
	buyflag = false;
	sellflag = false;
	healcount = 0;
	shopmenu = 0;
	shopmY = 0;
	money = 0;
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

	// �����ɐG�ꂽ��
	if (healflag == true) {
		if (KeyData::Get(KEY_INPUT_Z) == 1) {
			healcount = heal;
		}
	}

	// ��ʐl�ɐG�ꂽ��
	if (peopleflag == true) {
		if (KeyData::Get(KEY_INPUT_Z) == 1) {
			if (talkflag == false) {
				talkflag = true;
			}
			else {
				talkflag = false;
			}
		}
	}
	
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
					switch (shopmY) {
					case 0:
						//str = "�₭(�ɂ���������)����";
						ID = 2;
						buyflag = true;
						break;
					case 1:
						//str = "���炩�Ȑ�";
						ID = 3;
						buyflag = true;
						break;
					case 2:
						//str = "���ނ�_�}";
						ID = 3;
						buyflag = true;
						break;
					case 3:
						//str = "���E���̃n";
						ID = 4;
						buyflag = true;
						break;
					default:
						shopmenu = 0;
						shopmY = 0;
						break;
					}
				}
				// ������J�����Ƃ��̃V���b�v���
				else if (shopmenu == 2) {
					switch (shopmY) {
					case 0:
						//str = "�₭(�ɂ���������)����";
						break;
					case 1:
						//str = "���炩�Ȑ�";
						break;
					case 2:
						//str = "���ނ�_�}";
						break;
					case 3:
						//str = "���E���̃n";
						break;
					default:
						shopmenu = 0;
						shopmY = 0;
						break;
					}
				}
			}
			// �G�ꂽ�����̎�
			else {
				shopflag = true;
			}
		}
	}
	// �V���b�v�̒l�i�\��
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
		}
	}
	// �V���b�v��ʂł̃J�[�\���ړ�
	if (shopflag == true && itemflag == true) {
		// ���������
		if (KeyData::Get(KEY_INPUT_UP) == 1) {
			// ��ԏザ��Ȃ����
			if (shopmY > 0) {
				shopmY --;
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

	if (healcount > 0) {
		DrawFormatString(320, 240, BLACK, "�񕜂��܂����B");
		healcount--;
	}

	if (peopleflag == true && talkflag == true) {
		DrawFormatString(320, 240, BLACK, "�����͒��ł��B");
	}

	if (itemflag == true && shopflag == true) {
		if (shopmenu == 0) {
			DrawFormatString(35, cursor * 0, BLACK, "����");
			DrawFormatString(35, cursor * 1, BLACK, "����");
			DrawFormatString(35, cursor * 2, BLACK, "��߂�");
			DrawBox(0, shopmY * cursor, 32, 32 + (shopmY * cursor), BLUE, true);
			DrawFormatString(320, 240, BLACK, "���������[��");
		}
		else if(shopmenu == 1) {
			DrawFormatString(35, cursor * 0, BLACK, "�₭(�ɂ���������)����");
			DrawFormatString(35, cursor * 1, BLACK, "���炩�Ȑ�");
			DrawFormatString(35, cursor * 2, BLACK, "���ނ�_�}");
			DrawFormatString(35, cursor * 3, BLACK, "���E���̃n");
			DrawFormatString(35, cursor * 4, BLACK, "�߂�");
			DrawBox(0, shopmY * cursor, 32, 32 + (shopmY * cursor), BLUE, true);
			DrawFormatString(320, 240, BLACK, "���𔃂��H");
			if (shopmY < 4) {
				DrawFormatString(70, cursor * 6, BLACK, "%d�~�ł��B", money);
			}
		}
		else {
			for (int i = 0; i < 9; i++)
			{
				DrawFormatString(35, cursor * i, BLACK, itemm->SearchName(item[i]).c_str());
			}
			DrawFormatString(35, cursor * 9, BLACK, "�߂�");
			DrawBox(0, shopmY * cursor, 32, 32 + (shopmY * cursor), BLUE, true);
			DrawFormatString(320, 240, BLACK, "���𔄂�H");
			if (shopmY < 9) {
				DrawFormatString(70, cursor * 11, BLACK, "%d�~�ł��B", money);
			}
		}
	}
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

void SafeArea::SetID(int ID) {
	this->ID = ID;
}

int SafeArea::GetID() {
	return ID;
}

void SafeArea::SetnumID(int num, int ID) {
	item[num] = ID;
}

eStep SafeArea::GetStep() {
	return step;
}