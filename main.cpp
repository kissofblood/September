#include "septembereditor.h"
#include "setting/settingapp.h"

int main(int argc, char *argv[])
{
    SettingApp a(argc, argv, "September", "September");

    SeptemberEditor w;
    w.showMaximized();

    return a.exec();
}
