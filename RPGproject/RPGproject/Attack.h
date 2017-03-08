#pragma once

#include "DxLib.h"

#include "Input.h"
#include "Font.h"
#include "Scene.h"

class Attack
{
public:
	int power;		// 純粋な攻撃力
	int width;		// ダメージの振れ幅

	Attack();
	Attack(int power, int width);
	~Attack();

	int Damage();		// 攻撃力を受けとりダメージ量を返す関数
};