#include "view.h"
#include "game.h"
#include "menuscene.h"
#include "scene.h"
#include <QApplication>

View::View(QWidget *parent)
    : QGraphicsView(parent), m_gameScene(new Scene()), m_menuScene(new MenuScene())
{
    setScene(m_menuScene);
    resize(Game::RESOLUTION.width()+2, Game::RESOLUTION.height()+2);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    createConnections();
}

void View::createConnections()
{
    connect(m_gameScene, &Scene::goToMenuActivated, this, &View::menu);

    connect(m_menuScene, &MenuScene::startClicked, this, &View::start);
    connect(m_menuScene, &MenuScene::optionsClicked, this, &View::options);
    connect(m_menuScene, &MenuScene::quitClicked, this, &View::quit);
}

void View::start()
{
    setScene(m_gameScene);
    m_gameScene->start();
}

void View::options()
{

}

void View::quit()
{
    QApplication::instance()->quit();
}

void View::menu()
{
    setScene(m_menuScene);
}
