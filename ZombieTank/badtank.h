#ifndef BADTANK_H
#define BADTANK_H

#include"tank.h"
class BadTank:protected Tank
{
    friend class GameScene;
public:
    BadTank(int x,int y,const string& imageFile,QGraphicsScene* scene,int life);
//    ~BadTank();
};

#endif // BADTANK_H
