#pragma once
#include "DxLib.h"

#include "Input.h"
#include "Font.h"
#include "Scene.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// �_���W����
class Dungeon : public SuperScene {
private:
	int Gr_Back;		// �w�i
	int Gr_Wall;		// ��
	int Gr_Treasure;	// ��
	int Gr_Open;		// �󂢂Ă��

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

	const int flame = 30;	// �t���[��
	int comment;			// ��ɓ���\��
	int treasureMax;		// �󔠂̐�
	int num;				// �ǂ̕󔠂�
	bool treasure[10];		// �󔠊J���Ă邩�ǂ���
	bool touchflag;			// �󔠂ɐG��Ă��邩
	bool openflag;			// �J����ꂽ���ǂ���

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

	void Draw_UI();		// UI

	void MapData();

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
	void SetNum(int num);		// �ǂ̕󔠂�
	int GetNum();
	void SetTreasure(int num, bool treasure);	// ��
	bool GetTreasure(int num);
	void SetTouch(bool flag);		// �G�ꂽ���ǂ���
	bool GetTouch();
	void SetOpen(bool flag);		// �J�������ǂ���
	bool GetOpen();
	eStep GetStep();	// ���̃X�e�b�v��
};