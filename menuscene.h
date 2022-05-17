#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

class MenuScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MenuScene(QObject *parent = nullptr);

signals:
    void startClicked();
    void optionsClicked();
    void quitClicked();
private:
    QPixmap m_startTextPixmap;
    QPixmap m_optionsTextPixmap;
    QPixmap m_quitTextPixmap;
    void loadPixmaps();

    QGraphicsPixmapItem* m_startItem;
    QGraphicsPixmapItem* m_optionsItem;
    QGraphicsPixmapItem* m_quitItem;
    void createItemPos();
    void renderScene();

    // QGraphicsScene interface
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // MENUSCENE_H
