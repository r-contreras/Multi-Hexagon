#include "hexagon.h"

hexagon::hexagon(int& argc, char *argv[])
    :QApplication(argc, argv)
{
    //Icnono de la aplicacion:
    setWindowIcon(QIcon(":/hexaIcon.jpg"));

}

hexagon::~hexagon(){}

int hexagon::run(){
    this->mainWindow.show();
    return this->exec();
}
