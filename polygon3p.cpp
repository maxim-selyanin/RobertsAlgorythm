#include "polygon3p.h"
#include <QDebug>

polygon3p::polygon3p(const QVector3D &p1, const QVector3D &p2, const QVector3D &p3)
    : _a(p1)
    , _b(p2)
    , _c(p3)
{}

plane polygon3p::getPlane() const
{
    return planeEquation(_a, _b, _c);
}

QVector3D polygon3p::meanPoint() const
{
    return QVector3D(
                (_a.x() + _b.x() + _c.x())/3
                ,(_a.y() + _b.y() + _c.y())/3
                ,(_a.z() + _b.z() + _c.z())/3
                );
}

QVector3D polygon3p::a() const {return _a;}

QVector3D polygon3p::b() const {return _b;}

QVector3D polygon3p::c() const {return _c;}

QDebug operator<<(QDebug d, const polygon3p &p)
{
    d << "a: " << p.a() << "\nb: " << p.b() << "\nc: " << p.c();
    return d;
}
