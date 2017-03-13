#include "Treasure.h"

Treasure::Treasure()
{

}
Treasure::Treasure(int ID)
{
	// �摜
	Graph = LoadGraph("img\\treasure.png");

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
	ifstream ifs("img\\treasure.csv");

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
		// ID���v�Ȃ�X�e�[�^�X���

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

void Treasure::Opened()
{
	// �o�͏���
}

void Treasure::Draw(int cameraX, int cameraY)
{
	// �󂢂Ă�����
	if (open)
	{
		DrawGraph(X - cameraX, Y - cameraY, Graph, true);
	}
	// �󂢂Ă��Ȃ�������
	else
	{
		DrawGraph(X - cameraX, Y - cameraY, Graph, true);
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