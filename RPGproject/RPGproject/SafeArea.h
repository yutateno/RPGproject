#pragma once
#include "Manager.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// ���Ƃ��̋��_
class SafeArea : public SuperScene {
private:
	int Gr_Back;	// �w�i
	int Gr_Wall;	// ��

	vector<vector<string>> map;

	ifstream read_file;		// �ǂݍ��ރt�@�C��
	string read_line;		// �ǂݍ��񂾍s�i1�s�j
	int read_count;
	int x;
	int y;
	bool fieldflag;			// �o���ɂ��邩�ǂ���
	bool peopleflag;		// ��ʐl�ɐG�ꂽ��
	bool itemflag;			// ����ɐG�ꂽ��
	bool healflag;			// �����ɐG�ꂽ��
	int healcount;			// �t���[���J�E���g

public:
	SafeArea();
	~SafeArea();

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
	void SetPeople(bool flag);	// ��ʐl�ɐG�ꂽ��
	bool GetPeople();
	void SetItem(bool flag);	// ����ɐG�ꂽ��
	bool GetItem();
	void SetHeal(bool flag);	// �����ɐG�ꂽ��
	bool GetHeal();
	eStep GetStep();	// ���̃X�e�b�v��
};