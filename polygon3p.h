#ifndef POLYGON3P_H
#define POLYGON3P_H

#include <QVector3D>
#include "common.h"

class polygon3p
{
    QVector3D _a, _b, _c;

public:
    polygon3p(const QVector3D &p1, const QVector3D &p2, const QVector3D &p3);
    plane getPlane() const;
    QVector3D meanPoint() const;

    QVector3D a() const;
    QVector3D b() const;
    QVector3D c() const;

    friend QDebug operator<<(QDebug d, const polygon3p &p);
};

#endif // POLYGON3P_H
