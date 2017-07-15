#include "interfacedialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InterfaceDialog w;
    w.show();

    return a.exec();
}
