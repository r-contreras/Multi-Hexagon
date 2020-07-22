#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsLineItem>
#include "player.h"
#include "centercircle.h"
#include "game.h"

int main(int argc, char* argv[])
{
    QApplication main(argc, argv);

    QGraphicsScene* scene = new QGraphicsScene();

    //Agregar el centro
    CenterCircle* center = new CenterCircle();
    scene->addItem(center);
    //TODO : POR QUE SE MUEVE???



    //Visualizar la escena
    QGraphicsView* view = new QGraphicsView(scene);

    //Mostrar la escena
    view->show();

    //Hacer la ventana de un tamanho fijo
    view->setFixedSize(600,600);
    scene->setSceneRect(0,0,600,600);

    //Eliminar las scroll bars
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    /*
    //Pintar las lineas del centro
    QGraphicsLineItem* vertical = new QGraphicsLineItem(view->width()/2,0,view->width()/2,view->height());
    QGraphicsLineItem* horizontal = new QGraphicsLineItem(0,view->height()/2,view->width(),view->height()/2);
    scene->addItem(vertical);
    scene->addItem(horizontal);
    */

    //Cambiar las posiciones del centro
    center->setPos(view->width()/2 - center->rect().width()*1.1, view->height()/2 - center->rect().height()*1.1);

    //////////////////////////////////////////////////////////////////
    //Crear al jugador
    int playerRadius = 10;
    Player* player = new Player(view->width()/2 - playerRadius/2, view->height()/2 - playerRadius/2);

    //Hacer el jugador focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    //Agregarlo a la escena
    scene->addItem(player);
    /////////////////////////////////////////////////////////////////

    //Crear el Game para agregar enemigos a la escena
    Game* game = new Game();
    scene->addItem(game);

    /*
    //Anhadir un enemigo que se va cerrando
    Enemy* enemy = new Enemy();
    scene->addItem(enemy);

    */

    return main.exec();
}
