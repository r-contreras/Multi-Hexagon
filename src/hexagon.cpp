#include "hexagon.h"

/**
 * @brief Construct a new hexagon::hexagon object
 * 
 * @param argc 
 * @param argv 
 */
hexagon::hexagon(int& argc, char *argv[])
    :QApplication(argc, argv)
{
    //Icnono de la aplicacion:
    setWindowIcon(QIcon(":/hexaIcon.jpg"));

}

/**
 * @brief Destroy the hexagon::hexagon object
 * 
 */
hexagon::~hexagon(){}

/**
 * @brief Runs the app. Shows the main window and waits for user's action.
 * 
 * @return int that actually is the result of this->exce()
 */
int hexagon::run(){
    this->mainWindow.show();
    return this->exec();
}
