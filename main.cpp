#include "view.h"
#include "gamescene.h"
#include "menuscene.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    View w;
    w.show();

    return a.exec();
}
