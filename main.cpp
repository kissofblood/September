#include "septembereditor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SeptemberEditor w;
    w.show();

    return a.exec();
}
