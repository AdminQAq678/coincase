## qt命名规范和快捷键

![image-20201212172908551](C:\Users\admin\AppData\Roaming\Typora\typora-user-images\image-20201212172908551.png)

## **qt 自定义信号与槽****

1. 首先在类中的signals中声明信号方法，不用实现方法

2. 然后在另外的类中的public slots中声明槽方法，需要实现槽方法，然后使用connect方法去将信号与槽连接起来

3. **触发信号方法需要使用 emit 信号方法();**

**处理重载的信号和槽函数需要传递函数的地址**

![image-20201212173012601](C:\Users\admin\AppData\Roaming\Typora\typora-user-images\image-20201212173012601.png)

```c++
void(Teacher::*hun)(QString)=&Teacher::hungry;
void(Student::*tre)(QString)=&Student::treat;
void(Student::*tre1)(void)=&Student::treat;
connect(teacher,hun,student,tre);
```

>  需要指定作用域：Teacher 或者Student，同时指明函数参数为QString ，返回值为void

### **信号与槽函数的注意事项**

> 信号可以连接多个槽函数，一个槽函数也可以被多个信号连接
>
> 信号函数的参数个数应当多于或等于槽函数的参数个数
>
> 而不能小与



### **QString 转*char**

![image-20201212173035828](C:\Users\admin\AppData\Roaming\Typora\typora-user-images\image-20201212173035828.png)

### 信号可以连接另外一个信号，形成一条“信号链”

```c++
void(Teacher::*hun)(void)=&Teacher::hungry;
void(Student::*tre1)(void)=&Student::treat;
connect(teacher,hun,student,tre1);
//信号参数应当与槽的参数相对应
connect(button,&QPushButton::clicked,teacher,hun);
```

### **拓展**

![image-20201212173514492](C:\Users\admin\AppData\Roaming\Typora\typora-user-images\image-20201212173514492.png)



## QLabel



```C++
  
//显示图片
	ui->label->setPixmap(QPixmap(":/new/prefix1/1.jpg"));
    QMovie *movie=new QMovie(":/new/prefix1/my.gif");
//显示gif图片
    ui->label->setMovie(movie);
    movie->start();
}
```



## qt事件

### 一、自定义控件

1. 创建类（如命名为mylabel)，将继承的类改成需要的类如（QLabel），
2. 在ui设计页面中添加组件如（QLabel），选择组件，右键选择‘提升为’，然后输入自定义组件的类名（mylabel）

### 二、事件

在自定义控件中通过重写事件方法，实现在触发事件的时候做出执行相应的代码

 setMouseTracking(true); 设置跟踪鼠标，即使鼠标没有按下也会触发MouseMove事件

```c++
#ifndef MYLABEL_H
#define MYLABEL_H

#include <QWidget>
#include <QLabel>
class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = nullptr);

    virtual void mouseMoveEvent(QMouseEvent *ev);

signals:

public slots:
};

#endif // MYLABEL_H

```



```C++
#include "mylabel.h"
#include <QDebug>
#include <QMouseEvent>
MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{
    setMouseTracking(true);
}
void MyLabel::mouseMoveEvent(QMouseEvent *ev){
    qDebug()<<"鼠标移动了"<<ev->x()<<" "<<ev->y();
}

```



## 定时器

一、重写TimeEvent方法

```
   void timerEvent(QTimerEvent *event);
```

二、使用QTimer类，连接Qtimer类的信号方法和匿名函数方法（要执行的代码)

```c++
QTimer *timer=new QTimer(this);
    timer->start(1000);
    connect(timer,QTimer::timeout,[](){
        qDebug()<<"well";
    });
```



## 事件

1. 事件分发器

   重写bool event(QEvent* ev)方法，返回值为true则事件不往下分发

   ```c++
   bool event(QEvent* ev){
       if (ev->type() == QEvent::PolishRequest) {
           // overwrite handling of PolishRequest if any
           doThings();
           return true;
       } else  if (ev->type() == QEvent::Show) {
           // complement handling of Show if any
           doThings2();
           QWidget::event(ev);
           return true;
       }
       // Make sure the rest of events are handled
       return QWidget::event(ev);
   }
   ```

2. 事件过滤器

   重写eventFilter(QObject *obj, QEvent *event)方法，返回值为true则事件不往下分发

   ```c++
    bool MainWindow::eventFilter(QObject *obj, QEvent *event)
     {
         if (obj == textEdit) {
             if (event->type() == QEvent::KeyPress) {
                 //事件类型转换
                 QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
                 qDebug() << "Ate key press" << keyEvent->key();
                 return true;
             } else {
                 return false;
             }
         } else {
             // pass the event on to the parent class
             return QMainWindow::eventFilter(obj, event);
         }
     }
   ```

   

## 绘画事件

Qpainter 

QPen	画笔

QBrush 画刷，用于填充

**使用步骤**：重写组组件的paintEvent(QPaintEvent *event)函数

```c++
void MainWindow::paintEvent(QPaintEvent *event){
    //this为指定的画图设备
    QPainter painter(this);
    painter.drawLine(QPoint(0,0),QPoint(100,100));

    painter.drawRect(QRect(0,1,100,100));
    painter.drawText(QRect(200,200,100,50),"好啊后学习米卡水泥地上的");
    QPen pen(QColor(255,0,0));


	
    QBrush brush(Qt::cyan);
    pen.setBrush(brush);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawEllipse(QPoint(100,100),50,100);

    painter.drawRect(QRect(0,0,300,300));
}
```



## 绘图设备

![image-20201216154046215](C:\Users\admin\AppData\Roaming\Typora\typora-user-images\image-20201216154046215.png)