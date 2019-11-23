#ifndef OBJECT_H
#define OBJECT_H

#include<QGraphicsItem>
#include<QGraphicsScene>
#include<string>
using namespace std;

enum WarPart{ME,ENEMY,LIFESUPPLY};

class Object:public QGraphicsPixmapItem
{
public:
    Object(WarPart part,const string& imageFile);
//    ~Object();
    void synScreen(QGraphicsScene* scene);
    void delScreen(QGraphicsScene* scene);
    bool isexisting();

protected:
    WarPart part;
};

#endif // OBJECT_H
