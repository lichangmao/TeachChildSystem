#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QPointF>
#include <QStack>
#include <QGraphicsPathItem>
#include <QImage>
#include <QList>
#include <QColor>
#include "records.h"


class MyScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MyScene(QObject *parent = 0);

    //枚举类，保存要画的图形的基本形状
    enum DrawShape{
        PenShape,
        RuberShape
    };
    struct DrawStackItem{
        DrawShape shape;
        void* DrawTool;
    };

    QPainterPath shape(records);


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent );
    void mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent );
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent );
    bool judge1(double x,double y);//用来判断当前位置应该显示的颜色
    bool judge2(double x,double y);//用来判断当前位置是否有碰撞,若有返回TRUE

signals:


public slots:
    void operatebtnClick();//画笔函数
    void erase(); //擦除函数
    void cancel();//清屏
    void save();  //保存路径
    void SynShow(QList<records> points);//同步显示老师端的屏幕
private:
    bool isdraw;//判断为画图或者擦除   TRUE-画图；FALSE-擦除
    bool ismousePressed;//保存鼠标左键的信息

    QGraphicsPathItem * pathitem;

    QList<records> RecPoints;//用来记录画笔的移动状态


    QStack<DrawStackItem*> instack;
    QStack<DrawStackItem*> outstack;

    QPointF* startpoint;
    QPointF* endpoint;
    QPointF* prepoint;
    DrawShape drawshape;
    QPainterPath drawpath;


};

#endif // MYSCENE_H
