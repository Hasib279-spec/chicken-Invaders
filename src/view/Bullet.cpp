#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "Chicken.h"
#include "../Game.h"
#include <QAudioOutput>


extern Game *game; // External global object

Bullet::Bullet(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent) {
    QPixmap pixmap(":/images/Bullet");
    setPixmap(pixmap);
    setScale(0.3);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Bullet::move);
    timer->start(15); // Move the bullet
}

void Bullet::move() {
    setPos(x(), y() - 10);

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (QGraphicsItem *item : colliding_items) {
        if (typeid(*item) == typeid(Chicken)) {
            game->score->increase();
            emit static_cast<Chicken*>(item)->destroyed(); // Notify the game about the destruction

            scene()->removeItem(item);
            scene()->removeItem(this);
            delete item;
            delete this;
            return;
        }
    }

    if (pos().y() + pixmap().height() < 0) {
        scene()->removeItem(this);
        delete this;
    }
}