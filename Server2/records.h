#ifndef RECORDS_H
#define RECORDS_H

#include <QMetaType>
#include <QColor>

struct records{
    double x;
    double y;
    QRgb w;
};
//  add
Q_DECLARE_METATYPE(records)
// add end
#endif // RECORDS_H
