#include "student.h"

Student::Student(int id,QString &name,QPixmap &headPicture,QPixmap &result,QObject *parent) :
    QObject(parent)
{
    this->id = id;
    this->name = name;
    this->headPicture = headPicture;
    this->result = result;

}

Student::Student(QObject *parent):QObject(parent){

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
