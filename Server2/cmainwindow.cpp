#include "cmainwindow.h"
#include <QPixmap>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QFrame>
CMainWindow::CMainWindow(QWidget *parent) :QWidget(parent)
{
    scene=new MyScene;
    scene->setSceneRect(0,0,798,498);
    view=new MyView(this);
    view->setScene(scene);
    view->setBackgroundBrush(Qt::red);
    view->resize(800,500);

    //画笔按钮
    penbutton1btn=new QPushButton(this);
    penbutton1btn->setCheckable(true);
    penbutton1btn->setAutoExclusive(true);
    QPixmap penbutton1pixmap("images/penbutton1.png");//设置绘画按钮，相当于笔
    penbutton1btn->setGeometry(803,0,0,0);
    penbutton1btn->setFixedSize(penbutton1pixmap.width(),penbutton1pixmap.height());
    penbutton1btn->setStyleSheet("QPushButton{border-image: url(images/penbutton1.png);}QPushButton:hover{border-image: url(images/penbutton2.png);}QPushButton:checked{border-image: url(images/penbutton2.png);}" );
    connect(penbutton1btn,SIGNAL(clicked()),scene,SLOT(operatebtnClick()));


    //橡皮擦按钮
    erase1btn=new QPushButton(this);
    erase1btn->setCheckable(true);
    erase1btn->setAutoExclusive(true);
    QPixmap erase1pixmap("images/erase1.png");
    erase1btn->setGeometry(803,80,0,0);
    erase1btn->setFixedSize(erase1pixmap.width(),erase1pixmap.height());
    erase1btn->setStyleSheet("QPushButton{border-image: url(images/erase1.png);}QPushButton:hover{border-image: url(images/erase3.png);}QPushButton:checked{border-image: url(images/erase3.png);}" );
    connect(erase1btn,SIGNAL(clicked()),scene,SLOT(erase()));

    //撤销按钮
    cancel1btn=new QPushButton(this);
    QPixmap cancel1pixmap("images/cancel1.png");
    cancel1btn->setGeometry(803,120,0,0);
    cancel1btn->setFixedSize(cancel1pixmap.width(),cancel1pixmap.height());
    cancel1btn->setStyleSheet("QPushButton{border-image: url(images/cancel1.png);}QPushButton:hover{border-image: url(images/cancel2.png);}QPushButton:pressed{border-image: url(images/cancel3.png);}" );
    connect(cancel1btn,SIGNAL(clicked()),scene,SLOT(cancel()));

    //保存按钮
    save1btn=new QPushButton(this);
    QPixmap save1pixmap("images/save1.png");
    save1btn->setGeometry(803,160,0,0);
    save1btn->setFixedSize(save1pixmap.width(),save1pixmap.height());
    save1btn->setStyleSheet("QPushButton{border-image: url(images/save1.png);}QPushButton:hover{border-image: url(images/save2.png);}QPushButton:pressed{border-image: url(images/save3.png);}" );
    connect(save1btn,SIGNAL(clicked()),scene,SLOT(save()));


    resize(920,500);

}

