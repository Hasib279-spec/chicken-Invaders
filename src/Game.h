#ifndef CHICKEN_INVADERS_GAME_H
#define CHICKEN_INVADERS_GAME_H

#include <QGraphicsView>
#include "view/Score.h"
#include "view/Health.h"
#include <QTimer>

class Game : public QGraphicsView {
Q_OBJECT
public:
    Game();

public slots:
    void handlePlayerHit();
    void chickenDestroyed();

private:
    void startStage1();
    void startStage2();
    void createChickens(int rows, int cols, int xOffset, int yOffset);
    void clearChickens();
    void displayWinMessage();

    int currentStage;
    int chickensRemaining;
    QTimer *stageTimer;

public:
    Score* score;
    Health* health;
};

#endif // CHICKEN_INVADERS_GAME_H