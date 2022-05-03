#include "game.h"
#include <QDebug>
#include <cstdlib>

const float Game::ONE_SECOND = 1000.0f;//in milisecond
const float Game::HALF_SECOND = 500.0f;

Game::Game()
    : M(20), N(10), m_dx(0), m_rotate(false), m_colorNum(1), m_timer(0), m_delay(ONE_SECOND)
{
    for(int i = 0; i < M; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            m_field[i][j] = 0;
        }
    }
    //set zero for points
    for(int i = 0; i < 4; ++i)
    {
        m_a[i].x = 0;
        m_a[i].y = 0;
        m_b[i].x = 0;
        m_b[i].y = 0;
    }

    //I
    m_figures[0][0] = 1;
    m_figures[0][1] = 3;
    m_figures[0][2] = 5;
    m_figures[0][3] = 7;

    //Z
    m_figures[1][0] = 2;
    m_figures[1][1] = 4;
    m_figures[1][2] = 5;
    m_figures[1][3] = 7;

    //S
    m_figures[2][0] = 3;
    m_figures[2][1] = 5;
    m_figures[2][2] = 4;
    m_figures[2][3] = 6;

    //T
    m_figures[3][0] = 3;
    m_figures[3][1] = 5;
    m_figures[3][2] = 4;
    m_figures[3][3] = 7;

    //L
    m_figures[4][0] = 2;
    m_figures[4][1] = 3;
    m_figures[4][2] = 5;
    m_figures[4][3] = 7;

    //J
    m_figures[5][0] = 3;
    m_figures[5][1] = 5;
    m_figures[5][2] = 7;
    m_figures[5][3] = 6;


    //O
    m_figures[6][0] = 2;
    m_figures[6][1] = 3;
    m_figures[6][2] = 4;
    m_figures[6][3] = 5;

    //load textures
    if( !m_background.load(":/images/background.png") )
    {
        qDebug() << "Failed to load: " << ":/images/background.png";
    }
    if( !m_frame.load(":/images/frame.png") )
    {
        qDebug() << "Failed to load: " << ":/images/frame.png";
    }
    if( !m_tile.load(":/images/tiles.png") )
    {
        qDebug() << "Failed to load: " << ":/images/tiles.png";
    }
}

bool Game::check()
{
    for (int i=0;i<4;i++)
    {
        if (m_a[i].x<0 || m_a[i].x>=N || m_a[i].y>=M)
        {
            return false;
        }
        else if (m_field[m_a[i].y][m_a[i].x])
        {
            return false;
        }
    }

    return true;
}
