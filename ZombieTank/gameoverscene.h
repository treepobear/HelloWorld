#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H
#include<QGraphicsScene>
#include<QPushButton>

class GameOverScene:public QGraphicsScene
{
    Q_OBJECT
public:
    GameOverScene();
private:
    QPushButton* restartBtn;
    QPushButton* quitBtn;
    QPushButton* showRankBtn;
signals:
    void restartBtnClicked();
    void quitBtnClicked();
    void showRankBtnClicked();
};

#endif // GAMEOVERSCENE_H
