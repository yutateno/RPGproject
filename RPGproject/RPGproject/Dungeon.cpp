#include "Manager.h"

Dungeon::Dungeon() {
	this->endFlag = false;
	this->nextScene = eScene::S_End;
	this->step = eStep::Start;
	this->startCount = 0;
	this->endCount = 0;

}
Dungeon::~Dungeon() {

}

void Dungeon::UpDate() {
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
void Dungeon::UpDate_Start() {
	this->startCount++;

	if (this->startCount < 50) return;	// 50�t���[���ŊJ�n��ʏI��
	this->step = eStep::Main;
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
	this->endCount++;

	if (this->endCount < 50) return;	// 50�t���[���ŏI����ʏI��
	this->endFlag = true;
}
void Dungeon::Draw() {
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
void Dungeon::Draw_Start() {
	DrawStringToHandle(0, 0, "�_���W�������", WHITE, Font::Get(eFont::SELECT));
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "�J�n���%d", this->startCount);
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