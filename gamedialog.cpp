#include "gamedialog.h"
#include <QtDebug>

#define CURSOR_BASE_RADIUS 50
#define STATUS_BAR_HEIGHT 100
#define LEADERBOARD_FILENAME "../SpaceInvaders/LEADERBOARD.sav"
#define POWERUP_DROP_RATE 15 //35

namespace game {

/**
    The main class that controls all the functionality of the entire game. Constructor is
    in-charge to initialise every internal variabels and start in a title screen mode to
    wait for user input. One exception is when the config file does not exists or it is in
    an older-style, it will run in a legacy mode where the game will be function as the same
    in stage 2.
*/
GameDialog::GameDialog(QWidget* parent)
    : QDialog(parent), bullets(), stageMaker(this), debugMode(false),
      gameScore(0), statusBar(this), bg(500, 500), cursor(this), gameMenu(this, 0, POWERUP_DROP_RATE),
      swarms(NULL), leaderBoardNameRequest(LEADERBOARD_FILENAME, this), ship(NULL)
{
    // SET UP GAME DIMENSIONS AND CONFIG
    c = Config::getInstance();
    SCALEDWIDTH = c->get_SCALEDWIDTH();
    SCALEDHEIGHT = c->get_SCALEDHEIGHT();
    STATUSBARHEIGHT = STATUS_BAR_HEIGHT;
    this->frames = c->get_frames();
    // seed the random number generator
    GameDialog::SeedRandInt();

    // initialise all vairables
    laserBeam.exists = false;
    legacyMode = false;
    currentState = GAME_STATUS_TITLE_SCREEN;
    timerModifier = 1.0;
    powerUpDropRate = POWERUP_DROP_RATE;
    playerOverride = false;
    bg = Background(SCALEDWIDTH, SCALEDHEIGHT + STATUSBARHEIGHT);
    paused = false;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(static_cast<int>(this->frames * timerModifier));
    // MENU
    QList<QPair<QString, int>> dummy;
    menu = new Menu(this, c->get_name(), this->gameScore, dummy);
    // SET BACKGROUND
    setStyleSheet("background-color: #000000;");
    statusBar.buildBrush();
    // track mouse for extension
    this->setMouseTracking(true);
    // setup transition scence
    stageTransition = false;
    stageTransitionBox = QRect(SCALEDWIDTH, SCALEDHEIGHT*0.3, SCALEDWIDTH*0.5, SCALEDHEIGHT*0.3);
    // init internal variables
    initCommands();
    stageMaker.init();
    curStageNum = 0; // default stage 0
    this->next_instruct = 0;

    commandClearStage->execute();
    // test for legacy mode
    if(c->getSwarmList().size() <= 1){
        // if it is an old-style config file. Use legacy Mode
        legacyMode = true;
        STATUSBARHEIGHT = 0;
    }
    // SHIP
    QPixmap ship;
    if(legacyMode)
        ship.load(":/Images/ship.png");
    else
        ship.load(":/Images/ship_xwing.png");
    this->ship = new Ship(ship, c->get_scale(), c->get_startpos(), SCALEDHEIGHT);
    leaderBoard.init(SCALEDWIDTH, SCALEDHEIGHT + STATUSBARHEIGHT, LEADERBOARD_FILENAME);
    // EXTENSION STAGE 1 PART 1 - RESCALE GAME SCREEN FOR SHIP SIZE
    this->setFixedWidth(SCALEDWIDTH);
    this->setFixedHeight(SCALEDHEIGHT + STATUSBARHEIGHT);
    // resize menu as well
    gameMenu.setFixedWidth(SCALEDWIDTH*0.6);
    gameMenu.setFixedHeight((SCALEDHEIGHT + STATUSBARHEIGHT)*0.6);

    update();
    // set the cursor
    cursor.radius = CURSOR_BASE_RADIUS * c->get_scale();
    cursor.setCursorState(NORMAL);
    if(legacyMode){
        // if legacy, always in game
        currentState = GAME_STATUS_IN_GAME;
        QList<SwarmInfo> infos = c->getSwarmList()[0];
        generateAliens(infos);
    }
    // play background music
    if(!legacyMode)
        QTSoundPlayer::getInstance()->playBgMusic();
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

/**
    Helper method to initialise every command design pattern
*/
void GameDialog::initCommands(){
    commandGameStart = std::unique_ptr<Command>(new CommandGameStart(this));
    commandGamePause = std::unique_ptr<Command>(new CommandGamePause(this));
    commandClearStage = std::unique_ptr<Command>(new CommandClearStage(this));
    commandRestartStage = std::unique_ptr<Command>(new CommandRestartStage(this));
    commandGoToTitleScreenMode = std::unique_ptr<Command>(new CommandGotoTitleScreenMode(this));
    commandGoToGameMode = std::unique_ptr<Command>(new CommandGotoGameMode(this));
    commandGoToStageMakerMode = std::unique_ptr<Command>(new CommandGotoStageMakerMode(this));
    commandGoToLeaderBoardMode = std::unique_ptr<Command>(new CommandGotoLeaderBoardMode(this));
}

/**
    Given a list of swarm info, generate aliens

    @param list of swarm information
*/
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

/**
    Count the number of aliens on screen

    @param the root of swarm pointer
    @return number of aliens in that composite design pattern
*/
int GameDialog::countAliens(AlienBase* root){
    // given an alien base, return the recursive number of descendants
    int num = 0;
    for(AlienBase* child : root->getAliens()){
        num += countAliens(child);
    }
    // base case if this root is the global pointer swarms, decrease one
    if(root == swarms || root->getAliens().size() != 0)
        return num;
    return num + 1;
}

/**
    QT event that triggers when a key was pressed

    @param QKeyevent of the triggers
*/
void GameDialog::keyPressEvent(QKeyEvent* event) {
    // if it is legacy mdoe, limits the available functionality
    if(legacyMode){
        if(event->key() == Qt::Key_P){
            if(paused)
                commandGameStart->execute();
            else
                commandGamePause->execute();
        }
        return;
    }

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
        if(currentState == GAME_STATUS_STAGE_MAKER_TESTING){
            // special case of stage maker state
            commandGoToStageMakerMode->execute();
            return;
        }
        // show the main game menu
        commandGamePause->execute();
        gameMenu.show();
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
        case(Qt::Key_Z):
        {
            // cycle through each cannon
            int s = ship->cannonType;
            if(++s == END_OF_CANNON_TYPE)
                s = 0; // loop back to zero (NORMAL STATE)
            ship->cannonType = static_cast<CannonType>(s); // assign the cursor state
            ship->cannonAmmo = 100;
        }
            break;
        case(Qt::Key_R):
            commandRestartStage->execute();
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
        case(Qt::Key_F11):
            powerups.push_back(Powerup::generateRandomPowerup(GameDialog::randInt(0, SCALEDWIDTH), 0 - c->get_scale() * 20*2, c->get_scale() * 20));
            break;
        case(Qt::Key_F12):

            delete swarms;
            SwarmInfo def = SwarmInfo();
            swarms = new Swarm(def, *this->ship);
            qDebug() << "Clearing all aliens";
            break;
        }
    }
}

/**
    QT event triggers when a key is pressed

    @param QKey event
*/
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
        laserBeam.exists = false;
        break;
    }
}

/**
    QT event triggers when mouse is pressed

    @param QMouse event
*/
void GameDialog::mousePressEvent(QMouseEvent* event){
    cursor.getCurState()->processMousePress(event);
}
/**
    QT event triggers when mouse is released

    @param QMouse event
*/
void GameDialog::mouseReleaseEvent(QMouseEvent* event){
    cursor.getCurState()->processMouseRelease(event);
}
/**
    QT event triggers when mouse is moved within the dialog box

    @param QMouse event
*/
void GameDialog::mouseMoveEvent(QMouseEvent* event){
    cursor.getCurState()->processMouseEvent(event);
}

/**
    show the game score

*/
void GameDialog::showScore() {
    // in future, implement 'score list' in menu.
    menu->openScore();
}

void GameDialog::requestName(QString info){
    if(legacyMode) // do nothing in legacy mode
        return;
    if(currentState != GAME_STATUS_IN_GAME)
        // do nothing if the player is not playing the game
        return;
    leaderBoardNameRequest.ui->infoText->setText(info);
    leaderBoardNameRequest.show();
}

// FOLLOWING EACH INSTRUCTION TO FRAME - for PLAYER ship.
void GameDialog::nextFrame() {
    if (!paused) {
        switch(currentState){
        case(GAME_STATUS_IN_GAME):
        case(GAME_STATUS_STAGE_MAKER_TESTING):
            // we only update these things when the aliens / ship should be shown on screen
        {
            if(currentState == GAME_STATUS_IN_GAME){
                // we only check for stage transition if we are in the main game
                if(countAliens(swarms) <= 0){
                    // check if all aliens are dead
                    if(!stageTransition){
                        // if we are not transitioning and we have no aliens, then we should go to next stage.
                        // see if there's a next stage
                        if(curStageNum + 1 < c->getSwarmList().size()){
                            // yes there is, go to next stage
                            stageTransition = true;
                            stageTransitionBox.moveTo(SCALEDWIDTH, stageTransitionBox.y()); // move the box
                            ++curStageNum;
                        }else{
                            // finished all stage!
                            laserBeam.exists = false;
                            requestName("You WON!!! Congratuations, enter your name for the leader board!");
                        }
                    }else{
                        // we are transitioning to next stage. mvoe the transition box
                        stageTransitionBox.moveTo(stageTransitionBox.x() - 15, stageTransitionBox.y());
                        if(stageTransitionBox.right() < 0){
                            // only starts when the stage transition box has pass through entire screen
                            stageTransition = false;
                            // generatte all aliens
                            generateAliens(c->getSwarmList()[curStageNum]);
                        }
                    }
                }
            }
            ////////////////////////////////////////////
            //// NOW update all items within screen
            ////////////////////////////////////////////
            if(!ship->dead){
                // if the ship is dead, we do not need to update it
                Config* c = Config::getInstance();
                // get instructions
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
                            QTSoundPlayer::getInstance()->play(SOUND_Ship_Fire);
                        }else{

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
                        // special case of laser shooting
                        if(ship->cannonType == Laser && ship->cannonAmmo > 0){
                            laserBeam.exists = true;
                            laserBeam.originX = ship->get_x();
                            laserBeam.originY = ship->get_y();
                            laserBeam.width = ship->get_image().width() * 0.18  ;
                            ship->cannonAmmo -= 2;
                            if(ship->cannonAmmo <= 0){
                                ship->cannonType = Normal;
                                laserBeam.exists = false;
                            }
                        }else{
                            Bullet* b = this->ship->shoot();
                            if(b){
                                bullets.push_back(b);
                                QTSoundPlayer::getInstance()->play(SOUND_Ship_Fire);
                            }
                        }
                    }
                }
                ////////////////////////////////////////////
                //// update laser gun
                ////////////////////////////////////////////
                // loop through the recursive aliens, put in stack first
                if(laserBeam.exists){
                    std::stack<AlienBase*> stack;
                    stack.push(swarms);
                    while(stack.size() > 0){
                        AlienBase* root = stack.top();
                        stack.pop();
                        for(AlienBase* child: root->getAliens()){
                            if(child->getAliens().size() == 0){
                                // base case, check for collision
                                if(child->get_x() > laserBeam.originX && child->get_x() < laserBeam.originX + laserBeam.width){
                                    // create explosion at the place of alien
                                    explosions.push_back(Explosion(child->get_x()+child->get_image().width()/2,
                                                                   child->get_y()+child->get_image().height()/5,
                                                                   child->get_image().height()*1.2, SmallExplosion));
                                    addBullets(child->react());
                                    this->gameScore += child->get_score();
                                    root->remove(child);
                                    break;
                                }
                            }else{
                                stack.push(child);
                            }
                        }
                    }
                }
                ////////////////////////////////////////////
                //// Update power ups in screen
                ////////////////////////////////////////////
                // check collision of powerups with ship
                std::vector<Powerup>::iterator pit = powerups.begin();
                while (pit != powerups.end()) {
                    Powerup p = (*pit);
                    // checking if those two overlaps
                    if(ship->get_x() < (p.x()+p.radius*2) &&
                            ship->get_x()+ship->get_image().width() > p.x() &&
                            ship->get_y() < p.y()+p.radius*2 &&
                            ship->get_y()+ship->get_image().height() > p.y()){
                        laserBeam.exists = false;
                        //apply power up to ship and delete powerups
                        switch(p.type){
                        case(PenPowerup):
                            cursor.setCursorState(PEN);
                            break;
                        case(LaserPowerup):
                            ship->cannonType = Laser;
                            ship->cannonAmmo = 200;
                            break;
                        case(MachineGunPowerup):
                            ship->cannonType = MachineGun;
                            ship->cannonAmmo = 50;
                            break;
                        }
                        pit = powerups.erase(pit);
                        continue;
                        // power ups out of screen
                    }else if (p.y() > SCALEDHEIGHT) {
                        pit = powerups.erase(pit);
                        continue;
                    }
                    ++pit;
                }
                ship->update(); //update ship locations
            }

            updateBullets(); //update bullets locations

            if(!legacyMode){
                cursor.getCurState()->update(); // update cursor
                // update explosions
                for(Explosion& e: explosions)
                    e.nextFrame();
                // update powerup
                for(Powerup& p : powerups)
                    p.update();
                // update status bar
                statusBar.update();
            }

            // loop through each alien swarm, move and calculated collisions
            swarms->move("");  // recursive.
            checkSwarmCollisions(swarms);
            addBullets(swarms->shoot(""));

        }
            break;
        case(GAME_STATUS_LEADER_BOARD):
        {
            leaderBoard.update();
            if(leaderBoard.finished)
                commandGoToTitleScreenMode->execute();
        }
            break;
        }
        if(!legacyMode)
            bg.nextFrame(); //update background
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

        bool outOfScreen = (b->get_y() < 0 || b->get_y() >= SCALEDHEIGHT || /* out of screen in Y */
                            b->get_x() < 0 || b->get_x() >= SCALEDWIDTH); /* out of screen in X */
        if (outOfScreen || score > 0 || updateBullets_barrierChkHelper(b->get_x(), b->get_y())){ /* hit the barrier */
            // bullet shoud get destoryed
            delete b;
            bullets.erase(bullets.begin() + i);
            i--;
            if(!outOfScreen && !legacyMode){
                explosions.push_back(Explosion(b->get_x()+b->get_image().width()/2,
                                               b->get_y()+b->get_image().height()/5,
                                               b->get_image().height()*1.4, SmallExplosion));
            }
        } else if (score == -1) {
            if(legacyMode)
                close();
            if(ship->dead){
                b->move();
                return;
            }
            explosions.push_back(Explosion(ship->get_x()+ship->get_image().width()/2,
                                           ship->get_y()+ship->get_image().height()/5,
                                           ship->get_image().width()*1.4, ShipExplosion));
            // DEAD SHIP!
            ship->dead = true;
            delete b;
            bullets.erase(bullets.begin() + i);
            i--;
            requestName("Oh no you are DEAD. Enter your name to compare to others.");
            return;
        } else
        {
            b->move();// we move at the end so that we can see collisions before the game ends
        }
        if(score > 0)
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
    QList<AlienBase*> childList = root->getAliens();
    for (int i = 0; i < childList.size(); ++i) {
        // if the child is a leaf (i.e., an alien that has no children), check for collisions.
        const QList<AlienBase*>& list = childList[i]->getAliens();
        if (list.size() == 0) {  // leaf
            if(dynamic_cast<Swarm*>(childList[i]) != NULL){
                // detele empty swarm list
                root->remove(childList[i]);
                continue;
            }

            // check if it is crashing into the player ship
            if (childList[i]->collides(*this->ship)) {
                // DEAD SHIP AGAIN
                if(legacyMode)
                    close();
                ship->dead = true;
                explosions.push_back(Explosion(ship->get_x()+ship->get_image().width()/2,
                                               ship->get_y()+ship->get_image().height()/5,
                                               ship->get_image().width()*1.4, ShipExplosion));

                requestName("Oh no you are DEAD. Enter your name to compare to others.");
                return;
            }
        } else {
            checkSwarmCollisions(childList[i]);
        }
    }
}

void GameDialog::paintLaserBeam(QPainter& painter){
    // draw laser beam
    if(laserBeam.exists){
        painter.setPen(Qt::NoPen);
        // outer laser beam
        painter.setBrush(Qt::blue);
        painter.drawRect(laserBeam.originX + ship->get_image().width()/2 - laserBeam.width/2, 0,
                         laserBeam.width, laserBeam.originY + ship->get_image().height()/2);
        // inner laser beam
        painter.setBrush(Qt::white);
        painter.drawRect(laserBeam.originX + ship->get_image().width()/2 - laserBeam.width/4, 0,
                         laserBeam.width/2, laserBeam.originY + ship->get_image().height()/2);
    }
}

void GameDialog::paintTitleScreen(QPainter& painter){
    // if it is in title screen, draw the title and ignore others
    if(currentState == GAME_STATUS_TITLE_SCREEN){
        QPixmap pixmap;
        pixmap.load(":/Images/SpaceInvaderTitle.png");
        pixmap = pixmap.scaledToWidth(SCALEDWIDTH * 0.4);
        painter.drawPixmap( (SCALEDWIDTH - pixmap.width())/2, pixmap.height(), pixmap);
        painter.setPen(QColor::fromRgb(72, 240, 120));
        painter.save();
        QFont f("Tahoma");
        f.setPixelSize(SCALEDWIDTH * 0.04);
        painter.setFont(f);
        painter.drawText(0, SCALEDHEIGHT*0.4, SCALEDWIDTH, SCALEDHEIGHT*0.6, Qt::AlignCenter, "Press [ESC] to enter menu");
        painter.restore();
        return;
    }
}

void GameDialog::paintStageTransition(QPainter& painter){
    painter.save();
    QFont f = painter.font();
    f.setPixelSize(100);
    f.setBold(true);
    painter.setFont(f);
    // draw the transition scence
    painter.setPen(Qt::red);
    QString str = "Stage " + QString::number(curStageNum);
    painter.drawText(stageTransitionBox, Qt::AlignCenter, str);
    painter.restore();
}

// PAINTING THE SHIP AND ANY BULLETS
void GameDialog::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    if(!legacyMode){
        // Draw background first
        bg.draw(&painter);

        paintLaserBeam(painter);
        paintTitleScreen(painter);
    }

    if(currentState == GAME_STATUS_LEADER_BOARD){
        leaderBoard.draw(&painter);
        return;
    }

    // if it is currently transiting stage, draw the transititon animation
    if(stageTransition)
        paintStageTransition(painter);

    // Stage Maker MODE!
    if(currentState == GAME_STATUS_STAGE_MAKER_TESTING || currentState == GAME_STATUS_STAGE_MAKER)
        stageMaker.draw(&painter);


    if(currentState == GAME_STATUS_IN_GAME || currentState == GAME_STATUS_STAGE_MAKER_TESTING){
        // SHIP
        if(!ship->dead)
            painter.drawPixmap(ship->get_x(), ship->get_y(), ship->get_image());

        // loop through each alien swarm and draw
        paintSwarm(painter, swarms);

        // BULLETS last so they draw over everything
        paintBullets(painter);

        if(!legacyMode){
            // Draw all the PowerUps
            for(Powerup& p : powerups)
                p.draw(&painter);

            // Draw all the barrier blocks
            for(BarrierBlock& b: barriers)
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
            if(currentState == GAME_STATUS_IN_GAME)
                statusBar.draw(&painter);
        }
        // draw debug info if needed
        if(debugMode)
            printDebugInfo(&painter);
    }
}

/**
    if this bullet is unfriendly, only check if it hits Ship
    if this bullet is friendly, will check the swarm;
    returns the score from the deleted hit object.
    Returns 0 if nothing hit, -ve if ship is hit.
*/
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
            int r = c->get_scale() * 20;
            // randomly generate a powerup after killing an alien
            if(GameDialog::randInt(0, 100) > (100 - powerUpDropRate)){ // 35% drop rate
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
            if (child->getAliens().size() == 0 && totalScore > 0) {
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
    p->drawText(5, line_height, "[F1] Toggle Cheat | [C] Change Cursor | [Z] Change Cannon| [F11] Spawn powerups | [F12] Clear Stage");

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

    // print cursor state
    str = "Remaining Aliens: " + QString::number(countAliens(swarms));
    p->drawText(20, line_height * 4, str);
}

// HELPER FUNCTION for random number generate
int GameDialog::randInt(int low, int high){
    // Random number between low and high
    return qrand() % ((high + 1) - low) + low;
}


void GameDialog::SeedRandInt() {
    // seed the random int
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
}

}
