#include "pyramid.h"
#include <QVector>
#include "common.h"

pyramid::pyramid(const QVector3D &p1,
                 const QVector3D &p2,
                 const QVector3D &p3,
                 const QVector3D &p4)
    : a(p1)
    , b(p2)
    , c(p3)
    , d(p4)
{}

pyramid pyramid::makeRandom(const QVector3D &mins, const QVector3D &maxs)
{
    QVector3D p1 = randomPoint(mins, maxs);

    QVector3D p2;
    do {
        p2 = randomPoint(mins, maxs);
    } while (p1 == p2);

    QVector3D p3;
    do {
        p3 = randomPoint(mins, maxs);
    } while (onOneLine(p1, p2, p3));

    QVector3D p4;
    do {
        p4 = randomPoint(mins, maxs);
    } while (onOnePlane(p1, p2, p3, p4));

    return pyramid(p1, p2, p3, p4);
}

std::array<polygon3p, 4> pyramid::getPolygons() const
{
    return std::array<polygon3p, 4>{
        polygon3p(a, b, c)
        ,polygon3p(a, b, d)
        ,polygon3p(a, c, d)
        ,polygon3p(b, c, d)
    };
}

QVector<polygon3p> pyramid::getVectorPolygons() const
{
    QVector<polygon3p> v;
    v.reserve(4);
    auto ps = getPolygons();
    for (const polygon3p &i : ps) {
        v.append(i);
    }
    return v;
}

QDebug operator<<(QDebug d, const pyramid &p)
{
    d << p.a << p.b << p.c << p.d;
    return qDebug();
}
