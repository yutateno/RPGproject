#include "Manager.h"

Font::Font() {

}
Font::~Font() {

}

int Font::SELECT;

void Font::SetFontData() {
	Font::SELECT = CreateFontToHandle(NULL, 60, 6);	// 選択フォント
}

int Font::Get(eFont type) {
	switch (type){
	case eFont::SELECT:
		return Font::SELECT;
		break;
	default: // エラー
		return Font::SELECT;
		break;
	}
}