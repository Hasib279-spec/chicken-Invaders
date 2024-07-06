#include "Game.h"
#include "view/Chicken.h"
#include "view/SpaceShip.h"
#include "view/Score.h"
#include "view/Health.h"
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QTimer>

Game::Game() : currentStage(0), chickensRemaining(0) {
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    showFullScreen();

    auto *scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, width(), height());

    scene->setBackgroundBrush(QBrush(QImage(":/images/LevelOneBack")));

    int sceneWidth = scene->sceneRect().width();
    int sceneHeight = scene->sceneRect().height();

    SpaceShip *spaceShip = new SpaceShip(sceneWidth, sceneHeight);
    scene->addItem(spaceShip);
    spaceShip->setFlag(QGraphicsItem::ItemIsFocusable);
    spaceShip->setFocus();

    // Add score and health
    score = new Score();
    scene->addItem(score);

    health = new Health(scene);
    for (int i = 0; i < 3; ++i) {
        QGraphicsPixmapItem *heart = health->getHeart(i);
        if (heart) {
            scene->addItem(heart);
        }
    }

    setScene(scene);

    // Start the first stage after 4 seconds
    stageTimer = new QTimer(this);
    connect(stageTimer, &QTimer::timeout, this, &Game::startStage1);
    stageTimer->start(4000);
}

void Game::startStage1() {
    stageTimer->stop();
    clearChickens();
    createChickens(4, 5, 80, 100);
    currentStage = 1;
    chickensRemaining = 20;
}

void Game::startStage2() {
    stageTimer->stop();
    clearChickens();
    createChickens(4, 9, 50, 100);
    currentStage = 2;
    chickensRemaining = 36;
}

void Game::createChickens(int rows, int cols, int xOffset, int yOffset) {
    int chickenWidth = 90;
    int chickenHeight = 80;

    int sceneWidth = scene()->width();
    int totalWidth = cols * (chickenWidth + xOffset) - xOffset;
    int startX = (sceneWidth - totalWidth) / 2;

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int x = startX + col * (chickenWidth + xOffset);
            int y = -chickenHeight - row * yOffset; // Start above the screen and stagger them
            Chicken *chicken = new Chicken(x, y);
            connect(chicken, &Chicken::hitPlayer, this, &Game::handlePlayerHit);
            connect(chicken, &Chicken::destroyed, this, &Game::chickenDestroyed);
            scene()->addItem(chicken);
        }
    }
}

void Game::clearChickens() {
    QList<QGraphicsItem *> items = scene()->items();
    for (QGraphicsItem *item : items) {
        Chicken *chicken = dynamic_cast<Chicken *>(item);
        if (chicken) {
            scene()->removeItem(chicken);
            delete chicken;
        }
    }
}

        void Game::handlePlayerHit() {
            health->decrease();
            if (health->getHealth() == 0) {
                QList<QGraphicsItem *> items =scene()->items();
                for (QGraphicsItem *item : items){
                    SpaceShip *spaceShip = dynamic_cast<SpaceShip *> (item);
                    if(spaceShip){
                        QGraphicsPixmapItem *explosion = new QGraphicsPixmapItem(QPixmap(":/images/explosion"));

                        explosion->setPos(spaceShip->pos());
                        explosion->setScale(2);
                        scene()->addItem(explosion);
                        scene()->removeItem(spaceShip);
                        delete spaceShip;
                    }
                }
                //stop all chicken timers
                for(QGraphicsItem * item :items){
                    Chicken *chicken= dynamic_cast<Chicken * >(item);
                    if(chicken){
                        chicken->stopTimers();
                    }
                }



        // Display game over
        QGraphicsTextItem *gameOverText = new QGraphicsTextItem("GAME OVER");
        gameOverText->setDefaultTextColor(Qt::red);
        gameOverText->setFont(QFont("times", 50));
        gameOverText->setPos(scene()->width() / 2 - gameOverText->boundingRect().width() / 2, scene()->height() / 2 - gameOverText->boundingRect().height() / 2);
        scene()->addItem(gameOverText);

        // Disable any further input or actions
        for (QGraphicsItem *item : items) {
            if (dynamic_cast<SpaceShip *>(item)) {
                item->setEnabled(false);
            }
        }
    }
}

void Game::chickenDestroyed() {
    chickensRemaining--;
    if (chickensRemaining == 0) {
        if (currentStage == 1) {
            stageTimer->start(2000);  // Adding a brief delay before starting the next stage
            connect(stageTimer, &QTimer::timeout, this, &Game::startStage2);
        } else if (currentStage == 2) {
            displayWinMessage();
        }
    }
}

void Game::displayWinMessage() {
    // Display win message
    QGraphicsTextItem *winText = new QGraphicsTextItem("YOU WIN!");
    winText->setDefaultTextColor(Qt::green);
    winText->setFont(QFont("times", 50));
    winText->setPos(scene()->width() / 2 - winText->boundingRect().width() / 2, scene()->height() / 2 - winText->boundingRect().height() / 2);
    scene()->addItem(winText);

    // Stop all chicken timers and disable any further input or actions
    QList<QGraphicsItem *> items = scene()->items();
    for (QGraphicsItem *item : items) {
        Chicken *chicken = dynamic_cast<Chicken *>(item);
        if (chicken) {
            chicken->stopTimers();
        }
        if (dynamic_cast<SpaceShip *>(item)) {
            item->setEnabled(false);
        }
    }
}
