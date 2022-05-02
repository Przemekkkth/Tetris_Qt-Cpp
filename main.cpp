#include "view.h"
#include "scene.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Scene s;
    View w;
    w.setScene(&s);
    w.resize(QSize(s.sceneRect().size().width() + 2, s.sceneRect().size().height()+ 2));
    w.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    w.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    w.show();
    return a.exec();
}
