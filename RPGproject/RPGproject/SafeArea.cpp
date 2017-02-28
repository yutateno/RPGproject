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
	waitflag = false;
	healcount = 0;
	talkcount = 0;
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

	//// ��ʐl�ɐG�ꂽ��
	//if (peopleflag == true && waitflag == false) {
	//	if (KeyData::Get(KEY_INPUT_Z) == 1) {
	//		waitflag = true;
	//		talkcount = talkwait;
	//	}
	//}
	//if (waitflag == true) {
	//	if (talkcount < 0) {
	//		talkcount--;
	//	}
	//	if (talkcount == 0) {
	//		if (KeyData::Get(KEY_INPUT_Z) == 1) {
	//			peopleflag = false;
	//		}
	//	}
	//}
	//if (peopleflag == false && waitflag == true) {
	//	talkcount++;
	//	if (talkcount > talkwait) {
	//		talkflag = false;
	//		waitflag = false;
	//		talkcount = 0;
	//	}
	//}
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

	/*if (peopleflag == true && talkflag == true) {
		DrawFormatString(320, 240, BLACK, "�����͒��ł��B");
	}
	DrawFormatString(0, 0, BLACK, "%d", talkcount);*/
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
	if (fieldflag == true) {
		return true;
	}
	else {
		return false;
	}
}

void SafeArea::SetPeople(bool flag) {
	peopleflag = flag;
}

bool SafeArea::GetPeople() {
	if (peopleflag == true) {
		return true;
	}
	else {
		return false;
	}
}

void SafeArea::SetItem(bool flag) {
	itemflag = flag;
}

bool SafeArea::GetItem() {
	if (itemflag == true) {
		return true;
	}
	else {
		return false;
	}
}

void SafeArea::SetHeal(bool flag) {
	healflag = flag;
}

bool SafeArea::GetHeal() {
	if (healflag == true) {
		return true;
	}
	else {
		return false;
	}
}

void SafeArea::SetTalk(bool flag) {
	talkflag = flag;
}

bool SafeArea::GetTalk() {
	if (talkflag == true) {
		return true;
	}
	else {
		return false;
	}
}

eStep SafeArea::GetStep() {
	return step;
}