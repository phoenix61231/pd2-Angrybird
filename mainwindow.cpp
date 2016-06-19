#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include <QSize>
#include <QPoint>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);

    scene->addPixmap(QPixmap(":/background.jpg").scaled(1000,500));
    QLCDNumber *lcd = new QLCDNumber();
    lcd->display(0);
    lcd->setGeometry(0,0,100,50);
    scene->addWidget(lcd);

    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());
    // Create ground (You can edit here)
    itemList.push_back(new Land(16,1.5,32,1,QPixmap(":/ground.png").scaled(width(),height()/6.0),world,scene));

    //Create Bow (mine)
    Land *bow;
    bow = new Land(5,6,0.7/2,3.5/8,QPixmap(":/bow.png").scaled(40,120),world,scene);
    itemList.push_back(bow);
    bow->getBody().SetActive(0);

    // Create Block (mine)
    block0 = new block(15.0f,4.0f,1,1,&timer,QPixmap(":/block3.png").scaled(60,60),world,scene);
    itemList.push_back(block0);
    block1 = new block(17.0f,4.0f,1,1,&timer,QPixmap(":/block3.png").scaled(60,60),world,scene);
    itemList.push_back(block1);
    block2 = new block(19.0f,4.0f,1,1,&timer,QPixmap(":/block3.png").scaled(60,60),world,scene);
    itemList.push_back(block2);

    block3 = new block(16.0f,6.0f,1,1,&timer,QPixmap(":/block3.png").scaled(60,60),world,scene);
    itemList.push_back(block3);
    block4 = new block(18.0f,6.0f,1,1,&timer,QPixmap(":/block3.png").scaled(60,60),world,scene);
    itemList.push_back(block4);
    block5 = new block(17.0f,8.0f,1,1,&timer,QPixmap(":/block3.png").scaled(60,60),world,scene);
    itemList.push_back(block5);

    block6 = new block(25.0f,4.0f,1,1,&timer,QPixmap(":/block3.png").scaled(60,60),world,scene);
    itemList.push_back(block6);
    block7 = new block(27.0f,4.0f,1,1,&timer,QPixmap(":/block3.png").scaled(60,60),world,scene);
    itemList.push_back(block7);
    block8 = new block(29.0f,4.0f,1,1,&timer,QPixmap(":/block3.png").scaled(60,60),world,scene);
    itemList.push_back(block8);
    block9 = new block(27.0f,6.0f,1,1,&timer,QPixmap(":/block3.png").scaled(60,60),world,scene);
    itemList.push_back(block9);
    block10 = new block(29.0f,6.0f,1,1,&timer,QPixmap(":/block3.png").scaled(60,60),world,scene);
    itemList.push_back(block10);
    block11 = new block(29.0f,8.0f,1,1,&timer,QPixmap(":/block3.png").scaled(60,60),world,scene);
    itemList.push_back(block11);

    //Create pig (mine)
    pig0 = new pig(17.0f,12.0f,0.6,&timer,QPixmap(":/pig0.png").scaled(50,50),world,scene);
    itemList.push_back(pig0);
    pig1 = new pig(29.0f,10.0f,0.6,&timer,QPixmap(":/pig0.png").scaled(50,50),world,scene);
    itemList.push_back(pig1);
    pig2 = new pig(27.0f,8.0f,0.6,&timer,QPixmap(":/pig0.png").scaled(50,50),world,scene);
    itemList.push_back(pig2);
    pig3 = new pig(25.0f,6.0f,0.5,&timer,QPixmap(":/pig1.png").scaled(50,50),world,scene);
    itemList.push_back(pig3);

    //Create Bird
    redbird = new Bird(7.0f,6.0f,0.5,&timer,QPixmap(":/bird.png").scaled(50,50),world,scene);
    redbird->setLinearVelocity(b2Vec2(0,0));
    itemList.push_back(redbird);

    blackbirdo = new blackbird(3.0f,6.0f,0.9,&timer,QPixmap(":/blackbird.png").scaled(60,60),world,scene);
    blackbirdo->setLinearVelocity(b2Vec2(0,0));
    itemList.push_back(blackbirdo);

    bluebirdo = new bluebird(11.0f,6.0f,0.35,&timer,QPixmap(":/bluebird.png").scaled(30,30),world,scene);
    bluebirdo->setLinearVelocity(b2Vec2(0,0));
    itemList.push_back(bluebirdo);

    yellowbirdo = new yellowbird(9.0f,6.0f,0.5,&timer,QPixmap(":/yellowbird.png").scaled(50,50),world,scene);
    yellowbirdo->setLinearVelocity(b2Vec2(0,0));
    itemList.push_back(yellowbirdo);

    whitebirdo = new whitebird(1.0f,6.0f,0.9,&timer,QPixmap(":/whitebird.png").scaled(60,60),world,scene);
    whitebirdo->setLinearVelocity(b2Vec2(0,0));
    itemList.push_back(whitebirdo);

    //Create Quit and Restart Button
    quitbutton = new QPushButton("Quit",this);
    quitbutton->setGeometry(QRect(QPoint(850,25),QSize(75,25)));
    restartbutton = new QPushButton("Restart",this);
    restartbutton->setGeometry(QRect(QPoint(850,0),QSize(75,25)));

    quitbutton->show();
    restartbutton->show();

    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));    
    connect(quitbutton, SIGNAL (released()), this, SLOT (quitbuttonfun()));
    connect(restartbutton, SIGNAL (released()), this, SLOT (restartbuttonfun()));
    timer.start(100/6);

}
bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    // Hint: Notice the Number of every event!
    QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);


    if(event->type() == QEvent::MouseButtonPress && redlaunched == 0)
    {
        redbird->getBody().SetActive(1);
        bluebirdo->getBody().SetActive(0);
        blackbirdo->getBody().SetActive(0);
        yellowbirdo->getBody().SetActive(0);
        whitebirdo->getBody().SetActive(0);

        int x = mouse_event->x()/30;
        int y = 17-mouse_event->y()/30;

        Bird *bird = redbird;
        bird->getBody().SetTransform(b2Vec2(x,y),0);

        bird->setLinearVelocity(b2Vec2((5-x)*5,(6-y)*5));
    }

    if(event->type() == QEvent::MouseButtonPress && tmp1==0)
    {
        redbird->getBody().SetActive(1);
        bluebirdo->getBody().SetActive(1);
        blackbirdo->getBody().SetActive(0);
        yellowbirdo->getBody().SetActive(0);
        whitebirdo->getBody().SetActive(0);

        int x = mouse_event->x()/30;
        int y = 17-mouse_event->y()/30;

        bluebird *bird = bluebirdo;
        bird->getBody().SetTransform(b2Vec2(x,y),0);

        bird->setLinearVelocity(b2Vec2((5-x)*5,(6-y)*5));
        bluelaunched = 0;

    }

    if(event->type() == QEvent::MouseButtonPress && tmp2==0)
    {
        redbird->getBody().SetActive(1);
        bluebirdo->getBody().SetActive(1);
        blackbirdo->getBody().SetActive(1);
        yellowbirdo->getBody().SetActive(0);
        whitebirdo->getBody().SetActive(0);

        int x = mouse_event->x()/30;
        int y = 17-mouse_event->y()/30;

        blackbird *bird = blackbirdo;
        bird->getBody().SetTransform(b2Vec2(x,y),0);

        bird->setLinearVelocity(b2Vec2((5-x)*5,(6-y)*5));
        blacklaunched = 0;

    }

    if(event->type() == QEvent::MouseButtonPress && tmp3==0)
    {

        redbird->getBody().SetActive(1);
        bluebirdo->getBody().SetActive(1);
        blackbirdo->getBody().SetActive(1);
        yellowbirdo->getBody().SetActive(1);
        whitebirdo->getBody().SetActive(0);
        int x = mouse_event->x()/30;
        int y = 17-mouse_event->y()/30;

        yellowbird *bird = yellowbirdo;
        bird->getBody().SetTransform(b2Vec2(x,y),0);

        bird->setLinearVelocity(b2Vec2((5-x)*5,(6-y)*5));
        yellowlaunched = 0;

    }

    if(event->type() == QEvent::MouseButtonPress && tmp4==0)
    {
        redbird->getBody().SetActive(1);
        bluebirdo->getBody().SetActive(1);
        blackbirdo->getBody().SetActive(1);
        yellowbirdo->getBody().SetActive(1);
        whitebirdo->getBody().SetActive(1);

        int x = mouse_event->x()/30;
        int y = 17-mouse_event->y()/30;

        whitebird *bird = whitebirdo;
        bird->getBody().SetTransform(b2Vec2(x,y),0);

        bird->setLinearVelocity(b2Vec2((5-x)*5,(6-y)*5));
        whitelaunched = 0;

    }

    if(event->type() == QEvent::MouseButtonPress)
    {
        std::cout << "Press !" << std::endl ;
        std::cout << redlaunched << std::endl ;
        std::cout << bluelaunched << std::endl ;
        //std::cout << blacklaunched << std::endl ;
        //std::cout << yellowlaunched << std::endl ;
        //std::cout << whitelaunched << std::endl ;

    }
    if(event->type() == QEvent::MouseMove)
    {
        /* TODO : add your code here */
        std::cout << "Move !" << std::endl ;
        std::cout << redlaunched << std::endl ;
        std::cout << bluelaunched << std::endl ;
        //std::cout << blacklaunched << std::endl ;
        //std::cout << yellowlaunched << std::endl ;
        //std::cout << whitelaunched << std::endl ;
    }
    if(event->type() == QEvent::MouseButtonRelease && redlaunched==0)
    {
        redlaunched = 1;
        tmp1 = 0;
    }
    if(event->type() == QEvent::MouseButtonRelease && bluelaunched==0)
    {
        bluelaunched = 1;
        tmp1 = 1;
        tmp2 = 0;
    }
    if(event->type() == QEvent::MouseButtonRelease && blacklaunched==0)
    {
        blacklaunched = 1;
        tmp2 = 1;
        tmp3 = 0;
    }
    if(event->type() == QEvent::MouseButtonRelease && yellowlaunched==0)
    {
        yellowlaunched = 1;
        tmp3 = 1;
        tmp4 = 0;
    }
    if(event->type() == QEvent::MouseButtonRelease && whitelaunched==0)
    {
        whitelaunched = 1;
        tmp4 = 1;
    }


    if(event->type() == QEvent::MouseButtonRelease)
    {
        /* TODO : add your code here */        
        std::cout << "Release !" << std::endl ;
        std::cout << redlaunched << std::endl ;
        std::cout << bluelaunched << std::endl ;
        //std::cout << blacklaunched << std::endl ;
        //std::cout << yellowlaunched << std::endl ;
        //std::cout << whitelaunched << std::endl ;
    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event    
    emit quitGame();
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();
}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
}

void MainWindow::quitbuttonfun()
{
    emit quitGame();
    this->close();
}

void MainWindow::restartbuttonfun()
{
    delete redbird;
    delete blackbirdo;
    delete bluebirdo;
    delete yellowbirdo;
    delete whitebirdo;

    delete block0;
    delete block1;
    delete block2;
    delete block3;
    delete block4;
    delete block5;
    delete block6;
    delete block7;
    delete block8;
    delete block9;
    delete block10;
    delete block11;

    delete pig0;
    delete pig1;
    delete pig2;
    delete pig3;

    redbird = new Bird(7.0f,6.0f,0.5,&timer,QPixmap(":/bird.png").scaled(50,50),world,scene);    
    itemList.push_back(redbird);    

    blackbirdo = new blackbird(3.0f,6.0f,0.9,&timer,QPixmap(":/blackbird.png").scaled(60,60),world,scene);
    blackbirdo->setLinearVelocity(b2Vec2(0,0));
    itemList.push_back(blackbirdo);

    bluebirdo = new bluebird(11.0f,6.0f,0.35,&timer,QPixmap(":/bluebird.png").scaled(30,30),world,scene);
    bluebirdo->setLinearVelocity(b2Vec2(0,0));
    itemList.push_back(bluebirdo);

    yellowbirdo = new yellowbird(9.0f,6.0f,0.5,&timer,QPixmap(":/yellowbird.png").scaled(50,50),world,scene);
    yellowbirdo->setLinearVelocity(b2Vec2(0,0));
    itemList.push_back(yellowbirdo);

    whitebirdo = new whitebird(1.0f,6.0f,0.9,&timer,QPixmap(":/whitebird.png").scaled(60,60),world,scene);
    whitebirdo->setLinearVelocity(b2Vec2(0,0));
    itemList.push_back(whitebirdo);

    block0 = new block(15.0f,4.0f,1,1,&timer,QPixmap(":/block3.png").scaled(60,60),world,scene);
    itemList.push_back(block0);
    block1 = new block(17.0f,4.0f,1,1,&timer,QPixmap(":/block3.png").scaled(60,60),world,scene);
    itemList.push_back(block1);
    block2 = new block(19.0f,4.0f,1,1,&timer,QPixmap(":/block3.png").scaled(60,60),world,scene);
    itemList.push_back(block2);

    block3 = new block(16.0f,6.0f,1,1,&timer,QPixmap(":/block3.png").scaled(60,60),world,scene);
    itemList.push_back(block3);
    block4 = new block(18.0f,6.0f,1,1,&timer,QPixmap(":/block3.png").scaled(60,60),world,scene);
    itemList.push_back(block4);
    block5 = new block(17.0f,8.0f,1,1,&timer,QPixmap(":/block3.png").scaled(60,60),world,scene);
    itemList.push_back(block5);

    block6 = new block(25.0f,4.0f,1,1,&timer,QPixmap(":/block3.png").scaled(60,60),world,scene);
    itemList.push_back(block6);
    block7 = new block(27.0f,4.0f,1,1,&timer,QPixmap(":/block3.png").scaled(60,60),world,scene);
    itemList.push_back(block7);
    block8 = new block(29.0f,4.0f,1,1,&timer,QPixmap(":/block3.png").scaled(60,60),world,scene);
    itemList.push_back(block8);
    block9 = new block(27.0f,6.0f,1,1,&timer,QPixmap(":/block3.png").scaled(60,60),world,scene);
    itemList.push_back(block9);
    block10 = new block(29.0f,6.0f,1,1,&timer,QPixmap(":/block3.png").scaled(60,60),world,scene);
    itemList.push_back(block10);
    block11 = new block(29.0f,8.0f,1,1,&timer,QPixmap(":/block3.png").scaled(60,60),world,scene);
    itemList.push_back(block11);

    //Create pig (mine)
    pig0 = new pig(17.0f,12.0f,0.6,&timer,QPixmap(":/pig0.png").scaled(50,50),world,scene);
    itemList.push_back(pig0);
    pig1 = new pig(29.0f,10.0f,0.6,&timer,QPixmap(":/pig0.png").scaled(50,50),world,scene);
    itemList.push_back(pig1);
    pig2 = new pig(27.0f,8.0f,0.6,&timer,QPixmap(":/pig0.png").scaled(50,50),world,scene);
    itemList.push_back(pig2);
    pig3 = new pig(25.0f,6.0f,0.5,&timer,QPixmap(":/pig1.png").scaled(50,50),world,scene);
    itemList.push_back(pig3);

}
