#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include "mypushbutton.h"
#include "chooselevelscene.h"
#include <QTimer>
#include <QDebug>
#include <QSound>
MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{

    ui->setupUi(this);
    QSound *startSound = new QSound(":/res/TapButtonSound.wav",this);
    setFixedSize(320,588);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("翻转金币主场景");
    //添加退出操作
    connect(ui->actionquit,&QAction::triggered,this,&this->close);
    MyPushButton *startBtn=new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);
    chooseLevelSence=new ChooseLevelScene;
    //开始按钮
    connect(startBtn,QPushButton::clicked,[=](){
        startBtn->zoom1();
        startBtn->zoom2();
        //延时进入到选择关卡场景
        startSound->play();
        QTimer::singleShot(200,this,[=](){

            this->hide();
            chooseLevelSence->show();
        });

    });
    connect(chooseLevelSence,&ChooseLevelScene::myclose,[=](){
       qDebug()<<"窗口关闭";
       this->show();
    });
}

void MainScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    //拉伸显示背景图片
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");
    //缩放
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);

}

MainScene::~MainScene()
{
    delete ui;
}
