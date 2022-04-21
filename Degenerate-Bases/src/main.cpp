#include "pch.h"
#include "gui/MainWindow.h"
#include "settings/settings.h"

int main(int argc, char *argv[])
{
    dgn::Settings::CreateDefault();
    dgn::Settings::ReadSettings();

    QApplication a(argc, argv);

    dgn::MainWindow w;
    w.show();

    return a.exec();
}
