#include "meanpointcounter.h"

void meanPointCounter::operator()(const QVector3D &p)
{
    sum += p;
    ++amount;
}

QVector3D meanPointCounter::result() const
{
    if (amount) {
        return sum / amount;
    } else {
        return QVector3D();
    }
}
