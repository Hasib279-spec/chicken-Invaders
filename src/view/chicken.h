#ifndef CHICKEN_INVADERS_CHICKEN_H
#define CHICKEN_INVADERS_CHICKEN_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QList>

class Chicken : public QObject, public QGraphicsPixmapItem {
Q_OBJECT

private:
    int frame;
    QList<QPixmap*> frames;
    QTimer* animationTimer;
    QTimer* moveTimer;

public:
    Chicken(int x, int y, QGraphicsItem *parent = nullptr);
    void stopTimers();

signals:
    void hitPlayer();
    void destroyed();

public slots:
    void animate();
    void move();
};

#endif // CHICKEN_INVADERS_CHICKEN_H