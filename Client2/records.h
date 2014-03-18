#ifndef RECORDS_H
#define RECORDS_H

#include <QMetaType>
#include <QColor>

class records{
public:

    double x;
    double y;
    QRgb w;

    bool operator ==(const records re){
        if((x ==re.x) && (y==re.y) && (w==re.w))
                return true;
        else
                return false;
    }
};
//  add
Q_DECLARE_METATYPE(records)
// add end
#endif // RECORDS_H
