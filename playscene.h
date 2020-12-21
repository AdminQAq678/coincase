#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
//    explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int levelNum);
    int levelIndex;// 记录所选的关卡
    int gameArray[4][4]; //二维数组数据
    void paintEvent(QPaintEvent *event);
    MyCoin * coinBtn[4][4]; //金币按钮数组
    bool isWin = true; //是否胜利
signals:
     void myclose();
public slots:
};

#endif // PLAYSCENE_H
