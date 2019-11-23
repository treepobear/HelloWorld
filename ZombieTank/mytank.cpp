#include "mytank.h"

MyTank::MyTank(int x,int y,const string& imageFile,QGraphicsScene* scene,int life,int lan):
    Tank(x,y,imageFile,scene,life,ME),lan(lan)
{
    lantiao = new QGraphicsRectItem(x,y-10,lan,10);
    lantiao->setBrush(QBrush(Qt::blue));
    scene->addItem(lantiao);
}
void MyTank::lantiaogensui()
{
    delete lantiao;
    lantiao = new QGraphicsRectItem(this->pos().x(),this->pos().y()-10,lan,10);
    lantiao->setBrush(QBrush(Qt::blue));
    this->scene()->addItem(lantiao);
    this->scene()->update();
}
//MyTank::~MyTank(){}
void MyTank::huilan()
{
    delete lantiao;
    lan+=1;
    lantiao=new QGraphicsRectItem(this->pos().x(),this->pos().y()-10,this->lan,10);
    lantiao->setBrush(QBrush(Qt::blue));
    this->scene()->addItem(lantiao);
    this->scene()->update();
}
