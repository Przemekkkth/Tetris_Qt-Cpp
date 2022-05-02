#include "scene.h"
#include <QKeyEvent>

Scene::Scene(QObject *parent) : QGraphicsScene(parent), game(), timePerFrame(1000.0f/60.0f)
{
    setSceneRect(0,0, 320, 480);


    m_frame = new QGraphicsPixmapItem(game.m_frame);

    m_tiles = new QGraphicsPixmapItem(game.m_tile);

    //m_tiles->update()
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Scene::update);
    timer->start(timePerFrame);
    game.m_field[0][0] = 1;
    game.m_field[3][3] = 3;
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if( !event->isAutoRepeat() )
    {
        qDebug() << "Pressed key: " << event->key();
        switch(event->key())
        {
        case Qt::Key_Left:
            game.m_dx = -1;
            break;

        case Qt::Key_Right:
            game.m_dx = 1;
            break;

        case Qt::Key_Up:
            game.m_rotate = true;
            break;

        case Qt::Key_Down:
            game.m_delay = 0.05;
            break;
        default:
            break;
        }


    }

    QGraphicsScene::keyPressEvent(event);
}

void Scene::keyReleaseEvent(QKeyEvent *event)
{
    if( !event->isAutoRepeat() )
    {
        qDebug() << "Released key: " << event->key();
        switch(event->key())
        {
        case Qt::Key_Left:
        case Qt::Key_Right:
            game.m_dx = 0;
            break;

        case Qt::Key_Up:
            game.m_rotate = false;
            break;

        case Qt::Key_Down:
            game.m_delay = 0.03;
        default:
            break;
        }
    }
    QGraphicsScene::keyReleaseEvent(event);
}

void Scene::update()
{
    clear();
    m_background = new QGraphicsPixmapItem(game.m_background);
    addItem(m_background);


    for (int i=0;i<game.M;i++)
    {
        for (int j=0;j<game.N;j++)
          {
            if (game.m_field[i][j]==0) continue;
            QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(game.m_tile.copy(game.m_field[i][j]*18, 0, 18, 18));
            addItem(pixmapItem);
            pixmapItem->setPos(j*18, i*18);
            pixmapItem->moveBy(28, 31);
          }

    }

    for (int i=0;i<4;i++)
      {
        QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(game.m_tile.copy(game.m_colorNum, 0, 18, 18));
        addItem(pixmapItem);
        pixmapItem->setPos(game.m_a[i].x * 18, game.m_a[i].y * 18);
        pixmapItem->moveBy(28, 31);
      }
}
