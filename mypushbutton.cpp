#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>//动画特效
//MyPushButton::MyPushButton(QWidget *parent) : QWidget(parent)
//{

//}

MyPushButton::MyPushButton(QString normalImg, QString pressImg){
    this->normalImgPath=normalImg;
    this->pressImgPath=pressImg;
    QPixmap pix;
    bool ret=pix.load(normalImg);
    if(!ret){
        qDebug()<<"图片加载失败";
        return;
    }
    //设置固定大小
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则样式
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

}
void MyPushButton::zoom1(){
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);

    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}
void MyPushButton::zoom2(){
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);

    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

//void MyPushButton::showPressedImg(){
//    QPixmap pix;
//    bool ret=pix.load(this->pressImgPath);
//    if(!ret){
//        qDebug()<<"图片加载失败";
//        return;
//    }
//    this->setIcon(pix);
//}
 void MyPushButton::mousePressEvent(QMouseEvent *e){
     if(this->pressImgPath!=""){
         QPixmap pix;
         bool ret=pix.load(this->pressImgPath);
         if(!ret){
             qDebug()<<"图片加载失败";
             return;
         }
         this->setIcon(pix);
     }
     return QPushButton::mousePressEvent(e);

 }
 void MyPushButton::mouseReleaseEvent(QMouseEvent *e){
     if(this->pressImgPath!=""){
         QPixmap pix;
         bool ret=pix.load(this->normalImgPath);
         if(!ret){
             qDebug()<<"图片加载失败";
             return;
         }
         this->setIcon(pix);
     }
     return QPushButton::mouseReleaseEvent(e);

 }
