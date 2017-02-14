#include "Manager.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE);
	//SetGraphMode(1920, 1080, 32);
	SetGraphMode(640, 480, 32);
	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;        // �G���[���N�����璼���ɏI��
	}
	SetDrawScreen(DX_SCREEN_BACK);

	Font::SetFontData();
	PadData::SetPadNum();
	Manager *manager = new Manager();

	while (ProcessMessage() != -1 && !manager->GetEndFlag() &&
			KeyData::CheckEnd() && PadData::CheckEnd()) {//��ʍX�V & ���b�Z�[�W���� & ��ʏ���
		ClearDrawScreen();

		KeyData::UpDate();

		manager->UpDate();
		manager->Draw();
		ScreenFlip();
	}
	delete manager;

	InitGraph();

	DxLib_End(); // DX���C�u�����I������
	return 0;
}