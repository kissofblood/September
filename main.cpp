#include "septembereditor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SeptemberEditor w;
    w.showMaximized();

    return a.exec();
}
