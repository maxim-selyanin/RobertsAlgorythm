#include "common.h"
#include "randgen.h"

namespace {
float glc(float crd, float crd0, float acrd) {
    return (crd - crd0)/acrd;
}
//line обязательно валидная
float getSingleLambdaCoeff(const line &l, const QVector3D &p) {
    if (l.ax != 0) {
        return glc(p.x(), l.x0, l.ax);
    } else if (l.ay != 0) {
        return glc(p.y(), l.y0, l.ay);
    } else {//az != 0
        return glc(p.z(), l.z0, l.az);
    }
}
QVector3D getPointForLambda(const line &l, float lambda) {
    QVector3D p;
    p.setX(l.x0 + l.ax*lambda);
    p.setY(l.y0 + l.ay*lambda);
    p.setZ(l.z0 + l.az*lambda);
    return p;
}
}//namespace

bool onOneLine(const QVector3D &a, const QVector3D &b, const QVector3D &c)
{
    line l = lineEquation(a, b);
    if (!l.isValid()) {//a и b - одна и та же точка
        return true;
    }
    float lambda = getSingleLambdaCoeff(l, c);
    return getPointForLambda(l, lambda) == c;
}

bool onOnePlane(const QVector3D &a, const QVector3D &b, const QVector3D &c, const QVector3D &d)
{
    plane p = planeEquation(a, b, c);
    return p.a*d.x() + p.b*d.y() + p.c*d.z() + p.d == 0;
}

plane planeEquation(const QVector3D &m0, const QVector3D &m1, const QVector3D &m2)
{
    float vx10 = m1.x() - m0.x();
    float vx20 = m2.x() - m0.x();
    float vy10 = m1.y() - m0.y();
    float vy20 = m2.y() - m0.y();
    float vz10 = m1.z() - m0.z();
    float vz20 = m2.z() - m0.z();
    float detx = vy10*vz20 - vz10*vy20;
    float dety = -(vx10*vz20 - vz10*vx20);
    float detz = vx10*vy20 - vy10*vx20;
    float d = -m0.x()*detx - m0.y()*dety - m0.z()*detz;
    return plane{detx, dety, detz, d};
}

line lineEquation(const QVector3D &a, const QVector3D &b)
{
    if (a == b) {//невалидная линия
        return line();
    }
    QVector3D pv(a.x() - b.x(), a.y() - b.y(), a.z() - b.z());
    return line(a, pv);
}

line::line(const QVector3D &point, const QVector3D &vector)
    : x0(point.x())
    , y0(point.y())
    , z0(point.z())
    , ax(vector.x())
    , ay(vector.y())
    , az(vector.z())
{}

bool line::isValid() const {
    return !(ax == 0 && ay == 0 && az == 0);
}

bool plane::isValid() const {
    return !(a == 0 && b == 0 && c == 0 && d == 0);
}

void plane::reverse()
{
    a = -a;
    b = -b;
    c = -c;
    d = -d;
}

float plane::setPoint(const QVector3D &p) const
{
    return a*p.x() + b*p.y() + c*p.z() + d;
}

QVector3D randomPoint(const QVector3D &mins, const QVector3D &maxs)
{
    RandomGenerator xgen(mins.x(), maxs.x());
    RandomGenerator ygen(mins.y(), maxs.y());
    RandomGenerator zgen(mins.z(), maxs.z());
    return QVector3D(xgen(), ygen(), zgen());
}
