#include "visualized_neural_networks.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Visualized_Neural_Networks w;
    w.show();
    return a.exec();
}
