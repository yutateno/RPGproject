#pragma once

#include "DxLib.h"

#include "Input.h"
#include "Font.h"
#include "Scene.h"

#include <string>

using std::string;

class Textbox
{
public:
	// �R���X�g���N�^
	Textbox();
	~Textbox();

	// �`��
	static void Draw(int X, int Y, string log);
	static void Draw(int X, int Y, int width, int height, string log);
};