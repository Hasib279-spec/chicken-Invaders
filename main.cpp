#include <QApplication>
#include "src/Game.h"

Game *game; // Global object

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    game = new Game();
    game->show();

    return QApplication::exec();
}