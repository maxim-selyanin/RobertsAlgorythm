#include "interface.h"
#include <QOpenGLFunctions>
#include <QDebug>

void MyGLWidget::scene()
{
    QVector<polygon3p> &drawable = drawOnlyVisible ? endPolygons : startPolygons;
    for (int i = 0; i < drawable.length(); ++i) {
        glColor3f(colors[i].x(), colors[i].y(), colors[i].z());
        drawPolygon(drawable[i]);
    }
}

void MyGLWidget::drawPolygon(const polygon3p &p)
{
    glBegin(GL_POLYGON);
    glVertex3d(p.a().x(), p.a().y(), p.a().z());
    glVertex3d(p.b().x(), p.b().y(), p.b().z());
    glVertex3d(p.c().x(), p.c().y(), p.c().z());
    glEnd();
}

MyGLWidget::MyGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    this->setGeometry(500, 500, 500, 500);

    makeNew = new QPushButton("make new pyramid", this);
    makeNew->setGeometry(10, 10, 200, 30);

    onlyVisible = new QRadioButton("only visible sides", this);
    onlyVisible->setGeometry(228, 10, 150, 30);

    connect(makeNew, &QPushButton::pressed, this, &MyGLWidget::generatePyramid);
    connect(onlyVisible, &QRadioButton::pressed, this, &MyGLWidget::upd);
}

MyGLWidget::~MyGLWidget()
{
}

void MyGLWidget::setPolygons(const QVector<polygon3p> &start, const QVector<polygon3p> &end)
{
    startPolygons = start;
    endPolygons = end;
    update();
}

void MyGLWidget::initializeGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glClearDepth(1.0);                      // Разрешить очистку буфера глубины
    glDepthFunc(GL_LESS);                   // Тип теста глубины
    glEnable(GL_DEPTH_TEST);                // разрешить тест глубины

    glShadeModel(GL_SMOOTH);        // разрешить плавное цветовое сглаживание
    glMatrixMode(GL_PROJECTION);    // Выбор матрицы проекции
    glLoadIdentity();               // Сброс матрицы проекции
    //gluPerspective(45.0f,(GLfloat)this->width()/(GLfloat)this->height(),0.1f,100.0f);
                                    // Вычислить соотношение геометрических размеров для окна
    glMatrixMode(GL_MODELVIEW);     // Выбор матрицы просмотра модели

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
}

void MyGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //gluPerspective(120.0,(GLdouble)w/(GLdouble)h,1,1000.0);// Вычисление соотношения геометрических размеров для окна
    glMatrixMode(GL_MODELVIEW);     // Выбор матрицы просмотра модели
}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    this->scene();
    QOpenGLContext::currentContext()->swapBuffers(QOpenGLContext::currentContext()->surface());//swap buffers
}

void MyGLWidget::gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
    GLdouble xmin, xmax, ymin, ymax;

    ymax = zNear * tan( fovy * 3.14 / 360.0 );
    ymin = -ymax;
    xmin = ymin * aspect;
    xmax = ymax * aspect;

    glFrustum( xmin, xmax, ymin, ymax, zNear, zFar );
}

void MyGLWidget::upd()
{
    drawOnlyVisible = !drawOnlyVisible;
    update();
}
