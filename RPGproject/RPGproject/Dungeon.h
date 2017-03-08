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
	int Gr_Back;	// �w�i
	int Gr_Wall;	// ��

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

	void MapData();

	// �Q�b�^�[�Z�b�^�[
	int GetMapData(int x, int y);
	int GetMapWidth();
	int GetMapHeight();
	void SetX(int x);
	int GetX();
	void SetY(int y);
	int GetY();
	void SetField(bool flag);	// �o���ɂ��邩�ǂ���
	bool GetField();
	void SetBattle(bool flag);	// �퓬�s�����ǂ���
	bool GetBattle();
	void SetBoss(bool flag);	//�{�X�퓬�ɍs�����ǂ���
	bool GetBoss();
	eStep GetStep();	// ���̃X�e�b�v��
};