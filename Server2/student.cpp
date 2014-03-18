#include <QDebug>
#include "student.h"

Student::Student(QObject *parent) :
    QObject(parent)
{
}

Student::Student(int id, QString &name, QPixmap &headPicture, QPixmap &result, QObject *parent):QObject(parent){
    this->id = id;
    this->name = name;
    this->headPicture = headPicture;
    this->result = result;
}


int Student::getId(){
    return id;
}

QString Student::getName(){
    return name;
}

QPixmap Student::getHeadPicture(){
    return headPicture;
}

QPixmap Student::getResult(){
    return result;
}

void Student::setId(int id){
    this->id = id;
}

void Student::setName(QString name){
    this->name = name;
}

void Student::setHeadPicture(QPixmap &pixmap){
    this->headPicture = pixmap;
}

void Student::setResult(QPixmap &pixmap){
    this->result = pixmap;
}

void Student::print(){
    qDebug()<<"student.id= "<<id;
    qDebug()<<"student.name= "<<name;

}
