#include "game.h"
Game::Game()
    : scene(nullptr)
    , center(nullptr), player(nullptr)
    , spawnTimer(nullptr), scoreTimer(nullptr), musicTimer(nullptr)
    , backgroundMusic(nullptr)
    , playerLost(false)
    , playerRadius(10), playerScore(0), spawnrate(1000)
{}

Game::~Game()
{
    delete scene;
    delete center;
    delete player;
    delete spawnTimer;
    delete scoreTimer;
    delete musicTimer;
    delete backgroundMusic;
}

void Game::run()
{
    //Se inicia la escena
    initScene();
    //Se inicia el score (font,size,width)
    initScore();
    //Se inicia la musica de fondo
    initBackgroundMusicPlayer();
    //Se inician los timers
    initTimers();
}

void Game::initScene()
{
    scene = new QGraphicsScene();
    setScene(scene);

    //Hacer la ventana de un tamanho fijo
    this->setFixedSize(600,600);
    scene->setSceneRect(0,0,600,600);

    //Eliminar las scroll bars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    /*
    //Pintar las lineas del centro
    QGraphicsLineItem* vertical = new QGraphicsLineItem(width()/2,0,width()/2,height());
    QGraphicsLineItem* horizontal = new QGraphicsLineItem(0,height()/2,width(),height()/2);
    scene->addItem(vertical);
    scene->addItem(horizontal);
    */

    //Anhadir los principales actores (centro y jugador)
    addActors();

    //Mostrar el view
    show();

}

void Game::addActors()
{
    //Crear/ubicar el centro
    center = new CenterCircle();
    center->setPos(width()/2 - center->rect().width()*1.1, height()/2 - center->rect().height()*1.1);
    scene->addItem(center);

    //Crear/ubicar el jugador
    player = new Player(width()/2 - playerRadius/2, height()/2 - playerRadius/2);
    scene->addItem(player);

    //Crear/ubicar el score
    scoreTextBox = new QGraphicsTextItem();
    scene->addItem(scoreTextBox);

    //Hacer el jugador focusable (para que reaccione a los key press)
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
}

void Game::initTimers()
{
    //Se crea un timer para actualizar el score
    scoreTimer = new QTimer();

    //Se crea un timer para generar enemigos
    spawnTimer = new QTimer();

    //Se crea un timer para la musica de fondo
    musicTimer = new QTimer();

    //Se asgina a los timers sus intervalos de actualizacion
    scoreTimer->start(25); //Cada 25ms
    spawnTimer->start(spawnrate); //Dado en ms.
    musicTimer->start(219000); //Cada vez que se acaba la musica, se vuelve a poner (loop)


    //Se conectan los timers a sus subrutinas respectivas
    QObject::connect(spawnTimer, &QTimer::timeout, this, &Game::spawnEnemy);
    QObject::connect(scoreTimer, &QTimer::timeout, this, &Game::printScore);
    QObject::connect(musicTimer, &QTimer::timeout, this, &Game::playBackgroundMusic);
}

void Game::initScore()
{
    //Se establece el font y color del score
    scoreTextBox->setDefaultTextColor(Qt::magenta);
    scoreTextBox->QGraphicsTextItem::setFont(QFont("Helvetica",16));
    scoreTextBox->setTextWidth(200);
}

void Game::initBackgroundMusicPlayer()
{
    backgroundMusic = new QMediaPlayer();
    backgroundMusic->setMedia(QUrl("qrc:music/New World.mp3"));
    //Play (Loop con su timer)
    playBackgroundMusic();
}

void Game::playBackgroundMusic()
{
    backgroundMusic->play();
}

void Game::spawnEnemy()
{
    float angle = rand() % 360*16;
    Enemy* newEnemy = new Enemy(angle, playerScore, playerLost);
    scene->addItem(newEnemy);
}

void Game::printScore()
{
    scoreTextBox->setPlainText("Score : " + QString::number(playerScore)); //Se inicia en 0
    scoreTextBox->setPos(scene->width()/2 - (scoreTextBox->textWidth()/3), scene->height()/8);
}
