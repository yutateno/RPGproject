#include "Manager.h"

//////////////////////////////////////////////�L�[�{�[�h////////////////////////////////////////////////////
KeyData::KeyData() {

}
KeyData::~KeyData() {

}

int KeyData::key[256];
char KeyData::tmpKey[256];

void KeyData::UpDate() {
	KeyData::tmpKey[256];			// ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(KeyData::tmpKey);	// �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i < 256; i++) {
		if (KeyData::tmpKey[i] != 0) {	// i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			KeyData::key[i]++;   // ���Z
		}
		else if (KeyData::key[i] > 0) {	// �L�[�������ꂽ�u��
			KeyData::key[i] = -1; // -1�ɂ���
		}
		else {	// ����ȊO
			KeyData::key[i] = 0; // 0�ɂ���
		}
	}
}

bool KeyData::CheckEnd() {
	return KeyData::key[KEY_INPUT_ESCAPE] <= 0;
}

//////////////////////////////////////////////�Q�[���p�b�h////////////////////////////////////////////////////

int KeyData::Get(int KeyCode) {
	return KeyData::key[KeyCode];
}

PadData::PadData() {

}

PadData::~PadData() {

}

int PadData::button[4][16];  // �Q�[���p�b�h�̓��͏�Ԋi�[�p�ϐ�
XINPUT_STATE PadData::input[4];	// �Q�[���p�b�h�̃i���o�[
__int8 PadData::padNum;

void PadData::SetPadNum() {
	PadData::padNum = (__int8)GetJoypadNum();
}

void PadData::UpDate(){
	for (int j = 0; j < PadData::padNum; j++) {
		// ���͏�Ԃ��擾
		GetJoypadXInputState(DX_INPUT_PAD1, &PadData::input[j]);
		for (int i = 0; i < 16; i++) {
			if (PadData::input[j].Buttons[i] != 0) {	// i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
				PadData::button[j][i]++;   // ���Z
			}
			else if (button[i] > 0) {	// �L�[�������ꂽ�u��
				PadData::button[j][i] = -1; // -1�ɂ���
			}
			else {				// ����ȊO
				PadData::button[j][i] = 0; // 0�ɂ���
			}
		}
	}
}

int PadData::Get(int code, int padNum) {	// �Q�[���p�b�h�̓��͏�Ԏ擾
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