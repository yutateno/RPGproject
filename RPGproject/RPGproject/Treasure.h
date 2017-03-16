#pragma once

#include "DxLib.h"
#include "Scene.h"
#include "Input.h"

#include "Item.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Treasure
{
private:
	// �摜
	int closeGraph;
	int openGraph;

	// �X�e�[�^�X
	int ID;			// �Ǘ��ԍ�
	bool open;		// �J�����Ă��邩�ǂ���
	int X, Y;		// ���W
	int itemID;		// ���̃A�C�e���̂h�c
	int money;		// ���ɓ����Ă�����z

public:
	// �R���X�g���N�^�ƃf�X�g���N�^
	Treasure();
	Treasure(int ID);
	~Treasure();

	// ID����X�e�[�^�X������������֐�
	void Initialize();

	// �󔠂��J����ꂽ���̏���
	void OpenProcess();

	// �`��
	void Draw(int cameraX, int cameraY);

	// �Q�b�^�[
	int GetID();
	bool GetOpen();
	int GetX();
	int GetY();
	int GetItemID();
	int GetMoney();
	string GetName();
};