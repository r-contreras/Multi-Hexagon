#include <QApplication>
#include "game.h"

int main(int argc, char* argv[])
{
    QApplication mainApp(argc, argv);
    Game* game = new Game();
    game->run();

    return mainApp.exec();
}
