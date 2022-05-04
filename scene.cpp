#include "scene.h"
#include <QKeyEvent>
#include <QDebug>

Scene::Scene(QObject *parent) : QGraphicsScene(parent), game(), timePerFrame(1000.0f/60.0f)
{
    setSceneRect(0,0, 320, 480);
    srand(time(0));

    m_frame = new QGraphicsPixmapItem(game.m_frame);

    m_tiles = new QGraphicsPixmapItem(game.m_tile);

    //m_tiles->update()
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Scene::update);
    timer->start(timePerFrame);
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if( !event->isAutoRepeat() )
    {
        qDebug() << "Pressed key: " << event->key();
        switch(event->key())
        {
        case Qt::Key_Left:
        case Qt::Key_A:
            game.m_dx = -1;
            break;

        case Qt::Key_Right:
        case Qt::Key_D:
            game.m_dx = 1;
            break;

        case Qt::Key_Up:
        case Qt::Key_W:
            game.m_rotate = true;
            break;

        case Qt::Key_Down:
        case Qt::Key_S:
            game.m_delay = Game::SPEED_UP;
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
        case Qt::Key_A:
        case Qt::Key_D:
            game.m_dx = 0;
            break;

        case Qt::Key_Up:
        case Qt::Key_W:
            game.m_rotate = false;
            break;

        case Qt::Key_Down:
        case Qt::Key_S:
            game.m_delay = Game::SPEED;
        default:
            break;
        }
    }
    QGraphicsScene::keyReleaseEvent(event);
}

void Scene::update()
{
    game.m_timer += (timePerFrame);
    qDebug() << "timer " << game.m_timer;
    clear();
    //m_background = new QGraphicsPixmapItem(game.m_background);
    //addItem(m_background);
    QGraphicsPixmapItem* bg1 = new QGraphicsPixmapItem(QPixmap(":/images/background1.png"));
    bg1->moveBy(28, 31);
    addItem(bg1);

    //// <- Move -> ///
    for (int i= 0;i<4;i++)
    {
        game.m_b[i]= game.m_a[i];
        game.m_a[i].x += game.m_dx;
    }

    if (!game.check())
    {
        for (int i=0;i<4;i++)
        {
            game.m_a[i] = game.m_b[i];
        }
    }

    //////Rotate//////
    if (game.m_rotate)
    {
        Point p = game.m_a[1]; //center of rotation
        for (int i=0;i<4;i++)
        {
            int x = game.m_a[i].y-p.y;
            int y = game.m_a[i].x-p.x;
            game.m_a[i].x = p.x - x;
            game.m_a[i].y = p.y + y;
        }
        if (!game.check())
        {
            for (int i=0;i<4;i++)
            {
                game.m_a[i] = game.m_b[i];
            }
        }
        game.m_rotate = false;
    }

    ///////Tick//////
    if ( game.m_timer > game.m_delay)
    {
        for (int i=0;i<4;i++)
        {
            game.m_b[i] = game.m_a[i];
            game.m_a[i].y+=1;
        }

        if (!game.check())
        {
            for (int i=0;i<4;i++)
            {
                //qDebug() << "game.m_b[i].y " << game.m_b[i].y << " game.m_b[i].x " << game.m_b[i].x;
                game.m_field[game.m_b[i].y][game.m_b[i].x] = game.m_colorNum;
            }

            game.m_colorNum = 1+rand()%7;
            int n=rand()%7;
            for (int i=0;i<4;i++)
            {
                game.m_a[i].x = game.m_figures[n][i] % 2;
                game.m_a[i].y = game.m_figures[n][i] / 2;
            }
        }

        game.m_timer=0;
    }
    ///////check lines//////////
    int k=game.M-1;
    for (int i=game.M-1;i>0;i--)
    {
        int count=0;
        for (int j=0;j<game.N;j++)
        {
            if (game.m_field[i][j]) count++;
            game.m_field[k][j]= game.m_field[i][j];
        }
        if (count<game.N) k--;
    }

    game.m_dx=0; game.m_rotate=false; //game.m_delay = Game::SPEED;

    //draw
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
        QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(game.m_tile.copy(game.m_colorNum * 18, 0, 18, 18));
        addItem(pixmapItem);
        pixmapItem->setPos(game.m_a[i].x * 18, game.m_a[i].y * 18);
        pixmapItem->moveBy(28, 31);
    }
}
