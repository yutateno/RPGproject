#pragma once
#include "DxLib.h"

#include "Input.h"
#include "Font.h"
#include "Scene.h"

#include "Treasure.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// �_���W����
class Dungeon : public SuperScene {
private:
	int Gr_Back;		// �w�i
	int Gr_Wall;		// ��

	// �}�b�v
	vector<vector<string>> map;

	ifstream read_file;		// �ǂݍ��ރt�@�C��
	string read_line;		// �ǂݍ��񂾍s�i1�s�j
	int read_count;			// �ǂݍ��ޗ�
	int x;					// ��ʕ\���̂����W
	int y;					// ��ʕ\���̂����W
	bool fieldflag;			// �t�B�[���h��ʂ֍s�����ǂ���
	bool battleflag;		// �퓬��ʂ֍s�����ǂ���
	bool bossflag;			// �{�X�퓬�֍s�����ǂ���

	vector<Treasure> treasure;	// ��
	bool openflag;				// �J�������ǂ���
	bool treasureflag;			// �󔠂ɂȂ񂩂�����
	string treasurename;		// �󔠂̒��̖��O
	int treasuremoney;			// �󔠂̒��̋�

	int comment;				// �Ȃ񂩔����̉�b
	const int flame = 30;		// �t���[��
	int conUI_x;				// �R�����g�̕\���ʒu
	int conUI_y;
	int conUI_height;
	int conUI_width;
	string str;

public:
	Dungeon();
	~Dungeon();

	void UpDate();		// �A�b�v�f�[�g
	void UpDate(int playerX, int playerY);
	void UpDate_Start();// �J�n��ʃA�b�v�f�[�g
	void UpDate_Main();	// ���C����ʃA�b�v�f�[�g
	void UpDate_End();	// �I����ʃA�b�v�f�[�g

	void Draw();	// �`��
	void Draw_Start();	// �J�n��ʕ`��
	void Draw_Main(int x, int y);	// ���C����ʕ`��
	void Draw_End();	// �I����ʕ`��

	void Draw_UI();		// UI�̕`��
	void Dungeon_Map();	// �}�b�v�S��

	void MapData();

	int OpenTreasure(int num);	// �󔠂��J����ꂽ���̏���

	// �Q�b�^�[�Z�b�^�[
	int GetMapData(int x, int y);	// �}�b�v�̑S��
	int GetMapWidth();				// �}�b�v�̉���
	int GetMapHeight();				// �}�b�v�̏c��
	void SetX(int x);				// �J�����̂w���W
	int GetX();
	void SetY(int y);				// �J�����̂x���W
	int GetY();
	void SetField(bool flag);	// �o���ɂ��邩�ǂ���
	bool GetField();
	void SetBattle(bool flag);	// �퓬�s�����ǂ���
	bool GetBattle();
	void SetBoss(bool flag);	//�{�X�퓬�ɍs�����ǂ���
	bool GetBoss();
	int GetTreasureNum();			// �󔠂̔ԍ�
	int GetTreasureX(int num);		// ����󔠂̂w���W
	int GetTreasureY(int num);		// ����󔠂̂x���W
	void SetOpen(bool flag);	// �J�������ǂ���
	bool GetOpen();
	void SetTreasure(bool flag);	// �󔠂ɔ����������ǂ���
	bool GetTreasure();
	void SetTreasureMoney(int money);	// �󔠂��炨���𓾂���
	int GetTreasureMoney();
	eStep GetStep();	// ���̃X�e�b�v��
};