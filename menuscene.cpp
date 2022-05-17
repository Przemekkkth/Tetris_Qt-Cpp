#include "menuscene.h"
#include "game.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QDir>
#include <QPainter>

MenuScene::MenuScene(QObject *parent)
    : QGraphicsScene{parent}
{
    setBackgroundBrush(QBrush(QColor(Qt::white)));
    setSceneRect(0, 0, Game::RESOLUTION.width(), Game::RESOLUTION.height());
    loadPixmaps();
    m_startItem = new QGraphicsPixmapItem(m_startTextPixmap);
    addItem(m_startItem);
    m_optionsItem = new QGraphicsPixmapItem(m_optionsTextPixmap);
    addItem(m_optionsItem);
    m_quitItem = new QGraphicsPixmapItem(m_quitTextPixmap);
    addItem(m_quitItem);

    createItemPos();
}

void MenuScene::loadPixmaps()
{
    if( !m_startTextPixmap.load(":/images/start_text.png") )
    {
        qDebug() << "Failed to load: " << ":/images/start_text.png";
    }
    if( !m_optionsTextPixmap.load(":/images/options_text.png") )
    {
        qDebug() << "Failed to load: " << ":/images/options_text.png";
    }
    if( !m_quitTextPixmap.load(":/images/quit_text.png") )
    {
        qDebug() << "Failed to load: " << ":/images/quit_text.png";
    }
}

void MenuScene::createItemPos()
{
    m_startItem->setPos(80, 200);
    m_optionsItem->setPos(48, 300);
    m_quitItem->setPos(96, 400);
}

void MenuScene::renderScene()
{
    QString fileName = QDir::currentPath() + QDir::separator() + "game_menu.png";
    QRect rect = sceneRect().toAlignedRect();
    QImage image(rect.size(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);
    QPainter painter(&image);
    render(&painter);
    image.save(fileName);
    qDebug() << "saved " << fileName;
}

void MenuScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(
            event->scenePos().x() > m_startItem->x() && event->scenePos().x() < (m_startItem->x() + m_startItem->boundingRect().width()) &&
            event->scenePos().y() > m_startItem->y() && event->scenePos().y() < (m_startItem->y() + m_startItem->boundingRect().height())

            )
    {
        qDebug() << "Start clicked";
        emit startClicked();
    }

    if(
            event->scenePos().x() > m_optionsItem->x() && event->scenePos().x() < (m_optionsItem->x() + m_optionsItem->boundingRect().width()) &&
            event->scenePos().y() > m_optionsItem->y() && event->scenePos().y() < (m_optionsItem->y() + m_optionsItem->boundingRect().height())

            )
    {
        qDebug() << "Options clicked";
        emit optionsClicked();
    }

    if(
            event->scenePos().x() > m_quitItem->x() && event->scenePos().x() < (m_quitItem->x() + m_quitItem->boundingRect().width()) &&
            event->scenePos().y() > m_quitItem->y() && event->scenePos().y() < (m_quitItem->y() + m_quitItem->boundingRect().height())

            )
    {
        qDebug() << "Quit clicked";
        emit quitClicked();
    }
    QGraphicsScene::mousePressEvent(event);
}

void MenuScene::keyPressEvent(QKeyEvent *event)
{
    if( !event->isAutoRepeat() )
    {
        switch(event->key())
        {
        case Qt::Key_S:
            emit startClicked();
            break;
        case Qt::Key_O:
            emit optionsClicked();
            break;
        case Qt::Key_Y:
            renderScene();
            break;
        }
    }

    QGraphicsScene::keyPressEvent(event);
}
