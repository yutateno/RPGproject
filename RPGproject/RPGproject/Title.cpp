#include "Manager.h"

Title::Title() {
	endFlag = false;
	nextScene = eScene::S_End;
	step = eStep::Start;
	startCount = 0;
	endCount = 0;
	Icon_x = 140;
	Icon_y = 300;
	Icon_area = 0;
	Gr_Back = LoadGraph("Title.png");
}
Title::~Title() {
	DeleteGraph(Gr_Back);
}

void Title::UpDate() {
	switch (step){
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
void Title::UpDate_Start() {
	startCount++;
	
	if (startCount < 50) return;	// 50�t���[���ŊJ�n��ʏI��
	step = eStep::Main;
}
void Title::UpDate_Main() {
	if (KeyData::Get(KEY_INPUT_UP) >= 1) {
		Icon_area = 0;
	}
	if (KeyData::Get(KEY_INPUT_DOWN) >= 1) {
		Icon_area = 1;
	}
	if (KeyData::Get(KEY_INPUT_Z) >= 1) {
		if (Icon_area == 0) {
			nextScene = eScene::S_Field;
			step = eStep::End;
		}
		else {
			nextScene = eScene::S_End;
			step = eStep::End;
		}
	}
}
void Title::UpDate_End() {
	endCount++;

	if (endCount < 50) return;	// 50�t���[���ŏI����ʏI��
	endFlag = true;
}
void Title::Draw() {
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
void Title::Draw_Start() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, startCount * 5);
	DrawGraph(0, 0, Gr_Back, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
void Title::Draw_Main() {
	DrawGraph(0, 0, Gr_Back, FALSE);

	DrawBox(Icon_x, Icon_y + (Icon_area * 70), Icon_x + 50, Icon_y + 50 + (Icon_area * 70), BLUE, TRUE);

	DrawString(0, 450, "�㉺�ňړ��AZ�Ō���",WHITE);
}
void Title::Draw_End() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (endCount * 5));
	DrawGraph(0, 0, Gr_Back, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}