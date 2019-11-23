#ifndef MYTANK_H
#define MYTANK_H


#include"tank.h"

class MyTank:protected Tank
{
    friend class GameScene;
public:
    MyTank(int x,int y,const string& imageFile,QGraphicsScene* scene,int life,int lan);
//    ~MyTank();
private:
    int lan;
    QGraphicsRectItem* lantiao;
    void lantiaogensui();//蓝条跟随
    void huilan();//回蓝
};
#endif // MYTANK_H
