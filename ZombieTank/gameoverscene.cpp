#include "gameoverscene.h"

GameOverScene::GameOverScene()
{
    this->setSceneRect(0,0,800,600);
    this->setBackgroundBrush(QBrush(QPixmap(":/images/bg2.jpg")));
    restartBtn=new QPushButton("重新开始");
    restartBtn->setFont(QFont("华文琥珀",18));
    restartBtn->setStyleSheet("QPushButton{background:transparent;color:white;}"
                                "QPushButton:hover{color:red;}");
    restartBtn->move(this->width()*2/3,this->height()*2/3);
    connect(restartBtn,&QPushButton::clicked,this,&GameOverScene::restartBtnClicked);
    this->addWidget(restartBtn);

    quitBtn=new QPushButton("退出游戏");
    quitBtn->setFont(QFont("华文琥珀",18));
    quitBtn->setStyleSheet("QPushButton{background:transparent;color:white;}"
                                "QPushButton:hover{color:red;}");
    quitBtn->move(this->width()*2/3,this->height()*2/3+50);
    connect(quitBtn,&QPushButton::clicked,this,&GameOverScene::quitBtnClicked);
    this->addWidget(quitBtn);

    showRankBtn=new QPushButton("积分排行");
    showRankBtn->setFont(QFont("华文琥珀",18));
    showRankBtn->setStyleSheet("QPushButton{background:transparent;color:white;}"
                                "QPushButton:hover{color:red;}");
    showRankBtn->move(this->width()*2/3,this->height()*2/3+100);
    connect(showRankBtn,&QPushButton::clicked,this,&GameOverScene::showRankBtnClicked);
    this->addWidget(showRankBtn);

}
