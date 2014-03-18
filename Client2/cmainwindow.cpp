#include <qbitmap.h>
#include <qapplication.h>
#include <qdesktopwidget.h>
#include <QPushButton.h>
#include <QHBoxLayout>
#include <QDebug.h>
#include <QDialog>
#include <QGridLayout>
#include <QRadioButton>
#include <QButtonGroup>

#include "cmainwindow.h"
//#include "ui_mainwindow.h"


MainWindow::MainWindow(QMainWindow *parent) :
    QMainWindow(parent)
    //ui(new Ui::MainWindow)
    //ui(new MainWindow)
{

    //山妹部分
//    scene=new MyScene;
//    scene->setSceneRect(0,0,798,498);
//    view=new MyView(this);
//    view->setScene(scene);
//    view->setBackgroundBrush(Qt::red);
//    view->resize(800,500);

    //画笔按钮



    double x=QApplication::desktop()->width()/1366.0;
    double y=QApplication::desktop()->height()/768.0;
    this->setGeometry(250/x,150/y,1300,768);
    // this->setWindowFlags(Qt::FramelessWindowHint);

    QWidget *centralWidget = new QWidget(this);//qmainwindow 必须设置一个中心部件将这个作为中心部件，所有部件都在这个部件之上。
    this->setCentralWidget(centralWidget);
    // QPixmap mainbackgroundpixmap("images/background.png");//设置大的那个背景
    mainbackgroundframe = new QFrame(centralWidget);
    mainbackgroundframe->resize(1024/x,500/y);
    mainbackgroundframe->setStyleSheet("border-image:url(images/background.png)" );
    mainbackgroundframe->setGeometry((0-50)/x,(0-20)/y,800/x,500/y);

        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(200/x, 660/y, 140, 51));
        horizontalSlider->setOrientation(Qt::Horizontal);
//        horizontalSlider->hide();

        no_line = new QPushButton(centralWidget);
       no_line->setObjectName(QString::fromUtf8("pushButton"));
        no_line->setStyleSheet("QPushButton{border-image: url(images/no_line.png);}QPushButton:hover{border-image: url(images/no_line_2.png);}QPushButton:pressed{border-image: url(images/no_line_3.png);}" );
        no_line->setGeometry(QRect(70/x,30/y, 41, 41));
        connect(no_line,SIGNAL(clicked()),this,SLOT(change1()));



        quit = new QPushButton(centralWidget);
        quit->setObjectName(QString::fromUtf8("pushButton_1"));
        //quit ->setStyleSheet("QPushButton{border-image: url(images/no_line.png);}QPushButton:hover{border-image: url(images/no_line_2.png);}QPushButton:pressed{border-image: url(images/no_line_3.png);}" );
        quit->setGeometry(QRect(570/x,540/y, 41, 41));
        quit->setText(QApplication::translate("Widget", "退出", 0, QApplication::UnicodeUTF8));
        connect(quit,SIGNAL(clicked()),this,SLOT(Quit()));

        suspend = new QPushButton(centralWidget);
        suspend->setObjectName(QString::fromUtf8("pushButton_5"));
        suspend->setGeometry(QRect(70/x, 660/y, 41, 41));

        play = new QPushButton(centralWidget);
        play->setObjectName(QString::fromUtf8("pushButton_4"));
        play->setGeometry(QRect(120/x, 660/y, 41, 41));


        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(150/x, 100/y, 159/x, 32/y));


        comboBox->addItem(QString::fromUtf8("高音谱号"));
        comboBox->addItem(QString::fromUtf8("低音谱号"));
        comboBox->addItem(QString::fromUtf8("二分音符"));
        comboBox->addItem(QString::fromUtf8("全音符"));
        //comboBox->currentText();
        //comboBox->editTextChanged();
        //comboBox->changeEvent();
        //comboBox->item

        connect(comboBox,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(Quit()));
        //如何获取下拉列表内容，通过选择下拉内容如何直接传递信号值，做成信号槽。
        this->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));


        trace = new QPushButton(centralWidget);
        trace->setObjectName(QString::fromUtf8("pushButton_6"));
        //trace->setStyleSheet("QPushButton{border-image: url(images/no_line.png);}QPushButton:hover{border-image: url(images/no_line_2.png);}QPushButton:pressed{border-image: url(images/no_line_3.png);}" );
        trace->setGeometry(QRect(70/x,30/y, 41, 41));
        trace->hide();
        // connect(no_line,SIGNAL(clicked()),this,SLOT(change1()));
        //描红界面图片更改。



        try_paint = new QPushButton(centralWidget);
        try_paint->setObjectName(QString::fromUtf8("pushButton"));
        try_paint->setStyleSheet("QPushButton{border-image: url(images/no_line.png);}QPushButton:hover{border-image: url(images/no_line_2.png);}QPushButton:pressed{border-image: url(images/no_line_3.png);}" );
        try_paint->setGeometry(QRect(150/x,30/y, 41, 41));
        try_paint->hide();
        //connect(no_line,SIGNAL(clicked()),this,SLOT(change1()));
        //试绘界面图片更改。

        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(100, 30, 256, 192));

        tableWidget->setRowCount(10); //设置行数为10
        tableWidget->setColumnCount(4); //设置列数为5
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止编辑。
        QStringList header;
            header.append(QString::fromUtf8("序号"));
            header.append(QString::fromUtf8("图像"));
            header.append(QString::fromUtf8("姓名"));
            header.append(QString::fromUtf8("描红"));
            tableWidget->setHorizontalHeaderLabels(header);

        QTableWidgetItem *tmpItem;
        tmpItem = new QTableWidgetItem(QString("123"));
        tableWidget->setItem(0, 0, tmpItem);


        tableWidget->verticalHeader()->setVisible(false); //隐藏列表头
        tableWidget->setColumnWidth(0,50);
        tableWidget->setColumnWidth(1,50);
        tableWidget->setColumnWidth(2,50);
        tableWidget->setColumnWidth(3,50);
        //tableWidget->setStyleSheet("background:transparent");


        QPushButton *stu1;
        stu1 = new QPushButton(centralWidget);
        //stu1->setStyleSheet("QPushButton{border-image: url(images/no_line.png);}QPushButton:hover{border-image: url(images/no_line_2.png);}QPushButton:pressed{border-image: url(images/no_line_3.png);}" );
        tableWidget->setCellWidget(0,3,stu1);

        //connect(stu1,SIGNAL(),this,)
        //学生列表


        scene=new MyScene;
        scene->setSceneRect(0,0,498,598);
        //scene->setBackgroundBrush(Qt::black);
        view=new MyView(this);
        view->setScene(scene);
        view->setBackgroundBrush(Qt::transparent);
        view->resize(500,600);
        view->setGeometry(680/x,50/y,500,650);
        view->setBackgroundBrush(Qt::transparent);
        view->setStyleSheet("background:transparent");
        //view->setautoFillBackground(true);
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


        //resize(920,500);
        //end
}

MainWindow::~MainWindow()
{
    //delete ui;
}

static int yes=1;
void MainWindow::change1()
{
    if(yes==1){
    this->mainbackgroundframe->setStyleSheet("border-image:url(images/)" );
   this->no_line->setStyleSheet("QPushButton{border-image: url(images/background.png);}QPushButton:hover{border-image: url(images/line_2.png);}QPushButton:pressed{border-image: url(images/line_3.png);}" );
    yes=0;
    }
    else {
        this->mainbackgroundframe->setStyleSheet("border-image:url(images/background.png)" );
        this-> no_line->setStyleSheet("QPushButton{border-image: url(images/no_line.png);}QPushButton:hover{border-image: url(images/no_line_2.png);}QPushButton:pressed{border-image: url(images/no_line_3.png);}" );
        yes=1;
    }

}

void MainWindow::Quit()
{
    close();
}


void MainWindow::window_1()
{//界面一显示函数.
    this->horizontalSlider->show();
    this->play->show();
    this->suspend->show();
    this->no_line->show();
    this->quit->show();

    this->trace->hide();
    this->try_paint->hide();
}

void MainWindow::window_2()
{//界面二显示函数。

    this->trace->show();
    this->try_paint->show();

    this->horizontalSlider->hide();
    this->play->hide();
    this->suspend->hide();
    this->no_line->hide();
    this->quit->hide();
}

