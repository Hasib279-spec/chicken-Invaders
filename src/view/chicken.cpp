#include "Chicken.h"
#include <QPixmap>
#include <QGraphicsScene>
#include "SpaceShip.h"

Chicken::Chicken(int x, int y, QGraphicsItem *parent) : QGraphicsPixmapItem(parent), frame(0) {
    QPixmap* pixmap1 = new QPixmap(":/images/chicken1");
    QPixmap* scaledPixmap1 = new QPixmap(pixmap1->scaled(80, 70));
    frames.append(scaledPixmap1);

    QPixmap* pixmap2 = new QPixmap(":/images/chicken2");
    QPixmap* scaledPixmap2 = new QPixmap(pixmap2->scaled(80, 70));
    frames.append(scaledPixmap2);

    setPixmap(*frames[0]);

    setPos(x, y);

    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &Chicken::animate);
    animationTimer->start(80); // Change frames every 100 ms

    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Chicken::move);
    moveTimer->start(100); // Move every 100 ms
}

void Chicken::animate() {
    frame = (frame + 1) % 2;
    setPixmap(*frames[frame]);
}

void Chicken::move() {
    int newY = y() + 3; // Move down by 3 pixels
    setPos(x(), newY);

    // Check for collision with player (spaceship)
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (QGraphicsItem *item : colliding_items) {
        if (typeid(*item) == typeid(SpaceShip)) {
            emit hitPlayer();
            scene()->removeItem(this);
            emit destroyed();
            delete this;
            return;
        }
    }
}

void Chicken::stopTimers() {
    if (animationTimer) {
        animationTimer->stop();
    }
    if (moveTimer) {
        moveTimer->stop();
    }
}