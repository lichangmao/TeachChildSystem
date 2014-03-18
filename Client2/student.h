#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>
#include <QString>
#include <QPixmap>
#include <QDataStream>

/**
 * @brief The Student class 表示学生
 */

class Student : public QObject
{
    Q_OBJECT
public:
    explicit Student(int id, QString &name, QPixmap &headPicture, QPixmap &result, QObject *parent = 0);
    explicit Student(QObject *parent = 0);

    int getId();
    QString getName();
    QPixmap getHeadPicture();
    QPixmap getResult();


signals:

public slots:

private:
    int id;//学生ID
    QString name;//学生名字
    QPixmap headPicture;//学生头像
    QPixmap result;//学生的描红结果

};

#endif // STUDENT_H
