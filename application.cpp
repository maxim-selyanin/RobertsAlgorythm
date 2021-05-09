#include "application.h"
#include "pyramid.h"
#include "robertsalgo.h"

application::application(int argc, char **argv)
    : QApplication(argc, argv)
{
    w = new MyGLWidget();
    w->show();

    connect(w, &MyGLWidget::generatePyramid, this, &application::generatePyramid);
}

application::~application()
{
    delete w;
}

void application::generatePyramid()
{
    pyramid p = pyramid::makeRandom
            (QVector3D(-1,-1,0),
             QVector3D(1,1,1));
    //qDebug() << "pyramid: " << p;
    QVector<polygon3p> startPolygons = p.getVectorPolygons();

    robertsAlgo<4> algo(p.getPolygons());

    QVector<polygon3p> endPolygons = algo.visiblePolygons(QVector3D(0,0,0));
    //qDebug() << "result: " << endPolygons << '\n';
    w->setPolygons(startPolygons, endPolygons);
}
