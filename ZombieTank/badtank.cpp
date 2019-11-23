#include "badtank.h"

BadTank::BadTank(int x, int y, const string &imageFile, QGraphicsScene *scene, int life):
    Tank(x,y,imageFile,scene,life,ENEMY){}
//BadTank::~BadTank(){}
