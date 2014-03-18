#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>
#include <QDataStream>
#include <QString>
#include <QPixmap>

class Student : public QObject
{
    Q_OBJECT
public:
    explicit Student(QObject *parent = 0);
    explicit Student(int id, QString &name, QPixmap &headPicture, QPixmap &result, QObject *parent);
    int getId();
    QString getName();
    QPixmap getHeadPicture();
    QPixmap getResult();

    void setId(int id);
    void setName(QString name);
    void setHeadPicture(QPixmap &pixmap);
    void setResult(QPixmap &pixmap);


signals:

public slots:
    void print();
private:
    int id;//学生ID
    QString name;//学生名字
    QPixmap headPicture;//学生头像
    QPixmap result;//学生的描红结果

};

#endif // STUDENT_H
