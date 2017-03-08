#pragma once
#include "DxLib.h"

enum class eFont : __int8 {SELECT};

// ÇÊÇ≠égÇ§êF
const int WHITE = GetColor(255, 255, 255);
const int BLACK = GetColor(0, 0, 0);
const int YELLOW = GetColor(255, 255, 0);
const int RED = GetColor(255, 0, 0);
const int BLUE = GetColor(0, 0, 255);
const int GREEN = GetColor(0, 255, 0);

class Font {
private:
	static int SELECT;

public:
	Font();
	~Font();

	static void SetFontData();

	static int Get(eFont type);
};