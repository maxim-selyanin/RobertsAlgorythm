#pragma once

#include <QVector3D>
#include <array>
#include "common.h"
#include "polygon3p.h"
#include <QDebug>

class pyramid
{
    QVector3D a, b, c, d;

public:
    pyramid(const QVector3D &p1,
            const QVector3D &p2,
            const QVector3D &p3,
            const QVector3D &p4);

    static pyramid makeRandom(const QVector3D &mins, const QVector3D &maxs);
    std::array<polygon3p, 4> getPolygons() const;
    QVector<polygon3p> getVectorPolygons() const;

    friend QDebug operator<<(QDebug d, const pyramid &p);
};
