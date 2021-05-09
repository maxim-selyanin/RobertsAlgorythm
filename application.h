#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QApplication>
#include "interface.h"

class application : public QApplication
{
    Q_OBJECT

    MyGLWidget *w = nullptr;

public:
    explicit application(int argc, char **argv);
    ~application();

public slots:
    void generatePyramid();
};

#endif // APPLICATION_H
