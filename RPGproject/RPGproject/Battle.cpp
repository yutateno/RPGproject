#include "Manager.h"

Battle::Battle() {
	this->endFlag = false;
	this->nextScene = eScene::S_End;
	this->step = eStep::Start;
	this->startCount = 0;
	this->endCount = 0;

	// �摜
	Gr_Back = LoadGraph("img\\battle_background.png");		// �w�i

	// �R�}���h���
	command = NEUTRAL;

	// �J�[�\�����W
	cursorX = 0;
	cursorY = 0;
}
Battle::~Battle() {
	DeleteGraph(Gr_Back);
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

	// �J�[�\���ړ�
	if (KeyData::Get(KEY_INPUT_UP) == 1 && cursorY>0)
	{
		cursorY -= 100;
	}
	if (KeyData::Get(KEY_INPUT_DOWN) == 1 && cursorY<200)
	{
		cursorY += 100;
	}

	// Z�L�[�Ō���
	if (KeyData::Get(KEY_INPUT_Z) == 1) {
		switch (command)
		{
		case NEUTRAL:	// ����
			if (cursorY == 0)		// �U���I����
			{
				command = ATTACK;
			}
			else if (cursorY == 100)// ���@�I����
			{
				command = MAGIC;
			}
			else{					// ������I����
				command = RUN_AWAY;
			}
			break;

		case ATTACK:	// �U�����j���[
			if (cursorY == 0)		// ��U���I����
			{
				// �����ɐ퓬����������
				command = DATTACK;
			}
			else if (cursorY == 100)// ���U���I����
			{
				// �����ɐ퓬����������
				command = DATTACK;
			}
			else {					// �߂�I����
				cursorY = 0;		// �J�[�\�������Ƃ̈ʒu�ɖ߂�
				command = NEUTRAL;
			}
			break;

		case DATTACK:	// Manager�ɏ��������Ă�
			break;

		case MAGIC:		// ���@���j���[
			if (cursorY == 0)		// �㖂�@�I����
			{
				// �����ɐ퓬����������
				command = DMAGIC;
			}
			else if (cursorY == 100)// �����@�I����
			{
				// �����ɐ퓬����������
				command = DMAGIC;
			}
			else {					// �߂�I����
				cursorY = 0;		// �J�[�\�������Ƃ̈ʒu�ɖ߂�
				command = NEUTRAL;
			}
			break;

		case DMAGIC:	// Manager�ɏ��������Ă�
			break;

		case RUN_AWAY:	// ������
			break;

		default:		// �݂蓾�Ȃ��B�G���[
			endFlag = true;
			break;
		}
	}

	// ��������
	if (command == RUN_AWAY)
	{
		step = eStep::End;	// �퓬�I��
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
	// �w�i
	DrawGraph(0, 0, Gr_Back, true);

	// �R�}���h��Ԃɉ����ĕ\����ω�
	switch (command)
	{
	case NEUTRAL:	// ����
		DrawStringToHandle(0, 0, "  �U��", WHITE, Font::Get(eFont::SELECT));
		DrawStringToHandle(0, 100, "  ���@", WHITE, Font::Get(eFont::SELECT));
		DrawStringToHandle(0, 200, "  ������", WHITE, Font::Get(eFont::SELECT));
		break;

	case ATTACK:	// �U�����j���[
		DrawStringToHandle(0, 0, "  ��U��", WHITE, Font::Get(eFont::SELECT));
		DrawStringToHandle(0, 100, "  ���U��", WHITE, Font::Get(eFont::SELECT));
		DrawStringToHandle(0, 200, "  �߂�", WHITE, Font::Get(eFont::SELECT));
		break;

	case MAGIC:		// ���@���j���[
		DrawStringToHandle(0, 0, "  �㖂�@", WHITE, Font::Get(eFont::SELECT));
		DrawStringToHandle(0, 100, "  �����@", WHITE, Font::Get(eFont::SELECT));
		DrawStringToHandle(0, 200, "  �߂�", WHITE, Font::Get(eFont::SELECT));
		break;

	case RUN_AWAY:	// ������
		//DrawStringToHandle(0, 0, "  ���Ȃ��͓����o�����E�E�E", WHITE, Font::Get(eFont::SELECT));
		break;

	default:		// �݂蓾�Ȃ��B�G���[
		endFlag = true;
		break;
	}
	
	// �J�[�\��
	DrawStringToHandle(cursorX, cursorY, "��", WHITE, Font::Get(eFont::SELECT));
}
void Battle::Draw_End() {
	DrawStringToHandle(0, 0, "�퓬���", WHITE, Font::Get(eFont::SELECT));
	DrawFormatStringToHandle(0, 100, WHITE, Font::Get(eFont::SELECT), "�I�����%d", this->endCount);
}

// �ǂ̉�ʂ���퓬��ʂɈڍs�������i�퓬�I�����ɂ��̉�ʂɖ߂�)
void Battle::SetReturnScene(eScene scene) {
	this->nextScene = scene;
}

void Battle::SetCommand(Command command)
{
	this->command = command;
}
Command Battle::GetCommand()
{
	return command;
}
void Battle::SetStep(eStep step)
{
	this->step = step;
}