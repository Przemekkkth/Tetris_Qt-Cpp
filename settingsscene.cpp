#include "settingsscene.h"
#include "game.h"
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>

SettingsScene::SettingsScene(QObject *parent)
    : QGraphicsScene{parent}
{
    setBackgroundBrush(QBrush(QColor(Qt::white)));
    setSceneRect(0, 0, Game::RESOLUTION.width(), Game::RESOLUTION.height());
    loadPixmaps();

    m_rotateItem = new QGraphicsPixmapItem(m_rotatePixmap);
    addItem(m_rotateItem);
    m_rightItem = new QGraphicsPixmapItem(m_rightPixmap);
    addItem(m_rightItem);
    m_leftItem = new QGraphicsPixmapItem(m_leftPixmap);
    addItem(m_leftItem);
    m_speedupItem = new QGraphicsPixmapItem(m_speedupPixmap);
    addItem(m_speedupItem);
    m_pauseItem = new QGraphicsPixmapItem(m_pausePixmap);
    addItem(m_pauseItem);
    m_backspaceItem = new QGraphicsPixmapItem(m_backspacePixmap);
    addItem(m_backspaceItem);
    m_backTextItem = new QGraphicsPixmapItem(m_backTextPixmap);
    addItem(m_backTextItem);

    createItemPos();
}

void SettingsScene::loadPixmaps()
{
    if( !m_rotatePixmap.load(":/images/rotate_description.png") )
    {
        qDebug() << "Failed to load: " << ":/images/rotate_description.png";
    }

    if( !m_rightPixmap.load(":/images/right_description.png") )
    {
        qDebug() << "Failed to load: " << ":/images/right_description.png";
    }

    if( !m_leftPixmap.load(":/images/left_description.png") )
    {
        qDebug() << "Failed to load: " << ":/images/left_description.png";
    }

    if( !m_speedupPixmap.load(":/images/speedup_description.png") )
    {
        qDebug() << "Failed to load: " << ":/images/speedup_description.png";
    }

    if( !m_pausePixmap.load(":/images/pause_description.png") )
    {
        qDebug() << "Failed to load: " << ":/images/pause_description.png";
    }

    if( !m_backspacePixmap.load(":/images/back_description.png") )
    {
        qDebug() << "Failed to load: " << ":/images/back_description.png";
    }

    if( !m_backTextPixmap.load(":/images/back_text.png") )
    {
        qDebug() << "Failed to load: " << ":/images/back_text.png";
    }
}

void SettingsScene::createItemPos()
{
    //w:288px
    m_rotateItem->setPos(16,0);
    //w:256px
    m_rightItem->setPos(32,50);
    //w:224px
    m_leftItem->setPos(48,100);
    //w:320px
    m_speedupItem->setPos(0,150);
    //w:224px
    m_pauseItem->setPos(48,200);
    //w:224px
    m_backspaceItem->setPos(48,250);
    //w:128px
    m_backTextItem->setPos(96, 400);
}

void SettingsScene::keyPressEvent(QKeyEvent *event)
{
    if( !event->isAutoRepeat() )
    {
      switch(event->key())
        {
            case Qt::Key_Backspace:
                emit goToMenuActivated();
            break;
            default:
                break;
        }
    }

    QGraphicsScene::keyPressEvent(event);
}

void SettingsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(
            event->scenePos().x() > m_backTextItem->x() && event->scenePos().x() < (m_backTextItem->x() + m_backTextItem->boundingRect().width()) &&
            event->scenePos().y() > m_backTextItem->y() && event->scenePos().y() < (m_backTextItem->y() + m_backTextItem->boundingRect().height())

            )
    {
        emit goToMenuActivated();
    }
    QGraphicsScene::mousePressEvent(event);
}
