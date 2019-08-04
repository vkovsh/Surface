#pragma once

#include <QGLWidget>
#include <QtOpenGL>
#include <QTimer>

class MainWindow : public QGLWidget
{
    Q_OBJECT

public:
    MainWindow(int x, int y, int width, int height, QWidget* parent = 0);

private:
    QRect   _windowParams;
    double _radial;
    double _zenit;
    double _azimut;

    int geese_size;
    int gdx, gdy;
    int cax, cay, cbx, cby;
    bool singling;

private:
    void dekartToSphere(QVector3D& vertex);
    void self_cursor();
//    void setGeometry()

private:
    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();

private:
    void keyPressEvent(QKeyEvent *ke);
    void mouseMoveEvent(QMouseEvent *me);
    void mousePressEvent(QMouseEvent *me);
    void mouseReleaseEvent(QMouseEvent *me);

private:
    void singling_lb();
    void graph();


protected slots:
    void geese_coord();


};
