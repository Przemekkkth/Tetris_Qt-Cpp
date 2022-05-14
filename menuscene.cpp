#include "menuscene.h"
#include "game.h"
#include <QGraphicsSceneMouseEvent>

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

void MenuScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << event->scenePos();
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
    }
    QGraphicsScene::mousePressEvent(event);
}

void MenuScene::keyPressEvent(QKeyEvent *event)
{
    QGraphicsScene::keyPressEvent(event);
}
