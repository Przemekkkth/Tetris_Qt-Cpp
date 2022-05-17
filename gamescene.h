#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QObject>
#include <QGraphicsScene>
#include "game.h"
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QElapsedTimer>

class QSoundEffect;
class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GameScene(QObject* parent = nullptr);
    void start();
    void stop();
    void setMuted(bool val);
private:
    Game game;
    QGraphicsPixmapItem* m_background, *m_tiles, *m_frame;

    const float timePerFrame;
    QTimer *timer;

    QSoundEffect* m_hitSFX;
    bool m_isMuted;
    // QGraphicsScene interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
private slots:
    void update();
signals:
    void goToMenuActivated();
};

#endif // GAMESCENE_H
