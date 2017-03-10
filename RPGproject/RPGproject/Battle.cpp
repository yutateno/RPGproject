#include "Manager.h"

Battle::Battle() {
	// ����֌W
	this->endFlag = false;				// ���̃V�[���̏I������t���O
	this->nextScene = eScene::S_End;	// ���̃V�[���̐ݒ肷��

	// ���o�֌W
	this->step = eStep::Start;			// ���o�֌W
	this->startCount = 80;				// �V�[���J�n���̉��o����
	this->endCount = 50;					// �V�[���I�����̉��o����
	count = 0;							// (�t���[��)���Ԃ̃J�E���g

	// �摜
	Gr_Back = LoadGraph("img\\battle_background.png");		// �w�i

	// �퓬�V�X�e���֌W
	command = NEUTRAL;				// ���݂̃R�}���h
	preCommand = command;			// ���O�̃R�}���h��ۑ�����
	damageFlag = false;				// �_���[�W��^�������ǂ���
	damageWidth = 0;				//�_���[�W�̐U�ꕝ

	// �R�}���h������Ă��
	commandX = 8;
	commandY = 320;

	// �J�[�\�����W
	cursorX = 0;		// ���΍��W
	cursorY = 0;		// ���΍��W
}
Battle::~Battle() {
	// �摜�폜
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
	// �J�E���g�A�b�v
	count++;

	// startCount�������o����
	if (count < startCount) return;
	// �J�E���g���Z�b�g���Ď��̃X�e�b�v��
	count = 0;
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
		// �R�}���h�̏�Ԃ��珈����I��
		switch (command)
		{
		case NEUTRAL:	// ����
			if (cursorY == 0)		// �U���I����
			{
				// �����ɍU���͂Ȃǂ������鎮��ǉ�����
				damageWidth = 0;		// �U�ꕝ
				damageFlag = true;		// Manager�ɁAenemy�Ƀ_���[�W��^����悤�w������
				command = ATTACK;		// �R�}���h��Ԃ�ύX
			}
			else if (cursorY == 1)// ���@�I����
			{
				// �����ɍU���͂Ȃǂ������鎮��ǉ�����
				damageWidth = 3;		// �U�ꕝ
				damageFlag = true;		// Manager�ɁAenemy�Ƀ_���[�W��^����悤�w������
				command = MAGIC;		// �R�}���h��Ԃ�ύX
			}
			else{					// ������I����
				command = RUN_AWAY;
			}
			break;

		case ATTACK:	// �U�����j���[
			// �����ŋL�����邱�Ƃ͂Ȃ��BNEUTRAL�ɂ�Manager���߂��Ă����
			break;

		case MAGIC:		// ���@���j���[
			// �����ŋL�����邱�Ƃ͂Ȃ��BNEUTRAL�ɂ�Manager���߂��Ă����
			break;

		case RUN_AWAY:	// ������
			// �����ŋL�����邱�Ƃ͂Ȃ��BNEUTRAL�ɂ�Manager���߂��Ă����
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
	// �J�E���g�A�b�v
	count++;

	// endCount�������o����
	if (count < endCount) return;
	// �J�E���g�����Z�b�g���Ă��̃V�[�����I������
	count = 0;
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
	// ���X�ɉ�ʂ̕\�����鏈��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, count * 3);
	// �w�i
	DrawGraph(0, 0, Gr_Back, FALSE);
	// �u�����h���[�h�̌㏈��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
void Battle::Draw_Main() {
	// �w�i
	DrawGraph(0, 0, Gr_Back, true);
}
void Battle::Draw_Command()
{
	// �R�}���h�w�i
	DrawBox(commandX, commandY, commandX + 150, commandY + 150, BLACK, true);
	DrawBox(commandX, commandY, commandX + 150, commandY + 150, WHITE, false);

	// �R�}���h��Ԃɉ����ĕ\����ω�
	switch (command)
	{
	case NEUTRAL:	// ����
		DrawFormatString(commandX + 32, commandY + 32, WHITE, "  �U��");
		DrawFormatString(commandX + 32, commandY + 64, WHITE, "  ���@");
		DrawFormatString(commandX + 32, commandY + 96, WHITE, "  ������");
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
	DrawFormatString(commandX + 32 + cursorX, commandY + 32 + (cursorY * 32), WHITE, "��");
}
void Battle::Draw_End() {
	// ���X�ɉ�ʂ��Â����鏈��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (count * 5));
	// �w�i
	DrawGraph(0, 0, Gr_Back, FALSE);
	// �u�����h���[�h�̌㏈��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
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
int Battle::GetCount()
{
	return count;
}