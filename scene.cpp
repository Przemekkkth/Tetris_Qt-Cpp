#include "scene.h"
#include <QKeyEvent>
#include <QDebug>

Scene::Scene(QObject *parent) : QGraphicsScene(parent), game(), timePerFrame(1000.0f/60.0f)
{
    setSceneRect(0,0, Game::RESOLUTION.width(), Game::RESOLUTION.height() );
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
        //qDebug() << "Pressed key: " << event->key();
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
        case Qt::Key_P:
            if(game.m_state == Game::State::Active)
            {
                game.m_state = Game::State::Paused;
            }
            else if( game.m_state == Game::State::Paused )
            {
                game.m_state = Game::State::Active;
            }
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
        //qDebug() << "Released key: " << event->key();
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
    if(game.m_state == Game::State::Active)
    {
       game.m_timer += (timePerFrame);
    }
    clear();

    m_background = new QGraphicsPixmapItem(game.m_background.scaled(sceneRect().width(), sceneRect().height()));
    addItem(m_background);

    m_frame = new QGraphicsPixmapItem(game.m_frame);
    addItem(m_frame);
    m_frame->moveBy(28, 31);

    //// <- Move -> ///
    for (int i = 0; i < Game::COUNT_OF_BLOCKS ;i++)
    {
        game.m_b[i]= game.m_a[i];
        game.m_a[i].x += game.m_dx;
    }

    if (!game.check())
    {
        for (int i = 0; i < Game::COUNT_OF_BLOCKS; i++)
        {
            game.m_a[i] = game.m_b[i];
        }
    }

    //////Rotate//////
    if (game.m_rotate)
    {
        Point p = game.m_a[1]; //center of rotation
        for (int i = 0; i < Game::COUNT_OF_BLOCKS; i++)
        {
            int x = game.m_a[i].y-p.y;
            int y = game.m_a[i].x-p.x;
            game.m_a[i].x = p.x - x;
            game.m_a[i].y = p.y + y;
        }
        if (!game.check())
        {
            for (int i = 0; i < Game::COUNT_OF_BLOCKS; i++)
            {
                game.m_a[i] = game.m_b[i];
            }
        }
        game.m_rotate = false;
    }

    ///////Tick//////
    if ( game.m_timer > game.m_delay)
    {
        for (int i = 0; i < Game::COUNT_OF_BLOCKS; i++)
        {
            game.m_b[i] = game.m_a[i];
            game.m_a[i].y+=1;
        }

        if (!game.check())
        {
            for (int i = 0; i < Game::COUNT_OF_BLOCKS; i++)
            {
                //qDebug() << "game.m_b[i].y " << game.m_b[i].y << " game.m_b[i].x " << game.m_b[i].x;
                game.m_field[game.m_b[i].y][game.m_b[i].x] = game.m_colorNum;
            }

            game.m_colorNum = (rand() % (Game::COUNT_OF_COLORS - 1)) + 1;
            int n= rand() % Game::COUNT_OF_FIGURES;
            for (int i = 0; i < Game::COUNT_OF_BLOCKS; i++)
            {
                game.m_a[i].x = (game.m_figures[n][i] % 2) + game.BOARD_WIDTH/2-1;
                game.m_a[i].y = game.m_figures[n][i] / 2;
            }
        }

        game.m_timer=0;
    }
    ///////check lines//////////
    int k=game.BOARD_HEIGHT-1;
    for (int i= game.BOARD_HEIGHT-1; i > 0; i--)
    {
        int count = 0;
        for (int j = 0; j < game.BOARD_WIDTH;j++)
        {
            if (game.m_field[i][j]) count++;
            game.m_field[k][j]= game.m_field[i][j];
        }
        if (count<game.BOARD_WIDTH) k--;
    }

    game.m_dx=0; game.m_rotate=false; //game.m_delay = Game::SPEED;

    //draw
    for (int i=0;i<game.BOARD_HEIGHT;i++)
    {
        for (int j=0;j<game.BOARD_WIDTH;j++)
        {
            if (game.m_field[i][j]==0) continue;
            QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(game.m_tile.copy(game.m_field[i][j]*18, 0, 18, 18));
            addItem(pixmapItem);
            pixmapItem->setPos(j * Game::BLOCK_SIZE.width(), i * Game::BLOCK_SIZE.height());
            pixmapItem->moveBy(m_frame->pos().x(), m_frame->pos().y());
        }

    }

    for (int i = 0; i < Game::COUNT_OF_BLOCKS; i++)
    {
        QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(game.m_tile.copy(game.m_colorNum * 18, 0, 18, 18));
        addItem(pixmapItem);
        pixmapItem->setPos(game.m_a[i].x * Game::BLOCK_SIZE.width(), game.m_a[i].y * Game::BLOCK_SIZE.height());
        pixmapItem->moveBy(m_frame->pos().x(), m_frame->pos().y());
    }

    if(game.m_state == Game::State::Paused)
    {
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(game.m_pauseBackground);
        addItem(item);
    }
}
