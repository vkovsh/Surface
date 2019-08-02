#include <QtGui>
#include "mainwindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    MainWindow window(200, 200, 800, 800);
    window.setWindowTitle("3D Surface");
    window.show();
    window.setMouseTracking(true);window.setCursor(QCursor(Qt::BlankCursor));

    return app.exec();
}
