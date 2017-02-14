#pragma once
#include "Manager.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// �_���W����
class Dungeon : public SuperScene {
private:
	int Gr_Back;	// �w�i
	int Gr_Wall;

	vector<vector<string>> map;

	ifstream read_file;		// �ǂݍ��ރt�@�C��
	string read_line;		// �ǂݍ��񂾍s�i1�s�j
	int read_count;
	int x;
	int y;

public:
	Dungeon();
	~Dungeon();

	void UpDate();		// �A�b�v�f�[�g
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
	void SetX(int x);
	int GetX();
	void SetY(int y);
	int GetY();
};