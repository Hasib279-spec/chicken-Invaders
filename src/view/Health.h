#ifndef CHICKEN_INVADERS_HEALTH_H
#define CHICKEN_INVADERS_HEALTH_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QList>

class Health : public QObject {
Q_OBJECT
public:
    Health(QGraphicsScene *scene, QObject *parent = nullptr);
    void decrease();
    int getHealth() const;
    QGraphicsPixmapItem* getHeart(int index) const;

private:
    int health;
    QList<QGraphicsPixmapItem*> hearts;
    QGraphicsScene *scene;
};

#endif // CHICKEN_INVADERS_HEALTH_H