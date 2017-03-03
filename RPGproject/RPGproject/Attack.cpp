#include "Attack.h"

Attack::Attack()
{
	power = 1;
	width = 0;
}
Attack::Attack(int power, int width)
{
	this->power = power;
	this->width = width;
}
Attack::~Attack()
{

}

int Attack::Damage()
{
	return power + GetRand(width);		// ÀŞƒ[ƒW‚ğ•Ô‚·
}