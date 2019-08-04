#include "MainWindow.h"

MainWindow::MainWindow(int x, int y, int width, int height, const char* filename, QWidget* parent) :
    QGLWidget(parent),
    _windowParams(QRect(x, y, width, height)),
    _filename(QByteArray(filename))
{
    _centerX = 300;
    _centerY = 300;

    setGeometry(_windowParams);
//    geese_size=30;
    _singling=false;
    geese_coord();
    setFormat(QGLFormat(QGL::DoubleBuffer));
    glDepthFunc(GL_LEQUAL);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(geese_coord()));
    timer->start(750);
}

void MainWindow::initializeGL()
{
    qglClearColor(Qt::white); // Черный цвет фона
}

void MainWindow::resizeGL(int nWidth, int nHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
    _windowParams.setWidth(nWidth);
    _windowParams.setHeight(nHeight);
}

void MainWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // чистим буфер изображения и буфер глубины
    glMatrixMode(GL_PROJECTION); // устанавливаем матрицу
    glLoadIdentity(); // загружаем матрицу
    glOrtho(0, _windowParams.width(), _windowParams.height(), 0, 1, 0); // подготавливаем плоскости для матрицы
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    qglColor(Qt::white);

    graph(); // Рисуем объект

    if (_singling == true) { singling_lb(); } // Рисуем выделение, если оно есть

    self_cursor(); // Загружаем наш курсор

    swapBuffers();
}

void MainWindow::keyPressEvent(QKeyEvent *ke)
{
    switch (ke->key())
    {

          case Qt::Key_Space:
                geese_coord();
                break;
    }
    updateGL();
}

void MainWindow::mouseMoveEvent(QMouseEvent *me)
{
    // Получаем координаты курсора
    cax=me->x();
    cay=me->y();
    updateGL();
}

void MainWindow::mousePressEvent(QMouseEvent *me)
{
//    if(me->button()==Qt::LeftButton){
//        if(me->x()>gdx&&me->x()<gdx+geese_size){
//            if(me->y()>gdy&&me->y()<gdy+geese_size){
//                geese_coord();
//            }
//        }
//    }

//    if(me->button()==Qt::LeftButton){
//        singling=true;
//        cbx=me->x();
//        cby=me->y();
//        updateGL();
//    } else {
//        singling=false;
//    }
//    updateGL();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *me)
{
    // Если отпускаем левую кнопку мыши - удалить выделение
    if (_singling == true && me->button() == Qt::LeftButton)
    {
        _singling = false;
    }
    updateGL();
}

void MainWindow::self_cursor()
{
    glBegin(GL_POLYGON);
        glColor3f(1,0,0);// Цвет курсора
        // Координаты курсора
        glVertex2f(cax, cay);
        glVertex2f(cax+20, cay+20);
        glVertex2f(cax+8, cay+20);
        glVertex2f(cax, cay+30);
    glEnd();
}

void MainWindow::singling_lb()
{
    glBegin(GL_POLYGON);
        glColor4f(0,1,0, 0.25);
        glVertex2f(cbx, cby);
        glVertex2f(cax, cby);
        glVertex2f(cax, cay);
        glVertex2f(cbx, cay);
    glEnd();
}

void MainWindow::geese_coord()
{
//    gdx = (rand() % (_windowParams.width() - geese_size * 2)) + geese_size;
//    gdy = (rand() % (_windowParams.height() - geese_size * 2)) + geese_size;
    _centerX++;
    _centerY++;
    updateGL();
}


void MainWindow::graph()
{
//    glBegin(GL_POLYGON);
//        glColor3f(1,0,0);// Цвет выделенной области
//        // Координаты выделенной области
//        glVertex2f(gdx, gdy);
//        glVertex2f(gdx+geese_size, gdy);
//        glVertex2f(gdx+geese_size, gdy+geese_size);
//        glVertex2f(gdx, gdy+geese_size);
//    glEnd();
    glBegin(GL_LINES);
        glColor3f(1, 0, 0);
        glVertex2f(_centerX, _centerY);
        glVertex2f(_centerX, _centerY - 300);
        glColor3f(0, 1, 0);
        glVertex2f(_centerX, _centerY);
        glVertex2f(_centerX + 300, _centerY);
        glColor3f(0, 0, 1);
        glVertex2f(_centerX, _centerY);
        glVertex2f(_centerX - 150, _centerY + 300);
    glEnd();

//    int size = 400;
//    glBegin(GL_QUADS);
//        glColor3f(1, 0, 0);
//         // левая грань
//         glVertex3f( -size / 2, -size / 2, -size / 2);
//         glVertex3f( -size / 2,  size / 2, -size / 2);
//         glVertex3f( -size / 2,  size / 2,  size / 2);
//         glVertex3f( -size / 2, -size / 2,  size / 2);
//         // правая грань
//         glVertex3f(  size / 2, -size / 2, -size / 2);
//         glVertex3f(  size / 2, -size / 2,  size / 2);
//         glVertex3f(  size / 2,  size / 2,  size / 2);
//         glVertex3f(  size / 2,  size / 2, -size / 2);
//         // нижняя грань
//         glVertex3f( -size / 2, -size / 2, -size / 2);
//         glVertex3f( -size / 2, -size / 2,  size / 2);
//         glVertex3f(  size / 2, -size / 2,  size / 2);
//         glVertex3f(  size / 2, -size / 2, -size / 2);
//         // верхняя грань
//         glVertex3f( -size / 2, size / 2, -size / 2);
//         glVertex3f( -size / 2, size / 2,  size / 2);
//         glVertex3f(  size / 2, size / 2,  size / 2);
//         glVertex3f(  size / 2, size / 2, -size / 2);
//         // задняя грань
//         glVertex3f( -size / 2, -size / 2, -size / 2);
//         glVertex3f(  size / 2, -size / 2, -size / 2);
//         glVertex3f(  size / 2,  size / 2, -size / 2);
//         glVertex3f( -size / 2,  size / 2, -size / 2);
//         // передняя грань
//         glVertex3f( -size / 2, -size / 2,  size / 2);
//         glVertex3f(  size / 2, -size / 2,  size / 2);
//         glVertex3f(  size / 2,  size / 2,  size / 2);
//         glVertex3f( -size / 2,  size / 2,  size / 2);
//    glEnd();
}

void MainWindow::dekartToSphere(Vector3D& vertex)
{
    const double x = vertex.x;
    const double y = vertex.y;
    const double z = vertex.z;
    {
        const double x2 = x * x;
        const double y2 = y * y;
        const double z2 = z * z;
        vertex.x = sqrt(x2 + y2 + z2);
        vertex.y = atan(sqrt(x2 + y2) / z);
        vertex.z = atan(y / x);
    }
}

RetCode MainWindow::loadTopographyMap()
{
    _data.FlushSurface();
    return _data.ReadSurface(_filename.data());
}
