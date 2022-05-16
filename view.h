#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
class GameScene;
class MenuScene;
class SettingsScene;

class View : public QGraphicsView
{
    Q_OBJECT
public:
    explicit View(QWidget* parent = nullptr);

signals:

private:
    void createConnections();

    GameScene* m_gameScene;
    MenuScene* m_menuScene;
    SettingsScene* m_settingsScene;

private slots:
    void start();
    void options();
    void quit();
    void menu();
};

#endif // VIEW_H
