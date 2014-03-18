#include "myview.h"
#include <QPixmap>
MyView::MyView(QWidget *parent) :
    QGraphicsView(parent)
{
}

void MyView::Save()
{
    QPixmap pixmap;
    pixmap.grabWidget(this,this->geometry()).save("1.png");
}

