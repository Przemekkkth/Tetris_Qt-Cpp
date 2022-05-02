#ifndef GAME_H
#define GAME_H
#include "point.h"
#include <QPixmap>

class Game
{
public:
    Game();

    const int M;
    const int N;

    int m_field[20][10];

    Point m_a[4], b_[4];

    int m_figures[7][4];

    bool check();

    int m_dx;
    bool m_rotate;
    int m_colorNum;;
    float m_timer,m_delay;

    QPixmap m_tile;
    QPixmap m_background;
    QPixmap m_frame;
};

#endif // GAME_H
