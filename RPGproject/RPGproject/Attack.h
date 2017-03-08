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
	string name;	// 技名
	int power;		// 純粋な攻撃力
	int width;		// ダメージの振れ幅

	Attack();
	Attack(string name, int power, int width);
	~Attack();

	int Damage();		// 攻撃力を受けとりダメージ量を返す関数
};