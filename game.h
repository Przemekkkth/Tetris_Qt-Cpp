#ifndef GAME_H
#define GAME_H
#include "point.h"
#include <QPixmap>

class Game
{
public:
    Game();

    const int BOARD_HEIGHT;
    const int BOARD_WIDTH;

    static const float SPEED;
    static const float SPEED_UP;
    static const int COUNT_OF_COLORS;
    static const int COUNT_OF_FIGURES;
    static const int COUNT_OF_BLOCKS;
    static QSize BLOCK_SIZE;
    static QSize RESOLUTION;

    int m_field[20][10];

    Point m_a[4], m_b[4];

    int m_figures[7][4];

    bool check();

    int m_dx;
    bool m_rotate;
    int m_colorNum;;
    float m_timer,m_delay;

    QPixmap m_tile;
    QPixmap m_background;
    QPixmap m_frame;
    QPixmap m_pauseBackground;
    QPixmap m_scorePixmap;
    QPixmap m_numbersPixmap;
    QPixmap m_gameOverBackground;
    QPixmap m_restartTextPixmap;

    enum class State{
        Active, Paused, Game_Over
    };

    State m_state;

    int m_score;
    void addScore(int val);

    bool m_gameOver;

    void reset();
};

#endif // GAME_H
