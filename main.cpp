#include "gamewindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWindow w;
    w.setWindowTitle("Game Conway");
    w.showMaximized();
    return a.exec();
}
