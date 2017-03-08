#include "Manager.h"

Title::Title() {
	// �摜�֌W
	Gr_Back = LoadGraph("Title.png");

	// ����֌W
	endFlag = false;			// �V�[���̏I���̃t���O
	nextScene = eScene::S_End;	// ���ɃQ�[���I�����������̃V�[���Ƃ��ď�����

	// ���o�֌W
	step = eStep::Start;		// ���̃V�[���̊J�n����
	startCount = 0;				// ���̃J�E���g���������o���Ԃ�����
	endCount = 0;				// ���̃J�E���g�������I�����o������
	count = 0;					// (�t���[��)���Ԃ��v��

	// �A�C�R���֌W
	Icon_x = 140;				// �A�C�R���̐�΍��W
	Icon_y = 300;				// �A�C�R���̐�΍��W
	Icon_area = 0;				// ���ΓI�ȃA�C�R���̍��W
}
Title::~Title() {
	// �摜�폜
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
	// �J�E���g�A�b�v
	count++;
	
	// startCount�������o����
	if (count < startCount) return;
	// �J�E���g�����Z�b�g���ăX�e�b�v��i�s
	count = 0;
	step = eStep::Main;
}
void Title::UpDate_Main() {
	// �A�C�R���̈ړ�
	if (KeyData::Get(KEY_INPUT_UP) == 1) {
		Icon_area = 0;
	}
	if (KeyData::Get(KEY_INPUT_DOWN) == 1) {
		Icon_area = 1;
	}

	// ����
	if (KeyData::Get(KEY_INPUT_Z) == 1) {
		// ���΍��W���玟�ɍs���V�[����ݒ�
		if (Icon_area == 0) {
			// �t�B�[���h��
			nextScene = eScene::S_Field;
			// �X�e�b�v�i�s
			step = eStep::End;
		}
		else {
			// �Q�[���I����ʂ�
			nextScene = eScene::S_End;
			// �X�e�b�v�i�s
			step = eStep::End;
		}
	}
}
void Title::UpDate_End() {
	// �J�E���g�A�b�v
	count++;

	// endCount�������o����
	if (count < endCount) return;
	// �J�E���g�����Z�b�g���Ă��̃V�[�����I������
	count = 0;
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
	// ���X�ɉ�ʂ̕\�����鏈��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, count * 5);
	// �w�i
	DrawGraph(0, 0, Gr_Back, FALSE);
	// �u�����h���[�h�̌㏈��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
void Title::Draw_Main() {
	// �w�i
	DrawGraph(0, 0, Gr_Back, FALSE);

	// �I���A�C�R��
	DrawBox(Icon_x, Icon_y + (Icon_area * 70), Icon_x + 50, Icon_y + 50 + (Icon_area * 70), BLUE, TRUE);

	// TIPS
	DrawString(0, 450, "�㉺�ňړ��AZ�Ō���", BLUE);
}
void Title::Draw_End() {
	// ���X�ɉ�ʂ��Â����鏈��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (count * 5));
	// �w�i
	DrawGraph(0, 0, Gr_Back, FALSE);
	// �u�����h���[�h�̌㏈��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}