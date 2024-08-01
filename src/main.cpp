#include "dow.h"

#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DOW w;
    w.show();
    return a.exec();
}
