#pragma once

#include "DxLib.h"

#include "Input.h"
#include "Font.h"
#include "Scene.h"

#include "Title.h"
#include "player.h"
#include "Field.h"
#include "Enemy.h"
#include "Battle.h"
#include "Attack.h"
#include "GameOver.h"
#include "SafeArea.h"
#include "GameClear.h"
#include "Dungeon.h"
#include "Item.h"

class Player;
class Enemy;

class Manager :public SuperScene {
private:
	eScene NowScene;

	// �e�V�[���̎���
	Title* title;
	Player* player;
	Field* field;
	Enemy* enemy;
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

	int playerX;			// �v���C���[�����������ǂ����𔻒肷��ϐ�
	int playerY;			// �v���C���[�����������ǂ����𔻒肷��ϐ�
	int probability;		// �G���J�E���g����m�� : 1/probability

	// �퓬�֘A
	bool turn;				// ������̃^�[��������̃^�[����
	int count;				// ���O��\�����鎞��
	int preHP;				// ���O��HP�B���O�p
	bool lose;				// �擪�Ŕs�k���ɗ��t���O
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

	// �ǐ����l�����Ē�������L�q��UpDate���瓦�������ߍ쐬
	void FieldProcess();
	void BattleProcess();
	void DungeonProcess();
	void SafeAreaProcess();
};