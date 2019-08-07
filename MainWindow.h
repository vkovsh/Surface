#pragma once

#include <QGLWidget>
#include <QtOpenGL>
//#include <QTimer>

#include "SurfaceData.h"

class MainWindow : public QGLWidget
{
    Q_OBJECT

public:
    MainWindow(int x, int y, int width, int height, const char* filename, QWidget* parent = nullptr);

public:
    RetCode loadTopographyMap();

public:
    struct DecartPoint3D
    {
        DecartPoint3D(double ex, double ey, double ez): x(ex), y(ey), z(ez){}
        ~DecartPoint3D(){}
        double x;
        double y;
        double z;
    };

    struct SpherePoint3D
    {
        SpherePoint3D(double er, double ze, double az): r(er), zenit(ze), azimut(az){}
        SpherePoint3D(){}
        double r;
        double zenit;
        double azimut;
    };

private:
    QRect       _windowParams;
    SurfaceData _data;
    QByteArray _filename;

private:
    double _topWidth = 0;
    double _topHeight = 0;

private:
    int _centerX;
    int _centerY;

private:
    int _cax;
    int _cay;
    int _cbx;
    int _cby;
    bool _singling;

private:
    const double _X_MIN = -0.6;
    const double _X_MAX = 0.6;
    const double _Y_MIN = -0.15;
    const double _Y_MAX = 0.15;
    const double _Z_MIN = -0.6;
    const double _Z_MAX = 0.6;

private:
    double _cellWidth = 0;
    double _cellDepth = 0;
    double _minHeight = 0;
    double _maxHeight = 0;

private:
    double _zoom = 1;

private:
    SpherePoint3D dekartToSphere(DecartPoint3D& vertex);
    DecartPoint3D sphereToDekart(SpherePoint3D& vertex);
    void selfCursor();

private:
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();

private:
    void keyPressEvent(QKeyEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);

private:
    void singlingLb();
    void graph();
    void prysm(const DecartPoint3D& bottomLeft,
               const double width,
               const double height,
               const double depth,
               const GLfloat* color);

protected slots:
    void geese_coord();


};
