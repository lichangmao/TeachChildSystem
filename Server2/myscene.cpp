#include "myscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QRectF>
#include <QDebug>
#include <QPixmap>
#include <QFile>
#include <qtextstream.h>
#include <qtextcodec.h>

MyScene::MyScene(QObject *parent) :QGraphicsScene(parent)
{
    isdraw=FALSE;
    ismousePressed=FALSE;
    startpoint=new QPointF(0,0);
    endpoint=new QPointF(0,0);
    prepoint=new QPointF(0,0);
    //int paintwidth=10;

    //int paintwidth=10;
    // add
    qRegisterMetaType<records>("records");
    total =0;
    //add end


}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    ismousePressed=TRUE;

    *startpoint=mouseEvent->scenePos();
    qDebug()<<"scene clicked"<<*startpoint;

    if(isdraw){
        pathitem=new QGraphicsPathItem;
        pathitem->setFlag(QGraphicsItem::ItemIsMovable);
        pathitem->setFlag(QGraphicsItem::ItemIsFocusable);
        pathitem->setAcceptHoverEvents(true);

        //QPen pen(Qt::black);//笔迹的颜色
        //pen.setWidth(5);//笔迹的宽度
        QPainterPath* paintpath=new QPainterPath;
        drawpath=*paintpath;
        //pathitem->setPen(pen);
        pathitem->setPath(*paintpath);
        this->addItem(pathitem);
        *prepoint=*startpoint;
    }
    else if(isdraw==FALSE){
        pathitem=new QGraphicsPathItem;
        pathitem->setFlag(QGraphicsItem::ItemIsMovable);
        pathitem->setFlag(QGraphicsItem::ItemIsFocusable);
        pathitem->setAcceptHoverEvents(true);

        //QPen pen(Qt::transparent);//笔迹的颜色
        //pen.setWidth(5);//笔迹的宽度
        QPainterPath* paintpath=new QPainterPath;
        drawpath=*paintpath;
        //pathitem->setPen(pen);
        pathitem->setPath(*paintpath);
        this->addItem(pathitem);
        *prepoint=*startpoint;
    }
    else{
        QGraphicsScene::mousePressEvent(mouseEvent);
    }

}

void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

    if(ismousePressed){
        *endpoint=mouseEvent->scenePos();
        //画笔
        if(isdraw){
            QPen pen(Qt::black);//笔迹的颜色
            pen.setWidth(5);//笔迹的宽度
            pathitem->setPen(pen);

            drawpath=pathitem->path();
            drawpath.moveTo(prepoint->rx(),prepoint->ry());
            drawpath.lineTo(endpoint->rx(),endpoint->ry());
            pathitem->setPath(drawpath);

            //记录笔触的移动
            records tempt;
            tempt.x=prepoint->rx();
            tempt.y=prepoint->y();
            tempt.w=Qt::black;
            RecPoints<<tempt;
            // add
            total++;
            tempList<<tempt;
            if(total >=10){
                total =0;
                emit canSend(tempList);
                tempList.clear();
            }
            // add end
            //qDebug()<<tempt.x<<"  "<<tempt.y<<"  "<<tempt.w;
            //qDebug()<<RecPoints.last().x<<"  "<<RecPoints.last().y<<"  "<<RecPoints.last().w;

            *prepoint=*endpoint;
        }
        //橡皮擦
        else if(isdraw==FALSE){
            /*
            if(!collidingItems().isEmpty()){

                while(!instack.isEmpty()){
                    DrawStackItem* drawstackitem=instack.pop();
                    pathitem=(QGraphicsPathItem*)drawstackitem->DrawTool;
                    pathitem->setVisible(FALSE);
                    outstack.push(drawstackitem);
                }

                for(int i=0;i<RecPoints.size();i++){
                    QPen pen(RecPoints[i].w);//笔迹的颜色
                    pen.setWidth(5);//笔迹的宽度
                    pathitem->setPen(pen);
                    drawpath=pathitem->path();

                    drawpath.moveTo(RecPoints[i].x,RecPoints[i].y);
                    drawpath.lineTo(RecPoints[i].x,RecPoints[i].y);
                    pathitem->setPath(drawpath);
                    //prepoint=*endpoint;
                }

            }
            else{
                QPen pen(Qt::transparent);//笔迹的颜色
                pen.setWidth(5);//笔迹的宽度
                pathitem->setPen(pen);
                drawpath=pathitem->path();

                drawpath.moveTo(prepoint->rx(),prepoint->ry());
                drawpath.lineTo(endpoint->rx(),endpoint->ry());
                pathitem->setPath(drawpath);
                *prepoint=*endpoint;
            }*/
        }
    }
    else{
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }

}

void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent )
{
    ismousePressed=FALSE;
    DrawStackItem* drawstackitem=new DrawStackItem;
    if(isdraw){
        drawstackitem->shape=PenShape;
    }
    else{
        drawstackitem->shape=RuberShape;
    }

    drawstackitem->DrawTool=(void*)pathitem;
    instack.push(drawstackitem);
}



void MyScene::operatebtnClick()
{
    if(isdraw){
        isdraw=TRUE;
    }else {
        isdraw=TRUE;
    }
    qDebug()<<"Clicked Signal isdraw =  "<<isdraw;

}

void MyScene::erase()
{
    if(isdraw){
        isdraw=FALSE;
    }else {
        isdraw=FALSE;
    }
    qDebug()<<"Clicked Signal isdraw = "<<isdraw;

}

void MyScene::cancel()
{
    if(!instack.isEmpty()){
        while(!instack.isEmpty()){
            DrawStackItem* drawstackitem=instack.pop();
            pathitem=(QGraphicsPathItem*)drawstackitem->DrawTool;
            pathitem->setVisible(FALSE);
            outstack.push(drawstackitem);
        }
        RecPoints.clear();
    }
}

//保存函数，实现方式-出栈，保存在一个全局的变量中
void MyScene::save(){
    qDebug()<<"1";
    QFile file("MyRecordPoints.txt");
    if(file.open(QFile::WriteOnly|QIODevice::Text)){
        QTextStream stream(&file);
        for(int i=0;i<RecPoints.size();i++){
            stream<<RecPoints[i].x<<"  "<<RecPoints[i].y<<"  "<<RecPoints[i].w<<"\n";
        }
        file.close();
    }
}

/*bool MyScene::judge1(double x, double y){
    double m=QApplication::desktop()->width/1600.0;//长
    double n=QApplication::desktop()->height/900.0;//宽
    QImage qPic;
    qPic.load("C:/Users/123/Desktop/幼教/音符图片/高音谱号/高音谱号.png");

    //坐标的对应换算
    double p=x--;
    double q=y--;

    if(qPic.pixel(p,q)==Qt::black) return TRUE;
    else return FALSE;

}*/

/*bool MyScene::judge2(double x, double y){
    for(int i=0;i<RecPoints.size();i++){
        if(x==RecPoints[i].x&&y==RecPoints[i].y&&RecPoints[i].w==Qt::black){
            RecPoints[i].w=Qt::transparent;
            return TRUE;
        }
    }
    return FALSE;
}*/
/*
QPainterPath MyItem::shape()
{
    QPainterPath path;
    path.addPath(boundingRect());
   // path.addRect(-10, -10, 20, 20);
    return path;
}



*/
