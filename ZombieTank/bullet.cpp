#include "bullet.h"

Bullet::Bullet(WarPart part, int x, int y, const string &imageFile):
    Object (part,imageFile)
{
    setPos(x,y);
}
Bullet::~Bullet(){}
