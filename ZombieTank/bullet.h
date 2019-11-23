#ifndef BULLET_H
#define BULLET_H


#include"object.h"

class Bullet:public Object
{
    friend class GameScene;
public:
    Bullet(WarPart part, int x, int y, const string &imageFile);
    ~Bullet();
};

#endif // BULLET_H
