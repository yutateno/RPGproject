#pragma once
#include "Manager.h"

enum Command { NEUTRAL, ATTACK, MAGIC, RUN_AWAY };	// �R�}���h���

// �퓬���
class Battle : public SuperScene {
private:
	int Gr_Back;		// �w�i

	Command command;	// �R�}���h���	

	int cursorX, cursorY;			// �J�[�\���̍��W

public:
	Battle();
	~Battle();

	void UpDate();		// �A�b�v�f�[�g
	void UpDate_Start();// �J�n��ʃA�b�v�f�[�g
	void UpDate_Main();	// ���C����ʃA�b�v�f�[�g
	void UpDate_End();	// �I����ʃA�b�v�f�[�g

	void Draw();	// �`��
	void Draw_Start();	// �J�n��ʕ`��
	void Draw_Main();	// ���C����ʕ`��
	void Draw_End();	// �I����ʕ`��
	
	// �ǂ̉�ʂ���퓬��ʂɈڍs�������i�퓬�I�����ɂ��̉�ʂɖ߂�)
	void SetReturnScene(eScene scene);	
};
