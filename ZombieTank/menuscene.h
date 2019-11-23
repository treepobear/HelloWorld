#ifndef MENUSCENE_H
#define MENUSCENE_H

#include<QGraphicsScene>
#include<QPushButton>

class MenuScene:public QGraphicsScene
{
    Q_OBJECT
public:
    MenuScene();
    ~MenuScene();
private:
    QPushButton* startBtn;
    QPushButton* quitBtn;

signals:
    void startBtnClicked();
    void quitBtnClicked();
    //helpBtnClicked();
};

#endif // MENUSCENE_H
