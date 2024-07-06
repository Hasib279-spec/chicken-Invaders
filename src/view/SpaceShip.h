#ifndef CHICKEN_INVADERS_SPACESHIP_H
#define CHICKEN_INVADERS_SPACESHIP_H

#include <QPropertyAnimation>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QKeyEvent>
#include <QGraphicsRectItem>

class SpaceShip : public QObject, public QGraphicsPixmapItem {
Q_OBJECT

public:
    SpaceShip(int sceneWidth, int sceneHeight, QGraphicsItem *parent = nullptr);
    void keyPressEvent(QKeyEvent *event) override;
    void shoot();

signals:
    void hit();

};

#endif //CHICKEN_INVADERS_SPACESHIP_H