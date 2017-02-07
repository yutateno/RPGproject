#pragma once
#include "DxLib.h"

#include "Input.h"
#include "Font.h"
#include "Scene.h"

#include "Title.h"
#include "Field.h"
#include "Battle.h"
#include "GameOver.h"
#include "SafeArea.h"
#include "GameClear.h"
#include "Dungeon.h"


class Manager :public SuperScene {
private:
	eScene NowScene;

	// �e�V�[���̎���
	Title* title;
	Field* field;
	Battle* battle;
	SafeArea* safeArea;
	Dungeon* dungeon;
	GameOver* gameOver;
	GameClear* gameClear;

	// �e�V�[���̈ڍs����
	void ChengeScene_Title();
	void ChengeScene_Field();
	void ChengeScene_Battle();
	void ChengeScene_SafeArea();
	void ChengeScene_Dungeon();
	void ChengeScene_GameOver();
	void ChengeScene_GameClear();


public:
	Manager();
	~Manager();

	void UpDate();		// �A�b�v�f�[�g
	void UpDate_Start() {}	// �J�n��ʃA�b�v�f�[�g
	void UpDate_Main() {}		// ���C����ʃA�b�v�f�[�g
	void UpDate_End() {}		// �I����ʃA�b�v�f�[�g
	void Draw();		// �`��
	void Draw_Start() {}		// �J�n��ʕ`��
	void Draw_Main() {}		// ���C����ʕ`��
	void Draw_End() {}		// �I����ʕ`��
};