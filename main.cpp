#include <QtGui>
#include <QDebug>

#include "SurfaceData.h"
#include <errno.h>
#include "MainWindow.h"

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    MainWindow window(200, 200, 800, 800, "../Surface/test_maps/pyra.fdf");
    window.setWindowTitle("3D Surface");
    window.loadTopographyMap();
    window.show();
    window.setMouseTracking(true);window.setCursor(QCursor(Qt::BlankCursor));

//    SurfaceData reader("../Surface/test_maps/10-2.fdf");
//    qDebug() << reader.ReadSurface().toInt();
//    return 0;
    return app.exec();
}
