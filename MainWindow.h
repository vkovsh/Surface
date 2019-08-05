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
    struct Vector3D
    {
        double x;
        double y;
        double z;
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
    void dekartToSphere(Vector3D& vertex);
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

private:
    void singlingLb();
    void graph();

protected slots:
    void geese_coord();


};
