#include "Textbox.h"

Textbox::Textbox()
{

}
Textbox::~Textbox()
{

}

void Textbox::Draw(int X, int Y, string log)
{
	DrawFormatString(X + 8, Y + 8, WHITE, log.c_str());
}
void Textbox::Draw(int X, int Y, int width, int height,string log)
{
	// îwåi
	DrawBox(X, Y, X + width, Y + height, BLACK, true);
	DrawBox(X, Y, X + width, Y + height, WHITE, false);
	
	DrawFormatString(X + 8, Y + 8 , WHITE, log.c_str());
}