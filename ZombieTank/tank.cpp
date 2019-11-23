#include "tank.h"

Tank::Tank(int x, int y, const string &imageFile, QGraphicsScene *scene, int life, WarPart part):
    Object(part,imageFile),life(life)
{
    setPos(x,y);
    xuetiao=new QGraphicsRectItem(x,y-20,life,5);
    xuetiao->setBrush(QBrush(Qt::red));
    scene->addItem(this);
    scene->addItem(xuetiao);
    update();
}

void Tank::xuetiaogensui()
{
    delete xuetiao;
    xuetiao=new QGraphicsRectItem(this->pos().x(),this->pos().y()-23.5,this->life,10);
    xuetiao->setBrush(QBrush(Qt::red));
    scene()->addItem(xuetiao);
    scene()->update();
}

bool Tank::crash(QGraphicsScene* scene)
{
    life-=40;
    if(life<=0)
    {
        delScreen(scene);
        return false;
    }
    else
        return true;
}
