#include "chooselevelscene.h"
#include <QMenuBar>
#include <QMenu>
#include <QDebug>
#include <QPainter>
#include "mypushbutton.h"
#include <QLabel>
#include <QSound>
ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(320,588);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("选择关卡");
    QSound *chooseSound = new QSound(":/res/TapButtonSound.wav",this);
    //返回按钮音效
    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);
    QMenuBar *menubar=menuBar();
    setMenuBar(menubar);

    QMenu *startMenu=menubar->addMenu("开始");
    QAction *quitAction=startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
        qDebug()<<"quit";
    });

    MyPushButton *backBtn=new MyPushButton(":res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    connect(backBtn,&MyPushButton::clicked,[=](){
        qDebug()<<"点击了返回按钮";
        backSound->play();
        emit this->myclose();
        this->close();
    });


       for(int i=0;i<20;i++){
           MyPushButton *button=new MyPushButton(":/res/LevelIcon.png");
            button->setParent(this);
            button->move(25+i%4*70,130+i/4*70);

            QLabel *label=new QLabel;
            label->resize(button->width(),button->height());
            label->setParent(this);
            label->setText(QString::number(i+1));
            label->move(25+i%4*70,130+i/4*70);
            label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            label->setAttribute(Qt::WA_TransparentForMouseEvents);

            connect(button,&MyPushButton::clicked,[=](){
//                qDebug()<<"ok";
                chooseSound->play();
                this->hide();

                play=new PlayScene(i+1);
                play->show();
                connect(play,&PlayScene::myclose,[=](){
                   qDebug()<<"窗口关闭";
                   backSound->play();
                   this->show();
                   //删除场景
                   delete play;
                   play=NULL;
                });
            });

       }
}

void ChooseLevelScene::paintEvent(QPaintEvent *event){
   QPainter painter(this);
   QPixmap pix;
   pix.load(":/res/OtherSceneBg.png");
   painter.drawPixmap(0,0,this->width(),this->height(),pix);
   pix.load(":/res/Title.png");
   painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);
}
