#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QWidget>
#include "myscene.h"
#include "myview.h"
#include "server.h"
#include <QPushButton>
class CMainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit CMainWindow(QWidget *parent = 0);
    MyScene* scene;
    MyView* view;

    QPushButton *penbutton1btn; //画笔按钮
    QPushButton *erase1btn;//橡皮擦按钮
    QPushButton *cancel1btn;//撤销按钮
    QPushButton *save1btn;//保存按钮

private:

signals:

public slots:
    
};

#endif // CMAINWINDOW_H
