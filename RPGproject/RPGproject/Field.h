#pragma once
#include "Manager.h"

#include <vector>
#include<fstream>
#include<iostream>
#include<string>
#include <sstream>

using namespace std;

class Field : public SuperScene {
private:
	// �摜
	int Gr_Back;					// �w�i
	int mapchip1;					// �}�b�v�`�b�v

	vector<vector<int> > mapdata;	// �}�b�v�f�[�^�{��

public:
	Field();
	~Field();

	void UpDate();		// �A�b�v�f�[�g
	void UpData(int playerX, int PlayerY);		// ��{�I�Ɏg�p����I�[�o�[���[�h
	void UpDate_Start();// �J�n��ʃA�b�v�f�[�g
	void UpDate_Main();	// ���C����ʃA�b�v�f�[�g
	void UpDate_End();	// �I����ʃA�b�v�f�[�g

	void Draw();		// �`��
	void Draw_Start();	// �J�n��ʕ`��
	void Draw_Main();	// ���C����ʕ`��
	void Draw_End();	// �I����ʕ`��

	void ReadMapData();	//�}�b�v�f�[�^���e�L�X�g�t�@�C������ǂݍ��ފ֐�

	int GetMapData(int x, int y);		// �}�b�v�f�[�^�̃Q�b�^�[

};
