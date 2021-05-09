#ifndef COMMON_H
#define COMMON_H

#include <QVector3D>

struct plane {
    float a{0}, b{0}, c{0}, d{0};

    bool isValid() const;
    void reverse();
    float setPoint(const QVector3D &p) const;
};

struct line {
    float x0{0}, y0{0}, z0{0};
    float ax{0}, ay{0}, az{0};

    line(const QVector3D &point, const QVector3D &vector);
    line() = default;

    bool isValid() const;
};

line lineEquation(const QVector3D &a, const QVector3D &b);
bool onOneLine(const QVector3D &a, const QVector3D &b, const QVector3D &c);
bool onOnePlane(const QVector3D &a, const QVector3D &b, const QVector3D &c, const QVector3D &d);
plane planeEquation(const QVector3D &a, const QVector3D &b, const QVector3D &c);
QVector3D randomPoint(const QVector3D &mins, const QVector3D &maxs);

#endif // COMMON_H
