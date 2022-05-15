#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
class Scene;
class MenuScene;

class View : public QGraphicsView
{
    Q_OBJECT
public:
    explicit View(QWidget* parent = nullptr);

signals:

private:
    void createConnections();

    Scene* m_gameScene;
    MenuScene* m_menuScene;

private slots:
    void start();
    void options();
    void quit();
    void menu();
};

#endif // VIEW_H
