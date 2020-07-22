#include "game.h"
#include <QDebug>
Game::Game()
    : scene(nullptr)
    , center(nullptr), player(nullptr)
    , spawnTimer(nullptr), scoreTimer(nullptr), enemiesRandomnessUpdater(nullptr), musicTimer(nullptr)
    , backgroundMusic(nullptr)
{}

Game::~Game()
{
    delete scene;
    delete center;
    delete player;
    delete spawnTimer;
    delete scoreTimer;
    delete enemiesRandomnessUpdater;
    delete musicTimer;
    delete backgroundMusic;
}

void Game::run()
{
    //Initialize scene
    initScene();
    //initialize score text box (font,size,width)
    initScore();
    //Initialize background music
    initBackgroundMusicPlayer();
    //Initialize timers
    initTimers();
}

void Game::initScene()
{
    scene = new QGraphicsScene();
    setScene(scene);

    //Set a fixed size for both the scene and viewer
    this->setFixedSize(screenWidth,screenHeight);
    scene->setSceneRect(0,0,screenWidth,screenHeight);

    //Eliminate scroll bars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    /*
    //Pintar las lineas del centro
    QGraphicsLineItem* vertical = new QGraphicsLineItem(width()/2,0,width()/2,height());
    QGraphicsLineItem* horizontal = new QGraphicsLineItem(0,height()/2,width(),height()/2);
    scene->addItem(vertical);
    scene->addItem(horizontal);
    */

    //Add main actors (center circle and player)
    addActors();

    //Show scene view
    show();

}

void Game::addActors()
{
    //Create/locate center circle
    center = new CenterCircle();
    center->setPos(width()/2 - center->rect().width()*1.1, height()/2 - center->rect().height()*1.1);
    scene->addItem(center);

    //Create/locate player
    player = new Player(width()/2 - playerRadius/2, height()/2 - playerRadius/2);
    scene->addItem(player);

    //Create/locate score text box
    scoreTextBox = new QGraphicsTextItem();
    scene->addItem(scoreTextBox);

    //Make player focusable (react to key presses)
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
}

void Game::initTimers()
{
    //Create a timer to update score
    scoreTimer = new QTimer();

    //Create a timer for spawn
    spawnTimer = new QTimer();

    //Start closing speed variation
    enemiesRandomnessUpdater = new QTimer();

    //Since it will be called after 10 seconds, we create a random closing speed at run.
    enemiesClosingSpeed = (rand() % 10) + 4;

    //Create a timer for background music
    musicTimer = new QTimer();

    //Assign updating intervals
    scoreTimer->start(10); //Every 10ms
    spawnTimer->start(spawnrate); //In milisenconds.
    enemiesRandomnessUpdater->start(10000); //Every 10 seconds
    musicTimer->start(219000); //Loop music



    //Connect every timer to their respective update methods
    QObject::connect(spawnTimer, &QTimer::timeout, this, &Game::spawnEnemy);
    QObject::connect(scoreTimer, &QTimer::timeout, this, &Game::updateScore);
    QObject::connect(enemiesRandomnessUpdater, &QTimer::timeout, this, &Game::updateEnemiesRandomness);
    QObject::connect(musicTimer, &QTimer::timeout, this, &Game::playBackgroundMusic);
}

void Game::updateEnemiesRandomness()
{
    enemiesClosingSpeed = (rand() % 10) + 4;
    spawnTimer->start( (rand() % 500)+ 500);
}

void Game::initScore()
{
    //Se establece el font y color del score
    scoreTextBox->setDefaultTextColor(QColor(245,185,103));
    QFont font("Helvetica",16);
    font.setCapitalization(QFont::AllUppercase);
    scoreTextBox->setFont(font);
    scoreTextBox->setTextWidth(200);
}

void Game::initBackgroundMusicPlayer()
{
    backgroundMusic = new QMediaPlayer();
    backgroundMusic->setMedia(QUrl("qrc:music/New World.mp3"));

    //Play music(Loop with its timer)
    playBackgroundMusic();
}

void Game::playBackgroundMusic()
{
    backgroundMusic->play();
}

void Game::spawnEnemy()
{
    float angle = rand() % 360*16; //random aperture angle (not aperture size, but where it will be)

    Enemy* newEnemy = new Enemy(enemiesClosingSpeed, screenWidth, screenHeight, angle, playerScore, playerLost);
    scene->addItem(newEnemy);
}

void Game::updateScore()
{
    scoreTextBox->setPlainText("Score : " + QString::number(playerScore)); //initializes in 0
    scoreTextBox->setPos(scene->width()/2 - (scoreTextBox->textWidth()/4), scene->height()/8);

    if(playerLost)
    {
        //Stop timers
        scoreTimer->stop();
        spawnTimer->stop();
        enemiesRandomnessUpdater->stop();
        musicTimer->stop();
        //Stop music
        backgroundMusic->stop();
        displayLostMessage();
        //Display Score;
        scoreTextBox->setDefaultTextColor(Qt::red);
        scoreTextBox->setPlainText("You Lost\nScore: "+ QString::number(playerScore));

    }
}

void Game::displayLostMessage()
{
    //rip
}
