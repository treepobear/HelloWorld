#include "mainview.h"

MainView::MainView(QWidget *parent)
    : QGraphicsView(parent)
{
    //设置窗口
    this->setWindowTitle("僵尸坦克大作战");

    //进入菜单
    menuptr=new MenuScene();
    //绑定信号槽
    connect(menuptr,SIGNAL(startBtnClicked()),this,SLOT(enterGameScene()));
    connect(menuptr,SIGNAL(quitBtnClicked()),this,SLOT(quitGame()));
    this->setScene(menuptr);
    this->show();

}

MainView::~MainView()
{

}

void MainView::enterGameScene()
{
    gameptr=new GameScene();
    connect(gameptr,SIGNAL(gameover()),this,SLOT(enterGameOverScene()));
    this->setScene(gameptr);
    this->show();
}
void MainView::quitGame()
{
    exit(0);
}
void MainView::enterGameOverScene()
{
//    delete gameptr;
    gameoverptr=new GameOverScene();
    connect(gameoverptr,SIGNAL(restartBtnClicked()),this,SLOT(enterGameScene()));
    connect(gameoverptr,SIGNAL(showRankBtnClicked()),this,SLOT(enterRankScene()));
    connect(gameoverptr,SIGNAL(quitBtnClicked()),this,SLOT(quitGame()));
    this->setScene(gameoverptr);
    this->show();
}
void MainView::backtoMenu()
{
    this->setScene(menuptr);
    this->show();
}
void MainView::enterRankScene()
{
    rankptr=new RankScene();
    connect(rankptr,SIGNAL(backtoMenuBtnClicked()),this,SLOT(backtoMenu()));
    this->setScene(rankptr);
    this->show();
}
