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
	Gr_Player = LoadGraph("Dungeon\\player.png");
}

Dungeon::~Dungeon() {

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
		Draw_Main();
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
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, startCount * 1);
	DrawRotaGraph(320, 240, 1.0, startCount * 1, Gr_Back, FALSE);	//��]�p�x 1  �V��ł�"����"
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//DrawStringToHandle(0, 0, "�_���W�������", WHITE, Font::Get(eFont::SELECT));
	//DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "�J�n���%d", this->startCount);
}

void Dungeon::Draw_Main() {
	DrawStringToHandle(0, 0, "�_���W�������", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 100, "���C���������", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 200, "Z�L�[�Ő퓬��ʂ�", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 300, "X�L�[�Ńt�B�[���h��ʂ�", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 400, "C�L�[�ŃQ�[���N���A��ʂ�", WHITE, Font::Get(eFont::SELECT));
}

void Dungeon::Draw_End() {
	DrawStringToHandle(0, 0, "�_���W�������", WHITE, Font::Get(eFont::SELECT));
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "�I�����%d", this->endCount);
}