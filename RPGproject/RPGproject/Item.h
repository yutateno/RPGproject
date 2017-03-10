#pragma once

#include <string>

using std::string;

class Item
{
private:

public:
	int ID;						// �Ǘ��ԍ�
	string name;				// ���O
	int price;					// �l�i
	string effectText[2];		// ���ʂ̃e�L�X�g

	Item();
	Item(int ID);
	~Item();

	static string SearchName(int ID);						// �Ǘ��ԍ����疼�O����������֐�
	static int SearchPrice(int ID);							// �Ǘ��ԍ�����l�i����������֐�
	static string SearchEffectText(int ID, bool effected);	// �Ǘ��ԍ�������ʂ���������֐�
};