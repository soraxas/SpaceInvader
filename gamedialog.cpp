#include "gamedialog.h"
#include "bullet.h"
#include "ship.h"
#include <QDebug>
#include <QKeyEvent>
#include <QPainter>
#include <QPixmap>
#include <QSound>
#include <QTimer>
#include <QWidget>
#include <vector>
#include <QCursor>
#include <QtMath>
#include <QTime>

#define CURSOR_BASE_RADIUS 50
#define STATUS_BAR_HEIGHT 100

#define POWERUP_DROP_RATE 100

namespace game {

GameDialog::GameDialog(QWidget* parent)
    : QDialog(parent), bullets(), shipFiringSound(this), debugMode(false),
      gameScore(0), statusBar(this), bg(500, 500), cursor(this) {
    // SET UP GAME DIMENSIONS AND CONFIG
    c = Config::getInstance();
    swarms = NULL;
    SCALEDWIDTH = c->get_SCALEDWIDTH();
    SCALEDHEIGHT = c->get_SCALEDHEIGHT();
    STATUSBARHEIGHT = STATUS_BAR_HEIGHT;
    this->frames = c->get_frames();
    this->playerOverride = false;
    this->bg = Background(SCALEDWIDTH, SCALEDHEIGHT);
    timerModifier = 1.0;
    GameDialog::SeedRandInt(); // seed the random number generator

    // MENU
    QList<QPair<QString, int>> dummy;
    menu = new Menu(this, c->get_name(), this->gameScore, dummy);

    // EXTENSION STAGE 1 PART 1 - RESCALE GAME SCREEN FOR SHIP SIZE
    this->setFixedWidth(SCALEDWIDTH);
    this->setFixedHeight(SCALEDHEIGHT + STATUSBARHEIGHT);
    // resize menu as well
    gameMenu.setFixedWidth(SCALEDWIDTH*0.6);
    gameMenu.setFixedHeight((SCALEDHEIGHT + STATUSBARHEIGHT)*0.6);

    // SHIP
    QPixmap ship;
    if(c->shipUseXwing){
        ship.load(":/Images/ship_xwing.png");
    }else{
        ship.load(":/Images/ship.png");
    }
    this->ship = new Ship(ship, c->get_scale(), c->get_startpos(), SCALEDHEIGHT);
    this->next_instruct = 0;
    // SHIP SOUND
    shipFiringSound.setSource(QUrl::fromLocalFile(":/Sounds/shoot.wav"));
    shipFiringSound.setVolume(0.3);

    // set the stage
    if(c->getSwarmList().size() <= 1)
        curStageNum = 0; // default stage 0 (legacy mode)
    else
        curStageNum = 1;
    // ALIENS
    generateAliens(c->getSwarmList()[curStageNum]);

    // SET BACKGROUND
    setStyleSheet("background-color: #000000;");
    statusBar.buildBrush();

    paused = false;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(static_cast<int>(this->frames * timerModifier));

    // track mouse for extension
    this->setMouseTracking(true);

    update();

    // set the cursor
    cursor.radius = CURSOR_BASE_RADIUS * c->get_scale();
    cursor.setCursorState(NORMAL);
}

GameDialog::~GameDialog() {
    delete ship;
    delete timer;  // optional, don't have to do this apparently
    delete menu;

    // loop though swarms to delete aliens
    delete swarms;  // recursively deletes itself.
    for (Bullet* b : bullets) {
        delete b;
    }
}

// make the swarms for this level.
void GameDialog::generateAliens(const QList<SwarmInfo>& makeSwarms) {
    if(swarms)
        delete swarms;
    SwarmInfo def = SwarmInfo();

    swarms = new Swarm(def, *this->ship);
    for (SwarmInfo info : makeSwarms) {
        AlienBase* s = new Swarm(info, *this->ship);
        swarms->add(s);
    }
}

void GameDialog::pauseStart() {
    if (this->paused) {
        gameMenu.hide();
        // start game
        this->paused = false;
        this->menu->displayMenu(paused);
        this->timer->start(static_cast<int>(frames * timerModifier));
    } else {
        gameMenu.show();
        this->paused = true;
        this->menu->displayMenu(paused);
        this->timer->stop();
    }
}

void GameDialog::keyPressEvent(QKeyEvent* event) {
    // Deal with overriding config file
    if(!playerOverride){
        switch(event->key()){
        case(Qt::Key_Left):
        case(Qt::Key_Right):
        case(Qt::Key_A):
        case(Qt::Key_D):
        case(Qt::Key_Space):
            playerOverride = true;
        }
    }

    switch(event->key()){
    case(Qt::Key_P):
    case(Qt::Key_Escape):
        pauseStart();
        break;
    case(Qt::Key_Left):
        pressedKeys[Qt::Key_Left] = true;
        break;
    case(Qt::Key_Right):
        pressedKeys[Qt::Key_Right] = true;
        break;
    case(Qt::Key_A):
        pressedKeys[Qt::Key_A] = true;
        break;
    case(Qt::Key_D):
        pressedKeys[Qt::Key_D] = true;
        break;
    case(Qt::Key_Space):
        pressedKeys[Qt::Key_Space] = true;
        break;
    case(Qt::Key_F1):
        debugMode = !debugMode;
        break;
    case(Qt::Key_F2):
        timerModifier += 0.1;
        timer->start(c->get_frames() * timerModifier);
        qDebug() << QString::number(1/timerModifier);
        break;
    case(Qt::Key_F3):
        timerModifier -= 0.1;
        timer->start(c->get_frames() * timerModifier);
        qDebug() << QString::number(1/timerModifier);
        break;
    }

    // the debug / Cheat mode key map
    if(debugMode){
        switch(event->key()){
        case(Qt::Key_C):
        {
            // cycle through each cursor state
            int s = cursor.state;
            if(++s == END_OF_CURSOR_STATE)
                s = 0; // loop back to zero (NORMAL STATE)
            cursor.setCursorState(static_cast<CURSOR_STATE>(s)); // assign the cursor state
        }
            break;
        case(Qt::Key_Plus):
            if(curStageNum + 1 >= c->getSwarmList().size())
                break;
            curStageNum++;
            qDebug() << "Generating stage " << QString::number(curStageNum);
            generateAliens(c->getSwarmList()[curStageNum]);
            break;

        case(Qt::Key_Minus):
            if(curStageNum - 1 <= 0)
                break;
            curStageNum--;
            qDebug() << "Generating stage " << QString::number(curStageNum);
            generateAliens(c->getSwarmList()[curStageNum]);
            break;
        }
    }
}

void GameDialog::keyReleaseEvent(QKeyEvent* event) {
    switch(event->key()){
    case(Qt::Key_Left):
        pressedKeys[Qt::Key_Left] = false;
        break;
    case(Qt::Key_Right):
        pressedKeys[Qt::Key_Right] = false;
        break;
    case(Qt::Key_A):
        pressedKeys[Qt::Key_A] = false;
        break;
    case(Qt::Key_D):
        pressedKeys[Qt::Key_D] = false;
        break;
    case(Qt::Key_Space):
        pressedKeys[Qt::Key_Space] = false;
        break;
    }
}


void GameDialog::mousePressEvent(QMouseEvent* event){
    cursor.getCurState()->processMousePress(event);
}
void GameDialog::mouseReleaseEvent(QMouseEvent* event){
    cursor.getCurState()->processMouseRelease(event);
}
void GameDialog::mouseMoveEvent(QMouseEvent* event){
    cursor.getCurState()->processMouseEvent(event);
}

// shows this game score
void GameDialog::showScore() {
    // in future, implement 'score list' in menu.
    menu->openScore();
}

// FOLLOWING EACH INSTRUCTION TO FRAME - for PLAYER ship.
void GameDialog::nextFrame() {

    if (!paused) {
        Config* c = Config::getInstance();

        QStringList instruct = c->get_instructs();
        if (next_instruct >= instruct.size()) {
            next_instruct = next_instruct % instruct.size();
        }
        QString ins = instruct[next_instruct];
        next_instruct++;

        if(!playerOverride){
            if (ins == "Left") {
                ship->move_left();
            } else if (ins == "Right") {
                ship->move_right();
            } else if (ins == "Shoot") {
                Bullet* b = this->ship->shoot();
                if(b){
                    bullets.push_back(b);
                    this->shipFiringSound.play();
                }
            }
        }else{ // use user input keys
            if (pressedKeys[Qt::Key_Left] || pressedKeys[Qt::Key_A]) {
                ship->move_left();
            }
            if (pressedKeys[Qt::Key_Right] || pressedKeys[Qt::Key_D]) {
                ship->move_right();
            }
            if (pressedKeys[Qt::Key_Space]) {
                Bullet* b = this->ship->shoot();
                if(b){
                    bullets.push_back(b);
                    this->shipFiringSound.play();
                }
            }
        }

        cursor.getCurState()->update(); // update cursor
        updateBullets(); //update bullets
        ship->update(); //update ship
        bg.nextFrame(); //update background
        // update explosions
        for(Explosion& e: explosions)
            e.nextFrame();
        // update powerup
        for(Powerup& p : powerups)
            p.update();
        // update status bar
        statusBar.update();

        // loop through each alien swarm, move and calculated collisions
        swarms->move("");  // recursive.
        checkSwarmCollisions(swarms);
        addBullets(swarms->shoot(""));
    }
    // prepare collisions and calculate score
    update();
}

void GameDialog::paintBullets(QPainter& painter) {
    for (int i = 0; i < bullets.size(); i++) {
        Bullet* b = bullets[i];
        painter.drawPixmap(b->get_x(), b->get_y(), b->get_image());
    }
}

bool GameDialog::updateBullets_barrierChkHelper(int x, int y){
    // check if the given x, y is hit with the barrier block
    std::vector<BarrierBlock>::iterator it = barriers.begin();
    while (it != barriers.end()) {
        BarrierBlock b = (*it);
        if(x >= b.x && x <= b.x + b.width &&
                y >= b.y && y <= b.y + b.width){
            // delete the barrier and return true
            it = barriers.erase(it);
            return true;
        }
        ++it;
    }
    return false;
}

void GameDialog::updateBullets()
{
    for (int i = 0; i < bullets.size(); i++) {
        Bullet* b = bullets[i];
        // WHEN BULLET OFF GAME SCREEN, FREE MEMORY AND DELETE
        int score = get_collided(b, swarms);

        if (b->get_y() < 0 || b->get_y() >= SCALEDHEIGHT || /* out of screen in Y */
                b->get_x() < 0 || b->get_x() >= SCALEDWIDTH || /* out of screen in X */
                score > 0 || /* hit the ship */
                updateBullets_barrierChkHelper(b->get_x(), b->get_y())){ /* hit the barrier */
            delete b;
            bullets.erase(bullets.begin() + i);
            i--;
        } else if (score == -1) {
            // DEAD SHIP!
            ship->dead = true;
            explosions.push_back(Explosion(ship->get_x()+ship->get_image().width()/2,
                                           ship->get_y()+ship->get_image().height()/5,
                                           ship->get_image().width()*1.4, ShipExplosion));
            delete b;
            bullets.erase(bullets.begin() + i);
            i--;
        } else
        {
            b->move();// we move at the end so that we can see collisions before the game ends
        }
        gameScore += score;


    }
}

// recurse throughout the tree and draw everything.
// will also
void GameDialog::paintSwarm(QPainter& painter, AlienBase*& root) {
    for (AlienBase* child : root->getAliens()) {
        // if the child is a leaf (i.e., an alien that has no children), draw it.
        const QList<AlienBase*>& list = child->getAliens();
        if (list.size() == 0) {  // leaf
            painter.drawPixmap(child->get_x(), child->get_y(), child->get_image());
        } else {
            paintSwarm(painter, child);
        }
    }
}

//check if any aliens based off the alien root are crashing with the player ship.
void GameDialog::checkSwarmCollisions(AlienBase *&root)
{
    for (AlienBase* child : root->getAliens()) {
        // if the child is a leaf (i.e., an alien that has no children), check for collisions.
        const QList<AlienBase*>& list = child->getAliens();
        if (list.size() == 0) {  // leaf
            // check if it is crashing into the player ship
            if (child->collides(*this->ship)) {
                // DEAD SHIP AGAIN
                ship->dead = true;
                explosions.push_back(Explosion(ship->get_x()+ship->get_image().width()/2,
                                               ship->get_y()+ship->get_image().height()/5,
                                               ship->get_image().width()*1.4, ShipExplosion));
            }
        } else {
            checkSwarmCollisions(child);
        }
    }
}

// PAINTING THE SHIP AND ANY BULLETS
void GameDialog::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    // Draw background first
    bg.draw(&painter);

    // SHIP
    painter.drawPixmap(ship->get_x(), ship->get_y(), ship->get_image());

    // loop through each alien swarm and draw
    paintSwarm(painter, swarms);

    // Draw all the PowerUps
    for(Powerup p : powerups)
        p.draw(&painter);

    // BULLETS last so they draw over everything
    paintBullets(painter);

    // Draw all the barrier blocks
    for(BarrierBlock b: barriers)
        b.draw(&painter);

    // draw explosions
    std::vector<Explosion>::iterator it = explosions.begin();
    while (it != explosions.end()) {
        if((*it).finished) {
            it = explosions.erase(it);
            continue;
        }
        (*it).draw(&painter);
        ++it;
    }

    // draw status bar
    statusBar.draw(&painter);

    // draw debug info if needed
    if(debugMode)
        printDebugInfo(&painter);
}

// if this bullet is unfriendly, only check if it hits Ship
// if this bullet is friendly, will check the swarm;
// returns the score from the deleted hit object.
// Returns 0 if nothing hit, -ve if ship is hit.
int GameDialog::get_collided(Bullet*& b, AlienBase*& root) {
    int score = 0;
    // if it's an enemy bullet, then don't look at the swarm.
    if (!b->isFriendly()) {
        // check it hits the player ship
        if (b->collides(*this->ship)) {
            return -1;

        }  // future; add barriers here.
    } else {
        score = get_collided_swarm(b, root);

        if(score > 0){
            int r = c->get_scale() * 15;
            // randomly generate a powerup after killing an alien
            if(GameDialog::randInt(0, 100) > (100 - POWERUP_DROP_RATE)){ // 35% drop rate
                powerups.push_back(Powerup::generateRandomPowerup(b->get_x(), b->get_y() - r*2, r));
            }
        }
    }
    return score;
}

// helper function, recursively searches swarms.
int GameDialog::get_collided_swarm(Bullet*& b, AlienBase*& root) {
    int totalScore = 0;
    // Case 1: you are a leaf node, or root node
    if (root->getAliens().size() == 0) {
        // check collision.
        if (b->collides(*root)) {
            // if it is an alien, it will return >0.
            // if it's a swarm (i.e., root) it will return 0.
            return root->get_score();
        }

    } else {
        for (int i = 0; i < root->getAliens().size(); i++) {
            AlienBase* child = root->getAliens().at(i);
            // if it's another swarm, recurse down the tree
            totalScore += get_collided_swarm(b, child);
            // if something was hit, score > 0
            if (totalScore > 0 && child->getAliens().size() == 0) {
                // some children shoot more bullets when they die.
                // ask child for reaction when you're going to delete them
                addBullets(child->react());
                root->remove(child);
                i--;
                return totalScore;
            }
        }
    }
    return totalScore;
}

void GameDialog::addBullets(const QList<Bullet*>& list) {
    for (Bullet* b : list) {
        this->bullets.push_back(b);
    }
}

void GameDialog::printDebugInfo(QPainter* p){
    if(!debugMode)
        return;

    QFont f = p->font();
    f.setPointSize(12);
    p->setPen(Qt::yellow);
    p->setFont(f);
    int line_height = 18;
    QString str;

    // print keyboard hint
    p->drawText(5, line_height, "[F1] Toggle Cheat | [C] Change Cursor | [P] Pause/Resume | [-/+] Goto Prev/Next Stage");

    // print spaceship x, y
    str = "Spaceship [X:";
    str += QString::number(ship->get_x());
    str += " Y:";
    str += QString::number(ship->get_y()) + "]";
    p->drawText(20, line_height * 2, str);

    // print cursor state
    str = "Current Cursor: c";
    if (paused)
        str += "--PAUSED--";
    p->drawText(20, line_height * 3, str);
}

// HELPER FUNCTION
int GameDialog::randInt(int low, int high)
{
    // Random number between low and high
    return qrand() % ((high + 1) - low) + low;
}


void GameDialog::SeedRandInt()
{
    // seed the random int
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
}



}
