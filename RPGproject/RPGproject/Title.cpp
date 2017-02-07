#include "Manager.h"

Title::Title() {
	this->endFlag = false;
	this->nextScene = eScene::S_End;
	this->step = eStep::Start;
	this->startCount = 0;
	this->endCount = 0;

}
Title::~Title() {

}

void Title::UpDate() {
	switch (this->step){
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
void Title::UpDate_Start() {
	this->startCount++;
	
	if (this->startCount < 50) return;	// 50�t���[���ŊJ�n��ʏI��
	this->step = eStep::Main;
}
void Title::UpDate_Main() {

	// Z�L�[�Ńt�B�[���h��ʂ�
	if (KeyData::Get(KEY_INPUT_Z) >= 1) {
		this->nextScene = eScene::S_Field;
		this->step = eStep::End;
	}
	// X�L�[�ŃQ�[���I��
	if (KeyData::Get(KEY_INPUT_X) == 1) {
		this->nextScene = eScene::S_End;
		this->step = eStep::End;
	}

}
void Title::UpDate_End() {
	this->endCount++;

	if (this->endCount < 50) return;	// 50�t���[���ŏI����ʏI��
	this->endFlag = true;
}
void Title::Draw() {
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
void Title::Draw_Start() {
	DrawStringToHandle(0, 0, "�^�C�g�����", WHITE, Font::Get(eFont::SELECT));
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "�J�n���%d", this->startCount);
}
void Title::Draw_Main() {
	DrawStringToHandle(0, 0, "�^�C�g�����", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 100, "���C���������", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 200, "Z�L�[�Ńt�B�[���h", WHITE, Font::Get(eFont::SELECT));
	DrawStringToHandle(0, 300, "X�L�[�ŃQ�[���I��", WHITE, Font::Get(eFont::SELECT));
}
void Title::Draw_End() {
	DrawStringToHandle(0, 0, "�^�C�g�����", WHITE, Font::Get(eFont::SELECT));
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "�I�����%d", this->endCount);

}