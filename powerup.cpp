#include "powerup.h"
#include "gamedialog.h"

#define DELTA_X_PER_TICK 3
#define MAX_DELTA_X 35
#define Y_DESCEND_PER_TICK 2
#define VISIBILITY_RATE 0.05
#define VISIBILITY_MAX 0.9
#define VISIBILITY_MIN 0.4

namespace game {
/**
    This defines the power up within the game environment
*/

Powerup::Powerup(PowerupType type, int x, int y, int radius) :
    radius(radius), type(type), turnToInvisable(true), alpha(1), centerX(x), centerY(y), deltaX(0)
{}

void Powerup::draw(QPainter* p){
    QPen pen;
    pen.setWidth(2);
    p->setBrush(Qt::gray);

    switch(type){
    case(MachineGunPowerup):
        pen.setColor(Qt::green);
        break;
    case(LaserPowerup):
        pen.setColor(Qt::magenta);
        break;
    case(PenPowerup):
        pen.setColor(Qt::red);
        break;
    }
    p->setPen(pen);
    p->setOpacity(alpha);
    p->drawEllipse(x(), y(), radius*2, radius*2);
    p->setOpacity(100);
    QPixmap pixmap;
    switch (type) {
    case(MachineGunPowerup):
        pixmap.load(":/Images/MachineGun.png");
        break;
    case(LaserPowerup):
        pixmap.load(":/Images/LaserGun.png");
        break;
    case(PenPowerup):
        pixmap.load(":/Images/pen.png");
    }
    pixmap = pixmap.scaledToWidth(radius * 1.5);

    p->drawPixmap(x() + radius*0.25, y() + radius*0.25, pixmap);

}

/**
    Update the power up's location and visibility
*/
void Powerup::update(){
    double rate = VISIBILITY_RATE;
    // slowly transite between invisible or visible
    if(turnToInvisable){
        alpha -= rate;
        if(alpha <= VISIBILITY_MIN)
            turnToInvisable = false;
    }else{
        alpha += rate;
        if(alpha >= VISIBILITY_MAX)
            turnToInvisable = true;
    }
    if(moveLeft){
        deltaX -= DELTA_X_PER_TICK;
        if(-deltaX > MAX_DELTA_X)
            moveLeft = false;
    }else{
        deltaX += DELTA_X_PER_TICK;
        if(deltaX > MAX_DELTA_X)
            moveLeft = true;
    }

    this->centerY += Y_DESCEND_PER_TICK;
}

int Powerup::x(){
    return centerX + deltaX;
}
int Powerup::y(){
    return centerY;
}

Powerup Powerup::generateRandomPowerup(int x, int y, int radius){
    // randomise the type of powerup
    int randomType= GameDialog::randInt(0, static_cast<int>(END_OF_POWERUP));
    if(randomType == END_OF_POWERUP)
        randomType--;
    PowerupType type = static_cast<PowerupType>(randomType);
    return Powerup(type, x, y, radius);
}
}
