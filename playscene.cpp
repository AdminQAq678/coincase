#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QPainter>
#include <mypushbutton.h>
#include <QLabel>

#include <mycoin.h>
#include "dataconfig.h"

#include <QPropertyAnimation>

//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}
PlayScene::PlayScene(int levelNum)
{

    QString str=QString("进入了第 %1 关").arg(levelNum);

    this->levelIndex=levelNum;
    qDebug()<<str;

    this->setFixedSize(320,588);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("翻金币场景");

    //初始化二维数组
        dataConfig config;
        for(int i = 0 ; i < 4;i++)
        {
            for(int j = 0 ; j < 4; j++)
            {
                gameArray[i][j] = config.mData[this->levelIndex][i][j];
            }
        }

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

        qDebug()<<"翻转 点击了返回按钮";

        emit this->myclose();

    });

    //胜利图片
    QLabel* winLabel = new QLabel;
   QPixmap tmpPix;
   tmpPix.load(":/res/LevelCompletedDialogBg.png");
   winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
   winLabel->setPixmap(tmpPix);
   winLabel->setParent(this);
   winLabel->move( (this->width() - tmpPix.width())*0.5 , -tmpPix.height());


    //显示关卡
    QLabel *label=new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);
    QString levelStr=QString("Level: %1").arg(this->levelIndex);
    label->setText(levelStr);
    label->setGeometry(30,this->height()-50,120,50);

    //显示金币背景图案
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            QPixmap pix=QPixmap(":/res/BoardNode.png");
            QLabel *la=new QLabel;
            la->setGeometry(0,0,50,50);
            la->setPixmap(pix);
            la->setParent(this);
            la->move(57+i*50,200+j*50);
            QString str=":/res/Coin0001.png";
            if(this->gameArray[i][j]==0){
                str=":/res/Coin0008.png";
            }
            MyCoin *coin=new MyCoin(str);
            coinBtn[i][j] = coin;
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);
            coin->posX = i; //记录x坐标
            coin->posY = j; //记录y坐标
            coin->flag =gameArray[i][j]; //记录正反标志
            //监听金币点击
            connect(coin,&MyCoin::clicked,[=](){
                //qDebug() << "点击的位置： x = " <<  coin->posX << " y = " << coin->posY ;
                //延时翻转周围4个金币
                coinBtn[i][j]->changeFlag();
                gameArray[i][j]= gameArray[i][j]==0?1:0;
                QTimer::singleShot(300, this,[=](){
                //翻转右边
                if(coin->posX+1 <=3)
                {
                  coinBtn[coin->posX+1][coin->posY]->changeFlag();
                  gameArray[coin->posX+1][coin->posY] = gameArray[coin->posX+1][coin->posY]== 0 ? 1 : 0;
                }
                 //翻转左边
                if(coin->posX-1>=0)
                {
                  coinBtn[coin->posX-1][coin->posY]->changeFlag();
                  gameArray[coin->posX-1][coin->posY] = gameArray[coin->posX-1][coin->posY]== 0 ? 1 : 0;
                }
                  //翻转上面
                if(coin->posY+1<=3)
                {
                 coinBtn[coin->posX][coin->posY+1]->changeFlag();
                 gameArray[coin->posX][coin->posY+1] = gameArray[coin->posX+1][coin->posY]== 0 ? 1 : 0;
                }
                  //翻转下面
                if(coin->posY-1>=0)
                {
                 coinBtn[coin->posX][coin->posY-1]->changeFlag();
                 gameArray[coin->posX][coin->posY-1] = gameArray[coin->posX+1][coin->posY]== 0 ? 1 : 0;
                }

                //判断是否胜利
                                this->isWin = true;
                                for(int i = 0 ; i < 4;i++)
                                {
                                    for(int j = 0 ; j < 4; j++)
                                    {
                                        //qDebug() << coinBtn[i][j]->flag ;
                                        if( coinBtn[i][j]->flag == false)
                                        {
                                            this->isWin = false;
                                            break;
                                        }
                                    }
                                }
                                if(this->isWin)
                                {
                                    qDebug() << "胜利";
                                    QPropertyAnimation * animation1 =  new QPropertyAnimation(winLabel,"geometry");
                                    animation1->setDuration(1000);
                                    animation1->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                                    animation1->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                                    animation1->setEasingCurve(QEasingCurve::OutBounce);
                                    animation1->start();
                                    //禁用所有按钮点击事件
                                    for(int i = 0 ; i < 4;i++)
                                      {
                                        for(int j = 0 ; j < 4; j++)
                                        {
                                          coinBtn[i][j]->isWin = true;
                                        }
                                    }


                                }


            });
            });
        }
    }





}

void PlayScene::paintEvent(QPaintEvent *event){
    //加载背景

    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
//  qDebug()<<pix.width()<<pix.height();
 //加载标题
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);


}
