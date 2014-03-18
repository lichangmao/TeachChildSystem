#ifndef MYPOINT_H
#define MYPOINT_H

#include <QObject>
#include <QColor>
/**
 * @brief The Point class
 * 表示画笔或画刷的每一个点
 */

class MyPoint : public QObject
{
    Q_OBJECT
public:
    explicit MyPoint(QObject *parent = 0);
    explicit MyPoint(QColor &color, int x, int y, QObject *parent=0);

    friend QDataStream& operator<<(QDataStream &stream, const MyPoint &point);
signals:

public slots:

private:
    QColor color;//点的颜色
    int x;  //点的坐标
    int y;  //点的坐标

};

#endif // MYPOINT_H
