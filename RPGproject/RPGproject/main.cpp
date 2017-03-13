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

	// -----------------------------------------
	// ������������������

	// �ǂݍ��݂Ƃ��̃`�F�b�N
	ifstream ifs("origin\\treasure.csv");
	if (!ifs)
	{
		return 0;
	}

	// �o�̓t�@�C��
	ofstream ofs("treasure\\treasure.csv");

	// ���u��
	string treasure[6];
	string str;

	while (getline(ifs, str))
	{
		ofs << str << endl;
	}

	// �t�@�C�������
	ifs.close();
	ofs.close();

	// ���f�ޔj��
	for (int i = 0;i < 5;i++)
	{
		treasure[i].clear();
	}
	str.clear();

	// ���������������܂�
	// -----------------------------------------

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