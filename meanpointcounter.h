#ifndef MEANPOINTCOUNTER_H
#define MEANPOINTCOUNTER_H

#include <QVector3D>

class meanPointCounter
{
    QVector3D sum{0,0,0};
    int amount = 0;
public:
    meanPointCounter() = default;
    void operator()(const QVector3D &p);
    QVector3D result() const;
};

#endif // MEANPOINTCOUNTER_H
