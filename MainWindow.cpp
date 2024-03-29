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

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(IDENTITY_MATRIX);
    glLoadIdentity();
//    glOrtho(0, _windowParams.width(), _windowParams.height(), 0, 1, 0);
    glOrtho(-this->_zoom, this->_zoom, -this->_zoom, this->_zoom, -this->_zoom, this->_zoom);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    qglColor(Qt::white);

    // Включить тест глубины
    glEnable(GL_DEPTH_TEST);
    // Фрагмент будет выводиться только в том, случае, если он находится ближе к камере, чем предыдущий
    glDepthFunc(GL_LESS);

    static float angle = 10.0f;
    angle += 1.0f;
    glRotatef(angle, 1.0f, 1.0f, 1.0f);
    graph();

    double z = _Z_MIN;
    for (const SurfaceData::TopRow& row : _data.getData())
    {
        double x = _X_MIN;
        for (const SurfaceData::TopInfo& top : row)
        {
            DecartPoint3D bottomLeft = {x, 0, z};
//            const GLfloat color[3] = {(float)(rand()%256)/256, 0, 0};
            const GLfloat* color = top.topColor;
            prysm(bottomLeft, _cellWidth, top.relValue, _cellDepth, color);
            x += _cellWidth;
        }
        z += _cellDepth;
    }
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
//    _cax = me->x();
//    _cay = me->y();
//    updateGL();
}

void MainWindow::wheelEvent(QWheelEvent *me)
{
    _zoom += (me->delta() > 0) ? 0.1 : -0.1;
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

void MainWindow::prysm(const MainWindow::DecartPoint3D& bottomLeft,
                       double width,
                       double height,
                       double depth,
                       const GLfloat* color)
{
//    glColor3fv(color);
    glBegin(GL_QUADS);

    GLfloat color2[3];
//    qDebug() << height << _maxHeight;
    color2[0] = 1 * (height / _maxHeight);
    color2[1] = 1 * (height / _maxHeight);
    color2[2] = 1 * (height / _maxHeight);
    // правая грань
    {
        DecartPoint3D customBottomLeft(bottomLeft.x + width, bottomLeft.y, bottomLeft.z);
        glColor3fv(color);
        glVertex3f(customBottomLeft.x, customBottomLeft.y, bottomLeft.z);
        glVertex3f(customBottomLeft.x, customBottomLeft.y, bottomLeft.z + depth);
        glColor3fv(color2);
        glVertex3f(customBottomLeft.x, customBottomLeft.y + height, bottomLeft.z + depth);
        glVertex3f(customBottomLeft.x, customBottomLeft.y + height, bottomLeft.z);
    }

    // нижняя грань
    {
        DecartPoint3D customBottomLeft(bottomLeft.x, bottomLeft.y, bottomLeft.z);
        glColor3fv(color);
        glVertex3f(customBottomLeft.x, customBottomLeft.y, customBottomLeft.z);
        glVertex3f(customBottomLeft.x, customBottomLeft.y, customBottomLeft.z + depth);
        glVertex3f(customBottomLeft.x + width, customBottomLeft.y, customBottomLeft.z + depth);
        glVertex3f(customBottomLeft.x + width, customBottomLeft.y, customBottomLeft.z);
    }

    // верхняя грань
    {
        DecartPoint3D customBottomLeft(bottomLeft.x, bottomLeft.y + height, bottomLeft.z);
        glColor3fv(color2);
        glVertex3f(customBottomLeft.x, customBottomLeft.y, customBottomLeft.z);
        glVertex3f(customBottomLeft.x, customBottomLeft.y, customBottomLeft.z + depth);
        glVertex3f(customBottomLeft.x + width, customBottomLeft.y, customBottomLeft.z + depth);
        glVertex3f(customBottomLeft.x + width, customBottomLeft.y, customBottomLeft.z);
    }

    // левая грань
    {
        DecartPoint3D customBottomLeft(bottomLeft.x, bottomLeft.y, bottomLeft.z);
        glColor3fv(color);
        glVertex3f(customBottomLeft.x, customBottomLeft.y, customBottomLeft.z);
        glVertex3f(customBottomLeft.x, customBottomLeft.y + height, customBottomLeft.z);
        glColor3fv(color2);
        glVertex3f(customBottomLeft.x, customBottomLeft.y + height, customBottomLeft.z + depth);
        glVertex3f(customBottomLeft.x, customBottomLeft.y, customBottomLeft.z + depth);
    }

    // задняя грань
    {
        DecartPoint3D customBottomLeft(bottomLeft.x, bottomLeft.y, bottomLeft.z);
        glColor3fv(color);
        glVertex3f(customBottomLeft.x, customBottomLeft.y, customBottomLeft.z);
        glVertex3f(customBottomLeft.x + width, customBottomLeft.y, customBottomLeft.z);
        glColor3fv(color2);
        glVertex3f(customBottomLeft.x + width, customBottomLeft.y + height, customBottomLeft.z);
        glVertex3f(customBottomLeft.x, customBottomLeft.y + height, customBottomLeft.z);
    }

    // передняя грань
    {
        DecartPoint3D customBottomLeft(bottomLeft.x, bottomLeft.y, bottomLeft.z + depth);
        glColor3fv(color);
        glVertex3f(customBottomLeft.x, customBottomLeft.y, customBottomLeft.z);
        glVertex3f(customBottomLeft.x + width, customBottomLeft.y, customBottomLeft.z);
        glColor3fv(color2);
        glVertex3f(customBottomLeft.x + width, customBottomLeft.y + height, customBottomLeft.z);
        glVertex3f(customBottomLeft.x, customBottomLeft.y + height, customBottomLeft.z);
    }
    glEnd();
}

void MainWindow::graph()
{
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
}

MainWindow::DecartPoint3D MainWindow::sphereToDekart(SpherePoint3D& vertex)
{
    double x = vertex.r * sin(vertex.zenit) * cos(vertex.azimut);
    double y = vertex.r * sin(vertex.zenit) * sin(vertex.azimut);
    double z = vertex.r * cos(vertex.zenit);
    return DecartPoint3D(x, y, z);
}

MainWindow::SpherePoint3D MainWindow::dekartToSphere(DecartPoint3D& vertex)
{
    const double x2 = vertex.x * vertex.x;
    const double y2 = vertex.y * vertex.y;
    const double z2 = vertex.z * vertex.z;
    SpherePoint3D sphereVertex;
    sphereVertex.r = sqrt(x2 + y2 + z2);
    sphereVertex.zenit = atan(sqrt(x2 + y2) / vertex.z);
    sphereVertex.azimut = atan(vertex.y / vertex.x);
    return sphereVertex;
}

RetCode MainWindow::loadTopographyMap()
{
    _data.FlushSurface();
    RetCode ret = _data.ReadSurface(_filename.data());
    {
        double xAbs = abs(_X_MAX - _X_MIN);
        double zAbs = abs(_Z_MAX - _Z_MIN);
        _cellWidth = xAbs / _data.columnCount();
        _cellDepth = zAbs / _data.rowCount();
    }
//    double minHeight;
//    double maxHeight;
    _data.getTopRelValue(0, 0, _minHeight);
    _data.getTopRelValue(0, 0, _maxHeight);
    for (const SurfaceData::TopRow& row : _data.getData())
    {
        for (const SurfaceData::TopInfo& top : row)
        {
            if (top.absValue > _maxHeight)
            {
                _maxHeight = top.absValue;
            }
            else if (top.absValue < _minHeight)
            {
                _minHeight = top.absValue;
            }
        }
    }
    double step;
    if (_maxHeight >= 0 && _minHeight >= 0)
        step = _Y_MAX / _maxHeight;
    else if (_maxHeight < 0 && _minHeight < 0)
        step = abs(_Y_MIN / _minHeight);
    else
        step = abs(_Y_MAX - _Y_MIN) / abs(_maxHeight - _minHeight);

    qDebug() << abs(_Y_MAX - _Y_MIN) << abs(_maxHeight - _minHeight);
    qDebug() << step;

    _maxHeight *= step;
    for (int i = 0; i < _data.rowCount() - 1; ++i)
    {
        qDebug() << i;
        for (int j = 0; j < _data.columnCount() ; ++j)
        {
            SurfaceData::TopAbsValue val;
            _data.getTopAbsValue(i, j, val);
            _data.setTopRelValue(i, j, val * step);
            const SurfaceData::TopColor color = {0,0,1}; /*{(float)(rand()%256)/256, 0, 0};*/
            _data.setTopColor(i, j, color);
        }
    }

//        for (const SurfaceData::TopRow& row : _data.getData())
//        {
//            for (const SurfaceData::TopValue& top : row)
//            {
//                printf("%f ", top);
//            }
//            printf("\n");
//        }
    return ret;
}
