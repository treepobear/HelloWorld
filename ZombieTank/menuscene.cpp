#include "menuscene.h"

MenuScene::MenuScene()
{

    //设置菜单页场景
    this->setSceneRect(0,0,800,600);
    this->setBackgroundBrush(QBrush(QPixmap(":/images/bg.jpg")));
    ///开始按钮
    startBtn=new QPushButton("开始游戏");
    startBtn->setFont(QFont("华文琥珀",18));
    startBtn->setStyleSheet("QPushButton{background:transparent;color:white;}"
                                "QPushButton:hover{color:red;}");
    startBtn->move(this->width()*2/3,this->height()*2/3);
    connect(startBtn,&QPushButton::clicked,this,&MenuScene::startBtnClicked);
    this->addWidget(startBtn);
    ///结束按钮
    quitBtn=new QPushButton("退出游戏");
    quitBtn->setFont(QFont("华文琥珀",18));
    quitBtn->setStyleSheet("QPushButton{background:transparent;color:white;}"
                                "QPushButton:hover{color:red;}");
    quitBtn->move(this->width()*2/3,this->height()*2/3+50);
    connect(quitBtn,&QPushButton::clicked,this,&MenuScene::quitBtnClicked);
    this->addWidget(quitBtn);

}

MenuScene::~MenuScene()
{
}
