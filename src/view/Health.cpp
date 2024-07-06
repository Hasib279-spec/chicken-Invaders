#include "Health.h"
#include <QGraphicsScene>
#include <QPixmap>

Health::Health(QGraphicsScene *scene, QObject *parent) : QObject(parent), health(3), scene(scene) {
    // Initialize heart pixmaps
    QPixmap heartPixmap(":/images/Heart1");
    QPixmap scaledHeartPixmap = heartPixmap.scaled(40, 50); // Scale the heart to the desired size

    for (int i = 0; i < 3; ++i) {
        QGraphicsPixmapItem *heart = new QGraphicsPixmapItem(scaledHeartPixmap);
        heart->setPos(i * 40, scene->height() - 50); // Position hearts in bottom left corner, adjust spacing
        hearts.append(heart);
        scene->addItem(heart); // Add heart to the scene
    }
}

void Health::decrease() {
    if (health > 0) {
        --health;
        QGraphicsPixmapItem* heart = hearts.takeLast();
        scene->removeItem(heart);
        delete heart;
    }
}

int Health::getHealth() const {
    return health;
}

QGraphicsPixmapItem* Health::getHeart(int index) const {
    if (index >= 0 && index < hearts.size()) {
        return hearts[index];
    }
    return nullptr;
}