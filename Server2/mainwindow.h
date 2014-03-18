#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui/QSlider>
#include <QPushButton.h>
#include <QtGui/QHeaderView>
#include <QDialog>
#include "myscene.h"
#include "myview.h"
#include <QtGui/QComboBox>
#include <QtGui/QTableWidget>
#include <QWidget>

namespace Ui {
class MainWindow;
}

//using namespace Ui;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QMainWindow *parent = 0);
    ~MainWindow();
    MyScene* scene;
    MyView* view;
protected:
    QFrame *mainbackgroundframe;
    QSlider *horizontalSlider;
    QPushButton *no_line;//不显示五线谱按钮
    QPushButton *suspend;//中止按钮
    QPushButton *play;//播放暂停按钮
    QPushButton *quit;//退出按钮
    QComboBox *comboBox;//下拉按钮
    QPushButton *trace;//描红按钮
    QPushButton *try_paint;//试绘按钮a
    QTableWidget *tableWidget;//学生人员界面。

    //山妹部分
    //explicit CMainWindow(QWidget *parent = 0);
    //MyScene* scene;
    //MyView* view;

    QPushButton *penbutton1btn; //画笔按钮
    QPushButton *erase1btn;//橡皮擦按钮
    QPushButton *cancel1btn;//撤销按钮
    QPushButton *save1btn;//保存按钮
    //山妹部分 end


private slots:
    void change1();
    void Quit();
    void window_1();
    void window_2();

private:
    //Ui::MainWindow *ui;
    //MainWindow *ui;
};



#endif // MAINWINDOW_H
