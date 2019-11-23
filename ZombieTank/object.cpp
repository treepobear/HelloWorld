#include "object.h"

Object::Object(WarPart part, const string &imageFile):
    QGraphicsPixmapItem(QPixmap(QString::fromStdString(imageFile)))
{
    this->part = part;
}

//Object::~Object(){}

void Object::synScreen(QGraphicsScene *scene)
{
    if(!scene->items().contains(this))
    {
        scene->addItem(this);
        update();
    }
}

void Object::delScreen(QGraphicsScene *scene)
{
    scene->removeItem(this);
    update();
}
bool Object::isexisting()
{
    if(pos().x()<-80||pos().x()>scene()->width()||pos().y()<-80||pos().y()>scene()->height())
        return false;
    else
        return true;
}

