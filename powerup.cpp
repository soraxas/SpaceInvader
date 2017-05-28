#include "powerup.h"
#include "gamedialog.h"

#define DELTA_X_PER_TICK 3
#define MAX_DELTA_X 35

#define Y_DESCEND_PER_TICK 2

namespace game {

Powerup::Powerup(PowerupType type, int x, int y, int radius) :
    radius(radius), type(type), centerX(x), centerY(y), deltaX(0)
{}

void Powerup::draw(QPainter* p){
    p->setPen(Qt::NoPen);

    switch(type){
    case(MachineGunPowerup):
        p->setPen(Qt::green);
        p->setBrush(Qt::green);
        break;
    case(LaserPowerup):
        p->setPen(Qt::magenta);
        p->setBrush(Qt::magenta);
        break;
    case(PenPowerup):
        p->setPen(Qt::red);
        p->setBrush(Qt::red);
    }

    p->drawEllipse(x(), y(), radius*2, radius*2);
}
void Powerup::update(){
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
