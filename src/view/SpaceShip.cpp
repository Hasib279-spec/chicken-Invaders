#include "SpaceShip.h"
#include "Bullet.h"
#include <QGraphicsScene>

SpaceShip::SpaceShip(int sceneWidth, int sceneHeight, QGraphicsItem *parent)
        : QGraphicsPixmapItem(parent)
{
    QPixmap pixmap(":/images/ship");
    setPixmap(pixmap);

    setScale(0.8);

    // Adjust the initial position
    int initialY = sceneHeight - pixmap.height() - 5; // Adjust 5 as needed
    setPos(+sceneWidth / 2 - pixmap.width() / 2, initialY);
}

void SpaceShip::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left)
    {
        if (pos().x() > 0)
        {
            setPos(x() - 10, y());
        }
    }
    else if (event->key() == Qt::Key_Right)
    {
        if (pos().x() + pixmap().width() < scene()->width())
        {
            setPos(x() + 10, y());
        }
    }
    else if (event->key() == Qt::Key_Space)
    {
        shoot();
    }
}

void SpaceShip::shoot()
{
    // Create a bullet
    Bullet *bullet = new Bullet();
    bullet->setPos(x() + pixmap().width() / 2 - bullet->pixmap().width() / 2, y());
    scene()->addItem(bullet);
}