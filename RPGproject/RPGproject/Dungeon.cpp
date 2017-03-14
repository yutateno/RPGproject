#include "Manager.h"
#include "Dungeon.h"

Dungeon::Dungeon() {
	endFlag = false;
	nextScene = eScene::S_End;
	step = eStep::Start;
	startCount = 0;
	endCount = 0;

	Gr_Back = LoadGraph("Dungeon\\Dungeon_Back.png");
	Gr_Wall = LoadGraph("Dungeon\\wall.png");
	MapData();

	x = 0;
	y = 0;
	fieldflag = false;
	battleflag = false;
	bossflag = false;

	// ���̃}�b�v�͕�4~6���g�p
	for (int i = 4; i <= 6; i++)
	{
		treasure.push_back(i);
	}
	openflag = false;
	treasureflag = false;
	conUI_x = 150;
	conUI_y = 150;
}

Dungeon::~Dungeon() {
	DeleteGraph(Gr_Back);
	DeleteGraph(Gr_Wall);
}

void Dungeon::UpDate() {
	switch (step) {
	case eStep::Start:	// �J�n���
		UpDate_Start();
		break;
	case eStep::Main:	// ���C���������
		UpDate_Main();
		break;
	case eStep::End:	// �I�����
		UpDate_End();
		break;
	default:
		endFlag = true;	// �G���[�I��
		break;
	}
}

void Dungeon::UpDate(int playerX, int playerY) {
	switch (step) {
	case eStep::Start:	// �J�n���
		UpDate_Start();
		break;
	case eStep::Main:	// ���C���������
		UpDate_Main();
		break;
	case eStep::End:	// �I�����
		UpDate_End();
		break;
	default:
		endFlag = true;	// �G���[�I��
		break;
	}
}

void Dungeon::UpDate_Start() {
	startCount++;

	if (startCount < 50) return;	// 50�t���[���ŊJ�n��ʏI��
	step = eStep::Main;
}

void Dungeon::UpDate_Main() {

	// �{�X�`�b�v�ɓ���������퓬���
	if (battleflag == true) {
		this->nextScene = eScene::S_Battle;
		this->step = eStep::End;
	}
	// ����̏ꏊ�s������t�B�[���h��ʂ�
	if (fieldflag == true) {
		this->nextScene = eScene::S_Field;
		this->step = eStep::End;
	}
	// C�L�[�ŃQ�[���N���A��ʂ�
	if (KeyData::Get(KEY_INPUT_C) == 1) {
		this->nextScene = eScene::S_GameClear;
		this->step = eStep::End;
	}
	// �Ȃ񂩕󔠂ɂ���������
	if (treasureflag == true) {
		comment = flame;
		treasureflag = false;
	}
	if (comment > 0) {
		comment--;
	}
}
void Dungeon::UpDate_End() {
	endCount++;

	if (endCount < 50) return;	// 50�t���[���ŏI����ʏI��
	endFlag = true;
}
void Dungeon::Draw() {
	switch (step) {
	case eStep::Start:	// �J�n���
		Draw_Start();
		break;
	case eStep::Main:	// ���C���������
		Draw_Main(x, y);
		break;
	case eStep::End:	// �I�����
		Draw_End();
		break;
	default:
		endFlag = true;	// �G���[�I��
		break;
	}
}

void Dungeon::Draw_Start() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, startCount * 3);
	DrawGraph(0, 0, Gr_Back, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Dungeon::Draw_Main(int x, int y) {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawGraph(0, 0, Gr_Back, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	for (int i = 0, n = (int)map.size(); i < n; i++) {
		for (int j = 0, m = (int)map[i].size(); j < m; j++) {
				//stoi �ŕ����𐔒l�ɕϊ�
			switch ((int)(stoi(map[i][j]) * 0.1)) {
			case 0:	//00
				break;

			case 1:	//��
				switch (stoi(map[i][j]) % 10) {
				case 0:	//10
					DrawGraph(j * 32 - x - 32, i * 32 - y - 32, Gr_Wall, false);
					break;

				default:
					break;
				}
				break;

			case 2:
				switch (stoi(map[i][j]) % 10) {
				case 0:
					DrawBox(j * 32 - x - 32, i * 32 - y - 32, j * 32 - x, i * 32 - y, BLUE, TRUE);
					break;

				default:
					break;
				}
				break;

			case 3:
				switch (stoi(map[i][j]) % 10) {
				case 0:
					DrawBox(j * 32 - x - 32, i * 32 - y - 32, j * 32 - x, i * 32 - y, BLACK, TRUE);
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

	// ��
	for (int i = 0, n = (int)treasure.size(); i < n; i++) {
		treasure[i].Draw(x + 32, y + 32);
	}

	DrawFormatString(320, 400, WHITE, "C�L�[�ŃQ�[���N���A��ʂ�");
}

void Dungeon::Draw_End() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150 - (endCount * 3));
	DrawRotaGraph(320, 240, 1.0, endCount, Gr_Back, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Dungeon::Draw_UI() {
	if (comment > 0) {
		DrawBox(conUI_x - 10, conUI_y - 10, conUI_x + 200, conUI_y + 35, BLACK, true);
		DrawBox(conUI_x - 10, conUI_y - 10, conUI_x + 200, conUI_y + 35, GREEN, false);
		if (openflag == true) {
			DrawFormatString(conUI_x, conUI_y, WHITE, "�Ȃ񂩎�ɓ��ꂽ�I");
		}
		else {
			DrawFormatString(conUI_x, conUI_y, WHITE, "�����������t�̂悤��");
		}
	}
}

void Dungeon::MapData() {
	read_file.open("Dungeon\\DungeonMap.txt");
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

int Dungeon::OpenTreasure(int num) {
	//���u��
	int itemID = treasure[num].GetItemID();

	treasure[num].OpenProcess();

	return itemID;
}

int Dungeon::GetMapData(int x, int y) {
	return stoi(map[(int)(y / 32)][(int)(x / 32)]);
}

int Dungeon::GetMapWidth(){
	return (int)map[0].size();
}
int Dungeon::GetMapHeight(){
	return (int)map.size();
}

void Dungeon::SetX(int x) {
	this->x = x;
}

int Dungeon::GetX() {
	return this->x;
}

void Dungeon::SetY(int y) {
	this->y = y;
}

int Dungeon::GetY() {
	return this->y;
}

void Dungeon::SetField(bool flag) {
	fieldflag = flag;
}

bool Dungeon::GetField() {
	return fieldflag;
}

void Dungeon::SetBattle(bool flag) {
	battleflag = flag;
}

bool Dungeon::GetBattle() {
	return battleflag;
}

void Dungeon::SetBoss(bool flag) {
	bossflag = flag;
}

bool Dungeon::GetBoss() {
	return bossflag;
}

int Dungeon::GetTreasureNum() {
	int n = (int)treasure.size();
	return n;
}

int Dungeon::GetTreasureX(int num) {
	return treasure[num].GetX();
}

int Dungeon::GetTreasureY(int num) {
	return treasure[num].GetY();
}

void Dungeon::SetOpen(bool flag) {
	openflag = flag;
}

bool Dungeon::GetOpen() {
	return openflag;
}

void Dungeon::SetTreasure(bool flag) {
	treasureflag = flag;
}

bool Dungeon::GetTreasure() {
	return treasureflag;
}

eStep Dungeon::GetStep(){
	return step;
}