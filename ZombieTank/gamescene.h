#ifndef GAMESCENE_H
#define GAMESCENE_H

#include<QGraphicsScene>
#include<QKeyEvent>
#include<QTimer>
#include<vector>
#include"mytank.h"
#include"badtank.h"
#include"bullet.h"
using namespace std;

class Boom
{
public:
    QGraphicsPixmapItem* ptrItem;
    int phase;
    Boom(QGraphicsPixmapItem* ptrItem=NULL,int phase=0):ptrItem(ptrItem),phase(phase){}
};

class GameScene : public QGraphicsScene
{
    Q_OBJECT

public:
    GameScene();
    ~GameScene();
protected:
    void timerEvent(QTimerEvent *event);
    void keyPressEvent(QKeyEvent *event);
//    void keyReleaseEvent(QKeyEvent* event);
private:
    MyTank* mytank;
    vector<Bullet*>vec_mybullets;
    vector<Bullet*>vec_badbullets;
    vector<BadTank*>vec_badtanks;
    vector<Object*>vec_lifesupplys;

    int badbulletshoottimerid;
    int bulletsmovetimerid;
    int badtankgeneratetimerid;
    int badtankmovetimerid;
    int huilantimerid;
    int boomDisplayTimerId;
    void timerstop();
    void generatebadtank();
    void shootbadbullet();
    void shootmybullet();

//    bool changetankpos(Tank *tank, int newX, int newY);
    bool changeBadTankPos(vector<BadTank*>::iterator iter,int newX,int newY);
    bool changebulletpos(Bullet *bullet, int newX, int newY);

    void updatemybullet();
    void updatebadbullet();
    void updatetank();

    int score;
    QGraphicsTextItem* scoreText;

    ///爆炸点
    vector<Boom>vec_boompos;
    vector<Boom>::iterator boomptr;
    //产生爆炸区域
    void addBoomPos(QPointF pos);
    //爆炸效果演进
    void boomdisplay();
    //爆炸图片
    QPixmap* boompic;
signals:
    void gameover();

protected slots:
//    void startgame();
};

#endif // GAMESCENE_H
