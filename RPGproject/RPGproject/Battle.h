#pragma once
#include "DxLib.h"

#include "Input.h"
#include "Font.h"
#include "Scene.h"

// �R�}���h���
enum Command { NEUTRAL, ATTACK, MAGIC, RUN_AWAY };

class Battle : public SuperScene {
private:
	// �摜�֌W
	int Gr_Back;			// �w�i

	// �퓬�V�X�e���֌W
	Command command;		// �R�}���h���	
	Command preCommand;		// ���O�̃R�}���h
	bool damageFlag;		// �_���[�W��^���鏈���������Ȃ����ǂ����̃t���O
	int damageWidth;		// �_���[�W�̃u����

	// �R�}���h������Ă��
	int commandX, commandY;			// ��΍��W

	// �J�[�\���֌W
	int cursorX, cursorY;			// �J�[�\���̑��΍��W

	// ���o�֌W
	int count;			// (�t���[��)���Ԃ̃J�E���g
	bool logFlag;		// Manager�̃��O�\����Ԃ��擾	

public:
	Battle();
	~Battle();

	void UpDate();		// �A�b�v�f�[�g
	void UpDate_Start();// �J�n��ʃA�b�v�f�[�g
	void UpDate_Main();	// ���C����ʃA�b�v�f�[�g
	void UpDate_End();	// �I����ʃA�b�v�f�[�g

	void Draw();			// �`��
	void Draw_Start();		// �J�n��ʕ`��
	void Draw_Main();		// ���C����ʕ`��
	void Draw_Command();	// �R�}���h�����ɕ`��
	void Draw_End();		// �I����ʕ`��
	
	// �ǂ̉�ʂ���퓬��ʂɈڍs�������i�퓬�I�����ɂ��̉�ʂɖ߂�)
	void SetReturnScene(eScene scene);

	// �Z�b�^�[�Q�b�^�[
	void SetCommand(Command command);
	Command GetCommand();
	void SetDamageFlag(bool damageFlag);
	bool GetDamageFlag();
	int GetDamageWidth();
	void SetStep(eStep step);
	eStep GetStep();
	void SetNextScene(eScene nextScene);
	int GetCount();
	void SetLogFlag(bool logFlag);
};
