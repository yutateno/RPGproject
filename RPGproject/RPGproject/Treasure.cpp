#include "Treasure.h"

Treasure::Treasure()
{

}
Treasure::Treasure(int ID)
{
	// �摜
	closeGraph = LoadGraph("treasure\\treasure.png");
	openGraph = LoadGraph("treasure\\treasure.png");

	// �X�e�[�^�X
	this->ID = ID;
	Initialize();
}
Treasure::~Treasure()
{
	// �摜�폜
	// DeleteGraph(Graph);
}

void Treasure::Initialize()
{
	// �t�@�C���I�[�v��
	ifstream ifs("treasure\\treasure.csv");

	// �}�b�v�f�[�^�ǂݍ��ݎ��s
	if (!ifs)
	{
		// �G���[
		return;
	}

	// ���u��
	string str = "";
	int treasure[6] = { 0,0,0,0,0,0 };

	while (getline(ifs, str))
	{
		// ���u��
		int i = 0;
		string token = "";
		istringstream stream(str);

		while (getline(stream, token, ','))
		{
			// �Č���
			if (i == 0 && !(stoi(token) == ID))
			{
				break;
			}

			// ������ăJ�E���g�A�b�v
			treasure[i] = stoi(token);
			i++;
		}

		// �����I��
		if (i != 0)
		{
			// �e�X�e�[�^�X������ďI��
			open	= (bool)treasure[1];
			X		= treasure[2];
			Y		= treasure[3];
			itemID	= treasure[4];
			money	= treasure[5];
			break;
		}
	}
}

void Treasure::OpenProcess()
{
	// ----------------------------------------
	// �t�@�C��������������

	// �ǂݍ��݂Ƃ��̃`�F�b�N
	ifstream ifs("origin\\treasure.csv");
	if (!ifs)
	{
		return;
	}

	// �o�̓t�@�C��
	ofstream ofs("treasure\\treasure.csv");

	// ���u��
	string treasure[6];
	string str;

	// �t�@�C���u������
	for (int i = 0;i < ID;i++)
	{
		getline(ifs, str);
		ofs << str << endl;
	}
	getline(ifs, str);
	ofs << ID << "," << 1 << "," << X << "," << Y << "," << 0 << "," << 0 << endl;
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

	// �t�@�C��������������
	// ----------------------------------------
	

	// ��������
	open = true;
	itemID = 0;
	money = 0;
}

void Treasure::Draw(int cameraX, int cameraY)
{
	// �󂢂Ă�����
	if (open)
	{
		DrawGraph(X - cameraX, Y - cameraY, openGraph, true);
	}
	// �󂢂Ă��Ȃ�������
	else
	{
		DrawGraph(X - cameraX, Y - cameraY, closeGraph, true);
	}
}

int Treasure::GetID()
{
	return ID;
}
bool Treasure::GetOpen()
{
	return open;
}
int Treasure::GetX()
{
	return X;
}
int Treasure::GetY()
{
	return Y;
}
int Treasure::GetItemID()
{
	return itemID;
}
int Treasure::GetMoney()
{
	return money;
}