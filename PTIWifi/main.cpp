#include "interfacedialog.h"
#include <QApplication>
#include "linux.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InterfaceDialog w;
    w.show();

    return a.exec();
}
