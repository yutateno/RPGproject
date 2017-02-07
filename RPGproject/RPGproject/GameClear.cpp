#include "Manager.h"

GameClear::GameClear() {
	this->endFlag = false;
	this->nextScene = eScene::S_End;
	this->step = eStep::Start;
	this->startCount = 0;
	this->endCount = 0;

}
GameClear::~GameClear() {

}

void GameClear::UpDate() {
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
void GameClear::UpDate_Start() {
	this->startCount++;

	if (this->startCount < 50) return;	// 50�t���[���ŊJ�n��ʏI��
	this->step = eStep::Main;
}
void GameClear::UpDate_Main() {

	// Z�L�[�Ń^�C�g����ʂ�
	if (KeyData::Get(KEY_INPUT_Z) == 1) {
		this->nextScene = eScene::S_Title;
		this->step = eStep::End;
	}
	// X�L�[�ŃQ�[���I��
	if (KeyData::Get(KEY_INPUT_X) == 1) {
		this->nextScene = eScene::S_End;
		this->step = eStep::End;
	}
}
void GameClear::UpDate_End() {
	this->endCount++;

	if (this->endCount < 50) return;	// 50�t���[���ŏI����ʏI��
	this->endFlag = true;
}
void GameClear::Draw() {
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
void GameClear::Draw_Start() {
	DrawStringToHandle(0, 0, "�Q�[���N���A���", WHITE, Font::Get(eFont::SELECT));
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "�J�n���%d", this->startCount);
}
void GameClear::Draw_Main() {
	DrawStringToHandle(0, 0, "�Q�[���N���A���", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 100, "���C���������", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 200, "Z�L�[�Ń^�C�g����ʂ�", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 300, "X�L�[�ŃQ�[���I��", WHITE, Font::Get(eFont::SELECT));
}
void GameClear::Draw_End() {
	DrawStringToHandle(0, 0, "�Q�[���N���A���", WHITE, Font::Get(eFont::SELECT));
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "�I�����%d", this->endCount);
}