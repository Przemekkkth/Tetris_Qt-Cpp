#include "view.h"
#include "game.h"
#include "menuscene.h"
#include "gamescene.h"
#include "settingsscene.h"
#include <QApplication>
#include <QCursor>
#include <QSoundEffect>

View::View(QWidget *parent)
    : QGraphicsView(parent), m_gameScene(new GameScene()), m_menuScene(new MenuScene()), m_settingsScene(new SettingsScene())
{
    setScene(m_menuScene);
    resize(Game::RESOLUTION.width()+2, Game::RESOLUTION.height()+2);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_cursor = QCursor( QPixmap(":/images/cursor.png").scaled(16,16) );
    setCursor(m_cursor);

    m_backgroundMusic = new QSoundEffect(this);
    m_backgroundMusic->setSource(QUrl("qrc:/music/background.wav"));
    m_backgroundMusic->setLoopCount(QSoundEffect::Infinite);
    m_backgroundMusic->setVolume(0.5f);
    m_backgroundMusic->play();


    createConnections();
}

void View::createConnections()
{
    connect(m_gameScene, &GameScene::goToMenuActivated, this, &View::menu);

    connect(m_settingsScene, &SettingsScene::goToMenuActivated, this, &View::menu);

    connect(m_menuScene, &MenuScene::startClicked, this, &View::start);
    connect(m_menuScene, &MenuScene::optionsClicked, this, &View::options);
    connect(m_menuScene, &MenuScene::quitClicked, this, &View::quit);
}

void View::start()
{
    setScene(m_gameScene);
    m_gameScene->start();
    setCursor(QCursor(Qt::BlankCursor));
}

void View::options()
{
    setScene(m_settingsScene);
}

void View::quit()
{
    QApplication::instance()->quit();
}

void View::menu()
{
    setScene(m_menuScene);
    setCursor(m_cursor);
}
