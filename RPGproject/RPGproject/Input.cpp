#include "Manager.h"

//////////////////////////////////////////////キーボード////////////////////////////////////////////////////
KeyData::KeyData() {

}
KeyData::~KeyData() {

}

int KeyData::key[256];
char KeyData::tmpKey[256];

void KeyData::UpDate() {
	KeyData::tmpKey[256];			// 現在のキーの入力状態を格納する
	GetHitKeyStateAll(KeyData::tmpKey);	// 全てのキーの入力状態を得る
	for (int i = 0; i < 256; i++) {
		if (KeyData::tmpKey[i] != 0) {	// i番のキーコードに対応するキーが押されていたら
			KeyData::key[i]++;   // 加算
		}
		else if (KeyData::key[i] > 0) {	// キーが離された瞬間
			KeyData::key[i] = -1; // -1にする
		}
		else {	// それ以外
			KeyData::key[i] = 0; // 0にする
		}
	}
}

bool KeyData::CheckEnd() {
	return KeyData::key[KEY_INPUT_ESCAPE] <= 0;
}

//////////////////////////////////////////////ゲームパッド////////////////////////////////////////////////////

int KeyData::Get(int KeyCode) {
	return KeyData::key[KeyCode];
}

PadData::PadData() {

}

PadData::~PadData() {

}

int PadData::button[4][16];  // ゲームパッドの入力状態格納用変数
XINPUT_STATE PadData::input[4];	// ゲームパッドのナンバー
__int8 PadData::padNum;

void PadData::SetPadNum() {
	PadData::padNum = (__int8)GetJoypadNum();
}

void PadData::UpDate(){
	for (int j = 0; j < PadData::padNum; j++) {
		// 入力状態を取得
		GetJoypadXInputState(DX_INPUT_PAD1, &PadData::input[j]);
		for (int i = 0; i < 16; i++) {
			if (PadData::input[j].Buttons[i] != 0) {	// i番のキーコードに対応するキーが押されていたら
				PadData::button[j][i]++;   // 加算
			}
			else if (button[i] > 0) {	// キーが離された瞬間
				PadData::button[j][i] = -1; // -1にする
			}
			else {				// それ以外
				PadData::button[j][i] = 0; // 0にする
			}
		}
	}
}

int PadData::Get(int code, int padNum) {	// ゲームパッドの入力状態取得
	return PadData::button[padNum][code];
}

bool PadData::CheckEnd() {
	return{
		(PadData::button[0][XINPUT_BUTTON_START] < 1 && PadData::button[0][XINPUT_BUTTON_BACK] < 1) ||
		(PadData::button[1][XINPUT_BUTTON_START] < 1 && PadData::button[1][XINPUT_BUTTON_BACK] < 1) ||
		(PadData::button[2][XINPUT_BUTTON_START] < 1 && PadData::button[2][XINPUT_BUTTON_BACK] < 1) ||
		(PadData::button[3][XINPUT_BUTTON_START] < 1 && PadData::button[3][XINPUT_BUTTON_BACK] < 1)
	};
}