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
	preCommand = command;

	damageFlag = false;
	damageWidth = 0;

	textFlag = true;

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
	// ���O�̃R�}���h��ۑ�
	preCommand = command;

	// �J�[�\���ړ�
	if (KeyData::Get(KEY_INPUT_UP) == 1 && cursorY>0)
	{
		cursorY--;
	}
	if (KeyData::Get(KEY_INPUT_DOWN) == 1 && cursorY<2)
	{
		cursorY++;
	}

	// Z�L�[�Ō���
	if (KeyData::Get(KEY_INPUT_Z) == 1) {
		switch (command)
		{
		case NEUTRAL:	// ����
			if (cursorY == 0)		// �U���I����
			{
				// �����ɍU���͂Ȃǂ������鎮��ǉ�����
				damageWidth = 0;		// �U�ꕝ
				damageFlag = true;		// Manager�ɁAenemy�Ƀ_���[�W��^����悤�w������
				command = NEUTRAL;		// command��NEUTRAL�ɖ߂�
				command = ATTACK;
			}
			else if (cursorY == 1)// ���@�I����
			{
				// �����ɍU���͂Ȃǂ������鎮��ǉ�����
				damageWidth = 3;		// �U�ꕝ
				damageFlag = true;		// Manager�ɁAenemy�Ƀ_���[�W��^����悤�w������
				command = NEUTRAL;		// command��NEUTRAL�ɖ߂�
				command = MAGIC;
			}
			else{					// ������I����
				command = RUN_AWAY;
			}
			break;

		case ATTACK:	// �U�����j���[
			break;

		case MAGIC:		// ���@���j���[
			break;

		case RUN_AWAY:	// ������
			break;

		default:		// �݂蓾�Ȃ��B�G���[
			break;
		}
	}

	// �R�}���h�̕ω�����J�[�\����␳
	if (preCommand != command)
	{
		cursorY = 0;		// �J�[�\�������Ƃ̈ʒu�ɖ߂�
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
void Battle::Draw(bool flag) {
	// �i�s��Ԃ��󂯎��\�����邩�ǂ��������߂�
	textFlag = flag;

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

	if (textFlag)
	{
		// �R�}���h��Ԃɉ����ĕ\����ω�
		switch (command)
		{
		case NEUTRAL:	// ����
			DrawFormatString(0, 384, WHITE, "  �U��");
			DrawFormatString(0, 416, WHITE, "  ���@");
			DrawFormatString(0, 448, WHITE, "  ������");
			break;

		case ATTACK:	// �U�����j���[
			break;

		case MAGIC:		// ���@���j���[
			break;

		case RUN_AWAY:	// ������
			break;

		default:		// �݂蓾�Ȃ��B�G���[
			break;
		}

		// �J�[�\��
		//DrawStringToHandle(cursorX, 400 + (cursorY * 32), "��", WHITE, Font::Get(eFont::SELECT));
		DrawFormatString(cursorX, 384 + (cursorY * 32), WHITE, "��");
	}
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
void Battle::SetDamageFlag(bool damageFlag)
{
	this->damageFlag = damageFlag;
}
bool Battle::GetDamageFlag()
{
	return damageFlag;
}
int Battle::GetDamageWidth()
{
	return damageWidth;
}
void Battle::SetStep(eStep step)
{
	this->step = step;
}
eStep Battle::GetStep()
{
	return step;
}
void Battle::SetNextScene(eScene nextScene)
{
	this->nextScene = nextScene;
}