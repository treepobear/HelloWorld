#ifndef RANKSCENE_H
#define RANKSCENE_H

#include<QGraphicsScene>
#include<QPushButton>
class RankScene:public QGraphicsScene
{
    Q_OBJECT
public:
    RankScene();
private:
    QPushButton* backtoMenuBtn;
signals:
    void backtoMenuBtnClicked();

};

#endif // RANKSCENE_H
