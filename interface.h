#pragma once

#include <QOpenGLWidget>
#include <QVector3D>
#include <QPushButton>
#include <QRadioButton>
#include "polygon3p.h"

class MyGLWidget : public QOpenGLWidget
{
    Q_OBJECT

    QPushButton *makeNew = nullptr;
    QRadioButton *onlyVisible = nullptr;

    QVector<polygon3p> endPolygons{};
    QVector<polygon3p> startPolygons{};
    bool drawOnlyVisible = false;

    QVector3D colors[5] = {{1.0, 0.0, 0.0},//1. red
                          {0.0, 1.0, 0.0},// 2. green
                          {0.0, 0.0, 1.0},// 3. blue
                          {0.0, 0.0, 0.0},// 4. black
                          {1.0, 1.0, 1.0}};//5. white

    void scene();
    void drawPolygon(const polygon3p &p);

public:
    MyGLWidget(QWidget *parent = nullptr);
    ~MyGLWidget() override;

    void setPolygons(const QVector<polygon3p> &start, const QVector<polygon3p> &end);

protected:

    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

    void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);

signals:
    void generatePyramid();

private slots:
    void upd();
};
