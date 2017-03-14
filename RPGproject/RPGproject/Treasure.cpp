#include "Treasure.h"

Treasure::Treasure()
{

}
Treasure::Treasure(int ID)
{
	// �摜
	closeGraph = LoadGraph("treasure\\closetreasure.png");
	openGraph = LoadGraph("treasure\\opentreasure.png");

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
	ifstream ifs("treasure\\treasure.csv");
	if (!ifs)
	{
		return;
	}

	// ���u��
	string str;
	int i = 0;
	vector<string> treasure;

	while (getline(ifs, str))
	{
		treasure.push_back(str);
	}

	// �������J��
	str.clear();

	// �t�@�C�������
	ifs.close();

	// �o�̓t�@�C��
	ofstream ofs("treasure\\treasure.csv");

	// �t�@�C���u������
	for (i = 0;i < ID;i++)
	{
		ofs << treasure[i] << endl;
	}
	i++;
	ofs << ID << "," << 1 << "," << X << "," << Y << "," << itemID << "," << money << endl;
	for (int n = (int)treasure.size(); i < n; i++)
	{
		ofs << treasure[i] << endl;
	}

	treasure.clear();

	// �t�@�C�������
	ofs.close();

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