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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLfloat IDENTITY_MATRIX[16] = {
      1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1
    };

//    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(IDENTITY_MATRIX);
//    glLoadIdentity();
//    glOrtho(0, _windowParams.width(), _windowParams.height(), 0, 1, 0);
    glOrtho(-1, 1, -1, 1, -1, 1);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    qglColor(Qt::white);

    graph();

    if (_singling == true) { singlingLb(); }

    selfCursor();

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
    _cax = me->x();
    _cay = me->y();
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

void MainWindow::selfCursor()
{
    glBegin(GL_POLYGON);
        glColor3f(1,0,0);
        glVertex2f(_cax, _cay);
        glVertex2f(_cax + 20, _cay + 20);
        glVertex2f(_cax + 8, _cay + 20);
        glVertex2f(_cax, _cay + 30);
    glEnd();
}

void MainWindow::singlingLb()
{
    glBegin(GL_POLYGON);
        glColor4f(0, 1, 0, 0.25);
        glVertex2f(_cbx, _cby);
        glVertex2f(_cax, _cby);
        glVertex2f(_cax, _cay);
        glVertex2f(_cbx, _cay);
    glEnd();
}

void MainWindow::geese_coord()
{
//    _centerX++;
//    _centerY++;
//    updateGL();
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
//    glBegin(GL_LINES);
//        glColor3f(0, 0, 0);
//        glVertex2f(-1.0f, 0.0f);
//        glVertex2f(1.0f, 0.0f);
////        glVertex2f(_centerX, _centerY);
////        glVertex2f(_centerX, _centerY - 300);
////        glColor3f(0, 1, 0);
////        glVertex2f(_centerX, _centerY);
////        glVertex2f(_centerX + 300, _centerY);
////        glColor3f(0, 0, 1);
////        glVertex2f(_centerX, _centerY);
////        glVertex2f(_centerX - 150, _centerY + 300);
//    glEnd();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1, 0.0f, 0.0f); // sets color to black.

    glLoadIdentity();
//    glTranslatef(0.5f, 0.5f, 0.5f);

    static float angle = 0.0f;
    angle += 1.0f;
    glRotatef(angle, 1.0f, 1.0f, 1.0f);
//    glTranslatef(vec_vehicle_position_.x, vec_vehicle_position_.y, 0);
    glBegin(GL_QUADS);
        glColor3f(0.5f, 0.3f, 0.6f);
//        glColor3f((rand() % 0xff) / (double)0xff , (rand() % 0xff) / (double)0xff, (rand() % 0xff) / (double)0xff);
    // правая грань
//        glColor3f((rand() % 0xff) / (double)0xff , (rand() % 0xff) / (double)0xff, (rand() % 0xff) / (double)0xff);
        glVertex3f(0.5, -0.5, -0.5);
        glVertex3f(0.5, -0.5, 0.5);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(0.5, 0.5, -0.5);
    // нижняя грань
//        glColor3f((rand() % 0xff) / (double)0xff , (rand() % 0xff) / (double)0xff, (rand() % 0xff) / (double)0xff);
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(0.5, -0.5, 0.5);
        glVertex3f(0.5, -0.5, -0.5);
    // верхняя грань
//        glColor3f((rand() % 0xff) / (double)0xff , (rand() % 0xff) / (double)0xff, (rand() % 0xff) / (double)0xff);
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(-0.5, 0.5, 0.5);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(0.5, 0.5, -0.5);
    // левая грань
//        glColor3f((rand() % 0xff) / (double)0xff , (rand() % 0xff) / (double)0xff, (rand() % 0xff) / (double)0xff);
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(-0.5, 0.5, 0.5);
        glVertex3f(-0.5, -0.5,  0.5);
    // задняя грань
//        glColor3f((rand() % 0xff) / (double)0xff , (rand() % 0xff) / (double)0xff, (rand() % 0xff) / (double)0xff);
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(0.5, -0.5, -0.5);
        glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(-0.5, 0.5, -0.5);
    // передняя грань
//        glColor3f((rand() % 0xff) / (double)0xff , (rand() % 0xff) / (double)0xff, (rand() % 0xff) / (double)0xff);
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(0.5, -0.5, 0.5);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(-0.5, 0.5, 0.5);
    glEnd();

    glBegin(GL_LINES);
    //ox
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(1.0f, 0.0f, 0.0f);
    //oy
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, -1.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
    //oz
        glColor3f(0, 0, 1);
        glVertex3f(0.0f, 0.0f, -1.0f);
        glVertex3f(0.0f, 0.0f, 1.0f);
    glEnd();
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glColor3f(0.0f, 0.0f, 0.0f); // sets color to black.
//    glBegin(GL_QUADS);
//            glVertex2f(-0.25f, 0.25f); // vertex 1
//            glVertex2f(-0.5f, -0.25f); // vertex 2
//            glVertex2f(0.5f, -0.25f); // vertex 3
//            glVertex2f(0.25f, 0.25f); // vertex 4
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
