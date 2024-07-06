#ifndef CHICKEN_INVADERS_SCORE_H
#define CHICKEN_INVADERS_SCORE_H

#include <QGraphicsTextItem>

class Score : public QGraphicsTextItem {
public:
    Score(QGraphicsItem *parent = nullptr);
    void increase();
    int getScore();
private:
    int score;
};

#endif //CHICKEN_INVADERS_SCORE_H