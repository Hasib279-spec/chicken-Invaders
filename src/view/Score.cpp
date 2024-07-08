#include "Score.h"
#include <QFont>

Score::Score(QGraphicsItem *parent) : QGraphicsTextItem(parent) {

    score = 0;

    // Draw the text
    setPlainText(QString("SCORE: ") + QString::number(score));
    setDefaultTextColor(Qt::black);
    setFont(QFont("times", 30));
}

void Score::increase() {
    score += 5; // Each chicken gives 5 points
    setPlainText(QString("SCORE: ") + QString::number(score)); // Update the text
    setDefaultTextColor(Qt::green);


}

int Score::getScore() {
    return score;
}