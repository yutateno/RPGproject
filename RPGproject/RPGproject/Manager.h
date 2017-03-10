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
	bool playerDamageFlag;	// �_���[�W���󂯂Ă��邩�ǂ���
	bool enemyDamageFlag;	// �_���[�W���󂯂Ă��邩�ǂ���
	int probability;		// �G���J�E���g����m�� : 1/probability
	int drop;				// �G���A�C�e���𗎂Ƃ��m�� : item/drop

	// �퓬�֘A
	bool turn;				// ������̃^�[��������̃^�[����
	vector<string> log;		// ���O�{��
	int logLineNum;			// �P�y�[�W�ɉ��s�\�����邩
	int logCount;			// (�t���[��)�J�E���g
	int logTime;			// �\������
	int lineTime;			// �s�̐i�ގ���
	int statusX, statusY;	// �X�e�[�^�X������Ă����
	int logX, logY;			// ���O������Ă��
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

	// �ǐ����l�����Ē�������L�q�𓦂������ߍ쐬
	void FieldProcess();
	void BattleProcess();
	void BattleDraw();
	void DungeonProcess();
	void SafeAreaProcess();
};