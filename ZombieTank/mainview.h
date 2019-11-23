#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QGraphicsView>
#include"menuscene.h"
#include"gamescene.h"
#include"gameoverscene.h"
#include"rankscene.h"
class MainView : public QGraphicsView
{
    Q_OBJECT

public:
    MainView(QWidget *parent = 0);
    ~MainView();
private:
    QGraphicsScene* menuptr;
    QGraphicsScene* gameptr;
    QGraphicsScene* gameoverptr;
    QGraphicsScene* rankptr;
public slots:
    void enterGameScene();
    void quitGame();
    void enterGameOverScene();
    void enterRankScene();
    void backtoMenu();
};

#endif // MAINVIEW_H
