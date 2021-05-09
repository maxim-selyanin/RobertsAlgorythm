#ifndef ROBERTSALGO_H
#define ROBERTSALGO_H

#include <array>
#include "common.h"
#include <QVector3D>
#include <QVector>
#include "polygon3p.h"
#include <QDebug>
#include "meanpointcounter.h"

template<int polygonAmount>
class robertsAlgo
{
    std::array<polygon3p, polygonAmount> polygons{};
public:
    robertsAlgo(const std::array<polygon3p, polygonAmount> &pls);
    QVector<polygon3p> visiblePolygons(const QVector3D &viewpoint) const;
};

template<int polygonAmount>
robertsAlgo<polygonAmount>::robertsAlgo(const std::array<polygon3p, polygonAmount> &pls)
    : polygons(pls)
{}

template<int polygonAmount>
QVector<polygon3p> robertsAlgo<polygonAmount>::visiblePolygons(const QVector3D &viewpoint) const
{
    //нашли среднюю точку
    meanPointCounter c;
    for (const polygon3p &i: polygons) {
        c(i.meanPoint());
    }
    QVector3D mean = c.result();

    //получили плоскости полигонов
    std::array<plane, polygonAmount> planes;
    for (int i = 0; i < polygonAmount; ++i) {
        planes[i] = polygons[i].getPlane();
    }

    //реверснули уравнения плоскостей
    for (plane &i: planes) {
        if (i.setPoint(mean) > 0) {
            i.reverse();
        }
    }

    //получаем итоговые полигоны
    QVector<polygon3p> result;
    for (int i = 0; i < polygonAmount; ++i) {
        //qDebug() << planes[i].setPoint(QVector3D(0,0,0));
        if (planes[i].setPoint(viewpoint) >= 0) {
            result.append(polygons[i]);
        }
    }
    return result;
}

#endif // ROBERTSALGO_H
