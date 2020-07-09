#include <QtWidgets/QApplication>
#include "./app/app.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    App aps;
    aps.run();
    return a.exec();
}
