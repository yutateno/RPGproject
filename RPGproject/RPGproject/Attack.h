#pragma once

#include "DxLib.h"

#include "Input.h"
#include "Font.h"
#include "Scene.h"

#include <string>

using std::string;

class Attack
{
public:
	string name;	// �Z��
	int power;		// �����ȍU����
	int width;		// �_���[�W�̐U�ꕝ

	Attack();
	Attack(string name, int power, int width);
	~Attack();

	int Damage();		// �U���͂��󂯂Ƃ�_���[�W�ʂ�Ԃ��֐�
};