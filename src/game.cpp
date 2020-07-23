#include "game.h"

Game::Game(MainWindow* parentWindow)
    : parentWindow(parentWindow)
    , scene(nullptr)
    , center(nullptr), player(nullptr)
    , spawnTimer(nullptr), scoreTimer(nullptr), enemiesRandomnessUpdater(nullptr), musicTimer(nullptr)
    , backgroundMusic(nullptr)
{
    //seed
    std::srand (time(NULL));
}

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
    //Initialize buttons
    initButtons();
}

void Game::initScene()
{
    scene = new QGraphicsScene();
    setScene(scene);
    scene->setBackgroundBrush(Qt::black);

    //Set a fixed size for both the scene and viewer
    this->setFixedSize(screenWidth,screenHeight);
    scene->setSceneRect(0,0,screenWidth,screenHeight);

    //Eliminate scroll bars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

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

    //Create a timer for closing speed variation
    enemiesRandomnessUpdater = new QTimer();

    //Create a timer for background music
    musicTimer = new QTimer();

    //Connect every timer to their respective update methods
    QObject::connect(spawnTimer, &QTimer::timeout, this, &Game::spawnEnemy);
    QObject::connect(scoreTimer, &QTimer::timeout, this, &Game::updateScore);
    QObject::connect(enemiesRandomnessUpdater, &QTimer::timeout, this, &Game::updateEnemiesRandomness);
    QObject::connect(musicTimer, &QTimer::timeout, this, &Game::playBackgroundMusic);

    runTimers();
}

void Game::runTimers()
{
    //Since it will be called after 10 seconds, we create a random closing speed at run.
    enemiesClosingSpeed = lastClosingSpeed = 5;
    //Assign updating intervals
    scoreTimer->start(10); //Every 10ms
    spawnTimer->start(spawnrate); //In milisenconds.
    enemiesRandomnessUpdater->start(10000); //Every 10 seconds
    musicTimer->start(219000); //Loop music
}

void Game::updateEnemiesRandomness()
{
    int spawnIntervals[] = {500,750,1000,1250,1500};

    spawnTimer->start( spawnIntervals[rand()%3]);

    int newClonsingSpeed = (rand() % 10) + 3;
    if( newClonsingSpeed - 1 < lastClosingSpeed)
    {
        enemiesClosingSpeed = lastClosingSpeed = lastClosingSpeed -1 ;
    }
    else
    {
        enemiesClosingSpeed = lastClosingSpeed = newClonsingSpeed;
    }
}

void Game::initScore()
{
    //Se establece el font y color del score
    scoreTextBox->setDefaultTextColor(QColor(245,185,103));
    QFont font("Helvetica [Cronyx]",16);
    font.setCapitalization(QFont::AllUppercase);
    font.setStyle(QFont::StyleOblique);
    font.setWeight(QFont::DemiBold);
    font.setStyleStrategy(QFont::PreferAntialias);
    scoreTextBox->setFont(font);
    scoreTextBox->setTextWidth(200);
}

void Game::initButtons()
{
    //Create botons
    retryButton = new QPushButton("Retry",this);
    menuButton = new QPushButton("Main Menu",this);
    //Set button font
    retryButton->setFont(QFont("Helvetica [Cronyx]",20,QFont::DemiBold,true));
    menuButton->setFont(QFont("Helvetica [Cronyx]",20,QFont::DemiBold,true));
    //Set flags
    retryButton->setFlat(true);
    menuButton->setFlat(true);
    //Change styles
    retryButton->setStyleSheet("QPushButton {background-color: #000000; color: white; border:  none}");
    menuButton->setStyleSheet("QPushButton {background-color: #000000; color: white; border:  none}");
    //Set button dimensions
    retryButton->setGeometry(QRect(rect().width()/2 - retryButton->rect().width()/2,2*rect().height()/3,100,30));
    menuButton->setGeometry(QRect(rect().width()/2 - (menuButton->rect().width()/2)-25,2*(rect().height()+70)/3,150,30));
    //Connect buttons to their methods
    QObject::connect(retryButton,&QPushButton::clicked,this,&Game::restartGame);
    QObject::connect(menuButton,&QPushButton::clicked,this,&Game::endGame);
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
        //Stop player movement
        player->stopMovement();
        //Display Score;
        scoreTextBox->setDefaultTextColor(Qt::red);
        scoreTextBox->setPlainText("You Lost!\nScore: "+ QString::number(playerScore));
        //Display message in 500ms
        QTimer::singleShot(1000,this,&Game::displayLostMessage);
        this->setFocus();
    }
}

void Game::restartGame()
{
    //Hide buttons
    retryButton->hide();
    menuButton->hide();
    //Restart values
    playerLost = 0;
    playerScore = 0;
    //Restart timers
    scene->addItem(player);
    player->setFocus();
    runTimers();
    playBackgroundMusic();
    //Reset Score color
    scoreTextBox->setDefaultTextColor(QColor(245,185,103));
}

void Game::endGame()
{
    this->close();
    parentWindow->show();
}

void Game::displayLostMessage()
{
    //Add buttons to the scene
    retryButton->show();
    menuButton->show();
}
