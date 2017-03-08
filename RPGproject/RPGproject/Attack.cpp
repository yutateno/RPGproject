#include "Attack.h"

Attack::Attack()
{
	name = "UŒ‚";
	power = 1;
	width = 0;
}
Attack::Attack(string name, int power, int width)
{
	this->name = name;
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