#ifndef SETTINGSSCENE_H
#define SETTINGSSCENE_H

#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>

class SettingsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit SettingsScene(QObject *parent = nullptr);

signals:
    void goToMenuActivated();
private:
    QPixmap m_rotatePixmap;
    QPixmap m_rightPixmap;
    QPixmap m_leftPixmap;
    QPixmap m_speedupPixmap;
    QPixmap m_pausePixmap;
    QPixmap m_backspacePixmap;
    QPixmap m_backTextPixmap;

    QGraphicsPixmapItem* m_rotateItem;
    QGraphicsPixmapItem* m_rightItem;
    QGraphicsPixmapItem* m_leftItem;
    QGraphicsPixmapItem* m_speedupItem;
    QGraphicsPixmapItem* m_pauseItem;
    QGraphicsPixmapItem* m_backspaceItem;
    QGraphicsPixmapItem* m_backTextItem;

    void loadPixmaps();
    void createItemPos();

    // QGraphicsScene interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // SETTINGSSCENE_H
