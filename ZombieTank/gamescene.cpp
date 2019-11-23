#include "gamescene.h"

GameScene::GameScene()
{
    setSceneRect(0,0,800,600);
    setBackgroundBrush(QBrush(QPixmap(":/images/background.jpg")));
    boompic = new QPixmap(":/images/boom.BMP");
    mytank=new MyTank(0,40,":/images/mytankright.png",this,80,10);
    mytank->synScreen(this);
    badbulletshoottimerid=startTimer(1600);
    bulletsmovetimerid=startTimer(50);
    badtankgeneratetimerid=startTimer(4000);
    badtankmovetimerid=startTimer(100);
    huilantimerid=startTimer(100);
    boomDisplayTimerId=startTimer(40);

    score = 0; //得分清零
    scoreText = new QGraphicsTextItem;
    scoreText->setPos(50,150);
    scoreText->setHtml(tr("<font color=white>SCORE: %1</font>").arg(score));
    scoreText->setFont(QFont("Courier"));
    addItem(scoreText);

}


void GameScene::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==huilantimerid)
    {
        if(mytank->lan<80)
        {
            mytank->huilan();
        }
        for(vector<Object*>::iterator iter=vec_lifesupplys.begin();
            iter!=vec_lifesupplys.end();++iter)
        {
            if(mytank->collidesWithItem((*iter)))
            {
                if(mytank->life<80)
                    mytank->life+=15;
                removeItem((*iter));

            }
        }

    }
    else if(event->timerId()==bulletsmovetimerid)
    {
        updatemybullet();
        updatebadbullet();
    }
    else if(event->timerId()==badbulletshoottimerid)
    {
        shootbadbullet();
    }
    else if(event->timerId()==badtankmovetimerid)
    {
        updatetank();
        for(vector<BadTank*>::iterator iter=vec_badtanks.begin();
            iter!=vec_badtanks.end();++iter)
        {
            if(!(*iter)->isexisting())
                timerstop();
        }
    }
    else if(event->timerId()==badtankgeneratetimerid)
    {
        generatebadtank();
    }
    else if(event->timerId()==boomDisplayTimerId)
    {
        boomdisplay();
    }
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_W:
        mytank->setPos(mytank->pos().x(),mytank->pos().y()-10);
        mytank->xuetiaogensui();
        mytank->lantiaogensui();
        break;
    case Qt::Key_S:
        mytank->setPos(mytank->pos().x(),mytank->pos().y()+10);
        mytank->xuetiaogensui();
        mytank->lantiaogensui();
        break;
    case Qt::Key_A:
        mytank->setPos(mytank->pos().x()-10,mytank->pos().y());
        mytank->xuetiaogensui();
        mytank->lantiaogensui();
        break;
    case Qt::Key_D:
        mytank->setPos(mytank->pos().x()+10,mytank->pos().y());
        mytank->xuetiaogensui();
        mytank->lantiaogensui();
        break;
    case Qt::Key_J:
        if(mytank->lan>10)
            shootmybullet();
        break;
    }
}
void GameScene::shootmybullet()
{
    mytank->lan-=10;
    Bullet* bullet=new Bullet(ME,mytank->pos().x()+83,mytank->pos().y()+10,
                              ":/images/bullet2.png");
    vec_mybullets.push_back(bullet);
    bullet->synScreen(this);
}
bool GameScene::changebulletpos(Bullet *bullet, int newX, int newY)
{
    bool hit=false;
    //检查我有没有被打中
    if(bullet->part==ENEMY&&bullet->collidesWithItem(mytank))
    {
        addBoomPos(mytank->pos());
        hit=true;
        mytank->life-=20;
        if(mytank->life<0)
            timerstop();
    }
    //检查坏坦克有没有被打中
    else if(bullet->part==ME)
    {
        for(vector<BadTank*>::iterator iter=vec_badtanks.begin();
            iter!=vec_badtanks.end();)
        {
            bool alive=true;
            if(bullet->collidesWithItem(*iter))
            {
                addBoomPos((*iter)->pos());
                hit=true;
                alive=(*iter)->crash(this);
            }
            if(alive)
                iter++;
            else {
                removeItem((*iter)->xuetiao);
                delete *iter;
                iter=vec_badtanks.erase(iter);
                score=score+10;
                scoreText->setHtml(tr("<font color=white>SCORE: %1</font>").arg(score));
                srand(time(NULL));
                if(rand()%4==0)
                {
                    Object *lifeSupply = new Object(LIFESUPPLY, ":/images/lifesupply.png");
                    lifeSupply->setPos(bullet->pos());
                    vec_lifesupplys.push_back(lifeSupply);
                    addItem(lifeSupply);
                }
            }
        }

    }
    if(!hit)
    {
        bullet->synScreen(this);
        bullet->setPos(newX,newY);
        bullet->update();
        return true;
    }
    else
        return false;
}
void GameScene::updatemybullet()
{
    for(vector<Bullet*>::iterator iter=vec_mybullets.begin();
        iter!=vec_mybullets.end();)
    {
        if(changebulletpos(*iter,(*iter)->pos().x()+10,(*iter)->pos().y()))
            iter++;
        else {
            delete *iter;
            iter=vec_mybullets.erase(iter);
        }
    }
}
void GameScene::updatebadbullet()
{
    for(vector<Bullet*>::iterator iter=vec_badbullets.begin();iter!=vec_badbullets.end();)
    {
        if(changebulletpos(*iter,(*iter)->x()-10,(*iter)->y()))
        {
            iter++;
        }
        else
        {
            (*iter)->delScreen(this);
            delete *iter;
            iter=vec_badbullets.erase(iter);
        }
    }
}
void GameScene::shootbadbullet()
{
    for(vector<BadTank*>::iterator iter=vec_badtanks.begin();iter!=vec_badtanks.end();++iter)
    {
        if((*iter)->life>0)
        {
            Bullet* bullet=new Bullet(ENEMY,(*iter)->pos().x()-3,(*iter)->pos().y()+5,
                                      ":/images/bullet1.png");
            vec_badbullets.push_back(bullet);
            bullet->synScreen(this);
        }
    }
}


void GameScene::updatetank()
{
    for(vector<BadTank*>::iterator iter=vec_badtanks.begin();
        iter!=vec_badtanks.end();)
    {
        if(changeBadTankPos(iter,(*iter)->pos().x()-10,(*iter)->pos().y()))
            iter++;
        else {
            score=score+10;
            scoreText->setHtml(tr("<font color=white>SCORE: %1</font>").arg(score));
            removeItem((*iter)->xuetiao);
            iter=vec_badtanks.erase(iter);
        }
    }
}

bool GameScene::changeBadTankPos(vector<BadTank*>::iterator iter,
                                 int newX, int newY)
{
    bool alive = true;//标记坏坦克还活着吗
    //和我撞
    if((*iter)->collidesWithItem(mytank))
    {
        addBoomPos((*iter)->pos());
        mytank->life-=30;
        alive=(*iter)->crash(this);
        if(mytank->life<=0)
            timerstop();
    }
    //和我的子弹撞
    for(vector<Bullet*>::iterator mybullet=vec_mybullets.begin();mybullet!=vec_mybullets.end();++mybullet)
    {
        if((*iter)->collidesWithItem((*mybullet)))
        {
            alive=(*iter)->crash(this);
            addBoomPos((*iter)->pos());
        }
    }
    //如果死了返回假
    if(!alive)
    {
        return false;
    }
    else//如果还活着更新位置，血条跟随
    {
        (*iter)->setPos(newX,newY);
        (*iter)->xuetiaogensui();
        return true;

    }
}

void GameScene::generatebadtank()
{
    int rand_y=qrand()%(int)height();
    BadTank* ptr=new BadTank(800,rand_y,":/images/badtankleft.png",this,100);
    vec_badtanks.push_back((ptr));
    ptr->synScreen(this);
}
//产生爆炸本质上是在场景中加入一个item，这个item里面用绘图设备画爆炸效果
void GameScene::addBoomPos(QPointF pos)
{
    QGraphicsPixmapItem* p=new QGraphicsPixmapItem();
    p->setPos(pos);
    p->setZValue(10);
    addItem(p);
    vec_boompos.push_back(Boom(p,0));
};
//爆炸绘图设备
void GameScene::boomdisplay()
{
    for(boomptr=vec_boompos.begin();boomptr!=vec_boompos.end();++boomptr)
    {
        boomptr->phase++;
        if(boomptr->phase>8)
        {
            removeItem(boomptr->ptrItem);
            //vec_boompos.erase(boomptr);
        }
        else
        {
            QPixmap temp=boompic->copy(boompic->width()/8*(boomptr->phase-1),3,boompic->width()/8,boompic->height()-5);
            temp=temp.scaled(QSize(temp.width()/2,temp.height()/2), Qt::KeepAspectRatio);
            boomptr->ptrItem->setPixmap(temp);
            boomptr->ptrItem->update();
        }
    }
};
void GameScene::timerstop()
{
    killTimer(badbulletshoottimerid);
    killTimer(bulletsmovetimerid);
    killTimer(badtankmovetimerid);
    killTimer(badtankgeneratetimerid);
    killTimer(huilantimerid);
    killTimer(boomDisplayTimerId);
    emit gameover();
}
GameScene::~GameScene()
{
    delete mytank;
    for(vector<Bullet*>::iterator badbulletsPtr=vec_badbullets.begin();
        badbulletsPtr!=vec_badbullets.end();++badbulletsPtr)
    {
        delete (*badbulletsPtr);
        vec_badbullets.erase(badbulletsPtr);
    }
    for(vector<BadTank*>::iterator badTankPtr=vec_badtanks.begin();badTankPtr!=vec_badtanks.end();++badTankPtr)
    {
        delete (*badTankPtr);
        vec_badtanks.erase(badTankPtr);
    }
    for(vector<Bullet*>::iterator mybulletsPtr=vec_mybullets.begin();mybulletsPtr!=vec_mybullets.end();++mybulletsPtr)
    {
        delete (*mybulletsPtr);
        vec_mybullets.erase(mybulletsPtr);
    }
}
