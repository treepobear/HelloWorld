#ifndef TANK_H
#define TANK_H


#include"object.h"
class Tank:public Object
{
    friend class GameScene;
public:
    Tank(int x, int y,const string& imageFile,QGraphicsScene* scene,int life,WarPart part);
//    ~Tank();
    bool crash(QGraphicsScene* scene);

protected:
    int life;
    int score;
    QGraphicsRectItem* xuetiao;
    void xuetiaogensui();
};
#endif // TANK_H
