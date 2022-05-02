#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QGraphicsScene>
#include "game.h"
#include <QGraphicsPixmapItem>
#include <QTimer>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Scene(QObject* parent = nullptr);
private:
    Game game;
    QGraphicsPixmapItem* m_background, *m_tiles, *m_frame;

    const float timePerFrame;
    QTimer *timer;
    // QGraphicsScene interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
private slots:
    void update();

};

#endif // SCENE_H
