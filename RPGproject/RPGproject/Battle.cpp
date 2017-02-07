#include "Manager.h"

Battle::Battle() {
	this->endFlag = false;
	this->nextScene = eScene::S_End;
	this->step = eStep::Start;
	this->startCount = 0;
	this->endCount = 0;

}
Battle::~Battle() {

}

void Battle::UpDate() {
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
void Battle::UpDate_Start() {
	this->startCount++;

	if (this->startCount < 50) return;	// 50�t���[���ŊJ�n��ʏI��
	this->step = eStep::Main;
}
void Battle::UpDate_Main() {

	// Z�L�[�Ő퓬�I���@��O�̉�ʂ�
	if (KeyData::Get(KEY_INPUT_Z) == 1) {
		this->step = eStep::End;
	}
	// X�L�[�Ŏ��S��ʂ�
	if (KeyData::Get(KEY_INPUT_X) == 1) {
		this->nextScene = eScene::S_GameOver;
		this->step = eStep::End;
	}

}
void Battle::UpDate_End() {
	this->endCount++;

	if (this->endCount < 50) return;	// 50�t���[���ŏI����ʏI��
	this->endFlag = true;
}
void Battle::Draw() {
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
void Battle::Draw_Start() {
	DrawStringToHandle(0, 0, "�퓬���", WHITE, Font::Get(eFont::SELECT));
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "�J�n���%d", this->startCount);
}
void Battle::Draw_Main() {
	DrawStringToHandle(0, 0, "�퓬���", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 100, "���C���������", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 200, "Z�L�[�Ő퓬�I���@��O�̉�ʂ�", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 300, "X�L�[�ŃQ�[���I�[�o�[��ʂ�", WHITE, Font::Get(eFont::SELECT));
}
void Battle::Draw_End() {
	DrawStringToHandle(0, 0, "�퓬���", WHITE, Font::Get(eFont::SELECT));
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "�I�����%d", this->endCount);
}


// �ǂ̉�ʂ���퓬��ʂɈڍs�������i�퓬�I�����ɂ��̉�ʂɖ߂�)
void Battle::SetReturnScene(eScene scene) {
	this->nextScene = scene;
}