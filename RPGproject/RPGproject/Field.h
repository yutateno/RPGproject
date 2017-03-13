#pragma once
#include "DxLib.h"

#include "Input.h"
#include "Font.h"
#include "Scene.h"

#include "Treasure.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Field : public SuperScene {
private:
	// �摜
	int Gr_Back;					// �w�i
	int mapchip[4];					// �}�b�v�`�b�v
	int mapchipForID;				// �`�ʗp�̕ϐ�

	// �}�b�v�f�[�^�֌W
	ifstream ifs;					// �t�@�C���I�[�v���p
	vector<vector<int> > mapdata;	// �}�b�v�f�[�^�{��
	int mapchipNum;					// �}�b�v�`�b�v�̎�ސ�
	int mapchipSize;				// �}�b�v�`�b�v�̃T�C�Y

	// �J�����֌W
	int cameraX;					// �J�����̍��W
	int cameraY;					// �J�����̍��W

	// ���o�֌W
	int count;						// (�t���[��)���Ԃ��J�E���g����

	// �󔠊֌W
	vector<Treasure> treasure;

public:
	Field();
	~Field();

	void UpDate();		// �A�b�v�f�[�g
	void UpDate(int playerX, int playerY);			// ��{�I�Ɏg�p����I�[�o�[���[�h
	void UpDate_Start();// �J�n��ʃA�b�v�f�[�g
	void UpDate_Main();	// ���C����ʃA�b�v�f�[�g
	void UpDate_Main(int playerX, int playerY);		// ��{�I�Ɏg�p����I�[�o�[���[�h
	void UpDate_End();	// �I����ʃA�b�v�f�[�g

	void Draw();		// �`��
	void Draw_Start();	// �J�n��ʕ`��
	void Draw_Main();	// ���C����ʕ`��
	void Draw_End();	// �I����ʕ`��

	void ReadMapData();	//�}�b�v�f�[�^���e�L�X�g�t�@�C������ǂݍ��ފ֐�

	// �󔠂��J����ꂽ���̏���
	int OpenTreasure(int num);

	// �Q�b�^�[�Z�b�^�[
	void SetMapData(int x, int y, int data);
	int GetMapData(int x, int y);
	int GetMapWidth();
	int GetMapHeight();
	void SetStep(eStep step);
	eStep GetStep();
	void SetNextScene(eScene nextScene);
	void SetCamera(int x, int y);
	void SetCameraX(int x);
	void SetCameraY(int y);
	int GetTreasureNum();
	int GetTreasureX(int num);
	int GetTreasureY(int num);
};
