#pragma once
#include "DxLib.h"

#include "Input.h"
#include "Font.h"
#include "Scene.h"

// ���Ƃ��̋��_
class GameClear : public SuperScene {
private:
	int Gr_Back;	// �w�i

public:
	GameClear();
	~GameClear();

	void UpDate();		// �A�b�v�f�[�g
	void UpDate_Start();// �J�n��ʃA�b�v�f�[�g
	void UpDate_Main();	// ���C����ʃA�b�v�f�[�g
	void UpDate_End();	// �I����ʃA�b�v�f�[�g

	void Draw();	// �`��
	void Draw_Start();	// �J�n��ʕ`��
	void Draw_Main();	// ���C����ʕ`��
	void Draw_End();	// �I����ʕ`��
};