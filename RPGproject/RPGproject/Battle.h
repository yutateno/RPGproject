#pragma once
#include "Manager.h"

enum Command { NEUTRAL, ATTACK, MAGIC, RUN_AWAY };			// �R�}���h���

// �퓬���
class Battle : public SuperScene {
private:
	int Gr_Back;			// �w�i

	Command command;		// �R�}���h���	
	Command preCommand;		// ���O�̃R�}���h

	bool damageFlag;		// �_���[�W��^���鏈���������Ȃ����ǂ����̃t���O
	int damageWidth;		// �_���[�W�̃u����

	int cursorX, cursorY;			// �J�[�\���̍��W

	bool textFlag;					// �e�L�X�g��\�����邩�ǂ����̃t���O

public:
	Battle();
	~Battle();

	void UpDate();		// �A�b�v�f�[�g
	void UpDate_Start();// �J�n��ʃA�b�v�f�[�g
	void UpDate_Main();	// ���C����ʃA�b�v�f�[�g
	void UpDate_End();	// �I����ʃA�b�v�f�[�g

	void Draw();			// �`��
	void Draw(bool flag);	// ��{�I�ɂ��������Ă΂��
	void Draw_Start();		// �J�n��ʕ`��
	void Draw_Main();		// ���C����ʕ`��
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
};
