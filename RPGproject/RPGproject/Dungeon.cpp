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

	x = 0;
	y = 0;
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
	MapData();
}
void Dungeon::UpDate_Start() {
	startCount++;

	if (startCount < 50) return;	// 50�t���[���ŊJ�n��ʏI��
	step = eStep::Main;
}

void Dungeon::UpDate_Main() {

	// Z�L�[�Ő퓬��ʂ�
	if (KeyData::Get(KEY_INPUT_Z) == 1) {
		this->nextScene = eScene::S_Battle;
		this->step = eStep::End;
	}
	// X�L�[�Ńt�B�[���h��ʂ�
	if (KeyData::Get(KEY_INPUT_X) == 1) {
		this->nextScene = eScene::S_Field;
		this->step = eStep::End;
	}
	// C�L�[�ŃQ�[���N���A��ʂ�
	if (KeyData::Get(KEY_INPUT_C) == 1) {
		this->nextScene = eScene::S_GameClear;
		this->step = eStep::End;
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
		Draw_Main(GetX(), GetY());
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
					DrawGraph(j * 32 - x, i * 32 - y, Gr_Wall, false);
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

	DrawStringToHandle(0, 200, "Z�L�[�Ő퓬��ʂ�", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 300, "X�L�[�Ńt�B�[���h��ʂ�", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 400, "C�L�[�ŃQ�[���N���A��ʂ�", WHITE, Font::Get(eFont::SELECT));
}

void Dungeon::Draw_End() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150 - (endCount * 1));
	DrawRotaGraph(320, 240, 1.0, endCount * 1, Gr_Back, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
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
}

int Dungeon::GetMapData(int x, int y) {
	return stoi(map[(int)(y / 32)][(int)(x / 32)]);	//28�ɒ���
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