#include "MediaTestPlayer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MediaTestPlayer w;
    w.show();

    return a.exec();
}
