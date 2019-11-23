#include "rankscene.h"

RankScene::RankScene()
{
    this->setSceneRect(0,0,800,600);
    this->setBackgroundBrush(QBrush(QPixmap(":/images/bg2.jpg")));
    backtoMenuBtn=new QPushButton("回到菜单");
    backtoMenuBtn->setFont(QFont("华文琥珀",18));
    backtoMenuBtn->setStyleSheet("QPushButton{background:transparent;color:white;}"
                                "QPushButton:hover{color:red;}");
    backtoMenuBtn->move(this->width()*2/3,this->height()*2/3);
    connect(backtoMenuBtn,&QPushButton::clicked,this,&RankScene::backtoMenuBtnClicked);
    this->addWidget(backtoMenuBtn);

}
