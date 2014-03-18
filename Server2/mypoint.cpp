#include <QDataStream>
#include "mypoint.h"

MyPoint::MyPoint(QObject *parent) :
    QObject(parent)
{
    x = 0;
    y = 0;
}

MyPoint::MyPoint(QColor &color, int x, int y, QObject *parent):QObject(parent){
    this->color = color;
    this->x = x;
    this->y = y;
}


QDataStream& operator <<(QDataStream &stream, const MyPoint &point) {
    stream<< point.color;
    stream<< point.x;
    stream <<point.y;

    return stream;

}
