#pragma once

#include "Manager.h"

class Attack
{
public:
	int power;		// �����ȍU����
	int width;		// �_���[�W�̐U�ꕝ

	Attack();
	Attack(int power, int width);
	~Attack();

	int Damage();		// �U���͂��󂯂Ƃ�_���[�W�ʂ�Ԃ��֐�
};